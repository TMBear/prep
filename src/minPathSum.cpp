// Minimum path sum - https://leetcode.com/problems/minimum-path-sum/
#include <iostream>
#include <queue>
#include "utils.h"

struct Position {
  int x;
  int y;
};

struct Cell {
  Position pos;
  int distance;
};

std::ostream& operator<<(std::ostream& out, const Cell& c) {
  std::cout << c.distance << ":(" << c.pos.x << ", " << c.pos.y << ")";
  return out;
}

bool operator<(const Cell& c1, const Cell c2) {
  return c1.distance > c2.distance;
}

std::vector<Position> g_steps = {
  {1, 0},
 // {-1, 0},
  {0, 1}
//  {0, -1}
};

class Solution {
  using Matrix = std::vector<std::vector<int>>;

public:
  int minPathSum(const Matrix& grid) {
    std::priority_queue<Cell> queue;
    Matrix distances;
    distances.reserve(grid.size());
    for (std::size_t i = 0; i < grid.size(); ++i) {
      distances.emplace_back(grid[i].size(), std::numeric_limits<int>::max());
    }
    
    distances[0][0] = grid[0][0];
    queue.push({{0, 0}, grid[0][0]});

    while (!queue.empty()) {
      const Cell c = queue.top();
      queue.pop();

/*
      auto qtmp = queue;
      while (!qtmp.empty()) {
        std::cout << qtmp.top() << "  ";
        qtmp.pop();
      }
      std::cout << std::endl;
      std::cout << "(" << c.pos.x << ", " << c.pos.y << ")" << std::endl;
      std::cout << distances << std::endl << std::endl;
      std::cin.get();
*/
      const auto relaxedPositions = relax(grid, distances, c.pos);
      for (const auto& pos : relaxedPositions) {
        queue.push({pos, distances[pos.x][pos.y]});

      }
    }

    return distances.back().back();
  }

private:
  std::vector<Position> relax(const Matrix& grid, Matrix& distances, const Position& cur) {
    std::vector<Position> relaxed;

    for (const auto& step : g_steps) {
      const Position p{cur.x + step.x, cur.y + step.y};

      // Check if valid.
      if (p.x < 0 || p.y < 0 || p.x >= (int)grid.size() || p.y >= (int)grid[p.x].size())
        continue;

      auto newDistance = distances[cur.x][cur.y] + grid[p.x][p.y];
      if (newDistance >= distances[p.x][p.y])
        continue;

      distances[p.x][p.y] = newDistance;
      relaxed.push_back(p);
    }

    return relaxed;
  }
};


static void test() {
  Solution s;
  std::cout << s.minPathSum({
      {5,4,2,9,6,0,3,5,1,4,9,8,4,9,7,5,1},
      {3,4,9,2,9,9,0,9,7,9,4,7,8,4,4,5,8},
      {6,1,8,9,8,0,3,7,0,9,8,7,4,9,2,0,1},
      {4,0,0,5,1,7,4,7,6,4,1,0,1,0,6,2,8},
      {7,2,0,2,9,3,4,7,0,8,9,5,9,0,1,1,0},
      {8,2,9,4,9,7,9,3,7,0,3,6,5,3,5,9,6},
      {8,9,9,2,6,1,2,5,8,3,7,0,4,9,8,8,8},
      {5,8,5,4,1,5,6,6,3,3,1,8,3,9,6,4,8},
      {0,2,2,3,0,2,6,7,2,3,7,3,1,5,8,1,3},
      {4,4,0,2,0,3,8,4,1,3,3,0,7,4,2,9,8},
      {5,9,0,4,7,5,7,6,0,8,3,0,0,6,6,6,8},
      {0,7,1,8,3,5,1,8,7,0,2,9,2,2,7,1,5},
      {1,0,0,0,6,2,0,0,2,2,8,0,9,7,0,8,0},
      {1,1,7,2,9,6,5,4,8,7,8,5,0,3,8,1,5},
      {8,9,7,8,1,1,3,0,1,2,9,4,0,1,5,3,1},
      {9,2,7,4,8,7,3,9,2,4,2,2,7,8,2,6,7},
      {3,8,1,6,0,4,8,9,8,0,2,5,3,5,5,7,5},
      {1,8,2,5,7,7,1,9,9,8,9,2,4,9,5,4,0},
      {3,4,4,1,5,3,3,8,8,6,3,5,3,8,7,1,3}}) << std::endl;

  assert(s.minPathSum({{1,3,1}, {1,5,1}, {4,2,1}}) == 7);
}



