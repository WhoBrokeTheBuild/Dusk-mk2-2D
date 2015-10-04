#ifndef DUSK_UI_LABEL_HPP
#define DUSK_UI_LABEL_HPP

#include <Dusk/Tracking/ITrackedObject.hpp>
#include <Dusk/UI/IUIElement.hpp>
#include <Dusk/Graphics/TextBuffer.hpp>
#include <Dusk/Graphics/Font.hpp>
#include <Dusk/Graphics/Color.hpp>
#include <Dusk/Geometry/Vector2.hpp>

namespace dusk
{

class Label :
    public ITrackedObject,
    public IUIElement
{
public:

    inline Label()
    { }

    virtual inline ~Label() { Term(); }

    virtual inline string GetClassName() const { return "Text Button"; }

    virtual bool Init(Font* pFont, const string& text, const unsigned int& fontSize, const Color& color);
    virtual void Term();

    void SetFont(Font* pFont);

    inline string GetText() const { return m_TextBuffer.GetText(); }
    void SetText(const string& text);

    inline unsigned int GetFontSize() const { return m_TextBuffer.GetFontSize(); }
    void SetFontSize(const unsigned int& fontSize);

    inline Color GetColor() const { return m_TextBuffer.GetColor(); }
    inline void SetColor(const Color& color) { m_TextBuffer.SetColor(color); }

    virtual void Draw(GraphicsContext* ctx);

    virtual inline Vector2f GetPos() const { return m_TextBuffer.GetPos(); }
    virtual inline Vector2f GetSize() const { return m_TextBuffer.GetSize(); }

protected:

    virtual void SetPos(const Vector2f& pos) override;
    virtual void SetSize(const Vector2f& size) override;

    TextBuffer m_TextBuffer;

};

} // namespace dusk

#endif // DUSK_UI_LABEL_HPP