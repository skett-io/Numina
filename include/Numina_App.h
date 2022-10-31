#ifndef NUMINA_APP_H
#define NUMINA_APP_H

#include "Numina_Event.h"
#include "Numina_Plugin.h"

#include <unordered_map>
#include <vector>
#include <memory>

#include <typeindex>

namespace tt
{
    struct NuminaApp {
        bool running = true;

        template<typename T>
        NuminaApp &insert_resource(T resource) {
            m_resources.insert_or_assign(typeid(T), std::move(std::make_shared<T>(resource)));

            return *this;
        }

        template<typename T>
        NuminaApp &add_system(T system)
        {
            m_systems.push_back(std::move(std::make_unique<T>(system)));

            return *this;
        }

        template<typename T>
        NuminaApp &add_plugin(T plugin)
        {
            plugin.build(*this);

            return *this;
        }

        template<typename T>
        std::shared_ptr<T> get_resource()
        {
            return std::static_pointer_cast<T>(m_resources[typeid(T)]);
        }

        void dispatch_event(NuminaEvent);
        void run();

    private:
        std::vector<NuminaEvent> m_events;

        std::unordered_map<std::type_index, std::shared_ptr<Resource>> m_resources;
        std::vector<std::unique_ptr<System>> m_systems;
    };
}

#endif // NUMINA_APP_H
