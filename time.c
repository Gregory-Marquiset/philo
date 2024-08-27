/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 17:56:48 by gmarquis          #+#    #+#             */
/*   Updated: 2024/08/26 22:16:33 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

static size_t	ft_actualtime(void)
{
	struct timeval	t_val;

	if (gettimeofday(&t_val, NULL))
	{
		printf("Error: echec gettimeofday\n");
		return (0);
	}
	return (t_val.tv_sec * 1000 + t_val.tv_usec / 1000);
}

void	ft_sleep(size_t inter)
{
	size_t	init_time;

	init_time = ft_actualtime();
	while (1)
	{
		if(ft_actualtime() - init_time >= inter)
			break ;
	}
}

void	ft_philo_sleeping(int id, size_t time)
{
	printf("%ld %d is sleeping\n", time, id);
}

void	ft_philo_thinking(int id, size_t time)
{
	printf("%ld %d is thinking\n", time, id);
}

void	ft_philo_died(t_college *college, int id, size_t time)
{
	printf("%ld %d died\n", time, id);
	ft_leave_table(college, 1, "", 123);
}
