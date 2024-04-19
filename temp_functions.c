
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void description(){
    printf("This program calculates statistics based on the results of the operation of a year-round temperature sensor\n");
    printf("flags:\n");
    printf("-f To calculate per month year statistics based on sensor data, \nenter -f<file_name.csv> , where <file_name> - name of file with sensor data\n");
    printf("-y Get statistic per day for recent year\n");
    printf("-m To get statistics for a specific month - enter: -m<month> , \nwhere month - number of the month in year\n");
    printf("-d To get statistic for a specific day - enter: -d<day>, \nwhere day - number of the day in month. \nNote! To get this option you have to setup '-m' flag!\n");
    printf("-v To get graph of the interested statistic data. \nNote! You have to have python3 with tkinter lib and json lib on your PC to get this option\n");
}

void statisticCalcForYearDayByDay(char*name,int v){
    int i=1,curDay=-1,curMonth=-1,cntTempDay=0,cntSamplesDay=0,maxTemp=-273,minTemp=100,h=0,m=0,Y=0,M=0,d=0,t=0;
    int cntTempYear=0,cntSamplesYear=0,maxTempY=-273,minTempY=100;
    float temp=0;
    int error=255,num=0;
    FILE *fd=fopen(name,"r");
    FILE*lfd=fopen("test.json","w");
    if(fd!=NULL&lfd!=NULL){
        printf("Opened success!\n");
        printf("Statistic for year day by day\n");
        printf("Day\tAverage temp.\tmin temp.\tmax temp.\n");
        fprintf(lfd,"{\"title\":\"Statistic For Year Day By Day\",\"arr\":[");
        while((error=fscanf(fd,"%d;%d;%d;%d;%d;%d",&Y,&M,&d,&h,&m,&t))!=EOF){
            if(error==0){
                while(fgetc(fd)!='\n'){}
                printf("Error in line # %d\n",num);
            }
            num++;
            if((curDay!=d)|(curMonth!=M)){
                if(curDay>0){
                    temp=cntTempDay/cntSamplesDay;
                    printf("%d\t\t%.2f\t\t%d\t\t%d\n",curDay,temp,minTemp,maxTemp);
                    fprintf(lfd,"[%d,%.0f],",i,temp);

                    cntTempYear+=cntTempDay;
                    cntSamplesYear+=cntSamplesDay;

                    if(maxTemp>maxTempY){
                        maxTempY=maxTemp;
                    }
                    if(minTemp<minTempY){
                        minTempY=minTemp;
                    }

                    cntTempDay=0;
                    cntSamplesDay=0;
                    maxTemp=-273;
                    minTemp=100;
                }
                curDay=d;
                curMonth=M;
                i++;
            }


            cntTempDay+=t;
            cntSamplesDay++;
            if(t>maxTemp){
                maxTemp=t;
            }
            if(t<minTemp){
                minTemp=t;
            }
        }
        temp=cntTempDay/cntSamplesDay;
        printf("%d\t\t%.2f\t\t%d\t\t%d\n",curDay,temp,minTemp,maxTemp);
        fprintf(lfd,"[%d,%.0f]]}",i,temp);

        cntTempYear+=cntTempDay;
        cntSamplesYear+=cntSamplesDay;
        temp=cntTempYear/cntSamplesYear;

        if(maxTemp>maxTempY){
            maxTempY=maxTemp;
        }
        if(minTemp<minTempY){
            minTempY=minTemp;
        }

        printf("Average temp. at 2021 year was:%.2f\n",temp);
        printf("Min temp. per 2021 year was:%d\n",minTempY);
        printf("Max temp. per 2021 year was:%d\n",maxTempY);


        fclose(fd);
        fclose(lfd);
    }else{
        printf("Error! Cannot open file!\n");
    }
    if(v==1){
        system("python test.py");
    }

}

void statisticCalcForDay(char*name,int month,int day,int v){
    int i=1,curHour=-1,cntTempHour=0,cntSamplesHour=0,maxTemp=-273,minTemp=100,h=0,m=0,Y=0,M=0,d=0,t=0,flag=1,switcher=0;
    int cntTempDay=0,cntSamplesDay=0,maxTempDay=-273,minTempDay=100;
    float temp=0;
    int error=255,num=0;
    FILE *fd=fopen(name,"r");
    FILE*lfd=fopen("test.json","w");
    if(fd!=NULL&lfd!=NULL){
        printf("Opened success!\n");
        printf("Statistic for %d day of %d month hour by hour\n",day,month);
        printf("Hour\tAverage temp.\tmin temp.\tmax temp.\n");
        fprintf(lfd,"{\"title\":\"Statistic For %d Day of %d Month Hour By Hour\",\"arr\":[",day,month);
        while(((error=fscanf(fd,"%d;%d;%d;%d;%d;%d",&Y,&M,&d,&h,&m,&t))!=EOF)&(flag==1)){
            if(error==0){
                while(fgetc(fd)!='\n'){}
                printf("Error in line # %d\n",num);
            }
            num++;
            if(M==month){
                if(d==day){
                    switcher=1;
                    if(curHour!=h){
                        if(curHour>0){
                            temp=cntTempHour/cntSamplesHour;
                            printf("%d\t\t%.2f\t\t%d\t\t%d\n",curHour,temp,minTemp,maxTemp);
                            fprintf(lfd,"[%d,%.0f],",i,temp);

                            cntTempDay+=cntTempHour;
                            cntSamplesDay+=cntSamplesHour;

                            if(maxTemp>maxTempDay){
                                maxTempDay=maxTemp;
                            }
                            if(minTemp<minTempDay){
                                minTempDay=minTemp;
                            }

                            cntTempHour=0;
                            cntSamplesHour=0;
                            maxTemp=-273;
                            minTemp=100;
                        }
                        curHour=h;
                        i++;
                    }

                    cntTempHour+=t;
                    cntSamplesHour++;
                    if(t>maxTemp){
                        maxTemp=t;
                    }
                    if(t<minTemp){
                        minTemp=t;
                    }
                }else{
                    if(switcher==1){
                        flag=0;
                    }
                }
            }
        }
        temp=cntTempHour/cntSamplesHour;
        printf("%d\t\t%.2f\t\t%d\t\t%d\n",curHour,temp,minTemp,maxTemp);
        fprintf(lfd,"[%d,%.0f]]}",i,temp);


        cntTempDay+=cntTempHour;
        cntSamplesDay+=cntSamplesHour;
        temp=cntTempDay/cntSamplesDay;

        if(maxTemp>maxTempDay){
            maxTempDay=maxTemp;
        }
        if(minTemp<minTempDay){
            minTempDay=minTemp;
        }

        printf("Average temp. at %d day of %d month was:%.2f\n",day,month,temp);
        printf("Min temp. per %d day of %d month was:%d\n",day,month,minTempDay);
        printf("Max temp. per %d day of %d month was:%d\n",day,month,maxTempDay);

        fclose(fd);
        fclose(lfd);
    }else{
        printf("Error! Cannot open file!\n");
    }
    if(v==1){
        system("python test.py");
    }
}

void statisticCalcForMonth(char*name,int month,int v){
    int i=1,curMonth=0,curDay=-1,cntTempDay=0,cntSamplesDay=0,maxTemp=-273,minTemp=100,h=0,m=0,Y=0,M=0,d=0,t=0,flag=1,switcher=0;
    int cntTempMonth=0,cntSamplesMonth=0,maxTempMonth=-273,minTempMonth=100;
    float temp=0;
    int error=255,num=0;
    FILE *fd=fopen(name,"r");
    FILE*lfd=fopen("test.json","w");
    if(fd!=NULL&lfd!=NULL){
        printf("Opened success!\n");
        printf("Statistic of %d month day by day\n",month);
        printf("Day\tAverage temp.\tmin temp.\tmax temp.\n");
        fprintf(lfd,"{\"title\":\"Statistic of %d Month Day By Day\",\"arr\":[",month);
        while(((error=fscanf(fd,"%d;%d;%d;%d;%d;%d",&Y,&M,&d,&h,&m,&t))!=EOF)&(flag==1)){
            if(error==0){
                while(fgetc(fd)!='\n'){}
                printf("Error in line # %d\n",num);
            }
            num++;
            if(M==month){
                switcher=1;
                if(curDay!=d){
                    if(curDay>0){
                        temp=cntTempDay/cntSamplesDay;
                        printf("%d\t\t%.2f\t\t%d\t\t%d\n",curDay,temp,minTemp,maxTemp);
                        fprintf(lfd,"[%d,%.0f],",i,temp);

                        cntTempMonth+=cntTempDay;
                        cntSamplesMonth+=cntSamplesDay;

                        if(maxTemp>maxTempMonth){
                            maxTempMonth=maxTemp;
                        }
                        if(minTemp<minTempMonth){
                            minTempMonth=minTemp;
                        }

                        cntTempDay=0;
                        cntSamplesDay=0;
                        maxTemp=-273;
                        minTemp=100;
                    }
                    curDay=d;
                    i++;
                }

                cntTempDay+=t;
                cntSamplesDay++;
                if(t>maxTemp){
                    maxTemp=t;
                }
                if(t<minTemp){
                    minTemp=t;
                }
            }else{
                if(switcher==1){
                    flag=0;
                }
            }
        }
        temp=cntTempDay/cntSamplesDay;
        printf("%d\t\t%.2f\t\t%d\t\t%d\n",curDay,temp,minTemp,maxTemp);
        fprintf(lfd,"[%d,%.0f]]}",i,temp);

        cntTempMonth+=cntTempDay;
        cntSamplesMonth+=cntSamplesDay;
        temp=cntTempMonth/cntSamplesMonth;

        if(maxTemp>maxTempMonth){
            maxTempMonth=maxTemp;
        }
        if(minTemp<minTempMonth){
            minTempMonth=minTemp;
        }

        printf("Average temp. at %d month was:%.2f\n",month,temp);
        printf("Min temp. per %d month was:%d\n",month,minTempMonth);
        printf("Max temp. per %d month was:%d\n",month,maxTempMonth);


        fclose(fd);
        fclose(lfd);
    }else{
        printf("Error! Cannot open file!\n");
    }
    if(v==1){
        system("python test.py");
    }
}

void statisticCalcForYear(char*name,int v){
    int i=0,curYear=2021,curMonth=-1,cntTempMonth=0,cntTempYear=0,cntSamplesMonth=0,cntSamplesYear=0,maxTemp=-273,minTemp=100,maxTempY=-273,minTempY=100,h=0,m=0,Y=0,M=0,d=0,t=0;
    float temp=0;
    int error=255,num=0;
    FILE *fd=fopen(name,"r");
    FILE*lfd=fopen("test.json","w");
    if(fd!=NULL&lfd!=NULL){
        printf("Opened success!\n");
        printf("%d Year Temperature Statistic\n",curYear);
        printf("Month\tAverage temp.\tmin temp.\tmax temp.\n");
        fprintf(lfd,"{\"title\":\"%d Year Temperature Statistic by Month\",\"arr\":[",curYear);
        while((error=fscanf(fd,"%d;%d;%d;%d;%d;%d",&Y,&M,&d,&h,&m,&t))!=EOF){
            if(error==0){
                while(fgetc(fd)!='\n'){}
                printf("Error in line # %d\n",num);
            }
            num++;
            if(curYear!=Y){
                curYear=Y;
            }
            if(curMonth!=M){
                if(curMonth>0){
                    temp=cntTempMonth/cntSamplesMonth;
                    cntTempYear+=cntTempMonth;
                    cntSamplesYear+=cntSamplesMonth;
                    if(maxTemp>maxTempY){
                        maxTempY=maxTemp;
                    }
                    if(minTemp<minTempY){
                        minTempY=minTemp;
                    }

                    printf("%d\t\t%.2f\t\t%d\t\t%d\n",curMonth,temp,minTemp,maxTemp);
                    fprintf(lfd,"[%d,%.0f],",i,temp);

                    cntTempMonth=0;
                    cntSamplesMonth=0;
                    maxTemp=-273;
                    minTemp=100;
                }
                curMonth=M;
                i++;
            }

            cntTempMonth+=t;
            cntSamplesMonth++;
            if(t>maxTemp){
                maxTemp=t;
            }
            if(t<minTemp){
                minTemp=t;
            }
        }

        temp=cntTempMonth/cntSamplesMonth;
        printf("%d\t\t%.2f\t\t%d\t\t%d\n",curMonth,temp,minTemp,maxTemp);
        fprintf(lfd,"[%d,%.0f]]}",i,temp);

        cntTempYear+=cntTempMonth;
        cntSamplesYear+=cntSamplesMonth;
        temp=cntTempYear/cntSamplesYear;

        if(maxTemp>maxTempY){
            maxTempY=maxTemp;
        }
        if(minTemp<minTempY){
            minTempY=minTemp;
        }

        printf("Average temp. at %d year was:%.2f\n",curYear,temp);
        printf("Min temp. per %d year was:%d\n",curYear,minTempY);
        printf("Max temp. per %d year was:%d\n",curYear,maxTempY);

        fclose(fd);
        fclose(lfd);
    }else{
        printf("Error! Cannot open file!\n");
    }
    if(v==1){
        system("python test.py");
    }
}
