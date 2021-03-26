#pragma once
namespace Welder
{
    enum Selection
        {
            None,
            Duration,
            GO,
            Trigger,
            Settings,
            
            Max=Settings
        };
        enum TriggerSource
        {
            Auto,
            Pedal
        };    
};