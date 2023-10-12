/* 
 * File:   Traffic_Light.c
 * Author: Ahmed Yasser
 *
 * Created on October 12, 2023, 12:54 PM
 */

#include "Trrafic_Light.h"

led_confg_t led_green = {PORTA_INDEX, PIN0, LED_OFF};
led_confg_t led_yellow = {PORTA_INDEX, PIN1, LED_OFF};
led_confg_t led_red = {PORTA_INDEX, PIN2, LED_OFF};  

segment_confg_t segment_1 =
{
  .segment_pin[0].port = PORTC_INDEX,
  .segment_pin[0].pin  = PIN0,
  .segment_pin[0].direction = OUTPUT,
  .segment_pin[0].logic = LOW,
  .segment_pin[1].port = PORTC_INDEX,
  .segment_pin[1].pin = PIN1,
  .segment_pin[1].direction = OUTPUT,
  .segment_pin[1].logic = LOW,
  .segment_pin[2].port = PORTC_INDEX,
  .segment_pin[2].pin  = PIN2,
  .segment_pin[2].direction = OUTPUT,
  .segment_pin[2].logic = LOW,
  .segment_pin[3].port = PORTC_INDEX,
  .segment_pin[3].pin = PIN3,
  .segment_pin[3].direction = OUTPUT,
  .segment_pin[3].logic = LOW,    
  .segment_st = COMMON_CATHODE    
}; 

Pin_Config_t segment_enable_1 =
{
 .port = PORTD_INDEX,
 .pin  = PIN0,
 .direction = OUTPUT,
 .logic = HIGH,
};

Pin_Config_t segment_enable_2 =
{
 .port = PORTD_INDEX,
 .pin  = PIN1,
 .direction = OUTPUT,
 .logic = HIGH,
};

lcd_confg_4_t lcd_4bit = {
      .rs_lcd.port = PORTD_INDEX,
      .rs_lcd.pin  = PIN2,
      .rs_lcd.direction = OUTPUT,
      .rs_lcd.logic     = LOW,
      .en_lcd.port = PORTD_INDEX,
      .en_lcd.pin = PIN3,
      .en_lcd.direction = OUTPUT,
      .en_lcd.logic = LOW,
      .lcd_pin[0].port = PORTD_INDEX,
      .lcd_pin[0].pin = PIN4,
      .lcd_pin[0].direction = OUTPUT,
      .lcd_pin[0].logic = LOW,
      .lcd_pin[1].port = PORTD_INDEX,
      .lcd_pin[1].pin  = PIN5,
      .lcd_pin[1].direction = OUTPUT,
      .lcd_pin[1].logic = LOW,
      .lcd_pin[2].port = PORTD_INDEX,
      .lcd_pin[2].pin = PIN6,
      .lcd_pin[2].direction = OUTPUT,
      .lcd_pin[2].logic = LOW,
      .lcd_pin[3].port = PORTD_INDEX,
      .lcd_pin[3].pin  = PIN7,
      .lcd_pin[3].direction = OUTPUT,
      .lcd_pin[3].logic = LOW,
   };
  
uint8 x = 0;
uint8 t_delay = 0;
int main() {
    Std_ReturnType ret = E_NOT_OK;
    application_initialize();
     while(1){
         uint8 R = 30;
         uint8 G = 30;
         uint8 Y = 5;
        if(0 == x)
        {
           for(signed char i = R; i>=0; i--){
                Led_Turn_Off(&led_green);
                Led_Turn_On(&led_red);
                send_4_bit_string_data_pos(&lcd_4bit,2,8,"STOP");
                for(t_delay = 0; t_delay <= 50; t_delay++)
                   {   
                       segment_write_number(&segment_1,(R % 10));
                       gpio_pin_write_logic(&segment_enable_2,LOW);
                       __delay_ms(10);
                       gpio_pin_write_logic(&segment_enable_2,HIGH);
               
                       segment_write_number(&segment_1,(R / 10));
                       gpio_pin_write_logic(&segment_enable_1,LOW);
                       __delay_ms(10);
                       gpio_pin_write_logic(&segment_enable_1,HIGH);
                    }
                R--;
         } 
            x = 1;
        }
        else if(1 == x)
        { 
           for(signed char i = Y; i>=0; i--){
                Led_Turn_Off(&led_red);
                Led_Turn_On(&led_yellow);
                send_4_bit_string_data_pos(&lcd_4bit,2,8,"READY!!");
                for(t_delay = 0; t_delay <= 50; t_delay++)
                   {   
                       segment_write_number(&segment_1,(Y % 10));
                       gpio_pin_write_logic(&segment_enable_2,LOW);
                       __delay_ms(10);
                       gpio_pin_write_logic(&segment_enable_2,HIGH);
                
                       segment_write_number(&segment_1,(Y / 10));
                       gpio_pin_write_logic(&segment_enable_1,LOW);
                       __delay_ms(10);
                       gpio_pin_write_logic(&segment_enable_1,HIGH);
                   }
                Y--;
         }
           x = 2;
        }
        else if(2 == x)
        {
           for(signed char i = G; i>=0; i--){ 
                Led_Turn_Off(&led_yellow);
                Led_Turn_On(&led_green);
                send_4_bit_string_data_pos(&lcd_4bit,2,8," GO    "); 
                for(t_delay = 0; t_delay <= 50; t_delay++)
                   {   
                       segment_write_number(&segment_1,(G % 10));
                       gpio_pin_write_logic(&segment_enable_2,LOW);
                       __delay_ms(10);
                       gpio_pin_write_logic(&segment_enable_2,HIGH);
               
                       segment_write_number(&segment_1,(G / 10));
                       gpio_pin_write_logic(&segment_enable_1,LOW);
                       __delay_ms(10);
                       gpio_pin_write_logic(&segment_enable_1,HIGH);
                    }
                G--;
         } 
            x = 0; 
        }
        else{}
     }
      return (EXIT_SUCCESS);
}


void application_initialize(void){
    
    lcd_pins_4_initialize(&lcd_4bit);
    segment_pin_initialize(&segment_1);
    Led_initialize(&led_green);
    Led_initialize(&led_yellow);
    Led_initialize(&led_red);
    gpio_pin_direction_intialize(&segment_enable_1);
    gpio_pin_direction_intialize(&segment_enable_2);
}
