/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinicke <efinicke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 18:09:49 by spayeur           #+#    #+#             */
/*   Updated: 2022/02/08 03:52:39 by efinicke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* ************************************************************************** */
/*                                 Libraries                                  */
/* ************************************************************************** */

# include "../libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <linux/limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

/* ************************************************************************** */
/*                                 Structures                                 */
/* ************************************************************************** */

enum {infile_c, outfile_c};

typedef struct s_lx
{
	char		**cmds;
	int			type;
	int			squotes_mode;
	int			dquotes_mode;
	int			sq;
	int			dq;
	int			var;
	int			pos;
}			t_lx;

typedef struct s_cmd
{
	pid_t			pid;
	char			**file;
	int				*type;
	int				infile;
	int				outfile;
	int				argc;
	char			**argv;
	char			*path;
	struct s_cmd	*first;
	struct s_cmd	*next;
}			t_cmd;

/* ************************************************************************** */
/*                              Global variable                               */
/* ************************************************************************** */

extern int	g_return_code;

/* ************************************************************************** */
/*                           Function declarations                            */
/* ************************************************************************** */

/* ********************************* Shell ********************************** */

/*                                  pwd_var                                   */

void			set_pwd_var(char ***envp);

/*                                 shlvl_var                                  */

void			set_shlvl_var(char ***envp);

/*                                 envp_alloc                                 */

char			**envp_alloc(const char **system_envp);
char			**envp_sub_alloc(const char **system_envp, char **envp_copy);
void			envp_free(char **envp);

/*                                 envp_utils                                 */

const char		*ft_getenv(const char *name, const char **envp);
int				ft_getenv_id(const char *name, const char **envp);

/*                                  signals                                   */

void			set_signals(int mode);

/* ******************************** Parsing ********************************* */

/*                                   struct                                   */

t_lx			*init_datas_struct(t_lx *datas);
void			reinitialise_datas_struct(t_lx	*datas);

/*                                linked list                                 */

t_cmd			*create_and_init_first_cmd_lst(void);
t_cmd			*create_and_init_next_cmd_lst(t_cmd *last_cmd_lst);
void			init_cmd_lst_datas(t_cmd *cmd_lst);

/*                                   lexer                                    */

void			check_quotes_mode(char c, t_lx *datas);
int				is_valid_quotes(char *cmd_src, t_lx *datas);
char			*fix_spaces(char *cmd_src, t_lx *datas);
int				is_valid_syntax_1(char *cmd, t_lx *datas);
int				is_valid_syntax_2(char *cmd);
char			*put_tilde_var(char *cmd_src, t_lx *datas);
char			*replace_dollar_var_by_val(char *cmd_src, \
			char **envp, t_lx *datas);
void			put_val(char *cmd_src, char **cmd_dst, char **envp, \
			t_lx *datas);
char			*put_return_val(char *cmd_dst);
char			*put_env_val(char *cmd_dst, char *cmd_src, \
			t_lx *datas, char **envp);
char			*remove_quotes(char *cmd_src, t_lx *datas);
char			*get_env(char *name, char **envp);

/*                                fill structs                                */

void			fill_cmds_datas_struct_with_cmd_line(char *cmd_line, \
			t_lx *datas);
t_cmd			*parse_and_return_cmd_lst(char *line, char **envp);
t_cmd			*fill_lst(t_lx *datas, char **envp);
char			*fill_file_and_type(char *cmd, t_cmd *cmd_lst, \
				t_lx *datas, char **envp);
char			*return_file(char *cmd, int file_type, t_lx *datas, \
			t_cmd *cmd_lst);
void			add_type(int type_code, t_cmd *cmd_lst, int file_type);
void			pass_and_count_redir(char *cmd, t_lx *datas);
void			fill_file(char *file, t_lx *datas, t_cmd *cmd_lst, char **envp);
void			fill_argv_and_argc(char *cmd, t_cmd *cmd_lst, \
				t_lx *datas, char **envp);
void			fill_argv(char *cmd, t_cmd *cmd_lst, t_lx *datas, char **envp);
void			sub_fill_argv(char *cmd, char *tmp, t_cmd *cmd_lst, \
			t_lx *datas);
void			fill_argc(t_cmd *cmd_lst);
int				return_str_tab_size(char **tab);

/*                                    free                                    */

void			clear_all(char *cmd, t_cmd *cmd_lst, t_lx *datas);
void			clear_datas_struct(t_lx *datas);
void			clear_cmd_lst(t_cmd *cmd_lst);
void			clear_str_tab(char **str_tab);

/*                             utils : char *tab                              */

char			*str_c_join(char *cmd, char c);
char			*strjoin_free(char *cmd, char *c);
char			*str_dup(char *s1);
int				str_len(const char *str);
int				str_cmp(const char *s1, const char *s2);
int				str_n_cmp(const char *s1, const char *s2, size_t n);

/*                             utils : char **tab                             */

char			**str_tab_sub_alloc(const char **old_str_tab, \
			char **str_tab_copy);
char			**add_str_in_tab(char *str, char **old_str_tab);

/*                              utils : int *tab                              */

int				*add_int_in_tab(const int value, int *old_type);

/*                              error management                              */

void			send_error(char *error_message);

/*                              tests functions                               */

void			display_cmd_lst(t_cmd *cmd_lst);
void			display_str_tab(char **tab);
void			display_int_tab(int *tab);

/* ******************************** Builtins ******************************** */

/*                                    echo                                    */

int				cmd_echo(const int argc, const char **argv, const int outfile);

/*                                     cd                                     */

int				cmd_cd(const int argc, const char **argv, char ***envp, \
				const int outfile);
int				cd_without_argument(char ***envp, const int outfile);
int				cd_with_argument(const char *cd_string, char ***envp, \
				const int outfile);

int				cdpath(const char *cd_string, char ***envp, const int outfile);

int				slash_or_pwd(const char *cd_string, char *cd_string_allocated, \
				char ***envp, const int outfile);

int				canonical_form(const char *cd_string, \
				char *cd_string_allocated, char ***envp, const int outfile);
char			*dot_slash(char *str_allocated);
char			*dot_dot_slash(const char *str, char *str_allocated);
char			*slash_slash(char *str_allocated);
char			*cut_substr(char *cd_string_allocated, char *target, \
			unsigned int n);
int				no_directory_msg(const char *directory);

int				change_directory(const char *cd_string, \
				char *cd_string_allocated, char ***envp, const int outfile);

void			cd_perror_msg(const char *string);
void			cd_error_msg(const char *string, const char *error_msg);

/*                                    pwd                                     */

int				cmd_pwd(const int argc, const char **argv, const char **envp, \
				const int outfile);
const char		*pwd_accessors(const char *accessor, char *value);

/*                                   export                                   */

int				cmd_export(const int argc, const char **argv, char ***envp, \
				const int outfile);
int				export_without_argument(const char **envp, const int outfile);
int				export_with_argument(const char **argv, char ***envp);
char			**add_variable(const char *var, char **old_envp);
char			*replace_variable(const char *var, char **envp, const int id);

/*                                   unset                                    */

int				cmd_unset(const int argc, const char **argv, char ***envp);
char			**remove_variable(char **old_envp, const int id);

/*                                    env                                     */

int				cmd_env(const int argc, const char **argv, const char **envp, \
				const int outfile);

/*                                    exit                                    */

int				cmd_exit(t_cmd *cmd, char **envp, int *pipes, int is_fork);
int				exit_code_validity(const char *exit_code);
void			numeric_argument_required(const char *argument);

/* *************************** Command_executions *************************** */

/*                                 execution                                  */

int				execution(t_cmd *cmd, char ***envp);
int				basic_execution(t_cmd *cmd, int *pipes, char **envp, \
				const unsigned int size);

void			export_underscore(const char *path, char ***envp);

/*                                    path                                    */

void			get_cmds_path(t_cmd *cmd, const char **envp);
int				cmd_error(t_cmd *cmd, int *pipes, char **envp, \
				const unsigned int size);
unsigned int	get_cmd_list_size(t_cmd *cmd);

/*                                  here_doc                                  */

void			here_doc_implementation(t_cmd *cmd, int *pipes, \
			const unsigned int size, char **envp);

/*                                   files                                    */

int				open_all_io_files(t_cmd *cmd, int *pipes, \
				const unsigned int size, const unsigned int set_cmd_io);

/*                                  builtin                                   */

int				is_builtin(const char *cmd_path);
int				exec_builtin(t_cmd *cmd, char ***envp, const unsigned int size);
int				exec_builtin_in_fork(t_cmd *cmd, int *pipes, char **envp, \
				const unsigned int size);

/*                                    free                                    */

void			free_on_fork_failure(t_cmd *cmd, int *pipes, char **envp, \
			const unsigned int size);

#endif
