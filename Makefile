Objs                    = USB_a.o USB_libusb.o
CC              = gcc
CXX             = gcc
CCFlags         = -g -O1 -Wall -w -pedantic -fPIC -Wcpp -L/usr/lib64/ -lusb
#CCFlags         = -g -O1 -Wall -pedantic -fPIC -Wcpp -L/usr/lib64/ -lusb
DevFlags		= -D_GLIBCXX_USE_CXX11_ABI=0

# IncludeDirs     =  /opt/cactus/include ../

# IncludePaths            = $(IncludeDirs:%=-I%)

%.o: %.cc %.h 
	$(CXX) -std=c++11  $(DevFlags) $(CCFlags) $(UserCCFlags) $(CCDefines) -c -o $@ $<

all: $(Objs)
	$(CC) -std=c++11 -shared -L/usr/lib64/ -lusb -o libPh2_TCUSB.so $(Objs) -pthread
	mv libPh2_TCUSB.so lib
	#g++ -g -std=c++11 2sseh.cc -Llib -lPh2_TCUSB -o 2sseh.out
	#g++ -g -std=c++11 psfeh.cc -Llib -lPh2_TCUSB -o psfeh.out
	#g++ -g -std=c++11 psroh.cc -Llib -lPh2_TCUSB -lusb-1.0 -o psroh.out
	#g++ -g -std=c++11 2sfeh_v1.cc -Llib -lPh2_TCUSB -o 2sfeh_v1.out
	#g++ -g -std=c++11 half_skeleton.cc -Llib -lPh2_TCUSB -o half_skeleton.out
	g++ -g -std=c++11 pspoh.cc -Llib -lPh2_TCUSB -o pspoh.out

clean:
	rm -f *.o lib/*.so

