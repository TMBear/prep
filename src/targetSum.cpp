// 494. Target Sum - https://leetcode.com/problems/target-sum/
#include <iostream>
#include <vector>
#include "utils.h"


class Solution {
  using Data = std::vector<int>;
public:
  int findTargetSumWays(const Data& nums, int S) {
    initData(nums);

    return countWays(0, -S);
  }

private:
  int countWays(int index, int value) {
    if (index >= (int)m_nums.size()) {
      return value == 0 ? 1 : 0;
    }
    if (std::abs(value) > m_remainSum[index]) {
      return 0;
    }

    int waysMinus = countWays(index + 1, value - m_nums[index]);
    int waysPlus = countWays(index + 1, value + m_nums[index]);

    return waysMinus + waysPlus;

  }


  void initData(const Data& nums) {
    m_nums = nums;
    std::sort(m_nums.begin(), m_nums.end());

    m_remainSum.clear();
    m_remainSum.reserve(nums.size() + 1);
    m_remainSum.push_back(0);

    for (int i : nums)
      m_remainSum.push_back(i + m_remainSum.back());


    std::reverse(m_remainSum.begin(), m_remainSum.end());
    m_remainSum.pop_back();
    std::reverse(m_nums.begin(), m_nums.end());
  }

private:
  std::vector<int> m_nums;
  std::vector<int> m_remainSum;
};


static void test() {
  Solution s;
  std::cout << s.findTargetSumWays({1, 1, 1, 1, 1}, 3) << std::endl;

  assert(s.findTargetSumWays({1, 1, 1, 1, 1}, 3) == 5);
}


