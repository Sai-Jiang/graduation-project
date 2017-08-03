CC=g++
CFLAGS=-Wall -O2 
LDFLAGS=
LIBS=-lm -lboost_system -lpthread
CPPFLAGS=

OBJS= EncodedPackage.o Encoder.o PaddingPackage.o Serializer.o RobustSolitonDistribution.o \

%.o: %cpp
	$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<

all: test_Encoder test_UDPRawServer test_UDPRawClient test_UDPEncodedServer test_UDPEncodedClient

test_Encoder: test_Encoder.o $(OBJS)
	$(CC) $(CFLAGS) -lboost_system -lpthread $^ -o $@

test_UDPRawServer: UDPServer.o UDPRawServer.o test_UDPRawServer.o $(OBJS)
	$(CC) $(CFLAGS) -lboost_system -lpthread $^ -o $@

test_UDPRawClient: UDPClient.o UDPRawClient.o test_UDPRawClient.o $(OBJS)
	$(CC) $(CFLAGS) -lboost_system -lpthread $^ -o $@

test_UDPEncodedServer: UDPServer.o UDPEncodedServer.o test_UDPEncodedServer.o $(OBJS)
	$(CC) $(CFLAGS) -lboost_system -lpthread $^ -o $@

test_UDPEncodedClient: UDPClient.o UDPEncodedClient.o test_UDPEncodedClient.o $(OBJS)
	$(CC) $(CFLAGS) -lboost_system -lpthread $^ -o $@

EncodedPackage.o: EncodedPackage.cpp EncodedPackage.h
Encoder.o: Encoder.cpp Encoder.h RobustSolitonDistribution.h \
 EncodedPackage.h PaddingPackage.h
PaddingPackage.o: PaddingPackage.cpp PaddingPackage.h Encoder.h \
 RobustSolitonDistribution.h
RobustSolitonDistribution.o: RobustSolitonDistribution.cpp \
 RobustSolitonDistribution.h
Serializer.o: Serializer.cpp Serializer.h EncodedPackage.h
test_Encoder.o: test_Encoder.cpp Encoder.h RobustSolitonDistribution.h \
 Serializer.h EncodedPackage.h PaddingPackage.h
test_UDPEncodedClient.o: test_UDPEncodedClient.cpp Encoder.h \
 RobustSolitonDistribution.h UDPEncodedClient.h BlockQueue.h \
 EncodedPackage.h Serializer.h UDPClient.h
test_UDPEncodedServer.o: test_UDPEncodedServer.cpp Encoder.h \
 RobustSolitonDistribution.h UDPEncodedServer.h BlockQueue.h Serializer.h \
 EncodedPackage.h UDPServer.h
test_UDPRawClient.o: test_UDPRawClient.cpp UDPRawClient.h UDPClient.h
test_UDPRawServer.o: test_UDPRawServer.cpp UDPRawServer.h UDPServer.h
UDPClient.o: UDPClient.cpp UDPClient.h
UDPEncodedClient.o: UDPEncodedClient.cpp UDPEncodedClient.h BlockQueue.h \
 EncodedPackage.h Encoder.h RobustSolitonDistribution.h Serializer.h \
 UDPClient.h PaddingPackage.h
UDPEncodedServer.o: UDPEncodedServer.cpp UDPEncodedServer.h BlockQueue.h \
 Encoder.h RobustSolitonDistribution.h Serializer.h EncodedPackage.h \
 UDPServer.h PaddingPackage.h
UDPRawClient.o: UDPRawClient.cpp UDPRawClient.h UDPClient.h
UDPRawServer.o: UDPRawServer.cpp UDPRawServer.h UDPServer.h
UDPServer.o: UDPServer.cpp UDPServer.h

.PHONY: clean

clean:
	rm -rf *.o *.h264
	find . -perm -u=rwx -a ! -name "st*" -a ! -regex "\./\..*" -delete
