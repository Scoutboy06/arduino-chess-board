#define ARDUINO

#include "common/BoardState.h"
#include "common/globals.h"

constexpr int readPin = A0;
constexpr int mPins[4] = {2, 3, 4, 5};
constexpr int minThreshold = 450;
constexpr int maxThreshold = 600;

BoardState boardState;
uint8_t packedData[16] = {0};

void setup() {
  Serial.begin(9600);

  pinMode(readPin, INPUT);

  for (int i = 0; i < 4; i++) {
    pinMode(mPins[i], OUTPUT);
  }
}

void loop() {
  for (uint8_t row = 0; row < 8; row++) {
    for (uint8_t col = 0; col < 8; col++) {
      int readValue = readSquare(row, col);

      SquareState state;
      if (readValue < minThreshold) {
        state = SquareState::Black;
      } else if (readValue > maxThreshold) {
        state = SquareState::White;
      } else {
        state = SquareState::None;
      }

      boardState.SetSquareState(row, col, state);
    }
  }

  boardState.PackTransmitData(packedData);
}

int readSquare(uint8_t row, uint8_t col) {}

int readMux(int channel) {
  for (int i = 0; i < 4; i++) {
    bool val = ((channel >> i) & 1) == 1;
    digitalWrite(mPins[i], val);
  }

  return analogRead(readPin);
}
