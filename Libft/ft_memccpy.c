#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
    unsigned char   *cpy_dst;
    unsigned char   *cpy_src;
    unsigned char   chk;
    size_t          i;

    cpy_dst = dst;
    cpy_src = (unsigned char *)src;
    chk = 0;
    while (i < n)
    {
        cpy_dst[i] = cpy_src[i];
        if (cpy_src[i] == chk)
            return (dst + (i + 1));
        i++;
    }
    return (0);
}