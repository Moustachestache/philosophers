/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjochum <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:02:02 by mjochum           #+#    #+#             */
/*   Updated: 2023/10/14 19:24:13 by mjochum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*r;
	size_t	i;
	size_t	tmp;

	tmp = nmemb * size;
	i = 0;
	if (nmemb == 0 || size == 0)
		return (malloc(0));
	else if (tmp / size != nmemb)
		return (0);
	r = (char *)malloc(nmemb * size);
	if (!r)
		return (NULL);
	while (i < nmemb * size)
	{
		r[i] = '\0';
		i++;
	}
	return ((void *)r);
}

int	ft_atoi(const char *nptr)
{
	int	r;
	int	s;
	int	i;

	r = 0;
	s = 1;
	i = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			s *= -1;
		i++;
	}
	while (nptr[i] && (nptr[i] >= '0' && nptr[i] <= '9'))
	{
		r = (r * 10) + (nptr[i] - 48);
		i++;
	}
	return (r * s);
}

void	ft_mrintf(const char *str, t_philo *philo)
{
	pthread_mutex_lock(&philo->vars->printf_m);
	if (ft_run(philo->vars) > 0)
	{
		printf(MSG, ft_elapsedtime(philo), philo->id + 1, str);
		usleep(10);
	}
	pthread_mutex_unlock(&philo->vars->printf_m);
}

/*  struct timeval current_time;
  gettimeofday(&current_time, NULL);
  printf("seconds : %ld\nmicro seconds : %ld",
    current_time.tv_sec, current_time.tv_usec);*/
size_t	ft_currenttime(t_vars *vars)
{
	size_t	time;

	gettimeofday(&vars->dingdong, NULL);
	time = vars->dingdong.tv_sec * 1000;
	time += vars->dingdong.tv_usec / 1000;
	return (time);
}

size_t	ft_elapsedtime(t_philo *philo)
{
	size_t	time;

	pthread_mutex_lock(&philo->vars->time_m);
	time = ft_currenttime(philo->vars) - philo->vars->starttime;
	pthread_mutex_unlock(&philo->vars->time_m);
	return (time);
}
