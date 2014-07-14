/*
g++ -std=c++11 -g -o ack ack.cpp

The world's most time efficient Ackermann implementation.

The theory behind the Peter-Ackermann function (or more commonly, simply the
Ackermann or ack function) is that the algorithm can't be executed using loops,
but it does have a definite answer for every set of nonnegative arguments. The
complexity of the algorithm comes from the nature of recursion itself. Here's a
way to understand it.

The function A(m, n) takes nonnegative arguments. The pseudocode implementation
is this:

A(m, n):
	if m == 0 then return n + 1
	if n == 0 then return A(m - 1, 1)
	return A(m - 1, A(m, n - 1))

The first two lines are simply conditional terminators, a necessity for any
recursive function; the third line is the important part. There are two calls
here, but lets focus on the first. When m is reduced by 1, n's value increases
by an insane amount; this is what gives the Ackermann function it's magic. The
closest similarity to this would be a logarithmic curve, except that this
function's curve is much, much steeper. 

There are some simple rules for understanding the high-level workings. This
is how I understand it:

* Each iteration of A(m, n) will reduce it's internal value of m or n by 1.
* When m reaches 0, the whole algorithm terminates.
* When n reaches 0, m is reduced by 1.
* When m is reduced by 1, n is increased by an unknown amount.

*/

#include <iostream>
#include <map>

typedef signed long long int type_t;
typedef std::map<type_t, std::map<type_t, type_t>> matrix;

static type_t calls;

type_t ack(type_t m, type_t n) {
	static matrix table;

	++calls;

	//check to see if the answer is cached
	//use const iterators to skip multiple lookups
	auto const& iterM = table.find(m);
	if (iterM != table.end()) {
		auto const& iterN = iterM->second.find(n);
		if (iterN != iterM->second.end()) {
			return iterN->second;
		}
	}

	type_t ans;

	//run the conventional ackermann algorithm
	if (m == 0) {
		ans = n + 1;
	}
	else if (n == 0) {
		ans = ack(m-1, 1);
	}
	else {
		ans = ack(m-1, ack(m, n-1));
	}

	//cache new answers
	table[m][n] = ans;
	return ans;
}

int main(int argc, char** argv) {
	for (int i = 0; i < 6; ++i) {
		for (int j = 0; j < 6; ++j) {
			calls = 0;
			type_t ans = ack(i, j);
			std::cout << i << "," << j << ": " << ans << "; " << calls << std::endl;
		}
	}
	return 0;
}