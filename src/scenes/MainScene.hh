#pragma once

#include "../UI/Scene/Scene.hh"
#include "../UI/Components/Button.hh"
#include "../UI/Components/TextLabel.hh"
#include "../UI/Layouts/DynamicLayout.hh"

#include <format>

class MainMenuScene : public Scene {
public:
    MainMenuScene() = default;

    void OnCreate() {
        if (m_created) return;

        auto mainLayout = std::make_shared<DynamicLayout>(
            shared_from_this(),
            0, 0,
            Size::MatchParent, Size::MatchParent,
            2,
            DynamicLayout::LayoutMode::Horizontal
        );

        mainLayout->SetHorizontalAlignment(DynamicLayout::Alignment::Center);
        mainLayout->SetVerticalAlignment(DynamicLayout::Alignment::Center);

        for (int i = 0; i < 3; ++i) {
            CreateLayoutRow(mainLayout, "Hejka", "Naklejka", "Cwel", "Jebany");
        }

        AddWidget(mainLayout);

        mainLayout->UpdateHierarchy();
        m_created = true;
    }

    void Draw(ConsoleBuffer& buffer) override {
        for (auto& widget : m_widgets) {
            widget->Draw(buffer);
        }
    };

    void HandleEvent(Event& event) override {
        for (auto& widget : m_widgets) {
            widget->HandleEvent(event);
        }
    };
private:
    void CreateLayoutRow(
        std::shared_ptr<DynamicLayout> parent,
        std::string_view firstText,
        std::string_view secondText,
        std::string_view thirdText,
        std::string_view fourthText
    ) {
        auto layout = parent->CreateWidget<DynamicLayout>(
            0, 0,
            Size::MatchContent, Size::MatchContent,
            1
        );

        auto text1 = layout->CreateWidget<TextLabel>(
            0, 0,
            firstText
        );
        text1->SetDynamicSize(Size::MatchContent, Size::MatchContent);

        auto text2 = layout->CreateWidget<TextLabel>(
            0, 0,
            secondText
        );
        text2->SetDynamicSize(Size::MatchContent, Size::MatchContent);

        auto text3 = layout->CreateWidget<TextLabel>(
            0, 0,
            thirdText
        );
        text3->SetDynamicSize(Size::MatchContent, Size::MatchContent);

        auto text4 = layout->CreateWidget<TextLabel>(
            0, 0,
            fourthText
        );
        text4->SetDynamicSize(Size::MatchContent, Size::MatchContent);
    }

    bool m_created = false;
};