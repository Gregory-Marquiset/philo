/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 20:13:07 by gmarquis          #+#    #+#             */
/*   Updated: 2024/10/16 17:46:52 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/proto.h"

int	ph_sleeping(t_philo *philo)
{
	if (ph_check_sympos_states(philo))
		return (1);
	ph_speaking(philo->epis, philo->id, LPRO_SLEEP);
	ph_waiting(philo->epis->agal->tt_sleep);
	return (0);
}

void	ph_thinking(t_philo *philo)
{
	if (ph_check_sympos_states(philo))
		return ;
	ph_speaking(philo->epis, philo->id, LPRO_THINK);
}

void	ph_waiting(unsigned long time)
{
	unsigned long	init_time;

	init_time = ph_actualtime();
	while ((ph_actualtime() - init_time) < time)
	{
		usleep(time / 100);
	}
}
