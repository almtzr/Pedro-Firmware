// =================================================================================
//  File             : PedroRobot.ino
//  Description      : Firmware for controlling the Pedro robot:
//                     1- Normal mode
//                     2- Recording mode
//                     3- Replay mode
//                     4- Bluetooth mode
//                     5- Web Controller mode
//                     6- Radio mode
//  Supported Boards : Pedro Rev3
//  Servo Type       : 360° SG90 or MG90
//
//  Author           : Almoutazar SAANDI
//  Date             : Sep 4, 2025
//  Last Update      : v1.0.3
// =================================================================================

#include <ManageDisplay.h>
#include <ManageButton.h>
#include <ManageState.h>
#include <ModeRadio.h>

ManageDisplay manageDisplay;
ManageButton manageButton;
ManageState manageState;
ModeRadio modeRadio;

void setup() {
  Serial.begin(9600);  
  Serial1.begin(9600); 
  modeRadio.Init ();
  manageState.Init ();
}

void loop() {
  manageButton.updateBtnState ();
  manageDisplay.updateScreen ();
  manageState.updateState (&manageButton, &manageDisplay);
  modeRadio.communicationRadio (&manageState);
}
