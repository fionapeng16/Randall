# Make x86-64 random byte generators.

# Copyright 2015, 2020, 2021 Paul Eggert

# This program is free software: you can redistribute it and/or
# modify it under the terms of the GNU General Public License as
# published by the Free Software Foundation, either version 3 of the
# License, or (at your option) any later version.

# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

# Optimization level.  Change this -O2 to -Og or -O0 or whatever.
OPTIMIZE =

# The C compiler and its options.
CC = gcc
CFLAGS = $(OPTIMIZE) -g3 -Wall -Wextra -fanalyzer \
  -march=native -mtune=native -mrdrnd

# The archiver command, its options and filename extension.
TAR = tar
TARFLAGS = --gzip --transform 's,^,randall/,'
TAREXT = tgz

default: randall

randall: randall.c
	$(CC) $(CFLAGS) $@.c -o $@

assignment: randall-assignment.$(TAREXT)
assignment-files = COPYING Makefile randall.c
randall-assignment.$(TAREXT): $(assignment-files)
	$(TAR) $(TARFLAGS) -cf $@ $(assignment-files)

submission-tarball: randall-submission.$(TAREXT)
submission-files = $(assignment-files) \
  notes.txt # More files should be listed here, as needed.
randall-submission.$(TAREXT): $(submission-files)
	$(TAR) $(TARFLAGS) -cf $@ $(submission-files)

repository-tarball:
	$(TAR) -czf randall-git.tgz .git

.PHONY: default clean assignment submission-tarball repository-tarball

clean:
	rm -f *.o *.$(TAREXT) randall

# Unit test that checks NBYTES.
check: randall
	@echo "Running test cases..."
	@echo "=========== TEST 1 ==========="
@./randall 20 | wc -c | (grep -q "^20$$" && echo "PASSED") || (echo "FAILED" && false)
# Automatically formats all of your C code.
format:
	clang-format -i *.c *.h
# Helps find memory leaks. For an explanation on each flag, see this link.
valgrind: randall
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./randall 100
# Runs the Undefined Behavior (UBSAN) and Address (ASAN) sanitizers. GCC doesn’t support these on the SEASNet servers so we recommend using clang instead (a different C compiler).
sanitizers:
	clang -g3 -Wall -Wextra -mtune-native -mrdrnd -fsanitize=address \
		-fsanitize=undefined *.c -o randall

# Make sure to add these rules to .PHONY. These tells make that it should not look for files called each of these recipe targets.
.PHONY: default clean assignment submission-tarball repository-tarball check format valgrind sanitizers
