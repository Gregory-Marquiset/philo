/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proto.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 14:16:57 by gmarquis          #+#    #+#             */
/*   Updated: 2024/08/31 18:37:48 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTO_H
# define PROTO_H

# include "struct.h"
# include "define.h"

		//	act.c			//
void		ft_eating(t_philo *tmp);
void		ft_sleeping(t_philo *tmp);

		//	args_verif.c	//
t_sympos	*ft_args_verif_and_make_sympos(int argc, char **argv);

		//	init.c			//
t_sympos	*ft_init_sympos(t_epís *tmp);

		//	out.c			//
void		ft_quit_philo(t_sympos *sympos, int fd_out, char *message,
	int error_code);

		//	threading.c		//
void		ft_threading(t_sympos *sympos);

		//	utils.c			//
size_t		ft_actualtime(void);
void		ft_speaking(pthread_mutex_t *mutex, int time, int id, char *message);

		//	test_file.c		//
void		ft_print_sympos(t_sympos *sympos);

#endif
