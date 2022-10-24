#include "../inc/minishell.h"

char	*str_add(char *orig, char *new_part, int pos)
{
	int		i;
	int		orig_i;
	int		new_part_i;
	int		max_len;
	char	*copy;

	if (!new_part && orig)
		return (orig);
	pos--;
	i = 0;
	orig_i = 0;
	new_part_i = 0;
	max_len = ft_strlen(orig) + ft_strlen(new_part) + 1;
	copy = malloc(sizeof(char) * max_len);
	if (!copy || !orig)
		return (NULL);
	// copy original until pos reached
	while (orig[orig_i] != '\0' && (i < max_len && i < pos))
		copy[i++] = orig[orig_i++];
	// copy new_part
	while (new_part[new_part_i] != '\0')
		copy[i++] = new_part[new_part_i++];
	// copy original until end is reached
	while (orig[orig_i] != '\0')
		copy[i++] = orig[orig_i++];
	copy[i] = '\0';
	free(orig);
	return (copy);
}
