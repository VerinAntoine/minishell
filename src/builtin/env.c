/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 09:38:10 by averin            #+#    #+#             */
/*   Updated: 2024/02/13 08:41:28 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

/**
 * @brief Reproduce the behaviour of env builtin
 *
 * @param exec data of the execution branch
 * @return int
 */
int	cmd_env(t_exec *exec)
{
	size_t	i;
	char	*underscore;
	char	*del;

	i = -1;
	if (exec->args[0] == NULL || exec->args[1])
		return (C_SUCCESS);
	while (exec->data->envp[++i])
	{
		del = ft_strchr(exec->data->envp[i], '=');
		if (del && del[1] == '\0')
			continue ;
		if (exec->data->envp[i][0] == '_' && exec->data->envp[i][1] == '=')
			underscore = exec->data->envp[i];
		else
			ft_putendl_fd(exec->data->envp[i], exec->outfile);
	}
	return (ft_putendl_fd(underscore, exec->outfile), C_SUCCESS);
}
