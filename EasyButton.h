
#ifndef EasyButton_h
#define EasyButton_h

#include "Arduino.h"

extern "C" {
  typedef void (*ebCb)(unsigned long);
}

class EasyButton
{
public:
  EasyButton(int pin);

  //call every loop
  void read(void);

  //callbacks
  void attachDown(ebCb f);
  void attachUp(ebCb f);
  void attachClick(ebCb f);
  void attachLongPress(ebCb f);

  int state; //(debounced)
  unsigned int debounceMs = 20;
  unsigned int longPressMs = 500;

private:
  int _pin;

  ebCb _downFunc;
  ebCb _upFunc;
  ebCb _clickFunc;
  ebCb _longPressFunc;

  unsigned long _pinState;

  unsigned long _lastRise;
  unsigned long _lastFall;
  unsigned long _lastDown;

  bool _longPressFuncCalled;
  bool _downFuncCalled;
  bool _upFuncCalled = true;
};

#endif
