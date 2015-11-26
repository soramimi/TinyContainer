
#include <new>
#include <stdio.h>
#include <list>

#include "TinyContainer/TinyContainer.h"

void print(tiny::list<int> const *list)
{
	for (tiny::list<int>::const_iterator it = list->begin(); it != list->end(); it++) {
		printf("%d\n", *it);
	}
}

int main(int argc, char **argv)
{
	tiny::list<int> list;
	list.push_back(0);
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);
	list.push_back(4);
	list.push_back(5);

	list.clear();

	print(&list);

	size_t n = list.size();

	return 0;
}

