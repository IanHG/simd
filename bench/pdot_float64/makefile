# Set some defaults
ifeq ($(SIMD_ALIGNMENT),)
SIMD_ALIGNMENT := 256
endif

ifdef IACA
override IACA := -DINTEL_IACA
else
override IACA :=
endif

ifdef LIKWID
LIKWID=-DLIKWID
LIKWIDLIBS=-llikwid -llikwidpin -llikwid-hwloc -lpthread -lm
else
LIKWID=
LIKWIDLIBS=
endif

ifndef BENCHMARK_SIZE
BENCHMARK_SIZE=10000
endif

#CCACHE=ccache
CCACHE=
CXX=g++
C=gcc
CXXSTD=--std=c++17
CXXOPTIMFLAGS=-O3 -g
CXXDEBUGFLAGS=-g -O0 -rdynamic

#CXXFLAGS=-Wall $(CXXOPTIMFLAGS) -mavx2 -DALIGNED_ALLOC
CXXFLAGS=-Wall $(CXXOPTIMFLAGS) -mavx2 -DALIGNED_ALLOC -DSIMD_ALIGNMENT=$(SIMD_ALIGNMENT) $(IACA) -DGENERIC -DX86_SSE4_1 -DBENCHMARK_SIZE=$(BENCHMARK_SIZE)
#CXXFLAGS=-Wall $(CXXOPTIMFLAGS) -mavx2 -DALIGNED_ALLOC -DSIMD_ALIGNMENT=$(SIMD_ALIGNMENT) -DINTEL_IACA
#CXXFLAGS=-Wall $(CXXOPTIMFLAGS)
#CXXF(LAGS=-Wall $(CXXDEBUGFLAGS) -mavx2
ifneq ($(FMA), false)
CXXFLAGS+= -mfma
endif
ifneq ($(PREFETCH), false)
CXXFLAGS+= -DSIMD_SOFTWARE_PREFETCH
endif

LIBS=$(LIKWIDLIBS) -lbenchmark -lpthread

# find source files
SOURCEDIR := $(shell pwd)
BUILDDIR := $(shell pwd)
SOURCES := $(shell find $(SOURCEDIR)/../.. -path $(SOURCEDIR)/benchmark -prune -o -name '*.cpp' -print)
SOURCES_C := $(shell find $(SOURCEDIR)/../.. -path $(SOURCEDIR)/benchmark -prune -o -name '*.c' -print)
#OBJECTS := $(addprefix $(BUILDDIR)/,$(notdir $(SOURCES:.cpp=.o)))
OBJECTS := $(SOURCES:.cpp=.o)
OBJECTS_C := $(SOURCES_C:.c=.oc)

# link
main.x: $(OBJECTS) $(OBJECTS_C)
	$(CCACHE) $(CXX) $(CXXFLAGS) $(OBJECTS) $(OBJECTS_C) -o main.x $(LIBS)

# pull dependencies for existing .o files
-include $(OBJECTS:.o=.d)

# compile and generate dependency info
%.o: %.cpp %.d
	$(CCACHE) $(CXX) $(CXXSTD) -c  $(CXXFLAGS) $*.cpp -o $*.o
	$(CCACHE) $(CXX) $(CXXSTD) -MM $(CXXFLAGS) $*.cpp > $*.d

# compile and generate dependency info
%.oc: %.c %.d
	$(CCACHE) $(C) -c  $(CXXFLAGS) $*.c -o $*.oc
	$(CCACHE) $(C) -MM $(CXXFLAGS) $*.c > $*.d

# empty rule for dependency files
%.d: ;

clean:
	rm -f *core $(OBJECTS) $(OBJECTS_C) *.d src/*.o src/*.d
