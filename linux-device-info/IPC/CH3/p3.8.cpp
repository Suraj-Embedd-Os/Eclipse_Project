#include<stdio.h>
#include<stdlib.h>
#include <iostream>
using namespace std;

int main()
{
	void f1(),f2(),f3();
	 atexit(f1);
	 atexit(f2);
	 atexit(f3);
	 cout << "Getting ready to exit" << endl;
	 exit(0);
	return 0;
}

void f1()
{
	cout << "Doing F1" << endl;
	
}

void f2()
{
	cout << "Doing F2" << endl;
}

void f3()
{
	cout << "Doing F3" << endl;
	exit(0);
}
