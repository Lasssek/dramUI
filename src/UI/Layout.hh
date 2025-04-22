#pragma once

#include "Widget.hh"
#include <memory>

class Layout : public Widget, public std::enable_shared_from_this<Layout> {
public:
    virtual ~Layout() = default;
    virtual void PositionWidgets() = 0;
    virtual void CalculateSize()   = 0;
    virtual void UpdateHierarchy() = 0;

    void AddWidget(std::shared_ptr<Widget> widget) {
        m_widgets.emplace_back(widget);
        UpdateHierarchy();
    }

    void AddWidgets(std::initializer_list<std::shared_ptr<Widget>> widgets) {
        m_widgets.insert(m_widgets.end(), widgets.begin(), widgets.end());
        UpdateHierarchy();
    }

    void ClearWidgets() {
        m_widgets.clear();
        UpdateHierarchy();
    }

    void Draw(ConsoleBuffer& buffer) override {
        for (auto& widget : m_widgets) {
            widget->Draw(buffer);
        }
    }

    void HandleEvent(Event& event) override {
        for (auto& widget : m_widgets) {
            widget->HandleEvent(event);
        }
    }

    template <typename T, typename... Args>
    std::shared_ptr<T> CreateWidget(Args&&... args) {
        auto widget = std::make_shared<T>(shared_from_this(), args...);
        m_widgets.emplace_back(widget);

        UpdateHierarchy();
        return widget;
    }
protected:
    std::vector<std::shared_ptr<Widget>> m_widgets;
};