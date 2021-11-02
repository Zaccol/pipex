/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaccome <lzaccome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 05:09:33 by lzaccome          #+#    #+#             */
/*   Updated: 2021/10/29 06:30:46 by lzaccome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdlib.h>
# include <string.h>
# include <unistd.h>

static char			**part_cases(char const *s)
{
	char			**spl;

	if (!s)
		return (NULL);
	if (!(spl = malloc(sizeof(char *))))
		return (NULL);
	if (!(spl[0] = malloc(sizeof(char))))
		return (NULL);
	spl[0] = NULL;
	return (spl);
}

static char			**free_all(char **spl, unsigned int j)
{
	unsigned int	i;

	i = 0;
	while (i < j)
	{
		free(spl[i]);
		i++;
	}
	free(spl);
	return (NULL);
}

static unsigned int	get_word_count(char const *s, char c)
{
	unsigned int	count;
	int				i;

	count = 1;
	i = 0;
	while (s[i] == c)
		i++;
	if (s[i] == '\0')
		return (0);
	while (s[i])
	{
		if (s[i] == c && s[i + 1])
			if (s[i + 1] != c)
				count++;
		i++;
	}
	return (count);
}

static char			*fill_strs(char const *s, char c, unsigned int *i)
{
	int		j;
	char	*str;

	j = 0;
	while (s[j + *i] && s[j + *i] != c)
		j++;
	if (!(str = malloc(sizeof(char) * (j + 1))))
		return (NULL);
	j = 0;
	while (s[*i] && s[*i] != c)
	{
		str[j] = s[*i];
		(*i)++;
		j++;
	}
	(*i)++;
	str[j] = '\0';
	return (str);
}

char				**ft_split(char const *s, char c)
{
	unsigned int	wdct;
	char			**spl;
	unsigned int	i;
	unsigned int	j;

	if (!s || s[0] == '\0')
		return (part_cases(s));
	wdct = get_word_count(s, c);
	if (!(spl = malloc(sizeof(char *) * (wdct + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (j < wdct)
	{
		while (s[i] == c)
			i++;
		if (s[i])
			if (!(spl[j] = fill_strs(s, c, &i)))
				return (free_all(spl, j));
		j++;
	}
	spl[j] = NULL;
	return (spl);
}
