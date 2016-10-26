AutomatedMakefile = am
CC = g++


PROJECT_PATH = $(CURRENT_DIR)

INC_DIRS = -I$(CURRENT_DIR)/CSC2110
LIB_DIRS = -L$(CURRENT_DIR)/CSC2110

LIBS = -lCSC2110

COMPILE = $(CC) $(INC_DIRS) -c
LINK = $(CC) $(LIB_DIRS)

FILES = RadixSortDriver.o 
EXECUTABLE = Pro3.exe

all: Pro3	
	$(EXECUTABLE)

Pro3: 						$(FILES)
						$(LINK) $(FILES) $(LIBS) -o $(EXECUTABLE) 

InventoryDriver.o:			RadixSort.h RadixSortDriver.cpp
						$(COMPILE) RadixSortDriver.cpp

#DequeArrayDriver.o:    			   dequeArrayDriver.cpp
#						$(COMPILE) dequeArrayDriver.cpp
