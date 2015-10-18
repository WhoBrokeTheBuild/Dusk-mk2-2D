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
    mp_RootElement(New UIElement),
    mp_ScriptHost(New ScriptHost),
    m_Fonts(),
    m_Textures(),
    m_UIFonts(),
    m_UIElements()
{
    mp_RootElement->SetSize((Vector2f)Program::Inst()->GetGraphicsSystem()->GetWindowSize());

    Program::Inst()->AddEventListener(Program::EvtUpdate, this, &UIManager::OnUpdate);
    Program::Inst()->AddEventListener(Program::EvtRender, this, &UIManager::OnRender);
}

UIManager::~UIManager()
{
}

void UIManager::OnUpdate(const Event& evt)
{
    mp_RootElement->OnUpdate(evt);
}

void UIManager::OnRender(const Event& evt)
{
    mp_RootElement->OnRender(evt);
}

bool UIManager::LoadFile(const string& filename)
{
    return LoadFile(filename, mp_RootElement);
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
        mp_ScriptHost->RunFile(dirname + fileVal);
    }

    for (xml_node<>* node = root->first_node("Font"); node; node = node->next_sibling("Font"))
        ParseFont(node, pParentElement);

    //for (xml_node<>* node = root->first_node("Texture"); node; node = node->next_sibling("Texture"))
    //    ParseTexture(node);

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

string UIManager::ParseName(rapidxml::xml_node<>* node, shared_ptr<UIElement>& pParentElement)
{
    xml_attribute<>* nameAttr = node->first_attribute("name");
    if (nameAttr)
        return nameAttr->value();
    return "";
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
            shared_ptr<UIFrame>& pElement = ParseElement<UIFrame>(node, pParentElement, dirname);
            ParseFrame(node, pElement);
        }
        else if (nodeName == "Label")
        {
            shared_ptr<UILabel>& pElement = ParseElement<UILabel>(node, pParentElement, dirname);
            ParseLabel(node, pElement);
        }
        else if (nodeName == "Button")
        {
            shared_ptr<UIButton>& pElement = ParseElement<UIButton>(node, pParentElement, dirname);
            ParseButton(node, pElement);
        }
        else if (nodeName == "Input")
        {
            shared_ptr<UIInput>& pElement = ParseElement<UIInput>(node, pParentElement, dirname);
            ParseInput(node, pElement);
        }
    }
}

UIFont* UIManager::ParseFont(xml_node<>* node, shared_ptr<UIElement>& pParentElement)
{
    const string& name = ParseName(node, pParentElement);
    if (name.empty())
        return nullptr;

    UIFont* pUIFont = New UIFont();

    xml_attribute<>* fileAttr = node->first_attribute("file");
    if (fileAttr)
    {
        const string& fileVal = fileAttr->value();
        if (m_Fonts.contains_key(fileVal))
        {
            pUIFont->SetFont(m_Fonts[fileVal].get());
        }
        else
        {
            Font* pFont = New Font();

            if (!pFont->Load(fileVal))
            {
                delete pFont;
                delete pUIFont;
                return nullptr;
            }

            m_Fonts[fileVal] = std::move(unique_ptr<Font>(pFont));
            pUIFont->SetFont(pFont);
        }
    }

    xml_attribute<>* inheritsAttr = node->first_attribute("inherits");
    if (inheritsAttr && m_UIFonts.contains_key(inheritsAttr->value()))
    {
        UIFont* pInheritFrom = m_UIFonts[inheritsAttr->value()].get();

        if (pInheritFrom)
            pUIFont->Inherit(pInheritFrom);
    }

    xml_attribute<>* sizeAttr = node->first_attribute("size");
    if (sizeAttr)
    {
        const string& sizeVal = sizeAttr->value();
        pUIFont->SetFontSize(std::stoi(sizeVal));
    }

    xml_node<>* colorNode = node->first_node("Color");
    if (colorNode)
    {
        pUIFont->SetColor(ParseColor(colorNode));
    }

    m_UIFonts[name] = std::move(unique_ptr<UIFont>(pUIFont));
    return nullptr;
}

void UIManager::ParseFrame(rapidxml::xml_node<>* node, shared_ptr<UIFrame>& pFrame)
{

}

void UIManager::ParseLabel(rapidxml::xml_node<>* node, shared_ptr<UILabel>& pLabel)
{
}

void UIManager::ParseInput(rapidxml::xml_node<>* node, shared_ptr<UIInput>& pInput)
{
    pInput->SetText("100");
}

void UIManager::ParseButton(rapidxml::xml_node<>* node, shared_ptr<UIButton>& pButton)
{
}

} // namespace dusk
