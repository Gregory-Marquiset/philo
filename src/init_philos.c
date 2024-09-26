/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 07:20:41 by gmarquis          #+#    #+#             */
/*   Updated: 2024/09/26 14:35:32 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/proto.h"

static void	ph_init_philo_kine(t_sympos *sympos, t_philo *philo)
{
	philo->kine = ph_init_malloc(sympos, 1, sizeof(t_p_kinesis));
	philo->kine->last_meal = 0;
	philo->kine->count_meal = 0;
	philo->kine->phs_state = sympos->epis->kine->phs_states;
	philo->kine->phs_meal = sympos->epis->kine->phs_meals;
	philo->kine->mtx_meal = &(sympos->epis->mtx->mtx_phs_meals);
	philo->kine->phs_state = sympos->epis->kine->phs_states;
	philo->kine->mtx_state = &(sympos->epis->mtx->mtx_phs_states);
	philo->kine->mtx_printf = &(sympos->epis->mtx->mtx_printf);
}

void	ph_init_philos(t_sympos *sympos)
{
	int	i;

	i = 0;
	sympos->philos = ph_init_malloc(sympos, sympos->epis->agal->n_philos,
			sizeof(t_philo));
	while (i < sympos->epis->agal->n_philos)
	{
		sympos->philos[i].id = i + 1;
		sympos->philos[i].thread_ph = 0;
		ph_init_philo_kine(sympos, &(sympos->philos[i]));
		sympos->philos[i].epis = sympos->epis;
		if (i == 0)
			ph_init_fork(sympos, &sympos->philos[i], NULL, 0);
		else
			ph_init_fork(sympos, &sympos->philos[i], &sympos->philos[i - 1], 1);
		i++;
	}
	if (sympos->epis->agal->n_philos > 1)
		ph_init_fork(sympos, &sympos->philos[0], &sympos->philos[i - 1], 2);
}