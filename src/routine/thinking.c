/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thinking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 12:24:18 by gmarquis          #+#    #+#             */
/*   Updated: 2024/11/03 15:39:28 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/proto.h"

int	ph_check_die_while_thinking(t_philo *philo)
{
	long long		tt_result;
	unsigned long	last_meal;
	unsigned long	tt_die;

	last_meal = *philo->kine->last_meal;
	tt_die = philo->epis->agal->tt_die;
	tt_result = (long long)tt_die - ((long long)ph_actualtime() - (long long)last_meal);
	if (tt_result > 0)
		return (0);
	else
	{
		ph_speaking(philo->epis, philo->id, LPRO_THINK);
		ph_waiting((long long)tt_die - ((long long)ph_actualtime() - (long long)last_meal));
		ph_modif_var(&(philo->epis->mtx->mtx_id_dead),
			philo->epis->kine->id_dead, philo->id);
		return (1);
	}
}
