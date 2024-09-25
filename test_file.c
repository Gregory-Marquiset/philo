/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 22:53:35 by gmarquis          #+#    #+#             */
/*   Updated: 2024/09/25 10:44:28 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "includes/proto.h"

void	ph_print_sympos(t_sympos *sympos)
{
	t_sympos	*tmp = sympos;

	int	(i) = 0;
	printf(LU_BLU1 "Episkopos watches the symposium:\nHe speak at %14p for %d philosophers\n"
		"tt_die: %ld\ntt_eat: %ld\ntt_sleep: %ld\nn_meal: %d\n\n" LU_END,
		(void *)&tmp->philos[i].lf_fork, tmp->epis->n_philos,
		tmp->epis->time_to_die, tmp->epis->time_to_eat,
		tmp->epis->time_to_sleep, tmp->epis->n_meal);
	while (i < tmp->epis->n_philos)
	{
		printf(LU_MAJ1 "Philosopher[%d] philo_state = %d | philo_meals = %d\n"
			LU_END, i + 1, tmp->epis->philos_states[i], tmp->epis->philos_meals[i]);
		i++;
	}
	printf("\n");
	i = 0;
	while (i < tmp->epis->n_philos)
	{
		printf(LU_YEL1 "Philosopher[%2d] is here:\nrg_fork = %14p | lf_fork = %14p\n\n"
			LU_END, tmp->philos[i].id ,(void *)&*tmp->philos[i].rg_fork,
			(void *)&tmp->philos[i].lf_fork);
		i++;
	}
}
