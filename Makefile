Objs                    = USB_a.o 
CC              = gcc
CXX             = gcc
CCFlags         = -g -O1 -Wall -w -pedantic -fPIC -Wcpp -L/usr/lib64/ -lusb
#CCFlags         = -g -O1 -Wall -pedantic -fPIC -Wcpp -L/usr/lib64/ -lusb
DevFlags		= -D_GLIBCXX_USE_CXX11_ABI=0

#IncludeDirs     =  /opt/cactus/include ../

#IncludePaths            = $(IncludeDirs:%=-I%)

%.o: %.cc %.h 
	$(CXX) -std=c++11  $(DevFlags) $(CCFlags) $(UserCCFlags) $(CCDefines) -c -o $@ $<

all: $(Objs)
	$(CC) -std=c++11 -shared -L/usr/lib64/ -lusb -o libPh2_TCUSB.so $(Objs) -pthread
	mv libPh2_TCUSB.so lib

clean:
	rm -f *.o lib/*.so

