#pragma once

#include "Scene.hh"

template <typename Derived>
class SceneFactory : public Scene {
public:

    template <typename... Args>
    static std::shared_ptr<Derived> Create(Args&&... args) {
        static_assert(std::is_base_of_v<Scene, Derived>, "Invalid derived class!");
        
        auto scene = std::make_shared<Derived>(Derived(std::forward<Args>(args)...));
        scene->OnCreate();
        
        return scene;
    }
};