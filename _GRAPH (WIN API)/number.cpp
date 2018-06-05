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
		mov		ECX,	K;			k! k - повторов
		sub		ECX,	1;			на оди повтор меньше, первый множетель уже есть
		mov		EBX,	1;			знаменатель
		sub		EAX,	K;			
		add		EAX,	1;			множетель числителя
		mov		ESI,	EAX;		будет следующий множетель
		mov		EDX,	0;

		cmp		ECX,	0;
		jNG		end_;
for1:	
		add		ESI,	1;			следующий множетель
		mul		ESI;
		add		EBX,	1;			следующий знаменатель
		div		EBX;
		mov		EDX,	0;			для деления
		loopNZ	for1;

end_:
		mov		c,		EAX;	
	}
	return c;
}