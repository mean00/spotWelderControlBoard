
#include "go.h"
class GoAuto : public GoBase
{
    public:
        GoAuto(Navigate *n) : GoBase(n)
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