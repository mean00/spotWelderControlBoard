
#include "go.h"
#include "pedal.h"
class GoPedal : public GoBase
{
    public:
        GoPedal(Navigate *n,Pedal &pedal) : GoBase(n,Welder::Auto),_pedal(pedal)
        {
            _pedal.pushed(); // clear 
            _detectionCounter=0;
            
        }
        
        virtual ~GoPedal()
        {
            
        }
        void automaton();
        bool triggered()       ;
        bool contact()       ;
        bool start();
        int _detectionCounter;
        Pedal &_pedal;
       
};