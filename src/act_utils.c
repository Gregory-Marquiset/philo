/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 21:55:16 by gmarquis          #+#    #+#             */
/*   Updated: 2024/10/01 20:09:56 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/proto.h"

int	ph_check_sympos_states(t_philo *philo)
{
	pthread_mutex_lock(philo->kine->mtx_sy_states);
	if (*(philo->epis->kine->sy_states) != OPEN)
	{
		pthread_mutex_unlock(philo->kine->mtx_sy_states);
		return (1);
	}
	pthread_mutex_unlock(philo->kine->mtx_sy_states);
	pthread_mutex_lock(philo->kine->mtx_id_dead);
	if (*(philo->epis->kine->id_dead) != 0)
	{
		pthread_mutex_unlock(philo->kine->mtx_id_dead);
		return (1);
	}
	pthread_mutex_unlock(philo->kine->mtx_id_dead);
	return (0);
}

int	ph_check_tt_eat(t_philo *philo)
{
	if (*(philo->kine->count_meal) > 0)
	{
		if ((ph_actualtime() - *(philo->kine->last_meal))
			> philo->epis->agal->tt_die)
		{
			ph_modif_var(philo->kine->mtx_id_dead, philo->kine->id_dead,
				philo->id);
			return (1);
		}
	}
	return (0);
}

int	ph_check_printf_verif(t_epis *epis, int id)
{
	while (1)
	{
		pthread_mutex_lock(&epis->use_printf->mtx_verif);
		if (*(epis->use_printf->verif) == 0)
		{
			*(epis->use_printf->verif) = id;
			pthread_mutex_unlock(&epis->use_printf->mtx_verif);
			break ;
		}
		else if (*(epis->use_printf->verif) == -2)
		{
			pthread_mutex_unlock(&epis->use_printf->mtx_verif);
			return (1);
		}
		else
		{
			pthread_mutex_unlock(&epis->use_printf->mtx_verif);
			ph_waiting(1);
		}
	}
	return (0);
}

void	ph_speaking(t_epis *epis, int id, char *message)
{
	size_t	start_time;

	start_time = epis->agal->st_time;
	if (ph_check_printf_verif(epis, id))
		return ;
	pthread_mutex_lock(&epis->use_printf->mtx_printf);
	printf("%-10ld %-4d %s", (ph_actualtime() - start_time), id, message);
	pthread_mutex_unlock(&epis->use_printf->mtx_printf);
	pthread_mutex_lock(&epis->use_printf->mtx_verif);
	*(epis->use_printf->verif) = 0;
	pthread_mutex_unlock(&epis->use_printf->mtx_verif);
}
