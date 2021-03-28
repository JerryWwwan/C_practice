#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>


int main(){
    printf("=============================================\n");
    FILE *fp;
    pid_t cpid;
    int error = 0;


    system("./count1 & echo $! > ./count.pid");     //$!:PID of last job running in background.
    usleep(10000);
    fp = fopen("./count.pid","r");
    if(fp != NULL){
        fscanf(fp,"%d",&cpid);
        fclose(fp);
        if(kill(cpid,0) != 0){      //check job process
            error = 1;
        }
    } else {
        error = 1;
    }

    printf("process %s exists!!\n",error?"does not":"actually");
    sleep(2);
    if(error == 0){
        printf("sleep 5 second and then kill the process\n");
        sleep(5);
        kill(cpid, SIGKILL);        // kill the job by PID
    }

    return 0;
}