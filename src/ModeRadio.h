#ifndef __MODERADIO_H__
#define __MODERADIO_H__

#include <Arduino.h>
#include "Config.h"
#include <RF24.h>
#include "ManageState.h"


class ModeRadio {
  public:
    ModeRadio ();
    void Init ();
    void stopRadio ();
    void communicationRadio(ManageState * manageState);


  private:
    uint8_t m_radioType, m_selectMode, m_currentScreen;
    bool m_radioActive;
    byte m_radioKey;
    Command cmd;

};



#endif