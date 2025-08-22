#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER_SIZE (10000 + 1)

int ft_strncmp(char *s1, char *s2, int n)
{
	int i = 0;
	while (i < n && s1[i] == s2[i])
		i++;
	if (i == n)
		return (1);
	return (0);
}

int main(int ac, char **av)
{
	if (ac != 2 || av[1] == NULL || strlen(av[1]) == 0)
		return (1);

	char *buff = (char *)malloc(MAX_BUFFER_SIZE);

	if (!buff)
	{
		fprintf(stderr, "Error: ");
		perror("");
		return (1);
	}

	char *search_str = av[1];
	int search_len = strlen(av[1]);
	int buff_idx = 0;
	char current_char;
	ssize_t bytes;

	while ((bytes = read(STDIN_FILENO, &current_char, 1)) > 0)
	{
		if (buff_idx >= MAX_BUFFER_SIZE - 1)
			return (1);
		buff[buff_idx++] = current_char;
	}

	if (bytes == -1)
	{
		fprintf(stderr, "Error: ");
		perror("");
		return (1);
	}

	int process_idx = 0;
	while (buff[process_idx] != '\0')
	{
		if (process_idx + search_len <= buff_idx && ft_strncmp(&buff[process_idx], search_str, search_len))
		{
			for (int i = 0; i < search_len; i++)
				write(STDOUT_FILENO, "*", 1);
			process_idx += search_len;
		}
		else
		{
			write(STDOUT_FILENO, &buff[process_idx], 1);
			process_idx++;
		}
	}

	free(buff);

	return (0);
}
