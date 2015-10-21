#include "UIInput.hpp"

#include <Dusk/Program.hpp>
#include <Dusk/Input/InputSystem.hpp>
#include <Dusk/Logging/Logging.hpp>

namespace dusk
{

UIInput::UIInput()
{
    Program::Inst()->GetInputSystem()->AddEventListener(InputSystem::EvtTextInput, this, &UIInput::OnTextInput);
}


UIInput::~UIInput()
{
    Program::Inst()->GetInputSystem()->RemoveEventListener(InputSystem::EvtTextInput, this, &UIInput::OnTextInput);
}

void UIInput::Inherit(const UIElement* pInheritFrom)
{
    UIElement::Inherit(pInheritFrom);
    const UIInput* pInheritFromInput = dynamic_cast<const UIInput*>(pInheritFrom);
    if (pInheritFromInput)
    {

    }
}

void UIInput::Focus()
{
    UIElement::Focus();
    ApplyCursor();
}

void UIInput::Blur()
{
    UIElement::Blur();
    ChangeState(StateDefault);
    ApplyCursor();
}

void UIInput::OnTextInput(const Event& evt)
{
    if (GetState() == StateActive)
    {
        auto pData = evt.GetDataAs<TextInputEventData>();

        char input = (char)pData->GetInput();
        if ((m_MaxLen == 0 || m_Value.length() < m_MaxLen)
            && IsValidInput(input))
        {
            m_Value += input;
            ApplyCursor();
        }
        else if (input == 8)
        {
            m_Value = m_Value.substr(0, m_Value.length() - 1);
            ApplyCursor();
        }
        else if (input == 13)
        {
            Blur();
            // TODO ?
            ApplyCursor();
        }
    }
}

void UIInput::SetType(const InputType& type)
{
    m_Type = type;
    FixValue();
}

void UIInput::SetValue(const string& value)
{
    m_Value = value;
    FixValue();
}

void UIInput::SetMaxLength(const size_t& maxLen)
{
    m_MaxLen = maxLen;
    if (m_MaxLen > 0)
    {
        m_Value.substr(0, std::min(m_MaxLen, m_Value.length()));
    }
}

bool UIInput::IsValidInput(char input)
{
    switch (m_Type)
    {
    case TypeText:

        return (input >= ' ' && input <= '~'); // All Characters

    case TypeInt:

        return (input >= '0' && input <= '9'); // Digits

    case TypeFloat:

        return (input >= '0' && input <= '9') || (m_Value.find('.') == string::npos && input == '.');
    }
}

void UIInput::FixValue()
{
    string newValue;
    newValue.resize(m_Value.length());
    for (auto& c : m_Value)
    {
        if (IsValidInput(c))
            newValue += c;
    }
    m_Value = newValue;
    ApplyCursor();
}

void UIInput::ApplyCursor()
{
    if (GetState() == StateActive)
    {
        SetText(m_Value + "_");
    }
    else
    {
        SetText(m_Value);
    }
}

}