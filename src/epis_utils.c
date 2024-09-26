/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   epis_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:01:05 by gmarquis          #+#    #+#             */
/*   Updated: 2024/09/26 14:59:43 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/proto.h"

void	ph_open_table(t_epis *epis)
{
	pthread_mutex_lock(&epis->mtx->mtx_phs_states);
	while (*(epis->kine->phs_states) != epis->agal->n_philos)
	{
		pthread_mutex_unlock(&epis->mtx->mtx_phs_states);
		ph_waiting(1);
		pthread_mutex_lock(&epis->mtx->mtx_phs_states);
	}
	pthread_mutex_unlock(&epis->mtx->mtx_phs_states);
	ph_modif_var(&epis->mtx->mtx_sy_states, epis->kine->sy_states, OPEN);
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
