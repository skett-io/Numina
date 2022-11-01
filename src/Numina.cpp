#include "Numina_App.h"
#include "Numina_Graphics.h"
#include "Numina_SDL2.h"

#include <algorithm>

struct CloseOnEscape : public tt::System
{
    bool on_event(tt::NuminaApp &app, tt::NuminaEvent event)
    {
        if (event.m_type == tt::KeyUp)
        {
            app.running = false;
            return true;
        }

        return false;
    }
};

struct CancelKeyUp : public tt::System
{
    int32_t priority() override
    {
        return 1;
    }

    bool on_event(tt::NuminaApp &app, tt::NuminaEvent event) override
    {
        if (event.m_type == tt::KeyUp)
        {
            printf("Canceled event!\n");
            return true;
        }

        return false;
    }
};

void test()
{
    tt::NuminaApp app;
    app.insert_resource<tt::WindowDescriptor>({
                                                  .title = "Numina Example",
                                                  .width = 1920,
                                                  .height = 1080,
                                              })
        .add_plugin<tt::SDL2Plugin>({})
        .add_system<CloseOnEscape>({})
        .run();
}

void tt::NuminaApp::dispatch_event(tt::NuminaEvent event)
{
    m_events.push_back(event);
}

void tt::NuminaApp::run()
{
    if (m_systems.size() > 1)
    {
        std::sort(m_systems.begin(), m_systems.end(),
                  [](const std::unique_ptr<System> &left, const std::unique_ptr<System> &right) {
                      return left->priority() < right->priority();
                  });
    }

    for (auto &system : m_systems)
        system->on_startup(*this);

    while (this->running)
    {
        if (m_events.size())
        {
            std::sort(m_events.begin(), m_events.end(),
                      [](const NuminaEvent &left, const NuminaEvent &right) { return left.m_type < right.m_type; });

            for (auto &event : m_events)
            {
                for (auto system = m_systems.rbegin(); system != m_systems.rend(); system++)
                {
                    printf("Priority: %d\n", system->get()->priority());
                    if (system->get()->on_event(*this, event))
                        break;
                }
            }

            m_events.clear();
        }

        for (auto &system : m_systems)
            system->on_update(*this);

        for (auto &system : m_systems)
            system->on_render(*this);
    }

    for (auto system = m_systems.rbegin(); system != m_systems.rend(); system++)
        system->get()->on_destroy(*this);
}
