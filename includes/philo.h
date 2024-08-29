/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 14:16:57 by gmarquis          #+#    #+#             */
/*   Updated: 2024/08/30 01:45:55 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "struct.h"
# include "define.h"

		//	args_verif.c	//
t_sympos	*ft_args_verif_and_make_sympos(int argc, char **argv);

		//		init.c		//
t_sympos	*ft_init_sympos(t_epís *tmp);

		//		mutex_ft.c	//
void	ft_muprintf(pthread_mutex_t *mutex, int id, char *message);

		//		out.c		//
void	ft_quit_philo(t_sympos *sympos, int fd_out, char *message,
	int error_code);

		//		routine.c	//
void	*ft_routine(void *dexi_obeli);

		//		time.c		//
size_t	ft_actualtime(void);
void	ft_sleeping(size_t inter);

		//	test_file.c		//
void	ft_print_sympos(t_sympos *sympos);

#endif
