/* 
 * File:   7_segment.c
 * Author: Ahmed Yasser
 *
 * Created on August 8, 2023, 10:37 PM
 */

/* Section : Includes */
#include "ecu_7_segment.h"
/* Section : Macro Declarations    */
/* Section : Macro Function Declaration */
/* Section : Data Type Declarations */
/* Section : Function Declarations */

Std_ReturnType segment_pin_initialize(const segment_confg_t *segment){
    Std_ReturnType ret = E_OK;
    if(NULL == segment)
        ret = E_NOT_OK;
    else{
        gpio_pin_intialize(&(segment->segment_pin[SEGMENT_INPUT_1]));
        gpio_pin_intialize(&(segment->segment_pin[SEGMENT_INPUT_2]));
        gpio_pin_intialize(&(segment->segment_pin[SEGMENT_INPUT_3]));
        gpio_pin_intialize(&(segment->segment_pin[SEGMENT_INPUT_4]));
    }
    return ret;
    
}
Std_ReturnType segment_write_number(const segment_confg_t *segment, uint8 num){
     Std_ReturnType ret = E_OK;
    /* uint8 val_pin_1 = ((num % 2)) ? 1 : 0;
     uint8 val_pin_2 = (((num / 2) % 2) ? 1 : 0);
     uint8 val_pin_3 = (((num / 4) % 2) ? 1 : 0);
     uint8 val_pin_4 = (((num / 8) % 2) ? 1 : 0); 
     OR
     */
    if(NULL == segment)
        ret = E_NOT_OK;
    else {
        /* gpio_pin_write_logic(&(segment->segment_pin[SEGMENT_INPUT_1]), val_pin_1);
        gpio_pin_write_logic(&(segment->segment_pin[SEGMENT_INPUT_2]), val_pin_2);
        gpio_pin_write_logic(&(segment->segment_pin[SEGMENT_INPUT_3]), val_pin_3);
        gpio_pin_write_logic(&(segment->segment_pin[SEGMENT_INPUT_4]), val_pin_4);
         OR */
        gpio_pin_write_logic(&(segment->segment_pin[SEGMENT_INPUT_1]), num & 1); //note result is the status of first bit
        gpio_pin_write_logic(&(segment->segment_pin[SEGMENT_INPUT_2]), (num >> 1) & 1);
        gpio_pin_write_logic(&(segment->segment_pin[SEGMENT_INPUT_3]), (num >> 2) & 1);
        gpio_pin_write_logic(&(segment->segment_pin[SEGMENT_INPUT_4]), (num >> 3) & 1);
    }
     return ret;
    
}