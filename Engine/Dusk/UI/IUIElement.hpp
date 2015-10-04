#ifndef DUSK_I_UI_ELEMENT_HPP
#define DUSK_I_UI_ELEMENT_HPP

#include <Dusk/Events/IEventDispatcher.hpp>
#include <Dusk/Graphics/GraphicsContext.hpp>
#include <Dusk/Geometry/Vector2.hpp>

namespace dusk
{

class IUIElement :
    public IEventDispatcher
{
public:

    static EventID EvtResized;
    static EventID EvtFocus;
    static EventID EvtBlur;

    enum PositionType
    {
        Absolute,
        Relative
    };

    enum RelativeType
    {
        None,

        Above,
        Below,
        LeftOf,
        RightOf
    };

    inline IUIElement() :
        m_PosType(PositionType::Absolute),
        m_RelType(RelativeType::None),
        mp_RelTo(nullptr),
        m_RelOffset()
    { }

    virtual inline bool HasFocus() const { return m_Focus; }

    virtual Vector2f GetPos() const = 0;
    virtual Vector2f GetSize() const = 0;

    virtual inline void Focus() 
    { 
        m_Focus = true; 
        Dispatch(Event(EvtFocus));
    }

    virtual inline void Blur()
    {
        m_Focus = false;
        Dispatch(Event(EvtBlur));
    }

    virtual inline void Click() { }
    virtual inline void ClickOff() { }

    virtual void Draw(GraphicsContext* ctx) = 0;

    virtual void SetAbsolutePos(const Vector2f& pos);
    virtual void SetRelativePos(const RelativeType& type, IUIElement* pRelativeTo, const Vector2f& pos);

    virtual void OnMouseButtonRelease(const Event& evt);
    virtual void OnRelativeElementResize(const Event& evt);

protected:

    virtual void UpdateRelativePos();

    virtual bool Init();
    virtual void Term();

    virtual void SetPos(const Vector2f& pos) = 0;
    virtual void SetSize(const Vector2f& size) = 0;

    bool m_Focus;

    PositionType m_PosType;

    RelativeType m_RelType;
    IUIElement* mp_RelTo;
    Vector2f m_RelOffset;

}; // class IUIElement

} // namespace dusk

#endif // DUSK_I_UI_ELEMENT_HPP