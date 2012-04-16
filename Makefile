# Project: sfhp
# Makefile created by S.H.M ,Email:posinfo@126.com

CPP  = arm-elf-g++.exe
CC   = arm-elf-gcc.exe
AR  = arm-elf-ar.exe
LD   = arm-elf-ld.exe
OBJCOPY   = arm-elf-objcopy.exe
OBJ  = CARD.o GPRS.o IsLockUser.o LoginWay.o Main.o NetSetting.o User.o Menu.o
LINKOBJ  = CARD.o GPRS.o IsLockUser.o LoginWay.o Main.o NetSetting.o User.o Menu.o
LIBS =   
INCS = 
CXXINCS = 
BIN  = sfhp.cof
CXXFLAGS = $(CXXINCS)   -Wall
CFLAGS = $(INCS)   -Wall
RM = rm -f

.PHONY: all  clean

all: sfhp.cof


clean: 
	${RM} $(OBJ) $(BIN)


CARD.o: CARD.c
	$(CC) $(CFLAGS) -c CARD.c -o CARD.o

GPRS.o: GPRS.c
	$(CC) $(CFLAGS) -c GPRS.c -o GPRS.o

IsLockUser.o: IsLockUser.c
	$(CC) $(CFLAGS) -c IsLockUser.c -o IsLockUser.o

LoginWay.o: LoginWay.c
	$(CC) $(CFLAGS) -c LoginWay.c -o LoginWay.o

Main.o: Main.c
	$(CC) $(CFLAGS) -c Main.c -o Main.o

NetSetting.o: NetSetting.c
	$(CC) $(CFLAGS) -c NetSetting.c -o NetSetting.o

User.o: User.c
	$(CC) $(CFLAGS) -c User.c -o User.o

Menu.o: Menu.c
	$(CC) $(CFLAGS) -c Menu.c -o Menu.o

$(BIN): $(OBJ)
	$(LD) C:/HandPos/IDE/crt0.o $(LINKOBJ)  -o sfhp.cof $(LIBS) -T C:/HandPos/IDE/ldscript
	$(OBJCOPY) -O binary sfhp.cof sfhp.bin
