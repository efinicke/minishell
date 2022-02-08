/* ************************************************************************** */
/*									      */
/*							  :::	   ::::::::   */
/*   cd_change_directory.c                              :+:      :+:    :+:   */
/*						      +:+ +:+	      +:+     */
/*   By: spayeur <spayeur@student.42.fr>	    +#+  +:+	   +#+	      */
/*						  +#+#+#+#+#+	+#+	      */
/*   Created: 2022/01/19 12:21:16 by spayeur	       #+#    #+#	      */
/*   Updated: 2022/02/07 11:19:21 by spayeur          ###   ########.fr       */
/*									      */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	write_error_msg(void)
{
	perror("minishell: cd: write error");
	return (1);
}

static int	check_path_size(const char *cd_string, char *cd_string_allocated)
{
	if (ft_strlen(cd_string_allocated) > PATH_MAX)
	{
		free(cd_string_allocated);
		cd_error_msg(cd_string, ": File name too long");
		return (1);
	}
	if (chdir(cd_string_allocated) < 0)
	{
		free(cd_string_allocated);
		cd_perror_msg(cd_string);
		return (1);
	}
	return (0);
}

static void	update_pwd_oldpwd(char *cd_string_allocated, char ***envp, \
		const int outfile)
{
	const char	*unset_oldpwd[] = {"unset", "OLDPWD", NULL};
	const char	*export_oldpwd[] = {"export", "OLDPWD", NULL};
	int			id_pwd;
	int			id_oldpwd;
	const char	*pwd_value = ft_getenv("PWD", (const char **)*envp);

	pwd_accessors("SET", cd_string_allocated);
	id_pwd = ft_getenv_id("PWD", (const char **)*envp);
	id_oldpwd = ft_getenv_id("OLDPWD", (const char **)*envp);
	if (id_pwd != -1)
	{
		if (id_oldpwd != -1)
			free((*envp)[id_oldpwd]);
		if (id_oldpwd != -1)
			(*envp)[id_oldpwd] = ft_strjoin("OLDPWD=", pwd_value);
		free((*envp)[id_pwd]);
		(*envp)[id_pwd] = ft_strjoin("PWD=", cd_string_allocated);
	}
	else
	{
		if (id_oldpwd != -1)
			cmd_unset(2, unset_oldpwd, envp);
		if (id_oldpwd != -1)
			cmd_export(2, export_oldpwd, envp, outfile);
	}
}

int	change_directory(const char *cd_string, char *cd_string_allocated, \
	char ***envp, const int outfile)
{
	if (check_path_size(cd_string, cd_string_allocated) == 1)
		return (1);
	if (outfile >= 0)
	{
		if (write(outfile, cd_string_allocated, \
		ft_strlen(cd_string_allocated)) < 0)
		{
			update_pwd_oldpwd(cd_string_allocated, envp, outfile);
			free(cd_string_allocated);
			return (write_error_msg());
		}
		if (write(outfile, "\n", 1) < 0)
		{
			update_pwd_oldpwd(cd_string_allocated, envp, outfile);
			free(cd_string_allocated);
			return (write_error_msg());
		}
	}
	update_pwd_oldpwd(cd_string_allocated, envp, outfile);
	free(cd_string_allocated);
	return (0);
}
