/* 
 * File:   gpio.c
 * Author: Ahmed Yasser
 *
 * Created on July 16, 2023, 5:45 AM
 */
/* Section : Includes */
#include "gpio.h"

/* Section : Macro Declarations */

/* Section : Macro Function Declaration */
/* Section : Data Type Declarations */
/* Section : Function Declarations */

/* REFERENC TO THE DATA DIRECTION CONTROL REGISTER */
volatile uint8 *tris_reg[]= {&TRISA, &TRISB, &TRISC, &TRISD, &TRISE};

/* REFERENC TO THE DATA LATCH REGISTER */
volatile uint8 *lat_reg[]= {&LATA, &LATB, &LATC, &LATD, &LATE};

/* REFERENC TO THE PORT STATUS REGISTER */
volatile uint8 *port_reg[]= {&PORTA, &PORTB, &PORTC, &PORTD, &PORTE};

/**
 * @breif initialize direction of specific pin 
 * @param Pin_Config : pointer to the configuration
 * @return 
 */
#if (PORT_PIN_CONFIG == CONFIG_ENABLE)
Std_ReturnType gpio_pin_direction_intialize (const Pin_Config_t *Pin_Config){
    Std_ReturnType ret = E_OK;
    if(NULL == Pin_Config || Pin_Config->pin > PORT_PIN_MAX_NUMBER)
        ret = E_NOT_OK;
    else
    {
        if(Pin_Config->direction == OUTPUT) 
            CLEAR_BIT(*tris_reg[Pin_Config->port], Pin_Config->pin);
        else if
            SET_BIT((*tris_reg[Pin_Config->port]), (Pin_Config->pin));  
        else ret = E_NOT_OK;
    }
        return ret;
}
#endif
/**
 * @breif Read status direction of specific pin
 * @param Pin_Config : pointer to the configuration
 * @param direction_status
 * @return status of function
 *           E_OK : the function done successfully
 *           E_NOT_OK : the function has issue to perform this action
 */
#if (PORT_PIN_CONFIG == CONFIG_ENABLE)
Std_ReturnType gpio_pin_direction_status (const Pin_Config_t *Pin_Config,Direction_t *direction_status){
      Std_ReturnType ret = E_OK;
    if(NULL == Pin_Config || NULL == direction_status || Pin_Config->pin > PORT_PIN_MAX_NUMBER)
        ret = E_NOT_OK;
    else
    {
        *direction_status = READ_BIT(*tris_reg[Pin_Config->port], Pin_Config->pin);
    }
        return ret;
}
#endif
/**
 * @breif Write logic value on specific pin
 * @param Pin_Config : pointer to the configuration
 * @param logic
 * @return status of function
 *           E_OK : the function done successfully
 *           E_NOT_OK : the function has issue to perform this action
 */
#if (PORT_PIN_CONFIG == CONFIG_ENABLE)
Std_ReturnType gpio_pin_write_logic (const Pin_Config_t *Pin_Config, Logic_t logic){
     Std_ReturnType ret = E_OK;
    if(NULL == Pin_Config || Pin_Config->pin > PORT_PIN_MAX_NUMBER)
        ret = E_NOT_OK;
    else
    {
        if(logic == HIGH) 
            SET_BIT(*lat_reg[Pin_Config->port],Pin_Config->pin);
        else if
            CLEAR_BIT(*lat_reg[Pin_Config->port],Pin_Config->pin);  
        else ret = E_NOT_OK;
    }
        return ret;
}
#endif
/**
 * @breif Read logic value on specific pin
 * @param Pin_Config : pointer to the configuration
 * @param logic
 * @return status of function
 *           E_OK : the function done successfully
 *           E_NOT_OK : the function has issue to perform this action
 */
#if (PORT_PIN_CONFIG == CONFIG_ENABLE)
       Std_ReturnType gpio_pin_read_logic (const Pin_Config_t *Pin_Config, Logic_t *logic){
       Std_ReturnType ret = E_OK;
    if(NULL == Pin_Config || Pin_Config->pin > PORT_PIN_MAX_NUMBER)
        ret = E_NOT_OK;
    else
    {
        *logic = READ_BIT(*port_reg[Pin_Config->port], Pin_Config->pin);
    }
        return ret;
}
/**
 * @breif Toggle logic value on specific pin
 * @param Pin_Config : pointer to the configuration
 * @return status of function
 *           E_OK : the function done successfully
 *           E_NOT_OK : the function has issue to perform this action
 */
Std_ReturnType gpio_pin_toggle_logic (const Pin_Config_t *Pin_Config){
        Std_ReturnType ret = E_OK;
    if(NULL == Pin_Config || Pin_Config->pin > PORT_PIN_MAX_NUMBER)
        ret = E_NOT_OK;
    else
    {
        TOGGLE_BIT(*lat_reg[Pin_Config->port],Pin_Config->pin);
    }
        return ret;
    
}
#endif
/**
 * @breif detect direction of pin && write default logic value (from struct) on pin
 * @param Pin_Config : pointer to the configuration
 * @return status of function
 *           E_OK : the function done successfully
 *           E_NOT_OK : the function has issue to perform this action
 */
#if (PORT_PIN_CONFIG == CONFIG_ENABLE)
Std_ReturnType gpio_pin_intialize (const Pin_Config_t *Pin_Config){
      Std_ReturnType ret = E_OK;
    if(NULL == Pin_Config || Pin_Config->pin > PORT_PIN_MAX_NUMBER)
        ret = E_NOT_OK;
    else
    {
       ret = gpio_pin_direction_intialize(Pin_Config);
       ret = gpio_pin_write_logic(Pin_Config,Pin_Config->logic);
       
    }
        return ret;
}
#endif
/**
 * 
 * @param port
 * @return status of function
 *           E_OK : the function done successfully
 *           E_NOT_OK : the function has issue to perform this action
 */
#if (PORT_CONFIG == CONFIG_ENABLE)
Std_ReturnType gpio_port_direction_intialize (Port_Index_t port, Std_ReturnType direction){
        Std_ReturnType ret = E_OK;
    if(port > PORT_MAX_NUMBER - 1)
        ret = E_NOT_OK;
    else
    {
       *tris_reg[port] = direction;
    }
        return ret;
}
#endif
/**
 * 
 * @param port
 * @param direction_status
 * @return status of function
 *           E_OK : the function done successfully
 *           E_NOT_OK : the function has issue to perform this action
 */
#if (PORT_CONFIG == CONFIG_ENABLE)
Std_ReturnType gpio_port_direction_status (Port_Index_t port, Std_ReturnType *direction_status){
    Std_ReturnType ret = E_OK;
    if(NULL == direction_status || port > PORT_MAX_NUMBER - 1)
        ret = E_NOT_OK;
    else
    {
        *direction_status = *tris_reg[port];
    }
        return ret;
}
#endif
/**
 * 
 * @param port
 * @param logic
 * @return status of function
 *           E_OK : the function done successfully
 *           E_NOT_OK : the function has issue to perform this action
 */
#if (PORT_CONFIG == CONFIG_ENABLE)
Std_ReturnType gpio_port_write_logic (Port_Index_t port, Std_ReturnType logic){
    Std_ReturnType ret = E_OK;
    if(port > PORT_MAX_NUMBER - 1)
        ret = E_NOT_OK;
    else
    {
       *lat_reg[port] = logic;
    }
        return ret;
}
#endif
/**
 * 
 * @param port
 * @param logic
 * @return status of function
 *           E_OK : the function done successfully
 *           E_NOT_OK : the function has issue to perform this action
 */
#if (PORT_PIN_CONFIG == CONFIG_ENABLE)
Std_ReturnType gpio_port_read_logic (Port_Index_t port, Std_ReturnType *logic){
    Std_ReturnType ret = E_OK;
    if( NULL == logic || port > PORT_MAX_NUMBER - 1)
        ret = E_NOT_OK;
    else
    {
       *logic= *port_reg[port];
    }
        return ret;
}
#endif
/**
 * 
 * @param port
 * @param logic
 * @return status of function
 *           E_OK : the function done successfully
 *           E_NOT_OK : the function has issue to perform this action
 */
#if (PORT_PIN_CONFIG == CONFIG_ENABLE)
Std_ReturnType gpio_port_toggle_logic (Port_Index_t port){
    Std_ReturnType ret = E_OK;
    if(port > PORT_MAX_NUMBER - 1)
        ret = E_NOT_OK;
    else
    {
        *lat_reg[port] ^= PORT_MASK;
    }
        return ret;
}
#endif
