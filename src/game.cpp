
#include <iostream>
#include "marubatsu.h"
using namespace std;

int main()
{
	try{
		CMaruBatsuGame game(3,3);
		game.Exec();

	}catch(...){
		cerr << "例外が発生しました";
		return -1;
	}
	return 0;
}

