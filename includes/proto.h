/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proto.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 14:16:57 by gmarquis          #+#    #+#             */
/*   Updated: 2024/10/30 10:06:39 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTO_H
# define PROTO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

# include "struct.h"
# include "define.h"

		//	act.c			//
int				ph_check_printf_verif(t_epis *epis);
void			ph_speaking(t_epis *epis, int id, char *message);
void			ph_waiting(unsigned long time);

		//	args_verif.c	//
t_sympos		*ph_args_verif_and_make_sympos(int argc, char **argv);

		//	init.c			//
t_sympos		*ph_init_sympos(t_agalma *tmp);

		//	init_philos.c	//
void			ph_init_philos(t_sympos *sympos, t_agalma *tmp);

		//	init_utils.c	//
void			*ph_init_malloc_mutex(t_sympos *sympos, pthread_mutex_t *mutex,
				int nbr, size_t var_size);
void			*ph_init_malloc(t_sympos *sympos, int nbr, size_t var_size);
void			ph_init_thread(t_sympos *sympos, pthread_t *thread, void *fun,
					void *arg);
void			ph_init_mtx(t_sympos *sympos, pthread_mutex_t *mtx);
void			ph_init_fork(t_sympos *sympos, t_philo *philo, t_philo *rg_philo,
					int pos);

		//	out.c			//
void			ph_quit_philo(t_sympos *sympos, int fd_out, char *message,
					int error_code);

		//	threading.c		//
void			ph_threading(t_sympos *sympos);

		//	utils.c			//
int				ph_take_var(pthread_mutex_t *mutex, int *var);
void			ph_incr_var(pthread_mutex_t *mutex, int *var);
void			ph_modif_var(pthread_mutex_t *mutex, int *dest, int src);
unsigned long	ph_actualtime(void);

		//	test_file.c		//
void			ts_print_philos_fork(t_sympos *sympos);
void			ts_print_philos_states(t_epis *epis);
void			ts_print_sympos(t_sympos *sympos);

		//		epis.c		//
void			*ph_routine_epis(void *tmp);
/*
		//		even.c		//
void			*ph_routine_even(void *tmp);

		//	uneven.c		//
void			*ph_routine_uneven(void *tmp);

		//	utils_routine.c	//
int				ph_check_die_while_thinking(t_philo *philo);
int				ph_check_die_while_sleeping(t_philo *philo);
void			ph_starting_philo(t_philo *philo, int *alive);
*/
#endif
