#include "board.hpp"

// you might need additional includes
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

/**************************************************************************/
/* your function definitions                                              */
/**************************************************************************/

void InitBoard(Board& b) {
  // below was minimal to get tests to actually compile and given test case to
  // fail
  for (int i = 0; i < Board::kBoardWidth; i++) {
    for (int j = 0; j < Board::kBoardHeight; j++) {
      b.board[j][i] = DiskType::kEmpty;
    }
  }
  // b.board[0][0] = DiskType::kEmpty;
}
void DropDiskToBoard(Board& b, DiskType disk, int col) {
  if (col > Board::kBoardWidth || col < 0) {
    throw std::runtime_error("Col out of bounds");
  }
  if (b.board[Board::kBoardHeight - 1][col] != DiskType::kEmpty) {
    throw std::runtime_error("Error column full");
  }

  for (int i = 0; i < Board::kBoardHeight; i++) {
    if (b.board[i][col] == DiskType::kEmpty) {
      b.board[i][col] = disk;
      return;
    }
  }
}

bool HorizontalCheck(Board& b, DiskType disk) {
  for (int i = 0; i < Board::kBoardHeight; i++) {   // row
    for (int j = 0; j < Board::kBoardWidth; j++) {  // col
      if (b.board[i][j] == disk) {
        if (j + 3 < Board::kBoardWidth) {
          if (b.board[i][j + 1] == disk) {
            if (b.board[i][j + 2] == disk) {
              if (b.board[i][j + 3] == disk) {
                return true;
              }
            }
          }
        }
      }
    }
  }
  return false;
}

bool VerticalCheck(Board& b, DiskType disk) {
  for (int i = 0; i < Board::kBoardHeight; i++) {   // row
    for (int j = 0; j < Board::kBoardWidth; j++) {  // col
      if (b.board[i][j] == disk && i + 3 < Board::kBoardHeight) {
        if (b.board[i + 1][j] == disk && b.board[i + 2][j] == disk &&
            b.board[i + 3][j] == disk) {
          return true;
        }
      }
    }
  }
  return false;
}
bool RightDiagCheck(Board& b, DiskType disk) {
  for (int i = 0; i < Board::kBoardHeight; i++) {   // row
    for (int j = 0; j < Board::kBoardWidth; j++) {  // col
      if (b.board[i][j] == disk && i + 3 < Board::kBoardHeight &&
          j + 3 < Board::kBoardWidth) {
        if (b.board[i + 1][j + 1] == disk && b.board[i + 2][j + 2] == disk &&
            b.board[i + 3][j + 3] == disk) {
          return true;
        }
      }
    }
  }
  return false;
}
bool LeftDiagCheck(Board& b, DiskType disk) {
  for (int i = 0; i < Board::kBoardHeight; i++) {   // row
    for (int j = 0; j < Board::kBoardWidth; j++) {  // col
      if (b.board[i][j] == disk && i + 3 < Board::kBoardHeight && j - 3 >= 0) {
        if (b.board[i + 1][j - 1] == disk && b.board[i + 2][j - 2] == disk &&
            b.board[i + 3][j - 3] == disk) {
          return true;
        }
      }
    }
  }
  return false;
}

bool SearchForWinner(Board& b, DiskType disk, WinningDirection to_check) {
  if (to_check == WinningDirection::kHorizontal) {
    return HorizontalCheck(b, disk);
  }
  if (to_check == WinningDirection::kVertical) {
    return VerticalCheck(b, disk);
  }
  if (to_check == WinningDirection::kRightDiag) {
    return RightDiagCheck(b, disk);
  }
  if (to_check == WinningDirection::kLeftDiag) {
    return LeftDiagCheck(b, disk);
  }
  return false;
}

bool CheckForWinner(Board& b, DiskType disk) {
  if (SearchForWinner(b, disk, WinningDirection::kHorizontal)) {
    return true;
  }
  if (SearchForWinner(b, disk, WinningDirection::kVertical)) {
    return true;
  }
  if (SearchForWinner(b, disk, WinningDirection::kRightDiag)) {
    return true;
  }
  if (SearchForWinner(b, disk, WinningDirection::kLeftDiag)) {
    return true;
  }
  return false;
}

bool BoardLocationInBounds(int row, int col) {
  if (col >= Board::kBoardWidth || row >= Board::kBoardHeight) {
    return false;
  }
  if (row < 0 || col < 0) {
    return false;
  }
  return true;
}

/**************************************************************************/
/* provided to you                                                        */
/**************************************************************************/
std::string BoardToStr(const Board& b) {
  constexpr int kTotalWidth = Board::kBoardWidth * 11 - Board::kBoardHeight - 1;
  std::stringstream ss;
  ss << std::endl;
  for (int row = Board::kBoardHeight; row > 0; --row) {
    ss << " |";
    for (int col = 0; col < Board::kBoardWidth; ++col) {
      std::string value_here;
      value_here.push_back(static_cast<char>(b.board[row - 1][col]));
      ss << ' ' << CenterStr(value_here, Board::kBoardWidth + 1) << '|';
    }
    ss << std::endl;
    ss << " |" << std::setw(kTotalWidth) << std::setfill('-') << '|'
       << std::endl;
  }
  ss << " |";
  for (int col = 0; col < Board::kBoardWidth; ++col) {
    ss << ' ' << CenterStr(std::to_string(col), Board::kBoardWidth + 1) << '|';
  }
  return ss.str();
}

std::string CenterStr(const std::string& str, int col_width) {
  // quick and easy (but error-prone) implementation
  auto padl = (col_width - str.length()) / 2;
  auto padr = (col_width - str.length()) - padl;
  std::string strf = std::string(padl, ' ') + str + std::string(padr, ' ');
  return strf;
}