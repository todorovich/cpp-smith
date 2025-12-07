#pragma once

#include <unordered_map>
#include <unordered_set>

struct StrHash
{
    using is_transparent = void;
    size_t operator()(const std::string_view view) const noexcept
    {
        return std::hash<std::string_view>{}(view);
    }
};

struct StrEq
{
    using is_transparent = void;
    bool operator()(const std::string_view left, const std::string_view right) const noexcept
    {
        return left == right;
    }
};

template<class T>
using TransparentUnorderedSet = std::unordered_set<T, StrHash, StrEq>;

template<class K, class V>
using TransparentUnorderedMap = std::unordered_map<K, V, StrHash, StrEq>;