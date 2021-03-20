h34077
s 00001/00001/00170
d D 1.11 97/06/15 22:38:58 lm 12 11
c lint
cC
cK60593
cSAlpha2.11
e
s 00000/00002/00171
d D 1.10 97/06/12 21:30:06 lm 11 10
c bench.h
cK60363
cZ-07:00
e
s 00007/00006/00166
d D 1.9 96/11/11 03:36:51 lm 10 9
c Auto adjusting changes.
cK63670
e
s 00008/00005/00164
d D 1.8 96/11/08 19:59:23 lm 9 8
c gcc -Wall cleanup.
cK61696
cZ-08:00
e
s 00000/00001/00169
d D 1.7 96/05/30 00:33:07 lm 8 7
c no what strings
cK56533
cZ-07:00
e
s 00000/00001/00170
d D 1.6 95/03/10 18:22:25 lm 7 6
c lint
cK58604
e
s 00002/00000/00169
d D 1.5 95/02/14 11:01:32 lm 6 5
c *** empty log message ***
cK59751
e
s 00001/00001/00168
d D 1.4 94/11/25 16:36:44 lm 5 4
c dir
cK58206
e
s 00005/00001/00164
d D 1.3 94/11/25 15:19:52 lm 4 3
c chdir.
cK57368
e
s 00002/00000/00163
d D 1.2 94/11/20 16:59:37 lm 3 2
c Needed timing.c.
cK53873
e
s 00163/00000/00000
d D 1.1 94/11/18 00:49:48 lm 2 1
c Initial revision
cK52185
e
s 00000/00000/00000
d D 1.0 94/11/18 00:49:47 lm 1 0
cBlm@lm.bitmover.com|ChangeSet|20000131225335|47351|--LMBENCH--
cHlm.bitmover.com
cK08513
cPsrc/lat_fs.c
cRe78dec908fe62e64
cV4
cX0x21
cZ-08:00
e
u
U
f e 0
f x 0x21
t
lmbench src
T
I 2
/*
 * Benchmark creates & deletes.
 */

char	*id = "$Id$\n";

I 3
D 9
#include "timing.c"
E 9
I 9
D 10
#include	"timing.c"
#include	<fcntl.h>
E 10
I 10
D 11
#include "timing.h"
E 11
#include "bench.h"
D 11
#include <fcntl.h>
E 11
E 10
E 9

I 6
#ifndef	ITER
E 6
E 3
#define	ITER	1000
I 6
#endif
E 6
#define	S	5

D 4
main()
E 4
I 4
D 9
main(ac, av)
	char	**av;
E 9
I 9
void	mkfile(char *s, int sz);

int
main(int ac, char **av)
E 9
E 4
{
	static	int	sizes[] = { 0, 1024, 4096, 10*1024 };
	extern	char	*names[];
	int	i, j;
	double	tmp, create_m, delete_m;
	double	time_spent;
D 7
	char	buf[100];
E 7

I 4
	if (ac == 2) {
		chdir(av[1]);
	}
E 4
D 8
	write(2, id, strlen(id));
E 8
	for (i = 0; i < sizeof(sizes)/sizeof(int); ++i) {
		/*
		 * Go around the loop a few times for those really fast Linux
		 * boxes.
		 */
		for (time_spent = create_m = delete_m = 0; time_spent <= S; ) {
D 10
			start();
E 10
I 10
			start(0);
E 10
			for (j = 0; j < ITER; ++j) {
				mkfile(names[j], sizes[i]);
			}
D 10
			tmp = stop() / 1000000.;
E 10
I 10
			tmp = stop(0,0) / 1000000.;
E 10
			if (create_m == 0 || create_m > tmp) {
				create_m = tmp;
			}
			time_spent += tmp;
D 10
			start();
E 10
I 10
			start(0);
E 10
			for (j = 0; j < ITER; ++j) {
				unlink(names[j]);
			}
D 10
			tmp = stop() / 1000000.;
E 10
I 10
			tmp = stop(0,0) / 1000000.;
E 10
			if (delete_m == 0 || delete_m > tmp) {
				delete_m = tmp;
			}
			time_spent += tmp;
		}
D 5
		printf("%dk\t%d\t%.0f\t%.0f\n",
E 5
I 5
		fprintf(stderr, "%dk\t%d\t%.0f\t%.0f\n",
E 5
		    sizes[i]>>10, ITER,
		    ITER / create_m, ITER / delete_m);
	}
D 12
	exit(0);
E 12
I 12
	return(0);
E 12
}

D 9
mkfile(s, sz)
	char	*s;
E 9
I 9
void
mkfile(char *s, int sz)
E 9
{
	int	fd = creat(s, 0666);
	char	buf[128*1024];		/* XXX - track sizes */

	write(fd, buf, sz);
	close(fd);
}

char *names[] = {
"a",	"b",	"c",	"d",	"e",	"f",	"g",	"h",	"i",	"j",
"k",	"l",	"m",	"n",	"o",	"p",	"q",	"r",	"s",	"t",
"u",	"v",	"w",	"x",	"y",	"z",	"aa",	"ab",	"ac",	"ad",
"ae",	"af",	"ag",	"ah",	"ai",	"aj",	"ak",	"al",	"am",	"an",
"ao",	"ap",	"aq",	"ar",	"as",	"at",	"au",	"av",	"aw",	"ax",
"ay",	"az",	"ba",	"bb",	"bc",	"bd",	"be",	"bf",	"bg",	"bh",
"bi",	"bj",	"bk",	"bl",	"bm",	"bn",	"bo",	"bp",	"bq",	"br",
"bs",	"bt",	"bu",	"bv",	"bw",	"bx",	"by",	"bz",	"ca",	"cb",
"cc",	"cd",	"ce",	"cf",	"cg",	"ch",	"ci",	"cj",	"ck",	"cl",
"cm",	"cn",	"co",	"cp",	"cq",	"cr",	"cs",	"ct",	"cu",	"cv",
"cw",	"cx",	"cy",	"cz",	"da",	"db",	"dc",	"dd",	"de",	"df",
"dg",	"dh",	"di",	"dj",	"dk",	"dl",	"dm",	"dn",	"do",	"dp",
"dq",	"dr",	"ds",	"dt",	"du",	"dv",	"dw",	"dx",	"dy",	"dz",
"ea",	"eb",	"ec",	"ed",	"ee",	"ef",	"eg",	"eh",	"ei",	"ej",
"ek",	"el",	"em",	"en",	"eo",	"ep",	"eq",	"er",	"es",	"et",
"eu",	"ev",	"ew",	"ex",	"ey",	"ez",	"fa",	"fb",	"fc",	"fd",
"fe",	"ff",	"fg",	"fh",	"fi",	"fj",	"fk",	"fl",	"fm",	"fn",
"fo",	"fp",	"fq",	"fr",	"fs",	"ft",	"fu",	"fv",	"fw",	"fx",
"fy",	"fz",	"ga",	"gb",	"gc",	"gd",	"ge",	"gf",	"gg",	"gh",
"gi",	"gj",	"gk",	"gl",	"gm",	"gn",	"go",	"gp",	"gq",	"gr",
"gs",	"gt",	"gu",	"gv",	"gw",	"gx",	"gy",	"gz",	"ha",	"hb",
"hc",	"hd",	"he",	"hf",	"hg",	"hh",	"hi",	"hj",	"hk",	"hl",
"hm",	"hn",	"ho",	"hp",	"hq",	"hr",	"hs",	"ht",	"hu",	"hv",
"hw",	"hx",	"hy",	"hz",	"ia",	"ib",	"ic",	"id",	"ie",	"if",
"ig",	"ih",	"ii",	"ij",	"ik",	"il",	"im",	"in",	"io",	"ip",
"iq",	"ir",	"is",	"it",	"iu",	"iv",	"iw",	"ix",	"iy",	"iz",
"ja",	"jb",	"jc",	"jd",	"je",	"jf",	"jg",	"jh",	"ji",	"jj",
"jk",	"jl",	"jm",	"jn",	"jo",	"jp",	"jq",	"jr",	"js",	"jt",
"ju",	"jv",	"jw",	"jx",	"jy",	"jz",	"ka",	"kb",	"kc",	"kd",
"ke",	"kf",	"kg",	"kh",	"ki",	"kj",	"kk",	"kl",	"km",	"kn",
"ko",	"kp",	"kq",	"kr",	"ks",	"kt",	"ku",	"kv",	"kw",	"kx",
"ky",	"kz",	"la",	"lb",	"lc",	"ld",	"le",	"lf",	"lg",	"lh",
"li",	"lj",	"lk",	"ll",	"lm",	"ln",	"lo",	"lp",	"lq",	"lr",
"ls",	"lt",	"lu",	"lv",	"lw",	"lx",	"ly",	"lz",	"ma",	"mb",
"mc",	"md",	"me",	"mf",	"mg",	"mh",	"mi",	"mj",	"mk",	"ml",
"mm",	"mn",	"mo",	"mp",	"mq",	"mr",	"ms",	"mt",	"mu",	"mv",
"mw",	"mx",	"my",	"mz",	"na",	"nb",	"nc",	"nd",	"ne",	"nf",
"ng",	"nh",	"ni",	"nj",	"nk",	"nl",	"nm",	"nn",	"no",	"np",
"nq",	"nr",	"ns",	"nt",	"nu",	"nv",	"nw",	"nx",	"ny",	"nz",
"oa",	"ob",	"oc",	"od",	"oe",	"of",	"og",	"oh",	"oi",	"oj",
"ok",	"ol",	"om",	"on",	"oo",	"op",	"oq",	"or",	"os",	"ot",
"ou",	"ov",	"ow",	"ox",	"oy",	"oz",	"pa",	"pb",	"pc",	"pd",
"pe",	"pf",	"pg",	"ph",	"pi",	"pj",	"pk",	"pl",	"pm",	"pn",
"po",	"pp",	"pq",	"pr",	"ps",	"pt",	"pu",	"pv",	"pw",	"px",
"py",	"pz",	"qa",	"qb",	"qc",	"qd",	"qe",	"qf",	"qg",	"qh",
"qi",	"qj",	"qk",	"ql",	"qm",	"qn",	"qo",	"qp",	"qq",	"qr",
"qs",	"qt",	"qu",	"qv",	"qw",	"qx",	"qy",	"qz",	"ra",	"rb",
"rc",	"rd",	"re",	"rf",	"rg",	"rh",	"ri",	"rj",	"rk",	"rl",
"rm",	"rn",	"ro",	"rp",	"rq",	"rr",	"rs",	"rt",	"ru",	"rv",
"rw",	"rx",	"ry",	"rz",	"sa",	"sb",	"sc",	"sd",	"se",	"sf",
"sg",	"sh",	"si",	"sj",	"sk",	"sl",	"sm",	"sn",	"so",	"sp",
"sq",	"sr",	"ss",	"st",	"su",	"sv",	"sw",	"sx",	"sy",	"sz",
"ta",	"tb",	"tc",	"td",	"te",	"tf",	"tg",	"th",	"ti",	"tj",
"tk",	"tl",	"tm",	"tn",	"to",	"tp",	"tq",	"tr",	"ts",	"tt",
"tu",	"tv",	"tw",	"tx",	"ty",	"tz",	"ua",	"ub",	"uc",	"ud",
"ue",	"uf",	"ug",	"uh",	"ui",	"uj",	"uk",	"ul",	"um",	"un",
"uo",	"up",	"uq",	"ur",	"us",	"ut",	"uu",	"uv",	"uw",	"ux",
"uy",	"uz",	"va",	"vb",	"vc",	"vd",	"ve",	"vf",	"vg",	"vh",
"vi",	"vj",	"vk",	"vl",	"vm",	"vn",	"vo",	"vp",	"vq",	"vr",
"vs",	"vt",	"vu",	"vv",	"vw",	"vx",	"vy",	"vz",	"wa",	"wb",
"wc",	"wd",	"we",	"wf",	"wg",	"wh",	"wi",	"wj",	"wk",	"wl",
"wm",	"wn",	"wo",	"wp",	"wq",	"wr",	"ws",	"wt",	"wu",	"wv",
"ww",	"wx",	"wy",	"wz",	"xa",	"xb",	"xc",	"xd",	"xe",	"xf",
"xg",	"xh",	"xi",	"xj",	"xk",	"xl",	"xm",	"xn",	"xo",	"xp",
"xq",	"xr",	"xs",	"xt",	"xu",	"xv",	"xw",	"xx",	"xy",	"xz",
"ya",	"yb",	"yc",	"yd",	"ye",	"yf",	"yg",	"yh",	"yi",	"yj",
"yk",	"yl",	"ym",	"yn",	"yo",	"yp",	"yq",	"yr",	"ys",	"yt",
"yu",	"yv",	"yw",	"yx",	"yy",	"yz",	"za",	"zb",	"zc",	"zd",
"ze",	"zf",	"zg",	"zh",	"zi",	"zj",	"zk",	"zl",	"zm",	"zn",
"zo",	"zp",	"zq",	"zr",	"zs",	"zt",	"zu",	"zv",	"zw",	"zx",
"zy",	"zz",	"aaa",	"aab",	"aac",	"aad",	"aae",	"aaf",	"aag",	"aah",
"aai",	"aaj",	"aak",	"aal",	"aam",	"aan",	"aao",	"aap",	"aaq",	"aar",
"aas",	"aat",	"aau",	"aav",	"aaw",	"aax",	"aay",	"aaz",	"aba",	"abb",
"abc",	"abd",	"abe",	"abf",	"abg",	"abh",	"abi",	"abj",	"abk",	"abl",
"abm",	"abn",	"abo",	"abp",	"abq",	"abr",	"abs",	"abt",	"abu",	"abv",
"abw",	"abx",	"aby",	"abz",	"aca",	"acb",	"acc",	"acd",	"ace",	"acf",
"acg",	"ach",	"aci",	"acj",	"ack",	"acl",	"acm",	"acn",	"aco",	"acp",
"acq",	"acr",	"acs",	"act",	"acu",	"acv",	"acw",	"acx",	"acy",	"acz",
"ada",	"adb",	"adc",	"add",	"ade",	"adf",	"adg",	"adh",	"adi",	"adj",
"adk",	"adl",	"adm",	"adn",	"ado",	"adp",	"adq",	"adr",	"ads",	"adt",
"adu",	"adv",	"adw",	"adx",	"ady",	"adz",	"aea",	"aeb",	"aec",	"aed",
"aee",	"aef",	"aeg",	"aeh",	"aei",	"aej",	"aek",	"ael",	"aem",	"aen",
"aeo",	"aep",	"aeq",	"aer",	"aes",	"aet",	"aeu",	"aev",	"aew",	"aex",
"aey",	"aez",	"afa",	"afb",	"afc",	"afd",	"afe",	"aff",	"afg",	"afh",
"afi",	"afj",	"afk",	"afl",	"afm",	"afn",	"afo",	"afp",	"afq",	"afr",
"afs",	"aft",	"afu",	"afv",	"afw",	"afx",	"afy",	"afz",	"aga",	"agb",
"agc",	"agd",	"age",	"agf",	"agg",	"agh",	"agi",	"agj",	"agk",	"agl",
"agm",	"agn",	"ago",	"agp",	"agq",	"agr",	"ags",	"agt",	"agu",	"agv",
"agw",	"agx",	"agy",	"agz",	"aha",	"ahb",	"ahc",	"ahd",	"ahe",	"ahf",
"ahg",	"ahh",	"ahi",	"ahj",	"ahk",	"ahl",	"ahm",	"ahn",	"aho",	"ahp",
"ahq",	"ahr",	"ahs",	"aht",	"ahu",	"ahv",	"ahw",	"ahx",	"ahy",	"ahz",
"aia",	"aib",	"aic",	"aid",	"aie",	"aif",	"aig",	"aih",	"aii",	"aij",
"aik",	"ail",	"aim",	"ain",	"aio",	"aip",	"aiq",	"air",	"ais",	"ait",
"aiu",	"aiv",	"aiw",	"aix",	"aiy",	"aiz",	"aja",	"ajb",	"ajc",	"ajd",
"aje",	"ajf",	"ajg",	"ajh",	"aji",	"ajj",	"ajk",	"ajl",	"ajm",	"ajn",
"ajo",	"ajp",	"ajq",	"ajr",	"ajs",	"ajt",	"aju",	"ajv",	"ajw",	"ajx",
"ajy",	"ajz",	"aka",	"akb",	"akc",	"akd",	"ake",	"akf",	"akg",	"akh",
"aki",	"akj",	"akk",	"akl",	"akm",	"akn",	"ako",	"akp",	"akq",	"akr",
"aks",	"akt",	"aku",	"akv",	"akw",	"akx",	"aky",	"akz",	"ala",	"alb",
"alc",	"ald",	"ale",	"alf",	"alg",	"alh",	"ali",	"alj",	"alk",	"all",
};
E 2
I 1
E 1
