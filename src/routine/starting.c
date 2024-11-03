/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 21:55:16 by gmarquis          #+#    #+#             */
/*   Updated: 2024/11/03 13:40:44 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/proto.h"

static int	ph_check_die_while_starting(t_philo *philo)
{
	long long		tt_result;
	unsigned long	tt_die;
	unsigned long	tt_eat;

	tt_die = philo->epis->agal->tt_die;
	tt_eat = philo->epis->agal->tt_eat;
	tt_result = (long long)tt_die - ((long long)tt_eat);
	if (tt_result < 0)
	{
		ph_waiting(tt_die);
		if (philo->id % 2 != 0)
			ph_modif_var(&(philo->epis->mtx->mtx_id_dead),
				philo->epis->kine->id_dead, philo->id);
		return (1);
	}
	return (0);
}

static int	ph_one_philo(t_philo *philo)
{

	pthread_mutex_lock(&philo->rg_fork);
	ph_speaking(philo->epis, philo->id, LPRO_FORK);
	ph_waiting(philo->epis->agal->tt_die);
	pthread_mutex_unlock(&philo->rg_fork);
	ph_modif_var(&(philo->epis->mtx->mtx_id_dead),
		philo->epis->kine->id_dead, philo->id);
	return (1);
}

void	ph_starting_philo(t_philo *philo, int *alive)
{
	pthread_mutex_lock(&philo->epis->mtx->mtx_phs_states);
	pthread_mutex_unlock(&philo->epis->mtx->mtx_phs_states);
	while (ph_actualtime() < philo->epis->agal->st_time)
		ph_waiting(1);
	*(philo->kine->last_meal) = ph_actualtime();
	if (philo->epis->agal->n_philos == 1)
		*alive = ph_one_philo(philo);
	else if (philo->id % 2 == 0)
	{
		*alive = ph_check_die_while_starting(philo);
		if (!*alive)
			ph_waiting(philo->epis->agal->tt_eat - 1);
	}
	else
	{
		if (philo->epis->agal->n_philos % 2 != 0
			&& philo->id != 1)
		{
			*alive = ph_check_die_while_starting(philo);
			if (!*alive)
				ph_waiting((philo->epis->agal->tt_eat * 2) - 1);
		}
	}
}
