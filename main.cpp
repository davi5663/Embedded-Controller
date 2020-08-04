#include "Grove_LCD_RGB_Backlight.h" //Libary for LCD Backligt
#include "mbed.h"
#include "stm32746g_discovery_lcd.h" //Libary for TouchScreen

DigitalOut myblueled(D3);
DigitalOut myredled(D2);
DigitalIn mybutton(D4);
Grove_LCD_RGB_Backlight mylcd(D14, D15);
DigitalIn mytouchsensor(D8);
/*DigitalOut mylightsensor (D2);*/
Thread t;    // Creates Thread, threads can run more then one project at a time without intterupting each other.
int num = 0; // Declares the number

void Numbercounter() {
  while (1) {
    char maxlength[20];                       // How long the character can be
    sprintf(maxlength, "Number is: %d", num); //%d helps to print the integer, format string for char array is what sprintf is used for
    mylcd.clear();
    mylcd.print(maxlength);
    num++; // Counts up the number
    ThisThread::sleep_for(1000);
  }
}

int main() {
  printf("Program started...");

  mylcd.setRGB(0xff, 0xff, 0xff);
  // mylcd.print("We drive fast cars!");
  BSP_LCD_Init();
  BSP_LCD_LayerDefaultInit(LTDC_ACTIVE_LAYER, LCD_FB_START_ADDRESS);
  BSP_LCD_SelectLayer(LTDC_ACTIVE_LAYER);
  BSP_LCD_Clear(LCD_COLOR_BLACK);
  BSP_LCD_SetFont(&LCD_DEFAULT_FONT);
  BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
  BSP_LCD_DisplayStringAt(
      0, 0, (uint8_t *)"WELCOME TO MY PROJECT!",
      CENTER_MODE); // The first number 0 goes more to the right direction
  BSP_LCD_DisplayStringAt(0, 50, (uint8_t *)"MY NAME IS DAVID",
                          CENTER_MODE); // 50 goes more down
  HAL_Delay(1000);
  t.start(&Numbercounter);
  while (1) {
    if (mybutton == 1) {
      while (1) {

        if (mytouchsensor == 1) {
          mylcd.clear();
          mylcd.print("Reseting...");
          ThisThread::sleep_for(100);
          num = 0;
        }

        if (mybutton == 1) {
          // num = 0;
          BSP_LCD_Clear(LCD_COLOR_WHITE);
          BSP_LCD_DisplayStringAt(0, LINE(4), (uint8_t *)"PRESSING BUTTON", CENTER_MODE);
          myblueled = 1;
          myredled = 1;
          ThisThread::sleep_for(100); // Wait in miliseconds, this is 0.1 second
          myblueled = 0;
          myredled = 0;
          ThisThread::sleep_for(50);
          /*mylightsensor =1;*/
          /*mySensor = 1; */
        }

        else if (mybutton == 0) {
          myblueled = 0;
          myredled = 0;
          BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
          BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
          /* BSP_LCD_DrawRect(BSP_LCD_GetXSize()/2, BSP_LCD_GetYSize()/2, 40,* 50);*/ //Tried to create a rectangle as a button to reset my Counter
          BSP_LCD_ClearStringLine(4); // Clears string number 4 which is line 30
          BSP_LCD_DisplayStringAt(0, 1, (uint8_t *)"NOT PRESSING THE BUTTON",CENTER_MODE);
          /*mylightsensor = 0;*/
          /* mySensor = 0;*/
        }
      }
    }
  }
}
