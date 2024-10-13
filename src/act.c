/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 20:13:07 by gmarquis          #+#    #+#             */
/*   Updated: 2024/10/13 16:09:13 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/proto.h"

/*static int	ph_wait_or_not(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		if (*(philo->kine->count_meal) % 2 == 0 && philo->epis->agal->n_philos % 2 != 0)
		{
			if (philo->id == philo->epis->agal->n_philos && (*(philo->kine->count_meal) == 0 || *(philo->kine->count_meal) % 2 == 0))
			{
				if (ph_check_tt_eat(philo))
					return (1);
				ph_waiting(philo->epis->agal->tt_eat - 1);
			}
		}
		else if (*(philo->kine->count_meal) % 2 != 0)
		{
			if (ph_check_tt_eat(philo))
				return (1);
			ph_waiting(philo->epis->agal->tt_eat - 1);
		}
	}
	else
	{
		if (*(philo->kine->count_meal) % 2 == 0)
			ph_waiting(philo->epis->agal->tt_eat - 1);
	}
	if (ph_check_sympos_states(philo))
		return (1);
	if (ph_check_tt_eat(philo))
		return (1);
	return (0);
}*/

int	ph_eating(t_philo *tmp)
{
	t_philo	*philo;

	philo = tmp;
	//if (ph_wait_or_not(philo))
	//	return (1);
	ph_speaking(philo->epis, philo->id, LPRO_EAT);
	*(philo->kine->last_meal) = ph_actualtime();
	while (1)
	{
		if ((ph_actualtime() - *(philo->kine->last_meal))
			>= philo->epis->agal->tt_eat)
			break ;
	}
	*(philo->kine->count_meal) += 1;
	if (philo->epis->agal->n_meal > 0)
	{
		if (*(philo->kine->count_meal) == philo->epis->agal->n_meal)
			ph_incr_var(philo->kine->mtx_phs_meals, philo->kine->phs_meals);
	}
	return (0);
}

static int	ph_check_die_in_sleep(t_philo *philo)
{
	size_t	last_meal;
	size_t	tt_sleep;
	size_t	tt_die;
	size_t	tt_eat;

	last_meal = *philo->kine->last_meal;
	tt_sleep = philo->epis->agal->tt_sleep;
	tt_die = philo->epis->agal->tt_die;
	tt_eat = philo->epis->agal->tt_eat;
	if ((ph_actualtime() - (last_meal + tt_eat)) + tt_sleep <= tt_die)
		return (0);
	else
	{
		ph_waiting(tt_die - (ph_actualtime() - last_meal) + tt_eat);
		ph_speaking(philo->epis, philo->id, LPRO_SLEEP);
		ph_modif_var(&(philo->epis->mtx->mtx_id_dead),
			philo->epis->kine->id_dead, philo->id);
		return (1);
	}
}

int	ph_sleeping(t_philo *tmp)
{
	t_philo	*philo;

	philo = tmp;
	if (ph_check_sympos_states(philo))
		return (1);
	if (ph_check_die_in_sleep(philo))
		return (1);
	ph_speaking(philo->epis, philo->id, LPRO_SLEEP);
	ph_waiting(philo->epis->agal->tt_sleep);
	return (0);
}

void	ph_thinking(t_philo *tmp)
{
	t_philo	*philo;

	philo = tmp;
	if (ph_check_sympos_states(philo))
		return ;
	ph_speaking(philo->epis, philo->id, LPRO_THINK);
}

void	ph_waiting(size_t time)
{
	size_t	init_time;

	init_time = ph_actualtime();
	if (time > 99)
		usleep((time * 70) / 100);
	while (1)
	{
		if ((ph_actualtime() - init_time) >= time)
			break ;
	}
}
