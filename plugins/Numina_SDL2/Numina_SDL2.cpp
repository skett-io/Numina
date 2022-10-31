#include "Numina_SDL2.h"
#include "Numina_App.h"
#include <SDL.h>

struct SDL2Resource : public tt::Resource
{
    SDL_Window *window = nullptr;
    bool running = true;
};

tt::NuminaEvent tt_translate_event(SDL_Event *sdl_event)
{
    tt::NuminaEvent numina_event;

    switch (sdl_event->type)
    {
    case SDL_QUIT:
        numina_event.m_type = tt::Quit;
        break;
    case SDL_KEYUP:
        numina_event.m_type = tt::KeyUp;
        numina_event.event.key.code = sdl_event->key.keysym.sym;
        break;
    default:
        break;
    }

    return numina_event;
}

struct SDL2StartupSystem : public tt::System
{
    std::shared_ptr<SDL2Resource> m_resource = nullptr;

    int32_t priority() override
    {
        return -999;
    }

    void on_startup(tt::NuminaApp &app) override
    {
        m_resource = app.get_resource<SDL2Resource>();

        if (SDL_Init(SDL_INIT_VIDEO) != 0)
            return;

        m_resource->window =
            SDL_CreateWindow("Numina", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_OPENGL);
        if (!m_resource->window)
            return;
    }

    bool on_event(tt::NuminaApp &app, tt::NuminaEvent event) override
    {
        switch (event.m_type)
        {
        case tt::Quit:
            app.running = false;
            return true;
        default:
            return false;
        }
    }

    void on_update(tt::NuminaApp &app) override
    {
        SDL_Event window_event;
        while (SDL_PollEvent(&window_event))
            app.dispatch_event(tt_translate_event(&window_event));
    }
};

void tt::SDL2Plugin::build(tt::NuminaApp &app)
{
    app.insert_resource<SDL2Resource>({}).add_system<SDL2StartupSystem>({});
}
