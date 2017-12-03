.PHONY : clean all test othello run

BINDIR  := bin
OBJDIR  := obj
SRCDIR  := src
TESTDIR := test
AUXDIR  := $(BINDIR) $(OBJDIR)

TARGET  := othello
SOURCES := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
OTHELLO := $(BINDIR)/$(TARGET)

TEST_SOURCES := $(wildcard $(TESTDIR)/*.cpp)
TEST_OBJECTS := $(TEST_SOURCES:$(TESTDIR)/%.cpp=$(BINDIR)/%)
TEST_DEPOBJS := $(filter-out $(OBJDIR)/$(TARGET).o,$(OBJECTS))

MKDIR := mkdir
RM    := rm -rf

CXX      ?= g++
CXXFLAGS := -std=c++14 -O3 -D NDEBUG -Wall -Werror
TEST_CXXFLAGS := -std=c++14 -Og -ggdb -D DEBUG -Wall -Werror -I$(SRCDIR)

othello: all $(OTHELLO)
all : $(OBJECTS)
test: all $(TEST_OBJECTS)

test_run: test
	$(foreach t,$(TEST_OBJECTS),./$(t);)

run: othello
	./$(OTHELLO)

$(AUXDIR) :
	$(MKDIR) $@

$(OBJECTS) : $(OBJDIR)/%.o : $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) -c -o $@ $^ $(CXXFLAGS)

$(TEST_OBJECTS) : $(BINDIR)/% : $(TESTDIR)/%.cpp $(TEST_DEPOBJS) | $(BINDIR)
	$(CXX) -o $@ $^ $(TEST_CXXFLAGS)

$(OTHELLO) : $(OBJECTS) | $(BINDIR)
	$(CXX) -o $@ $^ $(CXXFLAGS)

clean :
	$(RM) $(AUXDIR)
