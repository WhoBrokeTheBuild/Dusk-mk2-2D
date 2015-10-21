#ifndef DUSK_UI_UI_INPUT_HPP
#define DUSK_UI_UI_INPUT_HPP

#include <Dusk/UI/UIElement.hpp>

namespace dusk
{

class UIInput :
    public UIElement
{
public:

    enum InputType
    {
        TypeText,
        TypeInt,
        TypeFloat,
    };

    UIInput();
    virtual ~UIInput();

    virtual inline string GetClassName() const { return "UI Input"; }

    virtual void Inherit(const UIElement* pInheritFrom);

    virtual void Focus() override;
    virtual void Blur() override;

    virtual void OnTextInput(const Event& evt);

    inline InputType GetType() const { return m_Type; }
    void SetType(const InputType& type);

    inline size_t GetMaxLength() const { return m_MaxLen; }
    void SetMaxLength(const size_t& maxLen);

    inline string GetValue() const { return m_Value; }
    inline int GetIntValue() const { return std::stoi(m_Value); }
    inline float GetFloatValue() const { return std::stof(m_Value); }

    void SetValue(const string& value);

protected:

    bool IsValidInput(char input);
    void FixValue();

    void ApplyCursor();

    bool m_HasCursor = false;

    InputType m_Type = TypeText;

    size_t m_MaxLen = 0;
    
    string m_Value;

};

} // namespace dusk

#endif // DUSK_UI_UI_INPUT_HPP