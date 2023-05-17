#include "stmanager.h"
#include "templatelinkedlist.h"

int main()
{
	std::ios::sync_with_stdio(false);
	nsp_MySTM::StudentManager mySTM;

	mySTM.run();
	
	return 0;
}