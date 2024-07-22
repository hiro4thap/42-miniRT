/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 10:57:07 by jhughes           #+#    #+#             */
/*   Updated: 2024/07/18 12:52:59 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

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
