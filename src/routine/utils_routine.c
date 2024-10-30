/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 21:55:16 by gmarquis          #+#    #+#             */
/*   Updated: 2024/10/30 10:17:04 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/proto.h"

int	ph_check_die_while_thinking(t_philo *philo)
{
	long long		tt_result;
	unsigned long	last_meal;
	unsigned long	tt_sleep;
	unsigned long	tt_die;
	unsigned long	tt_eat;

	last_meal = *philo->kine->last_meal;
	tt_sleep = philo->epis->agal->tt_sleep;
	tt_die = philo->epis->agal->tt_die;
	tt_eat = philo->epis->agal->tt_eat;
	tt_result = (long long)tt_sleep + ((long long)ph_actualtime() - (long long)last_meal);
	if (tt_result > 0 && tt_result < (long long)tt_die)
		return (0);
	else
	{
		ph_speaking(philo->epis, philo->id, LPRO_SLEEP);
		ph_waiting(tt_die - (ph_actualtime() - last_meal));
		ph_modif_var(&(philo->epis->mtx->mtx_id_dead),
			philo->epis->kine->id_dead, philo->id);
		return (1);
	}
	/*uneven*/
	if (philo->id % 2 != 0)
	{
		if (philo->id != 1)
		{
			if (philo->epis->agal->tt_think > 0)
				ph_waiting(philo->epis->agal->tt_think - 10);
			else
				ph_waiting(2);
		}
	}
	else if (philo->id == 1)
	{
		if (philo->epis->agal->tt_think > 0)
			ph_waiting(philo->epis->agal->tt_think - 1);
		else
			ph_waiting(2);
	}
	/*even*/
	if (philo->epis->agal->tt_think > 0)
		ph_waiting(philo->epis->agal->tt_think - 10);
	if (philo->epis->agal->n_philos % 2 != 0)
		ph_waiting(philo->epis->agal->tt_eat - 10);

}

int	ph_check_die_while_sleeping(t_philo *philo)
{
	long long		tt_result;
	unsigned long	last_meal;
	unsigned long	tt_sleep;
	unsigned long	tt_die;
	unsigned long	tt_eat;

	last_meal = *philo->kine->last_meal;
	tt_sleep = philo->epis->agal->tt_sleep;
	tt_die = philo->epis->agal->tt_die;
	tt_eat = philo->epis->agal->tt_eat;
	tt_result = (long long)tt_sleep + ((long long)ph_actualtime() - (long long)last_meal);
	if (tt_result > 0 && tt_result < (long long)tt_die)
		return (0);
	else
	{
		ph_speaking(philo->epis, philo->id, LPRO_SLEEP);
		ph_waiting(tt_die - (ph_actualtime() - last_meal));
		ph_modif_var(&(philo->epis->mtx->mtx_id_dead),
			philo->epis->kine->id_dead, philo->id);
		return (1);
	}
}

static int	ph_check_die_while_waiting(t_philo *philo)
{
	long long		tt_result;
	unsigned long	tt_die;
	unsigned long	tt_eat;

	tt_die = philo->epis->agal->tt_die;
	tt_eat = philo->epis->agal->tt_eat;
	/*if (philo->epis->agal->n_philos % 2 != 0)
		tt_result = (long long)tt_die - (((long long)tt_eat * 2));
	else*/
		tt_result = (long long)tt_die - ((long long)tt_eat);
	/*if (philo->id == 2 || philo->id == 3)
		printf(LU_RED1 "%3d check r = %lld, d = %lld\n"LU_END, philo->id, tt_result, (long long)tt_die - ((long long)tt_eat));
  */if (tt_result > 0 && tt_result < (long long)tt_die)
		return (0);
	else
	{
		ph_waiting(tt_die);
		if (philo->id % 2 != 0)
			ph_modif_var(&(philo->epis->mtx->mtx_id_dead),
				philo->epis->kine->id_dead, philo->id);
		return (1);
	}
}

void	ph_starting_philo(t_philo *philo, int *alive)
{
	pthread_mutex_lock(&philo->epis->mtx->mtx_phs_states);
	pthread_mutex_unlock(&philo->epis->mtx->mtx_phs_states);
	while (ph_actualtime() < philo->epis->agal->st_time)
	{
		ph_waiting(1);
	}
	if (philo->id % 2 == 0)
	{
		*alive = ph_check_die_while_waiting(philo);
		if (!*alive)
			ph_waiting(philo->epis->agal->tt_eat - 1);
	}
	else
	{
		if (philo->epis->agal->n_philos % 2 != 0
			&& philo->id != 1)
		{
			*alive = ph_check_die_while_waiting(philo);
			if (!*alive)
				ph_waiting((philo->epis->agal->tt_eat * 2) - 1);
		}
	}
}
