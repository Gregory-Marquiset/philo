/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 20:13:07 by gmarquis          #+#    #+#             */
/*   Updated: 2024/10/31 14:54:48 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/proto.h"

int	ph_check_printf_verif(t_epis *epis)
{
	int	tmp;

	pthread_mutex_lock(&epis->use_printf->mtx_verif);
	tmp = epis->use_printf->verif;
	pthread_mutex_unlock(&epis->use_printf->mtx_verif);
	if (tmp == -2)
		return (1);
	else
		return (0);
}

void	ph_speaking(t_epis *epis, int id, char *message)
{
	unsigned long	start_time;

	start_time = epis->agal->st_time;
	if (ph_check_printf_verif(epis))
		return ;
	pthread_mutex_lock(&epis->use_printf->mtx_printf);
	printf("%-10ld %-4d %s", (ph_actualtime() - start_time), id, message);
	pthread_mutex_unlock(&epis->use_printf->mtx_printf);
}

void	ph_waiting(t_philo *philo, unsigned long time)
{
	unsigned long	init_time;

	init_time = ph_actualtime();
	while ((ph_actualtime() - init_time) < time)
	{
		usleep(1);
		if (ph_take_var(&philo->epis->mtx->mtx_id_dead, philo->epis->kine->id_dead) != 0)
			break ;
	}
}
