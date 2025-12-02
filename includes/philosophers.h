/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iisraa11 <iisraa11@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 13:07:52 by iisraa11          #+#    #+#             */
/*   Updated: 2025/11/20 13:50:25 by iisraa11         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <unistd.h> // usleep, sleep, write
#include <stdlib.h> // malloc, free
#include <stdbool.h>
#include <pthread.h>  // pthread_*
#include <sys/time.h> // gettimeofday
#include <limits.h>   // INT_MAX
#include <stdio.h>

/*number_of_philosophers time_to_die time_to_eat
time_to_sleep
[number_of_times_each_philosopher_must_eat]*/

enum e_status
{
    THINKING,
    EATING,
    SLEEPING,
    FORK_TAKEN,
    DIED
};

typedef struct s_data t_data;

typedef enum e_mutex_action
{
    INIT,
    LOCK,
    UNLOCK,
    DESTROY
} t_mutex_action;

typedef struct s_fork
{
    int fork_id;
    pthread_mutex_t mutex;
} t_fork;

typedef struct s_philo
{
    int philo_id;
    int counter_meals;
    bool full;
    long long meal_time;
    t_fork *left_fork;
    t_fork *right_fork;
    pthread_t thread_id;
    t_data *table;
    pthread_mutex_t meal_mutex;
} t_philo;

struct s_data
{
    int philo_nbr;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int required_meals;
    int argc;
    long long start_time;
    int dead;
    pthread_mutex_t print_mutex;
    pthread_mutex_t dead_mutex;
    t_philo *philos;
    t_fork *forks;
};

void think(t_philo *philo);
void eat(t_philo *philo);
void philo_sleep(t_philo *philo);
void take_forks(t_philo *philo);
void release_forks(t_philo *philo);

void exit_error(const char *str);
void check_args(char **argv);
void parse_args(t_data *table, char **argv);
void safe_mutex(pthread_mutex_t *mutex, t_mutex_action action);
void *monitor_death(void *arg);
void print_action(t_philo *philo, char *action);
void data_init(t_data *table);
int simulation_finished(t_philo *philo);
long long get_time_ms(void);
void think(t_philo *philo);
void start_dinner(t_data *table);
long ft_atol(const char *argument);
int ft_isdigit(int c);
int is_space(char c);

#endif