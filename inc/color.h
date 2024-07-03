/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 23:24:44 by jhughes           #+#    #+#             */
/*   Updated: 2024/07/03 15:01:09 by jhughes          ###   ########.fr       */
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

int		get_red(t_color *color);
int		get_green(t_color *color);
int		get_blue(t_color *color);

t_color	set_color(unsigned char r, unsigned char g, unsigned char b);
t_color	mix(t_color color_a, double a_ratio, t_color color_b, double b_ratio);

#endif
