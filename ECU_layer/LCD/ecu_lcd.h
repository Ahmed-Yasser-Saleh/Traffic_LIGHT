/* 
 * File:   ecu_lcd.h
 * Author: Ahmed Yasser
 *
 * Created on August 21, 2023, 4:47 PM
 */

#ifndef ECU_LCD_H
#define	ECU_LCD_H
/* Section : Includes */
#include "../../MCAL_layer/GPIO/gpio.h"
#include "ecu_lcd_confg.h"

/* Section : Macro Declarations */
/*____ COMMANDS ____*/
#define CLEAR_DISPLAY                                       0x01
#define CURSOR_HOME                                         0x02
#define ENTRY_MODE_SET_INCREMENT_ON_SHIFT_OFF               0x06
#define ENTRY_MODE_SET_DECREMENT_ON_SHIFT_OFF               0x04
#define ENTRY_MODE_SET_INCREMENT_ON_SHIFT_ON                0x07
#define ENTRY_MODE_SET_DECREMENT_ON_SHIFT_ON                0x05
#define DISPLAY_OFF                                         0x08
#define DISPLAY_ON_UNDER_LINE_CURSOR_OFF_BLOCK_CURSOR_OFF   0x0C
#define DISPLAY_ON_UNDER_LINE_CURSOR_ON_BLOCK_CURSOR_OFF    0x0E
#define DISPLAY_ON_UNDER_LINE_CURSOR_ON_BLOCK_CURSOR_ON     0x0F
#define DISPLAY_ON_UNDER_LINE_CURSOR_OFF_BLOCK_CURSOR_ON    0x0D
#define MOVE_CURSOR_OFF_SHIFT_DISPLAY_RIGHT                 0x1C
#define MOVE_CURSOR_OFF_SHIFT_DISPLAY_LEFT                  0x18
#define MOVE_CURSOR_RIGH_SHIFT_DISPLAY_OFF                  0x14
#define MOVE_CURSOR_LEFT_SHIFT_DISPLAY_OFF                  0x10
#define LCD_8BIT_MODE_2_LINE                                0x38
#define LCD_4BIT_MODE_2_LINE                                0x28
#define START_LCD_CGRAM                                     0x40
#define START_LCD_DDRAM                                     0x80
/* Section : Macro Function Declaration */
/* Section : Data Type Declarations */
typedef struct{
    Pin_Config_t rs_lcd;
    Pin_Config_t lcd_pin[8];
    Pin_Config_t en_lcd;
}lcd_confg_8_t;

typedef struct{
    Pin_Config_t rs_lcd;
    Pin_Config_t lcd_pin[4];
    Pin_Config_t en_lcd;
}lcd_confg_4_t;

/* Section : Function Declarations */
Std_ReturnType lcd_pins_4_initialize(const lcd_confg_4_t *lcd);
Std_ReturnType send_4_bit_command(const lcd_confg_4_t *lcd, uint8 command);
Std_ReturnType send_4_bit_char_data(const lcd_confg_4_t *lcd, uint8 data);
Std_ReturnType send_4_bit_char_data_pos(const lcd_confg_4_t *lcd, uint8 row, uint8 column, uint8 data);
Std_ReturnType send_4_bit_string_data(const lcd_confg_4_t *lcd,uint8 *data);
Std_ReturnType send_4_bit_string_data_pos(const lcd_confg_4_t *lcd, uint8 row, uint8 column, uint8 *data);
Std_ReturnType send_4_bit_custome_char_data_pos(const lcd_confg_4_t *lcd, uint8 row, 
                                          uint8 column, uint8 *arr, uint8 mem_pos);

Std_ReturnType lcd_pins_8_initialize(const lcd_confg_8_t *lcd);
Std_ReturnType send_8_bit_command(const lcd_confg_8_t *lcd, uint8 command);
Std_ReturnType send_8_bit_char_data(const lcd_confg_8_t *lcd, uint8 data);
Std_ReturnType send_8_bit_char_data_pos(const lcd_confg_8_t *lcd, uint8 row, uint8 column, uint8 data);
Std_ReturnType send_8_bit_string_data(const lcd_confg_8_t *lcd,uint8 *data);
Std_ReturnType send_8_bit_string_data_pos(const lcd_confg_8_t *lcd, uint8 row, uint8 column, uint8 *data);
Std_ReturnType send_8_bit_custome_char_data_pos(const lcd_confg_8_t *lcd, uint8 row, 
                                          uint8 column, uint8 *arr, uint8 mem_pos);


Std_ReturnType cnvert_uint8_to_string(uint8 value, uint8 *ptr);
Std_ReturnType cnvert_uint16_to_string(uint16 value, uint8 *ptr);
Std_ReturnType cnvert_uint32_to_string(uint32 value, uint8 *ptr);
#endif	/* ECU_LCD_H */

