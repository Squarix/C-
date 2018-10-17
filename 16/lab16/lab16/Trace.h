#pragma once
//#include "GRB.h"

using namespace std;

int FST_TRACE_n = -1;
char rbuf[1024], sbuf[1024], lbuf[1024];

//#define ISNS(n) GRB::Rule::Chain::isN(n)

#define MFST_TRACE1 cout << setw(4) << left << ++FST_TRACE_n << ": " << setw(20) << left << rule.getCRule(rbuf, nrulechain) \
						 << setw(30) << left << getCLenta(lbuf, lenta_position) << setw(20) << left << getCSt(sbuf) << endl;

#define MFST_TRACE2 cout << setw(4) << left << FST_TRACE_n << ": " << setw(20) << left << " " \
						 << setw(30) << left << getCLenta(lbuf, lenta_position) << setw(20) << left << getCSt(sbuf) << endl;

#define MFST_TRACE3 cout << setw(4) << left << ++FST_TRACE_n << ": " << setw(20) << left << " " \
						 << setw(30) << left << getCLenta(lbuf, lenta_position) << setw(20) << left << getCSt(sbuf) << endl;

#define MFST_TRACE4(c) cout << setw(4) << left << ++FST_TRACE_n << ": " << setw(20) << left << " " << c << endl;

#define MFST_TRACE5(c) cout << setw(4) << left << FST_TRACE_n << ": " << setw(20) << left << " " << c << endl;

#define MFST_TRACE6(c, k) cout << setw(4) << left << ++FST_TRACE_n << ": " << setw(20) << left << " " << c << k << endl;

#define MFST_TRACE7 cout << setw(4) << left << state.lenta_position << ": " << setw(20) << left << rule.getCRule(rbuf, state.nrulechain) << endl;
