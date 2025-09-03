#include "ModeRadio.h"
#include "Config.h"

byte address[5] = {'P','E','D','R','1'};
RF24 radio(4, 12);

unsigned long lastSend = 0;
const uint8_t sendInterval = 10; 
uint8_t lastMode;
byte lastKey;

enum RadioMode {
  RADIO_OFF = 0,
  RADIO_TX  = 1,
  RADIO_RX  = 2
};

ModeRadio::ModeRadio() {
  m_radioType = 1;
  m_radioKey = 1;
  m_radioActive = false;
}

void ModeRadio::Init() {  
  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_2MBPS);  //RF24_250KBPS, RF24_1MBPS, RF24_2MBPS
  radio.setChannel(120); //2400 + 120 = 2520MHz 76 default

}

void ModeRadio::stopRadio() {
  if (!m_radioActive) return; // déjà OFF → inutile
  radio.stopListening();  // arrête RX et met en standby TX
  radio.flush_tx();       // vide le buffer d’émission
  radio.flush_rx();       // vide le buffer de réception
  radio.powerDown();      // OFF total
  m_radioActive = false;
}

void ModeRadio::communicationRadio(ManageState * manageState) {
m_radioType = manageState->getRadioType();
m_radioKey = manageState->getRadioKey();
cmd = manageState->getCommand();

m_selectMode = manageState->getSelectMode();
m_currentScreen = manageState->getCurrentScreen();
 
  if (m_radioType != lastMode || m_radioKey != lastKey) {
    address[4] = m_radioKey;
    m_radioActive = true;
    switch (m_radioType) {
      case RADIO_TX:
        Serial.println("Changement → MODE TX : ");
        radio.powerUp();
        radio.stopListening();
        radio.openWritingPipe(address);
        break;

      case RADIO_RX:
        Serial.println("Changement → MODE RX");
        radio.powerUp();
        radio.closeReadingPipe(1);
        radio.openReadingPipe(1, address);
        radio.startListening();
        break;

      default:
        Serial.println("Mode OFF");
        break;
    }
    lastMode = m_radioType; // mémorise le nouveau mode
    lastKey = m_radioKey; // mémorise le nouveau key
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
        /*Serial.print("RX: ");
        Serial.print(cmd.previousLed); Serial.print(",");
        Serial.print(cmd.currentLed); Serial.print(",");
        Serial.println(cmd.rotation);*/
        manageState->setCommand(cmd.previousLed, cmd.currentLed, cmd.rotation);
      }
    }
  }

}