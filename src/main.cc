#include "UI/Window.hh"
#include "scenes/MainScene.hh"
#include <iostream>

int main(void) {
    Window::Initialize();

    auto scene = std::make_shared<MainMenuScene>();
    scene->OnCreate();

    Window::GetInstance()->AddScene(scene);

    while (true) {
        Window::GetInstance()->ProcessInput();
        Window::GetInstance()->Render();
    }
}