/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proto.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 14:16:57 by gmarquis          #+#    #+#             */
/*   Updated: 2024/09/25 14:36:22 by gmarquis         ###   ########.fr       */
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
void		ph_waiting(size_t time);

		//	args_verif.c	//
t_sympos	*ph_args_verif_and_make_sympos(int argc, char **argv);

		//	epis_utils.c	//
void		ph_open_table(t_epis *epis);
void		ph_seat_on_table(t_philo *philo);
void		ph_speaking(pthread_mutex_t *mutex, int time, int id, char *message);

		//	init.c			//
t_sympos	*ph_init_sympos(t_e_agalma *tmp);

		//	out.c			//
void		ph_quit_philo(t_sympos *sympos, int fd_out, char *message,
	int error_code);

		//	threading.c		//
void		ph_threading(t_sympos *sympos);

		//	utils.c			//
size_t		ph_actualtime(void);

		//	test_file.c		//
void		ph_print_sympos(t_sympos *sympos);

#endif
