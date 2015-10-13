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

    UIFont();
    virtual inline ~UIFont() { Term(); }

    virtual inline string GetClassName() const { return "Font Element"; }

    bool Init(shared_ptr<UIFont> inheritFrom);
    bool Init();
    void Term();

    inline shared_ptr<Font> GetFont() const { return mp_Font; }
    inline void SetFont(shared_ptr<Font> pFont) { mp_Font = pFont; }

    inline size_t GetFontSize() const { return m_FontSize; }
    inline void SetFontSize(const size_t& size) { m_FontSize = size; }

    inline Color GetColor() const { return m_Color; }
    inline void SetColor(const Color& color) { m_Color = color; }

private:

    shared_ptr<Font> mp_Font;

    size_t m_FontSize;

    Color m_Color;

};

} // namespace dusk

#endif // DUSK_UI_UI_FONT_HPP