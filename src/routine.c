/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iisraa11 <iisraa11@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 13:11:32 by iisraa11          #+#    #+#             */
/*   Updated: 2026/02/28 12:42:28 by iisraa11         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void think(t_philo *philo)
{
    print_action(philo, "is thinking");

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
    safe_mutex(&philo->meal_mutex, LOCK);
    philo->meal_time = get_time_ms();
    safe_mutex(&philo->meal_mutex, UNLOCK);

    print_action(philo, "is eating");

    philo->counter_meals++;

    safe_mutex(&philo->meal_mutex, LOCK);
    if (philo->counter_meals == philo->table->required_meals)
        philo->full = true;
    safe_mutex(&philo->meal_mutex, UNLOCK);

    long long start = get_time_ms();
    while (get_time_ms() - start < philo->table->time_to_eat)
    {
        if (simulation_finished(philo))
            return;
        usleep(100);       
    }
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