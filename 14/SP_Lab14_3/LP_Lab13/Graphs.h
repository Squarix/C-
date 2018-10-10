#pragma once

#define N_GRAPHS 18
#define GRAPH_SEPARATORS 2,\
	Fst::NODE(11, Fst::RELATION(';',1), Fst::RELATION('=',1),\
				  Fst::RELATION(',',1), Fst::RELATION('{',1),\
				  Fst::RELATION('}',1), Fst::RELATION('(',1),\
				  Fst::RELATION(')',1), Fst::RELATION('*',1),\
				  Fst::RELATION('+',1), Fst::RELATION('-',1),\
				  Fst::RELATION('/',1)),\
	Fst::NODE()

#define GRAPH_ARYTHM 2,\
	Fst::NODE(11, Fst::RELATION('*',1), Fst::RELATION('+',1),\
			      Fst::RELATION('-',1), Fst::RELATION('/',1)),\
	Fst::NODE()

#define GRAPH_SEMICOLON 2,\
	Fst::NODE(1,Fst::RELATION(';',1)),\
	Fst::NODE()
#define GRAPH_EQUALS 2,\
	Fst::NODE(1,Fst::RELATION('=',1)),\
	Fst::NODE()
#define GRAPH_COMMA 2,\
	Fst::NODE(1,Fst::RELATION(',',1)),\
	Fst::NODE()
#define GRAPH_LEFT_BRACE 2,\
	Fst::NODE(1,Fst::RELATION('{',1)),\
	Fst::NODE()
#define GRAPH_RIGHT_BRACE 2,\
	Fst::NODE(1,Fst::RELATION('}',1)),\
	Fst::NODE()
#define GRAPH_OPEN_PARENTHESIS 2,\
	Fst::NODE(1,Fst::RELATION('(',1)),\
	Fst::NODE()
#define GRAPH_CLOSE_PARENTHESIS 2,\
	Fst::NODE(1,Fst::RELATION(')',1)),\
	Fst::NODE()

#define GRAPH_SUBSTR 7, \
	Fst::NODE(1,Fst::RELATION('s',1)),\
	Fst::NODE(1,Fst::RELATION('u',2)),\
	Fst::NODE(1,Fst::RELATION('b',3)),\
	Fst::NODE(1,Fst::RELATION('s',4)),\
	Fst::NODE(1,Fst::RELATION('t',5)),\
    Fst::NODE(1,Fst::RELATION('r',6)),\
	Fst::NODE()

#define GRAPH_STRLEN 7,\
	Fst::NODE(1,Fst::RELATION('s',1)),\
	Fst::NODE(1,Fst::RELATION('t',2)),\
	Fst::NODE(1,Fst::RELATION('r',3)),\
	Fst::NODE(1,Fst::RELATION('l',4)),\
	Fst::NODE(1,Fst::RELATION('e',5)),\
	Fst::NODE(1,Fst::RELATION('n',6)),\
	Fst::NODE()

#define GRAPH_FORWARD_SLASH 2,\
	Fst::NODE(1,Fst::RELATION('/',1)),\
	Fst::NODE()

#define GRAPH_INT_LITERAL 2, \
	Fst::NODE(10,Fst::RELATION('0',1),Fst::RELATION('1',1),\
				Fst::RELATION('3',1),Fst::RELATION('2',1),\
				Fst::RELATION('5',1),Fst::RELATION('4',1),\
				Fst::RELATION('7',1),Fst::RELATION('6',1),\
				Fst::RELATION('8',1),Fst::RELATION('9',1)),\
	Fst::NODE(10,Fst::RELATION('0',1),Fst::RELATION('1',1),\
				Fst::RELATION('3',1),Fst::RELATION('2',1),\
				Fst::RELATION('5',1),Fst::RELATION('4',1),\
				Fst::RELATION('7',1),Fst::RELATION('6',1),\
				Fst::RELATION('8',1),Fst::RELATION('9',1))

#define GRAPH_STRING_LITERAL 3, \
	Fst::NODE(1, Fst::RELATION('\'',1)),\
	Fst::NODE(64,Fst::RELATION('a',1),Fst::RELATION('b',1), \
				 Fst::RELATION('c', 1), Fst::RELATION('d', 1), \
				 Fst::RELATION('e', 1), Fst::RELATION('f', 1), \
				 Fst::RELATION('g', 1), Fst::RELATION('h', 1), \
				 Fst::RELATION('i', 1), Fst::RELATION('j', 1), \
				 Fst::RELATION('k', 1), Fst::RELATION('l', 1), \
				 Fst::RELATION('m', 1), Fst::RELATION('n', 1), \
				 Fst::RELATION('o', 1), Fst::RELATION('p', 1), \
				 Fst::RELATION('q', 1), Fst::RELATION('r', 1), \
				 Fst::RELATION('s', 1), Fst::RELATION('t', 1), \
				 Fst::RELATION('u', 1), Fst::RELATION('v', 1), \
				 Fst::RELATION('w', 1), Fst::RELATION('x', 1), \
				 Fst::RELATION('y', 1), Fst::RELATION('z', 1), \
				 Fst::RELATION('0', 1), Fst::RELATION('1',1),	\
				 Fst::RELATION('3', 1), Fst::RELATION('2',1),	\
				 Fst::RELATION('5', 1), Fst::RELATION('4',1),	\
				 Fst::RELATION('7', 1), Fst::RELATION('6',1),	\
				 Fst::RELATION('9', 1), Fst::RELATION('8',1), \
				 Fst::RELATION('A', 1),	 Fst::RELATION('B', 1), \
				 Fst::RELATION('C', 1),  Fst::RELATION('D', 1), \
				 Fst::RELATION('E', 1),  Fst::RELATION('F', 1), \
				 Fst::RELATION('G', 1),  Fst::RELATION('H', 1), \
				 Fst::RELATION('I', 1),  Fst::RELATION('J', 1), \
				 Fst::RELATION('K', 1),  Fst::RELATION('L', 1), \
				 Fst::RELATION('M', 1),  Fst::RELATION('N', 1), \
				 Fst::RELATION('O', 1),  Fst::RELATION('P', 1), \
				 Fst::RELATION('Q', 1),  Fst::RELATION('R', 1), \
				 Fst::RELATION('S', 1),  Fst::RELATION('T', 1), \
				 Fst::RELATION('U', 1),  Fst::RELATION('V', 1), \
				 Fst::RELATION('W', 1),  Fst::RELATION('X', 1), \
				 Fst::RELATION('Y', 1),  Fst::RELATION('Z', 1), \
				 Fst::RELATION(' ', 1), Fst::RELATION('\'',2)),\
	Fst::NODE()

#define GRAPH_MAIN 5, \
	Fst::NODE(1,Fst::RELATION('m',1)),\
	Fst::NODE(1,Fst::RELATION('a',2)),\
	Fst::NODE(1,Fst::RELATION('i',3)),\
	Fst::NODE(1,Fst::RELATION('n',4)),\
	Fst::NODE()


#define GRAPH_INTEGER 8, \
	Fst::NODE(1,Fst::RELATION('i',1)),\
	Fst::NODE(1,Fst::RELATION('n',2)),\
	Fst::NODE(1,Fst::RELATION('t',3)),\
	Fst::NODE(1,Fst::RELATION('e',4)),\
	Fst::NODE(1,Fst::RELATION('g',5)),\
    Fst::NODE(1,Fst::RELATION('e',6)),\
    Fst::NODE(1,Fst::RELATION('r',7)),\
	Fst::NODE()

#define GRAPH_STRING 7, \
	Fst::NODE(1,Fst::RELATION('s',1)),\
	Fst::NODE(1,Fst::RELATION('t',2)),\
	Fst::NODE(1,Fst::RELATION('r',3)),\
	Fst::NODE(1,Fst::RELATION('i',4)),\
	Fst::NODE(1,Fst::RELATION('n',5)),\
	Fst::NODE(1,Fst::RELATION('g',6)),\
	Fst::NODE()

#define GRAPH_FUNCTION 9, \
	Fst::NODE(1, Fst::RELATION('f', 1)),\
    Fst::NODE(1, Fst::RELATION('u', 2)),\
    Fst::NODE(1, Fst::RELATION('n', 3)),\
    Fst::NODE(1, Fst::RELATION('c', 4)),\
    Fst::NODE(1, Fst::RELATION('t', 5)),\
    Fst::NODE(1, Fst::RELATION('i', 6)),\
    Fst::NODE(1, Fst::RELATION('o', 7)),\
    Fst::NODE(1, Fst::RELATION('n', 8)),\
    Fst::NODE()

#define GRAPH_RETURN 7, \
	Fst::NODE(1,Fst::RELATION('r',1)),\
	Fst::NODE(1,Fst::RELATION('e',2)),\
	Fst::NODE(1,Fst::RELATION('t',3)),\
	Fst::NODE(1,Fst::RELATION('u',4)),\
	Fst::NODE(1,Fst::RELATION('r',5)),\
	Fst::NODE(1,Fst::RELATION('n',6)),\
	Fst::NODE()

#define GRAPH_DECLARE 8, \
    Fst::NODE(1, Fst::RELATION('d', 1)),\
    Fst::NODE(1, Fst::RELATION('e', 2)),\
    Fst::NODE(1, Fst::RELATION('c', 3)),\
    Fst::NODE(1, Fst::RELATION('l', 4)),\
    Fst::NODE(1, Fst::RELATION('a', 5)),\
    Fst::NODE(1, Fst::RELATION('r', 6)),\
    Fst::NODE(1, Fst::RELATION('e', 7)),\
    Fst::NODE()

#define GRAPH_PRINT 6,	\
	Fst::NODE(1, Fst::RELATION('p', 1)),\
    Fst::NODE(1, Fst::RELATION('r', 2)),\
    Fst::NODE(1, Fst::RELATION('i', 3)),\
    Fst::NODE(1, Fst::RELATION('n', 4)),\
    Fst::NODE(1, Fst::RELATION('t', 5)),\
    Fst::NODE()

#define GRAPH_ID 2, \
	Fst::NODE(26, Fst::RELATION('a',1),  Fst::RELATION('b',1), \
				 Fst::RELATION('c', 1),  Fst::RELATION('d', 1), \
				 Fst::RELATION('e', 1),  Fst::RELATION('f', 1), \
				 Fst::RELATION('g', 1),  Fst::RELATION('h', 1), \
				 Fst::RELATION('i', 1),  Fst::RELATION('j', 1), \
				 Fst::RELATION('k', 1),  Fst::RELATION('l', 1), \
				 Fst::RELATION('m', 1),  Fst::RELATION('n', 1), \
				 Fst::RELATION('o', 1),  Fst::RELATION('p', 1), \
				 Fst::RELATION('q', 1),  Fst::RELATION('r', 1), \
				 Fst::RELATION('s', 1),  Fst::RELATION('t', 1), \
				 Fst::RELATION('u', 1),  Fst::RELATION('v', 1), \
				 Fst::RELATION('w', 1),  Fst::RELATION('x', 1), \
				 Fst::RELATION('y', 1),  Fst::RELATION('z', 1)), \
	Fst::NODE(26, Fst::RELATION('a',1),  Fst::RELATION('b',1), \
				 Fst::RELATION('c', 1),  Fst::RELATION('d', 1), \
				 Fst::RELATION('e', 1),  Fst::RELATION('f', 1), \
				 Fst::RELATION('g', 1),  Fst::RELATION('h', 1), \
				 Fst::RELATION('i', 1),  Fst::RELATION('j', 1), \
				 Fst::RELATION('k', 1),  Fst::RELATION('l', 1), \
				 Fst::RELATION('m', 1),  Fst::RELATION('n', 1), \
				 Fst::RELATION('o', 1),  Fst::RELATION('p', 1), \
				 Fst::RELATION('q', 1),  Fst::RELATION('r', 1), \
				 Fst::RELATION('s', 1),  Fst::RELATION('t', 1), \
				 Fst::RELATION('u', 1),  Fst::RELATION('v', 1), \
				 Fst::RELATION('w', 1),  Fst::RELATION('x', 1), \
				 Fst::RELATION('y', 1),  Fst::RELATION('z', 1))
