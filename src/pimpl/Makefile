BINDIR := ./bin
create_bin_dir := $(shell mkdir -p $(BINDIR))
OBJDIR := ./.obj
create_obj_dir := $(shell mkdir -p $(OBJDIR))
SRCDIR := .

CPPFLAGS := -I ./
CXXFLAGS := -std=c++17 -Wall -Wextra -Werror -Wshadow -pedantic

target: pimpl

.PHONY: clean
clean:
	rm -rf $(OBJDIR)/* $(BINDIR)/*

pimpl: $(OBJDIR)/pimpl.o $(OBJDIR)/FridgeImpl.o
	@echo "LD pimpl"
	$(CXX) -o $(BINDIR)/pimpl $(OBJDIR)/pimpl.o $(OBJDIR)/FridgeImpl.o
all:: pimpl

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@echo "CXX $<"
	cppcheck --enable=all --suppress=missingIncludeSystem $<
	$(CXX) -c -o $@ $< $(CPPFLAGS) $(CXXFLAGS)

# http://make.mad-scientist.net/managing-recipe-echoing/
$(V).SILENT: