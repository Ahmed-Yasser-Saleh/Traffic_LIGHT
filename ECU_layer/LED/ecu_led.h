/* 
 * File:   ecu_led.h
 * Author: Ahmed Yasser
 *
 * Created on July 16, 2023, 6:41 AM
 */

#ifndef ECU_LED_H
#define	ECU_LED_H

/* Section : Includes */
#include "../../MCAL_layer/GPIO/gpio.h"
#include "ecu_led_confg.h"

/* Section : Macro Declarations    */
/* Section : Macro Function Declaration */
/* Section : Data Type Declarations */
typedef enum {
    LED_OFF,
    LED_ON
}led_st_t;

typedef struct{
    uint8 port   : 4;
    uint8 pin    : 3;
    uint8 led_st : 1;
}led_confg_t;


/* Section : Function Declarations */
Std_ReturnType Led_initialize(const led_confg_t *led);
Std_ReturnType Led_Turn_On(const led_confg_t *led);
Std_ReturnType Led_Turn_Off(const led_confg_t *led);
Std_ReturnType Led_Toggle(const led_confg_t *led);
#endif	/* ECU_LED_H */

