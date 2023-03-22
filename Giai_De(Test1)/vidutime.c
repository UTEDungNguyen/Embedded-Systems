#include <stdio.h>
#include <time.h>

#define VNA (+7)
#define CCT (+8)

int main ()
{

   time_t rawtime;
   struct tm *info;

   time(&rawtime);
   /* Get GMT time */
   info = gmtime(&rawtime );
   
   printf("Thời gian hiện tại:\n");
   printf("Tại VNAM: %2d:%02d\n", (info->tm_hour+VNA)%24, info->tm_min);
   printf("Tại Trung Quốc: %2d:%02d\n", (info->tm_hour+CCT)%24, info->tm_min);

   return(0);
}