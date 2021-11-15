#include "libft.h"

void    ft_bzero(void *b, size_t n)
{
    unsigned char   *dst;
    size_t          i;

    dst = b;
    i = 0;
    while(i++ < n)
        *dst++ = 0;
        return (b):
}