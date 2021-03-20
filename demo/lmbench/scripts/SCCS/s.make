H00268
s 00005/00001/00010
d D 1.3 01/06/19 12:09:16 staelin 4 3
c Add a fix to scripts/make which verifies that gmake actually works
cC
cHhpli69.hpli.hpl.hp.com
cK14870
cZ+03:00
e
s 00001/00001/00010
d D 1.2 00/04/16 14:45:59 staelin 3 2
c Fix typo
cC
cK10474
e
s 00011/00000/00000
d D 1.1 00/04/16 14:44:44 staelin 2 1
cF1
cK10322
cO-rwxr-xr-x
e
s 00000/00000/00000
d D 1.0 00/04/16 14:44:44 staelin 1 0
c BitKeeper file /tmp_mnt/usr/WebPaper/users/staelin/src/LMbench/scripts/make
cBlm@lm.bitmover.com|ChangeSet|20000131225335|47351|--LMBENCH--
cHhpli8.hpli.hpl.hp.com
cK39334
cPscripts/make
cR2e15ddc531019840
cV4
cX0xa1
cZ+02:00
e
u
U
f e 0
f x 0xa1
t
T
I 2
#!/bin/sh

if [ X$MAKE = X ]
then	MAKE=make
	for p in `echo $PATH | sed 's/:/ /g'`
	do	if [ -f $p/gmake ]
D 3
		then	CC=gmake
E 3
I 3
D 4
		then	MAKE=gmake
E 4
I 4
		then	
		    if $p/gmake testmake > /dev/null 2>&1
		    then
			MAKE=$p/gmake
		    fi
E 4
E 3
		fi
	done
fi
echo $MAKE
E 2
I 1
E 1
