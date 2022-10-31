#ifndef NUMINA_PLUGIN_H
#define NUMINA_PLUGIN_H

#include <stdint.h>

#include "Numina_Event.h"

namespace tt
{
struct NuminaApp;

struct Resource
{
};

struct System
{
    virtual int32_t priority()
    {
        return 0;
    }

    virtual void on_startup(NuminaApp &){};
    virtual bool on_event(NuminaApp &, NuminaEvent)
    {
        return false;
    };
    virtual void on_update(NuminaApp &){};
    virtual void on_render(NuminaApp &){};
    virtual void on_destroy(NuminaApp &){};
};

struct Plugin
{
    virtual void build(NuminaApp &) = 0;
};
} // namespace tt

#endif // NUMINA_PLUGIN_H
