#ifndef WINDOW_H
#define WINDOW_H

#include <memory>
#include "Layout.hh"
#include "Scene/Scene.hh"

class Window {
public:
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    static void Initialize();
    static void Initialize(short width, short height);

    static Window* GetInstance();

    int GetHeight() { return m_height; }
    int GetWidth()  { return m_width; }

    void AddScene(std::shared_ptr<Scene> scene);
    void ProcessInput();
    void Render();
private:
    Window(short width, short height);
    Window();

    void HandleInputEvent(Event& event);

    std::vector<std::shared_ptr<Scene>> m_scenes;
    static std::unique_ptr<Window> m_instance;
    ConsoleBuffer m_buffer;

    short m_width;
    short m_height;
};
#endif