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

  void SetSquareState(unsigned int row, unsigned int col, SquareState state);

  SquareState GetSquareState(unsigned int row, unsigned int col);

  void ResetBoard();

  void DebugPrint();

  void PackTransmitData(unsigned char *packedData);
};