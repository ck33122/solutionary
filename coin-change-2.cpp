// https://leetcode.com/problems/coin-change-2/submissions/

#include <vector>
using namespace std;

class Solution {
public:
  int change(int amount, vector<int>& coins) {
    sort(coins.begin(), coins.end());
    auto d = vector<int>(amount + 1, 0);
    d[0]   = 1;
    for (auto c : coins) {
      for (int i = 1; i <= amount; i++) {
        if (i - c >= 0) {
          d[i] += d[i - c];
        }
      }
    }
    return d[amount];
  }
};