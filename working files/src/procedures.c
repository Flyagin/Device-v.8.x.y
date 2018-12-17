#include "header.h"

/*****************************************************/
//Функція обновлення змінних при зміні конфігурації
/*****************************************************/
unsigned int action_after_changing_of_configuration(unsigned int new_configuration, __SETTINGS *target_label)
{
  unsigned int error_window = 0;
  
  /************************/
  //Спершу перевіряємо чи не знаходимося зараз ми у такому вікні, яке забороняє змінювати текучу конфігурацію
  /************************/
  //Перевірка МТЗ
  if ((new_configuration & ( 1<< MTZ_BIT_CONFIGURATION )) == 0)
  {
    if(
       (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_MTZ)
       || 
       (
        (current_ekran.current_level >= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_MTZ) &&
        (current_ekran.current_level <= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP4_MTZ) 
       )  
       ||  
       (
        (current_ekran.current_level >= EKRAN_SETPOINT_MTZ_GROUP1) &&
        (current_ekran.current_level <= EKRAN_SETPOINT_MTZ_GROUP4)
       )
       ||  
       (
        (current_ekran.current_level >= EKRAN_TIMEOUT_MTZ_GROUP1) &&
        (current_ekran.current_level <= EKRAN_TIMEOUT_MTZ_GROUP4)
       )
       ||  
       (current_ekran.current_level == EKRAN_CONTROL_MTZ)
      )
      error_window |= (1 << MTZ_BIT_CONFIGURATION );
  }
  //Перевірка ЗДЗ
  if ((new_configuration & (1<<ZDZ_BIT_CONFIGURATION)) == 0)
  {
    if(
       (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_ZDZ) ||
       (current_ekran.current_level == EKRAN_CONTROL_ZDZ        )
      )
      error_window |= (1 << ZDZ_BIT_CONFIGURATION );
  }
  //Перевірка ЗЗ
  if ((new_configuration & (1<<ZZ_BIT_CONFIGURATION)) == 0)
  {
    if(
       (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_ZZ)
       || 
       (
        (current_ekran.current_level >= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_ZZ) &&
        (current_ekran.current_level <= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP4_ZZ) 
       )  
       ||
       (
        (current_ekran.current_level >= EKRAN_SETPOINT_ZZ_GROUP1) &&
        (current_ekran.current_level <= EKRAN_SETPOINT_ZZ_GROUP4)
       )
       ||  
       (
        (current_ekran.current_level >= EKRAN_TIMEOUT_ZZ_GROUP1) &&
        (current_ekran.current_level <= EKRAN_TIMEOUT_ZZ_GROUP4)
       )
       ||  
       (current_ekran.current_level == EKRAN_CONTROL_ZZ        )
      )
      error_window |= (1 << ZZ_BIT_CONFIGURATION );
  }
  //Перевірка АПВ
  if ((new_configuration & (1<<APV_BIT_CONFIGURATION)) == 0)
  {
    if(
       (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_APV)
       || 
       (
        (current_ekran.current_level >= EKRAN_CHOOSE_TIMEOUT_GROUP1_APV) &&
        (current_ekran.current_level <= EKRAN_CHOOSE_TIMEOUT_GROUP4_APV) 
       )  
       ||  
       (
        (current_ekran.current_level >= EKRAN_TIMEOUT_APV_GROUP1) &&
        (current_ekran.current_level <= EKRAN_TIMEOUT_APV_GROUP4)
       )
       ||  
       (current_ekran.current_level == EKRAN_CONTROL_APV        )
      )
      error_window |= (1 << APV_BIT_CONFIGURATION );
  }
  //Перевірка АПВ-ЗМН
  if ((new_configuration & (1<<APV_ZMN_BIT_CONFIGURATION)) == 0)
  {
    if(
       (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_APV_ZMN)
       || 
       (
        (current_ekran.current_level >= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_APV_ZMN) &&
        (current_ekran.current_level <= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP4_APV_ZMN) 
       )  
       ||
       (
        (current_ekran.current_level >= EKRAN_SETPOINT_APV_ZMN_GROUP1) &&
        (current_ekran.current_level <= EKRAN_SETPOINT_APV_ZMN_GROUP4)
       )
       ||  
       (
        (current_ekran.current_level >= EKRAN_TIMEOUT_APV_ZMN_GROUP1) &&
        (current_ekran.current_level <= EKRAN_TIMEOUT_APV_ZMN_GROUP4)
       )
       ||  
       (current_ekran.current_level == EKRAN_CONTROL_APV_ZMN        )
      )
      error_window |= (1 << APV_ZMN_BIT_CONFIGURATION );
  }
  //Перевірка АЧР-ЧАПВ
  if ((new_configuration & (1<<ACHR_CHAPV_BIT_CONFIGURATION)) == 0)
  {
    if(
       (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_ACHR_CHAPV)
       || 
       (
        (current_ekran.current_level >= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_ACHR_CHAPV) &&
        (current_ekran.current_level <= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP4_ACHR_CHAPV) 
       )  
       ||
       (
        (current_ekran.current_level >= EKRAN_SETPOINT_ACHR_CHAPV_GROUP1) &&
        (current_ekran.current_level <= EKRAN_SETPOINT_ACHR_CHAPV_GROUP4)
       )
       ||  
       (
        (current_ekran.current_level >= EKRAN_TIMEOUT_ACHR_CHAPV_GROUP1) &&
        (current_ekran.current_level <= EKRAN_TIMEOUT_ACHR_CHAPV_GROUP4)
       )
       ||  
       (current_ekran.current_level == EKRAN_CONTROL_ACHR_CHAPV        )
      )
      error_window |= (1 << ACHR_CHAPV_BIT_CONFIGURATION );
  }
  //Перевірка УРОВ
  if ((new_configuration & (1<<UROV_BIT_CONFIGURATION)) == 0)
  {
    if(
       (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_UROV)
       || 
       (
        (current_ekran.current_level >= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_UROV) &&
        (current_ekran.current_level <= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP4_UROV) 
       )  
       ||
       (
        (current_ekran.current_level >= EKRAN_SETPOINT_UROV_GROUP1) &&
        (current_ekran.current_level <= EKRAN_SETPOINT_UROV_GROUP4)
       )
       ||  
       (
        (current_ekran.current_level >= EKRAN_TIMEOUT_UROV_GROUP1) &&
        (current_ekran.current_level <= EKRAN_TIMEOUT_UROV_GROUP4)
       )
       ||  
       (current_ekran.current_level == EKRAN_CONTROL_UROV        )
      )
      error_window |= (1 << UROV_BIT_CONFIGURATION );
  }
  //Перевірка ЗОП(КОФ)
  if ((new_configuration & (1<<ZOP_BIT_CONFIGURATION)) == 0)
  {
    if(
       (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_ZOP)
       || 
       (
        (current_ekran.current_level >= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_ZOP) &&
        (current_ekran.current_level <= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP4_ZOP) 
       )  
       ||
       (
        (current_ekran.current_level >= EKRAN_SETPOINT_ZOP_GROUP1) &&
        (current_ekran.current_level <= EKRAN_SETPOINT_ZOP_GROUP4)
       )
       ||  
       (
        (current_ekran.current_level >= EKRAN_TIMEOUT_ZOP_GROUP1) &&
        (current_ekran.current_level <= EKRAN_TIMEOUT_ZOP_GROUP4)
       )
       ||  
       (current_ekran.current_level == EKRAN_CONTROL_ZOP        )
      )
      error_window |= (1 << ZOP_BIT_CONFIGURATION );
  }
  //Перевірка Umin
  if ((new_configuration & (1<<UMIN_BIT_CONFIGURATION)) == 0)
  {
    if(
       (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_UMIN)
       || 
       (
        (current_ekran.current_level >= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_UMIN) &&
        (current_ekran.current_level <= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP4_UMIN) 
       )  
       ||
       (
        (current_ekran.current_level >= EKRAN_SETPOINT_UMIN_GROUP1) &&
        (current_ekran.current_level <= EKRAN_SETPOINT_UMIN_GROUP4)
       )
       ||  
       (
        (current_ekran.current_level >= EKRAN_TIMEOUT_UMIN_GROUP1) &&
        (current_ekran.current_level <= EKRAN_TIMEOUT_UMIN_GROUP4)
       )
       ||  
       (current_ekran.current_level == EKRAN_CONTROL_UMIN        )
      )
      error_window |= (1 << UMIN_BIT_CONFIGURATION );
  }
  //Перевірка Umax
  if ((new_configuration & (1<<UMAX_BIT_CONFIGURATION)) == 0)
  {
    if(
       (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_UMAX)
       || 
       (
        (current_ekran.current_level >= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_UMAX) &&
        (current_ekran.current_level <= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP4_UMAX) 
       )  
       ||
       (
        (current_ekran.current_level >= EKRAN_SETPOINT_UMAX_GROUP1) &&
        (current_ekran.current_level <= EKRAN_SETPOINT_UMAX_GROUP4)
       )
       ||  
       (
        (current_ekran.current_level >= EKRAN_TIMEOUT_UMAX_GROUP1) &&
        (current_ekran.current_level <= EKRAN_TIMEOUT_UMAX_GROUP4)
       )
       ||  
       (current_ekran.current_level == EKRAN_CONTROL_UMAX        )
      )
      error_window |= (1 << UMAX_BIT_CONFIGURATION );
  }
  //Перевірка АВР
  if ((new_configuration & (1<<AVR_BIT_CONFIGURATION)) == 0)
  {
    if(
       (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_AVR)
       || 
       (
        (current_ekran.current_level >= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_AVR) &&
        (current_ekran.current_level <= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP4_AVR) 
       )  
       ||
       (
        (current_ekran.current_level >= EKRAN_SETPOINT_AVR_GROUP1) &&
        (current_ekran.current_level <= EKRAN_SETPOINT_AVR_GROUP4)
       )
       ||  
       (
        (current_ekran.current_level >= EKRAN_TIMEOUT_AVR_GROUP1) &&
        (current_ekran.current_level <= EKRAN_TIMEOUT_AVR_GROUP4)
       )
       ||  
       (current_ekran.current_level == EKRAN_CONTROL_AVR        )
      )
      error_window |= (1 << AVR_BIT_CONFIGURATION );
  }
  //Перевірка "Контроль напруги О/Р живлення"
  if ((new_configuration & (1<<CONTROL_U_BIT_CONFIGURATION)) == 0)
  {
    if(
       (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_CONTROL_U)
       || 
       (
        (current_ekran.current_level >= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_CONTROL_U) &&
        (current_ekran.current_level <= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP4_CONTROL_U) 
       )  
       ||
       (
        (current_ekran.current_level >= EKRAN_SETPOINT_CONTROL_U_GROUP1) &&
        (current_ekran.current_level <= EKRAN_SETPOINT_CONTROL_U_GROUP4)
       )
       ||  
       (
        (current_ekran.current_level >= EKRAN_TIMEOUT_CONTROL_U_GROUP1) &&
        (current_ekran.current_level <= EKRAN_TIMEOUT_CONTROL_U_GROUP4)
       )
       ||  
       (current_ekran.current_level == EKRAN_CONTROL_CONTROL_U        )
      )
      error_window |= (1 << CONTROL_U_BIT_CONFIGURATION );
  }
  //Перевірка "Визначення місця пошкодження"
  if ((new_configuration & (1<<VMP_BIT_CONFIGURATION)) == 0)
  {
    if(
       (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_VMP)
       || 
       (
        (current_ekran.current_level >= EKRAN_SETPOINT_VMP_FORWARD) &&
        (current_ekran.current_level <= EKRAN_SETPOINT_VMP_BACKWARD) 
       )  
       ||  
       (current_ekran.current_level == EKRAN_CONTROL_VMP              )
      )
      error_window |= (1 << VMP_BIT_CONFIGURATION );
  }
  /************************/
  
  if (error_window == 0)
  {
    //Вводимо нову конфігурацю у цільову структуру
    target_label->configuration = new_configuration;
    
    unsigned int maska[N_SMALL] = {0, 0}, maska_1[N_BIG] = {0, 0, 0, 0, 0, 0}, maska_2 = 0;
  
    //Перевіряємо, чи МТЗ зараз знято з конфігурації
    if ((target_label->configuration & (1<<MTZ_BIT_CONFIGURATION)) == 0)
    {
      //Виводим ступені МТЗ
      target_label->control_mtz &= (unsigned int)(~(CTR_MTZ_1 | CTR_MTZ_2 | CTR_MTZ_3 | CTR_MTZ_4));
   
      //Виводим ступені МТЗ з АПВ
      target_label->control_apv &= (unsigned int)(~(CTR_APV_STARTED_FROM_MTZ1 | CTR_APV_STARTED_FROM_MTZ2 | CTR_APV_STARTED_FROM_MTZ3  | CTR_APV_STARTED_FROM_MTZ4));

      //Виводим ступені МТЗ з ЗДЗ
      target_label->control_zdz &= (unsigned int)(~(CTR_ZDZ_STARTED_FROM_MTZ1 | CTR_ZDZ_STARTED_FROM_MTZ2 | CTR_ZDZ_STARTED_FROM_MTZ3  | CTR_ZDZ_STARTED_FROM_MTZ4));
      
      //Виводим ступені МТЗ з УРОВ
      target_label->control_urov &= (unsigned int)(~(CTR_UROV_STARTED_FROM_MTZ1 | CTR_UROV_STARTED_FROM_MTZ2 | CTR_UROV_STARTED_FROM_MTZ3 | CTR_UROV_STARTED_FROM_MTZ4));
      
      //Формуємо маски функцій МТЗ
      maska[0] = 0;
      maska[1] = 0;
      for (int i = 0; i < NUMBER_MTZ_SIGNAL_FOR_RANG_INPUT; i++)
        _SET_BIT(
                 maska, 
                 (
                  NUMBER_GENERAL_SIGNAL_FOR_RANG_INPUT + 
                  i
                 )
                );

      maska_1[0] = 0;
      maska_1[1] = 0;
      maska_1[2] = 0;
      maska_1[3] = 0;
      maska_1[4] = 0;
      maska_1[5] = 0;
      for (int i = 0; i < NUMBER_MTZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG; i++)
        _SET_BIT(
                 maska_1, 
                 (
                  NUMBER_GENERAL_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + 
                  i
                 )
                );
      
      maska_2 = 0;
      for (int i = 0; i < NUMBER_MTZ_SIGNAL_FOR_RANG_BUTTON; i++) maska_2 = (maska_2 <<1) + 0x1;
      maska_2 =(
                maska_2 << (
                            NUMBER_GENERAL_SIGNAL_FOR_RANG_BUTTON
                           )
               );

      //Знімаємо всі функції для ранжування входів, які відповідають за МТЗ
      for (int i = 0; i < NUMBER_DEFINED_BUTTONS; i++)
        target_label->ranguvannja_buttons[i] &= ~maska_2;
      //Знімаємо всі функції для ранжування входів, які відповідають за МТЗ
      for (int i = 0; i < NUMBER_INPUTS; i++)
      {
        target_label->ranguvannja_inputs[N_SMALL*i  ] &= ~maska[0];
        target_label->ranguvannja_inputs[N_SMALL*i+1] &= ~maska[1];
      }
      //Знімаємо всі функції для ранжування виходів, які відповідають за МТЗ
      for (int i = 0; i < NUMBER_OUTPUTS; i++)
      {
        target_label->ranguvannja_outputs[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_outputs[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_outputs[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_outputs[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_outputs[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_outputs[N_BIG*i+5] &= ~maska_1[5];
      }
      //Знімаємо всі функції для ранжування світоіндикаторів, які відповідають за МТЗ
      for (int i = 0; i < NUMBER_LEDS; i++)
      {
        target_label->ranguvannja_leds[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_leds[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_leds[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_leds[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_leds[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_leds[N_BIG*i+5] &= ~maska_1[5];
      }
      //Знімаємо всі функції для ранжування дискретного реєстратора, які відповідають за МТЗ
      target_label->ranguvannja_digital_registrator[0] &= ~maska_1[0];
      target_label->ranguvannja_digital_registrator[1] &= ~maska_1[1];
      target_label->ranguvannja_digital_registrator[2] &= ~maska_1[2];
      target_label->ranguvannja_digital_registrator[3] &= ~maska_1[3];
      target_label->ranguvannja_digital_registrator[4] &= ~maska_1[4];
      target_label->ranguvannja_digital_registrator[5] &= ~maska_1[5];
      //Знімаємо всі функції для ранжування аналогового реєстратора, які відповідають за МТЗ
      target_label->ranguvannja_analog_registrator[0] &= ~maska_1[0];
      target_label->ranguvannja_analog_registrator[1] &= ~maska_1[1];
      target_label->ranguvannja_analog_registrator[2] &= ~maska_1[2];
      target_label->ranguvannja_analog_registrator[3] &= ~maska_1[3];
      target_label->ranguvannja_analog_registrator[4] &= ~maska_1[4];
      target_label->ranguvannja_analog_registrator[5] &= ~maska_1[5];
      //Знімаємо всі функції для ранжування оприділювальних функцій, які відповідають за МТЗ
      for (int i = 0; i < NUMBER_DEFINED_FUNCTIONS; i++)
      {
        target_label->ranguvannja_df_source_plus[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_df_source_plus[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_df_source_plus[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_df_source_plus[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_df_source_plus[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_df_source_plus[N_BIG*i+5] &= ~maska_1[5];

        target_label->ranguvannja_df_source_minus[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_df_source_minus[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_df_source_minus[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_df_source_minus[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_df_source_minus[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_df_source_minus[N_BIG*i+5] &= ~maska_1[5];

        target_label->ranguvannja_df_source_blk[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_df_source_blk[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_df_source_blk[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_df_source_blk[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_df_source_blk[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_df_source_blk[N_BIG*i+5] &= ~maska_1[5];
      }
      //Знімаємо всі функції для ранжування оприділювальних триґерів, які відповідають за МТЗ
      for (int i = 0; i < NUMBER_DEFINED_TRIGGERS; i++)
      {
        target_label->ranguvannja_set_dt_source_plus[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_set_dt_source_plus[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_set_dt_source_plus[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_set_dt_source_plus[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_set_dt_source_plus[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_set_dt_source_plus[N_BIG*i+5] &= ~maska_1[5];

        target_label->ranguvannja_set_dt_source_minus[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_set_dt_source_minus[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_set_dt_source_minus[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_set_dt_source_minus[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_set_dt_source_minus[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_set_dt_source_minus[N_BIG*i+5] &= ~maska_1[5];

        target_label->ranguvannja_reset_dt_source_plus[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+5] &= ~maska_1[5];

        target_label->ranguvannja_reset_dt_source_minus[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+5] &= ~maska_1[5];
      }
    }
  
    //Перевіряємо, чи ЗДЗ зараз знято з конфігурації
    if ((target_label->configuration & (1<<ZDZ_BIT_CONFIGURATION)) == 0)
    {
      //Виводим ЗДЗ
      target_label->control_zdz &= (unsigned int)(~CTR_ZDZ_STATE);

      //Виводим захист ЗДЗ з УРОВ
      target_label->control_urov &= (unsigned int)(~CTR_UROV_STARTED_FROM_ZDZ);
      
      //Формуємо маки функцій ЗДЗ
      maska[0] = 0;
      maska[1] = 0;
      for (int i = 0; i < NUMBER_ZDZ_SIGNAL_FOR_RANG_INPUT; i++)
        _SET_BIT(
                 maska, 
                 (
                  NUMBER_GENERAL_SIGNAL_FOR_RANG_INPUT    + 
                  NUMBER_MTZ_SIGNAL_FOR_RANG_INPUT        +
                  i
                 )
                );
     
      maska_1[0] = 0;
      maska_1[1] = 0;
      maska_1[2] = 0;
      maska_1[3] = 0;
      maska_1[4] = 0;
      maska_1[5] = 0;
      for (int i = 0; i < NUMBER_ZDZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG; i++)
        _SET_BIT(
                 maska_1, 
                 (
                  NUMBER_GENERAL_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG    + 
                  NUMBER_MTZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG        +
                  i
                 )
                );

      maska_2 = 0;
      for (int i = 0; i < NUMBER_ZDZ_SIGNAL_FOR_RANG_BUTTON; i++) maska_2 = (maska_2 <<1) + 0x1;
      maska_2 =(
                maska_2 << (
                            NUMBER_GENERAL_SIGNAL_FOR_RANG_BUTTON    + 
                            NUMBER_MTZ_SIGNAL_FOR_RANG_BUTTON
                           )
               );

      //Знімаємо всі функції для ранжування входів, які відповідають за ЗДЗ
      for (int i = 0; i < NUMBER_DEFINED_BUTTONS; i++)
        target_label->ranguvannja_buttons[i] &= ~maska_2;
      //Знімаємо всі функції для ранжування входів, які відповідають за ЗДЗ
      for (int i = 0; i < NUMBER_INPUTS; i++)
      {
        target_label->ranguvannja_inputs[N_SMALL*i  ] &= ~maska[0];
        target_label->ranguvannja_inputs[N_SMALL*i+1] &= ~maska[1];
      }
      //Знімаємо всі функції для ранжування виходів, які відповідають за ЗДЗ
      for (int i = 0; i < NUMBER_OUTPUTS; i++)
      {
        target_label->ranguvannja_outputs[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_outputs[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_outputs[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_outputs[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_outputs[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_outputs[N_BIG*i+5] &= ~maska_1[5];
      }
      //Знімаємо всі функції для ранжування світоіндикаторів, які відповідають за ЗДЗ
      for (int i = 0; i < NUMBER_LEDS; i++)
      {
        target_label->ranguvannja_leds[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_leds[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_leds[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_leds[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_leds[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_leds[N_BIG*i+5] &= ~maska_1[5];
      }
      //Знімаємо всі функції для ранжування дискретного реєстратора, які відповідають за ЗДЗ
      target_label->ranguvannja_digital_registrator[0] &= ~maska_1[0];
      target_label->ranguvannja_digital_registrator[1] &= ~maska_1[1];
      target_label->ranguvannja_digital_registrator[2] &= ~maska_1[2];
      target_label->ranguvannja_digital_registrator[3] &= ~maska_1[3];
      target_label->ranguvannja_digital_registrator[4] &= ~maska_1[4];
      target_label->ranguvannja_digital_registrator[5] &= ~maska_1[5];
      //Знімаємо всі функції для ранжування аналогового реєстратора, які відповідають за ЗДЗ
      target_label->ranguvannja_analog_registrator[0] &= ~maska_1[0];
      target_label->ranguvannja_analog_registrator[1] &= ~maska_1[1];
      target_label->ranguvannja_analog_registrator[2] &= ~maska_1[2];
      target_label->ranguvannja_analog_registrator[3] &= ~maska_1[3];
      target_label->ranguvannja_analog_registrator[4] &= ~maska_1[4];
      target_label->ranguvannja_analog_registrator[5] &= ~maska_1[5];
      //Знімаємо всі функції для ранжування оприділювальних функцій, які відповідають за ЗДЗ
      for (int i = 0; i < NUMBER_DEFINED_FUNCTIONS; i++)
      {
        target_label->ranguvannja_df_source_plus[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_df_source_plus[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_df_source_plus[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_df_source_plus[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_df_source_plus[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_df_source_plus[N_BIG*i+5] &= ~maska_1[5];

        target_label->ranguvannja_df_source_minus[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_df_source_minus[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_df_source_minus[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_df_source_minus[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_df_source_minus[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_df_source_minus[N_BIG*i+5] &= ~maska_1[5];

        target_label->ranguvannja_df_source_blk[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_df_source_blk[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_df_source_blk[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_df_source_blk[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_df_source_blk[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_df_source_blk[N_BIG*i+5] &= ~maska_1[5];
      }
      //Знімаємо всі функції для ранжування оприділювальних триґерів, які відповідають за ЗДЗ
      for (int i = 0; i < NUMBER_DEFINED_TRIGGERS; i++)
      {
        target_label->ranguvannja_set_dt_source_plus[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_set_dt_source_plus[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_set_dt_source_plus[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_set_dt_source_plus[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_set_dt_source_plus[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_set_dt_source_plus[N_BIG*i+5] &= ~maska_1[5];

        target_label->ranguvannja_set_dt_source_minus[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_set_dt_source_minus[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_set_dt_source_minus[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_set_dt_source_minus[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_set_dt_source_minus[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_set_dt_source_minus[N_BIG*i+5] &= ~maska_1[5];

        target_label->ranguvannja_reset_dt_source_plus[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+5] &= ~maska_1[5];

        target_label->ranguvannja_reset_dt_source_minus[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+5] &= ~maska_1[5];
      }
    }

    //Перевіряємо, чи ЗЗ зараз знято з конфігурації
    if ((target_label->configuration & (1<<ZZ_BIT_CONFIGURATION)) == 0)
    {
      //Виводим ЗЗ
      target_label->control_zz &= (unsigned int)(~(CTR_ZZ1_3I0_STATE | CTR_ZZ1_3U0_STATE | CTR_ZZ1_NZZ_STATE));
   
      //Виводим захисти 3I0, 3U0 і НЗЗ з УРОВ
      target_label->control_urov &= (unsigned int)(~(CTR_UROV_STARTED_FROM_3I0 | CTR_UROV_STARTED_FROM_3U0 |CTR_UROV_STARTED_FROM_NZZ));

      //Формуємо маки функцій ЗЗ
      maska[0] = 0;
      maska[1] = 0;
      for (int i = 0; i < NUMBER_ZZ_SIGNAL_FOR_RANG_INPUT; i++)
        _SET_BIT(
                 maska, 
                 (
                  NUMBER_GENERAL_SIGNAL_FOR_RANG_INPUT + 
                  NUMBER_MTZ_SIGNAL_FOR_RANG_INPUT     +
                  NUMBER_ZDZ_SIGNAL_FOR_RANG_INPUT     +
                  i
                 )
                );

      maska_1[0] = 0;
      maska_1[1] = 0;
      maska_1[2] = 0;
      maska_1[3] = 0;
      maska_1[4] = 0;
      maska_1[5] = 0;
      for (int i = 0; i < NUMBER_ZZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG; i++)
        _SET_BIT(
                 maska_1, 
                 (
                  NUMBER_GENERAL_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + 
                  NUMBER_MTZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG     +
                  NUMBER_ZDZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG     +
                  i
                 )
                );
      
      maska_2 = 0;
      for (int i = 0; i < NUMBER_ZZ_SIGNAL_FOR_RANG_BUTTON; i++) maska_2 = (maska_2 <<1) + 0x1;
      maska_2 =(
                maska_2 << (
                            NUMBER_GENERAL_SIGNAL_FOR_RANG_BUTTON + 
                            NUMBER_MTZ_SIGNAL_FOR_RANG_BUTTON     +
                            NUMBER_ZDZ_SIGNAL_FOR_RANG_BUTTON
                           )
               );

      //Знімаємо всі функції для ранжування входів, які відповідають за ЗЗ
      for (int i = 0; i < NUMBER_DEFINED_BUTTONS; i++)
        target_label->ranguvannja_buttons[i] &= ~maska_2;
      //Знімаємо всі функції для ранжування входів, які відповідають за ЗЗ
      for (int i = 0; i < NUMBER_INPUTS; i++)
      {
        target_label->ranguvannja_inputs[N_SMALL*i  ] &= ~maska[0];
        target_label->ranguvannja_inputs[N_SMALL*i+1] &= ~maska[1];
      }
      //Знімаємо всі функції для ранжування виходів, які відповідають за ЗЗ
      for (int i = 0; i < NUMBER_OUTPUTS; i++)
      {
        target_label->ranguvannja_outputs[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_outputs[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_outputs[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_outputs[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_outputs[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_outputs[N_BIG*i+5] &= ~maska_1[5];
      }
      //Знімаємо всі функції для ранжування світоіндикаторів, які відповідають за ЗЗ
      for (int i = 0; i < NUMBER_LEDS; i++)
      {
        target_label->ranguvannja_leds[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_leds[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_leds[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_leds[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_leds[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_leds[N_BIG*i+5] &= ~maska_1[5];
      }
      //Знімаємо всі функції для ранжування дискретного реєстратора, які відповідають за ЗЗ
      target_label->ranguvannja_digital_registrator[0] &= ~maska_1[0];
      target_label->ranguvannja_digital_registrator[1] &= ~maska_1[1];
      target_label->ranguvannja_digital_registrator[2] &= ~maska_1[2];
      target_label->ranguvannja_digital_registrator[3] &= ~maska_1[3];
      target_label->ranguvannja_digital_registrator[4] &= ~maska_1[4];
      target_label->ranguvannja_digital_registrator[5] &= ~maska_1[5];
      //Знімаємо всі функції для ранжування аналогового реєстратора, які відповідають за ЗЗ
      target_label->ranguvannja_analog_registrator[0] &= ~maska_1[0];
      target_label->ranguvannja_analog_registrator[1] &= ~maska_1[1];
      target_label->ranguvannja_analog_registrator[2] &= ~maska_1[2];
      target_label->ranguvannja_analog_registrator[3] &= ~maska_1[3];
      target_label->ranguvannja_analog_registrator[4] &= ~maska_1[4];
      target_label->ranguvannja_analog_registrator[5] &= ~maska_1[5];
      //Знімаємо всі функції для ранжування оприділювальних функцій, які відповідають за ЗЗ
      for (int i = 0; i < NUMBER_DEFINED_FUNCTIONS; i++)
      {
        target_label->ranguvannja_df_source_plus[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_df_source_plus[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_df_source_plus[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_df_source_plus[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_df_source_plus[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_df_source_plus[N_BIG*i+5] &= ~maska_1[5];

        target_label->ranguvannja_df_source_minus[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_df_source_minus[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_df_source_minus[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_df_source_minus[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_df_source_minus[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_df_source_minus[N_BIG*i+5] &= ~maska_1[5];

        target_label->ranguvannja_df_source_blk[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_df_source_blk[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_df_source_blk[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_df_source_blk[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_df_source_blk[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_df_source_blk[N_BIG*i+5] &= ~maska_1[5];
      }
      //Знімаємо всі функції для ранжування оприділювальних триґерів, які відповідають за ЗЗ
      for (int i = 0; i < NUMBER_DEFINED_TRIGGERS; i++)
      {
        target_label->ranguvannja_set_dt_source_plus[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_set_dt_source_plus[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_set_dt_source_plus[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_set_dt_source_plus[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_set_dt_source_plus[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_set_dt_source_plus[N_BIG*i+5] &= ~maska_1[5];

        target_label->ranguvannja_set_dt_source_minus[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_set_dt_source_minus[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_set_dt_source_minus[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_set_dt_source_minus[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_set_dt_source_minus[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_set_dt_source_minus[N_BIG*i+5] &= ~maska_1[5];

        target_label->ranguvannja_reset_dt_source_plus[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+5] &= ~maska_1[5];

        target_label->ranguvannja_reset_dt_source_minus[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+5] &= ~maska_1[5];
      }
    }

    //Перевіряємо, чи АПВ зараз знято з конфігурації
    if ((target_label->configuration & (1<<APV_BIT_CONFIGURATION)) == 0)
    {
      //Виводим АПВ
      target_label->control_apv &= (unsigned int)(~(CTR_APV_STAGE_1 | CTR_APV_STAGE_2 | CTR_APV_STAGE_3 | CTR_APV_STAGE_4));
   
      //Формуємо маки функцій АПВ
      maska[0] = 0;
      maska[1] = 0;
      for (int i = 0; i < NUMBER_APV_SIGNAL_FOR_RANG_INPUT; i++)
        _SET_BIT(
                 maska, 
                 (
                  NUMBER_GENERAL_SIGNAL_FOR_RANG_INPUT + 
                  NUMBER_MTZ_SIGNAL_FOR_RANG_INPUT     +
                  NUMBER_ZDZ_SIGNAL_FOR_RANG_INPUT     +
                  NUMBER_ZZ_SIGNAL_FOR_RANG_INPUT      +
                  i
                 )
                );

      maska_1[0] = 0;
      maska_1[1] = 0;
      maska_1[2] = 0;
      maska_1[3] = 0;
      maska_1[4] = 0;
      maska_1[5] = 0;
      for (int i = 0; i < NUMBER_APV_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG; i++)
        _SET_BIT(
                 maska_1, 
                 (
                  NUMBER_GENERAL_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + 
                  NUMBER_MTZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG     +
                  NUMBER_ZDZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG     +
                  NUMBER_ZZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG      +
                  i
                 )
                );
      
      maska_2 = 0;
      for (int i = 0; i < NUMBER_APV_SIGNAL_FOR_RANG_BUTTON; i++) maska_2 = (maska_2 <<1) + 0x1;
      maska_2 =(
                maska_2 << (
                            NUMBER_GENERAL_SIGNAL_FOR_RANG_BUTTON + 
                            NUMBER_MTZ_SIGNAL_FOR_RANG_BUTTON     + 
                            NUMBER_ZDZ_SIGNAL_FOR_RANG_BUTTON     + 
                            NUMBER_ZZ_SIGNAL_FOR_RANG_BUTTON
                           )
               );

      //Знімаємо всі функції для ранжування входів, які відповідають за АПВ
      for (int i = 0; i < NUMBER_DEFINED_BUTTONS; i++)
        target_label->ranguvannja_buttons[i] &= ~maska_2;
      //Знімаємо всі функції для ранжування входів, які відповідають за АПВ
      for (int i = 0; i < NUMBER_INPUTS; i++)
      {
        target_label->ranguvannja_inputs[N_SMALL*i  ] &= ~maska[0];
        target_label->ranguvannja_inputs[N_SMALL*i+1] &= ~maska[1];
      }
      //Знімаємо всі функції для ранжування виходів, які відповідають за АПВ
      for (int i = 0; i < NUMBER_OUTPUTS; i++)
      {
        target_label->ranguvannja_outputs[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_outputs[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_outputs[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_outputs[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_outputs[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_outputs[N_BIG*i+5] &= ~maska_1[5];
      }
      //Знімаємо всі функції для ранжування світоіндикаторів, які відповідають за АПВ
      for (int i = 0; i < NUMBER_LEDS; i++)
      {
        target_label->ranguvannja_leds[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_leds[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_leds[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_leds[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_leds[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_leds[N_BIG*i+5] &= ~maska_1[5];
      }
      //Знімаємо всі функції для ранжування дискретного реєстратора, які відповідають за АПВ
      target_label->ranguvannja_digital_registrator[0] &= ~maska_1[0];
      target_label->ranguvannja_digital_registrator[1] &= ~maska_1[1];
      target_label->ranguvannja_digital_registrator[2] &= ~maska_1[2];
      target_label->ranguvannja_digital_registrator[3] &= ~maska_1[3];
      target_label->ranguvannja_digital_registrator[4] &= ~maska_1[4];
      target_label->ranguvannja_digital_registrator[5] &= ~maska_1[5];
      //Знімаємо всі функції для ранжування аналогового реєстратора, які відповідають за АПВ
      target_label->ranguvannja_analog_registrator[0] &= ~maska_1[0];
      target_label->ranguvannja_analog_registrator[1] &= ~maska_1[1];
      target_label->ranguvannja_analog_registrator[2] &= ~maska_1[2];
      target_label->ranguvannja_analog_registrator[3] &= ~maska_1[3];
      target_label->ranguvannja_analog_registrator[4] &= ~maska_1[4];
      target_label->ranguvannja_analog_registrator[5] &= ~maska_1[5];
      //Знімаємо всі функції для ранжування оприділювальних функцій, які відповідають за АПВ
      for (int i = 0; i < NUMBER_DEFINED_FUNCTIONS; i++)
      {
        target_label->ranguvannja_df_source_plus[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_df_source_plus[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_df_source_plus[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_df_source_plus[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_df_source_plus[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_df_source_plus[N_BIG*i+5] &= ~maska_1[5];

        target_label->ranguvannja_df_source_minus[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_df_source_minus[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_df_source_minus[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_df_source_minus[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_df_source_minus[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_df_source_minus[N_BIG*i+5] &= ~maska_1[5];

        target_label->ranguvannja_df_source_blk[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_df_source_blk[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_df_source_blk[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_df_source_blk[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_df_source_blk[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_df_source_blk[N_BIG*i+5] &= ~maska_1[5];
      }
      //Знімаємо всі функції для ранжування оприділювальних триґерів, які відповідають за АПВ
      for (int i = 0; i < NUMBER_DEFINED_TRIGGERS; i++)
      {
        target_label->ranguvannja_set_dt_source_plus[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_set_dt_source_plus[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_set_dt_source_plus[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_set_dt_source_plus[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_set_dt_source_plus[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_set_dt_source_plus[N_BIG*i+5] &= ~maska_1[5];

        target_label->ranguvannja_set_dt_source_minus[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_set_dt_source_minus[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_set_dt_source_minus[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_set_dt_source_minus[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_set_dt_source_minus[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_set_dt_source_minus[N_BIG*i+5] &= ~maska_1[5];

        target_label->ranguvannja_reset_dt_source_plus[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+5] &= ~maska_1[5];

        target_label->ranguvannja_reset_dt_source_minus[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+5] &= ~maska_1[5];
      }
    }

    //Перевіряємо, чи АПВ-ЗМН зараз знято з конфігурації
    if ((target_label->configuration & (1<<APV_ZMN_BIT_CONFIGURATION)) == 0)
    {
      //Виводим АПВ-ЗМН
      target_label->control_apv_zmn &= (unsigned int)(~CTR_APV_ZMN);
   
      //Формуємо маки функцій АПВ-ЗМН
      maska[0] = 0;
      maska[1] = 0;
      for (int i = 0; i < NUMBER_APV_ZMN_SIGNAL_FOR_RANG_INPUT; i++)
        _SET_BIT(
                 maska, 
                 (
                  NUMBER_GENERAL_SIGNAL_FOR_RANG_INPUT    + 
                  NUMBER_MTZ_SIGNAL_FOR_RANG_INPUT        +
                  NUMBER_ZDZ_SIGNAL_FOR_RANG_INPUT        +
                  NUMBER_ZZ_SIGNAL_FOR_RANG_INPUT         +
                  NUMBER_APV_SIGNAL_FOR_RANG_INPUT        +
                  i
                 )
                );
     
      maska_1[0] = 0;
      maska_1[1] = 0;
      maska_1[2] = 0;
      maska_1[3] = 0;
      maska_1[4] = 0;
      maska_1[5] = 0;
      for (int i = 0; i < NUMBER_APV_ZMN_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG; i++)
        _SET_BIT(
                 maska_1, 
                 (
                  NUMBER_GENERAL_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG    + 
                  NUMBER_MTZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG        +
                  NUMBER_ZDZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG        +
                  NUMBER_ZZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG         +
                  NUMBER_APV_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG        +
                  i
                 )
                );

      maska_2 = 0;
      for (int i = 0; i < NUMBER_APV_ZMN_SIGNAL_FOR_RANG_BUTTON; i++) maska_2 = (maska_2 <<1) + 0x1;
      maska_2 =(
                maska_2 << (
                            NUMBER_GENERAL_SIGNAL_FOR_RANG_BUTTON +
                            NUMBER_MTZ_SIGNAL_FOR_RANG_BUTTON     +
                            NUMBER_ZDZ_SIGNAL_FOR_RANG_BUTTON     +
                            NUMBER_ZZ_SIGNAL_FOR_RANG_BUTTON      + 
                            NUMBER_APV_SIGNAL_FOR_RANG_BUTTON
                           )
               );

      //Знімаємо всі функції для ранжування входів, які відповідають за АПВ-ЗМН
      for (int i = 0; i < NUMBER_DEFINED_BUTTONS; i++)
        target_label->ranguvannja_buttons[i] &= ~maska_2;
      //Знімаємо всі функції для ранжування входів, які відповідають за АПВ-ЗМН
      for (int i = 0; i < NUMBER_INPUTS; i++)
      {
        target_label->ranguvannja_inputs[N_SMALL*i  ] &= ~maska[0];
        target_label->ranguvannja_inputs[N_SMALL*i+1] &= ~maska[1];
      }
      //Знімаємо всі функції для ранжування виходів, які відповідають за АПВ-ЗМН
      for (int i = 0; i < NUMBER_OUTPUTS; i++)
      {
        target_label->ranguvannja_outputs[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_outputs[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_outputs[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_outputs[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_outputs[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_outputs[N_BIG*i+5] &= ~maska_1[5];
      }
      //Знімаємо всі функції для ранжування світоіндикаторів, які відповідають за АПВ-ЗМН
      for (int i = 0; i < NUMBER_LEDS; i++)
      {
        target_label->ranguvannja_leds[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_leds[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_leds[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_leds[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_leds[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_leds[N_BIG*i+5] &= ~maska_1[5];
      }
      //Знімаємо всі функції для ранжування дискретного реєстратора, які відповідають за АПВ-ЗМН
      target_label->ranguvannja_digital_registrator[0] &= ~maska_1[0];
      target_label->ranguvannja_digital_registrator[1] &= ~maska_1[1];
      target_label->ranguvannja_digital_registrator[2] &= ~maska_1[2];
      target_label->ranguvannja_digital_registrator[3] &= ~maska_1[3];
      target_label->ranguvannja_digital_registrator[4] &= ~maska_1[4];
      target_label->ranguvannja_digital_registrator[5] &= ~maska_1[5];
      //Знімаємо всі функції для ранжування аналогового реєстратора, які відповідають за АПВ-ЗМН
      target_label->ranguvannja_analog_registrator[0] &= ~maska_1[0];
      target_label->ranguvannja_analog_registrator[1] &= ~maska_1[1];
      target_label->ranguvannja_analog_registrator[2] &= ~maska_1[2];
      target_label->ranguvannja_analog_registrator[3] &= ~maska_1[3];
      target_label->ranguvannja_analog_registrator[4] &= ~maska_1[4];
      target_label->ranguvannja_analog_registrator[5] &= ~maska_1[5];
      //Знімаємо всі функції для ранжування оприділювальних функцій, які відповідають за АПВ-ЗМН
      for (int i = 0; i < NUMBER_DEFINED_FUNCTIONS; i++)
      {
        target_label->ranguvannja_df_source_plus[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_df_source_plus[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_df_source_plus[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_df_source_plus[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_df_source_plus[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_df_source_plus[N_BIG*i+5] &= ~maska_1[5];

        target_label->ranguvannja_df_source_minus[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_df_source_minus[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_df_source_minus[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_df_source_minus[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_df_source_minus[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_df_source_minus[N_BIG*i+5] &= ~maska_1[5];

        target_label->ranguvannja_df_source_blk[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_df_source_blk[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_df_source_blk[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_df_source_blk[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_df_source_blk[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_df_source_blk[N_BIG*i+5] &= ~maska_1[5];
      }
      //Знімаємо всі функції для ранжування оприділювальних триґерів, які відповідають за АПВ-ЗМН
      for (int i = 0; i < NUMBER_DEFINED_TRIGGERS; i++)
      {
        target_label->ranguvannja_set_dt_source_plus[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_set_dt_source_plus[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_set_dt_source_plus[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_set_dt_source_plus[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_set_dt_source_plus[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_set_dt_source_plus[N_BIG*i+5] &= ~maska_1[5];

        target_label->ranguvannja_set_dt_source_minus[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_set_dt_source_minus[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_set_dt_source_minus[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_set_dt_source_minus[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_set_dt_source_minus[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_set_dt_source_minus[N_BIG*i+5] &= ~maska_1[5];

        target_label->ranguvannja_reset_dt_source_plus[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+5] &= ~maska_1[5];

        target_label->ranguvannja_reset_dt_source_minus[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+5] &= ~maska_1[5];
      }
    }

    //Перевіряємо, чи АЧР-ЧАПВ зараз знято з конфігурації
    if ((target_label->configuration & (1<<ACHR_CHAPV_BIT_CONFIGURATION)) == 0)
    {
      //Виводим АЧР-ЧАПВ
      target_label->control_achr_chapv &= (unsigned int)(~(CTR_ACHR | CTR_CHAPV));

      //Виводим захисти АЧР з УРОВ
      target_label->control_urov &= (unsigned int)(~CTR_UROV_STARTED_FROM_ACHR);
      
      //Формуємо маки функцій АЧР-ЧАПВ
      maska[0] = 0;
      maska[1] = 0;
      for (int i = 0; i < NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_INPUT; i++)
        _SET_BIT(
                 maska, 
                 (
                  NUMBER_GENERAL_SIGNAL_FOR_RANG_INPUT + 
                  NUMBER_MTZ_SIGNAL_FOR_RANG_INPUT     +
                  NUMBER_ZDZ_SIGNAL_FOR_RANG_INPUT     +
                  NUMBER_ZZ_SIGNAL_FOR_RANG_INPUT      +
                  NUMBER_APV_SIGNAL_FOR_RANG_INPUT     +
                  NUMBER_APV_ZMN_SIGNAL_FOR_RANG_INPUT +
                  i
                 )
                );
     
      maska_1[0] = 0;
      maska_1[1] = 0;
      maska_1[2] = 0;
      maska_1[3] = 0;
      maska_1[4] = 0;
      maska_1[5] = 0;
      for (int i = 0; i < NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG; i++)
        _SET_BIT(
                 maska_1, 
                 (
                  NUMBER_GENERAL_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + 
                  NUMBER_MTZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG     +
                  NUMBER_ZDZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG     +
                  NUMBER_ZZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG      +
                  NUMBER_APV_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG     +
                  NUMBER_APV_ZMN_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG +
                  i
                 )
                );

      maska_2 = 0;
      for (int i = 0; i < NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_BUTTON; i++) maska_2 = (maska_2 <<1) + 0x1;
      maska_2 =(
                maska_2 << (
                            NUMBER_GENERAL_SIGNAL_FOR_RANG_BUTTON + 
                            NUMBER_MTZ_SIGNAL_FOR_RANG_BUTTON     +
                            NUMBER_ZDZ_SIGNAL_FOR_RANG_BUTTON     +
                            NUMBER_ZZ_SIGNAL_FOR_RANG_BUTTON      +
                            NUMBER_APV_SIGNAL_FOR_RANG_BUTTON     +
                            NUMBER_APV_ZMN_SIGNAL_FOR_RANG_BUTTON
                           )
               );

      //Знімаємо всі функції для ранжування входів, які відповідають за АЧР-ЧАПВ
      for (int i = 0; i < NUMBER_DEFINED_BUTTONS; i++)
        target_label->ranguvannja_buttons[i] &= ~maska_2;
      //Знімаємо всі функції для ранжування входів, які відповідають за АЧР-ЧАПВ
      for (int i = 0; i < NUMBER_INPUTS; i++)
      {
        target_label->ranguvannja_inputs[N_SMALL*i  ] &= ~maska[0];
        target_label->ranguvannja_inputs[N_SMALL*i+1] &= ~maska[1];
      }
      //Знімаємо всі функції для ранжування виходів, які відповідають за АЧР-ЧАПВ
      for (int i = 0; i < NUMBER_OUTPUTS; i++)
      {
        target_label->ranguvannja_outputs[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_outputs[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_outputs[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_outputs[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_outputs[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_outputs[N_BIG*i+5] &= ~maska_1[5];
      }
      //Знімаємо всі функції для ранжування світоіндикаторів, які відповідають за АЧР-ЧАПВ
      for (int i = 0; i < NUMBER_LEDS; i++)
      {
        target_label->ranguvannja_leds[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_leds[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_leds[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_leds[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_leds[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_leds[N_BIG*i+5] &= ~maska_1[5];
      }
      //Знімаємо всі функції для ранжування дискретного реєстратора, які відповідають за АЧР-ЧАПВ
      target_label->ranguvannja_digital_registrator[0] &= ~maska_1[0];
      target_label->ranguvannja_digital_registrator[1] &= ~maska_1[1];
      target_label->ranguvannja_digital_registrator[2] &= ~maska_1[2];
      target_label->ranguvannja_digital_registrator[3] &= ~maska_1[3];
      target_label->ranguvannja_digital_registrator[4] &= ~maska_1[4];
      target_label->ranguvannja_digital_registrator[5] &= ~maska_1[5];
      //Знімаємо всі функції для ранжування аналогового реєстратора, які відповідають за АЧР-ЧАПВ
      target_label->ranguvannja_analog_registrator[0] &= ~maska_1[0];
      target_label->ranguvannja_analog_registrator[1] &= ~maska_1[1];
      target_label->ranguvannja_analog_registrator[2] &= ~maska_1[2];
      target_label->ranguvannja_analog_registrator[3] &= ~maska_1[3];
      target_label->ranguvannja_analog_registrator[4] &= ~maska_1[4];
      target_label->ranguvannja_analog_registrator[5] &= ~maska_1[5];
      //Знімаємо всі функції для ранжування оприділювальних функцій, які відповідають за АЧР-ЧАПВ
      for (int i = 0; i < NUMBER_DEFINED_FUNCTIONS; i++)
      {
        target_label->ranguvannja_df_source_plus[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_df_source_plus[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_df_source_plus[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_df_source_plus[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_df_source_plus[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_df_source_plus[N_BIG*i+5] &= ~maska_1[5];

        target_label->ranguvannja_df_source_minus[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_df_source_minus[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_df_source_minus[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_df_source_minus[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_df_source_minus[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_df_source_minus[N_BIG*i+5] &= ~maska_1[5];

        target_label->ranguvannja_df_source_blk[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_df_source_blk[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_df_source_blk[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_df_source_blk[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_df_source_blk[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_df_source_blk[N_BIG*i+5] &= ~maska_1[5];
      }
      //Знімаємо всі функції для ранжування оприділювальних триґерів, які відповідають за АЧР-ЧАПВ
      for (int i = 0; i < NUMBER_DEFINED_TRIGGERS; i++)
      {
        target_label->ranguvannja_set_dt_source_plus[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_set_dt_source_plus[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_set_dt_source_plus[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_set_dt_source_plus[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_set_dt_source_plus[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_set_dt_source_plus[N_BIG*i+5] &= ~maska_1[5];

        target_label->ranguvannja_set_dt_source_minus[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_set_dt_source_minus[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_set_dt_source_minus[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_set_dt_source_minus[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_set_dt_source_minus[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_set_dt_source_minus[N_BIG*i+5] &= ~maska_1[5];

        target_label->ranguvannja_reset_dt_source_plus[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+5] &= ~maska_1[5];

        target_label->ranguvannja_reset_dt_source_minus[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+5] &= ~maska_1[5];
      }
    }

    //Перевіряємо, чи УРОВ зараз знято з конфігурації
    if ((target_label->configuration & (1<<UROV_BIT_CONFIGURATION)) == 0)
    {
      //Виводим УРОВ
      target_label->control_urov &= (unsigned int)(~CTR_UROV_STATE);
   
        //Формуємо маки функцій УРОВ
      maska[0] = 0;
      maska[1] = 0;
      for (int i = 0; i < NUMBER_UROV_SIGNAL_FOR_RANG_INPUT; i++)
        _SET_BIT(
                 maska, 
                 (
                  NUMBER_GENERAL_SIGNAL_FOR_RANG_INPUT    + 
                  NUMBER_MTZ_SIGNAL_FOR_RANG_INPUT        +
                  NUMBER_ZDZ_SIGNAL_FOR_RANG_INPUT        +
                  NUMBER_ZZ_SIGNAL_FOR_RANG_INPUT         +
                  NUMBER_APV_SIGNAL_FOR_RANG_INPUT        +
                  NUMBER_APV_ZMN_SIGNAL_FOR_RANG_INPUT    +
                  NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_INPUT +
                  i
                 )
                );
     
      maska_1[0] = 0;
      maska_1[1] = 0;
      maska_1[2] = 0;
      maska_1[3] = 0;
      maska_1[4] = 0;
      maska_1[5] = 0;
      for (int i = 0; i < NUMBER_UROV_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG; i++)
        _SET_BIT(
                 maska_1, 
                 (
                  NUMBER_GENERAL_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG    + 
                  NUMBER_MTZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG        +
                  NUMBER_ZDZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG        +
                  NUMBER_ZZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG         +
                  NUMBER_APV_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG        +
                  NUMBER_APV_ZMN_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG    +
                  NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG +
                  i
                 )
                );

      maska_2 = 0;
      for (int i = 0; i < NUMBER_UROV_SIGNAL_FOR_RANG_BUTTON; i++) maska_2 = (maska_2 <<1) + 0x1;
      maska_2 =(
                maska_2 << (
                            NUMBER_GENERAL_SIGNAL_FOR_RANG_BUTTON    + 
                            NUMBER_MTZ_SIGNAL_FOR_RANG_BUTTON        +
                            NUMBER_ZDZ_SIGNAL_FOR_RANG_BUTTON        +
                            NUMBER_ZZ_SIGNAL_FOR_RANG_BUTTON         +
                            NUMBER_APV_SIGNAL_FOR_RANG_BUTTON        +
                            NUMBER_APV_ZMN_SIGNAL_FOR_RANG_BUTTON    +
                            NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_BUTTON
                           )
               );

      //Знімаємо всі функції для ранжування входів, які відповідають за УРОВ
      for (int i = 0; i < NUMBER_DEFINED_BUTTONS; i++)
        target_label->ranguvannja_buttons[i] &= ~maska_2;
      //Знімаємо всі функції для ранжування входів, які відповідають за УРОВ
      for (int i = 0; i < NUMBER_INPUTS; i++)
      {
        target_label->ranguvannja_inputs[N_SMALL*i  ] &= ~maska[0];
        target_label->ranguvannja_inputs[N_SMALL*i+1] &= ~maska[1];
      }
      //Знімаємо всі функції для ранжування виходів, які відповідають за УРОВ
      for (int i = 0; i < NUMBER_OUTPUTS; i++)
      {
        target_label->ranguvannja_outputs[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_outputs[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_outputs[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_outputs[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_outputs[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_outputs[N_BIG*i+5] &= ~maska_1[5];
      }
      //Знімаємо всі функції для ранжування світоіндикаторів, які відповідають за УРОВ
      for (int i = 0; i < NUMBER_LEDS; i++)
      {
        target_label->ranguvannja_leds[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_leds[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_leds[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_leds[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_leds[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_leds[N_BIG*i+5] &= ~maska_1[5];
      }
      //Знімаємо всі функції для ранжування дискретного реєстратора, які відповідають за УРОВ
      target_label->ranguvannja_digital_registrator[0] &= ~maska_1[0];
      target_label->ranguvannja_digital_registrator[1] &= ~maska_1[1];
      target_label->ranguvannja_digital_registrator[2] &= ~maska_1[2];
      target_label->ranguvannja_digital_registrator[3] &= ~maska_1[3];
      target_label->ranguvannja_digital_registrator[4] &= ~maska_1[4];
      target_label->ranguvannja_digital_registrator[5] &= ~maska_1[5];
      //Знімаємо всі функції для ранжування аналогового реєстратора, які відповідають за УРОВ
      target_label->ranguvannja_analog_registrator[0] &= ~maska_1[0];
      target_label->ranguvannja_analog_registrator[1] &= ~maska_1[1];
      target_label->ranguvannja_analog_registrator[2] &= ~maska_1[2];
      target_label->ranguvannja_analog_registrator[3] &= ~maska_1[3];
      target_label->ranguvannja_analog_registrator[4] &= ~maska_1[4];
      target_label->ranguvannja_analog_registrator[5] &= ~maska_1[5];
      //Знімаємо всі функції для ранжування оприділювальних функцій, які відповідають за УРОВ
      for (int i = 0; i < NUMBER_DEFINED_FUNCTIONS; i++)
      {
        target_label->ranguvannja_df_source_plus[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_df_source_plus[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_df_source_plus[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_df_source_plus[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_df_source_plus[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_df_source_plus[N_BIG*i+5] &= ~maska_1[5];

        target_label->ranguvannja_df_source_minus[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_df_source_minus[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_df_source_minus[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_df_source_minus[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_df_source_minus[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_df_source_minus[N_BIG*i+5] &= ~maska_1[5];

        target_label->ranguvannja_df_source_blk[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_df_source_blk[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_df_source_blk[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_df_source_blk[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_df_source_blk[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_df_source_blk[N_BIG*i+5] &= ~maska_1[5];
      }
      //Знімаємо всі функції для ранжування оприділювальних триґерів, які відповідають за УРОВ
      for (int i = 0; i < NUMBER_DEFINED_TRIGGERS; i++)
      {
        target_label->ranguvannja_set_dt_source_plus[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_set_dt_source_plus[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_set_dt_source_plus[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_set_dt_source_plus[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_set_dt_source_plus[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_set_dt_source_plus[N_BIG*i+5] &= ~maska_1[5];

        target_label->ranguvannja_set_dt_source_minus[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_set_dt_source_minus[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_set_dt_source_minus[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_set_dt_source_minus[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_set_dt_source_minus[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_set_dt_source_minus[N_BIG*i+5] &= ~maska_1[5];

        target_label->ranguvannja_reset_dt_source_plus[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+5] &= ~maska_1[5];

        target_label->ranguvannja_reset_dt_source_minus[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+5] &= ~maska_1[5];
      }
    }

    //Перевіряємо, чи ЗОП(КОФ) зараз знято з конфігурації
    if ((target_label->configuration & (1<<ZOP_BIT_CONFIGURATION)) == 0)
    {
      //Виводим ЗОП(КОФ)
      target_label->control_zop &= (unsigned int)(~CTR_ZOP_STATE);
   
      //Виводим захисти ЗОП(КОФ) з УРОВ
      target_label->control_urov &= (unsigned int)(~CTR_UROV_STARTED_FROM_ZOP1);

      //Формуємо маки функцій ЗОП(КОФ)
      maska[0] = 0;
      maska[1] = 0;
      for (int i = 0; i < NUMBER_ZOP_SIGNAL_FOR_RANG_INPUT; i++)
        _SET_BIT(
                 maska, 
                 (
                  NUMBER_GENERAL_SIGNAL_FOR_RANG_INPUT    + 
                  NUMBER_MTZ_SIGNAL_FOR_RANG_INPUT        +
                  NUMBER_ZDZ_SIGNAL_FOR_RANG_INPUT        +
                  NUMBER_ZZ_SIGNAL_FOR_RANG_INPUT         +
                  NUMBER_APV_SIGNAL_FOR_RANG_INPUT        +
                  NUMBER_APV_ZMN_SIGNAL_FOR_RANG_INPUT    +
                  NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_INPUT +
                  NUMBER_UROV_SIGNAL_FOR_RANG_INPUT       +
                  i
                 )
                );
     
      maska_1[0] = 0;
      maska_1[1] = 0;
      maska_1[2] = 0;
      maska_1[3] = 0;
      maska_1[4] = 0;
      maska_1[5] = 0;
      for (int i = 0; i < NUMBER_ZOP_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG; i++)
        _SET_BIT(
                 maska_1, 
                 (
                  NUMBER_GENERAL_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG    + 
                  NUMBER_MTZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG        +
                  NUMBER_ZDZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG        +
                  NUMBER_ZZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG         +
                  NUMBER_APV_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG        +
                  NUMBER_APV_ZMN_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG    +
                  NUMBER_UROV_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG       +
                  NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG +
                  i
                 )
                );

      maska_2 = 0;
      for (int i = 0; i < NUMBER_ZOP_SIGNAL_FOR_RANG_BUTTON; i++) maska_2 = (maska_2 <<1) + 0x1;
      maska_2 =(
                maska_2 << (
                            NUMBER_GENERAL_SIGNAL_FOR_RANG_BUTTON    + 
                            NUMBER_MTZ_SIGNAL_FOR_RANG_BUTTON        +
                            NUMBER_ZDZ_SIGNAL_FOR_RANG_BUTTON        +
                            NUMBER_ZZ_SIGNAL_FOR_RANG_BUTTON         +
                            NUMBER_APV_SIGNAL_FOR_RANG_BUTTON        +
                            NUMBER_APV_ZMN_SIGNAL_FOR_RANG_BUTTON    +
                            NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_BUTTON +
                            NUMBER_UROV_SIGNAL_FOR_RANG_BUTTON
                           )
               );

      //Знімаємо всі функції для ранжування входів, які відповідають за ЗОП(КОФ)
      for (int i = 0; i < NUMBER_DEFINED_BUTTONS; i++)
        target_label->ranguvannja_buttons[i] &= ~maska_2;
      //Знімаємо всі функції для ранжування входів, які відповідають за ЗОП(КОФ)
      for (int i = 0; i < NUMBER_INPUTS; i++)
      {
        target_label->ranguvannja_inputs[N_SMALL*i  ] &= ~maska[0];
        target_label->ranguvannja_inputs[N_SMALL*i+1] &= ~maska[1];
      }
      //Знімаємо всі функції для ранжування виходів, які відповідають за ЗОП(КОФ)
      for (int i = 0; i < NUMBER_OUTPUTS; i++)
      {
        target_label->ranguvannja_outputs[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_outputs[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_outputs[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_outputs[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_outputs[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_outputs[N_BIG*i+5] &= ~maska_1[5];
      }
      //Знімаємо всі функції для ранжування світоіндикаторів, які відповідають за ЗОП(КОФ)
      for (int i = 0; i < NUMBER_LEDS; i++)
      {
        target_label->ranguvannja_leds[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_leds[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_leds[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_leds[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_leds[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_leds[N_BIG*i+5] &= ~maska_1[5];
      }
      //Знімаємо всі функції для ранжування дискретного реєстратора, які відповідають за ЗОП(КОФ)
      target_label->ranguvannja_digital_registrator[0] &= ~maska_1[0];
      target_label->ranguvannja_digital_registrator[1] &= ~maska_1[1];
      target_label->ranguvannja_digital_registrator[2] &= ~maska_1[2];
      target_label->ranguvannja_digital_registrator[3] &= ~maska_1[3];
      target_label->ranguvannja_digital_registrator[4] &= ~maska_1[4];
      target_label->ranguvannja_digital_registrator[5] &= ~maska_1[5];
      //Знімаємо всі функції для ранжування аналогового реєстратора, які відповідають за ЗОП(КОФ)
      target_label->ranguvannja_analog_registrator[0] &= ~maska_1[0];
      target_label->ranguvannja_analog_registrator[1] &= ~maska_1[1];
      target_label->ranguvannja_analog_registrator[2] &= ~maska_1[2];
      target_label->ranguvannja_analog_registrator[3] &= ~maska_1[3];
      target_label->ranguvannja_analog_registrator[4] &= ~maska_1[4];
      target_label->ranguvannja_analog_registrator[5] &= ~maska_1[5];
      //Знімаємо всі функції для ранжування оприділювальних функцій, які відповідають за ЗОП(КОФ)
      for (int i = 0; i < NUMBER_DEFINED_FUNCTIONS; i++)
      {
        target_label->ranguvannja_df_source_plus[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_df_source_plus[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_df_source_plus[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_df_source_plus[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_df_source_plus[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_df_source_plus[N_BIG*i+5] &= ~maska_1[5];

        target_label->ranguvannja_df_source_minus[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_df_source_minus[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_df_source_minus[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_df_source_minus[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_df_source_minus[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_df_source_minus[N_BIG*i+5] &= ~maska_1[5];

        target_label->ranguvannja_df_source_blk[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_df_source_blk[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_df_source_blk[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_df_source_blk[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_df_source_blk[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_df_source_blk[N_BIG*i+5] &= ~maska_1[5];
      }
      //Знімаємо всі функції для ранжування оприділювальних триґерів, які відповідають за ЗОП(КОФ)
      for (int i = 0; i < NUMBER_DEFINED_TRIGGERS; i++)
      {
        target_label->ranguvannja_set_dt_source_plus[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_set_dt_source_plus[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_set_dt_source_plus[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_set_dt_source_plus[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_set_dt_source_plus[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_set_dt_source_plus[N_BIG*i+5] &= ~maska_1[5];

        target_label->ranguvannja_set_dt_source_minus[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_set_dt_source_minus[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_set_dt_source_minus[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_set_dt_source_minus[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_set_dt_source_minus[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_set_dt_source_minus[N_BIG*i+5] &= ~maska_1[5];

        target_label->ranguvannja_reset_dt_source_plus[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+5] &= ~maska_1[5];

        target_label->ranguvannja_reset_dt_source_minus[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+5] &= ~maska_1[5];
      }
    }

    //Перевіряємо, чи Umin зараз знято з конфігурації
    if ((target_label->configuration & (1<<UMIN_BIT_CONFIGURATION)) == 0)
    {
      //Виводим ступені Umin
      target_label->control_Umin &= (unsigned int)(~(CTR_UMIN1 | CTR_UMIN2));
   
      //Виводим ступені Umin з УРОВ
      target_label->control_urov &= (unsigned int)(~(CTR_UROV_STARTED_FROM_UMIN1 | CTR_UROV_STARTED_FROM_UMIN2));
      
      //Формуємо маски функцій Umin
      maska[0] = 0;
      maska[1] = 0;
      for (int i = 0; i < NUMBER_UMIN_SIGNAL_FOR_RANG_INPUT; i++)
        _SET_BIT(
                 maska, 
                 (
                  NUMBER_GENERAL_SIGNAL_FOR_RANG_INPUT    + 
                  NUMBER_MTZ_SIGNAL_FOR_RANG_INPUT        +
                  NUMBER_ZDZ_SIGNAL_FOR_RANG_INPUT        +
                  NUMBER_ZZ_SIGNAL_FOR_RANG_INPUT         +
                  NUMBER_APV_SIGNAL_FOR_RANG_INPUT        +
                  NUMBER_APV_ZMN_SIGNAL_FOR_RANG_INPUT    +
                  NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_INPUT +
                  NUMBER_UROV_SIGNAL_FOR_RANG_INPUT       +
                  NUMBER_ZOP_SIGNAL_FOR_RANG_INPUT        +
                  i
                 )
                );
     
      maska_1[0] = 0;
      maska_1[1] = 0;
      maska_1[2] = 0;
      maska_1[3] = 0;
      maska_1[4] = 0;
      maska_1[5] = 0;
      for (int i = 0; i < NUMBER_UMIN_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG; i++)
        _SET_BIT(
                 maska_1, 
                 (
                  NUMBER_GENERAL_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG    + 
                  NUMBER_MTZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG        +
                  NUMBER_ZDZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG        +
                  NUMBER_ZZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG         +
                  NUMBER_APV_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG        +
                  NUMBER_APV_ZMN_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG    +
                  NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG +
                  NUMBER_UROV_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG       +
                  NUMBER_ZOP_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG       +
                  i
                 )
                );

      maska_2 = 0;
      for (int i = 0; i < NUMBER_UMIN_SIGNAL_FOR_RANG_BUTTON; i++) maska_2 = (maska_2 <<1) + 0x1;
      maska_2 =(
                maska_2 << (
                            NUMBER_GENERAL_SIGNAL_FOR_RANG_BUTTON    + 
                            NUMBER_MTZ_SIGNAL_FOR_RANG_BUTTON        +
                            NUMBER_ZDZ_SIGNAL_FOR_RANG_BUTTON        +
                            NUMBER_ZZ_SIGNAL_FOR_RANG_BUTTON         +
                            NUMBER_APV_SIGNAL_FOR_RANG_BUTTON        +
                            NUMBER_APV_ZMN_SIGNAL_FOR_RANG_BUTTON    +
                            NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_BUTTON +
                            NUMBER_UROV_SIGNAL_FOR_RANG_BUTTON       +
                            NUMBER_ZOP_SIGNAL_FOR_RANG_BUTTON
                           )
               );

      //Знімаємо всі функції для ранжування входів, які відповідають за Umin
      for (int i = 0; i < NUMBER_DEFINED_BUTTONS; i++)
        target_label->ranguvannja_buttons[i] &= ~maska_2;
      //Знімаємо всі функції для ранжування входів, які відповідають за Umin
      for (int i = 0; i < NUMBER_INPUTS; i++)
      {
        target_label->ranguvannja_inputs[N_SMALL*i  ] &= ~maska[0];
        target_label->ranguvannja_inputs[N_SMALL*i+1] &= ~maska[1];
      }
      //Знімаємо всі функції для ранжування виходів, які відповідають за Umin
      for (int i = 0; i < NUMBER_OUTPUTS; i++)
      {
        target_label->ranguvannja_outputs[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_outputs[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_outputs[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_outputs[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_outputs[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_outputs[N_BIG*i+5] &= ~maska_1[5];
      }
      //Знімаємо всі функції для ранжування світоіндикаторів, які відповідають за Umin
      for (int i = 0; i < NUMBER_LEDS; i++)
      {
        target_label->ranguvannja_leds[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_leds[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_leds[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_leds[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_leds[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_leds[N_BIG*i+5] &= ~maska_1[5];
      }
      //Знімаємо всі функції для ранжування дискретного реєстратора, які відповідають за Umin
      target_label->ranguvannja_digital_registrator[0] &= ~maska_1[0];
      target_label->ranguvannja_digital_registrator[1] &= ~maska_1[1];
      target_label->ranguvannja_digital_registrator[2] &= ~maska_1[2];
      target_label->ranguvannja_digital_registrator[3] &= ~maska_1[3];
      target_label->ranguvannja_digital_registrator[4] &= ~maska_1[4];
      target_label->ranguvannja_digital_registrator[5] &= ~maska_1[5];
      //Знімаємо всі функції для ранжування аналогового реєстратора, які відповідають за Umin
      target_label->ranguvannja_analog_registrator[0] &= ~maska_1[0];
      target_label->ranguvannja_analog_registrator[1] &= ~maska_1[1];
      target_label->ranguvannja_analog_registrator[2] &= ~maska_1[2];
      target_label->ranguvannja_analog_registrator[3] &= ~maska_1[3];
      target_label->ranguvannja_analog_registrator[4] &= ~maska_1[4];
      target_label->ranguvannja_analog_registrator[5] &= ~maska_1[5];
      //Знімаємо всі функції для ранжування оприділювальних функцій, які відповідають за Umin
      for (int i = 0; i < NUMBER_DEFINED_FUNCTIONS; i++)
      {
        target_label->ranguvannja_df_source_plus[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_df_source_plus[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_df_source_plus[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_df_source_plus[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_df_source_plus[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_df_source_plus[N_BIG*i+5] &= ~maska_1[5];

        target_label->ranguvannja_df_source_minus[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_df_source_minus[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_df_source_minus[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_df_source_minus[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_df_source_minus[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_df_source_minus[N_BIG*i+5] &= ~maska_1[5];

        target_label->ranguvannja_df_source_blk[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_df_source_blk[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_df_source_blk[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_df_source_blk[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_df_source_blk[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_df_source_blk[N_BIG*i+5] &= ~maska_1[5];
      }
      //Знімаємо всі функції для ранжування оприділювальних триґерів, які відповідають за Umin
      for (int i = 0; i < NUMBER_DEFINED_TRIGGERS; i++)
      {
        target_label->ranguvannja_set_dt_source_plus[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_set_dt_source_plus[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_set_dt_source_plus[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_set_dt_source_plus[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_set_dt_source_plus[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_set_dt_source_plus[N_BIG*i+5] &= ~maska_1[5];

        target_label->ranguvannja_set_dt_source_minus[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_set_dt_source_minus[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_set_dt_source_minus[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_set_dt_source_minus[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_set_dt_source_minus[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_set_dt_source_minus[N_BIG*i+5] &= ~maska_1[5];

        target_label->ranguvannja_reset_dt_source_plus[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+5] &= ~maska_1[5];

        target_label->ranguvannja_reset_dt_source_minus[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+5] &= ~maska_1[5];
      }
    }

    //Перевіряємо, чи Umax зараз знято з конфігурації
    if ((target_label->configuration & (1<<UMAX_BIT_CONFIGURATION)) == 0)
    {
      //Виводим ступені Umax
      target_label->control_Umax &= (unsigned int)(~(CTR_UMAX1 | CTR_UMAX2));

      //Виводим ступені Umin з УРОВ
      target_label->control_urov &= (unsigned int)(~(CTR_UROV_STARTED_FROM_UMAX1 | CTR_UROV_STARTED_FROM_UMAX2));
   
      //Формуємо маски функцій Umax
      maska[0] = 0;
      maska[1] = 0;
      for (int i = 0; i < NUMBER_UMAX_SIGNAL_FOR_RANG_INPUT; i++)
        _SET_BIT(
                 maska, 
                 (
                  NUMBER_GENERAL_SIGNAL_FOR_RANG_INPUT    + 
                  NUMBER_MTZ_SIGNAL_FOR_RANG_INPUT        +
                  NUMBER_ZDZ_SIGNAL_FOR_RANG_INPUT        +
                  NUMBER_ZZ_SIGNAL_FOR_RANG_INPUT         +
                  NUMBER_APV_SIGNAL_FOR_RANG_INPUT        +
                  NUMBER_APV_ZMN_SIGNAL_FOR_RANG_INPUT    +
                  NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_INPUT +
                  NUMBER_UROV_SIGNAL_FOR_RANG_INPUT       +
                  NUMBER_ZOP_SIGNAL_FOR_RANG_INPUT        +
                  NUMBER_UMIN_SIGNAL_FOR_RANG_INPUT       +
                  i
                 )
                );
     
      maska_1[0] = 0;
      maska_1[1] = 0;
      maska_1[2] = 0;
      maska_1[3] = 0;
      maska_1[4] = 0;
      maska_1[5] = 0;
      for (int i = 0; i < NUMBER_UMAX_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG; i++)
        _SET_BIT(
                 maska_1, 
                 (
                  NUMBER_GENERAL_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG    + 
                  NUMBER_MTZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG        +
                  NUMBER_ZDZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG        +
                  NUMBER_ZZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG         +
                  NUMBER_APV_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG        +
                  NUMBER_APV_ZMN_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG    +
                  NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG +
                  NUMBER_UROV_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG       +
                  NUMBER_ZOP_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG        +
                  NUMBER_UMIN_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG       +
                  i
                 )
                );


      maska_2 = 0;
      for (int i = 0; i < NUMBER_UMAX_SIGNAL_FOR_RANG_BUTTON; i++) maska_2 = (maska_2 <<1) + 0x1;
      maska_2 =(
                maska_2 << (
                            NUMBER_GENERAL_SIGNAL_FOR_RANG_BUTTON    + 
                            NUMBER_MTZ_SIGNAL_FOR_RANG_BUTTON        +
                            NUMBER_ZDZ_SIGNAL_FOR_RANG_BUTTON        +
                            NUMBER_ZZ_SIGNAL_FOR_RANG_BUTTON         +
                            NUMBER_APV_SIGNAL_FOR_RANG_BUTTON        +
                            NUMBER_APV_ZMN_SIGNAL_FOR_RANG_BUTTON    +
                            NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_BUTTON +
                            NUMBER_UROV_SIGNAL_FOR_RANG_BUTTON       +
                            NUMBER_ZOP_SIGNAL_FOR_RANG_BUTTON        +
                            NUMBER_UMIN_SIGNAL_FOR_RANG_BUTTON
                           )
               );

      //Знімаємо всі функції для ранжування входів, які відповідають за Umax
      for (int i = 0; i < NUMBER_DEFINED_BUTTONS; i++)
        target_label->ranguvannja_buttons[i] &= ~maska_2;
      //Знімаємо всі функції для ранжування входів, які відповідають за Umax
      for (int i = 0; i < NUMBER_INPUTS; i++)
      {
        target_label->ranguvannja_inputs[N_SMALL*i  ] &= ~maska[0];
        target_label->ranguvannja_inputs[N_SMALL*i+1] &= ~maska[1];
      }
      //Знімаємо всі функції для ранжування виходів, які відповідають за Umax
      for (int i = 0; i < NUMBER_OUTPUTS; i++)
      {
        target_label->ranguvannja_outputs[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_outputs[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_outputs[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_outputs[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_outputs[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_outputs[N_BIG*i+5] &= ~maska_1[5];
      }
      //Знімаємо всі функції для ранжування світоіндикаторів, які відповідають за Umax
      for (int i = 0; i < NUMBER_LEDS; i++)
      {
        target_label->ranguvannja_leds[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_leds[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_leds[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_leds[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_leds[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_leds[N_BIG*i+5] &= ~maska_1[5];
      }
      //Знімаємо всі функції для ранжування дискретного реєстратора, які відповідають за Umax
      target_label->ranguvannja_digital_registrator[0] &= ~maska_1[0];
      target_label->ranguvannja_digital_registrator[1] &= ~maska_1[1];
      target_label->ranguvannja_digital_registrator[2] &= ~maska_1[2];
      target_label->ranguvannja_digital_registrator[3] &= ~maska_1[3];
      target_label->ranguvannja_digital_registrator[4] &= ~maska_1[4];
      target_label->ranguvannja_digital_registrator[5] &= ~maska_1[5];
      //Знімаємо всі функції для ранжування аналогового реєстратора, які відповідають за Umax
      target_label->ranguvannja_analog_registrator[0] &= ~maska_1[0];
      target_label->ranguvannja_analog_registrator[1] &= ~maska_1[1];
      target_label->ranguvannja_analog_registrator[2] &= ~maska_1[2];
      target_label->ranguvannja_analog_registrator[3] &= ~maska_1[3];
      target_label->ranguvannja_analog_registrator[4] &= ~maska_1[4];
      target_label->ranguvannja_analog_registrator[5] &= ~maska_1[5];
      //Знімаємо всі функції для ранжування оприділювальних функцій, які відповідають за Umax
      for (int i = 0; i < NUMBER_DEFINED_FUNCTIONS; i++)
      {
        target_label->ranguvannja_df_source_plus[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_df_source_plus[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_df_source_plus[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_df_source_plus[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_df_source_plus[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_df_source_plus[N_BIG*i+5] &= ~maska_1[5];

        target_label->ranguvannja_df_source_minus[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_df_source_minus[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_df_source_minus[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_df_source_minus[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_df_source_minus[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_df_source_minus[N_BIG*i+5] &= ~maska_1[5];

        target_label->ranguvannja_df_source_blk[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_df_source_blk[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_df_source_blk[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_df_source_blk[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_df_source_blk[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_df_source_blk[N_BIG*i+5] &= ~maska_1[5];
      }
      //Знімаємо всі функції для ранжування оприділювальних триґерів, які відповідають за Umax
      for (int i = 0; i < NUMBER_DEFINED_TRIGGERS; i++)
      {
        target_label->ranguvannja_set_dt_source_plus[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_set_dt_source_plus[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_set_dt_source_plus[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_set_dt_source_plus[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_set_dt_source_plus[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_set_dt_source_plus[N_BIG*i+5] &= ~maska_1[5];

        target_label->ranguvannja_set_dt_source_minus[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_set_dt_source_minus[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_set_dt_source_minus[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_set_dt_source_minus[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_set_dt_source_minus[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_set_dt_source_minus[N_BIG*i+5] &= ~maska_1[5];

        target_label->ranguvannja_reset_dt_source_plus[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+5] &= ~maska_1[5];

        target_label->ranguvannja_reset_dt_source_minus[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+5] &= ~maska_1[5];
      }
    }

    //Перевіряємо, чи АВР зараз знято з конфігурації
    if ((target_label->configuration & (1<<AVR_BIT_CONFIGURATION)) == 0)
    {
      //Виводим ступені АВР
      target_label->control_avr &= (unsigned int)(~CTR_AVR);
   
      //Формуємо маски функцій АВР
      maska[0] = 0;
      maska[1] = 0;
      for (int i = 0; i < NUMBER_AVR_SIGNAL_FOR_RANG_INPUT; i++)
        _SET_BIT(
                 maska, 
                 (
                  NUMBER_GENERAL_SIGNAL_FOR_RANG_INPUT    + 
                  NUMBER_MTZ_SIGNAL_FOR_RANG_INPUT        +
                  NUMBER_ZDZ_SIGNAL_FOR_RANG_INPUT        +
                  NUMBER_ZZ_SIGNAL_FOR_RANG_INPUT         +
                  NUMBER_APV_SIGNAL_FOR_RANG_INPUT        +
                  NUMBER_APV_ZMN_SIGNAL_FOR_RANG_INPUT    +
                  NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_INPUT +
                  NUMBER_UROV_SIGNAL_FOR_RANG_INPUT       +
                  NUMBER_ZOP_SIGNAL_FOR_RANG_INPUT        +
                  NUMBER_UMIN_SIGNAL_FOR_RANG_INPUT       +
                  NUMBER_UMAX_SIGNAL_FOR_RANG_INPUT       +
                  i
                 )
                );
     
      maska_1[0] = 0;
      maska_1[1] = 0;
      maska_1[2] = 0;
      maska_1[3] = 0;
      maska_1[4] = 0;
      maska_1[5] = 0;
      for (int i = 0; i < NUMBER_AVR_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG; i++)
        _SET_BIT(
                 maska_1, 
                 (
                  NUMBER_GENERAL_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG    + 
                  NUMBER_MTZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG        +
                  NUMBER_ZDZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG        +
                  NUMBER_ZZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG         +
                  NUMBER_APV_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG        +
                  NUMBER_APV_ZMN_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG    +
                  NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG +
                  NUMBER_UROV_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG       +
                  NUMBER_ZOP_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG        +
                  NUMBER_UMIN_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG       +
                  NUMBER_UMAX_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG       +
                  i
                 )
                );


      maska_2 = 0;
      for (int i = 0; i < NUMBER_AVR_SIGNAL_FOR_RANG_BUTTON; i++) maska_2 = (maska_2 <<1) + 0x1;
      maska_2 =(
                maska_2 << (
                            NUMBER_GENERAL_SIGNAL_FOR_RANG_BUTTON    + 
                            NUMBER_MTZ_SIGNAL_FOR_RANG_BUTTON        +
                            NUMBER_ZDZ_SIGNAL_FOR_RANG_BUTTON        +
                            NUMBER_ZZ_SIGNAL_FOR_RANG_BUTTON         +
                            NUMBER_APV_SIGNAL_FOR_RANG_BUTTON        +
                            NUMBER_APV_ZMN_SIGNAL_FOR_RANG_BUTTON    +
                            NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_BUTTON +
                            NUMBER_UROV_SIGNAL_FOR_RANG_BUTTON       +
                            NUMBER_ZOP_SIGNAL_FOR_RANG_BUTTON        +
                            NUMBER_UMIN_SIGNAL_FOR_RANG_BUTTON       +
                            NUMBER_UMAX_SIGNAL_FOR_RANG_BUTTON
                           )
               );

      //Знімаємо всі функції для ранжування входів, які відповідають за АВР
      for (int i = 0; i < NUMBER_DEFINED_BUTTONS; i++)
        target_label->ranguvannja_buttons[i] &= ~maska_2;
      //Знімаємо всі функції для ранжування входів, які відповідають за АВР
      for (int i = 0; i < NUMBER_INPUTS; i++)
      {
        target_label->ranguvannja_inputs[N_SMALL*i  ] &= ~maska[0];
        target_label->ranguvannja_inputs[N_SMALL*i+1] &= ~maska[1];
      }
      //Знімаємо всі функції для ранжування виходів, які відповідають за АВР
      for (int i = 0; i < NUMBER_OUTPUTS; i++)
      {
        target_label->ranguvannja_outputs[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_outputs[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_outputs[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_outputs[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_outputs[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_outputs[N_BIG*i+5] &= ~maska_1[5];
      }
      //Знімаємо всі функції для ранжування світоіндикаторів, які відповідають за АВР
      for (int i = 0; i < NUMBER_LEDS; i++)
      {
        target_label->ranguvannja_leds[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_leds[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_leds[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_leds[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_leds[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_leds[N_BIG*i+5] &= ~maska_1[5];
      }
      //Знімаємо всі функції для ранжування дискретного реєстратора, які відповідають за АВР
      target_label->ranguvannja_digital_registrator[0] &= ~maska_1[0];
      target_label->ranguvannja_digital_registrator[1] &= ~maska_1[1];
      target_label->ranguvannja_digital_registrator[2] &= ~maska_1[2];
      target_label->ranguvannja_digital_registrator[3] &= ~maska_1[3];
      target_label->ranguvannja_digital_registrator[4] &= ~maska_1[4];
      target_label->ranguvannja_digital_registrator[5] &= ~maska_1[5];
      //Знімаємо всі функції для ранжування аналогового реєстратора, які відповідають за АВР
      target_label->ranguvannja_analog_registrator[0] &= ~maska_1[0];
      target_label->ranguvannja_analog_registrator[1] &= ~maska_1[1];
      target_label->ranguvannja_analog_registrator[2] &= ~maska_1[2];
      target_label->ranguvannja_analog_registrator[3] &= ~maska_1[3];
      target_label->ranguvannja_analog_registrator[4] &= ~maska_1[4];
      target_label->ranguvannja_analog_registrator[5] &= ~maska_1[5];
      //Знімаємо всі функції для ранжування оприділювальних функцій, які відповідають за АВР
      for (int i = 0; i < NUMBER_DEFINED_FUNCTIONS; i++)
      {
        target_label->ranguvannja_df_source_plus[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_df_source_plus[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_df_source_plus[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_df_source_plus[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_df_source_plus[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_df_source_plus[N_BIG*i+5] &= ~maska_1[5];

        target_label->ranguvannja_df_source_minus[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_df_source_minus[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_df_source_minus[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_df_source_minus[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_df_source_minus[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_df_source_minus[N_BIG*i+5] &= ~maska_1[5];

        target_label->ranguvannja_df_source_blk[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_df_source_blk[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_df_source_blk[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_df_source_blk[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_df_source_blk[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_df_source_blk[N_BIG*i+5] &= ~maska_1[5];
      }
      //Знімаємо всі функції для ранжування оприділювальних триґерів, які відповідають за АВР
      for (int i = 0; i < NUMBER_DEFINED_TRIGGERS; i++)
      {
        target_label->ranguvannja_set_dt_source_plus[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_set_dt_source_plus[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_set_dt_source_plus[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_set_dt_source_plus[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_set_dt_source_plus[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_set_dt_source_plus[N_BIG*i+5] &= ~maska_1[5];

        target_label->ranguvannja_set_dt_source_minus[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_set_dt_source_minus[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_set_dt_source_minus[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_set_dt_source_minus[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_set_dt_source_minus[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_set_dt_source_minus[N_BIG*i+5] &= ~maska_1[5];

        target_label->ranguvannja_reset_dt_source_plus[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+5] &= ~maska_1[5];

        target_label->ranguvannja_reset_dt_source_minus[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+5] &= ~maska_1[5];
      }
    }

    //Перевіряємо, чи "Контроль напруги О/Р живлення" зараз знято з конфігурації
    if ((target_label->configuration & (1<<CONTROL_U_BIT_CONFIGURATION)) == 0)
    {
      //Виводим ступені "Контроль напруги О/Р живлення"
      target_label->control_control_U &= (unsigned int)(~(CTR_U_OL | CTR_U_RL));
   
      //Формуємо маски функцій "Контроль напруги О/Р живлення"
      maska[0] = 0;
      maska[1] = 0;
      for (int i = 0; i < NUMBER_CONTROL_U_SIGNAL_FOR_RANG_INPUT; i++)
        _SET_BIT(
                 maska, 
                 (
                  NUMBER_GENERAL_SIGNAL_FOR_RANG_INPUT    + 
                  NUMBER_MTZ_SIGNAL_FOR_RANG_INPUT        +
                  NUMBER_ZDZ_SIGNAL_FOR_RANG_INPUT        +
                  NUMBER_ZZ_SIGNAL_FOR_RANG_INPUT         +
                  NUMBER_APV_SIGNAL_FOR_RANG_INPUT        +
                  NUMBER_APV_ZMN_SIGNAL_FOR_RANG_INPUT    +
                  NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_INPUT +
                  NUMBER_UROV_SIGNAL_FOR_RANG_INPUT       +
                  NUMBER_ZOP_SIGNAL_FOR_RANG_INPUT        +
                  NUMBER_UMIN_SIGNAL_FOR_RANG_INPUT       +
                  NUMBER_UMAX_SIGNAL_FOR_RANG_INPUT       +
                  NUMBER_AVR_SIGNAL_FOR_RANG_INPUT        +
                  i
                 )
                );
     
      maska_1[0] = 0;
      maska_1[1] = 0;
      maska_1[2] = 0;
      maska_1[3] = 0;
      maska_1[4] = 0;
      maska_1[5] = 0;
      for (int i = 0; i < NUMBER_CONTROL_U_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG; i++)
        _SET_BIT(
                 maska_1, 
                 (
                  NUMBER_GENERAL_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG    + 
                  NUMBER_MTZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG        +
                  NUMBER_ZDZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG        +
                  NUMBER_ZZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG         +
                  NUMBER_APV_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG        +
                  NUMBER_APV_ZMN_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG    +
                  NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG +
                  NUMBER_UROV_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG       +
                  NUMBER_ZOP_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG        +
                  NUMBER_UMIN_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG       +
                  NUMBER_UMAX_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG       +
                  NUMBER_AVR_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG        +
                  i
                 )
                );


      maska_2 = 0;
      for (int i = 0; i < NUMBER_CONTROL_U_SIGNAL_FOR_RANG_BUTTON; i++) maska_2 = (maska_2 <<1) + 0x1;
      maska_2 =(
                maska_2 << (
                            NUMBER_GENERAL_SIGNAL_FOR_RANG_BUTTON    + 
                            NUMBER_MTZ_SIGNAL_FOR_RANG_BUTTON        +
                            NUMBER_ZDZ_SIGNAL_FOR_RANG_BUTTON        +
                            NUMBER_ZZ_SIGNAL_FOR_RANG_BUTTON         +
                            NUMBER_APV_SIGNAL_FOR_RANG_BUTTON        +
                            NUMBER_APV_ZMN_SIGNAL_FOR_RANG_BUTTON    +
                            NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_BUTTON +
                            NUMBER_UROV_SIGNAL_FOR_RANG_BUTTON       +
                            NUMBER_ZOP_SIGNAL_FOR_RANG_BUTTON        +
                            NUMBER_UMIN_SIGNAL_FOR_RANG_BUTTON       +
                            NUMBER_UMAX_SIGNAL_FOR_RANG_BUTTON       +
                            NUMBER_AVR_SIGNAL_FOR_RANG_BUTTON
                           )
               );

      //Знімаємо всі функції для ранжування входів, які відповідають за "Контроль напруги О/Р живлення"
      for (int i = 0; i < NUMBER_DEFINED_BUTTONS; i++)
        target_label->ranguvannja_buttons[i] &= ~maska_2;
      //Знімаємо всі функції для ранжування входів, які відповідають за "Контроль напруги О/Р живлення"
      for (int i = 0; i < NUMBER_INPUTS; i++)
      {
        target_label->ranguvannja_inputs[N_SMALL*i  ] &= ~maska[0];
        target_label->ranguvannja_inputs[N_SMALL*i+1] &= ~maska[1];
      }
      //Знімаємо всі функції для ранжування виходів, які відповідають за "Контроль напруги О/Р живлення"
      for (int i = 0; i < NUMBER_OUTPUTS; i++)
      {
        target_label->ranguvannja_outputs[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_outputs[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_outputs[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_outputs[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_outputs[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_outputs[N_BIG*i+5] &= ~maska_1[5];
      }
      //Знімаємо всі функції для ранжування світоіндикаторів, які відповідають за "Контроль напруги О/Р живлення"
      for (int i = 0; i < NUMBER_LEDS; i++)
      {
        target_label->ranguvannja_leds[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_leds[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_leds[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_leds[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_leds[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_leds[N_BIG*i+5] &= ~maska_1[5];
      }
      //Знімаємо всі функції для ранжування дискретного реєстратора, які відповідають за "Контроль напруги О/Р живлення"
      target_label->ranguvannja_digital_registrator[0] &= ~maska_1[0];
      target_label->ranguvannja_digital_registrator[1] &= ~maska_1[1];
      target_label->ranguvannja_digital_registrator[2] &= ~maska_1[2];
      target_label->ranguvannja_digital_registrator[3] &= ~maska_1[3];
      target_label->ranguvannja_digital_registrator[4] &= ~maska_1[4];
      target_label->ranguvannja_digital_registrator[5] &= ~maska_1[5];
      //Знімаємо всі функції для ранжування аналогового реєстратора, які відповідають за "Контроль напруги О/Р живлення"
      target_label->ranguvannja_analog_registrator[0] &= ~maska_1[0];
      target_label->ranguvannja_analog_registrator[1] &= ~maska_1[1];
      target_label->ranguvannja_analog_registrator[2] &= ~maska_1[2];
      target_label->ranguvannja_analog_registrator[3] &= ~maska_1[3];
      target_label->ranguvannja_analog_registrator[4] &= ~maska_1[4];
      target_label->ranguvannja_analog_registrator[5] &= ~maska_1[5];
      //Знімаємо всі функції для ранжування оприділювальних функцій, які відповідають за "Контроль напруги О/Р живлення"
      for (int i = 0; i < NUMBER_DEFINED_FUNCTIONS; i++)
      {
        target_label->ranguvannja_df_source_plus[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_df_source_plus[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_df_source_plus[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_df_source_plus[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_df_source_plus[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_df_source_plus[N_BIG*i+5] &= ~maska_1[5];

        target_label->ranguvannja_df_source_minus[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_df_source_minus[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_df_source_minus[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_df_source_minus[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_df_source_minus[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_df_source_minus[N_BIG*i+5] &= ~maska_1[5];

        target_label->ranguvannja_df_source_blk[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_df_source_blk[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_df_source_blk[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_df_source_blk[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_df_source_blk[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_df_source_blk[N_BIG*i+5] &= ~maska_1[5];
      }
      //Знімаємо всі функції для ранжування оприділювальних триґерів, які відповідають за "Контроль напруги О/Р живлення"
      for (int i = 0; i < NUMBER_DEFINED_TRIGGERS; i++)
      {
        target_label->ranguvannja_set_dt_source_plus[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_set_dt_source_plus[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_set_dt_source_plus[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_set_dt_source_plus[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_set_dt_source_plus[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_set_dt_source_plus[N_BIG*i+5] &= ~maska_1[5];

        target_label->ranguvannja_set_dt_source_minus[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_set_dt_source_minus[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_set_dt_source_minus[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_set_dt_source_minus[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_set_dt_source_minus[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_set_dt_source_minus[N_BIG*i+5] &= ~maska_1[5];

        target_label->ranguvannja_reset_dt_source_plus[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+5] &= ~maska_1[5];

        target_label->ranguvannja_reset_dt_source_minus[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+5] &= ~maska_1[5];
      }
    }

    //Перевіряємо, чи "Визначення місця пошкодження" зараз знято з конфігурації
    if ((target_label->configuration & (1<<VMP_BIT_CONFIGURATION)) == 0)
    {
      //Виводим ВМП
      target_label->control_vmp &= (unsigned int)(~CTR_VMP_STATE);
    }
  }
  
  return error_window;
}
/*****************************************************/

/*****************************************************/
//Функція обновлення змінних при зміні типу вхідних напруг
/*****************************************************/
void action_after_changing_phase_line(__SETTINGS *target_label)
{
  if ((target_label->control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_3U0_Ubc_TN2) != 0)
  {
    //Виводим 3U0 і НЗЗ
    target_label->control_zz &= (unsigned int)(~(CTR_ZZ1_3U0_STATE | CTR_ZZ1_NZZ_STATE));
    
    //Виводим 3U0 і НЗЗ з УРОВ
    target_label->control_urov &= (unsigned int)(~(CTR_UROV_STARTED_FROM_3U0 | CTR_UROV_STARTED_FROM_NZZ));
      
    unsigned int /*maska[N_SMALL] = {0,0}, */maska_1[N_BIG] = {0, 0, 0, 0, 0, 0};
    
    _SET_BIT(maska_1, RANG_OUTPUT_LED_DF_REG_PO_NZZ);
    _SET_BIT(maska_1, RANG_OUTPUT_LED_DF_REG_NZZ);
    _SET_BIT(maska_1, RANG_OUTPUT_LED_DF_REG_PO_3U0);
    _SET_BIT(maska_1, RANG_OUTPUT_LED_DF_REG_3U0);
    _SET_BIT(maska_1, RANG_OUTPUT_LED_DF_REG_SECTOR_NZZ);
    
//    //Знімаємо всі функції для ранжування входів, які відповідають за наявність каналу 3U0
//    for (int i = 0; i < NUMBER_DEFINED_BUTTONS; i++)
//      target_label->ranguvannja_buttons[i] &= ~maska_2;
    //Знімаємо всі функції для ранжування входів, які відповідають за наявність каналу 3U0
//    for (int i = 0; i < NUMBER_INPUTS; i++)
//    {
//      target_label->ranguvannja_inputs[N_SMALL*i  ] &= ~maska[0];
//      target_label->ranguvannja_inputs[N_SMALL*i+1] &= ~maska[1];
//    }
    //Знімаємо всі функції для ранжування виходів, які відповідають за наявність каналу 3U0
    for (int i = 0; i < NUMBER_OUTPUTS; i++)
    {
      target_label->ranguvannja_outputs[N_BIG*i  ] &= ~maska_1[0];
      target_label->ranguvannja_outputs[N_BIG*i+1] &= ~maska_1[1];
      target_label->ranguvannja_outputs[N_BIG*i+2] &= ~maska_1[2];
      target_label->ranguvannja_outputs[N_BIG*i+3] &= ~maska_1[3];
      target_label->ranguvannja_outputs[N_BIG*i+4] &= ~maska_1[4];
      target_label->ranguvannja_outputs[N_BIG*i+5] &= ~maska_1[5];
    }
    //Знімаємо всі функції для ранжування світоіндикаторів, які відповідають за наявність каналу 3U0
    for (int i = 0; i < NUMBER_LEDS; i++)
    {
      target_label->ranguvannja_leds[N_BIG*i  ] &= ~maska_1[0];
      target_label->ranguvannja_leds[N_BIG*i+1] &= ~maska_1[1];
      target_label->ranguvannja_leds[N_BIG*i+2] &= ~maska_1[2];
      target_label->ranguvannja_leds[N_BIG*i+3] &= ~maska_1[3];
      target_label->ranguvannja_leds[N_BIG*i+4] &= ~maska_1[4];
      target_label->ranguvannja_leds[N_BIG*i+5] &= ~maska_1[5];
    }
    //Знімаємо всі функції для ранжування дискретного реєстратора, які відповідають за наявність каналу 3U0
    target_label->ranguvannja_digital_registrator[0] &= ~maska_1[0];
    target_label->ranguvannja_digital_registrator[1] &= ~maska_1[1];
    target_label->ranguvannja_digital_registrator[2] &= ~maska_1[2];
    target_label->ranguvannja_digital_registrator[3] &= ~maska_1[3];
    target_label->ranguvannja_digital_registrator[4] &= ~maska_1[4];
    target_label->ranguvannja_digital_registrator[5] &= ~maska_1[5];
    //Знімаємо всі функції для ранжування аналогового реєстратора, які відповідають за наявність каналу 3U0
    target_label->ranguvannja_analog_registrator[0] &= ~maska_1[0];
    target_label->ranguvannja_analog_registrator[1] &= ~maska_1[1];
    target_label->ranguvannja_analog_registrator[2] &= ~maska_1[2];
    target_label->ranguvannja_analog_registrator[3] &= ~maska_1[3];
    target_label->ranguvannja_analog_registrator[4] &= ~maska_1[4];
    target_label->ranguvannja_analog_registrator[5] &= ~maska_1[5];
    //Знімаємо всі функції для ранжування оприділювальних функцій, які відповідають за наявність каналу 3U0
    for (int i = 0; i < NUMBER_DEFINED_FUNCTIONS; i++)
    {
      target_label->ranguvannja_df_source_plus[N_BIG*i  ] &= ~maska_1[0];
      target_label->ranguvannja_df_source_plus[N_BIG*i+1] &= ~maska_1[1];
      target_label->ranguvannja_df_source_plus[N_BIG*i+2] &= ~maska_1[2];
      target_label->ranguvannja_df_source_plus[N_BIG*i+3] &= ~maska_1[3];
      target_label->ranguvannja_df_source_plus[N_BIG*i+4] &= ~maska_1[4];
      target_label->ranguvannja_df_source_plus[N_BIG*i+5] &= ~maska_1[5];

      target_label->ranguvannja_df_source_minus[N_BIG*i  ] &= ~maska_1[0];
      target_label->ranguvannja_df_source_minus[N_BIG*i+1] &= ~maska_1[1];
      target_label->ranguvannja_df_source_minus[N_BIG*i+2] &= ~maska_1[2];
      target_label->ranguvannja_df_source_minus[N_BIG*i+3] &= ~maska_1[3];
      target_label->ranguvannja_df_source_minus[N_BIG*i+4] &= ~maska_1[4];
      target_label->ranguvannja_df_source_minus[N_BIG*i+5] &= ~maska_1[5];

      target_label->ranguvannja_df_source_blk[N_BIG*i  ] &= ~maska_1[0];
      target_label->ranguvannja_df_source_blk[N_BIG*i+1] &= ~maska_1[1];
      target_label->ranguvannja_df_source_blk[N_BIG*i+2] &= ~maska_1[2];
      target_label->ranguvannja_df_source_blk[N_BIG*i+3] &= ~maska_1[3];
      target_label->ranguvannja_df_source_blk[N_BIG*i+4] &= ~maska_1[4];
      target_label->ranguvannja_df_source_blk[N_BIG*i+5] &= ~maska_1[5];
    }
    //Знімаємо всі функції для ранжування оприділювальних триґерів, які відповідають за наявність каналу 3U0
    for (int i = 0; i < NUMBER_DEFINED_TRIGGERS; i++)
    {
      target_label->ranguvannja_set_dt_source_plus[N_BIG*i  ] &= ~maska_1[0];
      target_label->ranguvannja_set_dt_source_plus[N_BIG*i+1] &= ~maska_1[1];
      target_label->ranguvannja_set_dt_source_plus[N_BIG*i+2] &= ~maska_1[2];
      target_label->ranguvannja_set_dt_source_plus[N_BIG*i+3] &= ~maska_1[3];
      target_label->ranguvannja_set_dt_source_plus[N_BIG*i+4] &= ~maska_1[4];
      target_label->ranguvannja_set_dt_source_plus[N_BIG*i+5] &= ~maska_1[5];

      target_label->ranguvannja_set_dt_source_minus[N_BIG*i  ] &= ~maska_1[0];
      target_label->ranguvannja_set_dt_source_minus[N_BIG*i+1] &= ~maska_1[1];
      target_label->ranguvannja_set_dt_source_minus[N_BIG*i+2] &= ~maska_1[2];
      target_label->ranguvannja_set_dt_source_minus[N_BIG*i+3] &= ~maska_1[3];
      target_label->ranguvannja_set_dt_source_minus[N_BIG*i+4] &= ~maska_1[4];
      target_label->ranguvannja_set_dt_source_minus[N_BIG*i+5] &= ~maska_1[5];

      target_label->ranguvannja_reset_dt_source_plus[N_BIG*i  ] &= ~maska_1[0];
      target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+1] &= ~maska_1[1];
      target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+2] &= ~maska_1[2];
      target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+3] &= ~maska_1[3];
      target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+4] &= ~maska_1[4];
      target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+5] &= ~maska_1[5];

      target_label->ranguvannja_reset_dt_source_minus[N_BIG*i  ] &= ~maska_1[0];
      target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+1] &= ~maska_1[1];
      target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+2] &= ~maska_1[2];
      target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+3] &= ~maska_1[3];
      target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+4] &= ~maska_1[4];
      target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+5] &= ~maska_1[5];
    }
  }

}
/*****************************************************/

/*****************************************************/
//Функція обновлення змінних при зміні типу реле 33/3I0
/*****************************************************/
void action_after_changing_zz1_type(__SETTINGS *target_label)
{
  if ((target_label->control_zz & CTR_ZZ1_TYPE) != 0)
  {
    //Виводим НЗЗ і Сектор НЗЗ
    target_label->control_zz &= (unsigned int)(~(CTR_ZZ1_NZZ_STATE/* | CTR_ZZ1_SECTOR*/));
    
    //Виводим НЗЗ з УРОВ
    target_label->control_urov &= (unsigned int)(~CTR_UROV_STARTED_FROM_NZZ);
      
    unsigned int /*maska[N_SMALL] = {0,0}, */maska_1[N_BIG] = {0, 0, 0, 0, 0, 0};
    
    _SET_BIT(maska_1, RANG_OUTPUT_LED_DF_REG_PO_NZZ);
    _SET_BIT(maska_1, RANG_OUTPUT_LED_DF_REG_NZZ);
    _SET_BIT(maska_1, RANG_OUTPUT_LED_DF_REG_SECTOR_NZZ);
    
//    //Знімаємо всі функції для ранжування входів, які відповідають за наявність каналу 3U0
//    for (int i = 0; i < NUMBER_DEFINED_BUTTONS; i++)
//      target_label->ranguvannja_buttons[i] &= ~maska_2;
    //Знімаємо всі функції для ранжування входів, які відповідають за наявність каналу 3U0
//    for (int i = 0; i < NUMBER_INPUTS; i++)
//    {
//      target_label->ranguvannja_inputs[N_SMALL*i  ] &= ~maska[0];
//      target_label->ranguvannja_inputs[N_SMALL*i+1] &= ~maska[1];
//    }
    //Знімаємо всі функції для ранжування виходів, які відповідають за наявність каналу 3U0
    for (int i = 0; i < NUMBER_OUTPUTS; i++)
    {
      target_label->ranguvannja_outputs[N_BIG*i  ] &= ~maska_1[0];
      target_label->ranguvannja_outputs[N_BIG*i+1] &= ~maska_1[1];
      target_label->ranguvannja_outputs[N_BIG*i+2] &= ~maska_1[2];
      target_label->ranguvannja_outputs[N_BIG*i+3] &= ~maska_1[3];
      target_label->ranguvannja_outputs[N_BIG*i+4] &= ~maska_1[4];
      target_label->ranguvannja_outputs[N_BIG*i+5] &= ~maska_1[5];
    }
    //Знімаємо всі функції для ранжування світоіндикаторів, які відповідають за наявність каналу 3U0
    for (int i = 0; i < NUMBER_LEDS; i++)
    {
      target_label->ranguvannja_leds[N_BIG*i  ] &= ~maska_1[0];
      target_label->ranguvannja_leds[N_BIG*i+1] &= ~maska_1[1];
      target_label->ranguvannja_leds[N_BIG*i+2] &= ~maska_1[2];
      target_label->ranguvannja_leds[N_BIG*i+3] &= ~maska_1[3];
      target_label->ranguvannja_leds[N_BIG*i+4] &= ~maska_1[4];
      target_label->ranguvannja_leds[N_BIG*i+5] &= ~maska_1[5];
    }
    //Знімаємо всі функції для ранжування дискретного реєстратора, які відповідають за наявність каналу 3U0
    target_label->ranguvannja_digital_registrator[0] &= ~maska_1[0];
    target_label->ranguvannja_digital_registrator[1] &= ~maska_1[1];
    target_label->ranguvannja_digital_registrator[2] &= ~maska_1[2];
    target_label->ranguvannja_digital_registrator[3] &= ~maska_1[3];
    target_label->ranguvannja_digital_registrator[4] &= ~maska_1[4];
    target_label->ranguvannja_digital_registrator[5] &= ~maska_1[5];
    //Знімаємо всі функції для ранжування аналогового реєстратора, які відповідають за наявність каналу 3U0
    target_label->ranguvannja_analog_registrator[0] &= ~maska_1[0];
    target_label->ranguvannja_analog_registrator[1] &= ~maska_1[1];
    target_label->ranguvannja_analog_registrator[2] &= ~maska_1[2];
    target_label->ranguvannja_analog_registrator[3] &= ~maska_1[3];
    target_label->ranguvannja_analog_registrator[4] &= ~maska_1[4];
    target_label->ranguvannja_analog_registrator[5] &= ~maska_1[5];
    //Знімаємо всі функції для ранжування оприділювальних функцій, які відповідають за наявність каналу 3U0
    for (int i = 0; i < NUMBER_DEFINED_FUNCTIONS; i++)
    {
      target_label->ranguvannja_df_source_plus[N_BIG*i  ] &= ~maska_1[0];
      target_label->ranguvannja_df_source_plus[N_BIG*i+1] &= ~maska_1[1];
      target_label->ranguvannja_df_source_plus[N_BIG*i+2] &= ~maska_1[2];
      target_label->ranguvannja_df_source_plus[N_BIG*i+3] &= ~maska_1[3];
      target_label->ranguvannja_df_source_plus[N_BIG*i+4] &= ~maska_1[4];
      target_label->ranguvannja_df_source_plus[N_BIG*i+5] &= ~maska_1[5];

      target_label->ranguvannja_df_source_minus[N_BIG*i  ] &= ~maska_1[0];
      target_label->ranguvannja_df_source_minus[N_BIG*i+1] &= ~maska_1[1];
      target_label->ranguvannja_df_source_minus[N_BIG*i+2] &= ~maska_1[2];
      target_label->ranguvannja_df_source_minus[N_BIG*i+3] &= ~maska_1[3];
      target_label->ranguvannja_df_source_minus[N_BIG*i+4] &= ~maska_1[4];
      target_label->ranguvannja_df_source_minus[N_BIG*i+5] &= ~maska_1[5];

      target_label->ranguvannja_df_source_blk[N_BIG*i  ] &= ~maska_1[0];
      target_label->ranguvannja_df_source_blk[N_BIG*i+1] &= ~maska_1[1];
      target_label->ranguvannja_df_source_blk[N_BIG*i+2] &= ~maska_1[2];
      target_label->ranguvannja_df_source_blk[N_BIG*i+3] &= ~maska_1[3];
      target_label->ranguvannja_df_source_blk[N_BIG*i+4] &= ~maska_1[4];
      target_label->ranguvannja_df_source_blk[N_BIG*i+5] &= ~maska_1[5];
    }
    //Знімаємо всі функції для ранжування оприділювальних триґерів, які відповідають за наявність каналу 3U0
    for (int i = 0; i < NUMBER_DEFINED_TRIGGERS; i++)
    {
      target_label->ranguvannja_set_dt_source_plus[N_BIG*i  ] &= ~maska_1[0];
      target_label->ranguvannja_set_dt_source_plus[N_BIG*i+1] &= ~maska_1[1];
      target_label->ranguvannja_set_dt_source_plus[N_BIG*i+2] &= ~maska_1[2];
      target_label->ranguvannja_set_dt_source_plus[N_BIG*i+3] &= ~maska_1[3];
      target_label->ranguvannja_set_dt_source_plus[N_BIG*i+4] &= ~maska_1[4];
      target_label->ranguvannja_set_dt_source_plus[N_BIG*i+5] &= ~maska_1[5];

      target_label->ranguvannja_set_dt_source_minus[N_BIG*i  ] &= ~maska_1[0];
      target_label->ranguvannja_set_dt_source_minus[N_BIG*i+1] &= ~maska_1[1];
      target_label->ranguvannja_set_dt_source_minus[N_BIG*i+2] &= ~maska_1[2];
      target_label->ranguvannja_set_dt_source_minus[N_BIG*i+3] &= ~maska_1[3];
      target_label->ranguvannja_set_dt_source_minus[N_BIG*i+4] &= ~maska_1[4];
      target_label->ranguvannja_set_dt_source_minus[N_BIG*i+5] &= ~maska_1[5];

      target_label->ranguvannja_reset_dt_source_plus[N_BIG*i  ] &= ~maska_1[0];
      target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+1] &= ~maska_1[1];
      target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+2] &= ~maska_1[2];
      target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+3] &= ~maska_1[3];
      target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+4] &= ~maska_1[4];
      target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+5] &= ~maska_1[5];

      target_label->ranguvannja_reset_dt_source_minus[N_BIG*i  ] &= ~maska_1[0];
      target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+1] &= ~maska_1[1];
      target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+2] &= ~maska_1[2];
      target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+3] &= ~maska_1[3];
      target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+4] &= ~maska_1[4];
      target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+5] &= ~maska_1[5];
    }
  }

}
/*****************************************************/

/*****************************************************/
//Функція, яка визначає кількість біт затримки, який допускається між байтами у RS-485 згідно з визначеними настройками
/*****************************************************/
void calculate_namber_bit_waiting_for_rs_485(void)
{
  unsigned int number_bits_rs_485_waiting_tmp = 10;
  
  //Підраховуємо кількість біт у байті
  if (current_settings.pare_bit_RS485 > 0) number_bits_rs_485_waiting_tmp++;
  if (current_settings.number_stop_bit_RS485 > 0) number_bits_rs_485_waiting_tmp++;
  
  //Врахування швидкості
  unsigned int multiplicator;
  switch (current_settings.speed_RS485)
  {
  case 0:
    {
      multiplicator = 12; //9600
      break;
    }
  case 1:
    {
      multiplicator = 8;  //14400
      break;
    }
  case 2:
    {
      multiplicator = 6;  //19200
      break;
    }
  case 3:
    {
      multiplicator = 4;  //28800
      break;
    }
  case 4:
    {
      multiplicator = 3;  //38400
      break;
    }
  case 5:
    {
      multiplicator = 2;  //57600
      break;
    }
  default:
    {
      multiplicator = 1;  //115200
      break;
    }
  }
  number_bits_rs_485_waiting_tmp *= (multiplicator*current_settings.time_out_1_RS485);
  number_bits_rs_485_waiting_tmp /= 10;
  
  number_bits_rs_485_waiting = number_bits_rs_485_waiting_tmp;
}
/*****************************************************/

/******************************************************
//Функція, яка фіксує зміни у настройках і запускає запис настройок у EEPROM
-----------------------------------------------------
setting_rang: 0 - запис уставок
              1 - запис ранжування

source:       0 - мінімальні параметри
              1 - клавіатура
              2 - USB
              3 - RS-485
---------------------------------------------------
******************************************************/
void fix_change_settings(unsigned int setting_rang, unsigned int source)
{
  unsigned char *point_to_target;
  
  if (setting_rang == 0) point_to_target = (&current_settings)->time_setpoints;
  else point_to_target = (&current_settings)->time_ranguvannja;
  
  //Помічаємо, що відбулася зміна настройок
  information_about_settings_changed |= ((1 << USB_RECUEST)|(1 << RS485_RECUEST));
  
  //Записуємо час останніх змін
  unsigned char *label_to_time_array;
  if (copying_time == 2) label_to_time_array = time_copy;
  else label_to_time_array = time;
  for (unsigned int i = 0; i < 7; i++) *(point_to_target + i) = *(label_to_time_array + i);
  *(point_to_target + 7) = (unsigned char)(source & 0xff);
  
  //Помічаємо, що таблиця змінилася і її треба буде з системи захистів зкопіювати у таблицю з якою працює система захистів
  changed_settings = CHANGED_ETAP_ENDED;
  
  //Запускаємо запис у EEPROM
  _SET_BIT(control_i2c_taskes, TASK_START_WRITE_SETTINGS_EEPROM_BIT);
}
/*****************************************************/

/******************************************************
Відновлення триґерних функцій
******************************************************/
void restore_trigger_functions(unsigned int *active_functions_point)
{
  active_functions[RANG_OUTPUT_LED_DF_REG_DT1_OUT >> 5] |= _CHECK_SET_BIT(active_functions_point, RANG_OUTPUT_LED_DF_REG_DT1_OUT);
  active_functions[RANG_OUTPUT_LED_DF_REG_DT2_OUT >> 5] |= _CHECK_SET_BIT(active_functions_point, RANG_OUTPUT_LED_DF_REG_DT2_OUT);
  active_functions[RANG_OUTPUT_LED_DF_REG_DT3_OUT >> 5] |= _CHECK_SET_BIT(active_functions_point, RANG_OUTPUT_LED_DF_REG_DT3_OUT);
  active_functions[RANG_OUTPUT_LED_DF_REG_DT4_OUT >> 5] |= _CHECK_SET_BIT(active_functions_point, RANG_OUTPUT_LED_DF_REG_DT4_OUT);
    
  trigger_APV_ZMN_2 = (_CHECK_SET_BIT(active_functions_point, RANG_OUTPUT_LED_DF_REG_BLOCK_KRATN_APV_ZMN) != 0);
  trigger_APV_ZMN_0 = (_CHECK_SET_BIT(active_functions_point, RANG_OUTPUT_LED_DF_REG_BLOCK_APV_ZMN_VID_ZAKHYSTIV) != 0);
  trigger_AVR_0 = (_CHECK_SET_BIT(active_functions_point, RANG_OUTPUT_LED_DF_REG_BLOCK_AVR_VID_ZAKHYSTIV) != 0);
  trigger_AVR_1 = (_CHECK_SET_BIT(active_functions_point, RANG_OUTPUT_LED_DF_REG_BLOCK_KRATN_AVR) != 0);
}
/*****************************************************/

/*****************************************************/
//Функція зміни інформації по діагностиці
/*****************************************************/
void changing_diagnostyka_state(void)
{
  /*****
  Визначаємо новий стан діагностики
  
  Алгоритм:
  - Копіюємо у тимчасові масиви біти, які треба скинути і які треба виставити у 
    діагностиці
  - Після цього копіювання більш пріоритетні ситстеми можуть добавляти (не 
    скидають ніколи!!!) нові біти у глобальні масиви
  - Біти , які ми будуть скидалися/встановлюватися очищаємо з глобальних масивів
    (якщо в процесі цього алгоритму більшпріоритетні системи добавили чи 
    добавлятимуть нові біти, то вони не скинуться, а опрацюються при наступному 
    виклику цієї функції)

  - Спочатку очищаємо біти а потім встановлюємо, бо фіксація події має більший 
    пріоритет за очищення
  *****/
  unsigned int clear_diagnostyka_tmp[3], set_diagnostyka_tmp[3];
  
  clear_diagnostyka_tmp[0] = clear_diagnostyka[0];
  clear_diagnostyka_tmp[1] = clear_diagnostyka[1];
  clear_diagnostyka_tmp[2] = clear_diagnostyka[2];

  set_diagnostyka_tmp[0] = set_diagnostyka[0];
  set_diagnostyka_tmp[1] = set_diagnostyka[1];
  set_diagnostyka_tmp[2] = set_diagnostyka[2];
    
  diagnostyka[0] &= (unsigned int)(~clear_diagnostyka_tmp[0]); 
  diagnostyka[0] |= set_diagnostyka_tmp[0]; 

  diagnostyka[1] &= (unsigned int)(~clear_diagnostyka_tmp[1]); 
  diagnostyka[1] |= set_diagnostyka_tmp[1]; 

  diagnostyka[2] &= (unsigned int)(~clear_diagnostyka_tmp[2]); 
  diagnostyka[2] |= set_diagnostyka_tmp[2]; 
  
  diagnostyka[2] &= USED_BITS_IN_LAST_INDEX; 

  clear_diagnostyka[0] &= (unsigned int)(~clear_diagnostyka_tmp[0]);
  clear_diagnostyka[1] &= (unsigned int)(~clear_diagnostyka_tmp[1]);
  clear_diagnostyka[2] &= (unsigned int)(~clear_diagnostyka_tmp[2]);
  
  set_diagnostyka[0] &= (unsigned int)(~set_diagnostyka_tmp[0]);
  set_diagnostyka[1] &= (unsigned int)(~set_diagnostyka_tmp[1]);
  set_diagnostyka[2] &= (unsigned int)(~set_diagnostyka_tmp[2]);
  /*****/
  
  //Визначаємо, чи відбулися зміни
  unsigned int value_changes[3], diagnostyka_now[3];
  /*
  Робимо копію тепершньої діагностики, бо ця функція працює на найнижчому пріоритеті,
  тому під час роботи може появитися нові значення, які ми не врахували у цій функції
  */
  diagnostyka_now[0] = diagnostyka[0];
  diagnostyka_now[1] = diagnostyka[1];
  diagnostyka_now[2] = diagnostyka[2];
  value_changes[0] = diagnostyka_before[0] ^ diagnostyka_now[0];
  value_changes[1] = diagnostyka_before[1] ^ diagnostyka_now[1];
  value_changes[2] = diagnostyka_before[2] ^ diagnostyka_now[2];
  
  /*
  У реєстраторі програмних подій має реєструватися тільки перехід з пасивного стану у активний
  таких подій як " Старт устр.    " і " Рестарт устр.  "
  тому перехід з активного у пачсивний ми ігноруємо і крім того затираємо біти, які його "засигналізували"
  */
  
  /*****/
  //Подія " Старт устр.    "
  /*****/
  if (_CHECK_SET_BIT(value_changes, EVENT_START_SYSTEM_BIT) != 0)
  {
    //Зафіксовано що подія " Старт устр.    " змінила свій стан
    if (_CHECK_SET_BIT(diagnostyka_now, EVENT_START_SYSTEM_BIT) == 0)
    {
      /*
      Новий стан події " Старт устр.    " є неактивний стан
      Тому робимо так, щоб ця подія не попала у реєстратор програмних подій таким операціями
      - знімаємо встановлений біт про зміну стану діагностики
      - знімаємо повідомлення, що у попередньому стані діагностики ця подія була активною
      - у текучому стані діагностики нічого міняти не треба, бо цей сигнал є неактивним
      */
      _CLEAR_BIT(value_changes, EVENT_START_SYSTEM_BIT);
      _CLEAR_BIT(diagnostyka_before, EVENT_START_SYSTEM_BIT);
    }
  }
  /*****/
  
  /*****/
  //Подія " Рестарт устр.  "
  /*****/
  if (_CHECK_SET_BIT(value_changes, EVENT_RESTART_SYSTEM_BIT) != 0)
  {
    //Зафіксовано що подія " Рестарт устр.  " змінила свій стан
    if (_CHECK_SET_BIT(diagnostyka_now, EVENT_RESTART_SYSTEM_BIT) == 0)
    {
      /*
      Новий стан події " Рестарт устр.  " є неактивний стан
      Тому робимо так, щоб ця подія не попала у реєстратор програмних подій таким операціями
      - знімаємо встановлений біт про зміну стану діагностики
      - знімаємо повідомлення, що у попередньому стані діагностики ця подія була активною
      - у текучому стані діагностики нічого міняти не треба, бо цей сигнал є неактивним
      */
      _CLEAR_BIT(value_changes, EVENT_RESTART_SYSTEM_BIT);
      _CLEAR_BIT(diagnostyka_before, EVENT_RESTART_SYSTEM_BIT);
    }
  }
  /*****/

  //Перевіряємо, чи треба виконувати дії поо зміні діагностики
  if (
      (value_changes[0] != 0) ||
      (value_changes[1] != 0) ||
      (value_changes[2] != 0)
     )
  {
    //Є біти, які треба встановити, або зняти
    
    /*****/
    //При можливості формуємо запис у реєстратор програмних помилок
    /*****/
    if (_CHECK_SET_BIT(diagnostyka, ERROR_PR_ERR_OVERLOAD_BIT) == 0)
    {
      /*
      Новий запис робимо тільки тоді, коли попередньо не було зафіксовано 
      переповнення буферу, інакше чикаємо, поки запис у реєстратор програмних подій
      знімить подію про переповнення буферу
      */
      
      //Визначаємо кількість доступних комірок у буфері для реєстратора програмних подій
      int number_empty_cells;
      unsigned int head = head_fifo_buffer_pr_err_records, tail = tail_fifo_buffer_pr_err_records;
      number_empty_cells = (int)(((unsigned int)tail) - ((unsigned int)head));
      while (number_empty_cells <= 0) number_empty_cells += MAX_NUMBER_RECORDS_PR_ERR_INTO_BUFFER;
      if (number_empty_cells == 1)
      {
        //Це є остання вільна комірка, то помічаємо, що з цим записом відбувається повне заповнення буферу
        _SET_BIT(diagnostyka, ERROR_PR_ERR_OVERLOAD_BIT);
        /*
        відбулася зміна стану діагностики, яку треба врахувати у даному записфі ,тому
        робимо повторноу копію тепершньої діагностики, яка може врахувати і ті зміни які відбулися
        між операціями копіювання стану діагностики на початку цієї функції і
        операцією, як зараз ми будемо виконувати
        */
        diagnostyka_now[0] = diagnostyka[0];
        diagnostyka_now[1] = diagnostyka[1];
        diagnostyka_now[2] = diagnostyka[2];
        
        //Підраховуємо нову кількість змін в діагностиці
        value_changes[0] = diagnostyka_before[0] ^ diagnostyka_now[0];
        value_changes[1] = diagnostyka_before[1] ^ diagnostyka_now[1];
        value_changes[2] = diagnostyka_before[2] ^ diagnostyka_now[2];
      }

      //Вираховуємо кількість змін сигналів
      unsigned int number_changes = 0;
      for(unsigned int i = 0; i < (8*sizeof(value_changes)); i++)
      {
        if (_CHECK_SET_BIT(value_changes, i) != 0) number_changes++;
      }

      if(number_changes != 0)
      {
        /*
        теоретично може бути ситуація, що ми знімали повідомлення про переповнення буферу
        FIFO для записів реєстратора програмних подій  і це була єдина зміна, али при цьому
        є тільки одна вільна комірка, тому ми знову виставили повідомлення про переповнення.
        Тому ми не можемо зняти це повідомлення - тому і не можемо робити нового запису, 
        бо фактично і зміни ніякої нема
        */
        
        //Визначаємо індекс у масиві буферу програмних помилок з якого трбе почати заповнювати дані
        unsigned int index_into_buffer_pr_err = head*SIZE_ONE_RECORD_PR_ERR;
      
        //Помічаємо мітку початку запису
        buffer_pr_err_records[index_into_buffer_pr_err + 0] = LABEL_START_RECORD_PR_ERR;

        //Час фіксації зміни у діагностиці
        if(
           (_CHECK_SET_BIT(diagnostyka, EVENT_START_SYSTEM_BIT   ) == 0) &&
           (_CHECK_SET_BIT(diagnostyka, EVENT_RESTART_SYSTEM_BIT ) == 0) &&
           (_CHECK_SET_BIT(diagnostyka, EVENT_STOP_SYSTEM_BIT    ) == 0)
          )
        {
          //Вже відбулося перше зчитуванння часу - тобто системний час у нас є
          unsigned char *label_to_time_array;
          if (copying_time == 2) label_to_time_array = time_copy;
          else label_to_time_array = time;
          for(unsigned int i = 0; i < 7; i++) buffer_pr_err_records[index_into_buffer_pr_err + 1 + i] = *(label_to_time_array + i);
        }
        else
        {
          //Ще не відбулося перше зчитуванння часу - тому покищо ці поля записуємо числом 0xff, а потім, коли системний час зчитається, то ми це поле обновимо
          for(unsigned int i = 0; i < 7; i++)  buffer_pr_err_records[index_into_buffer_pr_err + 1 + i] = 0xff;
        }

        buffer_pr_err_records[index_into_buffer_pr_err + 8] = number_changes & 0xff;
      
        //Записуємо попередній стан діагностики
        buffer_pr_err_records[index_into_buffer_pr_err + 9 ] =  diagnostyka_before[0]        & 0xff;
        buffer_pr_err_records[index_into_buffer_pr_err + 10] = (diagnostyka_before[0] >> 8 ) & 0xff;
        buffer_pr_err_records[index_into_buffer_pr_err + 11] = (diagnostyka_before[0] >> 16) & 0xff;
        buffer_pr_err_records[index_into_buffer_pr_err + 12] = (diagnostyka_before[0] >> 24) & 0xff;
        buffer_pr_err_records[index_into_buffer_pr_err + 13] =  diagnostyka_before[1]        & 0xff;
        buffer_pr_err_records[index_into_buffer_pr_err + 14] = (diagnostyka_before[1] >> 8 ) & 0xff;
        buffer_pr_err_records[index_into_buffer_pr_err + 15] = (diagnostyka_before[1] >> 16) & 0xff;
        buffer_pr_err_records[index_into_buffer_pr_err + 16] = (diagnostyka_before[1] >> 24) & 0xff;
        buffer_pr_err_records[index_into_buffer_pr_err + 17] =  diagnostyka_before[2]        & 0xff;
        buffer_pr_err_records[index_into_buffer_pr_err + 18] = (diagnostyka_before[2] >> 8 ) & 0xff;
        buffer_pr_err_records[index_into_buffer_pr_err + 19] = (diagnostyka_before[2] >> 16) & 0xff;

        //Записуємо теперішній стан діагностики
        buffer_pr_err_records[index_into_buffer_pr_err + 20] =  diagnostyka_now[0]        & 0xff;
        buffer_pr_err_records[index_into_buffer_pr_err + 21] = (diagnostyka_now[0] >> 8 ) & 0xff;
        buffer_pr_err_records[index_into_buffer_pr_err + 22] = (diagnostyka_now[0] >> 16) & 0xff;
        buffer_pr_err_records[index_into_buffer_pr_err + 23] = (diagnostyka_now[0] >> 24) & 0xff;
        buffer_pr_err_records[index_into_buffer_pr_err + 24] =  diagnostyka_now[1]        & 0xff;
        buffer_pr_err_records[index_into_buffer_pr_err + 25] = (diagnostyka_now[1] >> 8 ) & 0xff;
        buffer_pr_err_records[index_into_buffer_pr_err + 26] = (diagnostyka_now[1] >> 16) & 0xff;
        buffer_pr_err_records[index_into_buffer_pr_err + 27] = (diagnostyka_now[1] >> 24) & 0xff;
        buffer_pr_err_records[index_into_buffer_pr_err + 28] =  diagnostyka_now[2]        & 0xff;
        buffer_pr_err_records[index_into_buffer_pr_err + 29] = (diagnostyka_now[2] >> 8 ) & 0xff;
        buffer_pr_err_records[index_into_buffer_pr_err + 30] = (diagnostyka_now[2] >> 16) & 0xff;
        
        /*
        У реєстраторі програмних подій має реєструватися тільки перехід з пасивного стану у активний
        таких події як " Останов.устр.  " і ця подія не має бути активною у текучій діагностиці,
        бо це, фактично, подія, яка мала місце до останнього включення приладу в роботу.
        Тобто це подія "попереднього сеансу роботи"
        тому перехід з пасивного у фіксуємо ми фіксуємо і зразу затираємо цей біт у теперішній діагностіці,
        яка після цього буде зкомійомана у масив. який відповідає за попередній стан діагностики, так і у масив
        діагностики, який відповідає за текучий стан подій діагностики
        */
        if (_CHECK_SET_BIT(value_changes, EVENT_STOP_SYSTEM_BIT) != 0)
        {
          /*
          Cтан події " Останов.устр.  " змінився (допускається нашим програмним забезпеченням
          зміна з пасивного стану у активний стан)
          Тому робимо такі операції
          - знімаємо встановлений біт у масиві, який зараз буде копіюватися у масив попереднього стану
          - знімаємо встановлений біт у масиві, який відповідає за текучий стан подій діагностики
          */
          _CLEAR_BIT(diagnostyka_now, EVENT_STOP_SYSTEM_BIT);
          _CLEAR_BIT(diagnostyka, EVENT_STOP_SYSTEM_BIT);
        }

        //Фіксуємо попередній стан, який ми вже записали і відносно якого будемо визначати нові зміни
        diagnostyka_before[0] = diagnostyka_now[0];
        diagnostyka_before[1] = diagnostyka_now[1];
        diagnostyka_before[2] = diagnostyka_now[2];

        //Підготовлюємося до запуску запису у реєстратор програмних подій
          unsigned int next_index_into_fifo_buffer = head + 1;
          while(next_index_into_fifo_buffer >= MAX_NUMBER_RECORDS_PR_ERR_INTO_BUFFER) next_index_into_fifo_buffer -= MAX_NUMBER_RECORDS_PR_ERR_INTO_BUFFER;
          
          //Встановлюємо нове значення голови буфера FIFO 
          head_fifo_buffer_pr_err_records = next_index_into_fifo_buffer;
      }
    }
    /*****/
  }
}
/*****************************************************/

/*****************************************************/
//Підрахунок кількості втановлених одиничок у області пам'яті початок якої визначається вказівником source
/*****************************************************/
unsigned int count_number_set_bit(unsigned int* source, unsigned int total_number)
{
  unsigned int count = 0;
  unsigned int offset, shift;
  
  for (unsigned int i = 0; i < total_number; i++)  
  {
    offset = i >> 5; //Це є, фактично, ділення на 32
    shift  = (i & (32 - 1)); //Це є, фактично, визначення остачі від ділення на 32
    if ( ( (*(source + offset))  & ((unsigned int)(1 << shift)) ) != 0 ) count++;
  }

  return count;
}
/*****************************************************/

/*****************************************************/
//Контроль достовірності настройок
/*****************************************************/
void control_settings(void)
{
  unsigned char crc_settings_tmp = 0, temp_value_1, temp_value_2;
  unsigned char  *point_1 = (unsigned char*)(&current_settings); 
  unsigned char  *point_2 = (unsigned char*)(&current_settings_prt); 
  unsigned int i = 0, difference = 0;
  while ((difference == 0) && (i < sizeof(__SETTINGS)))
  {
    temp_value_1 = *(point_1);
    temp_value_2 = *(point_2);
    crc_settings_tmp += temp_value_1;
    if (temp_value_1 != temp_value_2) difference = 0xff;
    point_1++;
    point_2++;
    i++;
  }
  
  if ((difference == 0) && (crc_settings == crc_settings_tmp))
  {
    //Контроль достовірності таблиці настройок пройшов успішно
    
    //Скидаємо повідомлення у слові діагностики
    _SET_BIT(clear_diagnostyka, ERROR_SETTINGS_EEPROM_CONTROL_BIT);
  }
  else
  {
    //Контроль достовірності таблиці настройок не пройшов

    //Виствляємо повідомлення у слові діагностики
    _SET_BIT(set_diagnostyka, ERROR_SETTINGS_EEPROM_CONTROL_BIT);
  }
}
/*****************************************************/

/*****************************************************/
//Контроль достовірності юстування
/*****************************************************/
void control_ustuvannja(void)
{
  unsigned char crc_ustuvannja_tmp = 0, temp_value_1, temp_value_2;
  unsigned char  *point_1; 
  unsigned char  *point_2; 
  unsigned int i = 0, difference = 0;

  /*
  У контрольу суму входить індетифікатор типу набору юстуючих коефіцієнтів,
  який займає розмір типу unsigned int
  */
  unsigned int adjustment_id_tmp = ADJUSTMENT_ID;
  point_1 = (unsigned char*)(&adjustment_id_tmp); 
  while (i < sizeof(unsigned int))
  {
    temp_value_1 = *(point_1);
    crc_ustuvannja_tmp += temp_value_1;
    point_1++;
    i++;
  }
  
  point_1 = (unsigned char*)(&ustuvannja); 
  point_2 = (unsigned char*)(&ustuvannja_meas);
  i = 0;
  while ((difference == 0) && (i < sizeof(ustuvannja)))
  {
    temp_value_1 = *(point_1);
    temp_value_2 = *(point_2);
    crc_ustuvannja_tmp += temp_value_1;
    if (temp_value_1 != temp_value_2) difference = 0xff;
    point_1++;
    point_2++;
    i++;
  }

  point_1 = (unsigned char*)(&phi_ustuvannja); 
  point_2 = (unsigned char*)(&phi_ustuvannja_meas);
  i = 0;
  while ((difference == 0) && (i < sizeof(phi_ustuvannja)))
  {
    temp_value_1 = *(point_1);
    temp_value_2 = *(point_2);
    crc_ustuvannja_tmp += temp_value_1;
    if (temp_value_1 != temp_value_2) difference = 0xff;
    point_1++;
    point_2++;
    i++;
  }

  point_1 = (unsigned char*)(&phi_ustuvannja_sin_cos); 
  point_2 = (unsigned char*)(&phi_ustuvannja_sin_cos_meas);
  i = 0;
  while ((difference == 0) && (i < sizeof(phi_ustuvannja_sin_cos)))
  {
    temp_value_1 = *(point_1);
    temp_value_2 = *(point_2);
    crc_ustuvannja_tmp += temp_value_1;
    if (temp_value_1 != temp_value_2) difference = 0xff;
    point_1++;
    point_2++;
    i++;
  }

  /*
  Не треба контролювати ідентичність серійног номеру, який працює з вимірювально системою,
  чи системою захистів, чи ще якоюсь високопріоритетною і високонадійною від завад системою,
  бо його просто не існує
  */
  point_1 = (unsigned char*)(&serial_number_dev); 
  i = 0;
  while ((difference == 0) && (i < sizeof(serial_number_dev)))
  {
    temp_value_1 = *(point_1);
    crc_ustuvannja_tmp += temp_value_1;
    point_1++;
    i++;
  }
  
  if ((difference == 0) && (crc_ustuvannja == crc_ustuvannja_tmp))
  {
    //Контроль достовірності юстування пройшов успішно
    
    //Скидаємо повідомлення у слові діагностики
    _SET_BIT(clear_diagnostyka, ERROR_USTUVANNJA_EEPROM_CONTROL_BIT);
  }
  else
  {
    //Контроль достовірності юстування не пройшов

    //Виствляємо повідомлення у слові діагностики
    _SET_BIT(set_diagnostyka, ERROR_USTUVANNJA_EEPROM_CONTROL_BIT);
  }
}
/*****************************************************/

/*****************************************************/
//Контроль достовірності триґерної інформації
/*****************************************************/
void control_trg_func(void)
{
  unsigned char crc_trg_func_tmp = 0, temp_value_1;
  unsigned char  *point; 
  unsigned int i;
  
  temp_value_1 = misceve_dystancijne_ctrl & 0xff;
  crc_trg_func_tmp += temp_value_1;
  
  point = (unsigned char*)(trigger_active_functions_ctrl);
  i = 0;  
  while (i < sizeof(trigger_active_functions_ctrl))
  {
    temp_value_1 = *(point);
    crc_trg_func_tmp += temp_value_1;
    point++;
    i++;
  }
  
  if (crc_trg_func == crc_trg_func_tmp)
  {
    //Контроль достовірності юстування пройшов успішно
    
    //Скидаємо повідомлення у слові діагностики
    _SET_BIT(clear_diagnostyka, ERROR_TRG_FUNC_EEPROM_CONTROL_BIT);
  }
  else
  {
    //Контроль достовірності юстування не пройшов

    //Виствляємо повідомлення у слові діагностики
    _SET_BIT(set_diagnostyka, ERROR_TRG_FUNC_EEPROM_CONTROL_BIT);
  }
}
/*****************************************************/

/*****************************************************/
//Контроль достовірності інформації по реєстраторах
/*****************************************************/
unsigned int control_info_rejestrator(__INFO_REJESTRATOR* info_rejestrator_point, unsigned char crc_info_rejestrator)
{
  unsigned int result;
  unsigned char crc_info_rejestrator_tmp = 0, temp_value_1;
  unsigned char  *point = (unsigned char*)(info_rejestrator_point); 
  unsigned int i = 0;
  while (i < sizeof(__INFO_REJESTRATOR))
  {
    temp_value_1 = *(point);
    crc_info_rejestrator_tmp += temp_value_1;
    point++;
    i++;
  }
  
  if (crc_info_rejestrator == crc_info_rejestrator_tmp)
  {
    //Контроль достовірності реєстратора пройшов успішно
    result = 1;    
  }
  else
  {
    //Контроль достовірності реєстратора не пройшов
    result = 0;    
  }
  
  return result;
}
/*****************************************************/

/*****************************************************/
//Контроль достовірності лічильника ресурсу
/*****************************************************/
void control_resurs(void)
{
  unsigned char crc_resurs_tmp = 0, temp_value;
  unsigned char *point;
  
  point = (unsigned char*)(&resurs_vymykacha_ctrl); 
  for (unsigned int i = 0; i < sizeof(resurs_vymykacha_ctrl); i++)
  {
    temp_value = *(point);
    crc_resurs_tmp += temp_value;
    point++;
  }

  point = (unsigned char*)(&resurs_vidkljuchennja_ctrl); 
  for (unsigned int i = 0; i < sizeof(resurs_vidkljuchennja_ctrl); i++)
  {
    temp_value = *(point);
    crc_resurs_tmp += temp_value;
    point++;
  }

  if (crc_resurs_ctrl == crc_resurs_tmp)
  {
    //Контроль достовірності ресурсу лічильника пройшов успішно
    
    //Скидаємо повідомлення у слові діагностики
    _SET_BIT(clear_diagnostyka, ERROR_RESURS_EEPROM_CONTROL_BIT);
  }
  else
  {
    //Контроль достовірності юстування не пройшов

    //Виствляємо повідомлення у слові діагностики
    _SET_BIT(set_diagnostyka, ERROR_RESURS_EEPROM_CONTROL_BIT);
  }
  
}
/*****************************************************/

/*****************************************************/
//Визначення номеру місяця з константи __DATE__
/*****************************************************/
int str_to_int_DATE_Mmm(void)
{
  static const char month_names[12*3] = "JanFebMarAprMayJunJulAugSepOctNovDec";
  
  int i = 0;
  while(i < 12)
  {
    if (
        (month_names[3*i + 0] == __DATE__[0]) &&
        (month_names[3*i + 1] == __DATE__[1]) &&
        (month_names[3*i + 2] == __DATE__[2])
       )
    {
      break;
    }
    
    i++;
  } 
  
  if (i < 12)
  { 
    i += 1; /*щоб нумерація місяців ішла з "1", а не з "0"*/
    return ((i / 10) << 4) + (i % 10);
  }
  else return 0;
}
/*****************************************************/

/*****************************************************/
/*****************************************************/
//
/*****************************************************/
