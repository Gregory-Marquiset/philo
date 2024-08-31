/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 20:13:07 by gmarquis          #+#    #+#             */
/*   Updated: 2024/08/31 18:38:18 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/proto.h"

void	ft_eating(t_philo *tmp)
{
	t_philo *philo = tmp;
	size_t	init_time;

	init_time = ft_actualtime();
	philo->state = EAT;
	ft_speaking(&philo->epís->mprintf, philo->epís->start_time, philo->id, LPRO_EAT);
	while (1)
	{
		if(ft_actualtime() - init_time >= philo->epís->time_to_eat)
			break ;
	}
	philo->last_meal = ft_actualtime();
	philo->count_meal++;
	if (philo->count_meal >= philo->epís->n_meal)
		philo->epís->meal_stat[philo->id - 1] = 1;
}

void	ft_sleeping(t_philo *tmp)
{
	t_philo *philo = tmp;
	size_t	init_time;

	init_time = ft_actualtime();
	philo->state = SLEEP;
	ft_speaking(&philo->epís->mprintf, philo->epís->start_time, philo->id, LPRO_SLEEP);
	while (1)
	{
		if(ft_actualtime() - init_time >= philo->epís->time_to_sleep)
			break ;
	}
	philo->state = THINK;
}
