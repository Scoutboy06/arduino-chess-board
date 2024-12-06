#include "BoardState.h"
#include "globals.h"

void BoardState::SetSquareState(unsigned int row, unsigned int col,
                                SquareState state) {
  if (row < 8 && col < 8) {
    board[row][col] = state;
  }
}

SquareState BoardState::GetSquareState(unsigned int row, unsigned int col) {
  return board[row][col];
}

void BoardState::ResetBoard() {
  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      switch (row) {
      case 0:
      case 1:
        board[row][col] = Black;
        break;
      case 6:
      case 7:
        board[row][col] = White;
        break;
      default:
        board[row][col] = None;
      }
    }
  }
}

void BoardState::DebugPrint() {
  PRINT("-------------------------\n");

  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      switch (board[row][col]) {
      case None:
        PRINT('_');
        break;
      case White:
        PRINT('W');
        break;
      case Black:
        PRINT('b');
        break;
      }
    }

    PRINT('\n');
  }

  PRINT("-------------------------\n");
}

void BoardState::PackTransmitData(unsigned char *packedData) {
  memset(packedData, 0, sizeof(packedData));

  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      SquareState val = board[row][col];
      int byteIndex = row * 2 + (col / 4);
      int bitOffset = (col % 4) * 2;

      packedData[byteIndex] |= (val << bitOffset);
    }
  }
}