#ifndef SENTENCE_H
#define SENTENCE_H

#include <iostream>

using namespace std;

#define IN			const		//notation of the input parameter
#define OUT						//notation the output parameter
#define INOUT					//notation the in-output parameter
#define MAX_TEXTLEN	16			//maximum length of sentence

#define RET_OK		true		//true value
#define RET_FAIL	false		//false value
#define INVALID_POS -1			//invalid position of symbol-combination

//typedef
typedef  char			CPos;
typedef unsigned char	CTxtLen;
typedef char			CText;

void EnterSentence( OUT CText *&pText);
void EnterSymbols(IN CText* pText, OUT CText*& pSymb);

bool DelSymbols(INOUT CText*& pText, IN CText* pSymb);

CPos GetStrPos(IN CText* pText, IN CText* pSymb);
void ShiftLeft(INOUT CText *pText, IN CTxtLen& Len);

bool IsMemoryOk(void* pVoid);

#endif /*SENTENCE_H*/