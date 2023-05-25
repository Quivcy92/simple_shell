#include "shell.h"

/**
 * cmp_env_name - compares env variables names
 * with the name passed.
 * @nenv: name of the environment variable
 * @name: name passed
 *
 * Return: 0 if are not equal. Another value if they are.
 */
int cmp_env_name(const char *nenv, const char *name)
{
	int s;

	for (s = 0; nenv[s] != '='; s++)
	{
		if (nenv[s] != name[s])
		{
			return (0);
		}
	}

	return (s + 1);
}

/**
 * _getenv - get an environment variable
 * @name: name of the environment variable
 * @_environ: environment variable
 *
 * Return: value of the environment variable if is found.
 * In other case, returns NULL.
 */
char *_getenv(const char *name, char **_environ)
{
	char *ptr_env;
	int s, mov;

	/* Initialize ptr_env value */
	ptr_env = NULL;
	mov = 0;
	/* Compare all environment variables */
	/* environ is declared in the header file */
	for (s = 0; _environ[s]; s++)
	{
		/* If name and env are equal */
		mov = cmp_env_name(_environ[s], name);
		if (mov)
		{
			ptr_env = _environ[s];
			break;
		}
	}

	return (ptr_env + mov);
}

/**
 * _env - prints the evironment variables
 *
 * @datash: data relevant.
 * Return: 1 on success.
 */
int _env(data_shell *datash)
{
	int s, x;

	for (s = 0; datash->_environ[s]; s++)
	{

		for (x = 0; datash->_environ[s][x]; x++)
			;

		write(STDOUT_FILENO, datash->_environ[s], x);
		write(STDOUT_FILENO, "\n", 1);
	}
	datash->status = 0;

	return (1);
}
