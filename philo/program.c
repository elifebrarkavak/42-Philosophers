/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elikavak <elikavak@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:35:41 by elikavak          #+#    #+#             */
/*   Updated: 2025/06/10 16:35:41 by elikavak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*one_philo(void *data)
{
	t_data	*p_data;

	p_data = (t_data *)data;
	pthread_mutex_lock(&p_data->forks[0]);
	printf("%lld %d has taken a fork\n",
		present() - p_data->start_time, p_data->philos[0].id);
	while (!p_data->philos[0].someone_dead)
	{
		if (p_data->philos[0].philo_death_time <= present()
			&& !p_data->dead_flag)
		{
			p_data->philos[0].someone_dead = 1;
			p_data->dead_flag = 1;
			printf("%lld  %d is died\n",
				present() - p_data->start_time, p_data->philos[0].id);
			break ;
		}
		usleep(50);
	}
	pthread_mutex_unlock(&p_data->forks[0]);
	return (0);
}

void	ft_run_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		if (pthread_create(&data->philos[i].p_thread, NULL, \
					life_process, &data->philos[i]))
		{
			write(2, "threads are not created succesfully.\n", 37);
			return ;
		}
		i++;
	}
	i = 0;
	while (i < data->num_of_philos)
	{
		pthread_join(data->philos[i].p_thread, NULL);
		i++;
	}
}
