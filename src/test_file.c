/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 22:53:35 by gmarquis          #+#    #+#             */
/*   Updated: 2024/10/25 10:10:56 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/proto.h"

void	ts_print_philos_fork(t_sympos *sympos)
{
	int (i) = 0;
	pthread_mutex_lock(&sympos->epis->use_printf->mtx_printf);
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
	pthread_mutex_unlock(&sympos->epis->use_printf->mtx_printf);
}

void	ts_print_philos_states(t_epis *epis)
{
	pthread_mutex_lock(&epis->use_printf->mtx_printf);
	pthread_mutex_lock(&epis->mtx->mtx_phs_states);
	pthread_mutex_lock(&epis->mtx->mtx_phs_meals);
	printf(LU_MAJ1 "\nEpiskopos check:\n phs_states = %d "
		"| phs_meals = %d\n\n" LU_END, *(epis->kine->phs_states),
		*(epis->kine->phs_meals));
	pthread_mutex_unlock(&epis->mtx->mtx_phs_meals);
	pthread_mutex_unlock(&epis->mtx->mtx_phs_states);
	pthread_mutex_unlock(&epis->use_printf->mtx_printf);
}

void	ts_print_sympos(t_sympos *sympos)
{
	pthread_mutex_lock(&sympos->epis->use_printf->mtx_printf);
	printf(LU_BLU1 "Episkopos watches the symposium:\n"
		"He speak at %14p for %d philosophers\ntt_die: %ld\ntt_eat: %ld\n"
		"tt_sleep: %ld\nn_meal: %d\ntt_think = %ld\ntt_alt = %ld\n" LU_END,
		(void *)&sympos->epis->use_printf->mtx_printf, sympos->epis->agal->n_philos,
		sympos->epis->agal->tt_die, sympos->epis->agal->tt_eat,
		sympos->epis->agal->tt_sleep, sympos->epis->agal->n_meal,
		sympos->epis->agal->tt_think, sympos->epis->agal->tt_alt);
	pthread_mutex_unlock(&sympos->epis->use_printf->mtx_printf);
	ts_print_philos_states(sympos->epis);
	ts_print_philos_fork(sympos);
}

//	-fsanitize=
//	./philo 199 190 60 60 5 | sed -r 's/\x1B\[[0-9;]*[A-Za-z]//g' | xclip -selection c
