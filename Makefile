# https://stackoverflow.com/a/16346321
BINDIR := ./bin
create_bin_dir := $(shell mkdir -p $(BINDIR))
OBJDIR := ./obj
create_obj_dir := $(shell mkdir -p $(OBJDIR))
SRCDIR := ./src

CPPFLAGS := -I ./ -I ./GSL/include
CXXFLAGS := -std=c++17 -Wall -Wextra -Werror -Wshadow -pedantic
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
	preincrement \
	exception01 \
	std_endl \
	enum_as_index \
	tee \
	character_literals \
	exception02 \
	crtp_vs_mixin \
	singleton \
	factory

ifeq ($(shell ./check_compiler.sh gnu 70000 $(CXX)),0)
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

# shellcheck all shell scripts
# https://stackoverflow.com/a/5423310/496459
SHCHK := shellcheck
scripts := $(shell find . -type f -name \*.sh)
.PHONY: ${scripts}
${scripts}:
	@echo "SHCHK $@"
	$(SHCHK) $@

.PHONY: shellcheck
shellcheck: ${scripts}

.PHONY: all
all:: shellcheck
define make-target
$(1): $(OBJDIR)/$(1).o
	@echo "LD $(1)"
	$(CXX) -o $(BINDIR)/$(1) $(OBJDIR)/$(1).o $(LDFLAGS)
all:: $(1)
endef
# To debug a foreach loop, replace $(eval ...) with $(info ...)
$(foreach element,$(targets),$(eval $(call make-target,$(element))))

.PHONY: clean
clean:
	rm -rf $(OBJDIR)/* $(BINDIR)/*

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@echo "CXX $<"
	cppcheck --enable=all --suppress=missingIncludeSystem $<
	$(CXX) -c -o $@ $< $(CPPFLAGS) $(CXXFLAGS)

# http://make.mad-scientist.net/managing-recipe-echoing/
$(V).SILENT:
