/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uneven.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 21:55:16 by gmarquis          #+#    #+#             */
/*   Updated: 2024/11/03 13:38:32 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/proto.h"

static int	ph_check_uneven_die_while_eating(t_philo *philo)
{
	long long		tt_result;
	unsigned long	tt_die;
	unsigned long	tt_eat;
	unsigned long	last_meal;

	tt_die = philo->epis->agal->tt_die;
	tt_eat = philo->epis->agal->tt_eat;
	*(philo->kine->last_meal) = ph_actualtime();
	last_meal = *philo->kine->last_meal;
	tt_result = ((long long)tt_die - (((long long)ph_actualtime() - (long long)last_meal) + (long long)tt_eat));
	if (tt_result > 0 && tt_result < (long long)tt_die)
		return (0);
	else
	{
		pthread_mutex_lock(&philo->rg_fork);
		ph_speaking(philo->epis, philo->id, LPRO_FORK);
		pthread_mutex_lock(philo->lf_fork);
		ph_speaking(philo->epis, philo->id, LPRO_FORK);

		ph_speaking(philo->epis, philo->id, LPRO_EAT);
		ph_waiting(tt_die);

		pthread_mutex_unlock(&philo->rg_fork);
		pthread_mutex_unlock(philo->lf_fork);
		ph_modif_var(&(philo->epis->mtx->mtx_id_dead),
			philo->epis->kine->id_dead, philo->id);
		return (1);
	}
}

void	*ph_routine_uneven(void *tmp)
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

		alive = ph_check_die_from_starvation(philo);
		if (alive)
			break ;
		alive = ph_check_uneven_die_while_eating(philo);
		if (alive)
			break ;
		pthread_mutex_lock(philo->lf_fork);
		ph_speaking(philo->epis, philo->id, LPRO_FORK);
		pthread_mutex_lock(&philo->rg_fork);
		ph_speaking(philo->epis, philo->id, LPRO_FORK);
		ph_speaking(philo->epis, philo->id, LPRO_EAT);
		*(philo->kine->last_meal) = ph_actualtime();
		ph_waiting(philo->epis->agal->tt_eat);
		pthread_mutex_unlock(philo->lf_fork);
		pthread_mutex_unlock(&philo->rg_fork);

		*(philo->kine->count_meal) += 1;
		if (philo->epis->agal->n_meal > 0 && *(philo->kine->count_meal) == philo->epis->agal->n_meal)
			ph_incr_var(philo->kine->mtx_phs_meals, philo->kine->phs_meals);

		verif = ph_take_var(&philo->epis->mtx->mtx_id_dead, philo->epis->kine->id_dead);
		if (verif != 0)
			break;

		alive = ph_check_die_while_sleeping(philo);
		if (alive)
			break ;
		ph_speaking(philo->epis, philo->id, LPRO_SLEEP);
		ph_waiting(philo->epis->agal->tt_sleep);

		verif = ph_take_var(&philo->epis->mtx->mtx_id_dead, philo->epis->kine->id_dead);
		if (verif)
			break;




		ph_speaking(philo->epis, philo->id, LPRO_THINK);
		alive = ph_check_die_while_thinking(philo);
		if (alive)
			break ;
		if (philo->id != 1)
		{
			if (philo->epis->agal->tt_think > 0)
				ph_waiting(philo->epis->agal->tt_think - 10);
			else
				ph_waiting(2);
		}
		else if (philo->id == 1)
		{
			if (philo->epis->agal->tt_think > 0)
				ph_waiting(philo->epis->agal->tt_think - 1);
			else
				ph_waiting(2);
		}


		verif = ph_take_var(&philo->epis->mtx->mtx_id_dead, philo->epis->kine->id_dead);
		if (verif != 0)
			break;

		i++;
	}
	return (NULL);
}
