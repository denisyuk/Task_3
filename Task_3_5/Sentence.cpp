#include "Sentence.h"

void EnterSentence( OUT CText*& pText)
{
	CText* pTmp = (CText*)calloc(MAX_TEXTLEN, sizeof(CText));
	if(!IsMemoryOk((CText*)pTmp))
	{
		exit(0);
	}

//entering of the text
	cout<<"\nLet's enter text (max "<<MAX_TEXTLEN<<" symbols): ";
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	cin.getline(pTmp, MAX_TEXTLEN, '\n');

	if(strlen(pTmp) >= (MAX_TEXTLEN))
	{
		*(pTmp + MAX_TEXTLEN) = '\0';
	}
//end an entering of text

	CTxtLen TxtLen = (CTxtLen)strlen(pTmp);		//length of entered text

	pText = (CText*)calloc(TxtLen, sizeof(CText));
	if(!IsMemoryOk((CText*)pText))
	{
		exit(0);
	}
	else
	{
		memcpy(pText, pTmp, TxtLen);
		*(pText + TxtLen) = '\0';
	}
}

void EnterSymbols(IN CText* pText, OUT CText*& pSymb)
{
	if(pText == NULL)
	{
		cout<<"(Enter Symbol)Bad pointer\n";
		system("pause");
		exit(0);
	}

	CTxtLen TxtLen = strlen(pText);		//length of entered text

	CText* pTmp = (CText*)calloc((MAX_TEXTLEN - TxtLen), sizeof(CText));
	if(!IsMemoryOk((CText*)pTmp))
	{
		exit(0);
	}

//entering of text
	cout<<"\nLet's enter any symbol-combination \n (max "<<((int)TxtLen - 1)<<" symbols): ";
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	cin.getline(pTmp, TxtLen, '\n');

	if(strlen(pTmp) >= (MAX_TEXTLEN - TxtLen))
	{
		*(pTmp + (MAX_TEXTLEN - TxtLen)) = '\0';
	}
//end an entering of text

	TxtLen = (CTxtLen)strlen(pTmp);		//length of entered text

	pSymb = (CText*)calloc(TxtLen, sizeof(CText));
	if(!IsMemoryOk((CText*)pSymb))
	{
		exit(0);
	}
	else
	{
		memcpy(pSymb, pTmp, TxtLen);
		*(pSymb + TxtLen) = '\0';
	}
}

bool DelSymbols(INOUT CText*& pText, IN CText* pSymb)
{
	CPos SymbPos = INVALID_POS;
	CPos CurPos = NULL;
	CTxtLen SymbLen = (CTxtLen)strlen(pSymb);
	CTxtLen TextLen = (CTxtLen)strlen(pText);

	CText *TmpTxt = (CText*) calloc(TextLen, sizeof(CText));
	if(!IsMemoryOk((CText*)TmpTxt))
	{
		exit(0);
	}
	else
	{
		memcpy(TmpTxt, pText, TextLen);
		*(TmpTxt + TextLen) = '\0';
	}

	//if there are no matches then do nothing
	if(strstr(TmpTxt, pSymb) == NULL)
	{
		return RET_FAIL;
	}
	else	//if we have some matches then delete it from the sentence
	{
		do
		{
		
			SymbPos = GetStrPos(TmpTxt + CurPos, pSymb);	//get first, second, ...n position of the symbols-combination in sentence
			if(SymbPos != INVALID_POS)
			{
				ShiftLeft(TmpTxt + (SymbPos + CurPos), SymbLen);
				
				CurPos += SymbPos;
				
			}		
		}
		while(SymbPos != INVALID_POS);

		TextLen = (CTxtLen)strlen(TmpTxt);
		if(TextLen != NULL)
		{
			pText = (CText*)realloc(pText, sizeof(CText) * TextLen);
			if(!IsMemoryOk((CText*)pText))
			{
				exit(0);
			}
			else
			{
				memcpy(pText, TmpTxt, TextLen);
				*(pText + TextLen) = '\0';
			}
		}
		else
		{
			pText = NULL;
		}

		return RET_OK;
	}
}

CPos GetStrPos(IN CText* pText, IN CText* pSymb)
{
	CTxtLen TxtLen = strlen(pText);
	CTxtLen SymbLen = strlen(pSymb);

	for(CTxtLen i = 0; i < TxtLen; i++)
	{
		if(*(pText + i) == *(pSymb))
		{
			for(CTxtLen j = 0; j < SymbLen; j++)
			{
				if(*(pText + i + j) != *(pSymb + j))
				{
					break;
				}
				else
				{
					if(j >= (SymbLen - 1))
					{
						return i;
					}
				}
			}
		}
	}


	return INVALID_POS;
}

void ShiftLeft(INOUT CText* pText, IN CTxtLen& Len)
{
	CTxtLen SymbCount = 0;	//count of symbols in symbol-combination
	while(SymbCount<Len)
	{
		CTxtLen TxtLen = 0;
		do
		{		
			*(pText + TxtLen) = *(pText + TxtLen + 1);
			TxtLen++;
		}while(*(pText + TxtLen) != '\0');
		SymbCount++;
	}

}
//if Pointer is equal NULL - then "error"
bool IsMemoryOk(void* pVoid)
{
	if(pVoid == NULL)
	{
		cout<<"Can't allocate memory!\n";
		system("pause");
		return RET_FAIL;
	}

	return RET_OK;
}