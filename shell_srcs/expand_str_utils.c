/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_str_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 14:29:26 by jnannie           #+#    #+#             */
/*   Updated: 2020/10/24 17:39:28 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				check_quotes_error(int single_q, int double_q,
								t_shell *shell)
{
	if (double_q || single_q)
	{
		g_last_exit_status = 258;
		print_error(0, "syntax error all quotes must be enclosed", 1);
		shell->parsing_error = 1;
		return (-1);
	}
	return (0);
}
