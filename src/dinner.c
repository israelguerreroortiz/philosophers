/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iisraa11 <iisraa11@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 13:15:37 by iisraa11          #+#    #+#             */
/*   Updated: 2025/10/23 15:28:38 by iisraa11         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int simulation_finished(t_philo *philo)
{
    int finished;

    pthread_mutex_lock(&philo->table->dead_mutex);
    finished = philo->table->dead;
    pthread_mutex_unlock(&philo->table->dead_mutex);
    return (finished);
}

static void *philosopher_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;

    while (!simulation_finished(philo))
    {
        if (philo->full == true)
            break;
        think(philo);
        take_forks(philo);
        eat(philo);
        release_forks(philo);
        philo_sleep(philo);
    }
    return (NULL);
}

void start_dinner(t_data *table)
{
    int i;
    pthread_t monitor_thread;

    table->start_time = get_time_ms();
    i = -1;
    while (++i < table->philo_nbr)
    {
        table->philos[i].meal_time = table->start_time;
        if (pthread_create(&table->philos[i].thread_id, NULL,
                           &philosopher_routine, &table->philos[i]) != 0)
            exit_error("Thread creation failed");
    }
    pthread_create(&monitor_thread, NULL, monitor_death, (void *)table);
    i = -1;
    while (++i < table->philo_nbr)
        pthread_join(table->philos[i].thread_id, NULL);
    pthread_join(monitor_thread, NULL);
}