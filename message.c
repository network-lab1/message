#include<stdio.h> 
#include<sys/ipc.h> 
#include<sys/msg.h> 
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
  
//structure for message queue 
struct mesg_buffer { 
    long mesg_type; 
    int a[5][5]; 
}sendmsge,recmsge; 
  
int main() 
{ 
    key_t key;
    pid_t p; 
    int msgid,i,j; 
  
    //ftok to generate unique key 
    key = ftok("progfile", 65); 
  
    //msgget creates a message queue 
    //and returns identifier 
    msgid = msgget(key, 0666 | IPC_CREAT); 
    sendmsge.mesg_type = 1; 
  
    p = fork();
    
    if(p<0)
    	printf("Fork failled");
    	
    else if(p>0){
		printf("Enter Array Elements: "); 
		for(i =0; i<5; i++){
			for(j=0; j<5; j++)
				scanf("%d", &sendmsge.a[i][j]);
		} 
	  
		//msgsnd to send message 
		msgsnd(msgid, &sendmsge, sizeof(sendmsge), 0);
		 
	  
		printf("Matrix send is :\n"); 
	  	for(i =0; i<5; i++){
			for(j=0; j<5; j++)
				printf("%d\t", sendmsge.a[i][j]);
			printf("\n");
		}
	}
  
 	else{ 
		//msgrcv to receive message 
		msgrcv(msgid, &recmsge, sizeof(recmsge), 1, 0); 
	   
    	
    	printf("Diagonal Elements is:\n");
		for(i =0; i<5; i++){
    		for(j=0; j<5; j++){
    			if(i==j)
    				printf("%d", recmsge.a[i][j]);
    		} 
	  	}
		printf("\n");
		// to destroy the message queue 
		msgctl(msgid, IPC_RMID, NULL); 
		exit(0);
	}
    return 0; 
} 
