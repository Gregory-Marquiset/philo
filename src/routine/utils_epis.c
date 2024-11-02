/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_epis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:01:05 by gmarquis          #+#    #+#             */
/*   Updated: 2024/10/31 14:58:19 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/proto.h"

int	ph_without_target_meals(t_epis *epis)
{
	int	res;

	res = 0;
	pthread_mutex_lock(&epis->mtx->mtx_id_dead);
	while (*(epis->kine->id_dead) == 0)
	{
		pthread_mutex_unlock(&epis->mtx->mtx_id_dead);
		usleep(1);
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
		usleep(1);
	}
}

int	ph_check_id_dead(t_epis *epis)
{
	int	res;

	res = 0;
	pthread_mutex_lock(&epis->mtx->mtx_id_dead);
	if (*(epis->kine->id_dead) > 0)
	{
		res = *epis->kine->id_dead;
		pthread_mutex_unlock(&epis->mtx->mtx_id_dead);
		return (res);
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
		usleep(1);
		pthread_mutex_lock(&epis->mtx->mtx_phs_states);
	}
	pthread_mutex_unlock(&epis->mtx->mtx_phs_states);
	ph_modif_var(&epis->mtx->mtx_id_dead, epis->kine->id_dead, 0);
}

void	ph_speaking_for_dead(t_epis *epis, int id, char *message)
{
	unsigned long	start_time;

	start_time = epis->agal->st_time;
	pthread_mutex_lock(&epis->use_printf->mtx_verif);
	epis->use_printf->verif = -2;
	pthread_mutex_unlock(&epis->use_printf->mtx_verif);
	pthread_mutex_lock(&epis->use_printf->mtx_printf);
	printf("%-10ld %-4d %s", (ph_actualtime() - start_time), id, message);
	pthread_mutex_unlock(&epis->use_printf->mtx_printf);
}
