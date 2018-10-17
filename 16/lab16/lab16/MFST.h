#pragma once
#include <stack>
#include "GRB.h"
#include "LexAnalis.h"
#define MFST_DIAGN_NUMBER 3
typedef std::stack<short > MFSTSTSTACK;

namespace MFST
{
	struct MfstState // структура для сохранения состояния автомата Mfst при встрече нетерминала
	{
		short lenta_position; // текущая просматриваемая лексема на ленте (это должна быть лексема нетерминала)
		short nrulechain; // номер правила, в которое мы развернули текущий нетерминал на ленте перед сохранением
		MFSTSTSTACK st; // полное сохранение стека автомата Mfst
		int nrule;
		MfstState() {};
		MfstState(short pposition, MFSTSTSTACK pst, short pnrulechain, int nrule);
	};

	struct Mfst
	{
		enum RC_STEP
		{
			NS_OK,
			NS_NORULE,
			NS_NORULECHAIN,
			NS_ERROR,
			TS_OK,
			TS_NOK,
			LENTA_END,
			SURPRISE
		} cur_status;

		struct MfstDiagnosis // структура для сохранения диагностического сообщения
		{
			short lenta_position;
			RC_STEP rc_step;
			short nrule;
			short nrule_chain;
			MfstDiagnosis() {};
			MfstDiagnosis(short plenta_position, RC_STEP prc_step, short pnrule, short pnrule_chain);
		} diagnosis[MFST_DIAGN_NUMBER];

		GRBALPHABET* lenta;
		short lenta_position; // позиция, просматриваемая автоматом
		short nrule; // последнее используемое правило для встреченного нетерминала
		short nrulechain; // последняя цепочка правила, которая была использована
		short lenta_size;
		GRB::Greibach greibach;
		Lexer::LEX lex; // таблица лексем, которая инициализирует lenta
		MFSTSTSTACK st; // текущий стек автомата, в котором хранится выражение на языке грамматики Greibach
		std::stack<MfstState> storestate; // стек для сохранения состояний автомата
		Mfst() {};
		Mfst(Lexer::LEX plex, GRB::Greibach pgreibach);
		char* getCSt(char* buf); //содержимое стека для печати
		char* getCLenta(char* buf, short pos, short n = 25);
		char* getDiagnosis(short n, char* buf);
		bool savestate();
		bool reststate();
		bool push_chain(GRB::Rule::Chain chain);
		RC_STEP step();
		bool start();
		bool savediagnosis(RC_STEP pprc_step);
		void printDiagnosis();
		void printRules();
	};
}