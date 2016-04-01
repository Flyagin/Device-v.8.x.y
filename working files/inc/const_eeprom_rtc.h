#ifndef __CONST_EEPROM_RTC__
#define __CONST_EEPROM_RTC__

#define I2C_EVENT_MASTER_BYTE_RECEIVED_NO_BUSY            ((uint32_t)0x00000040)  /* RxNE */

#define MAX_NUMBER_BUSY_STATE     10

#define ERROR_TOTAL_BIT           0
#define ERROR_UNEXPECTED_BIT      1
#define ERROR_FIX_ERRORS_BIT      2

#define CLOCKSPEED_1MBIT      1000000
#define CLOCKSPEED            400000
#define SIZE_PAGE_EEPROM      64
#define EEPROM_ADDRESS        0xA2
#define RTC_ADDRESS           0xD0

#define SIZE_USTUVANNJA         (sizeof(unsigned int) + sizeof(ustuvannja) + sizeof(phi_ustuvannja) + sizeof(phi_ustuvannja_sin_cos) + sizeof(serial_number_dev))
#define SIZE_SETTINGS            sizeof(__SETTINGS)
#define SIZE_ENERGY              sizeof(energy)

#define START_ADDRESS_USTUVANNJA_IN_EEPROM              0x0
#define START_ADDRESS_SETTINGS_IN_EEPROM                (((START_ADDRESS_USTUVANNJA_IN_EEPROM         + (SIZE_USTUVANNJA                        + 1)) & (unsigned int)(~(SIZE_PAGE_EEPROM - 1))) + SIZE_PAGE_EEPROM)
#define START_ADDRESS_STATE_LEDS_OUTPUTS_IN_EEPROM      (((START_ADDRESS_SETTINGS_IN_EEPROM           + (SIZE_SETTINGS                          + 1)) & (unsigned int)(~(SIZE_PAGE_EEPROM - 1))) + SIZE_PAGE_EEPROM)
#define START_ADDRESS_TRG_FUNC                          (((START_ADDRESS_STATE_LEDS_OUTPUTS_IN_EEPROM + (2*(1 + 2))                                 ) & (unsigned int)(~(SIZE_PAGE_EEPROM - 1))) + SIZE_PAGE_EEPROM)
#define START_ADDRESS_INFO_REJESTRATORS_DR              (((START_ADDRESS_TRG_FUNC                     + (1 + sizeof(trigger_active_functions  ) + 1)) & (unsigned int)(~(SIZE_PAGE_EEPROM - 1))) + SIZE_PAGE_EEPROM)
#define START_ADDRESS_INFO_REJESTRATORS_PR_ERR          (((START_ADDRESS_INFO_REJESTRATORS_DR         + (    sizeof(info_rejestrator_dr       ) + 1)) & (unsigned int)(~(SIZE_PAGE_EEPROM - 1))) + SIZE_PAGE_EEPROM)
#define START_ADDRESS_INFO_REJESTRATORS_AR              (((START_ADDRESS_INFO_REJESTRATORS_PR_ERR     + (    sizeof(info_rejestrator_pr_err   ) + 1)) & (unsigned int)(~(SIZE_PAGE_EEPROM - 1))) + SIZE_PAGE_EEPROM)
#define START_ADDRESS_RESURS_IN_EEPROM                  (((START_ADDRESS_INFO_REJESTRATORS_AR         + (    sizeof(info_rejestrator_ar       ) + 1)) & (unsigned int)(~(SIZE_PAGE_EEPROM - 1))) + SIZE_PAGE_EEPROM)
#define START_ADDRESS_ENERGY_IN_EEPROM                  (((START_ADDRESS_RESURS_IN_EEPROM             + (  2*sizeof(unsigned int              ) + 1)) & (unsigned int)(~(SIZE_PAGE_EEPROM - 1))) + SIZE_PAGE_EEPROM)

#define START_ADDRESS_TIME_REGISTERS              0x0
#define MAX_NUMBER_REGISTERS_RTC                  20

#define SIZE_BUFFER_FOR_EEPROM_EXCHNGE (sizeof(__SETTINGS) + 1)

#define COMPARISON_WRITING_SETTINGS_BIT                                 0
#define COMPARISON_WRITING_SETTINGS                                     (1 << COMPARISON_WRITING_SETTINGS_BIT)
#define COMPARISON_WRITING_USTUVANNJA_BIT                               1
#define COMPARISON_WRITING_USTUVANNJA                                   (1 << COMPARISON_WRITING_USTUVANNJA_BIT)
#define COMPARISON_WRITING_STATE_LEDS_OUTPUTS_BIT                       2
#define COMPARISON_WRITING_STATE_LEDS_OUTPUTS                           (1 << COMPARISON_WRITING_STATE_LEDS_OUTPUTS_BIT)
#define COMPARISON_WRITING_TRG_FUNC_BIT                                 3
#define COMPARISON_WRITING_TRG_FUNC                                     (1 << COMPARISON_WRITING_TRG_FUNC_BIT)
#define COMPARISON_WRITING_INFO_REJESTRATOR_AR_BIT                      4
#define COMPARISON_WRITING_INFO_REJESTRATOR_AR                          (1 << COMPARISON_WRITING_INFO_REJESTRATOR_AR_BIT)
#define COMPARISON_WRITING_INFO_REJESTRATOR_DR_BIT                      5
#define COMPARISON_WRITING_INFO_REJESTRATOR_DR                          (1 << COMPARISON_WRITING_INFO_REJESTRATOR_DR_BIT)
#define COMPARISON_WRITING_INFO_REJESTRATOR_PR_ERR_BIT                  6
#define COMPARISON_WRITING_INFO_REJESTRATOR_PR_ERR                      (1 << COMPARISON_WRITING_INFO_REJESTRATOR_PR_ERR_BIT)
#define COMPARISON_WRITING_RESURS_BIT                                   7
#define COMPARISON_WRITING_RESURS                                       (1 << COMPARISON_WRITING_RESURS_BIT)
#define COMPARISON_WRITING_ENERGY_BIT                                   8
#define COMPARISON_WRITING_ENERGY                                       (1 << COMPARISON_WRITING_ENERGY_BIT)

#define TASK_BLK_OPERATION_BIT                                          0      
#define TASK_BLK_WRITING_EEPROM_BIT                                     1      

#define TASK_START_WRITE_SETTINGS_EEPROM_BIT                            2      
#define TASK_WRITING_SETTINGS_EEPROM_BIT                                3      

#define TASK_START_READ_SETTINGS_EEPROM_BIT                             4      
#define TASK_READING_SETTINGS_EEPROM_BIT                                5      

#define TASK_START_WRITE_USTUVANNJA_EEPROM_BIT                          6      
#define TASK_WRITING_USTUVANNJA_EEPROM_BIT                              7      

#define TASK_START_READ_USTUVANNJA_EEPROM_BIT                           8      
#define TASK_READING_USTUVANNJA_EEPROM_BIT                              9      

#define TASK_START_WRITE_STATE_LEDS_OUTPUTS_EEPROM_BIT                  10      
#define TASK_WRITING_STATE_LEDS_OUTPUTS_EEPROM_BIT                      11      

#define TASK_START_READ_STATE_LEDS_OUTPUTS_EEPROM_BIT                   12      
#define TASK_READING_STATE_LEDS_OUTPUTS_EEPROM_BIT                      13      

#define TASK_START_WRITE_TRG_FUNC_EEPROM_BIT                            14      
#define TASK_WRITING_TRG_FUNC_EEPROM_BIT                                15      

#define TASK_START_READ_TRG_FUNC_EEPROM_BIT                             16      
#define TASK_READING_TRG_FUNC_EEPROM_BIT                                17      

#define TASK_START_WRITE_INFO_REJESTRATOR_AR_EEPROM_BIT                 18      
#define TASK_WRITING_INFO_REJESTRATOR_AR_EEPROM_BIT                     19      

#define TASK_START_READ_INFO_REJESTRATOR_AR_EEPROM_BIT                  20      
#define TASK_READING_INFO_REJESTRATOR_AR_EEPROM_BIT                     21      

#define TASK_START_WRITE_INFO_REJESTRATOR_DR_EEPROM_BIT                 22      
#define TASK_WRITING_INFO_REJESTRATOR_DR_EEPROM_BIT                     23      

#define TASK_START_READ_INFO_REJESTRATOR_DR_EEPROM_BIT                  24      
#define TASK_READING_INFO_REJESTRATOR_DR_EEPROM_BIT                     25      

#define TASK_START_WRITE_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT             26      
#define TASK_WRITING_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT                 27      

#define TASK_START_READ_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT              28      
#define TASK_READING_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT                 29      

#define TASK_START_READ_RTC_BIT                                         30      
#define TASK_READING_RTC_BIT                                            31     

#define TASK_START_WRITE_RTC_BIT                                        32      
#define TASK_WRITING_RTC_BIT                                            33      

#define TASK_SET_START_SETTINGS_RTC_BIT                                 34      
#define TASK_RESET_ST_RTC_BIT                                           35      
#define TASK_RESET_OF_RTC_BIT                                           36      

#define TASK_START_WRITE_RESURS_EEPROM_BIT                              37      
#define TASK_WRITING_RESURS_EEPROM_BIT                                  38      

#define TASK_START_READ_RESURS_EEPROM_BIT                               39      
#define TASK_READING_RESURS_EEPROM_BIT                                  40

#define TASK_START_WRITE_ENERGY_EEPROM_BIT                              41      
#define TASK_WRITING_ENERGY_EEPROM_BIT                                  42      

#define TASK_START_READ_ENERGY_EEPROM_BIT                               43      
#define TASK_READING_ENERGY_EEPROM_BIT                                  44

#define STATE_SETTINGS_EEPROM_EMPTY_BIT                                 0      
#define STATE_SETTINGS_EEPROM_EMPTY                                     (1<<STATE_SETTINGS_EEPROM_EMPTY_BIT)      
#define STATE_SETTINGS_EEPROM_FAIL_BIT                                  1      
#define STATE_SETTINGS_EEPROM_FAIL                                      (1<<STATE_SETTINGS_EEPROM_FAIL_BIT)      
#define STATE_SETTINGS_EEPROM_GOOD_BIT                                  2      
#define STATE_SETTINGS_EEPROM_GOOD                                      (1<<STATE_SETTINGS_EEPROM_GOOD_BIT)      

#define STATE_USTUVANNJA_EEPROM_EMPTY_BIT                               3      
#define STATE_USTUVANNJA_EEPROM_EMPTY                                   (1<<STATE_USTUVANNJA_EEPROM_EMPTY_BIT)      
#define STATE_USTUVANNJA_EEPROM_FAIL_BIT                                4      
#define STATE_USTUVANNJA_EEPROM_FAIL                                    (1<<STATE_USTUVANNJA_EEPROM_FAIL_BIT)      
#define STATE_USTUVANNJA_EEPROM_GOOD_BIT                                5      
#define STATE_USTUVANNJA_EEPROM_GOOD                                    (1<<STATE_USTUVANNJA_EEPROM_GOOD_BIT)      

#define STATE_STATE_LEDS_OUTPUTS_EEPROM_EMPTY_BIT                       6      
#define STATE_STATE_LEDS_OUTPUTS_EEPROM_EMPTY                           (1<<STATE_STATE_LEDS_OUTPUTS_EEPROM_EMPTY_BIT)      
#define STATE_STATE_LEDS_EEPROM_FAIL_BIT                                7      
#define STATE_STATE_LEDS_EEPROM_FAIL                                    (1<<STATE_STATE_LEDS_EEPROM_FAIL_BIT)      
#define STATE_STATE_LEDS_EEPROM_GOOD_BIT                                8      
#define STATE_STATE_LEDS_EEPROM_GOOD                                    (1<<STATE_STATE_LEDS_EEPROM_GOOD_BIT)      
#define STATE_STATE_OUTPUTS_EEPROM_FAIL_BIT                             9      
#define STATE_STATE_OUTPUTS_EEPROM_FAIL                                 (1<<STATE_STATE_OUTPUTS_EEPROM_FAIL_BIT)      
#define STATE_STATE_OUTPUTS_EEPROM_GOOD_BIT                             10      
#define STATE_STATE_OUTPUTS_EEPROM_GOOD                                 (1<<STATE_STATE_OUTPUTS_EEPROM_GOOD_BIT)      

#define STATE_TRG_FUNC_EEPROM_EMPTY_BIT                                 11      
#define STATE_TRG_FUNC_EEPROM_EMPTY                                     (1<<STATE_TRG_FUNC_EEPROM_EMPTY_BIT)      
#define STATE_TRG_FUNC_EEPROM_FAIL_BIT                                  12      
#define STATE_TRG_FUNC_EEPROM_FAIL                                      (1<<STATE_TRG_FUNC_EEPROM_FAIL_BIT)      
#define STATE_TRG_FUNC_EEPROM_GOOD_BIT                                  13      
#define STATE_TRG_FUNC_EEPROM_GOOD                                      (1<<STATE_TRG_FUNC_EEPROM_GOOD_BIT)      

#define STATE_INFO_REJESTRATOR_AR_EEPROM_EMPTY_BIT                      14      
#define STATE_INFO_REJESTRATOR_AR_EEPROM_EMPTY                          (1<<STATE_INFO_REJESTRATOR_AR_EEPROM_EMPTY_BIT)      
#define STATE_INFO_REJESTRATOR_AR_EEPROM_FAIL_BIT                       15      
#define STATE_INFO_REJESTRATOR_AR_EEPROM_FAIL                           (1<<STATE_INFO_REJESTRATOR_AR_EEPROM_FAIL_BIT)      
#define STATE_INFO_REJESTRATOR_AR_EEPROM_GOOD_BIT                       16      
#define STATE_INFO_REJESTRATOR_AR_EEPROM_GOOD                           (1<<STATE_INFO_REJESTRATOR_AR_EEPROM_GOOD_BIT)      

#define STATE_INFO_REJESTRATOR_DR_EEPROM_EMPTY_BIT                      17      
#define STATE_INFO_REJESTRATOR_DR_EEPROM_EMPTY                          (1<<STATE_INFO_REJESTRATOR_DR_EEPROM_EMPTY_BIT)      
#define STATE_INFO_REJESTRATOR_DR_EEPROM_FAIL_BIT                       18      
#define STATE_INFO_REJESTRATOR_DR_EEPROM_FAIL                           (1<<STATE_INFO_REJESTRATOR_DR_EEPROM_FAIL_BIT)      
#define STATE_INFO_REJESTRATOR_DR_EEPROM_GOOD_BIT                       29      
#define STATE_INFO_REJESTRATOR_DR_EEPROM_GOOD                           (1<<STATE_INFO_REJESTRATOR_DR_EEPROM_GOOD_BIT)      

#define STATE_INFO_REJESTRATOR_PR_ERR_EEPROM_EMPTY_BIT                  20      
#define STATE_INFO_REJESTRATOR_PR_ERR_EEPROM_EMPTY                      (1<<STATE_INFO_REJESTRATOR_PR_ERR_EEPROM_EMPTY_BIT)      
#define STATE_INFO_REJESTRATOR_PR_ERR_EEPROM_FAIL_BIT                   21      
#define STATE_INFO_REJESTRATOR_PR_ERR_EEPROM_FAIL                       (1<<STATE_INFO_REJESTRATOR_PR_ERR_EEPROM_FAIL_BIT)      
#define STATE_INFO_REJESTRATOR_PR_ERR_EEPROM_GOOD_BIT                   22      
#define STATE_INFO_REJESTRATOR_PR_ERR_EEPROM_GOOD                       (1<<STATE_INFO_REJESTRATOR_PR_ERR_EEPROM_GOOD_BIT)      

#define STATE_RESURS_EEPROM_EMPTY_BIT                                   23      
#define STATE_RESURS_EEPROM_EMPTY                                       (1<<STATE_RESURS_EEPROM_EMPTY_BIT)      
#define STATE_RESURS_EEPROM_FAIL_BIT                                    24      
#define STATE_RESURS_EEPROM_FAIL                                        (1<<STATE_RESURS_EEPROM_FAIL_BIT)      
#define STATE_RESURS_EEPROM_GOOD_BIT                                    25      
#define STATE_RESURS_EEPROM_GOOD                                        (1<<STATE_RESURS_EEPROM_GOOD_BIT) 

#define STATE_ENERGY_EEPROM_EMPTY_BIT                                   26      
#define STATE_ENERGY_EEPROM_EMPTY                                       (1<<STATE_ENERGY_EEPROM_EMPTY_BIT)      
#define STATE_ENERGY_EEPROM_FAIL_BIT                                    27      
#define STATE_ENERGY_EEPROM_FAIL                                        (1<<STATE_ENERGY_EEPROM_FAIL_BIT)      
#define STATE_ENERGY_EEPROM_GOOD_BIT                                    28      
#define STATE_ENERGY_EEPROM_GOOD                                        (1<<STATE_ENERGY_EEPROM_GOOD_BIT) 

#define STATE_FIRST_READING_RTC_BIT                                     30      
#define STATE_FIRST_READING_RTC                                         (1<<STATE_FIRST_READING_RTC_BIT)    

#define ETAP_CLEAR_OF_NONE                                      -1                                            //-1
#define ETAP_CLEAR_OF_ST_STOP                                   0                                             //0
#define ETAP_CLEAR_OF_ST_CLEAR                                  (ETAP_CLEAR_OF_ST_STOP + 1)                   //1
#define ETAP_CLEAR_OF_ST_START_WAITING_5S                       (ETAP_CLEAR_OF_ST_CLEAR + 1)                  //2
#define ETAP_CLEAR_OF_ST_WAITING_5S                             (ETAP_CLEAR_OF_ST_START_WAITING_5S + 1)       //3
#define ETAP_CLEAR_OF_WRITE_OF_0                                (ETAP_CLEAR_OF_ST_WAITING_5S + 1)             //4

#endif
