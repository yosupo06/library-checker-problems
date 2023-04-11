#pragma once
#include <vector>
#include <utility>
#include <cassert>
#include "csr-array.hpp"

namespace nachia{


struct Graph {
public:
    struct Edge{
        int from, to;
        void reverse(){ std::swap(from, to); }
    };
    using Base = std::vector<std::pair<int, int>>;
    Graph(int n = 0, bool undirected = false, int m = 0) : m_n(n), m_e(m), m_isUndir(undirected) {}
    Graph(int n, const std::vector<std::pair<int, int>>& edges, bool undirected = false) : m_n(n), m_isUndir(undirected){
        m_e.resize(edges.size());
        for(std::size_t i=0; i<edges.size(); i++) m_e[i] = { edges[i].first, edges[i].second };
    }
    template<class Cin>
    static Graph Input(Cin& cin, int n, bool undirected, int m, bool offset = 0){
        Graph res(n, undirected, m);
        for(int i=0; i<m; i++){
            int u, v; cin >> u >> v;
            res[i].from = u - offset;
            res[i].to = v - offset;
        }
        return res;
    }
    int numVertices() const noexcept { return m_n; }
    int numEdges() const noexcept { return int(m_e.size()); }
    int addNode() noexcept { return m_n++; }
    int addEdge(int from, int to){ m_e.push_back({ from, to }); return numEdges() - 1; }
    Edge& operator[](int ei) noexcept { return m_e[ei]; }
    const Edge& operator[](int ei) const noexcept { return m_e[ei]; }
    Edge& at(int ei) { return m_e.at(ei); }
    const Edge& at(int ei) const { return m_e.at(ei); }
    auto begin(){ return m_e.begin(); }
    auto end(){ return m_e.end(); }
    auto begin() const { return m_e.begin(); }
    auto end() const { return m_e.end(); }
    bool isUndirected() const noexcept { return m_isUndir; }
    void reverseEdges() noexcept { for(auto& e : m_e) e.reverse(); }
    void contract(int newV, const std::vector<int>& mapping){
        assert(numVertices() == int(mapping.size()));
        for(int i=0; i<numVertices(); i++) assert(0 <= mapping[i] && mapping[i] < newV);
        for(auto& e : m_e){ e.from = mapping[e.from]; e.to = mapping[e.to]; }
    }
    std::vector<Graph> induce(int num, const std::vector<int>& mapping) const {
        int n = numVertices();
        assert(n == int(mapping.size()));
        for(int i=0; i<n; i++) assert(-1 <= mapping[i] && mapping[i] < num);
        std::vector<int> indexV(n), newV(num);
        for(int i=0; i<n; i++) if(mapping[i] >= 0) indexV[i] = newV[mapping[i]]++;
        std::vector<Graph> res; res.reserve(num);
        for(int i=0; i<num; i++) res.emplace_back(newV[i], isUndirected());
        for(auto e : m_e) if(mapping[e.from] == mapping[e.to] && mapping[e.to] >= 0) res[mapping[e.to]].addEdge(indexV[e.from], indexV[e.to]);
        return res;
    }
    CsrArray<int> getEdgeIndexArray(bool undirected) const {
        std::vector<std::pair<int, int>> src;
        src.reserve(numEdges() * (undirected ? 2 : 1));
        for(int i=0; i<numEdges(); i++){
            auto e = operator[](i);
            src.emplace_back(e.from, i);
            if(undirected) src.emplace_back(e.to, i);
        }
        return CsrArray<int>::Construct(numVertices(), src);
    }
    CsrArray<int> getEdgeIndexArray() const { return getEdgeIndexArray(isUndirected()); }
    CsrArray<int> getAdjacencyArray(bool undirected) const {
        std::vector<std::pair<int, int>> src;
        src.reserve(numEdges() * (undirected ? 2 : 1));
        for(auto e : m_e){
            src.emplace_back(e.from, e.to);
            if(undirected) src.emplace_back(e.to, e.from);
        }
        return CsrArray<int>::Construct(numVertices(), src);
    }
    CsrArray<int> getAdjacencyArray() const { return getAdjacencyArray(isUndirected()); }
private:
    int m_n;
    std::vector<Edge> m_e;
    bool m_isUndir;
};

} // namespace nachia
