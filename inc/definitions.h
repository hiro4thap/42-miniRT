/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   definitions.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 23:26:05 by jhughes           #+#    #+#             */
/*   Updated: 2024/07/05 14:46:01 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINITIONS_H
# define DEFINITIONS_H

# define TRUE 1
# define FALSE 0

typedef int	t_bool;

# define SPECULAR_ON 0

# ifndef __linux__

#  define ON_LINUX 0

enum e_keycode
{
	KEY_ESC = 53,
	KEY_LSHIFT = 257,
	KEY_RSHIFT = 258,
	KEY_LCTRL = 279,
	KEY_RCTRL = 269,
	KEY_LCMD = 259,
	KEY_RCMD =260,
	KEY_LALT = 261,
	KEY_RALT = 262,
	KEY_TILDE = 50,
	KEY_ONE = 18,
	KEY_TWO = 19,
	KEY_THREE = 20,
	KEY_FOUR = 21,
	KEY_FIVE = 23,
	KEY_SIX = 22,
	KEY_SEVEN = 26,
	KEY_EIGHT = 28,
	KEY_NINE = 25,
	KEY_ZERO = 29,
	KEY_PLUS = 24,
	KEY_MINUS = 27,
	KEY_RETURN = 36,
	KEY_UP = 126,
	KEY_DOWN = 125,
	KEY_LEFT = 123,
	KEY_RIGHT = 124
};
# else

#  define ON_LINUX 1

enum e_keycode
{
	KEY_ESC = 65307,
	KEY_LSHIFT = 65505,
	KEY_RSHIFT = 66506,
	KEY_LCTRL = 66507,
	KEY_RCTRL = 66508,
	KEY_LALT = 65513,
	KEY_RALT = 65514,
	KEY_TILDE = 96,
	KEY_ONE = 49,
	KEY_TWO = 50,
	KEY_THREE = 51,
	KEY_FOUR = 52,
	KEY_FIVE = 53,
	KEY_SIX = 54,
	KEY_SEVEN = 55,
	KEY_EIGHT = 56,
	KEY_NINE = 57,
	KEY_ZERO = 29,
	KEY_PLUS = 61,
	KEY_MINUS = 45,
	KEY_RETURN = 65293,
	KEY_UP = 65362,
	KEY_DOWN = 65364,
	KEY_LEFT = 65361,
	KEY_RIGHT = 65363
};
# endif

enum e_mousecode
{
	MOUSE_LEFT = 1,
	MOUSE_MIDDLE,
	MOUSE_RIGHT,
	MOUSE_SCROLL_UP,
	MOUSE_SCROLL_DOWN,
	MOUSE_BACK = 8,
	MOUSE_FORWARD
};

// From X.h
enum e_event_type
{
	EVENT_KEY_PRESS = 2,
	EVENT_KEY_RELEASE,
	EVENT_BUTTON_PRESS,
	EVENT_BUTTON_RELEASE,
	EVENT_MOTION_NOTIFY,
	EVENT_ENTER_NOTIFY,
	EVENT_LEAVE_NOTIFY,
	EVENT_FOCUS_IN,
	EVENT_FOCUS_OUT,
	EVENT_KEYMAP_NOTIFY,
	EVENT_VISIBILITY_NOTIFY = 15,
	EVENT_CREATE_NOTIFY,
	EVENT_DESTROY_NOTIFY,
	EVENT_CONFIGURE_NOTIFY = 22,
	EVENT_CONFIGURE_REQUEST,
	EVENT_GRAVITY_NOTIFY,
	EVENT_RESIZE_REQUEST
};

# define EVENT_MASK_NO_EVENT 0

enum e_event_mask
{
	EVENT_MASK_KEY_PRESS,
	EVENT_MASK_KEY_RELEASE,
	EVENT_MASK_BUTTON_PRESS,
	EVENT_MASK_BUTTON_RELEASE,
	EVENT_MASK_ENTER_WINDOW,
	EVENT_MASK_LEAVE_WINDOW,
	EVENT_MASK_POINTER_MOTION,
	EVENT_MASK_POINTER_MOTION_HINT,
	EVENT_MASK_BUTTON_1,
	EVENT_MASK_BUTTON_2,
	EVENT_MASK_BUTTON_3,
	EVENT_MASK_BUTTON_4,
	EVENT_MASK_BUTTON_5,
	EVENT_MASK_BUTTON_MOTION,
	EVENT_MASK_KEYMAP_STATE,
	EVENT_MASK_EXPOSURE,
	EVENT_MASK_VISIBILITY_CHANGE,
	EVENT_MASK_STRUCTURE_NOTIFY,
	EVENT_MASK_RESIZE_REDIRECT,
	EVENT_MASK_SUBSTRUCTURE_NOTIFY,
	EVENT_MASK_SUBSTRUCTURE_REDIRECT,
	EVENT_MASK_FOCUS_CHANGE,
	EVENT_MASK_PROPERTY_CHANGE,
	EVENT_MASK_COLORMAP_CHANGE,
	EVENT_MASK_OWNER_GRAB_BUTTON
};

#endif
