#include "shell.h"

/**
 * _strcat - concatenate two strings
 * @dest: char pointer the dest of the copied str
 * @src: const char pointer the source of str
 * Return: the dest
 */
char *_strcat(char *dest, const char *src)
{
	int s;
	int x;

	for (s = 0; dest[s] != '\0'; s++)
		;

	for (x = 0; src[x] != '\0'; x++)
	{
		dest[s] = src[x];
		s++;
	}

	dest[s] = '\0';
	return (dest);
}
/**
 * *_strcpy - Copies the string pointed to by src.
 * @dest: Type char pointer the dest of the copied str
 * @src: Type char pointer the source of str
 * Return: the dest.
 */
char *_strcpy(char *dest, char *src)
{

	size_t d;

	for (d = 0; src[d] != '\0'; d++)
	{
		dest[d] = src[d];
	}
	dest[d] = '\0';

	return (dest);
}
/**
 * _strcmp - Function that compares two strings.
 * @s1: type str compared
 * @s2: type str compared
 * Return: Always 0.
 */
int _strcmp(char *s1, char *s2)
{
	int s;

	for (s = 0; s1[s] == s2[s] && s1[s]; s++)
		;

	if (s1[s] > s2[s])
		return (1);
	if (s1[s] < s2[s])
		return (-1);
	return (0);
}
/**
 * _strchr - locates a character in a string,
 * @s: string.
 * @c: character.
 * Return: the pointer to the first occurrence of the character c.
 */
char *_strchr(char *s, char c)
{
	unsigned int i = 0;

	for (; *(s + i) != '\0'; i++)
		if (*(s + i) == c)
			return (s + i);
	if (*(s + i) == c)
		return (s + i);
	return ('\0');
}
/**
 * _strspn - gets the length of a prefix substring.
 * @s: initial segment.
 * @accept: accepted bytes.
 * Return: the number of accepted bytes.
 */
int _strspn(char *s, char *accept)
{
	int y, x, bool;

	for (y = 0; *(s + y) != '\0'; y++)
	{
		bool = 1;
		for (x = 0; *(accept + x) != '\0'; x++)
		{
			if (*(s + y) == *(accept + x))
			{
				bool = 0;
				break;
			}
		}
		if (bool == 1)
			break;
	}
	return (y);
}
