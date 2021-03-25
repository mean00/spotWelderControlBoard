#pragma once
namespace Welder
{
    enum Selection
        {
            None,
            Duration,
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