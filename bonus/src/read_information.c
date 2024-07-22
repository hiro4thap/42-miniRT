/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_information.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:34:29 by hiono             #+#    #+#             */
/*   Updated: 2024/07/22 14:11:13 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

int	read_double(const char *number, double *data)
{
	int		index;
	int		index_dot;
	double	value;
	int		sign;

	index = 0;
	value = 0;
	sign = 1;
	while (number[index] == ' ')
		index++;
	if (number[index] == '-')
	{
		index++;
		sign = -1;
	}
	while (ft_isdigit(number[index]))
		value = 10 * value + number[index++] - '0';
	if (number[index] == '.')
	{
		index_dot = index;
		while (ft_isdigit(number[++index]))
			value += (number[index] - '0') * pow(10, index_dot - index);
	}
	*data = sign * value;
	return (index);
}

int	read_rgb(const char *rgb, t_color *data)
{
	int		index;
	int		itr;
	double	value;

	index = 0;
	itr = 0;
	while (rgb[index] == ' ')
		index++;
	while (itr < 3)
	{
		if (rgb[index] == ',')
			index++;
		value = 0;
		index += read_double(&rgb[index], &value);
		if (itr == 0)
			data->r = (double) value / 255.0;
		else if (itr == 1)
			data->g = (double) value / 255.0;
		else if (itr == 2)
			data->b = (double) value / 255.0;
		itr++;
	}
	return (index);
}

int	read_coordinate(const char *coordinate, t_vector *data)
{
	int	index;
	int	itr;

	index = 0;
	itr = 0;
	while (coordinate[index] == ' ')
		index++;
	while (itr < 3)
	{
		if (coordinate[index] == ',')
			index++;
		if (itr == 0)
			index += read_double(&coordinate[index], &data->x);
		else if (itr == 1)
			index += read_double(&coordinate[index], &data->y);
		else if (itr == 2)
			index += read_double(&coordinate[index], &data->z);
		itr++;
	}
	return (index);
}

int	read_material_type(const char *flag, enum e_material *data)
{
	int	index;

	index = 0;
	while (flag[index] == ' ')
		index++;
	*data = flag[index++] - '0';
	return (index);
}

int	read_flag(const char *flag, int *data)
{
	int	index;

	index = 0;
	while (flag[index] == ' ')
		index++;
	*data = flag[index++] - '0';
	return (index);
}
