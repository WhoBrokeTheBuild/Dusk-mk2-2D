#include "IUIElement.hpp"

#include <Dusk/Program.hpp>
#include <Dusk/Input/InputSystem.hpp>
#include <Dusk/Input/Mouse.hpp>
#include <Dusk/Geometry/Rect.hpp>

namespace dusk
{

dusk::EventID IUIElement::EvtResized = 1;
dusk::EventID IUIElement::EvtFocus   = 2;
dusk::EventID IUIElement::EvtBlur = 3;

void IUIElement::OnMouseButtonRelease(const Event& evt)
{
    const MouseButtonEventData* pData = evt.GetDataAs<MouseButtonEventData>();

    if (FloatRect(GetPos(), GetSize()).contains(pData->GetMousePos()))
    {
        Click();
    }
    else
    {
        ClickOff();
    }
}

void IUIElement::OnRelativeElementResize(const Event& evt)
{
    UpdateRelativePos();
}

void IUIElement::SetAbsolutePos(const Vector2f& pos)
{
    if (mp_RelTo)
    {
        mp_RelTo->RemoveEventListener(IUIElement::EvtResized, this, &IUIElement::OnRelativeElementResize);
    }

    m_PosType = PositionType::Absolute;
    m_RelType = RelativeType::None;
    mp_RelTo = nullptr;
    m_RelOffset = Vector2f();
    SetPos(pos);
}

void IUIElement::SetRelativePos(const RelativeType& type, IUIElement* pRelativeTo, const Vector2f& offset)
{
    if (mp_RelTo)
    {
        mp_RelTo->RemoveEventListener(IUIElement::EvtResized, this, &IUIElement::OnRelativeElementResize);
    }

    m_PosType = PositionType::Relative;
    m_RelType = type;
    mp_RelTo = pRelativeTo;
    m_RelOffset = offset;
    UpdateRelativePos();

    mp_RelTo->AddEventListener(IUIElement::EvtResized, this, &IUIElement::OnRelativeElementResize);
}

void IUIElement::UpdateRelativePos()
{
    Vector2f pos = mp_RelTo->GetPos();

    switch (m_RelType)
    {
    case Above:

        pos.x += m_RelOffset.x;

        pos.y -= m_RelOffset.y;
        pos.y -= GetSize().y;

        break;
    case Below:

        pos.x += m_RelOffset.x;

        pos.y += mp_RelTo->GetSize().y;
        pos.y += m_RelOffset.y;

        break;
    case LeftOf:

        pos.x -= m_RelOffset.x;
        pos.x -= GetSize().x;

        pos.y += m_RelOffset.y;

        break;
    case RightOf:

        pos.x += mp_RelTo->GetSize().x;
        pos.x += m_RelOffset.x;

        pos.y += m_RelOffset.y;

        break;
    }

    SetPos(pos);
}

bool IUIElement::Init()
{
    InputSystem* pIS = Program::Inst()->GetInputSystem();
    pIS->AddEventListener(InputSystem::EvtMouseButtonRelease, this, &IUIElement::OnMouseButtonRelease);

    return true;
}

void IUIElement::Term()
{
    //if (mp_RelTo)
    //{
    //    mp_RelTo->RemoveEventListener(IUIElement::EvtResized, this, &IUIElement::OnRelativeElementResize);
    //}

    mp_RelTo = nullptr;

    InputSystem* pIS = Program::Inst()->GetInputSystem();
    pIS->RemoveEventListener(InputSystem::EvtMouseButtonRelease, this, &IUIElement::OnMouseButtonRelease);

    RemoveAllListeners();
}

} // namespace dusk