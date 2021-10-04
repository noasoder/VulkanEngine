#pragma once

#include <assert.h>

template<typename T>
class Singleton {
public:
    static T& Instance() {
        if (Singleton::instance_ == 0) {
            Singleton::instance_ = CreateInstance();
            ScheduleForDestruction(Singleton::Destroy);
        }
        return *(Singleton::instance_);
    };
    static void Init() {
        if (Singleton::instance_ == 0) {
            Singleton::instance_ = CreateInstance();
            ScheduleForDestruction(Singleton::Destroy);
        }
    };
    static void Destroy() {
        if (Singleton::instance_ != 0) {
            DestroyInstance(Singleton::instance_);
            Singleton::instance_ = 0;
        }
    };

protected:
    inline explicit Singleton() {
        assert(Singleton::instance_ == 0);
        Singleton::instance_ = static_cast<T*>(this);
    }
    inline ~Singleton() {
        Singleton::instance_ = 0;
    }

private:
    static T* CreateInstance() { return new T(); };
    static void ScheduleForDestruction(void (*pFun)()) { std::atexit(pFun); };
    static void DestroyInstance(T* p) { delete p; };

private:
    static T* instance_;

private:
    inline explicit Singleton(Singleton const&) {}
    inline Singleton& operator=(Singleton const&) { return *this; }
};    //end of class Singleton

template<typename T>
T* Singleton<T>::instance_ = 0;