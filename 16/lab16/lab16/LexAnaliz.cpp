#include "stdafx.h"
#include "LexAnalis.h"
#include "Graphs.h"

namespace Lexer
{
	Graph graph[N_GRAPHS] =
	{
		{ 'l', Fst::FST(GRAPH_INT_LITERAL) },
		{ 'l', Fst::FST(GRAPH_STRING_LITERAL) },
		{ 'm', Fst::FST(GRAPH_MAIN) },
		{ 't', Fst::FST(GRAPH_INTEGER) },
		{ 't', Fst::FST(GRAPH_STRING) },
		{ 'f', Fst::FST(GRAPH_FUNCTION) },
		{ 'r', Fst::FST(GRAPH_RETURN) },
		{ 'd', Fst::FST(GRAPH_DECLARE) },
		{ 'p', Fst::FST(GRAPH_PRINT) },
		{ 'i', Fst::FST(GRAPH_ID) },
		{ '+', Fst::FST(GRAPH_ARYTHM_PLUS) },
		{ '-', Fst::FST(GRAPH_ARYTHM_MINUS) },
		{ '*', Fst::FST(GRAPH_ARYTHM_MULT) },
		{ '/', Fst::FST(GRAPH_ARYTHM_DIV) },
		{ ';', Fst::FST(GRAPH_SEMICOLON) },
		{ '=', Fst::FST(GRAPH_EQUALS) },
		{ ',', Fst::FST(GRAPH_COMMA) },
		{ '{', Fst::FST(GRAPH_LEFT_BRACE) },
		{ '}', Fst::FST(GRAPH_RIGHT_BRACE) },
		{ '(', Fst::FST(GRAPH_OPEN_PARENTHESIS) },
		{ ')', Fst::FST(GRAPH_CLOSE_PARENTHESIS) },
	};

	LEX RunAnalysis(In::IN& in, Log::LOG &log) {
		LEX lex_out;
		lex_out.Lextable = LT::Create(in.tokensSize);
		lex_out.IDtable = IT::Create(in.tokensSize);
		LT::Entry new_lexem;
		IT::Entry new_identifier;
		bool isFunction = false;
		bool isDeclare = false;
		bool openParen = false;
		bool isInteger = false;
		bool isString = false;
		char visibility[10][ID_MAXSIZE + 1]; // ��������� - ����� ������������ ������� ����������� ����� 10
		strcpy(visibility[0], "GLOBAL"); // ������ ������� ��������� - ����������
		int current_vis_level = 0;
		bool wait_for_semicolon = false;

		for (int i = 0; i < in.tokensSize; i++) {
			bool recognized = false;
			for (int j = 0; j < N_GRAPHS; j++) {
				Fst::FST fst_test(in.tokens[i].token, graph[j].graph);
				if (Fst::execute(fst_test)) { // ��������� in.tokens[i].token �� �������������� ������� graph[j]
					new_lexem.sn = in.tokens[i].line;
					recognized = true;
					if (graph[j].lexema == 'l') { // ��������� ������� �������
						new_lexem.lexema[0] = LEX_LITERAL;
						new_identifier.idtype = IT::IDTYPE::L; // ��� - �������
						if (j == 0) { // GRAPH_INT_LITERAL
							new_identifier.iddatatype = IT::IDDATATYPE::INT; // �������������
							new_identifier.value.vint = atoi(in.tokens[i].token); // ����������� �� ������ � �����
						}
						else { //GRAPH_STRING_LITERAL
							new_identifier.iddatatype = IT::IDDATATYPE::STR; // ������
							new_identifier.value.vstr.len = strlen(in.tokens[i].token) - 2;
							strncpy(new_identifier.value.vstr.str, in.tokens[i].token + 1, new_identifier.value.vstr.len);
							new_identifier.value.vstr.str[new_identifier.value.vstr.len] = 0;
						}
						strcpy(new_identifier.vis, visibility[current_vis_level]);
						new_lexem.idxTI = IT::Add(lex_out.IDtable, new_identifier); // ����� ���������� ������ �������������� ��������� ��� id � �������
						int lexid = LT::Add(lex_out.Lextable, new_lexem); // ��������� id ������� ����� �� ����������
						lex_out.IDtable.table[new_lexem.idxTI].idxfirstLE = lexid; // � ������� ��������������� ��������� id �������
						isInteger = false;
						isString = false;

						if (lex_out.Lextable.size - 4 >= 0) { //��������
							int s = lex_out.Lextable.size - 1;
							if (lex_out.Lextable.table[s - 1].lexema[0] == '=' && lex_out.Lextable.table[s - 2].lexema[0] == 'i' &&
								lex_out.Lextable.table[s - 3].lexema[0] == 't' && lex_out.Lextable.table[s - 4].lexema[0] == 'd') {
								if (new_identifier.iddatatype != lex_out.IDtable.table[lex_out.Lextable.table[s - 2].idxTI].iddatatype) {
									throw ERROR_THROW_IN(115, in.tokens[i].line, in.tokens[i].pos);
								}
								if (new_identifier.iddatatype == IT::IDDATATYPE::INT) {
									lex_out.IDtable.table[lex_out.Lextable.table[s - 2].idxTI].value.vint = new_identifier.value.vint;
								}
								else {
									strcpy(lex_out.IDtable.table[lex_out.Lextable.table[s - 2].idxTI].value.vstr.str, new_identifier.value.vstr.str);
									lex_out.IDtable.table[lex_out.Lextable.table[s - 2].idxTI].value.vstr.len = new_identifier.value.vstr.len;
								}
							}
						}

					}
					else if (graph[j].lexema == 't') { // ��������� ������� ���
						if (j == 3) { // GRAPH_INTEGER
							new_lexem.lexema[0] = LEX_INTEGER;
							isInteger = true;
							isString = false;
						}
						else { // GRAPH_STRING
							new_lexem.lexema[0] = LEX_STRING;
							isInteger = false;
							isString = true;
						}
						LT::Add(lex_out.Lextable, new_lexem);
					}
					else if (graph[j].lexema == 'i') { // ��������� ������� �������������

						{	// ��������� ��������� �������� ��������������
							new_identifier.value.vint = 0;
							strcpy(new_identifier.value.vstr.str, "");
							new_identifier.value.vstr.len = 0;
						}

						if (strlen(in.tokens[i].token) > 5) { // ������������� �� ����� ���� ������� 5 ��������, ������� �� 5
							strncpy(new_identifier.id, in.tokens[i].token, 5); // ��������� ��� ��������������
							new_identifier.id[5] = 0;
						}
						else {
							strcpy(new_identifier.id, in.tokens[i].token); // ��������� ��� ��������������
						}

						new_lexem.lexema[0] = LEX_ID; // ��� ������� - �������������

						if (isDeclare) {
							new_identifier.idtype = IT::IDTYPE::V;
							strcpy(new_identifier.vis, visibility[current_vis_level]); // ��� ���������� ������ ������������� ������� ������� ���������
						}
						else if (isFunction && !openParen) {
							new_identifier.idtype = IT::IDTYPE::F;
							strcpy(new_identifier.vis, visibility[current_vis_level]); // ��������� �������, �� ������������� �� ������� ������� ���������
							current_vis_level++; // ���������� �������
							strcpy(visibility[current_vis_level], new_identifier.id); // ������ ����� ������� ��������� ��� ���� �������
						}
						else if (isFunction && openParen) {
							new_identifier.idtype = IT::IDTYPE::P;
							strcpy(new_identifier.vis, visibility[current_vis_level]); // ��� ���������� ������ ������������� ������� ������� ���������
						}
						else {
							strcpy(new_identifier.vis, visibility[current_vis_level]); // ��� ���������� ������ ������������� ������� ������� ���������
						}

						if (isInteger) {
							new_identifier.iddatatype = IT::IDDATATYPE::INT;
						}
						else if (isString) {
							new_identifier.iddatatype = IT::IDDATATYPE::STR;
						}
						else {
							new_identifier.iddatatype = IT::IDDATATYPE::UNKNOWN;
						}
						// declare integer a;
						// declare integer function b(integer c);
						// a = b + c;
						if (new_identifier.iddatatype == IT::IDDATATYPE::UNKNOWN) {
							int idx = IT::IsId(lex_out.IDtable, new_identifier.id, new_identifier.vis);
							if (idx != TI_NULLIDX) {
								new_lexem.idxTI = idx; // ������������� ����� �������������� � ������� ��������������� ��� �������
								LT::Add(lex_out.Lextable, new_lexem); // ��������� ������� � ������� ������
							}
							else {
								// new_lexem.idxTI = IT::Add(lex_out.IDtable, new_identifier);
								// ����� ������ - �������������� ����������
								throw ERROR_THROW_IN(114, in.tokens[i].line, in.tokens[i].pos);
							}
						}
						else {
							/*if (IT::IsId(lex_out.IDtable, new_identifier.id, new_identifier.vis) != TI_NULLIDX) {
							throw ERROR_THROW_IN(114, in.tokens[i].line, in.tokens[i].pos); ������ ���������� ����������
							}*/
							new_lexem.idxTI = IT::Add(lex_out.IDtable, new_identifier);
							int lexid = LT::Add(lex_out.Lextable, new_lexem);
							lex_out.IDtable.table[new_lexem.idxTI].idxfirstLE = lexid; // � ������� ��������������� ��������� id �������
						}
						isInteger = false;
						isString = false;
					}
					else { // ��� ��������� ������� ����������� ���������
						new_lexem.lexema[0] = graph[j].lexema;
						new_lexem.idxTI = LT_TI_NULLIDX;
						LT::Add(lex_out.Lextable, new_lexem);

						if (wait_for_semicolon) {
							if (graph[j].lexema == ';') {
								current_vis_level--;
							}
							isFunction = false;
							wait_for_semicolon = false;
						}

						if (graph[j].lexema == 'f') {
							isFunction = true;
							isDeclare = false;
						}
						else if (graph[j].lexema == 'd') {
							isFunction = false;
							isDeclare = true;
						}
						else if (graph[j].lexema == '(') {
							openParen = true;
						}
						else if (graph[j].lexema == ')') {
							openParen = false;
							if (isFunction) {
								wait_for_semicolon = true;
							}
						}
						else if (graph[j].lexema == '}') {
							wait_for_semicolon = true;
						}
					}
					break;
				}
			}
			if (!recognized) {
				throw ERROR_THROW_IN(113, in.tokens[i].line, in.tokens[i].pos); // ����� ��� ������ ��� ����������� �������
			}
		}
		return lex_out;
	}
}