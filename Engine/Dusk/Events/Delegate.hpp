#ifndef DUSK_DELEGATE_HPP
#define DUSK_DELEGATE_HPP

#include <Dusk/Tracking/TrackedObject.hpp>
#include <Dusk/Events/Callbacks.hpp>

namespace dusk
{

class ScriptHost;

template <typename ReturnType, typename Param = void>
class Delegate :
    public TrackedObject
{
public:

    Delegate(ReturnType(*pFunction)(Param))
    {
        mp_Callback = New FunctionCallback<ReturnType, Param>(pFunction);
    }

    template <typename ObjectType, typename Method>
    Delegate(ObjectType* pObject, Method method)
    {
        mp_Callback = New MethodCallback<ReturnType, Param, ObjectType, Method>(pObject, method);
    }

    Delegate(ScriptHost* pScriptHost, const string& callback)
    {
        mp_Callback = New LuaFucntionCallback(pScriptHost, callback);
    }

    Delegate(const Delegate<ReturnType, Param>& rhs)
    {
        mp_Callback = rhs.mp_Callback->Clone();
    }

    virtual inline ~Delegate()
    {
        delete mp_Callback; mp_Callback = nullptr;
    }

    virtual inline string GetClassName() const
    {
        return "Delegate";
    }

    inline ReturnType Invoke(Param param)
    {
        return mp_Callback->Invoke(param);
    }
    inline ReturnType operator()(Param param)
    {
        return Invoke(param);
    }

    inline bool IsMethodOf(void* pObject)
    {
        if (!mp_Callback) return false;
        return mp_Callback->IsMethodOf(pObject);
    }

    bool operator==(const Delegate<ReturnType, Param>& rhs)
    {
        if (!mp_Callback || !rhs.mp_Callback)
            return false;

        if (mp_Callback == rhs.mp_Callback)
            return true;

        return (*(mp_Callback) == *(rhs.mp_Callback));
    }

    bool operator!=(const Delegate<ReturnType, Param>& rhs)
    {
        return !((*this) == rhs);
    }

private:

    ICallback<ReturnType, Param>*    mp_Callback;


}; // class Delegate

} // namespace dusk

#endif // DUSK_DELEGATE_HPP
