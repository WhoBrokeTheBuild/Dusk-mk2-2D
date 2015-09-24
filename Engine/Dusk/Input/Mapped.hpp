#ifndef DUSK_INPUT_MAPPED_INPUT_EVENT_DATA_HPP
#define DUSK_INPUT_MAPPED_INPUT_EVENT_DATA_HPP

#include <Dusk/Events/Event.hpp>

namespace dusk
{

typedef string MappedInputID;

class MappedInputEventData :
    public EventData
{
public:

    MappedInputEventData(const MappedInputID& mappedInput) :
        m_MappedInput(mappedInput)
    { }

    virtual inline string GetClassName() const { return "Mapped Input Event Data"; }

    virtual inline EventData* Clone() const { return New MappedInputEventData(m_MappedInput); }

    inline MappedInputID GetMappedInput() const { return m_MappedInput; }

    virtual int PushDataToLua(lua_State* L) const;

private:

    MappedInputID        m_MappedInput;

}; // class MappedInputEventData

} // namespace dusk

#endif // DUSK_INPUT_MAPPED_INPUT_EVENT_DATA_HPP