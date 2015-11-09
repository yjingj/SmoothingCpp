#Makefile

# Supported platforms
#       Unix / Linux               	LNX
#       Mac                        	MAC
# Compilation options
#       32-bit binary        		FORCE_32BIT

# Set this variable to either LNX or MAC
SYS = LNX
# Leave blank after "=" to disable; put "= 1" to enable
# Disable WITH_LAPACK option can slow computation speed significantly and is not recommended
# Disable WITH_ARPACK option only disable -apprx option in the software
WITH_LAPACK = 1
FORCE_32BIT = 
FORCE_DYNAMIC =
DIST_NAME = BABF

# --------------------------------------------------------------------
# Edit below this line with caution
# --------------------------------------------------------------------

CPP = g++

CPPFLAGS = -ggdb -Wall -O3 -D__ZLIB_AVAILABLE__ -D_FILE_OFFSET_BITS=64 -D__STDC_LIMIT_MACROS #-pg

LIBS = -lgsl -lgslcblas -pthread -lz -lm 

OUTPUT = ./bin/babf

SOURCES = ./main.cpp

HDR = 

# Detailed library paths, D for dynamic and S for static

LIBS_MAC_D_LAPACK = -framework Veclib
LIBS_LNX_S_LAPACK = /usr/lib/lapack/liblapack.a -lgfortran  /usr/lib/atlas-base/libatlas.a /usr/lib/libblas/libblas.a -Wl,--allow-multiple-definition 

# Options

SOURCES += ./src/io.cpp ./src/mathfunc.cpp ./src/mcmc.cpp 

HDR += ./src/io.h ./src/mathfunc.h ./src/mcmc.h

CPPFLAGS += -DWITH_LAPACK

ifeq ($(SYS), MAC)
  LIBS += $(LIBS_MAC_D_LAPACK)
else
  LIBS += $(LIBS_LNX_S_LAPACK)
endif

ifdef FORCE_32BIT
  CPPFLAGS += -m32
else
  CPPFLAGS += -m64
endif

CPPFLAGS += -static

# all
OBJS = $(SOURCES:.cpp=.o)

all: $(OUTPUT)

$(OUTPUT): $(OBJS)
	$(CPP) $(CPPFLAGS) $(OBJS) $(LIBS) -o $(OUTPUT)

$(OBJS) : $(HDR)

.cpp.o: 
	$(CPP) $(CPPFLAGS) $(HEADERS) -c $*.cpp -o $*.o
.SUFFIXES : .cpp .c .o $(SUFFIXES)


clean:
	rm -rf ./src/*.o ./src/*~ *~ $(OUTPUT)

DIST_COMMON = Makefile


tar:
	mkdir -p ./$(DIST_NAME)
	cp $(DIST_COMMON) ./$(DIST_NAME)/
	tar cvzf $(DIST_NAME).tar.gz ./$(DIST_NAME)/
	rm -r ./$(DIST_NAME)
