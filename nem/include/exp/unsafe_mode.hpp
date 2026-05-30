/*

This is purely design documentation ideas on how to make customizable, optimized and neat safety handling features in NEM. This is a WIP code that is further to be analyzed, tested and designed

struct safe_t   { explicit constexpr safe_t()   = default; };
struct unsafe_t { explicit constexpr unsafe_t() = default; };

inline constexpr safe_t   safe{};
inline constexpr unsafe_t unsafe{};

/// <summary>
/// Calculates euclidean modulo of a % b = r, where r belongs to [0, b). Unline standard C++ modulo operator, works with any floating-point numbers and can never yield negative numbers.
/// </summary>
template <nem::scalar_type T> constexpr T mod(T a, T b, nem::unsafe_t)
{
    const T absb = nem::abs(b);
    const T v = a - nem::floor(a / b) * b;
    const T r = v < 0 ? v + absb : v;
    return nem::equal(r, absb) ? (T)0.0 : r;
}

/// <summary>
/// Calculates euclidean modulo of a % b = r, where r belongs to [0, b). Unline standard C++ modulo operator, works with any floating-point numbers and can never yield negative numbers.
/// </summary>
template <nem::scalar_type T> constexpr T mod(T a, T b, nem::safe_t = nem::safe)
{
    if (nem::is_zero(b))
    {
        return nem::error::invalid_result<T>(nem::error::Kind::DivisionByZero);
    }
    return nem::mod(a, b, nem::unsafe);
}

*/