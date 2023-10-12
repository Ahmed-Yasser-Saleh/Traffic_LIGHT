/* 
 * File:   ecu_7_segment.h
 * Author: Ahmed Yasser
 *
 * Created on August 8, 2023, 10:44 PM
 */

#ifndef ECU_7_SEGMENT_H
#define	ECU_7_SEGMENT_H

/* Section : Includes */
#include "ecu_7_segment_confg.h"
#include "../../MCAL_layer/GPIO/gpio.h"

/* Section : Macro Declarations    */
#define SEGMENT_INPUT_1     0
#define SEGMENT_INPUT_2     1
#define SEGMENT_INPUT_3     2
#define SEGMENT_INPUT_4     3
/* Section : Macro Function Declaration */
/* Section : Data Type Declarations */
typedef enum{
    COMMON_CATHODE,
    COMMON_ANODE        
}sev_segment_st_t;

typedef struct {
  Pin_Config_t segment_pin[4];
  sev_segment_st_t segment_st;
}segment_confg_t;

/* Section : Function Declarations */
Std_ReturnType segment_pin_initialize(const segment_confg_t *segment);
Std_ReturnType segment_write_number(const segment_confg_t *segment, uint8 num);
#endif	/* ECU_7_SEGMENT_H */

