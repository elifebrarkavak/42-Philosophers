/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elikavak <elikavak@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:35:00 by elikavak          #+#    #+#             */
/*   Updated: 2025/06/10 16:35:00 by elikavak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	setup_all(t_data *data, char **argv, int argc)
{
	if (initialize_simulation(argc, argv, data))
		return (1);
	data->philos = malloc(data->num_of_philos * sizeof(t_philo));
	data->forks = malloc(data->num_of_philos * sizeof(pthread_mutex_t));
	assign_philosophers(data);
	setup_mutexes(data);
	allocate_and_initialize_forks(data);
	return (0);
}

static void	ft_cleanup(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->mutex_flag);
	pthread_mutex_destroy(&data->mutex_text);
	free(data->forks);
	free(data->philos);
	free(data);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	int		i;

	i = 1;
	if (argc != 5 && argc != 6)
	{
		write(2, "Invalid argument count!\n", 25);
		return (1);
	}
	while (i < argc)
	{
		if (ft_isdigit(argv[i]))
		{
			write(2, "Non-numerical arguments!\n", 25);
			return (1);
		}
		i++;
	}
	data = malloc(sizeof(t_data));
	if (setup_all(data, argv, argc))
		return (1);
	ft_run_philos(data);
	ft_cleanup(data);
	return (0);
}
