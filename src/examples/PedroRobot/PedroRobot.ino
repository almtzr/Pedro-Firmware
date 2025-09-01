// =================================================================================
//  File             : PedroRobot.ino
//  Description      : Firmware for controlling the Pedro robot:
//                     1- Normal mode
//                     2- Recording mode
//                     3- Replay mode
//                     4- Bluetooth mode
//                     6- IHM Web Controller mode
//  Supported Boards : Pedro Rev3
//  Servo Type       : 360° SG90 or MG90
//
//  Author           : Almoutazar SAANDI
//  Date             : Sep 1, 2025
//  Last Update      : v1.0.3
// =================================================================================

#include <RF24.h>

#include <ManageDisplay.h>
#include <ManageButton.h>
#include <ManageState.h>
#include <ModeRadio.h>

ManageDisplay manageDisplay;
ManageButton manageButton;
ManageState manageState;
ModeRadio modeRadio;

RF24 radio(4, 12);
const uint64_t pipeA = 0xE8E8F0F0E1LL;

void setup() {
  Serial.begin(9600);  
  Serial1.begin(9600);  
  
  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_2MBPS);  //RF24_250KBPS, RF24_1MBPS, RF24_2MBPS
  radio.setChannel(120); //2400 + 120 = 2520MHz 76 default
  //radio.openReadingPipe(1,pipeA);
  //radio.startListening();
  
  manageState.Init ();

}

void loop() {
  manageButton.updateBtnState ();
  manageDisplay.updateScreen ();
  manageState.updateState (&manageButton, &manageDisplay);
  modeRadio.communicationRadio (&manageState, &radio);
}
