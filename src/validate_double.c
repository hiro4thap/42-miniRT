/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_double.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:17:59 by hiono             #+#    #+#             */
/*   Updated: 2024/07/21 19:11:23 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

int	validate_double(const char *number)
{
	int		index;

	index = 0;
	while (number[index] == ' ')
		index++;
	if (number[index] == '-')
		index++;
	if (!ft_isdigit(number[index]))
		return (0);
	while (ft_isdigit(number[index]))
		index++;
	if (number[index] == '.')
	{
		index++;
		if (!ft_isdigit(number[index]))
			return (0);
		while (ft_isdigit(number[index]))
			index++;
	}
	if (number[index] != ' ' && number[index] != '\n' && number[index] != '\0')
		return (0);
	return (index);
}

int	validate_udouble(const char *number)
{
	int		index;
	double	value;

	if (!validate_double(number))
		return (0);
	index = read_double(number, &value);
	if (value < 0)
		return (0);
	return (index);
}

int	validate_double_value(const char *number, double min, double max)
{
	int		index;
	double	value;

	if (!validate_double(number))
		return (0);
	index = read_double(number, &value);
	if (value < min || max < value)
		return (0);
	return (index);
}

int	validate_double_info(const char *number)
{
	int		index;

	index = 0;
	if (number[index] == '-')
		index++;
	if (!ft_isdigit(number[index]))
		return (0);
	while (ft_isdigit(number[index]))
		index++;
	if (number[index] == '.')
	{
		index++;
		if (!ft_isdigit(number[index]))
			return (0);
		while (ft_isdigit(number[index]))
			index++;
	}
	if (number[index] != ' ' && number[index] != '\n' && number[index] != '\0'
		&& number[index] != ',')
		return (0);
	return (index);
}

int	validate_double_value_info(const char *number, double min,
		double max)
{
	int		index;
	double	value;

	if (!validate_double_info(number))
		return (0);
	index = read_double(number, &value);
	if (value < min || max < value)
		return (0);
	return (index);
}
