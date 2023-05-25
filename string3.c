#include "shell.h"

/**
 * rev_string - reverses a string.
 * @s: input string.
 * Return: no return.
 */
void rev_string(char *s)
{
	int count = 0, d, x;
	char *str, temp;

	while (count >= 0)
	{
		if (s[count] == '\0')
			break;
		count++;
	}
	str = s;

	for (d = 0; d < (count - 1); d++)
	{
		for (x = d + 1; x > 0; x--)
		{
			temp = *(str + x);
			*(str + x) = *(str + (x - 1));
			*(str + (x - 1)) = temp;
		}
	}
}
