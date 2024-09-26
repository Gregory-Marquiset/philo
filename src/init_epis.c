/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_epis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 07:46:37 by gmarquis          #+#    #+#             */
/*   Updated: 2024/09/26 08:00:19 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/proto.h"

static void	ph_init_epis_mtx(t_sympos *sympos)
{
	sympos->epis->mtx = ph_init_malloc(sympos, 1, sizeof(t_e_mtx));
	if (!sympos->epis->mtx)
		ph_quit_philo(sympos, 2, LERR_MALLOC, CERR_MALLOC);
	ph_init_mtx(sympos, sympos->epis->mtx->printf);
	ph_init_mtx(sympos, sympos->epis->mtx->phs_meals);
	ph_init_mtx(sympos, sympos->epis->mtx->phs_states);
	ph_init_mtx(sympos, sympos->epis->mtx->sy_states);
}

static void	ph_init_epis_kinesis(t_sympos *sympos, t_e_agalma *tmp)
{
	int	i;

	i = 0;
	sympos->epis->kine = ph_init_malloc(sympos, 1, sizeof(t_e_kinesis));
	sympos->epis->kine->id_dead = 0;
	sympos->epis->kine->sy_states = SETING;
	sympos->epis->kine->phs_states = ph_init_malloc(sympos, tmp->n_philos,
			sizeof(int));
	sympos->epis->kine->phs_meals = ph_init_malloc(sympos, tmp->n_philos,
			sizeof(int));
	while (i < tmp->n_philos)
	{
		sympos->epis->kine->phs_states[i] = GET_READY;
		if (tmp->n_meal == -1)
			sympos->epis->kine->phs_meals[i] = -1;
		else
			sympos->epis->kine->phs_meals[i] = 0;
		i++;
	}
}

static void	ph_init_epis_agalma(t_sympos *sympos, t_e_agalma *tmp)
{
	sympos->epis->agal = ph_init_malloc(sympos, 1, sizeof(t_e_agalma));
	sympos->epis->agal->n_philos = tmp->n_philos;
	sympos->epis->agal->n_meal = tmp->n_meal;
	sympos->epis->agal->st_time = 0;
	sympos->epis->agal->n_philos = tmp->n_philos;
	sympos->epis->agal->tt_die = tmp->tt_die;
	sympos->epis->agal->tt_eat = tmp->tt_eat;
	sympos->epis->agal->tt_sleep = tmp->tt_sleep;
}

void	ph_init_epis(t_sympos *sympos, t_e_agalma *tmp)
{
	sympos->epis = ph_init_malloc(sympos, 1, sizeof(t_epis));
	ph_init_epis_agalma(sympos, tmp);
	ph_init_epis_kinesis(sympos, tmp);
	ph_init_epis_mtx(sympos);
	sympos->epis->thread_ep = 0;
}
