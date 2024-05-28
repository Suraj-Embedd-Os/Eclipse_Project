 #include <iostream>
 #include <cstdlib>
 #include <sys/types.h>
 #include <unistd.h>
using namespace std;


int main(int argc, char *argv[])
{
	
	if(argc>1)
	{
		execvp(argv[1],&argv[1]);
		perror("falied execvp");
		return 1;
	}
	cerr << "Usage: " << *argv << " exe [arg(s)]" << endl;
	return 2;
	
}

	