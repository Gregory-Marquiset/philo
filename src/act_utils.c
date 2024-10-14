/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 21:55:16 by gmarquis          #+#    #+#             */
/*   Updated: 2024/10/14 23:03:22 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/proto.h"

int	ph_check_sympos_states(t_philo *philo)
{
	int	tmp;

	pthread_mutex_lock(philo->kine->mtx_id_dead);
	tmp = *(philo->epis->kine->id_dead);
	pthread_mutex_unlock(philo->kine->mtx_id_dead);
	if (tmp != 0)
		return (1);
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

int	ph_check_printf_verif(t_epis *epis)
{
	int	tmp;

	pthread_mutex_lock(&epis->use_printf->mtx_verif);
	tmp = *(epis->use_printf->verif);
	pthread_mutex_unlock(&epis->use_printf->mtx_verif);
	if (tmp == -2)
		return (1);
	else
		return (0);
}

void	ph_speaking(t_epis *epis, int id, char *message)
{
	unsigned long	start_time;
	unsigned long	ttime = ph_actualtime();

	start_time = epis->agal->st_time;
	/*if (ph_check_printf_verif(epis))
		return ;*/
	pthread_mutex_lock(&epis->use_printf->mtx_printf);
	printf("%-10ld %-4d %s", (ttime - start_time), id, message);
	pthread_mutex_unlock(&epis->use_printf->mtx_printf);
}
