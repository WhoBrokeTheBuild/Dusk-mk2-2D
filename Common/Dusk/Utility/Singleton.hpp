#ifndef DUSK_SINGLETON_HPP
#define DUSK_SINGLETON_HPP

#define DUSK_SINGLETON(CLASS) \
public: \
    static inline CLASS* Inst() { return sp_Inst; } \
    static inline CLASS* CreateInst() \
    { \
        DestroyInst(); \
        sp_Inst = New CLASS(); \
        return sp_Inst; \
    } \
    static inline void DestroyInst() \
    { \
        delete sp_Inst; \
        sp_Inst = nullptr; \
    } \
private: \
    static CLASS* sp_Inst;

#define DUSK_SINGLETON_IMPL(CLASS) \
    CLASS* CLASS::sp_Inst = nullptr;

#endif // DUSK_SINGLETON_HPP