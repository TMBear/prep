// Valid Square: https://leetcode.com/problems/valid-square/
#include <iostream>
#include <tgmath.h>
#include <vector>
using namespace std;

struct Point {
  int x;
  int y;
};

bool operator==(const Point& pt1, const Point& pt2) {
  return pt1.x == pt2.x &&
         pt1.y == pt2.y;
}

struct AngleComparer {
  AngleComparer(double pivotX, double pivotY)
    : m_pivotX(pivotX)
    , m_pivotY(pivotY)
    {}
  
  bool operator()(const Point& pt1, const Point& pt2) {
    return atan2(pt1.y - m_pivotY, pt1.x - m_pivotX) < atan2(pt2.y - m_pivotY, pt2.x - m_pivotX);
  }
  
  const double m_pivotX;
  const double m_pivotY;
};

class Solution {
  
  long long lineLenSq(const Point& pt1, const Point& pt2) {
    long long dx = pt1.x - pt2.x;
    long long dy = pt1.y - pt2.y;
    
    return dx*dx + dy*dy;
  }

public:
    bool validSquare(vector<int>& p1, vector<int>& p2, vector<int>& p3, vector<int>& p4) {
        std::vector<Point> points = {
          {p1[0], p1[1]},
          {p2[0], p2[1]},
          {p3[0], p3[1]},
          {p4[0], p4[1]}
        };
      
      double pivotX = ((double)(p1[0] + p2[0] + p3[0] + p4[0])) / 4.0;
      double pivotY = ((double)(p1[1] + p2[1] + p3[1] + p4[1])) / 4.0;
      
      AngleComparer ac(pivotX, pivotY);
      std::sort(points.begin(), points.end(), ac);
      if (std::unique(points.begin(), points.end()) != points.end())
        return false;
 
//      for (const auto& pt : points) {
//        std::cout << "(" << pt.x << ", " << pt.y << ")" << std::endl;
//      }
      
      auto l1 = lineLenSq(points[0], points[1]);
      auto l2 = lineLenSq(points[1], points[2]);
      auto l3 = lineLenSq(points[2], points[3]);
      auto l4 = lineLenSq(points[3], points[0]);

//      std::cout << l1 << " " << l2 << " " << l3 << " " << l4 << std::endl;
      
      if (l1 != l2 || l1 != l3 || l1 != l4)
        return false;
      
      auto d1 = lineLenSq(points[0], points[2]);
      auto d2 = lineLenSq(points[1], points[3]);

      return d1 == d2;
    }
};


static void test() {
  {
    std::vector<int> p1 = {0, 0};
    std::vector<int> p2 = {1, 1};
    std::vector<int> p3 = {1, 0};
    std::vector<int> p4 = {0, 1};

    Solution s;
    std::cout << s.validSquare(p1, p2, p3, p4) << "/true" << std::endl;
  }
  {
    std::vector<int> p1 = {1, 1};
    std::vector<int> p2 = {5, 3};
    std::vector<int> p3 = {3, 5};
    std::vector<int> p4 = {7, 7};

    Solution s;
    std::cout << s.validSquare(p1, p2, p3, p4) << "/false" << std::endl;
  }
  {
    std::vector<int> p1 = {0, 0};
    std::vector<int> p2 = {5, 0};
    std::vector<int> p3 = {5, 4};
    std::vector<int> p4 = {0, 4};

    Solution s;
    std::cout << s.validSquare(p1, p2, p3, p4) << "/false" << std::endl;
  }
  {
    std::vector<int> p1 = {0, 0};
    std::vector<int> p2 = {0, 0};
    std::vector<int> p3 = {0, 0};
    std::vector<int> p4 = {0, 0};

    Solution s;
    std::cout << s.validSquare(p1, p2, p3, p4) << "/false" << std::endl;
  }
}

