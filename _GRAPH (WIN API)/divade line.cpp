#include "_GRAPH (Dima).h"


const char  razdel[]="{,?!. '\n'}";
 
int massiv_slov(char string[], char ** words)// ��������� ������ string �� ����� � ��������� ��� ������  words
{	
	//char razdel1[]="{},";
	int count = 0 ;
	words[count] = strtok( string, razdel );
	while( words[count] != NULL )
	{	count++; 	
	words[count] = strtok( NULL, razdel );
	}
	return count; //���������� ���������� ���� � ������
}