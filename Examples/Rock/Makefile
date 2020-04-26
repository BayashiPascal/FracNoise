#directory
PBERRDIR=../../../PBErr
PBMATHDIR=../../../PBMath
GENBRUSHDIR=../../../GenBrush
GSETDIR=../../../GSet
SHAPOIDDIR=../../../Shapoid
BCURVEDIR=../../../BCurve
GTREEDIR=../../../GTree
PBJSONDIR=../../../PBJson
PBCEXTENSIONDIR=../../../PBCExtension
FRACNOISEDIR=../..

# Build mode
# 0: development (max safety, no optimisation)
# 1: release (min safety, optimisation)
# 2: fast and furious (no safety, optimisation)
BUILDMODE=0

# 0: monolith version, the GBSurface is rendered toward a TGA image
# 1: GTK version, the GBSurface is rendered toward a TGA image or 
#    a GtkWidget
BUILDWITHGRAPHICLIB=0

MAKEFILE_INC=../../../PBMake/Makefile.inc
include $(MAKEFILE_INC)

INCPATH=-I./ -I$(PBERRDIR)/ -I$(PBMATHDIR)/ -I$(GENBRUSHDIR)/ -I$(SHAPOIDDIR)/ -I$(BCURVEDIR)/ -I$(FRACNOISEDIR)/ -I$(GSETDIR)/ -I$(PBJSONDIR)/ -I$(GTREEDIR)/ -I$(PBCEXTENSIONDIR)/
BUILDOPTIONS=$(BUILDPARAM) $(INCPATH) -ggdb

# compiler
COMPILER=gcc

#rules
all : main

main: main.o pberr.o bcurve.o shapoid.o pbmath.o gset.o genbrush.o fracnoise.o pbjson.o gtree.o Makefile 
	$(COMPILER) main.o pberr.o bcurve.o shapoid.o pbmath.o gset.o pbjson.o gtree.o genbrush.o fracnoise.o $(LINKOPTIONS) -lm -o main $(GTKLINK) $(CAIROLINK)

main.o : main.c $(PBERRDIR)/pberr.h $(SHAPOIDDIR)/shapoid.h $(SHAPOIDDIR)/shapoid-inline.c $(PBMATHDIR)/pbmath.h $(PBMATHDIR)/pbmath-inline.c $(GSETDIR)/gset.h $(GSETDIR)/gset-inline.c $(BCURVEDIR)/bcurve.h $(BCURVEDIR)/bcurve-inline.c $(GENBRUSHDIR)/genbrush.h $(GENBRUSHDIR)/genbrush-inline.c $(FRACNOISEDIR)/fracnoise.c $(FRACNOISEDIR)/fracnoise-inline.c $(FRACNOISEDIR)/fracnoise.h Makefile
	$(COMPILER) $(BUILDOPTIONS) -c main.c

unitTest :
	main > unitTest.txt; diff unitTest.txt unitTestRef.txt

HF:
	povray +FT -W500 -H300 -D -P -Q9 +A +UA -IHF.pov

DF3:
	povray +FT -W500 -H300 -D -P -Q9 +A -IDF3.pov
