
#include "go.h"
#include "pedal.h"
class GoPedal : public GoBase
{
    public:
        GoPedal(Navigate *n,Pedal &pedal) : GoBase(n,Welder::Auto),_pedal(pedal)
        {
            _detectionCounter=0;
        }
        virtual ~GoPedal()
        {
            
        }
        bool triggered()       ;
        bool contact()       ;
        int _detectionCounter;
        Pedal &_pedal;
       
};