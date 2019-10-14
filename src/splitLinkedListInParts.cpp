// Split Linked List in Parts: https://leetcode.com/problems/split-linked-list-in-parts/

#include <iostream>
#include <vector>

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
  std::vector<ListNode*> splitListToParts(ListNode* root, int k) {
    std::vector<ListNode*> parts;
    parts.reserve(k);

    int length = listLength(root);

    while (k != 0) {
      int nodesInCurPart = length / k;
      if (length % k)
        ++nodesInCurPart;

      parts.push_back(root);

      ListNode* tail = nullptr;
      for (int i = 0; i < nodesInCurPart; ++i) {
        tail = root;
        root = root->next;
      }

      if (tail)
        tail->next = nullptr;

      length -= nodesInCurPart;
      --k;
    }

    return parts;
  }


protected:
  int listLength(const ListNode* root) {
    int length = 0;
    while (root != nullptr) {
      root = root->next;
      ++length;
    }
    return length;   
  }
};

