// https://leetcode.com/problems/combination-sum-iv/submissions/

#include <vector>
using namespace std;

class Solution {
public:
  int combinationSum4(vector<int>& nums, int target) {
    auto d = vector<unsigned int>(target + 1, 0);
    d[0]   = 1;
    for (int i = 1; i <= target; i++) {
      for (auto x : nums) {
        if (i - x >= 0) {
          // overflows! -> used unsigned int
          d[i] += d[i - x];
        }
      }
    }
    return d[target];
  }
};
