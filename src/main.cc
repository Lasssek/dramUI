#include "UI/Window.hh"
#include "scenes/MainScene.hh"

int main(void) {
    Window::Initialize();

    auto scene = MainMenuScene::Create();

    Window::GetInstance()->AddScene(scene);

    while (true) {
        Window::GetInstance()->ProcessInput();
        Window::GetInstance()->Render();
    }
}