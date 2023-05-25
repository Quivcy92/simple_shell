#include "shell.h"

/**
 * check_env - checks if the typed variable is an env variable
 *
 * @h: head of linked list
 * @in: input string
 * @data: data structure
 * Return: no return
 */
void check_env(r_var **h, char *in, data_shell *data)
{
	int row, chr, x, lval;
	char **_envr;

	_envr = data->_environ;
	for (row = 0; _envr[row]; row++)
	{
		for (x = 1, chr = 0; _envr[row][chr]; chr++)
		{
			if (_envr[row][chr] == '=')
			{
				lval = _strlen(_envr[row] + chr + 1);
				add_rvar_node(h, x, _envr[row] + chr + 1, lval);
				return;
			}

			if (in[x] == _envr[row][chr])
				x++;
			else
				break;
		}
	}

	for (x = 0; in[x]; x++)
	{
		if (in[x] == ' ' || in[x] == '\t' || in[x] == ';' || in[x] == '\n')
			break;
	}

	add_rvar_node(h, x, NULL, 0);
}

/**
 * check_vars - check if the typed variable is $$ or $?
 *
 * @h: head of the linked list
 * @in: input string
 * @st: last status of the Shell
 * @data: data structure
 * Return: no return
 */
int check_vars(r_var **h, char *in, char *st, data_shell *data)
{
	int s, lst, lpd;

	lst = _strlen(st);
	lpd = _strlen(data->pid);

	for (s = 0; in[s]; s++)
	{
		if (in[s] == '$')
		{
			if (in[s + 1] == '?')
				add_rvar_node(h, 2, st, lst), s++;
			else if (in[s + 1] == '$')
				add_rvar_node(h, 2, data->pid, lpd), s++;
			else if (in[s + 1] == '\n')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[s + 1] == '\0')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[s + 1] == ' ')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[s + 1] == '\t')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[s + 1] == ';')
				add_rvar_node(h, 0, NULL, 0);
			else
				check_env(h, in + s, data);
		}
	}

	return (s);
}

/**
 * replaced_input - replaces string into variables
 *
 * @head: head of the linked list
 * @input: input string
 * @new_input: new input string (replaced)
 * @nlen: new length
 * Return: replaced string
 */
char *replaced_input(r_var **head, char *input, char *new_input, int nlen)
{
	r_var *indx;
	int s, x, d;

	indx = *head;
	for (x = s = 0; s < nlen; s++)
	{
		if (input[x] == '$')
		{
			if (!(indx->len_var) && !(indx->len_val))
			{
				new_input[s] = input[x];
				x++;
			}
			else if (indx->len_var && !(indx->len_val))
			{
				for (d = 0; d < indx->len_var; d++)
					x++;
				s--;
			}
			else
			{
				for (d = 0; d < indx->len_val; d++)
				{
					new_input[s] = indx->val[d];
					s++;
				}
				x += (indx->len_var);
				s--;
			}
			indx = indx->next;
		}
		else
		{
			new_input[s] = input[x];
			x++;
		}
	}

	return (new_input);
}

/**
 * rep_var - calls functions to replace string into vars
 *
 * @input: input string
 * @datash: data structure
 * Return: replaced string
 */
char *rep_var(char *input, data_shell *datash)
{
	r_var *head, *indx;
	char *status, *new_input;
	int olen, nlen;

	status = aux_itoa(datash->status);
	head = NULL;

	olen = check_vars(&head, input, status, datash);

	if (head == NULL)
	{
		free(status);
		return (input);
	}

	indx = head;
	nlen = 0;

	while (indx != NULL)
	{
		nlen += (indx->len_val - indx->len_var);
		indx = indx->next;
	}

	nlen += olen;

	new_input = malloc(sizeof(char) * (nlen + 1));
	new_input[nlen] = '\0';

	new_input = replaced_input(&head, input, new_input, nlen);

	free(input);
	free(status);
	free_rvar_list(&head);

	return (new_input);
}
