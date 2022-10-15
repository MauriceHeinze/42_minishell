#include "../inc/minishell.h"

char	*str_add(char *orig, char *new_part, int pos)
{
	int		i;
	int		orig_i;
	int		new_part_i;
	int		max_len;
	char	*copy;


	printf("\nDEBUG PART 1:\n");
	printf("pos	%d\n", pos);
	printf("orig:	%s\n", orig);
	printf("new_part:	%s\n\n", new_part);

	pos--;
	i = 0;
	orig_i = 0;
	new_part_i = 0;
	max_len = ft_strlen(orig) + ft_strlen(new_part) + 1;
	copy = malloc(sizeof(char) * max_len);
	if (!copy || !orig || !new_part)
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
	printf("DEBUG PART 2:\n");
	printf("pos	%d\n", pos);
	printf("orig:	%s\n", orig);
	printf("i:	%d\n", i);
	printf("orig_i:	%d\n", orig_i);
	printf("Last char of copy:	%c\n", copy[i - 1]);
	printf("Last char of orig:	%c\n", orig[orig_i - 1]);
	printf("Result:\n%s\n", copy);

	return (copy);
}
