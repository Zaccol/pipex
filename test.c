/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaccome <lzaccome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 06:07:05 by lzaccome          #+#    #+#             */
/*   Updated: 2021/11/02 01:28:55 by lzaccome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

// SPLIT

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

	// FIN SPLIT 

size_t	strlen(const char *s)
{
	unsigned int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char *cat_cmd(char *split, char *cmd)
{
	int i;
	int j;
	char *ret;

	ret = malloc(sizeof(char) * (strlen(split) + strlen(cmd) + 2));
	if (ret == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (split[i])
	{
		ret[i] = split[i];
		i++;
	}
	ret[i++] = '/';
	while (cmd[j])
		ret[i++] = cmd[j++];
	ret[i] = '\0';
	return (ret);
}

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int i;

	i = 0;
	if (n == 0)
		return (0);
	if (s1 == NULL || s2 == NULL)
		return (-1);
	while (s1[i] && s2[i] && (unsigned char)s1[i] == (unsigned char)s2[i]
	&& i < (n - 1))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char *cmd_search(char **envp, char *argv)
{
	int		i;
	char	*str;
	char	**cmd;
	char	**split;
	char	*path_cmd;
	
	i = 0;
	cmd = ft_split(argv, ' ');
	if (!cmd)
		return (NULL);
	while (cmd[i])
	{
		printf("%s\n", cmd[i]);
		i++;
	}
	if (!envp)
		return (NULL);
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		str = envp[i];
	if (str)
	{
		split = ft_split((str + 5), ':');
		i = 0;
		while (split && split[i])
		{
			path_cmd = cat_cmd(split[i], cmd[0]);
			if (!path_cmd)
				return (NULL);
			if (!access(path_cmd, F_OK))
				return (path_cmd);
			i++;
		}
	}
	return (NULL);
}

int	main(int argc, char **argv, char **envp)
{
	// char *split;
	// char *cmd;
	char *test;

	// split = "path";
	// cmd = "ls";
	// test = cat_cmd(split, cmd);
	// printf("%s\n", test);
	test = cmd_search(envp, argv[2]);
	printf("%s\n", test);
}