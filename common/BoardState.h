#include "./globals.h"

enum SquareState {
  None = 0,
  White = 1,
  Black = 2,
};

class BoardState {
private:
  // board is viewed from white's perspective
  // board[row][col]
  // board[0][0] = a8
  // board[0][7] = a1
  // board[7][0] = h1
  // board[7][7] = h8
  SquareState board[8][8];

public:
  BoardState() {
    for (int row = 0; row < 8; row++) {
      for (int col = 0; col < 8; col++) {
        board[row][col] = None;
      }
    }
  }

  void SetSquareState(unsigned int row, unsigned int col, SquareState state) {
    if (row < 8 && col < 8) {
      board[row][col] = state;
    }
  }

  SquareState GetSquareState(unsigned int row, unsigned int col) {
    return board[row][col];
  }

  void ResetBoard() {
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

  void DebugPrint() {
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

  void PackTransmitData(unsigned char *packedData) {
    memset(packedData, 0, 16);

    for (int row = 0; row < 8; row++) {
      for (int col = 0; col < 8; col++) {
        SquareState val = board[7 - row][col];
        int byteIndex = row * 2 + (col / 4);
        int bitOffset = (col % 4) * 2;

        packedData[byteIndex] |= (val << bitOffset);
      }
    }
  }
};