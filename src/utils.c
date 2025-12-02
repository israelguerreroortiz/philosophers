/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iisraa11 <iisraa11@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 16:26:32 by iisraa11          #+#    #+#             */
/*   Updated: 2025/11/19 16:50:29 by iisraa11         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void    exit_error(const char *str)
{
    printf("%s\n", str);
    exit(EXIT_FAILURE);
}

int is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

int ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

void print_action(t_philo *philo, char *action)
{
	if (simulation_finished(philo))
		return;
		
    long long timestamp;

    safe_mutex(&philo->table->print_mutex, LOCK);
    timestamp = get_time_ms() - philo->table->start_time;
    printf("%lld %d %s\n", timestamp, philo->philo_id, action);
    safe_mutex(&philo->table->print_mutex, UNLOCK);
}


long ft_atol(const char *argument)
{
	int i;
	int sign;
	long result;

	i = 0;
	sign = 1;
	result = 0;
	while (argument[i] != '\0' && is_space(argument[i]))
		i++;
	if (argument[i] == '-' || argument[i] == '+')
	{
		if (argument[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (argument[i] != '\0' && ft_isdigit(argument[i]))
	{
		result = result * 10 + (argument[i] - '0');
		i++;
	}
	result *= sign;
	if (result < 0)
		exit_error("Negative numbers are not valid");
	return (result);
}
