#include <iostream >
#include "List.h"
#include <conio.h>
using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	List List1(3);

	List1.AddItem_end(25);
	List1.AddItem_end(40);
	List1.AddItem_first(50);

	List1.Print();

	List1.RemoveItem(3);

	List1.AddItem_cut(2, 100);
	List1.AddItem_end(12);
	List1.Print();

	List1.RemoveItem(1);
	List1.Print();
	List1.AddItem_end(8);
	List1.Print();

	_getch();
	return 0;
}