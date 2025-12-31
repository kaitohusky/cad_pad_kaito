#include <Keyboard.h>

const uint8_t numRows = 3;
const uint8_t numCols = 5;

const uint8_t rowPins[numRows] = {26, 27, 28};
const uint8_t colPins[numCols] = {29, 0, 1, 2, 4};

char keymap[numRows][numCols] = {
  {'a', 'b', 'c', 'd', 'e'},
  {'f', 'g', 'h', 'i', 'j'},
  {'k', 'l', 'm', 'n', 'o'}
};

bool keyState[numRows][numCols];

void setup() {
  for (uint8_t r = 0; r < numRows; r++) {
    pinMode(rowPins[r], OUTPUT);
    digitalWrite(rowPins[r], HIGH);
  }
  for (uint8_t c = 0; c < numCols; c++) {
    pinMode(colPins[c], INPUT_PULLUP);
  }
  Keyboard.begin();
}

void handleKey(uint8_t r, uint8_t c, bool pressed) {
  if (pressed && !keyState[r][c]) {
    keyState[r][c] = true;
    Keyboard.press(keymap[r][c]);
  } else if (!pressed && keyState[r][c]) {
    keyState[r][c] = false;
    Keyboard.release(keymap[r][c]);
  }
}

void loop() {
  for (uint8_t r = 0; r < numRows; r++) {
    digitalWrite(rowPins[r], LOW);
    delayMicroseconds(5);
    for (uint8_t c = 0; c < numCols; c++) {
      bool pressed = (digitalRead(colPins[c]) == LOW);
      handleKey(r, c, pressed);
    }
    digitalWrite(rowPins[r], HIGH);
  }
}
