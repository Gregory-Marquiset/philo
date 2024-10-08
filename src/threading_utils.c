/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 22:27:08 by gmarquis          #+#    #+#             */
/*   Updated: 2024/10/08 16:19:18 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/proto.h"

int	ph_without_target_meals(t_epis *epis)
{
	int	res;

	res = 0;
	pthread_mutex_lock(&epis->mtx->mtx_id_dead);
	while (*(epis->kine->id_dead) == 0)
	{
		pthread_mutex_unlock(&epis->mtx->mtx_id_dead);
		ph_waiting(1);
		res = *(epis->kine->id_dead);
		pthread_mutex_lock(&epis->mtx->mtx_id_dead);
	}
	pthread_mutex_unlock(&epis->mtx->mtx_id_dead);
	return (res);
}

int	ph_with_target_meals(t_epis *epis)
{
	while (1)
	{
		pthread_mutex_lock(&epis->mtx->mtx_phs_meals);
		if (*(epis->kine->phs_meals) >= epis->agal->n_philos)
		{
			pthread_mutex_unlock(&epis->mtx->mtx_phs_meals);
			return (1);
		}
		else
		{
			pthread_mutex_unlock(&epis->mtx->mtx_phs_meals);
			if (ph_check_id_dead(epis))
				return (0);
		}
		ph_waiting(1);
	}
}
