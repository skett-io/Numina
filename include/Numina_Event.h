#ifndef __NUMINA_EVENT_H_
#define __NUMINA_EVENT_H_

#include <stdint.h>

namespace tt
{
    enum EventType
    {
        Quit = 0,

        KeyDown = 100,
        KeyUp = 101
    };

    struct NuminaEvent
    {
        EventType m_type;

        union
        {
            struct KeyEvent
            {
                uint32_t code;
            } key;
        } event;
    };
}

#endif // __NUMINA_EVENT_H_

