/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaccome <lzaccome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 04:54:16 by lzaccome          #+#    #+#             */
/*   Updated: 2021/11/06 05:03:02 by lzaccome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/proto.h"

char	*reach_path(char **envp)
{
	int		i;
	char	*str;

	i = 0;
	str = NULL;
	if (!envp)
		return (NULL);
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		str = envp[i];
	return (str);
}

char	*cmd_search(char **envp, char *argv, char **split, char *path_cmd)
{
	int		i;
	char	*str;

	i = 0;
	str = reach_path(envp);
	if (str)
	{
		split = ft_split((str + 5), ':');
		if (!split)
			free_error(split);
		while (split && split[i])
		{
			path_cmd = cat_cmd(split[i], argv);
			if (!path_cmd)
				free_split_error(split);
			if (!access(path_cmd, X_OK))
				return (path_cmd);
			free(path_cmd);
			path_cmd = NULL;
			i++;
		}
	}
	free(path_cmd);
	free_split(split);
	return (NULL);
}
