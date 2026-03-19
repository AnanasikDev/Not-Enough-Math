#pragma once

#include <concepts>
#include <limits>

#include "config.hpp"

namespace nem
{
    template <typename T>
    concept CanBeNaN = std::floating_point<T> || 
        (requires 
        {
            { std::numeric_limits<T>::has_quiet_NaN } -> std::convertible_to<bool>;
            requires std::numeric_limits<T>::has_quiet_NaN;
        }
        );

    template<typename T>
    concept CanBeNaNIfConfig = std::conditional_t<
        ERR_USE_NAN,
        std::bool_constant<CanBeNaN<T>>,
        std::true_type
    >::value;
}