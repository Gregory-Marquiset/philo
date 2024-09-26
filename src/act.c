/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 20:13:07 by gmarquis          #+#    #+#             */
/*   Updated: 2024/09/26 17:42:38 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/proto.h"

void	ph_eating(t_philo *tmp)
{
	t_philo	*philo;

	philo = tmp;
	philo->kine->last_meal = ph_actualtime();
	ph_speaking(&philo->epis->mtx->mtx_printf, philo->epis->agal->st_time,
		philo->id, LPRO_EAT);
	while (1)
	{
		if ((ph_actualtime() - philo->kine->last_meal) >= philo->epis->agal->tt_eat)
			break ;
	}
	philo->kine->count_meal++;
	if (philo->epis->agal->n_meal > 0)
	{
		if (philo->kine->count_meal >= philo->epis->agal->n_meal)
			ph_modif_var(philo->kine->mtx_meal, philo->kine->phs_meal, *(philo->kine->phs_meal) + 1);
	}
}

void	ph_sleeping(t_philo *tmp)
{
	t_philo	*philo;
	size_t	init_time;

	philo = tmp;
	init_time = ph_actualtime();
	ph_speaking(&philo->epis->mtx->mtx_printf, philo->epis->agal->st_time,
		philo->id, LPRO_SLEEP);
	while (1)
	{
		if ((ph_actualtime() - init_time) >= philo->epis->agal->tt_sleep)
			break ;
	}
}

void	ph_waiting(size_t time)
{
	size_t	init_time;

	init_time = ph_actualtime();
	while (1)
	{
		if ((ph_actualtime() - init_time) >= time)
			break ;
	}
}
