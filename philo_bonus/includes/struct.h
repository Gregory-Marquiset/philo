/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:41:17 by gmarquis          #+#    #+#             */
/*   Updated: 2024/12/04 08:54:55 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

		//		philo		//

typedef struct s_agalma
{
	int				n_meal;
	unsigned long	st_time;
	unsigned long	tt_start;
	unsigned long	tt_eat;
	unsigned long	tt_sleep;
	unsigned long	tt_think;
	unsigned long	tt_die;
}				t_agalma;

typedef struct s_philo
{
	int				id;
	t_agalma		*agal;
	unsigned long	*last_meal;
	int				*count_meal;
}				t_philo;

		//		symposium		//

typedef struct s_sympos
{
	int		n_philos;
	t_philo	*philos;
}				t_sympos;

#endif
