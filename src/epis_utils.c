/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   epis_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:01:05 by gmarquis          #+#    #+#             */
/*   Updated: 2024/10/01 20:06:51 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/proto.h"

int	ph_check_id_dead(t_epis *epis)
{
	pthread_mutex_lock(&epis->mtx->mtx_id_dead);
	if (*(epis->kine->id_dead) != 0)
	{
		pthread_mutex_unlock(&epis->mtx->mtx_id_dead);
		ph_modif_var(&epis->mtx->mtx_sy_states, epis->kine->sy_states,
			CLOSE);
		return (1);
	}
	pthread_mutex_unlock(&epis->mtx->mtx_id_dead);
	return (0);
}

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

void	ph_speaking_for_dead(t_epis *epis, int id, char *message)
{
	size_t	start_time;

	start_time = epis->agal->st_time;
	while (1)
	{
		pthread_mutex_lock(&epis->use_printf->mtx_verif);
		if (*(epis->use_printf->verif) == 0)
		{
			*(epis->use_printf->verif) = -2;
			pthread_mutex_unlock(&epis->use_printf->mtx_verif);
			break ;
		}
		else
		{
			pthread_mutex_unlock(&epis->use_printf->mtx_verif);
			ph_waiting(1);
		}
	}
	pthread_mutex_lock(&epis->use_printf->mtx_printf);
	printf("%-10ld %-4d %s", (ph_actualtime() - start_time), id, message);
	pthread_mutex_unlock(&epis->use_printf->mtx_printf);
}
