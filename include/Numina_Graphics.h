#ifndef __NUMINA_GRAPHICS_H_
#define __NUMINA_GRAPHICS_H_

#include "Numina_Plugin.h"

namespace tt
{
    struct WindowDescriptor : public tt::Resource
    {
        const char *title = "Numina";
        int width = 1280, height = 720;
    };
}

#endif // __NUMINA_GRAPHICS_H_

