# ifndef CppADCompareIncluded
# define CppADCompareIncluded

/* -----------------------------------------------------------------------
CppAD: C++ Algorithmic Differentiation: Copyright (C) 2003-06 Bradley M. Bell

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
------------------------------------------------------------------------ */

/*
-------------------------------------------------------------------------------
$begin Compare$$
$spell
	cos
	Op
	bool
	const
	inline
$$

$index binary, AD compare operator$$
$index AD, binary compare operator$$
$index compare, AD binary operator$$
$index operator, AD binary compare$$

$index <, AD operator$$
$index <=, AD operator$$
$index >, AD operator$$
$index >=, AD operator$$
$index ==, AD operator$$
$index !=, AD operator$$

$section AD Binary Comparison Operators$$


$table
$bold Syntax$$ 
$cnext 
$syntax% %b% = %x% %Op% %y%$$
$tend

$fend 20$$

$head Purpose$$
Compares two operands where one of the operands is an
$syntax%AD<%Base%>%$$ object.
The comparison has the same interpretation as for 
the $italic Base$$ type.


$head Op$$
The operator $italic Op$$ is one of the following:
$table
$bold Op$$ $pre $$  $cnext $bold Meaning$$                           $rnext
$code <$$   $cnext is $italic x$$ less than $italic y$$              $rnext
$code <=$$  $cnext is $italic x$$ less than or equal $italic y$$     $rnext
$code >$$   $cnext is $italic x$$ greater than $italic y$$           $rnext
$code >=$$  $cnext is $italic x$$ greater than or equal $italic y$$  $rnext
$code ==$$  $cnext is $italic x$$ equal to $italic y$$               $rnext
$code !=$$  $cnext is $italic x$$ not equal to $italic y$$
$tend
 
$head x$$
The operand $italic x$$ has prototype
$syntax%
	const %Type% &%x%
%$$
where $italic Type$$ is $syntax%AD<%Base%>%$$, $italic Base$$, or $code int$$.

$head y$$
The operand $italic y$$ has prototype
$syntax%
	const %Type% &%y%
%$$
where $italic Type$$ is $syntax%AD<%Base%>%$$, $italic Base$$, or $code int$$.

$head b$$
The result $italic b$$ has type
$syntax%
	bool %b%
%$$

$head Taping$$
The result of this operation is a $code bool$$ value
(not an an AD object).
Hence the operation can not be recorded as part of any
$xref/AD/AD Operation Sequence/AD operation sequence/$$.
For example, suppose 
$italic x$$ and $italic y$$ are $syntax%AD<%Base%>%$$ objects,
the tape corresponding to $syntax%AD<%Base%>%$$ is recording,
$italic b$$ is true,
and the subsequent code is
$syntax%
	if( %b% )
		%y% = cos(%x%);
	else	%y% = sin(%x%); 
%$$
only the assignment $syntax%%y% = cos(%x%)%$$ is recorded on the tape.
The $xref/ADFun/CompareChange/CompareChange/$$ function can yield
some information about changes in comparison operation results.
You can use $xref/CondExp/$$ to obtain comparison operations
that depends on the 
$xref/glossary/Independent Variable/independent variable/$$ 
values with out re-taping the AD sequence of operations.

$head Assumptions$$
If one of the $italic Op$$ operators listed above
is used with an $syntax%AD<%Base%>%$$ object,
it is assumed that the same operator is supported by the base type 
$italic Base$$.

$head Example$$
$children%
	Example/Compare.cpp
%$$
The file
$xref/Compare.cpp/$$
contains an example and test of these operations.
It returns true if it succeeds and false otherwise.

$end
-------------------------------------------------------------------------------
*/
//  BEGIN CppAD namespace
namespace CppAD {

template <class Base>

// -------------- RecordCompare(cop, result, left, right) --------------------
void ADTape<Base>::RecordCompare(
	enum CompareOp  cop   ,
	bool           result ,
	const AD<Base> &left  ,
	const AD<Base> &right )
{	size_t ind0, ind1, ind2, ind3;

	// ind[1] = base 2 representation of [result, Var(left), Var(right])
	ind1 = 0;

	// ind[2] = left address
	if( Parameter(left) )
		ind2 = Rec.PutPar(left.value);
	else
	{	ind1 += 2;
		ind2 =  left.taddr;
	}

	// ind[3] = right address
	if( Parameter(right) )
		ind3 = Rec.PutPar(right.value);
	else
	{	ind1 += 4;
		ind3 =  right.taddr;
	}

	// If both left and right are parameters, do not need to record
	if( ind1 == 0 )
		return;

	// ind[1] & 1 = result
	if( result )
		ind1+= 1;

	// ind[0] = cop 
	ind0 = size_t (cop);

	CppADUnknownError( ind1 > 1 );
	CppADUnknownError( NumInd(ComOp) == 4 );

	// put the operator in the tape
	Rec.PutOp(ComOp);
	Rec.PutInd(ind0, ind1, ind2, ind3);
}

// -------------------------------- < -------------------------
# ifdef NDEBUG

template <class Base>
inline bool AD<Base>::operator < (const AD<Base> &right) const
{	bool result =  (value < right.value); 
	return result;
}

# else
template <class Base>
inline bool AD<Base>::operator < (const AD<Base> &right) const
{	bool result =  (value < right.value); 

	if( AD<Base>::Tape()->State() == Empty )
		return result;

	AD<Base>::Tape()->RecordCompare(CompareLt, result, *this, right);

	return result;
}
# endif

// convert other cases into the case above
CppADFoldBinaryOperator(bool, <)

// -------------------------------- <= -------------------------
# ifdef NDEBUG

template <class Base>
inline bool AD<Base>::operator <= (const AD<Base> &right) const
{ 	bool result =  (value <= right.value); 
	return result;
}

# else
template <class Base>
inline bool AD<Base>::operator <= (const AD<Base> &right) const
{ 	bool result =  (value <= right.value); 

	if( AD<Base>::Tape()->State() == Empty )
		return result;

	AD<Base>::Tape()->RecordCompare(CompareLe, result, *this, right);

	return result;
}
# endif

// convert other cases into the case above
CppADFoldBinaryOperator(bool, <=)


// -------------------------------- > -------------------------
# ifdef NDEBUG

template <class Base>
inline bool AD<Base>::operator > (const AD<Base> &right) const
{	bool result =  (value > right.value); 
	return result;
}

# else
template <class Base>
inline bool AD<Base>::operator > (const AD<Base> &right) const
{	bool result =  (value > right.value); 

	if( AD<Base>::Tape()->State() == Empty )
		return result;

	AD<Base>::Tape()->RecordCompare(CompareGt, result, *this, right);

	return result;
}
# endif

// convert other cases into the case above
CppADFoldBinaryOperator(bool, >)

// -------------------------------- >= -------------------------
# ifdef NDEBUG

template <class Base>
inline bool AD<Base>::operator >= (const AD<Base> &right) const
{ 	bool result =  (value >= right.value); 
	return result;
}

# else
template <class Base>
inline bool AD<Base>::operator >= (const AD<Base> &right) const
{ 	bool result =  (value >= right.value); 

	if( AD<Base>::Tape()->State() == Empty )
		return result;

	AD<Base>::Tape()->RecordCompare(CompareGe, result, *this, right);

	return result;
}
# endif

// convert other cases into the case above
CppADFoldBinaryOperator(bool, >=)


// -------------------------------- == -------------------------
# ifdef NDEBUG

template <class Base>
inline bool AD<Base>::operator == (const AD<Base> &right) const
{	bool result =  (value == right.value); 
	return result;
}

# else 
template <class Base>
inline bool AD<Base>::operator == (const AD<Base> &right) const
{	bool result =  (value == right.value); 

	if( AD<Base>::Tape()->State() == Empty )
		return result;

	AD<Base>::Tape()->RecordCompare(CompareEq, result, *this, right);

	return result;
}
# endif

// convert other cases into the case above
CppADFoldBinaryOperator(bool, ==)

// -------------------------------- != -------------------------
# ifdef NDEBUG

template <class Base>
inline bool AD<Base>::operator != (const AD<Base> &right) const
{	bool result =  (value != right.value);
	return result;
}

# else
template <class Base>
inline bool AD<Base>::operator != (const AD<Base> &right) const
{	bool result =  (value != right.value);

	if( AD<Base>::Tape()->State() == Empty )
		return result;

	AD<Base>::Tape()->RecordCompare(CompareNe, result, *this, right);

	return result;
}
# endif

// convert other cases into the case above
CppADFoldBinaryOperator(bool, !=)

} // END CppAD namespace

# endif
