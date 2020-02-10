// https://leetcode.com/problems/fair-candy-swap

#include <algorithm> // sort, lower_bound
#include <numeric>   // accumulate
#include <vector>    // vector
using namespace std;

class Solution {
public:
  vector<int> fairCandySwap(vector<int>& A, vector<int>& B) {
    vector<int> ans(2, INT_MIN);
    sort(B.begin(), B.end());
    int sa = accumulate(A.begin(), A.end(), 0);
    int sb = accumulate(B.begin(), B.end(), 0);
    for (int i = 0; i < A.size() && ans[0] == INT_MIN; i++) {
      if ((sb - sa) % 2 != 0) {
        continue;
      }
      int needed = (sb - sa + 2 * A[i]) / 2;
      if (needed < 1) {
        continue;
      }
      auto it = lower_bound(B.begin(), B.end(), needed);
      if (it != B.end() && *it == needed) {
        ans[0] = A[i];
        ans[1] = *it;
      }
    }
    return ans;
  }
};