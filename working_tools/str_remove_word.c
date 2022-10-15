#include "../inc/minishell.h"

char	*str_remove_word(char const *orig, unsigned int start, size_t len)
{
	int		i;
	int		orig_i;
	int		new_part_i;
	char	*copy;

	// printf("DEBUG PART 1:\n");
	// printf("len	%zu\n", len);
	// printf("start	%d\n", start);
	// printf("orig:	%s\n", orig);
	// printf("str len:	%zu\n", ft_strlen(orig));

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

	// printf("DEBUG PART 2:\n");
	// printf("len	%zu\n", len);
	// printf("start	%d\n", start);
	// printf("orig:	%s\n", orig);
	// printf("i:	%d\n", i);
	// printf("orig_i:	%d\n", orig_i);
	// printf("Last char of copy:	%c\n", copy[i - 1]);
	// printf("Last char of orig:	%c\n", orig[orig_i - 1]);
	// printf("Result:\n%s\n", copy);
	return (copy);
}
// echo $PWD/path | echo $USER
