/* 
 * File:   ecu_led.c
 * Author: Ahmed Yasser
 *
 * Created on July 16, 2023, 6:41 AM
 */

/* Section : Includes */
#include "ecu_led.h"

/* Section : Macro Declarations */

/* Section : Macro Function Declaration */
/* Section : Data Type Declarations */
/* Section : Function Declarations */
Std_ReturnType Led_initialize(const led_confg_t *led){
        Std_ReturnType ret = E_OK;
    if(NULL == led)
        ret = E_NOT_OK;
    else
    {
     Pin_Config_t led_pin = {led->port, led->pin, OUTPUT, led->led_st};
     gpio_pin_intialize(&led_pin);
    }
        return ret;
}
Std_ReturnType Led_Turn_On(const led_confg_t *led){
        Std_ReturnType ret = E_OK;
    if(NULL == led  )
        ret = E_NOT_OK;
    else
    {
     Pin_Config_t led_pin = {led->port, led->pin, OUTPUT, led->led_st};
     gpio_pin_write_logic(&led_pin, HIGH);
    }
        return ret;
}
Std_ReturnType Led_Turn_Off(const led_confg_t *led){
        Std_ReturnType ret = E_OK;
    if(NULL == led )
        ret = E_NOT_OK;
    else
    {
     Pin_Config_t led_pin = {led->port, led->pin, OUTPUT, led->led_st};
     gpio_pin_write_logic(&led_pin, LOW);
       
    }
        return ret;
}
Std_ReturnType Led_Toggle(const led_confg_t *led){
       Std_ReturnType ret = E_OK;
    if(NULL == led)
        ret = E_NOT_OK;
    else
    {
     Pin_Config_t led_pin = {led->port, led->pin, OUTPUT, led->led_st};
     gpio_pin_toggle_logic(&led_pin); 
    }
        return ret; 
}