class Multiplexer {
private:
  uint8_t _digitalPins[4];
  uint8_t _analogPin;

public:
  Multiplexer(const uint8_t (&digitalPins)[4], uint8_t analogPin)
      : _analogPin(analogPin) {
    for (uint8_t i = 0; i < 4; ++i) {
      _digitalPins[i] = digitalPins[i];
    }
  }

  void Setup() {
    pinMode(_analogPin, INPUT);
    pinMode(_digitalPins[0], OUTPUT);
    pinMode(_digitalPins[1], OUTPUT);
    pinMode(_digitalPins[2], OUTPUT);
    pinMode(_digitalPins[3], OUTPUT);
  }

  void SetChannel(uint8_t channel) {
    for (uint8_t i = 0; i < 4; ++i) {
      bool val = ((channel >> i) & 1) == 1; // true => HIGH, false => LOW
      digitalWrite(_digitalPins[i], val);
    }
  }

  uint8_t Read() { return analogRead(_analogPin); }
};