#define NUM_PINS 3

enum MuxMode {
  IN,
  OUT,
  NONE,
};

class Multiplexer {
private:
  uint8_t _digitalPins[NUM_PINS];
  uint8_t _analogPin;
  MuxMode _mode;

public:
  Multiplexer(const uint8_t (&digitalPins)[NUM_PINS], MuxMode mode = NONE, uint8_t analogPin = 0)
      : _analogPin(analogPin), _mode(mode) {
    for (uint8_t i = 0; i < NUM_PINS; ++i) {
      _digitalPins[i] = digitalPins[i];
    }
  }

  void Setup() {
    for (uint8_t i = 0; i < NUM_PINS; ++i) {
      pinMode(_digitalPins[i], OUTPUT);
    }

    if (_mode == IN) {
      pinMode(_analogPin, INPUT);
    } else if (_mode == OUT) {
      pinMode(_analogPin, OUTPUT);
    }
  }

  void SetChannel(uint8_t channel) {
    for (uint8_t i = 0; i < NUM_PINS; ++i) {
      bool val = ((channel >> i) & 1) == 1; // true => HIGH, false => LOW
      digitalWrite(_digitalPins[i], val);
    }
  }

  uint8_t Read() {
    if (_mode == IN) {
      return analogRead(_analogPin);
    }
    return 0;
  }
};