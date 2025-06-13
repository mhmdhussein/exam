#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>

static int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

static int	ft_putstr(char *s)
{
	int i = 0;
	if (!s)
		return (write(1, "(null)", 6));
	while (s[i])
		write(1, &s[i++], 1);
	return (i);
}

static int	ft_putnbr(int n)
{
	long	nb = n;
	int		len = 0;
	if (nb < 0)
	{
		len += ft_putchar('-');
		nb = -nb;
	}
	if (nb >= 10)
		len += ft_putnbr(nb / 10);
	len += ft_putchar(nb % 10 + '0');
	return (len);
}

static int	ft_puthex(unsigned int n)
{
	char *hex = "0123456789abcdef";
	int len = 0;

	if (n >= 16)
		len += ft_puthex(n / 16);
	len += ft_putchar(hex[n % 16]);
	return (len);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i = 0;
	int		len = 0;

	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			i++;
			if (format[i] == 's')
				len += ft_putstr(va_arg(args, char *));
			else if (format[i] == 'd')
				len += ft_putnbr(va_arg(args, int));
			else if (format[i] == 'x')
				len += ft_puthex(va_arg(args, unsigned int));
		}
		else
			len += ft_putchar(format[i]);
		i++;
	}
	va_end(args);
	return (len);
}
