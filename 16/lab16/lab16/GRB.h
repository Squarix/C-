#pragma once

#include "Error.h"

typedef short GRBALPHABET;

namespace GRB
{
	#define NS(n) Rule::Chain::N(n)
	#define TS(n) Rule::Chain::T(n)

	struct Rule
	{
		GRBALPHABET nn; //нетерминал
		int iderror; //идентификатор диагностического сообщения
		short size; //количество цепочек
		struct Chain
		{
			short size; //длина цепочки
			GRBALPHABET* nt; //цепочка терминалов и нетерминалов 
			Chain() {size = 0; nt = 0;}
			Chain(short psize, GRBALPHABET s, ...); //количество символов и символы
			char* getCChain(char* b); //получить правую сторону правила
			static GRBALPHABET T(char t) {return GRBALPHABET(t);} //терминал
			static GRBALPHABET N(char n) {return -GRBALPHABET(n);} //нетерминал
			static bool isT(GRBALPHABET s) {return s > 0;}
			static bool isN(GRBALPHABET s) {return !isT(s);}
			static char alphabet_to_char(GRBALPHABET s) {return isT(s)?char(s):char(-s);}
		}* chains; //массив цепочек
		Rule() {nn = 0x00; size = 0;}
		Rule(GRBALPHABET pnn, int piderror, short psize, Chain c, ...);
		char* getCRule(char* b, short nchain); //получить правило для распечатки
		short getNextChain(GRBALPHABET t, Chain& pchain, short j); //получить следующую цепочку
	};

	struct Greibach
	{
		short size; //количество правил
		GRBALPHABET startN; //стартовый символ
		GRBALPHABET stbottomT; //дно стека
		Rule* rules; //множество правил
		Greibach() {size = 0; startN = 0; stbottomT = 0; rules = 0;};
		Greibach(GRBALPHABET pstartN, GRBALPHABET psbottomT, short psize, Rule r, ...);
		short getRule(GRBALPHABET pnn, Rule& prule); //получить правило
		Rule getRule(short n); //правило по номеру
		static Greibach getGreibach(); //получить грамматику
	};

}
