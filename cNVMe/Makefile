CXX = g++
CXXFLAGS = -w -std=c++11 -fpermissive -pthread -fPIC
DEBUG = 1

ifeq ($(DEBUG), 1)
CXXFLAGS += -g -O0 -D_DEBUG
else
CXXFLAGS += -O3
endif

PREFIX = /home/yixiao.du/cNVMe

SO64 = $(PREFIX)/lib/libcnvme.so
SO32 = $(PREFIX)/lib/libcnvme32.so

SRCS += Command.cpp
SRCS += Controller.cpp
SRCS += ControllerRegisters.cpp
SRCS += DLL.cpp
SRCS += Driver.cpp
SRCS += Identify.cpp
# SRCS += Logger.cpp
SRCS += LoopingThread.cpp
SRCS += Namespace.cpp
SRCS += Payload.cpp
SRCS += PCIe.cpp
SRCS += PRP.cpp
SRCS += Queue.cpp
SRCS += Strings.cpp
SRCS += System.cpp
SRCS += Tests.cpp

TEST_SRC = Main.cpp
TEST_EXE = testmain.out

HDRS += Command.h
HDRS += Constants.h
HDRS += Controller.h
HDRS += ControllerRegisters.h
HDRS += DLL.h
HDRS += Driver.h
HDRS += Identify.h
HDRS += Logger.h
HDRS += LogPages.h
HDRS += LoopingThread.h
HDRS += Namespace.h
HDRS += Payload.h
HDRS += PCIe.h
HDRS += PRP.h
HDRS += Queue.h
HDRS += Strings.h
HDRS += System.h
HDRS += Tests.h
HDRS += Types.h

.PHONY: all so64 clean headers test

all: so64 headers

$(TEST_EXE): $(SRCS) $(TEST_SRC)
	$(CXX) $^ $(CXXFLAGS) -o $(TEST_EXE)

test: $(TEST_EXE)
	./$(TEST_EXE)

so64: $(SO64)

$(SO64): $(SRCS)
	mkdir -p $(PREFIX)/lib
	$(CXX) $^ $(CXXFLAGS) -DDLL_BUILD -shared -m64 -o $(SO64)

headers: $(HDRS)
	mkdir -p $(PREFIX)/include/cnvme
	cp *.h $(PREFIX)/include/cnvme

$(SO32): $(SRCS)
	mkdir -p $(PREFIX)/lib
	$(CXX) $^ $(CXXFLAGS) -DDLL_BUILD -shared -m32 -o $(SO32)

clean:
	rm -f *.out *.so
	rm -f $(SO64) $(SO32)