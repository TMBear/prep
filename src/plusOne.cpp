// https://leetcode.com/submissions/detail/266370357/

#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:
  std::vector<int> plusOne(std::vector<int>& digits) {
    std::vector<int> result;
    result.reserve(digits.size() + 1);

    digits.back() += 1;
    int rem = 0;
    for (auto it = digits.crbegin(); it != digits.crend(); ++it) {
      int res = *it + rem;
      result.push_back(res % 10);
      rem = res / 10;
    }

    if (rem)
      result.push_back(rem);

    std::reverse(result.begin(), result.end());
    
    return result;
  }
};


