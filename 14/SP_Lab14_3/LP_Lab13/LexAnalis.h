#pragma once

#include "stdafx.h"
#include "IT.h"
#include "LT.h"
#include "In.h"
#include "Log.h"
#include "FST.h"

namespace Lexer
{
	struct LEX
	{
		LT::LexTable Lextable;
		IT::IdTable	IDtable;
	};

	struct Graph
	{
		char lexema;
		Fst::FST graph;
	};

	LEX RunAnalysis(In::IN& in, Log::LOG& log);
}
