#pragma once

#include "Widget.hh"
#include <memory>
#include "WidgetRegister.hh"


class Layout : public Widget, public WidgetRegister<Layout> {
public:
    virtual ~Layout() = default;
    virtual void PositionWidgets() = 0;
    virtual void CalculateSize()   = 0;
    virtual void UpdateHierarchy() = 0;

    void Draw(ConsoleBuffer& buffer) override {
        for (auto& [_, widget] : m_widgets) {
            widget->Draw(buffer);
        }
    }

    void HandleEvent(Event& event) override {
        for (auto& [_, widget] : m_widgets) {
            widget->HandleEvent(event);
        }
        UpdateHierarchy();
    }

    // template <typename T, typename... Args>
    // std::shared_ptr<T> CreateWidget(Args&&... args) {
    //     auto widget = std::make_shared<T>(shared_from_this(), args...);
    //     m_widgets.emplace_back(widget);

    //     UpdateHierarchy();
    //     return widget;
    // }
protected:
    void OnWidgetsChanged() override {
        UpdateHierarchy();
    }
};