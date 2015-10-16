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

    static EventID EvtLayoutChanged;

    UIElement();
    virtual ~UIElement() { Term(); }

    virtual inline string GetClassName() const { return "UI Element"; }

    bool Init(shared_ptr<UIElement> inheritFrom);
    bool Init();
    void Term();

    void OnUpdate(const Event& evt);
    void OnRender(const Event& evt);

    void OnRelativeToLayoutChanged(const Event& evt);
    
    string GetName() const { return m_Name; }
    void SetName(string name) { m_Name = name; }

    Vector2f GetPos() const { return m_Pos; }
    Vector2f GetInnerPos() const { return m_Pos; }

    Vector2f GetSize() const { return m_Size; }
    void SetSize(const Vector2f& size);

    shared_ptr<UIElement> GetParent() const { return m_Parent; }
    void SetParent(shared_ptr<UIElement> parent);

    shared_ptr<UIElement> GetRelativeTo() const { return m_RelativeTo; }
    void SetRelativeTo(shared_ptr<UIElement> relTo);

    UIRelPoint GetRelativePoint() const { return m_RelativePoint; }
    void SetRelativePoint(UIRelPoint relPoint);

    Vector2f GetOffset() const { return m_Offset; }
    void SetOffset(const Vector2f& offset);

    size_t GetBorderSize(const UIState& state = UIState::StateDefault) const { return m_BorderSize.GetValue(state); }
    void SetBorderSize(const size_t& size, const UIState& state = UIState::StateDefault) { m_BorderSize.SetValue(state, size); }

    Color GetBorderColor(const UIState& state = UIState::StateDefault) const { return m_BorderColor.GetValue(state); }
    void SetBorderColor(const Color& color, const UIState& state = UIState::StateDefault) { m_BorderColor.SetValue(state, color); }

    shared_ptr<UIFont> GetFont(const UIState& state = UIState::StateDefault) const { return m_Font.GetValue(state); }
    void SetFont(shared_ptr<UIFont> font, const UIState& state = UIState::StateDefault);

    string GetText() const { return m_TextBuffer.GetText(); }
    void SetText(const string& text);

    void AddChild(shared_ptr<UIElement>& pChild);

protected:
    
    void UpdateState();
    void UpdateLayout();

    string m_Name;
    UIState m_State;

    bool m_Active;
    bool m_Visible;

    Vector2f m_Pos;
    Vector2f m_TargetSize;
    Vector2f m_Size;

    shared_ptr<UIElement> m_RelativeTo;
    UIRelPoint m_RelativePoint;
    Vector2f m_Offset;

    StateProp<size_t> m_BorderSize;
    StateProp<Color> m_BorderColor;
    StateProp<shared_ptr<UIFont>> m_Font;

    TextBuffer m_TextBuffer;

    shared_ptr<UIElement> m_Parent;
    ArrayList<shared_ptr<UIElement>> m_Children;
};

} // namespace dusk

#endif // DUSK_UI_UI_ELEMENT_HPP