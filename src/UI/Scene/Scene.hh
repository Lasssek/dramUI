#pragma once

#include <vector>
#include <memory>
#include "../Widget.hh"

class Scene : public ParentProvider, public std::enable_shared_from_this<Scene> {
public:
    virtual ~Scene() = default;
    virtual void OnCreate() = 0;

    virtual void Draw(ConsoleBuffer& buffer) = 0;
    virtual void HandleEvent(Event& event)   = 0;

    void AddWidget(std::shared_ptr<Widget> widget);

    int GetWidth();
    int GetHeight();

    void Show();
    void Hide();
    bool IsVisible();
protected:
    std::vector<std::shared_ptr<Widget>> m_widgets;
    bool m_shown = true;
};