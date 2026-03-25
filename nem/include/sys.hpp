#pragma once

#if defined(_MSVC_LANG)
    #define NEM_CPP_VERSION _MSVC_LANG
#else
    #define NEM_CPP_VERSION __cplusplus
#endif

#define NEM_CPP_00 199711L
#define NEM_CPP_11 201103L
#define NEM_CPP_14 201402L
#define NEM_CPP_17 201703L
#define NEM_CPP_20 202002L
#define NEM_CPP_23 202302L

#define NEM_CPP_20_OR_HIGHER() ( NEM_CPP_VERSION >= NEM_CPP_20 )
#define NEM_CPP_17_OR_HIGHER() ( NEM_CPP_VERSION >= NEM_CPP_17 )
#define NEM_CPP_14_OR_HIGHER() ( NEM_CPP_VERSION >= NEM_CPP_14 )
#define NEM_CPP_11_OR_HIGHER() ( NEM_CPP_VERSION >= NEM_CPP_11 )

#if NEM_CPP_20_OR_HIGHER()
#include <bit>
#endif

namespace nem
{
    namespace sys
    {
        namespace language
        {
            // C++

            using VersionT = unsigned char;

            enum class LanguageVersion : VersionT
            {
                _00 = 0,
                _11,
                _14,
                _17,
                _20,
                _23
            };

            namespace internal
            {
                constexpr LanguageVersion compute_version()
                {
                    if      constexpr (NEM_CPP_VERSION >= NEM_CPP_23) return LanguageVersion::_23;
                    else if constexpr (NEM_CPP_VERSION >= NEM_CPP_20) return LanguageVersion::_20;
                    else if constexpr (NEM_CPP_VERSION >= NEM_CPP_17) return LanguageVersion::_17;
                    else if constexpr (NEM_CPP_VERSION >= NEM_CPP_14) return LanguageVersion::_14;
                    else if constexpr (NEM_CPP_VERSION >= NEM_CPP_11) return LanguageVersion::_11;
                    else                                              return LanguageVersion::_00;
                }
                constexpr LanguageVersion versionid = compute_version();

                constexpr LanguageVersion impl_language_version()
                {
                    return versionid;
                }
            }

            constexpr LanguageVersion language_version()
            {
                return internal::impl_language_version();
            }

            constexpr bool is_23_or_higher() { return language_version() >= LanguageVersion::_23; }
            constexpr bool is_20_or_higher() { return language_version() >= LanguageVersion::_20; }
            constexpr bool is_17_or_higher() { return language_version() >= LanguageVersion::_17; }
            constexpr bool is_14_or_higher() { return language_version() >= LanguageVersion::_14; }
            constexpr bool is_11_or_higher() { return language_version() >= LanguageVersion::_11; }
            constexpr bool is_below_11() { return language_version() == LanguageVersion::_00; }

        } // language
            
        namespace byte
        {
#if NEM_CPP_20_OR_HIGHER()
            constexpr bool little = (std::endian::native == std::endian::little);
#define NEM_LITTLE_ENDIAN 1
#define NEM_BIG_ENDIAN 0
#elif defined(_WIN32)
            constexpr bool little = true;
#define NEM_LITTLE_ENDIAN 1
#define NEM_BIG_ENDIAN 0
#elif defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define NEM_LITTLE_ENDIAN 1
#define NEM_BIG_ENDIAN 0
            constexpr bool little = true;
#elif defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define NEM_LITTLE_ENDIAN 0
#define NEM_BIG_ENDIAN 1
            constexpr bool little = false;
#else
#error "Cannot determine endianness"
#endif

            constexpr bool is_little() { return little; }
            constexpr bool is_big() { return !little; }

#if NEM_LITTLE_ENDIAN
            template <typename T>
            constexpr T shift_lower(T value, int delta = 1) { value >> delta; return value; }
#elif NEM_BIG_ENDIAN
            template <typename T>
            constexpr T shift_lower(T value, int delta = 1) { value << delta; return value; }
#else
#error "Cannot use endianness"
#endif

#if NEM_LITTLE_ENDIAN
            template <typename T>
            constexpr T shift_higher(T value, int delta = 1) { value << delta; return value; }
#elif NEM_BIG_ENDIAN
            template <typename T>
            constexpr T shift_higher(T value, int delta = 1) { value >> delta; return value; }
#else
#error "Cannot use endianness"
#endif
        } // byte
    }
}

#ifdef NEM_CPP_VERSION
#undef NEM_CPP_VERSION
#endif
