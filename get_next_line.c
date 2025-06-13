#include <unistd.h>
#include <stdlib.h>

static int	has_newline(char *s)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == '\n')
			return (1);
		s++;
	}
	return (0);
}

static int	ft_strlen(char *s)
{
	int i = 0;
	while (s && s[i])
		i++;
	return (i);
}

static char	*ft_strjoin(char *s1, char *s2)
{
	int i = 0, j = 0;
	int len = ft_strlen(s1) + ft_strlen(s2);
	char *res = malloc(len + 1);
	if (!res)
		return (NULL);
	while (s1 && s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
		res[i++] = s2[j++];
	res[i] = '\0';
	free(s1);
	return (res);
}

static char	*extract_line(char *stash)
{
	int i = 0;
	char *line;

	if (!stash || !stash[0])
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	line = malloc(stash[i] == '\n' ? i + 2 : i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*clean_stash(char *stash)
{
	int i = 0, j = 0;
	char *new_stash;

	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	new_stash = malloc(ft_strlen(stash) - i + 1);
	if (!new_stash)
		return (NULL);
	i++;
	while (stash[i])
		new_stash[j++] = stash[i++];
	new_stash[j] = '\0';
	free(stash);
	return (new_stash);
}

char	*get_next_line(int fd)
{
	static char *stash;
	char buffer[BUFFER_SIZE + 1];
	char *line;
	int bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	bytes = 1;
	while (!has_newline(stash) && bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
		{
			free(stash);
			stash = NULL;
			return (NULL);
		}
		buffer[bytes] = '\0';
		stash = ft_strjoin(stash, buffer);
	}
	line = extract_line(stash);
	stash = clean_stash(stash);
	return (line);
}
