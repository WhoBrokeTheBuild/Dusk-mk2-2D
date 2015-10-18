#ifndef DUSK_UI_UI_ELEMENT_HPP
#define DUSK_UI_UI_ELEMENT_HPP

#include <Dusk/Tracking/TrackedObject.hpp>
#include <Dusk/Events/EventDispatcher.hpp>
#include <Dusk/Geometry/Vector2.hpp>
#include <Dusk/Graphics/Color.hpp>
#include <Dusk/Graphics/TextBuffer.hpp>
#include <Dusk/Collections/Map.hpp>
#include <Dusk/Collections/ArrayList.hpp>
#include <Dusk/UI/UIFont.hpp>

namespace dusk
{

enum UIState {
    StateDefault,
    StateActive,
    StateHover,
    StateDisabled
};

enum UIRelPoint {
    TopLeft,
    TopRight,
    BottomLeft,
    BottomRight
};

template <typename PropType>
struct StateProp
{
public:

    StateProp(PropType def) :
        m_Values()
    {
        m_Values.add(UIState::StateDefault, def);
    }

    StateProp() :
        m_Values()
    {
        m_Values.add(UIState::StateDefault, PropType());
    }

    StateProp( const StateProp<PropType>& other ) :
        m_Values(other.m_Values)
    { }

    PropType GetValue(const UIState& state) const
    {
        if (m_Values.contains_key(state))
            return m_Values.at(state);
        return m_Values.at(UIState::StateDefault);
    }

    void SetValue(const UIState& state, PropType prop)
    {
        m_Values.erase(state);
        m_Values.add(state, prop);
    }

private:

    Map<UIState, PropType> m_Values;

};

class UIElement :
    public TrackedObject,
    public EventDispatcher
{
public:

    enum : EventID
    {
        EvtShown,
        EvtHidden,

        EvtLayoutChanged,
        EvtStateChanged,
    };

    UIElement();
    UIElement(const UIElement&) = delete;
    UIElement& operator=(const UIElement&) = delete;
    virtual ~UIElement();

    virtual inline string GetClassName() const { return "UI Element"; }

    virtual void Inherit(const UIElement* pInheritFrom);

    void OnUpdate(const Event& evt);
    void OnRender(const Event& evt);

    void OnRelativeToLayoutChanged(const Event& evt);
    
    string GetName() const { return m_Name; }
    void SetName(string name) { m_Name = name; }

    Vector2f GetPos() const { return m_Pos; }

    Vector2f GetSize() const { return m_Size; }
    void SetSize(const Vector2f& size);

    weak_ptr<UIElement> GetParent() const { return mp_Parent; }
    void SetParent(weak_ptr<UIElement> pParent);

    weak_ptr<UIElement> GetRelativeTo() const { return m_RelativeTo; }
    void SetRelativeTo(weak_ptr<UIElement> pRelativeTo);

    UIRelPoint GetRelativePoint() const { return m_RelativePoint; }
    void SetRelativePoint(UIRelPoint relPoint);

    Vector2f GetOffset() const { return m_Offset; }
    void SetOffset(const Vector2f& offset);

    float GetBorderSize(const UIState& state = UIState::StateDefault) const { return m_BorderSize.GetValue(state); }
    void SetBorderSize(const float& size, const UIState& state = UIState::StateDefault) { m_BorderSize.SetValue(state, size); }

    Color GetBorderColor(const UIState& state = UIState::StateDefault) const { return m_BorderColor.GetValue(state); }
    void SetBorderColor(const Color& color, const UIState& state = UIState::StateDefault) { m_BorderColor.SetValue(state, color); }

    UIFont* GetFont(const UIState& state = UIState::StateDefault) const { return m_Font.GetValue(state); }
    void SetFont(UIFont* pFont, const UIState& state = UIState::StateDefault);

    string GetText() const { return m_TextBuffer.GetText(); }
    void SetText(const string& text);

    void AddChild(shared_ptr<UIElement>& pChild);

protected:
    
    void UpdateState();
    void UpdateLayout();

    string m_Name;
    UIState m_State = StateDefault;

    bool m_Active = true;
    bool m_Visible = true;

    Vector2f m_Pos;
    Vector2f m_TargetSize;
    Vector2f m_Size;

    weak_ptr<UIElement> m_RelativeTo;
    UIRelPoint m_RelativePoint;
    Vector2f m_Offset;

    StateProp<float> m_BorderSize;
    StateProp<Color> m_BorderColor;
    StateProp<UIFont*> m_Font;

    TextBuffer m_TextBuffer;

    weak_ptr<UIElement> mp_Parent;
    ArrayList<shared_ptr<UIElement>> m_Children;
};

} // namespace dusk

#endif // DUSK_UI_UI_ELEMENT_HPP