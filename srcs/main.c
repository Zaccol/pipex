/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaccome <lzaccome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 18:53:25 by lzaccome          #+#    #+#             */
/*   Updated: 2021/11/06 15:00:17 by lzaccome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/proto.h"

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

void	exec_cmd(char **envp, char *argv_n)
{
	char	**split;
	char	**cmd;
	char	*path_cmd;
	char	*search;

	search = NULL;
	split = NULL;
	while (*argv_n == ' ')
		argv_n++;
	if (*argv_n == '\0')
		error();
	cmd = ft_split(argv_n, ' ');
	if (!cmd)
		error();
	path_cmd = cmd_search(envp, cmd[0], split, search);
	if (!path_cmd)
	{
		free_split(cmd);
		error();
	}
	execve(path_cmd, cmd, envp);
	free(path_cmd);
	free_split(cmd);
	return ;
}

void	write_to_pipe(int *fd, char **argv, char **envp)
{
	int	file1;

	file1 = open(argv[1], O_RDONLY);
	if (file1 == -1)
		error();
	dup2(file1, STDIN_FILENO);
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	close(file1);
	exec_cmd(envp, argv[2]);
}

void	read_from_pipe(int *fd, char **argv, char **envp)
{
	int	file2;

	file2 = open(argv[4], O_WRONLY | O_CREAT, 0666);
	if (file2 == -1)
		error();
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	dup2(file2, STDOUT_FILENO);
	close(fd[1]);
	close(file2);
	exec_cmd(envp, argv[3]);
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	int		pid1;
	int		pid2;

	if (argc != 5 || (*argv[2] == 0) || (*argv[3] == 0))
		wrong_number_arg();
	if (pipe(fd) == -1)
		error();
	pid1 = fork();
	if (pid1 < 0)
		error();
	if (pid1 == 0)
		write_to_pipe(fd, argv, envp);
	pid2 = fork();
	if (pid2 < 0)
		error();
	if (pid2 == 0)
		read_from_pipe(fd, argv, envp);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid2, NULL, 0);
	waitpid(pid1, NULL, 0);
	return (0);
}
