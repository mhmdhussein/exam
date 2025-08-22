#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int ft_strlen(char *s)
{
	int i = 0;
	while (s[i])
		i++;
	return (i);
}

int ft_factorial(int n)
{
	if (n <= 1)
		return 1;
	return (n * ft_factorial(n - 1));
}

void ft_strcpy(char *d, char *s)
{
	int i;
	for (i = 0; s[i]; i++)
		d[i] = s[i];
	d[i] = '\0';
}

void generate_all_perms(int current_index, int size, char *s, char **all_perms, int *perms_row_index)
{
	if (current_index == size)
	{
		ft_strcpy(all_perms[(*perms_row_index)], s);
		(*perms_row_index)++;
		return ;
	}
	for (int i = current_index; i < size; i++)
	{
		char temp = s[i];
		s[i] = s[current_index];
		s[current_index] = temp;
		generate_all_perms(current_index + 1, size, s, all_perms, perms_row_index);
		temp = s[i];
		s[i] = s[current_index];
		s[current_index] = temp;
	}
}

int ft_strcmp(char *s1, char *s2)
{
	int i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

void sort_perms(char **all_perms, int total_perms)
{
	for (int i = 0; i < total_perms; i++)
	{
		for (int j = i + 1; j < total_perms; j++)
		{
			if (ft_strcmp(all_perms[i], all_perms[j]) > 0)
			{
				char *temp = all_perms[i];
				all_perms[i] = all_perms[j];
				all_perms[j] = temp;
			}
		}
	}
}

void print_perms(char **all_perms, int total_perms)
{
	for (int i = 0; i < total_perms; i++)
		puts(all_perms[i]);
}

int main(int ac, char **av)
{
	if (ac != 2)
	{
		write(1, "\n", 1);
		return (1);
	}
	char *s = av[1];
	int size = ft_strlen(s);
	if (size == 0)
	{
		write(1, "\n", 1);
		return (1);
	}
	int total_perms = ft_factorial(size);

	char **all_perms = malloc(sizeof(char *) * total_perms);

	for (int i = 0; i < total_perms; i++)
		all_perms[i] = calloc(size + 1, sizeof(char));

	int perms_row_index = 0;
	int current_index = 0;
	generate_all_perms(current_index, size, s, all_perms, &perms_row_index);
	sort_perms(all_perms, total_perms);
	print_perms(all_perms, total_perms);
	return (0);
}
