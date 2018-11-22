#! /bin/bash -e
# -----------------------------------------------------------------------------
# CppAD: C++ Algorithmic Differentiation: Copyright (C) 2003-15 Bradley M. Bell
#
# CppAD is distributed under the terms of the
#              Eclipse Public License Version 2.0.
#
# This Source Code may also be made available under the following
# Secondary License when the conditions for such availability set forth
# in the Eclipse Public License, Version 2.0 are satisfied:
#            GNU General Public License, Version 3.0.
# -----------------------------------------------------------------------------
if [ ! -e "bin/check_op_code.sh" ]
then
	echo "bin/check_op_code.sh: must be executed from its parent directory"
	exit 1
fi
echo "bin/check_op_code.sh: checking that op codes are in alphabetical order:"
file='include/cppad/local/op_code.hpp'
# ---------------------------------------------------------------------------
# check enum list of codes are in alphabetical order
sed -n -e '/^enum/,/^\tNumberOp  /p' $file | sed \
	-e '/^enum/d' \
	-e '/^\tNumberOp  /d' \
	-e 's/^[	]*//' \
	-e 's/Op[, ].*//' \
	-e '/^\/\//d' > bin/op_code.1.$$
#
sort --ignore-case bin/op_code.1.$$ > bin/op_code.2.$$
if ! diff bin/op_code.1.$$ bin/op_code.2.$$
then
	echo "check_op_code.sh: enum list is not in alphabetical order"
	rm bin/op_code.*.$$
	exit 1
fi
# -----------------------------------------------------------------------------
# check NumArgTable
sed -n -e '/NumArgTable\[\]/,/^[ \t]*};/p' $file | \
	sed \
		-e '/NumArgTable\[\]/d' \
		-e '/NumberOp.*not used/d' \
		-e '/^[ \t]*};/d' \
		-e 's|^[ \t]*[0-9],* *// *||' \
		-e 's|Op.*||' \
		> bin/op_code.3.$$
#
if ! diff bin/op_code.1.$$ bin/op_code.3.$$
then
	echo "check_op_code.sh: NumArgTable list is not in alphabetical order"
	rm bin/op_code.*.$$
	exit 1
fi
# -----------------------------------------------------------------------------
# check NumResTable (last line of NumResTable is not used)
sed -n -e '/NumResTable\[\]/,/^[ \t]*};/p' $file | \
	sed \
		-e '/NumResTable\[\]/d' \
		-e '/^[ \t]*};/d' \
		-e '/NumberOp.*not used/d' \
		-e 's|^[ \t]*[0-9],* *// *||' \
		-e 's|Op.*||' \
		> bin/op_code.4.$$
#
if ! diff bin/op_code.1.$$ bin/op_code.4.$$
then
	echo "check_op_code.sh: NumResTable list is not in alphabetical order"
	echo "(or missing last line)"
	rm bin/op_code.*.$$
	exit 1
fi
# -----------------------------------------------------------------------------
# check OpNameTable
sed -n -e '/const char \*OpNameTable\[\]/,/^[ \t]*};/p' $file | \
	sed \
		-e '/OpNameTable\[\]/d' \
		-e '/"Number".*not used/d' \
		-e '/^[ \t]*};/d' \
		-e 's|^[ \t]*"||' \
		-e 's|".*||' \
		> bin/op_code.5.$$
#
if ! diff bin/op_code.1.$$ bin/op_code.5.$$
then
	echo "check_op_code.sh: OpName list is not in alphabetical order"
	rm bin/op_code.*.$$
	exit 1
fi
# -----------------------------------------------------------------------------
# clean up
rm bin/op_code.*.$$
# ----------------------------------------------------------------------------
echo "$0: OK"
exit 0
