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
    mp_RootElement->SetUIManager(this);

    Program::Inst()->AddEventListener(Program::EvtUpdate, this, &UIManager::OnUpdate);
    Program::Inst()->AddEventListener(Program::EvtRender, this, &UIManager::OnRender);

    Program::Inst()->GetGraphicsSystem()->AddEventListener(GraphicsSystem::EvtWindowResize, this, &UIManager::OnWindowResize);
    Program::Inst()->GetInputSystem()->AddEventListener(InputSystem::EvtMouseMove, this, &UIManager::OnMouseMove);
    Program::Inst()->GetInputSystem()->AddEventListener(InputSystem::EvtMouseButtonPress, this, &UIManager::OnMouseButtonPress);
    Program::Inst()->GetInputSystem()->AddEventListener(InputSystem::EvtMouseButtonRelease, this, &UIManager::OnMouseButtonRelease);
}

UIManager::~UIManager()
{
    Program::Inst()->GetInputSystem()->RemoveEventListener(InputSystem::EvtMouseButtonRelease, this, &UIManager::OnMouseButtonRelease);
    Program::Inst()->GetInputSystem()->RemoveEventListener(InputSystem::EvtMouseButtonPress, this, &UIManager::OnMouseButtonPress);
    Program::Inst()->GetInputSystem()->RemoveEventListener(InputSystem::EvtMouseMove, this, &UIManager::OnMouseMove);
    Program::Inst()->GetGraphicsSystem()->RemoveEventListener(GraphicsSystem::EvtWindowResize, this, &UIManager::OnWindowResize);

    Program::Inst()->RemoveEventListener(Program::EvtRender, this, &UIManager::OnRender);
    Program::Inst()->RemoveEventListener(Program::EvtUpdate, this, &UIManager::OnUpdate);
}

void UIManager::OnUpdate(const Event& evt)
{
    mp_RootElement->OnUpdate(evt);
}

void UIManager::OnRender(const Event& evt)
{
    mp_RootElement->OnRender(evt);
}

void UIManager::OnWindowResize(const Event& evt)
{
    auto pData = evt.GetDataAs<WindowResizeEventData>();
    mp_RootElement->SetSize((Vector2f)pData->GetSize());
}

void UIManager::OnMouseMove(const Event& evt)
{
    mp_RootElement->OnMouseMove(evt);
}

void UIManager::OnMouseButtonPress(const Event& evt)
{
    mp_RootElement->OnMouseButtonPress(evt);
}

void UIManager::OnMouseButtonRelease(const Event& evt)
{
    mp_RootElement->OnMouseButtonRelease(evt);
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

void UIManager::ParseBindings(rapidxml::xml_node<>* node, shared_ptr<UIElement>& pElement, const string& nodeName, const EventID& eventId)
{
    for (xml_node<>* bindNode = node->first_node(nodeName.c_str()); bindNode; bindNode = bindNode->next_sibling(nodeName.c_str()))
    {
        xml_attribute<>* funcAttr = bindNode->first_attribute("func");
        if (!funcAttr)
            continue;

        const string& funcName = funcAttr->value();
        pElement->AddEventListener(eventId, mp_ScriptHost.get(), funcName);
    }
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
            shared_ptr<UIElement> pElement(New UIElement);
            ParseElement(node, pElement, pParentElement, dirname);
        }
        else if (nodeName == "Frame")
        {
            shared_ptr<UIFrame> pElement(New UIFrame);
            shared_ptr<UIElement> pGenericElement = dynamic_pointer_cast<UIElement>(pElement);
            if (ParseElement(node, pGenericElement, pParentElement, dirname))
            {
                ParseFrame(node, pElement);
            }
        }
        else if (nodeName == "Label")
        {
            shared_ptr<UILabel> pElement(New UILabel);
            shared_ptr<UIElement> pGenericElement = dynamic_pointer_cast<UIElement>(pElement);
            if (ParseElement(node, pGenericElement, pParentElement, dirname))
            {
                ParseLabel(node, pElement);
            }
        }
        else if (nodeName == "Button")
        {
            shared_ptr<UIButton> pElement(New UIButton);
            shared_ptr<UIElement> pGenericElement = dynamic_pointer_cast<UIElement>(pElement);
            if (ParseElement(node, pGenericElement, pParentElement, dirname))
            {
                ParseButton(node, pElement);
            }
        }
        else if (nodeName == "Input")
        {
            shared_ptr<UIInput> pElement(New UIInput);
            shared_ptr<UIElement> pGenericElement = dynamic_pointer_cast<UIElement>(pElement);
            if (ParseElement(node, pGenericElement, pParentElement, dirname))
            {
                ParseInput(node, pElement);
            }
        }
        else if (nodeName == "RenderFrame")
        {
            xml_attribute<>* typeAttr = node->first_attribute("type");
            if (typeAttr)
            {
                const string& type = typeAttr->value();
                if (m_RenderFrameTypes.contains_key(type))
                {
                    shared_ptr<UIElement> pGenericElement = m_RenderFrameTypes[type]();
                    if (ParseElement(node, pGenericElement, pParentElement, dirname))
                    {
                        // Extra Loading Stuff
                    }
                }
            }
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

bool UIManager::ParseElement(rapidxml::xml_node<>* node, shared_ptr<UIElement>& pElement, shared_ptr<UIElement>& pParentElement, const string& currentDir)
{
    const string& name = ParseName(node, pParentElement);
    if (name.empty())
        return false;

    if (!pElement)
        return false;

    pElement->SetUIManager(this);
    pElement->SetName(name);

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
        isVirtual = (string(virtualAttr->value()) == "true" ? true : false);

    if (!isVirtual && pParentElement)
    {
        pElement->SetParent(pParentElement);
        pParentElement->AddChild(pElement);
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

    for (xml_node<>* backgroundNode = node->first_node("Background"); backgroundNode; backgroundNode = backgroundNode->next_sibling("Background"))
    {
        UIState state = StateDefault;
        xml_attribute<>* stateAttr = backgroundNode->first_attribute("state");
        if (stateAttr)
            state = ParseState(stateAttr->value());

        xml_node<>* bgColorNode = backgroundNode->first_node("Color");
        pElement->SetBackgroundColor(ParseColor(bgColorNode), state);
    }

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

    xml_node<>* bindingsNode = node->first_node("Bindings");
    if (bindingsNode)
    {
        ParseBindings(bindingsNode, pElement, "OnUpdate", UIElement::EvtUpdate);
        ParseBindings(bindingsNode, pElement, "OnRender", UIElement::EvtRender);
        ParseBindings(bindingsNode, pElement, "OnShow", UIElement::EvtShow);
        ParseBindings(bindingsNode, pElement, "OnHide", UIElement::EvtHide);
        ParseBindings(bindingsNode, pElement, "OnActivate", UIElement::EvtActivate);
        ParseBindings(bindingsNode, pElement, "OnDeactivate", UIElement::EvtDeactivate);
        ParseBindings(bindingsNode, pElement, "OnMouseEnter", UIElement::EvtMouseEnter);
        ParseBindings(bindingsNode, pElement, "OnMouseLeave", UIElement::EvtMouseLeave);
        ParseBindings(bindingsNode, pElement, "OnMouseDown", UIElement::EvtMouseDown);
        ParseBindings(bindingsNode, pElement, "OnMouseUp", UIElement::EvtMouseUp);
        ParseBindings(bindingsNode, pElement, "OnFocus", UIElement::EvtFocus);
        ParseBindings(bindingsNode, pElement, "OnBlur", UIElement::EvtBlur);
        ParseBindings(bindingsNode, pElement, "OnClick", UIElement::EvtClick);
        ParseBindings(bindingsNode, pElement, "OnChange", UIElement::EvtChange);
    }

    xml_node<>* childrenNode = node->first_node("Children");
    if (childrenNode)
        ParseElementNodes(childrenNode, pParentElement, currentDir);

    m_UIElements[name] = pElement;
    return true;
}

void UIManager::ParseFrame(rapidxml::xml_node<>* node, shared_ptr<UIFrame>& pFrame)
{

}

void UIManager::ParseLabel(rapidxml::xml_node<>* node, shared_ptr<UILabel>& pLabel)
{
    xml_attribute<>* targetAttr = node->first_attribute("target");
    if (targetAttr)
    {
        weak_ptr<UIElement> pTarget = m_UIElements[targetAttr->value()];

        if (!pTarget.expired())
            pLabel->SetTarget(pTarget);
    }
}

void UIManager::ParseInput(rapidxml::xml_node<>* node, shared_ptr<UIInput>& pInput)
{
    xml_attribute<>* maxLenAttr = node->first_attribute("maxLength");
    if (maxLenAttr)
    {
        const string& maxLenStr = maxLenAttr->value();
        size_t maxLen = std::stoull(maxLenStr);
        pInput->SetMaxLength(maxLen);
    }

    xml_attribute<>* typeAttr = node->first_attribute("type");
    if (typeAttr)
    {
        const string& type = typeAttr->value();
        if (type == "text")
        {
            pInput->SetType(UIInput::TypeText);
        }
        else if (type == "int")
        {
            pInput->SetType(UIInput::TypeInt);
        }
        else if (type == "float")
        {
            pInput->SetType(UIInput::TypeFloat);
        }
    }
}

void UIManager::ParseButton(rapidxml::xml_node<>* node, shared_ptr<UIButton>& pButton)
{
}

} // namespace dusk
