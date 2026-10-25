#include <algorithm>
#include <array>
#include <string>
#include <vector>
#include "testlib.h"

using namespace std;

struct Graph {
  int V, E;
  vector<array<int, 2>> ends;  // ends[e]: endpoints of edge e
};

Graph read_graph(InStream& stream) {
  Graph g;
  g.V = stream.readInt();
  g.E = stream.readInt();
  g.ends.resize(g.E);
  for (auto& [a, b] : g.ends) {
    a = stream.readInt();
    b = stream.readInt();
  }
  return g;
}

// -1: invalid, 0: No, 1: Yes
int read_yes_no(InStream& stream) {
  string token = stream.readToken();
  if (token == "No") return 0;
  if (token == "Yes") return 1;
  return -1;
}

// Reads a rotation system (for each vertex, its neighbors in cyclic order) and
// checks that it is a planar embedding.
// Dart p is the p-th listed neighbor; nxt[p] is the dart after p around its tail
// and twin[p] the reverse dart, so the dart after p on its face is nxt[twin[p]].
void read_embedding(const Graph& g, InStream& stream, int tc) {
  int V = g.V, E = g.E;
  vector<int> deg(V, 0);
  for (auto [a, b] : g.ends) deg[a]++, deg[b]++;

  // (tail, head, dart) for the listed darts and (tail, head, 2 * e + side) for the graph's
  vector<array<int, 3>> listed(2 * E), graph_darts(2 * E);
  vector<int> nxt(2 * E), twin(2 * E);
  if (!stream.seekEoln()) stream.quitf(_pe, "case %d: expected end of line after Yes", tc);
  for (int v = 0, p = 0; v < V; v++) {
    for (int i = 0; i < deg[v]; i++, p++) {
      if (stream.seekEoln()) {
        stream.quitf(_pe, "case %d: expected %d neighbors on the line of vertex %d, found %d", tc, deg[v], v, i);
      }
      listed[p] = {v, stream.readInt(0, V - 1, "neighbor"), p};
      nxt[p] = i + 1 < deg[v] ? p + 1 : p - i;
    }
    if (!stream.seekEoln()) {
      stream.quitf(_pe, "case %d: expected %d neighbors on the line of vertex %d, found more", tc, deg[v], v);
    }
  }
  for (int e = 0; e < E; e++) {
    for (int side = 0; side < 2; side++) {
      graph_darts[2 * e + side] = {g.ends[e][side], g.ends[e][side ^ 1], 2 * e + side};
    }
  }
  sort(listed.begin(), listed.end());
  sort(graph_darts.begin(), graph_darts.end());
  // Each vertex lists exactly deg(v) darts, so listed[i][0] == graph_darts[i][0] for all i
  // and the two lists match if and only if the heads agree.
  vector<int> pos(2 * E);  // pos[2 * e + side]: the listed dart equal to it
  for (int i = 0; i < 2 * E; i++) {
    auto [v, w, p] = listed[i];
    if (w < graph_darts[i][1]) {
      if (i > 0 && listed[i - 1][0] == v && listed[i - 1][1] == w) {
        stream.quitf(_wa, "case %d: vertex %d listed twice around vertex %d", tc, w, v);
      }
      stream.quitf(_wa, "case %d: vertex %d is not adjacent to vertex %d", tc, w, v);
    } else if (w > graph_darts[i][1]) {
      stream.quitf(_wa, "case %d: vertex %d is missing around vertex %d", tc, graph_darts[i][1], v);
    }
    pos[graph_darts[i][2]] = p;
  }
  for (int d = 0; d < 2 * E; d++) twin[pos[d]] = pos[d ^ 1];

  // F = 2C + E - V, over the components with at least one edge
  int expected_face_cycles = 0;
  {
    vector<bool> has_edge(V, false);
    vector<int> par(V, -1);
    auto get_par = [&](int a) -> int {
      while (par[a] >= 0) {
        if (par[par[a]] >= 0) par[a] = par[par[a]];
        a = par[a];
      }
      return a;
    };
    auto merge = [&](int a, int b) -> bool {
      a = get_par(a), b = get_par(b);
      if (a == b) return false;
      if (par[a] > par[b]) swap(a, b);
      par[a] += par[b];
      par[b] = a;
      return true;
    };
    for (int e = 0; e < E; e++) {
      for (int u : g.ends[e]) {
        if (!has_edge[u]) {
          has_edge[u] = true;
          expected_face_cycles++;
        }
      }
      expected_face_cycles += 1 - 2 * merge(g.ends[e][0], g.ends[e][1]);
    }
  }

  int num_face_cycles = 0;
  {
    vector<bool> face_vis(2 * E, false);
    for (int d = 0; d < 2 * E; d++) {
      if (face_vis[d]) continue;
      num_face_cycles++;
      for (int cur = d; !face_vis[cur]; cur = nxt[twin[cur]]) face_vis[cur] = true;
    }
  }
  // Non-planar rotation systems have fewer faces.
  if (num_face_cycles != expected_face_cycles) {
    stream.quitf(_wa, "case %d: rotation system is not planar (%d faces, a planar embedding has %d)",
                 tc, num_face_cycles, expected_face_cycles);
  }
}

int main(int argc, char* argv[]) {
  registerTestlibCmd(argc, argv);

  int T = inf.readInt();
  for (int tc = 0; tc < T; tc++) {
    Graph g = read_graph(inf);
    int jury_answer = read_yes_no(ans);
    if (jury_answer == -1) quitf(_fail, "writer's output is invalid (case %d)", tc);
    if (ouf.seekEof()) quitf(_wa, "unexpected EOF in the participant's output (case %d)", tc);
    int participant_answer = read_yes_no(ouf);
    if (participant_answer == -1) quitf(_wa, "case %d: expected Yes or No", tc);
    if (jury_answer == 1) read_embedding(g, ans, tc);
    if (participant_answer == 1) read_embedding(g, ouf, tc);
    if (jury_answer == 1 && participant_answer == 0) {
      quitf(_wa, "case %d: the graph is planar, but participant printed No", tc);
    }
    if (jury_answer == 0 && participant_answer == 1) {
      quitf(_fail, "case %d: participant found a planar embedding, but the answer says No", tc);
    }
  }
  if (!ouf.seekEof()) quitf(_wa, "participant's output contains extra tokens");
  quitf(_ok, "%d cases", T);
}
