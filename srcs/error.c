/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaccome <lzaccome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 04:48:51 by lzaccome          #+#    #+#             */
/*   Updated: 2021/11/06 05:02:51 by lzaccome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/proto.h"

void	wrong_number_arg(void)
{
	write(2, "Wrong number of arguments \n", 28);
	exit(1);
}

void	free_split_error(char **split)
{
	free_split(split);
	error();
}

void	free_error(char **split)
{
	free(split);
	error();
}

void	error(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}
