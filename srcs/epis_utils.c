/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   epis_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:01:05 by gmarquis          #+#    #+#             */
/*   Updated: 2024/09/25 18:59:15 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/proto.h"

void	ph_open_table(t_epis *epis)
{
	int	i;

	i = 0;
	while (i < epis->agal->n_philos)
	{
		if (epis->kine->phs_states[i] == READY)
			i++;
	}
	epis->kine->sy_states = OPEN;
}

void	ph_seat_on_table(t_philo *philo)
{
	while (philo->epis->kine->sy_states == SETING)
		ph_waiting(10);
}

void	ph_speaking(pthread_mutex_t *mutex, int start_time, int id,
	char *message)
{
	pthread_mutex_lock(mutex);
	if (id == 0)
		printf("%-10d %s", (int)ph_actualtime() - start_time, message);
	else
		printf("%-10d %-4d %s", (int)ph_actualtime() - start_time, id, message);
	pthread_mutex_unlock(mutex);
}
