/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:59:27 by gmarquis          #+#    #+#             */
/*   Updated: 2024/10/13 16:08:45 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/proto.h"

void	ph_seat_on_table(t_philo *philo)
{
	ph_incr_var(philo->kine->mtx_phs_states, philo->kine->phs_states);
	pthread_mutex_lock(&philo->epis->mtx->mtx_id_dead);
	while (*(philo->epis->kine->id_dead) != 0)
	{
		pthread_mutex_unlock(&philo->epis->mtx->mtx_id_dead);
		ph_waiting(1);
		pthread_mutex_lock(&philo->epis->mtx->mtx_id_dead);
	}
	pthread_mutex_unlock(&philo->epis->mtx->mtx_id_dead);
	while (ph_actualtime() < *(philo->epis->agal->st_time))
	{
		;
	}
}
