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
  while(true) {
    std::cout<<"quitttttttttted"<<std::endl;
    vex::task::sleep(20);
  }
}

int main () {
  //Brain.Screen.render();

  if (!v5loadROM("tetris.gb")) {
    std::cout<<"v5loadROM failed"<<std::endl;
    quit();
  }

  std::cout<<"Entering main loop"<<std::endl;
  while(true) {
    keys.keys1 = 0xf;
    keys.keys2 = 0xf;


    std::cout<<"keys stored in memory at address "<<&keys<<std::endl;
    std::cout<<"Reading ab keys"<<std::endl;
    // Handle A and B
    if(Controller.ButtonA.pressing() == true) {keys.a = 0;}
    if(Controller.ButtonB.pressing() == true) {keys.b = 0;}

    std::cout<<"Reading udlr keys"<<std::endl;
    //Handle Up, Down, Left, and Right
    if(Controller.ButtonLeft.pressing()) keys.left = 0;
    if(Controller.ButtonRight.pressing()) keys.right = 0;
    if(Controller.ButtonUp.pressing()) keys.up = 0;
    if(Controller.ButtonDown.pressing()) keys.down = 0;

    std::cout<<"Reading ss keys"<<std::endl;
    //Handle Select and Start
    if(Controller.ButtonR1.pressing()) keys.select = 0;
    if(Controller.ButtonL1.pressing()) keys.start  = 0;

    std::cout<<"Read Keys. Stepping CPU"<<std::endl;
    cpuStep();
    std::cout<<"Stepping GPU"<<std::endl;
    gpuStep();
    std::cout<<"Reading interrupts"<<std::endl;
    interruptStep();
  }

  quit();
  return 0;
}

