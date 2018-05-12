#directory
PBERRDIR=../../../PBErr
PBMATHDIR=../../../PBMath
GENBRUSHDIR=../../../GenBrush
GSETDIR=../../../GSet
SHAPOIDDIR=../../../Shapoid
BCURVEDIR=../../../BCurve
GTREEDIR=../../../GTree
PBJSONDIR=../../../PBJson
FRACNOISEDIR=../..

# Build mode
# 0: development (max safety, no optimisation)
# 1: release (min safety, optimisation)
# 2: fast and furious (no safety, optimisation)
BUILDMODE=1

# 0: monolith version, the GBSurface is rendered toward a TGA image
# 1: GTK version, the GBSurface is rendered toward a TGA image or 
#    a GtkWidget
BUILDWITHGRAPHICLIB=0

include $(PBERRDIR)/Makefile.inc

INCPATH=-I./ -I$(PBERRDIR)/ -I$(PBMATHDIR)/ -I$(GENBRUSHDIR)/ -I$(SHAPOIDDIR)/ -I$(BCURVEDIR)/ -I$(FRACNOISEDIR)/ -I$(GSETDIR)/ -I$(PBJSONDIR)/ -I$(GTREEDIR)/
BUILDOPTIONS=$(BUILDPARAM) $(INCPATH) -ggdb

# compiler
COMPILER=gcc

#rules
all : main

main: main.o pberr.o bcurve.o shapoid.o pbmath.o gset.o genbrush.o fracnoise.o pbjson.o gtree.o Makefile 
	$(COMPILER) main.o pberr.o bcurve.o shapoid.o pbmath.o gset.o pbjson.o gtree.o genbrush.o fracnoise.o $(LINKOPTIONS) -lm -o main $(GTKLINK) $(CAIROLINK)

main.o : main.c $(PBERRDIR)/pberr.h $(SHAPOIDDIR)/shapoid.h $(SHAPOIDDIR)/shapoid-inline.c $(PBMATHDIR)/pbmath.h $(PBMATHDIR)/pbmath-inline.c $(GSETDIR)/gset.h $(GSETDIR)/gset-inline.c $(BCURVEDIR)/bcurve.h $(BCURVEDIR)/bcurve-inline.c $(GENBRUSHDIR)/genbrush.h $(GENBRUSHDIR)/genbrush-inline.c $(FRACNOISEDIR)/fracnoise.c $(FRACNOISEDIR)/fracnoise-inline.c $(FRACNOISEDIR)/fracnoise.h Makefile
	$(COMPILER) $(BUILDOPTIONS) -c main.c

pbjson.o : $(PBJSONDIR)/pbjson.c $(PBJSONDIR)/pbjson-inline.c $(PBJSONDIR)/pbjson.h Makefile
	$(COMPILER) $(BUILDOPTIONS) -c $(PBJSONDIR)/pbjson.c

gtree.o : $(GTREEDIR)/gtree.c $(GTREEDIR)/gtree.h $(GTREEDIR)/gtree-inline.c Makefile $(GSETDIR)/gset-inline.c $(GSETDIR)/gset.h $(PBERRDIR)/pberr.c $(PBERRDIR)/pberr.h
	$(COMPILER) $(BUILDOPTIONS) -c $(GTREEDIR)/gtree.c

fracnoise.o: $(FRACNOISEDIR)/fracnoise.h $(FRACNOISEDIR)/fracnoise.c $(FRACNOISEDIR)/fracnoise-inline.c $(PBMATHDIR)/pbmath.h Makefile
	$(COMPILER) $(BUILDOPTIONS) -c $(FRACNOISEDIR)/fracnoise.c
	
genbrush.o : $(GENBRUSHDIR)/genbrush.c $(GENBRUSHDIR)/genbrush.h $(GENBRUSHDIR)/genbrush-inline.c $(BCURVEDIR)/bcurve.h $(BCURVEDIR)/bcurve-inline.c $(SHAPOIDDIR)/shapoid.h $(SHAPOIDDIR)/shapoid-inline.c $(PBMATHDIR)/pbmath.h $(PBMATHDIR)/pbmath-inline.c $(GSETDIR)/gset.h $(GSETDIR)/gset-inline.c $(PBERRDIR)/pberr.h Makefile
	$(COMPILER) $(BUILDOPTIONS) -c $(GENBRUSHDIR)/genbrush.c

bcurve.o : $(BCURVEDIR)/bcurve.c $(BCURVEDIR)/bcurve-inline.c $(BCURVEDIR)/bcurve.h $(SHAPOIDDIR)/shapoid.h $(SHAPOIDDIR)/shapoid-inline.c $(PBMATHDIR)/pbmath.h $(PBMATHDIR)/pbmath-inline.c $(GSETDIR)/gset.h $(GSETDIR)/gset-inline.c $(PBERRDIR)/pberr.h Makefile
	$(COMPILER) $(BUILDOPTIONS) -c $(BCURVEDIR)/bcurve.c

shapoid.o : $(SHAPOIDDIR)/shapoid.c $(SHAPOIDDIR)/shapoid.h $(SHAPOIDDIR)/shapoid-inline.c $(PBMATHDIR)/pbmath.h $(PBMATHDIR)/pbmath-inline.c $(GSETDIR)/gset.h $(GSETDIR)/gset-inline.c $(PBERRDIR)/pberr.h Makefile
	$(COMPILER) $(BUILDOPTIONS) -c $(SHAPOIDDIR)/shapoid.c

pberr.o : $(PBERRDIR)/pberr.c $(PBERRDIR)/pberr.h Makefile
	$(COMPILER) $(BUILDOPTIONS) -c $(PBERRDIR)/pberr.c

pbmath.o : $(PBMATHDIR)/pbmath.c $(PBMATHDIR)/pbmath-inline.c $(PBMATHDIR)/pbmath.h Makefile $(PBERRDIR)/pberr.h
	$(COMPILER) $(BUILDOPTIONS) -c $(PBMATHDIR)/pbmath.c

gset.o : $(GSETDIR)/gset.c $(GSETDIR)/gset-inline.c $(GSETDIR)/gset.h Makefile $(PBERRDIR)/pberr.h
	$(COMPILER) $(BUILDOPTIONS) -c $(GSETDIR)/gset.c

clean : 
	rm -rf *.o main

valgrind :
	valgrind -v --track-origins=yes --leak-check=full --gen-suppressions=yes --show-leak-kinds=all ./main
	
unitTest :
	main > unitTest.txt; diff unitTest.txt unitTestRef.txt

HF:
	povray +FT -W500 -H300 -D -P -Q9 +A +UA -IHF.pov

DF3:
	povray +FT -W500 -H300 -D -P -Q9 +A -IDF3.pov
