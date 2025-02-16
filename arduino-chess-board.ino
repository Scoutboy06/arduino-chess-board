#define ARDUINO

#include "./Multiplexer.h"
#include "common/BoardState.h"
#include "common/globals.h"

constexpr int upperThresh = 500;
constexpr int lowerThresh = 400;

Multiplexer colMux({A2, A1, A0});
Multiplexer rowMux({A3, A5, 4});
// Multiplexer sigMux({2, 3, 4}, IN, A7);

BoardState boardState;
uint8_t packedData[16] = {0};

void setup() {
  Serial.begin(9600);

  rowMux.Setup();
  colMux.Setup();

  pinMode(A7, INPUT);
}

void loop() {
  for (int8_t row = 7; row >= 0; --row) {
    for (int8_t col = 0; col < 8; ++col) {
      SquareState s = ReadSquare(row, col);
      boardState.SetSquareState(7 - row, col, s);
    }
    // PRINT('\n');
  }
  // PRINT('\n');

  boardState.PackTransmitData(packedData);
  // boardState.DebugPrint();
  Serial.write(packedData, sizeof(packedData)); // Send all 16 bytes
  Serial.write('\r\n');                         // Add a newline delimiter

  delay(1000);
}

SquareState ReadSquare(uint8_t rowChannel, uint8_t colChannel) {
  rowMux.SetChannel(rowChannel);
  colMux.SetChannel(colChannel);

  int val = analogRead(A7);
  // PRINT(val);
  // PRINT(' ');

  if (val < 430)
    return SquareState::Black;
  else if (val > 550)
    return SquareState::White;
  return SquareState::None;
}