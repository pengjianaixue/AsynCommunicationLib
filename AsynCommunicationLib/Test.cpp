#include "stdafx.h"
#include "comdevice.h"
int main()
{
	ComDevice a;
	a.CreateCom("COM2", 9600, 8, 1, 2, 0);
	system("pause");
	return 0;

}