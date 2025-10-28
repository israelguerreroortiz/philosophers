/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iisraa11 <iisraa11@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 16:17:00 by iisraa11          #+#    #+#             */
/*   Updated: 2025/10/24 13:04:53 by iisraa11         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long get_time_ms(void)
{
    struct timeval tv;
    long long miliseconds;

    gettimeofday(&tv, NULL);
    miliseconds = (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000LL);
    return (miliseconds);
}


static void clean(t_data *table)
{
    int i;

    i = -1;
    while (++i < table->philo_nbr)
        pthread_mutex_destroy(&table->forks[i].mutex);
    pthread_mutex_destroy(&table->print_mutex);
    pthread_mutex_destroy(&table->dead_mutex);
    free(table->philos);
    free(table->forks);
}

int main(int argc, char **argv)
{
    t_data table;
    if (!(argc == 5 || argc == 6))
        exit_error("Required args are number_of_philosophers, time_to_die, time_to_eat"
                   "time_to_sleep and optionally number of times each philosopher must eat");
    table.argc = argc;
    check_args(argv);
    parse_args(&table, argv);
    data_init(&table);
    start_dinner(&table);
    clean(&table);
}