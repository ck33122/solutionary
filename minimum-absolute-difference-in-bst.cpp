// https://leetcode.com/problems/minimum-absolute-difference-in-bst
#include <algorithm>
#include <functional>
#include <limits>

using namespace std;

struct TreeNode {
  int       val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x)
    : val(x)
    , left(nullptr)
    , right(nullptr) {}
};

class Solution {
public:
  int getMinimumDifference(TreeNode* root) {
    int                       prev = -1, diff = numeric_limits<int>::max();
    function<void(TreeNode*)> visit;
    visit = [&](TreeNode* c) {
      if (c->left) {
        visit(c->left);
      }
      if (prev != -1) {
        diff = min(diff, c->val - prev);
      }
      prev = c->val;
      if (c->right) {
        visit(c->right);
      }
    };
    visit(root);
    return diff;
  }
};