#include "TextBox.hpp"

namespace dusk
{

bool TextBox::Init(const unsigned int& maxChars, Font* pFont, string text, const unsigned int& fontSize, const Color& color)
{
    if (!IUIElement::Init())
    {
        return false;
    }

    m_MaxChars = maxChars;
    if (text.length() > maxChars)
    {
        text.substr(0, maxChars);
    }

    m_TextBuffer.Init(pFont, text, fontSize, color);
    UpdateSize();

    return true;
}

void TextBox::Term()
{
    IUIElement::Term();
}

void TextBox::SetMaxChars(const unsigned int& maxChars)
{
    m_MaxChars = maxChars;
}

void TextBox::SetFont(Font* pFont)
{
    m_TextBuffer.SetFont(pFont);
    Dispatch(Event(IUIElement::EvtResized));
}

void TextBox::SetText(const string& text)
{
    m_TextBuffer.SetText(text);
    Dispatch(Event(IUIElement::EvtResized));
}

void TextBox::SetFontSize(const unsigned int& fontSize)
{
    m_TextBuffer.SetFontSize(fontSize);
    Dispatch(Event(IUIElement::EvtResized));
}

void TextBox::Draw(GraphicsContext* ctx)
{
    sf::RectangleShape rectangle(GetSize() + Vector2f(0.0f, 6.0f)); // TODO: Fix height
    rectangle.setPosition(GetPos());
    ctx->Draw(rectangle);

    ctx->Draw(&m_TextBuffer);
}

void TextBox::UpdateSize()
{
    string text = m_TextBuffer.GetText();
    string tmp;
    tmp.resize(m_MaxChars, 'W');

    m_TextBuffer.SetText(tmp);
    m_Size = m_TextBuffer.GetSize();

    m_TextBuffer.SetText(text);
}

void TextBox::SetPos(const Vector2f& pos)
{
    m_TextBuffer.SetPos(pos);
}

void TextBox::SetSize(const Vector2f& size)
{
    throw std::logic_error("You cannot set the size of a Label.");
}

} // namespace dusk