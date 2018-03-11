PBERRDIR=/home/bayashi/Coding/PBErr
PBMATHDIR=/home/bayashi/Coding/PBMath
GENBRUSHDIR=/home/bayashi/Coding/GenBrush
GSETDIR=/home/bayashi/Coding/GSet
SHAPOIDDIR=/home/bayashi/Coding/Shapoid
BCURVEDIR=/home/bayashi/Coding/BCurve
include $(PBERRDIR)/Makefile.inc
INCPATH=-I./ -I../../ -I$(PBERRDIR)/ -I$(PBMATHDIR)/ -I$(GENBRUSHDIR)/ -I$(SHAPOIDDIR)/ -I$(BCURVEDIR)/ -I$(GSETDIR)/
BUILDOPTIONS=$(BUILDPARAM) $(INCPATH) -ggdb
BUILDMODE=0

# compiler
COMPILER=gcc

#rules
all : main

main: main.o Makefile 
	$(COMPILER) main.o ../../pberr.o ../../bcurve.o ../../shapoid.o ../../pbmath.o ../../gset.o ../../genbrush.o ../../fracnoise.o $(LINKOPTIONS) -lm -o main $(GTKLINK) $(CAIROLINK)

main.o : main.c Makefile
	$(COMPILER) $(BUILDOPTIONS) -c main.c

clean : 
	rm -rf *.o main

DF3:
	povray +FT -W500 -H300 -D -P -Q9 +A -Icloud.pov
