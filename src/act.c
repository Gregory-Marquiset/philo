/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 20:13:07 by gmarquis          #+#    #+#             */
/*   Updated: 2024/09/29 18:13:23 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/proto.h"

void	ph_eating(t_philo *tmp)
{
	t_philo	*philo;

	philo = tmp;
	pthread_mutex_lock(philo->kine->mtx_sy_states);
	if (*(philo->epis->kine->sy_states) != OPEN)
	{
		pthread_mutex_unlock(philo->kine->mtx_sy_states);
		return ;
	}
	else
		pthread_mutex_unlock(philo->kine->mtx_sy_states);
	if (*(philo->kine->count_meal) > 0)
	{
		if ((ph_actualtime() - *(philo->kine->last_meal)) > philo->epis->agal->tt_die)
		{
			ph_modif_var(philo->kine->mtx_id_dead, philo->kine->id_dead, philo->id);
			return ;
		}
	}
	*(philo->kine->last_meal) = ph_actualtime();
	ph_speaking(philo->epis, philo->id, LPRO_EAT);
	while (1)
	{
		if ((ph_actualtime() - *(philo->kine->last_meal))
			>= philo->epis->agal->tt_eat)
			break ;
	}
	*(philo->kine->count_meal) += 1;
	if (philo->epis->agal->n_meal > 0)
	{
		if (*(philo->kine->count_meal) == philo->epis->agal->n_meal)
			ph_incr_var(philo->kine->mtx_phs_meals, philo->kine->phs_meals);
	}
}

void	ph_sleeping(t_philo *tmp)
{
	t_philo	*philo;
	size_t	init_time;

	philo = tmp;
	pthread_mutex_lock(philo->kine->mtx_sy_states);
	if (*(philo->epis->kine->sy_states) != OPEN)
	{
		pthread_mutex_unlock(philo->kine->mtx_sy_states);
		return ;
	}
	else
		pthread_mutex_unlock(philo->kine->mtx_sy_states);
	init_time = ph_actualtime();
	ph_speaking(philo->epis, philo->id, LPRO_SLEEP);
	while (1)
	{
		if ((ph_actualtime() - init_time) >= philo->epis->agal->tt_sleep)
			break ;
	}
}

void	ph_thinking(t_philo *tmp)
{
	t_philo	*philo;

	philo = tmp;
	pthread_mutex_lock(philo->kine->mtx_sy_states);
	if (*(philo->epis->kine->sy_states) != OPEN)
	{
		pthread_mutex_unlock(philo->kine->mtx_sy_states);
		return ;
	}
	else
		pthread_mutex_unlock(philo->kine->mtx_sy_states);
	ph_speaking(philo->epis, philo->id, LPRO_THINK);
}

void	ph_waiting(size_t time)
{
	size_t	init_time;

	init_time = ph_actualtime();
	while (1)
	{
		if ((ph_actualtime() - init_time) >= time)
			break ;
	}
}

void	ph_speaking(t_epis *epis, int id, char *message)
{
	size_t	start_time;

	start_time = epis->agal->st_time;

	while (1)
	{
		pthread_mutex_lock(&epis->use_printf->mtx_verif);
		if (*(epis->use_printf->verif) == 0)
		{
			*(epis->use_printf->verif) = id;
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


	pthread_mutex_lock(&epis->use_printf->mtx_verif);
	*(epis->use_printf->verif) = 0;
	pthread_mutex_unlock(&epis->use_printf->mtx_verif);
}
