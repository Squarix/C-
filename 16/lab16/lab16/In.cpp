#include "stdafx.h"
#include "In.h"
#include "Error.h"
#include "FST.h"
#include "Log.h"
#include <fstream>
#include <iostream>
#include <string.h>

using namespace std;

namespace In
{
	IN getin(wchar_t infile[])
	{
		IN in;
		int constCode[128] = IN_CODE_TABLE;
		for (int i = 0; i < 128; i++)
			in.code[i] = constCode[i];
		std::ifstream ifs;
		ifs.open(infile, std::ifstream::in);
		if (ifs.fail()) {
			throw ERROR_THROW(110);
		}

		in.text = new unsigned char[IN_MAX_LEN_TEXT];
		bool literalFlag = false;
		unsigned char c;  

		while ((c = ifs.get()) && (!ifs.eof()))
		{
			if (in.code[c] == IN::L)
			{
				if (literalFlag == true)
					literalFlag = false;
				else
					literalFlag = true;
				in.text[in.size++] = c;
			}
			switch (in.code[c])
			{
			case IN::STAB:
			{
				if (in.text[in.size - 1] == IN_CODE_ENDL)
				{
					in.ignor++;
				}
				in.text[in.size++] = c;
				in.lines++;
				break;
			}
			case IN::SPACE:
			{
				if (in.text[in.size - 1] == IN_CODE_SPACE)
				{
					in.ignor++;
				}
				in.text[in.size++] = c;
				break;
			}
			case IN::SEP:
			{
				//if (in.text[in.size - 1] == IN_CODE_SPACE) //удаляем пробелы рядом с сепараторами
				//	in.text[in.size - 1] = c;
				//else
					in.text[in.size++] = c;
				break;
			}
			case IN::F:
			{
				throw ERROR_THROW_IN(111, in.lines, in.size);
				break;
			}

			case IN::I:
			{
				in.ignor++;
				in.text[in.size++] = c;
				break;
			}
			case IN::T:
			{
				//if (in.code[in.text[in.size - 2]] == IN::SEP && in.code[in.text[in.size - 1]] == IN::SPACE) //удаляем пробелы рядом с сепараторами
				//	in.text[in.size - 1] = c;
				//else
					in.text[in.size++] = c;
				break;
			}
			}
		}

		for (int i = 0; i < in.size; i++)
		{
			if (in.text[i] == '\n')
				in.text[i] = '|';
		}

		in.text[in.size] = IN_CODE_NULL;

		return in;
	}

	void addToken(IN &in, char* &buf, int &posbuf, int line, int pos)
	{
		buf[posbuf++] = 0; // После занесённого слова выставляем конец строки
		strcpy_s(in.tokens[in.tokensSize].token, posbuf, buf);
		in.tokens[in.tokensSize].line = in.start_line;
		in.tokens[in.tokensSize].pos = in.start_pos;
		in.tokensSize++;
		buf[0] = 0;
		posbuf = 0;
	}

	void push_buf(IN &in, char* &buf, int &posbuf, int line, int pos, char c) {
		if (posbuf == 0) {
			in.start_line = line;
			in.start_pos = pos;
		}
		buf[posbuf++] = c;
	}

	IN parsOfToken(IN &in)
	{
		in.tokens = new StToken[IN_MAX_LEN_TEXT];
		char *buf = new char[IN_MAX_STRING_CODE];
		int posBuf = 0;
		bool textLiteralFlag = false;
		int line = 0;
		int pos = 0;

		in.tokensSize = 0;

		for (int i = NULL; in.text[i] != 0; i++)
		{
			pos++;
			switch (in.code[in.text[i]])
			{
				case IN::LNBREAK:
					line++;
					pos = 0;
					break;
				case IN::SPACE:
				{
					if (buf[0] != 0)
					{
						if (textLiteralFlag == true)
						{
							push_buf(in, buf, posBuf, line, pos, in.text[i]);
							break;
						}
						if (posBuf > 0)
						{
							addToken(in, buf, posBuf, line, pos);
						}
					}
					break;
				}
				case IN::SEP:
				{
					if (textLiteralFlag == true) {
						push_buf(in, buf, posBuf, line, pos, in.text[i]);
						break;
					}
					if (buf[0] != 0)
					{
						addToken(in, buf, posBuf, line, pos);
					}
					push_buf(in, buf, posBuf, line, pos, in.text[i]);
					addToken(in, buf, posBuf, line, pos);
					break;
				}
				case IN::L:
				{
					if (textLiteralFlag == true)
					{
						textLiteralFlag = false;
					}
					else
					{
						textLiteralFlag = true;
					}
					push_buf(in, buf, posBuf, line, pos, in.text[i]);
					break;
				}
				case IN::I:
					break;
				default:
				{
					push_buf(in, buf, posBuf, line, pos, in.text[i]);
					break;
				}
			}
		}

		return in;
	}
}
