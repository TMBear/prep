// 312. Burst Balloons - https://leetcode.com/problems/burst-balloons/
#include <iostream>
#include <vector>


class Solution {
  using VecType = std::vector<int>;
public:
  int maxCoins(const VecType& nums) {
    initCache(nums.size());

    return getCoins(nums, 0, nums.size() - 1);
  }

  
private:
  
  int getCoins(const VecType& nums, int left, int right) {
//    std::cout << left << "-" << right << std::endl;
    if (left > right)
      return 0;

    auto& cachedVal = m_cache[left][right];
    if (cachedVal != -1) {
//      std::cout << left << "-" << right << ": CacheHit " << cachedVal << std::endl;
      return cachedVal;
    }
 

    auto leftValue = getValue(nums, left - 1);
    auto rightValue = getValue(nums, right + 1);
    for (int lastPopped = left; lastPopped <= right; ++lastPopped) {
      int coins = getCoins(nums, left, lastPopped - 1) +
                  leftValue * getValue(nums, lastPopped) * rightValue + 
                  getCoins(nums, lastPopped + 1, right);

      cachedVal = std::max(cachedVal, coins);
    }

//    std::cout << left << "-" << right << ": " << cachedVal << std::endl;
    return cachedVal;
  }


  int getValue(const VecType& nums, int index) {
    if (index < 0)
      return 1;
    if (index >= (int)nums.size())
      return 1;

    return nums[index];
  }


  void initCache(std::size_t numsCount) {
    m_cache.clear();
    m_cache.reserve(numsCount);
    for (std::size_t i = 0; i < numsCount; ++i) {
      m_cache.emplace_back(numsCount, -1);
    }
  }



private:
  std::vector<std::vector<int>> m_cache;
};



static void test() {
  Solution s;
  std::cout << s.maxCoins({3, 1, 5, 8}) << std::endl;

  assert(s.maxCoins({3, 1, 5, 8}) == 167);
}


