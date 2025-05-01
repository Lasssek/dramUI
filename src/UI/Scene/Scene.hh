#pragma once

#include <vector>
#include <memory>
#include "../Widget.hh"
#include "../WidgetRegister.hh"

class Scene : public WidgetRegister<Scene>, public IParentProvider {
public:
    virtual ~Scene() = default;
    virtual void OnCreate() = 0;

    virtual void Draw(ConsoleBuffer& buffer) = 0;
    virtual void HandleEvent(Event& event)   = 0;

    int GetWidth();
    int GetHeight();

    void Show();
    void Hide();
    bool IsVisible();
protected:
    void OnWidgetsChanged() override {
        return;
    };
    bool m_shown = true;
};