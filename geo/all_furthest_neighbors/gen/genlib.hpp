#ifndef ALL_FURTHEST_NEIGHBORS_GENLIB_HPP
#define ALL_FURTHEST_NEIGHBORS_GENLIB_HPP

#include <algorithm>
#include <cstdio>
#include <numeric>
#include <utility>
#include <vector>

#include "../params.h"
#include "random.h"

using ll = long long;
using Point = std::pair<ll, ll>;

std::vector<Point> primitive_polygon(int n) {
  int quarter = (n + 3) / 4;
  int bound = 1;
  std::vector<Point> candidates;
  while (true) {
    candidates.clear();
    for (int x = 1; x <= bound; ++x) {
      for (int y = 1; y <= bound; ++y) {
        if (std::gcd(x, y) == 1) candidates.emplace_back(x, y);
      }
    }
    if (int(candidates.size()) >= quarter) break;
    bound *= 2;
  }
  std::sort(candidates.begin(), candidates.end(), [](Point a, Point b) {
    return a.second * b.first < b.second * a.first;
  });

  std::vector<Point> edges;
  edges.reserve(4 * quarter);
  for (int rotation = 0; rotation < 4; ++rotation) {
    for (int i = 0; i < quarter; ++i) {
      Point e = candidates[ll(i) * candidates.size() / quarter];
      ll x = e.first;
      ll y = e.second;
      if (rotation == 0) edges.emplace_back(x, y);
      if (rotation == 1) edges.emplace_back(-y, x);
      if (rotation == 2) edges.emplace_back(-x, -y);
      if (rotation == 3) edges.emplace_back(y, -x);
    }
  }

  std::vector<Point> polygon;
  polygon.reserve(edges.size());
  ll x = 0;
  ll y = 0;
  for (Point e : edges) {
    polygon.emplace_back(x, y);
    x += e.first;
    y += e.second;
  }

  ll min_x = polygon[0].first;
  ll max_x = polygon[0].first;
  ll min_y = polygon[0].second;
  ll max_y = polygon[0].second;
  for (Point p : polygon) {
    min_x = std::min(min_x, p.first);
    max_x = std::max(max_x, p.first);
    min_y = std::min(min_y, p.second);
    max_y = std::max(max_y, p.second);
  }
  ll diameter = std::max(max_x - min_x, max_y - min_y);
  ll scale = 2LL * X_AND_Y_ABS_MAX / diameter;
  for (Point& p : polygon) {
    p.first *= scale;
    p.second *= scale;
  }
  min_x *= scale;
  max_x *= scale;
  min_y *= scale;
  max_y *= scale;
  ll shift_x = -(min_x + max_x) / 2;
  ll shift_y = -(min_y + max_y) / 2;
  for (Point& p : polygon) {
    p.first += shift_x;
    p.second += shift_y;
  }

  if (int(polygon.size()) > n) {
    std::vector<Point> selected;
    selected.reserve(n);
    for (int i = 0; i < n; ++i) {
      selected.push_back(polygon[ll(i) * polygon.size() / n]);
    }
    polygon.swap(selected);
  }
  return polygon;
}

std::vector<Point> select_vertices(const std::vector<Point>& polygon,
                                   std::vector<int> ids) {
  std::sort(ids.begin(), ids.end());
  std::vector<Point> result;
  result.reserve(ids.size());
  for (int i : ids) result.push_back(polygon[i]);
  return result;
}

void cyclic_shift(std::vector<Point>& polygon, Random& gen) {
  int shift = gen.uniform<int>(0, int(polygon.size()) - 1);
  std::rotate(polygon.begin(), polygon.begin() + shift, polygon.end());
}

void rotate_quarter(std::vector<Point>& polygon, int rotation) {
  rotation %= 4;
  for (Point& p : polygon) {
    ll x = p.first;
    ll y = p.second;
    if (rotation == 1) p = {-y, x};
    if (rotation == 2) p = {-x, -y};
    if (rotation == 3) p = {y, -x};
  }
}

void output(const std::vector<std::vector<Point>>& cases) {
  printf("%d\n", int(cases.size()));
  for (const auto& polygon : cases) {
    printf("%d\n", int(polygon.size()));
    for (Point p : polygon) printf("%lld %lld\n", p.first, p.second);
  }
}

#endif
