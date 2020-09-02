/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sub.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: merlijn <merlijn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/17 19:45:02 by merlijn       #+#    #+#                 */
/*   Updated: 2020/08/17 20:51:28 by merlijn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int	check_sub_argument_types(t_argument *args)
{
	if (args[0].type != ARG_TYPE_REG
	|| args[1].type != ARG_TYPE_REG
	|| args[2].type != ARG_TYPE_REG)
		return (ERROR);
	return (OK);
}

void		sub(char *mem, t_cursor *cursor)
{
	int	arg1;
	int arg2;
	int	arg3;
	int sum;

	get_argument_types(mem, cursor);
	if (check_sub_argument_types(cursor->args) == ERROR)
		return ;
	arg1 = mem[get_pos(cursor->pos, 2)];
	arg2 = mem[get_pos(cursor->pos, 3)];
	arg3 = mem[get_pos(cursor->pos, 4)];
	if (is_registry(arg1) && is_registry(arg2) && is_registry(arg3))
	{
		sum = cursor->registries[arg1 - 1] - cursor->registries[arg2 - 1];
		cursor->registries[arg3 - 1] = sum;
		if (sum == 0)
			cursor->carry = 1;
		else
			cursor->carry = 0;
	}
}