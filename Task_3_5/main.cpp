#include "Sentence.h"

void main(void)
{
	CText*	gpText = NULL;
	CText*	gpSymb = NULL;

	CText Choice;

	do
	{
		system("cls");	//clear console-display

		EnterSentence(gpText);
		EnterSymbols(gpText, gpSymb);
	
		system("cls");	//clear console-display

		cout<<"Results:\n\n";
		cout<<"\nEntered tex: "<<gpText;
		cout<<"\nAn initial length:"<<strlen(gpText)<<"\n";

		cout<<"\nEntered symbol-combination: "<<gpSymb;

		if(DelSymbols(gpText, gpSymb))
		{
			if(gpText != NULL)
			{
				cout<<"\n\nA final sentence: "<<gpText;
				cout<<"\nA final length:"<<strlen(gpText)<<"\n";
			}
			else
			{
				cout<<"\n\nWhole sentence are clear!\n\n";
			}
		}
		else
		{
			cout<<"\n\nNo matches in sentence!\n\n";
		}

		cout<<"\nWould you enter text again!? (y/n): ";
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cin>>Choice;

	}while(Choice == 'y');
	
	cout<<"\nExit.";
	system("pause");
}