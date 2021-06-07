#include "stdio_impl.h"

extern void eapp_print(const char*s, ...);

// Penglai stdout
int puts(const char *s)
{
	int r;
	eapp_print(s);
	return r;
	// FLOCK(stdout);
	// r = -(fputs(s, stdout) < 0 || putc_unlocked('\n', stdout) < 0);
	// FUNLOCK(stdout);
	// return r;
}
