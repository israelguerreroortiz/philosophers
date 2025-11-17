/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrguerr <isrguerr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 11:13:23 by iisraa11          #+#    #+#             */
/*   Updated: 2025/11/17 16:40:56 by isrguerr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	monitor_full(t_data *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		if (table->philos[i].full == false)
			return (0);
		i++;
	}
	safe_mutex(&table->dead_mutex, LOCK);
	table->dead = 1;
	safe_mutex(&table->dead_mutex, UNLOCK);
	return (1);
}

int	check_dead(t_data *table)
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

static int	time_since_last_meal(t_data *table, t_philo *philo)
{
	long long	now;
	long long	time_since_last_meal;

	now = get_time_ms();
	time_since_last_meal = now - philo->meal_time;
	if (time_since_last_meal > table->time_to_die)
	{
		safe_mutex(&table->dead_mutex, LOCK);
		table->dead = 1;
		safe_mutex(&table->dead_mutex, UNLOCK);
		safe_mutex(&table->print_mutex, LOCK);
		printf("%lld %d died\n", now - table->start_time, philo->philo_id);
		safe_mutex(&table->print_mutex, UNLOCK);
		return (1);
	}
	if (check_dead(table))
		return (1);
	return (0);
}

void	*monitor_death(void *arg)
{
	t_data	*table;
	int		i;

	table = (t_data *)arg;
	while (1)
	{
		if (table->required_meals != -1 && monitor_full(table))
			return (NULL);
		i = -1;
		while (++i < table->philo_nbr)
		{
			if (table->philos[i].full == true)
				continue ;
			else if (time_since_last_meal(table, &table->philos[i]))
				return (NULL);
		}
		usleep(500);
	}
    
	return (NULL);
}
