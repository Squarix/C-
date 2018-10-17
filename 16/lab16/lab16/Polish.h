#include "stdafx.h"
#include "LT.h"
#include "IT.h"

namespace Polish
{
	const int STACK_MAXSIZE = 10000;

	struct Lex_Range // первая и последняя лексемы для рабора в полькую нотацию
	{
		int start_lex;
		int end_lex;
	};

	struct Pol_Stack // стек эмулирующий разбор в польскую нотацию
	{
		int stack[STACK_MAXSIZE]; // индексы лексем
		int top;
	};

	const char symbols[] = { '(', ')', ',', '+', '-', '*', '/' }; // символы лексем в разборе
	const int priority[] = { 0, 0, 1, 2, 2, 3, 3 }; // приоритеты
	const int P_LEN = 7; // длина массивов symbols и priority
	const int P_ID = 100; // значение по умолчанию для get_priority()

	bool PolishNotation(int lextable_pos, LT::LexTable& lextable, IT::IdTable& idtable);
	int get_priority(char c); // получаем величину приоритета по символу лексемы
	Lex_Range find_lex_range(int lextable_pos, LT::LexTable& lextable); // ищем индексы первой и последней лексемы в таблице лексем для разбора в польскую нотацию
	bool is_lex_allowed(char l); // проверка, разрешена ли данная лексема в разборе польской нотации
}