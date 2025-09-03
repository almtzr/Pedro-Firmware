#include "ModeRadio.h"
#include "Config.h"

//const byte basePrefix[4] = {'P','D','R','B'};
//byte m_address[5]; 
//uint8_t suffix = 0;


const byte address[6] = "00001";
RF24 radio(4, 12);

unsigned long lastSend = 0;
const uint8_t sendInterval = 10; 
uint8_t lastMode;

enum RadioMode {
  RADIO_OFF = 0,
  RADIO_TX  = 1,
  RADIO_RX  = 2
};

ModeRadio::ModeRadio() {

  m_radioType = 0;

}

void ModeRadio::Init() {  
  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_2MBPS);  //RF24_250KBPS, RF24_1MBPS, RF24_2MBPS
  radio.setChannel(120); //2400 + 120 = 2520MHz 76 default

}


void ModeRadio::communicationRadio(ManageState * manageState) {
m_radioType = manageState->getRadioType();
cmd = manageState->getCommand();

m_selectMode = manageState->getSelectMode();
  m_currentScreen = manageState->getCurrentScreen();

  const byte* addr = manageState->getAddress();  // pointeur vers le tableau m_address

Serial.print("Suffixe : ");
Serial.print(addr[0]);
Serial.print(addr[1]);
Serial.print(addr[2]);
Serial.print(addr[3]);  
Serial.println(addr[4]);  

  if (m_radioType != lastMode) {
    switch (m_radioType) {
      case RADIO_TX:
        Serial.println("Changement → MODE TX : ");
        radio.stopListening();
        radio.openWritingPipe(address);
        break;

      case RADIO_RX:
        Serial.println("Changement → MODE RX");
        radio.openReadingPipe(1, address);
        radio.startListening();
        break;

      default:
        Serial.println("Mode OFF");
        break;
    }
    lastMode = m_radioType; // mémorise le nouveau mode
  }

  if (m_selectMode == 6 and m_currentScreen == 1) {
    if (m_radioType == RADIO_TX) {

   // Serial.print("TX: ");
   // Serial.print(cmd.previousLed); Serial.print(",");
   // Serial.print(cmd.currentLed); Serial.print(",");
   // Serial.println(cmd.rotation);
  
    if (millis() - lastSend >= sendInterval) {
      lastSend = millis();
      radio.write(&cmd, sizeof(cmd));
    }

    } else if (m_radioType == RADIO_RX) {
      if (radio.available()) {
        radio.read(&cmd, sizeof(cmd));
        Serial.print("RX: ");
        Serial.print(cmd.previousLed); Serial.print(",");
        Serial.print(cmd.currentLed); Serial.print(",");
        Serial.println(cmd.rotation);
        manageState->setCommand(cmd.previousLed, cmd.currentLed, cmd.rotation);
      }
    }
  }

}