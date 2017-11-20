/* --------------------------------------------------------------------------
CppAD: C++ Algorithmic Differentiation: Copyright (C) 2003-17 Bradley M. Bell

CppAD is distributed under multiple licenses. This distribution is under
the terms of the
                    Eclipse Public License Version 1.0.

A copy of this license is included in the COPYING file of this distribution.
Please visit http://www.coin-or.org/CppAD/ for information on other licenses.
-------------------------------------------------------------------------- */

/*
$begin subgraph_jac_rev.cpp$$
$spell
	Cpp
	Jacobian
$$

$section Computing Sparse Jacobian Using Reverse Mode: Example and Test$$

$code
$srcfile%example/sparse/subgraph_jac_rev.cpp%0%// BEGIN C++%// END C++%1%$$
$$

$end
*/
// BEGIN C++
# include <cppad/cppad.hpp>
bool subgraph_jac_rev(void)
{	bool ok = true;
	//
	using CppAD::AD;
	using CppAD::NearEqual;
	using CppAD::sparse_rc;
	using CppAD::sparse_rcv;
	//
	typedef CPPAD_TESTVECTOR(AD<double>) a_vector;
	typedef CPPAD_TESTVECTOR(double)     d_vector;
	typedef CPPAD_TESTVECTOR(size_t)     s_vector;
	typedef CPPAD_TESTVECTOR(bool)       b_vector;
	//
	// domain space vector
	size_t n = 4;
	a_vector  a_x(n);
	for(size_t j = 0; j < n; j++)
		a_x[j] = AD<double> (0);
	//
	// declare independent variables and starting recording
	CppAD::Independent(a_x);
	//
	size_t m = 3;
	a_vector  a_y(m);
	a_y[0] = a_x[0] + a_x[1];
	a_y[1] = a_x[2] + a_x[3];
	a_y[2] = a_x[0] + a_x[1] + a_x[2] + a_x[3] * a_x[3] / 2.;
	//
	// create f: x -> y and stop tape recording
	CppAD::ADFun<double> f(a_x, a_y);
	//
	// new value for the independent variable vector
	d_vector x(n);
	for(size_t j = 0; j < n; j++)
		x[j] = double(j);
	/*
	       [ 1 1 0 0  ]
	J(x) = [ 0 0 1 1  ]
	       [ 1 1 1 x_3]
	*/
	//
	// row-major order values of J(x)
	size_t nnz = 8;
	s_vector check_row(nnz), check_col(nnz);
	d_vector check_val(nnz);
	for(size_t k = 0; k < nnz; k++)
	{	// check_val
		if( k < 7 )
			check_val[k] = 1.0;
		else
			check_val[k] = x[3];
		//
		// check_row and check_col
		check_col[k] = k;
		if( k < 2 )
			check_row[k] = 0;
		else if( k < 4 )
			check_row[k] = 1;
		else
		{	check_row[k] = 2;
			check_col[k] = k - 4;
		}
	}
	//
	// select all range components of domain and range
	b_vector select_domain(n), select_range(m);
	for(size_t j = 0; j < n; ++j)
		select_domain[j] = true;
	for(size_t i = 0; i < m; ++i)
		select_range[i] = true;
	//
	bool transpose     = false;
	sparse_rc<s_vector> pattern_jac;
	f.subgraph_sparsity(
		select_domain, select_range, transpose, pattern_jac
	);
	//
	// compute entire Jacobian
	sparse_rcv<s_vector, d_vector> subset( pattern_jac );
	f.subgraph_jac_rev(x, subset);
	//
	const s_vector row( subset.row() );
	const s_vector col( subset.col() );
	const d_vector val( subset.val() );
	s_vector row_major = subset.row_major();
	//
	ok  &= subset.nnz() == nnz;
	for(size_t k = 0; k < nnz; k++)
	{	ok &= row[ row_major[k] ] == check_row[k];
		ok &= col[ row_major[k] ] == check_col[k];
		ok &= val[ row_major[k] ] == check_val[k];
	}
	//
	return ok;
}
// END C++
