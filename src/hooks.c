/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 10:57:07 by jhughes           #+#    #+#             */
/*   Updated: 2024/07/05 12:28:48 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

int	input(int key, t_program *program)
{
	if (key == KEY_ESC)
		exit_program(program);
	return (0);
}

int	exit_program(t_program *program)
{
	(void)program;
	exit(0);
}
