#pragma once

#include "Widget.hh"
#include <map>
#include <stdexcept>
#include <string>

template <class Derived>
class WidgetRegister : public std::enable_shared_from_this<Derived> {
public:
    virtual ~WidgetRegister() = default;

    template <class T, class ...Args>
    std::shared_ptr<T> CreateWidget(const std::string& id, Args&&... args) {
        static_assert(std::is_base_of_v<Widget, T>, "Not derived from Widget!");

        if (m_widgets.contains(id)) throw std::invalid_argument("Widget with that id already exists");

        auto parent = this->std::enable_shared_from_this<Derived>::shared_from_this();
        auto widget = std::make_shared<T>(parent, args...);
        m_widgets.emplace(id, widget);
        OnWidgetsChanged();

        return widget;
    }

    bool RemoveWidget(const std::string& id) {
        if (!m_widgets.contains(id)) return false;

        OnWidgetsChanged();
        
        return m_widgets.erase(id);
    }

    void ClearWidgets() {
        m_widgets.clear();
        OnWidgetsChanged();
    }

    bool AddWidget(const std::string& id, std::shared_ptr<Widget> widget) {
        if (m_widgets.contains(id)) return false;

        m_widgets.emplace(id, widget);
        OnWidgetsChanged();

        return true;
    }

    void AddWidgets(
        std::initializer_list<std::string> ids, 
        std::initializer_list<std::shared_ptr<Widget>> widgets
    ) {
        if (ids.size() != widgets.size()) {
            throw std::invalid_argument("IDs and Widgets lists must have the same size!");
        }

        auto idsIt     = ids.begin();
        auto widgetsIt = widgets.begin();

        while (idsIt != ids.end() && widgetsIt != widgets.end()) {
            AddWidget(*idsIt, *widgetsIt);
            ++idsIt;
            ++widgetsIt;
        }
    }   

    std::shared_ptr<Widget> GetWidgetById(const std::string& id) {
        auto it = m_widgets.find(id);

        if (it == m_widgets.end()) {
            throw std::out_of_range("Widget with ID " + id + " not found");
        }

        return it->second;
    }
    
protected:
    virtual void OnWidgetsChanged() = 0;
    std::map<std::string, std::shared_ptr<Widget>> m_widgets;
};