#pragma once

#include "Blueprint/WidgetTree.h"
#include "Presentation/CFMagritteBinding.h"
#include "Presentation/CFMenu.h"

/** A tab presentation over the immediate descriptions in a Magritte container. */
class FCFHorizontalMenuBuilder final : private magritte::Visitor
{
public:
    static UCFMenu* Build(UWidgetTree& Tree, const magritte::Description& Container,
        UCFMenuTheme* Theme, const std::string& SelectedId,
        TArray<const magritte::Description*>& OutDescriptions)
    {
        auto* Menu = Tree.ConstructWidget<UCFMenu>();
        Menu->Theme = Theme;
        OutDescriptions.Reset();
        FCFHorizontalMenuBuilder Builder(Tree, *Menu, OutDescriptions);
        for (const auto& Child : Container.orderedChildren())
        {
            Builder.visit(*Child);
        }

        const int32 Selected = OutDescriptions.IndexOfByPredicate([&SelectedId](const auto* Description) {
            return Description->id == SelectedId;
        });
        Menu->InitialSelectedIndex = Selected == INDEX_NONE ? 0 : Selected;
        return Menu;
    }

private:
    FCFHorizontalMenuBuilder(UWidgetTree& InTree, UCFMenu& InMenu,
        TArray<const magritte::Description*>& InDescriptions)
        : Tree(InTree), Menu(InMenu), Descriptions(InDescriptions)
    {
    }

    void visitToOneRelationDescription(magritte::Description& Description) override
    {
        if (!Description.flag("visible"))
        {
            return;
        }

        auto* Item = Tree.ConstructWidget<UCFMenuItem>();
        const auto Label = Description.property("label");
        if (const auto* Text = std::get_if<std::string>(&Label.data))
        {
            Item->SetLabel(FText::FromString(UTF8_TO_TCHAR(Text->c_str())));
        }
        const auto Icon = Description.property("metadata:cfIcon");
        if (const auto* Symbol = std::get_if<magritte::Value::Symbol>(&Icon.data))
        {
            if (const auto* Brush = Menu.GetMenuTheme().Icons.Find(FName(UTF8_TO_TCHAR(Symbol->utf8.c_str()))))
            {
                Item->SetIcon(*Brush);
            }
        }
        Menu.AddChild(Item);
        Descriptions.Add(&Description);
    }

    UWidgetTree& Tree;
    UCFMenu& Menu;
    TArray<const magritte::Description*>& Descriptions;
};
