/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:08:00 by gmarquis          #+#    #+#             */
/*   Updated: 2024/08/30 01:45:47 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/philo.h"

static size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static void	ft_exit(int fd_out, char *message, int error_code)
{
	if (message)
		write(fd_out, message, ft_strlen(message));
	exit(error_code);
}

void	ft_quit_philo(t_sympos *sympos, int fd_out, char *message,
	int error_code)
{
	int	i;
	int	tmp_n_philos;

	i = 0;
	if (sympos)
	{
		if (sympos->epís)
		{
			tmp_n_philos = sympos->epís->n_philos;
			pthread_mutex_destroy(&sympos->epís->mprintf);
			free(sympos->epís->meal_stat);
			free(sympos->epís);
		}
		if (sympos->philos)
		{
			while (i < tmp_n_philos)
			{
				pthread_mutex_destroy(&sympos->philos[i].dexi_obeli);
				i++;
			}
			free(sympos->philos);
		}
		free(sympos);
		}
	ft_exit(fd_out, message, error_code);
}
