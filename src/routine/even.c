/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   even.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 21:55:16 by gmarquis          #+#    #+#             */
/*   Updated: 2024/11/05 19:01:36 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/proto.h"

/*void	*ph_routine_even(void *tmp)
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
		alive = ph_check_even_die_while_eating(philo);
		if (alive)
			break ;
		pthread_mutex_lock(philo->lf_fork);
		ph_speaking(philo->epis, philo->id, LPRO_FORK);
		pthread_mutex_lock(&philo->rg_fork);
		ph_speaking(philo->epis, philo->id, LPRO_FORK);

		ph_speaking(philo->epis, philo->id, LPRO_EAT);
		ph_waiting(philo->epis->agal->tt_eat);

		pthread_mutex_unlock(philo->lf_fork);
		pthread_mutex_unlock(&philo->rg_fork);
		*(philo->kine->count_meal) += 1;
		if (philo->epis->agal->n_meal > 0)
		{
			if (*(philo->kine->count_meal) == philo->epis->agal->n_meal)
				ph_incr_var(philo->kine->mtx_phs_meals, philo->kine->phs_meals);
		}

		verif = ph_take_var(&philo->epis->mtx->mtx_id_dead, philo->epis->kine->id_dead);
		if (verif != 0)
			break;

		alive = ph_check_die_while_sleeping(philo);
		if (alive)
			break ;
		ph_speaking(philo->epis, philo->id, LPRO_SLEEP);
		ph_waiting(philo->epis->agal->tt_sleep);

		verif = ph_take_var(&philo->epis->mtx->mtx_id_dead, philo->epis->kine->id_dead);
		if (verif != 0)
			break;



		alive = ph_check_die_while_thinking(philo);
		if (alive)
			break ;
		ph_speaking(philo->epis, philo->id, LPRO_THINK);
		if (philo->epis->agal->tt_think > 0)
			ph_waiting(philo->epis->agal->tt_think - 10);
		verif = ph_take_var(&philo->epis->mtx->mtx_id_dead, philo->epis->kine->id_dead);
		if (verif != 0)
			break;
		if (philo->epis->agal->n_philos % 2 != 0)
			ph_waiting(philo->epis->agal->tt_eat - 10);





		verif = ph_take_var(&philo->epis->mtx->mtx_id_dead, philo->epis->kine->id_dead);
		if (verif != 0)
			break;

		i++;
	}
	return (NULL);
}*/
