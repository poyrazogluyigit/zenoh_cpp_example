LIBDIR=/usr/local/lib
CXX=/usr/bin/g++
CXXFLAGS=-L$(LIBDIR) -lzenohc

run: sub pub
	@./z_pub &
	@./z_sub

sub:
	@g++ z_sub.cpp $(CXXFLAGS) -o z_sub

pub:
	@g++ z_pub.cpp $(CXXFLAGS) -o z_pub

clean:
	@rm z_pub z_sub