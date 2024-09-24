/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 22:53:35 by gmarquis          #+#    #+#             */
/*   Updated: 2024/09/24 21:31:06 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "includes/proto.h"

void	ph_print_sympos(t_sympos *sympos)
{
	t_sympos	*tmp = sympos;

	int	(i) = 0;
	printf(LU_BLU1 "Epískopos watches the symposium:\nHe speak at %14p for %d philosophers\n"
		"tt_die: %ld\ntt_eat: %ld\ntt_sleep: %ld\nn_meal: %d\n\n" LU_END,
		(void *)&tmp->philos[i].lf_fork, tmp->epís->n_philos,
		tmp->epís->time_to_die, tmp->epís->time_to_eat,
		tmp->epís->time_to_sleep, tmp->epís->n_meal);
	while (i < tmp->epís->n_philos)
	{
		printf(LU_MAJ1 "Philosopher[%d] philo_state = %d | philo_meals = %d\n"
			LU_END, i + 1, tmp->epís->philos_states[i], tmp->epís->philos_meals[i]);
		i++;
	}
	printf("\n");
	i = 0;
	while (i < tmp->epís->n_philos)
	{
		printf(LU_YEL1 "Philosopher[%2d] is here:\nrg_fork = %14p | lf_fork = %14p\n\n"
			LU_END, tmp->philos[i].id ,(void *)&*tmp->philos[i].rg_fork,
			(void *)&tmp->philos[i].lf_fork);
		i++;
	}
}
