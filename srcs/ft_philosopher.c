/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philosopher.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjochum <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 13:32:58 by mjochum           #+#    #+#             */
/*   Updated: 2023/10/18 15:07:26 by mjochum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

//	relevant links
//	https://stackoverflow.com/questions/62001623/why-does-hel
//grind-show-lock-order-violated-error-message
//	https://docs.oracle.com/cd/E19205-01/820-0619/geojs/index.html
static int	ft_die(t_philo *philo)
{
	if (ft_elapsedtime(philo) - philo->lasteat > philo->msdie)
	{
		ft_mrintf(MSGD, philo);
		pthread_mutex_lock(&philo->vars->run_m);
		philo->vars->run = 0;
		pthread_mutex_unlock(&philo->vars->run_m);
		philo->isalive = 0;
		return (1);
	}
	return (0);
}

static int	ft_think(t_philo *philo)
{
	t_fork	*left;
	t_fork	*right;

	if (philo->nphilos == 1)
		return (0);
	left = philo->vars->fork[philo->left];
	right = philo->vars->fork[philo->id];
	ft_mutex_fourchette(philo, 1);
	if (left->fork == 1 && right->fork == 1 \
		&& right->lastid != philo->id && left->lastid != philo->id)
	{
		left->fork--;
		right->fork--;
		philo->lfork = 1;
		philo->rfork = 1;
		left->lastid = philo->id;
		right->lastid = philo->id;
		ft_mrintf(MSGF, philo);
		ft_mutex_fourchette(philo, 2);
		return (1);
	}
	ft_mutex_fourchette(philo, 2);
	return (0);
}

static int	ft_eat(t_philo *philo)
{
	t_fork		*left;
	t_fork		*right;

	left = philo->vars->fork[philo->left];
	right = philo->vars->fork[philo->id];
	if (ft_die(philo) == 1)
		return (1);
	ft_mrintf(MSGE, philo);
	philo->lasteat = ft_elapsedtime(philo);
	philo->nextdeath = philo->lasteat + philo->msdie;
	usleep(philo->vars->mseat * 1000);
	if (ft_die(philo) == 1)
		return (1);
	ft_mutex_fourchette(philo, 1);
	left->fork = 1;
	right->fork = 1;
	philo->lfork = 0;
	philo->rfork = 0;
	ft_mutex_fourchette(philo, 2);
	return (0);
}

int	ft_nmeals(t_philo *philo)
{
	if (philo->noneat == 1)
		return (1);
	else if (philo->nmeals >= philo->neat && philo->noneat == 0)
	{
		return (0);
	}
	return (1);
}

void	*ft_philosopher(void *arg)
{
	t_philo	*philo;
	t_vars	*vars;

	philo = arg;
	vars = philo->vars;
	if (philo->id % 2 == 0)
		usleep(10);
	while (ft_run(philo->vars) > 0 && philo->isalive == 1 && ft_die(philo) == 0)
	{
		if (ft_nmeals(philo) == 0)
			break ;
		ft_mrintf(MSGT, philo);
		while (ft_think(philo) == 0 && ft_die(philo) == 0)
			usleep(philo->msdie);
		if (ft_die(philo) == 1)
			break ;
		if (ft_eat(philo) == 1)
			break ;
		philo->nmeals++;
		ft_mrintf(MSGS, philo);
		usleep(philo->mssleep * 1000);
	}
	pthread_mutex_lock(&philo->vars->run_m);
	philo->vars->run -= 1;
	pthread_mutex_unlock(&philo->vars->run_m);
	return (arg);
}
