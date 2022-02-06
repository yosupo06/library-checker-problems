
#include <vector>
#include <utility>

namespace nachia{

// replacement for std::vector<std::vector<int>>
struct AdjacencyList{
public:
    struct AdjacencyListRange{
        using iterator = typename std::vector<int>::const_iterator;
        iterator begi, endi;
        iterator begin() const { return begi; }
        iterator end() const { return endi; }
        int size() const { return (int)std::distance(begi, endi); }
        const int& operator[](int i) const { return begi[i]; }
    };
private:
    int mn;
    std::vector<int> E;
    std::vector<int> I;
public:
    AdjacencyList(int n, std::vector<std::pair<int,int>> edges, bool rev){
        mn = n;
        std::vector<int> buf(n+1, 0);
        for(auto [u,v] : edges){ ++buf[u]; if(rev) ++buf[v]; }
        for(int i=1; i<=n; i++) buf[i] += buf[i-1];
        E.resize(buf[n]);
        for(int i=(int)edges.size()-1; i>=0; i--){
            auto [u,v] = edges[i];
            E[--buf[u]] = v;
            if(rev) E[--buf[v]] = u;
        }
        I = std::move(buf);
    }
    AdjacencyList(const std::vector<std::vector<int>>& edges = {}){
        int n = mn = edges.size();
        std::vector<int> buf(n+1, 0);
        for(int i=0; i<n; i++) buf[i+1] = buf[i] + edges[i].size();
        E.resize(buf[n]);
        for(int i=0; i<n; i++) for(int j=0; j<(int)edges[i].size(); j++) E[buf[i]+j] = edges[i][j];
        I = std::move(buf);
    }
    static AdjacencyList from_raw(std::vector<int> targets, std::vector<int> bounds){
        AdjacencyList res;
        res.mn = bounds.size() - 1;
        res.E = std::move(targets);
        res.I = std::move(bounds);
        return res;
    }
    AdjacencyListRange operator[](int u) const {
        return AdjacencyListRange{ E.begin() + I[u], E.begin() + I[u+1] };
    }
    int num_vertices() const { return mn; }
    int num_edges() const { return E.size(); }
    AdjacencyList reversed_edges() const {
        AdjacencyList res;
        int n = res.mn = mn;
        std::vector<int> buf(n+1, 0);
        for(int v : E) ++buf[v];
        for(int i=1; i<=n; i++) buf[i] += buf[i-1];
        res.E.resize(buf[n]);
        for(int u=0; u<n; u++) for(int v : operator[](u)) res.E[--buf[v]] = u;
        res.I = std::move(buf);
        return res;
    }
};



// replacement for std::vector<std::vector<Edge>>
//     while struct Edge { int to; int edgeidx; };
struct AdjacencyListEdgeIndexed{
public:
    struct Edge { int to; int edgeidx; };
    struct AdjacencyListRange{
        using iterator = typename std::vector<Edge>::const_iterator;
        iterator begi, endi;
        iterator begin() const { return begi; }
        iterator end() const { return endi; }
        int size() const { return (int)std::distance(begi, endi); }
        const Edge& operator[](int i) const { return begi[i]; }
    };
private:
    int mn;
    std::vector<Edge> E;
    std::vector<int> I;
public:
    AdjacencyListEdgeIndexed(int n, const std::vector<std::pair<int,int>>& edges, bool rev){
        mn = n;
        std::vector<int> buf(n+1, 0);
        for(auto [u,v] : edges){ ++buf[u]; if(rev) ++buf[v]; }
        for(int i=1; i<=n; i++) buf[i] += buf[i-1];
        E.resize(buf[n]);
        for(int i=(int)edges.size()-1; i>=0; i--){
            auto [u,v] = edges[i];
            E[--buf[u]] = { v, i };
            if(rev) E[--buf[v]] = { u, i };
        }
        I = std::move(buf);
    }
    AdjacencyListEdgeIndexed() : AdjacencyListEdgeIndexed(0, {}, false) {}
    AdjacencyListRange operator[](int u) const {
        return AdjacencyListRange{ E.begin() + I[u], E.begin() + I[u+1] };
    }
    int num_vertices() const { return mn; }
    int num_edges() const { return E.size(); }
    AdjacencyListEdgeIndexed reversed_edges() const {
        AdjacencyListEdgeIndexed res;
        int n = res.mn = mn;
        std::vector<int> buf(n+1, 0);
        for(auto [v,i] : E) ++buf[v];
        for(int i=1; i<=n; i++) buf[i] += buf[i-1];
        res.E.resize(buf[n]);
        for(int u=0; u<n; u++) for(auto [v,i] : operator[](u)) res.E[--buf[v]] = {u,i};
        res.I = std::move(buf);
        return res;
    }
};

} // namespace nachia

#include <vector>

namespace nachia{

class BiconnectedComponents{
private:
    int mn;
    int mm;
    int mnum_bcs;
    std::vector<std::pair<int, int>> medges;
    std::vector<int> edgeidx_to_bcidx;
public:
    BiconnectedComponents(int n, std::vector<std::pair<int, int>> edges){

		// after dfs1 ... dfsi_to_vtx[i] is the vertex that comes i-th in dfs preorder
        std::vector<int> dfsi_to_vtx;
		// after dfs1 ... inverse of dfsi_to_vtx
        std::vector<int> vtx_to_dfsi;
		// not visited by dfs1 ... -1
		// visited by dfs1 ... (the parent of parent of v and v would be cut when we delete the parent of v) ? 1 : 0
        std::vector<int> linked_over;
		// not visited by dfs1 ... -1
		// visited by dfs1 and no parent in the dfs tree ... -2
		// otherwise ... the parent
        std::vector<int> dfs_parent;

        mn = n;
        int m = edges.size();
        medges = std::move(edges);
        nachia::AdjacencyListEdgeIndexed adj(n, medges, true);
        dfsi_to_vtx.resize(n);
        vtx_to_dfsi.resize(n);
        dfs_parent.assign(n, -1);
        linked_over.assign(n, -1);
        int dfsi = 0;

		// return the vertex earliest in dfs preorder, that backedges reach
        auto dfs1 = [&](int p, auto self)->int {
            vtx_to_dfsi[p] = dfsi;
            dfsi_to_vtx[dfsi] = p;
            int backedge = dfsi;
            dfsi++;
            for(auto [nx,i] : adj[p]){
                if(dfs_parent[nx] != -1){
					 // backedges and multiedges
					backedge = std::min(backedge, vtx_to_dfsi[nx]);
				}
                else{
					// along dfs tree
                    dfs_parent[nx] = i;
                    int link = self(nx, self);
                    backedge = std::min(backedge, link);
                    linked_over[nx] = (link < vtx_to_dfsi[p]) ? 1 : 0; // whether backedges come strictly further than p
                }
            }
            return backedge;
        };
        for(int i=0; i<n; i++) if(dfs_parent[i] == -1){ // for each component
            dfs_parent[i] = -2;
            dfs1(i, dfs1);
        }
        
        std::vector<int> res(m);
        auto dfs2 = [&](int p, int bcid, int& maxbcid, auto self)-> void {
            if(dfs_parent[p] < 0){
				// different child is in different block
                for(auto [nx,i] : adj[p]) if(dfs_parent[nx] == i){
                    bcid = maxbcid++;
                    self(nx, bcid, maxbcid, self);
                }
                return;
            }
            for(auto [nx,i] : adj[p]) if(dfs_parent[nx] != i){
				// backedges and multiedges
				res[i] = bcid;
			}
            for(auto [nx,i] : adj[p]) if(dfs_parent[nx] == i){
				// along dfs tree
                int nx_bcid = bcid;
                if(!linked_over[nx]) nx_bcid = maxbcid++; // cut
                self(nx, nx_bcid, maxbcid, self);
            }
        };
        int bcid = 0;
		// for each component (along dfs trees)
        for(int i=0; i<n; i++) if(dfs_parent[i] < 0) dfs2(i, -1, bcid, dfs2);
        edgeidx_to_bcidx = std::move(res);
        mm = m;
        mnum_bcs = bcid;
    }

    int get_num_bcts() const { return mnum_bcs; }

    std::vector<std::vector<int>> get_bcs() const {
        std::vector<std::vector<int>> res(mnum_bcs);
        for(int i=0; i<mm; i++){
            res[edgeidx_to_bcidx[i]].push_back(i);
        }
        return res;
    }

    AdjacencyList get_bct() const {
        int bct_n = mn + mnum_bcs;
        AdjacencyList bc_edgelists; {
            std::vector<int> buf(mnum_bcs+1);
            for(int bci : edgeidx_to_bcidx) ++buf[bci];
            for(int i=1; i<=mnum_bcs; i++) buf[i] += buf[i-1];
            std::vector<int> E(buf.back());
            for(int i=0; i<mm; i++) E[--buf[edgeidx_to_bcidx[i]]] = i;
            bc_edgelists = AdjacencyList::from_raw(std::move(E), std::move(buf));
        }
        std::vector<std::pair<int, int>> res(bct_n - 1);
        int resi = 0;
        std::vector<int> visited(mn);
        for(int bci=0; bci<mnum_bcs; bci++){
            for(int e : bc_edgelists[bci]){
                auto [u,v] = medges[e];
                if(!visited[u]){ visited[u] = 1; res[resi++] = {mn+bci,u}; }
                if(!visited[v]){ visited[v] = 1; res[resi++] = {mn+bci,v}; }
            }
            for(int e : bc_edgelists[bci]){
                auto [u,v] = medges[e];
                visited[u] = visited[v] = 0;
            }
        }
        return AdjacencyList(bct_n, res, true);
    }
};

} // namespace nachia



#include <cstdio>
#include <cassert>

int main() {
    int n; scanf("%d", &n);
    int m; scanf("%d", &m);
    std::vector<std::pair<int, int>> edges(m);
    for(auto& [u,v] : edges) scanf("%d%d", &u, &v);

    for(auto [u,v] : edges) if(!(0 <= u)) return 1;
    for(auto [u,v] : edges) if(!(0 <= v)) return 1;
    for(auto [u,v] : edges) if(!(u < n)) return 1;
    for(auto [u,v] : edges) if(!(v < n)) return 1;
    for(auto [u,v] : edges) if(!(u != v)) return 1;

    auto bcs = nachia::BiconnectedComponents(n, edges).get_bcs();
    printf("%d\n", (int)bcs.size());
    for(auto& bc : bcs){
        printf("%d", (int)bc.size());
        for(auto v : bc) printf(" %d", v);
        printf("\n");
    }
    return 0;
}
