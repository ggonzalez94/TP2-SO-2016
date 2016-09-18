#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/ksamp.h"

void getMainProgram(struct Datos *datos){

    strcpy(path,"/proc/cpuinfo");
    strcpy(before,"model name");
    strcpy(after,"");
    parseFile(fp,path,before,after,&buff);
    strcpy(datos->cpu,buff+2);

    strcpy(path,"/proc/version");
    strcpy(before,"version ");
    strcpy(after,"(");
    parseFile(fp,path,before,after,&buff);
    strcpy(datos->kernel,buff);

    strcpy(path,"/proc/uptime");
    strcpy(before," ");
    strcpy(after,"");
    parseFile(fp,path,before,after,&buff);
    datos->uptime = atol(buff);

    getSupFs(fp,&datos->filesystems);
}

void getStats(struct Datos *datos){

   	strcpy(path,"/proc/stat");
    strcpy(before,"cpu");
    strcpy(after,"");
    parseFile(fp,path,before,after,&buff);

	buff = strstr(buff," ") + strlen(" ")+1;
	strcpy(buffer,strtok(buff," "));

    datos->userTime = atoi(buffer);
    strcpy(buffer,strtok(NULL," "));
    strcpy(buffer,strtok(NULL," "));
    datos->sysTime = atoi(buffer);
    strcpy(buffer,strtok(NULL," "));
    datos->idleTime = atoi(buffer);

	getBootTime(&buff,datos->uptime);
    strcpy(datos->bootTime, buff);
	
    strcpy(path,"/proc/stat");
    strcpy(before,"ctxt ");
    strcpy(after,"");
    parseFile(fp,path,before,after,&buff);
    datos->contextChanges = atoi(buff);
    
	strcpy(path,"/proc/stat");
    strcpy(before,"processes ");
    strcpy(after,"");
    parseFile(fp,path,before,after,&buff);
    datos->processes = atoi(buff);
}


void calculateInterval(struct Interval *interval){

	strcpy(path,"/proc/diskstats");
    strcpy(before,"sda");
    strcpy(after,"");
    parseFile(fp,path,before,after,&buff);

	buff = strstr(buff," ") + strlen(" ");	
	strcpy(buffer,strtok(buff," "));

    interval->reads = atoi(buffer);
    strcpy(buffer,strtok(NULL," "));
    strcpy(buffer,strtok(NULL," "));
    strcpy(buffer,strtok(NULL," "));
    strcpy(buffer,strtok(NULL," "));
    interval->writes = atoi(buffer);

    interval->rw = interval->reads + interval->writes;

	strcpy(path,"/proc/meminfo");
    strcpy(before,"MemTotal:");
    strcpy(after,"");
    parseFile(fp,path,before,after,&buff);
    
    interval->memTot = atoi(buff);

    strcpy(before,"MemFree:");
    parseFile(fp,path,before,after,&buff);
    
    interval->memDisp = atoi(buff);

	strcpy(path,"/proc/loadavg");
    strcpy(before,"");
    strcpy(after," ");
    parseFile(fp,path,before,after,&buff);
    
    interval->loadAvg = atof(buff);
}