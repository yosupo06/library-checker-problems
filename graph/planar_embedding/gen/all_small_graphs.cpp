// Exhaustive small graphs: every labelled graph on N <= 5 vertices
// (1 + 2 + 8 + 64 + 1024 graphs) and every graph on 6, 7, 8 vertices up to
// isomorphism (156 + 1044 + 12346 graphs, OEIS A000088). Seed 0 prints them
// with canonical labels in a fixed order; other seeds relabel vertices,
// shuffle edges and edge orientations and shuffle the case order.
#include <set>
#include "planar_gen.h"

namespace {

// Graph on n <= 8 vertices as adjacency bitmasks.
struct Small {
	int n;
	std::array<unsigned, 8> adj;
};

// Code of a labelled graph: bit of pair (i, j), i < j, is placed so that pairs
// (0,1), (0,2), (1,2), (0,3), ... are the most significant bits.
constexpr int NPAIRS = 28;
inline int pair_index(int i, int j) { return j * (j - 1) / 2 + i; }

// Vertex invariant: iterated degree refinement.
std::vector<int> refine(const Small& g) {
	int n = g.n;
	std::vector<int> color(n, 0);
	for (int v = 0; v < n; v++) color[v] = __builtin_popcount(g.adj[v]);
	while (true) {
		std::vector<std::pair<std::vector<int>, int>> keys(n);
		for (int v = 0; v < n; v++) {
			std::vector<int> k{color[v]};
			for (int w = 0; w < n; w++) if (g.adj[v] >> w & 1) k.push_back(color[w]);
			std::sort(k.begin() + 1, k.end());
			keys[v] = {k, v};
		}
		std::vector<std::pair<std::vector<int>, int>> sorted = keys;
		std::sort(sorted.begin(), sorted.end());
		std::vector<int> nc(n);
		int classes = 0;
		for (int i = 0; i < n; i++) {
			if (i > 0 && sorted[i].first != sorted[i - 1].first) classes++;
			nc[sorted[i].second] = classes;
		}
		int old_classes = *std::max_element(color.begin(), color.end());
		bool same = classes == old_classes;
		color = nc;
		if (same) break;
	}
	return color;
}

// Canonical form: lexicographically smallest code over all vertex orderings
// compatible with the refined colouring (vertices sorted by colour).
struct Canon {
	const Small& g;
	std::vector<int> color;
	std::vector<int> pos_color;  // colour required at each position
	std::vector<int> perm;       // perm[pos] = vertex
	unsigned used = 0;
	unsigned best = ~0u;
	std::vector<int> best_perm;
	bool found = false;

	Canon(const Small& g_) : g(g_), color(refine(g_)), pos_color(g_.n), perm(g_.n) {
		std::vector<int> sorted(color);
		std::sort(sorted.begin(), sorted.end());
		pos_color = sorted;
	}

	void rec(int p, unsigned code) {
		if (p == g.n) {
			if (!found || code < best) { best = code; best_perm = perm; found = true; }
			return;
		}
		unsigned prefix_mask = p == 0 ? 0u : ~0u << (NPAIRS - pair_index(0, p));
		if (found && (code & prefix_mask) > (best & prefix_mask)) return;
		for (int v = 0; v < g.n; v++) {
			if (used >> v & 1) continue;
			if (color[v] != pos_color[p]) continue;
			unsigned c = code;
			for (int i = 0; i < p; i++) {
				if (g.adj[v] >> perm[i] & 1) c |= 1u << (NPAIRS - 1 - pair_index(i, p));
			}
			unsigned mask = ~0u << (NPAIRS - pair_index(0, p + 1));
			if (found && (c & mask) > (best & mask)) continue;
			used |= 1u << v;
			perm[p] = v;
			rec(p + 1, c);
			used &= ~(1u << v);
		}
	}

	Small run() {
		rec(0, 0);
		Small h{g.n, {}};
		for (int p = 0; p < g.n; p++) {
			for (int q = 0; q < g.n; q++) {
				if (g.adj[best_perm[p]] >> best_perm[q] & 1) h.adj[p] |= 1u << q;
			}
		}
		return h;
	}
};

unsigned code_of(const Small& g) {
	unsigned c = 0;
	for (int j = 0; j < g.n; j++)
		for (int i = 0; i < j; i++)
			if (g.adj[i] >> j & 1) c |= 1u << (NPAIRS - 1 - pair_index(i, j));
	return c;
}

Graph to_graph(const Small& g) {
	Graph h; h.add_vertices(g.n);
	for (int i = 0; i < g.n; i++)
		for (int j = i + 1; j < g.n; j++)
			if (g.adj[i] >> j & 1) h.add_edge(i, j);
	return h;
}

}  // namespace

int main(int, char* argv[]) {
	int64_t seed = atoll(argv[1]);
	Random gen(seed);
	std::vector<Graph> gs;

	// All labelled graphs on n <= 5 vertices.
	for (int n = 1; n <= 5; n++) {
		int pairs = n * (n - 1) / 2;
		for (unsigned mask = 0; mask < (1u << pairs); mask++) {
			Graph g; g.add_vertices(n);
			int k = 0;
			for (int j = 0; j < n; j++)
				for (int i = 0; i < j; i++, k++)
					if (mask >> k & 1) g.add_edge(i, j);
			gs.push_back(g);
		}
	}
	assert(gs.size() == 1 + 2 + 8 + 64 + 1024);

	// All graphs on n <= 8 vertices up to isomorphism, by vertex extension.
	static const int A000088[9] = {1, 1, 2, 4, 11, 34, 156, 1044, 12346};
	std::vector<Small> level{Small{1, {}}};
	for (int n = 2; n <= 8; n++) {
		std::set<unsigned> seen;
		std::vector<Small> next;
		for (const Small& g : level) {
			for (unsigned nb = 0; nb < (1u << (n - 1)); nb++) {
				Small h{n, g.adj};
				h.adj[n - 1] = nb;
				for (int v = 0; v < n - 1; v++) if (nb >> v & 1) h.adj[v] |= 1u << (n - 1);
				Small c = Canon(h).run();
				if (seen.insert(code_of(c)).second) next.push_back(c);
			}
		}
		assert(int(next.size()) == A000088[n]);
		level = next;
		if (n >= 6) for (const Small& g : level) gs.push_back(to_graph(g));
	}
	assert(gs.size() == 1099 + 156 + 1044 + 12346);

	if (seed == 0) {
		print_graphs(gen, gs, false, false, false);
	} else {
		gen.shuffle(gs.begin(), gs.end());
		print_graphs(gen, gs);
	}
	return 0;
}
