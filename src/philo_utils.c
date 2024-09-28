/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:59:27 by gmarquis          #+#    #+#             */
/*   Updated: 2024/09/28 15:05:41 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/proto.h"

void	ph_seat_on_table(t_philo *philo)
{
	ph_incr_var(philo->kine->mtx_phs_states, philo->kine->phs_states);
	pthread_mutex_lock(&philo->epis->mtx->mtx_sy_states);
	while (*(philo->epis->kine->sy_states) == SETING)
	{
		pthread_mutex_unlock(&philo->epis->mtx->mtx_sy_states);
		ph_waiting(1);
		pthread_mutex_lock(&philo->epis->mtx->mtx_sy_states);
	}
	pthread_mutex_unlock(&philo->epis->mtx->mtx_sy_states);
}
