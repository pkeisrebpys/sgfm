CC=g++

INCDIR := ../include
LIBDIR := ../lib
SRCFILES := $(wildcard *.cpp)

OBJFILES := $(SRCFILES:%.cpp=%.o)
EXEFILES := $(SRCFILES:%.cpp=%.exe)

INFILES := $(SRCFILES:%.cpp=%.in)
OUTFILES := $(SRCFILES:%.cpp=%.out)
LOGFILES := $(SRCFILES:%.cpp=%.log)

DIFFILES := $(SRCFILES:%.cpp=%.dif)

LIBFILE := $(LIBDIR)/libsgfm.so

all : testResion.exe gen_load gen_edc


allall : $(EXEFILES)


init : testResion.in
	

initall : $(INFILES)


mod:
	./mod_input.sh


run : testResion.out
	

runall : $(OUTFILES)


diff : $(DIFFILES)


clean : 
	rm -f $(OBJFILES) $(EXEFILES)

clearinit:
	rm -f $(INFILES)

clearrun:
	rm -f $(OUTFILES) $(LOGFILES) *.err *.in_* *.out_*

gen_load:gen_load.c
	gcc -o $@ $< -lm

gen_edc:gen_edc.c
	gcc -o $@ $< -lm

%.exe : %.o
	$(CC) -std=c++11 -L$(LIBDIR) -I$(INCDIR) -o $@ $^ -lsgfm -Wl,-rpath=$(LIBDIR)

%.o : %.cpp
	$(CC) -std=c++11 -Wall -Werror -O2 -c -I$(INCDIR) -o $@ $<

%.out : %.exe %.in $(LIBFILE)
	./$< $(patsubst %.exe,%.in,$<) $@ > $(patsubst %.out,%.log,$@) 2> $(patsubst %.out,%.err,$@) 

%.in : %.exe $(LIBFILE)
	./$< $@ > $(patsubst %.in,%.err,$@) 2>&1

%.dif : %.in %.out
	-diff $^

$(LIBFILE) :
	cd ../ && $(MAKE)
