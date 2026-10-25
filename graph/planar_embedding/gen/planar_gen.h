#pragma once
// Shared helpers for the planar_embedding generators.
#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <vector>
#include <array>
#include <utility>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <cassert>
#include "random.h"

using Edges = std::vector<std::array<int, 2>>;

// Simple graph under construction.
struct Graph {
	int n = 0;
	Edges edges;
	int add_vertex() { return n++; }
	int add_vertices(int k) { int f = n; n += k; return f; }
	void add_edge(int u, int v) { assert(u != v); assert(0 <= u && u < n && 0 <= v && v < n); edges.push_back({u, v}); }
	// Adds a path v_0 - v_1 - ... - v_{k-1} through the given vertices.
	void add_path(const std::vector<int>& vs) { for (size_t i = 1; i < vs.size(); i++) add_edge(vs[i - 1], vs[i]); }
	void add_cycle(const std::vector<int>& vs) { add_path(vs); if (vs.size() >= 3) add_edge(vs.back(), vs.front()); }
	// Adds a disjoint copy of another graph, returns the offset.
	int add_graph(const Graph& g) {
		int off = add_vertices(g.n);
		for (auto [u, v] : g.edges) add_edge(u + off, v + off);
		return off;
	}
	// Adds a path of `len` edges between u and v, creating len-1 new vertices.
	void add_subdivided_edge(int u, int v, int len) {
		assert(len >= 1);
		std::vector<int> vs{u};
		for (int i = 0; i < len - 1; i++) vs.push_back(add_vertex());
		vs.push_back(v);
		add_path(vs);
	}
};

// Key of the undirected edge {u, v} of a graph with n vertices.
inline int64_t edge_key(int n, int u, int v) {
	if (u > v) std::swap(u, v);
	return int64_t(u) * n + v;
}

// Removes duplicate edges (in either orientation) and self-loops.
inline void dedup(Graph& g) {
	Edges out;
	std::unordered_set<int64_t> seen;
	for (auto [u, v] : g.edges) {
		if (u == v) continue;
		if (seen.insert(edge_key(g.n, u, v)).second) out.push_back({u, v});
	}
	g.edges = out;
}

// Prints one case (the graph). By default, relabels vertices randomly,
// shuffles the edge order and randomly flips edge orientations.
inline void print_case(Random& gen, Graph g, bool relabel = true, bool shuffle_edges = true, bool flip = true) {
	if (relabel) {
		auto perm = gen.perm<int>(g.n);
		for (auto& [u, v] : g.edges) { u = perm[u]; v = perm[v]; }
	}
	if (shuffle_edges) gen.shuffle(g.edges.begin(), g.edges.end());
	if (flip) {
		for (auto& [u, v] : g.edges) if (gen.uniform_bool()) std::swap(u, v);
	}
	printf("%d %d\n", g.n, int(g.edges.size()));
	for (auto [u, v] : g.edges) printf("%d %d\n", u, v);
}

// Prints a test file consisting of the given cases (see print_case).
inline void print_graphs(Random& gen, const std::vector<Graph>& gs, bool relabel = true, bool shuffle_edges = true, bool flip = true) {
	printf("%d\n", int(gs.size()));
	for (const auto& g : gs) print_case(gen, g, relabel, shuffle_edges, flip);
}

// Prints a test file with a single case.
inline void print_graph(Random& gen, Graph g, bool relabel = true, bool shuffle_edges = true, bool flip = true) {
	print_graphs(gen, {std::move(g)}, relabel, shuffle_edges, flip);
}

// ---- Fixed families ----

inline Graph complete_graph(int n) {
	Graph g; g.add_vertices(n);
	for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) g.add_edge(i, j);
	return g;
}
inline Graph complete_bipartite(int a, int b) {
	Graph g; g.add_vertices(a + b);
	for (int i = 0; i < a; i++) for (int j = 0; j < b; j++) g.add_edge(i, a + j);
	return g;
}
inline Graph path_graph(int n) {
	Graph g; g.add_vertices(n);
	for (int i = 0; i + 1 < n; i++) g.add_edge(i, i + 1);
	return g;
}
inline Graph cycle_graph(int n) {
	Graph g = path_graph(n);
	if (n >= 3) g.add_edge(n - 1, 0);
	return g;
}
inline Graph star_graph(int n) {
	Graph g; g.add_vertices(n);
	for (int i = 1; i < n; i++) g.add_edge(0, i);
	return g;
}
// Wheel W_n: a hub plus a cycle of n-1 vertices.
inline Graph wheel_graph(int n) {
	Graph g; g.add_vertices(n);
	for (int i = 1; i < n; i++) { g.add_edge(0, i); g.add_edge(i, i % (n - 1) + 1); }
	return g;
}
// Ladder P_k x K_2 (planar).
inline Graph ladder_graph(int k) {
	Graph g; g.add_vertices(2 * k);
	for (int i = 0; i < k; i++) {
		g.add_edge(2 * i, 2 * i + 1);
		if (i + 1 < k) { g.add_edge(2 * i, 2 * i + 2); g.add_edge(2 * i + 1, 2 * i + 3); }
	}
	return g;
}
// Prism C_k x K_2 (planar), k >= 3.
inline Graph prism_graph(int k) {
	Graph g = ladder_graph(k);
	g.add_edge(2 * (k - 1), 0);
	g.add_edge(2 * (k - 1) + 1, 1);
	return g;
}
// Moebius ladder on n (even, >= 6) vertices: C_n plus the n/2 "antipodal" chords. Nonplanar.
// n = 6 gives K3,3 and n = 8 gives the Wagner graph.
inline Graph moebius_ladder(int n) {
	Graph g = cycle_graph(n);
	for (int i = 0; i < n / 2; i++) g.add_edge(i, i + n / 2);
	return g;
}
inline Graph petersen_graph() {
	Graph g; g.add_vertices(10);
	for (int i = 0; i < 5; i++) {
		g.add_edge(i, (i + 1) % 5);
		g.add_edge(5 + i, 5 + (i + 2) % 5);
		g.add_edge(i, 5 + i);
	}
	return g;
}
// Goldner-Harary graph: maximal planar, 11 vertices, 27 edges.
// Triangular bipyramid (equator 0,1,2; apexes 3,4) with a degree-3 vertex stacked into each of its 6 faces.
inline Graph goldner_harary_graph() {
	Graph g; g.add_vertices(11);
	g.add_edge(0, 1); g.add_edge(1, 2); g.add_edge(2, 0);
	for (int apex : {3, 4}) for (int i = 0; i < 3; i++) g.add_edge(apex, i);
	int v = 5;
	for (int apex : {3, 4}) for (int i = 0; i < 3; i++) {
		g.add_edge(v, apex); g.add_edge(v, i); g.add_edge(v, (i + 1) % 3);
		v++;
	}
	return g;
}
// Groetzsch (Mycielski of C_5) graph: 11 vertices, 20 edges, nonplanar.
inline Graph grotzsch_graph() {
	Graph g; g.add_vertices(11);
	// C5 on 0..4, shadow vertices 5..9, apex 10
	for (int i = 0; i < 5; i++) {
		g.add_edge(i, (i + 1) % 5);
		g.add_edge(5 + i, (i + 1) % 5);
		g.add_edge(5 + i, (i + 4) % 5);
		g.add_edge(5 + i, 10);
	}
	return g;
}
// Heawood graph: 14 vertices, 21 edges, nonplanar.
inline Graph heawood_graph() {
	Graph g = cycle_graph(14);
	for (int i = 0; i < 14; i += 2) g.add_edge(i, (i + 5) % 14);
	return g;
}
inline Graph hypercube_graph(int d) {
	Graph g; g.add_vertices(1 << d);
	for (int v = 0; v < (1 << d); v++) for (int b = 0; b < d; b++) if (!(v >> b & 1)) g.add_edge(v, v | (1 << b));
	return g;
}
// Octahedron K_{2,2,2} (planar).
inline Graph octahedron_graph() {
	Graph g; g.add_vertices(6);
	for (int i = 0; i < 6; i++) for (int j = i + 1; j < 6; j++) if (j != i + 3 && i != j + 3) g.add_edge(i, j);
	return g;
}
// Icosahedron (planar, 12 vertices, 30 edges).
inline Graph icosahedron_graph() {
	Graph g; g.add_vertices(12);
	// 0 top, 1..5 upper ring, 6..10 lower ring, 11 bottom
	for (int i = 0; i < 5; i++) {
		g.add_edge(0, 1 + i);
		g.add_edge(1 + i, 1 + (i + 1) % 5);
		g.add_edge(6 + i, 6 + (i + 1) % 5);
		g.add_edge(11, 6 + i);
		g.add_edge(1 + i, 6 + i);
		g.add_edge(1 + i, 6 + (i + 1) % 5);
	}
	return g;
}
// Dodecahedron (planar, 20 vertices, 30 edges).
inline Graph dodecahedron_graph() {
	Graph g; g.add_vertices(20);
	// outer 5-cycle 0..4, ring 5..9, ring 10..14, inner 15..19
	for (int i = 0; i < 5; i++) {
		g.add_edge(i, (i + 1) % 5);
		g.add_edge(i, 5 + i);
		g.add_edge(5 + i, 10 + i);
		g.add_edge(5 + i, 10 + (i + 4) % 5);
		g.add_edge(10 + i, 15 + i);
		g.add_edge(15 + i, 15 + (i + 1) % 5);
	}
	return g;
}
// Grid graph a x b, optionally deleting each vertex with probability hole_prob.
inline Graph grid_graph(Random& gen, int a, int b, double hole_prob = 0.0) {
	Graph g;
	std::vector<int> id((size_t)a * b, -1);
	for (int i = 0; i < a; i++) for (int j = 0; j < b; j++) {
		if (hole_prob > 0 && gen.uniform01() < hole_prob) continue;
		id[(size_t)i * b + j] = g.add_vertex();
	}
	for (int i = 0; i < a; i++) for (int j = 0; j < b; j++) {
		int v = id[(size_t)i * b + j];
		if (v < 0) continue;
		if (i + 1 < a && id[(size_t)(i + 1) * b + j] >= 0) g.add_edge(v, id[(size_t)(i + 1) * b + j]);
		if (j + 1 < b && id[(size_t)i * b + j + 1] >= 0) g.add_edge(v, id[(size_t)i * b + j + 1]);
	}
	return g;
}

// ---- Random planar families ----

inline Graph random_tree(Random& gen, int n) {
	Graph g; g.add_vertices(n);
	for (int i = 1; i < n; i++) g.add_edge(gen.uniform(0, i - 1), i);
	return g;
}
// Long-path-ish random tree: parent is chosen among the last `window` vertices.
inline Graph random_deep_tree(Random& gen, int n, int window) {
	Graph g; g.add_vertices(n);
	for (int i = 1; i < n; i++) g.add_edge(gen.uniform(std::max(0, i - window), i - 1), i);
	return g;
}
// Random 2-tree on n >= 2 vertices (2n-3 edges, planar).
inline Graph random_two_tree(Random& gen, int n) {
	Graph g; g.add_vertices(n);
	if (n >= 2) g.add_edge(0, 1);
	for (int i = 2; i < n; i++) {
		auto [u, v] = g.edges[gen.uniform<int>(0, int(g.edges.size()) - 1)];
		g.add_edge(u, i);
		g.add_edge(v, i);
	}
	return g;
}
// Random Apollonian network (stacked triangulation) on n >= 3 vertices: maximal planar.
inline Graph random_apollonian(Random& gen, int n) {
	Graph g; g.add_vertices(n);
	assert(n >= 3);
	g.add_edge(0, 1); g.add_edge(1, 2); g.add_edge(2, 0);
	std::vector<std::array<int, 3>> faces{{0, 1, 2}, {0, 2, 1}};
	for (int v = 3; v < n; v++) {
		int fi = gen.uniform<int>(0, int(faces.size()) - 1);
		auto [a, b, c] = faces[fi];
		g.add_edge(a, v); g.add_edge(b, v); g.add_edge(c, v);
		faces[fi] = {a, b, v};
		faces.push_back({b, c, v});
		faces.push_back({c, a, v});
	}
	return g;
}
// Random planar triangulation on n >= 3 vertices, obtained from a fan
// triangulation by `flips` random edge flips (Delaunay-like mixing). Maximal planar.
inline Graph random_triangulation(Random& gen, int n, int64_t flips) {
	assert(n >= 3);
	// Start from a "double fan": vertices 1..n-2 form a path, all adjacent to 0 (one side) and n-1 (other side).
	// Faces are oriented consistently; apex[(u,v)] is the third vertex of the face on the left of u->v.
	std::unordered_map<int64_t, int> apex;
	auto dkey = [n](int u, int v) { return int64_t(u) * n + v; };
	auto set_face = [&](int a, int b, int c) {
		apex[dkey(a, b)] = c; apex[dkey(b, c)] = a; apex[dkey(c, a)] = b;
	};
	Edges edges;
	if (n == 3) {
		set_face(0, 1, 2); set_face(0, 2, 1);
		edges = {{0, 1}, {1, 2}, {2, 0}};
	} else {
		int t = n - 1;
		for (int i = 1; i + 1 <= n - 2; i++) {
			set_face(0, i, i + 1);   // faces (0, i, i+1)
			set_face(t, i + 1, i);   // faces (t, i+1, i)
		}
		// Close up at both ends: faces (0, n-2, t) and (t, 1, 0)
		set_face(0, n - 2, t);
		set_face(t, 1, 0);
		edges.push_back({0, t});
		for (int i = 1; i <= n - 2; i++) { edges.push_back({0, i}); edges.push_back({t, i}); }
		for (int i = 1; i + 1 <= n - 2; i++) edges.push_back({i, i + 1});
	}
	for (int64_t f = 0; f < flips; f++) {
		int ei = gen.uniform<int>(0, int(edges.size()) - 1);
		auto [u, v] = edges[ei];
		auto ia = apex.find(dkey(u, v)), ib = apex.find(dkey(v, u));
		assert(ia != apex.end() && ib != apex.end());
		int a = ia->second, b = ib->second;  // faces (u, v, a) and (v, u, b)
		if (a == b || apex.count(dkey(a, b))) continue;
		apex.erase(ia); apex.erase(ib);
		// The quadrilateral u, b, v, a (ccw) is re-split by the diagonal a-b.
		set_face(u, b, a);
		set_face(b, v, a);
		edges[ei] = {a, b};
	}
	Graph g; g.add_vertices(n);
	g.edges = std::move(edges);
	assert(int(g.edges.size()) == 3 * n - 6);
	return g;
}
// Random maximal outerplanar graph: the cycle 0..n-1 plus a random triangulation of the polygon.
inline Graph random_maximal_outerplanar(Random& gen, int n) {
	Graph g = cycle_graph(n);
	std::vector<std::array<int, 2>> stk;
	if (n >= 4) stk.push_back({0, n - 1});
	while (!stk.empty()) {
		auto [l, r] = stk.back(); stk.pop_back();
		if (r - l < 2) continue;
		int m = gen.uniform(l + 1, r - 1);
		if (m != l + 1) { g.add_edge(l, m); stk.push_back({l, m}); }
		if (m != r - 1) { g.add_edge(m, r); stk.push_back({m, r}); }
	}
	return g;
}
// Random cactus: a tree of cycles and bridges. Returns n vertices (n >= 1).
inline Graph random_cactus(Random& gen, int n, int max_cycle) {
	Graph g; g.add_vertex();
	while (g.n < n) {
		int base = gen.uniform(0, g.n - 1);
		int remaining = n - g.n;
		if (remaining >= 2 && gen.uniform_bool()) {
			int len = gen.uniform(2, std::min(remaining, max_cycle - 1));
			std::vector<int> vs{base};
			for (int i = 0; i < len; i++) vs.push_back(g.add_vertex());
			g.add_cycle(vs);
		} else {
			g.add_edge(base, g.add_vertex());
		}
	}
	return g;
}
// Keeps each edge independently with probability p.
inline Graph random_edge_subset(Random& gen, Graph g, double p) {
	Edges out;
	for (auto e : g.edges) if (gen.uniform01() < p) out.push_back(e);
	g.edges = std::move(out);
	return g;
}
// Keeps exactly `keep` edges chosen uniformly at random.
inline Graph random_edge_sample(Random& gen, Graph g, int keep) {
	gen.shuffle(g.edges.begin(), g.edges.end());
	if (int(g.edges.size()) > keep) g.edges.resize(keep);
	return g;
}
// Adds `k` random new edges that are not already present (and not loops).
inline void add_random_nonedges(Random& gen, Graph& g, int k) {
	std::unordered_set<int64_t> seen;
	for (auto [u, v] : g.edges) seen.insert(edge_key(g.n, u, v));
	assert(g.n >= 2);
	while (k > 0) {
		auto [u, v] = gen.uniform_pair(0, g.n - 1);
		if (seen.insert(edge_key(g.n, u, v)).second) { g.add_edge(u, v); k--; }
	}
}
// Random simple graph with n vertices and m edges (m <= n(n-1)/2).
inline Graph random_simple_graph(Random& gen, int n, int m) {
	Graph g; g.add_vertices(n);
	add_random_nonedges(gen, g, m);
	return g;
}
// Subdivides every edge of g into a path with a random length in [min_len, max_len].
inline Graph subdivide_edges(Random& gen, const Graph& g, int min_len, int max_len) {
	Graph h; h.add_vertices(g.n);
	for (auto [u, v] : g.edges) h.add_subdivided_edge(u, v, gen.uniform(min_len, max_len));
	return h;
}
