#include "stdafx.h"
#include "MFST.h"
#include "GRB.h"
#include "Error.h"
#include "Trace.h"

namespace MFST
{
	MfstState::MfstState(short pposition, MFSTSTSTACK pst, short pnrulechain, int nrule)
	{
		this->lenta_position = pposition;
		this->nrulechain = pnrulechain;
		this->st = pst;
		this->nrule = nrule;
	}

	Mfst::MfstDiagnosis::MfstDiagnosis(short plenta_position, RC_STEP prc_step, short pnrule, short pnrule_chain)
	{
		this->lenta_position = plenta_position;
		this->rc_step = prc_step;
		this->nrule = pnrule;
		this->nrule_chain = pnrule_chain;
	}

	Mfst::Mfst(Lexer::LEX plex, GRB::Greibach pgreibach)
	{
		this->lex = plex;
		this->greibach = pgreibach;
		this->lenta = new GRBALPHABET[this->lex.Lextable.size];
		for (int i = 0; i < this->lex.Lextable.size; i++)
			this->lenta[i] = GRB::TS(this->lex.Lextable.table[i].lexema[0]); // на ленте только лексемы, т.е. терминалы
		// основное отличие ленты от рабочего стека Mfst в том, что на ленте хранятся только лексемы (они у нас терминалы), 
		// а в стеке хранится выражения языка Greibach, которое использует и терминалы и нетерминалы
		this->lenta_size = lex.Lextable.size;
	}
	char* Mfst::getCSt(char* buf)
	{
		MFSTSTSTACK tempst; // создаем временную переменную стека, т.к. мы не можем обратиться ко всем элементам стек сразу
		int i = 0;
		while (!st.empty()) { // из основного стека st заносим во временный стек tempst все элементы по очередиы
			buf[i++] = GRB::Rule::Chain::alphabet_to_char(st.top()); // преобразуем из short в char и записываем элемент из tempst в st
			tempst.push(st.top());
			st.pop();
		} 
		// теперь st пуст
		while (!tempst.empty())
		{
			st.push(tempst.top());
			tempst.pop();
		}
		buf[i] = 0;
		return buf;
	}
	char* Mfst::getCLenta(char* buf, short pos, short n) // печатает n символов ленты, начиная с позиции pos (в автомате это соответствует позиции lenta_position)
	{
		for (int i = 0; i < n; i++)
		{
			if (pos + i < this->lenta_size) {
				buf[i] = GRB::Rule::Chain::alphabet_to_char(this->lenta[pos + i]);
			} else {
				buf[i] = 0; // если лента закончилась, то в конец строки пишем нулевой символ и возвращаем
				return buf;
			}
		}
		buf[n] = 0;
		return buf;
	}

	char* Mfst::getDiagnosis(short n, char* buf) //получить текст для печати о диагност. сообщении
	{
		strcpy(buf, "");
		if (n < MFST_DIAGN_NUMBER) {
			int pos = diagnosis[n].lenta_position;
			if (pos >= 0) {
				int err = greibach.getRule(diagnosis[n].nrule).iderror;
				Error::ERROR er = Error::geterror(err);
				sprintf(buf, "%d: строка %d,  %s", er.id, lex.Lextable.table[pos].sn, er.message);
			}
		}
		return buf;
	}

	bool Mfst::savestate()
	{
		// создаем копию текущего состояния автомата и записываем на верхушку стека storestate
		// эта функция вызывается в том случае, если на верхушке стека st автомата Msft находится нетерминал
		this->storestate.push(MfstState(this->lenta_position, this->st, this->nrulechain, this->nrule));
		MFST_TRACE6("SAVESTATE:", this->storestate.size())
		return true;
	}
	bool Mfst::reststate()
	{
		if (!this->storestate.empty()) {
			// восстанавливаем 3 сохраненные выше переменные из верхушки стека состояний в Msft
			this->lenta_position = this->storestate.top().lenta_position;
			this->nrulechain = this->storestate.top().nrulechain;
			this->st = this->storestate.top().st;
			// выталкиваем из стека предыдущее сохраненное состояние
			this->storestate.pop();
			MFST_TRACE5("RESTATE")
			MFST_TRACE2
			return true; // восстановление прошло успешно
		} else 
			return false; // ничего восстановить не удалось
	}
	bool Mfst::push_chain(GRB::Rule::Chain chain)
	{
		// записываем цепочку правила в рабочий стек Msft в обратном порядке
		for (int i = chain.size - 1; i >= 0; i--) {
			this->st.push(chain.nt[i]);
		}
		return true;
	}
	Mfst::RC_STEP Mfst::step() //  основная работа автомата Mfst
	{
		if (this->st.empty() && this->lenta_position == this->lenta_size) { // кончилась лента
			MFST_TRACE4("LENTA_END")
			return LENTA_END;
		}
		if ((this->st.empty() && this->lenta_position < this->lenta_size) || ((!this->st.empty()) && this->lenta_position >= this->lenta_size)) {
			// либо лента кончилась, и стек не пуст, либо наоборот
			return SURPRISE;
		}
		if (GRB::Rule::Chain::isN(this->st.top())) { // на вершине стека нетерминальный символ, нужно найти соответствущее правило
			GRB::Rule rule;
			GRB::Rule::Chain chain;
			int found = this->greibach.getRule(this->st.top(), rule);
			if (found == -1) { // правило не найдено
				return NS_NORULE;
			}
			this->nrule = found;
			if (cur_status == TS_NOK) { // после reststate() переходим к следующей цепочке
				this->nrulechain = rule.getNextChain(this->lenta[this->lenta_position], chain, this->nrulechain + 1); // get next chain
				if (this->nrulechain >= this->greibach.getRule(this->nrule).size) { // если цепочек больше не осталось, то делаем откат без сохранения
					MFST_TRACE4("NS_NORULECHAIN/NS_NORULE")
					this->savediagnosis(NS_NORULECHAIN);
					if (!this->reststate())	{
						return NS_NORULECHAIN;
					}
					return TS_NOK;
				}
			} else { // иначе это новый нетерминальный символ и разбор начинаем с первого правила
				this->nrulechain = rule.getNextChain(this->lenta[this->lenta_position], chain, 0); // get next chain
				if (this->nrulechain == this->greibach.getRule(this->nrule).size) { //если не нашли ни одно правило начинающееся с терминала this->lenta[this->lenta_position]
					this->nrulechain = 0;
					return TS_NOK;
				}
			}
			MFST_TRACE1
			this->savestate();
			this->st.pop();
			this->push_chain(rule.chains[this->nrulechain]);
			MFST_TRACE2
			return NS_OK;
		} else {
			if (this->st.top() == this->lenta[this->lenta_position]) { // совпадает символ на верхушке стека и в текущей позиции ленты
				this->lenta_position++;
				this->st.pop();
				MFST_TRACE3
				return TS_OK;
			} else {
				MFST_TRACE4("TS_NOK/NS_NORULECHAIN")
				if (!this->reststate()) {
					return NS_NORULECHAIN;
				}
				return TS_NOK;
			}
		}
	}

	void Mfst::printDiagnosis()
	{
		char buf[1024];
		for (int i = 0; i < MFST_DIAGN_NUMBER; i++)
			if (this->diagnosis[i].lenta_position >= 0)
				cout << getDiagnosis(i, buf) << endl;
	}

	bool Mfst::start()
	{
		this->st.push(this->greibach.stbottomT);
		this->st.push(this->greibach.startN);

		this->lenta_position = 0;
		this->lenta_size = this->lex.Lextable.size;
		this->nrule = 0;
		this->nrulechain = 0;

		for (int i = 0; i < MFST_DIAGN_NUMBER; i++)
			diagnosis[i].lenta_position = -1;

		cur_status = Mfst::RC_STEP::NS_OK;
		while (cur_status != Mfst::RC_STEP::LENTA_END)
		{
			cur_status = this->step();
			switch (cur_status)
			{
			case Mfst::RC_STEP::NS_NORULE: 
				MFST_TRACE4("------>NS_NORULE")
				this->printDiagnosis();
				return false;
				break;
			case Mfst::RC_STEP::NS_NORULECHAIN:
				MFST_TRACE4("------>NS_NORULECHAIN")
				this->printDiagnosis();
				return false;
				break;
			case Mfst::RC_STEP::NS_ERROR:
				MFST_TRACE4("------>NS_ERROR")
				this->printDiagnosis();
				return false;
				break;
			case Mfst::RC_STEP::SURPRISE:
				MFST_TRACE4("------>NS_SURPRISE")
				this->printDiagnosis();
				return false;
				break;
			}
		}
		MFST_TRACE4("------>LENTA_END")
		cout << "-------------------------------------------------------------------------------" << endl;
		cout << setw(4) << left << 0 << ": всего строк " << this->lenta_size << ", синтаксический анализ выполнен без ошибок" << endl;
		return true;
	}

	bool Mfst::savediagnosis(RC_STEP pprc_step)
	{
		int i = 0;
		while (i < MFST_DIAGN_NUMBER && this->lenta_position <= diagnosis[i].lenta_position)
			i++;
		if (i < MFST_DIAGN_NUMBER) {
			diagnosis[i] = Mfst::MfstDiagnosis(this->lenta_position, pprc_step, this->nrule, this->nrulechain);
			for (int j = i + 1; j < MFST_DIAGN_NUMBER; j++)
				diagnosis[j].lenta_position = -1;
			return true;
		}
		else
			return false;
		return true;
	}

	void Mfst::printRules()
	{
		MfstState state;
		GRB::Rule rule;
		std::stack<MfstState> tempstore;
		char buf[1024];
		while (!storestate.empty()) {
			tempstore.push(storestate.top());
			storestate.pop();
		}
		while (!tempstore.empty()) {
			state = tempstore.top();
			rule = this->greibach.getRule(state.nrule);
			MFST_TRACE7
			storestate.push(tempstore.top());
			tempstore.pop();
		}
	}
}