/* 
 * File:   ecu_lcd.c
 * Author: Ahmed Yasser
 *
 * Created on August 21, 2023, 4:47 PM
 */

/* Section : Includes */
#include "ecu_lcd.h"
/* Section : Macro Declarations */
#define _XTAL_FREQ 4000000UL
/* Section : Macro Function Declaration */
/* Section : Data Type Declarations */
/* Section : Function Declarations */
static Std_ReturnType send_4_bit_help(const lcd_confg_4_t *lcd, uint8 command);
static Std_ReturnType lcd_4_bit_set_cursor(const lcd_confg_4_t *lcd, uint8 row, uint8 column);
static Std_ReturnType send_4_bit_enable(const lcd_confg_4_t *lcd);
static Std_ReturnType send_8_bit_enable(const lcd_confg_8_t *lcd);
static Std_ReturnType lcd_8_bit_set_cursor(const lcd_confg_8_t *lcd,uint8 row,uint8 column);

Std_ReturnType lcd_pins_4_initialize(const lcd_confg_4_t *lcd){
             Std_ReturnType ret = E_OK;
    if(NULL == lcd)
        ret = E_NOT_OK;
    else
    {
        ret = gpio_pin_intialize(&(lcd->rs_lcd));
        ret = gpio_pin_intialize(&(lcd->en_lcd));
        for(uint8 cnt_pin = 0; cnt_pin < 4; cnt_pin++)
          ret = gpio_pin_intialize(&(lcd->lcd_pin[cnt_pin]));
        
        __delay_ms(20);
        ret = send_4_bit_command(lcd, LCD_8BIT_MODE_2_LINE);
        __delay_ms(5);
        ret = send_4_bit_command(lcd, LCD_8BIT_MODE_2_LINE);
        __delay_us(150);
        ret = send_4_bit_command(lcd, LCD_8BIT_MODE_2_LINE);
        ret = send_4_bit_command(lcd, CLEAR_DISPLAY);
        ret = send_4_bit_command(lcd, CURSOR_HOME);
        ret = send_4_bit_command(lcd, ENTRY_MODE_SET_INCREMENT_ON_SHIFT_OFF);
        ret = send_4_bit_command(lcd, DISPLAY_ON_UNDER_LINE_CURSOR_OFF_BLOCK_CURSOR_OFF);
        ret = send_4_bit_command(lcd, LCD_4BIT_MODE_2_LINE);
        send_4_bit_command(lcd, 0x80); //option  == send_8_bit_command(lcd, CURSOR_HOME);
    }
        return ret; 
}
Std_ReturnType send_4_bit_command(const lcd_confg_4_t *lcd, uint8 command){
             Std_ReturnType ret = E_OK;
    if(NULL == lcd)
        ret = E_NOT_OK;
    else
    {
        ret = gpio_pin_write_logic(&(lcd->rs_lcd),LOW);
        ret = send_4_bit_help(lcd,command >> 4);
        ret = send_4_bit_enable(lcd);
        ret = send_4_bit_help(lcd,command);
        ret = send_4_bit_enable(lcd);
    }
             return ret;
}
Std_ReturnType send_4_bit_char_data(const lcd_confg_4_t *lcd, uint8 data){
               Std_ReturnType ret = E_OK;
    if(NULL == lcd)
        ret = E_NOT_OK;
    else
    {
        ret = gpio_pin_write_logic(&(lcd->rs_lcd),HIGH);
        ret = send_4_bit_help(lcd,data >> 4);
        ret = send_4_bit_enable(lcd);
        ret = send_4_bit_help(lcd,data);
        ret = send_4_bit_enable(lcd);
    }
             return ret;
}
static Std_ReturnType send_4_bit_enable(const lcd_confg_4_t *lcd){
                    Std_ReturnType ret = E_OK;
    if(NULL == lcd)
        ret = E_NOT_OK;
    else
    {
        ret = gpio_pin_write_logic(&(lcd->en_lcd),HIGH);
        __delay_us(5);
        ret = gpio_pin_write_logic(&(lcd->en_lcd),LOW);
    }
        return ret;
}
Std_ReturnType send_4_bit_char_data_pos(const lcd_confg_4_t *lcd, uint8 row, uint8 column, uint8 data){
                   Std_ReturnType ret = E_OK;              
    if(NULL == lcd)
        ret = E_NOT_OK;
    else
    {
        ret = lcd_4_bit_set_cursor(lcd,row,column);
        ret = send_4_bit_char_data(lcd, data);
    }
        return ret;  
}
Std_ReturnType send_4_bit_string_data(const lcd_confg_4_t *lcd,uint8 *data){
                        Std_ReturnType ret = E_OK;
                 
    if(NULL == lcd)
        ret = E_NOT_OK;
    else
    {
      while(*data){
          ret = send_4_bit_char_data(lcd,*data++);
      }        
    }
        return ret;  
}
Std_ReturnType send_4_bit_string_data_pos(const lcd_confg_4_t *lcd, uint8 row, uint8 column, uint8 *data){
                       Std_ReturnType ret = E_OK;
                 
    if(NULL == lcd)
        ret = E_NOT_OK;
    else
    {
        ret = lcd_4_bit_set_cursor(lcd,row,column);
      while(*data){
          ret = send_4_bit_char_data(lcd,*data++);
      }        
    }
        return ret; 
}
static Std_ReturnType send_4_bit_help(const lcd_confg_4_t *lcd, uint8 data_command){
               Std_ReturnType ret = E_OK;
    if(NULL == lcd)
        ret = E_NOT_OK;
    else
    {
           ret = gpio_pin_write_logic(&(lcd->lcd_pin[0]),((data_command >> 0)& (uint8)0x01));
           ret = gpio_pin_write_logic(&(lcd->lcd_pin[1]),((data_command >> 1)& (uint8)0x01));
           ret = gpio_pin_write_logic(&(lcd->lcd_pin[2]),((data_command >> 2)& (uint8)0x01));
           ret = gpio_pin_write_logic(&(lcd->lcd_pin[3]),((data_command >> 3)& (uint8)0x01));  
    }
             return ret;
}

static Std_ReturnType lcd_4_bit_set_cursor(const lcd_confg_4_t *lcd, uint8 row, uint8 column){
                    Std_ReturnType ret = E_OK;
                 column--;
    if(NULL == lcd)
        ret = E_NOT_OK;
    else
    {
        if(row == 1)
        {
            ret = send_4_bit_command(lcd,(0x80 + column));
        }
        else if(row == 2)
        {
            ret = send_4_bit_command(lcd,(0xC0 + column));
        }
        else if(row == 3){
            ret = send_4_bit_command(lcd,(0x94 + column));
        }
        else if(row == 4){
            ret = send_4_bit_command(lcd,(0xD4 + column));
        }  
        
    }
        return ret;   
}
Std_ReturnType send_4_bit_custome_char_data_pos(const lcd_confg_4_t *lcd, uint8 row, 
                                          uint8 column, uint8 *arr, uint8 mem_pos){
    Std_ReturnType ret = E_OK;
       mem_pos--;          
    if(NULL == lcd)
        ret = E_NOT_OK;
    else
    {
        send_4_bit_command(lcd,(START_LCD_CGRAM + (mem_pos*8)));
        for( uint8 cnt = 0; cnt < 8; cnt++)
          ret = send_4_bit_char_data(lcd,arr[cnt]);
        send_4_bit_char_data_pos(lcd,row,column,mem_pos); // choose address of pattern in CGRAM THEN WRITE PATTER 
                                                          //THEN DETECT THE LOACATION OF LCD YOU WANT TO WRITE THIS
                                                          //PATTERN IN IT WITH DATA OF PATTERN (MEM POS OF CGRAM)
    }
        return ret;
    
}

Std_ReturnType lcd_pins_8_initialize(const lcd_confg_8_t *lcd){
          Std_ReturnType ret = E_OK;
    if(NULL == lcd)
        ret = E_NOT_OK;
    else
    {
        ret = gpio_pin_intialize(&(lcd->rs_lcd));
        ret = gpio_pin_intialize(&(lcd->en_lcd));
        for(uint8 cnt_pin = 0; cnt_pin < 8; cnt_pin++)
          ret = gpio_pin_intialize(&(lcd->lcd_pin[cnt_pin]));
        
        __delay_ms(20);
        ret = send_8_bit_command(lcd, LCD_8BIT_MODE_2_LINE);
        __delay_ms(5);
        ret = send_8_bit_command(lcd, LCD_8BIT_MODE_2_LINE);
        __delay_us(150);
        ret = send_8_bit_command(lcd, LCD_8BIT_MODE_2_LINE);
        ret = send_8_bit_command(lcd, CLEAR_DISPLAY);
        ret = send_8_bit_command(lcd, CURSOR_HOME);
        ret = send_8_bit_command(lcd, ENTRY_MODE_SET_INCREMENT_ON_SHIFT_OFF);
        ret = send_8_bit_command(lcd, DISPLAY_ON_UNDER_LINE_CURSOR_OFF_BLOCK_CURSOR_OFF);
        ret = send_8_bit_command(lcd, LCD_8BIT_MODE_2_LINE);
        //send_8_bit_command(lcd, 0x80); //option  == send_8_bit_command(lcd, CURSOR_HOME);
    }
        return ret; 
}

Std_ReturnType send_8_bit_command(const lcd_confg_8_t *lcd, uint8 command){
             Std_ReturnType ret = E_OK;
    if(NULL == lcd)
        ret = E_NOT_OK;
    else
    {
        ret = gpio_pin_write_logic(&(lcd->rs_lcd),LOW);
       for(uint8 cnt_pin = 0; cnt_pin < 8; cnt_pin++)
       {
           ret = gpio_pin_write_logic(&(lcd->lcd_pin[cnt_pin]),((command >> cnt_pin)& (uint8)0x01));
       }
        ret = send_8_bit_enable(lcd);
    }
        return ret; 
}

Std_ReturnType send_8_bit_char_data(const lcd_confg_8_t *lcd, uint8 data){
              Std_ReturnType ret = E_OK;
    if(NULL == lcd)
        ret = E_NOT_OK;
    else
    {
        gpio_pin_write_logic(&(lcd->rs_lcd),HIGH);
       for(uint8 cnt_pin = 0; cnt_pin < 8; cnt_pin++)
       {
           gpio_pin_write_logic(&(lcd->lcd_pin[cnt_pin]),((data >> cnt_pin)& (uint8)0x01));
       }
         send_8_bit_enable(lcd);
    }
        return ret; 
}

static Std_ReturnType send_8_bit_enable(const lcd_confg_8_t *lcd){
                 Std_ReturnType ret = E_OK;
    if(NULL == lcd)
        ret = E_NOT_OK;
    else
    {
        gpio_pin_write_logic(&(lcd->en_lcd),LOW); //OR HIGH
        __delay_us(5);
         gpio_pin_write_logic(&(lcd->en_lcd),HIGH);//OR LOW
    }
        return ret;
}

Std_ReturnType send_8_bit_char_data_pos(const lcd_confg_8_t *lcd, uint8 row, uint8 column, uint8 data){
                 Std_ReturnType ret = E_OK;              
    if(NULL == lcd)
        ret = E_NOT_OK;
    else
    {
        lcd_8_bit_set_cursor(lcd,row,column);
        send_8_bit_char_data(lcd, data);
    }
        return ret;  
}

static Std_ReturnType lcd_8_bit_set_cursor(const lcd_confg_8_t *lcd, uint8 row, uint8 column){
                  Std_ReturnType ret = E_OK;
                 column--;
    if(NULL == lcd)
        ret = E_NOT_OK;
    else
    {
        if(row == 1)
        {
            ret = send_8_bit_command(lcd,(0x80 + column));
        }
        else if(row == 2)
        {
            ret = send_8_bit_command(lcd,(0xC0 + column));
        }
        else if(row == 3){
            ret = send_8_bit_command(lcd,(0x94 + column));
        }
        else if(row == 4){
            ret = send_8_bit_command(lcd,(0xD4 + column));
        }  
        
    }
        return ret;   
}

Std_ReturnType send_8_bit_string_data(const lcd_confg_8_t *lcd, uint8 *data){
                    Std_ReturnType ret = E_OK;
                 
    if(NULL == lcd)
        ret = E_NOT_OK;
    else
    {
      while(*data){
          ret = send_8_bit_char_data(lcd,*data++);
      }        
    }
        return ret;  
}
Std_ReturnType send_8_bit_string_data_pos(const lcd_confg_8_t *lcd, uint8 row, uint8 column, uint8 *data){
                    Std_ReturnType ret = E_OK;
                 
    if(NULL == lcd)
        ret = E_NOT_OK;
    else
    {
        lcd_8_bit_set_cursor(lcd,row,column);
      while(*data){
          ret = send_8_bit_char_data(lcd,*data++);
      }        
    }
        return ret; 
}
Std_ReturnType send_8_bit_custome_char_data_pos(const lcd_confg_8_t *lcd, uint8 row, 
                                          uint8 column, uint8 *arr, uint8 mem_pos){
                     Std_ReturnType ret = E_OK;
       mem_pos--;          
    if(NULL == lcd)
        ret = E_NOT_OK;
    else
    {
        send_8_bit_command(lcd,(START_LCD_CGRAM + (mem_pos * 8)));
        for( uint8 cnt = 0; cnt < 8; cnt++)
          ret = send_8_bit_char_data(lcd,arr[cnt]);
        send_8_bit_char_data_pos(lcd,row,column,mem_pos); // choose address of pattern in CGRAM THEN WRITE PATTER 
                                                          //THEN DETECT THE LOACATION OF LCD YOU WANT TO WRITE THIS
                                                          //PATTERN IN IT WITH DATA OF PATTERN (MEM POS OF CGRAM)
    }
        return ret; 
}
          
Std_ReturnType cnvert_uint8_to_string(uint8 value, uint8 *str){
        Std_ReturnType ret = E_OK;
    uint8 Temp_String[4] = {0};
    uint8 DataCounter = 0;
    if(NULL == str){
        ret = E_NOT_OK;
    }
    else{    
        memset(str, ' ', 3);
        str[3] = '\0';
        sprintf((char *)Temp_String, "%i", value);
        while(Temp_String[DataCounter] != '\0'){
            str[DataCounter] = Temp_String[DataCounter]; 
            DataCounter++;
        }
    }
    return ret; /* Std_ReturnType ret = E_OK;         
    if(NULL == ptr)
        ret = E_NOT_OK;
    else
    {
        memset(ptr,'\0', 4); // 2^8 = 256 "include null termenation"
        sprintf(ptr, "%i", value);
    }
        return ret; */
}
Std_ReturnType cnvert_uint16_to_string(uint16 value, uint8 *str){
  Std_ReturnType ret = E_OK;
    uint8 Temp_String[6] = {0};
    uint8 DataCounter = 0;
    if(NULL == str){
        ret = E_NOT_OK;
    }
    else{    
        memset(str, ' ', 5);
        str[5] = '\0';
        sprintf((char *)Temp_String, "%i", value);
        while(Temp_String[DataCounter] != '\0'){
            str[DataCounter] = Temp_String[DataCounter]; 
            DataCounter++;
        }
    }
    return ret;
   /* Std_ReturnType ret = E_OK;         
    if(NULL == ptr)
        ret = E_NOT_OK;
    else
    {
        memset(ptr,'\0', 6); // 2^16 = 65,536 "include null termenation"
        sprintf(ptr, "%i", value);
    }
        return ret; */
}
Std_ReturnType cnvert_uint32_to_string(uint32 value, uint8 *str){
 
      Std_ReturnType ret = E_OK;
    uint8 Temp_String[11] = {0};
    uint8 DataCounter = 0;
    if(NULL == str){
        ret = E_NOT_OK;
    }
    else{    
        memset(str, ' ', 10);
        str[10] = '\0';
        sprintf((char *)Temp_String, "%i", value);
        while(Temp_String[DataCounter] != '\0'){
            str[DataCounter] = Temp_String[DataCounter]; 
            DataCounter++;
        }
    }
    return ret;/* Std_ReturnType ret = E_OK;         
    if(NULL == ptr)
        ret = E_NOT_OK;
    else
    {
        memset(ptr,'\0', 11); // 2^32 = 4294967296 "include null termenation"
        sprintf(ptr, "%i", value);
    }
        return ret; */
}
