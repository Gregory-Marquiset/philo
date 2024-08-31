/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 20:07:20 by gmarquis          #+#    #+#             */
/*   Updated: 2024/08/31 19:12:53 by gmarquis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

	//		code help		//
# define CERR_ARGS_H0 1
# define CERR_ARGS_H1 2

	//		code error		//
# define CERR_MALLOC 3
# define CERR_PT_CREAT 4
# define CERR_PT_JOIN 5
# define CERR_MU_INIT 6
# define CERR_GETTIME 7

	//		log utils		//
# define LU_GRAY "\033[1;30m"
# define LU_RED1 "\033[0;31m"
# define LU_RED2 "\033[1;31m"
# define LU_GRE1 "\033[0;32m"
# define LU_GRE2 "\033[1;32m"
# define LU_YEL1 "\033[0;33m"
# define LU_YEL2 "\033[1;33m"
# define LU_BLU1 "\033[0;34m"
# define LU_BLU2 "\033[1;34m"
# define LU_MAJ1 "\033[0;35m"
# define LU_MAJ2 "\033[1;35m"
# define LU_CYA1 "\033[0;36m"
# define LU_CYA2 "\033[1;36m"
# define LU_WHI1 "\033[0;37m"
# define LU_WHI2 "\033[1;37m"

# define LU_END "\033[0m"

	//		log help		//
# define LERR_ARGS_H1 LU_RED2 "Error: " LU_END "Bad argument format!\n" LU_BLU2 "For help run: " LU_END "./philo --help\n"
# define LERR_ARGS_H2 "./program_name number_of_philosophers time_to_die time_to_eat \
time_to_sleep (optional)number_of_times_each_philosopher_must_eat\n"\
LU_BLU2 "For more details run: " LU_END "./philo --help++\n"
# define LERR_ARGS_H3 LU_BLU2 "\nHere some details about the project philo:\n" LU_END \
"the project calls for creating a symposium of philosophers\n\
who eat, think and sleep continuously in the same dish\n\
but with a limited number of obeliskos and must therefore\n\
eat in turns so as not to die of hunger.\n\n" \
LU_BLU2 "For run project philo you need 5 or 6 arguments\n" LU_END \
"1: program_name -> The program name\n\
2: number_of_philosophers -> The number of philosopher you want\n\
3: time_to_die -> Time max between each philosopher meal\n\
4: time_to_eat -> Time needed by a philosopher for eating a meal\n\
5: time_to_sleep -> Time spent sleeping\n\
6: (optional)number_of_times_each_philosopher_must_eat -> Number of meal for each philo,\n\
when reached program stop, ifndef run until 1 philo die\n\n" \
LU_YEL1 "All time values are in milliseconds\n\
All value most be an int between 1 and int max\n\n" LU_END

	//		log error		//
# define LERR_ARGS_H0 LU_RED1 "Error: arguments can only be positive int\n" LU_END
# define LERR_MALLOC LU_RED1 "Error: echec malloc\n" LU_END
# define LERR_PT_CREAT LU_RED1 "Error: echec pthead_creat\n" LU_END
# define LERR_PT_JOIN LU_RED1 "Error: echec pthead_join\n" LU_END
# define LERR_MU_INIT LU_RED1 "Error: echec nutex_init\n" LU_END
# define LERR_GETTIME LU_RED1 "Error: echec gettimeofday\n" LU_END

	//		project log		//
# define LPRO_JSYM LU_GRE1 "join the symposium\n" LU_END
# define LPRO_LSYM LU_GRE1 "left the symposium\n" LU_END
# define LPRO_FORK LU_BLU1 "has taken a fork\n" LU_END
# define LPRO_MEAL LU_GRE1 "all meal as bean eaten\n\n" LU_END
# define LPRO_EAT LU_MAJ1 "is eating\n" LU_END
# define LPRO_SLEEP LU_CYA1 "is sleeping\n" LU_END
# define LPRO_THINK LU_YEL1 "is thinking\n" LU_END
# define LPRO_DIED LU_RED1 "died\n" LU_END

	//		test log		//
# define LTEST_TEST_3D LU_YEL2 "Test:%3d\n" LU_END
# define LTEST_SUCC_IN LU_GRE2 "\nSuccess: Symposium opened!\n\n" LU_END
# define LTEST_SUCC_OUT LU_GRE2 "\nSuccess: Symposium closed!\n\n" LU_END

#endif
