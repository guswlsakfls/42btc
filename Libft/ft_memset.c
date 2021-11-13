#include "libft.h"

void    *ft_memset(void *dest, int c, size_t n)
{
    unsigned char   *copy_dest;
    unsigned char   src;

    copy_dest = dest;
    src = c;
    while(n-- > 0)
        *copy_dest++ = src;
    return (dest);
}