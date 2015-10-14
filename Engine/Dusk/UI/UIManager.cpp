#include "UIManager.hpp"

#include <Dusk/Program.hpp>
#include <Dusk/Graphics/GraphicsSystem.hpp>
#include <Dusk/Logging/Logging.hpp>
#include <Dusk/Utility/Strings.hpp>

#include <cfloat>

using namespace rapidxml;

namespace dusk
{

UIManager::UIManager() :
    m_Fonts(),
    m_UIFonts(),
    m_UIElements(),
    m_RootElement(nullptr)
{ }

bool UIManager::Init()
{
    m_Fonts.clear();
    m_UIFonts.clear();
    m_UIElements.clear();
    m_RootElement = shared_ptr<UIElement>(New UIElement());
    m_ScriptHost = unique_ptr<ScriptHost>(New ScriptHost());
    m_ScriptHost->Init();

    m_RootElement->Init();
    m_RootElement->SetSize((Vector2f)Program::Inst()->GetGraphicsSystem()->GetWindowSize());

    Program::Inst()->AddEventListener(Program::EvtUpdate, this, &UIManager::OnUpdate);
    Program::Inst()->AddEventListener(Program::EvtRender, this, &UIManager::OnRender);

    return true;
}

void UIManager::Term()
{
    m_Fonts.clear();
    m_Fonts.clear();
    m_UIFonts.clear();
    m_UIElements.clear();
    m_RootElement = nullptr;
    m_ScriptHost = nullptr;

    Program::Inst()->RemoveEventListener(Program::EvtUpdate, this, &UIManager::OnUpdate);
    Program::Inst()->RemoveEventListener(Program::EvtRender, this, &UIManager::OnRender);
}

void UIManager::OnUpdate(const Event& evt)
{
    m_RootElement->OnUpdate(evt);
}

void UIManager::OnRender(const Event& evt)
{
    m_RootElement->OnRender(evt);
}

bool UIManager::LoadFile(const string& filename)
{
    return LoadFile(filename, m_RootElement);
}

bool UIManager::LoadFile(const string& filename, shared_ptr<UIElement>& pParentElement)
{
    string dirname = Dirname(filename);
    if (dirname == filename)
        dirname = "";
    else
        dirname += "/";

    rapidxml::file<> xmlFile(filename.c_str());
    rapidxml::xml_document<> dom;
    dom.parse<0>(xmlFile.data());

    xml_node<>* root = dom.first_node("DuskUI");

    if (!root)
        return false;

    for (xml_node<>* node = root->first_node("Include"); node; node = node->next_sibling("Include"))
    {
        xml_attribute<>* fileAttr = node->first_attribute("file");
        if (!fileAttr)
            continue;

        const string& fileVal = fileAttr->value();
        LoadFile(dirname + fileVal, pParentElement);
    }

    for (xml_node<>* node = root->first_node("Script"); node; node = node->next_sibling("Script"))
    {
        xml_attribute<>* fileAttr = node->first_attribute("file");
        if (!fileAttr)
            continue;

        const string& fileVal = fileAttr->value();
        m_ScriptHost->RunFile(dirname + fileVal);
    }

    for (xml_node<>* node = root->first_node("Font"); node; node = node->next_sibling("Font"))
        ParseFont(node);

    ParseElementNodes(root, pParentElement, dirname);

    return true;
}

Color UIManager::ParseColor(rapidxml::xml_node<>* node)
{
    xml_attribute<>* rAttr = node->first_attribute("r");
    xml_attribute<>* gAttr = node->first_attribute("g");
    xml_attribute<>* bAttr = node->first_attribute("b");
    xml_attribute<>* aAttr = node->first_attribute("a");

    if (!rAttr && !gAttr && !bAttr)
    {
        return Color::Transparent;
    }

    const string& rVal = rAttr->value();
    const string& gVal = gAttr->value();
    const string& bVal = bAttr->value();

    Color color = Color(0, 0, 0, 255);
    color.r = std::stoi(rVal);
    color.g = std::stoi(gVal);
    color.b = std::stoi(bVal);

    if (aAttr)
    {
        const string& aVal = aAttr->value();
        color.a = std::stoi(aVal);
    }

    return color;
}

dusk::Vector2f UIManager::ParseVector2(rapidxml::xml_node<>* node)
{
    xml_attribute<>* xAttr = node->first_attribute("x");
    xml_attribute<>* yAttr = node->first_attribute("y");

    Vector2f value;

    if (xAttr && yAttr)
    {
        const string& xVal = xAttr->value();
        const string& yVal = yAttr->value();

        if (!xVal.empty() && !xVal.empty())
        {
            if (xVal[0] == '$')
            {
                if (xVal == "$min")
                    value.x = FLT_MIN;
                else if (xVal == "$max")
                    value.x = FLT_MAX;
            }
            else
                value.x = stof(xVal);
        }

        if (!yVal.empty() && !yVal.empty())
        {
            if (yVal[0] == '$')
            {
                if (yVal == "$min")
                    value.y = FLT_MIN;
                else if (yVal == "$max")
                    value.y = FLT_MAX;
            }
            else
                value.y = stof(yVal);
        }
    }

    return value;
}

dusk::UIState UIManager::ParseState(const string& state)
{
    if (state == "active")
    {
        return StateActive;
    }
    else if (state == "hover")
    {
        return StateHover;
    }
    else if (state == "disabled")
    {
        return StateDisabled;
    }

    return StateDefault;
}

void UIManager::ParseElementNodes(rapidxml::xml_node<>* root, shared_ptr<UIElement>& pParentElement, const string& dirname)
{
    for (xml_node<>* node = root->first_node(); node; node = node->next_sibling())
    {
        string nodeName = node->name();
        if (nodeName == "Include")
        {
            xml_attribute<>* fileAttr = node->first_attribute("file");
            if (!fileAttr)
                continue;

            const string& fileVal = fileAttr->value();
            LoadFile(dirname + fileVal, pParentElement);
        }
        else if (nodeName == "Element")
        {
            ParseElement<UIElement>(node, pParentElement, dirname);
        }
        else if (nodeName == "Frame")
        {
            shared_ptr<UIFrame> pElement = ParseElement<UIFrame>(node, pParentElement, dirname);
            ParseFrame(node, pElement);
        }
        else if (nodeName == "Label")
        {
            shared_ptr<UILabel> pElement = ParseElement<UILabel>(node, pParentElement, dirname);
            ParseLabel(node, pElement);
        }
        else if (nodeName == "Button")
        {
            shared_ptr<UIButton> pElement = ParseElement<UIButton>(node, pParentElement, dirname);
            ParseButton(node, pElement);
        }
        else if (nodeName == "Input")
        {
            shared_ptr<UIInput> pElement = ParseElement<UIInput>(node, pParentElement, dirname);
            ParseInput(node, pElement);
        }
    }
}

shared_ptr<UIFont> UIManager::ParseFont(xml_node<>* node)
{
    xml_attribute<>* nameAttr = node->first_attribute("name");
    xml_attribute<>* fileAttr = node->first_attribute("file");
    xml_attribute<>* inheritsAttr = node->first_attribute("inherits");
    xml_attribute<>* sizeAttr = node->first_attribute("size");

    xml_node<>* colorNode = node->first_node("Color");

    shared_ptr<UIFont> pFontElement(New UIFont());

    if (inheritsAttr)
    {
        const string& inheritsVal = inheritsAttr->value();
        shared_ptr<UIFont> pInheritFrom = m_UIFonts[inheritsVal];

        if (pInheritFrom != nullptr)
        {
            if (!pFontElement->Init(pInheritFrom))
                return nullptr;
        }
    }
    else
    {
        if (!pFontElement->Init())
            return nullptr;
    }

    if (fileAttr)
    {
        const string& fileVal = fileAttr->value();
        if (m_Fonts.contains_key(fileVal))
        {
            pFontElement->SetFont(m_Fonts[fileVal]);
        }
        else
        {
            shared_ptr<Font> pFont(New Font());

            if (!pFont->Load(fileVal))
                return nullptr;

            pFontElement->SetFont(pFont);
            m_Fonts.add(fileVal, pFont);
        }
    }

    if (sizeAttr)
    {
        const string& sizeVal = sizeAttr->value();
        size_t size = std::stoi(sizeVal);
        pFontElement->SetFontSize(size);
    }

    if (colorNode)
    {
        Color color = ParseColor(colorNode);
        pFontElement->SetColor(color);
    }

    if (nameAttr)
    {
        const string& nameVal = nameAttr->value();
        m_UIFonts.add(nameVal, pFontElement);

        return pFontElement;
    }

    return nullptr;
}

void UIManager::ParseFrame(rapidxml::xml_node<>* node, shared_ptr<UIFrame>& pElement)
{

}

void UIManager::ParseLabel(rapidxml::xml_node<>* node, shared_ptr<UILabel>& pElement)
{
}

void UIManager::ParseInput(rapidxml::xml_node<>* node, shared_ptr<UIInput>& pElement)
{
    pElement->SetText("100");
}

void UIManager::ParseButton(rapidxml::xml_node<>* node, shared_ptr<UIButton>& pElement)
{
    shared_ptr<UIElement> pGenericElement = dynamic_pointer_cast<UIElement>(pElement);
}

void UIManager::ParseElementName(rapidxml::xml_node<>* node, shared_ptr<UIElement>& pElement, shared_ptr<UIElement>& pParentElement, const string& dirname)
{
    xml_attribute<>* nameAttr = node->first_attribute("name");

    if (nameAttr)
    {
        const string& nameVal = nameAttr->value();
        pElement->SetName(nameVal);
        m_UIElements.add(nameVal, pElement);
    }
}

void UIManager::ParseElementVirtual(rapidxml::xml_node<>* node, shared_ptr<UIElement>& pElement, shared_ptr<UIElement>& pParentElement, const string& dirname)
{
    xml_attribute<>* virtualAttr = node->first_attribute("virtual");

    bool isVirtual = false;
    if (virtualAttr)
    {
        const string& virtualVal = virtualAttr->value();
        isVirtual = (virtualVal == "true" ? true : false);
    }

    if (!isVirtual && pParentElement)
    {
        pElement->SetParent(pParentElement);
        pParentElement->AddChild(pElement);
    }
}

void UIManager::ParseElementSize(rapidxml::xml_node<>* node, shared_ptr<UIElement>& pElement, shared_ptr<UIElement>& pParentElement, const string& dirname)
{
    xml_node<>* sizeNode = node->first_node("Size");

    if (sizeNode)
    {
        Vector2f size = ParseVector2(sizeNode);
        pElement->SetSize(size);
    }
}

void UIManager::ParseElementPosition(rapidxml::xml_node<>* node, shared_ptr<UIElement>& pElement, shared_ptr<UIElement>& pParentElement, const string& dirname)
{
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
}

void UIManager::ParseElementText(rapidxml::xml_node<>* node, shared_ptr<UIElement>& pElement, shared_ptr<UIElement>& pParentElement, const string& dirname)
{
    xml_attribute<>* textAttr = node->first_attribute("text");

    if (textAttr)
    {
        const string& textVal = textAttr->value();
        pElement->SetText(textVal);
    }
}

void UIManager::ParseElementFont(rapidxml::xml_node<>* node, shared_ptr<UIElement>& pElement, shared_ptr<UIElement>& pParentElement, const string& dirname)
{
    for (xml_node<>* fontNode = node->first_node("UseFont"); fontNode; fontNode = fontNode->next_sibling("UseFont"))
    {
        xml_attribute<>* nameAttr = fontNode->first_attribute("name");
        xml_attribute<>* stateAttr = fontNode->first_attribute("state");

        if (!nameAttr)
            continue;

        const string& nameVal = nameAttr->value();
        if (!m_UIFonts.contains_key(nameVal))
            continue;

        shared_ptr<UIFont> font = m_UIFonts[nameVal];

        UIState state = StateDefault;
        if (stateAttr)
        {
            const string& stateVal = stateAttr->value();
            state = ParseState(stateVal);
        }

        pElement->SetFont(font, state);
    }
}

void UIManager::ParseElementBorder(rapidxml::xml_node<>* node, shared_ptr<UIElement>& pElement, shared_ptr<UIElement>& pParentElement, const string& dirname)
{
    for (xml_node<>* borderNode = node->first_node("Border"); borderNode; borderNode = borderNode->next_sibling("Border"))
    {
        xml_attribute<>* stateAttr = borderNode->first_attribute("state");

        UIState state = StateDefault;
        if (stateAttr)
        {
            const string& stateVal = stateAttr->value();

            if (stateVal == "default")
            {
                state = StateDefault;
            }
            else if (stateVal == "active")
            {
                state = StateActive;
            }
            else if (stateVal == "hover")
            {
                state = StateHover;
            }
            else if (stateVal == "disabled")
            {
                state = StateDisabled;
            }
        }

        xml_attribute<>* sizeAttr = borderNode->first_attribute("size");

        size_t size = 1;
        if (sizeAttr)
        {
            const string& sizeVal = sizeAttr->value();
            size = std::stoi(sizeVal);
        }
        pElement->SetBorderSize(size, state);

        xml_node<>* colorNode = borderNode->first_node("Color");
        Color color = Color::Black;
        if (colorNode)
        {
            color = ParseColor(colorNode);
        }

        pElement->SetBorderColor(color, state);
    }
}

} // namespace dusk
