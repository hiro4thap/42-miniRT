/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_information.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:40:17 by hiono             #+#    #+#             */
/*   Updated: 2024/07/17 16:06:05 by hiono            ###   ########.fr       */
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

int	validate_rgb(const char *rgb)
{
	int	index;
	int	itr;
	int	result;

	index = 0;
	itr = 0;
	while (rgb[index] == ' ')
		index++;
	while (itr < 3)
	{
		if (rgb[index] == ',')
			index++;
		result = validate_double_value(&rgb[index], 0, 255);
		if (!result)
			return (0);
		index += result;
		itr++;
	}
	return (index);
}

int	validate_coordinate(const char *coordinate)
{
	int	index;
	int	itr;
	int	result;

	index = 0;
	itr = 0;
	while (coordinate[index] == ' ')
		index++;
	while (itr < 3)
	{
		if (coordinate[index] == ',')
			index++;
		result = validate_double(&coordinate[index]);
		if (!result)
			return (0);
		index += result;
		itr++;
	}
	return (index);
}

int	validate_normalized_vector(const char *normalized_vector)
{
	int			index;
	int			itr;
	int			result;
	t_vector	vector;

	index = 0;
	itr = 0;
	while (normalized_vector[index] == ' ')
		index++;
	while (itr < 3)
	{
		if (normalized_vector[index] == ',')
			index++;
		result = validate_double_value(&normalized_vector[index], -1, 1);
		if (!result)
			return (0);
		index += result;
		itr++;
	}
	index = 0;
	index += read_coordinate(&normalized_vector[index], &vector);
	if ((vector.x == 0 && vector.y == 0 && vector.z == 0)
		|| !equal(vector, normalise(vector)))
		return (0);
	return (index);
}
