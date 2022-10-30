#include "Numina_App.h"
#include "Numina_SDL2.h"

#include <algorithm>

struct WindowDescriptor : public tt::Resource {
    int x = 0;
};

struct WindowSystem : public tt::System {
    int32_t priority() override {
        return 100;
    }

    void on_startup(tt::NuminaApp &) {}

    void on_event(tt::NuminaApp &) {}

    void on_update(tt::NuminaApp &) {}

    void on_render(tt::NuminaApp &) {}

    void on_destroy(tt::NuminaApp &) {}
};

struct EventSystem : public tt::System {
    int32_t priority() override {
        return 1;
    }

    void on_startup(tt::NuminaApp &) {}

    void on_event(tt::NuminaApp &) {}

    void on_update(tt::NuminaApp &) {}

    void on_render(tt::NuminaApp &) {}

    void on_destroy(tt::NuminaApp &) {}
};

void test() {
    tt::NuminaApp app;
    app.insert_resource<WindowDescriptor>({})
            .add_system<WindowSystem>({})
            .add_system<EventSystem>({})
            .add_plugin<tt::SDL2Plugin>({})
            .run();
}

void tt::NuminaApp::run() {
    if (m_systems.size() > 1) {
        std::sort(m_systems.begin(), m_systems.end(),
                  [](const std::unique_ptr<System> &left, const std::unique_ptr<System> &right) {
                      return left->priority() < right->priority();
                  });
    }

    for (auto &system: m_systems) {
        system->on_startup(*this);
    }

    while (this->running) {
        for (auto &system: m_systems) {
            system->on_event(*this);
        }

        for (auto &system: m_systems) {
            system->on_update(*this);
        }
    }

    for (auto &system : m_systems) {
        system->on_destroy(*this);
    }
}
