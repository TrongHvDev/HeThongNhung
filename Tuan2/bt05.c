//read cpu temp

#include <stdio.h>
#include <unistd.h>
#include <time.h>

int main(void){
// hien thi nhiet do cpu
    FILE *tempfile;
    float temp;
    tempfile = fopen("/sys/class/thermal/thermal_zone0/temp", "r");
    fscanf(tempfile, "%f", &temp);
    temp = temp / 1000;
    fclose(tempfile);
 
    
// hien thi thoi gian  
    time_t rawtime;
    struct tm *ct;

    time (&rawtime);
    ct = localtime (&rawtime);
    printf("%02d/%02d/%04d/ %02d:%02d:%02d %.2f \n", ct->tm_mday, ct->tm_mon+1,ct->tm_year+1900, ct->tm_hour, ct->tm_min, ct->tm_sec, temp);

    return 0;

}