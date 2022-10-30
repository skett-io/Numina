#ifndef NUMINA_SDL2_H
#define NUMINA_SDL2_H

#include "Numina_Plugin.h"

namespace tt
{
    struct SDL2Plugin : public Plugin
    {
        void build(tt::NuminaApp &) override;
    };
}

#endif // NUMINA_SDL2_H
