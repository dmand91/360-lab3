#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "cs360utils.c"
#include <iostream>
#include <string.h>
#include <vector>
#include <sys/stat.h>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
//#include <unistd.h>
//#include <iostream>
//#include <stdio.h>
//#include <sys/types.h>
#include <dirent.h>
//#include<iostream>
//#include<fstream>
using namespace std;


#define SOCKET_ERROR        -1
#define BUFFER_SIZE         10000
#define MESSAGE             "This is the message I'm sending back and forth"
#define QUEUE_SIZE          5

int get_file_size(std::string path)
{
	struct stat filestat;
	if(stat(path.c_str(), &filestat)){
		return -1;
	}
	//check brackets
	return filestat.st_size;
}




int main(int argc, char* argv[])
{
    int hSocket,hServerSocket;  /* handle to socket */
    struct hostent* pHostInfo;   /* holds info about a machine */
    struct sockaddr_in Address; /* Internet socket address stuct */
    int nAddressSize=sizeof(struct sockaddr_in);
    char pBuffer[BUFFER_SIZE];
    int nHostPort;

    if(argc < 3)
      {
        printf("\nUsage: server host-port dir\n");
        return 0;
      }
    else
      {
        nHostPort=atoi(argv[1]);
      }

    printf("\nStarting server");

    printf("\nMaking socket");
    /* make a socket */
    hServerSocket=socket(AF_INET,SOCK_STREAM,0);

    if(hServerSocket == SOCKET_ERROR)
    {
        printf("\nCould not make a socket\n");
        return 0;
    }

    /* fill address struct */
    Address.sin_addr.s_addr=INADDR_ANY;
    Address.sin_port=htons(nHostPort);
    Address.sin_family=AF_INET;

    printf("\nBinding to port %d",nHostPort);

    /* bind to a port */
    if(bind(hServerSocket,(struct sockaddr*)&Address,sizeof(Address)) 
                        == SOCKET_ERROR)
    {
        printf("\nCould not connect to host\n");
        return 0;
    }
 /*  get port number */
    getsockname( hServerSocket, (struct sockaddr *) &Address,(socklen_t *)&nAddressSize);
    printf("opened socket as fd (%d) on port (%d) for stream i/o\n",hServerSocket, ntohs(Address.sin_port) );

        printf("Server\n\
              sin_family        = %d\n\
              sin_addr.s_addr   = %d\n\
              sin_port          = %d\n"
              , Address.sin_family
              , Address.sin_addr.s_addr
              , ntohs(Address.sin_port)
            );


    printf("\nMaking a listen queue of %d elements",QUEUE_SIZE);
    /* establish listen queue */
    if(listen(hServerSocket,QUEUE_SIZE) == SOCKET_ERROR)
    {
        printf("\nCould not listen\n");
        return 0;
    }
int optval = 1;
setsockopt (hServerSocket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

    for(;;)
    {
        printf("\nWaiting for a connection\n");
        /* get the connected socket */
        hSocket=accept(hServerSocket,(struct sockaddr*)&Address,(socklen_t *)&nAddressSize);

        printf("\nGot a connection from %X (%d)\n",
              Address.sin_addr.s_addr,
              ntohs(Address.sin_port));
        memset(pBuffer,0,sizeof(pBuffer));
        int rval = read(hSocket,pBuffer,BUFFER_SIZE);
	printf("Got from browser %d\n%s\n",rval, pBuffer);
#define MAXPATH 1000
	char path[MAXPATH];
	rval = sscanf(pBuffer,"GET %s HTTP/1.1",path);
	printf("Got rval %d, path %s\n",rval,path);
	char fullpath[MAXPATH];
	sprintf(fullpath,"%s%s",argv[2], path);
	printf("fullpath %s\n",fullpath);
//http://	

        
//     strcpy(path,fullpath);
	memset(pBuffer,0,sizeof(pBuffer));

	//find type of image

	//convert path to string		
	//string paths
	
		
 struct stat filestat;

	string pathStr(path);
	cout<<"path before: "<< pathStr<<endl;
	if(pathStr.at(0)=='/') pathStr=pathStr.substr(1,pathStr.length());
	cout<<"path AFTER: "<< pathStr<<endl;
	if(pathStr.length()==0) pathStr=".";
	//reconvert

	//char typeChar[1024];
        strncpy(path, pathStr.c_str(), sizeof(path));
        path[sizeof(path) - 1] = 0;
 
//CHECKING THE PATH TO SEE IF IT IS LEGAL============================================	
        if(stat(path, &filestat)) { //CHECK TO SEE IF FILE DOESN'T EXIST
                cout <<"ERROR in stat\nRESETING SERVER\n";

		//HTM L FOR THE EROR
		if(pathStr!="favicon.ico"){

		string htmlErrorStr = "<html><body><h1>THIS FILE OR DIRECTORY DOESN'T EXIST, COME ON MAN</h1></body></html>";
		  char *bufferError = (char *)malloc(1024+1);
                   char htmlError[1024];
                   strncpy(htmlError, htmlErrorStr.c_str(), sizeof(htmlError));
                   htmlError[sizeof(htmlError) - 1] = 0;

		memset(bufferError ,0,sizeof(BUFFER_SIZE));
        	sprintf(bufferError ,"HTTP/1.1 404 ERROR \r\n\r\n%s", htmlError);
         	write(hSocket,bufferError, strlen(bufferError));
		free(bufferError);


		}
        }
//============================IS A DIRECTORY OR FILE =================
else
{

	
	


	//FILE CHECKER HERE
        if(S_ISREG(filestat.st_mode)) {
                cout << path << " is a regular file \n";
                cout << "file size = "<<filestat.st_size <<"\n";
		
		//GRAB TYPE
		 string type;
		int position=pathStr.rfind(".");

		 printf("position of decimal %d\n",position);
		type=pathStr.substr(position+1);

		string typeofFile;
		if(type=="html") typeofFile="text/html";
		else if(type=="jpg") typeofFile="image/jpg";
		else if(type=="gif") typeofFile="image/gif";	
		else typeofFile="text/plain";
		

		 cout<< "type of file: " << typeofFile <<endl;
	 //cout<< "End of file\n"<<endl;
		

        string STRING;
        ifstream infile;
        infile.open (path);
        //while(!infile.eof()) // To get you all the lines.
       // {
         //       getline(infile,STRING); // Saves the line in STRING.
           //     cout<<STRING<<endl; // Prints our STRING.
       // }
        infile.close();

         cout<< "End of file\n"<<endl;
	char typeChar[1024];
	strncpy(typeChar, typeofFile.c_str(), sizeof(typeChar));
	typeChar[sizeof(typeChar) - 1] = 0;
	
		  int file_size= get_file_size(path);
        sprintf(pBuffer,"HTTP/1.1 200 OK\r\n\
Content-Type: %s\r\n\
Content-Length: %d\
\r\n\r\n",typeChar,file_size);
        write(hSocket,pBuffer, strlen(pBuffer));
        FILE *fp = fopen(path,"r");
        char *buffer = (char *)malloc(file_size+1);
        if (fp==NULL)
        {

                 printf("filepointer is null!!!!");
        }

        else{


                printf("filepointer: %s\n",fp);
        fread(buffer, file_size, 1,fp);
        write(hSocket,buffer,file_size);
        free(buffer);
        fclose(fp);
        }

//DIRECTORY CHECK===================================

        }
        if(S_ISDIR(filestat.st_mode)) {
                cout << path << " is a directory \n";
                 int len;
                DIR *dirp;
                struct dirent *dp;

                 dirp = opendir(path);
		string html="";
		bool indexFound=false;
		html+="<html><body><h1>Here is the directory listing</h1><br><ul>";
                  while ((dp = readdir(dirp)) != NULL){
                           printf("name %s\n", dp->d_name);
			   string name(dp->d_name);
			   if (name=="index.html") indexFound=true;
			   html+="<li><a href =\"/"+pathStr+"/"+ name+"\">"+name+ "</li>";
			}
                          (void)closedir(dirp);
		   html+= "</ul></body></html>";
		  cout<< "full html of DIR: " <<html<< endl;
	    if(indexFound!=true){
		 char *bufferDir = (char *)malloc(1024+1);
		 char htmlChar[1024];
        	strncpy(htmlChar, html.c_str(), sizeof(htmlChar));
        	htmlChar[sizeof(htmlChar) - 1] = 0;



		memset(bufferDir ,0,sizeof(BUFFER_SIZE));
        	sprintf(bufferDir ,"HTTP/1.1 200 OK \r\n\r\n%s\n", htmlChar);
         	write(hSocket,bufferDir, strlen(bufferDir ));
		free(bufferDir);		
		}
            else{//OPENING THE INDEX.HTML FILE IF IT EXISTS
	string thePath(path);
	thePath+="/index.html";
	strncpy(path, thePath.c_str(), sizeof(path));
        path[sizeof(path) - 1] = 0;

		 int file_size= get_file_size(path);
        sprintf(pBuffer,"HTTP/1.1 200 OK\r\n\
	Content-Type: %s\r\n\
	Content-Length: %d\
	\r\n\r\n","text/html",file_size);
        write(hSocket,pBuffer, strlen(pBuffer));
        FILE *fp = fopen(path,"r");
        char *buffer = (char *)malloc(file_size+1);
        if (fp==NULL)
        {

                 printf("filepointer is null!!!!IN HTML INDEX SECTIONS");
        }

        else{


                printf("filepointer: %s\n",fp);
        fread(buffer, file_size, 1,fp);
        write(hSocket,buffer,file_size);
        free(buffer);
        fclose(fp);
        }




		}			
	    	
		
		 // sprintf(bufferDir, htmlChar);
		   //write(hSocket,bufferDir, strlen(bufferDir));
        }


}


//END OF FILE LOGICE ======================================================
#ifdef notdef
linger lin;
unsigned int y=sizeof(lin);
lin.l_onoff=1;
lin.l_linger=10;
setsockopt(hSocket,SOL_SOCKET, SO_LINGER,&lin,sizeof(lin));	
shutdown(hSocket, SHUT_RDWR);
#endif
    printf("\nClosing the socket");
        /* close socket */
        if(close(hSocket) == SOCKET_ERROR)
        {
         printf("\nCould not close socket\n");
         return 0;
        }
    }
}
