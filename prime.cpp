#include <iostream>
#include <list>
#include <vector>

typedef long long int Type;
typedef std::list<Type> List;

//find primes within a range
List calcSieve(List precedent, Type lowerBound, Type upperBound) {
	List primes;
	std::vector<bool> sieve;

	sieve.assign(upperBound - lowerBound, false);

	//calculate precedent influence
	for (Type iter = lowerBound; iter <= upperBound; iter++) {
		for (Type const& p : precedent) {
			if (iter % p == 0) {
				sieve[iter - lowerBound] = true;
				break;
			}
		}
	}

	//find unset memebers
	for (Type iter = lowerBound; iter <= upperBound; iter++) {
		if (sieve[iter - lowerBound] == false) {
			//set all multiples of the iterator to true
			for (Type i = iter; i <= upperBound; i += iter) {
				sieve[i - lowerBound] = true;
			}

			//save the iterator value
			primes.push_back(iter);
		}
	}

	//return the calculated list
	return primes;
}

List calcPrimes(Type upperBound) {
	List primes;
	constexpr Type interval = 256 * 256 * 256; //2 ^ 24

	//shortcut
	if (upperBound < interval) {
		return calcSieve(primes, 2, upperBound);
	}

	//run each interval
	for (Type i = 2; i < upperBound; i += interval) {
		primes.splice(primes.end(), calcSieve(primes, i, std::min(i + interval -1, upperBound) ));
	}

	return primes;
}

int main(int, char**) {
	List primes = calcPrimes(1000 * 1000 * 100);

//	int j = 1;
//	for (Type const& i : primes) {
//		std::cout << j << ":\t" << i << std::endl;
//		j++;
//	}

	std::cout << "Final size: " << primes.size() << std::endl;

	return 0;
}

/*
int main(int, char**) {
	std::list<int> primes;
	std::vector<bool> sieve;

	sieve.assign(60, false);

	//skip 1
	sieve[0] = true;

	//search for an unset member
	for (int iter = 1; iter <= sieve.size(); iter++) {
		if (sieve[iter - 1] == false) {
			//set all multiples of the iterator to true
			for (int i = iter; i <= sieve.size(); i += iter) {
				sieve[i - 1] = true;
			}

			//save the iterator value
			primes.push_back(iter);
		}
	}

	//print the result
	for (auto const& i : primes) {
		std::cout << i << std::endl;
	}

	return 0;
}
*/