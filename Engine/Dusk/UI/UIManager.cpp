#include "UIManager.hpp"

#include <Dusk/Program.hpp>
#include <Dusk/Graphics/GraphicsSystem.hpp>
#include <Dusk/Logging/Logging.hpp>
#include <Dusk/Utility/Strings.hpp>

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
            ParseElement<UIFrame>(node, pParentElement, dirname);
        }
        else if (nodeName == "Label")
        {
            ParseElement<UILabel>(node, pParentElement, dirname);
        }
        else if (nodeName == "Button")
        {
            ParseElement<UIButton>(node, pParentElement, dirname);
        }
        else if (nodeName == "Input")
        {
            ParseElement<UIInput>(node, pParentElement, dirname);
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

} // namespace dusk