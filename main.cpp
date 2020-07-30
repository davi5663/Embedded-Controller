#include "mbed.h"
#include "stm32746g_discovery_lcd.h"
#include "Grove_LCD_RGB_Backlight.h"


DigitalOut myblueled(D3);
DigitalOut myredled (D2);
DigitalIn mybutton (D4);
Grove_LCD_RGB_Backlight mylcd(D15, D14);
/*DigitalOut mylightsensor (D2);*/
/*DigitalOut mySensor(D2); */

int main() {  
      
        
    mylcd.setRGB(0xff,0xff, 0xff);
    BSP_LCD_Init();
    BSP_LCD_LayerDefaultInit(LTDC_ACTIVE_LAYER, LCD_FB_START_ADDRESS);
    BSP_LCD_SelectLayer(LTDC_ACTIVE_LAYER);
    BSP_LCD_Clear(LCD_COLOR_BLACK);
    BSP_LCD_SetFont(&LCD_DEFAULT_FONT);
    BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
    BSP_LCD_DisplayStringAt(0, 1, (uint8_t *)"DAVID", CENTER_MODE);
    HAL_Delay(1000);
    
     while(1)
    {    
   
        if (mybutton == 1)
        {
            BSP_LCD_Clear(LCD_COLOR_WHITE);
            BSP_LCD_DisplayStringAt(0, LINE(4), (uint8_t *)"PRESSING BUTTON", CENTER_MODE);                     
            myblueled = 1;
            myredled = 1;
            ThisThread::sleep_for(100); //Wait in miliseconds, this is 0.1 second
            myblueled = 0;
            myredled = 0;
            ThisThread::sleep_for(50);
            /*mylightsensor =1;*/
            /*mySensor = 1; */
        }
            
            else if (mybutton == 0)
            { 
                myblueled = 0;
                myredled = 0;
                BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
                BSP_LCD_ClearStringLine(4); //Clears string number 4 which is line 30
                BSP_LCD_DisplayStringAt(0, 1, (uint8_t *)"NOT PRESSING THE BUTTON", CENTER_MODE);
                /*mylightsensor = 0;*/
                /* mySensor = 0;*/
            }  
    }
        


}
