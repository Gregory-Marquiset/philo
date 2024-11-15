/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   epis.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 21:55:16 by gmarquis          #+#    #+#             */
/*   Updated: 2024/10/25 09:45:20 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/proto.h"

void	ph_starting_philo(t_philo *philo, int *alive)
{
	while (*philo->epis->st_time > ph_actualtime())
		ph_waiting(1);
	if (philo->agal->n_philos == 1)
	{
		pthread_mutex_lock(&philo->rg_fork);
		ph_speaking(philo->epis, philo->id, LPRO_FORK);
		ph_waiting(philo->agal->tt_die);
		pthread_mutex_unlock(&philo->rg_fork);
		ph_modif_var(philo->kine->mtx_id_dead,
			philo->kine->id_dead, philo->id);
	}
	else
		ph_waiting(philo->agal->tt_start);
	*alive = ph_take_var(philo->kine->mtx_id_dead, philo->kine->id_dead);
}

void  *ph_routine_philos(void *tmp)
{
	t_philo (*philo) = (t_philo *)tmp;
	//int (verif) = 0;
	int (alive) = 0;
	//int (i) = 0;
	ph_starting_philo(philo, &alive);
	if (!alive)
		ph_speaking(philo->epis, philo->id, LPRO_JSYM);
	ph_incr_var(philo->kine->mtx_phs_meals,
		philo->kine->phs_meals);
	return (NULL);
}
