// https://leetcode.com/problems/count-primes/

#include <cstring>
#include <cstdlib>

struct bit_set {
  bit_set(int n) {
    c = (n >> 3) + 1;
    p = (char *)malloc(c);
    memset(p, 0, c);
  }
  ~bit_set() { free(p); }
  void set(int bit) {
    int pos = ((1 << 3) - 1) & bit;
    char *tmp = p + (bit >> 3);
    *tmp |= (1 << (8 - pos - 1));
  }
  void unset(int bit) {
    int pos = ((1 << 3) - 1) & bit;
    char *tmp = p + (bit >> 3);
    *tmp &= ~(1 << (8 - pos - 1));
  }
  bool test(int bit) {
    int pos = ((1 << 3) - 1) & bit;
    char *tmp = p + (bit >> 3);
    return ((1 << (8 - pos - 1)) & *tmp);
  }
  int count() {
    int res = 0;
    for (int i = 0; i < c; i++) {
      char v = p[i];
      if (v & 0b00000001)
        res++;
      if (v & 0b00000010)
        res++;
      if (v & 0b00000100)
        res++;
      if (v & 0b00001000)
        res++;
      if (v & 0b00010000)
        res++;
      if (v & 0b00100000)
        res++;
      if (v & 0b01000000)
        res++;
      if (v & 0b10000000)
        res++;
    }
    return res;
  }
  char *p;
  int c; // bytes count
};

class Solution {
public:
  int countPrimes(int n) {
    bit_set p(n);
    for (int i = 2; i < n; i++) {
      p.set(i);
    }
    if (n > 0)
      p.unset(0);
    if (n > 1)
      p.unset(1);
    for (int i = 2; i < n; i++) {
      if (p.test(i)) {
        // i is prime
        for (int j = 2; i * j < n; j++) {
          p.unset(i * j);
        }
      }
    }
    return p.count();
  }
};