#include "number.h"





int C_n_k(int N, int K)
{
	if ((K==0)||(K==N))	return 1;
	if (K==1)	return N;
	int c;
	if (N-K<K)
		K=N-K;
	__asm
	{
		mov		EAX,	N;
		mov		ECX,	K;			k! k - ��������
		sub		ECX,	1;			�� ��� ������ ������, ������ ��������� ��� ����
		mov		EBX,	1;			�����������
		sub		EAX,	K;			
		add		EAX,	1;			��������� ���������
		mov		ESI,	EAX;		����� ��������� ���������
		mov		EDX,	0;

		cmp		ECX,	0;
		jNG		end_;
for1:	
		add		ESI,	1;			��������� ���������
		mul		ESI;
		add		EBX,	1;			��������� �����������
		div		EBX;
		mov		EDX,	0;			��� �������
		loopNZ	for1;

end_:
		mov		c,		EAX;	
	}
	return c;
}