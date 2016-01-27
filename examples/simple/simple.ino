#include "EasyButton.h"

#define PIN_BUTTON 12

EasyButton eb = EasyButton(PIN_BUTTON);

void down(unsigned long now) {
  Serial.println("down");
}

void up(unsigned long now) {
  Serial.println("up");
}

void click(unsigned long now) {
  Serial.println("click");
}

void longPress(unsigned long now) {
  Serial.println("long-press");
}

void setup() {
  Serial.begin(115200);

  eb.attachDown(down);
  eb.attachUp(up);
  eb.attachClick(click);
  eb.attachLongPress(longPress);

  Serial.println("ready");
}

void loop() {
  eb.read();
}
