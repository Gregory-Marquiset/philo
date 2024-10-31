/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 21:55:16 by gmarquis          #+#    #+#             */
/*   Updated: 2024/10/31 14:59:05 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/proto.h"

int	ph_check_die_from_starvation(t_philo *philo)
{
	long long		tt_result;
	unsigned long	tt_die;
	unsigned long	tt_eat;
	unsigned long	last_meal;

	tt_die = philo->epis->agal->tt_die;
	tt_eat = philo->epis->agal->tt_eat;
	last_meal = *philo->kine->last_meal;
	tt_result = (long long)tt_die - ((long long)ph_actualtime() - (long long)last_meal);
	//printf("%d = %lld\n", philo->id, tt_result);
	if (tt_result > 0)
		return (0);
	return (1);
}

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
	tt_result = ((long long)tt_die - ((long long)ph_actualtime() - (long long)last_meal));
	tt_result -= 10;
	if (tt_result > 0 && tt_result < ((long long)tt_die - (long long)tt_eat - (long long)tt_sleep))
		return (0);
	else
	{
		ph_speaking(philo->epis, philo->id, LPRO_THINK);
		ph_waiting(philo, tt_die - (ph_actualtime() - last_meal));
		ph_modif_var(&(philo->epis->mtx->mtx_id_dead),
			philo->epis->kine->id_dead, philo->id);
		return (1);
	}
	/*uneven
	if (philo->id % 2 != 0)
	{
		if (philo->id == 1)
		{
			ph_speaking(philo->epis, philo->id, LPRO_THINK);
			if (philo->epis->agal->tt_think > 0)
				ph_waiting(philo->epis->agal->tt_think - 1);
			else
				ph_waiting(2);
		}
		else
		{
			ph_speaking(philo->epis, philo->id, LPRO_THINK);
			if (philo->epis->agal->tt_think > 0)
				ph_waiting(philo->epis->agal->tt_think - 10);
			else
				ph_waiting(2);
		}
	}
	else
	{
	even
		if (philo->epis->agal->tt_think > 0)
			ph_waiting(philo->epis->agal->tt_think - 10);
		if (philo->epis->agal->n_philos % 2 != 0)
			ph_waiting(philo->epis->agal->tt_eat - 10);
	}*/
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
	tt_result = (long long)tt_sleep + ((long long)ph_actualtime() - (long long)last_meal); /* Add tt_eat ??? */
	if (tt_result > 0 && tt_result < (long long)tt_die) /* Add tt_eat ??? */
		return (0);
	else
	{
		ph_speaking(philo->epis, philo->id, LPRO_SLEEP);
		ph_waiting(philo, tt_die - (ph_actualtime() - last_meal));
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
	if (philo->id % 2 == 0)
		tt_result = (long long)tt_die - (long long)tt_eat;
	else
		tt_result = (long long)tt_die - ((long long)tt_eat * 2);
	if (tt_result > 0 && tt_result < (long long)tt_die)
		return (0);
	else
	{
		ph_waiting(philo, tt_die);
		return (1);
	}
}

void	ph_starting_philo(t_philo *philo, int *alive)
{
	pthread_mutex_lock(&philo->epis->mtx->mtx_phs_states);
	pthread_mutex_unlock(&philo->epis->mtx->mtx_phs_states);
	while (ph_actualtime() < philo->epis->agal->st_time)
	{
		usleep(1);
	}
	*philo->kine->last_meal = ph_actualtime();
	if (philo->id != 1)
	{
		*alive = ph_check_die_while_waiting(philo);
		if (!*alive)
		{
			if (philo->id % 2 == 0)
				ph_waiting(philo, philo->epis->agal->tt_eat);
			else
				ph_waiting(philo, philo->epis->agal->tt_eat * 2);
		}
	}
}
