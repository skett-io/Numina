#include "Numina_App.h"
#include "Numina_SDL2.h"
#include <SDL.h>

struct SDL2Resource : public tt::Resource {
    SDL_Window *window = nullptr;
    bool running = true;
};

struct SDL2System : public tt::System {
    std::shared_ptr<SDL2Resource> m_resource = nullptr;

    void on_startup(tt::NuminaApp &app) {
        m_resource = app.get_resource<SDL2Resource>();

        if (SDL_Init(SDL_INIT_VIDEO) != 0)
            return;

        m_resource->window = SDL_CreateWindow("Numina", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_OPENGL);
        if (!m_resource->window)
            return;
    }

    void on_event(tt::NuminaApp &app) {
        SDL_Event window_event;
        while (SDL_PollEvent(&window_event))
        {
            if (window_event.type == SDL_QUIT)
                app.running = false;
        }
    }

    void on_update(tt::NuminaApp &) {
    }

    void on_render(tt::NuminaApp &) {}

    void on_destroy(tt::NuminaApp &) {
        SDL_DestroyWindow(m_resource->window);
        SDL_Quit();
    }
};

void tt::SDL2Plugin::build(tt::NuminaApp &app) {
    app.insert_resource<SDL2Resource>({})
    .add_system<SDL2System>({});
}
