#include "libft.h"

void    *ft_memset(void *dst, int c, size_t n)
{
    unsigned char   *copy_dst;
    unsigned char   src;

    copy_dst = dst;
    src = c;
    while(n-- > 0)
        *copy_dst++ = src;
    return (dst);
}
