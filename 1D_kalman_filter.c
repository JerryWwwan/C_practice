#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>


#define     Forecast_Noise   1
#define     Measure_Noise    10
float Best_Error = 0; 
float Kalman_Gain; 
float Forecast_Value = 0; 
float Forecast_Error;
float Kalman_Filter(float Best_Value);

float Kalman_Filter(float Best_Value){

    if(Forecast_Value == 0) Forecast_Value = Best_Value;
    Forecast_Error = sqrt(pow(Forecast_Noise,2)+pow(Best_Error,2));
    Kalman_Gain = sqrt(pow(Forecast_Error,2)/(pow(Forecast_Error,2)+pow(Measure_Noise,2)));
    Best_Value = Forecast_Value + Kalman_Gain * ( Best_Value - Forecast_Value);
    Best_Error = sqrt((1-Kalman_Gain)*pow(Forecast_Error,2));
    Forecast_Value = Best_Value;
    printf("KG=%f,",Kalman_Gain);
    return Best_Value;
}
int main(void)
{
    int i;
    float temp = 25;
    float noise;
    float report_temp;
    float filter_temp;

    while (1)
    {
        i += rand()%2;
        // temp += 0.2;
        if(temp >= 100) temp=100;
        noise =  ( i & 1)?rand()%3:rand()%10;
        report_temp = ( i & 1)?temp-noise:temp+noise;
        filter_temp = Kalman_Filter(report_temp);
        printf("real:%f,repot:%f,filter:%f\n",temp,report_temp,filter_temp);
        sleep(1);
    }
    
   
    
    return 0;
}