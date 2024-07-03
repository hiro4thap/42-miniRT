/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 23:24:44 by jhughes           #+#    #+#             */
/*   Updated: 2024/07/03 17:57:03 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

typedef struct s_color
{
	double	r;
	double	g;
	double	b;
}	t_color;

// color.c

unsigned char	get_red(t_color *color);
unsigned char	get_green(t_color *color);
unsigned char	get_blue(t_color *color);
t_color			set_color(unsigned char r, unsigned char g, unsigned char b);

// color_operations.c

t_color			color_proportion(t_color color, double ratio);
t_color			color_add(t_color color_a, t_color color_b);
t_color			color_multiply(t_color color_a, t_color color_b);

#endif
