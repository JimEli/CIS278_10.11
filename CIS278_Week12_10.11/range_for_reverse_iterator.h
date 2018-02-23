#pragma once

/*
 * Using reverse iterators with C++11 range-based "for" loops.
 * 
 * Unfortunately, STL classes/containers allow iterating in a 
 * reverse order using reverse_iterators, but there is no support
 * for them in the range-based for loop.
 *
 * This is fixed by creating a proxy template which uses some 
 * Cc++11 features. This template proxy assumes the class provides 
 * reverse iterators via rbegin() and rend(), in the same manner 
 * that the range-based for loop assumes the object passed provides 
 * begin() and end().
 *
 * Use in the following manner:
 *   string s = "able was I saw elba";
 *   for(char c : reverse(s))
 *     cout << c;
 */

template<class Cont>
class const_reverse_wrapper {
	const Cont& container;

public:
	const_reverse_wrapper(const Cont& cont) : container(cont) { }
	decltype(container.rbegin()) begin() const { return container.rbegin(); }
	decltype(container.rend()) end() const { return container.rend(); }
};

template<class Cont>
class reverse_wrapper {
	Cont& container;

public:
	reverse_wrapper(Cont& cont) : container(cont) { }
	decltype(container.rbegin()) begin() { return container.rbegin(); }
	decltype(container.rend()) end() { return container.rend(); }
};

template<class Cont>
const_reverse_wrapper<Cont> reverse(const Cont& cont) {
	return const_reverse_wrapper<Cont>(cont);
}

template<class Cont>
reverse_wrapper<Cont> reverse(Cont& cont) {
	return reverse_wrapper<Cont>(cont);
}

