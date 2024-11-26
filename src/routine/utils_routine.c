/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 21:55:16 by gmarquis          #+#    #+#             */
/*   Updated: 2024/11/20 08:25:04 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/proto.h"

int	ph_check_die_while_thinking(t_philo *philo)
{
	long long		tt_result;
	unsigned long	last_meal;
	unsigned long	tt_die;

	last_meal = *philo->kine->last_meal;
	tt_die = philo->agal->tt_die;
	tt_result = (long long)tt_die - ((long long)ph_actualtime() - (long long)last_meal);
	//printf("%d = %lld\n", philo->id, tt_result);
	if (tt_result > 0 && tt_result < (long long)tt_die)
		return (0);
	else
	{
		ph_speaking(philo->epis, philo->id, LPRO_THINK);
		ph_waiting(tt_die - (ph_actualtime() - last_meal));
		ph_modif_var(&(philo->epis->mtx_id_dead),
			philo->kine->id_dead, philo->id);
		return (1);
	}
}

void  ph_thinking(t_philo *philo, int *verif, int *alive)
{
	*verif = ph_take_var(philo->kine->mtx_id_dead, philo->kine->id_dead);
	if (*verif != 0)
		return ;
	*alive = ph_check_die_while_thinking(philo);
	if (*alive)
		return ;
	ph_speaking(philo->epis, philo->id, LPRO_THINK);
	ph_waiting(philo->agal->tt_think);
}

int	ph_check_die_while_sleeping(t_philo *philo)
{
	long long		tt_result;
	unsigned long	last_meal;
	unsigned long	tt_sleep;
	unsigned long	tt_die;

	last_meal = *philo->kine->last_meal;
	tt_sleep = philo->agal->tt_sleep;
	tt_die = philo->agal->tt_die;
	tt_result = (long long)tt_sleep + ((long long)ph_actualtime() - (long long)last_meal);
	if (tt_result > 0 && tt_result < (long long)tt_die)
		return (0);
	else
	{
		ph_speaking(philo->epis, philo->id, LPRO_SLEEP);
		ph_waiting(tt_die - ((long long)ph_actualtime() - (long long)last_meal));
		ph_modif_var(philo->kine->mtx_id_dead,
			philo->kine->id_dead, philo->id);
		return (1);
	}
}

void  ph_sleeping(t_philo *philo, int *verif, int *alive)
{
	*verif = ph_take_var(philo->kine->mtx_id_dead, philo->kine->id_dead);
	if (*verif != 0)
		return ;
	*alive = ph_check_die_while_sleeping(philo);
	if (*alive)
		return ;
	ph_speaking(philo->epis, philo->id, LPRO_SLEEP);
	ph_waiting(philo->agal->tt_sleep);
}

void  ph_take_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->lf_fork);
		ph_speaking(philo->epis, philo->id, LPRO_FORK);
		pthread_mutex_lock(&philo->rg_fork);
		ph_speaking(philo->epis, philo->id, LPRO_FORK);
	}
	else
	{
		pthread_mutex_lock(&philo->rg_fork);
		ph_speaking(philo->epis, philo->id, LPRO_FORK);
		pthread_mutex_lock(philo->lf_fork);
		ph_speaking(philo->epis, philo->id, LPRO_FORK);
	}
}

static int	ph_check_even_die_while_eating(t_philo *philo)
{
	long long		tt_result;
	unsigned long	last_meal;

	unsigned long	(tt_die) = philo->agal->tt_die;
	unsigned long	(tt_eat) = philo->agal->tt_eat;
	*(philo->kine->last_meal) = ph_actualtime();
	last_meal = *philo->kine->last_meal;
	tt_result = (((long long)ph_actualtime() - (long long)last_meal) + (long long)tt_eat);
	if (tt_result > 0 && tt_result < (long long)tt_die)
		return (0);
	else
	{
		ph_take_fork(philo);
		ph_speaking(philo->epis, philo->id, LPRO_EAT);
		ph_waiting(tt_die);
		pthread_mutex_unlock(philo->lf_fork);
		pthread_mutex_unlock(&philo->rg_fork);
		ph_modif_var(philo->kine->mtx_id_dead, philo->kine->id_dead, philo->id);
		return (1);
	}
}

void  ph_eating(t_philo *philo, int *verif, int *alive)
{
	*verif = ph_take_var(philo->kine->mtx_id_dead, philo->kine->id_dead);
	if (*verif != 0)
		return ;
	*alive = ph_check_even_die_while_eating(philo);
	if (*alive)
		return ;
	ph_take_fork(philo);
	ph_speaking(philo->epis, philo->id, LPRO_EAT);
	ph_waiting(philo->agal->tt_eat);
	pthread_mutex_unlock(philo->lf_fork);
	pthread_mutex_unlock(&philo->rg_fork);
	*(philo->kine->count_meal) += 1;
	if (philo->agal->n_meal > 0)
		if (*(philo->kine->count_meal) == philo->agal->n_meal)
			ph_incr_var(philo->kine->mtx_phs_meals, philo->kine->phs_meals);
}

