h38673
s 00001/00001/00153
d D 1.3 00/02/28 17:01:13 brucec 4 3
c Make char *id a static pointer so that getopt.o can link with
c stdlib.so if getopt() is already provided there.
cC
cHrx7
cK47204
cZ-05:00
e
s 00002/00002/00152
d D 1.2 00/02/27 09:27:12 staelin 3 2
c fix to get getopt.c to compile in lmbench environment
cC
cK46524
e
s 00154/00000/00000
d D 1.1 00/02/02 14:09:30 staelin 2 1
cC
cF1
cK47290
cO-rw-r--r--
e
s 00000/00000/00000
d D 1.0 00/02/02 14:09:30 staelin 1 0
c BitKeeper file /users/staelin/src/LMbench/src/getopt.c
cBlm@lm.bitmover.com|ChangeSet|20000131225335|47351|--LMBENCH--
cHhpli8.hpli.hpl.hp.com
cK24836
cPsrc/getopt.c
cR7b02d3d0190880ea
cV4
cX0x21
cZ+02:00
e
u
U
f e 0
f x 0x21
t
T
I 2
/*
 * Copyright (c) 1997 L.W.McVoy 
 *
 * SGI's fucking getopt doesn't follow GNU's reset policy.  Isn't having
 * N versions of Unix a great thing for the world?  I'm gonna move to NT
 * if these assholes don't get their act together.
 *
 * This version handles
 *
 *	-	(leaves it and returns)
 *	-a
 *	-abcd
 *	-r <arg>
 *	-r<arg>
 *	-abcr <arg>
 *	-abcr<arg>
 *	-r<arg> -R<arg>, etc.
 *
 * A special form is "d|" instead of "d:".  This means the arg has to be
 * right next to the option.  
 * Another special form is "d;".  This means the option must be right next
 * to the option letter and can not be blank.
 */
D 3
#include "sccs.h"
WHATSTR("@(#)getopt.c 1.9");
E 3
I 3
#include "bench.h"
D 4
char *id = "%@%";
E 4
I 4
static char *id = "%@%";
E 4
E 3

int	optopt;		/* option that is in error, if we return an error */
int     optind;		/* next arg in argv we process */
char   *optarg;		/* argument to an option */
static int n;

int
getopt(int ac, char **av, char *opts)
{
	char	*t;

	if (!optind) {
		optind = 1;
		n = 1;
	}
	debug((stderr, "GETOPT ind=%d n=%d arg=%s av[%d]='%s'\n",
	    optind, n, optarg ? optarg : "", optind, av[optind]));

	if ((optind >= ac) || (av[optind][0] != '-') || !av[optind][1]) {
		return (EOF);
	}

	assert(av[optind][n]);
	for (t = (char *)opts; *t; t++) {
		if (*t == av[optind][n]) {
			break;
		}
	}
	if (!*t) { 
		optopt = av[optind][n];
		debug((stderr, "\tran out of option letters\n"));
		return ('?');
	}

	/* OK, we found a legit option, let's see what to do with it.
	 * If it isn't one that takes an option, just advance and return.
	 */
	if (t[1] != ':' && t[1] != '|' && t[1] != ';') {
		if (!av[optind][n+1]) {
			optind++;
			n = 1;
		} else {
			n++;
		}
		debug((stderr, "\tLegit singleton %c\n", *t));
		return (*t);
	}

	/* got one with an option, see if it is cozied up to the flag */
	if (av[optind][n+1]) {
		if (av[optind][n+1]) {
			optarg = &av[optind][n+1];
		} else {
			optarg = 0;
		}
		optind++;
		n = 1;
		debug((stderr, "\t%c with %s\n", *t, optarg));
		return (*t);
	} 
	
	/* If it was not there, and it is optional, OK */
	if (t[1] == '|') {
		optarg = 0;
		optind++;
		n = 1;
		debug((stderr, "\t%c without arg\n", *t));
		return (*t);
	}

	/* was it supposed to be there? */
	if (t[1] == ';') {
		optarg = 0;
		optind++;
		optopt = *t;
		debug((stderr, "\twanted another word\n"));
		return ('?');
	}

	/* Nope, there had better be another word. */
	if ((optind + 1 == ac) || (av[optind+1][0] == '-')) {
		optopt = av[optind][n];
		debug((stderr, "\twanted another word\n"));
		return ('?');
	}
	optarg = av[optind+1];
	optind += 2;
	n = 1;
	debug((stderr, "\t%c with arg %s\n", *t, optarg));
	return (*t);
}

#ifdef	TEST

/* XXX a.out -y file */
main(int ac, char **av)
{
	extern	char *optarg;
	extern	int optind;
	char	*comment = 0;
	int	c;

	while ((c = getopt(ac, av, "fnpsx:y|")) != -1) {
		switch (c) {
		    case 'f': 
		    case 'n': 
		    case 'p': 
		    case 's': 
		    	printf("Got option %c\n", c);
			break;
		    case 'x':
		    case 'y':
		   	 comment = optarg; 
			 printf("Got optarg %s with -%c\n", comment, c);
			 break;
		    case '?':
			fprintf(stderr, "bad option %c\n", optopt);
			break;
		    default:
			fprintf(stderr, "unknown ret %c\n", c);
			break;
	    	}
	}
	while (av[optind]) {
		printf("av[%d] = %s\n", optind, av[optind++]);
	}
	exit(0);
}
#endif
E 2
I 1
E 1
