.PHONY : clean all test

BINDIR  := bin
OBJDIR  := obj
SRCDIR  := src
TESTDIR := test
AUXDIR  := $(BINDIR) $(OBJDIR)

SOURCES := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

TEST_SOURCES := $(wildcard $(TESTDIR)/*.cpp)
TEST_OBJECTS := $(TEST_SOURCES:$(TESTDIR)/%.cpp=$(BINDIR)/%)

MKDIR := mkdir
RM    := rm -rf

CXX      ?= g++
CXXFLAGS := -std=c++14 -O3 -D NDEBUG -Wall -Werror
TEST_CXXFLAGS := -std=c++14 -Og -ggdb -D DEBUG -Wall -Werror -I$(SRCDIR)

all : $(OBJECTS)
test: all $(TEST_OBJECTS)

test_run: test
	$(foreach t,$(TEST_OBJECTS),./$(t);)

$(AUXDIR) :
	$(MKDIR) $@

$(OBJECTS) : $(OBJDIR)/%.o : $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) -c -o $@ $^ $(CXXFLAGS)

$(TEST_OBJECTS) : $(BINDIR)/% : $(TESTDIR)/%.cpp $(OBJECTS) | $(BINDIR)
	$(CXX) -o $@ $^ $(TEST_CXXFLAGS)

clean :
	$(RM) $(AUXDIR)
