#include "Window.hh"

#include <format>

std::unique_ptr<Window> Window::m_instance = nullptr;

Window::Window(int width, int height) : m_buffer(width, height), m_width(width), m_height(height) {};
Window::Window() : m_buffer() {
    Vector2D size = m_buffer.GetSize();

    m_height = size.height;
    m_width  = size.width;
};

void Window::AddScene(std::shared_ptr<Scene> scene) {
    m_scenes.emplace_back(scene);
}

void Window::ProcessInput() {
    HANDLE handle = GetStdHandle(STD_INPUT_HANDLE);
    DWORD numEvents = 0;

    GetNumberOfConsoleInputEvents(handle, &numEvents);

    if (numEvents > 0) {
        std::vector<INPUT_RECORD> inputEvents(numEvents);
        DWORD numRead = 0;
        ReadConsoleInput(handle, inputEvents.data(), numEvents, &numRead);

        for (auto& inputEvent : inputEvents) {
            Event event;

            switch(inputEvent.EventType) {
                case MOUSE_EVENT: {
                    auto& mouse = inputEvent.Event.MouseEvent;
                    
                    if (mouse.dwEventFlags & MOUSE_MOVED) {
                        event.type = EventType::onMouseMove;
                    } else {
                        event.type = (mouse.dwButtonState != 0) ? EventType::onMousePress : EventType::onMouseRelease;
                    }
                    
                    event.mouse.position = mouse.dwMousePosition;
                    event.mouse.buttons = mouse.dwButtonState;
                    event.mouse.flags = mouse.dwEventFlags;

                    HandleInputEvent(event);
                } break;

                case KEY_EVENT: {
                    auto& key = inputEvent.Event.KeyEvent;
                    event.type = key.bKeyDown ? EventType::onKeyPress : EventType::onKeyRelease;

                    event.keyboard.key = key.wVirtualKeyCode;
                    event.keyboard.asciiChar = key.uChar.AsciiChar;
                    event.keyboard.controlKeyState = key.dwControlKeyState;

                    HandleInputEvent(event);
                } break;
            }
        }
    }
}


void Window::HandleInputEvent(Event& event) {
    for (auto& scene : m_scenes) {
        if (scene->IsVisible()) {
            scene->HandleEvent(event);
        }
    }
}

void Window::Render() {
    m_buffer.Clear();

    for (auto& scene : m_scenes) {
        if (scene->IsVisible()) {
            scene->Draw(m_buffer);
        }
    }
    m_buffer.Render();
}

Window* Window::GetInstance() {
    if (!m_instance) {
        throw std::runtime_error("Window is not initialized");
    }

    return m_instance.get();
}

void Window::Initialize(int width, int height) {
    if (!m_instance) {
        m_instance = std::unique_ptr<Window>(new Window(width, height));
    }
}

void Window::Initialize() {
    if (!m_instance) {
        m_instance = std::unique_ptr<Window>(new Window);
    }
}