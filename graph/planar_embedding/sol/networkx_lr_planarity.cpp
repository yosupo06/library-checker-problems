// Independent cross-check: the left-right planarity test and embedding
// (U. Brandes, "The Left-Right Planarity Test", 2009), translated statement
// by statement from the iterative implementation in networkx 3.7,
// networkx/algorithms/planarity.py (classes Interval, ConflictPair,
// LRPlanarity and the parts of PlanarEmbedding that LRPlanarity uses).
// https://github.com/networkx/networkx/blob/networkx-3.7/networkx/algorithms/planarity.py
// The Python source is quoted in the comments directly above each translated
// statement.
//
// Translation conventions:
// - vertices are 0..N-1; None becomes -1;
// - the undirected edge i = {edges[i][0], edges[i][1]} yields the two directed
//   edges ("darts") 2i = (edges[i][0], edges[i][1]) and 2i+1 = its reverse,
//   so a networkx edge key (v, w) is a dart d with tail(d) = v, head(d) = w,
//   and the reverse edge (w, v) is d ^ 1;
// - dicts keyed by node / edge become vectors indexed by vertex / dart;
// - the DiGraph DG is the set of darts with in_DG[d] set;
// - "top_of_stack(S) == stack_bottom[ei]" compares object identity in
//   Python; here a stack entry is identified by its index in S;
// - the PlanarEmbedding stores, per dart d = (v, w), the darts cw[d] and
//   ccw[d] that follow (v, w) clockwise / counterclockwise around v, and per
//   vertex the dart to its leftmost neighbor (networkx keeps that neighbor as
//   the last key of self._succ[v]);
// - the DFS routines keep their explicit stacks; the per-call defaultdicts
//   ind / skip_init / old_ref are vectors allocated once per phase.
//
// NetworkX is distributed with the 3-clause BSD license.
//
//    Copyright (c) 2004-2026, NetworkX Developers
//    Aric Hagberg <hagberg@lanl.gov>
//    Dan Schult <dschult@colgate.edu>
//    Pieter Swart <swart@lanl.gov>
//    All rights reserved.
//
//    Redistribution and use in source and binary forms, with or without
//    modification, are permitted provided that the following conditions are
//    met:
//
//      * Redistributions of source code must retain the above copyright
//        notice, this list of conditions and the following disclaimer.
//
//      * Redistributions in binary form must reproduce the above
//        copyright notice, this list of conditions and the following
//        disclaimer in the documentation and/or other materials provided
//        with the distribution.
//
//      * Neither the name of the NetworkX Developers nor the names of its
//        contributors may be used to endorse or promote products derived
//        from this software without specific prior written permission.
//
//    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
//    "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
//    LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
//    A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
//    OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
//    SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
//    LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//    DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//    THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
//    OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <utility>
#include <vector>

namespace {

struct LRPlanarity;

// class Interval:
//     """Represents a set of return edges.
//
//     All return edges in an interval induce a same constraint on the contained
//     edges, which means that all edges must either have a left orientation or
//     all edges must have a right orientation.
//     """
struct Interval {
	// def __init__(self, low=None, high=None):
	//     self.low = low
	//     self.high = high
	int low = -1, high = -1;

	// def empty(self):
	//     """Check if the interval is empty"""
	//     return self.low is None and self.high is None
	bool empty() const { return low == -1 && high == -1; }

	// def copy(self):
	//     """Returns a copy of this interval"""
	//     return Interval(self.low, self.high)
	Interval copy() const { return Interval{low, high}; }

	// def conflicting(self, b, planarity_state):
	//     """Returns True if interval I conflicts with edge b"""
	// # translator's note: the body needs LRPlanarity's lowpt and is defined after the class.
	bool conflicting(int b, const LRPlanarity& planarity_state) const;
};

// class ConflictPair:
//     """Represents a different constraint between two intervals.
//
//     The edges in the left interval must have a different orientation than
//     the one in the right interval.
//     """
struct ConflictPair {
	// def __init__(self, left=Interval(), right=Interval()):
	//     self.left = left
	//     self.right = right
	Interval left, right;

	// def swap(self):
	//     """Swap left and right intervals"""
	//     temp = self.left
	//     self.left = self.right
	//     self.right = temp
	void swap() { std::swap(left, right); }

	// def lowest(self, planarity_state):
	//     """Returns the lowest lowpoint of a conflict pair"""
	// # translator's note: the body needs LRPlanarity's lowpt and is defined after the class.
	int lowest(const LRPlanarity& planarity_state) const;
};

// def top_of_stack(l):
//     """Returns the element on top of the stack."""
//     if not l:
//         return None
//     return l[-1]
// # translator's note: a stack entry is identified by its index; -1 stands for None.
int top_of_stack(const std::vector<ConflictPair>& l) { return int(l.size()) - 1; }

// class PlanarEmbedding(nx.DiGraph):
//     """Represents a planar graph with its planar embedding.
//     ...
//     """
// # translator's note: only the half-edge insertion used by LRPlanarity is kept.
// # Half-edge (v, w) is the dart d; cw[d] / ccw[d] are the darts out of v that
// # follow d in clockwise / counterclockwise order; leftmost_nbr[v] is the dart
// # from v to its leftmost neighbor (-1 if v has no out-half-edge yet).
struct PlanarEmbedding {
	std::vector<int> cw, ccw, leftmost_nbr;

	PlanarEmbedding(int N, int M) : cw(2 * M, -1), ccw(2 * M, -1), leftmost_nbr(N, -1) {}

	// def add_half_edge(self, start_node, end_node, *, cw=None, ccw=None):
	//     """Adds a half-edge from `start_node` to `end_node`.
	//     ...
	//     """
	// # translator's note: d = (start_node, end_node); cw_ref / ccw_ref are the
	// # darts (start_node, cw) / (start_node, ccw).
	void add_half_edge(int start_node, int d, int cw_ref, int ccw_ref) {
		// succs = self._succ.get(start_node)
		// if succs:
		if (leftmost_nbr[start_node] != -1) {
			// # there is already some edge out of start_node
			// leftmost_nbr = next(reversed(self._succ[start_node]))
			int leftmost = leftmost_nbr[start_node];
			bool move_leftmost_nbr_to_end;
			// if cw is not None:
			if (cw_ref != -1) {
				// if cw not in succs:
				//     raise nx.NetworkXError("Invalid clockwise reference node.")
				// if ccw is not None:
				//     raise nx.NetworkXError("Only one of cw/ccw can be specified.")
				assert(ccw_ref == -1);
				// ref_ccw = succs[cw]["ccw"]
				int ref_ccw = ccw[cw_ref];
				// super().add_edge(start_node, end_node, cw=cw, ccw=ref_ccw)
				cw[d] = cw_ref;
				ccw[d] = ref_ccw;
				// succs[ref_ccw]["cw"] = end_node
				cw[ref_ccw] = d;
				// succs[cw]["ccw"] = end_node
				ccw[cw_ref] = d;
				// # when (cw == leftmost_nbr), the newly added neighbor is
				// # already at the end of dict self._succ[start_node] and
				// # takes the place of the former leftmost_nbr
				// move_leftmost_nbr_to_end = cw != leftmost_nbr
				move_leftmost_nbr_to_end = cw_ref != leftmost;
			// elif ccw is not None:
			} else if (ccw_ref != -1) {
				// if ccw not in succs:
				//     raise nx.NetworkXError("Invalid counterclockwise reference node.")
				// ref_cw = succs[ccw]["cw"]
				int ref_cw = cw[ccw_ref];
				// super().add_edge(start_node, end_node, cw=ref_cw, ccw=ccw)
				cw[d] = ref_cw;
				ccw[d] = ccw_ref;
				// succs[ref_cw]["ccw"] = end_node
				ccw[ref_cw] = d;
				// succs[ccw]["cw"] = end_node
				cw[ccw_ref] = d;
				// move_leftmost_nbr_to_end = True
				move_leftmost_nbr_to_end = true;
			// else:
			//     raise nx.NetworkXError(
			//         "Node already has out-half-edge(s), either cw or ccw reference node required."
			//     )
			} else {
				assert(false);
			}
			// if move_leftmost_nbr_to_end:
			//     # LRPlanarity (via self.add_half_edge_first()) requires that
			//     # we keep track of the leftmost neighbor, which we accomplish
			//     # by keeping it as the last key in dict self._succ[start_node]
			//     succs[leftmost_nbr] = succs.pop(leftmost_nbr)
			if (move_leftmost_nbr_to_end) {
				leftmost_nbr[start_node] = leftmost;
			} else {
				leftmost_nbr[start_node] = d;
			}
		// else:
		} else {
			// if cw is not None or ccw is not None:
			//     raise nx.NetworkXError("Invalid reference node.")
			assert(cw_ref == -1 && ccw_ref == -1);
			// # adding the first edge out of start_node
			// super().add_edge(start_node, end_node, ccw=end_node, cw=end_node)
			cw[d] = d;
			ccw[d] = d;
			leftmost_nbr[start_node] = d;
		}
	}

	// def add_half_edge_first(self, start_node, end_node):
	//     """Add a half-edge and set end_node as start_node's leftmost neighbor.
	//     ...
	//     """
	void add_half_edge_first(int start_node, int d) {
		// succs = self._succ.get(start_node)
		// # the leftmost neighbor is the last entry in the
		// # self._succ[start_node] dict
		// leftmost_nbr = next(reversed(succs)) if succs else None
		int leftmost = leftmost_nbr[start_node];
		// self.add_half_edge(start_node, end_node, cw=leftmost_nbr)
		add_half_edge(start_node, d, leftmost, -1);
	}
};

// class LRPlanarity:
//     """A class to maintain the state during planarity check."""
struct LRPlanarity {
	int N, M;
	std::vector<std::array<int, 2>> edges;

	int tail(int d) const { return edges[d >> 1][d & 1]; }
	int head(int d) const { return edges[d >> 1][(d & 1) ^ 1]; }

	// def __init__(self, G):
	//     # copy G without adding self-loops
	//     self.G = nx.Graph()
	//     self.G.add_nodes_from(G.nodes)
	//     for e in G.edges:
	//         if e[0] != e[1]:
	//             self.G.add_edge(e[0], e[1])
	// # translator's note: the input is a simple graph; G is given by N and edges.

	//     self.roots = []
	std::vector<int> roots;

	//     # distance from tree root
	//     self.height = defaultdict(lambda: None)
	std::vector<int> height;

	//     self.lowpt = {}  # height of lowest return point of an edge
	//     self.lowpt2 = {}  # height of second lowest return point
	//     self.nesting_depth = {}  # for nesting order
	std::vector<int> lowpt, lowpt2, nesting_depth;

	//     # None -> missing edge
	//     self.parent_edge = defaultdict(lambda: None)
	std::vector<int> parent_edge;

	//     # oriented DFS graph
	//     self.DG = nx.DiGraph()
	//     self.DG.add_nodes_from(G.nodes)
	// # translator's note: in_DG[d] tells whether dart d is an edge of DG; DG[v]
	// # lists its out-darts in insertion order, like DiGraph successor iteration.
	std::vector<char> in_DG;
	std::vector<std::vector<int>> DG;

	//     self.adjs = {}
	//     self.ordered_adjs = {}
	std::vector<std::vector<int>> adjs, ordered_adjs;

	//     self.ref = defaultdict(lambda: None)
	//     self.side = defaultdict(lambda: 1)
	std::vector<int> ref, side;

	//     # stack of conflict pairs
	//     self.S = []
	//     self.stack_bottom = {}
	//     self.lowpt_edge = {}
	std::vector<ConflictPair> S;
	std::vector<int> stack_bottom, lowpt_edge;

	//     self.left_ref = {}
	//     self.right_ref = {}
	std::vector<int> left_ref, right_ref;

	//     self.embedding = PlanarEmbedding()
	PlanarEmbedding embedding;

	// # translator's note: the per-call defaultdicts of dfs_orientation /
	// # dfs_testing / dfs_embedding / sign, allocated once and reused.
	std::vector<int> ind;
	std::vector<char> skip_init;
	std::vector<int> old_ref;

	LRPlanarity(int N_, std::vector<std::array<int, 2>> edges_)
		: N(N_), M(int(edges_.size())), edges(std::move(edges_)),
		  height(N, -1), lowpt(2 * M), lowpt2(2 * M), nesting_depth(2 * M),
		  parent_edge(N, -1), in_DG(2 * M, 0), DG(N), adjs(N), ordered_adjs(N),
		  ref(2 * M, -1), side(2 * M, 1), stack_bottom(2 * M, -1), lowpt_edge(2 * M, -1),
		  left_ref(N, -1), right_ref(N, -1), embedding(N, M),
		  ind(N, 0), skip_init(2 * M, 0), old_ref(2 * M, -1) {}

	// def lr_planarity(self):
	//     """Execute the LR planarity test.
	//
	//     Returns
	//     -------
	//     embedding : dict
	//         If the graph is planar an embedding is returned. Otherwise None.
	//     """
	bool lr_planarity() {
		// if self.G.order() > 2 and self.G.size() > 3 * self.G.order() - 6:
		//     # graph is not planar
		//     return None
		if (N > 2 && M > 3 * N - 6) {
			return false;
		}

		// # make adjacency lists for dfs
		// for v in self.G:
		//     self.adjs[v] = list(self.G[v])
		for (int i = 0; i < M; i++) {
			adjs[edges[i][0]].push_back(2 * i);
			adjs[edges[i][1]].push_back(2 * i + 1);
		}

		// # orientation of the graph by depth first search traversal
		// for v in self.G:
		//     if self.height[v] is None:
		//         self.height[v] = 0
		//         self.roots.append(v)
		//         self.dfs_orientation(v)
		for (int v = 0; v < N; v++) {
			if (height[v] == -1) {
				height[v] = 0;
				roots.push_back(v);
				dfs_orientation(v);
			}
		}

		// # Free no longer used variables
		// self.G = None
		// self.lowpt2 = None
		// self.adjs = None
		lowpt2.clear();
		adjs.clear();

		// # testing
		// for v in self.DG:  # sort the adjacency lists by nesting depth
		//     # note: this sorting leads to non linear time
		//     self.ordered_adjs[v] = sorted(
		//         self.DG[v], key=lambda x: self.nesting_depth[(v, x)]
		//     )
		for (int v = 0; v < N; v++) {
			ordered_adjs[v] = DG[v];
			std::stable_sort(ordered_adjs[v].begin(), ordered_adjs[v].end(), [&](int x, int y) {
				return nesting_depth[x] < nesting_depth[y];
			});
		}
		// for v in self.roots:
		//     if not self.dfs_testing(v):
		//         return None
		std::fill(ind.begin(), ind.end(), 0);
		std::fill(skip_init.begin(), skip_init.end(), 0);
		for (int v : roots) {
			if (!dfs_testing(v)) {
				return false;
			}
		}

		// # Free no longer used variables
		// self.height = None
		// self.lowpt = None
		// self.S = None
		// self.stack_bottom = None
		// self.lowpt_edge = None
		height.clear();
		S.clear();
		stack_bottom.clear();
		lowpt_edge.clear();

		// for e in self.DG.edges:
		//     self.nesting_depth[e] = self.sign(e) * self.nesting_depth[e]
		for (int e = 0; e < 2 * M; e++) {
			if (in_DG[e]) nesting_depth[e] = sign(e) * nesting_depth[e];
		}

		// self.embedding.add_nodes_from(self.DG.nodes)
		// for v in self.DG:
		//     # sort the adjacency lists again
		//     self.ordered_adjs[v] = sorted(
		//         self.DG[v], key=lambda x: self.nesting_depth[(v, x)]
		//     )
		//     # initialize the embedding
		//     previous_node = None
		//     for w in self.ordered_adjs[v]:
		//         self.embedding.add_half_edge(v, w, ccw=previous_node)
		//         previous_node = w
		for (int v = 0; v < N; v++) {
			ordered_adjs[v] = DG[v];
			std::stable_sort(ordered_adjs[v].begin(), ordered_adjs[v].end(), [&](int x, int y) {
				return nesting_depth[x] < nesting_depth[y];
			});
			int previous_node = -1;
			for (int w : ordered_adjs[v]) {
				embedding.add_half_edge(v, w, -1, previous_node);
				previous_node = w;
			}
		}

		// # Free no longer used variables
		// self.DG = None
		// self.nesting_depth = None
		// self.ref = None
		DG.clear();
		nesting_depth.clear();
		ref.clear();

		// # compute the complete embedding
		// for v in self.roots:
		//     self.dfs_embedding(v)
		std::fill(ind.begin(), ind.end(), 0);
		for (int v : roots) {
			dfs_embedding(v);
		}

		// # Free no longer used variables
		// self.roots = None
		// self.parent_edge = None
		// self.ordered_adjs = None
		// self.left_ref = None
		// self.right_ref = None
		// self.side = None

		// return self.embedding
		return true;
	}

	// def dfs_orientation(self, v):
	//     """Orient the graph by DFS, compute lowpoints and nesting order."""
	void dfs_orientation(int v) {
		// # the recursion stack
		// dfs_stack = [v]
		std::vector<int> dfs_stack = {v};
		// # index of next edge to handle in adjacency list of each node
		// ind = defaultdict(lambda: 0)
		// # boolean to indicate whether to skip the initial work for an edge
		// skip_init = defaultdict(lambda: False)

		// while dfs_stack:
		while (!dfs_stack.empty()) {
			// v = dfs_stack.pop()
			v = dfs_stack.back();
			dfs_stack.pop_back();
			// e = self.parent_edge[v]
			int e = parent_edge[v];

			// for w in self.adjs[v][ind[v] :]:
			while (ind[v] < int(adjs[v].size())) {
				// vw = (v, w)
				int vw = adjs[v][ind[v]];
				int w = head(vw);

				// if not skip_init[vw]:
				if (!skip_init[vw]) {
					// if (v, w) in self.DG.edges or (w, v) in self.DG.edges:
					//     ind[v] += 1
					//     continue  # the edge was already oriented
					if (in_DG[vw] || in_DG[vw ^ 1]) {
						ind[v] += 1;
						continue;
					}

					// self.DG.add_edge(v, w)  # orient the edge
					in_DG[vw] = 1;
					DG[v].push_back(vw);

					// self.lowpt[vw] = self.height[v]
					// self.lowpt2[vw] = self.height[v]
					lowpt[vw] = height[v];
					lowpt2[vw] = height[v];
					// if self.height[w] is None:  # (v, w) is a tree edge
					if (height[w] == -1) {
						// self.parent_edge[w] = vw
						// self.height[w] = self.height[v] + 1
						parent_edge[w] = vw;
						height[w] = height[v] + 1;

						// dfs_stack.append(v)  # revisit v after finishing w
						// dfs_stack.append(w)  # visit w next
						// skip_init[vw] = True  # don't redo this block
						// break  # handle next node in dfs_stack (i.e. w)
						dfs_stack.push_back(v);
						dfs_stack.push_back(w);
						skip_init[vw] = 1;
						break;
					// else:  # (v, w) is a back edge
					//     self.lowpt[vw] = self.height[w]
					} else {
						lowpt[vw] = height[w];
					}
				}

				// # determine nesting graph
				// self.nesting_depth[vw] = 2 * self.lowpt[vw]
				// if self.lowpt2[vw] < self.height[v]:  # chordal
				//     self.nesting_depth[vw] += 1
				nesting_depth[vw] = 2 * lowpt[vw];
				if (lowpt2[vw] < height[v]) {
					nesting_depth[vw] += 1;
				}

				// # update lowpoints of parent edge e
				// if e is not None:
				if (e != -1) {
					// if self.lowpt[vw] < self.lowpt[e]:
					//     self.lowpt2[e] = min(self.lowpt[e], self.lowpt2[vw])
					//     self.lowpt[e] = self.lowpt[vw]
					if (lowpt[vw] < lowpt[e]) {
						lowpt2[e] = std::min(lowpt[e], lowpt2[vw]);
						lowpt[e] = lowpt[vw];
					// elif self.lowpt[vw] > self.lowpt[e]:
					//     self.lowpt2[e] = min(self.lowpt2[e], self.lowpt[vw])
					} else if (lowpt[vw] > lowpt[e]) {
						lowpt2[e] = std::min(lowpt2[e], lowpt[vw]);
					// else:
					//     self.lowpt2[e] = min(self.lowpt2[e], self.lowpt2[vw])
					} else {
						lowpt2[e] = std::min(lowpt2[e], lowpt2[vw]);
					}
				}

				// ind[v] += 1
				ind[v] += 1;
			}
		}
	}

	// def dfs_testing(self, v):
	//     """Test for LR partition."""
	bool dfs_testing(int v) {
		// # the recursion stack
		// dfs_stack = [v]
		std::vector<int> dfs_stack = {v};
		// # index of next edge to handle in adjacency list of each node
		// ind = defaultdict(lambda: 0)
		// # boolean to indicate whether to skip the initial work for an edge
		// skip_init = defaultdict(lambda: False)

		// while dfs_stack:
		while (!dfs_stack.empty()) {
			// v = dfs_stack.pop()
			v = dfs_stack.back();
			dfs_stack.pop_back();
			// e = self.parent_edge[v]
			int e = parent_edge[v];
			// # to indicate whether to skip the final block after the for loop
			// skip_final = False
			bool skip_final = false;

			// for w in self.ordered_adjs[v][ind[v] :]:
			while (ind[v] < int(ordered_adjs[v].size())) {
				// ei = (v, w)
				int ei = ordered_adjs[v][ind[v]];
				int w = head(ei);

				// if not skip_init[ei]:
				if (!skip_init[ei]) {
					// self.stack_bottom[ei] = top_of_stack(self.S)
					stack_bottom[ei] = top_of_stack(S);

					// if ei == self.parent_edge[w]:  # tree edge
					if (ei == parent_edge[w]) {
						// dfs_stack.append(v)  # revisit v after finishing w
						// dfs_stack.append(w)  # visit w next
						// skip_init[ei] = True  # don't redo this block
						// skip_final = True  # skip final work after breaking
						// break  # handle next node in dfs_stack (i.e. w)
						dfs_stack.push_back(v);
						dfs_stack.push_back(w);
						skip_init[ei] = 1;
						skip_final = true;
						break;
					// else:  # back edge
					//     self.lowpt_edge[ei] = ei
					//     self.S.append(ConflictPair(right=Interval(ei, ei)))
					} else {
						lowpt_edge[ei] = ei;
						S.push_back(ConflictPair{Interval{}, Interval{ei, ei}});
					}
				}

				// # integrate new return edges
				// if self.lowpt[ei] < self.height[v]:
				if (lowpt[ei] < height[v]) {
					// if w == self.ordered_adjs[v][0]:  # e_i has return edge
					//     self.lowpt_edge[e] = self.lowpt_edge[ei]
					if (ei == ordered_adjs[v][0]) {
						lowpt_edge[e] = lowpt_edge[ei];
					// else:  # add constraints of e_i
					//     if not self.add_constraints(ei, e):
					//         # graph is not planar
					//         return False
					} else {
						if (!add_constraints(ei, e)) {
							return false;
						}
					}
				}

				// ind[v] += 1
				ind[v] += 1;
			}

			// if not skip_final:
			//     # remove back edges returning to parent
			//     if e is not None:  # v isn't root
			//         self.remove_back_edges(e)
			if (!skip_final) {
				if (e != -1) {
					remove_back_edges(e);
				}
			}
		}

		// return True
		return true;
	}

	// def add_constraints(self, ei, e):
	bool add_constraints(int ei, int e) {
		// P = ConflictPair()
		ConflictPair P;
		// # merge return edges of e_i into P.right
		// while True:
		while (true) {
			// Q = self.S.pop()
			ConflictPair Q = S.back();
			S.pop_back();
			// if not Q.left.empty():
			//     Q.swap()
			if (!Q.left.empty()) {
				Q.swap();
			}
			// if not Q.left.empty():  # not planar
			//     return False
			if (!Q.left.empty()) {
				return false;
			}
			// if self.lowpt[Q.right.low] > self.lowpt[e]:
			if (lowpt[Q.right.low] > lowpt[e]) {
				// # merge intervals
				// if P.right.empty():  # topmost interval
				//     P.right = Q.right.copy()
				// else:
				//     self.ref[P.right.low] = Q.right.high
				// P.right.low = Q.right.low
				if (P.right.empty()) {
					P.right = Q.right.copy();
				} else {
					ref[P.right.low] = Q.right.high;
				}
				P.right.low = Q.right.low;
			// else:  # align
			//     self.ref[Q.right.low] = self.lowpt_edge[e]
			} else {
				ref[Q.right.low] = lowpt_edge[e];
			}
			// if top_of_stack(self.S) == self.stack_bottom[ei]:
			//     break
			if (top_of_stack(S) == stack_bottom[ei]) {
				break;
			}
		}
		// # merge conflicting return edges of e_1,...,e_i-1 into P.L
		// while top_of_stack(self.S).left.conflicting(ei, self) or top_of_stack(
		//     self.S
		// ).right.conflicting(ei, self):
		while (!S.empty() && (S.back().left.conflicting(ei, *this) || S.back().right.conflicting(ei, *this))) {
			// Q = self.S.pop()
			ConflictPair Q = S.back();
			S.pop_back();
			// if Q.right.conflicting(ei, self):
			//     Q.swap()
			if (Q.right.conflicting(ei, *this)) {
				Q.swap();
			}
			// if Q.right.conflicting(ei, self):  # not planar
			//     return False
			if (Q.right.conflicting(ei, *this)) {
				return false;
			}
			// # merge interval below lowpt(e_i) into P.R
			// self.ref[P.right.low] = Q.right.high
			// if Q.right.low is not None:
			//     P.right.low = Q.right.low
			ref[P.right.low] = Q.right.high;
			if (Q.right.low != -1) {
				P.right.low = Q.right.low;
			}

			// if P.left.empty():  # topmost interval
			//     P.left = Q.left.copy()
			// else:
			//     self.ref[P.left.low] = Q.left.high
			// P.left.low = Q.left.low
			if (P.left.empty()) {
				P.left = Q.left.copy();
			} else {
				ref[P.left.low] = Q.left.high;
			}
			P.left.low = Q.left.low;
		}

		// if not (P.left.empty() and P.right.empty()):
		//     self.S.append(P)
		// return True
		if (!(P.left.empty() && P.right.empty())) {
			S.push_back(P);
		}
		return true;
	}

	// def remove_back_edges(self, e):
	void remove_back_edges(int e) {
		// u = e[0]
		int u = tail(e);
		// # trim back edges ending at parent u
		// # drop entire conflict pairs
		// while self.S and top_of_stack(self.S).lowest(self) == self.height[u]:
		while (!S.empty() && S.back().lowest(*this) == height[u]) {
			// P = self.S.pop()
			// if P.left.low is not None:
			//     self.side[P.left.low] = -1
			ConflictPair P = S.back();
			S.pop_back();
			if (P.left.low != -1) {
				side[P.left.low] = -1;
			}
		}

		// if self.S:  # one more conflict pair to consider
		if (!S.empty()) {
			// P = self.S.pop()
			ConflictPair P = S.back();
			S.pop_back();
			// # trim left interval
			// while P.left.high is not None and P.left.high[1] == u:
			//     P.left.high = self.ref[P.left.high]
			while (P.left.high != -1 && head(P.left.high) == u) {
				P.left.high = ref[P.left.high];
			}
			// if P.left.high is None and P.left.low is not None:
			//     # just emptied
			//     self.ref[P.left.low] = P.right.low
			//     self.side[P.left.low] = -1
			//     P.left.low = None
			if (P.left.high == -1 && P.left.low != -1) {
				ref[P.left.low] = P.right.low;
				side[P.left.low] = -1;
				P.left.low = -1;
			}
			// # trim right interval
			// while P.right.high is not None and P.right.high[1] == u:
			//     P.right.high = self.ref[P.right.high]
			while (P.right.high != -1 && head(P.right.high) == u) {
				P.right.high = ref[P.right.high];
			}
			// if P.right.high is None and P.right.low is not None:
			//     # just emptied
			//     self.ref[P.right.low] = P.left.low
			//     self.side[P.right.low] = -1
			//     P.right.low = None
			if (P.right.high == -1 && P.right.low != -1) {
				ref[P.right.low] = P.left.low;
				side[P.right.low] = -1;
				P.right.low = -1;
			}
			// self.S.append(P)
			S.push_back(P);
		}

		// # side of e is side of a highest return edge
		// if self.lowpt[e] < self.height[u]:  # e has return edge
		if (lowpt[e] < height[u]) {
			// hl = top_of_stack(self.S).left.high
			// hr = top_of_stack(self.S).right.high
			int hl = S.back().left.high;
			int hr = S.back().right.high;

			// if hl is not None and (hr is None or self.lowpt[hl] > self.lowpt[hr]):
			//     self.ref[e] = hl
			// else:
			//     self.ref[e] = hr
			if (hl != -1 && (hr == -1 || lowpt[hl] > lowpt[hr])) {
				ref[e] = hl;
			} else {
				ref[e] = hr;
			}
		}
	}

	// def dfs_embedding(self, v):
	//     """Completes the embedding."""
	void dfs_embedding(int v) {
		// # the recursion stack
		// dfs_stack = [v]
		std::vector<int> dfs_stack = {v};
		// # index of next edge to handle in adjacency list of each node
		// ind = defaultdict(lambda: 0)

		// while dfs_stack:
		while (!dfs_stack.empty()) {
			// v = dfs_stack.pop()
			v = dfs_stack.back();
			dfs_stack.pop_back();

			// for w in self.ordered_adjs[v][ind[v] :]:
			while (ind[v] < int(ordered_adjs[v].size())) {
				// ind[v] += 1
				// ei = (v, w)
				int ei = ordered_adjs[v][ind[v]];
				int w = head(ei);
				ind[v] += 1;

				// if ei == self.parent_edge[w]:  # tree edge
				if (ei == parent_edge[w]) {
					// self.embedding.add_half_edge_first(w, v)
					// self.left_ref[v] = w
					// self.right_ref[v] = w
					embedding.add_half_edge_first(w, ei ^ 1);
					left_ref[v] = ei;
					right_ref[v] = ei;

					// dfs_stack.append(v)  # revisit v after finishing w
					// dfs_stack.append(w)  # visit w next
					// break  # handle next node in dfs_stack (i.e. w)
					dfs_stack.push_back(v);
					dfs_stack.push_back(w);
					break;
				// else:  # back edge
				} else {
					// if self.side[ei] == 1:
					//     self.embedding.add_half_edge(w, v, ccw=self.right_ref[w])
					if (side[ei] == 1) {
						embedding.add_half_edge(w, ei ^ 1, -1, right_ref[w]);
					// else:
					//     self.embedding.add_half_edge(w, v, cw=self.left_ref[w])
					//     self.left_ref[w] = v
					} else {
						embedding.add_half_edge(w, ei ^ 1, left_ref[w], -1);
						left_ref[w] = ei ^ 1;
					}
				}
			}
		}
	}

	// def sign(self, e):
	//     """Resolve the relative side of an edge to the absolute side."""
	int sign(int e) {
		// # the recursion stack
		// dfs_stack = [e]
		std::vector<int> dfs_stack = {e};
		// # dict to remember reference edges
		// old_ref = defaultdict(lambda: None)

		// while dfs_stack:
		while (!dfs_stack.empty()) {
			// e = dfs_stack.pop()
			e = dfs_stack.back();
			dfs_stack.pop_back();

			// if self.ref[e] is not None:
			if (ref[e] != -1) {
				// dfs_stack.append(e)  # revisit e after finishing self.ref[e]
				// dfs_stack.append(self.ref[e])  # visit self.ref[e] next
				// old_ref[e] = self.ref[e]  # remember value of self.ref[e]
				// self.ref[e] = None
				dfs_stack.push_back(e);
				dfs_stack.push_back(ref[e]);
				old_ref[e] = ref[e];
				ref[e] = -1;
			// else:
			//     self.side[e] *= self.side[old_ref[e]]
			// # translator's note: old_ref is fresh per call and side[None] == 1, so an
			// # edge whose ref was already resolved by an earlier call is left unchanged;
			// # resetting old_ref[e] after use reproduces that with one shared vector.
			} else {
				if (old_ref[e] != -1) side[e] *= side[old_ref[e]];
				old_ref[e] = -1;
			}
		}

		// return self.side[e]
		return side[e];
	}
};

// def conflicting(self, b, planarity_state):
bool Interval::conflicting(int b, const LRPlanarity& planarity_state) const {
	// return (
	//     not self.empty()
	//     and planarity_state.lowpt[self.high] > planarity_state.lowpt[b]
	// )
	return !empty() && planarity_state.lowpt[high] > planarity_state.lowpt[b];
}

// def lowest(self, planarity_state):
int ConflictPair::lowest(const LRPlanarity& planarity_state) const {
	// if self.left.empty():
	//     return planarity_state.lowpt[self.right.low]
	if (left.empty()) {
		return planarity_state.lowpt[right.low];
	}
	// if self.right.empty():
	//     return planarity_state.lowpt[self.left.low]
	if (right.empty()) {
		return planarity_state.lowpt[left.low];
	}
	// return min(
	//     planarity_state.lowpt[self.left.low], planarity_state.lowpt[self.right.low]
	// )
	return std::min(planarity_state.lowpt[left.low], planarity_state.lowpt[right.low]);
}

} // namespace

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int T;
	std::cin >> T;
	while (T--) {
		int N, M;
		std::cin >> N >> M;
		std::vector<std::array<int, 2>> edges(M);
		for (auto& e : edges) {
			std::cin >> e[0] >> e[1];
		}
		LRPlanarity lr(N, std::move(edges));
		if (!lr.lr_planarity()) {
			std::cout << "No\n";
			continue;
		}
		std::cout << "Yes\n";
		// # translator's note: embedding.neighbors_cw_order(v) starts at the first
		// # successor of v and follows the "cw" links; here we start at the leftmost
		// # neighbor.
		for (int v = 0; v < N; v++) {
			int d0 = lr.embedding.leftmost_nbr[v];
			if (d0 != -1) {
				int d = d0;
				bool first = true;
				do {
					if (!first) std::cout << ' ';
					first = false;
					std::cout << lr.head(d);
					d = lr.embedding.cw[d];
				} while (d != d0);
			}
			std::cout << '\n';
		}
	}
	return 0;
}
