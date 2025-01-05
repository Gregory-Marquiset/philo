#include "../includes/proto.h"

/*
   phb_micro_sleep:
   - Permet de "dormir" au sens du projet pendant `ms` millisecondes.
   - Mais on va découper ce temps en tranches plus petites (par exemple 200 µs, 500 µs...)
   - À chaque petite tranche, on vérifie si (now - last_meal) > time_to_die.
   - Si oui, le philosophe meurt immédiatement.
*/
void phb_micro_sleep(t_sympos *sympos, t_philo *philo,
                     unsigned long ms, unsigned long *last_meal_time)
{
    unsigned long start;
    unsigned long now;

    start = phb_actualtime();
    while (1)
    {
        usleep(ms / 10);

        now = phb_actualtime();
        if ((now - *last_meal_time) > philo->agal->tt_die)
        {
            phb_speaking_for_dead(sympos, philo->id);
            exit(philo->id);
        }
        if ((now - start) >= ms)
            break ;
    }
}

void phb_philo_routine(t_sympos *sympos, t_philo *philo)
{
    unsigned long last_meal_time = phb_actualtime();
    unsigned long now;

    //usleep(1);
    if (sympos->n_philos == 1)
    {
        sem_wait(sympos->sem_forks);
        phb_speaking(sympos, philo->id, LPRO_FORK);
        phb_waiting(philo->agal->tt_die);
        sem_post(sympos->sem_forks);
        phb_speaking_for_dead(sympos, philo->id);
        exit(philo->id);
    }
    phb_waiting(philo->agal->tt_start);
    //printf("%d: %d/%d\n", philo->id, *philo->count_meal, philo->agal->n_meal);
    while (1)
    {
        sem_wait(sympos->sem_forks);
        phb_speaking(sympos, philo->id, LPRO_FORK);
        sem_wait(sympos->sem_forks);
        phb_speaking(sympos, philo->id, LPRO_FORK);

        phb_speaking(sympos, philo->id, LPRO_EAT);
        last_meal_time = phb_actualtime();
        phb_micro_sleep(sympos, philo, philo->agal->tt_eat, &last_meal_time);

        sem_post(sympos->sem_forks);
        sem_post(sympos->sem_forks);

        if (philo->agal->n_meal != -1)
        {
            philo->count_meal++;
            if (philo->count_meal == philo->agal->n_meal)
                exit(0);
        }


        phb_speaking(sympos, philo->id, LPRO_SLEEP);
        phb_micro_sleep(sympos, philo, philo->agal->tt_sleep, &last_meal_time);

        phb_speaking(sympos, philo->id, LPRO_THINK);

        if (philo->agal->tt_think > 0)
            phb_micro_sleep(sympos, philo, philo->agal->tt_think, &last_meal_time);

        now = phb_actualtime();
        if ((now - last_meal_time) > philo->agal->tt_die)
        {
            phb_speaking_for_dead(sympos, philo->id);
            exit(philo->id);
        }
    }
}
