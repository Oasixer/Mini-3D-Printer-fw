/*
Group 414
3D Printer
Ending procedure functions
*/

#include "global.c"
#include "move.c"
#include "misc.c"

#ifndef END_C
#define END_C

//notifies the user using a sound and flashing lights. for when the print is ready for removal
void notifyUser(int frequency, int timeSound, TEV3LEDPatterns led)
{
  playTone(frequency, timeSound);
  setLEDColor(led);
}

void endProcedure()
{
  moveZ(Z_MAX); //move the extruder out of the way by lifting as high as possible

  notifyUser(440, 30, ledOrangePulse); //play noises and flash lights

  notifyUser(440, 30, ledRedFlash);

  wait10Msec(COOL_DOWN_TIME); //wait until the extruder has cooled

  notifyUser(440, 30, ledGreenFlash); //play noise and flash light

  waitForEnter();
}

#endif
