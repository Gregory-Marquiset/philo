/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:08:00 by gmarquis          #+#    #+#             */
/*   Updated: 2024/08/27 03:50:33 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

static size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_exit(int fd_out, char *message, int error_code)
{
	if (message)
		write(fd_out, message, ft_strlen(message));
	exit(error_code);
}

void	ft_leave_table(t_college *college, int fd_out, char *message,
	int error_code)
{
	int	i;

	i = 0;
	if (college->philos)
	{
		while (college->philos[i])
		{
			pthread_mutex_destroy(&college->philos[i]->left_chopstick);
			free(college->philos[i]);
			i++;
		}
		free(college->philos);
	}
	if (college->utils)
		free(college->utils);
	ft_exit(fd_out, message, error_code);
}
