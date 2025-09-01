#ifndef __MANAGEDISPLAY_H__
#define __MANAGEDISPLAY_H__

#include "ManageButton.h"
#include <Arduino.h>


class ManageDisplay {

      public:
            ManageDisplay ();
            void screenSelectMode ();
            void screenIntro ();
            void screenControl ();
            void screenRadio ();
            void oledControl ();
            void oledRecord ();
            void oledRepeat ();
            void oledRadio ();
            void oledWebControl ();
            void oledBluetooth ();
            void oledRadioType ();
            void oledRadioKey ();
            void oledRadioOK ();
            uint8_t getScreen ();
            void setDisplayScreen (uint8_t displayScreen);
            void setModeActivated(String modeActivated);
            void setModeSelected(uint8_t modeSelected);
            void setRadioSelected(uint8_t selectRadio);
            void setRadioKey(uint8_t radioKey);
            void setRadioType(uint8_t radioType);
            uint8_t getRadioType();
            void updateScreen ();
            void menuPosition(uint8_t modeSelected, const char* name, uint8_t positionX, uint8_t positionY, uint8_t bloc);

      private:
            uint8_t m_radioType;
            uint8_t m_currentScreen, m_getScreen;
            uint8_t m_modeSelected, m_selectRadio, m_radioKey;
            String m_mode_activated;
};


#endif