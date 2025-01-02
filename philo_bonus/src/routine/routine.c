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
        // Petite pause (200 µs, 500 µs, 1000 µs... selon ta préférence)
        usleep(ms / 10);

        now = phb_actualtime();
        // Vérification de la mort
        if ((now - *last_meal_time) > philo->agal->tt_die)
        {
            // “sem_wait” s’il n’est pas déjà pris
            phb_speaking_for_dead(sympos, philo->id);
            exit(philo->id);
        }
        // On sort si le temps écoulé dépasse 'ms'
        if ((now - start) >= ms)
            break;
    }
}

void phb_philo_routine(t_sympos *sympos, t_philo *philo)
{
    unsigned long last_meal_time = phb_actualtime();
    unsigned long now;

    while (1)
    {
        /* --- PRENDRE LES FOURCHETTES --- */
        sem_wait(sympos->sem_forks);
        phb_speaking(sympos, philo->id, LPRO_FORK);
        sem_wait(sympos->sem_forks);
        phb_speaking(sympos, philo->id, LPRO_FORK);

        /* --- MANGER --- */
        phb_speaking(sympos, philo->id, LPRO_EAT);
        last_meal_time = phb_actualtime(); 
        // On “mange” pendant philo->agal->tt_eat ms,
        // en micro-sleep pour check la mort régulièrement
        phb_micro_sleep(sympos, philo, philo->agal->tt_eat, &last_meal_time);

        // Gestion du nombre de repas
        if (philo->agal->n_meal != -1)
        {
            philo->count_meal++;
            if (*philo->count_meal >= philo->agal->n_meal)
            {
                // Libérer les fourchettes
                sem_post(sympos->sem_forks);
                sem_post(sympos->sem_forks);
                exit(0);
            }
        }

        // RENDRE LES FOURCHETTES
        sem_post(sympos->sem_forks);
        sem_post(sympos->sem_forks);

        /* --- DORMIR --- */
        phb_speaking(sympos, philo->id, LPRO_SLEEP);
        // Ici, on ne remplace pas last_meal_time, car ce n’est pas un repas
        // On passe quand même &last_meal_time, car on veut continuer à checker
        // la mort par rapport à son dernier repas.
        phb_micro_sleep(sympos, philo, philo->agal->tt_sleep, &last_meal_time);

        /* --- PENSER --- */
        phb_speaking(sympos, philo->id, LPRO_THINK);

        // (éventuellement un petit temps de réflexion, ex: 100 ms)
        // Cf. “tt_think” si tu l’utilises :
        if (philo->agal->tt_think > 0)
            phb_micro_sleep(sympos, philo, philo->agal->tt_think, &last_meal_time);

        /* --- CHECK MORT (optionnel, déjà fait dans micro_sleep) --- */
        now = phb_actualtime();
        if ((now - last_meal_time) > philo->agal->tt_die)
        {
            phb_speaking_for_dead(sympos, philo->id);
            exit(philo->id);
        }
    }
}
