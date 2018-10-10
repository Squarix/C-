#include "stdafx.h"
#include "LT.h"
#include "Error.h"
namespace LT
{
	LexTable Create(int size)
	{
		LexTable lextable;
		if (size <= LT_MAXSIZE)
			lextable.maxsize = size;
		else
			throw ERROR_THROW(104);
		lextable.size = 0;
		lextable.table = new Entry[size];
		return lextable;
	}

	int Add(LexTable& lextable, Entry entry)
	{
		if (lextable.size >= lextable.maxsize)
		{
			throw ERROR_THROW(104);
		}
		lextable.table[lextable.size] = entry;
		lextable.size++;
		return lextable.size - 1;
	}

	Entry GetEntry(LexTable& lextable, int n)
	{
		return lextable.table[n];
	}

	void Delete(LexTable& lextable)
	{
		delete[] lextable.table;
	}
}