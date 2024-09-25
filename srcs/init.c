/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 22:41:45 by gmarquis          #+#    #+#             */
/*   Updated: 2024/09/25 18:46:18 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/proto.h"

static void	ph_init_fork(t_sympos *sympos, t_philo *philo, t_philo *rg_philo,
	int pos)
{
	if (pos == 0)
	{
		if (pthread_mutex_init(&philo->lf_fork, NULL))
			ph_quit_philo(sympos, 2, LERR_MU_INIT, CERR_MU_INIT);
	}
	else if (pos == 1)
	{
		if (pthread_mutex_init(&philo->lf_fork, NULL))
			ph_quit_philo(sympos, 2, LERR_MU_INIT, CERR_MU_INIT);
		philo->rg_fork = &rg_philo->lf_fork;
	}
	else if (pos == 2)
		philo->rg_fork = &rg_philo->lf_fork;
}

static void	ph_init_philos(t_sympos *sympos)
{
	int	i;

	i = 0;
	sympos->philos = ph_init_malloc(sympos, sympos->epis->agal->n_philos,
			sizeof(t_philo));
	while (i < sympos->epis->agal->n_philos)
	{
		sympos->philos[i].id = i + 1;
		sympos->philos[i].thread_ph = 0;
		sympos->philos[i].kine = ph_init_malloc(sympos, 1, sizeof(t_p_kinesis));
		sympos->philos[i].kine->last_meal = 0;
		sympos->philos[i].kine->count_meal = 0;
		sympos->philos[i].kine->ph_state = &(sympos->epis->kine->phs_states[i]);
		*(sympos->philos[i].kine->ph_state) = READY;
		sympos->philos[i].kine->ph_meal = &(sympos->epis->kine->phs_meals[i]);
		sympos->philos[i].epis = sympos->epis;
		if (i == 0)
			ph_init_fork(sympos, &sympos->philos[i], NULL, 0);
		else
			ph_init_fork(sympos, &sympos->philos[i], &sympos->philos[i - 1], 1);
		i++;
	}
	if (sympos->epis->agal->n_philos > 1)
		ph_init_fork(sympos, &sympos->philos[0], &sympos->philos[i - 1], 2);
	sympos->epis->kine->sy_states = OPEN;
}

static void	ph_init_states_meals(t_sympos *sympos)
{
	int	i;

	i = 0;
	sympos->epis->kine->phs_states = ph_init_malloc(sympos,
			sympos->epis->agal->n_philos, sizeof(int));
	sympos->epis->kine->phs_meals = ph_init_malloc(sympos,
			sympos->epis->agal->n_philos, sizeof(int));
	while (i < sympos->epis->agal->n_philos)
	{
		sympos->epis->kine->phs_states[i] = GET_READY;
		if (sympos->epis->agal->n_meal == -1)
			sympos->epis->kine->phs_meals[i] = -1;
		else
			sympos->epis->kine->phs_meals[i] = 0;
		i++;
	}
}

static void	ph_init_epis(t_sympos *sympos, t_e_agalma *tmp)
{
	sympos->epis = ph_init_malloc(sympos, 1, sizeof(t_epis));
	sympos->epis->agal = ph_init_malloc(sympos, 1, sizeof(t_e_agalma));
	sympos->epis->agal->n_philos = tmp->n_philos;
	sympos->epis->agal->n_meal = tmp->n_meal;
	sympos->epis->agal->st_time = 0;
	sympos->epis->agal->n_philos = tmp->n_philos;
	sympos->epis->agal->tt_die = tmp->tt_die;
	sympos->epis->agal->tt_eat = tmp->tt_eat;
	sympos->epis->agal->tt_sleep = tmp->tt_sleep;
	sympos->epis->kine = ph_init_malloc(sympos, 1, sizeof(t_e_kinesis));
	sympos->epis->kine->id_dead = 0;
	sympos->epis->kine->sy_states = SETING;
	ph_init_states_meals(sympos);
	if (pthread_mutex_init(&sympos->epis->mprintf, NULL))
		ph_quit_philo(sympos, 2, LERR_MU_INIT, CERR_MU_INIT);
	sympos->epis->thread_ep = 0;
}

t_sympos	*ph_init_sympos(t_e_agalma *tmp)
{
	t_sympos	*sympos;

	sympos = NULL;
	sympos = ph_init_malloc(sympos, 1, sizeof(t_sympos));
	ph_init_epis(sympos, tmp);
	ph_init_philos(sympos);
	return (sympos);
}
