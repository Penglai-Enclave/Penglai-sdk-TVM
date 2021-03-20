H31139
s 00003/00001/00307
d D 1.10 02/03/18 11:41:04 staelin 11 10
c fix bug in disk.c with large disks; reported by Dean Gaudet
cC
cHhpli69.hpli.hpl.hp.com
cK24538
cZ+02:00
e
s 00001/00003/00307
d D 1.9 00/08/02 18:04:57 staelin 10 9
c - #include "flushdisk.c" so we don't require two .c files on the compiler's command line,
c   which seems to make the compiler generate .o files in the src directory which can 
c   cause problems in a clustered environment.
cC
cHhpli8.hpli.hpl.hp.com
cK23302
cZ+03:00
e
s 00002/00002/00308
d D 1.8 98/07/02 17:32:54 lm 9 8
c Fix a bug in the prototype.
cC
cK24803
e
s 00002/00000/00308
d D 1.7 98/06/29 23:49:35 lm 8 7
c glibc/llseek
cK23785
e
s 00006/00003/00302
d D 1.6 98/06/29 22:37:15 lm 7 6
c Redo to compile clean with -Wall.
cHlm.bitmover.com
cK20494
e
s 00007/00000/00298
d D 1.5 98/05/19 16:24:08 lm 6 5
c use llseek.
cHwork
cK18347
cZ-07:00
e
s 00098/00025/00200
d D 1.4 98/03/29 14:56:39 lm 5 4
c This is a work in progress. Linux limits me to 2GB and I haven't fixed
c that yet.
cK10315
e
s 00048/00065/00177
d D 1.3 97/11/05 19:39:28 lm 4 3
c Better disk size/32 bit vs 64 bit handling.
cK61962
cZ-08:00
e
s 00002/00009/00240
d D 1.2 97/10/24 13:48:42 lm 3 2
c linux shit.
cK24526
e
s 00249/00000/00000
d D 1.1 97/10/19 23:48:33 lm 2 1
c Initial revision
cK33582
e
s 00000/00000/00000
d D 1.0 97/10/19 23:48:32 lm 1 0
cBlm@lm.bitmover.com|ChangeSet|20000131225335|47351|--LMBENCH--
cHlm.bitmover.com
cK09828
cPsrc/disk.c
cR4136b37fbde5c85d
cV4
cX0x21
cZ-07:00
e
u
U
f e 0
f x 0x21
t
Time disks.
T
I 2
/*
 * disk - calculate zone bandwidths and seek times
 *
 * Usage: disk device
 *
 * Copyright (c) 1994-1997 Larry McVoy.  All rights reserved.
 * Bits of this are derived from work by Ethan Solomita.
 */

#include	<stdio.h>
#include	<sys/types.h>
#include	<unistd.h>
#include	<stdlib.h>
#include	"bench.h"
I 10
#include	"flushdisk.c"
E 10
D 3
#ifdef	linux
#include	<linux/fs.h>
#endif
E 3

#ifndef sgi
#define	NO_LSEEK64
#define	off64_t	long long
#endif
I 5
#define	SEEKPOINTS	2000
#define	ZONEPOINTS	150
E 5

D 4
off64_t lseek64(int, off64_t, int);
E 4
I 4
uint64	disksize(char *);
D 5
void	seekto(int, uint64);
E 4
int	zone(char *disk, int oflag, int stride, int bsize);
int	seek(char *disk, int oflag, int stride);
E 5
I 5
int	seekto(int, uint64);
int	zone(char *disk, int oflag, int bsize);
int	seek(char *disk, int oflag);
I 7
D 10
#ifdef	linux
int	flushdisk(int);
#endif
E 10
E 7
E 5

I 7
int
E 7
main(int ac, char **av)
{
	fprintf(stderr, "\"Seek times for %s\n", av[1]);
D 5
	seek(av[1], 0, 1<<18);
E 5
I 5
	seek(av[1], 0);
E 5
	fprintf(stderr, "\n");
	fprintf(stderr, "\"Zone bandwidth for %s\n", av[1]);
D 5
	zone(av[1], 0, (1<<22), 1<<20);
E 5
I 5
	zone(av[1], 0, (1<<20));
I 7
	return (0);
E 7
E 5
}

int
D 5
zone(char *disk, int oflag, int stride, int bsize)
E 5
I 5
zone(char *disk, int oflag, int bsize)
E 5
{
	char	*buf;
	int	usecs;
	int	error;
D 7
	int	n, moved;
E 7
I 7
	int	n;
E 7
	int	fd;
I 4
	uint64	off;
I 5
	int	stride;
E 5
E 4

	if ((fd = open(disk, oflag)) == -1) {
		perror(disk);
		exit(1);
	}
	buf = valloc(bsize);
	if (!buf) {
		perror("valloc");
		exit(1);
	}
	bzero(buf, bsize);
#ifdef	linux
D 3
	ioctl(fd, BLKFLSBUF, 0);
	usleep(100000);
E 3
I 3
	flushdisk(fd);
E 3
#endif

	/*
I 5
	 * We want ZONEPOINTS data points 
	 * but the stride has to be at least 512 and a 512 multiple.
	 * Weird code below for precision.
	 */
	off = disksize(disk);
	off /= ZONEPOINTS;
	stride = off;
	if (stride < 512) stride = 512;
	stride += 511;
	stride >>= 9;
	stride <<= 9;

	/*
	 * Very small disks such as ZIP drives get a 256K blocksize.
	 * As measured on my SCSI ZIP, there seems to be no
	 * difference between 256K and 1MB for sequential reads.
	 * XXX - there is a rotational delay difference but that's tough.
	 */
	if (bsize > stride) bsize = 256<<10;
	if (bsize > stride) stride = bsize;

	off *= ZONEPOINTS;
	debug((stdout, "stride=%d bs=%d size=%dM points=%d\n",
	    stride, bsize, (int)(off >> 20), (int)(off/stride)));

	/*
E 5
	 * Read buf's worth of data every stride and time it.
	 * Don't include the rotational delay.
	 * This first I/O outside the loop is to catch read/write permissions.
	 */

#define	IO(a,b,c)	(oflag == 0 ? (n = read(a,b,c)) : (n = write(a,b,c)))

	error = IO(fd, buf, 512);
	if (error == -1) {
		perror(disk);
		exit(1);
	}
I 4
	off = 512;
E 4
	for ( ;; ) {
		if (IO(fd, buf, 1024) != 1024) {
			exit(0);
		}
I 4
		off += 1024;
E 4
		start(0);
		if (IO(fd, buf, bsize) != bsize) {
			exit(0);
		}
		usecs = stop(0, 0);
I 4
		off += bsize;
E 4
D 5
		fprintf(stderr, "%.04f %.04f\n",
E 5
I 5
		fprintf(stderr, "%.01f %.2f\n",
E 5
D 4
		    (lseek64(fd, 0LL, 1) - bsize) / 1000000.,
		    (double)bsize/usecs);
		lseek64(fd, stride, 1);
E 4
I 4
		    off/1000000.0, (double)bsize/usecs);
		off += stride;
D 11
		seekto(fd, off);
E 11
I 11
		if (seekto(fd, off)) {
			exit(0);
		}
E 11
E 4
	}
	exit(0);
}

/*
 * Seek - calculate seeks as a function of distance.
 */
#undef	IO
#define	IO(a,b,c)	error = (oflag == 0 ? read(a,b,c) : write(a,b,c)); \
			if (error == -1) { perror("io"); exit(1); }
#define	IOSIZE		512
#define	TOOSMALL	1000	/* seeks this small are cached */
D 4
#define	TOOBIG		95000	/* seeks this big are remapped or weirdos */
E 4
I 4
#define	TOOBIG		1000000	/* seeks this big are remapped or weirdos */
E 4
				/* zip drives have seeks this long */

int
D 5
seek(char *disk, int oflag, int stride)
E 5
I 5
seek(char *disk, int oflag)
E 5
{
	char	*buf;
	int	fd;
	off64_t	size;
	off64_t	begin, end;
	int	usecs;
	int	error;
	int	tot_msec = 0, tot_io = 0;
D 7
	double	avg_msec;
E 7
I 5
	int	stride;
E 5

	if ((fd = open(disk, oflag)) == -1) {
		perror(disk);
		return (-1);
	}
#ifdef	linux
D 3
	if (ioctl(fd, BLKFLSBUF, 0) == -1) {
		perror("BLKFLSBUF");
	}
	usleep(100000);
E 3
I 3
	flushdisk(fd);
E 3
#endif
D 4
	size = (off64_t)disksize_in_mb(disk);
	size <<= 20;
E 4
I 4
	size = disksize(disk);
E 4
	buf = valloc(IOSIZE);
	bzero(buf, IOSIZE);

	/*
	 * We flip back and forth, in strides of 1MB (typically).
	 * If we have a 100MB fd, that means we do
	 * 1, 99, 2, 98, etc.
I 5
	 *
	 * We want around SEEK POINTS data points 
	 * but the stride has to be at least 512 and a 512 multiple.
E 5
	 */
I 5
	stride = size / SEEKPOINTS;
	if (stride < 512) stride = 512;
	stride += 511;
	stride >>= 9;
	stride <<= 9;

	debug((stdout, "stride=%d size=%dM points=%d\n",
	    stride, (int)(size >> 20), (int)(size/stride)));

E 5
	end = size;
	begin = 0;
D 4
	if (lseek64(fd, begin, 0)) {
		perror("lseek");
		return (-1);
	}
E 4
I 4
	seekto(fd, begin);
E 4
	IO(fd, buf, IOSIZE);
	while (end >= begin + stride*2) {
		end -= stride;
		start(0);
D 4
		if (lseek64(fd, end, 0) != end) {
			perror("lseek");
			return (-1);
		}
E 4
I 4
		seekto(fd, end);
E 4
		IO(fd, buf, IOSIZE);
		usecs = stop(0, 0);
		if (usecs > TOOSMALL && usecs < TOOBIG) {
			tot_io++; tot_msec += usecs/1000;
D 5
			fprintf(stderr, "%.04f %.04f\n",
E 5
I 5
			fprintf(stderr, "%.01f %.02f\n",
E 5
			    (end - begin - stride) / 1000000., usecs/1000.);
		}

		begin += stride;
		start(0);
D 4
		if (lseek64(fd, begin, 0) != begin) {
			perror("lseek");
			return (-1);
		}
E 4
I 4
		seekto(fd, begin);
E 4
		IO(fd, buf, IOSIZE);
		usecs = stop(0, 0);
		if (usecs > TOOSMALL && usecs < TOOBIG) {
			tot_io++; tot_msec += usecs/1000;
D 5
			fprintf(stderr, "%.04f %.04f\n",
E 5
I 5
			fprintf(stderr, "%.01f %.02f\n",
E 5
			    (end + stride - begin) / 1000000., usecs/1000.);
		}
	}
	/*
	 * This is wrong, it should take the 1/3 stroke seek average.
	avg_msec = (double)tot_msec/tot_io;
	fprintf(stderr, "Average time == %.04f\n", avg_msec);
	 */
	return (0);
}

/*
 * Calculate how big a device is.
 *
 * To avoid 32 bit problems, our units are MB.
 */
D 4
#define	LSEEK(a,b,c)	lseek64(a,(long long)(b),c)
E 4
I 4
D 5
#define	FORWARD		(1<<30)
#define	BACKWARD	(128<<20)
E 5
I 5
#define	FORWARD		(512<<20)
#define	FORWARD1	(64<<20)
#define	FORWARD2	(1<<20)
E 5
E 4

/*
D 4
 * XXX - I think this alg screws up at times, at least some version of this
 * used to get things too small.
E 4
I 4
 * Go forward in 1GB chunks until you can't.
 * Go backwards in 128MB chunks until you can.
I 5
 * Go forwards in 1MB chunks until you can't and return that -1.
E 5
E 4
 */
D 4
int
disksize_in_mb(char *disk)
E 4
I 4
uint64
disksize(char *disk)
E 4
{
	int	fd = open(disk, 0);
	char	buf[512];
D 4
	int	offmb = 0;
	int	try = 1<<30;
E 4
I 4
	uint64	off = 0;
E 4

	if (fd == -1) {
		perror("usage: disksize device");
		return(0);
	}
D 4
	if (read(fd, buf, sizeof(buf)) != sizeof(buf)) {
		printf("0\n");
		exit(1);
E 4
I 4
	/*
	 * Go forward until it doesn't work.
	 */
	for ( ;; ) {
		off += FORWARD;
D 5
		seekto(fd, off);
		if (read(fd, buf, sizeof(buf)) != sizeof(buf)) {
E 5
I 5
		if (seekto(fd, off)) {
			debug((stdout, "seekto(%dM) failed\n", (int)(off>>20)));
			off -= FORWARD;
E 5
			break;
		}
I 5
		if ((read(fd, buf, sizeof(buf)) != sizeof(buf))) {
			debug((stdout, "read @ %dM failed\n", (int)(off>>20)));
			off -= FORWARD;
			break;
		}
E 5
E 4
	}
D 4
	while (try >= 1<<20) {
		for ( ;; ) {
			if (LSEEK(fd, try, 1) == -1) {
				break;
			}
			if (read(fd, buf, sizeof(buf)) != sizeof(buf)) {
				close(fd);
				fd = reopen(disk, offmb);
				if (read(fd, buf, sizeof(buf)) != sizeof(buf)) {
					goto out;
				}
				break;
			}
			offmb += try >> 20;
E 4
I 4

D 5
	/*
	 * Go backwards until we find a location that works.
	 */
E 5
	for ( ;; ) {
D 5
		off -= BACKWARD;
		seekto(fd, off);
		if (read(fd, buf, sizeof(buf)) == sizeof(buf)) {
E 5
I 5
		off += FORWARD1;
		if (seekto(fd, off)) {
			debug((stdout, "seekto(%dM) failed\n", (int)(off>>20)));
			off -= FORWARD1;
E 5
			break;
E 4
		}
I 5
		if ((read(fd, buf, sizeof(buf)) != sizeof(buf))) {
			debug((stdout, "read @ %dM failed\n", (int)(off>>20)));
			off -= FORWARD1;
			break;
		}
E 5
D 4
		try /= 2;
E 4
	}
I 5

	for ( ;; ) {
		off += FORWARD2;
		if (seekto(fd, off)) {
			debug((stdout, "seekto(%dM) failed\n", (int)(off>>20)));
			off -= FORWARD2;
			break;
		}
		if ((read(fd, buf, sizeof(buf)) != sizeof(buf))) {
			debug((stdout, "read @ %dM failed\n", (int)(off>>20)));
			off -= FORWARD2;
			break;
		}
	}

E 5
D 7
out:
E 7
I 5
	debug((stdout, "disksize(%s) = %d MB\n", disk, (int)(off >> 20)));
E 5
D 4
	return (offmb);
E 4
I 4
	return (off);
E 4
}

D 4

reopen(char *file, int offmb)
E 4
I 4
D 5
void
E 5
I 5
#define	BIGSEEK	(1<<30)

int
E 5
seekto(int fd, uint64 off)
E 4
{
I 6
#ifdef	__linux__
I 8
D 9
	extern	int llseek(int, loff_t, int);
E 9
I 9
	extern	loff_t llseek(int, loff_t, int);
E 9

E 8
D 9
	if (llseek(fd, (loff_t)off, SEEK_SET) == -1) {
E 9
I 9
	if (llseek(fd, (loff_t)off, SEEK_SET) == (loff_t)-1) {
E 9
		return(-1);
	}
	return (0);
#else
E 6
D 4
	int	fd = open(file, 0);
	int	i;
E 4
I 4
	uint64	here = 0;
E 4

D 4
	for (i = 0; i < offmb; i++) {
		LSEEK(fd, 1<<20, 1);
E 4
I 4
	lseek(fd, 0, 0);
D 5
	while (off - here > 1<<30) {
		lseek(fd, 1<<30, SEEK_CUR);
		here += 1<<30;
E 5
I 5
	while ((uint64)(off - here) > (uint64)BIGSEEK) {
		if (lseek(fd, BIGSEEK, SEEK_CUR) == -1) break;
		here += BIGSEEK;
E 5
E 4
	}
D 4
	return (fd);
E 4
I 4
D 5
	lseek(fd, (int)(off - here), SEEK_CUR);
E 5
I 5
	assert((uint64)(off - here) <= (uint64)BIGSEEK);
	if (lseek(fd, (int)(off - here), SEEK_CUR) == -1) return (-1);
	return (0);
I 6
#endif
E 6
E 5
E 4
}
D 4

#ifdef	NO_LSEEK64
off64_t
lseek64(int fd, off64_t off, int whence)
{
	if (off & 0xffffffff00000000LL) {
		fprintf(stderr, "Bad seek offset: %lld\n", off);
		exit(1);
	}
	return ((off64_t)lseek(fd, (off_t)off, whence));
}
#endif

E 4
E 2
I 1
E 1
