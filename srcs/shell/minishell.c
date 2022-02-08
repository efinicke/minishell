/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinicke <efinicke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 16:14:16 by spayeur           #+#    #+#             */
/*   Updated: 2022/02/07 17:02:53 by efinicke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	g_return_code;

static void	for_each_line(char *line, char ***envp)
{
	t_cmd	*cmd;

	if (line[0])
		add_history(line);
	cmd = parse_and_return_cmd_lst(line, *envp);
	if (cmd)
	{
		set_signals(2);
		g_return_code = execution(cmd, envp);
		set_signals(1);
		clear_cmd_lst(cmd);
	}
	free(line);
}

int	minishell(const char **system_envp)
{
	char	*line;
	char	**envp;

	envp = envp_alloc(system_envp);
	set_pwd_var(&envp);
	set_shlvl_var(&envp);
	g_return_code = 0;
	set_signals(1);
	line = readline("minishell$ ");
	while (line)
	{
		for_each_line(line, &envp);
		line = readline("minishell$ ");
	}
	rl_clear_history();
	pwd_accessors("SET", NULL);
	envp_free(envp);
	write(STDERR_FILENO, "exit\n", 5);
	return (g_return_code);
}

int	main(int argc, char **argv, const char **system_envp)
{
	(void)argc;
	(void)argv;
	return (minishell(system_envp));
}
