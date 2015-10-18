#ifndef DUSK_UI_UI_MANAGER_HPP
#define DUSK_UI_UI_MANAGER_HPP

#include <Dusk/Tracking/TrackedObject.hpp>
#include <Dusk/Collections/Map.hpp>
#include <Dusk/Graphics/Font.hpp>
#include <Dusk/Graphics/Texture.hpp>
#include <Dusk/UI/UIElement.hpp>
#include <Dusk/UI/UIFrame.hpp>
#include <Dusk/UI/UILabel.hpp>
#include <Dusk/UI/UIInput.hpp>
#include <Dusk/UI/UIButton.hpp>
#include <Dusk/UI/UIFont.hpp>
#include <Dusk/Utility/Types.hpp>
#include <Dusk/Scripting/ScriptHost.hpp>

#include <RapidXML/rapidxml.hpp>
#include <RapidXML/rapidxml_utils.hpp>

namespace dusk
{

class UIManager :
    public TrackedObject
{
public:

    UIManager();
    UIManager(const UIManager&) = delete;
    UIManager& operator=(const UIManager&) = delete;
    virtual ~UIManager();

    virtual inline string GetClassName() const { return "UI Manager"; }

    void OnUpdate(const Event& evt);
    void OnRender(const Event& evt);

    bool LoadFile(const string& filename);

private:

    bool LoadFile(const string& filename, shared_ptr<UIElement>& pParentElement);

    Color ParseColor(rapidxml::xml_node<>* node);
    Vector2f ParseVector2(rapidxml::xml_node<>* node);
    UIState ParseState(const string& state);
    string ParseName(rapidxml::xml_node<>* node, shared_ptr<UIElement>& pParentElement);

    template <typename ElementType>
    shared_ptr<ElementType> ParseElement(rapidxml::xml_node<>* node, shared_ptr<UIElement>& pParentElement, const string& dirname);

    void ParseElementNodes(rapidxml::xml_node<>* root, shared_ptr<UIElement>& pParentElement, const string& dirname);

    UIFont* ParseFont(rapidxml::xml_node<>* node, shared_ptr<UIElement>& pParentElement);
    void ParseFrame(rapidxml::xml_node<>* node, shared_ptr<UIFrame>& pFrame);
    void ParseLabel(rapidxml::xml_node<>* node, shared_ptr<UILabel>& pLabel);
    void ParseInput(rapidxml::xml_node<>* node, shared_ptr<UIInput>& pInput);
    void ParseButton(rapidxml::xml_node<>* node, shared_ptr<UIButton>& pButton);

    unique_ptr<ScriptHost> mp_ScriptHost;
    shared_ptr<UIElement> mp_RootElement;

    Map<string, unique_ptr<Font>> m_Fonts;
    Map<string, unique_ptr<Texture>> m_Textures;
    Map<string, unique_ptr<UIFont>> m_UIFonts;
    Map<string, shared_ptr<UIElement>> m_UIElements;

};

template <typename ElementType>
shared_ptr<ElementType> UIManager::ParseElement(rapidxml::xml_node<>* node, shared_ptr<UIElement>& pParentElement, const string& currentDir)
{
    const string& name = ParseName(node, pParentElement);
    if (name.empty())
        return shared_ptr<ElementType>();

    shared_ptr<ElementType> pElement(New ElementType());
    shared_ptr<UIElement> pGenericElement = dynamic_pointer_cast<UIElement>(pElement);

    if (!pGenericElement)
        return shared_ptr<ElementType>();

    xml_attribute<>* inheritsAttr = node->first_attribute("inherits");
    if (inheritsAttr && m_UIElements.contains_key(inheritsAttr->value()))
    {
        UIElement* pInheritFrom = m_UIElements[inheritsAttr->value()].get();

        if (pInheritFrom)
            pElement->Inherit(pInheritFrom);
    }

    bool isVirtual = false;
    xml_attribute<>* virtualAttr = node->first_attribute("virtual");
    if (virtualAttr)
        isVirtual = (virtualAttr->value() == "true" ? true : false);

    if (!isVirtual && pParentElement)
    {
        pElement->SetParent(pParentElement);
        pParentElement->AddChild(pGenericElement);
    }

    xml_node<>* sizeNode = node->first_node("Size");
    if (sizeNode)
        pElement->SetSize(ParseVector2(sizeNode));

    xml_node<>* posNode = node->first_node("Position");
    if (posNode)
    {
        Vector2f offset = ParseVector2(posNode);
        pElement->SetOffset(offset);

        xml_attribute<>* relToAttr = posNode->first_attribute("relTo");
        xml_attribute<>* relPointAttr = posNode->first_attribute("relPoint");

        if (relToAttr)
        {
            const string& relToVal = relToAttr->value();
            if (!relToVal.empty())
            {
                if (relToVal[0] == '$')
                {
                    if (relToVal == "$parent")
                        pElement->SetRelativeTo(pParentElement);
                }
                else
                {
                    if (m_UIElements.contains_key(relToVal))
                        pElement->SetRelativeTo(m_UIElements[relToVal]);
                }
            }
        }

        if (relPointAttr)
        {
            const string& relPointVal = relPointAttr->value();

            UIRelPoint relPoint;
            if (relPointVal == "TopLeft")
            {
                relPoint = TopLeft;
            }
            else if (relPointVal == "TopRight")
            {
                relPoint = TopRight;
            }
            else if (relPointVal == "BottomLeft")
            {
                relPoint = BottomLeft;
            }
            else if (relPointVal == "BottomRight")
            {
                relPoint = BottomRight;
            }
            pElement->SetRelativePoint(relPoint);
        }
    }

    xml_attribute<>* textAttr = node->first_attribute("text");
    if (textAttr)
        pElement->SetText(textAttr->value());

    for (xml_node<>* fontNode = node->first_node("UseFont"); fontNode; fontNode = fontNode->next_sibling("UseFont"))
    {
        xml_attribute<>* nameAttr = fontNode->first_attribute("name");
        if (!nameAttr)
            continue;

        const string& nameVal = nameAttr->value();
        if (!m_UIFonts.contains_key(nameVal))
            continue;

        UIFont* font = m_UIFonts[nameVal].get();

        UIState state = StateDefault;
        xml_attribute<>* stateAttr = fontNode->first_attribute("state");
        if (stateAttr)
            state = ParseState(stateAttr->value());

        pElement->SetFont(font, state);
    }

    for (xml_node<>* borderNode = node->first_node("Border"); borderNode; borderNode = borderNode->next_sibling("Border"))
    {
        UIState state = StateDefault;
        xml_attribute<>* stateAttr = borderNode->first_attribute("state");
        if (stateAttr)
            state = ParseState(stateAttr->value());

        float size = 1;
        xml_attribute<>* sizeAttr = borderNode->first_attribute("size");
        if (sizeAttr)
            size = std::stof(sizeAttr->value());
        pElement->SetBorderSize(size, state);

        xml_node<>* colorNode = borderNode->first_node("Color");
        Color color = Color::Black;
        if (colorNode)
            color = ParseColor(colorNode);

        pElement->SetBorderColor(color, state);
    }

    xml_node<>* childrenNode = node->first_node("Children");
    if (childrenNode)
        ParseElementNodes(childrenNode, pParentElement, currentDir);

    m_UIElements[name] = pGenericElement;
    return pElement;
}

} // namespace dusk

#endif // DUSK_UI_UI_MANAGER_HPP