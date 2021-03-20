h61593
s 00012/00003/00309
d D 1.11 00/01/31 16:29:28 lm 12 11
c Updates for BitKeeper.
cC
cK02127
e
s 00169/00155/00143
d D 1.10 97/10/31 18:04:34 lm 11 10
c Rewack for the html stuff.
c Rewack all the scripts to be robust when no data.
cC
cK25654
e
s 00003/00000/00295
d D 1.9 96/01/27 23:01:07 lm 10 9
c *** empty log message ***
cK36483
e
s 00003/00000/00292
d D 1.8 96/01/22 23:29:14 lm 9 8
c mem.x target.
cK32197
e
s 00002/00002/00290
d D 1.7 95/11/07 17:43:34 lm 8 7
c get.
cK27943
e
s 00003/00001/00289
d D 1.6 95/11/03 15:12:46 lm 7 6
c *** empty log message ***
cK27943
cZ-08:00
e
s 00018/00000/00272
d D 1.5 95/10/25 09:44:33 lm 6 5
c paper targets.
cK25816
e
s 00117/00013/00155
d D 1.4 95/09/28 11:20:55 lm 5 4
c *** empty log message ***
cK56069
cZ-07:00
e
s 00001/00001/00167
d D 1.3 94/11/25 16:41:45 lm 4 3
c *** empty log message ***
cK26782
e
s 00001/00001/00167
d D 1.2 94/11/25 12:28:24 lm 3 2
c typo.
cK25525
e
s 00168/00000/00000
d D 1.1 94/11/23 17:46:57 lm 2 1
c Initial revision
cK24554
e
s 00000/00000/00000
d D 1.0 94/11/23 17:46:56 lm 1 0
cBlm@lm.bitmover.com|ChangeSet|20000131225335|47351|--LMBENCH--
cHlm.bitmover.com
cK04215
cPresults/Makefile
cRb60f2a10c224046e
cV4
cX0x23
cZ-08:00
e
u
U
f e 0
f x 0x23
t
T
I 2
# Makefile for lmbench results.
# $Id$
#
# Usage: make [ LIST="aix/* sunos/* ..." ] [ what ]
#
# What to make:
#	print			Prints the results 1 per page.
D 11
#	8			Prints the result 8 per page
#	8.ps			Saves the postscript of 8 per page in PS/PS8
E 11
#	ps			Saves the postscript of 1 per page in PS/PS
I 11
#	4.ps			Saves the postscript of 4 per page in PS/PS4
#	8.ps			Saves the postscript of 8 per page in PS/PS8
E 11
#	x			Previews 1 per page using groff -X
#	summary	[default]	Ascii summary of the results
D 11
#	percent			Ascii summary as percentages of the best.
#	list			Print out the current list
E 11
I 11
#	stats			Do statistics over a set of results
E 11
#	roff			Print the ascii summaries into a roff file
I 5
D 11
#	html			(Under construction)
E 11
#	slides			Makes the pic for inclusion in slides
E 5
#
# This Makefile requires groff, gpic, and perl.  You could try it with
# other *roff processors; I have no idea if it works.
#
I 11
# XXX - this is all out of date.
#
E 11
D 3
# There are three sorts of results:
E 3
I 3
# There are three sorts of graphical results:
E 3
#
# 1. Bargraphs comparing each system in the LIST on the measurements listed
#    in the BG list below (pretty much everything).
# 2. A 2-D graph for each system in LIST, displaying context switch times
#    as a function of (# of processes, size of each process).
# 3. A 2-D graph for each system in LIST, displaying memory read times as
#    a function of (stride size, memory size).
#
# The bargraphs are in a format of my own - the perl script in scripts
# called bargraph takes them as input and produces pic as output.
# It is a pretty straightforward format, you could probably incorparate
# into some Windows spreadsheet if you wanted to.  See tmp/*.bg after
# running make in this directory.
#
# The 2-D graphs are in a format that can (probably) be read by Xgraph.
# I've added a few extensions for titles, etc., that you could just
# take out.  See tmp/mem.* after running a make in this directory.
#
# This Makefile is of marginal usefulness to a site with just one machine.
# I intend to make results available so that people can compare, as well
# as a service where you can compare your results against the "best of
# the breed" for each vendor, as well as against best of the lot.

# List of result files to process.  Defaults to everything.
D 7
LIST=	`$(SCRIPTS)getlist`	
E 7
I 7
LIST=	`$(SCRIPTS)getlist $(LST)`	
E 7

# Grrrrr
SHELL=/bin/sh

SCRIPTS=../scripts/
I 12
SRCS= ../scripts/allctx ../scripts/allmem ../scripts/bargraph \
	../scripts/bghtml ../scripts/getbg ../scripts/getbw \
	../scripts/getctx ../scripts/getdisk ../scripts/getlist \
	../scripts/getmax ../scripts/getmem ../scripts/getpercent \
	../scripts/getresults ../scripts/getsummary ../scripts/gifs \
	../scripts/graph ../scripts/html-list ../scripts/html-man \
	../scripts/os ../scripts/percent ../scripts/save \
	../scripts/stats ../scripts/xroff 
E 12

MISC=	tmp/misc_mhz.bg \
	tmp/lat_ctx.bg \
	tmp/lat_ctx8.bg \
	tmp/lat_nullsys.bg \
D 5
	tmp/lat_mappings.bg
E 5
I 5
	tmp/lat_signal.bg \
	tmp/lat_pagefault.bg \
	tmp/lat_mappings.bg \
	tmp/lat_fs_create.bg
E 5

PROC=	tmp/lat_nullproc.bg \
	tmp/lat_simpleproc.bg \
	tmp/lat_shproc.bg

LATENCY= \
	tmp/lat_pipe.bg \
I 5
	tmp/lat_connect.bg \
E 5
	tmp/lat_udp_local.bg \
	tmp/lat_rpc_udp_local.bg \
	tmp/lat_tcp_local.bg  \
	tmp/lat_rpc_tcp_local.bg 

BANDWIDTH= \
	tmp/bw_pipe.bg \
	tmp/bw_tcp_local.bg \
	tmp/bw_file.bg \
	tmp/bw_reread.bg \
	tmp/bw_mmap.bg \
	tmp/bw_bcopy_libc.bg \
	tmp/bw_bcopy_unrolled.bg \
	tmp/bw_mem_rdsum.bg \
	tmp/bw_mem_wr.bg

BG=	$(MISC) $(PROC) $(LATENCY) $(BANDWIDTH)

I 11
MK=@$(MAKE) -s
E 11
PRINT=groff -p | lpr -h
D 11
PS8UP=groff -p | mpage -P -8 -a | $(SCRIPTS)save PS/PS8
I 5
PS4UP=groff -p | mpage -P -4 -a | $(SCRIPTS)save PS/PS4
SIZE=-big
GIF=pbm
#GIF=gifmono
E 11
I 11
PS=groff -p | $(SCRIPTS)save PS/PS
PS8UP=groff -p | mpage -P- -8 -a | $(SCRIPTS)save PS/PS8
PS4UP=groff -p | mpage -P- -4 -a | $(SCRIPTS)save PS/PS4
SIZE=-big 
IMAGE=pbm
CLOSE=
GMEM=$(CLOSE) -grid -logx -xm -below
GCTX=$(CLOSE) -grid -below
GDISK=-below -close -grid -nolines
#IMAGE=gifmono
E 11
E 5

I 7
D 8
get:	# nothing to do

E 8
E 7
D 12
summary:
E 12
I 12
summary: $(SRCS)
E 12
	@$(SCRIPTS)getsummary $(LIST)

D 12
percent:
E 12
I 12
percent: $(SRCS)
E 12
	@$(SCRIPTS)getpercent $(LIST)

I 11
D 12
stats:
E 12
I 12
stats: $(SRCS)
E 12
	$(SCRIPTS)getsummary $(LIST) | $(SCRIPTS)percent

E 11
roff:
	echo .nf	> summary.roff
	echo .ft CB	>> summary.roff
	echo .ps 12	>> summary.roff
	echo .po .35i	>> summary.roff
	echo .sp .5i	>> summary.roff
D 5
	make summary	>> summary.roff
E 5
I 5
	make LIST="$(LIST)" summary	>> summary.roff
E 5
	echo .bp	>> summary.roff
	echo .sp .5i	>> summary.roff
D 5
	make percent	>> summary.roff
E 5
I 5
	make LIST="$(LIST)" percent	>> summary.roff
E 5

list:
	@echo $(LIST)

D 11
print: bargraphs ctx mem
E 11
I 11
print: ctx mem disk bwfile bwmem
E 11

8:
D 11
	make LIST="$(LIST)" PRINT="groff -p | mpage -P -8 -a | lpr -h" print
E 11
I 11
	$(MK) LIST="$(LIST)" PRINT="groff -p | mpage -P -8 -a | lpr -h" print
E 11

8.ps 8ps 8up:
D 11
	make LIST="$(LIST)" PRINT="$(PS8UP)" print
E 11
I 11
	$(MK) LIST="$(LIST)" PRINT="$(PS8UP)" print
E 11

I 5
4.ps 4ps 4up:
D 11
	make LIST="$(LIST)" PRINT="$(PS4UP)" print
E 11
I 11
	$(MK) LIST="$(LIST)" PRINT="$(PS4UP)" print
E 11

E 5
ps:
D 11
	make LIST="$(LIST)" PRINT="groff -p | $(SCRIPTS)save PS/PS" print
E 11
I 11
	$(MK) LIST="$(LIST)" PRINT="$(PS)" print
E 11

I 5
smallps:
D 11
	make LIST="$(LIST)" SIZE= PRINT="groff -p | $(SCRIPTS)save PS/smallPS" print
E 11
I 11
	$(MK) LIST="$(LIST)" SIZE= PRINT="groff -p | $(SCRIPTS)save PS/smallPS" print
E 11

E 5
x: 
D 11
	make LIST="$(LIST)" PRINT="$(SCRIPTS)xroff -p" print
E 11
I 11
	$(MK) LIST="$(LIST)" PRINT="$(SCRIPTS)xroff -p" print
E 11

I 10
ctx.x: 
D 11
	make LIST="$(LIST)" PRINT="$(SCRIPTS)xroff -p" ctx
E 11
I 11
	$(MK) LIST="$(LIST)" PRINT="$(SCRIPTS)xroff -p" ctx
E 11

I 11
ctx.ps4:
	$(MK) LIST="$(LIST)" PRINT="$(PS4UP)" ctx

E 11
E 10
I 9
mem.x: 
D 11
	make LIST="$(LIST)" PRINT="$(SCRIPTS)xroff -p" mem
E 11
I 11
	$(MK) LIST="$(LIST)" PRINT="$(SCRIPTS)xroff -p" mem
E 11

I 11
disk.x: 
	$(MK) LIST="$(LIST)" PRINT="$(SCRIPTS)xroff -p" disk

bwfile.ps: 
	$(MK) LIST="$(LIST)" PRINT="$(PS)" bwfile

bwfile.x: 
	$(MK) LIST="$(LIST)" PRINT="$(SCRIPTS)xroff -p" bwfile

bwmem.ps: 
	$(MK) LIST="$(LIST)" PRINT="$(PS)" bwmem

bwmem.x: 
	$(MK) LIST="$(LIST)" PRINT="$(SCRIPTS)xroff -p" bwmem

E 11
E 9
I 5
smallx:
D 11
	make LIST="$(LIST)" PRINT="$(SCRIPTS)xroff -p" SIZE= print
E 11
I 11
	$(MK) LIST="$(LIST)" PRINT="$(SCRIPTS)xroff -p" SIZE= print
E 11

slides:
D 11
	make LIST="$(LIST)" SIZE=-slide bargraphs.slides ctx.slides mem.slides
E 11
I 11
	$(MK) LIST="$(LIST)" SIZE=-slide bargraphs.slides ctx.slides mem.slides
E 11

I 6
paper:
D 11
	make LIST="$(LIST)" tbl.paper ctx.paper mem.paper
E 11
I 11
	$(MK) LIST="$(LIST)" tbl.paper ctx.paper mem.paper
E 11

I 11
# XXX - this has to be made incremental, doing everything over from
# scratch makes you want a Ghz machine.
E 11
E 6
html:
	-make clean
D 11
	$(SCRIPTS)bghtml $(BG)
E 11
I 11
	#$(SCRIPTS)bghtml $(BG)
E 11
	$(SCRIPTS)html-list $(LIST)
D 11
	make LIST="$(LIST)" summary > HTML/summary
	make LIST="$(LIST)" percent > HTML/percent
	make LIST="$(LIST)" SIZE= PRINT="groff -p | $(SCRIPTS)save PS/PS" print
	make LIST="$(LIST)" SIZE= SHARP="#" PRINT="groff -p | $(SCRIPTS)save PS/PS" mem ctx
	gs -sOutputFile=HTML/bar%02d.$(GIF) -sDEVICE=$(GIF) -q -dNOPAUSE PS/PS < /dev/null
	gs -sOutputFile=HTML/ctx%02d.$(GIF) -sDEVICE=$(GIF) -q -dNOPAUSE PS/PS.1 < /dev/null
	gs -sOutputFile=HTML/mem%02d.$(GIF) -sDEVICE=$(GIF) -q -dNOPAUSE PS/PS.2 < /dev/null
	gs -sOutputFile=HTML/mem-unscaled%02d.$(GIF) -sDEVICE=$(GIF) -q -dNOPAUSE PS/PS.3 < /dev/null
	gs -sOutputFile=HTML/ctx-unscaled%02d.$(GIF) -sDEVICE=$(GIF) -q -dNOPAUSE PS/PS.4 < /dev/null
	$(SCRIPTS)/gifs $(GIF)
	# rm HTML/*.bpm HTML/*.gifmono
E 11
I 11
	$(MK) LIST="$(LIST)" summary > HTML/summary
	#make LIST="$(LIST)" percent > HTML/percent
	$(MK) LIST="$(LIST)" SIZE=  PRINT="$(PS)" \
	    GMEM="$(GMEM) -cut -gthk1" GCTX="$(GCTX) -cut -gthk1" print
	$(MK) LIST="$(LIST)" SIZE= NOOP=-noop PRINT="$(PS)" \
	    GMEM="$(GMEM) -cut -gthk1" GCTX="$(GCTX) -cut -gthk1" print
	gs -sOutputFile=HTML/ctx%02d.$(IMAGE) -sDEVICE=$(IMAGE) -q -dNOPAUSE PS/PS < /dev/null
	gs -sOutputFile=HTML/mem%02d.$(IMAGE) -sDEVICE=$(IMAGE) -q -dNOPAUSE PS/PS.1 < /dev/null
	gs -sOutputFile=HTML/disk%02d.$(IMAGE) -sDEVICE=$(IMAGE) -q -dNOPAUSE PS/PS.2 < /dev/null
	gs -sOutputFile=HTML/bwfile%02d.$(IMAGE) -sDEVICE=$(IMAGE) -q -dNOPAUSE PS/PS.3 < /dev/null
	gs -sOutputFile=HTML/bwmem%02d.$(IMAGE) -sDEVICE=$(IMAGE) -q -dNOPAUSE PS/PS.4 < /dev/null
	gs -sOutputFile=HTML/ctx-unscaled%02d.$(IMAGE) -sDEVICE=$(IMAGE) -q -dNOPAUSE PS/PS.5 < /dev/null
	gs -sOutputFile=HTML/mem-unscaled%02d.$(IMAGE) -sDEVICE=$(IMAGE) -q -dNOPAUSE PS/PS.6 < /dev/null
	gs -sOutputFile=HTML/bwfile-unscaled%02d.$(IMAGE) -sDEVICE=$(IMAGE) -q -dNOPAUSE PS/PS.7 < /dev/null
	gs -sOutputFile=HTML/bwmem-unscaled%02d.$(IMAGE) -sDEVICE=$(IMAGE) -q -dNOPAUSE PS/PS.8 < /dev/null
	$(SCRIPTS)/gifs
	rm HTML/*.pbm HTML/___tmp*
E 11

bghtml:
	$(SCRIPTS)bghtml $(BG)

html-list:
	$(SCRIPTS)html-list $(LIST)

I 11
ctx: dirs
	$(SCRIPTS)getctx $(LIST) > tmp/FILES
	@if [ -s tmp/FILES ]; \
	then	$(SCRIPTS)getmax $(NOOP) -graph `cat tmp/FILES`; \
		for i in `cat tmp/FILES`; \
		do	$(SCRIPTS)graph $(SIZE) $(GCTX) $$i; \
			echo .bp; \
		done | sed '$$d' | $(PRINT); \
	else	echo No context switch data in $(LIST); \
	fi
E 11

E 5
D 11
mem:
	-@mkdir tmp PS 2>/dev/null
	$(SCRIPTS)getmem $(LIST)
	for i in $(LIST); \
	do	f=`basename $$i`; \
D 5
		$(SCRIPTS)graph -close -big -nomarks -logx -xm tmp/mem.$$f; \
E 5
I 5
		MEM="$${MEM}tmp/mem.$$f "; \
	done; \
	$(SHARP)$(SCRIPTS)getmax -graph $$MEM; \
	for i in $(LIST); \
	do	f=`basename $$i`; \
		$(SCRIPTS)graph -close $(SIZE) -nomarks -logx -xm tmp/mem.$$f; \
E 11
I 11
disk: dirs
	if [ X$(NOOP) = X ]; then \
		$(SCRIPTS)getdisk $(LIST) > tmp/FILES; \
		if [ -s tmp/FILES ]; \
		then	for i in `cat tmp/FILES`; \
			do	$(SCRIPTS)graph $(SIZE) $(GDISK) $$i; \
				echo .bp; \
        		done | sed '$$d' | $(PRINT); \
		else	echo No disk data in $(LIST); \
		fi; \
	fi

mem: dirs
	$(SCRIPTS)getmem $(LIST) > tmp/FILES
	if [ -s tmp/FILES ]; \
	then	$(SCRIPTS)getmax $(NOOP) -graph `cat tmp/FILES`; \
		for i in `cat tmp/FILES`; \
		do	$(SCRIPTS)graph $(SIZE) $(GMEM) -nomarks $$i; \
			echo .bp; \
        	done | sed '$$d' | $(PRINT); \
	else	echo No memory latency data in $(LIST); \
	fi

bwfile: dirs
	$(SCRIPTS)getbw $(LIST) > tmp/FILES
	if [ -s tmp/FILES ]; \
	then	$(SCRIPTS)getmax $(NOOP) -graph `cat tmp/FILES`; \
		for i in `cat tmp/FILES`; \
		do	$(SCRIPTS)graph $(SIZE) $(GMEM) -logy $$i; \
			echo .bp; \
        	done | sed '$$d' | $(PRINT); \
	else	echo No file bandwidth data in $(LIST); \
	fi

bwmem: dirs
	$(SCRIPTS)getbw -all $(LIST) > tmp/FILES
	if [ -s tmp/FILES ]; \
	then	$(SCRIPTS)getmax $(NOOP) -graph `cat tmp/FILES`; \
		for i in `cat tmp/FILES`; \
		do	$(SCRIPTS)graph -halfgrid -gthk_5 -thk2 -medium \
			    -nomarks -nolabels -grapheach $(GMEM) \
			    -logy %P="'`basename $$i`'" $$i; \
			echo .bp; \
        	done | sed '$$d' | $(PRINT); \
	else	echo No memory bandwidth data in $(LIST); \
	fi

tbl.paper:
	$(SCRIPTS)getbg -paper $(LIST) 


bargraphs.1st: dirs
	$(SCRIPTS)getbg -nosort $(LIST)
	#$(SCRIPTS)getmax -v $(PROC)
	#$(SCRIPTS)getmax -v $(LATENCY)
	#$(SCRIPTS)getmax -v -half $(BANDWIDTH)

bargraphs: bargraphs.1st
	for i in $(BG); \
	do	$(SCRIPTS)bargraph $(SIZE) -nobox -sideways $$i; \
E 11
E 5
		echo .bp; \
D 11
        done | $(PRINT)
E 11
I 11
        done | sed '$$d' | $(PRINT)
E 11

I 11
bargraphs.slides: bargraphs.1st
	for i in $(BG); \
	do	$(SCRIPTS)bargraph $(SIZE) -nobox -sideways $$i > $${i}.pic; \
        done 

bargraphs.8up: bargraphs.1st
	for i in $(BG); \
	do	$(SCRIPTS)bargraph -sideways $(SIZE) -nobox $$i; \
		echo .bp; \
	done | sed '$$d' | $(PS8UP)

latency.8up: bargraphs.1st
	for i in $(LATENCY); \
	do	$(SCRIPTS)bargraph -sideways $(SIZE) -nobox $$i; \
		echo .bp; \
	done | sed '$$d' | $(PS8UP)

bw.8up: bargraphs.1st
	for i in $(BANDWIDTH); \
	do	$(SCRIPTS)bargraph -sideways $(SIZE) -nobox $$i; \
		echo .bp; \
	done | sed '$$d' | $(PS8UP)

get:	# nothing to do
E 11
I 6
D 11
mem.paper:
	-@mkdir tmp PS 2>/dev/null
	$(SCRIPTS)allmem $(LIST) | \
	$(SCRIPTS)graph -close -small -nolabels -nodatal \
	-thk1_5 -nomarks -grapheach -logx -xm > tmp/mem.pic
E 11

E 6
I 5
D 11
mem.slides:
	-@mkdir tmp PS 2>/dev/null
	$(SCRIPTS)getmem $(LIST)
	for i in $(LIST); \
	do	f=`basename $$i`; \
		MEM="$${MEM}tmp/mem.$$f "; \
	done; \
	$(SHARP)$(SCRIPTS)getmax -graph $$MEM; \
	for i in $(LIST); \
	do	f=`basename $$i`; \
		$(SCRIPTS)graph -close $(SIZE) -nomarks -logx -xm tmp/mem.$$f > tmp/mem.$$f.pic; \
        done 

mem.smallgif:
	-@mkdir tmp PS 2>/dev/null
	$(SCRIPTS)getmem $(LIST)
	for i in $(LIST); \
	do	f=`basename $$i`; \
		MEM="$${MEM}tmp/mem.$$f "; \
	done; \
	# $(SCRIPTS)getmax -graph $$MEM; \
	for i in $(LIST); \
	do	f=`basename $$i`; \
		$(SCRIPTS)graph -close -nodatal -nomarks -logx -xm tmp/mem.$$f | \
		groff -p | \
		gs -sDEVICE=$(GIF) -IGS -sPAPERSIZE=lmgraph -q \
		-sOutputFile=HTML/mem.$$f.smallgif -; \
        done 

E 5
ctx:
	-@mkdir PS tmp 2>/dev/null
	$(SCRIPTS)getctx $(LIST)
	for i in $(LIST); \
	do	f=`basename $$i`; \
D 5
		$(SCRIPTS)graph -big -below tmp/ctx.$$f; \
E 5
I 5
		CTX="$${CTX}tmp/ctx.$$f "; \
	done; \
	for i in $(LIST); \
	do	f=`basename $$i`; \
		$(SCRIPTS)graph $(SIZE) -below tmp/ctx.$$f; \
E 5
		echo .bp; \
	done | $(PRINT)

I 5
#	$(SHARP)$(SCRIPTS)getmax -graph $$CTX; 

I 6
ctx.paper:
	-@mkdir PS tmp 2>/dev/null
	$(SCRIPTS)allctx $(LIST) | \
	$(SCRIPTS)graph -nolabels -nomarks -thk1_5 \
	-nodatal -small -close -br_title > tmp/ctx.pic

E 6
ctx.slides:
	-@mkdir PS tmp 2>/dev/null
	$(SCRIPTS)getctx $(SIZE) $(LIST)
	for i in $(LIST); \
	do	f=`basename $$i`; \
		CTX="$${CTX}tmp/ctx.$$f "; \
	done; \
	$(SHARP)$(SCRIPTS)getmax -graph $$CTX; \
	for i in $(LIST); \
	do	f=`basename $$i`; \
		$(SCRIPTS)graph $(SIZE) tmp/ctx.$$f > tmp/ctx.$$f.pic; \
	done 

I 6
tbl.paper:
	$(SCRIPTS)getbg -paper $(LIST) 

E 6
E 5
bargraphs.1st:
	-@mkdir PS tmp 2>/dev/null
D 5
	$(SCRIPTS)getbg $(LIST)
	$(SCRIPTS)getmax $(LATENCY)
	$(SCRIPTS)getmax $(BANDWIDTH)
E 5
I 5
	$(SCRIPTS)getbg $(SIZE) -nosort $(LIST)
	#$(SCRIPTS)getmax -v $(PROC)
	#$(SCRIPTS)getmax -v $(LATENCY)
	#$(SCRIPTS)getmax -v -half $(BANDWIDTH)
E 5

bargraphs: bargraphs.1st
	for i in $(BG); \
D 5
	do	$(SCRIPTS)bargraph -big -nobox $$i; \
E 5
I 5
	do	$(SCRIPTS)bargraph $(SIZE) -nobox -sideways $$i; \
E 5
		echo .bp; \
        done | $(PRINT)

I 5
bargraphs.slides: bargraphs.1st
	for i in $(BG); \
	do	$(SCRIPTS)bargraph $(SIZE) -nobox -sideways $$i > $${i}.pic; \
        done 

E 5
bargraphs.8up: bargraphs.1st
	for i in $(BG); \
D 5
	do	$(SCRIPTS)bargraph -big -nobox $$i; \
E 5
I 5
	do	$(SCRIPTS)bargraph -sideways $(SIZE) -nobox $$i; \
E 5
		echo .bp; \
	done | $(PS8UP)

latency.8up: bargraphs.1st
	for i in $(LATENCY); \
D 5
	do	$(SCRIPTS)bargraph -big -nobox $$i; \
E 5
I 5
	do	$(SCRIPTS)bargraph -sideways $(SIZE) -nobox $$i; \
E 5
		echo .bp; \
	done | $(PS8UP)

bw.8up: bargraphs.1st
	for i in $(BANDWIDTH); \
D 5
	do	$(SCRIPTS)bargraph -big -nobox $$i; \
E 5
I 5
	do	$(SCRIPTS)bargraph -sideways $(SIZE) -nobox $$i; \
E 5
		echo .bp; \
	done | $(PS8UP)

I 8
get:	# nothing to do

E 11
E 8
clean:
D 4
	/bin/rm -f PS/* tmp/* 
E 4
I 4
D 5
	/bin/rm -f PS/* tmp/* summary.roff
E 5
I 5
	/bin/rm -f PS/* GIF/* HTML/* tmp/* summary.roff
I 12
	-bk clean
E 12
I 11

dirs:
	@if [ ! -d tmp ]; then mkdir tmp; fi
	@if [ ! -d PS ]; then mkdir PS; fi
	@if [ ! -d HTML ]; then mkdir HTML; fi
E 11
E 5
E 4
E 2
I 1
E 1
