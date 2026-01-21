#pragma once

#include "../basics.hpp"

namespace numtheo {
	constexpr i64 modint_inner = -2000000000;
	template<class Derived, i64 P, bool _64 = false> class ModIntBase {
		/*
		lt 0 for dynamic, lt -1e9 for internal use
		occupied P shown below:
		1	dis_log.hpp > ord
		2	excrt.hpp > excrt(T, T, T, T)
		3	pollard_rho.hpp > miller_rabin
		4	pollard_rho.hpp > pollard_rho
		5	prim_root.hpp > is_prim_root
		6	square_decomp_2.hpp > sqdecomp2_m4e1
		*/
	public:
		using val_t = std::conditional_t<_64, u64, u32>;
		using mul_t = i128::up_t<val_t>;
	protected:
		val_t val;
		inline static val_t dyn_mod = 0;
	public:
		static void set_mod(val_t p) {
			static_assert(P < 0);
			dyn_mod = p;
		}
		static val_t mod() {
			if (P < 0) {
				return dyn_mod;
			}
			return P;
		}
		ModIntBase() : val(0) {}
		template<class T> ModIntBase(T v, bool need_mod = true) : val(
			static_cast<val_t>(need_mod ? (v < 0 ? mod() - (-v) % mod() : v % mod()) : v)
		) {}
		void read_by_mod() {
			std::string s;
			std::cin >> s;
			val = 0;
			for (char c : s) {
				val = (static_cast<mul_t>(val) * 10 + (c ^ 48)) % mod();
			}
		}
		friend std::istream &operator>>(std::istream &in, Derived &x) {
			in >> x.val;
			return in;
		}
		val_t value() const {
			return val;
		}
		Derived operator+(Derived x) const {
			Derived ret;
			ret.val = val + x.val;
			if (ret.val >= mod()) {
				ret.val -= mod();
			}
			return ret;
		}
		Derived &operator+=(Derived x) {
			val += x.val;
			if (val >= mod()) {
				val -= mod();
			}
			return static_cast<Derived&>(*this);
		}
		Derived operator-() const {
			Derived ret;
			ret.val = mod() - val;
			return ret;
		}
		Derived operator-(Derived x) const {
			Derived ret;
			ret.val = val + mod() - x.val;
			if (ret.val >= mod()) {
				ret.val -= mod();
			}
			return ret;
		}
		Derived &operator-=(Derived x) {
			val += mod() - x.val;
			if (val >= mod()) {
				val -= mod();
			}
			return static_cast<Derived&>(*this);
		}
		Derived operator*(Derived x) const {
			return static_cast<Derived>(static_cast<mul_t>(val) * x.val);
		}
		Derived &operator*=(Derived x) {
			val = static_cast<val_t>(static_cast<mul_t>(val) * x.val % mod());
			return static_cast<Derived&>(*this);
		}
		friend bool operator==(Derived x, Derived y) {
			return x.val == y.val;
		}
		friend bool operator!=(Derived x, Derived y) {
			return x.val != y.val;
		}
	};
	template<i64 P, bool _64> class ModIntPr : public ModIntBase<ModIntPr<P, _64>, P, _64> { // P prime
	private:
		using Base = ModIntBase<ModIntPr<P, _64>, P, _64>;
		using Base::Base;
	public:
		using typename Base::val_t;
		using typename Base::mul_t;
		using Base::mod;
		using Base::set_mod;
	};
	template<i64 P, bool _64> class ModInt : public ModIntBase<ModInt<P, _64>, P, _64> {
	private:
		using Base = ModIntBase<ModInt<P, _64>, P, _64>;
		using Base::Base;
	public:
		using typename Base::val_t;
		using typename Base::mul_t;
		using Base::mod;
		using Base::set_mod;
	};
	template<i64 P> using ModIntPr32 = ModIntPr<P, false>;
	template<i64 P> using ModIntPr64 = ModIntPr<P, true>;
	template<i64 P> using ModInt32 = ModInt<P, false>;
	template<i64 P> using ModInt64 = ModInt<P, true>;
}
