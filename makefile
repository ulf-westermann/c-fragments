CC = gcc
RM = trash -f

EXECUTABLE = test
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
DEPS = $(OBJS:.o=.d)

CPPFLAGS = $(INCFLAGS) -MMD -MP
CFLAGS = -g -std=c99 -O3 -Wall -Wpedantic -Wextra -fanalyzer

$(EXECUTABLE): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@ $(LDLIBS)

.PHONY: runtest
runtest: $(EXECUTABLE)
	./test

.PHONY: clean
clean:
	$(RM) $(EXECUTABLE) $(OBJS) $(DEPS) tags

.PHONY: format
format:
	clang-format -i *.c *.h

.PHONY: check
check:
	cppcheck --check-config --std=c11 --enable=all --suppress=missingIncludeSystem -I. $(SRCS)
	cbmc --function cbmc --object-bits 16 --unwind 256 --trace --localize-faults --bounds-check --pointer-check --memory-leak-check --memory-cleanup-check --div-by-zero-check --signed-overflow-check --unsigned-overflow-check --pointer-overflow-check --conversion-check --undefined-shift-check --float-overflow-check --nan-check --enum-range-check --pointer-primitive-check $(SRCS)

.PHONY: tags
tags:
	ctags -R .

-include $(DEPS)
