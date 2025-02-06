#define ARDUINO

#include "./Multiplexer.h"
#include "common/BoardState.h"
#include "common/globals.h"

constexpr int upperThresh = 500;
constexpr int lowerThresh = 400;

Multiplexer vccMux({ A2, A1, A0 });
Multiplexer gndMux({ 8, 7, 6 });
Multiplexer sigMux({ 2, 3, 4 }, IN, A7);

BoardState boardState;
uint8_t packedData[16] = {0};

void setup() {
  Serial.begin(9600);

  gndMux.Setup();
  sigMux.Setup();
  vccMux.Setup();
}

void loop() {
  for (int8_t row = 7; row >= 0; --row) {
    for (int8_t col = 0; col < 8; ++col) {
      SquareState s = ReadSquare(row, col);
      // boardState.SetSquareState(7 - row, col, s);
      delay(500);
    }
    PRINT('\n');
  }
  PRINT('\n');

  // boardState.PackTransmitData(packedData);
  // boardState.DebugPrint();
  delay(5000);
}

SquareState ReadSquare(uint8_t rowChannel, uint8_t colChannel) {
  gndMux.SetChannel(rowChannel);
  delay(2);
  sigMux.SetChannel(rowChannel);
  delay(2);
  vccMux.SetChannel(colChannel);
  delay(2);

  uint8_t val = sigMux.Read();
  PRINT(val);
  PRINT(' ');

  if (val < 70)
    return SquareState::White;
  else if (val < 150)
    return SquareState::Black;
  return SquareState::None;
}