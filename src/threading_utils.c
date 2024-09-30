/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 22:27:08 by gmarquis          #+#    #+#             */
/*   Updated: 2024/09/30 22:27:33 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/proto.h"

void	ph_without_target_meals(t_epis *epis)
{
	pthread_mutex_lock(&epis->mtx->mtx_id_dead);
	while (*(epis->kine->id_dead) == 0)
	{
		pthread_mutex_unlock(&epis->mtx->mtx_id_dead);
		ph_waiting(1);
		pthread_mutex_lock(&epis->mtx->mtx_id_dead);
	}
	pthread_mutex_unlock(&epis->mtx->mtx_id_dead);
	ph_modif_var(&epis->mtx->mtx_sy_states, epis->kine->sy_states, CLOSE);
}

void	ph_with_target_meals(t_epis *epis)
{
	while (epis->agal->n_meal > 0)
	{
		pthread_mutex_lock(&epis->mtx->mtx_phs_meals);
		if (*(epis->kine->phs_meals) >= epis->agal->n_philos)
		{
			pthread_mutex_unlock(&epis->mtx->mtx_phs_meals);
			ph_modif_var(&epis->mtx->mtx_sy_states, epis->kine->sy_states,
				CLOSE);
			return ;
		}
		else
		{
			pthread_mutex_unlock(&epis->mtx->mtx_phs_meals);
			if (ph_check_id_dead(epis))
				return ;
		}
		ph_waiting(1);
	}
}
