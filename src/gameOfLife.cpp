// 289. Game of Life https://leetcode.com/problems/game-of-life/
#include <iostream>
#include <vector>
#include "utils.h"


class Board {
  using CellType = int;
  using RowType = std::vector<CellType>;
  using BoardType = std::vector<RowType>;
  static const int c_curOffset = 0;
  static const int c_nextOffset = 1;

  class CellRef {
  public:
    CellRef(BoardType& rawBoard, int row, int column)
      : m_rawBoard(rawBoard)
      , m_row(row)
      , m_column(column)
    {}

    operator bool() const {
      if (m_row < 0 || m_row >= (int)m_rawBoard.size())
        return 0;

      if (m_column < 0 || m_column >= (int)m_rawBoard.front().size())
        return 0;

      int cellValue = m_rawBoard[m_row][m_column];

      return (cellValue & (1 << c_curOffset));
    }

    void setNextStep(bool occupied) {
      if (m_row < 0 || m_row >= (int)m_rawBoard.size())
        return;

      if (m_column < 0 || m_column >= (int)m_rawBoard.front().size())
        return;

      auto& valRef = m_rawBoard[m_row][m_column];
      valRef = (valRef & ~(1UL << c_nextOffset)) | (occupied << c_nextOffset);
    }

  private:
    BoardType& m_rawBoard;
    int m_row;
    int m_column;
  };



  class RowRef {
  public:
    RowRef(BoardType& rawBoard, int row)
      : m_rawBoard(rawBoard)
      , m_row(row)
    {}

    const CellRef operator[](int column) const {
      return CellRef(m_rawBoard, m_row, column);
    }

    CellRef operator[](int column) {
      return CellRef(m_rawBoard, m_row, column);
    }

  private:
    BoardType& m_rawBoard;
    int m_row;
  };


public:
  Board(BoardType& rawBoard)
    : m_rawBoard(rawBoard)
  {}


  const RowRef operator[](int row) const {
    return RowRef(m_rawBoard, row);
  }

  RowRef operator[](int row) {
    return RowRef(m_rawBoard, row);
  }

  void applyNextStep() {
    for (auto& row : m_rawBoard) {
      for (auto& cell : row) {
        cell >>= 1; // Hack!
      }
    }
  }

private:
  BoardType& m_rawBoard;
};



static std::vector<std::pair<int, int>> s_neightbors = {
  std::make_pair(-1, 1),
  std::make_pair(0, 1),
  std::make_pair(1, 1),
  std::make_pair(1, 0),
  std::make_pair(1, -1),
  std::make_pair(0, -1),
  std::make_pair(-1, -1),
  std::make_pair(-1, 0)
};

class Solution {
public:

  void gameOfLife(std::vector<std::vector<int>>& board) {
    Board b(board);
    for (int r = 0; r < (int)board.size(); ++r) {
      for (int c = 0; c < (int)board.front().size(); ++c) {
        int neightbors = getNeightborCount(b, r, c);
        bool nextStep = false;
        if (neightbors == 3)
          nextStep = true;
        else if (neightbors == 2 && b[r][c])
          nextStep = true;

        b[r][c].setNextStep(nextStep);
      }
    }

    b.applyNextStep();
  }

private:

  int getNeightborCount(const Board& b, int row, int column) {
    int neightbors = 0;
    for (const auto& n: s_neightbors) {
      if (b[row + n.first][column + n.second])
        ++neightbors;
    }

    return neightbors;
  }
  
};


static void test() {
  Solution s;

  std::vector<std::vector<int>> data ={{0,1,0}, {0,0,1}, {1,1,1}, {0,0,0}};

  s.gameOfLife(data);
  std::cout << data << std::endl; 
}


