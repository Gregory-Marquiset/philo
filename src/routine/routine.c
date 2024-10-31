/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 13:25:40 by gmarquis          #+#    #+#             */
/*   Updated: 2024/10/31 14:55:57 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/proto.h"

static int	ph_check_die_while_eating(t_philo *philo)
{
	long long		tt_result;
	unsigned long	tt_die;
	unsigned long	tt_eat;
	unsigned long	last_meal;

	tt_die = philo->epis->agal->tt_die;
	tt_eat = philo->epis->agal->tt_eat;
	if (ph_check_die_from_starvation(philo))
		return (1);
	*(philo->kine->last_meal) = ph_actualtime();
	last_meal = *philo->kine->last_meal;
	tt_result = ((long long)tt_die - ((long long)ph_actualtime() - (long long)last_meal));
	tt_result -= (long long)tt_eat;
	if (tt_result > 0 && tt_result < (long long)tt_die)
		return (0);
	else
	{
		if (philo->id % 2 == 0)
		{
			pthread_mutex_lock(philo->lf_fork);
			pthread_mutex_lock(&philo->rg_fork);
		}
		else
		{
			pthread_mutex_lock(&philo->rg_fork);
			pthread_mutex_lock(philo->lf_fork);
		}
		ph_speaking(philo->epis, philo->id, LPRO_FORK);
		ph_speaking(philo->epis, philo->id, LPRO_FORK);

		ph_speaking(philo->epis, philo->id, LPRO_EAT);
		ph_waiting(philo, tt_die);

		if (philo->id % 2 == 0)
		{
			pthread_mutex_unlock(philo->lf_fork);
			pthread_mutex_unlock(&philo->rg_fork);
		}
		else
		{
			pthread_mutex_unlock(&philo->rg_fork);
			pthread_mutex_unlock(philo->lf_fork);
		}
		ph_modif_var(&(philo->epis->mtx->mtx_id_dead),
			philo->epis->kine->id_dead, philo->id);
		return (1);
	}
}

static void	ph_eating(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->lf_fork);
		pthread_mutex_lock(&philo->rg_fork);
	}
	else
	{
		pthread_mutex_lock(&philo->rg_fork);
		pthread_mutex_lock(philo->lf_fork);
	}

	ph_speaking(philo->epis, philo->id, LPRO_EAT);
	ph_waiting(philo, philo->epis->agal->tt_eat);
	*(philo->kine->last_meal) = ph_actualtime();

	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->lf_fork);
		pthread_mutex_unlock(&philo->rg_fork);
	}
	else
	{
		pthread_mutex_unlock(&philo->rg_fork);
		pthread_mutex_unlock(philo->lf_fork);
	}
	*(philo->kine->count_meal) += 1;
	if (philo->epis->agal->n_meal > 0)
	{
		if (*(philo->kine->count_meal) == philo->epis->agal->n_meal)
			ph_incr_var(philo->kine->mtx_phs_meals, philo->kine->phs_meals);
	}
}

void	*ph_routine(void *tmp)
{
	t_philo	*philo;
	int		verif = 0;
	int		alive = 0;
	int		i = 0;

	philo = (t_philo *)tmp;
	ph_starting_philo(philo, &alive);

	while (verif == 0 && alive == 0)
	{
		verif = ph_take_var(&philo->epis->mtx->mtx_id_dead, philo->epis->kine->id_dead);
		if (verif != 0)
			break;

		alive = ph_check_die_while_eating(philo);
		if (alive)
			break ;
		ph_eating(philo);

		verif = ph_take_var(&philo->epis->mtx->mtx_id_dead, philo->epis->kine->id_dead);
		if (verif != 0)
			break;

		alive = ph_check_die_while_sleeping(philo);
		if (alive)
			break ;
		ph_speaking(philo->epis, philo->id, LPRO_SLEEP);
		ph_waiting(philo, philo->epis->agal->tt_sleep);

		verif = ph_take_var(&philo->epis->mtx->mtx_id_dead, philo->epis->kine->id_dead);
		if (verif != 0)
			break;


		alive = ph_check_die_while_thinking(philo);
		if (alive)
			break ;
		ph_speaking(philo->epis, philo->id, LPRO_THINK);
		if (philo->epis->agal->tt_think > 0)
			ph_waiting(philo, philo->epis->agal->tt_think);
		if (philo->epis->agal->n_philos % 2 != 0 && philo->id % 2 == 0)
			ph_waiting(philo, philo->epis->agal->tt_eat);





		verif = ph_take_var(&philo->epis->mtx->mtx_id_dead, philo->epis->kine->id_dead);
		if (verif != 0)
			break;

		i++;
	}
	return (NULL);
}
