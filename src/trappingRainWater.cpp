// Trapping Rain Water : https://leetcode.com/problems/trapping-rain-water/
#include <iostream>
#include <vector>
#include <assert.h>

struct Bucket {
  int height;
  int width;
  int curCapacity;
};


class Solution {
public:
  int trap(const std::vector<int>& height);
protected:
  void pushReduce(int h);
protected:
  std::vector<Bucket> m_buckets;
};


int Solution::trap(const std::vector<int>& height) {
  m_buckets = {};

  for (int h : height)
    pushReduce(h);

  int totalCapacity = 0;
  for (const auto& b : m_buckets)
    totalCapacity += b.curCapacity;

  return totalCapacity;
}


void Solution::pushReduce(int h) {

  Bucket newBucket = {h, 1, 0};
  int maxLevelOnLeft = m_buckets.empty() ? 0 : m_buckets.front().height;
  int maxFillLevel = std::min(h, maxLevelOnLeft);

  while (!m_buckets.empty() && m_buckets.back().height <= h) {
    const auto& oldBucket = m_buckets.back();
    newBucket.curCapacity += oldBucket.curCapacity;
    newBucket.curCapacity += oldBucket.width * (maxFillLevel - oldBucket.height);
    newBucket.width += oldBucket.width;

    m_buckets.pop_back();
  }

  m_buckets.push_back(newBucket);

}



static void test() {
  Solution s;
  assert(s.trap({0,1,0,2,1,0,1,3,2,1,2,1}) == 6);
  assert(s.trap({}) == 0);
  assert(s.trap({0}) == 0);
  assert(s.trap({1}) == 0);
  assert(s.trap({0,1,1,0}) == 0);
  assert(s.trap({0,1,0}) == 0);
  assert(s.trap({0,1,0,1}) == 1);
  assert(s.trap({0,1,0,2}) == 1);
}



