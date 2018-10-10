// LP_Lab13.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"

#include "Error.h"
#include "In.h"
#include "Log.h"
#include "Parm.h"
#include "FST.h"
#include "LT.h"
#include "IT.h"
#include "LexAnalis.h"

#include <iostream>

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_CTYPE, "rus");

	try {
		Parm::PARM parm = Parm::getparm(argc, argv);
		In::IN in = In::getin(parm.in);

		Log::LOG logger = Log::getlog(parm.log);

		Log::WriteLog(logger); // �������� ���������
		Log::WriteParm(logger, parm); // �������� ������� ��������� ���������
		Log::WriteIn(logger, in); // �������� ���������� �� �����

		In::parsOfToken(in);
		Lexer::LEX lex = Lexer::RunAnalysis(in, logger); // ��������� �� �������

		WriteLexems(logger, lex.Lextable); // �������� ������� ������
		WriteItentifiers(logger, lex.IDtable); // �������� ������� ���������������

		Log::Close(logger);
	}
	catch (Error::ERROR e){
		std::cout << "������ " << e.id << ": " << e.message << std::endl << std::endl;
		std::cout << "������ " << e.inext.line + 1 << " ������� " << e.inext.col << std::endl << std::endl;;
	}

	system("pause");
	return 0;
}

