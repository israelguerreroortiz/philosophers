/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isrguerr <isrguerr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 11:37:33 by iisraa11          #+#    #+#             */
/*   Updated: 2025/11/17 13:20:15 by isrguerr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	check_args(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			while (argv[i][j] != '\0' && is_space(argv[i][j]))
				j++;
			if (argv[i][j] == '-')
				exit_error("Negative numbers are not valid");
			else if (argv[i][j] == '+')
				j++;
			if (argv[i][j] == '\0' || !ft_isdigit(argv[i][j]))
				exit_error("The arguments must be digits");
			j++;
		}
		i++;
	}
}

void	parse_args(t_data *table, char **argv)
{
	table->philo_nbr = ft_atol(argv[1]);
	if (table->philo_nbr <= 0)
		exit_error("Number of philosophers must be greater than 0");
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_sleep = ft_atol(argv[3]);
	table->time_to_eat = ft_atol(argv[4]);
	table->required_meals = -1;
	if (table->argc == 6)
		table->required_meals = ft_atol(argv[5]);
}

void	safe_mutex(pthread_mutex_t *mutex, t_mutex_action action)
{
	if (action == INIT)
	{
		if (pthread_mutex_init(mutex, NULL) != 0)
			exit_error("Mutex initialization failed");
	}
	else if (action == LOCK)
	{
		if (pthread_mutex_lock(mutex) != 0)
			exit_error("Mutex lock failed");
	}
	else if (action == UNLOCK)
	{
		if (pthread_mutex_unlock(mutex) != 0)
			exit_error("Mutex unlock failed");
	}
	else if (action == DESTROY)
	{
		if (pthread_mutex_destroy(mutex) != 0)
			exit_error("Mutex destroy failed");
	}
	else
		exit_error("Invalid mutex action");
}

static void	philo_init(t_data *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_nbr)
	{
		table->philos[i].philo_id = i + 1;
		table->philos[i].counter_meals = 0;
		table->philos[i].full = false;
		table->philos[i].right_fork = &table->forks[i];
		table->philos[i].left_fork = &table->forks[(i + 1) % table->philo_nbr];
		table->philos[i].table = table;
	}
}

void	data_init(t_data *table)
{
	int	i;

	table->philos = malloc(sizeof(t_philo) * table->philo_nbr);
	if (!table->philos)
		exit_error("Malloc failed for philosophers");
	table->forks = malloc(sizeof(t_philo) * table->philo_nbr);
	if (!table->forks)
		exit_error("Malloc failed for forks");
	table->dead = 0;
	safe_mutex(&table->print_mutex, INIT);
	safe_mutex(&table->dead_mutex, INIT);
	i = -1;
	while (++i < table->philo_nbr)
	{
		table->forks[i].fork_id = i + 1;
		safe_mutex(&table->forks[i].mutex, INIT);
	}
	philo_init(table);
}
