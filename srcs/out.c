/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:08:00 by gmarquis          #+#    #+#             */
/*   Updated: 2024/09/25 10:44:03 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/proto.h"

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

void	ph_quit_philo(t_sympos *sympos, int fd_out, char *message,
	int error_code)
{
	int	i;
	int	tmp_n_philos;

	i = 0;
	if (sympos)
	{
		if (sympos->epis)
		{
			tmp_n_philos = sympos->epis->n_philos;
			pthread_mutex_destroy(&sympos->epis->mprintf);
			free(sympos->epis->philos_states);
			free(sympos->epis->philos_meals);
			free(sympos->epis);
		}
		if (sympos->philos)
		{
			while (i < tmp_n_philos)
			{
				pthread_mutex_destroy(&sympos->philos[i].lf_fork);
				i++;
			}
			free(sympos->philos);
		}
		free(sympos);
		}
	ph_exit(fd_out, message, error_code);
}
