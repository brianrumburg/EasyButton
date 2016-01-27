
#ifndef EasyButton_h
#define EasyButton_h

#include "Arduino.h"

extern "C" {
  typedef void (*callback)(unsigned long);
}

class EasyButton
{
public:
  EasyButton(int pin);

  //call every loop
  void read(void);

  //callbacks
  void attachDown(callback f);
  void attachUp(callback f);
  void attachClick(callback f);
  void attachLongPress(callback f);

  int state; //(debounced)
  unsigned int debounceMs = 20;
  unsigned int longPressMs = 500;

private:
  int _pin;

  callback _downFunc;
  callback _upFunc;
  callback _clickFunc;
  callback _longPressFunc;

  unsigned long _pinState;

  unsigned long _lastRise;
  unsigned long _lastFall;
  unsigned long _lastDown;

  bool _longPressFuncCalled;
  bool _downFuncCalled;
  bool _upFuncCalled = true;
};

#endif
