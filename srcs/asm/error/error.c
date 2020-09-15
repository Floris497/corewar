/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: floris <ffredrik@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/13 22:17:00 by floris        #+#    #+#                 */
/*   Updated: 2020/09/13 22:17:00 by floris        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>
#include "error.h"

static const t_errinfo	g_errinfo[70] =
{
	{
		.format = ERR_PFX_FL"%d:%d -- kSuccsess (0)\n",
	},
	{
		.format = ERR_PFX_FL"%d:%d -- kError (1) TOKEN:[%s]\n",
	},
	{
		.format = ERR_PFX"kAllocError (2)\n",
	},
	{
		.format = ERR_PFX_FL" -- kErrorOpeningFile (3)\n",
	},
	{
		.format = ERR_PFX_FL" -- kErrorEmptyFile (4)\n",
	},
	{
		.format = ERR_PFX"\n",
	},
	{
		.format = ERR_PFX"\n",
	},
	{
		.format = ERR_PFX"\n",
	},
	{
		.format = ERR_PFX"\n",
	},
	{
		.format = ERR_PFX"\n",
	},
	{
		.format = ERR_PFX_FL"%d:%d -- kInputError (10) TOKEN:[%s]\n",
	},
	{
		.format = ERR_PFX_FL"%d:%d -- kParseError (11) TOKEN:[%s]\n",
	},
	{
		.format = ERR_PFX"\n",
	},
	{
		.format = ERR_PFX"\n",
	},
	{
		.format = ERR_PFX"\n",
	},
	{
		.format = ERR_PFX"\n",
	},
	{
		.format = ERR_PFX"\n",
	},
	{
		.format = ERR_PFX"\n",
	},
	{
		.format = ERR_PFX"\n",
	},
	{
		.format = ERR_PFX"\n",
	},
	{
		.format = ERR_PFX"\n",
	},
	{
		.format = ERR_PFX"\n",
	},
	{
		.format = ERR_PFX"\n",
	},
	{
		.format = ERR_PFX"\n",
	},
	{
		.format = ERR_PFX"\n",
	},
	{
		.format = ERR_PFX"\n",
	},
	{
		.format = ERR_PFX"\n",
	},
	{
		.format = ERR_PFX"\n",
	},
	{
		.format = ERR_PFX"\n",
	},
	{
		.format = ERR_PFX"\n",
	},
	{
		.format = ERR_PFX_FL"%d:%d -- kTranslationError (30) TOKEN:[%s]\n",
	},
	{
		.format = ERR_PFX_FL"%d:%d -- kInvalidArgumentCount (31) TOKEN:[%s]\n",
	},
	{
		.format = ERR_PFX_FL"%d:%d -- kUndefineInstructionError (32) TOKEN:[%s]\n",
	},
	{
		.format = ERR_PFX"\n",
	},
	{
		.format = ERR_PFX"\n",
	},
	{
		.format = ERR_PFX"\n",
	},
	{
		.format = ERR_PFX"\n",
	},
	{
		.format = ERR_PFX"\n",
	},
	{
		.format = ERR_PFX"\n",
	},
	{
		.format = ERR_PFX"\n",
	},
	{
		.format = ERR_PFX_FL"%d:%d -- kLinkingError (40) TOKEN:[%s]\n",
	},
	{
		.format = ERR_PFX_FL"%d:%d -- kLinkNotFoundError (41) TOKEN:[%s]\n",
	},
	{
		.format = ERR_PFX"\n",
	},
	{
		.format = ERR_PFX"\n",
	},
	{
		.format = ERR_PFX"\n",
	},
	{
		.format = ERR_PFX"\n",
	},
	{
		.format = ERR_PFX"\n",
	},
	{
		.format = ERR_PFX"\n",
	},
	{
		.format = ERR_PFX"\n",
	},
	{
		.format = ERR_PFX"\n",
	},
	{
		.format = ERR_PFX_FL"%d:%d -- kTokenError (50) TOKEN:[%s]\n",
	},
	{
		.format = ERR_PFX"\n",
	},
	{
		.format = ERR_PFX"\n",
	},
	{
		.format = ERR_PFX"\n",
	},
	{
		.format = ERR_PFX"\n",
	},
	{
		.format = ERR_PFX"\n",
	},
	{
		.format = ERR_PFX"\n",
	},
	{
		.format = ERR_PFX"\n",
	},
	{
		.format = ERR_PFX"\n",
	},
	{
		.format = ERR_PFX"\n",
	},
	{
		.format = ERR_PFX_FL"%d:%d -- kMetaParseError (60) TOKEN:[%s]\n",
	},
	{
		.format = ERR_PFX_FL"%d:%d -- kMPNameTooLong (61)\n",
	},
	{
		.format = ERR_PFX_FL"%d:%d -- kMPCommentTooLong (62)\n",
	},
};

// 	ft_printf("Error: %.3d Line: %.4d:%.4d [%s]\n\n", error.code, error.token->loc.ln, error.token->loc.chr, error.token->str);

static size_t	line_width(const char *str, size_t num)
{
	t_index	idx;
	size_t	len;

	idx = 0;
	len = 0;
	while (idx < num && str[idx] != '\0')
	{
		if (str[idx] == '\t')
			len += 4 - (len % 4);
		else
			len += 1;
		idx++;
	}
	return (len);
}

void	print_error(t_error *err, t_list *lines)
{
	if (err->code <= 0 && err->code >= -70)
		ft_printf(g_errinfo[-err->code].format, err->file_name, err->token->loc.ln, err->token->loc.chr, err->token->str);
	while (lines != NULL)
	{
		if (lines->content_size == err->token->loc.ln)
		{
			ft_printf("%s\n", lines->content);
			if (err->token->str != NULL || err->token->loc.chr != 0)
				ft_printf("%*.c\n", line_width(lines->content, err->token->loc.chr + 1), '^');
		}
		lines = lines->next;
	}
}

t_ret	set_error(const char *file, t_index idx, t_ret ret, t_error *error)
{
	error->code = ret;
	error->token = &error->rtoken;
	error->rtoken.loc.ln = ft_chrcnt(file, '\n', idx + 1) + 1;
	error->rtoken.loc.chr = 0;
	return (ret);
}

t_ret	set_err_loc(t_place loc, t_ret ret, t_error *error)
{
	error->code = ret;
	error->token = &error->rtoken;
	error->rtoken.loc = loc;
	return (ret);
}

t_ret	set_err_token(t_tksave *token, t_ret ret, t_error *error)
{
	error->code = ret;
	error->token = token;
	return (ret);
}

