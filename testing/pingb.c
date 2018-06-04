// This program pings a list of hosts a specified number of times
// with a delay between each ping, and records how many tries it took for 
// each host to first answer


#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

#include <stdio.h>
#include <string.h>

#include <stdio.h>
#include <stdlib.h>


#include <time.h>

#define HOST_COUNT 7

 static char const * hosts[HOST_COUNT]= {

  "192.168.1.158",
  "192.168.1.160",
  "192.168.1.162",
  "192.168.1.163",
  "192.168.1.165",
  "192.168.1.167",
  "192.168.1.168",
  
};

#define TRYCOUNT 20 	// try 10 times for 30 seconds each = 300 seconds = 5mins per on/off cycle

time_t nextrun=0;

// Each line of output looks like...
// 192.168.1.162 is alive

#define BUFLEN (HOST_COUNT * 30)

char buf[BUFLEN];

#define COMMAND_MAX 300

char command[COMMAND_MAX];


int answeredin[HOST_COUNT];			// Keep track of how long each host took to answer (starts at 0, and 0=never)						
									// Global so it gets inited to 0's

int main(int argc, char **argv)
{


	fprintf(stderr,"Building command line...\n");
	  
	strcpy( command , "/usr/bin/fping -a ");
	  
	for( int r = 0 ; r< HOST_COUNT ; r++ ) {
	  
		strcat( command , hosts[r] ); 
		strcat( command , " " ); 
	  
	}
	  
	fprintf(stderr,"Command:%s\n",command);
	
	  
	  

	// Start looking for pings

	time_t nextping = 0;   
	
	int t = 0;					// pass number?
	
	int alivecount=0;			// How many hosts have responded so far?
    
   while ( t< TRYCOUNT && alivecount< HOST_COUNT) { 
   
	  t++;
	  
	  fprintf( stderr , "try %d of %d\n" ,t , TRYCOUNT );
         	  
      if (nextping>=time(NULL)) {
        fprintf(stderr,"waiting....\n");
        while (nextping>=time(NULL));
        fprintf(stderr,"ready.\n");
      }
      
	  nextping = time(NULL) + 10;   
	  
	  fprintf(stderr,"Running...\n");
      
      FILE *fp=fp = popen(command, "r");

	  fprintf(stderr,"...done\n");
      
      while (fgets( buf , BUFLEN , fp ) ) {
            
        //fprintf(stderr,"parsing...\n");
              
        // grab first token which is the address
        
        char *addrsaveptr;           
        char  *addr = strtok_r( buf , " \n\r" , &addrsaveptr );
        
        //fprintf(stderr,">%s<\n",addr);                                
		
		for(int f=0; f< HOST_COUNT; f++ ) {
			
			//fprintf(stderr,"comparing >%s< >%s<\n",addr,hosts[f]);
			
			if (!strcmp( hosts[f] , addr )) {		// Match?
			
				//fprintf(stderr,"match\n");
				
				if (!answeredin[f]) {
					
					fprintf(stderr,"newly answered %s.\n",hosts[f]);
					answeredin[f]= t; 		

					alivecount++;
				}
			}			
			
		}
    
      }
  
      fclose(fp);
	  
	  fprintf(stderr,"alive %d of %d\n" , alivecount , HOST_COUNT );
		  
	  for( int f =0 ;f< HOST_COUNT; f++ ) {
		  
		  fprintf(stderr,"%2.02d" , answeredin[f]);
		  if (f<HOST_COUNT-1) fprintf(stderr,",");
		  
	  }
	  
	  fprintf(stderr,"\n");
	  
	    
  }
  
  if (alivecount==HOST_COUNT) {
	  fprintf(stderr,"all alive!\n");
  }
  
  for( int f =0 ;f< HOST_COUNT; f++ ) {
	  
	  printf("%2.02d" , answeredin[f]);
	  if (f<HOST_COUNT-1) printf(",");
	  
	  
  }
  
  printf("\n");

  
  return alivecount;
  
}
