/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 21:36:20 by jnannie           #+#    #+#             */
/*   Updated: 2020/10/24 17:39:38 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int				process_quote(int quote1, int quote2,
									char **temp_data, char **data)
{
	if (!quote1)
		quote2 = !quote2;
	else
		*(*temp_data)++ = **data;
	(*data)++;
	return (quote2);
}

static char				*proc_var(t_shell *shell, char **new_data,
										char **data, t_token *token)
{
	int		i;

	if ((i = expand_variable(shell, new_data, data)) == 0 && **data == '\0')
	{
		free(token->data);
		token->data = 0;
		free(*new_data);
		return (0);
	}
	else
		return (*new_data + i);
}

static void				process_backslash(int single_q, int double_q,
										char **temp_data, char **data)
{
	if ((is_escape_char(*(*data + 1)) && !single_q) ||
		(!single_q && !double_q))
		(*data)++;
	*(*temp_data)++ = *(*data)++;
}

static char				*init_vars(t_shell *shell, t_quotes *quotes,
								char **new_data, char *data)
{
	quotes->sq = 0;
	quotes->dq = 0;
	if (!(*new_data = ft_calloc(ft_strlen(data) + 1, sizeof(char))))
		exit_shell(shell, EXIT_FAILURE);
	return (*new_data);
}

int						expand_str(t_shell *shell, t_token *token, char *data)
{
	char				*new_data;
	t_quotes			q;
	char				*temp_data;

	temp_data = init_vars(shell, &q, &new_data, data);
	while (*data)
		if (*data == '\'')
			q.sq = process_quote(q.dq, q.sq, &temp_data, &data);
		else if (*data == '"')
			q.dq = process_quote(q.sq, q.dq, &temp_data, &data);
		else if (*data == '\\')
			process_backslash(q.sq, q.dq, &temp_data, &data);
		else if (*data == '$')
		{
			if (q.sq)
				*temp_data++ = *data++;
			else if (!(temp_data = proc_var(shell, &new_data, &data, token)))
				return (0);
		}
		else
			*temp_data++ = *data++;
	free(token->data);
	token->data = new_data;
	return (check_quotes_error(q.sq, q.dq, shell));
}
