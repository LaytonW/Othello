.PHONY : clean all test

BINDIR  := bin
OBJDIR  := obj
SRCDIR  := src
TESTDIR := test
AUXDIR  := $(BINDIR) $(OBJDIR)

SOURCES := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

TEST_SOURCES := $(wildcard $(TESTDIR)/*.cpp)
TEST_OBJECTS := $(TEST_SOURCES:$(TESTDIR)/%.cpp=$(OBJDIR)/%.o)

MKDIR := mkdir -p
RM    := rm -rf

CXX      ?= g++
CXXFLAGS := --std=c++14 -O3 -D NDEBUG -Wall -Werror

all : $(OBJECTS)
test: $(TEST_OBJECTS)

$(AUXDIR) :
	$(MKDIR) $@

$(OBJECTS) : $(OBJDIR)/%.o : $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) -c -o $@ $^ $(CXXFLAGS)

clean :
	$(RM) $(AUXDIR)
