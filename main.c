/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaccome <lzaccome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 18:53:25 by lzaccome          #+#    #+#             */
/*   Updated: 2021/11/02 01:42:36 by lzaccome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proto.h"

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

// char **get_flag(char *argv)
// {
// 	int		i;
// 	char 	**cmd;

// 	i = 0;
// 	while (argv[i])
// 	{
// 		if (argv[i] == ' ' || argv[i] == '	')
// 			{
// 				cmd = ft_split(argv, argv[i]);
// 				return (cmd);
// 			}
// 		i++;
// 	}
// 	return (NULL);
// }

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
	char 	**flag;
	char	**split;
	char	*path_cmd;
	
	i = 0;
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
			path_cmd = cat_cmd(split[i], argv);
			if (!path_cmd)
				return (NULL);
			if (!access(path_cmd, F_OK))
				return (path_cmd);
			i++;
		}
	}
	return (NULL);
}

void	exec_cmd(char **envp, char *argv_n)
{
	char	**cmd;
	char	*path_cmd;
	
	cmd = ft_split(argv_n, ' ');
	if (!cmd)
		return ;
	path_cmd = cmd_search(envp, cmd[0]); /*cmd_str*/
	execve(path_cmd, cmd, envp);  /*flag*/
	free(cmd);
	return ;
}

int	main(int argc, char **argv, char **envp)
{
	int		i;
	char	*cmd_str;
	char	*cmd2;
	char	**flag;

	int fd[2];

	if (pipe(fd) == -1)
		return 0;

	int pid1 = fork();
	if (pid1 < 0)
	{
		return 0;
	}

	if (pid1 == 0)
	{
		// open
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		exec_cmd(envp, argv[2]);
	}
	
	int pid2 = fork();
	if (pid2 < 0)
	{
		return 0;
	}

	if (pid2 == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		exec_cmd(envp, argv[3]);
	}
	
	close (fd[0]);
	close (fd[1]);

	waitpid(pid2, NULL, 0);
	waitpid(pid1, NULL, 0);
	return 0;
}