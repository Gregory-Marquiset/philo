/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 19:56:41 by gmarquis          #+#    #+#             */
/*   Updated: 2024/10/15 19:14:18 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/proto.h"

static void	*ph_routine_even(void *tmp)
{
	t_philo	*philo;
	int i = 0;

	philo = (t_philo *)tmp;
	pthread_mutex_lock(&philo->epis->mtx->mtx_phs_states);
	pthread_mutex_unlock(&philo->epis->mtx->mtx_phs_states);
	while (ph_actualtime() < philo->epis->agal->st_time)
	{
		ph_waiting(1);
	}
	while (i < philo->epis->agal->n_meal)
	{
		if (i % 2 == 0)
			ph_waiting(philo->epis->agal->tt_eat);
		ph_speaking(philo->epis, philo->id, LPRO_EAT);

		pthread_mutex_lock(&philo->rg_fork);
		pthread_mutex_lock(philo->lf_fork);

		ph_waiting(philo->epis->agal->tt_eat);

		pthread_mutex_unlock(&philo->rg_fork);
		pthread_mutex_unlock(philo->lf_fork);

		ph_speaking(philo->epis, philo->id, LPRO_SLEEP);
		ph_waiting(philo->epis->agal->tt_sleep);
		ph_speaking(philo->epis, philo->id, LPRO_THINK);
		i++;
	}
	return (NULL);
}

static void	*ph_routine_uneven(void *tmp)
{
	t_philo	*philo;
	int	i = 0;

	philo = (t_philo *)tmp;
	pthread_mutex_lock(&philo->epis->mtx->mtx_phs_states);
	pthread_mutex_unlock(&philo->epis->mtx->mtx_phs_states);
	while (ph_actualtime() < philo->epis->agal->st_time)
	{
		ph_waiting(1);
	}
	while (i < philo->epis->agal->n_meal)
	{
		if (i % 2 != 0)
			ph_waiting(philo->epis->agal->tt_eat);
		ph_speaking(philo->epis, philo->id, LPRO_EAT);

		pthread_mutex_lock(philo->lf_fork);
		pthread_mutex_lock(&philo->rg_fork);

		ph_waiting(philo->epis->agal->tt_eat);

		pthread_mutex_lock(philo->lf_fork);
		pthread_mutex_lock(&philo->rg_fork);

		ph_speaking(philo->epis, philo->id, LPRO_SLEEP);
		ph_waiting(philo->epis->agal->tt_sleep);
		ph_speaking(philo->epis, philo->id, LPRO_THINK);
		i++;
	}
	return (NULL);
}

static void	*ph_routine_epis(void *tmp)
{
	t_epis	*epis;

	epis = (t_epis *)tmp;
	epis->agal->st_time = ph_actualtime() + 100;
	return (NULL);
}

/*static void	*ph_routine_philos(void *tmp)
{
	t_philo	*philo;
	int		turn;

	philo = (t_philo *)tmp;
	while (ph_actualtime() < philo->epis->agal->st_time)
	{
		ph_waiting(1);
	}
	turn = 0;
	while (turn == 0)
	{
		turn = ph_eating(philo);
		turn = ph_sleeping(philo);
		ph_thinking(philo);
	}
	return (NULL);
}

static void	*ph_routine_epis(void *tmp)
{
	t_epis *epis;
	int		dead;
	int		meal;

	epis = (t_epis *)tmp;
	dead = 0;
	meal = 0;
	//ph_open_table(epis);
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
}*/

void	ph_threading(t_sympos *sympos)
{
	int	i;

	ph_init_thread(sympos, &sympos->epis->thread_ep, &ph_routine_epis,
		sympos->epis);
	i = 0;
	pthread_mutex_lock(&sympos->epis->mtx->mtx_phs_states);
	while (i < sympos->epis->agal->n_philos)
	{
		if ((i + 1) % 2 == 0)
		{
			ph_init_thread(sympos, &sympos->philos[i].thread_ph, &ph_routine_even,
				&sympos->philos[i]);
		}
		else
		{
			ph_init_thread(sympos, &sympos->philos[i].thread_ph, &ph_routine_uneven,
				&sympos->philos[i]);
		}
		i++;
	}
	pthread_mutex_unlock(&sympos->epis->mtx->mtx_phs_states);
	i = 0;
	while (i < sympos->epis->agal->n_philos)
	{
		if (pthread_join(sympos->philos[i].thread_ph, NULL))
			ph_quit_philo(sympos, 2, LERR_PT_JOIN, CERR_PT_JOIN);
		i++;
	}
	if (pthread_join(sympos->epis->thread_ep, NULL))
		ph_quit_philo(sympos, 2, LERR_PT_JOIN, CERR_PT_JOIN);
}
