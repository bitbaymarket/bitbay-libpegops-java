
ifeq (${JAVA_HOME},)
    $(error "JAVA_HOME env var is null")
endif

LINK:=$(CXX)
ARCH:=$(system lscpu | head -n 1 | awk '{print $2}')

DEFS += $(addprefix -I,$(CURDIR) $(CURDIR)/bay $(CURDIR)/obj ${JAVA_HOME}/include ${JAVA_HOME}/include/linux)
DEFS += -DBOOST_SPIRIT_THREADSAFE -DBOOST_NO_CXX11_SCOPED_ENUMS
DEFS += -DBOOST_ALL_NO_LIB

LIBS += \
   -l boost_system \
   -l ssl \
   -l crypto 

xCXXFLAGS = -fPIC -O2 -std=c++11 -Wall -Wextra -Wno-ignored-qualifiers -Wformat -Wformat-security -Wno-unused-parameter $(DEFS) $(CXXFLAGS)

all : libpegops.so

test : all
	java -Djava.library.path=. bay.pegops

clean :
	rm -f bay/bay_pegops.h bay/*.class libpegops.so obj/*

OBJS= \
    obj/bay_pegops.o \
    obj/pegdata.o \
    obj/pegdata_compat.o \
    obj/pegutil.o \
    obj/pegopsp.o \
    obj/pegops.o \
    obj/peglevel.o \
    obj/pegfractions.o \

# auto-generated dependencies:
-include obj/*.P

libpegops.so: $(OBJS:obj/%=obj/%)
	$(LINK) $(xCXXFLAGS) -z noexecstack -shared -o $@ $^ $(xLDFLAGS) $(LIBS)

bay/bay_pegops.h : bay/pegops.java
	javac -h bay -classpath bay bay/pegops.java

obj/%.o: bay/%.cpp bay/bay_pegops.h
	$(CXX) -c $(xCXXFLAGS) -MMD -MF $(@:%.o=%.d) -o $@ $<
	@cp $(@:%.o=%.d) $(@:%.o=%.P); \
	  sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
	      -e '/^$$/ d' -e 's/$$/ :/' < $(@:%.o=%.d) >> $(@:%.o=%.P); \
	  rm -f $(@:%.o=%.d)
