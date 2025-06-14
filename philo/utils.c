/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elikavak <elikavak@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:35:49 by elikavak          #+#    #+#             */
/*   Updated: 2025/06/10 16:35:49 by elikavak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	present(void)
{
	struct timeval	tval;

	gettimeofday(&tval, NULL);
	return ((((long long)tval.tv_sec) * 1000) + (tval.tv_usec / 1000));
}

int	ft_isdigit(char *str)
{
	int	i;

	if (str == NULL || str[0] == 0)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '-' || str[i] == '+')
			i++;
		if (!((str[i] <= 57 && str[i] >= 48)) && str[i])
			return (1);
		i++;
	}
	return (0);
}

long	ft_atoi(char *str)
{
	int		i;
	long	sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	if (!str[i])
		return (0);
	while (((str[i] >= 9 && str[i] <= 13) || str[i] == 32) && str[i])
		i++;
	if (str[i] == '-')
	{
		i++;
		sign = -1;
	}
	while ((str[i] >= '0' && str[i] <= '9') && str[i])
	{
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	return (sign * result);
}

void	print_text(t_philo *phil, long long time, int num, char *str)
{
	pthread_mutex_lock(&phil->data->mutex_text);
	pthread_mutex_lock(&phil->data->mutex_flag);
	phil->someone_dead = phil->data->dead_flag;
	pthread_mutex_unlock(&phil->data->mutex_flag);
	if (!phil->someone_dead)
		printf("%lld %d %s", (time - phil->data->start_time), \
				num, str);
	pthread_mutex_unlock(&phil->data->mutex_text);
	usleep(1);
}
