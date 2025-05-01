#include "Scene.hh"
#include "../Window.hh"

int Scene::GetWidth()  { return Window::GetInstance()->GetWidth(); };
int Scene::GetHeight() { return Window::GetInstance()->GetHeight(); };
void Scene::Show() { m_shown = true; };
void Scene::Hide() { m_shown = false; };
bool Scene::IsVisible() { return m_shown; };