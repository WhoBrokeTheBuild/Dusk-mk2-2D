#ifndef DUSK_UI_UI_ELEMENT_HPP
#define DUSK_UI_UI_ELEMENT_HPP

#include <Dusk/Tracking/TrackedObject.hpp>
#include <Dusk/Events/EventDispatcher.hpp>
#include <Dusk/Geometry/Vector2.hpp>
#include <Dusk/Geometry/Rect.hpp>
#include <Dusk/Graphics/Color.hpp>
#include <Dusk/Graphics/TextBuffer.hpp>
#include <Dusk/Collections/Map.hpp>
#include <Dusk/Collections/ArrayList.hpp>
#include <Dusk/UI/UIFont.hpp>
#include <Dusk/Program.hpp>

namespace dusk
{

enum UIState {
    StateDefault  = 1,
    StateActive   = 2,
    StateHover    = 3,
    StateDisabled = 4,
};

enum UIRelPoint {
    TopLeft     = 1,
    TopRight    = 2,
    BottomLeft  = 3,
    BottomRight = 4,
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

class UIManager;

class UIElement :
    public TrackedObject,
    public EventDispatcher
{
public:

    enum : EventID
    {
        EvtShow         = 1,
        EvtHide         = 2,

        EvtActivate     = 3,
        EvtDeactivate   = 4,

        EvtMouseEnter   = 5,
        EvtMouseLeave   = 6,

        EvtMouseDown    = 7,
        EvtMouseUp      = 8,

        EvtFocus        = 9,
        EvtBlur         = 10,

        EvtUpdate       = 11,
        EvtRender       = 12,

        EvtLayoutChange = 13,
        EvtStateChange  = 14,
    };

    UIElement();
    UIElement(const UIElement&) = delete;
    UIElement& operator=(const UIElement&) = delete;
    virtual ~UIElement();

    virtual inline string GetClassName() const { return "UI Element"; }

    virtual void Inherit(const UIElement* pInheritFrom);

    void SetUIManager(UIManager* pUIManager);

    virtual void OnUpdate(const Event& evt);
    virtual void OnRender(const Event& evt);
    virtual void OnMouseMove(const Event& evt);
    virtual void OnMouseButtonPress(const Event& evt);
    virtual void OnMouseButtonRelease(const Event& evt);

    void OnRelativeToLayoutChange(const Event& evt);

    virtual inline void Show() { SetVisible(true); }
    virtual inline void Hide() { SetVisible(false); }
    virtual inline void Activate() { SetActive(true); }
    virtual inline void Deactivate() { SetActive(false); }
    virtual inline void MouseEnter() { Dispatch(Event(UIElement::EvtMouseEnter)); }
    virtual inline void MouseLeave() { Dispatch(Event(UIElement::EvtMouseLeave)); }
    virtual inline void MouseUp() { Dispatch(Event(UIElement::EvtMouseUp)); }
    virtual inline void MouseDown() { Dispatch(Event(UIElement::EvtMouseDown)); }
    virtual void Focus();
    virtual void Blur();

    bool IsMouseOver() const { return m_MouseOver; }
    bool IsMouseDown() const { return m_MouseDown; }
    bool HasFocus() const { return m_HasFocus; }

    bool IsFocusable() const { return m_Focusable; }
    void SetFocusable(bool focusable);

    bool IsActive() const { return m_Active; }
    void SetActive(bool active);

    bool IsVisible() const { return m_Visible; }
    void SetVisible(bool visible);
    
    string GetName() const { return m_Name; }
    void SetName(string name) { m_Name = name; }

    UIState GetState() const { return m_State; }

    Vector2f GetPos() const { return m_Pos; }

    Vector2f GetSize() const { return m_Size; }
    virtual void SetSize(const Vector2f& size);

    weak_ptr<UIElement> GetParent() const { return mp_Parent; }
    void SetParent(weak_ptr<UIElement> pParent);

    weak_ptr<UIElement> GetRelativeTo() const { return m_RelativeTo; }
    void SetRelativeTo(weak_ptr<UIElement> pRelativeTo);

    UIRelPoint GetRelativePoint() const { return m_RelativePoint; }
    void SetRelativePoint(UIRelPoint relPoint);

    Vector2f GetOffset() const { return m_Offset; }
    virtual void SetOffset(const Vector2f& offset);

    virtual FloatRect GetBounds() const { return{ m_Pos.x, m_Pos.y, m_Size.x, m_Size.y }; }

    virtual Color GetBackgroundColor(const UIState& state = UIState::StateDefault) const { return m_BackgroundColor.GetValue(state); }
    virtual void SetBackgroundColor(const Color& color, const UIState& state = UIState::StateDefault) { m_BackgroundColor.SetValue(state, color); }

    virtual float GetBorderSize(const UIState& state = UIState::StateDefault) const { return m_BorderSize.GetValue(state); }
    virtual void SetBorderSize(const float& size, const UIState& state = UIState::StateDefault) { m_BorderSize.SetValue(state, size); }

    virtual Color GetBorderColor(const UIState& state = UIState::StateDefault) const { return m_BorderColor.GetValue(state); }
    virtual void SetBorderColor(const Color& color, const UIState& state = UIState::StateDefault) { m_BorderColor.SetValue(state, color); }

    virtual UIFont* GetFont(const UIState& state = UIState::StateDefault) const { return m_Font.GetValue(state); }
    virtual void SetFont(UIFont* pFont, const UIState& state = UIState::StateDefault);

    virtual string GetText() const { return m_TextBuffer.GetText(); }
    virtual void SetText(const string& text);

    virtual ArrayList<shared_ptr<UIElement>>& GetChildren() { return m_Children; }
    virtual void AddChild(shared_ptr<UIElement>& pChild);

protected:
    
    virtual void UpdateState();
    virtual void UpdateStateData();
    virtual void UpdateLayout();

private:

    UIManager* mp_UIManager;

    string m_Name;
    UIState m_State = StateDefault;

    bool m_Focusable = true;

    bool m_Active = true;
    bool m_Visible = true;

    bool m_MouseOver = false;
    bool m_MouseDown = false;
    bool m_HasFocus = false;

    Vector2f m_Pos;
    Vector2f m_TargetSize;
    Vector2f m_Size;

    weak_ptr<UIElement> m_RelativeTo;
    UIRelPoint m_RelativePoint;
    Vector2f m_Offset;

    StateProp<Color> m_BackgroundColor = StateProp<Color>(Color::Transparent);
    StateProp<float> m_BorderSize;
    StateProp<Color> m_BorderColor;
    StateProp<UIFont*> m_Font;

    TextBuffer m_TextBuffer;

    weak_ptr<UIElement> mp_Parent;
    ArrayList<shared_ptr<UIElement>> m_Children;

public:

    static void Script_RegisterFunctions();

    static int Script_IsMouseOver(lua_State* L);
    static int Script_IsMouseDown(lua_State* L);
    static int Script_HasFocus(lua_State* L);

    static int Script_IsFocusable(lua_State* L);
    static int Script_SetFocusable(lua_State* L);

    static int Script_IsActive(lua_State* L);
    static int Script_SetActive(lua_State* L);

    static int Script_IsVisible(lua_State* L);
    static int Script_SetVisible(lua_State* L);

    static int Script_GetValue(lua_State* L);

    static int Script_GetState(lua_State* L);

    static int Script_GetPos(lua_State* L);
    static int Script_GetBounds(lua_State* L);

    static int Script_GetParent(lua_State* L);
    //static int Script_SetParent(lua_State* L);

    static int Script_GetSize(lua_State* L);
    static int Script_SetSize(lua_State* L);

    static int Script_GetOffset(lua_State* L);
    static int Script_SetOffset(lua_State* L);

    static int Script_GetRelativePoint(lua_State* L);
    //static int Script_SetRelativePoint(lua_State* L);

    static int Script_GetRelativeTo(lua_State* L);
    static int Script_SetRelativeTo(lua_State* L);

    static int Script_GetText(lua_State* L);
    static int Script_SetText(lua_State* L);

};

class StateChangeData :
    public EventData
{
public:

    StateChangeData(const UIState& oldState, const UIState& newState) :
        m_OldState(oldState),
        m_NewState(newState)
    { }

    virtual inline string GetClassName() const
    {
        return "State Change Event Data";
    }

    virtual inline EventData* Clone() const
    {
        return New StateChangeData(m_OldState, m_NewState);
    }

    inline unsigned int GetWidth() const { return m_OldState; }
    inline unsigned int GetHeight() const { return m_NewState; }

    virtual int PushDataToLua(lua_State* L) const;

private:

    UIState m_OldState;
    UIState m_NewState;

};

} // namespace dusk

#endif // DUSK_UI_UI_ELEMENT_HPP