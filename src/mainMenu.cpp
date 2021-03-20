
#define HWIRE I2C1

#include <Wire.h>
#include "OLED_I2C.h"
#include "MapleFreeRTOS1000_pp.h"
#include "pinMapping.h"
#include "printf.h"
#include "dso_debug.h"
#include "dso_eeprom.h"
#include "navigate.h"
#include "vector"

extern OLED  *myOLED;

/**
 * 
 * @param p
 */
class MainMenu : public Navigate
{
public:
   
            MainMenu(Navigate *p);                
    virtual ~MainMenu();
    virtual Navigate *handleEvent(Event evt,bool &subMenu);
    virtual void redraw();
    virtual void  handleRotary(int inc);
    
protected:
    class menuItem
    {
    public:
        const char *str;
    };
    std::vector<menuItem *>menu;
    int _dex;
    
};
/**
 * 
 * @return 
 */
Navigate * spawnMainMenu()
{
    
    return new MainMenu(NULL);
}
/**
 * 
 * @param p
 */
MainMenu::MainMenu(Navigate *p): Navigate(p)
{
    menuItem *one=new menuItem;
    one->str="Vbat calib";
    menu.push_back(one);

    redraw();
}
/**
 * 
 */
MainMenu::~MainMenu()
{
    int n=menu.size();
    for(int i=0;i<n;i++) delete menu[i];
    menu.clear();
}
/**
 * 
 * @param evt
 * @param subMenu
 * @return 
 */
Navigate *MainMenu::handleEvent(Event evt,bool &subMenu)
{
    
}
/**
 * 
 */
void MainMenu::redraw()
{
    myOLED->clrScr();
    int dex=_dex % (menu.size());
    myOLED->print(menu[dex]->str,20,35);
    myOLED->update();
}
/**
 * 
 * @param inc
 */
void  MainMenu::handleRotary(int inc)
{
    
}