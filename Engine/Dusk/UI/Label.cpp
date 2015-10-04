#include "Label.hpp"

namespace dusk
{

bool Label::Init(Font* pFont, const string& text, const unsigned int& fontSize, const Color& color)
{
    if (!IUIElement::Init())
    {
        return false;
    }
    m_TextBuffer.Init(pFont, text, fontSize, color);

    return true;
}

void Label::Term()
{
    IUIElement::Term();
}

void Label::SetFont(Font* pFont)
{
    m_TextBuffer.SetFont(pFont);
    Dispatch(Event(IUIElement::EvtResized));
}

void Label::SetText(const string& text)
{
    m_TextBuffer.SetText(text);
    Dispatch(Event(IUIElement::EvtResized));
}

void Label::SetFontSize(const unsigned int& fontSize)
{
    m_TextBuffer.SetFontSize(fontSize);
    Dispatch(Event(IUIElement::EvtResized));
}

void Label::Draw(GraphicsContext* ctx)
{
    ctx->Draw(&m_TextBuffer);
}

void Label::SetPos(const Vector2f& pos)
{
    m_TextBuffer.SetPos(pos);
}

void Label::SetSize(const Vector2f& size)
{
    throw std::logic_error("You cannot set the size of a Label.");
}

} // namespace dusk