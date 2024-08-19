template <typename K>
struct Group_Affine {
  using F = pair<K, K>;
  using value_type = F;
  static constexpr F op(const F &x, const F &y) noexcept {
    return F({x.first * y.first, x.second * y.first + y.second});
  }
  static constexpr F inversecond(const F &x) {
    auto [a, b] = x;
    a = K(1) / a;
    return {a, a * (-b)};
  }
  static constexpr K eval(const F &f, K x) noexcept { return f.first * x + f.second; }
  static constexpr F unit() { return {K(1), K(0)}; }
  static constexpr bool commute = false;
};