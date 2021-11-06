/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proto.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaccome <lzaccome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 12:52:24 by rmechety          #+#    #+#             */
/*   Updated: 2021/11/06 04:59:15 by lzaccome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTO_H
# define PROTO_H

# include "pipex.h"

/* -------------------------------------------------------------------------- */
/*                              FILE = ./main.c                               */
/* -------------------------------------------------------------------------- */
char	*cat_cmd(char *split, char *cmd);
char	*cmd_search(char **envp, char *argv, char **split, char *path_cmd);
int		main(int argc, char **argv, char **envp);

/* -------------------------------------------------------------------------- */
/*                              FILE = ./split.c                              */
/* -------------------------------------------------------------------------- */
char	**bc_malloc_norm(unsigned int wdct, char c, char **spl, char const *s);
char	**ft_split(char const *s, char c);

/* -------------------------------------------------------------------------- */
/*                              FILE = ./split2.c                             */
/* -------------------------------------------------------------------------- */
char	**free_all(char **spl, unsigned int j);
void	free_split(char **split);

/* -------------------------------------------------------------------------- */
/*                              FILE = ./error.c                              */
/* -------------------------------------------------------------------------- */
void	wrong_number_arg(void);
void	free_split_error(char **split);
void	free_error(char **split);
void	error(void);

/* -------------------------------------------------------------------------- */
/*                              FILE = ./path_env.c                           */
/* -------------------------------------------------------------------------- */
char	*reach_path(char **envp);
char	*cmd_search(char **envp, char *argv, char **split, char *path_cmd);

/* -------------------------------------------------------------------------- */
/*                              FILE = ./utils.c                            */
/* -------------------------------------------------------------------------- */
int		ft_strncmp(char *s1, char *s2, unsigned int n);
size_t	strlen(const char *s);

#endif
