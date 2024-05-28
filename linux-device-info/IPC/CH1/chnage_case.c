#include<stdio.h>
#include <ctype.h>
#include<stdlib.h>


char *change_case(char *s)
{
   char * t =&s[0];
   
   while(*t)
   {
   	if(isalpha(*t))
   	 *t+=islower(*t)?-32:32;
   	
    ++t;
   }
	
	return s;
}

int main()
{
	char str[]="abcd1234abc";
	
	char *s=change_case(str);
	
	printf("%s ",s);
	return 0;
}
