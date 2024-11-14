/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 22:53:35 by gmarquis          #+#    #+#             */
/*   Updated: 2024/10/30 08:43:40 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/proto.h"

void	ts_print_philos_infos(t_sympos *sympos)
{
	int (i) = 0;
	int (n_philo) = sympos->philos[0].agal->n_philos;
	pthread_mutex_lock(&sympos->epis->mtx_printf);
	while (i < n_philo)
	{
		printf(LU_YEL1 "Philosopher[%2d] is here:\nhe start at %ld and think %ld\n" LU_END,
			sympos->philos[i].id, sympos->philos[i].agal->tt_start, sympos->philos[i].agal->tt_think);
		if (sympos->philos[0].agal->n_philos > 1)
		{
			pthread_mutex_lock(sympos->philos[i].lf_fork);

			printf(LU_YEL1 "lf_fork = %14p" LU_END,
				(void *)&*sympos->philos[i].lf_fork);

			pthread_mutex_unlock(sympos->philos[i].lf_fork);
		}
		else
			printf(LU_YEL1 "lf_fork = NULL" LU_END);
		pthread_mutex_lock(&sympos->philos[i].rg_fork);
		printf(LU_YEL1 " | rg_fork = %14p\n\n" LU_END,
			(void *)&sympos->philos[i].rg_fork);
		pthread_mutex_unlock(&sympos->philos[i].rg_fork);
		i++;
	}
	pthread_mutex_unlock(&sympos->epis->mtx_printf);
}

void	ts_print_sympos(t_sympos *sympos)
{
	pthread_mutex_lock(&sympos->epis->mtx_printf);
	printf(LU_BLU1 "Episkopos watches the symposium:\n"
		"He speak at %14p for %d philosophers\ntt_die: %ld\ntt_eat: %ld\n"
		"tt_sleep: %ld\nn_meal: %d\n" LU_END,
		(void *)&sympos->epis->mtx_printf, sympos->philos[0].agal->n_philos,
		sympos->philos[0].agal->tt_die, sympos->philos[0].agal->tt_eat,
		sympos->philos[0].agal->tt_sleep, sympos->philos[0].agal->n_meal);
	pthread_mutex_unlock(&sympos->epis->mtx_printf);
	ts_print_philos_infos(sympos);
}

//	-fsanitize=
//	./philo 199 190 60 60 5 | sed -r 's/\x1B\[[0-9;]*[A-Za-z]//g' | xclip -selection c
