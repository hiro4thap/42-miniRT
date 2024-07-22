/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 10:57:07 by jhughes           #+#    #+#             */
/*   Updated: 2024/07/22 16:12:29 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/bonus/miniRT_bonus.h"

int	input(int key, t_program *program)
{
	if (key == KEY_ESC)
		cleanup(program, EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

int	exit_program(t_program *program)
{
	return (cleanup(program, EXIT_SUCCESS));
}
