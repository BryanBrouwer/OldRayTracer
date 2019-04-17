#include "Application.h"


int main()
{

	Application myApl;

	myApl.onCreate(); 
	myApl.Running = true;
	do
	{
		myApl.onUpdate();
	} while (myApl.Running == true);

	myApl.onDestroy();


}
	
