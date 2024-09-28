/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 22:53:35 by gmarquis          #+#    #+#             */
/*   Updated: 2024/09/28 17:28:46 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/proto.h"

void	ts_print_philos_fork(t_sympos *sympos)
{
	int (i) = 0;
	pthread_mutex_lock(&sympos->epis->mtx->mtx_printf);
	while (i < sympos->epis->agal->n_philos)
	{
		printf(LU_YEL1 "Philosopher[%2d] is here:\n" LU_END,
			sympos->philos[i].id);
		if ((void *)&*sympos->philos[i].lf_fork != NULL)
		{
			pthread_mutex_lock(sympos->philos[i].lf_fork);
			printf(LU_YEL1 "lf_fork = %14p" LU_END,
				(void *)&*sympos->philos[i].lf_fork);
			pthread_mutex_unlock(sympos->philos[i].lf_fork);
		}
		else
			printf(LU_YEL1 "lf_fork = NULL" LU_END);
		if ((void *)&sympos->philos[i].rg_fork != NULL)
		{
			pthread_mutex_lock(&sympos->philos[i].rg_fork);
			printf(LU_YEL1 " | rg_fork = %14p\n\n" LU_END,
				(void *)&sympos->philos[i].rg_fork);
			pthread_mutex_unlock(&sympos->philos[i].rg_fork);
		}
		i++;
	}
	pthread_mutex_unlock(&sympos->epis->mtx->mtx_printf);
}

void	ts_print_philos_states(t_epis *epis)
{
	pthread_mutex_lock(&epis->mtx->mtx_printf);
	pthread_mutex_lock(&epis->mtx->mtx_phs_states);
	pthread_mutex_lock(&epis->mtx->mtx_phs_meals);
	pthread_mutex_lock(&epis->mtx->mtx_sy_states);
	printf(LU_MAJ1 "\nEpiskopos check:\nsy_states %d | phs_states = %d "
		"| phs_meals = %d\n\n" LU_END, *(epis->kine->sy_states),
		*(epis->kine->phs_states), *(epis->kine->phs_meals));
	pthread_mutex_unlock(&epis->mtx->mtx_sy_states);
	pthread_mutex_unlock(&epis->mtx->mtx_phs_meals);
	pthread_mutex_unlock(&epis->mtx->mtx_phs_states);
	pthread_mutex_unlock(&epis->mtx->mtx_printf);
}

void	ts_print_sympos(t_sympos *sympos)
{
	pthread_mutex_lock(&sympos->epis->mtx->mtx_printf);
	printf(LTEST_SUCC_IN LU_BLU1 "Episkopos watches the symposium:\n"
		"He speak at %14p for %d philosophers\ntt_die: %ld\ntt_eat: %ld\n"
		"tt_sleep: %ld\nn_meal: %d\n" LU_END,
		(void *)&sympos->epis->mtx->mtx_printf, sympos->epis->agal->n_philos,
		sympos->epis->agal->tt_die, sympos->epis->agal->tt_eat,
		sympos->epis->agal->tt_sleep, sympos->epis->agal->n_meal);
	pthread_mutex_unlock(&sympos->epis->mtx->mtx_printf);
	ts_print_philos_states(sympos->epis);
	ts_print_philos_fork(sympos);
}
