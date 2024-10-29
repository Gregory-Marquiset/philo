/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_epis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 07:46:37 by gmarquis          #+#    #+#             */
/*   Updated: 2024/10/25 09:34:12 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/proto.h"

static void	ph_init_use_printf(t_sympos *sympos)
{
	sympos->epis->use_printf = ph_init_malloc(sympos, 1, sizeof(t_printf));
	ph_init_mtx(sympos, sympos->epis->use_printf->mtx_printf);
	ph_init_mtx(sympos, sympos->epis->use_printf->mtx_verif);
	sympos->epis->use_printf->verif = ph_init_malloc(sympos, 1, sizeof(int));
	*(sympos->epis->use_printf->verif) = 0;
}

static void	ph_init_epis_kinesis(t_sympos *sympos)
{
	sympos->epis->kine = ph_init_malloc(sympos, 1, sizeof(t_e_kinesis));
	pthread_mutex_lock(&sympos->epis->mtx->mtx_id_dead);
	sympos->epis->kine->id_dead = ph_init_malloc_mutex(sympos,
			&sympos->epis->mtx->mtx_id_dead, 1, sizeof(int));
	*(sympos->epis->kine->id_dead) = 0;
	pthread_mutex_unlock(&sympos->epis->mtx->mtx_id_dead);
	pthread_mutex_lock(&sympos->epis->mtx->mtx_phs_states);
	sympos->epis->kine->phs_states = ph_init_malloc_mutex(sympos,
			&sympos->epis->mtx->mtx_phs_states, 1, sizeof(int));
	*(sympos->epis->kine->phs_states) = 0;
	pthread_mutex_unlock(&sympos->epis->mtx->mtx_phs_states);
	pthread_mutex_lock(&sympos->epis->mtx->mtx_phs_meals);
	sympos->epis->kine->phs_meals = ph_init_malloc_mutex(sympos,
			&sympos->epis->mtx->mtx_phs_meals, 1, sizeof(int));
	*(sympos->epis->kine->phs_meals) = 0;
	pthread_mutex_unlock(&sympos->epis->mtx->mtx_phs_meals);
}

static void	ph_init_epis_mtx(t_sympos *sympos)
{
	sympos->epis->mtx = ph_init_malloc(sympos, 1, sizeof(t_e_mtx));
	ph_init_mtx(sympos, sympos->epis->mtx->mtx_id_dead);
	ph_init_mtx(sympos, sympos->epis->mtx->mtx_phs_meals);
	ph_init_mtx(sympos, sympos->epis->mtx->mtx_phs_states);
}

static void	ph_init_epis_agalma(t_sympos *sympos, t_e_agalma *tmp)
{
	sympos->epis->agal = ph_init_malloc(sympos, 1, sizeof(t_e_agalma));
	sympos->epis->agal->n_philos = tmp->n_philos;
	sympos->epis->agal->n_meal = tmp->n_meal;
	sympos->epis->agal->st_time = ph_actualtime();
	sympos->epis->agal->tt_die = tmp->tt_die;
	sympos->epis->agal->tt_eat = tmp->tt_eat;
	sympos->epis->agal->tt_sleep = tmp->tt_sleep;
	sympos->epis->agal->tt_think = tmp->tt_think;
	sympos->epis->agal->tt_alt = tmp->tt_alt;
}

void	ph_init_epis(t_sympos *sympos, t_e_agalma *tmp)
{
	sympos->epis = ph_init_malloc(sympos, 1, sizeof(t_epis));
	ph_init_epis_agalma(sympos, tmp);
	ph_init_epis_mtx(sympos);
	ph_init_epis_kinesis(sympos);
	ph_init_use_printf(sympos);
	sympos->epis->thread_ep = 0;
}