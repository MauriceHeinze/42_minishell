#include "../inc/minishell.h"

char	*str_remove_word(char *orig, unsigned int start, size_t len)
{
	int		i;
	int		orig_i;
	int		new_part_i;
	char	*copy;

	if (start > 0)
		start--;
	i = 0;
	orig_i = 0;
	new_part_i = 0;
	copy = malloc(sizeof(char) * (ft_strlen(orig) + 1));
	if (!copy || !orig)
		return (NULL);
	// copy original until start is reached
	while (orig[orig_i] != '\0' && (i < start))
		copy[i++] = orig[orig_i++];
	// skip part to remove
	while (orig[orig_i] != '\0' && ((orig_i - start) < len))
		orig_i++;
	// copy original until end is reached
	while (orig[orig_i] != '\0')
		copy[i++] = orig[orig_i++];
	copy[i] = '\0';
	free(orig);
	return (copy);
}