#include "Set.h"

void main()
{
	Set<int> test1;
	Set<int> test2;
	Set<int> test3;
	int N = 55;
	for (int s = 1; s <= N; s++)
	{
		test1.add(s);
		test2.add(2 * s);
	}
	cout << "set 1: " << endl;
	test1.show_all_element();
	cout << "set 2: " << endl;
	test2.show_all_element();

	cout << "***************************************" << endl;
	test3 = test1 + test2;
	cout << "set 3: " << endl;
	test3.show_all_element();
	cout << "***************************************" << endl;

	cout << "set 1: " << endl;
	test1.show_all_element();
	cout << "set 2: " << endl;
	test2.show_all_element();

	cout << (test1!=test2) << endl;
	
	system("pause");
}