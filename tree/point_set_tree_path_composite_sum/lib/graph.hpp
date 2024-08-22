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
    };
    using Base = std::vector<std::pair<int, int>>;
    Graph(int n = 0, bool undirected = false, int m = 0) : m_n(n), m_e(m), m_isUndir(undirected) {}
    int numVertices() const noexcept { return m_n; }
    int numEdges() const noexcept { return int(m_e.size()); }
    int addEdge(int from, int to){ m_e.push_back({ from, to }); return numEdges() - 1; }
    Edge& operator[](int ei) noexcept { return m_e[ei]; }
    const Edge& operator[](int ei) const noexcept { return m_e[ei]; }
    bool isUndirected() const noexcept { return m_isUndir; }
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
private:
    int m_n;
    std::vector<Edge> m_e;
    bool m_isUndir;
};

} // namespace nachia
