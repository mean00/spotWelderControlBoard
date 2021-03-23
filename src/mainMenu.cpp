

#include "navigate.h"
#include "screen.h"
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
    int                     _dex;
    MyScreen::Selection     _selection;
    float                   _voltage;
    MyScreen::TriggerType   _triggerType;
    int                     _durationMs;
    
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
    one->str="BB calib";
    menu.push_back(one);
    _selection=MyScreen::None;
    _triggerType=MyScreen::Pedal;
    _voltage=12.;
    _durationMs=5;
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
    
            switch(_selection)
            {
                case   MyScreen::Duration: break;
                case   MyScreen::Trigger: break;
                case   MyScreen::Settings: 
                    subMenu=true;
                    return spawnCalibration(this);
                    break;
            }
            
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
    myScreen->redrawStockScreen(_selection, _voltage,_triggerType,_durationMs);
}
/**
 * 
 * @param inc
 */
void  MainMenu::handleRotary(int inc)
{
    int s=(int)_selection;
    s--;
    s+=inc;
    s%=(MyScreen::Max);
    s++;
    _selection=(MyScreen::Selection)s;
}
// EOF