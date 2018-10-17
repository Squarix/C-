#pragma once
#include "stdafx.h"

#define LEXEMA_FIXSIZE		1
#define LT_MAXSIZE			4096
#define LT_TI_NULLIDX		0xffffffff
#define LEX_INTEGER			't'
#define LEX_STRING			't'
#define LEX_ID				'i'
#define LEX_LITERAL			'l'
#define LEX_FUNCTION		'f'
#define LEX_DECLARE			'd'
#define LEX_RETURN			'r'
#define LEX_PRINT			'p'
#define LEX_MAIN			'm'
#define LEX_SEMICOLON		';'
#define LEX_COMMA			','
#define LEX_LEFTBRACE		'{'
#define LEX_BRACELET		'}'
#define LEX_LEFTTHESIS		'('
#define LEX_RIGHTHESIS		')'
#define LEX_PLUS			'+'
#define LEX_MINUS			'-'
#define LEX_STAR			'*'
#define LEX_DIRSLASH		'/'
#define LEX_EQUALITY		'='

#define LEX_NULL			'%'
namespace LT
{
	struct Entry
	{
		char lexema[LEXEMA_FIXSIZE];
		int sn;
		int idxTI;
		Entry() {};
		Entry(char plexema, int psn, int pidxTI) {this->lexema[0] = plexema; this->sn = psn; this->idxTI = pidxTI;};
	};
	struct LexTable
	{
		int maxsize;
		int size;
		Entry* table;
	};
	LexTable Create(int size);
	int		 Add(LexTable& lextable, Entry entry);
	Entry	 GetEntry(LexTable& lextable, int n);
	void     Delete(LexTable& lextable);
};