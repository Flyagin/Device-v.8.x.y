#ifndef __CONST_I2C__
#define __CONST_I2C__

#define I2C_EVENT_MASTER_BYTE_RECEIVED_NO_BUSY            ((uint32_t)0x00000040)  /* RxNE */

#define MAX_NUMBER_BUSY_STATE     10

#define ERROR_TOTAL_BIT           0
#define ERROR_UNEXPECTED_BIT      1
#define ERROR_FIX_ERRORS_BIT      2

#ifdef I2C_EEPROM
#define CLOCKSPEED_1MBIT      1000000
#define EEPROM_ADDRESS        0xA2
#endif

#define CLOCKSPEED            400000

#define RTC_ADDRESS           0xD0


#define START_ADDRESS_TIME_REGISTERS              0x0
#define MAX_NUMBER_REGISTERS_RTC                  20

#ifndef I2C_EEPROM
#define SIZE_BUFFER_FOR_I2C     MAX_NUMBER_REGISTERS_RTC
#else
#define SIZE_BUFFER_FOR_I2C     (sizeof(__SETTINGS) + 1)
#endif



enum  _task_i2c_bit
{
TASK_BLK_OPERATION_BIT,

TASK_START_READ_RTC_BIT,
TASK_READING_RTC_BIT,

TASK_START_WRITE_RTC_BIT,
TASK_WRITING_RTC_BIT,

TASK_SET_START_SETTINGS_RTC_BIT,
TASK_RESET_ST_RTC_BIT,
TASK_RESET_OF_RTC_BIT,

__TASK_NUMBER_RTC
};

#ifndef I2C_EEPROM
#define N_I2C   ((__TASK_NUMBER_RTC / 32) + (__TASK_NUMBER_RTC % 32))
#endif



#define STATE_FIRST_READING_RTC_BIT                                     30      
#define STATE_FIRST_READING_RTC                                         (1<<STATE_FIRST_READING_RTC_BIT)    

#define ETAP_CLEAR_OF_NONE                                      -1                                            //-1
#define ETAP_CLEAR_OF_ST_STOP                                   0                                             //0
#define ETAP_CLEAR_OF_ST_CLEAR                                  (ETAP_CLEAR_OF_ST_STOP + 1)                   //1
#define ETAP_CLEAR_OF_ST_START_WAITING_5S                       (ETAP_CLEAR_OF_ST_CLEAR + 1)                  //2
#define ETAP_CLEAR_OF_ST_WAITING_5S                             (ETAP_CLEAR_OF_ST_START_WAITING_5S + 1)       //3
#define ETAP_CLEAR_OF_WRITE_OF_0                                (ETAP_CLEAR_OF_ST_WAITING_5S + 1)             //4

#endif
