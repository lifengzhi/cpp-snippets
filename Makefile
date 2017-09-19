# https://stackoverflow.com/a/16346321
BINDIR := ./bin
create_bin_dir := $(shell mkdir -p $(BINDIR))
OBJDIR := ./obj
create_obj_dir := $(shell mkdir -p $(OBJDIR))
SRCDIR := ./src

CPPFLAGS := -I ./ -I ./GSL/include
CXXFLAGS := -std=c++1z -Wall -Wextra -Werror -pedantic
LDFLAGS := -lpthread

targets :=\
	multithreading01\
	min_element01\
	raii01\
	type_traits\
	read_lines_from_file\
	span01\
	span02\
	const_pass_by_value\
	tests4geeks_sample_test_question\
	array_copy \
	preincrement

ifeq ($(shell expr `$(CXX) -dumpversion | cut -c 1-1` \> 6), 1)
CXXFLAGS += \
    -Wduplicated-cond \
    -Wduplicated-branches \
    -Wlogical-op \
    -Wrestrict \
    -Wnull-dereference \
    -Wold-style-cast \
    -Wuseless-cast \
    -Wdouble-promotion \
    -Wshadow \
    -Wformat=2

targets += \
    arrays_with_auto \
    check_type_deduction
endif

define make-target
$(1): $(OBJDIR)/$(1).o
	@echo "LD $(1)"
	$(CXX) -o $(BINDIR)/$(1) $(OBJDIR)/$(1).o $(LDFLAGS)
all:: $(1)
endef

# To debug a foreach loop, replace $(eval ...) with $(info ...)
$(foreach element,$(targets),$(eval $(call make-target,$(element))))

clean:
	rm -rf $(OBJDIR)/* $(BINDIR)/*

.PHONY: all clean

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@echo "CXX $<"
	$(CXX) -c -o $@ $< $(CPPFLAGS) $(CXXFLAGS)

# http://make.mad-scientist.net/managing-recipe-echoing/
$(V).SILENT:
