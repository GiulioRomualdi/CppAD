var list_across0 = [
'_contents.htm',
'_reference.htm',
'_index.htm',
'_search.htm',
'_external.htm'
];
var list_up0 = [
'cppad.htm',
'ad.htm',
'advalued.htm',
'atomic.htm',
'atomic_three.htm',
'atomic_three_hes_sparsity.htm',
'atomic_three_hes_sparsity.cpp.htm'
];
var list_down3 = [
'checkpoint.htm',
'atomic_three.htm',
'atomic_three_example.htm'
];
var list_down2 = [
'atomic_three_ctor.htm',
'atomic_three_afun.htm',
'atomic_three_type.htm',
'atomic_three_forward.htm',
'atomic_three_reverse.htm',
'atomic_three_jac_sparsity.htm',
'atomic_three_hes_sparsity.htm'
];
var list_down1 = [
'atomic_three_hes_sparsity.cpp.htm'
];
var list_current0 = [
'atomic_three_hes_sparsity.cpp.htm#Purpose',
'atomic_three_hes_sparsity.cpp.htm#Function',
'atomic_three_hes_sparsity.cpp.htm#Jacobian',
'atomic_three_hes_sparsity.cpp.htm#Hessians',
'atomic_three_hes_sparsity.cpp.htm#Start Class Definition',
'atomic_three_hes_sparsity.cpp.htm#Constructor',
'atomic_three_hes_sparsity.cpp.htm#type',
'atomic_three_hes_sparsity.cpp.htm#forward',
'atomic_three_hes_sparsity.cpp.htm#jac_sparsity',
'atomic_three_hes_sparsity.cpp.htm#hes_sparsity',
'atomic_three_hes_sparsity.cpp.htm#Use Atomic Function',
'atomic_three_hes_sparsity.cpp.htm#Test with u_1 Both a Variable and a Parameter'
];
function choose_across0(item)
{	var index          = item.selectedIndex;
	item.selectedIndex = 0;
	if(index > 0)
		document.location = list_across0[index-1];
}
function choose_up0(item)
{	var index          = item.selectedIndex;
	item.selectedIndex = 0;
	if(index > 0)
		document.location = list_up0[index-1];
}
function choose_down3(item)
{	var index          = item.selectedIndex;
	item.selectedIndex = 0;
	if(index > 0)
		document.location = list_down3[index-1];
}
function choose_down2(item)
{	var index          = item.selectedIndex;
	item.selectedIndex = 0;
	if(index > 0)
		document.location = list_down2[index-1];
}
function choose_down1(item)
{	var index          = item.selectedIndex;
	item.selectedIndex = 0;
	if(index > 0)
		document.location = list_down1[index-1];
}
function choose_down0(item)
{	var index          = item.selectedIndex;
	item.selectedIndex = 0;
	if(index > 0)
		document.location = list_down0[index-1];
}
function choose_current0(item)
{	var index          = item.selectedIndex;
	item.selectedIndex = 0;
	if(index > 0)
		document.location = list_current0[index-1];
}