H60794
s 00116/00672/01161
d D 1.5 02/06/06 09:15:39 staelin 6 5
c Updated paper describing lmbench3's scalability
cC
cHhpli69.hpli.hpl.hp.com
cK28006
cZ+03:00
e
s 00174/00036/01659
d D 1.4 02/01/07 23:28:57 staelin 5 4
c Lost of revisions and new content
cC
cHfirewall.staelin.co.il
cK49929
e
s 00344/00101/01351
d D 1.3 02/01/07 17:14:17 staelin 4 3
c Another rewrite; added some more results; ...
cC
cHhpli69.hpli.hpl.hp.com
cK33981
e
s 00195/00039/01257
d D 1.2 02/01/04 13:06:02 staelin 3 2
c Revised; Added some figures and tables; Added some more information to
c the architecture primer
cC
cHfirewall.staelin.co.il
cK08235
e
s 01296/00000/00000
d D 1.1 01/12/31 16:48:02 staelin 2 1
cC
cF1
cK02631
cO-rwxrwxr--
e
s 00000/00000/00000
d D 1.0 01/12/31 16:48:02 staelin 1 0
c BitKeeper file /usr/WebPaper/users/staelin/src/LMbench3/doc/lmbench3.ms
cBlm@lm.bitmover.com|ChangeSet|20000131225335|47351|--LMBENCH--
cHhpli69.hpli.hpl.hp.com
cK63657
cPdoc/lmbench3.ms
cRf24c2467a20d143
cV4
cX0x821
cZ+02:00
e
u
U
f e 0
f x 0x821
t
T
I 2
.\" This document is GNU groff -mgs -t -p -R -s
.\" It will not print with normal troffs, it uses groff features, in particular,
.\" long names for registers & strings.
.\" Deal with it and use groff - it makes things portable.
.\"
.\" $X$ xroff -mgs -t -p -R -s $file
.\" $tty$ groff -mgs -t -p -R -s $file | colcrt - | more
.\" $lpr$ groff -mgs -t -p -R -s $file > ${file}.lpr
.VARPS
.\" Define a page top that looks cool
.\" HELLO CARL!  To turn this off, s/PT/oldPT/
D 6
.de draftPT
.\" .tl '\fBDRAFT\fP'Printed \\*(DY'\fBDRAFT\fP'
E 6
I 6
.de PT
.tl '\fBDRAFT\fP'\\*(DY'\fBDRAFT\fP'
E 6
..
.de lmPT
.if \\n%>1 \{\
.	sp -.1i
.	ps 14
.	ft 3
.	nr big 24
.	nr space \\w'XXX'
.	nr titlewid \\w'\\*[title]'
.	nr barwid (\\n[LL]-(\\n[titlewid]+(2*\\n[space])))/2
.	ds ln \\l'\\n[barwid]u'\\h'-\\n[barwid]u'\v'-.25'
.	ds bar \\s(\\n[big]\\*(ln\\*(ln\\*(ln\\*(ln\\*(ln\v'1.25'\\h'\\n[barwid]u'\\s0
.	ce 1
\\*[bar]\h'\\n[space]u'\v'-.15'\\*[title]\v'.15'\h'\\n[space]u'\\*[bar]
.	ps
.	sp -.70
.	ps 12
\\l'\\n[LL]u'
.	ft
.	ps
.\}
..
.\" Define a page bottom that looks cool
.\" HELLO CARL!  To turn this off, s/BT/oldBT/
D 6
.de draftBT
.\" .tl '\fBDRAFT\fP'Page %'\fBDRAFT\fP'
E 6
I 6
.de BT
.tl '\fBDRAFT\fP'Page %'\fBDRAFT\fP'
E 6
..
.de lmBT
.	ps 9
\v'-1'\\l'\\n(LLu'
.	sp -1
D 6
.	tl '\(co 2001 \\*[author]'\\*(DY'%'
E 6
I 6
.	tl '\(co 2002 \\*[author]'\\*(DY'%'
E 6
.	ps
..
.de SP
.	if t .sp .5
.	if n .sp 1
..
.de BU
.	SP
.	ne 2
\(bu\ 
.	if \\n[.$] \fB\\$1\fP\\$2
..
.nr FIGURE 0
.nr TABLE 0
.nr SMALL .25i
.de TSTART
.	KF
.	if \\n[.$] \s(24\\l'\\n[pg@colw]u'\s0
.	ps -1
.	vs -1
..
.de TEND
.	ps +1
.	vs +1
.	if \\n[.$]=2 \{\
.	sp -.5
\s(24\\l'\\n[pg@colw]u'\s0 \}
.	sp .25
.	nr TABLE \\n[TABLE]+1
.	ce 1
\fBTable \\n[TABLE].\ \ \\$1\fP
.	SP
.	KE
..
.de FEND
.	ps +1
.	vs +1
.	if \\n[.$]=2 \{\
.	sp -.5
\s(24\\l'\\n[pg@colw]u'\s0 \}
.	sp .25
.	nr FIGURE \\n[FIGURE]+1
.	ce 1
\fBFigure \\n[FIGURE].\ \ \\$1\fP
.	SP
.	KE
..
.\" Configuration
.nr PI 3n
.nr HM 1i
.nr FM 1i
.nr PO 1i
.if t .po 1i
.nr LL 6.5i
.if n .nr PO 0i
.if n .nr LL 7.5i
.nr PS 10
.nr VS \n(PS+1
.ds title Measuring scalability
.ds author Carl Staelin
.ds lmbench \f(CWlmbench\fP
I 6
.ds lmbench1 \f(CWlmbench1\fP
E 6
.ds lmbench2 \f(CWlmbench2\fP
.ds lmbench3 \f(CWlmbench3\fP
D 6
.ds lmdd  \f(CWlmdd\fP
E 6
.ds bcopy \f(CWbcopy\fP
I 6
.ds benchmp  \f(CWbenchmp\fP
.ds bw_file_rd \f(CWbw_file_rd\fP
.ds bw_mem \f(CWbw_mem\fP
.ds bw_mmap_rd \f(CWbw_mmap_rd\fP
.ds bw_pipe \f(CWbw_pipe\fP
.ds bw_tcp \f(CWbw_tcp\fP
.ds bw_udp \f(CWbw_udp\fP
.ds bw_unix \f(CWbw_unix\fP
.ds close \f(CWclose\fP
E 6
.ds connect \f(CWconnect\fP
.ds execlp  \f(CWexeclp\fP
I 4
.ds execve  \f(CWexecve\fP
E 4
.ds exit \f(CWexit\fP
I 4
.ds fcntl \f(CWfcntl\fP
E 4
.ds fork \f(CWfork\fP
I 6
.ds fstat \f(CWfstat\fP
E 6
.ds gcc \f(CWgcc\fP
D 6
.ds getpid \f(CWgetpid\fP
E 6
I 6
.ds getppid \f(CWgetppid\fP
E 6
.ds getpid \f(CWgetpid\fP
.ds gettimeofday \f(CWgettimeofday\fP
.ds kill \f(CWkill\fP
D 6
.ds memmove \f(CWmemmove\fP
.ds mmap \f(CWmmap\fP
.ds popen  \f(CWpopen\fP
I 4
.ds pipe  \f(CWpipe\fP
E 4
.ds read \f(CWread\fP
I 4
.ds semop \f(CWsemop\fP
E 4
.ds stream \f(CWstream\fP
.ds system  \f(CWsystem\fP
.ds uiomove \f(CWuiomove\fP
.ds write \f(CWwrite\fP
.ds yield  \f(CWyield\fP
.ds select  \f(CWselect\fP
I 4
.ds sh  \f(CW/bin/sh\fP
E 4
.ds benchmp  \f(CWbenchmp\fP
.ds mhz  \f(CWmhz\fP
D 4
.ds lat_ops  \f(CWlat_ops\fP
.ds lat_connect  \f(CWlat_connect\fP
E 4
I 4
.ds bw_file_rd \f(CWbw_file_rd\fP
.ds bw_mem \f(CWbw_mem\fP
.ds bw_mmap_rd \f(CWbw_mmap_rd\fP
.ds bw_pipe \f(CWbw_pipe\fP
.ds bw_tcp \f(CWbw_tcp\fP
.ds bw_udp \f(CWbw_udp\fP
.ds bw_unix \f(CWbw_unix\fP
E 6
.ds lat_connect \f(CWlat_connect\fP
.ds lat_ctx \f(CWlat_ctx\fP
.ds lat_fcntl \f(CWlat_fcntl\fP
.ds lat_fifo \f(CWlat_fifo\fP
.ds lat_fs \f(CWlat_fs\fP
.ds lat_http \f(CWlat_http\fP
.ds lat_mem_rd \f(CWlat_mem_rd\fP
.ds lat_mmap \f(CWlat_mmap\fP
.ds lat_ops \f(CWlat_ops\fP
.ds lat_pagefault \f(CWlat_pagefault\fP
.ds lat_pipe \f(CWlat_pipe\fP
.ds lat_proc \f(CWlat_proc\fP
.ds lat_rpc \f(CWlat_rpc\fP
.ds lat_select \f(CWlat_select\fP
.ds lat_sem \f(CWlat_sem\fP
.ds lat_sig \f(CWlat_sig\fP
.ds lat_syscall \f(CWlat_syscall\fP
.ds lat_tcp \f(CWlat_tcp\fP
.ds lat_udp \f(CWlat_udp\fP
.ds lat_unix \f(CWlat_unix\fP
.ds lat_unix_connect \f(CWlat_unix_connect\fP
.ds line \f(CWline\fP
D 6
.ds tlb \f(CWtlb\fP
.ds stream \f(CWstream\fP
E 6
I 6
.ds lmdd  \f(CWlmdd\fP
E 6
.ds lmdd \f(CWlmdd\fP
I 6
.ds memmove \f(CWmemmove\fP
.ds mhz  \f(CWmhz\fP
.ds mmap \f(CWmmap\fP
.ds open \f(CWopen\fP
E 6
.ds par_mem  \f(CWpar_mem\fP
E 4
.ds par_ops  \f(CWpar_ops\fP
I 6
.ds pipe  \f(CWpipe\fP
.ds popen  \f(CWpopen\fP
.ds read \f(CWread\fP
.ds select  \f(CWselect\fP
.ds semop \f(CWsemop\fP
.ds sh  \f(CW/bin/sh\fP
.ds stream \f(CWstream\fP
.ds stat \f(CWstat\fP
.ds system  \f(CWsystem\fP
.ds tlb \f(CWtlb\fP
.ds uiomove \f(CWuiomove\fP
.ds write \f(CWwrite\fP
.ds yield  \f(CWyield\fP
E 6
.\" References stuff
.de RN  \"Reference Name: .RN $1 -- prints the reference prettily
.\" [\s-2\\$1\s+2]\\$2
[\s-1\\$1\s0]\\$2
..
.\" .R1
.\" sort A+DT
.\" database references
.\" label-in-text
.\" label A.nD.y-2
.\" bracket-label \*([. \*(.] ", "
.\" .R2
.EQ
delim $$
.EN
.TL
\s(14lmbench3: Measuring scalability\s0
.AU
\s+2\fR\*[author]\fP\s0
.AI
\fI\s+2Hewlett-Packard Laboratories Israel\s0\fP
.SP
.AB
I 5
D 6
\*[lmbench] is a portable, extensible suite of micro-
benchmarks which measure a variety of important features
of system performance.
E 5
\*[lmbench] version 3 incorporates a new timing harness,
benchmp, designed to measure performance at specific levels 
of parallel (simultaneous) load.  It also incorporates some
new micro-benchmarks to measure basic system operations
and scalability, such as arithmetic operations and the
D 3
memory hierarchy.
.\" .SP
\*[lmbench]'s new capabilities for analyzing the memory 
hierarchy are discussed in greater detail in another 
paper.
E 3
I 3
basic elements of the memory hierarchy.
E 3
.\" .SP
E 6
I 6
\*[lmbench3] extends the \*[lmbench2] system to
measure a system's performance under scalable load.
There is a new timing harness, \*[benchmp], designed 
to measure performance at specific levels of parallel 
(simultaneous) load, and most existing benchmarks have
been converted to use the new harness.
.SP
E 6
\*[lmbench] is a micro-benchmark suite designed to focus
attention on the basic building blocks of many
common system applications, such as databases, simulations, 
software development, and networking.  
I 6
It is also designed to make it easy for users to create
additional micro-benchmarks that can measure features, 
algorithms, or subsystems of particular interest to the
user.
E 6
.AE
.if t .MC 3.05i
.NH 1
Introduction
.LP
I 4
\*[lmbench] is a widely used suite of micro-benchmarks
that measures important aspects of computer system
performance, such as memory latency and bandwidth.
Crucially, the suite is written in portable ANSI-C
using POSIX interfaces and is intended to run on a 
wide range of systems without modification.
.LP
The benchmarks included in the suite were chosen
because in the \*[lmbench] developer's experience,
they each represent an aspect of system performance
which has been crucial to an application's
performance.  
.LP
In general the benchmarks report either the latency
or bandwidth of an operation or data pathway.  The
exceptions are generally those benchmarks that
report on a specific aspect of the hardware, such
as the processor clock rate, which is reported 
in MHz and nanoseconds.
.LP
\*[lmbench] consists of three major components:
a timing harness, the individual benchmarks
built on top of the timing harness, and the
various scripts and glue that build and run the 
benchmarks and process the results.
.NH 2
\*[lmbench] history
.LP
D 6
\*[lmbench] version 1 was written by Larry McVoy
while he was at Sun Microsystems.  It 
E 6
I 6
\*[lmbench1] was written by Larry McVoy
while he was at Sun Microsystems.  It focussed
on two measures of system performance: latency
and bandwidth.  It measured a number of basic
operating system functions, such as file system
read/write bandwidth or file creation time.  It
also focussed a great deal of energy on measuring
data transfer operations, such as \*[bcopy] and
\*[pipe] latency and bandwidth as well as raw
memory latency and bandwidth.
.LP
Shortly after 
.RN McVoy96
was published, 
.RN Brown97
examined the \*[lmbench] benchmarks and published
a detailed critique of its strengths and weaknesses.
Largely in response to these remarks, development
of \*[lmbench2] began with a focus on
improving the experimental design and statistical
data analysis.  The primary change was the development
and adoption across all the benchmarks of a timing 
harness that incorporated loop-autosizing and clock 
resolution detection.  In addition, each experiment
was typically repeated eleven times with the median
result reported to the user.
E 6
.LP
D 6
\*[lmbench] version 3 focussed on extending 
E 6
I 6
\*[lmbench3] focussed on extending 
E 6
\*[lmbench]'s functionality along two dimensions:
measuring multi-processor scalability and measuring
D 6
basic aspects of processor architecture.
.LP
There are any number of aspects of a computer's
micro-architecture that can impact a program's
performance, such as the design of the memory
hierarchy and the basic performance of the various
arithmetic units.
.LP
All of the new benchmarks were added to \*[lmbench]
because the author needed them to help guide his
design decisions in one or more projects over the
last few years.  
For example, \*[lat_ops] was added because the
author was trying to decide whether a particular
image processing algorithm should be implemented
using integer or floating point arithmetic.
Floating point arithmetic was preferred for a
variety of reasons, but it was feared that 
floating point arithmetic would be prohibitively
expensive compared to integer operations.
By quickly building \*[lat_ops] the author was
able to verify that the floating point performance
should be no worse than integer performance.
E 6
I 6
basic aspects of processor micro-architecture.
E 6
D 5
(See
E 5
.LP
E 4
An important feature of multi-processor systems is their
D 6
ability to scale their performance.  \*[lmbench] version
1 was able to measure various important aspects of 
E 6
I 6
ability to scale their performance.  \*[lmbench1]
was able to measure various important aspects of 
E 6
system performance, except that only one client process
was active at a time
.RN McVoy96 .
\*[lmbench2] introduced a new macro, BENCH(), which
implemented a sophisticated timing harness that
automatically managed nearly all aspects of accurately
timing operations
.RN Staelin98 .
For example, it automatically
detects the minimal timing interval necessary to 
provide timing results within 1% accuracy, and it
automatically repeats most experiments eleven times
and reports the median result.
.LP
However, this timing harness is incapable of measuring
the performance of a system under scalable loads.  
\*[lmbench3] took the ideas and techniques
developed in the earlier versions and extended them
to create a new timing harness which can measure
system performance under parallel, scalable loads.
.LP
\*[lmbench3] also includes a version of John 
McCalpin's STREAM benchmarks.  Essentially the STREAM 
kernels were placed in the new \*[lmbench] timing harness.
Since the new timing harness also measures scalability
D 6
under parallel load, the new \*[lmbench] version
includes this capability automatically.  
E 6
I 6
under parallel load, the \*[lmbench3] STREAM
benchmarks include this capability automatically.  
E 6
.LP
Finally, \*[lmbench3] includes a number of new
benchmarks which measure various aspects of the
processor architecture, such as basic operation
latency and parallelism, to provide developers
with a better understanding of system capabilities.
The hope is that better informed developers will
be able to better design and evaluate performance
critical software in light of their increased
understanding of basic system performance.
.NH 1
Prior Work
.LP
Benchmarking is not a new field of endeavor.
There are a wide variety of approaches to 
benchmarking, many of which differ greatly
from that taken by \*[lmbench].  
.LP
One common form of benchmark is to take an
important application or application and
worklist, and to measure the time required
to complete the entire task.  
This approach is particularly useful when 
evaluating the utility of systems for a 
single and well-known task.
.LP
Other benchmarks, such as SPECint, use a
variation on this approach by measuring
several applications and combining the
results to predict overall performance.
D 4
.LP
XXX Byte benchmark
E 4
I 4
.\" .LP
.\" XXX Byte benchmark
E 4
.LP
Another variation takes the "kernel" of
an important application and measures its
performance, where the "kernel" is usually
a simplification of the most expensive
portion of a program.  
Dhrystone 
.RN Weicker84
is an example of this type of
benchmark as it measures the performance
of important matrix operations and was often
used to predict system performance for
numerical operations.
.LP
.RN Banga98
developed a benchmark to measure HTTP server
performance which can accurately measure
server performance under high load.
Due to the idiosyncracies of the HTTP protocol 
and TCP design and implementation, there are 
generally operating system limits on the rate 
at which a single system can generate 
independent HTTP requests.  
However, 
.RN Banga98
developed a system which can scalably present
load to HTTP servers in spite of this limitation.
.LP
John McCalpin's STREAM benchmark measures
memory bandwidth during four common vector
operations
.RN McCalpin95 .
It does not measure memory latency, and
strictly speaking it does not measure raw
memory bandwith although memory bandwidth
is crucial to STREAM performance.
More recently, work has begun on extending
STREAM to measure scalable memory subsystem
performance, particularly for multi-processor
machines.
.LP
I 5
Uros Prestor
.RN Prestor01
XXX
.LP
E 5
Micro-benchmarking extends this "kernel" 
approach, by measuring the performance
of operations or resources in isolation.
\*[lmbench] and many other benchmarks, such 
as nfsstone
.RN Shein89 ,
measure the performance of key operations so 
users can predict performance for certain 
workloads and applications by combining the 
performance of these operations in the right 
mixture.
.LP
D 4
.RN Seltzer99
E 4
I 4
.RN Saavedra92
E 4
takes the micro-benchmark approach and applies
it to the problem of predicting application
performance. 
D 4
They instrument applications to determine the
basic components of application usage in terms
of the elements measured by \*[lmbench], and
then they predict application performance on
a variety of systems by combining the measured
resource requirements with the measured system
performance.
I 3
XXX I think someone else did this before Margo
E 4
I 4
They analyze applications or other benchmarks
in terms of their ``narrow spectrum benchmarks''
to create a linear model of the application's
computing requirements.  
They then measure the computer system's 
performance across this set of micro-benchmarks
and use a linear model to predict the application's
performance on the computer system.
.RN Seltzer99
applied this technique using the features
measured by \*[lmbench] as the basis for
application prediction.
E 4
E 3
.LP
Benchmarking I/O systems has proven particularly
troublesome over the years, largely due to the
strong non-linearities exhibited by disk systems.
Sequential I/O provides much higher bandwidth
than non-sequential I/O, so performance is 
highly dependent on the workload characteristics
as well as the file system's ability to 
capitalize on available sequentiality by
laying out data contiguously on disk.
.LP
I/O benchmarks have a tendency to age poorly.
For example, IOStone
D 5
.RN Park90a 
E 5
I 5
.RN Park90a ,
IOBench
.RN Wolman89 ,
E 5
and the Andrew benchmark
.RN Howard88
used fixed size datasets, whose size was
significant at the time, but which no longer
measure I/O performance as the data can now
fit in the processor cache of many modern
machines.
.LP
I 5
The Andrew benchmark attempts to separately
measure the time to create, write, re-read, 
and then delete a large number of files in
a hierarchical file system.  
.LP
E 5
Bonnie
.RN Bray90
measures sequential, streaming I/O bandwidth
D 5
for a single process.  
IOBench
.RN Wolman89
XXX
E 5
I 5
for a single process, and random I/O latency
for multiple processes.
E 5
.LP
Peter Chen developed an adaptive harness for
I/O benchmarking
.RN Chen94a ,
which defines I/O load in terms of five parameters,
uniqueBytes, sizeMean, readFrac, seqFrac, and
processNum.  The benchmark then explores the
parameter space to measure file system performance
in a scalable fashion.
I 3
D 5
.LP
The AIM benchmark... XXX
.LP
Prestor's memory analysis and Saavedra's work XXX
E 5
E 3
.NH 1
D 3
Computer architecture primer
E 3
I 3
D 6
Computer Architecture Primer
E 3
.LP
A processor architecture is generally defined by its
instruction set, but most computer architectures
incorporate a large number of common building blocks
and concepts, such as registers, arithmetic logic
units, and caches.
.LP
I 3
Of necessity, this primer over-simplifies the
many details and variations of specific computer
designs and architectures.  For more information,
please see 
.RN Hennessy96 .
.TSTART 1
.so lmbench3_arch.pic
.FEND "Architecture diagram" 1
.LP
Figure \n[FIGURE] contains a greatly simplified block diagram
of a computer.  Various important elements, such as
the I/O bus and devices, have been left out.  The
core of the processor are the registers (r0, ..., rn
and f0, ..., fn) and the arithmetic units (ALU and FPU).
In general, the arithmetic units can access data in
registers ''instantly''.  Often data must be explicitly
loaded from memory into a register before it can be
manipulated by the arithmetic units.
.LP
The ALU handles integer arithmetic, such as bit
operations (AND, OR, XOR, NOT, and SHIFT) as
well as ADD, MUL, DIV, and MOD.  Sometimes there
is specialized hardware to handle one or more
operations, such as a barrel shifter for SHIFT
or a multiplier, and sometimes there is no
hardware support for certain operations, such
as MUL, DIV, and MOD.  
.LP
The FPU handles floating point arithmetic.
Sometimes there are separate FPUs for single
and double precision floating point operations.
.NH 2
Memory Hierarchy
.LP
D 4
Nearly all modern processors use some form of virtual
memory addressing, meaning that each process has its
own virtual address space, or mapping of virtual 
addresses to physical addresses.  The core of the
system operates on virtual addresses, so addresses
must be translated to physical addresses in order
to actually read or write data to memory.  Most
machines do the translation between the core and
the top level cache using a ``translation look-aside
buffer'' (TLB), which is really a cache of virtual
to physical page mappings.
E 4
I 4
Nearly all modern, general purpose computers use
virtual memory with phyically addressed caches.
As such, there is typically one or more caches
between the physical memory and the processor,
and virtual-to-physical address translation
occurs between the processor and the top-level
cache.  Cache staging and replacement is done
in \fIcache line\fR units, which are typically
several words in length, and caches lower in 
the hierarchy sometimes have cache lines which
are larger than those in the higher caches.
E 4
.LP
D 4
Nearly all machines use at least some form of
data caching, and many machines have multiple
levels of cache.  A rule of thumb is that moving
down a level in hierarchy decreases the performance 
by at least a factor of two while the size increases 
by a factor of ten.
E 4
I 4
Modern processors usually incorporate at least
an L1 cache on-chip, and some are starting to
also incorporate the L2 cache on-chip.  In
addition, most include a translation look-aside
buffer (TLB) on-chip for fast virtual-to-physical
address translation.
E 4
.LP
D 4
Caches store and replace data in fixed size units, 
called ``lines''.  Cache lines are some multiple 
of the basic word size.  
E 4
I 4
One key element of any cache design is its
replacement strategy.  Most caches use either
direct-mapped or set associative caches.  In
the first instance any word in physical memory
has exactly one cache line where into which it
may be staged, while set associative caches
allow a given word to be cached into one of a
set of lines.  Direct-mapped caches have a 
very simple replacement policy: the contents
of the line that is needed is discarded.
Set associative caches usually use LRU or
some variant within each set, so the least
recently used line in the set of possible
cache lines is replaced.  The control logic
for direct-mapped caches is much cheaper to
build, but they are generally only as 
effective as a set-associative cache half
D 5
the size.\**
.FS 
See
.RN Hennessy96
page 396.
.FE
E 5
I 5
the size
.RN Hennessy96 .
E 5
E 4
.LP
D 4
In most cases, a write
to any location in a cache line which is not
currently resident in the cache will cause the
line to be read into the cache before the
dirty portion is over-written.  
E 4
I 4
Another key element of memory hierarchy design
is the management of dirty data; at what point
are writes passed down the memory hierarchy to
lower caches and main memory?  The two basic
policies are write-through and write-back.
A write-through policy means that writes are
immediately passed through the cache to the
next level in the hierarchy, so the lower
levels are updated at the same time as the
cache.  A write-back policy means that the
cache line is marked as dirty in the cache,
and only when the line is ejected from the
cache is the data passed down the hierarchy.
Write-through policies are often used in 
higher (smaller) caches because multi-
processor systems need to keep a coherent
view of memory and the writes are often
propagated to other processors by \fIsnoopy\fR
caches.
E 4
.LP
D 4
Cache replacement policies need to be fast, so
systems usually use some form of set-associative
replacement policy.  In this case, each word in
memory can be place into any of a set of lines.
If the set has a single member, then the cache
is called ``direct mapped'' because each location
in memory has a direct mapping to a single cache
line.  Typically large caches might be direct-
mapped, while smaller caches tend to have higher
levels of associativity.
E 4
I 4
One often overlooked aspect of cache
performance is cache behavior during
writes.  Most cache lines contain
several words, and most instructions
only update the line a word at a time.
This means that when the processor
writes a word to a cache line that is
not present, the cache will read the
line from memory before completing the
write operation.  For \*[bcopy]-like
operations this means that the overall
memory bandwidth requirement is actually
two reads and one write per copied word,
rather than the expected read and write.
.LP
Most modern processors now include some form
of prefetch in the memory hierarchy.  For
the most part these are simple systems that
can recognize fixed strided accesses through
memory, such as might be seen in many array
operations.  However, prefetching systems
appear to be growing in complexity and
capability.
.LP
Additionally, modern memory subsystems can
usually support multiple outstanding requests;
the level of parallelism is usually dependent
on the level of the hierarchy being accessed.
Top-level caches can sometimes support as 
many as six or eight outstanding requests,
while main memory can usually support two
outstanding requests.  Other elements of 
the memory hierarchy, such as the TLB, often
have additional limits on the level of
achievable parallelism in practice.\**
.FS 
For example, if the TLB serializes all
TLB misses, and if each memory access
causes a TLB miss, then the memory
accesses will be serialized even if
the data was in a cache supporting
six outstanding requests.
.FE
.LP
For more information and details on memory 
subsystem design, and computer architecture
in general, please see
.RN Hennessy96
which has an excellent description of these
and many other issues.
E 4
.NH 2
Some Recent Innovations
.LP
E 3
There are a number of modern extensions to computer
architecture that attempt to increase the processor's
ability to do several things at once.  Nearly all of
these enhancements are intended to be invisible to
programmers using higher-level languages such as
C or JAVA.
D 3
.IP "Superscalar processors"
E 3
I 3
.IP "\fBSuperscalar processors\fR"
E 3
Superscalar processors have multiple processing
units which can operate simultaneously.  
D 3
.IP "Dynamic instruction reordering"
E 3
I 3
.IP "\fBDynamic instruction reordering\fR"
E 3
Dynamic instruction reordering allows the processor
to execute instructions whose operands are ready
before instructions which are stalled waiting for
memory or other instruction's completion.
D 3
.IP "Memory parallelism"
E 3
I 3
.IP "\fBMemory parallelism\fR"
E 3
By allowing multiple outstanding memory requests,
processors allow the memory subsystem to service
multiple (independent) requests in parallel. 
Since memory accesses are a common performance
bottleneck, this can greatly improve performance.
D 3
.IP "Vector processing"
E 3
I 3
.IP "\fBVector processing\fR"
E 3
Vector processing allows the processor to execute
arithmetic operations on vector operands in 
parallel, and in modern commodity processors goes
by names such as MMX, SSE, and 3DNow.
D 3
.IP "Simultaneous multi-threading (SMT)"
E 3
I 3
.IP "\fBSimultaneous multi-threading (SMT)\fR"
E 3
SMT allows superscalar processors to simulatenously
execute instructions from several threads (contexts)
D 3
.RN Tullset96 .
E 3
I 3
.RN Tullsen96 .
E 3
SMT may include extensions which allow for very
lightweight inter-thread synchronization primitives
that enable much finer-grained thread-level 
parallelism than traditional synchronization
methods
.RN Tullsen99 .
D 3
.IP "Explicitly parallel instruction computers (EPIC)"
E 3
I 3
.IP "\fBExplicitly parallel instruction computers (EPIC)\fR"
E 3
EPIC allows the compiler to explicitly issue $N$
instructions in parallel at each instruction, which
informs the hardware that these instructions are
independent and may be executed in parallel
.RN Schlansker00 .
It moves much of the burden regarding dependency
checking from the hardware to the compiler.
.NH 1
E 6
D 3
Timing harness
E 3
I 3
Timing Harness
E 3
.LP
The first, and most crucial element in extending
\*[lmbench2] so that it could measure scalable
performance, was to develop a new timing harness
that could accurately measure performance for
any given load.
Once this was done, then each benchmark would
be migrated to the new timing harness.
.LP
I 3
The harness is designed to accomplish a number
of goals:
.IP 1.
during any timing interval of any child it is
guaranteed that all other child processes are
also running the benchmark
.IP 2.
the timing intervals are long enough to average
out most transient OS scheduler affects
.IP 3.
the timing intervals are long enough to ensure
that error due to clock resolution is negligible
.IP 4.
timing measurements can be postponed to allow
the OS scheduler to settle and adjust to the
load
I 5
.IP 5.
the reported results should be representative 
and the data analysis should be robust
.IP 6.
timing intervals should be as short as possible
while ensuring accurate results
E 5
.LP
E 3
Developing an accurate timing harness with a
valid experimental design is more difficult 
than is generally supposed.
Many programs incorporate elementary timing
harnesses which may suffer from one or more
defects, such as insufficient care taken to
ensure that the benchmarked operation is run
long enough to ensure that the error introduced 
by the clock resolution is insignificant.
The basic elements of a good timing harness
are discussed in 
.RN Staelin98 .
.LP
The new timing harness must also collect and process
the timing results from all the child processes so
that it can report the representative performance.
It currently reports the median performance over
all timing intervals from all child processes.  It
might perhaps be argued that it should report the
median of the medians.
.LP
Most of the benchmarks now accept a "-P <parallelism>"
flag, and the timing harness does the right thing to
try and measure parallel application performance.
I 4
.LP
When running benchmarks with more than one child,
the harness must first get a baseline estimate
of performance by running the benchmark in only
one process using the standard \*[lmbench] timing
interval, which is often 5,000 micro-seconds.
Using this information, the harness can compute
the average time per iteration for a single
process, and it uses this figure to compute the
number of iterations necessary to ensure that
each child runs for at least one second.
E 4
.NH 2
I 5
Clock resolution
.LP
\*[lmbench] uses the \*[gettimeofday] clock, whose 
interface resolves time down to 1 micro-second.  
However, many system clock's resolution is only 10 
milli-seconds, and there is no portable way to query 
the system to discover the true clock resolution.
.LP
The problem is that the timing intervals must
be substantially larger than the clock resolution
in order to ensure that the timing error doesn't
impact the results.  For example, the true duration
of an event measured with a 10 milli-second clock
can vary $+-$10 milli-seconds from the true time,
assuming that the reported time is always a
truncated version of the true time.  If the clock
itself is not updated precisely, the true error
can be even larger.  
This implies that timing intervals on these systems
should be at least 1 second.
.LP
However, the \*[gettimeofday] clock resolution in
most modern systems is 1 micro-second, so timing
intervals can as small as a few milli-seconds
without incurring significant timing errors related
to clock resolution.
.LP
D 6
Since there is no interface to query the operating
E 6
I 6
Since there is no standard interface to query the operating
E 6
system for the clock resolution, \*[lmbench] must 
experimentally determine the appropriate timing 
interval duration which provides results in a timely 
fashion with a negligible clock resolution error.
.NH 2
E 5
Coordination
.LP
D 5
However, developing a timing harness that
correctly manages $N$ processes and accurately
measures system performance over those same
$N$ processes is significantly more difficult
because of the asynchronous nature of the
distributed programming problem.
E 5
I 5
Developing a timing harness that correctly manages 
$N$ processes and accurately measures system performance 
over those same $N$ processes is significantly more difficult
than simply measuring system performance with a single
process because of the asynchronous nature of
parallel programming.
E 5
.LP
In essence, the new timing harness needs to create
$N$ jobs, and measure the average performance of the
target subsystem while all $N$ jobs are running.  This
is a standard problem for parallel and distributed
programming, and involves starting the child
processes and then stepping through a handshaking
process to ensure that all children have started
executing the benchmarked operation before any child
starts taking measurements.
D 4
Table 1 shows the various steps taken by the timing
harness.
E 4
.TSTART 1
.TS
box tab (/) allbox expand ;
c c
l l .
Parent/Child
T{
D 4
running the benchmark with P==1 to get a 
baseline estimate of performance.  The
timing interval is auto-scaled to the system
gettimeofday() clock resolution so this is 
usually quite fast.  
T}/
T{
compute the number of iterations required for 
a single benchmark to run for one second.  
During the timing intervals each child will 
repeat the benchmark this number of times.
T}
T{
E 4
start up P child processes
T}/T{
run benchmark operation for a little while
T}
T{
wait for P "ready" signals
T}/T{
send a "ready" signal
T}
T{
[sleep for "warmup" microseconds]
T}/T{
run benchmark operation while polling for a "go" signal
T}
T{
send "go" signal to P children
T}/T{
begin timing benchmark operation
T}
T{
wait for P "done" signals
T}/T{
send a "done" signal
T}
T{
for each child, send "results" signal and gather results
T}/T{
run benchmark operation while polling for a "results" signal
T}
T{
collate results
T}/T{
send timing results and wait for "exit" signal
T}
T{
send "exit" signal
T}/T{
exit
T}
.TE
.TEND "Timing harness sequencing"
I 4
.LP
Table \n[TABLE] shows how the parent and child
processes coordinate their activities to ensure
that all children are actively running the
benchmark activity while any child could be
taking timing measurements.
.LP
E 4
D 3
.LP
This convoluted system is designed to accomplish a number
of goals:
.IP 1.
during any timing interval of any child it is
guaranteed that all other child processes are
also running the benchmark
.IP 2.
the timing intervals are long enough to average
out most transient OS scheduler affects
E 3
.NH 2
Accuracy
.LP
The new timing harness also needs to ensure that the 
timing intervals are long enough for the results to 
be representative.  The previous timing harness assumed
that only single process results were important, and
it was able to use timing intervals as short as
possible while ensuring that errors introduced by
the clock resolution were negligible.  
In many instances this meant that the timing intervals 
were smaller than a single scheduler time slice.  
The new timing harness must run benchmarked items 
long enough to ensure that timing intervals are longer
than a single scheduler time slice.
Otherwise, you can get results which are complete nonsense.  
For example, running several copies of an \*[lmbench2] 
benchmark on a uni-processor machine will often report 
that the performance with $N$ jobs running in parallel 
is equivalent to the performance with a single job running!\**
.FS
This was discovered by someone who naively attempted
to parallelize \*[lmbench2] in this fashion, and I
received a note from the dismayed developer describing
the failed experiment.
.FE
.LP
In addition, since the timing intervals now have to be
longer than a single scheduler time slice, they also
need to be long enough so that a single scheduler time
slice is insignificant compared to the timing interval.
Otherwise the timing results can be dramatically 
affected by small variations in the scheduler's
behavior.
.NH 2
Resource consumption
.LP
One important design goal was that resource consumption
be constant with respect to the number of child
processes.  
This is why the harness uses shared pipes to communicate
with the children, rather than having a separate set of
pipes to communicate with each child.
An early design of the system utilized a pair of pipes
per child for communication and synchronization between
the master and slave processes.  However, as the number
of child processes grew, the fraction of system 
resources consumed by the harness grew and the additional
system overhead could start to interfere with the accuracy 
of the measurements.
.LP
Additionally, if the master has to poll (\*[select])
$N$ pipes, then the system overhead of that operation
also scales with the number of children.  
.NH 2
Pipe atomicity
.LP
Since all communication between the master process and
the slave (child) processes is done via a set of shared
pipes, we have to ensure that we never have a situation
where the message can be garbled by the intermingling
of two separate messages from two separate children.
This is ensured by either using pipe operations that
are guaranteed to be atomic on all machines, or by
coordinating between processes so that at most one
process is writing at a time.
.LP
The atomicity guarantees are provided by having each
client communicate synchronization states in one-byte 
messages.  For example, the signals from the master
to each child are one-byte messages, so each child
only reads a single byte from the pipe.  Similarly,
the responses from the children back to the master
are also one-byte messages.  In this way no child
can receive partial messages, and no message can
be interleaved with any other message.
.LP
However, using this design means that we need to
have a separate pipe for each \fIbarrier\fR in
the process, so the master uses three pipes to
send messages to the children, namely: \fIstart_signal\fR,
\fIresult_signal\fR, and \fIexit_signal\fR.
If a single pipe was used for all three barrier events,
then it is possible for a child to miss a signal,
or if the signal is encoded into the message, 
then it is possible for a child to infinite loop
pulling a signal off the pipe, recognizing that
it has already received that signal so that it
needs to push it back into the pipe, and then
then re-receiving the same message it just re-sent.
.LP
However, all children share a single pipe to send
data back to the master process.  Usually the
messages on this pipe are single-byte signals,
such as \fIready\fR or \fIdone\fR.  However, the
timing data results need to be sent from the
children to the master and they are (much) larger
than a single-byte message.  In this case, the
timing harness sends a single-byte message on
the \fIresult_signal\fR channel, which can be
received by at most one child process.  This
child then knows that it has sole ownership of
the response pipe, and it writes its entire 
set of timing results to this pipe.  Once the
master has received all of the timing results
from a single child, it sends the next one-byte
message on the \fIresult_signal\fR channel to
gather the next set of timing results.
I 3
.TSTART 1
.so lmbench3_signals.pic
.FEND "Control signals" 1
.LP
The design of the signals is shown in Figure \n[FIGURE].
E 3
.NH 2
Benchmark initialization
.LP
By allowing the benchmark to specify an
initialization routine that is run in the
child processes, the new timing harness
allows benchmarks to do either or both
global initializations that are shared
by all children and specific per-child
initializations that are done independently
by each child.
Global initialization is done in the
master process before the \*[benchmp] 
harness is called, so the state is 
preserved across the \*[fork] operations.
Per-child initialization is done inside
the \*[benchmp] harness by the optional
initialization routine and is done after
the \*[fork] operation.
.LP
Similarly, each benchmark is allowed to
specify a cleanup routine that is run by
the child processes just before exiting.
This allows the benchmark routines to
release any resources that they may have
used during the benchmark.
Most system resources would be automatically
released on process exit, such as file
descriptors and shared memory segments,
but some resources such as temporary files
might need to be explicitly released by
the benchmark.
.NH 2
Scheduler transients
.LP
Particularly on multi-processor systems, side-effects
of process migration can dramatically affect program 
runtimes.  For example, if the processes are all
initially assigned to the same processor as the parent
process, and the timing is done before the scheduler
migrates the processes to other available processors,
then the system performance will appear to be that of
a uniprocessor.  Similarly, if the scheduler is
over-enthusiastic about re-assigning processes to
processors, then performance will be worse than
necessary because the processes will keep encountering
cold caches and will pay exhorbitant memory access
costs.
.LP
The first case is a scheduler transient, and users
may not want to measure such transient phenomena
if their primary interest is in predicting performance
for long-running programs.  Conversely, that same
user would be extraordinarily interested in the
second phenomena.  The harness was designed to
allow users to specify that the benchmarked processes
are run for long enough to (hopefully) get the
scheduler past the transient startup phase, so it
can measure the steady-state behavior.
I 5
.NH 2
Data analysis
.LP
Analyzing the data to produce representative results
is a crucial step in the benchmarking process.  
\*[lmbench] generally reports the \fImedian\fP
result for $11$ measurements.  
Most benchmarks report the results of a single measurement
.RN Howard88 ,
an average of several results
.RN McCalpin95 ,
or a trimmed mean
.RN Brown97 .
XXX UNKNOWN:
.RN Weicker84,Shein89,Park,Wolman89,Banga97,Saavedra92,Chen94a,Bray90
.LP
Since \*[lmbench] is able to use timing intervals
that are often smaller than a scheduler time slice,
the raw timing results are often severely skewed.
The median is preferable to the mean when the data
can be very skewed
.RN Jain91 .
.LP
In some instances, however, \*[lmbench] internally
uses the \fIminimum\fP rather than the median, 
such as in \*[mhz].  
In those instances, we are not trying to find the 
\fIrepresentative\fP value, but rather the 
\fIminimum\fP value.
There are only a few sources of error which could
cause a the measured timing result to be shorter 
than the true elapsed time: the system clock is
D 6
adjusted, and round-off error in the clock resolution.
E 6
I 6
adjusted, or round-off error in the clock resolution.
E 6
The timing interval duration is set to ensure that
the round-off error is bounded to 1% of the timing
interval, and we blithely assume that people don't
reset their system clocks while benchmarking their
systems.
.LP
\*[lmbench] does not currently report any statistics
representing measurement variation, such as the 
difference between the first and third quartiles.
E 5
.NH 1
Interface
.LP
Unfortunately we had to move away from the
macro-based timing harness used in \*[lmbench2] 
and migrate to a function-based system.  
.LP
The new interface looks like:
.DS
typedef void (*bench_f)(uint64 iterations, 
			void* cookie);
typedef void (*support_f)(void* cookie);

extern void benchmp(support_f initialize,
		bench_f benchmark,
		support_f cleanup,
		int enough,
		int parallel,
		int warmup,
		int repetitions,
		void* cookie);
.DE
.LP
A brief description of the parameters:
.IP \fIenough\fR
Enough can be used to ensure that a timing interval is at
least 'enough' microseconds in duration.  For most benchmarks
this should be zero, but some benchmarks have to run for more
time due to startup effects or other strange behavior.
.IP \fIparallel\fR
is simply the number of instances of the benchmark
that will be run in parallel on the system.  
.IP \fIwarmup\fR
can be used to force the benchmark to run for warmup
microseconds before the system starts making timing measurements.
Note that it is a lower bound, not a fixed value, since it
is simply the time that the parent sleeps after receiving the
last "ready" signal from each child (and before it sends 
the "go" signal to the children).  
.IP \fIrepetitions\fR
is the number of times the experiment should
be repeated.  The default is eleven.
.IP \fIcookie\fR
is a pointer that can be used by the benchmark
writer to pass in configuration information, such as buffer
size or other parameters needed by the inner loop.  
In \*[lmbench3] it is generally used to point
to a structure containing the relevant configuration
information.
.LP
To write a simple benchmark for getppid() all you would need
to do is:
.DS
void
benchmark_getppid(uint64 iterations, 
			void* cookie)
{
	while (iterations-- > 0) {
		getppid();
	}
}
.DE
.LP
and then somewhere in your program you might call:
.DS
benchmp(NULL, benchmark_getppid, NULL, 
	0, 1, 0, NULL);
micro("getppid", get_n());
.DE
D 6
.LP
A more complex example which has "state" and uses the 
initialization and cleanup capabilities might look something
like this:
.DS
struct bcopy_state {
	int len;
	char* src;
	char* dst;
};
.DE
.DS
void
initialize_bcopy(void* cookie)
{
	struct bcopy_state* state = 
		(struct bcopy_state*)cookie;

	state->src = valloc(state->len);
	state->dst = valloc(state->len);

	bzero(src, state->len);
	bzero(src, state->len);
}
.DE
.DS
void
benchmark_bcopy(uint64 iterations, 
		void* cookie)
{
	struct bcopy_state* state = 
		(struct bcopy_state*)cookie;

	while (iterations-- > 0) {
		bcopy(state->src, 
		      state->dst, state->len);
	}
}
.DE
.DS
void
cleanup_bcopy(void* cookie)
{
	struct bcopy_state* state = 
		(struct bcopy_state*)cookie;

	free(state->src);
	free(state->dst);
}
.DE
.LP
and then your program look something like:
.DS
#include "bench.h"
int
main()
{
	struct bcopy_state state;

	state.len = 8 * 1024 * 1024;
	benchmp(initialize_bcopy, 
		benchmark_bcopy, 
		cleanup_bcopy, 
		0, 1, 0, TRIES, &state);
	fprintf(stderr, "bcopy: ");
	mb(state.len * get_n());
	exit(0);
}
.DE
.LP
Note that this particular micro-benchmark would measure
cache-to-cache \*[bcopy] performance unless the amount of
memory being copied was larger than half the cache size.
A slightly more sophisticated approach might allocate
as much memory as possible and then \*[bcopy] from one
segment to another, changing segments within the allocated
memory before each \*[bcopy] to defeat the caches.
E 6
.NH 1
I 3
Benchmarks
.LP
\*[lmbench] contains a large number of micro-benchmarks
that measure various aspects of hardware and operating
system performance.  The benchmarks generally measure
latency or bandwidth, but some new benchmarks also
measure parallelism.
I 4
.TSTART
.TS
center box tab (&);
c c 
l & l .
Name&Measures
_
D 6
&Bandwidth
E 6
I 6
&\fBBandwidth\fR
E 6
D 5
bw_file_rd&\*[read] and then load into processor
bw_mem&read, write, and copy data to/from memory
E 5
I 5
bw_file_rd&T{
\*[read] and then load into processor
T}
bw_mem&T{
read, write, and copy data to/from memory
T}
E 5
bw_mmap_rd&read from \*[mmap]'ed memory
D 6
bw_pipe&\*[pipe] inter-process
bw_tcp&TCP inter-process
E 6
I 6
bw_pipe&\*[pipe] inter-process data copy
bw_tcp&TCP inter-process data copy
E 6
bw_unix&UNIX inter-process
_
D 6
&Latency
lat_connect&TCP socket connection
E 6
I 6
&\fBLatency\fR
E 6
D 5
lat_ctx&context switch via \*[pipe]-based ``hot-potato'' token passing
E 5
I 5
lat_ctx&T{
context switch via \*[pipe]-based ``hot-potato'' token passing
T}
E 5
D 6
lat_fcntl&\*[fcntl]
E 6
I 6
lat_fcntl&\*[fcntl] operation
E 6
D 5
lat_fifo&FIFO ``hot-potato'' token passing
E 5
I 5
lat_fifo&T{
FIFO ``hot-potato'' token passing
T}
E 5
lat_fs&file creation and deletion
D 6
lat_http&
E 6
I 6
lat_http&http GET request latency
E 6
lat_mem_rd&memory read
D 6
lat_mmap&mmap
lat_ops&basic operations
E 6
I 6
lat_mmap&\*[mmap] operation
E 6
lat_pagefault&page fault handler
lat_pipe&\*[pipe] ``hot-potato'' token passing
lat_proc&T{
procedure call overhead and process creation using \*[fork],
\*[fork] and \*[execve], and \*[fork] and \*[sh]
T}
lat_rpc&SUN RPC procedure call
D 6
lat_select&\*[select]
E 6
I 6
lat_select&\*[select] operation
E 6
D 5
lat_sem&semaphore ``hot-potato'' token passing
lat_sig&signal handle installation and handling
E 5
I 5
lat_sem&T{
semaphore ``hot-potato'' token passing
T}
lat_sig&T{
signal handle installation and handling
T}
E 5
D 6
lat_syscall&
E 6
I 6
lat_syscall&T{
\*[getppid], 
\*[write], 
\*[stat], 
\*[fstat], 
\*[open], 
\*[close]
T}
E 6
lat_tcp&TCP ``hot-potato'' token passing
lat_udp&UDP ``hot-potato'' token passing
lat_unix&UNIX ``hot-potato'' token passing
lat_unix_connect&UNIX socket connection
_
D 6
&Parallelism
par_mem&memory subsystem
par_ops&T{
instruction-level parallelism of basic arithmetic operations
T}
_
mhz&CPU clock frequency
line&cache line size
tlb&number of pages mapped by TLB
E 6
I 6
&\fBOther\fR
E 6
stream&STREAM clones
lmdd&\fIdd\fR clone
.TE
.TEND "\*[lmbench] micro-benchmarks"
.LP
Table \n[TABLE] contains the full list of micro-benchmarks
D 6
in \*[lmbench].
E 4
.NH 2
I 5
Bandwidth
.LP
description of bandwidth benchmarks with some sample results.
.NH 2
Latency
.LP
description of latency benchmarks with some sample results.
E 6
I 6
in \*[lmbench] that were converted to measure performance
under scalable load.  A detailed description of each
benchmark can be found in
.RN McVoy96 .
E 6
.NH 1
Scaling Benchmarks
.LP
There are a number of issues associated with converting
single-process benchmarks with a single process to 
scalable benchmarks with several independent processes,
in addition to the various issues addressed by
the timing harness.
Many of the benchmarks consume or utilize system
resources, such as memory or network bandwidth,
and a careful assessment of the likely resource
contention issues is necessary to ensure that the
benchmarks measure important aspects of system performance
and not artifacts of artificial resource contention.
.LP
For example, the Linux 2.2 kernel uses a single lock to
control access to the kernel data structures for a file.
This means that multiple processes accessing that file
will have their operations serialized by that lock.
.NH 2
E 5
E 3
File System
.LP
A number of the benchmarks measure aspects of file system
D 4
performance, such as bw_file_rd, bw_mmap_rd, lat_mmap, and 
lat_pagefault.
E 4
I 4
performance, such as \*[bw_file_rd], \*[bw_mmap_rd], 
\*[lat_mmap], and \*[lat_pagefault].
E 4
It is not immediately apparent how these benchmarks should
be extended to the parallel domain.  For example, it may
be important to know how file system performance scales
when multiple processes are reading the same file, or
when multiple processes are reading different files.
D 3
The first case might be important for large scientific
calculations, while the second might be more important
for a web server.
E 3
I 3
The first case might be important for large, distributed 
scientific calculations, while the second might be more 
important for a web server.
E 3
.LP
However, for the operating system, the two cases are
significantly different.  When multiple processes
access the same file, access to the kernel data 
structures for that file must be coordinated and
so contention and locking of those structures can
D 3
impact performance.
E 3
I 3
impact performance, while this is less true when
multiple processes access different files.
E 3
.LP
In addition, there are any number of issues associated
with ensuring that the benchmarks are either measuring
operating system overhead (e.g., that no I/O is actually
done to disk), or actually measuring the system's I/O
performance (e.g., that the data cannot be resident in
the buffer cache).  Especially with file system related
benchmarks, it is very easy to develop benchmarks that
compare apples and oranges (e.g., the benchmark includes
the time to flush data to disk on one system, but only
includes the time to flush a portion of data to disk on
another system).
.LP
\*[lmbench3] allows the user to measure either case
as controlled by a command-line switch.  When measuring
accesses to independent files, the benchmarks first
create their own private copies of the file, one for
each child process.  Then each process accesses its
private file.  When measuring accesses to a single
file, each child simply uses the designated file
directly.
D 3
.NH 1
Context switching
E 3
I 3
.NH 2
Context Switching
E 3
.LP
Measuring context switching accurately is a difficult
D 6
task.  \*[lmbench] versions 1 and 2 measured context
E 6
I 6
task.  \*[lmbench1] and \*[lmbench2] measured context
E 6
switch times via a "hot-potato" approach using pipes
connected in a ring.  However, this experimental
design heavily favors schedulers that do "hand-off"
scheduling, since at most one process is active at
a time.
Consequently, it is not really a good benchmark
for measuring scheduler overhead in multi-processor
machines.
.LP
The design and methodology for measuring context
switching and scheduler overhead need to be revisited
so that it can more accurately measure performance
for multi-processor machines.
I 5
.NH 1
D 6
New Benchmarks
.LP
\*[lmbench] version 3 also includes a number of
new benchmarks.
E 5
D 3
.NH 1
E 3
I 3
.NH 2
E 6
E 3
Stream
.LP
\*[lmbench3] includes a new micro-benchmark which
measures the performance of John McCalpin's \*[stream]
D 3
benchmark kernels for both versions 1 and 2.
E 3
I 3
benchmark kernels for \*[stream] versions 1 and 2.
E 3
This benchmark faithfully recreates each of the
kernel operations from both \*[stream] benchmarks,
and because of the powerful new timing harness it
can easily measure memory system scalability.
.TSTART 1
.TS
center box tab (|);
c s s s s
I 5
c | c | c s | c
E 5
l | l | l | l | l .
Stream
_
D 5
Kernel|Code|Bytes|Bytes|FLOPS
||read|write|
E 5
I 5
Kernel|Code|Bytes|FL
||rd|wr|OPS
E 5
_
COPY|$a[i]=b[i]$|8(+8)|8|0
SCALE|$a[i]=q times b[i]$|8(+8)|8|1
ADD|$a[i]=b[i]+c[i]$|16(+8)|8|1
TRIAD|$a[i]=b[i]+q times c[i]$|16(+8)|8|2
.TE
.TS
center box tab (|);
c s s s s
I 5
c | c | c s | c
E 5
l | l | l | l | l .
Stream2
_
D 5
Kernel|Code|Bytes|Bytes|FLOPS
||read|write|
E 5
I 5
Kernel|Code|Bytes|FL
||rd|wr|OPS
E 5
_
FILL|$a[i]=q$|0(+8)|8|0
COPY|$a[i]=b[i]$|8(+8)|8|0
DAXPY|$a[i]=a[i]+q times b[i]$|16|8|2
SUM|$sum=sum + a[i]$|8|0|1
.TE
.TEND "Stream operations"
.LP
D 4
Table 2 shows the four kernels for each version
E 4
I 4
Table \n[TABLE] shows the four kernels for each version
E 4
of the \*[stream] benchmark.  Note that the
.I read
columns include numbers in parenthesis, which
represent the average number of bytes read into 
the cache as a result of the write to that
variable.  Cache lines are almost invariably
bigger than a single double, and so when a
write miss occurs the cache will read the line
from memory and then modify the selected bytes.
Sometimes vector instructions such as SSE
and 3DNow can avoid this load by writing an 
entire cache line at once.
D 3
.NH 1
E 3
I 3
D 6
.NH 2
E 3
Basic operation latency
.LP
\*[lmbench3] includes a new micro-benchmark 
which measures the latency for a variety of basic
operations, such as addition, multiplication, and
division of integer, float, and double operands.
To measure the basic operation latency we construct
a basic arithmetic statement containing the desired
operands and operations.  This statement is repeated
one hundred times and these repetitions are then
D 4
embedded in a loop.  The statements used are shown
in Table 3 below.
E 4
I 4
embedded in a loop.  
E 4
.TSTART
.TS
center box tab (&);
c c c
l & l & l .
Operand&Operation&Statement
_
int&$bit$&r^=i;s^=r;r|=s;
&$add$&a+=b;b-=a;
&$mul$&r=(r*i)^r;
&$div$&r=(r/i)^r;
&$mod$&r=(r%i)^r;
_
float&$add$&f+=f;
&$mul$&f*=f;
&$div$&f=g/f;
_
double&$add$&f+=f;
&$mul$&f*=f;
&$div$&f=g/f;
.TE
.TEND "lat_ops statements"
.LP
I 4
Table \n[TABLE] shows the data type and expressions
used for each basic operation type.  The variable
$i$ indicates the loop variable and generally
changes every ten or hundred evaluations of the
basic expression.  All other variables are of
the basic type being measured, and aside from
being modified by the relevant expressions are
only initialized once at the beginning of the
benchmark routine.
.LP
E 4
Each statement has been designed to ensure that
the statement instances are \fIinterlocked\fR,
namely that the processor cannot begin processing
the next instance of the statement until it has
completed processing the previous instance.  This
property is crucial to the correct measurement of
operation latency.
.LP
One important consideration in the design of
the statements was that they not be optimized
out of the loop by intelligent compilers.  
Since the statements are repeated one hundred
times, the compiler has the option of evaluating
the sequence of one hundred repetitions of the
same statement, and sometimes it can find
optimizations that are not immediately 
apparent.  For example, the integer statement
$a=a+a;$ when repeated one hundred times in
a loop can be replaced with the single statement
$a=0;$ because the statement $a=a+a;$ is equivalent
to $a<<=1;$, and one hundred repetitions of that
statement is equivalent to $a<<=100;$, which for
32bit (or even 64bit) integers is equivalent to
$a=0;$.  
.LP
It is relatively easy to identify floating
point statements that interlock, are not
optimized away, and that only use the operation
of interest.
It is much harder to identify integer statements
meeting the same criterion.  All simple 
integer bitwise operations can either be optimized
away, don't interlock, or use operations other
than one of interest.
We chose to add operations other than the 
operation(s) of interest to the statements.
.LP
The integer $mul$, $div$, and $mod$ statements all 
include an added $xor$ operation which prevents
(current) compilers from optimizing the statements
away.  Since the $xor$ operation is generally
completed in a single clock tick, and since
we can measure the $xor$ operation latency
separately and subtract that overhead, we can
still measure the latencies of the other 
operations of interest.
.LP
It is not possible to measure latency for 64bit
operations on 32bit machines because most
implementations allow operations on the upper
and lower bits to overlap.  This means that
on most 32bit machines, the measured latency
would appear to be a non-integral multiple of
the basic clock cycle.  For example, in the
D 5
$mul$ statement, the system could first add
E 5
I 5
$add$ statement, the system could first add
E 5
the two lower words.  Then, in parallel it
could both add the two upper words (along with
the carry from the lower words), and compute
the $xor$ of the lower word.  Finally, it
can overlap the $xor$ of the upper word
with the addition of the two lower words from
the next instantiation of the statement.
I 3
.TSTART
.TS
center box tab (&);
D 4
c c c c
c c c c
l & l & r & r .
Operand&Operation&PA-RISC 2.0&PIII
&&180MHz&667MHz
E 4
I 4
c c c c c
c c c c c
l & l & r & r & r .
Operand&Op&HPPA2.0&PIII&AMD
&&400MHz&667MHz&1.3GHz
E 4
_
D 4
int&$bit$&&1.16ns
&$add$&&2.36ns
&$mul$&&6.07ns
&$div$&&58.52ns
&$mod$&&65.01ns
E 4
I 4
mhz&&2.50&1.50&0.75
D 5
int&$bit$&2.53&1.16&0.75
&$add$&2.50&2.36&0.75
E 5
I 5
int&$bit$&2.53&1.50&0.75
&$add$&2.50&1.51&0.75
E 5
&$mul$&14.52&6.07&3.03
&$div$&109.40&58.52&30.86
&$mod$&75.14&65.01&32.59
E 4
_
D 4
float&$add$&&4.58ns
&$mul$&&7.50ns
&$div$&&35.26ns
E 4
I 4
float&$add$&7.54&4.58&3.0
&$mul$&7.50&7.50&3.0
&$div$&45.00&35.26&13.21
E 4
_
D 4
double&$add$&&4.53ns
&$mul$&&7.71ns
&$div$&&35.51ns
E 4
I 4
double&$add$&7.52&4.53&3.01
&$mul$&7.52&7.71&3.01
&$div$&85.01&35.51&13.16
E 4
.TE
D 4
.TEND "lat_ops results"
E 4
I 4
.TEND "lat_ops results (ns)"
E 4
E 3
.LP
D 3
The $bit$ statement is potentially problematic
on systems without a barrel shifter that can
conduct a shift of any magnitude in a single
cycle.  
.NH 1
E 3
I 3
Table \n[TABLE] contains some sample results
for two processors.  
It does contain one result which is slightly
surprising unless you are familiar with the
PA-RISC architecture: floating point multiply
and divide are faster than the corresponding
integer operations!  This is because PA-RISC
does not contain integer MUL, DIV, or MOD
instructions and the optimizing compiler
converts the integers into floating point,
does the operations in the floating point
unit, and then converts the result back
into an integer.
.NH 2
E 3
Basic operation parallelism
.LP
D 3
Intra-processor parallelism in commodity processors
E 3
I 3
Instruction-level parallelism in commodity processors
E 3
has become commonplace in the last ten years.  
Modern processors typically have more than one
operational unit that can be active during a
given clock cycle, such as an integer arithmetic
unit and a floating point unit.  In addition, 
processors may have more than a single instance
of a given type of operational unit, both of
which may be active at a given time.  All this
intra-processor parallelism is used to try and
reduce the average number of clock cycles per
executed instruction.  
.LP
\*[lmbench3] incorporates a new benchmark \*[par_ops]
which attempts to quantify the level of available
instruction-level parallelism provided by the processor.  This 
benchmark is very similar to \*[lat_ops], and
in fact uses the same statement kernels, but it
has been modified and extended.  We create
different versions of each benchmark; each
version has $N$ sets of interleaved statements.
Each set is identical to equivalent \*[lat_ops]
statements.  In this way multiple independent
sets can be executing the same operation(s)
in parallel, if the hardware supports it.
.LP
For example, the float $mul$ benchmark to measure
performance with two parallel streams of statements
would look like something this:
.DS
#define TEN(a) a a a a a a a a a a
void benchmark_1(iter_t iterations, void* cookie)
{
    register iter_t i = iterations;
    struct _state* state = (struct _state*)cookie;
    register float f0 = state->float_data[0];
    register float f1 = state->float_data[1];

    while (i-- > 0) {
        TEN(f0*=f0; f1*=f1;)
    }
    use_int((int)f0);
    use_int((int)f1);
}
.DE
.LP
If the processor had two floating point multiply
units, then both $f0$ and $f1$ multiplies could
proceed in parallel.
.LP
However, there are some potential problems with
the integer operations, namely the fact that the
statements contain mixed operations.  In general,
processors have at least as many integer units
that can do $xor$ as can do the other operations
of interest ($mul$, $div$ and $mod$), so the
inclusion of $xor$ in the statements shouldn't
be a bottleneck.  
.LP
However, since parallelism is measured by comparing 
the latency of the single-stream with that of 
multiple interleaved streams, and since the single-stream 
latency includes the $xor$ latency, the apparent 
parallelism of $mul$, $div$, $mod$ can be over-stated.
For example, if a process has one unit that can
do integer bit operations, such as $xor$, and another
unit for integer $mul$ operations, then the average
latency for $a0 = (i * a0) ^ a0$ in the single stream 
case would be:
.EQ
t bar = t sub xor + t sub mul
.EN
In the multi-stream case, the execution of the $xor$ 
operation of one stream can be overlapped with the 
$mul$ of another stream, so the average latency per 
stream would simply be $t bar = t sub mul$, assuming 
that $mul$ operations are not cheaper than $xor$ 
operations, which results in an apparent parallelism 
$p tilde$:
.EQ
p tilde = {t sub xor + t sub mul} over { t sub mul }
.EN
Assuming that $t sub xor << t sub mul$, this
still gives a reasonable approximation to
the correct answer.  Unfortunately, this is
not always a reasonable assumption.
.LP
Of course, if it was known ahead of time that
$xor$ and { $mul$, $div$, and $mod$ } used
different execution units, then the benchmark
could simply subtract $t sub xor$ from the
baseline measurement.  The difficulty lies
in determining whether the units overlap
or not.
I 3
.TSTART
.TS
center box tab (&);
D 4
c c c c
c c c c
l & l & r & r .
Operand&Operation&PA-RISC 2.0&PIII
&&180MHz&667MHz
E 4
I 4
c c c c c
c c c c c
l & l & r & r & r .
Operand&Op&HPPA2.0&PIII&AMD
&&400MHz&667MHz&1.3GHz
E 4
_
D 4
int&$bit$&&1.00
&$add$&&1.61
&$mul$&&3.81
&$div$&&1.20
&$mod$&&1.11
E 4
I 4
D 5
int&$bit$&1.99&1.00&1.87
E 5
I 5
int&$bit$&1.99&1.70&1.87
E 5
&$add$&1.99&1.61&1.90
&$mul$&6.64&3.81&2.00
&$div$&2.81&1.20&1.00
&$mod$&2.78&1.11&1.03
E 4
_
D 4
float&$add$&&1.00
&$mul$&&1.14
&$div$&&1.03
E 4
I 4
float&$add$&5.88&1.00&2.66
&$mul$&5.86&1.14&2.47
&$div$&2.12&1.03&1.14
E 4
_
D 4
double&$add$&&1.08
&$mul$&&1.00
&$div$&&1.03
E 4
I 4
double&$add$&5.68&1.08&2.49
&$mul$&5.58&1.00&2.53
&$div$&2.19&1.03&1.14
E 4
.TE
.TEND "par_ops results"
.LP
I 5
.NH 1
Results
.LP
Some sample results
.LP
bw_mem_rd performance vs. scaling on an SMP machine
.LP

E 6
E 5
E 3
.NH 1
Unscalable benchmarks
.LP
There are a number of benchmarks which either
did not make sense for scalable load, such as
D 6
\*[mhz], and other benchmarks which could not
E 6
I 6
\*[mhz], or which could not
E 6
be extended to measure scalable load due to
other constraints, such as \*[lat_connect].
.LP
\*[mhz] measures the processor clock speed,
which is not a scalable feature of the system,
so it doesn't make any sense to create a
version of it that measures scalable performance.
.LP
More specifically, \*[lat_connect] measures
the latency of connecting to a TCP socket.
TCP implementations have a timeout on
sockets and there is generally a fixed size
queue for sockets in the TIMEOUT state.  
This means that once the queue has been 
filled by a program connecting and closing
sockets as fast as possible, then all new
socket connections have to wait TIMEOUT
seconds.  Needless to say, this gives no
insight into the latency of socket creation
per se, but is rather a boring artifact.
Since the \*[lmbench2] version of the
benchmark can run for very short periods
of time, it generally does not run into
this problem and is able to correctly
measure TCP connection latency.  
.LP
Any scalable version of the benchmark needs 
each copy to run for at least a second, and 
there are $N$ copies creating connections as 
fast as possible, so it would essentially be
guaranteed to run into the TIMEOUT problem.
Consequently, \*[lat_connect] was not
enhanced to measure scalable performance.
.NH 1
I 6
Results
.LP
Some sample results
.LP
bw_mem_rd performance vs. scaling on an SMP machine
.LP

.NH 1
E 6
Conclusion
.LP
\*[lmbench] is a useful, portable micro-benchmark 
suite designed to measure important aspects of 
system performance.
\*[lmbench3] adds a number of important extensions,
such as the ability to measure system scalability.
I 6
.LP
The benchmarks are available at
.ft I
http://ftp.bitmover.com/lmbench
.ft
E 6
.NH 1
Acknowledgments
.LP
Many people have provided invaluable help and insight into both the
benchmarks themselves and the paper.  The \s-1USENIX\s0 reviewers
were especially helpful.
We thank all of them
and especially thank:
Wayne Scott \s-1(BitMover)\s0,
Larry McVoy \s-1(BitMover)\s0,
and
Bruce Chapman \s-1(SUN)\s0.
.LP
We would also like to thank all of the people that have run the
benchmark and contributed their results; none of this would have been possible
without their assistance.
.LP
Our thanks to 
all of the free software community for tools that were used during this
project.
\*[lmbench] is currently developed on Linux, a copylefted Unix written by 
Linus Torvalds and his band of happy hackers.
D 6
This paper and all of the 
\*[lmbench] documentation was produced using
the \f(CWgroff\fP suite of tools written by James Clark.
Finally, all of the data processing of the results is done with
\f(CWperl\fP written by Larry Wall.  
.NH 1
Obtaining the benchmarks
.LP
The benchmarks are available at
.ft I
http://ftp.bitmover.com/lmbench
.ft
E 6
.\" .R1
.\" bibliography references-lmbench3
.\" .R2
.\"********************************************************************
.\" Redefine the IP paragraph format so it won't insert a useless line
.\" break when the paragraph tag is longer than the indent distance
.\"
.de @IP
.if \\n[.$]>1 .nr \\n[.ev]:ai (n;\\$2)
.par*start \\n[\\n[.ev]:ai] 0
.if !'\\$1'' \{\
.	\" Divert the label so as to freeze any spaces.
.	di par*label
.	in 0
.	nf
\&\\$1
.	di
.	in
.	fi
.	chop par*label
.	ti -\\n[\\n[.ev]:ai]u
.	ie \\n[dl]+1n<=\\n[\\n[.ev]:ai] \\*[par*label]\h'|\\n[\\n[.ev]:ai]u'\c
.	el \{\
\\*[par*label]
.\".	br
.	\}
.	rm par*label
.\}
..
.\"********************************************************************
.\" redefine the way the reference tag is printed so it is enclosed in
.\" square brackets
.\"
.de ref*end-print
.ie d [F .IP "[\\*([F]" 2
.el .XP
\\*[ref*string]
..
.\"********************************************************************
.\" Get journal number entries right.  Now will print as V(N) rather
.\" than the awful V, N.
.\"
.de ref*add-N
.ref*field N "" ( ) 
..
.\"********************************************************************
.\" Get journal volume entries right.  Now will print as V(N) rather
.\" than the awful V, N.
.\"
.de ref*add-V
.ref*field V , "" "" ""
..
.\"********************************************************************
.\" Get the date entry right.  Should not be enclosed in parentheses.
.\"
.de ref*add-D
.ref*field D ","
..
.R1
accumulate
sort A+DT
database references-lmbench3
label-in-text
label A.nD.y-2
bracket-label [ ] ", "
bibliography references-lmbench3
.R2
.\" .so bios
E 2
I 1
E 1
