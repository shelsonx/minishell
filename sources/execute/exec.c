/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: progerio <progerio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:51:09 by sjhony-x          #+#    #+#             */
/*   Updated: 2023/03/08 16:49:06 by progerio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_input_cmd(int position)
{
	char			*num_str;
	static char		index_cmd[128];

	ft_memset(index_cmd, 0, 128);
	num_str = ft_itoa(position);
	ft_strcpy(index_cmd, num_str);
	free(num_str);
	return (index_cmd);
}

void	exec_only_one_command(t_data *data, t_parser *parser_data)
{
	char	*index_cmd;
	int		fd_in;
	int		fd_out;

	data->pipeline = get_pipeline(data, parser_data, 0);
	expander(data->pipeline, parser_data->builtin_vars, data);
	remove_quotes(data->pipeline);
	index_cmd = get_input_cmd(0);
	if ((has_redirect(parser_data, "<", index_cmd)
			&& has_redirect(parser_data, ">", index_cmd))
		|| (has_redirect(parser_data, "<", index_cmd)
			&& has_redirect(parser_data, ">>", index_cmd)))
	{
		if (!set_fds(parser_data, index_cmd, &fd_in, &fd_out))
			return ;
	}
	else
	{
		if (!set_in(parser_data, index_cmd, &fd_in))
			return ;
		if (!set_out(parser_data, index_cmd, &fd_out))
			return ;
	}
	exec_one_command(data, fd_in, fd_out);
}

void	exec_two_commands(t_data *data,
	t_parser *parser_data, int total_commands)
{
	char	*index_cmd;
	int		fd_in;
	int		fd_out;

	index_cmd = get_input_cmd(0);
	data->pipeline = get_pipeline(data, parser_data, 0);
	expander(data->pipeline, parser_data->builtin_vars, data);
	remove_quotes(data->pipeline);
	data->fds = create_pipes(1);
	fd_in = get_fd_in(parser_data, index_cmd);
	fd_out = get_fd_out(parser_data, index_cmd);
	if (fd_in != INVALID_FD && fd_out != INVALID_FD)
		exec_first_command(data, fd_in, fd_out);
	data->pipeline = get_pipeline(data, parser_data, 1);
	expander(data->pipeline, parser_data->builtin_vars, data);
	remove_quotes(data->pipeline);
	index_cmd = get_input_cmd(1);
	fd_in = get_fd_in(parser_data, index_cmd);
	if (fd_in == -1)
		fd_in = data->fds[0][0];
	index_cmd = get_input_cmd(total_commands -1);
	fd_out = get_fd_out(parser_data, index_cmd);
	exec_last_command(data, fd_in, fd_out);
}

void	exec_serveral_commands(t_data *data,
		t_parser *parser_data, int total_commands)
{
	char	*index_cmd;
	int		fd_in;

	data->pipeline = get_pipeline(data, parser_data, 0);
	expander(data->pipeline, parser_data->builtin_vars, data);
	remove_quotes(data->pipeline);
	data->fds = create_pipes(total_commands -1);
	index_cmd = get_input_cmd(0);
	exec_first_command(data,
		get_fd_in(parser_data, index_cmd),
		get_fd_out(parser_data, index_cmd));
	exec_middles_commands(data, parser_data, total_commands -2);
	ft_free_tab(data->pipeline);
	data->pipeline = NULL;
	data->pipeline = get_pipeline(data, parser_data, total_commands -1);
	expander(data->pipeline, parser_data->builtin_vars, data);
	remove_quotes(data->pipeline);
	index_cmd = get_input_cmd(total_commands -1);
	fd_in = get_fd_in(parser_data, index_cmd);
	if (fd_in == -1)
		fd_in = data->fds[total_commands -2][0];
	index_cmd = get_input_cmd(total_commands -1);
	exec_last_command(data, fd_in, get_fd_out(parser_data, index_cmd));
}

int	execute(t_parser *parser_data)
{
	t_data		data;
	int			total_commands;
	static int	exit_status;

	data.fds = NULL;
	data.pipeline = NULL;
	data.exit_status = &exit_status;
	data.builtin_vars = parser_data->builtin_vars;
	data.parser_data = parser_data;
	total_commands = parser_data->index;
	parser_data->data = &data;
	set_data(&data);
	handler_cmds(&data, parser_data, total_commands);
	if (total_commands > 0)
		exit_program(&data);
	wait_all_pids(parser_data, total_commands);
	return (0);
}
