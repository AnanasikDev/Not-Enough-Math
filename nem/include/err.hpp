#pragma once

#include <stdexcept>
#include <limits>

#include "config.hpp"
#include "nan.hpp"

namespace nem
{
    namespace error
    {
        enum class Kind : unsigned char
        {
            RuntimeError = 0,
            OutOfRange,
            DivisionByZero,
            InvalidArgument,
            ZeroVector,
        };

        namespace internal
        {
            template <nem::scalar_type T>
            NEM_INLINE T invalid_result_base()
            {
#ifdef NEM_ERR_USE_NAN
                return std::numeric_limits<T>::quiet_NaN();
#else
                return (T)0.0;
#endif
            }

            /// <summary>
            /// For non-scalar objects
            /// </summary>
            template <typename T>
            NEM_INLINE T invalid_result_base()
            {
#ifdef NEM_ERR_USE_NAN
                return T::NaN();
#else
                return T{ };
#endif
            }

            NEM_INLINE void push_log(nem_string msg)
            {
                printf("%s\n", GET_C_STRING(msg));
            }

            NEM_INLINE void push_log_prefix(nem_string prefix, nem_string msg)
            {
                printf("%s %s\n", GET_C_STRING(prefix), GET_C_STRING(msg));
            }

            NEM_INLINE void force_log(nem_string msg, nem::error::Kind type = Kind::RuntimeError)
            {
                switch (type)
                {
                    case Kind::InvalidArgument: push_log_prefix("Not Enough Math [Invalid Argument] Error: ", msg); break;
                    case Kind::DivisionByZero: push_log_prefix("Not Enough Math [Division By Zero] Error: ", msg); break;
                    case Kind::OutOfRange: push_log_prefix("Not Enough Math [Out Of Range] Error: ", msg); break;
                    default: push_log_prefix("Not Enough Math Error: ", msg); break;
                }
            }

            NEM_INLINE bool force_throw(nem_string msg, nem::error::Kind type = Kind::RuntimeError)
            {
#ifdef _STDEXCEPT_
                switch (type)
                {
                    case Kind::OutOfRange:
                    {
                        throw std::out_of_range(msg);
                    } break;
                    case Kind::DivisionByZero:
                    {
                        throw std::logic_error(msg);
                    } break;
                    case Kind::InvalidArgument:
                    {
                        throw std::invalid_argument(msg);
                    } break;
                    case Kind::RuntimeError:
                    default:
                    {
                        throw std::runtime_error(msg);
                    }
                }
                return true;
#endif
                return false;
            }
        }

        NEM_INLINE void report(nem_string msg, nem::error::Kind type = Kind::RuntimeError)
        {
#ifdef NEM_ERR_THROW
            internal::force_throw(msg, type);
#endif
#ifdef NEM_ERR_LOG
            internal::force_log(msg, type);
#endif
        }

        NEM_INLINE void report_invalid(nem::error::Kind kind = Kind::RuntimeError, const char* const msg = nullptr)
        {
#ifdef NEM_ERR_THROW
            internal::force_throw(msg ? msg : "Invalid result", kind);
#endif
#ifdef NEM_ERR_LOG
            internal::force_log(msg ? msg : "Invalid result", kind);
#endif
        }

        template <typename T>
        NEM_INLINE T invalid_result(nem::error::Kind kind = Kind::RuntimeError, const char* const msg = nullptr)
        {
            report_invalid(kind, msg);
            return internal::invalid_result_base<T>();
        }
    }
}
