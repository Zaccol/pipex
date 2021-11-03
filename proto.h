/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proto.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaccome <lzaccome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 12:52:24 by rmechety          #+#    #+#             */
/*   Updated: 2021/11/03 01:27:23 by lzaccome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTO_H
# define PROTO_H

# include "pipex.h"

/* -------------------------------------------------------------------------- */
/*                              FILE = ./main.c                               */
/* -------------------------------------------------------------------------- */
size_t	strlen(const char *s);
char	*cat_cmd(char *split, char *cmd);
int		ft_strncmp(char *s1, char *s2, unsigned int n);
char	*cmd_search(char **envp, char *argv);
int		main(int argc, char **argv, char **envp);

/* -------------------------------------------------------------------------- */
/*                              FILE = ./split.c                              */
/* -------------------------------------------------------------------------- */
char	**ft_split(char const *s, char c);
void	free_split(char **split);

#endif
