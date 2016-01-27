#include "EasyButton.h"

EasyButton::EasyButton(int pin)
{
  pinMode(pin, INPUT_PULLUP);
  _pin = pin;

  int newPinState = digitalRead(_pin);

  _pinState = newPinState;
  state = newPinState;
}

void EasyButton::attachDown(callback f)
{
  _downFunc = f;
}

void EasyButton::attachUp(callback f)
{
  _upFunc = f;
}

void EasyButton::attachClick(callback f)
{
  _clickFunc = f;
}

void EasyButton::attachLongPress(callback f)
{
  _longPressFunc = f;
}

void EasyButton::read(void)
{
  int newPinState = digitalRead(_pin);
  unsigned long now = micros();
  unsigned long debounceUs = debounceMs * 1000;
  unsigned long longPressUs = longPressMs * 1000;

  if(_pinState != newPinState) { //edge
    if(!newPinState) { //falling
      _lastFall = now;
    }
    else { //rising
      _lastRise = now;
    }
  }
  else { //non-edge
    if(!_pinState) { //low
      unsigned long lowUs = now - _lastFall;

      if(lowUs >= debounceUs && !_downFuncCalled) {
        state = LOW;

        if(_downFunc != NULL) { _downFunc(now); }
        _lastDown = now;
        _downFuncCalled = true;
        _upFuncCalled = false;
      }

      unsigned long downUs = now - _lastDown;

      if(_downFuncCalled && downUs >= longPressUs - debounceUs && !_longPressFuncCalled){
        if(_longPressFunc != NULL)  { _longPressFunc(now); }
        _longPressFuncCalled = true;
      }
    }
    else { //high
      unsigned long highUs = now - _lastRise;

      if(highUs >= debounceUs && !_upFuncCalled) {
        state = HIGH;

        if(_upFunc != NULL) { _upFunc(now); }
        _upFuncCalled = true;
        _downFuncCalled = false;
        _longPressFuncCalled = false;

        unsigned long downUs = now - _lastDown;

        if(downUs < longPressUs) {
          if(_clickFunc != NULL) { _clickFunc(now); }
        }
      }
    }
  }

  _pinState = newPinState;
}
