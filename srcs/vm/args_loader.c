/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   args_loader.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: floris <ffredrik@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/06 10:00:00 by floris        #+#    #+#                 */
/*   Updated: 2020/09/07 12:00:00 by floris        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "vm.h"

static int		ind_arg(uint8_t *mem, int idx)
{
	int value;

	value = (int16_t)read_2_bytes(mem, idx);
	return (value);
}

static int		dir_arg(uint8_t *mem, int idx, int t_dir_size)
{
	int value;

	value = 0;
	if (t_dir_size == 2)
		value = (int16_t)read_2_bytes(mem, idx);
	else if (t_dir_size == 4)
		value = (int32_t)read_4_bytes(mem, idx);
	return (value);
}

static int		reg_arg(uint8_t *mem, int idx, t_cursor *cursor, t_error *ret)
{
	int reg;

	reg = mem[get_pos(idx, 0)];
	if (!is_registry(reg))
		*ret = kError;
	return (reg);
}

static bool	arg_for_idx(t_arena *arena, t_cursor *cur, int *offset, int nr)
{
	t_error		ret;
	int			arg_len;
	t_args_type	type;
	t_enbyte	eb;

	eb = *get_enbyte(arena, cur->pos);
	reverse_eb(&eb);
	type = get_arg(eb, cur->opcode, nr);
	ret = kOk;
	if (type != kTNone && ret == kOk)
	{
		cur->args[nr - 1].type = type;
		arg_len = arg_length(type, cur->opcode);
		if (type == kTDir)
			cur->args[nr - 1].value = ind_arg(arena->mem, cur->pos + *offset);
		if (type == kTInd)
			cur->args[nr - 1].value = dir_arg(arena->mem, cur->pos + *offset, get_opinfo(cur->opcode)->dir_size);
		if (type == kTReg)
			cur->args[nr - 1].value = reg_arg(arena->mem, *offset, cur, &ret);
		*offset += arg_len;
	}
	return (ret);
}

bool	preload_args(t_arena *arena_s, t_cursor *cursor)
{
	t_error		ret;
	int			offset;

	offset = 1 + (get_opinfo(cursor->opcode)->has_enbyte ? 1 : 0); // one for skip opcode + 1 for enbyte
	ret = arg_for_idx(arena_s, cursor, &offset, 1);
	if (ret == kOk)
		ret = arg_for_idx(arena_s, cursor, &offset, 2);
	if (ret == kOk)
		ret = arg_for_idx(arena_s, cursor, &offset, 3);
	return (ret == kOk ? true : false);
}
