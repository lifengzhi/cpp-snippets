# https://stackoverflow.com/a/16346321
create_bin_dir := $(shell mkdir -p ./bin)

BINDIR := ./bin

CPPFLAGS := -I ./
CXXFLAGS := -std=c++14 -Wall -Wextra -Werror -pedantic

all: multithreading01 \
	 min_element01 \
	 type_traits

.PHONY: all clean

multithreading01: multithreading01.o
	@echo "LD $@"
	$(CXX) -o $(BINDIR)/$@ $^ $(CPPFLAGS) $(CXXFLAGS) -lpthread

min_element01: min_element01.o
	@echo "LD $@"
	$(CXX) -o $(BINDIR)/$@ $^ $(CPPFLAGS) $(CXXFLAGS)

type_traits: type_traits.o
	@echo "LD $@"
	$(CXX) -o $(BINDIR)/$@ $^ $(CPPFLAGS) $(CXXFLAGS)

clean:
	rm -rf *.o $(BINDIR)/*

%.o: %.cpp
	@echo "CXX $<"
	$(CXX) -c -o $@ $< $(CPPFLAGS) $(CXXFLAGS)

# http://make.mad-scientist.net/managing-recipe-echoing/
$(V).SILENT:
