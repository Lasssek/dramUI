#include "Scene.hh"
#include "../Window.hh"

void Scene::AddWidget(std::shared_ptr<Widget> widget) {
    m_widgets.emplace_back(widget);
}

int Scene::GetWidth()  { return Window::GetInstance()->GetWidth(); };
int Scene::GetHeight() { return Window::GetInstance()->GetHeight(); };
void Scene::Show() { m_shown = true; };
void Scene::Hide() { m_shown = false; };
bool Scene::IsVisible() { return m_shown; };