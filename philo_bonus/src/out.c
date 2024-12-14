/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:08:00 by gmarquis          #+#    #+#             */
/*   Updated: 2024/12/04 08:37:06 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/proto.h"

static unsigned long	st_strlen(char *str)
{
	unsigned long (i) = 0;
	while (str[i])
		i++;
	return (i);
}

static void	st_exit(int fd_out, char *message, int error_code)
{
	if (message)
		write(fd_out, message, st_strlen(message));
	exit(error_code);
}

void	phb_quit_philo(t_sympos *sympos, int fd_out, char *message,
	int error_code)
{
	int	n_philos;
	int	i;

	n_philos = 0;
	i = 0;
	if (sympos)
	{
		n_philos = sympos->n_philos;
		if (sympos->philos)
		{
			while (i < n_philos)
			{
				free(sympos->philos[i].agal);
				i++;
			}
			free(sympos->philos);
		}
		free(sympos);
	}
	st_exit(fd_out, message, error_code);
}
