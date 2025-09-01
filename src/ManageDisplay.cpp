#include "U8glib.h"
#include "ManageDisplay.h"
#include "Config.h"

#include <string.h>
using namespace std;

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_DEV_0|U8G_I2C_OPT_NO_ACK|U8G_I2C_OPT_FAST);
//U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_DEV_0|U8G_I2C_OPT_NO_ACK|U8G_I2C_OPT_FAST);
ManageButton * m_btnState;

ManageDisplay::ManageDisplay() {
    m_radioType = 1;
    m_currentScreen = DEFAULT_SCREEN;
    m_getScreen = m_currentScreen;
    m_mode_activated = MODE_CONTROL;  
    m_modeSelected = 1;
    m_selectRadio = 1;
    m_radioKey = 1; 
}


void ManageDisplay::menuPosition(uint8_t modeSelected, const char* name, uint8_t positionX, uint8_t positionY, uint8_t bloc) {  

    if (m_modeSelected == modeSelected) {
        u8g.drawBox(positionX - 2, LEVELWIDTH + (positionY - 1)*16, bloc, 14);
        u8g.setColorIndex(1);
        u8g.drawStr(positionX, SCREEN_SIZE_Y/4.4*2 + (positionY - 1)*16, name);
    } else {
        u8g.setColorIndex(0);
        u8g.drawStr(positionX, SCREEN_SIZE_Y/4.4*2 + (positionY - 1)*16, name);
    }
}

void ManageDisplay::oledControl() {  
    menuPosition (1,"NORMAL",3,1,SCREEN_SIZE_X/2.8);
}

void ManageDisplay::oledRecord() {  
    menuPosition (2,"RECORD",3,2,SCREEN_SIZE_X/2.8);
}

void ManageDisplay::oledRepeat() {  
    menuPosition (3,"REPEAT",3,3,SCREEN_SIZE_X/2.8); 
}

void ManageDisplay::oledWebControl() {  
    menuPosition (4,"WEBCTRL",50,1,SCREEN_SIZE_X/2.4); 
}

void ManageDisplay::oledBluetooth() {  
    menuPosition (5,"BLUETOOTH",50,2,SCREEN_SIZE_X/1.9); 
}

void ManageDisplay::oledRadio() {  
    menuPosition (6,"RADIO",50,3,SCREEN_SIZE_X/3.3); 
}

void ManageDisplay::screenIntro() {  
    u8g.firstPage();
    do { 
        u8g.drawBox(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y);
        u8g.setColorIndex(0);
        u8g.setFont(u8g_font_8x13B);
        u8g.drawStr(SCREEN_SIZE_X/6, SCREEN_SIZE_Y/2, TITLE_DLE);
        u8g.setFont(u8g_font_6x13B);
        u8g.drawStr(SCREEN_SIZE_X/1.6, SCREEN_SIZE_Y/1.4, RELEASE);
        u8g.setColorIndex(1);
    } while( u8g.nextPage() );
}

void ManageDisplay::screenControl() {  
    u8g.firstPage();
    do {   
        u8g.drawBox(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y);
        u8g.setColorIndex(0);
        u8g.setFont(u8g_font_8x13B);
        u8g.drawStr(SCREEN_SIZE_X/6, 13, TITLE_DLE);
        
        u8g.setFont(u8g_font_8x13B);
        u8g.drawStr(2, SCREEN_SIZE_Y/2, "MODE");
        u8g.setFont(u8g_font_fub14r);
        u8g.drawStr(2, SCREEN_SIZE_Y - 10, m_mode_activated.c_str());
        u8g.setColorIndex(1);
    } while( u8g.nextPage() );
}

void ManageDisplay::screenSelectMode() { 
    u8g.firstPage();
    do {  
        u8g.drawBox(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y);
        u8g.setColorIndex(0);
        u8g.setFont(u8g_font_8x13B);
        u8g.drawStr(2, SCREEN_SIZE_Y/4.5, TITLE_MODE);

        u8g.setFont(u8g_font_7x13B);
        oledControl();
        oledRecord();
        oledRepeat();
        oledWebControl();
        oledBluetooth();
        oledRadio();
        u8g.setColorIndex(1);

    } while( u8g.nextPage() );
}


void ManageDisplay::oledRadioType() {  

    u8g.setFont(u8g_font_7x13B);

    if (m_selectRadio == 1) {
        u8g.drawBox(SCREEN_SIZE_X/3, SCREEN_SIZE_Y/2 - 12, SCREEN_SIZE_X/2 + 20, 15);
        u8g.setColorIndex(1);
    } else {
        u8g.setColorIndex(0);
    }
    if (m_radioType == 1) {
        u8g.drawStr(SCREEN_SIZE_X/3 + 1, SCREEN_SIZE_Y/2, TYPE_TX);
    } else  if (m_radioType == 2){
        u8g.drawStr(SCREEN_SIZE_X/3 + 1, SCREEN_SIZE_Y/2, TYPE_RX);
    }
}

void ManageDisplay::oledRadioKey() {  

    u8g.setFont(u8g_font_7x13B);

    char buffer[4];
    sprintf(buffer, "%d", m_radioKey);
    
    if (m_selectRadio == 2) {
        u8g.drawBox(SCREEN_SIZE_X/3, SCREEN_SIZE_Y/1.3 - 12, SCREEN_SIZE_X/4, 15);
        u8g.setColorIndex(1);
        u8g.drawStr(SCREEN_SIZE_X/3 + 1, SCREEN_SIZE_Y/1.3, buffer);
    } else {
        u8g.setColorIndex(0);
        u8g.drawStr(SCREEN_SIZE_X/3 + 1, SCREEN_SIZE_Y/1.3, buffer);
    }
}

void ManageDisplay::oledRadioOK() {  
    
    u8g.setFont(u8g_font_8x13B);
    if (m_selectRadio == 3) {
        u8g.drawBox(SCREEN_SIZE_X/2 + 19, SCREEN_SIZE_Y - 15, SCREEN_SIZE_X/4, 15);
        u8g.setColorIndex(1);
        u8g.drawStr(SCREEN_SIZE_X/2 + 24, SCREEN_SIZE_Y, "OK");
    } else {
        u8g.setColorIndex(0);
        u8g.drawStr(SCREEN_SIZE_X/2 + 24, SCREEN_SIZE_Y, "OK");
    }
}

void ManageDisplay::screenRadio() { 
    u8g.firstPage();
    do {  
        u8g.drawBox(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y);
        u8g.setColorIndex(0);
        u8g.setFont(u8g_font_8x13B);
        u8g.drawStr(2, 13, TITLE_RADIO);
        
        u8g.drawStr(2, SCREEN_SIZE_Y/2, "TYPE:");
        u8g.drawStr(2, SCREEN_SIZE_Y/1.3,"KEY:");

        oledRadioType();
        oledRadioKey();
        oledRadioOK();
        
        u8g.setColorIndex(1);
    } while( u8g.nextPage() );
}

uint8_t ManageDisplay::getScreen() { return m_getScreen; }
void ManageDisplay::setDisplayScreen(uint8_t displayScreen) { m_currentScreen = displayScreen; }
void ManageDisplay::setModeActivated(String modeActivated) { m_mode_activated = modeActivated; }
void ManageDisplay::setModeSelected(uint8_t modeSelected) { m_modeSelected = modeSelected; }
void ManageDisplay::setRadioKey(uint8_t radioKey) { m_radioKey = radioKey; }
void ManageDisplay::setRadioSelected(uint8_t selectRadio) { m_selectRadio = selectRadio; }

void ManageDisplay::setRadioType(uint8_t radioType) { m_radioType = radioType; }
uint8_t ManageDisplay::getRadioType() { return m_radioType; }


void ManageDisplay::updateScreen () {  

    if (m_currentScreen == 0) {
        screenIntro ();
        m_getScreen = 0;
        m_currentScreen = -1;
    } else if (m_currentScreen == 1) {
        screenControl ();
        m_getScreen = 1;
        m_currentScreen = -1;
    } else if (m_currentScreen == 2) {
        screenSelectMode ();
        m_getScreen = 2;
    } else if (m_currentScreen == 3) {
        screenRadio ();
        m_getScreen = 3;
    }  /*else if (m_currentScreen == 4) {
        screenRadio ();
        m_getScreen = 3;  */  
}