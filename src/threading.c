/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 19:56:41 by gmarquis          #+#    #+#             */
/*   Updated: 2024/10/16 20:19:18 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/proto.h"

static void	ph_starting_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->epis->mtx->mtx_phs_states);
	pthread_mutex_unlock(&philo->epis->mtx->mtx_phs_states);
	while (ph_actualtime() < philo->epis->agal->st_time)
	{
		ph_waiting(1);
	}
}

static int	ph_check_die_while_sleeping(t_philo *philo)
{
	unsigned long	last_meal;
	unsigned long	tt_sleep;
	unsigned long	tt_die;
	unsigned long	tt_eat;

	last_meal = *philo->kine->last_meal;
	tt_sleep = philo->epis->agal->tt_sleep;
	tt_die = philo->epis->agal->tt_die;
	tt_eat = philo->epis->agal->tt_eat;
	if ((ph_actualtime() - (last_meal + tt_eat)) + tt_sleep <= tt_die)
		return (0);
	else
	{
		ph_speaking(philo->epis, philo->id, LPRO_SLEEP);
		ph_waiting(tt_die - ph_actualtime() - last_meal);
		ph_modif_var(&(philo->epis->mtx->mtx_id_dead),
			philo->epis->kine->id_dead, philo->id);
		return (1);
	}
}

static int	ph_check_die_while_eating(t_philo *philo)
{
	unsigned long	last_meal;
	unsigned long	tt_sleep;
	unsigned long	tt_die;
	unsigned long	tt_eat;

	last_meal = *philo->kine->last_meal;
	tt_sleep = philo->epis->agal->tt_sleep;
	tt_die = philo->epis->agal->tt_die;
	tt_eat = philo->epis->agal->tt_eat;
	if (ph_actualtime() - last_meal + tt_eat < tt_die)
	{
		ph_speaking(philo->epis, philo->id, LTEST_TEST);
		*(philo->kine->last_meal) = ph_actualtime();
		return (0);
	}
	else
	{
		ph_speaking(philo->epis, philo->id, LPRO_EAT);
		ph_waiting(tt_die);
		ph_modif_var(&(philo->epis->mtx->mtx_id_dead),
			philo->epis->kine->id_dead, philo->id);
		return (1);
	}
}

static void	*ph_routine_even(void *tmp)
{
	t_philo	*philo;
	int		verif = 0;
	int		alive = 0;
	int i = 0;

	philo = (t_philo *)tmp;
	ph_starting_philo(philo);
	ph_waiting(philo->epis->agal->tt_eat);
	while (verif == 0 && alive == 0)
	{
		verif = ph_take_var(&philo->epis->mtx->mtx_id_dead, philo->epis->kine->id_dead);
		if (verif != 0)
			break;
		alive = ph_check_die_while_eating(philo);
		if (alive)
			break ;
		ph_speaking(philo->epis, philo->id, LPRO_EAT);
		ph_waiting(philo->epis->agal->tt_eat);
		*(philo->kine->count_meal) += 1;
		if (philo->epis->agal->n_meal > 0)
		{
			if (*(philo->kine->count_meal) == philo->epis->agal->n_meal)
				ph_incr_var(philo->kine->mtx_phs_meals, philo->kine->phs_meals);
		}

		verif = ph_take_var(&philo->epis->mtx->mtx_id_dead, philo->epis->kine->id_dead);
		if (verif != 0)
			break;

		alive = ph_check_die_while_sleeping(philo);
		if (alive)
			break ;
		ph_speaking(philo->epis, philo->id, LPRO_SLEEP);
		ph_waiting(philo->epis->agal->tt_sleep);

		verif = ph_take_var(&philo->epis->mtx->mtx_id_dead, philo->epis->kine->id_dead);
		if (verif != 0)
			break;

		ph_speaking(philo->epis, philo->id, LPRO_THINK);
		if (philo->epis->agal->tt_think > 0)
			ph_waiting(philo->epis->agal->tt_think);

		verif = ph_take_var(&philo->epis->mtx->mtx_id_dead, philo->epis->kine->id_dead);
		if (verif != 0)
			break;

		i++;
	}
	return (NULL);
}

static void	*ph_routine_uneven(void *tmp)
{
	t_philo	*philo;
	int		verif = 0;
	int		alive = 0;
	int		i = 0;

	philo = (t_philo *)tmp;
	ph_starting_philo(philo);
	while (verif == 0 && alive == 0)
	{
		verif = ph_take_var(&philo->epis->mtx->mtx_id_dead, philo->epis->kine->id_dead);
		if (verif != 0)
			break;
		alive = ph_check_die_while_eating(philo);
		if (alive)
			break ;
		ph_speaking(philo->epis, philo->id, LPRO_EAT);
		*(philo->kine->last_meal) = ph_actualtime();
		ph_waiting(philo->epis->agal->tt_eat);
		*(philo->kine->count_meal) += 1;
		if (philo->epis->agal->n_meal > 0 && *(philo->kine->count_meal) == philo->epis->agal->n_meal)
			ph_incr_var(philo->kine->mtx_phs_meals, philo->kine->phs_meals);

		verif = ph_take_var(&philo->epis->mtx->mtx_id_dead, philo->epis->kine->id_dead);
		if (verif != 0)
			break;

		alive = ph_check_die_while_sleeping(philo);
		if (alive)
			break ;
		ph_speaking(philo->epis, philo->id, LPRO_SLEEP);
		ph_waiting(philo->epis->agal->tt_sleep);

		verif = ph_take_var(&philo->epis->mtx->mtx_id_dead, philo->epis->kine->id_dead);
		if (verif)
			break;

		ph_speaking(philo->epis, philo->id, LPRO_THINK);
		if (philo->epis->agal->tt_think > 0)
			ph_waiting(philo->epis->agal->tt_think);

		verif = ph_take_var(&philo->epis->mtx->mtx_id_dead, philo->epis->kine->id_dead);
		if (verif != 0)
			break;

		i++;
	}
	return (NULL);
}

static void	*ph_routine_epis(void *tmp)
{
	t_epis	*epis;
	int		dead;
	int		meal;

	epis = (t_epis *)tmp;
	dead = 0;
	meal = 0;
	epis->agal->st_time = ph_actualtime() + 101;
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
}*/

/*static void	*ph_routine_epis(void *tmp)
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
	ph_waiting(1);
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
