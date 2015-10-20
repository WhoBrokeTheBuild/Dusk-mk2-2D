#ifndef DUSK_UI_UI_INPUT_HPP
#define DUSK_UI_UI_INPUT_HPP

#include <Dusk/UI/UIElement.hpp>

namespace dusk
{

class UIInput :
    public UIElement
{
public:

    UIInput();
    virtual ~UIInput();

    virtual inline string GetClassName() const { return "UI Input"; }

    virtual void Inherit(const UIElement* pInheritFrom);

    virtual void Focus() override;
    virtual void Blur() override;

    virtual void OnTextInput(const Event& evt);

protected:

    void ApplyCursor();

    bool m_HasCursor = false;

    size_t m_MaxLen = 0;
    
    string m_Value;

};

} // namespace dusk

#endif // DUSK_UI_UI_INPUT_HPP