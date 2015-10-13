#ifndef DUSK_UI_UI_MANAGER_HPP
#define DUSK_UI_UI_MANAGER_HPP

#include <Dusk/Tracking/TrackedObject.hpp>
#include <Dusk/Collections/Map.hpp>
#include <Dusk/Graphics/Font.hpp>
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
    virtual ~UIManager() { Term(); }

    virtual inline string GetClassName() const { return "UI Manager"; }

    bool Init();
    void Term();

    void OnUpdate(const Event& evt);
    void OnRender(const Event& evt);

    bool LoadFile(const string& filename);

private:

    bool LoadFile(const string& filename, shared_ptr<UIElement>& pParentElement);

    Color ParseColor(rapidxml::xml_node<>* node);
    Vector2f ParseVector2(rapidxml::xml_node<>* node);

    template <typename ElementType>
    shared_ptr<ElementType> ParseElement(rapidxml::xml_node<>* node, shared_ptr<UIElement>& pParentElement, const string& dirname);

    void ParseElementNodes(rapidxml::xml_node<>* root, shared_ptr<UIElement>& pParentElement, const string& dirname);

    shared_ptr<UIFont> ParseFont(rapidxml::xml_node<>* node);
    shared_ptr<UIFrame> ParseFrame(rapidxml::xml_node<>* node);
    shared_ptr<UILabel> ParseLabel(rapidxml::xml_node<>* node);
    shared_ptr<UIInput> ParseInput(rapidxml::xml_node<>* node);
    shared_ptr<UIButton> ParseButton(rapidxml::xml_node<>* node);

    unique_ptr<ScriptHost> m_ScriptHost;

    shared_ptr<UIElement> m_RootElement;

    Map<string, shared_ptr<Font>> m_Fonts;
    //Map<string, shared_ptr<Texture>> m_Textures;

    Map<string, shared_ptr<UIFont>> m_UIFonts;
    Map<string, shared_ptr<UIElement>> m_UIElements;
    //Map<string, shared_ptr<UIFrame>> m_UIFrames;

};

template <typename ElementType>
shared_ptr<ElementType> UIManager::ParseElement(rapidxml::xml_node<>* node, shared_ptr<UIElement>& pParentElement, const string& dirname)
{
    xml_attribute<>* nameAttr = node->first_attribute("name");
    xml_attribute<>* virtualAttr = node->first_attribute("virtual");
    xml_attribute<>* inheritsAttr = node->first_attribute("inherits");

    xml_node<>* sizeNode = node->first_node("Size");
    xml_node<>* posNode = node->first_node("Position");
    xml_node<>* childrenNode = node->first_node("Children");

    shared_ptr<ElementType> pElement(New ElementType());
    shared_ptr<UIElement> pGenericElement = dynamic_pointer_cast<UIElement>(pElement);

    if (inheritsAttr)
    {
        const string& inheritsVal = inheritsAttr->value();
        shared_ptr<ElementType> pInheritFrom = dynamic_pointer_cast<ElementType>(m_UIElements[inheritsVal]);

        if (pInheritFrom != nullptr)
        {
            if (!pElement->Init(pInheritFrom))
                return nullptr;
        }
    }
    else
    {
        if (!pElement->Init())
            return nullptr;
    }

    bool isVirtual = false;
    if (virtualAttr)
    {
        const string& virtualVal = virtualAttr->value();
        isVirtual = (virtualVal == "true" ? true : false);
    }

    if (!isVirtual && pParentElement)
    {
        pElement->SetParent(pParentElement);
        pParentElement->AddChild(pGenericElement);
    }

    if (nameAttr)
    {
        const string& nameVal = nameAttr->value();
        pElement->SetName(nameVal);
        m_UIElements.add(nameVal, pElement);
    }

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

    if (sizeNode)
    {
        Vector2f size = ParseVector2(sizeNode);
        pElement->SetSize(size);
    }

    if (childrenNode)
    {
        ParseElementNodes(childrenNode, pParentElement, dirname);
    }

    return pElement;
}

} // namespace dusk

#endif // DUSK_UI_UI_MANAGER_HPP