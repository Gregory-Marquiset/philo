/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 20:07:20 by gmarquis          #+#    #+#             */
/*   Updated: 2024/08/29 23:49:31 by gmarquis         ###   ########.fr       */
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
# define LU_RED "\033[1;31m"
# define LU_BLU "\033[1;34m"
# define LU_GRE "\033[1;32m"
# define LU_YEL "\033[1;33m"
# define LU_END "\033[0m"

	//		log help		//
# define LERR_ARGS_H1 LU_RED "Error: " LU_END "Bad argument format!\n" LU_BLU "For help run: " LU_END "./philo --help\n"
# define LERR_ARGS_H2 "./program_name number_of_philosophers time_to_die time_to_eat \
time_to_sleep (optional)number_of_times_each_philosopher_must_eat\n"\
LU_BLU "For more details run: " LU_END "./philo --help++\n"
# define LERR_ARGS_H3 LU_BLU "\nHere some details about the project philo:\n" LU_END \
"the project calls for creating a symposium of philosophers\n\
who eat, think and sleep continuously in the same dish\n\
but with a limited number of obeliskos and must therefore\n\
eat in turns so as not to die of hunger.\n\n" \
LU_BLU "For run project philo you need 5 or 6 arguments\n" LU_END \
"1: program_name -> The program name\n\
2: number_of_philosophers -> The number of philosopher you want\n\
3: time_to_die -> Time max between each philosopher meal\n\
4: time_to_eat -> Time needed by a philosopher for eating a meal\n\
5: time_to_sleep -> Time spent sleeping\n\
6: (optional)number_of_times_each_philosopher_must_eat -> Number of meal for each philo,\n\
when reached program stop, ifndef run until 1 philo die\n\n" \
LU_YEL "All time values are in milliseconds\n\
All value most be an int between 1 and int max\n\n" LU_END

	//		log error		//
# define LERR_ARGS_H0 LU_RED "Error: arguments can only be positive int\n" LU_END
# define LERR_MALLOC LU_RED "Error: echec malloc\n" LU_END
# define LERR_PT_CREAT LU_RED "Error: echec pthead_creat\n" LU_END
# define LERR_PT_JOIN LU_RED "Error: echec pthead_join\n" LU_END
# define LERR_MU_INIT LU_RED "Error: echec nutex_init\n" LU_END
# define LERR_GETTIME LU_RED "Error: echec gettimeofday\n" LU_END

	//		project log		//
# define PLOG_FORK "has taken a fork\n"
# define PLOG_EAT "is eating\n"
# define PLOG_SLEEP "is sleeping\n"
# define PLOG_THINK "is thinking\n"
# define PLOG_DIED "died\n"

	//		test log		//
# define LTEST_TEST_3D LU_YEL "Test:%3d\n" LU_END
# define LTEST_SUCC_IN LU_GRE "Success: Symposium opened!\n" LU_END
# define LTEST_SUCC_OUT LU_GRE "Success: Symposium closed!\n" LU_END

#endif
