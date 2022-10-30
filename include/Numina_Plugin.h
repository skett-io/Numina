#ifndef NUMINA_PLUGIN_H
#define NUMINA_PLUGIN_H

#include <stdint.h>

namespace tt
{
    struct NuminaApp;

    struct Resource
    {};

    struct System
    {
        virtual int32_t priority()
        {
            return 0;
        }

        virtual void on_startup(NuminaApp &) = 0;
        virtual void on_event(NuminaApp &) = 0;
        virtual void on_update(NuminaApp &) = 0;
        virtual void on_render(NuminaApp &) = 0;
        virtual void on_destroy(NuminaApp &) = 0;
    };

    struct Plugin
    {
        virtual void build(NuminaApp &) = 0;
    };
}

#endif // NUMINA_PLUGIN_H
