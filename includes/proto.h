/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proto.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 14:16:57 by gmarquis          #+#    #+#             */
/*   Updated: 2024/09/28 18:18:58 by gmarquis         ###   ########.fr       */
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
void		ph_eating(t_philo *tmp);
void		ph_sleeping(t_philo *tmp);
void		ph_thinking(t_philo *tmp);
void		ph_waiting(size_t time);

		//	args_verif.c	//
t_sympos	*ph_args_verif_and_make_sympos(int argc, char **argv);

		//	epis_utils.c	//
void		ph_without_target_meals(t_epis *epis);
void		ph_with_target_meals(t_epis *epis);
void		ph_open_table(t_epis *epis);
void		ph_speaking(pthread_mutex_t *mutex, int tmp, int id,
				char *message);

		//	init_epis.c	//
void		ph_init_epis(t_sympos *sympos, t_e_agalma *tmp);

		//	init_philos.c	//
void		ph_init_philos(t_sympos *sympos);

		//	init.c			//
void		ph_init_thread(t_sympos *sympos, pthread_t *thread, void *fun,
				void *arg);
void		ph_init_mtx(t_sympos *sympos, pthread_mutex_t mtx);
void		*ph_init_malloc(t_sympos *sympos, int nbr, int var_size);
void		ph_init_fork(t_sympos *sympos, t_philo *philo, t_philo *rg_philo,
				int pos);
t_sympos	*ph_init_sympos(t_e_agalma *tmp);

		//	out.c			//
void		ph_quit_philo(t_sympos *sympos, int fd_out, char *message,
				int error_code);

		//	philos_utils.c	//
void	ph_seat_on_table(t_philo *philo);

		//	threading.c		//
void		ph_threading(t_sympos *sympos);

		//	utils.c			//
void		ph_incr_var(pthread_mutex_t *mutex, int *var);
void		ph_modif_var(pthread_mutex_t *mutex, int *dest, int src);
size_t		ph_actualtime(void);

		//	test_file.c		//
void		ts_print_philos_fork(t_sympos *sympos);
void		ts_print_philos_states(t_epis *epis);
void		ts_print_sympos(t_sympos *sympos);

#endif
