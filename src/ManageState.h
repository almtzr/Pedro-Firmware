#ifndef __MANAGESTATE_H__
#define __MANAGESTATE_H__

#include <Arduino.h>
#include "Config.h"
#include "ManageDisplay.h"
#include "ManageButton.h"

extern const uint8_t ledPins[4];
extern const uint8_t servoPins[4];
extern const int16_t servoSpeed[4];
extern Servo servoList[4];

struct Command {
    byte previousLed;
    byte currentLed;
    byte rotation;
};

class ManageState {
  public:
    ManageState ();
    void Init ();
    void updateState (ManageButton * manageButton, ManageDisplay * manageDisplay);
    void screenIntro ();
    void screenControl ();
    void screenSelectMode ();
    void screenRadio ();
    void replayMovements ();
    uint8_t getRadioType (); 
    uint8_t getRadioKey (); 
    uint8_t getSelectMode();
    uint8_t getCurrentScreen();
    Command getCommand() const;
    void setCommand(byte previous, byte current, byte rotation);

  private:
    uint8_t m_currentScreen, m_selectMode, m_selectRadio, m_radioKey, m_currentLed, m_movementIndex, m_radioType;
    int16_t m_intervalIntro, m_lastPulse;
    unsigned long m_previousMillis, m_lastChange;
    bool m_isPressBtnRight, m_isBtnRightOn;
    bool m_isPressBtnLeft, m_isBtnLeftOn;
    bool m_isBtnCenterPressed, m_isBtnCenterLongPress, m_isBtnCenterReleased;
    bool m_startRecord, m_fromSelectMode;
    Command m_cmd;
};



#endif