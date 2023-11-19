#pragma once

// Credit to Skyth / DML

#include <list>
#include <vector>
#include "Allocator.hpp"


// Using std types allocated within the game require us to manipulate
// them with the same allocator, otherwise we'll run into crashes.
// The types have been put under the "prj" namespace for differentiation.
namespace prj
{
    using string = std::basic_string<char, std::char_traits<char>, GameAllocator<char>>;

    template<typename T>
    using vector = std::vector<T, GameAllocator<T>>;

    template<typename T>
    using list = std::list<T, GameAllocator<T>>;

    template <class T>
    struct default_delete
    {
        void operator()(T* ptr) const noexcept
        {
            customFree(ptr);
        }
    };

    template <class T>
    struct default_delete<T[]>
    {
        void operator()(T* ptr) const noexcept
        {
            static_assert(std::is_trivially_destructible_v<T>); // Needs to be trivially destructible for now
            customFree(ptr);
        }
    };

    template<typename T>
    using unique_ptr = std::unique_ptr<T, default_delete<T>>;
}