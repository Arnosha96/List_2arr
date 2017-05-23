#pragma once
#include <iostream>

using namespace std;

class List
{
private:
	double*Elems; //массив для хранения элементов списка
	int *Refs;// массив для хранения ссылок
	int capacity;// максимально доступное кол-во элементов в списке
	int After;// указатель предыдущего элемента
	int Before;// указатель следующего элемента
	int Count; // кол-во элементов в списке

	const int NullElem = 0;
	const int NullFreeSpace = 1;
public:
	List(int Count)
	{
		capacity = 100;

		if (Count <= capacity)
		{
			Elems = new double[Count + 1];
			Refs = new int[Count + 1];

			Refs[NullElem] = NullElem;
			for (int i(NullFreeSpace); i < Count + 1; i++)
				Refs[i] = i + 1;
			Refs[Count + 1] = 0; // закольцовываем "свободное место" 
			After = 0;
			Before = 0;
		}

	}

	~List()
	{
		Elems = NULL;
		delete[]Elems;
		Refs = NULL;
		delete[]Refs;
	}

	void Link(int virtualIndex, int realIndex)
	{
		Refs[virtualIndex] = realIndex;
	}

	int GetSpace()
	{
		int i = Refs[NullFreeSpace];
		Link(NullFreeSpace, Refs[i]);
		return i;
	}

	void PutSpace(int i)
	{
		Link(i, Refs[NullFreeSpace]);
		Link(NullFreeSpace, i);
	}

	void AddItem_end(double element)
	{

		int i = GetSpace();
		if (i>0) {
			Link(After, i);
			Link(i, Before);
			Before = i;
			Elems[i] = element;
			MoveNext();
			Count++;
		}
		else
			cout << "Таблица заполнена" << endl;
	}

	void AddItem_first(double element)
	{
		int i = GetSpace();
		if (i>0)
		{
			Link(i, Refs[NullElem]);
			Link(NullElem, i);
			Elems[i] = element;
			Before = Refs[i];
			After = 0;
			Count++;

		}
		else
			cout << "Таблица заполнена" << endl;
	}

	void AddItem_cut(int index, double element)
	{
		MoveFront();
		for (int j(0); j<(index - 1); j++) MoveNext();
		int i = GetSpace();
		if (i>0)
		{
			Elems[i] = element;
			Count++;
			Link(i, Refs[After]);
			Link(After, i);
		}
		else
			cout << "Таблица заполнена" << endl;

	}
	void RemoveItem(int index)
	{
		MoveFront();
		for (int j(0); j < index - 1; j++) MoveNext();
		int i;
		if (Count != 0)
		{
			i = Before;
			Before = Refs[i];
			Link(After, Before);
			PutSpace(i);
			Count--;
		}
		else cout << "Список пуст";
	}

	void MoveNext()
	{
		After = Before;
		Before = Refs[Before];
	}

	void MoveFront()
	{
		After = 0;
		Before = Refs[NullElem];
	}

	bool IsEndOfList()
	{
		bool IsEndOfList = false;
		if (Refs[After] == NullElem) IsEndOfList = true;
		return IsEndOfList;
	}

	double ReadItem(int index)
	{
		int readIt;
		if (!(index >= 0) && (index < Count))
		{
			if (IsEndOfList()) readIt = Elems[After];
			else readIt = Elems[Before];
		}
		else
		{
			int k;
			k = NullElem;
			for (int i(0); i <= index; i++) k = Refs[k];
			readIt = Elems[k];
		}
		return readIt;
	}

	void Print()
	{
		MoveFront();
		for (int i(0); i < Count; i++)
		{
			cout << ReadItem(i) << " ";
			MoveNext();
		}
		cout << endl;
	}
};
