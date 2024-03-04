/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fourchettes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjochum <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:38:00 by mjochum           #+#    #+#             */
/*   Updated: 2023/10/15 12:08:02 by mjochum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

//	a haiku:
//	too many lines
//	function displaced
//	weird file
int	ft_run(t_vars *vars)
{
	int	state;

	state = 0;
	pthread_mutex_lock(&vars->run_m);
	if (vars->run)
		state = vars->run;
	pthread_mutex_unlock(&vars->run_m);
	return (state);
}

//	lock
static void	ft_mourchette_1(t_philo *philo, \
			pthread_mutex_t *left, pthread_mutex_t *right)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(right);
		pthread_mutex_lock(left);
	}
	else
	{
		pthread_mutex_lock(left);
		pthread_mutex_lock(right);
	}
}

//	unlock
static void	ft_mourchette_2(t_philo *philo, \
			pthread_mutex_t *left, pthread_mutex_t *right)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(right);
		pthread_mutex_unlock(left);
	}
	else
	{
		pthread_mutex_unlock(left);
		pthread_mutex_unlock(right);
	}
}

// if 1
//	lock mutex
// if 2
//	release mutex
void	ft_mutex_fourchette(t_philo *philo, int status)
{
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;

	left = &philo->vars->fork[philo->left]->mutex;
	right = &philo->vars->fork[philo->id]->mutex;
	if (status == 1)
		ft_mourchette_1(philo, left, right);
	else if (status == 2)
		ft_mourchette_2(philo, left, right);
}
