// https://qandori.github.io/cp-library/math/combinatorics/binomial_prefix_sum_incremental_light.hpp.html
#line 1 "math/combinatorics/binomial_prefix_sum_incremental_light.hpp"



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


#line 6 "math/combinatorics/binomial_prefix_sum_incremental_light.hpp"
#include <memory>

namespace light_combinatorics {
template<class Mint = mint> class IncrementalBinomialPrefixSum {
	using Table = light_binomial_prefix_detail::Table<Mint>;
	std::shared_ptr<const Table> table_;
	int n_ = 0, k_ = 0;
	Mint value_ = Mint(0);
	Mint halve(Mint value) const {
		return value * table_->half;
	}

  public:
	explicit IncrementalBinomialPrefixSum(int max_n = 0) : table_(std::make_shared<Table>(max_n)) {}
	void build(int max_n) {
		table_ = std::make_shared<Table>(max_n);
		n_ = k_ = 0;
		value_ = Mint(0);
	}
	int max_n() const { return int(table_->factorial.size()) - 1; }
	Mint binom(int n, int k) const {
		if (n < 0 || k < 0 || k > n) return Mint(0);
		assert(n <= max_n());
		return table_->binom(n, k);
	}
	[[gnu::always_inline]] Mint query(int n, std::int64_t k) {
		assert(0 <= n && n <= max_n());
		int m = int(std::clamp(k, std::int64_t(0), std::int64_t(n) + 1));
		if (m <= 1 || m == n + 1) {
			n_ = n, k_ = m;
			return value_ = m == 0 ? Mint(0) : m == 1 ? Mint(1) : table_->power2[n];
		}
		const Table& table = *table_;
		int row = n_, column = k_;
		Mint value = value_;
		if (column == m) {
			while (row < n) value = value + value - table.binom(row++, column - 1);
			while (row > n) value = halve(value + table.binom(--row, column - 1));
		} else {
			if (!column) row = n;
			while (row < n && column < m) value = value + value + table.binom(row++, column++);
			while (row > n && column > m) value = halve(value - table.binom(--row, --column));
			while (row < n) value = value + value - table.binom(row++, column - 1);
			if (column < m) value += column + 1 == m ? table.binom(row, column) : table.range(row, column, m);
			else if (column > m) value -= m + 1 == column ? table.binom(row, m) : table.range(row, m, column);
			while (row > n) value = halve(value + table.binom(--row, m - 1));
		}
		n_ = n, k_ = m;
		return value_ = value;
	}
};

}



#line 1 "mo.cpp"
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <vector>

struct Query {
    int n, k, id;
    bool complement;
};

int main() {
    int t;
    scanf("%d", &t);
    std::vector<Query> queries(t);
    int max_n = 0;
    for (int i = 0; i < t; ++i) {
        int n, k;
        scanf("%d%d", &n, &k);
        bool complement = k < n && k > (n - 1) / 2;
        queries[i] = {n, complement ? n - k - 1 : k, i, complement};
        max_n = std::max(max_n, n);
    }
    std::vector<mint> power2(max_n + 1, mint(1)), answer(t);
    for (int n = 1; n <= max_n; ++n) power2[n] = power2[n - 1] + power2[n - 1];
    queries.erase(std::remove_if(queries.begin(), queries.end(), [&](const Query& q) {
        if (q.k != q.n) return false;
        answer[q.id] = power2[q.n];
        return true;
    }), queries.end());

    int block = std::max(1, static_cast<int>(max_n / std::sqrt(t)));
    std::sort(queries.begin(), queries.end(), [block](const Query& a, const Query& b) {
        int x = a.n / block, y = b.n / block;
        if (x != y) return x < y;
        if (a.k != b.k) return (x & 1) ? a.k > b.k : a.k < b.k;
        return a.id < b.id;
    });

    light_combinatorics::IncrementalBinomialPrefixSum<> sum(max_n);
    for (const auto& q : queries) {
        mint value = sum.query(q.n, q.k + 1);
        answer[q.id] = q.complement ? power2[q.n] - value : value;
    }
    for (mint value : answer) printf("%u\n", value.val());
}
