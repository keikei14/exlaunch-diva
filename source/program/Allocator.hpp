#pragma once

// Credit to Skyth / DML

#include "lib.hpp"

void* (*customMalloc)(size_t) = reinterpret_cast<void*(*)(size_t)>(exl::util::modules::GetTargetOffset(0x4bd80));
void (*customFree)(void*) = reinterpret_cast<void(*)(void*)>(exl::util::modules::GetTargetOffset(0x4bdf0));
void* (*customNew)(size_t) = reinterpret_cast<void*(*)(size_t)>(exl::util::modules::GetTargetOffset(0x9f87c0));
void (*customDelete)(void*) = reinterpret_cast<void(*)(void*)>(exl::util::modules::GetTargetOffset(0x9f87a0));

template <class T>
class GameAllocator
{
public:
    using value_type = T;

    GameAllocator() noexcept {}
    template <class U> GameAllocator(GameAllocator<U> const&) noexcept {}

    value_type* allocate(std::size_t n)
    {
        return reinterpret_cast<value_type*>(customNew(n * sizeof(value_type)));
    }

    void deallocate(value_type* p, std::size_t) noexcept
    {
        customDelete(reinterpret_cast<void*>(p));
    }
};

template <class T, class U>
bool operator==(GameAllocator<T> const&, GameAllocator<U> const&) noexcept
{
    return true;
}

template <class T, class U>
bool operator!=(GameAllocator<T> const& x, GameAllocator<U> const& y) noexcept
{
    return !(x == y);
}