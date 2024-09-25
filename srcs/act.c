/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 20:13:07 by gmarquis          #+#    #+#             */
/*   Updated: 2024/09/25 10:02:41 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/proto.h"

void	ph_eating(t_philo *tmp)
{
	t_philo *philo = tmp;
	size_t	init_time;

	init_time = ph_actualtime();
	*philo->philo_state = EAT;
	ph_speaking(&philo->epís->mprintf, philo->epís->start_time, philo->id, LPRO_EAT);
	while (1)
	{
		if(ph_actualtime() - init_time >= philo->epís->time_to_eat)
			break ;
	}
	philo->last_meal = ph_actualtime();
	philo->count_meal++;
	if (philo->epís->n_meal > 0)
	{
		if (philo->count_meal >= philo->epís->n_meal)
			*(philo->philo_meal) = -1;
	}
}

void	ph_sleeping(t_philo *tmp)
{
	t_philo *philo = tmp;
	size_t	init_time;

	init_time = ph_actualtime();
	*philo->philo_state = SLEEP;
	ph_speaking(&philo->epís->mprintf, philo->epís->start_time, philo->id, LPRO_SLEEP);
	while (1)
	{
		if(ph_actualtime() - init_time >= philo->epís->time_to_sleep)
			break ;
	}
	*philo->philo_state = THINK;
}
