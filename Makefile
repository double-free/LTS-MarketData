###########################################
#Makefile for simple programs
###########################################
INC=
LIBPATH=$$HOME/Lib/LTS
LIB=-l:L2mduserapi.so -lpthread
CC=g++ -std=c++14
# display all warnings
CC_FLAG=-Wall -g -O2

PRG=MarketMachine
OBJ=main.o ltsmdspi.o mmap_buffer/mmapper.o\
		ThirdParty/inih/ini.o ThirdParty/inih/INIReader.o

$(PRG):$(OBJ)
	$(CC) $(INC) -o $@ $(OBJ) -L$(LIBPATH) $(LIB)

.SUFFIXES: .c .o .cpp
.cpp.o:
	$(CC) $(CC_FLAG) $(INC) -c $*.cpp -o $*.o

.PRONY:clean
clean:
	@echo "Removing linked and compiled files......"
	rm -f $(OBJ) $(PRG)
