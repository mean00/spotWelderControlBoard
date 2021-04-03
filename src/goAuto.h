
#include "go.h"
class GoAuto : public GoBase
{
    public:
        GoAuto(Navigate *n) : GoBase(n,Welder::Auto)
        {
            _detectionCounter=0;
        }
        virtual ~GoAuto()
        {
            
        }
        bool triggered()       ;
        bool contact()       ;
        bool start();
        int _detectionCounter;
        void   automaton();
       
};