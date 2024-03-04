/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjochum <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 10:56:40 by mjochum           #+#    #+#             */
/*   Updated: 2023/10/19 15:38:32 by mjochum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_philo	*ft_init_philo(int i, t_vars *vars)
{
	t_philo	*philo;

	philo = ft_calloc(1, sizeof (t_philo));
	philo->id = i;
	philo->isalive = 1;
	philo->nextdeath = vars->msdie;
	philo->starttime = vars->starttime;
	philo->noneat = vars->noneat;
	philo->neat = vars->neat;
	philo->mssleep = vars->mssleep;
	philo->mseat = vars->mseat;
	philo->msdie = vars->msdie;
	philo->nphilos = vars->nphilos;
	philo->vars = vars;
	if (i == 0)
		philo->left = vars->nphilos - 1;
	else
		philo->left = i - 1;
	return (philo);
}

static void	ft_init_table(t_vars *vars)
{
	size_t	i;

	i = -1;
	while (++i < vars->nphilos)
		vars->philo[i] = ft_init_philo(i, vars);
	i = -1;
	while (++i < vars->nphilos)
	{
		vars->fork[i] = ft_calloc(1, sizeof (t_fork));
		vars->fork[i]->fork = 1;
		pthread_mutex_init(&vars->fork[i]->mutex, NULL);
	}
}

// ft_init
// vars
static t_vars	*ft_init(int ac, char *av[])
{
	t_vars	*vars;

	vars = ft_calloc(1, sizeof (t_vars));
	vars->nphilos = ft_atoi(av[1]);
	vars->msdie = ft_atoi(av[2]);
	vars->mseat = ft_atoi(av[3]);
	vars->mssleep = ft_atoi(av[4]);
	if (ac == 6)
		vars->neat = ft_atoi(av[5]);
	else
		vars->noneat = 1;
	vars->run = vars->nphilos;
	vars->fork = ft_calloc(vars->nphilos, sizeof (t_fork *));
	vars->philo = ft_calloc(vars->nphilos, sizeof (t_philo *));
	pthread_mutex_init(&vars->printf_m, NULL);
	pthread_mutex_init(&vars->time_m, NULL);
	pthread_mutex_init(&vars->death_m, NULL);
	pthread_mutex_init(&vars->run_m, NULL);
	ft_init_table(vars);
	return (vars);
}

static int	ft_datacheck(char *av[])
{
	if (ft_atoi(av[1]) <= 0 || ft_atoi(av[2]) < 0 \
		|| ft_atoi(av[3]) < 0 || ft_atoi(av[4]) < 0)
		return (1);
	if (av[5] && ft_atoi(av[5]) < 0)
		return (1);
	return (0);
}

int	main(int ac, char *av[])
{
	t_vars	*vars;
	size_t	i;

	if (ac != 5 && ac != 6)
		return (printf(ERR, av[0]));
	if (ft_datacheck(av) == 1)
		exit(EXIT_FAILURE);
	vars = ft_init(ac, av);
	i = -1;
	vars->starttime = ft_currenttime(vars);
	while (++i < vars->nphilos)
		pthread_create(&vars->philo[i]->pthread, NULL, \
		ft_philosopher, vars->philo[i]);
	while (ft_run(vars) > 0)
		usleep(1000);
	ft_exit(EXIT_SUCCESS, vars);
	exit(69);
}
