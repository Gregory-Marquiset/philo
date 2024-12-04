/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   epis.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 21:55:16 by gmarquis          #+#    #+#             */
/*   Updated: 2024/12/04 08:37:48 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/proto.h"

static void	ph_speaking_for_dead(t_epis *epis, int id, char *message)
{
	unsigned long	st_time;

	st_time = *epis->st_time;
	pthread_mutex_lock(&epis->mtx_verif);
	*(epis->verif) = -2;
	pthread_mutex_unlock(&epis->mtx_verif);
	pthread_mutex_lock(&epis->mtx_printf);
	printf("%-10ld %-4d %s", (ph_actualtime() - st_time), id, message);
	pthread_mutex_unlock(&epis->mtx_printf);
}

static int	ph_check_id_dead(t_epis *epis)
{
	int	res;

	res = 0;
	pthread_mutex_lock(&epis->mtx_id_dead);
	res = *epis->id_dead;
	pthread_mutex_unlock(&epis->mtx_id_dead);
	return (res);
}

static int	ph_without_target_meals(t_epis *epis)
{
	int	res;

	res = 0;
	while (res == 0)
	{
		pthread_mutex_lock(&epis->mtx_id_dead);
		res = *(epis->id_dead);
		pthread_mutex_unlock(&epis->mtx_id_dead);
		ph_waiting(1);
	}
	return (res);
}

static int	ph_with_target_meals(t_epis *epis)
{
	while (1)
	{
		pthread_mutex_lock(&epis->mtx_phs_meals);
		if (*(epis->phs_meals) >= epis->n_philos)
		{
			pthread_mutex_unlock(&epis->mtx_phs_meals);
			return (1);
		}
		else
		{
			pthread_mutex_unlock(&epis->mtx_phs_meals);
			if (ph_check_id_dead(epis))
				return (0);
		}
		ph_waiting(1);
	}
}

void	*ph_routine_epis(void *tmp)
{
	t_epis	*epis;
	int		dead;
	int		meal;

	epis = (t_epis *)tmp;
	dead = 0;
	meal = 0;
	while (*epis->st_time > ph_actualtime())
		ph_waiting(1);
	while (dead == 0 && meal == 0)
	{
		if (epis->n_meal > 0)
		{
			meal = ph_with_target_meals(epis);
			if (meal == 1)
				ph_modif_var(&epis->mtx_id_dead, epis->id_dead, -1);
			dead = ph_check_id_dead(epis);
		}
		else
			dead = ph_without_target_meals(epis);
	}
	if (dead > 0)
		ph_speaking_for_dead(epis, dead, LPRO_DIED);
	return (NULL);
}
