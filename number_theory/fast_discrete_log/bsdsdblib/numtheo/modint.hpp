#pragma once

#include <numeric>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <vector>

#include "../basics.hpp"
#include "euler_sieve.hpp"
#include "pollard_rho.hpp"
#include "prod_funcs.hpp"

namespace numtheo_n {
	template<i32 P> class MIP;
	template<i32 P> class MI;
	// discrete log
	template<i32 P> std::optional<u32> dis_log(MIP<P>, MIP<P>);
	template<i32 P> std::vector<std::optional<u32>> dis_logs(MIP<P>, std::vector<MIP<P>>);
	template<i32 P> u32 fast_dis_ln(MIP<P>);
	template<i32 P> u32 ord(MIP<P>);
	template<i32 P> std::optional<u32> dis_log(MI<P>, MI<P>);
	template<i32 P> std::vector<std::optional<u32>> dis_logs(MI<P>, std::vector<MI<P>>);
	template<i32 P> std::optional<u32> ord(MI<P> x);
	template<class Derived, i32 P> class ModIntBase { // lt 0 for dynamic, le -1073741824 for internal use
		/* 
		occupied P shown below:
		-1073741824 : template<i32 P> MI<P> std::optional<u32> ord(MI<P>)
		*/
	protected:
		u32 val;
		inline static u32 dyn_mod = 0;
	public:
		static void set_mod(u32 p) {
			dyn_mod = p;
		}
		static u32 mod() {
			if (P < 0) {
				return dyn_mod;
			}
			return P;
		}
		ModIntBase() : val(0) {}
		ModIntBase(u32 v, bool need_mod = true) : val(need_mod ? v % mod() : v) {}
		ModIntBase(u64 v, bool need_mod = true) : val(
			static_cast<u32>(need_mod ? v % mod() : v)
		) {}
		ModIntBase(i32 v, bool need_mod = true) {
			if (need_mod) {
				v %= mod();
				if (v < 0) {
					v += mod();
				}
			}
			val = static_cast<u32>(v);
		}
		ModIntBase(i64 v, bool need_mod = true) {
			if (need_mod) {
				v %= mod();
				if (v < 0) {
					v += mod();
				}
			}
			val = static_cast<u32>(v);
		}
		void read_by_mod() {
			std::string s;
			std::cin >> s;
			val = 0;
			for (char c : s) {
				val = (static_cast<u64>(val) * 10 + (c ^ 48)) % mod();
			}
		}
		friend std::istream &operator>>(std::istream &in, ModIntBase<Derived, P> &x) {
			in >> x.val;
			return in;
		}
		u32 value() const {
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
			return static_cast<Derived>(static_cast<u64>(val) * x.val);
		}
		Derived &operator*=(Derived x) {
			val = static_cast<u32>(static_cast<u64>(val) * x.val % mod());
			return static_cast<Derived&>(*this);
		}
		friend bool operator==(Derived x, Derived y) {
			return x.val == y.val;
		}
		friend bool operator!=(Derived x, Derived y) {
			return x.val != y.val;
		}
	};
	template<i32 P> class MIP : public ModIntBase<MIP<P>, P> { // P prime
	private:
		using Base = ModIntBase<MIP<P>, P>;
		using Base::Base;
		inline static std::vector<MIP<P>> inv_v;
		// O(1) inv
		inline static u32 cbrtP_log2, cbrtP, cbrtP2;
		inline static bool O1inv_mode = false;
		inline static std::vector<std::pair<u32, u32>> farey_v, farey_prec, farey_succ;
		// fast discrete ln
		inline static std::vector<u32> lesqrt_ln;
	public:
		using Base::mod;
		using Base::set_mod;
		// discrete log
		friend std::optional<u32> dis_log<>(MIP<P>, MIP<P>);
		friend std::vector<std::optional<u32>> dis_logs<>(MIP<P>, std::vector<MIP<P>>);
		static void dis_ln_preproc(MIP<P>);
		friend u32 fast_dis_ln<>(MIP<P>);
		friend u32 ord<>(MIP<P>);
	};
	template<i32 P> class MI : public ModIntBase<MI<P>, P> {
	private:
		using Base = ModIntBase<MI<P>, P>;
		using Base::Base;
	public:
		using Base::mod;
		using Base::set_mod;
		// discrete log
		friend std::optional<u32> dis_log<>(MI<P>, MI<P>);
		friend std::vector<std::optional<u32>> dis_logs<>(MI<P>, std::vector<MI<P>>);
		friend std::optional<u32> ord<>(MI<P>);
	};
}

#include "modint_class/fast_dis_ln.hpp"
#include "modint_class/dis_log.hpp"