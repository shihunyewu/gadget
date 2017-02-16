#include<stdio.h>
#include<stdlib.h>
#include <time.h>

//用来获取系统时间
void getTime(int *systime);
void halt(int time);
void printOption();

int main()
{
	int option = -1;
	int time = 0;
	int systime[2];
	int pvtime[2];
	int hours;
	
	printOption();
	scanf("%d",&option);
	
	switch(option)
	{
		case 1: 
			printf("input the time:");
			scanf("%d",&time);
			while(time<0)
			{
				printf("error!please input again:");
				scanf("%d",&time);
			}	
			if(time<3600)
				printf("system will halt after %.2f minutes",(float)time/60);
			else
				printf("system will halt after %.2f hours",(float)time/3600);
			printf("\n");
			halt(time);
			break;
		case 2:
			printf("when will system halt:");
			scanf("%d:%d",&pvtime[0],&pvtime[1]);
			getTime(systime);
			pvtime[0]=pvtime[0]-systime[0]>0?pvtime[0]:pvtime[0]+24;
			hours = (pvtime[0]-systime[0])%24*60;
			time = (hours+(pvtime[1]-systime[1]))*60;
			printf("system will halt at %d:%d\n",pvtime[0]%24,pvtime[1]);
			
			halt(time);
			break;
		case 3:
			system("shutdown -a");
			printf("cancle!\n");
			system("pause");
			exit(0);
			break;
		case 4:
			exit(0);
			break;
	}
	return 0;
}

void getTime(int *systime)
{
	time_t timep;
    struct tm *p;
	
    time(&timep);
    p = gmtime(&timep);
	systime[0] = (p->tm_hour+8)%24;
	systime[1] = p->tm_min;
}

void printOption()
{
	printf("1--time\n");
	printf("2--when\n");
	printf("3--cancle\n");
	printf("0--exit\n");
	printf("select the option:");
}

void halt(int time)
{
	char str[50];
	system("shutdown -a >log.txt");
	sprintf(str,"shutdown -s -t %d",time);
	system(str);
	sprintf(str,"echo 'shutdown -s -t %d'>log.txt",time);
	system("pause");	
}

