/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iisraa11 <iisraa11@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 11:13:23 by iisraa11          #+#    #+#             */
/*   Updated: 2026/02/28 12:42:28 by iisraa11         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int monitor_full(t_data *table)
{
    int i;

    i = 0;
    while (i < table->philo_nbr)
    {
        safe_mutex(&table->philos[i].meal_mutex, LOCK);
        if (table->philos[i].full == false)
        {
            safe_mutex(&table->philos[i].meal_mutex, UNLOCK);
            return (0);
        }
        safe_mutex(&table->philos[i].meal_mutex, UNLOCK);
        i++;
    }

    safe_mutex(&table->dead_mutex, LOCK);
    table->dead = 1;
    safe_mutex(&table->dead_mutex, UNLOCK);
    return (1);
}

static int check_dead(t_data *table)
{
    safe_mutex(&table->dead_mutex, LOCK);
    if (table->dead == 1)
    {
        safe_mutex(&table->dead_mutex, UNLOCK);
        return (1);
    }
    safe_mutex(&table->dead_mutex, UNLOCK);
    return (0);
}

static int time_since_last_meal(t_data *table, t_philo *philo)
{
    long long now;
    long long time_since_last_meal;

    now = get_time_ms();
    safe_mutex(&philo->meal_mutex, LOCK);
    time_since_last_meal = now - philo->meal_time;
    safe_mutex(&philo->meal_mutex, UNLOCK);
    if (time_since_last_meal > table->time_to_die)
    {
        safe_mutex(&table->dead_mutex, LOCK);
        table->dead = 1;
        safe_mutex(&table->dead_mutex, UNLOCK);

        safe_mutex(&table->print_mutex, LOCK);
        printf("%lld %d died\n",
               now - table->start_time,
               philo->philo_id);
        safe_mutex(&table->print_mutex, UNLOCK);
        return (1);
    }
    if (check_dead(table))
        return (1);
    return (0);
}

void *monitor_death(void *arg)
{
    t_data *table;
    int i;
    
    table = (t_data *)arg;

    while (1)
    {
        if (table->required_meals != -1 && monitor_full(table))
            return (NULL);
        i = -1;
        while (++i < table->philo_nbr)
        {
            safe_mutex(&table->philos[i].meal_mutex, LOCK);
            if (table->philos[i].full == false)
            {
                safe_mutex(&table->philos[i].meal_mutex, UNLOCK);
                if (time_since_last_meal(table, &table->philos[i]))
                    return (NULL);
            }
            else
                safe_mutex(&table->philos[i].meal_mutex, UNLOCK);
        }
        usleep(500);
    }
    return (NULL);
}
