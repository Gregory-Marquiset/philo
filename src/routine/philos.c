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
	unsigned long (tt_start) = philo->agal->tt_start;
	unsigned long (tt_die) = philo->agal->tt_die;
	//ts_print_philo(philo);
	while (*philo->epis->st_time > ph_actualtime())
		ph_waiting(1);
	if (philo->agal->n_philos == 1)
	{
		pthread_mutex_lock(&philo->rg_fork);
		ph_speaking(philo->epis, philo->id, LPRO_FORK);
		ph_waiting(tt_die);
		pthread_mutex_unlock(&philo->rg_fork);
		ph_modif_var(philo->kine->mtx_id_dead,
			philo->kine->id_dead, philo->id);
	}
	if (tt_start < tt_die)
		ph_waiting(tt_start);
	else
	{
		ph_waiting(tt_die);
		if(!ph_take_var(philo->kine->mtx_id_dead, philo->kine->id_dead))
			ph_modif_var(philo->kine->mtx_id_dead, philo->kine->id_dead, philo->id);
	}
	*alive = ph_take_var(philo->kine->mtx_id_dead, philo->kine->id_dead);
}

void  *ph_routine_philos(void *tmp)
{
	t_philo (*philo) = (t_philo *)tmp;
	int (verif) = 0;
	int (alive) = 0;
	ph_starting_philo(philo, &alive);
	ph_incr_var(philo->kine->mtx_phs_meals, philo->kine->phs_meals);
	while (verif == 0 && !alive)
	{
		ph_eating(philo, &verif, &alive);
		if (verif != 0 || alive)
			break;
		ph_sleeping(philo, &verif, &alive);
		if (verif != 0 || alive)
			break;
		ph_thinking(philo, &verif, &alive);
	}
	return (NULL);
}
