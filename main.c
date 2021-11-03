/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaccome <lzaccome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 18:53:25 by lzaccome          #+#    #+#             */
/*   Updated: 2021/11/03 04:03:13 by lzaccome         ###   ########.fr       */
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

void	free_split(char **split)
{
	int i;

	i = 0;
	while(split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	return;
}

void	error(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}

char	*cat_cmd(char *split, char *cmd)
{
	int		i;
	int		j;
	char	*ret;

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
	unsigned int	i;

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

char	*cmd_search(char **envp, char *argv)
{
	int		i;
	char	*str;
	char	**split;
	char	*path_cmd;

	i = 0;
	str = NULL;
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
				error();
			if (!access(path_cmd, F_OK))
				return (path_cmd);
			i++;
		}
	}
	error();
	return (NULL);
}

void	exec_cmd(char **envp, char *argv_n)
{
	char	**cmd;
	char	*path_cmd;

	cmd = ft_split(argv_n, ' ');
	if (!cmd)
		error();
	path_cmd = cmd_search(envp, cmd[0]);
	execve(path_cmd, cmd, envp);
	free(path_cmd);
	free_split(cmd);
	return ;
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	int		file1;
	int		file2;

	if (argc != 5)
	{
		write(2 , "Wrong number of arguments \n", 28);
		return 0;		
	} 
	if (pipe(fd) == -1)
		return (0);

	int pid1 = fork();
	if (pid1 < 0)
		return 0;

	if (pid1 == 0)
	{
		file1 = open(argv[1], O_RDONLY);
		if (file1 == -1)
			error();
		dup2(file1, STDIN_FILENO);
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		exec_cmd(envp, argv[2]);
		close(file1);
	}

	int pid2 = fork();
	if (pid2 < 0)
		return 0;

	if (pid2 == 0)
	{
		file2 = open(argv[4], O_WRONLY | O_CREAT | S_IRWXU, 777);
		if (file2 == -1)
			error();
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		dup2(file2, STDOUT_FILENO);
		close(fd[1]);
		exec_cmd(envp, argv[3]);
		close(file2);
	}

	close(fd[0]);
	close(fd[1]);

	waitpid(pid2, NULL, 0);
	waitpid(pid1, NULL, 0);
	return 0;
}