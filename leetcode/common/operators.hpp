#pragma once

#include <concepts>
#include <ostream>
#include <ranges>
#include <string_view>
#include <utility>

template <typename First, typename Second>
std::ostream& operator<<(std::ostream& stream, std::pair<First, Second> const& value);

template <std::ranges::input_range Range>
    requires(!std::convertible_to<Range const&, std::string_view>)
std::ostream& operator<<(std::ostream& stream, Range const& range);

template <typename First, typename Second>
std::ostream& operator<<(std::ostream& stream, std::pair<First, Second> const& value)
{
    return stream << '(' << value.first << ", " << value.second << ')';
}

template <std::ranges::input_range Range>
    requires(!std::convertible_to<Range const&, std::string_view>)
std::ostream& operator<<(std::ostream& stream, Range const& range)
{
    stream << '[';
    auto separator = "";
    for (auto const& value : range)
    {
        stream << separator << value;
        separator = ", ";
    }
    return stream << ']';
}
