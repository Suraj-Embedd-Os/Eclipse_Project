 #include <iostream>
 #include <cstdlib>
 #include <sys/types.h>
 #include <unistd.h>
 
 
 using namespace std;
 
 int main(int argc,char *argv[])
 {
	 
	 if(argc>1)
	 {
		 execlp("/bin/cat","cat",argv[1],(char*)NULL);
		 perror("Exec Failed ");
		 return 1;
		 
	 }
	 cerr<<"Usage error "<<*argv<<" text file"<<endl;
	 return 0;
 }
 