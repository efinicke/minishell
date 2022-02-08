/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spayeur <spayeur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 17:40:41 by spayeur           #+#    #+#             */
/*   Updated: 2022/02/02 17:54:25 by spayeur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	shell_ctrl_c(int signal)
{
	write(STDERR_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	(void)signal;
	g_return_code = 130;
}

static void	cmd_ctrl_c(int signal)
{
	write(STDERR_FILENO, "\n", 1);
	(void)signal;
	g_return_code = 130;
}

static void	cmd_ctrl_back_slash(int signal)
{
	write(STDERR_FILENO, "Quit (core dumped)\n", 19);
	(void)signal;
	g_return_code = 131;
}

void	set_signals(int mode)
{
	if (mode == 1)
	{
		signal(SIGINT, shell_ctrl_c);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == 2)
	{
		signal(SIGINT, cmd_ctrl_c);
		signal(SIGQUIT, cmd_ctrl_back_slash);
	}
	else
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
}
