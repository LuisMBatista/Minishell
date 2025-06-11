/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumiguel <lumiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:45:39 by treis-ro          #+#    #+#             */
/*   Updated: 2025/06/10 11:54:02 by lumiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "../libft/libft.h"
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h> 
# include <sys/wait.h>
# include <sys/stat.h> 
# include <fcntl.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>

# define BUFFER_SIZE	4096

/*── exit codes ─────────────────────────────────────────────────────*/

# define EOF_CODE			-1
# define SUCCESS			0
# define FATAL_ERR			1
# define SYNTAX_ERR			2
# define CANNOT_EXECUTE		126
# define CMD_NOT_FOUND		127
# define INVALID_EXIT		128    
# define SIGINT_ERR			130    
# define SIGQUIT_ERR		131    
# define OUT_OF_RANGE		255    

# define TOKEN_PIPE			1
# define TOKEN_REDIRECT		2
# define TOKEN_CMD			3
# define TOKEN_ENV			4

# define OUTPUT			1
# define APPEND			2
# define INPUT			3
# define HEREDOC		4

# define STDIN 0
# define STDOUT 1
# define STDERR 2

typedef struct s_redirection
{
	char					*file;
	int						type;
	int						fd;
	struct s_redirection	*next;
}	t_redirection;

typedef struct s_token
{
	char			*value;
	int				type;
	int				expand;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_env
{
	char			*key;
	char			*value;
	int				e_flag;
	struct s_env	*next;
}	t_env;

typedef struct s_val
{
	char	*real_value;
	int		i;
	int		j;
	int		buffer_size;
}	t_val;

typedef struct s_cmd
{
	char				**cmd;
	int					prev_fd;
	int					fd[2];
	t_redirection		*redir;
	t_env				*env;
	struct s_cmd		*next;
	int					status;
}	t_cmd;

typedef struct s_shell
{
	pid_t			*pids;
	size_t			n_pids;
	t_env			*env;				
	t_env			*shell_vars;
	t_token			*tokens;
	t_cmd			*commands;
	char			*last_input;
	int				stdin_backup;
	int				stdout_backup;
	char			*path;
}	t_shell;	

typedef struct s_pipex
{
	int		fd;
	int		pid;
	int		prev_fd;
	int		pipe_fd[2];
	int		in_fd;
	int		out_fd;
	int		i;
	t_shell	*shell;
}	t_pipex;

extern volatile sig_atomic_t	g_exit_signal;

int		parse_main(t_shell *shell);

void	free_shell(t_shell *shell);

t_env	*env_init(char **envp);
t_shell	shell_init(t_shell *shell, char **envp);
void	export_sorter(t_env *env);
void	env_add(char **env, const char *new_env_line);
char	**env_delete(char **env, const char *env_line, int count);
int		env_line_count(char **env);

void	print_export(t_env *env);
int		exp_sorter(t_env *ptr);
void	free_tokens(t_shell *shell);
int		special_char(char c);
char	**ft_realloc(char **ptr, size_t size);
void	free_char_array(char **tokens);
int		check_quotes(char *input);
int		token_type(char *token);
int		var_creation_check(char *token);
char	*lvlupdate(t_env *env);
void	unset_env(int i, char **keys, t_env *env);

char	**split_input(char *input);

//util functions
int		ft_strcmp(const char *s1, const char *s2);

//builtsins
int		ft_cd(char **args);
int		ft_echo(char **args, int n_flag);
int		ft_export(char **args, t_env *env);
int		ft_unset(t_env **env, char **keys);
int		ft_pwd(void);
int		exit_shell(char **args, int *flag);
int		ft_env_cmd(t_env *env, t_cmd *cmd);
int		new_variable_env( char *cmd, t_env *env);

int		is_valid_identifier(const char *str);
t_env	*find_env_key(t_env *env, const char *key);
void	new_variable(t_env *env, char *key, char *value);
t_env	*ft_envlast(t_env *lst);
char	*try_paths(char **path, char *cmd_with_slash);
char	*get_right_path(char **env, char *cmd_with_slash);
char	*get_path(char **env, char *cmd);
int		execute_pipeline(t_cmd *cmd, t_shell *shell);
size_t	count_cmds(t_cmd *cmd);
char	**create_exec_env(t_env *env, t_env *l_env);
void	free_partial_env(char **env, size_t size);
int		fill_env(char **final_env, t_env *src, t_env *other, size_t *i);
int		add_env_entry(char **final_env, size_t *i, t_env *entry);
char	*key_value_join(char *key, char *value);
void	sig_int(int code);
void	sig_quit(int code, t_pipex *pipex);
void	putstr_fd(char *s, int fd);
void	putendl_fd(char *s, int fd);
void	free_commands(t_shell *shell);
int		env_list_size(t_env *env);

void	close_child_fds(t_pipex *pipex);
void	child_ft_handler(t_cmd *cmd, t_pipex *pipex);
char	*tild_expansion(char *real_value, int *j, int *i, t_shell *shell);
char	*resize_buffer(char *real_value, int *buffer_size);
char	*handle_quotes(t_token *token, char *real_value, int *j, int *i);
char	*process_var(t_val *val, char *token, t_shell *shell);
char	*handle_token_value(t_val *val, t_token *token, t_shell *shell);

int		add_to_command_env(t_cmd *cmd, t_token *token, t_shell *shell);
void	add_env_to_command(t_cmd *cmd, t_env *new_env);
char	*expand_var(char *token, int *index, t_shell *shell);
t_env	*find_env(t_env *env, const char *key);
char	*find_home_env(t_shell *shell);
int		add_env_node(char *envp, t_env **env, t_env **current);
int		add_redirection(t_cmd *cmd, t_token *token, t_shell *shell);
int		redir_heredoc(t_redirection *redir, t_token *token,
			t_shell *shell, t_cmd *cmd);
int		get_here_input(t_shell *shell, char *del, int *pipe_fds, int quote);
int		redir_input(t_redirection *redir, t_token *token, t_shell *shell);
int		redir_output(t_redirection *redir,
			t_token *token, int type, t_shell *shell);
int		slash_check(char *path);
int		force_env(t_env **env, t_env **curr);
int		quote_expand(char quote, int expand);
int		add_to_command_argument(t_cmd *cmd, t_token *token, t_shell *shell);
char	**command_realloc(char **old_cmd, size_t new_size);
void	cmd_lstadd_back(t_cmd **cmd_list, t_cmd *new_cmd);
void	set_fds(t_cmd **cmd_list);
t_cmd	*init_cmd(void);

char	*find_real_value(t_token *token, t_shell *shell);
char	*realloc_value(char *old_value, int old_size, int new_size);
int		redir_check(t_redirection *redir);
void	init_val(t_val *val);

int		parse_tokens_into_commands(t_shell *shell, int status, t_token *token);

int		builtin_check(t_cmd *cmd);
int		builtin(t_cmd *cmd, t_shell *shell);

int		apply_redirections(t_cmd *cmd, t_redirection *redir);
char	**create_exec_env(t_env *env, t_env *l_env);
int		is_whitespace(char c);
int		add_shell_vars(t_shell *shell, t_env *cmd_vars);

void	cleanup_shell(t_shell *shell);
void	free_redirection(t_redirection *r);
void	free_env(t_env *env);
void	ft_execve(t_cmd *cmd, t_shell *shell);
void	ftf_execve(char *path, t_cmd *cmd, char **exec_env, t_shell *shell);
void	error_handler_execve(int code, t_cmd *cmd, t_shell *shell, char **e_v);
char	*search_var(t_shell *shell, char *var_name);
void	init_pipe(t_pipex *pipex, t_shell *shell);

void	missing_path_exit(t_cmd *cmd, t_shell *shell, char **array, char *path);

int		special_exit(t_shell *shell);
int		exec_command_type(t_shell *shell);
int		exec_single_cmd(t_shell *shell);
int		start_exec(t_shell *shell);

char	*remove_quotes(t_token *token, int *quote);
int		print_error(char *str, int err_code);

int		create_token_node(t_shell *shell, t_token **current, char *str);
int		check_valid_input(t_shell *shell, char *input);

void	free_ucommands(t_cmd *cmd);
void	free_cmd_content(t_cmd *cmd);
#endif
