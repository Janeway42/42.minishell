#include <unistd.h>
#include <stdio.h>
#include <termios.h>
// testing what ttyname function does
// it apparently returns the name of the terminal in this case /dev/tty002
int main()
{
	char *s = ttyname(1);
	printf("%s\n", s);
	return (0);
}

