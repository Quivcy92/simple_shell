#include "shell.h"

/**
 * get_builtin - builtin that pais the command in the arg
 * @cmd: command
 * Return: function pointer of the builtin command
 */
int (*get_builtin(char *cmd))(data_shell *)
{
	builtin_t builtin[] = {
		{ "env", _env },
		{ "exit", exit_shell },
		{ "setenv", _setenv },
		{ "unsetenv", _unsetenv },
		{ "cd", cd_shell },
		{ "help", get_help },
		{ NULL, NULL }
	};
	int s;

	for (s = 0; builtin[s].name; s++)
	{
		if (_strcmp(builtin[s].name, cmd) == 0)
			break;
	}

	return (builtin[s].f);
}
