#
# Copyright 2022-2032 by MICROPORT
#
# File Name:  	Makefile
# File Path:   
# Author:		Richard Xie
# Version:		1.0
# Description: use this Makefile to build unit test
#
#
# History:
#  Date		    Author			CR number	        CR Title
 
INCLUDE_DIRS = /usr/include/ /usr/local/include/ ../../include/    \
../UnitTestFramework/src											\
../UnitTestFramework/include/gtest									\
../UnitTestFramework/include										\
../UnitTestFramework/include/gtest/internal							\
../../include/UtilityComponent


CP = cp -f
RM-F := rm -f
C11 = -std=c++11
THREAD = -pthread

CC = gcc
CXX = g++
READELF = readelf
STRIP = strip
COMPILE_OPTIONS = $(C11) $(THREAD)
COMMON_LIB_PATH =

#add for code coverage audit..
ifeq ($(GCOV), yes)
   OPTIM     += -fprofile-arcs -ftest-coverage
   LINKERCXX += -fprofile-arcs -ftest-coverage
else
   OPTIM     +=
   LINKERCXX +=
endif

EXECUTABLE := TestApp    # 可执行文件名
MAPFILE := TestApp.map
WL_MAP   := -Wl,-Map=TestApp.map
SYMSFILE := TestApp.syms
ELFBAKFILE := TestApp.bak


LIBS := pthread


# 除了当前目录外，其他的源代码文件目录
SRC_DIR:=  ../UnitTestFramework/src   \
../../src/UtilityComponent \

		   
CPPFLAGS += $(COMPILE_OPTIONS) $(addprefix -I,$(INCLUDE_DIRS))
CPPFLAGS += -DFL_LIBRARY -MMD


# # You shouldn't need to change anything below this point.
#
SRCS := $(wildcard *.cpp) $(wildcard $(addsuffix /*.cpp, $(SRC_DIR)))
OBJS := $(patsubst %.cpp,%.o,$(SRCS))
DEPS := $(patsubst %.o,%.d,$(OBJS))
MISSING_DEPS := $(filter-out $(wildcard $(DEPS)),$(DEPS))
MISSING_DEPS_SOURCES := $(wildcard $(patsubst %.d,%.cpp,$(MISSING_DEPS)))

.PHONY : all deps objs clean veryclean rebuild info

all:   $(EXECUTABLE)
deps : $(DEPS)

objs : $(OBJS)

clean :
	-$(RM-F) $(OBJS) $(DEPS)
	@find . -type f -name "*.gcno" -exec rm {} \;
	@find . -type f -name "*.gcda" -exec rm {} \;
	@find . -type f -name "*.gcov" -exec rm {} \;
	@find . -type f -name "*.info" -exec rm {} \;
	-@echo ' '
	-$(RM-F) $(EXECUTABLE)
	-$(RM-F) $(MAPFILE)
	-@echo ' '


rebuild: veryclean all
-include $(DEPS)
$(EXECUTABLE) : $(OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	$(CXX) $(WL_MAP) -o $(EXECUTABLE) $(OBJS) $(addprefix -l,$(LIBS)) $(LINKERCXX)
#	$(CP) $(EXECUTABLE) $(ELFBAKFILE)
	$(STRIP) $(EXECUTABLE)
	@echo 'Finished building target: $@'
	@echo ' '

info:
	@echo $(SRCS)
	@echo $(OBJS)
	@echo $(DEPS)
	@echo $(MISSING_DEPS)
	@echo $(MISSING_DEPS_SOURCES)