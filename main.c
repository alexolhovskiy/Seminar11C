////////////////////////////////////
///                              ///
///        ALEX OLHOVSKIY        ///
///                              ///
////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "temp_functions.h"


int main(int argc,char*argv[])
{
    char*fileName;
    int rez=0,month=0,day=0,key=0,visualisationFlag=0;
	// opterr=0;
	while ( (rez = getopt(argc,argv,"hf:ym:d:v")) != -1){
		switch (rez){
			case 'h':
                key=0;
                break;
			case 'f':
                fileName=optarg;
                key=1;
                break;
            case 'y':
                key=2;
                break;
			case 'm':
                key=3;
                month=strtol(optarg,NULL,10);
                break;
            case 'd':
                key=4;
                day=strtol(optarg,NULL,10);
                break;
            case 'v':
                visualisationFlag=1;
                break;
		};
	};

    switch(key){
        case 0:description();
            break;
        case 1:statisticCalcForYear(fileName,visualisationFlag);
            break;
        case 2:statisticCalcForYearDayByDay(fileName,visualisationFlag);
            break;
        case 3:statisticCalcForMonth(fileName,month,visualisationFlag);
            break;
        case 4:statisticCalcForDay(fileName,month,day,visualisationFlag);
            break;
        default:;
    }



    return 0;
}
