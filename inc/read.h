/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:40:00 by hiono             #+#    #+#             */
/*   Updated: 2024/07/10 12:31:25 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READ_H
# define READ_H

# include <fcntl.h>
# include "miniRT.h"

typedef struct s_program t_program;

int	read_file(char *file, t_program *program);

#endif
