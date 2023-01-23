Program name libftprintf.a
Turn in files Makefile, *.h, */*.h, *.c, */*.c
Makefile NAME, all, clean, fclean, re
External functs. malloc, free, write,
va_start, va_arg, va_copy, va_end
Libft authorized Yes
Description Write a library that contains ft_printf(), a
function that will mimic the original printf()

make me this code for recode the function printf() with these requirements :

You have to recode the printf() function from libc.
The prototype of ft_printf() is:
int ft_printf(const char *, ...);
Here are the requirements:
• Don’t implement the buffer management of the original printf().
• Your function has to handle the following conversions: cspdiuxX%
• Your function will be compared against the original printf().
• You must use the command ar to create your library.
Using the libtool command is forbidden.
• Your libftprintf.a has to be created at the root of your repository.

You have to implement the following conversions:
• %c Prints a single character.
• %s Prints a string (as defined by the common C convention).
• %p The void * pointer argument has to be printed in hexadecimal format.
• %d Prints a decimal (base 10) number.
• %i Prints an integer in base 10.
• %u Prints an unsigned decimal (base 10) number.
• %x Prints a number in hexadecimal (base 16) lowercase format.
• %X Prints a number in hexadecimal (base 16) uppercase format.
• %% Prints a percent sign.

Makefile:

NAME = libftprintf.a

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

and the files.h and the function .c:

ft_printf.h:

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdlib.h>
# include <stdarg.h>

int ft_printf(const char *format, ...);

#endif

ft_printf.c:

#include "ft_printf.h"

int ft_printf(const char *format, ...) {
  va_list args;
  int i;
  int ret;
  
  va_start(args, format);
  
  i = 0;
  ret = 0;
  while (format && format[i]) {
    if (format[i] == '%') {
      i++;
      if (format[i] == 'c') {
        ret += ft_print_char(va_arg(args, int));
      } else if (format[i] == 's') {
        ret += ft_print_str(va_arg(args, char *));
      } else if (format[i] == 'p') {
        ret += ft_print_ptr(va_arg(args, void *));
      } else if (format[i] == 'd' || format[i] == 'i') {
        ret += ft_print_int(va_arg(args, int));
      } else if (format[i] == 'u') {
        ret += ft_print_uint(va_arg(args, unsigned int));
      } else if (format[i] == 'x') {
        ret += ft_print_hex(va_arg(args, unsigned int), 0);
      } else if (format[i] == 'X') {
        ret += ft_print_hex(va_arg(args, unsigned int), 1);
      } else if (format[i] == '%') {
        ret += ft_print_char('%');
      }
    } else {
      ret += ft_print_char(format[i]);
    }
    i++;
  }
  va_end(args);
  return (ret);
}

ft_print_char.c:

#include "ft_printf.h"

int ft_print_char(char c) {
  write(1, &c, 1);
  return (1);
}

ft_print_str.c:

#include "ft_printf.h"

int ft_print_str(char *s) {
  int i;
  
  i = 0;
  if (s == NULL) {
    write(1, "(null)", 6);
    return (6);
  }
  while (s[i]) {
    write(1, &s[i], 1);
    i++;
  }
  return (i);
}

ft_print_ptr.c:

#include "ft_printf.h"

int ft_print_ptr(void *p) {
  int i;
  unsigned long ptr;
  char *str;
  char *hex;
  
  ptr = (unsigned long)p;
  str = malloc(sizeof(char) * 17);
  hex = "0123456789abcdef";
  str[0] = '0';
  str[1] = 'x';
  i = 15;
  while (ptr > 0) {
    str[i] = hex[ptr % 16];
    ptr /= 16;
    i--;
  }
  write(1, str, 17);
  free(str);
  return (17);
}

ft_print_int.c:

#include "ft_printf.h"

int ft_print_int(int n) {
  int len;
  int tmp;
  char c;
  
  len = 0;
  if (n == 0) {
    write(1, "0", 1);
    return (1);
  }
  if (n < 0) {
    n *= -1;
    write(1, "-", 1);
    len++;
  }
  tmp = n;
  while (tmp > 0) {
    tmp /= 10;
    len++;
  }
  tmp = len;
  while (tmp > 0) {
    c = (n / ft_pow(10, (tmp - 1))) + '0';
    n %= ft_pow(10, (tmp - 1));
    write(1, &c, 1);
    tmp--;
  }
  return (len);
}

ft_print_uint.c:

#include "ft_printf.h"

int ft_print_uint(unsigned int n) {
  int len;
  int tmp;
  char c;
  
  len = 0;
  if (n == 0) {
    write(1, "0", 1);
    return (1);
  }
  tmp = n;
  while (tmp > 0) {
    tmp /= 10;
    len++;
  }
  tmp = len;
  while (tmp > 0) {
    c = (n / ft_pow(10, (tmp - 1))) + '0';
    n %= ft_pow(10, (tmp - 1));
    write(1, &c, 1);
    tmp--;
  }
  return (len);
}


ft_print_hex.c:

#include "ft_printf.h"

int ft_print_hex(unsigned int n, int upper) {
  int len;
  int tmp;
  char c;
  char *hex;
  
  len = 0;
  if (n == 0) {
    write(1, "0", 1);
    return (1);
  }
  if (upper)
    hex = "0123456789ABCDEF";
  else
    hex = "0123456789abcdef";
  tmp = n;
  while (tmp > 0) {
    tmp /= 16;
    len++;
  }
  tmp = len;
  while (tmp > 0) {
    c = hex[n / ft_pow(16, (tmp - 1))];
    n %= ft_pow(16, (tmp - 1));
    write(1, &c, 1);
    tmp--;
  }
  return (len);
}

ft_pow.c:

#include "ft_printf.h"

int ft_pow(int n, int pow) {
  if (pow == 0)
    return (1);
  return (n * ft_pow(n, pow - 1));
}

explain me line by line 

ft_printf.h:
This is the header file for the ft_printf() function. It includes the necessary libraries for the function, as well as a function prototype for ft_printf().

ft_printf.c:
This is the main implementation of the ft_printf() function, which is responsible for parsing the format string and dispatching the appropriate functions for each conversion type. It takes a variable number of arguments and uses a va_list to access them. It then iterates through the format string, checking for the '%' character, which indicates that a conversion needs to be done. Depending on what follows the '%' character, a different conversion function is called.

ft_print_char.c:
This function is responsible for printing a single character. It takes a single argument, which is the character to print, and then uses the write() function to print the character to stdout. It returns the number of characters printed, which is always 1.

ft_print_str.c:
This function is responsible for printing a string. It takes a single argument, which is the string to print, and then uses the write() function to print the string to stdout. It returns the number of characters printed.

ft_print_ptr.c:
This function is responsible for printing a void pointer in hexadecimal format. It takes a single argument, which is the pointer to print, and then uses the write() function to print the pointer to stdout. It returns the number of characters printed, which is always 17.

ft_print_int.c:
This function is responsible for printing an integer in decimal format. It takes a single argument, which is the integer to print, and then uses the write() function to print the integer to stdout. It returns the number of characters printed.

ft_print_uint.c:
This function is responsible for printing an unsigned integer in decimal format. It takes a single argument, which is the unsigned integer to print, and then uses the write() function to print the integer to stdout. It returns the number of characters printed.

ft_print_hex.c:
This function is responsible for printing an unsigned integer in hexadecimal format. It takes two arguments, the first is the unsigned integer to print, and the second is a flag indicating whether the output should be in lowercase or uppercase format
