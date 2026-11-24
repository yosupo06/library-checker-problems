// https://qandori.github.io/cp-library/lightweight/math/combinatorics/binomial_prefix_sum.hpp.html
#include <type_traits>
#include <utility>
namespace cp_library_cxx17 {
template<class T> constexpr T bit_floor(T x) {
    if (!x) return 0;
    T result = 1;
    while (x >>= 1) result <<= 1;
    return result;
}
template<class T> constexpr T bit_ceil(T x) {
    T result = 1;
    while (result < x) result <<= 1;
    return result;
}
template<class T> constexpr bool has_single_bit(T x) {
    return x && !(x & (x - 1));
}
template<class T> struct TypeIdentity { using type = T; };
template<class T> using type_identity_t = typename TypeIdentity<T>::type;
template<class T, class = void> struct HasEquality : std::false_type {};
template<class T> struct HasEquality<T, std::void_t<decltype(std::declval<const T&>() == T(0))>> : std::true_type {};
}
#line 1 "math/combinatorics/binomial_prefix_sum_light.hpp"


#include <cmath>
#line 1 "components/binomial_prefix_core_light.hpp"



#line 1 "components/factorial_table_light.hpp"



#line 1 "math/mint.hpp"


#include <cassert>
#include <istream>
#include <ostream>
#include <type_traits>

#if defined(__GNUC__) && !defined(__clang__) && (defined(__x86_64__) || defined(__i386__))
#pragma GCC push_options
#pragma GCC optimize("O3")
#endif

namespace mint_detail {
template <class I>
constexpr bool mint_integral = std::is_integral_v<I>
#if defined(__SIZEOF_INT128__)
							   || std::is_same_v<I, __int128> || std::is_same_v<I, unsigned __int128>
#endif
	;
struct Mint {
	using mint = Mint;
	unsigned v = 0;
	static constexpr unsigned mod() { return 998244353; }
	static unsigned reduce(unsigned long long x) {
		return (x + (unsigned long long)(unsigned(x) * 998244351u) * mod()) >> 32;
	}
	[[gnu::always_inline]] Mint() = default;
	template <class I, std::enable_if_t<mint_integral<I>, int> = 0>
	Mint(I x) {
		long long r = x % (long long)mod();
		if (r < 0) r += mod();
		v = reduce((unsigned long long)r * 932051910);
	}
	static Mint raw(unsigned x) {
		Mint a;
		a.v = reduce((unsigned long long)x * 932051910);
		return a;
	}
	static Mint word(unsigned x) {
		Mint a;
		a.v = x;
		return a;
	}
	unsigned val() const {
		unsigned r = reduce(v);
		return r < mod() ? r : r - mod();
	}
	friend std::istream &operator>>(std::istream &is, Mint &x) {
		long long value;
		if (is >> value) x = Mint(value);
		return is;
	}
	friend std::ostream &operator<<(std::ostream &os, const Mint &x) {
		return os << x.val();
	}
	Mint &operator+=(Mint b) {
		v += b.v;
		if (v >= 2 * mod()) v -= 2 * mod();
		return *this;
	}
	Mint &operator-=(Mint b) {
		v -= b.v;
		if (v >> 31) v += 2 * mod();
		return *this;
	}
	Mint &operator*=(Mint b) {
		v = reduce((unsigned long long)v * b.v);
		return *this;
	}
	Mint &operator/=(Mint b) { return *this *= b.inv(); }
	Mint &operator++() { return *this += Mint(1); }
	Mint &operator--() { return *this -= Mint(1); }
	Mint operator++(int) {
		Mint a = *this;
		++*this;
		return a;
	}
	Mint operator--(int) {
		Mint a = *this;
		--*this;
		return a;
	}
	Mint operator+() const { return *this; }
	Mint operator-() const { return word(v ? 2 * mod() - v : 0); }
	Mint operator+(Mint b) const { return Mint(*this) += b; }
	Mint operator-(Mint b) const { return Mint(*this) -= b; }
	Mint operator*(Mint b) const { return Mint(*this) *= b; }
	Mint operator/(Mint b) const { return Mint(*this) /= b; }
	bool operator==(Mint b) const { return (v < mod() ? v : v - mod()) == (b.v < mod() ? b.v : b.v - mod()); }
	bool operator!=(Mint b) const { return !(*this == b); }
	template <class I, std::enable_if_t<mint_integral<I>, int> = 0>
	friend Mint operator+(I a, Mint b) { return Mint(a) + b; }
	template <class I, std::enable_if_t<mint_integral<I>, int> = 0>
	friend Mint operator-(I a, Mint b) { return Mint(a) - b; }
	template <class I, std::enable_if_t<mint_integral<I>, int> = 0>
	friend Mint operator*(I a, Mint b) { return Mint(a) * b; }
	template <class I, std::enable_if_t<mint_integral<I>, int> = 0>
	friend Mint operator/(I a, Mint b) { return Mint(a) / b; }
	template <class I, std::enable_if_t<mint_integral<I>, int> = 0>
	friend bool operator==(I a, Mint b) { return Mint(a) == b; }
	template <class I, std::enable_if_t<mint_integral<I>, int> = 0>
	friend bool operator!=(I a, Mint b) { return Mint(a) != b; }
	Mint pow(long long n) const {
		assert(n >= 0);
		if (!n) return Mint(1);
		Mint r(1), a = *this;
		for (; n > 1; n >>= 1, a *= a)
			if (n & 1) r *= a;
		return r * a;
	}
	[[gnu::noinline]] Mint inv() const {
		assert(*this != Mint(0));
		Mint a2 = *this * *this, a3 = a2 * *this;
		Mint a7 = a3 * a3 * *this;
		Mint a31 = a7;
		for (int i = 0; i < 2; ++i) a31 *= a31;
		a31 *= a3;
		Mint r = a7;
		for (int i = 0; i < 3; ++i) r *= r;
		r *= a3;
		r *= r;
		for (int j = 0; j < 4; ++j) {
			for (int i = 0; i < 5; ++i) r *= r;
			r *= a31;
		}
		for (int i = 0; i < 3; ++i) r *= r;
		return r * a7;
	}
};
} // namespace mint_detail

using mint = mint_detail::Mint;
using fps_mint = mint;

#if defined(__GNUC__) && !defined(__clang__) && (defined(__x86_64__) || defined(__i386__))
#pragma GCC pop_options
#endif


#line 5 "components/factorial_table_light.hpp"
#include <algorithm>
#line 7 "components/factorial_table_light.hpp"
#include <cstdint>
#include <limits>
#include <vector>

namespace light_factorial_detail {
template<class Mint> struct Table {
	decltype(Mint::mod()) modulus;
	std::vector<Mint> factorial, inverse_factorial;

	explicit Table(int max_n) : modulus(Mint::mod()) {
		assert(0 <= max_n && max_n < std::numeric_limits<int>::max() && modulus > 1);
		int n = static_cast<int>(std::min(std::uint64_t(max_n), std::uint64_t(modulus) - 1));
		factorial.resize(n + 1), inverse_factorial.resize(n + 1);
		factorial[0] = Mint(1);
		for (int i = 1; i <= n; ++i) factorial[i] = factorial[i - 1] * Mint(i);
		inverse_factorial[n] = factorial[n].inv();
		for (int i = n; i > 0; --i) inverse_factorial[i - 1] = inverse_factorial[i] * Mint(i);
	}
};
}


#line 6 "components/binomial_prefix_core_light.hpp"

namespace light_binomial_prefix_detail {
template<class Mint> struct Table : light_factorial_detail::Table<Mint> {
	using Base = light_factorial_detail::Table<Mint>;
	using Base::factorial;
	using Base::inverse_factorial;
	std::vector<Mint> power2;
	Mint half;

	explicit Table(int n = 0) : Base(n) {
		assert(std::uint64_t(n) < Mint::mod());
		power2.resize(n + 1);
		power2[0] = Mint(1);
		for (int i = 1; i <= n; ++i) power2[i] = power2[i - 1] + power2[i - 1];
		half = Mint((std::uint64_t(Mint::mod()) + 1) / 2);
	}
	void build(int n) { *this = Table(n); }
	Mint binom(int n, int k) const {
		if (k < 0 || k > n) return Mint(0);
		return factorial[n] * inverse_factorial[k] * inverse_factorial[n - k];
	}
	Mint center(int n) const {
		if (!n) return Mint(0);
		return n & 1 ? power2[n - 1] : (power2[n] - binom(n, n / 2)) * half;
	}
	Mint range(int n, int l, int r) const {
		assert(0 <= l && l <= r && r <= n + 1);
		Mint sum(0);
		for (int i = l; i < r; ++i) sum += inverse_factorial[i] * inverse_factorial[n - i];
		return factorial[n] * sum;
	}
};
}


#line 1 "components/binomial_prefix_polynomial_light.hpp"



#line 1 "components/binomial_prefix_polynomial_base.hpp"



#line 7 "components/binomial_prefix_polynomial_base.hpp"
#include <utility>
#line 9 "components/binomial_prefix_polynomial_base.hpp"

#if defined(__GNUC__) && !defined(__clang__) && (defined(__x86_64__) || defined(__i386__))
#pragma GCC push_options
#pragma GCC optimize("O3")
#endif

namespace binomial_prefix_detail {
template<class Mint> struct PolynomialScalarArithmetic {
	using F = std::vector<Mint>;
	static void add(F& a, const F& b) {
		a.resize(std::max(a.size(), b.size()));
		for (std::size_t i = 0; i < b.size(); ++i) a[i] += b[i];
	}
	static void trim(F& a) {
		if constexpr (cp_library_cxx17::HasEquality<Mint>::value)
			while (!a.empty() && a.back() == Mint(0)) a.pop_back();
	}
	static F multiply(const F& a, const F& b) {
		if (a.empty() || b.empty()) return {};
		F c(a.size() + b.size() - 1);
		if (std::min(a.size(), b.size()) <= 32) {
			for (std::size_t i = 0; i < a.size(); ++i)
				for (std::size_t j = 0; j < b.size(); ++j) c[i + j] += a[i] * b[j];
			return c;
		}
		std::size_t mid = (std::max(a.size(), b.size()) + 1) / 2;
		F al(a.begin(), a.begin() + std::min(mid, a.size()));
		F ah(a.begin() + std::min(mid, a.size()), a.end());
		F bl(b.begin(), b.begin() + std::min(mid, b.size()));
		F bh(b.begin() + std::min(mid, b.size()), b.end());
		F low = multiply(al, bl), high = multiply(ah, bh);
		add(al, ah), add(bl, bh);
		F cross = multiply(al, bl);
		for (std::size_t i = 0; i < low.size(); ++i) cross[i] -= low[i], c[i] += low[i];
		for (std::size_t i = 0; i < high.size(); ++i) cross[i] -= high[i], c[2 * mid + i] += high[i];
		for (std::size_t i = 0; i < cross.size() && mid + i < c.size(); ++i) c[mid + i] += cross[i];
		return c;
	}
	static F inverse(const F& a, std::size_t size) {
		Mint constant = a[0];
		F b{constant.inv()};
		while (b.size() < size) {
			std::size_t next = b.size() + std::min(b.size(), size - b.size());
			F prefix(a.begin(), a.begin() + std::min(a.size(), next));
			F error = multiply(prefix, b);
			error.resize(next);
			for (auto& x : error) x = Mint(0) - x;
			error[0] += Mint(2);
			b = multiply(b, error);
			b.resize(next);
		}
		return b;
	}
	static F remainder(F a, const F& b) {
		trim(a);
		if (a.size() < b.size()) return a;
		std::size_t size = a.size() - b.size() + 1;
		if (size <= 32 || b.size() <= 32) {
			for (std::size_t i = size; i-- > 0;) {
				Mint coefficient = a[i + b.size() - 1];
				for (std::size_t j = 0; j + 1 < b.size(); ++j) a[i + j] -= coefficient * b[j];
			}
		} else {
			F reversed(b.rbegin(), b.rend());
			F top(a.rbegin(), a.rbegin() + size);
			F quotient = multiply(top, inverse(reversed, size));
			quotient.resize(size);
			std::reverse(quotient.begin(), quotient.end());
			F product = multiply(quotient, b);
			for (std::size_t i = 0; i + 1 < b.size(); ++i) a[i] -= product[i];
		}
		a.resize(b.size() - 1);
		trim(a);
		return a;
	}
	static Mint eval(const F& a, Mint x) {
		Mint value(0);
		for (auto i = a.rbegin(); i != a.rend(); ++i) value = value * x + *i;
		return value;
	}
};

template<class Mint, class Series> struct PolynomialSeriesArithmetic : PolynomialScalarArithmetic<Mint> {
	using F = Series;
	static void add(F& a, const F& b) { a += b; }
	static F multiply(const F& a, const F& b) {
		if (!a.empty() && !b.empty() && a.size() + b.size() - 1 > (1 << 23))
			return F(PolynomialScalarArithmetic<Mint>::multiply(a, b));
		return F::multiply(a, b);
	}
	static F remainder(F a, const F& b) {
		PolynomialScalarArithmetic<Mint>::trim(a);
		if (a.size() < b.size()) return a;
		if (a.size() > (1 << 22)) return F(PolynomialScalarArithmetic<Mint>::remainder(std::move(a), b));
		return a.divmod(b).second;
	}
};

template<class Mint, class Arithmetic, class Table> class PolynomialEvaluator {
	using F = typename Arithmetic::F;
	struct Point { int m, n; std::uint32_t id; };
	struct Node {
		F product, sum, modulus;
		int begin = 0, end = 0, start = 0;
	};
	static constexpr int block = 16;
	const Table& table_;
	std::vector<Point> points_;
	std::vector<int> groups_;
	std::vector<Node> tree_;
	std::vector<Mint>& result_;
	const Point& point(int i) const { return points_[groups_[i]]; }
	std::pair<F, F> basis(int a, int b) const {
		if (a == b) return {F{1}, F{}};
		if (b - a <= 24) {
			F product{1}, sum(b - a);
			for (int i = a; i < b; ++i) {
				for (int j = 0; j < int(product.size()); ++j) sum[j] += product[j] * table_.inverse_factorial[i];
				product.push_back(product.back());
				for (int j = int(product.size()) - 2; j >= 1; --j) product[j] = product[j - 1] - product[j] * Mint(i);
				product[0] *= Mint(0) - Mint(i);
			}
			PolynomialScalarArithmetic<Mint>::trim(sum);
			return {std::move(product), std::move(sum)};
		}
		int mid = a + (b - a) / 2;
		auto [left, sum] = basis(a, mid);
		auto [right, tail] = basis(mid, b);
		Arithmetic::add(sum, Arithmetic::multiply(left, tail));
		left = Arithmetic::multiply(left, right);
		PolynomialScalarArithmetic<Mint>::trim(sum);
		return {std::move(left), std::move(sum)};
	}
	void build(int node, int l, int r, int start, bool need_basis) {
		auto& cur = tree_[node];
		cur.begin = l, cur.end = r, cur.start = start;
		if (r - l <= block) {
			if (need_basis) {
				auto pair = basis(start, point(r - 1).m);
				cur.product = std::move(pair.first), cur.sum = std::move(pair.second);
			}
			if (node == 1) return;
			cur.modulus = {1};
			for (int i = l; i < r; ++i) {
				Mint x(point(i).n);
				cur.modulus.push_back(cur.modulus.back());
				for (int j = int(cur.modulus.size()) - 2; j >= 1; --j) cur.modulus[j] = cur.modulus[j - 1] - x * cur.modulus[j];
				cur.modulus[0] *= Mint(0) - x;
			}
			return;
		}
		int mid = l + (r - l) / 2;
		build(2 * node, l, mid, start, true);
		build(2 * node + 1, mid, r, point(mid - 1).m, need_basis);
		const auto& left = tree_[2 * node];
		const auto& right = tree_[2 * node + 1];
		if (node != 1) cur.modulus = Arithmetic::multiply(left.modulus, right.modulus);
		if (need_basis) {
			cur.product = Arithmetic::multiply(left.product, right.product);
			cur.sum = left.sum;
			Arithmetic::add(cur.sum, Arithmetic::multiply(left.product, right.sum));
			PolynomialScalarArithmetic<Mint>::trim(cur.sum);
		}
	}
	void evaluate(int node, F sum, F product) {
		const auto& cur = tree_[node];
		if (cur.end - cur.begin <= block) {
			for (int i = cur.begin; i < cur.end; ++i) {
				const auto& query = point(i);
				const int m = query.m, n = query.n;
				const Mint x(n);
				Mint tail(0), factor(1);
				for (int j = cur.start; j < m; ++j) {
					tail += factor * table_.inverse_factorial[j];
					factor *= x - Mint(j);
				}
				Mint value = Arithmetic::eval(sum, x) + Arithmetic::eval(product, x) * tail;
				for (int j = groups_[i]; j < groups_[i + 1]; ++j) {
					auto destination = points_[j].id;
					result_[destination >> 1] = destination & 1 ? table_.power2[n] - value : value;
				}
			}
			return;
		}
		const auto& left = tree_[2 * node];
		const auto& right = tree_[2 * node + 1];
		F right_sum = sum;
		Arithmetic::add(right_sum, Arithmetic::multiply(product, left.sum));
		F right_product = Arithmetic::multiply(product, left.product);
		right_sum = Arithmetic::remainder(std::move(right_sum), right.modulus);
		right_product = Arithmetic::remainder(std::move(right_product), right.modulus);
		sum = Arithmetic::remainder(std::move(sum), left.modulus);
		product = Arithmetic::remainder(std::move(product), left.modulus);
		evaluate(2 * node, std::move(sum), std::move(product));
		evaluate(2 * node + 1, std::move(right_sum), std::move(right_product));
	}

  public:
	PolynomialEvaluator(const Table& table, const std::vector<std::pair<int, int>>& points,
			   const std::vector<std::uint32_t>& ids, std::vector<Mint>& result) : table_(table), result_(result) {
		assert(!points.empty() && points.size() == ids.size());
		points_.reserve(points.size());
		for (int i = 0; i < int(points.size()); ++i) points_.push_back({points[i].first, points[i].second, ids[i]});
		std::sort(points_.begin(), points_.end(), [](const Point& a, const Point& b) {
			return a.m != b.m ? a.m < b.m : a.n < b.n;
		});
		groups_.reserve(points_.size() + 1);
		for (int i = 0; i < int(points_.size()); ++i)
			if (!i || points_[i].m != points_[i - 1].m || points_[i].n != points_[i - 1].n) groups_.push_back(i);
		const int count = int(groups_.size());
		groups_.push_back(int(points_.size()));
		int size = 1;
		while (std::size_t(size) * block < std::size_t(count)) size <<= 1;
		tree_.resize(std::size_t(2) * size);
		build(1, 0, count, 0, false);
		evaluate(1, F{}, F{1});
	}
};
}

#if defined(__GNUC__) && !defined(__clang__) && (defined(__x86_64__) || defined(__i386__))
#pragma GCC pop_options
#endif


#line 1 "fps/fps_light.hpp"


#line 1 "components/fps_light_backend.hpp"



#line 5 "components/fps_light_backend.hpp"
#line 7 "components/fps_light_backend.hpp"
#include <cstddef>
#include <initializer_list>
#line 10 "components/fps_light_backend.hpp"
#include <optional>
#line 1 "components/polynomial_product_tree.hpp"



#line 9 "components/polynomial_product_tree.hpp"

namespace polynomial_detail {
template<class F, std::size_t Limit = 1U << 23>
struct ProductTree {
	static_assert(Limit >= 2);
	using T = typename F::value_type;
	std::size_t size = 1, count;
	std::vector<F> product;
	static void trim(F& f) { while (!f.empty() && f.back() == T(0)) f.pop_back(); }
	static F multiply(const F& a, const F& b) {
		if (a.empty() || b.empty()) return {};
		const auto n = a.size() + b.size() - 1;
		return n <= Limit ? F::multiply(a, b) : multiply_low(a, b, n);
	}
	static F multiply_low(const F& a, const F& b, std::size_t n) {
		F result(n);
		constexpr std::size_t block = Limit / 2;
		for (std::size_t i = 0; i < std::min(a.size(), n); i += block)
			for (std::size_t j = 0; j < std::min(b.size(), n - i); j += block) {
				F x(a.begin() + i, a.begin() + std::min(i + block, a.size()));
				F y(b.begin() + j, b.begin() + std::min(j + block, b.size()));
				F p = F::multiply(x, y);
				for (std::size_t k = 0; k < std::min(p.size(), n - i - j); ++k)
					result[i + j + k] += p[k];
			}
		return result;
	}

	explicit ProductTree(const std::vector<T>& xs) : count(xs.size()) {
		assert(count <= Limit);
		while (size < count) size <<= 1;
		product.resize(2 * size);
		for (std::size_t i = 0; i < size; ++i)
			product[size + i] = i < count ? F{-xs[i], T(1)} : F{T(1)};
		for (std::size_t i = size; --i;) {
			const auto& a = product[2 * i];
			const auto& b = product[2 * i + 1];
			product[i] = b.size() == 1 ? a : multiply(a, b);
		}
	}

	std::vector<T> evaluate(const F& f) const {
		std::vector<T> result(count);
		if (!count) return result;
		auto remainder = [](const F& a, const F& b) {
			return a.size() < b.size() ? a : a.divmod(b).second;
		};
		auto visit = [&](auto&& self, std::size_t node, const F& value) -> void {
			if (value.empty()) return;
			if (node >= size) {
				result[node - size] = value[0];
				return;
			}
			self(self, node * 2, remainder(value, product[node * 2]));
			if (product[node * 2 + 1].size() > 1)
				self(self, node * 2 + 1, remainder(value, product[node * 2 + 1]));
		};
		F value = f;
		trim(value);
		visit(visit, 1, remainder(value, product[1]));
		return result;
	}

	F interpolate(const std::vector<T>& ys) const {
		assert(ys.size() == count);
		if (!count) return {};
		F derivative = product[1].diff();
		trim(derivative);
		std::vector<T> denominator = evaluate(derivative), prefix(count + 1, T(1));
		for (std::size_t i = 0; i < count; ++i) {
			assert(denominator[i] != T(0));
			prefix[i + 1] = prefix[i] * denominator[i];
		}
		T inverse = prefix[count].inv();
		std::vector<F> value(2 * size);
		for (std::size_t i = count; i--;) {
			value[size + i] = F{ys[i] * inverse * prefix[i]};
			inverse *= denominator[i];
		}
		for (std::size_t i = size; --i;) {
			value[i] = F::multiply(value[2 * i], product[2 * i + 1])
				+ F::multiply(value[2 * i + 1], product[2 * i]);
			value[2 * i] = F();
			value[2 * i + 1] = F();
		}
		value[1].resize(count);
		return std::move(value[1]);
	}
};
}


#line 16 "components/fps_light_backend.hpp"

#if (defined(__x86_64__) || defined(__i386__)) && (defined(__GNUC__) || defined(__clang__))
#include <immintrin.h>
#endif

#if defined(__GNUC__) && !defined(__clang__) && (defined(__x86_64__) || defined(__i386__))
#pragma GCC push_options
#pragma GCC optimize("O3")
#endif

namespace fps_light_detail {
static_assert(sizeof(mint) == sizeof(unsigned) && std::is_trivially_copyable_v<mint>);
inline bool simd_available() {
#if (defined(__x86_64__) || defined(__i386__)) && (defined(__GNUC__) || defined(__clang__))
	return __builtin_cpu_supports("avx2");
#else
	return false;
#endif
}
template<bool Inverse>
void scalar_stage(mint *a, std::size_t n, std::size_t h, const mint *roots) {
	for (std::size_t start = 0; start < n; start += h * 2)
		for (std::size_t j = 0; j < h; ++j) {
			mint x = a[start + j], y = a[start + j + h];
			if constexpr (Inverse) y *= roots[j];
			a[start + j] = x + y;
			a[start + j + h] = x - y;
			if constexpr (!Inverse) a[start + j + h] *= roots[j];
		}
}

#if (defined(__x86_64__) || defined(__i386__)) && (defined(__GNUC__) || defined(__clang__))
__attribute__((target("avx2")))
inline __m256i product(__m256i x, __m256i y) {
	const auto p = _mm256_set1_epi32(mint::mod());
	auto even = _mm256_mul_epu32(x, y);
	auto odd = _mm256_mul_epu32(_mm256_srli_epi64(x, 32), _mm256_srli_epi64(y, 32));
	auto q = _mm256_mullo_epi32(_mm256_mullo_epi32(x, y), _mm256_set1_epi32(998244351));
	even = _mm256_srli_epi64(_mm256_add_epi64(even, _mm256_mul_epu32(q, p)), 32);
	odd = _mm256_add_epi64(odd, _mm256_mul_epu32(_mm256_srli_epi64(q, 32), p));
	return _mm256_blend_epi32(even, odd, 0xaa);
}

__attribute__((target("avx2")))
inline __m256i fixed_product(__m256i x, __m256i w, __m256i q) {
	auto even = _mm256_mul_epu32(x, q);
	auto odd = _mm256_mul_epu32(_mm256_srli_epi64(x, 32), _mm256_srli_epi64(q, 32));
	q = _mm256_blend_epi32(_mm256_srli_epi64(even, 32), odd, 0xaa);
	return _mm256_sub_epi32(_mm256_mullo_epi32(x, w), _mm256_mullo_epi32(q, _mm256_set1_epi32(mint::mod())));
}

__attribute__((target("avx2")))
inline void pointwise_avx2(mint *a, const mint *b, std::size_t n) {
	std::size_t i = 0;
	for (; i + 8 <= n; i += 8) {
		auto x = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(a + i));
		auto y = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(b + i));
		_mm256_storeu_si256(reinterpret_cast<__m256i *>(a + i), product(x, y));
	}
	for (; i < n; ++i) a[i] *= b[i];
}

__attribute__((target("avx2")))
inline void scale_avx2(mint *a, std::size_t n, mint factor) {
	std::size_t i = 0;
	unsigned value = factor.val();
	const auto f = _mm256_set1_epi32(value);
	const auto q = _mm256_set1_epi32((static_cast<unsigned long long>(value) << 32) / mint::mod());
	for (; i + 8 <= n; i += 8) {
		auto x = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(a + i));
		_mm256_storeu_si256(reinterpret_cast<__m256i *>(a + i), fixed_product(x, f, q));
	}
	for (; i < n; ++i) a[i] *= factor;
}

__attribute__((target("avx2")))
inline __m256i sum_vec(__m256i x, __m256i y) {
	auto z = _mm256_add_epi32(x, y);
	return _mm256_min_epu32(z, _mm256_sub_epi32(z, _mm256_set1_epi32(2 * mint::mod())));
}

__attribute__((target("avx2")))
inline __m256i diff_vec(__m256i x, __m256i y) {
	auto z = _mm256_sub_epi32(x, y);
	return _mm256_min_epu32(z, _mm256_add_epi32(z, _mm256_set1_epi32(2 * mint::mod())));
}

template<bool Inverse>
__attribute__((target("avx2")))
void leaf8(mint *a, std::size_t n, const mint *roots) {
	alignas(32) unsigned values[8], quotients[8];
	for (int i = 0; i < 8; ++i) {
		values[i] = roots[i].val();
		quotients[i] = (static_cast<unsigned long long>(values[i]) << 32) / mint::mod();
	}
	const auto w2 = _mm256_broadcastq_epi64(_mm_loadl_epi64(reinterpret_cast<const __m128i *>(values + 2)));
	const auto w4 = _mm256_broadcastsi128_si256(_mm_loadu_si128(reinterpret_cast<const __m128i *>(values + 4)));
	const auto q2 = _mm256_broadcastq_epi64(_mm_loadl_epi64(reinterpret_cast<const __m128i *>(quotients + 2)));
	const auto q4 = _mm256_broadcastsi128_si256(_mm_loadu_si128(reinterpret_cast<const __m128i *>(quotients + 4)));
	for (std::size_t i = 0; i < n; i += 8) {
		auto x = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(a + i));
		if constexpr (!Inverse) {
			auto y = _mm256_permute2x128_si256(x, x, 1);
			x = _mm256_blend_epi32(sum_vec(x, y), fixed_product(diff_vec(y, x), w4, q4), 0xf0);
			y = _mm256_shuffle_epi32(x, 0x4e);
			x = _mm256_blend_epi32(sum_vec(x, y), fixed_product(diff_vec(y, x), w2, q2), 0xcc);
			y = _mm256_shuffle_epi32(x, 0xb1);
			x = _mm256_blend_epi32(sum_vec(x, y), diff_vec(y, x), 0xaa);
		} else {
			auto y = _mm256_shuffle_epi32(x, 0xb1);
			x = _mm256_blend_epi32(sum_vec(x, y), diff_vec(y, x), 0xaa);
			x = _mm256_blend_epi32(x, fixed_product(x, w2, q2), 0xcc);
			y = _mm256_shuffle_epi32(x, 0x4e);
			x = _mm256_blend_epi32(sum_vec(x, y), diff_vec(y, x), 0xcc);
			x = _mm256_blend_epi32(x, fixed_product(x, w4, q4), 0xf0);
			y = _mm256_permute2x128_si256(x, x, 1);
			x = _mm256_blend_epi32(sum_vec(x, y), diff_vec(y, x), 0xf0);
		}
		_mm256_storeu_si256(reinterpret_cast<__m256i *>(a + i), x);
	}
}

__attribute__((target("avx2")))
inline void expand_roots(mint *out, const mint *previous, std::size_t n, mint step) {
	const auto factor = _mm256_set1_epi32(step.v);
	for (std::size_t i = 0; i < n; i += 8) {
		auto x = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(previous + i));
		auto y = product(x, factor);
		auto low = _mm256_unpacklo_epi32(x, y), high = _mm256_unpackhi_epi32(x, y);
		_mm256_storeu_si256(reinterpret_cast<__m256i *>(out + 2 * i), _mm256_permute2x128_si256(low, high, 0x20));
		_mm256_storeu_si256(reinterpret_cast<__m256i *>(out + 2 * i + 8), _mm256_permute2x128_si256(low, high, 0x31));
	}
}

template<bool Inverse>
__attribute__((target("avx2")))
void vector_stage(mint *a, std::size_t n, std::size_t h, const mint *roots) {
	const auto p = _mm256_set1_epi32(2 * mint::mod());
	for (std::size_t start = 0; start < n; start += h * 2)
		for (std::size_t j = 0; j < h; j += 8) {
			auto *first = reinterpret_cast<__m256i *>(a + start + j);
			auto *last = reinterpret_cast<__m256i *>(a + start + j + h);
			auto x = _mm256_loadu_si256(first), y = _mm256_loadu_si256(last);
			auto w = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(roots + j));
			if constexpr (Inverse) y = product(y, w);
			auto sum = _mm256_add_epi32(x, y), difference = _mm256_sub_epi32(x, y);
			sum = _mm256_min_epu32(sum, _mm256_sub_epi32(sum, p));
			difference = _mm256_min_epu32(difference, _mm256_add_epi32(difference, p));
			if constexpr (!Inverse) difference = product(difference, w);
			_mm256_storeu_si256(first, sum);
			_mm256_storeu_si256(last, difference);
		}
}
#endif

struct Roots {
	std::vector<mint> forward{0, 1}, inverse{0, 1};
	void prepare(std::size_t n) {
		std::size_t begin = forward.size();
		if (begin >= n) return;
		forward.resize(n), inverse.resize(n);
		for (std::size_t h = begin; h < n; h *= 2) {
			mint step = mint(3).pow((mint::mod() - 1) / (h * 2));
#if (defined(__x86_64__) || defined(__i386__)) && (defined(__GNUC__) || defined(__clang__))
			if (simd_available() && h >= 16) expand_roots(forward.data() + h, forward.data() + h / 2, h / 2, step);
			else
#endif
			for (std::size_t j = 0; j < h / 2; ++j) {
				forward[h + 2 * j] = forward[h / 2 + j];
				forward[h + 2 * j + 1] = forward[h / 2 + j] * step;
			}
			inverse[h] = 1;
			for (std::size_t j = 1; j < h; ++j) inverse[h + j] = -forward[2 * h - j];
		}
	}
};

inline void pointwise(std::vector<mint> &a, const std::vector<mint> &b, [[maybe_unused]] bool vectorized = simd_available()) {
	assert(a.size() == b.size());
#if (defined(__x86_64__) || defined(__i386__)) && (defined(__GNUC__) || defined(__clang__))
	if (vectorized) return pointwise_avx2(a.data(), b.data(), a.size());
#endif
	for (std::size_t i = 0; i < a.size(); ++i) a[i] *= b[i];
}

inline void scale(std::vector<mint> &a, mint factor, [[maybe_unused]] bool vectorized = simd_available()) {
#if (defined(__x86_64__) || defined(__i386__)) && (defined(__GNUC__) || defined(__clang__))
	if (vectorized) return scale_avx2(a.data(), a.size(), factor);
#endif
	for (auto &x : a) x *= factor;
}

template<bool Inverse>
void stage(mint *a, std::size_t n, std::size_t h, const mint *roots, [[maybe_unused]] bool vectorized) {
#if (defined(__x86_64__) || defined(__i386__)) && (defined(__GNUC__) || defined(__clang__))
	if (vectorized && h >= 8) return vector_stage<Inverse>(a, n, h, roots);
#endif
	scalar_stage<Inverse>(a, n, h, roots);
}

inline void transform(std::vector<mint> &a, bool inverse = false) {
	std::size_t n = a.size();
	assert(cp_library_cxx17::has_single_bit(n) && n <= (std::size_t(1) << 23));
	static Roots roots;
	roots.prepare(n);
	bool vectorized = false;
#if (defined(__x86_64__) || defined(__i386__)) && (defined(__GNUC__) || defined(__clang__))
	vectorized = __builtin_cpu_supports("avx2");
#endif
	if (inverse) {
		std::size_t h = 1;
#if (defined(__x86_64__) || defined(__i386__)) && (defined(__GNUC__) || defined(__clang__))
		if (vectorized && n >= 8) leaf8<true>(a.data(), n, roots.inverse.data()), h = 8;
#endif
		for (; h < n; h *= 2) stage<true>(a.data(), n, h, roots.inverse.data() + h, vectorized);
		scale(a, mint(n).inv());
	} else {
		std::size_t h = n / 2;
		for (; h >= 8; h /= 2) stage<false>(a.data(), n, h, roots.forward.data() + h, vectorized);
#if (defined(__x86_64__) || defined(__i386__)) && (defined(__GNUC__) || defined(__clang__))
		if (vectorized && n >= 8) return leaf8<false>(a.data(), n, roots.forward.data());
#endif
		for (; h; h /= 2) stage<false>(a.data(), n, h, roots.forward.data() + h, vectorized);
	}
}

inline std::vector<mint> multiply(const std::vector<mint> &a, const std::vector<mint> &b) {
	if (a.empty() || b.empty()) return {};
	[[maybe_unused]] constexpr std::size_t limit = std::size_t(1) << 23;
	assert(a.size() <= limit && b.size() <= limit && a.size() + b.size() - 1 <= limit);
	std::size_t length = a.size() + b.size() - 1;
	if (std::min(a.size(), b.size()) <= 32) {
		std::vector<mint> result(length);
		for (std::size_t i = 0; i < a.size(); ++i)
			for (std::size_t j = 0; j < b.size(); ++j) result[i + j] += a[i] * b[j];
		return result;
	}
	std::size_t n = cp_library_cxx17::bit_ceil(length);
	std::vector<mint> x = a;
	x.resize(n);
	transform(x);
	if (&a == &b) {
		pointwise(x, x);
	} else {
		std::vector<mint> y = b;
		y.resize(n);
		transform(y);
		pointwise(x, y);
	}
	transform(x, true);
	x.resize(length);
	return x;
}
}

#if defined(__GNUC__) && !defined(__clang__) && (defined(__x86_64__) || defined(__i386__))
#pragma GCC pop_options
#endif

#if defined(__GNUC__) && !defined(__clang__) && (defined(__x86_64__) || defined(__i386__))
#pragma GCC push_options
#pragma GCC optimize("O3")
#endif

template<class T = mint>
struct LightFormalPowerSeries : std::vector<T> {
	static_assert(T::mod() == 998244353);
	using base = std::vector<T>;
	using F = LightFormalPowerSeries;
	using base::base;
	LightFormalPowerSeries() = default;
	LightFormalPowerSeries(base a) : base(std::move(a)) {}
	F &operator=(base a) { base::operator=(std::move(a)); return *this; }
	F &operator=(std::initializer_list<T> a) { base::operator=(a); return *this; }
	static F multiply(const F &a, const F &b) {
		if constexpr (std::is_same_v<T, mint>) return fps_light_detail::multiply(a, b);
		else {
			auto x = a.native();
			return from_native(&a == &b ? Native::multiply(x, x) : Native::multiply(x, b.native()));
		}
	}
	F operator-() const { F r = *this; for (T &x : r) x = -x; return r; }
	F &operator+=(const F &g) {
		if (this->size() < g.size()) this->resize(g.size());
		for (std::size_t i = 0; i < g.size(); ++i) (*this)[i] += g[i];
		return *this;
	}
	F &operator-=(const F &g) {
		if (this->size() < g.size()) this->resize(g.size());
		for (std::size_t i = 0; i < g.size(); ++i) (*this)[i] -= g[i];
		return *this;
	}
	F &operator+=(T x) { if (this->empty()) this->resize(1); (*this)[0] += x; return *this; }
	F &operator-=(T x) { return *this += -x; }
	F &operator*=(const F &g) { return *this = multiply(*this, g); }
	F &operator/=(const F &g) { return *this = div_series(g); }
	F &operator%=(const F &g) { return *this = divmod(g).second; }
	F &operator*=(T x) { for (T &v : *this) v *= x; return *this; }
	F &operator/=(T x) { return *this *= x.inv(); }
	friend F operator+(F a, const F &b) { return a += b; }
	friend F operator-(F a, const F &b) { return a -= b; }
	friend F operator*(const F &a, const F &b) { return multiply(a, b); }
	friend F operator/(const F &a, const F &b) { return a.div_series(b); }
	friend F operator%(const F &a, const F &b) { return a.divmod(b).second; }
	friend F operator+(F a, T b) { return a += b; }
	friend F operator-(F a, T b) { return a -= b; }
	friend F operator*(F a, T b) { return a *= b; }
	friend F operator/(F a, T b) { return a /= b; }
	friend F operator+(T a, F b) { return b += a; }
	friend F operator-(T a, const F &b) { return -b + a; }
	friend F operator*(T a, F b) { return b *= a; }
	F &operator<<=(int d) {
		assert(d >= 0);
		const auto n = this->size();
		if (std::size_t(d) >= n) return *this = F(n);
		this->insert(this->begin(), d, T(0));
		this->resize(n);
		return *this;
	}
	F &operator>>=(int d) {
		assert(d >= 0);
		const auto n = this->size();
		this->erase(this->begin(), this->begin() + std::min(n, std::size_t(d)));
		this->resize(n);
		return *this;
	}
	friend F operator<<(F a, int d) { return a <<= d; }
	friend F operator>>(F a, int d) { return a >>= d; }
	F pre(int n) const {
		assert(n >= 0);
		return F(this->begin(), this->begin() + std::min(std::size_t(n), this->size()));
	}
	void shrink() { while (!this->empty() && this->back() == T(0)) this->pop_back(); }
	void trim() { shrink(); }
	T eval(T x) const {
		T result = 0;
		for (auto it = this->rbegin(); it != this->rend(); ++it) result = result * x + *it;
		return result;
	}
	F diff() const {
		F result(this->size());
		for (std::size_t i = 1; i < this->size(); ++i) result[i - 1] = (*this)[i] * T(i);
		return result;
	}
	F integral() const {
		assert(this->size() < T::mod());
		F result(this->size());
		const auto &inv = inverses(static_cast<int>(this->size()));
		for (std::size_t i = 1; i < this->size(); ++i) result[i] = (*this)[i - 1] * inv[i];
		return result;
	}
	void onemul(int d, T c) {
		assert(d >= 0);
		if (!d) { *this *= T(1) + c; return; }
		for (std::size_t i = this->size(); i > std::size_t(d); --i) (*this)[i - 1] += (*this)[i - 1 - d] * c;
	}
	void onediv(int d, T c) {
		assert(d >= 0);
		if (!d) { *this /= T(1) + c; return; }
		for (std::size_t i = d; i < this->size(); ++i) (*this)[i] -= (*this)[i - d] * c;
	}
	F inv(int deg = -1) const {
		const int n = precision(deg);
		if (!n) return {};
		assert(!this->empty() && (*this)[0] != T(0));
		if constexpr (!std::is_same_v<T, mint>) return from_native(native().inv(n));
		else {
			const int work = newton_precision(n), initial = std::min(work, 32);
			F result(initial);
			const T inverse = (*this)[0].inv();
			result[0] = inverse;
			for (int i = 1; i < initial; ++i) {
				T sum = 0;
				for (int j = 1; j <= i && std::size_t(j) < this->size(); ++j) sum += (*this)[j] * result[i - j];
				result[i] = -sum * inverse;
			}
			for (int k = initial; k < work; k *= 2) inverse_step(*this, result, std::min(k * 2, work));
			result.resize(n);
			for (int i = work; i < n; ++i) {
				T sum = 0;
				for (int j = 1; j <= i && std::size_t(j) < this->size(); ++j) sum += (*this)[j] * result[i - j];
				result[i] = -sum * inverse;
			}
			return result;
		}
	}
	F div_series(const F &g, int deg = -1) const {
		const int n = precision(deg);
		if (!n) return {};
		assert(!g.empty() && g[0] != T(0));
		if constexpr (!std::is_same_v<T, mint>) return from_native(native().div_series(g.native(), n));
		else {
			if (n <= 32) {
				F result(n);
				const T inverse = g[0].inv();
				for (int i = 0; i < n; ++i) {
					T value = std::size_t(i) < this->size() ? (*this)[i] : T(0);
					for (int j = 1; j <= i && std::size_t(j) < g.size(); ++j) value -= g[j] * result[i - j];
					result[i] = value * inverse;
				}
				return result;
			}
			const int work = newton_precision(n), k = cp_library_cxx17::bit_floor(unsigned(work - 1)), length = k * 2;
			F inverse = g.inv(k), result = pre(k);
			const T constant = inverse[0];
			inverse.resize(length), result.resize(length);
			fps_light_detail::transform(inverse);
			fps_light_detail::transform(result);
			fps_light_detail::pointwise(result, inverse);
			fps_light_detail::transform(result, true);
			std::fill(result.begin() + k, result.end(), T(0));
			F quotient = result, error = g.pre(work);
			error.resize(length);
			fps_light_detail::transform(quotient);
			fps_light_detail::transform(error);
			fps_light_detail::pointwise(error, quotient);
			fps_light_detail::transform(error, true);
			std::fill(error.begin(), error.begin() + k, T(0));
			for (int i = k; i < work; ++i) error[i] = (std::size_t(i) < this->size() ? (*this)[i] : T(0)) - error[i];
			std::fill(error.begin() + work, error.end(), T(0));
			fps_light_detail::transform(error);
			fps_light_detail::pointwise(error, inverse);
			fps_light_detail::transform(error, true);
			result.resize(n);
			std::copy(error.begin() + k, error.begin() + work, result.begin() + k);
			for (int i = work; i < n; ++i) {
				T value = std::size_t(i) < this->size() ? (*this)[i] : T(0);
				for (int j = 1; j <= i && std::size_t(j) < g.size(); ++j) value -= g[j] * result[i - j];
				result[i] = value * constant;
			}
			return result;
		}
	}
	F log(int deg = -1) const {
		const int n = precision(deg);
		if (!n) return {};
		assert(!this->empty() && (*this)[0] == T(1));
		if constexpr (!std::is_same_v<T, mint>) return from_native(native().log(n));
		else {
			F result = pre(n).diff().pre(n - 1).div_series(pre(n), n - 1);
			result.resize(n);
			return result.integral();
		}
	}
	F exp(int deg = -1) const {
		const int n = precision(deg);
		if (!n) return {};
		assert(this->empty() || (*this)[0] == T(0));
		if constexpr (!std::is_same_v<T, mint>) return from_native(native().exp(n));
		else {
			const int work = newton_precision(n), initial = std::min(work, 32);
			const auto &inv = inverses(n);
			F result(initial);
			result[0] = T(1);
			for (int i = 1; i < initial; ++i) {
				T sum = 0;
				for (int j = 1; j <= i && std::size_t(j) < this->size(); ++j) sum += T(j) * (*this)[j] * result[i - j];
				result[i] = sum * inv[i];
			}
			if (work == n && initial == n) return result;
			F reciprocal = result.inv(initial);
			for (int k = initial; k < work; k *= 2) {
				const int length = k * 2, m = std::min(length, work);
				if (reciprocal.size() < std::size_t(k)) inverse_step(result, reciprocal, k);
				F frequency = result, inverse = reciprocal, error(length);
				frequency.resize(length), inverse.resize(length);
				fps_light_detail::transform(frequency);
				fps_light_detail::transform(inverse);
				for (int i = 1; i < m && std::size_t(i) < this->size(); ++i) error[i - 1] = (*this)[i] * T(i);
				fps_light_detail::transform(error);
				fps_light_detail::pointwise(error, frequency);
				fps_light_detail::transform(error, true);
				std::fill(error.begin(), error.begin() + k - 1, T(0));
				std::fill(error.begin() + m - 1, error.end(), T(0));
				fps_light_detail::transform(error);
				fps_light_detail::pointwise(error, inverse);
				fps_light_detail::transform(error, true);
				for (int i = m - 1; i >= k; --i) error[i] = error[i - 1] * inv[i];
				std::fill(error.begin(), error.begin() + k, T(0));
				std::fill(error.begin() + m, error.end(), T(0));
				fps_light_detail::transform(error);
				fps_light_detail::pointwise(error, frequency);
				fps_light_detail::transform(error, true);
				result.resize(m);
				std::copy(error.begin() + k, error.begin() + m, result.begin() + k);
			}
			result.resize(n);
			for (int i = work; i < n; ++i) {
				T sum = 0;
				for (int j = 1; j <= i && std::size_t(j) < this->size(); ++j) sum += T(j) * (*this)[j] * result[i - j];
				result[i] = sum * inv[i];
			}
			return result;
		}
	}
	F sqrt(int deg = -1) const {
		const int n = precision(deg);
		if (!n) return {};
		if constexpr (!std::is_same_v<T, mint>) return from_native(native().sqrt(n));
		else {
			int first = 0, last = static_cast<int>(std::min(this->size(), std::size_t(n)));
			while (first < last && (*this)[first] == T(0)) ++first;
			if (first == last) return F(n);
			if (first & 1) return {};
			auto constant = scalar_sqrt((*this)[first]);
			if (!constant) return {};
			const int shift = first / 2, target = n - shift, work = newton_precision(target), initial = std::min(work, 32);
			F f(this->begin() + first, this->begin() + last), result(initial);
			const T half = T(2).inv(), factor = (T(2) * *constant).inv();
			result[0] = *constant;
			for (int i = 1; i < initial; ++i) {
				T value = std::size_t(i) < f.size() ? f[i] : T(0);
				for (int j = 1; j < i; ++j) value -= result[j] * result[i - j];
				result[i] = value * factor;
			}
			if (initial == target) {
				result.insert(result.begin(), shift, T(0));
				return result;
			}
			F reciprocal = result.inv(initial);
			for (int k = initial; k < work; k *= 2) {
				const int length = k * 2, m = std::min(length, work);
				F error;
				if (reciprocal.size() < std::size_t(k)) inverse_step(result, reciprocal, k, &error);
				if (error.empty()) { error = result; fps_light_detail::transform(error); }
				F inverse = reciprocal;
				fps_light_detail::pointwise(error, error);
				fps_light_detail::transform(error, true);
				error.resize(length), inverse.resize(length);
				for (int i = 0; i < m - k; ++i) {
					T low = std::size_t(i) < f.size() ? f[i] : T(0);
					T high = std::size_t(k + i) < f.size() ? f[k + i] : T(0);
					error[i] = (low + high - error[i]) * half;
				}
				std::fill(error.begin() + m - k, error.end(), T(0));
				fps_light_detail::transform(error);
				fps_light_detail::transform(inverse);
				fps_light_detail::pointwise(error, inverse);
				fps_light_detail::transform(error, true);
				result.resize(m);
				std::copy_n(error.begin(), m - k, result.begin() + k);
			}
			result.resize(target);
			for (int i = work; i < target; ++i) {
				T value = std::size_t(i) < f.size() ? f[i] : T(0);
				for (int j = 1; j < i; ++j) value -= result[j] * result[i - j];
				result[i] = value * factor;
			}
			result.insert(result.begin(), shift, T(0));
			return result;
		}
	}
	F pow(long long k) const {
		assert(k >= 0);
		const int n = precision(-1);
		if (!n) return {};
		if (!k) { F result(n); result[0] = 1; return result; }
		if (k == 1) return *this;
		int first = 0;
		while (first < n && (*this)[first] == T(0)) ++first;
		if (first == n || first > (n - 1) / k) return F(n);
		const int shift = static_cast<int>(first * k), len = n - shift;
		const T lead = (*this)[first];
		F f(this->begin() + first, this->end());
		f.resize(len);
		f /= lead;
		F result = (f.log(len) * T(k)).exp(len) * lead.pow(k);
		result.insert(result.begin(), shift, T(0));
		return result;
	}
	std::pair<F, F> divmod(const F &divisor) const {
		F a = *this, b = divisor;
		a.shrink(), b.shrink();
		assert(!b.empty());
		if (a.size() < b.size()) return {{}, std::move(a)};
		assert(a.size() <= (std::size_t(1) << 22));
		const int qn = static_cast<int>(a.size() - b.size() + 1), m = static_cast<int>(b.size());
		if (m <= 32 || std::size_t(m) * qn <= 2048) {
			F q(qn);
			const T inverse = b.back().inv();
			for (int i = qn - 1; i >= 0; --i) {
				T value = q[i] = a[i + m - 1] * inverse;
				for (int j = 0; j < m; ++j) a[i + j] -= value * b[j];
			}
			a.resize(m - 1);
			a.shrink(), q.shrink();
			return {std::move(q), std::move(a)};
		}
		F ra(a.rbegin(), a.rend()), rb(b.rbegin(), b.rend());
		F q = ra.div_series(rb, qn);
		std::reverse(q.begin(), q.end());
		F r = a - multiply(q, b);
		r.resize(m - 1);
		r.shrink(), q.shrink();
		return {std::move(q), std::move(r)};
	}

  private:
	static int newton_precision(int n) {
		const int prefix = cp_library_cxx17::bit_floor(unsigned(n));
		return prefix >= 4096 && n - prefix <= 4 ? prefix : n;
	}
	using Native = LightFormalPowerSeries<mint>;
	Native native() const {
		Native result(this->size());
		for (std::size_t i = 0; i < this->size(); ++i) result[i] = mint::raw((*this)[i].val());
		return result;
	}
	static F from_native(const Native &a) {
		F result(a.size());
		for (std::size_t i = 0; i < a.size(); ++i) result[i] = T::raw(a[i].val());
		return result;
	}
	static void inverse_step(const F &f, F &result, int n, F *frequency = nullptr) {
		const int k = static_cast<int>(result.size()), length = k * 2;
		assert(k > 0 && cp_library_cxx17::has_single_bit(unsigned(k)) && k < n && n <= length);
		F error = f.pre(n), inverse = result;
		error.resize(length), inverse.resize(length);
		fps_light_detail::transform(error);
		if (frequency) *frequency = error;
		fps_light_detail::transform(inverse);
		fps_light_detail::pointwise(error, inverse);
		fps_light_detail::transform(error, true);
		std::fill(error.begin(), error.begin() + k, T(0));
		fps_light_detail::transform(error);
		fps_light_detail::pointwise(error, inverse);
		fps_light_detail::transform(error, true);
		result.resize(n);
		for (int i = k; i < n; ++i) result[i] = -error[i];
	}
	int precision(int deg) const {
		assert(this->size() <= std::size_t(std::numeric_limits<int>::max()));
		int n = deg < 0 ? static_cast<int>(this->size()) : deg;
		assert(0 <= n && n <= (1 << 22));
		return n;
	}
	static const std::vector<T> &inverses(int n) {
		static std::vector<T> inv{T(0), T(1)};
		for (int i = static_cast<int>(inv.size()); i < n; ++i) inv.push_back(T(T::mod() - T::mod() / i) * inv[T::mod() % i]);
		return inv;
	}
	static std::optional<T> scalar_sqrt(T a) {
		if (a == T(0)) return T(0);
		if (a.pow((T::mod() - 1) / 2) != T(1)) return std::nullopt;
		constexpr int q = 119;
		T x = a.pow((q + 1) / 2), t = a.pow(q), c = T(3).pow(q);
		int m = 23;
		while (t != T(1)) {
			int i = 1;
			T next = t * t;
			while (i < m && next != T(1)) next *= next, ++i;
			assert(i < m);
			T b = c.pow(1LL << (m - i - 1));
			x *= b;
			c = b * b;
			t *= c;
			m = i;
		}
		return T::raw(std::min(x.val(), T::mod() - x.val()));
	}
};

using light_fps = LightFormalPowerSeries<>;
using LightFPS = light_fps;

#if defined(__GNUC__) && !defined(__clang__) && (defined(__x86_64__) || defined(__i386__))
#pragma GCC pop_options
#endif

namespace fps_light_detail {
template<class T>
using ProductTree = polynomial_detail::ProductTree<LightFormalPowerSeries<T>>;
}

namespace light_fps_algorithms {
template<class T>
LightFormalPowerSeries<T> taylor_shift(LightFormalPowerSeries<T> f, cp_library_cxx17::type_identity_t<T> c) {
	using F = LightFormalPowerSeries<T>;
	const std::size_t n = f.size();
	if (n <= 1 || c == T(0)) return f;
	assert(n < T::mod());
	F factorial(n, T(1)), inverse(n, T(1)), a(n), b(n);
	for (std::size_t i = 1; i < n; ++i) factorial[i] = factorial[i - 1] * T(i);
	inverse[n - 1] = factorial[n - 1].inv();
	for (std::size_t i = n - 1; i; --i) inverse[i - 1] = inverse[i] * T(i);
	T power = 1;
	for (std::size_t i = 0; i < n; ++i) {
		a[n - 1 - i] = f[i] * factorial[i];
		b[i] = power * inverse[i];
		power *= c;
	}
	a = F::multiply(a, b);
	for (std::size_t i = 0; i < n; ++i) f[i] = a[n - 1 - i] * inverse[i];
	return f;
}

template<class T>
T bostan_mori(LightFormalPowerSeries<T> p, LightFormalPowerSeries<T> q, long long k) {
	using F = LightFormalPowerSeries<T>;
	assert(k >= 0 && !q.empty() && q[0] != T(0));
	p.shrink();
	q.shrink();
	while (k && !p.empty() && q.size() > 1) {
		F opposite = q;
		for (std::size_t i = 1; i < opposite.size(); i += 2) opposite[i] = -opposite[i];
		F numerator = F::multiply(p, opposite), denominator = F::multiply(q, opposite);
		p.resize((numerator.size() + 1 - std::size_t(k & 1)) / 2);
		for (std::size_t i = 0; i < p.size(); ++i) p[i] = numerator[2 * i + std::size_t(k & 1)];
		q.resize((denominator.size() + 1) / 2);
		for (std::size_t i = 0; i < q.size(); ++i) q[i] = denominator[2 * i];
		p.shrink();
		q.shrink();
		k >>= 1;
	}
	return static_cast<unsigned long long>(k) < p.size() ? p[std::size_t(k)] / q[0] : T(0);
}

template<class T>
T linear_recurrence(const std::vector<T> &initial, const std::vector<T> &coefficients, long long k) {
	using F = LightFormalPowerSeries<T>;
	assert(k >= 0 && initial.size() == coefficients.size());
	const std::size_t n = initial.size();
	if (static_cast<unsigned long long>(k) < n) return initial[std::size_t(k)];
	if (!n) return T(0);
	F q(n + 1);
	q[0] = T(1);
	for (std::size_t i = 0; i < n; ++i) q[i + 1] = -coefficients[i];
	F p = F::multiply(F(initial.begin(), initial.end()), q).pre(static_cast<int>(n));
	return bostan_mori(std::move(p), std::move(q), k);
}

template<class T>
std::vector<T> multipoint_eval(const LightFormalPowerSeries<T> &f, const std::vector<T> &xs) {
	if (f.size() <= 32 || xs.size() <= 32) {
		std::vector<T> result;
		result.reserve(xs.size());
		for (T x : xs) result.push_back(f.eval(x));
		return result;
	}
	return fps_light_detail::ProductTree<T>(xs).evaluate(f);
}

template<class T>
LightFormalPowerSeries<T> interpolate(const std::vector<T> &xs, const std::vector<T> &ys) {
	assert(xs.size() == ys.size());
	return fps_light_detail::ProductTree<T>(xs).interpolate(ys);
}
}


#line 4 "fps/fps_light.hpp"

#line 7 "components/binomial_prefix_polynomial_light.hpp"

namespace light_binomial_prefix_detail {
template<class Mint> using PolynomialScalarArithmetic = binomial_prefix_detail::PolynomialScalarArithmetic<Mint>;
template<class Mint> struct PolynomialArithmetic : PolynomialScalarArithmetic<Mint> {};
template<> struct PolynomialArithmetic<mint> : binomial_prefix_detail::PolynomialSeriesArithmetic<mint, light_fps> {};

template<class Mint> class Polynomial : public binomial_prefix_detail::PolynomialEvaluator<Mint, PolynomialArithmetic<Mint>, Table<Mint>> {
	using Base = binomial_prefix_detail::PolynomialEvaluator<Mint, PolynomialArithmetic<Mint>, Table<Mint>>;

  public:
	Polynomial(const Table<Mint>& table, const std::vector<std::pair<int, int>>& points,
			   const std::vector<std::uint32_t>& ids, std::vector<Mint>& result) : Base(table, points, ids, result) {}
};
}


#line 7 "math/combinatorics/binomial_prefix_sum_light.hpp"

namespace light_combinatorics {
template<class Mint = mint> class BinomialPrefixSum {
	light_binomial_prefix_detail::Table<Mint> table_;
	int max_n_ = 0, block_ = 1;
	std::vector<std::size_t> offsets_;
	std::vector<Mint> data_;
	void check([[maybe_unused]] int n) const { assert(0 <= n && n <= max_n_); }

  public:
	explicit BinomialPrefixSum(int max_n = 0, int block_size = 0) { build(max_n, block_size); }
	void build(int max_n, int block_size = 0) {
		assert(max_n >= 0 && block_size >= 0);
		table_.build(max_n);
		max_n_ = max_n;
		block_ = block_size ? block_size : std::max(1, int(std::sqrt(double(max_n) + 1)));
		int blocks = ((max_n + 1) / 2) / block_;
		offsets_.resize(blocks + 1);
		std::size_t total = 0;
		for (int j = 1; j <= blocks; ++j) {
			offsets_[j] = total;
			total += max_n - 2 * (j * block_) + 2;
		}
		data_.resize(total);
		for (int j = 1; j <= blocks; ++j) {
			int m = j * block_, start = 2 * m - 1;
			Mint value = table_.factorial[m - 1] * table_.power2[start - 1];
			std::size_t offset = offsets_[j];
			data_[offset] = value;
			for (int n = start; n < max_n; ++n) {
				value = value + value - table_.factorial[n] * table_.inverse_factorial[n - m + 1];
				data_[++offset] = value;
			}
		}
	}
	int max_n() const { return max_n_; }
	int block_size() const { return block_; }
	std::size_t table_size() const { return data_.size(); }
	Mint query(int n, std::int64_t k) const {
		check(n);
		if (k <= 0) return Mint(0);
		if (k >= std::int64_t(n) + 1) return table_.power2[n];
		bool reflect = k > (n + 1) / 2;
		int m = reflect ? n + 1 - int(k) : int(k), center = (n + 1) / 2;
		Mint value(1);
		if (m != 1) {
			int j = m / block_, anchor = j * block_, distance = m - anchor;
			if (std::int64_t(anchor) + block_ <= center && block_ - distance < distance) ++j, anchor += block_, distance = anchor - m;
			if (center - m < distance) anchor = center, value = table_.center(n);
			else value = anchor ? data_[offsets_[j] + n - (2 * anchor - 1)] * table_.inverse_factorial[anchor - 1] : Mint(0);
			if (anchor < m) value += table_.range(n, anchor, m);
			else if (m < anchor) value -= table_.range(n, m, anchor);
		}
		return reflect ? table_.power2[n] - value : value;
	}
	Mint prod(int n, std::int64_t l, std::int64_t r) const {
		assert(l <= r);
		return query(n, r) - query(n, l);
	}
};

template<class Mint = mint, class K = int>
std::vector<Mint> binomial_prefix_sum(const std::vector<std::pair<int, K>>& queries) {
	static_assert(std::is_integral_v<K> && std::is_signed_v<K> && sizeof(K) <= 8);
	assert(queries.size() <= std::size_t(std::numeric_limits<int>::max()));
	if (queries.empty()) return {};
	int max_n = 0;
	for (auto [n, k] : queries) { (void)k; assert(n >= 0); max_n = std::max(max_n, n); }
	light_binomial_prefix_detail::Table<Mint> table(max_n);
	std::vector<Mint> result(queries.size());
	std::vector<std::pair<int, int>> points;
	std::vector<std::uint32_t> ids;
	points.reserve(queries.size()), ids.reserve(queries.size());
	for (int i = 0; i < int(queries.size()); ++i) {
		auto [n, k] = queries[i];
		if (k <= 0) continue;
		if (std::uint64_t(k) >= std::uint64_t(n) + 1) { result[i] = table.power2[n]; continue; }
		bool reflect = k > (n + 1) / 2;
		int m = reflect ? n + 1 - int(k) : int(k);
		if (m == 1 || m == (n + 1) / 2) {
			Mint value = m == 1 ? Mint(1) : table.center(n);
			result[i] = reflect ? table.power2[n] - value : value;
		} else points.emplace_back(m, n), ids.push_back((std::uint32_t(i) << 1) | reflect);
	}
	if (!points.empty()) light_binomial_prefix_detail::Polynomial<Mint>(table, points, ids, result);
	return result;
}

}



#line 1 "correct.cpp"
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <utility>
#include <vector>

int main() {
    int t;
    scanf("%d", &t);
    std::vector<std::pair<int, int>> queries(t);
    int max_n = 0;
    for (auto& [n, k] : queries) {
        scanf("%d%d", &n, &k);
        max_n = std::max(max_n, n);
    }
    int block = std::max(1, static_cast<int>(max_n / std::sqrt(t)));
    light_combinatorics::BinomialPrefixSum<> sum(max_n, block);
    for (auto [n, k] : queries) printf("%u\n", sum.query(n, k + 1).val());
}
