
#include "go.h"
class GoAuto : public GoBase
{
    public:
        GoAuto(Navigate *n) : GoBase(n,Welder::Auto)
        {
            
        }
        virtual ~GoAuto()
        {
            
        }
        bool triggered()
        {
            return true;
        }
        bool contact()
        {
            return true;
        }
       
};