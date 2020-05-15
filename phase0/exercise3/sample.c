#include <spede/stdio.h>
#include <spede/flames.h>

void DisplayMessage(int);

int main(void)
{
	int i;
	i = 111;
	for (; i<=115; i++)
	{
		DisplayMessage(i);
	}
	return 0;
}

void DisplayMessage(int i)
{
	printf("%d Hello world %d\nECS", i, 2*1);
	printf("--> Hello world <--\nCPE/CSC");
}
