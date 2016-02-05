#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include<iostream>
#include<fstream>

using namespace std;

main(int argc, char **argv)
{
	struct stat filestat;

	if(stat(argv[1], &filestat)) {
		cout <<"ERROR in stat\n";
	}
	if(S_ISREG(filestat.st_mode)) {
		cout << argv[1] << " is a regular file \n";
		cout << "file size = "<<filestat.st_size <<"\n";
	string STRING;
	ifstream infile;
	infile.open (argv[1]);
        while(!infile.eof()) // To get you all the lines.
        {
	        getline(infile,STRING); // Saves the line in STRING.
		cout<<STRING<<endl; // Prints our STRING.
        }
	infile.close();
		
	 cout<< "End of file\n"<<endl;

	      
	}
	if(S_ISDIR(filestat.st_mode)) {
		cout << argv[1] << " is a directory \n";
		 int len;
 		DIR *dirp;
  		struct dirent *dp;

 		 dirp = opendir(argv[1]);
		  while ((dp = readdir(dirp)) != NULL)
			    printf("name %s\n", dp->d_name);
			  (void)closedir(dirp);
				
	}
	
}

