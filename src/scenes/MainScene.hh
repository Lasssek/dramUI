#pragma once

#include "../UI/Scene/SceneFactory.hh"
#include "../UI/Components/Button.hh"
#include "../UI/Components/TextLabel.hh"
#include "../UI/Layouts/DynamicLayout.hh"

#include <thread>
#include <format>

class MainMenuScene : public SceneFactory<MainMenuScene> {
private:
    friend class SceneFactory<MainMenuScene>;

    MainMenuScene() = default;

    void OnCreate() override {
        auto layout = WidgetRegister::CreateWidget<DynamicLayout>(
            "mainLayout",
            0, 0,
            Size::MatchParent, Size::MatchParent
        );

        layout->SetHorizontalAlignment(DynamicLayout::Alignment::Center);

        auto button = layout->CreateWidget<Button>(
            "buttonSigma",
            0, 0,
            L"SkiBadi"
        );

        button->SetDynamicSize(Size::MatchContent, Size::MatchContent);

        auto textLabel = layout->CreateWidget<TextLabel>(
            "labelSigma",
            0, 0,
            L"Label"
        );
        textLabel->SetDynamicSize(Size::MatchContent, Size::MatchContent);
        textLabel->SetBorder(BorderType::Square);

        button->SetOnClick([layout]() {
            layout->RemoveWidget("labelSigma");
        });
    }
public:
    void Draw(ConsoleBuffer& buffer) override {
        
        for (auto& [_, widget] : m_widgets) {
            widget->Draw(buffer);
        }
    };

    void HandleEvent(Event& event) override {
        for (auto& [_, widget] : m_widgets) {
            widget->HandleEvent(event);
        }
    };
};