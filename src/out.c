/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:08:00 by gmarquis          #+#    #+#             */
/*   Updated: 2024/09/26 08:04:06 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/proto.h"

static size_t	ph_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static void	ph_exit(int fd_out, char *message, int error_code)
{
	if (message)
		write(fd_out, message, ph_strlen(message));
	exit(error_code);
}

static void	*ph_free_epis(t_epis *epis, int *tmp_n_philos)
{
	if (epis->agal)
	{
		*tmp_n_philos = epis->agal->n_philos;
		free(epis->agal);
	}
	if (epis->kine)
	{
		free(epis->kine->phs_states);
		free(epis->kine->phs_meals);
		free(epis->kine);
	}
	pthread_mutex_destroy(&epis->mtx->printf);
	pthread_mutex_destroy(&epis->mtx->phs_meals);
	pthread_mutex_destroy(&epis->mtx->phs_states);
	pthread_mutex_destroy(&epis->mtx->sy_states);
	free(epis->mtx);
	return (NULL);
}

void	ph_quit_philo(t_sympos *sympos, int fd_out, char *message,
	int error_code)
{
	int (i) = 0;
	int (tmp_n_philos) = 0;
	if (sympos)
	{
		if (sympos->epis)
			sympos->epis = ph_free_epis(sympos->epis, &tmp_n_philos);
		if (sympos->philos)
		{
			while (i < tmp_n_philos)
			{
				pthread_mutex_destroy(&sympos->philos[i].lf_fork);
				free(sympos->philos[i].kine);
				i++;
			}
			free(sympos->philos);
		}
		free(sympos);
	}
	ph_exit(fd_out, message, error_code);
}
