/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iisraa11 <iisraa11@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 13:11:32 by iisraa11          #+#    #+#             */
/*   Updated: 2025/10/23 13:18:46 by iisraa11         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void think(t_philo *philo)
{
    print_action(philo, "is thinking");

    if (philo->table->philo_nbr % 2 == 1)
        usleep(1000);
}

void take_forks(t_philo *philo)
{
    if (philo->philo_id % 2 == 0)
    {
        safe_mutex(&philo->right_fork->mutex, LOCK);
        print_action(philo, "has taken a fork");
        safe_mutex(&philo->left_fork->mutex, LOCK);
        print_action(philo, "has taken a fork");
    }
    else
    {
        safe_mutex(&philo->left_fork->mutex, LOCK);
        print_action(philo, "has taken a fork");
        safe_mutex(&philo->right_fork->mutex, LOCK);
        print_action(philo, "has taken a fork");
    }
}

void eat(t_philo *philo)
{
    pthread_mutex_lock(&philo->table->dead_mutex);
    philo->last_meal_time = get_time_ms();
    pthread_mutex_unlock(&philo->table->dead_mutex);

    print_action(philo, "is eating");

    philo->counter_meals++;

    if (philo->counter_meals == philo->table->required_meals)
        philo->full = true;

    long long start = get_time_ms();
    while (get_time_ms() - start < philo->table->time_to_eat)
        usleep(100);
}

void release_forks(t_philo *philo)
{
    safe_mutex(&philo->left_fork->mutex, UNLOCK);
    safe_mutex(&philo->right_fork->mutex, UNLOCK);
}

void philo_sleep(t_philo *philo)
{
    long start = get_time_ms();

    print_action(philo, "is sleeping");
    while (!simulation_finished(philo) &&
           (get_time_ms() - start) < philo->table->time_to_sleep)
        usleep(100);
}