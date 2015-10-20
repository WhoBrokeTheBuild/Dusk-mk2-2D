#include "UIInput.hpp"

#include <Dusk/Program.hpp>
#include <Dusk/Input/InputSystem.hpp>

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
        
        if (m_MaxLen > 0 && m_Value.length() >= m_MaxLen)
            return;

        m_Value += (char)pData->GetInput();
        ApplyCursor();
    }
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