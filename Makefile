Objs            = USB_a.o USB_libusb.o
CC              = gcc

CXX             = gcc
CCFlags         = -g -O1 -Wall -w -pedantic -fPIC -Wcpp -L/usr/lib64/ -lusb
DevFlags		= -D_GLIBCXX_USE_CXX11_ABI=0

TARGET	= pspoh

%.o: %.cc %.h 
	$(CXX) -std=c++11  $(DevFlags) $(CCFlags) $(UserCCFlags) $(CCDefines) -c -o $@ $<

pspoh: pspoh.o TC_PSPOH.o 
	g++ -g -std=c++11 -Llib -lPh2_TCUSB -o $(TARGET) $(TARGET).o TC_PSPOH.o 

$(TARGET).o: $(TARGET).cc TC_PSPOH.h USB_a.h
	g++ -g -std=c++11 -c $(TARGET).cc

reseter: reseter.o TC_PSPOH.o 
	g++ -g -std=c++11 -Llib -lPh2_TCUSB -o reseter reseter.o TC_PSPOH.o 

reseter.o: reseter.cc TC_PSPOH.h USB_a.h
	g++ -g -std=c++11 -c reseter.cc

fileExtists: fileExtists.o
	g++ -g -std=c++11 -Llib -lPh2_TCUSB -o fileExtists fileExtists.o

fileExtists.o: fileExtists.cpp
	g++ -g -std=c++11 -c fileExtists.cpp

TC_PSPOH.o: TC_PSPOH.h

USB_a.o: USB_a.h

USB_libusb.o: USB_libusb.h


all: $(Objs)
	$(CC) -std=c++11 -shared -L/usr/lib64/ -lusb -o libPh2_TCUSB.so $(Objs) -pthread
	cp libPh2_TCUSB.so lib
	#g++ -g -std=c++11 2sseh.cc -Llib -lPh2_TCUSB -o 2sseh.out
	#g++ -g -std=c++11 psfeh.cc -Llib -lPh2_TCUSB -o psfeh.out
	#g++ -g -std=c++11 psroh.cc -Llib -lPh2_TCUSB -lusb-1.0 -o psroh.out
	#g++ -g -std=c++11 2sfeh_v1.cc -Llib -lPh2_TCUSB -o 2sfeh_v1.out
	#g++ -g -std=c++11 half_skeleton.cc -Llib -lPh2_TCUSB -o half_skeleton.out
	#g++ -g -std=c++11 pspoh.cc -Llib -lPh2_TCUSB -o pspoh.out
	
clean:
	rm -f *.o lib/*.so
	$(RM) $(TARGET) $(TARGET).o
	$(RM) TC_PSPOH.o
