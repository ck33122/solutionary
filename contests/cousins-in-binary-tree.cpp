// https://leetcode.com/problems/cousins-in-binary-tree

#include <algorithm>
#include <array>
#include <queue>
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
  struct F {
    TreeNode* node;
    TreeNode* parent;
    int       level;
  };
  bool isCousins(TreeNode* root, int x, int y) {
    auto needed = array<int, 2>{x, y};
    auto result = array<F, 2>{};
    for (int i = 0; i < needed.size(); i++) {
      auto     val = needed[i];
      queue<F> q;
      q.push({root, nullptr, 0});
      while (!q.empty()) {
        auto f = q.front();
        if (f.node->val == val) {
          result[i] = f;
          break;
        }
        if (f.node->left) {
          q.push({f.node->left, f.node, f.level + 1});
        }
        if (f.node->right) {
          q.push({f.node->right, f.node, f.level + 1});
        }
        q.pop();
      }
    }
    return result[0].level == result[1].level &&
           result[0].parent != result[1].parent;
  }
};