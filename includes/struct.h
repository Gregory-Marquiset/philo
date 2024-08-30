/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:41:17 by gmarquis          #+#    #+#             */
/*   Updated: 2024/08/30 17:50:00 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

	//	Lexique		//

/*
	Droite		: δεξιός	(dexiós)

	Gauche		: ἀριστερός	(aristerós)

	Veilleur	: ἐπίσκοπος	(epískopos)
		qui signifie littéralement "celui qui veille sur"

	Fourchette	: ὀβελίσκος (obeliskos)
		brochette en métal, utilisée pour cuisiner la viande et manger
*/

typedef enum s_state
{
	WAITING,
	THINK,
	EAT,
	SLEEP,
	DEAD,
}			t_state;

typedef struct s_epís
{
	int				n_philos;		//	Number of philosophers and fork from 1 to n
	size_t			time_to_die;	//	(in milliseconds) time max beatween each philosophermeal
	size_t			time_to_eat;	//	(in milliseconds) time needed by a philosopher for eating a meal
	size_t			time_to_sleep;	//	(in milliseconds) time spend sleeping
	int				n_meal;			//	n meal for each philo, when reached program stop, if ndef infinit loop until 1 philo die

	pthread_mutex_t	mprintf;		//	pour mute printf
	int				*id_dead;		//	l'id du philo mort
	int				*meal_stat;		//	tableau de buleen de n_philos qui sera placer a 1 si le philo a attein n_meal, si il sont tous a 1 le programme s'arrete
}				t_epís;

typedef struct s_philo
{
	int				id;				//	Un id unique par philosophe, utilisé pour les distinguer l'rs de l'affichage ou la gestion des ressources
	pthread_t		thread;			//	Le thread associé à chaque philosophe, permettant de gérer leur exécution simultanée
	pthread_mutex_t	aris_obeli;		//	Pointeurs vers les mutexes représentant les baguettes à gauche et à droite du philosophe
	pthread_mutex_t	*dexi_obeli;	//	Ils sont utilisés pour synchroniser l'accès aux baguettes
	time_t			last_meal;		//	Le moment où le philosophe a mangé pour la dernière fois, utilisé pour vérifier s'il a faim ou implémenter des règles supplémentaires (comme la gestion de la famine)
	int				count_meal;		//	Nombre de repas pris, utilisé pour limiter le nombre de fois qu'un philosophe mange ou pour collecter des statistiques
	t_state			state;			//	Indique l'état actuel du philosophe (penser, manger, dormir), utile pour le débogage et affichages précis
	t_epís			*epís;
}				t_philo;

typedef struct s_sympos
{
	t_epís	*epís;
	t_philo	*philos;
}				t_sympos;

#endif
