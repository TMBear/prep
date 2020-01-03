// Largest plus sign - https://leetcode.com/problems/largest-plus-sign/

#include <iostream>
#include <vector>
#include "utils.h"


typedef std::vector<int> IVec;

void pgm_cw( std::vector<IVec> &p )
{
    // Need to allocate an array to store the transform
    std::vector<IVec> temp(p[0].size(), IVec(p.size()));

    std::size_t count = 0;        // count variable
    std::size_t count2 = 0;      // 2nd count variable

    for( count = 0; count < p.size(); count++ )
    {
        for( count2 = 0; count2 < p[0].size(); count2++ )
        {
            // Clockwise rotation
            temp[count2][temp[0].size()-count-1] = p[count][count2];
            // Counter-clockwise rotation
            //temp[temp.size()-count2-1][count] = p[count][count2];
        }
    }

    p = temp;       // set p equal to temp
}



using Matrix = std::vector<std::vector<int>>;


class Solution {

public:
  
  int orderOfLargestPlusSign(int N, const std::vector<std::vector<int>>& mines) {
    Matrix m;
    m.reserve(N);
    for (int i = 0; i < N; ++i) {
      m.emplace_back(N, 1);
    }

    for (const auto& mine : mines) {
      int x = mine[0];
      int y = mine[1];
      m[x][y] = 0;
    }

    swipe(m, false);
//    std::cout << m << std::endl;
    pgm_cw(m);
    swipe(m, true);
//    std::cout << m << std::endl;
    pgm_cw(m);
    swipe(m, true);
//    std::cout << m << std::endl;
    pgm_cw(m);
    swipe(m, true);
//    std::cout << m << std::endl;

    int result = 0;
    for (const auto& row: m) {
      for (const int val : row)
        result = std::max(result, val);
    }

    return result;

  }
  
private:
  void swipe(Matrix& m, bool reduce) {
    for (auto& row : m) {
      int prev = 0;
      for (auto& val : row) {
        if (val == 0) {
          prev = 0;
          continue;
        }
        ++prev;
        int newVal = prev;
        if (reduce)
          newVal = std::min(newVal, val);
        
        val = newVal;
      }
    }
    
  }
};

static void test() {
  Solution s;
  assert(s.orderOfLargestPlusSign(5, {{4, 2}}) == 2);
  assert(s.orderOfLargestPlusSign(2, {}) == 1);
  assert(s.orderOfLargestPlusSign(1, {{0, 0}}) == 0);
}



