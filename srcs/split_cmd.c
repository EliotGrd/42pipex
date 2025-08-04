/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiraud <egiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 22:46:21 by egiraud           #+#    #+#             */
/*   Updated: 2025/08/03 21:08:33 by egiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static int	count_args(const char *s)
{
	int	i;
	int	in_quotes;
	int	arg_count;

	i = 0;
	arg_count = 0;
	in_quotes = 0;
	while (ft_iswspace(s[i]))
		i++;
	while (s[i])
	{
		if (!in_quotes)
		{
			if ((s[i] != ' ' && s[i + 1] == ' ') || (s[i] != ' ' && s[i
					+ 1] == '\0') || (s[i]) == '\'')
				arg_count++;
			if (s[i] == '\'')
				in_quotes = 1;
		}
		else if (s[i] == '\'')
			in_quotes = 0;
		i++;
	}
	return (arg_count);
}

static char	*extract_args(char **p)
{
	char	*start;
	int		arg_len;
	char	*arg;

	start = NULL;
	start = *p;
	if (*(*p)++ == '\'')
	{
		start++;
		while (*(*p) != '\'' && **p)
			(*p)++;
		arg_len = *p - start;
		(*p)++;
	}
	else
	{
		while (*(*p) != ' ' && **p)
			(*p)++;
		arg_len = *p - start;
	}
	arg = pmalloc(sizeof(char) * (arg_len + 1));
	ft_memcpy(arg, start, arg_len);
	arg[arg_len] = 0;
	return (arg);
}

static void	check_quotes(const char *s)
{
	int	quote_count;

	quote_count = 0;
	while (*s)
	{
		if (*s == '\'')
			quote_count++;
		s++;
	}
	if (quote_count % 2 == 1)
		fatal_error("quotes not closed", EINVAL);
}

char	**split_cmd(char *s)
{
	char	**argv;
	int		arg_count;
	char	*p;
	int		j;

	p = NULL;
	if (s[0] == 0)
		fatal_error("empty command", EINVAL);
	check_quotes(s);
	arg_count = count_args(s);
	argv = pmalloc(sizeof(char *) * (arg_count + 1));
	p = s;
	j = -1;
	while (++j < arg_count)
	{
		while (ft_iswspace(*p))
			p++;
		argv[j] = extract_args(&p);
	}
	argv[arg_count] = 0;
	return (argv);
}
