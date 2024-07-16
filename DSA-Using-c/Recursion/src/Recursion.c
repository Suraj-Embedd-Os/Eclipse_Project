/*
 ============================================================================
 Name        : Recursion.c
 Author      : EmbeddedOs
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int factorial(int num);
int puzzel(int num);

int eval(char *exp);

int main(void) {

char exp[] = "4+2*5";
		printf("%d ",eval(exp));
	return EXIT_SUCCESS;
}


int factorial(int num)
{
	if(num == 0)
		return 1;
	else
		return num*factorial(num-1);
}

int puzzel(int num)
{
	if(num == 1) return 1;

	if(num%2 == 0)
		return puzzel(num/2);
	else
		return puzzel(3*num+1);
}

int eval(char *exp)
{
	int static i =0;
	int x=0;

	while(exp[i] == ' ')i++;

	if(exp[i] == '+')
	{
		i++; return eval(exp) + eval(exp);
	}
	if(exp[i] == '*')
	{
		i++; return eval(exp) * eval(exp);
	}

	while(exp[i]>= '0' && exp[i] <='9'){
		x=x*10+(exp[i++] - '0');
	}
	return x;

}
