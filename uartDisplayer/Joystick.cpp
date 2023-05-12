#include "Joystick.h"

void Joystick::init(){
  pinMode(pinZ, INPUT_PULLUP);

}

int Joystick::readX(){
  return analogRead(pinX);
}

int Joystick::readY(){
  return analogRead(pinY);
}
