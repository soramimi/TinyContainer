
#include <new>
#include <stdio.h>
#include <vector>

#include "TinyContainer/TinyContainer.h"

void print(tiny::vector<int> const *vec)
{
	for (tiny::vector<int>::const_iterator it = vec->begin(); it != vec->end(); it++) {
		printf("%d\n", *it);
	}
}

int main(int argc, char **argv)
{
	tiny::vector<int> vec;
	vec.push_back(0);
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);
	vec.push_back(5);

	print(&vec);

	return 0;
}

