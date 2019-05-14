/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\Drew                                             */
/*    Created:      Fri May 10 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
#include "robot.h"
#include <iostream>

#include "rom.h"
#include "registers.h"
#include "cpu.h"
#include "gpu.h"
#include "interrupts.h"
#include "debug.h"
#include "keys.h"
#include "display.h"

void quit() {
  exit(1);
}

int main () {
  Brain.Screen.render();

  #ifndef NOFS
  if (!v5loadROM("tetris.gb")) {
    std::cout<<"v5loadROM failed"<<std::endl;
    quit();
  }
  #else
  std::cout<<"NOFS Not Implemented in VexV5 yet"<<std::endl;
  #endif


  while(true) {
    keys.keys1 = 0xf;
    keys.keys2 = 0xf;


    // Handle A and B
    if(Controller.ButtonA.pressing()) keys.a = 0;
    if(Controller.ButtonB.pressing()) keys.b = 0;

    //Handle Up, Down, Left, and Right
    if(Controller.ButtonLeft.pressing()) keys.left = 0;
    if(Controller.ButtonRight.pressing()) keys.right = 0;
    if(Controller.ButtonUp.pressing()) keys.up = 0;
    if(Controller.ButtonDown.pressing()) keys.down = 0;

    //Handle Select and Start
    if(Controller.ButtonR1.pressing()) keys.select = 0;
    if(Controller.ButtonL1.pressing()) keys.start  = 0;

    cpuStep();
    gpuStep();
    interruptStep();
  }

  quit();
  return 0;
}

