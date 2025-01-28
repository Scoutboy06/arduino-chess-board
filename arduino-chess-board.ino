#define ARDUINO

#include "./Multiplexer.h"
#include "common/BoardState.h"
#include "common/globals.h"

constexpr int upperThresh = 600;
constexpr int lowerThresh = 450;

constexpr uint8_t rowPins[] = {2, 3, 4, 5};
constexpr uint8_t rowReadPin = A0;
Multiplexer rowMux(rowPins, rowReadPin);

constexpr uint8_t colPins[] = {6, 7, 8, 9};
constexpr uint8_t colReadPin = A1;
Multiplexer colMux(colPins, colReadPin);

BoardState boardState;
uint8_t packedData[16] = {0};

void setup() {
  Serial.begin(9600);

  rowMux.Setup();
  colMux.Setup();
}

void loop() {
  for (uint8_t row = 0; row < 8; row++) {
    for (uint8_t col = 0; col < 8; col++) {
      SquareState s = ReadSquare(row, col);
      boardState.SetSquareState(row, col, s);
    }
  }

  boardState.PackTransmitData(packedData);
}

SquareState ReadSquare(uint8_t rowChannel, uint8_t colChannel) {
  rowMux.SetChannel(rowChannel);
  colMux.SetChannel(colChannel);

  uint8_t rowVal = rowMux.Read();
  uint8_t colVal = colMux.Read();

  if (rowVal > upperThresh && colVal > upperThresh)
    return SquareState::White;
  else if (rowVal < lowerThresh && colVal < lowerThresh)
    return SquareState::Black;
  return SquareState::None;
}