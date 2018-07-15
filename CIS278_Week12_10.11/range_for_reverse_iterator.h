/*
 * Reverse iterators with C++11 range-based "for" loops.
 * 
 * Unfortunately, STL classes/containers allow iterating in a 
 * reverse order using reverse_iterators, but there is no support
 * for them in the range-based for loop.
 *
 * This is fixed by creating a proxy template which uses some 
 * C++11 features. This template proxy assumes the class provides 
 * reverse iterators via rbegin() and rend(), in the same manner 
 * that the range-based for loop assumes the object passed provides 
 * begin() and end().
 *
 * Use in the following manner:
 *   string s = "able was I saw elba";
 *   for(char c : reverse(s))
 *     cout << c;
 */
#pragma once
/*
template<class C>
class const_reverse_wrapper 
{
	const C& container;
public:
	const_reverse_wrapper(const C& cont) : container(cont) { }
	decltype(container.rbegin()) begin() const { return container.rbegin(); }
	decltype(container.rend()) end() const { return container.rend(); }
};

template<class C>
class reverse_wrapper 
{
	C& container;
public:
	reverse_wrapper(C& cont) : container(cont) { }
	decltype(container.rbegin()) begin() { return container.rbegin(); }
	decltype(container.rend()) end() { return container.rend(); }
};

template<class C>
const_reverse_wrapper<C> reverse(const C& cont) { return const_reverse_wrapper<C>(cont); }

template<class C>
reverse_wrapper<C> reverse(C& cont) { return reverse_wrapper<C>(cont); }
*/

// -------------------------------------------------------------------
// Reversed iterable
// Reverse iterators with (MSVC) C++17 range-based "for" loops.
using std::rbegin, std::rend;

template <typename T>
struct reversion_wrapper { T& iterable; };

template <typename T>
auto begin(reversion_wrapper<T> w) { return rbegin(w.iterable); }

template <typename T>
auto end(reversion_wrapper<T> w) { return rend(w.iterable); }

template <typename T>
reversion_wrapper<T> reverse(T&& iterable) { return { iterable }; }
