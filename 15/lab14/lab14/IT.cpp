#include "stdafx.h"
#include "IT.h"
#include "Error.h"
namespace IT
{
	IdTable Create(int size)
	{
		if (size > TI_MAXSIZE)
		{
			throw ERROR_THROW(104); 
		}
		IdTable idtable;
		idtable.table = new Entry[size];
		idtable.size = 0;
		idtable.maxsize = size;
		return idtable;
	}

	int Add(IdTable& idtable, Entry entry)
	{
		if (idtable.size >= idtable.maxsize)
		{
			throw ERROR_THROW(104); 
		}
		idtable.table[idtable.size] = entry;
		idtable.size++;
		return idtable.size - 1;
	}

	Entry GetEntry(IdTable& idtable, int n)
	{
		return idtable.table[n];
	}

	int IsId(IdTable &idtable, char id[ID_MAXSIZE], char* visibility)
	{
		for (int i = 0; i < idtable.size; i++)
			if (strcmp(idtable.table[i].id, id) == 0 && strcmp(idtable.table[i].vis, visibility) == 0)
				return i;
		return TI_NULLIDX;
	}

	void Delete(IdTable& idtable)
	{
		delete[] idtable.table;
	}
}
