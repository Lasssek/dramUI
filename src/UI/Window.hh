#pragma once

#include <memory>
#include "Layout.hh"
#include "./Scene/Scene.hh"

class Window {
public:
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    static void Initialize();
    static void Initialize(int width, int height);

    static Window* GetInstance();

    int GetHeight() { return m_height; }
    int GetWidth()  { return m_width; }

    void AddScene(std::shared_ptr<Scene> scene);
    void ProcessInput();
    void Render();
private:
    Window(int width, int height);
    Window();

    void HandleInputEvent(Event& event);

    std::vector<std::shared_ptr<Scene>> m_scenes;
    static std::unique_ptr<Window> m_instance;
    ConsoleBuffer m_buffer;

    int m_width;
    int m_height;
};
