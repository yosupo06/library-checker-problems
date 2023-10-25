#ifndef FASTIO_H
#define FASTIO_H 1

#include <cassert>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <type_traits>
#include <utility>
#include <vector>

using namespace std;

namespace fastio {
static constexpr int SZ = 1 << 17;
char inbuf[SZ], outbuf[SZ];
int in_left = 0, in_right = 0, out_right = 0;

struct Pre {
  char num[40000];
  constexpr Pre() : num() {
    for (int i = 0; i < 10000; i++) {
      int n = i;
      for (int j = 3; j >= 0; j--) {
        num[i * 4 + j] = n % 10 + '0';
        n /= 10;
      }
    }
  }
} constexpr pre;

inline void load() {
  int len = in_right - in_left;
  memmove(inbuf, inbuf + in_left, len);
  in_right = len + fread(inbuf + len, 1, SZ - len, stdin);
  in_left = 0;
}

inline void flush() {
  fwrite(outbuf, 1, out_right, stdout);
  out_right = 0;
}

inline void rd(char &c) {
  if (in_left + 32 > in_right) load();
  c = inbuf[in_left++];
}
template <typename T>
inline void rd(T &x) {
  if (in_left + 32 > in_right) load();
  char c;
  do c = inbuf[in_left++];
  while (c < '-');
  [[maybe_unused]] bool minus = false;
  if constexpr (is_signed<T>::value == true) {
    if (c == '-') minus = true, c = inbuf[in_left++];
  }
  x = 0;
  while (c >= '0') {
    x = x * 10 + (c & 15);
    c = inbuf[in_left++];
  }
  if constexpr (is_signed<T>::value == true) {
    if (minus) x = -x;
  }
}
inline void rd() {}
template <typename Head, typename... Tail>
inline void rd(Head &head, Tail &...tail) {
  rd(head);
  rd(tail...);
}

inline void wt(char c) { outbuf[out_right++] = c; }
template <typename T>
inline void wt(T x) {
  if (out_right > SZ - 32) flush();
  if (!x) {
    outbuf[out_right++] = '0';
    return;
  }
  if constexpr (is_signed<T>::value == true) {
    if (x < 0) outbuf[out_right++] = '-', x = -x;
  }
  int i = 12;
  char buf[16];
  while (x >= 10000) {
    memcpy(buf + i, pre.num + (x % 10000) * 4, 4);
    x /= 10000;
    i -= 4;
  }
  if (x < 100) {
    if (x < 10) {
      outbuf[out_right] = '0' + x;
      ++out_right;
    } else {
      uint32_t q = (uint32_t(x) * 205) >> 11;
      uint32_t r = uint32_t(x) - q * 10;
      outbuf[out_right] = '0' + q;
      outbuf[out_right + 1] = '0' + r;
      out_right += 2;
    }
  } else {
    if (x < 1000) {
      memcpy(outbuf + out_right, pre.num + (x << 2) + 1, 3);
      out_right += 3;
    } else {
      memcpy(outbuf + out_right, pre.num + (x << 2), 4);
      out_right += 4;
    }
  }
  memcpy(outbuf + out_right, buf + i + 4, 12 - i);
  out_right += 12 - i;
}
inline void wt() {}
template <typename Head, typename... Tail>
inline void wt(Head &&head, Tail &&...tail) {
  wt(head);
  wt(forward<Tail>(tail)...);
}

template <typename... Args>
inline void wtn(Args &&...x) {
  wt(forward<Args>(x)...);
  wt('\n');
}

template <typename T>
inline void wtv(vector<T> &v) {
  static_assert(is_integral<T>::value == true);
  for (int i = 0; i < (int)v.size(); i++) {
    wt(v[i]);
    wt(" \n"[i == (int)v.size() - 1]);
  }
}

struct Dummy {
  Dummy() { atexit(flush); }
} dummy;

}  // namespace fastio
using fastio::rd;
using fastio::wt;
using fastio::wtn;
using fastio::wtv;

#endif