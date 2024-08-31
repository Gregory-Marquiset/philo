/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 22:53:35 by gmarquis          #+#    #+#             */
/*   Updated: 2024/08/31 19:01:43 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "includes/proto.h"

void	ft_print_sympos(t_sympos *sympos)
{
	t_sympos	*tmp = sympos;

	int	(i) = 0;
	printf(LU_BLU1 "Epískopos watches the symposium:\nHe speak at %14p for %d_philosophers\n"
		"tt_die: %ld\ntt_eat: %ld\ntt_sleep: %ld\nn_meal: %d\n\n" LU_END,
		(void *)&tmp->philos[i].aris_obeli, tmp->epís->n_philos,
		tmp->epís->time_to_die, tmp->epís->time_to_eat,
		tmp->epís->time_to_sleep, tmp->epís->n_meal);
	while (i < tmp->epís->n_philos)
	{
		printf(LU_MAJ1 "Philosopher[%d] meal_stat = %d\n" LU_END, i + 1, tmp->epís->meal_stat[i]);
		i++;
	}
	printf("\n");
	i = 0;
	while (i < tmp->epís->n_philos)
	{
		printf(LU_YEL1 "Philosopher[%2d] is here:\nDexiós = %14p | Aristerós = %14p\n\n" LU_END, tmp->philos[i].id ,(void *)&*tmp->philos[i].dexi_obeli, (void *)&tmp->philos[i].aris_obeli);
		i++;
	}
}
