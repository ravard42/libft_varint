#include "libft.h"

size_t			ft_strlen(const char *s)
{
	size_t	i;

	if (!s && ft_dprintf(2, "%strying to ft_strlen(NULL)... 0 returned%s\n", KYEL, KNRM))
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t			ft_wstrlen(wchar_t *wc)
{
	int		i;

	if (!wc && ft_dprintf(2, "%strying to ft_wstrlen(NULL)... 0 returned%s\n", KYEL, KNRM))
		return (0);
	i = -1;
	while (wc[++i])
		;
	return (i);
}
