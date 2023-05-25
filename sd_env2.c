#include "shell.h"

/**
 * copy_info - copies info to create
 * a new env or alias
 * @name: name (env or alias)
 * @value: value (env or alias)
 *
 * Return: new env or alias.
 */
char *copy_info(char *name, char *value)
{
	char *new;
	int l_name, l_value, l;

	l_name = _strlen(name);
	l_value = _strlen(value);
	l = l_name + l_value + 2;
	new = malloc(sizeof(char) * (l));
	_strcpy(new, name);
	_strcat(new, "=");
	_strcat(new, value);
	_strcat(new, "\0");

	return (new);
}

/**
 * set_env - sets an environment variable
 *
 * @name: name of the environment variable
 * @value: value of the environment variable
 * @datash: data structure (environ)
 * Return: no return
 */
void set_env(char *name, char *value, data_shell *datash)
{
	int s;
	char *var_env, *name_env;

	for (s = 0; datash->_environ[s]; s++)
	{
		var_env = _strdup(datash->_environ[s]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, name) == 0)
		{
			free(datash->_environ[s]);
			datash->_environ[s] = copy_info(name_env, value);
			free(var_env);
			return;
		}
		free(var_env);
	}

	datash->_environ = _reallocdp(datash->_environ, s, sizeof(char *) * (s + 2));
	datash->_environ[s] = copy_info(name, value);
	datash->_environ[s + 1] = NULL;
}

/**
 * _setenv - compares env variables names
 * with the name passed.
 * @datash: data relevant (env name and env value)
 *
 * Return: 1 on success.
 */
int _setenv(data_shell *datash)
{

	if (datash->args[1] == NULL || datash->args[2] == NULL)
	{
		get_error(datash, -1);
		return (1);
	}

	set_env(datash->args[1], datash->args[2], datash);

	return (1);
}

/**
 * _unsetenv - deletes a environment variable
 *
 * @datash: data relevant (env name)
 *
 * Return: 1 on success.
 */
int _unsetenv(data_shell *datash)
{
	char **realloc_environ;
	char *var_env, *name_env;
	int s, x, d;

	if (datash->args[1] == NULL)
	{
		get_error(datash, -1);
		return (1);
	}
	d = -1;
	for (s = 0; datash->_environ[s]; s++)
	{
		var_env = _strdup(datash->_environ[s]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, datash->args[1]) == 0)
		{
			d = s;
		}
		free(var_env);
	}
	if (d == -1)
	{
		get_error(datash, -1);
		return (1);
	}
	realloc_environ = malloc(sizeof(char *) * (s));
	for (s = x = 0; datash->_environ[s]; s++)
	{
		if (s != d)
		{
			realloc_environ[x] = datash->_environ[s];
			x++;
		}
	}
	realloc_environ[x] = NULL;
	free(datash->_environ[d]);
	free(datash->_environ);
	datash->_environ = realloc_environ;
	return (1);
}
