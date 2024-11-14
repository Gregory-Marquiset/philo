/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infos.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 07:54:54 by gmarquis          #+#    #+#             */
/*   Updated: 2024/11/05 20:56:01 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
for (tt_start)
{
	if (philo->id == 1) -> take one fork and die at tt_die
		tt_start = 0;

	if (philo->id == even) -> uneven start eating then even
		tt_start = tt_eat;

	if (philo->id == uneven) -> 1 start eating then even then uneven exepte 1
		tt_start = tt_eat * 2
}

for (tt_think)
{
	for (n_philos == even)
	{
		if (tt_eat > tt_sleep)
			tt_think = tt_eat - tt_sleep;
		if (tt_eat <= tt_sleep)
			tt_think = 0;
	}
	for (n_philo == uneven)
	{
		if (tt_eat > tt_sleep)
			tt_think = (tt_eat * 2) + (tt_eat - tt_sleep);
		if (tt_eat <= tt_sleep)
			tt_think = (tt_eat * 2);
	}
}
*/
