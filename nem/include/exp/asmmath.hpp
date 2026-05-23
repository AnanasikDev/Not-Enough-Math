#pragma once

#include <stdio.h>

namespace nem
{
    namespace experimental
    {
        namespace asmmath
        {
            void mul(int a, int b)
            {
                /*int dst = a;
                asm("imull %1, %0"
                    : "+r" (dst)
                    : "r" (b));

                printf("%d\n", dst);*/
            }

            void sin(float t)
            {
                /*float result;
                asm("fsin"
                    : "=t" (result) 
                    : "0" (t));1

                printf("sin(%f) = %f\n", t, result);*/
            }
        }
    }
}