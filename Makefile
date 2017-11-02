.PHONY : clean all

BINDIR := bin
OBJDIR := obj
SRCDIR := src
AUXDIR := $(BINDIR) $(OBJDIR)

SOURCES := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

MKDIR := mkdir -p
RM    := rm -rf

CXX      ?= g++
CXXFLAGS := --std=c++14 -O3 -D NDEBUG -Wall

all : $(OBJECTS)

$(AUXDIR) :
	$(MKDIR) $@

$(OBJECTS) : $(OBJDIR)/%.o : $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) -c -o $@ $^ $(CXXFLAGS)

clean :
	$(RM) $(AUXDIR)
