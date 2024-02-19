#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#define TRUE 1
#define FALSE 0

#define SUCCESS 0
#define FAIL -1
#define ERROR 1

typedef struct s_arg
{
    int num_of_philo;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int must_eat_cnt;
} t_arg;

typedef struct s_info
{
    int left;
    int right;
    int eat_cnt;
    int start_time;
    int last_eat_time;
} t_info;

typedef struct s_mutex
{
    pthread_mutex_t *fork;
    pthread_mutex_t *last_eat_time_mutex;
    pthread_mutex_t dead_mutex;
    int dead;
} t_mutex;

typedef struct s_philo
{
    int id;
    t_arg *arg;
    t_info info;
    t_mutex *mutex;
} t_philo;

void *dining(void *arg);

int get_time();

t_arg init_argument(int argc, char **argv);
t_mutex init_mutex(t_arg *arg);
t_philo *init_philo(t_arg *arg, t_mutex *mutex);
int err(t_mutex *mutex, t_philo *philo);
int philo_thread_create(t_philo *philo);

/*ft_atoi*/
int ft_atoi(const char *str);

int print_act(t_philo *philo, char *str);
void a_few_moments_later(int end_time);

void monitor(t_philo *philo);

#endif