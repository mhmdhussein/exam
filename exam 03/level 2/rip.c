#include <stdio.h>
#include <unistd.h>

int ft_strlen(char *s)
{
	int i = 0;
	while (s[i])
		i++;
	return (i);
}

int min_to_remove(char *s)
{
	int open = 0, close = 0;
	for (int i = 0; s[i]; i++)
	{
		if (s[i] == '(')
			open++;
		else if (s[i] == ')')
		{
			if (open > 0)
				open--;
			else
				close++;
		}
	}
	return (open + close);
}

void solve(int current_index, int total_to_remove, int num_removed, char *s)
{
	if (current_index == ft_strlen(s))
	{
		if (num_removed == total_to_remove && !min_to_remove(s))
			puts(s);
		return ;
	}
	if (num_removed > total_to_remove)
		return ;
	if (s[current_index] == '(' || s[current_index] == ')')
	{
		char temp = s[current_index];
		s[current_index] = ' ';
		solve(current_index + 1, total_to_remove, num_removed + 1, s);
		s[current_index] = temp;
		solve(current_index + 1, total_to_remove, num_removed, s);
	}
	else
		solve(current_index + 1, total_to_remove, num_removed, s);

}

int main(int ac, char **av)
{
	if (ac != 2)
	{
		write(1, "\n", 1);
		return (0);
	}
	char *s = av[1];
	if (!min_to_remove(s))
	{
		puts(s);
		return (0);
	}
	solve(0, min_to_remove(s), 0, s);
	return (0);
}
