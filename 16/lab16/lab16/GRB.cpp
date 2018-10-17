#include "stdafx.h"
#include "GRB.h"
#include <stdio.h>
#define GRB_ERROR_SERIES 600
namespace GRB
{
	Greibach greibach( NS('S'), TS('$'), 6,
		Rule(NS('S'), GRB_ERROR_SERIES + 0, 2, // программные блоки: main{...}; | type function identifier(params list) {...};
			Rule::Chain(8, TS('m'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), TS(';')), // m{NrE;};
			//Rule::Chain(9, TS('m'), TS('{'), NS('N'), TS('r'), NS('E'),	TS(';'), TS('}'), TS(';'), NS('S')), // m{NrE;};S

			//Rule::Chain(13, TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), TS(';')), // tfi(F){NrE;};
			Rule::Chain(14, TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), TS(';'), NS('S')) // tfi(F){NrE;};S
		),
		Rule(NS('N'), GRB_ERROR_SERIES + 1, 14, // операторы: define type identifier; | identifier = expression; | ...
			Rule::Chain(4, TS('d'), TS('t'), TS('i'), TS(';')), //dti;
			Rule::Chain(5, TS('d'), TS('t'), TS('i'), TS(';'), NS('N')), //dti;N

			Rule::Chain(3, TS('r'), NS('E'), TS(';')), //rE;
			Rule::Chain(4, TS('r'), NS('E'), TS(';'), NS('N')), //rE;N

			Rule::Chain(4, TS('i'), TS('='), NS('E'), TS(';')), //i=E;
			Rule::Chain(5, TS('i'), TS('='), NS('E'), TS(';'), NS('N')), //i=E;N

			Rule::Chain(8, TS('d'), TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS(';')), //dtfi(F);
			Rule::Chain(9, TS('d'), TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS(';'), NS('N')), //dtfi(F);N

			Rule::Chain(3, TS('p'), TS('i'), TS(';')), //pi;
			Rule::Chain(4, TS('p'), TS('i'), TS(';'), NS('N')), //pi;N
			Rule::Chain(3, TS('p'), TS('l'), TS(';')), //pl;
			Rule::Chain(4, TS('p'), TS('l'), TS(';'), NS('N')), //pl;N

			Rule::Chain(6, TS('d'), TS('t'), TS('i'), TS('='), NS('E'), TS(';')), //dti=E;
			Rule::Chain(7, TS('d'), TS('t'), TS('i'), TS('='), NS('E'), TS(';'), NS('N')) //dti=E;N
		),
		Rule(NS('E'), GRB_ERROR_SERIES + 2, 8, // выражени€: (identifier + literal)*function(params)
			Rule::Chain(1, TS('i')), //i
			Rule::Chain(2, TS('i'), NS('M')), //iM

			Rule::Chain(1, TS('l')), //l
			Rule::Chain(2, TS('l'), NS('M')), //lM

			Rule::Chain(3, TS('('), NS('E'), TS(')')), //(E)
			Rule::Chain(4, TS('('), NS('E'), TS(')'), NS('M')), //(E)M

			Rule::Chain(4, TS('i'), TS('('), NS('W'), TS(')')), //i(W)
			Rule::Chain(5, TS('i'), TS('('), NS('W'), TS(')'), NS('M')) //i(W)M
		),
		Rule(NS('F'), GRB_ERROR_SERIES + 3, 2, // список параметров функции в ее определении
			Rule::Chain(2, TS('t'), TS('i')), //ti
			Rule::Chain(4, TS('t'), TS('i'), TS(','), NS('F')) //ti,F
		),
		Rule(NS('W'), GRB_ERROR_SERIES + 4, 4, // список параметров функции при вызове
			Rule::Chain(1, TS('i')), //i
			Rule::Chain(3, TS('i'), TS(','), NS('W')), //i,W

			Rule::Chain(1, TS('l')), //l
			Rule::Chain(3, TS('l'), TS(','), NS('W')) //l,W
		),
		Rule(NS('M'), GRB_ERROR_SERIES + 5, 4, // вспомогательный нетерминал дл€ 'E', позвол€ет рекурсивно определ€ть составные выражени€
			Rule::Chain(2, TS('+'), NS('E')), // +E
			Rule::Chain(2, TS('-'), NS('E')), // -E
			Rule::Chain(2, TS('*'), NS('E')), // *E
			Rule::Chain(2, TS('/'), NS('E')) // /E
		)
	);

	// конструктор дл€ Chain
	Rule::Chain::Chain(short psize, GRBALPHABET s, ...)
	{
		this->size = psize; // количество терминалов и нетерминалов в правой части правила грамматики
		this->nt = new GRBALPHABET[this->size];
		this->nt[0] = s;
		for (int i = 1; i < this->size; i++)
			this->nt[i] = *(&s + i*sizeof(GRBALPHABET)) ; // каждый следующий параметр функции находитс€ по смещению +2 байти в стеке
	}

	char* Rule::Chain::getCChain(char* b)
	{
		for (int i = 0; i < this->size; i++)
			b[i] = Rule::Chain::alphabet_to_char(this->nt[i]);
		b[this->size] = 0;
		return b;
	}

	Rule::Rule(GRBALPHABET pnn, int piderror, short psize, Chain c, ...) // компил€тор сам разбираетс€ с нужным смещением дл€ следующего параметра
	{
		this->nn = pnn;
		this->iderror = piderror ;
		this->size = psize;
		this->chains = new Rule::Chain[this->size];
		this->chains[0] = c;
		for (int i = 1; i < this->size; i++)
			this->chains[i] = *(&c + i); 
	}

	char* Rule::getCRule(char* b, short nchain)
	{
		char buf[256];
		sprintf(b, "%c->%s", Rule::Chain::alphabet_to_char(this->nn), this->chains[nchain].getCChain(buf));
		return b;
	}

	short Rule::getNextChain(GRBALPHABET t, Rule::Chain& pchain, short j) 
	{
		while (j < this->size && this->chains[j].nt[0] != t)
			j++;
		if (j == this->size) {
			return this->size;
		}
		pchain = this->chains[j];
		return j;
	}

	Greibach::Greibach(GRBALPHABET pstartN, GRBALPHABET psbottomT, short psize, Rule r, ...)
	{
		this->startN = pstartN;
		this->stbottomT = psbottomT;
		this->size = psize;
		this->rules = new Rule[this->size];
		this->rules[0] = r;
		for (int i = 1; i < this->size; i++)
			this->rules[i] = *(&r + i);
	}

	short Greibach::getRule(GRBALPHABET pnn, Rule& prule)
	{
		for (int i = 0; i < this->size; i++)
			if (this->rules[i].nn == pnn) {
				prule = this->rules[i];
				return i;
			}
		return -1;
	}

	Rule Greibach::getRule(short n)
	{
		return this->rules[n];
	}

	Greibach Greibach::getGreibach()
	{
		return greibach;
	}
}