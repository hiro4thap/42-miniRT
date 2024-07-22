/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_information.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:40:17 by hiono             #+#    #+#             */
/*   Updated: 2024/07/22 09:33:37 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

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
		if (itr != 0)
		{
			if (coordinate[index] != ',')
				return (0);
			index++;
		}
		result = validate_double_info(&coordinate[index]);
		if (!result)
			return (0);
		index += result;
		itr++;
	}
	return (index);
}

// static t_bool	is_valid_normalized_vector_value(const char
//	 *normalized_vector)
// {
// 	int			index;
// 	t_vector	vector;

// 	index = 0;
// 	index += read_coordinate(&normalized_vector[index], &vector);
// 	return (!(vector.x == 0 && vector.y == 0 && vector.z == 0)
// 		&& equal(vector, normalise(vector)));
// }

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

int	validate_flag(const char *flag)
{
	int	index;

	index = 0;
	while (flag[index] == ' ')
		index++;
	if (flag[index] != '0' && flag[index] != '1')
		return (0);
	index++;
	return (index);
}
