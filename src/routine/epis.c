/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   epis.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 21:55:16 by gmarquis          #+#    #+#             */
/*   Updated: 2024/11/03 12:39:16 by gmarquis         ###   ########.fr       */
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

void	ph_speaking_for_dead(t_epis *epis, int id, char *message)
{
	unsigned long	start_time;

	start_time = epis->agal->st_time;
	pthread_mutex_lock(&epis->use_printf->mtx_verif);
	*(epis->use_printf->verif) = -2;
	pthread_mutex_unlock(&epis->use_printf->mtx_verif);
	pthread_mutex_lock(&epis->use_printf->mtx_printf);
	printf("%-10ld %-4d %s", (ph_actualtime() - start_time), id, message);
	pthread_mutex_unlock(&epis->use_printf->mtx_printf);
}

void	*ph_routine_epis(void *tmp)
{
	t_epis	*epis;
	int		dead;
	int		meal;

	epis = (t_epis *)tmp;
	dead = 0;
	meal = 0;
	while (dead == 0 && meal == 0)
	{
		if (epis->agal->n_meal > 0)
		{
			meal = ph_with_target_meals(epis);
			if (meal == 1)
				ph_modif_var(&epis->mtx->mtx_id_dead, epis->kine->id_dead, -1);
			dead = ph_check_id_dead(epis);
		}
		else
			dead = ph_without_target_meals(epis);
	}
	if (dead != 0)
		ph_speaking_for_dead(epis, dead, LPRO_DIED);
	return (NULL);
}
