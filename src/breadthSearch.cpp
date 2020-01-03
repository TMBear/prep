// https://www.hackerrank.com/challenges/castle-on-the-grid/problem
//
#include <iostream>
#include <vector>
#include <queue>
#include "utils.h"

struct Position {
  int x;
  int y;
};


bool operator==(const Position& p1, const Position& p2) {
  return p1.x == p2.x && p1.y == p2.y;
}


struct Movement {
  int dx;
  int dy;
};


using MovesGrid = std::vector<std::vector<int>>;


Position move(const Position& pos, const Movement& mov) {
  Position result = pos;
  result.x += mov.dx;
  result.y += mov.dy;

  return result;
};


MovesGrid createGrid(int size) {
  MovesGrid grid;
  grid.resize(size);
  for (auto& row : grid)
    row.resize(size, -1);

  return grid;
}

bool insideGrid(int size, const Position& pos) {
  return pos.x >= 0 && pos.y >= 0 &&
    pos.x < size && pos.y < size;
}


const std::vector<Movement> c_possibleSteps = {
  { 0,  1},
  {-1,  0},
  { 0, -1},
  { 1,  0}
};




std::vector<Position> getPossibleSteps(const std::vector<std::string>& grid, const Position& start, const Movement& mv) {
  std::vector<Position> result;

  Position curPos = start;

  while (insideGrid(grid.size(), curPos)) {
    if (grid[curPos.x][curPos.y] == 'X')
      break;

    result.push_back(curPos);
    curPos = move(curPos, mv);
  }

  return result;
}


std::vector<Position> getPossibleSteps(const std::vector<std::string>& grid, const Position& start) {
  std::vector<Position> result;
  for (const auto& mv : c_possibleSteps) {
    const auto& stepResults = getPossibleSteps(grid, start, mv);
    std::copy(stepResults.begin(), stepResults.end(), std::back_inserter(result));
  }

  return result;
}




int minimumMoves(std::vector<std::string>& grid, const Position& start, const Position& goal) {
  int gridSize = (int)grid.size();
  if (gridSize == 0)
    return 0;

  MovesGrid moves = createGrid(gridSize);
  std::queue<std::pair<Position, int>> steps;

  steps.emplace(start, 0);

  while (!steps.empty()) {
    auto curPos = steps.front().first;
    int curSteps = steps.front().second;
    steps.pop();

//    std::cout << "(" << curPos.x << ", " << curPos.y << ")-" << curSteps << std::endl;

    // Hit wall
    if (grid[curPos.x][curPos.y] == 'X')
      continue;

    if (curPos == goal)
      return curSteps;

    // Already visited.
    if (moves[curPos.x][curPos.y] >= 0)
      continue;

//    std::cout << moves << std::endl;

    moves[curPos.x][curPos.y] = curSteps;

    const auto possibleSteps = getPossibleSteps(grid, curPos);
    for (const auto& step : possibleSteps) {
      steps.emplace(step, curSteps + 1);
    }
  }
  
  return -1;  // impossible - we couldn't find goal.
}



void breadthSearch() {
  {
    std::vector<std::string> grid = {
      "...",
      ".X.",
      "..."
    };

    const Position start = {0, 0};
    const Position end = {1, 2};

    std::cout << minimumMoves(grid, start, end) << std::endl;
  }
  {
    std::vector<std::string> grid = {
      ".X.",
      ".X.",
      "..."
    };

    const Position start = {0, 0};
    const Position end = {0, 2};


    std::cout << minimumMoves(grid, start, end) << std::endl;
  }
}

