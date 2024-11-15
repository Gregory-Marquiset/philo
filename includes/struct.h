/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:41:17 by gmarquis          #+#    #+#             */
/*   Updated: 2024/11/05 20:55:37 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

		//		episkopos		//

typedef struct s_epis
{
	pthread_t		thread_ep;
	pthread_mutex_t	mtx_verif;
	int				*verif;
	pthread_mutex_t	mtx_printf;			//	mute printf
	pthread_mutex_t	mtx_id_dead;		//	mute id_dead
	int				*id_dead;         		//	l'id du philo mort
	pthread_mutex_t	mtx_phs_meals;	//	mute phs_meals
	int				*phs_meals;		        //	indique l'etat des repas des philos
	unsigned long	st_time;
	int				n_meal;
	int				n_philos;
}				t_epis;

		//		philo		//

typedef struct s_agalma
{
	int				n_philos;	//	Number of philosophers and fork from 1 to n
	int				n_meal;		//	n meal for each philo, when reached program stop, if ndef infinit loop until 1 philo die
	unsigned long	st_time;	//  tume to start the routine
	unsigned long	tt_start;	//	(in milliseconds) time spend waiting before starting
	unsigned long	tt_eat;		//	(in milliseconds) time needed by a philosopher for eating a meal
	unsigned long	tt_sleep;	//	(in milliseconds) time spend sleeping
	unsigned long	tt_think;	//	(in milliseconds) time spend waiting before starting
	unsigned long	tt_die;		//	(in milliseconds) time max beatween each philosophermeal
}				t_agalma;

typedef struct s_kinesis
{
	unsigned long	*last_meal;		//	Time of the last meal
	int				*count_meal;	//	Nombre of meals eaten
	pthread_mutex_t *mtx_phs_meals;
	int				*phs_meals;		//	Increment when count_meal == n_meal
	pthread_mutex_t	*mtx_id_dead;
	int				*id_dead;		//	= id philo dead / -1 == all meals eaten
}				t_kinesis;

typedef struct s_philo
{
	int				id;			//	Un id unique par philosophe, utilisé pour les distinguer l'rs de l'affichage ou la gestion des ressources
	pthread_t		thread_ph;	//	Le thread associé à chaque philosophe, permettant de gérer leur exécution simultanée
	t_agalma		*agal;
	t_kinesis		*kine;		//	variable modifiable
	t_epis			*epis;		//	acces direct a l'episkopos
	pthread_mutex_t	*lf_fork;	//	Pointeurs vers les mutexes représentant les baguettes à gauche et à droite du philosophe
	pthread_mutex_t	rg_fork;	//	Ils sont utilisés pour synchroniser l'accès aux baguettes
}				t_philo;

		//		symposium		//

typedef struct s_sympos
{
	t_epis	*epis;
	t_philo	*philos;
}				t_sympos;

#endif
