

#include "navigate.h"
#include "welderUi.h"
#include "screen.h"
#include "pedal.h"
#include "welderUi.h"
Navigate *spawnCalibration(Navigate *parent);
Navigate *spawnTrigger(Navigate *parent);
Navigate *spawnPulseWidth(Navigate *parent);
Navigate *spawnGoAuto(Navigate *parent);
Navigate *spawnGoPedal(Navigate *parent, Pedal &p);
bool detectConnection();
extern int voltageOffset;
extern int pulseWidth;
int getVBat10(int offset);
extern Pedal *myPedal;

Welder::TriggerSource triggerSource=Welder::Pedal;

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
    int                   _dex;
    Welder::Selection     _selection;
    float                 _voltage;    
    
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
    _selection=Welder::GO;
    _voltage=12.;
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
    _voltage= (0.5+getVBat10(voltageOffset))/10.;
     switch(evt)
    {
        case Navigate::E_PUSH:            
    
            switch(_selection)
            {
                case Welder::GO:
                    subMenu=true;
                    switch(triggerSource)
                    {
                        case  Welder::Pedal: return spawnGoPedal(this,*myPedal);break;
                        case  Welder::Auto:  return spawnGoAuto(this);break;
                        default: xAssert(0);break;
                    }
                    break;
                case   Welder::Duration:  
                    subMenu=true;
                    return spawnPulseWidth(this);
                case   Welder::Trigger: 
                    subMenu=true;
                    return spawnTrigger(this);
                    break;
                case   Welder::Settings: 
                    subMenu=true;
                    return spawnCalibration(this);
                    break;
            }
            break;
        case Navigate::E_TIMER:
            redraw();
            return NULL;
        default:
            xAssert(0);
            break;            
    }
    return NULL;
}
/**
 * 
 */
void MainMenu::redraw()
{
    bool contact=detectConnection();
    myScreen->redrawStockScreen(_selection, triggerSource,pulseWidth,contact);
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
    while(s<0) s+=Welder::Max;
    s%=(Welder::Max);
    s++;
    _selection=(Welder::Selection)s;
}
// EOF
