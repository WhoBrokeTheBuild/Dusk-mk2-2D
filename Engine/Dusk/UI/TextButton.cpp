#include "TextButton.hpp"

namespace dusk
{

dusk::EventID TextButton::EvtClicked = 10;

bool TextButton::Init(Font* pFont, const string& text, const unsigned int& fontSize, const Color& color)
{
    if (!IUIElement::Init())
    {
        return false;
    }
    m_TextBuffer.Init(pFont, text, fontSize, color);

    return true;
}

void TextButton::Term()
{
    IUIElement::Term();
}

void TextButton::SetFont(Font* pFont)
{
    m_TextBuffer.SetFont(pFont);
    Dispatch(Event(IUIElement::EvtResized));
}

void TextButton::SetText(const string& text)
{
    m_TextBuffer.SetText(text);
    Dispatch(Event(IUIElement::EvtResized));
}

void TextButton::SetFontSize(const unsigned int& fontSize)
{
    m_TextBuffer.SetFontSize(fontSize);
    Dispatch(Event(IUIElement::EvtResized));
}

void TextButton::Click()
{
    Dispatch(Event(EvtClicked));
}

void TextButton::Draw(GraphicsContext* ctx)
{
    sf::RectangleShape rectangle(GetSize() + Vector2f(0.0f, 6.0f)); // TODO: Fix height
    rectangle.setPosition(GetPos());
    rectangle.setFillColor(Color::Transparent);
    rectangle.setOutlineColor(m_TextBuffer.GetColor());
    rectangle.setOutlineThickness(1.0f);
    ctx->Draw(rectangle);

    ctx->Draw(&m_TextBuffer);
}

void TextButton::SetPos(const Vector2f& pos)
{
    m_TextBuffer.SetPos(pos);
}

void TextButton::SetSize(const Vector2f& size)
{
    throw std::logic_error("You cannot set the size of a Text Button.");
}

} // namespace dusk