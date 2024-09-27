/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:59:27 by gmarquis          #+#    #+#             */
/*   Updated: 2024/09/27 23:27:44 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/proto.h"

void	ph_seat_on_table(t_philo *philo)
{
	ph_modif_var(philo->kine->mtx_states, philo->kine->phs_states,
		*(philo->kine->phs_states) + 1);
	pthread_mutex_lock(&philo->epis->mtx->mtx_sy_states);
	while (*(philo->epis->kine->sy_states) == SETING)
	{
		pthread_mutex_unlock(&philo->epis->mtx->mtx_sy_states);
		ph_waiting(1);
		pthread_mutex_lock(&philo->epis->mtx->mtx_sy_states);
	}
	pthread_mutex_unlock(&philo->epis->mtx->mtx_sy_states);
}
