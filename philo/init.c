/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elikavak <elikavak@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:35:13 by elikavak          #+#    #+#             */
/*   Updated: 2025/06/10 16:35:13 by elikavak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_number(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (ft_atoi(argv[i]) < 0)
			return (0);
		i++;
	}
	return (1);
}

int	initialize_simulation(int argc, char **argv, t_data *data)
{
	if (check_number(argv))
	{
		data->num_of_philos = ft_atoi(argv[1]);
		data->time_to_die = ft_atoi(argv[2]);
		data->time_to_eat = ft_atoi(argv[3]);
		data->time_to_sleep = ft_atoi(argv[4]);
		if (argc != 5)
			data->num_of_eat = ft_atoi(argv[5]);
		else
			data->num_of_eat = -1;
		data->start_time = present();
		data->dead_flag = 0;
	}
	else
	{
		write(2, "Program can't take negative number\n", 35);
		free(data);
		return (1);
	}
	return (0);
}

void	assign_philosophers(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		data->philos[i].number_of_eat = 0;
		data->philos[i].someone_dead = 0;
		data->philos[i].id = i + 1;
		data->philos[i].data = data;
		data->philos[i].time_to_die = data->time_to_die;
		data->philos[i].last_meal_time = data->start_time;
		data->philos[i].philo_death_time = data->start_time + data->time_to_die;
		i++;
	}
}

void	setup_mutexes(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_init(&data->mutex_text, NULL);
	pthread_mutex_init(&data->mutex_flag, NULL);
	while (i < data->num_of_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
}

void	allocate_and_initialize_forks(t_data *data)
{
	int	f;

	f = 0;
	while (f < data->num_of_philos)
	{
		data->philos[f].left_fork = &data->forks[f];
		data->philos[f].right_fork = &data->forks[(f + 1)
			% (data->num_of_philos)];
		f++;
	}
}
