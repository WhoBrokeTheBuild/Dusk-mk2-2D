#ifndef DUSK_UI_UI_MANAGER_HPP
#define DUSK_UI_UI_MANAGER_HPP

#include <Dusk/Tracking/TrackedObject.hpp>
#include <Dusk/Collections/Map.hpp>
#include <Dusk/Graphics/Font.hpp>
#include <Dusk/Graphics/Texture.hpp>
#include <Dusk/UI/UIElement.hpp>
#include <Dusk/UI/UIFrame.hpp>
#include <Dusk/UI/UILabel.hpp>
#include <Dusk/UI/UIInput.hpp>
#include <Dusk/UI/UIButton.hpp>
#include <Dusk/UI/UIFont.hpp>
#include <Dusk/UI/UIRenderFrame.hpp>
#include <Dusk/Utility/Types.hpp>
#include <Dusk/Scripting/Scripting.hpp>
#include <Dusk/Scripting/ScriptHost.hpp>

#include <RapidXML/rapidxml.hpp>
#include <RapidXML/rapidxml_utils.hpp>

namespace dusk
{

class UIManager :
    public TrackedObject
{
public:

    UIManager();
    UIManager(const UIManager&) = delete;
    UIManager& operator=(const UIManager&) = delete;
    virtual ~UIManager();

    virtual inline string GetClassName() const { return "UI Manager"; }

    UIElement* GetFocusedElement() const { return mp_FocusedElement; }
    void SetFocusedElement(UIElement* pFocusedElement) { mp_FocusedElement = pFocusedElement; }

    UIElement* GetElement(const string& name) { return m_UIElements[name].get(); }

    void OnUpdate(const Event& evt);
    void OnRender(const Event& evt);
    void OnWindowResize(const Event& evt);
    void OnMouseMove(const Event& evt);
    void OnMouseButtonPress(const Event& evt);
    void OnMouseButtonRelease(const Event& evt);

    bool LoadFile(const string& filename);

    typedef shared_ptr<UIElement>(*RenderFrameTypeFunc)(void);

    template <class T>
    bool RegisterRenderFrameType(const string& name)
    {
        if (m_RenderFrameTypes.contains_key(name))
            return false;

        m_RenderFrameTypes.add(name, []() -> shared_ptr<UIElement> { return shared_ptr<UIElement>(New T); });
        return true;
    }

private:

    bool LoadFile(const string& filename, shared_ptr<UIElement>& pParentElement);

    Color ParseColor(rapidxml::xml_node<>* node);
    Vector2f ParseVector2(rapidxml::xml_node<>* node);
    UIState ParseState(const string& state);
    string ParseName(rapidxml::xml_node<>* node, shared_ptr<UIElement>& pParentElement);

    void ParseBindings(rapidxml::xml_node<>* node, shared_ptr<UIElement>& pElement, const string& nodeName, const EventID& eventId);

    void ParseElementNodes(rapidxml::xml_node<>* root, shared_ptr<UIElement>& pParentElement, const string& dirname);

    UIFont* ParseFont(rapidxml::xml_node<>* node, shared_ptr<UIElement>& pParentElement);
    bool ParseElement(rapidxml::xml_node<>* node, shared_ptr<UIElement>& pElement, shared_ptr<UIElement>& pParentElement, const string& dirname);
    void ParseFrame(rapidxml::xml_node<>* node, shared_ptr<UIFrame>& pFrame);
    void ParseLabel(rapidxml::xml_node<>* node, shared_ptr<UILabel>& pLabel);
    void ParseInput(rapidxml::xml_node<>* node, shared_ptr<UIInput>& pInput);
    void ParseButton(rapidxml::xml_node<>* node, shared_ptr<UIButton>& pButton);

    unique_ptr<ScriptHost> mp_ScriptHost;
    shared_ptr<UIElement> mp_RootElement;
    UIElement* mp_FocusedElement = nullptr;

    Map<string, unique_ptr<Font>> m_Fonts;
    Map<string, unique_ptr<Texture>> m_Textures;
    Map<string, unique_ptr<UIFont>> m_UIFonts;
    Map<string, shared_ptr<UIElement>> m_UIElements;

    Map<string, RenderFrameTypeFunc> m_RenderFrameTypes;

public:

    static void Script_RegisterFunctions();
    static int Script_GetElement(lua_State* L);

};

} // namespace dusk

#endif // DUSK_UI_UI_MANAGER_HPP