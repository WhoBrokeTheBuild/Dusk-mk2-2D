#ifndef DUSK_UI_UI_MANAGER_HPP
#define DUSK_UI_UI_MANAGER_HPP

#include <Dusk/Tracking/TrackedObject.hpp>
#include <Dusk/Collections/Map.hpp>
#include <Dusk/Graphics/Font.hpp>
#include <Dusk/UI/UIElement.hpp>
#include <Dusk/UI/UIFrame.hpp>
#include <Dusk/UI/UILabel.hpp>
#include <Dusk/UI/UIInput.hpp>
#include <Dusk/UI/UIButton.hpp>
#include <Dusk/UI/UIFont.hpp>
#include <Dusk/Utility/Types.hpp>
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
    virtual ~UIManager() { Term(); }

    virtual inline string GetClassName() const { return "UI Manager"; }

    bool Init();
    void Term();

    void OnUpdate(const Event& evt);
    void OnRender(const Event& evt);

    bool LoadFile(const string& filename);

private:

    bool LoadFile(const string& filename, shared_ptr<UIElement>& pParentElement);

    Color ParseColor(rapidxml::xml_node<>* node);
    Vector2f ParseVector2(rapidxml::xml_node<>* node);
    UIState ParseState(const string& state);

    void ParseElementNodes(rapidxml::xml_node<>* root, shared_ptr<UIElement>& pParentElement, const string& currentDir);

    shared_ptr<UIFont> ParseFont(rapidxml::xml_node<>* node);
    void ParseElement(rapidxml::xml_node<>* node, shared_ptr<UIElement>& pParentElement, const string& currentDir);
    void ParseFrame(rapidxml::xml_node<>* node, shared_ptr<UIElement>& pParentElement, const string& currentDir);
    void ParseLabel(rapidxml::xml_node<>* node, shared_ptr<UIElement>& pParentElement, const string& currentDir);
    void ParseInput(rapidxml::xml_node<>* node, shared_ptr<UIElement>& pParentElement, const string& currentDir);
    void ParseButton(rapidxml::xml_node<>* node, shared_ptr<UIElement>& pParentElement, const string& currentDir);

    shared_ptr<UIElement> ParseElementInherits(rapidxml::xml_node<>* node);
    void ParseElementName(rapidxml::xml_node<>* node, shared_ptr<UIElement>& pElement, shared_ptr<UIElement>& pParentElement, const string& dirname);
    void ParseElementVirtual(rapidxml::xml_node<>* node, shared_ptr<UIElement>& pElement, shared_ptr<UIElement>& pParentElement, const string& dirname);
    void ParseElementSize(rapidxml::xml_node<>* node, shared_ptr<UIElement>& pElement, shared_ptr<UIElement>& pParentElement, const string& dirname);
    void ParseElementPosition(rapidxml::xml_node<>* node, shared_ptr<UIElement>& pElement, shared_ptr<UIElement>& pParentElement, const string& dirname);
    void ParseElementText(rapidxml::xml_node<>* node, shared_ptr<UIElement>& pElement, shared_ptr<UIElement>& pParentElement, const string& dirname);
    void ParseElementFont(rapidxml::xml_node<>* node, shared_ptr<UIElement>& pElement, shared_ptr<UIElement>& pParentElement, const string& dirname);
    void ParseElementBorder(rapidxml::xml_node<>* node, shared_ptr<UIElement>& pElement, shared_ptr<UIElement>& pParentElement, const string& dirname);

    unique_ptr<ScriptHost> m_ScriptHost;

    shared_ptr<UIElement> m_RootElement;

    Map<string, shared_ptr<Font>> m_Fonts;
    //Map<string, shared_ptr<Texture>> m_Textures;

    Map<string, shared_ptr<UIFont>> m_UIFonts;
    Map<string, shared_ptr<UIElement>> m_UIElements;
    //Map<string, shared_ptr<UIFrame>> m_UIFrames;

};

} // namespace dusk

#endif // DUSK_UI_UI_MANAGER_HPP