#include "get_next_line.h"

void	*ft_memset(void *dest, int c, size_t len)
{
    char	*d;

    d = (char *)dest;
    while (len--)
        *d++ = c;
    return (dest);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
    char	*pointer;
    size_t	mem_size;

    mem_size = nmemb * size;
    pointer = malloc(mem_size);
    if (!(pointer))
        return (NULL);
    ft_memset(pointer, '\0', mem_size);
    return (pointer);
}