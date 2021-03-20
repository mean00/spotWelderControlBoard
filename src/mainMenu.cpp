

#include "navigate.h"

Navigate *spawnCalibration(Navigate *parent);
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
    one->str="xxx calib";
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
     switch(evt)
    {
        case Navigate::E_PUSH:            
            subMenu=true;
            return spawnCalibration(this);
        case Navigate::E_TIMER:
            redraw();
            return NULL;
        default:
            xAssert(0);
            break;
            
    }
}
/**
 * 
 */
void MainMenu::redraw()
{
    myScreen->clear();
    int dex=_dex % (menu.size());
    myScreen->print(menu[dex]->str,20,35);
    myScreen->update();
}
/**
 * 
 * @param inc
 */
void  MainMenu::handleRotary(int inc)
{
    
}