#include "../common/BoardState.h"
#include "../common/globals.h"

BoardState boardState;
// Packed board data (16 bytes for 64 squares with 2 bits per square)
unsigned char packedData[16] = {0};

void printPackedData() {
  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      int squareIndex = row * 8 + col;
      int byteIndex = squareIndex / 4;
      int bitOffset = (squareIndex % 4) * 2;

      int value = (packedData[byteIndex] >> bitOffset) & 0b011;

      switch (value) {
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
      // PRINT(value);
    }
    PRINT('\n');
  }
}

int main() {
  boardState.ResetBoard();
  boardState.SetSquareState(0, 1, White);
  boardState.SetSquareState(1, 0, White);
  boardState.SetSquareState(5, 6, Black);
  boardState.DebugPrint();

  boardState.PackTransmitData(packedData);
  printPackedData();
}
