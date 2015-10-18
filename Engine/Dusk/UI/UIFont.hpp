#ifndef DUSK_UI_UI_FONT_HPP
#define DUSK_UI_UI_FONT_HPP

#include <Dusk/Tracking/TrackedObject.hpp>
#include <Dusk/Graphics/Color.hpp>
#include <Dusk/Graphics/Font.hpp>
#include <Dusk/Utility/Types.hpp>

namespace dusk
{

class UIFont :
    public TrackedObject
{
public:

    inline UIFont() :
        mp_Font(nullptr)
    { }

    virtual inline ~UIFont()
    { }

    virtual inline string GetClassName() const { return "UI Font"; }

    inline void Inherit(const UIFont* pInheritFrom)
    {
        mp_Font = pInheritFrom->mp_Font;
        m_FontSize = pInheritFrom->m_FontSize;
        m_Color = pInheritFrom->m_Color;
    }

    inline Font* GetFont() const { return mp_Font; }
    inline void SetFont(Font* pFont) { mp_Font = pFont; }

    inline unsigned int GetFontSize() const { return m_FontSize; }
    inline void SetFontSize(const unsigned int& size) { m_FontSize = size; }

    inline Color GetColor() const { return m_Color; }
    inline void SetColor(const Color& color) { m_Color = color; }

private:

    Font* mp_Font;

    unsigned int m_FontSize;

    Color m_Color;

};

} // namespace dusk

#endif // DUSK_UI_UI_FONT_HPP