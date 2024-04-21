CC = gcc
RM = trash -f

EXECUTABLE = test
SRCS = test.c
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
	cbmc --trace --localize-faults --function main --unwind 128 --bounds-check --pointer-check --memory-leak-check --div-by-zero-check --signed-overflow-check --unsigned-overflow-check --pointer-overflow-check --conversion-check --undefined-shift-check --float-overflow-check --nan-check $(SRCS)

.PHONY: tags
tags:
	ctags -R .

-include $(DEPS)
