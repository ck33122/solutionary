// https://leetcode.com/problems/coin-change/submissions/

#include <climits>
#include <vector>
using namespace std;

class Solution {
public:
  int coinChange(vector<int>& coins, int amount) {
    auto d = vector<int>(amount + 1, INT_MAX);
    d[0]   = 0;
    for (int i = 1; i <= amount; i++) {
      for (auto x : coins) {
        if (i - x >= 0 && d[i - x] != INT_MAX) {
          d[i] = min(d[i], d[i - x] + 1);
        }
      }
    }
    if (d[amount] == INT_MAX) {
      return -1;
    } else {
      return d[amount];
    }
  }
};