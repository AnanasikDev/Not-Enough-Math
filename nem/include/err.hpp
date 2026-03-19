#pragma once

#include <stdexcept>

#include "config.hpp"
#include "nan.hpp"

namespace nem
{
    namespace error
    {
        enum class Type : unsigned char
        {
            RuntimeError = 0,
            OutOfRange,
            DivisionByZero,
            InvalidArgument,
        };

        template <typename T>
        T invalid_result_base()
        {
#ifdef NEM_ERR_USE_NAN
            return T(NAN);
#else
            return T(0.0);
#endif
        }

        void push_log(nem_string msg)
        {
            printf("%s\n", GET_C_STRING(msg));
        }

        void push_log_prefix(nem_string prefix, nem_string msg)
        {
            printf("%s %s\n", GET_C_STRING(prefix), GET_C_STRING(msg));
        }

        void force_log(nem_string msg, nem::error::Type type = Type::RuntimeError)
        {
            switch (type)
            {
                case Type::InvalidArgument: push_log_prefix("Not Enough Math [Invalid Argument] Error: ", msg); break;
                case Type::DivisionByZero: push_log_prefix("Not Enough Math [Division By Zero] Error: ", msg); break;
                case Type::OutOfRange: push_log_prefix("Not Enough Math [Out Of Range] Error: ", msg); break;
                default: push_log_prefix("Not Enough Math Error: ", msg); break;
            }
        }

        bool force_throw(nem_string msg, nem::error::Type type = Type::RuntimeError)
        {
#ifdef _STDEXCEPT_
            switch (type)
            {
                case Type::OutOfRange:
                {
                    throw std::out_of_range(msg);
                } break;
                case Type::DivisionByZero:
                {
                    throw std::logic_error(msg);
                } break;
                case Type::InvalidArgument:
                {
                    throw std::invalid_argument(msg);
                } break;
                case Type::RuntimeError:
                default:
                {
                    throw std::runtime_error(msg);
                }
            }
            return true;
#endif
            return false;
        }

        void report(nem_string msg, nem::error::Type type = Type::RuntimeError)
        {
#ifdef NEM_ERR_THROW
            force_throw(msg, type);
#endif
#ifdef NEM_ERR_LOG
            force_log(msg, type);
#endif
        }

        template <typename T>
        T invalid_result(nem::error::Type type = Type::RuntimeError)
        {
            report("Invalid result", type);
            return invalid_result_base<T>();
        }
    }
}
