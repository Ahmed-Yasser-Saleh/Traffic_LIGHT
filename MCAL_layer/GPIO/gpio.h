/* 
 * File:   gpio.h
 * Author: Ahmed Yasser
 *
 * Created on July 16, 2023, 6:07 AM
 */

#ifndef GPIO_H
#define	GPIO_H

/* Section : Includes */
#include "../mcal_std_types.h"
#include <../proc/pic18f4620.h>
#include "../device_config.h"
#include "gpio_config.h"

/* Section : Macro Declarations */
#define BIT_MASK             (uint8)1
#define PORT_MASK             0xff
#define PORT_PIN_MAX_NUMBER     8
#define PORT_MAX_NUMBER         5
#define PORT_PIN_CONFIG     CONFIG_ENABLE
#define PORT_CONFIG         CONFIG_ENABLE
/* Section : Macro Function Declaration */
#define HWREG8(_X)     (*((vloatile uint8 *)(_X)))

#define SET_BIT(REG,POS_BIT)      (REG |= (BIT_MASK << POS_BIT))
#define CLEAR_BIT(REG,POS_BIT)    (REG &= ~(BIT_MASK << POS_BIT))
#define TOGGLE_BIT(REG,POS_BIT)   (REG ^= (BIT_MASK << POS_BIT))
#define READ_BIT(REG,POS_BIT)     (REG >> POS_BIT & BIT_MASK)
/* Section : Data Type Declarations */
typedef enum {
    LOW,
    HIGH        
}Logic_t;

typedef enum {
    OUTPUT,
    INPUT        
}Direction_t;

typedef enum {
    PIN0,
    PIN1,
    PIN2,
    PIN3,
    PIN4,
    PIN5,
    PIN6,
    PIN7
}Pin_Index_t;

typedef enum {
    PORTA_INDEX,
    PORTB_INDEX,
    PORTC_INDEX,
    PORTD_INDEX,
    PORTE_INDEX        
}Port_Index_t;

typedef struct{
  uint8 port      :  3; /* @ref  Port_Index_t */
  uint8 pin       :  3; /* @ref  Pin_Index_t  */
  uint8 direction :  1; /* @ref  Direction_t  */
  uint8 logic     :  1; /* @ref  Logic_t      */
}Pin_Config_t;

/* Section : Function Declarations */
Std_ReturnType gpio_pin_direction_intialize (const Pin_Config_t *Pin_Config);
Std_ReturnType gpio_pin_direction_status (const Pin_Config_t *Pin_Config,Direction_t *direction_status);
Std_ReturnType gpio_pin_write_logic (const Pin_Config_t *Pin_Config, Logic_t logic);
Std_ReturnType gpio_pin_read_logic (const Pin_Config_t *Pin_Config, Logic_t *logic);
Std_ReturnType gpio_pin_toggle_logic (const Pin_Config_t *Pin_Config);
Std_ReturnType gpio_pin_intialize (const Pin_Config_t *Pin_Config);

Std_ReturnType gpio_port_direction_intialize (Port_Index_t port, Std_ReturnType direction);
Std_ReturnType gpio_port_direction_status (Port_Index_t port, Std_ReturnType *direction_status);
Std_ReturnType gpio_port_write_logic (Port_Index_t port, Std_ReturnType logic);
Std_ReturnType gpio_port_read_logic (Port_Index_t port, Std_ReturnType *logic);
Std_ReturnType gpio_port_toggle_logic (Port_Index_t port);
#endif	/* GPIO_H */

