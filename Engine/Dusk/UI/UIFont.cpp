#include "UIFont.hpp"

namespace dusk
{

UIFont::UIFont() :
    mp_Font(nullptr),
    m_FontSize(),
    m_Color()
{ }

bool UIFont::Init(shared_ptr<UIFont> inheritFrom)
{
    mp_Font = inheritFrom->mp_Font;
    m_FontSize = inheritFrom->m_FontSize;
    m_Color = inheritFrom->m_Color;

    return true;
}

bool UIFont::Init()
{
    Term();
    return true;
}

void UIFont::Term()
{
    mp_Font = nullptr;
    m_FontSize = 0;
    m_Color = Color::Black;
}

} // namespace dusk