// pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// void    *func1(void *arg)
// {
//     int i;

//     i = 0;
//     pthread_mutex_lock(&mutex);
//     while (i < 100)
//     {
//         printf("%s\n", (char*)arg);
//         i++;
//     }
//     // printf("\n");
//     pthread_mutex_unlock(&mutex);
//     pthread_exit(arg);
// }

// void    *func2(void *arg)
// {
//     int i;

//     i = 0;
//     pthread_mutex_lock(&mutex);
//     while (i < 100)
//     {
//         printf("%s\n", (char *)arg);
//         i++;
//     }
//     printf("\n");
//     pthread_mutex_unlock(&mutex);
//     pthread_exit(arg);
// }

// int main(void)
// {
//     pthread_t t1;
//     pthread_t t2;
//     char      *s1;
//     char      *s2;

//     pthread_create(&t1, NULL, func1, "yassine");
//     pthread_create(&t2, NULL, func2, "hebbat");
//     pthread_join(t1,(void **)&s1);
//     pthread_join(t2,(void **)&s2);
//     printf("%s-------------%s\n", s1, s2);
// }

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

// pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
// typedef	struct              s_p
// {
//     pthread_mutex_t         mutex;
//     int                     i;
// }                           t_p;

// // int ft_strlen(char *str)
// // {
// //     int i = 0;
// //     while (str[i])
// //         i++;
// //     return (i);
// // }

// void    *go1(void *pp)
// {
//     char *str;
//     int i = 0;
//     t_p *ppp;

//     ppp = (t_p *)pp;
//     str = "tread 1 : coucou ca va ? \n";
//     pthread_mutex_lock(&ppp->mutex); // si on enleve ici
//     while (str[i])
//     {
//         write(1, &str[i], 1);
//         i++;
//     }
//     pthread_mutex_unlock(&ppp->mutex); // si on enleve ici
//     return (NULL);
// }
int nb = 0;
pthread_mutex_t lock;

void *routine(void *param)
{
    
    int i;

    // printf("hello\n");
    // i = -1;
    // pthread_mutex_lock(&lock);
    // while (++i < 10000)
    //     nb++;
    // pthread_mutex_unlock(&lock);
    // return (NULL);
    while (1)
    {
        //fork
        //eat
        last_meal = current_time();
        //sleep
        //think
    }
    return (NULL);
}

unsigned long long current_time()
{
    struct timeval current;

    gettimeofday(&current, NULL);
    return ((current.tv_sec * 1000) + (current.tv_usec / 1000));
}

void sleepu(unsigned long long end)
{
    // unsigned long long end;

    // end = current_time() + time;
    while (current_time() < end)
        usleep(10);
}
void stop_simulation(t_philo *philo)
{
    int i;

    while (done < nb_philos)
    {
        i = -1;
        while (++i < nb_philos)
        {
            if (!philo[i]->is_eating && (current_time() - philo[i]->last_meal) > time_to_die)
            {
                //lock _write
                //printf id die
                // return 
            }
        }
        // lock_write
        //return
    }
}

int main()
{
    // struct timeval current;

    // gettimeofday(&current, NULL);
    // current.tv_sec;
    // current.tv_usec;
    // unsigned long long now;
    // now = (current.tv_sec * 1000) + (current.tv_usec / 1000);
    // printf("[%llu]\n", now);
    // unsigned long long start;
    // unsigned long long end;

    // (philo->id % 2)

    // start = current_time();
    // usleep(800 * 1000 - 10000);
    // sleepu(start + 800 + 5);
    // end = current_time();
    // printf("%llu\n", end - start);
    // // gettimeofday(&current, NULL);
    // // now = (current.tv_sec * 1000) + (current.tv_usec / 1000) - now;
    // // printf("[%llu]\n", now);
    // return (0);
    t_philo *philo;
    // pthread_t *thread = malloc(sizeof(pthread_t) );
    int i = -1;
    // pthread_mutex_init(&lock, NULL);
    while (++i < nb_philos)
    {
        if (pthread_create(&philo[i]->id, NULL, routine, NULL))
            printf("error\n");
    }
    // while (1)
    stop_simulation(philo);
    // sleep(1);
    // printf("done %d\n", nb);
    return (0);
}
