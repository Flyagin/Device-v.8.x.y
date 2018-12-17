#include "header.h"

/*****************************************************/
//������� ���������� ������ ��� ��� ������������
/*****************************************************/
unsigned int action_after_changing_of_configuration(unsigned int new_configuration, __SETTINGS *target_label)
{
  unsigned int error_window = 0;
  
  /************************/
  //������ ���������� �� �� ����������� ����� �� � ������ ���, ��� ��������� �������� ������ ������������
  /************************/
  //�������� ���
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
  //�������� ���
  if ((new_configuration & (1<<ZDZ_BIT_CONFIGURATION)) == 0)
  {
    if(
       (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_ZDZ) ||
       (current_ekran.current_level == EKRAN_CONTROL_ZDZ        )
      )
      error_window |= (1 << ZDZ_BIT_CONFIGURATION );
  }
  //�������� ��
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
  //�������� ���
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
  //�������� ���-���
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
  //�������� ���-����
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
  //�������� ����
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
  //�������� ���(���)
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
  //�������� Umin
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
  //�������� Umax
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
  //�������� ���
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
  //�������� "�������� ������� �/� ��������"
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
  //�������� "���������� ���� �����������"
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
    //������� ���� ����������� � ������� ���������
    target_label->configuration = new_configuration;
    
    unsigned int maska[N_SMALL] = {0, 0}, maska_1[N_BIG] = {0, 0, 0, 0, 0, 0}, maska_2 = 0;
  
    //����������, �� ��� ����� ����� � ������������
    if ((target_label->configuration & (1<<MTZ_BIT_CONFIGURATION)) == 0)
    {
      //������� ������ ���
      target_label->control_mtz &= (unsigned int)(~(CTR_MTZ_1 | CTR_MTZ_2 | CTR_MTZ_3 | CTR_MTZ_4));
   
      //������� ������ ��� � ���
      target_label->control_apv &= (unsigned int)(~(CTR_APV_STARTED_FROM_MTZ1 | CTR_APV_STARTED_FROM_MTZ2 | CTR_APV_STARTED_FROM_MTZ3  | CTR_APV_STARTED_FROM_MTZ4));

      //������� ������ ��� � ���
      target_label->control_zdz &= (unsigned int)(~(CTR_ZDZ_STARTED_FROM_MTZ1 | CTR_ZDZ_STARTED_FROM_MTZ2 | CTR_ZDZ_STARTED_FROM_MTZ3  | CTR_ZDZ_STARTED_FROM_MTZ4));
      
      //������� ������ ��� � ����
      target_label->control_urov &= (unsigned int)(~(CTR_UROV_STARTED_FROM_MTZ1 | CTR_UROV_STARTED_FROM_MTZ2 | CTR_UROV_STARTED_FROM_MTZ3 | CTR_UROV_STARTED_FROM_MTZ4));
      
      //������� ����� ������� ���
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

      //������ �� ������� ��� ���������� �����, �� ���������� �� ���
      for (int i = 0; i < NUMBER_DEFINED_BUTTONS; i++)
        target_label->ranguvannja_buttons[i] &= ~maska_2;
      //������ �� ������� ��� ���������� �����, �� ���������� �� ���
      for (int i = 0; i < NUMBER_INPUTS; i++)
      {
        target_label->ranguvannja_inputs[N_SMALL*i  ] &= ~maska[0];
        target_label->ranguvannja_inputs[N_SMALL*i+1] &= ~maska[1];
      }
      //������ �� ������� ��� ���������� ������, �� ���������� �� ���
      for (int i = 0; i < NUMBER_OUTPUTS; i++)
      {
        target_label->ranguvannja_outputs[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_outputs[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_outputs[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_outputs[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_outputs[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_outputs[N_BIG*i+5] &= ~maska_1[5];
      }
      //������ �� ������� ��� ���������� �������������, �� ���������� �� ���
      for (int i = 0; i < NUMBER_LEDS; i++)
      {
        target_label->ranguvannja_leds[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_leds[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_leds[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_leds[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_leds[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_leds[N_BIG*i+5] &= ~maska_1[5];
      }
      //������ �� ������� ��� ���������� ����������� ����������, �� ���������� �� ���
      target_label->ranguvannja_digital_registrator[0] &= ~maska_1[0];
      target_label->ranguvannja_digital_registrator[1] &= ~maska_1[1];
      target_label->ranguvannja_digital_registrator[2] &= ~maska_1[2];
      target_label->ranguvannja_digital_registrator[3] &= ~maska_1[3];
      target_label->ranguvannja_digital_registrator[4] &= ~maska_1[4];
      target_label->ranguvannja_digital_registrator[5] &= ~maska_1[5];
      //������ �� ������� ��� ���������� ����������� ����������, �� ���������� �� ���
      target_label->ranguvannja_analog_registrator[0] &= ~maska_1[0];
      target_label->ranguvannja_analog_registrator[1] &= ~maska_1[1];
      target_label->ranguvannja_analog_registrator[2] &= ~maska_1[2];
      target_label->ranguvannja_analog_registrator[3] &= ~maska_1[3];
      target_label->ranguvannja_analog_registrator[4] &= ~maska_1[4];
      target_label->ranguvannja_analog_registrator[5] &= ~maska_1[5];
      //������ �� ������� ��� ���������� �������������� �������, �� ���������� �� ���
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
      //������ �� ������� ��� ���������� �������������� ������, �� ���������� �� ���
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
  
    //����������, �� ��� ����� ����� � ������������
    if ((target_label->configuration & (1<<ZDZ_BIT_CONFIGURATION)) == 0)
    {
      //������� ���
      target_label->control_zdz &= (unsigned int)(~CTR_ZDZ_STATE);

      //������� ������ ��� � ����
      target_label->control_urov &= (unsigned int)(~CTR_UROV_STARTED_FROM_ZDZ);
      
      //������� ���� ������� ���
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

      //������ �� ������� ��� ���������� �����, �� ���������� �� ���
      for (int i = 0; i < NUMBER_DEFINED_BUTTONS; i++)
        target_label->ranguvannja_buttons[i] &= ~maska_2;
      //������ �� ������� ��� ���������� �����, �� ���������� �� ���
      for (int i = 0; i < NUMBER_INPUTS; i++)
      {
        target_label->ranguvannja_inputs[N_SMALL*i  ] &= ~maska[0];
        target_label->ranguvannja_inputs[N_SMALL*i+1] &= ~maska[1];
      }
      //������ �� ������� ��� ���������� ������, �� ���������� �� ���
      for (int i = 0; i < NUMBER_OUTPUTS; i++)
      {
        target_label->ranguvannja_outputs[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_outputs[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_outputs[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_outputs[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_outputs[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_outputs[N_BIG*i+5] &= ~maska_1[5];
      }
      //������ �� ������� ��� ���������� �������������, �� ���������� �� ���
      for (int i = 0; i < NUMBER_LEDS; i++)
      {
        target_label->ranguvannja_leds[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_leds[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_leds[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_leds[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_leds[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_leds[N_BIG*i+5] &= ~maska_1[5];
      }
      //������ �� ������� ��� ���������� ����������� ����������, �� ���������� �� ���
      target_label->ranguvannja_digital_registrator[0] &= ~maska_1[0];
      target_label->ranguvannja_digital_registrator[1] &= ~maska_1[1];
      target_label->ranguvannja_digital_registrator[2] &= ~maska_1[2];
      target_label->ranguvannja_digital_registrator[3] &= ~maska_1[3];
      target_label->ranguvannja_digital_registrator[4] &= ~maska_1[4];
      target_label->ranguvannja_digital_registrator[5] &= ~maska_1[5];
      //������ �� ������� ��� ���������� ����������� ����������, �� ���������� �� ���
      target_label->ranguvannja_analog_registrator[0] &= ~maska_1[0];
      target_label->ranguvannja_analog_registrator[1] &= ~maska_1[1];
      target_label->ranguvannja_analog_registrator[2] &= ~maska_1[2];
      target_label->ranguvannja_analog_registrator[3] &= ~maska_1[3];
      target_label->ranguvannja_analog_registrator[4] &= ~maska_1[4];
      target_label->ranguvannja_analog_registrator[5] &= ~maska_1[5];
      //������ �� ������� ��� ���������� �������������� �������, �� ���������� �� ���
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
      //������ �� ������� ��� ���������� �������������� ������, �� ���������� �� ���
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

    //����������, �� �� ����� ����� � ������������
    if ((target_label->configuration & (1<<ZZ_BIT_CONFIGURATION)) == 0)
    {
      //������� ��
      target_label->control_zz &= (unsigned int)(~(CTR_ZZ1_3I0_STATE | CTR_ZZ1_3U0_STATE | CTR_ZZ1_NZZ_STATE));
   
      //������� ������� 3I0, 3U0 � ��� � ����
      target_label->control_urov &= (unsigned int)(~(CTR_UROV_STARTED_FROM_3I0 | CTR_UROV_STARTED_FROM_3U0 |CTR_UROV_STARTED_FROM_NZZ));

      //������� ���� ������� ��
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

      //������ �� ������� ��� ���������� �����, �� ���������� �� ��
      for (int i = 0; i < NUMBER_DEFINED_BUTTONS; i++)
        target_label->ranguvannja_buttons[i] &= ~maska_2;
      //������ �� ������� ��� ���������� �����, �� ���������� �� ��
      for (int i = 0; i < NUMBER_INPUTS; i++)
      {
        target_label->ranguvannja_inputs[N_SMALL*i  ] &= ~maska[0];
        target_label->ranguvannja_inputs[N_SMALL*i+1] &= ~maska[1];
      }
      //������ �� ������� ��� ���������� ������, �� ���������� �� ��
      for (int i = 0; i < NUMBER_OUTPUTS; i++)
      {
        target_label->ranguvannja_outputs[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_outputs[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_outputs[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_outputs[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_outputs[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_outputs[N_BIG*i+5] &= ~maska_1[5];
      }
      //������ �� ������� ��� ���������� �������������, �� ���������� �� ��
      for (int i = 0; i < NUMBER_LEDS; i++)
      {
        target_label->ranguvannja_leds[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_leds[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_leds[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_leds[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_leds[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_leds[N_BIG*i+5] &= ~maska_1[5];
      }
      //������ �� ������� ��� ���������� ����������� ����������, �� ���������� �� ��
      target_label->ranguvannja_digital_registrator[0] &= ~maska_1[0];
      target_label->ranguvannja_digital_registrator[1] &= ~maska_1[1];
      target_label->ranguvannja_digital_registrator[2] &= ~maska_1[2];
      target_label->ranguvannja_digital_registrator[3] &= ~maska_1[3];
      target_label->ranguvannja_digital_registrator[4] &= ~maska_1[4];
      target_label->ranguvannja_digital_registrator[5] &= ~maska_1[5];
      //������ �� ������� ��� ���������� ����������� ����������, �� ���������� �� ��
      target_label->ranguvannja_analog_registrator[0] &= ~maska_1[0];
      target_label->ranguvannja_analog_registrator[1] &= ~maska_1[1];
      target_label->ranguvannja_analog_registrator[2] &= ~maska_1[2];
      target_label->ranguvannja_analog_registrator[3] &= ~maska_1[3];
      target_label->ranguvannja_analog_registrator[4] &= ~maska_1[4];
      target_label->ranguvannja_analog_registrator[5] &= ~maska_1[5];
      //������ �� ������� ��� ���������� �������������� �������, �� ���������� �� ��
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
      //������ �� ������� ��� ���������� �������������� ������, �� ���������� �� ��
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

    //����������, �� ��� ����� ����� � ������������
    if ((target_label->configuration & (1<<APV_BIT_CONFIGURATION)) == 0)
    {
      //������� ���
      target_label->control_apv &= (unsigned int)(~(CTR_APV_STAGE_1 | CTR_APV_STAGE_2 | CTR_APV_STAGE_3 | CTR_APV_STAGE_4));
   
      //������� ���� ������� ���
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

      //������ �� ������� ��� ���������� �����, �� ���������� �� ���
      for (int i = 0; i < NUMBER_DEFINED_BUTTONS; i++)
        target_label->ranguvannja_buttons[i] &= ~maska_2;
      //������ �� ������� ��� ���������� �����, �� ���������� �� ���
      for (int i = 0; i < NUMBER_INPUTS; i++)
      {
        target_label->ranguvannja_inputs[N_SMALL*i  ] &= ~maska[0];
        target_label->ranguvannja_inputs[N_SMALL*i+1] &= ~maska[1];
      }
      //������ �� ������� ��� ���������� ������, �� ���������� �� ���
      for (int i = 0; i < NUMBER_OUTPUTS; i++)
      {
        target_label->ranguvannja_outputs[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_outputs[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_outputs[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_outputs[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_outputs[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_outputs[N_BIG*i+5] &= ~maska_1[5];
      }
      //������ �� ������� ��� ���������� �������������, �� ���������� �� ���
      for (int i = 0; i < NUMBER_LEDS; i++)
      {
        target_label->ranguvannja_leds[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_leds[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_leds[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_leds[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_leds[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_leds[N_BIG*i+5] &= ~maska_1[5];
      }
      //������ �� ������� ��� ���������� ����������� ����������, �� ���������� �� ���
      target_label->ranguvannja_digital_registrator[0] &= ~maska_1[0];
      target_label->ranguvannja_digital_registrator[1] &= ~maska_1[1];
      target_label->ranguvannja_digital_registrator[2] &= ~maska_1[2];
      target_label->ranguvannja_digital_registrator[3] &= ~maska_1[3];
      target_label->ranguvannja_digital_registrator[4] &= ~maska_1[4];
      target_label->ranguvannja_digital_registrator[5] &= ~maska_1[5];
      //������ �� ������� ��� ���������� ����������� ����������, �� ���������� �� ���
      target_label->ranguvannja_analog_registrator[0] &= ~maska_1[0];
      target_label->ranguvannja_analog_registrator[1] &= ~maska_1[1];
      target_label->ranguvannja_analog_registrator[2] &= ~maska_1[2];
      target_label->ranguvannja_analog_registrator[3] &= ~maska_1[3];
      target_label->ranguvannja_analog_registrator[4] &= ~maska_1[4];
      target_label->ranguvannja_analog_registrator[5] &= ~maska_1[5];
      //������ �� ������� ��� ���������� �������������� �������, �� ���������� �� ���
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
      //������ �� ������� ��� ���������� �������������� ������, �� ���������� �� ���
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

    //����������, �� ���-��� ����� ����� � ������������
    if ((target_label->configuration & (1<<APV_ZMN_BIT_CONFIGURATION)) == 0)
    {
      //������� ���-���
      target_label->control_apv_zmn &= (unsigned int)(~CTR_APV_ZMN);
   
      //������� ���� ������� ���-���
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

      //������ �� ������� ��� ���������� �����, �� ���������� �� ���-���
      for (int i = 0; i < NUMBER_DEFINED_BUTTONS; i++)
        target_label->ranguvannja_buttons[i] &= ~maska_2;
      //������ �� ������� ��� ���������� �����, �� ���������� �� ���-���
      for (int i = 0; i < NUMBER_INPUTS; i++)
      {
        target_label->ranguvannja_inputs[N_SMALL*i  ] &= ~maska[0];
        target_label->ranguvannja_inputs[N_SMALL*i+1] &= ~maska[1];
      }
      //������ �� ������� ��� ���������� ������, �� ���������� �� ���-���
      for (int i = 0; i < NUMBER_OUTPUTS; i++)
      {
        target_label->ranguvannja_outputs[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_outputs[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_outputs[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_outputs[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_outputs[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_outputs[N_BIG*i+5] &= ~maska_1[5];
      }
      //������ �� ������� ��� ���������� �������������, �� ���������� �� ���-���
      for (int i = 0; i < NUMBER_LEDS; i++)
      {
        target_label->ranguvannja_leds[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_leds[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_leds[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_leds[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_leds[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_leds[N_BIG*i+5] &= ~maska_1[5];
      }
      //������ �� ������� ��� ���������� ����������� ����������, �� ���������� �� ���-���
      target_label->ranguvannja_digital_registrator[0] &= ~maska_1[0];
      target_label->ranguvannja_digital_registrator[1] &= ~maska_1[1];
      target_label->ranguvannja_digital_registrator[2] &= ~maska_1[2];
      target_label->ranguvannja_digital_registrator[3] &= ~maska_1[3];
      target_label->ranguvannja_digital_registrator[4] &= ~maska_1[4];
      target_label->ranguvannja_digital_registrator[5] &= ~maska_1[5];
      //������ �� ������� ��� ���������� ����������� ����������, �� ���������� �� ���-���
      target_label->ranguvannja_analog_registrator[0] &= ~maska_1[0];
      target_label->ranguvannja_analog_registrator[1] &= ~maska_1[1];
      target_label->ranguvannja_analog_registrator[2] &= ~maska_1[2];
      target_label->ranguvannja_analog_registrator[3] &= ~maska_1[3];
      target_label->ranguvannja_analog_registrator[4] &= ~maska_1[4];
      target_label->ranguvannja_analog_registrator[5] &= ~maska_1[5];
      //������ �� ������� ��� ���������� �������������� �������, �� ���������� �� ���-���
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
      //������ �� ������� ��� ���������� �������������� ������, �� ���������� �� ���-���
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

    //����������, �� ���-���� ����� ����� � ������������
    if ((target_label->configuration & (1<<ACHR_CHAPV_BIT_CONFIGURATION)) == 0)
    {
      //������� ���-����
      target_label->control_achr_chapv &= (unsigned int)(~(CTR_ACHR | CTR_CHAPV));

      //������� ������� ��� � ����
      target_label->control_urov &= (unsigned int)(~CTR_UROV_STARTED_FROM_ACHR);
      
      //������� ���� ������� ���-����
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

      //������ �� ������� ��� ���������� �����, �� ���������� �� ���-����
      for (int i = 0; i < NUMBER_DEFINED_BUTTONS; i++)
        target_label->ranguvannja_buttons[i] &= ~maska_2;
      //������ �� ������� ��� ���������� �����, �� ���������� �� ���-����
      for (int i = 0; i < NUMBER_INPUTS; i++)
      {
        target_label->ranguvannja_inputs[N_SMALL*i  ] &= ~maska[0];
        target_label->ranguvannja_inputs[N_SMALL*i+1] &= ~maska[1];
      }
      //������ �� ������� ��� ���������� ������, �� ���������� �� ���-����
      for (int i = 0; i < NUMBER_OUTPUTS; i++)
      {
        target_label->ranguvannja_outputs[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_outputs[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_outputs[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_outputs[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_outputs[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_outputs[N_BIG*i+5] &= ~maska_1[5];
      }
      //������ �� ������� ��� ���������� �������������, �� ���������� �� ���-����
      for (int i = 0; i < NUMBER_LEDS; i++)
      {
        target_label->ranguvannja_leds[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_leds[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_leds[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_leds[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_leds[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_leds[N_BIG*i+5] &= ~maska_1[5];
      }
      //������ �� ������� ��� ���������� ����������� ����������, �� ���������� �� ���-����
      target_label->ranguvannja_digital_registrator[0] &= ~maska_1[0];
      target_label->ranguvannja_digital_registrator[1] &= ~maska_1[1];
      target_label->ranguvannja_digital_registrator[2] &= ~maska_1[2];
      target_label->ranguvannja_digital_registrator[3] &= ~maska_1[3];
      target_label->ranguvannja_digital_registrator[4] &= ~maska_1[4];
      target_label->ranguvannja_digital_registrator[5] &= ~maska_1[5];
      //������ �� ������� ��� ���������� ����������� ����������, �� ���������� �� ���-����
      target_label->ranguvannja_analog_registrator[0] &= ~maska_1[0];
      target_label->ranguvannja_analog_registrator[1] &= ~maska_1[1];
      target_label->ranguvannja_analog_registrator[2] &= ~maska_1[2];
      target_label->ranguvannja_analog_registrator[3] &= ~maska_1[3];
      target_label->ranguvannja_analog_registrator[4] &= ~maska_1[4];
      target_label->ranguvannja_analog_registrator[5] &= ~maska_1[5];
      //������ �� ������� ��� ���������� �������������� �������, �� ���������� �� ���-����
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
      //������ �� ������� ��� ���������� �������������� ������, �� ���������� �� ���-����
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

    //����������, �� ���� ����� ����� � ������������
    if ((target_label->configuration & (1<<UROV_BIT_CONFIGURATION)) == 0)
    {
      //������� ����
      target_label->control_urov &= (unsigned int)(~CTR_UROV_STATE);
   
        //������� ���� ������� ����
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

      //������ �� ������� ��� ���������� �����, �� ���������� �� ����
      for (int i = 0; i < NUMBER_DEFINED_BUTTONS; i++)
        target_label->ranguvannja_buttons[i] &= ~maska_2;
      //������ �� ������� ��� ���������� �����, �� ���������� �� ����
      for (int i = 0; i < NUMBER_INPUTS; i++)
      {
        target_label->ranguvannja_inputs[N_SMALL*i  ] &= ~maska[0];
        target_label->ranguvannja_inputs[N_SMALL*i+1] &= ~maska[1];
      }
      //������ �� ������� ��� ���������� ������, �� ���������� �� ����
      for (int i = 0; i < NUMBER_OUTPUTS; i++)
      {
        target_label->ranguvannja_outputs[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_outputs[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_outputs[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_outputs[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_outputs[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_outputs[N_BIG*i+5] &= ~maska_1[5];
      }
      //������ �� ������� ��� ���������� �������������, �� ���������� �� ����
      for (int i = 0; i < NUMBER_LEDS; i++)
      {
        target_label->ranguvannja_leds[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_leds[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_leds[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_leds[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_leds[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_leds[N_BIG*i+5] &= ~maska_1[5];
      }
      //������ �� ������� ��� ���������� ����������� ����������, �� ���������� �� ����
      target_label->ranguvannja_digital_registrator[0] &= ~maska_1[0];
      target_label->ranguvannja_digital_registrator[1] &= ~maska_1[1];
      target_label->ranguvannja_digital_registrator[2] &= ~maska_1[2];
      target_label->ranguvannja_digital_registrator[3] &= ~maska_1[3];
      target_label->ranguvannja_digital_registrator[4] &= ~maska_1[4];
      target_label->ranguvannja_digital_registrator[5] &= ~maska_1[5];
      //������ �� ������� ��� ���������� ����������� ����������, �� ���������� �� ����
      target_label->ranguvannja_analog_registrator[0] &= ~maska_1[0];
      target_label->ranguvannja_analog_registrator[1] &= ~maska_1[1];
      target_label->ranguvannja_analog_registrator[2] &= ~maska_1[2];
      target_label->ranguvannja_analog_registrator[3] &= ~maska_1[3];
      target_label->ranguvannja_analog_registrator[4] &= ~maska_1[4];
      target_label->ranguvannja_analog_registrator[5] &= ~maska_1[5];
      //������ �� ������� ��� ���������� �������������� �������, �� ���������� �� ����
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
      //������ �� ������� ��� ���������� �������������� ������, �� ���������� �� ����
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

    //����������, �� ���(���) ����� ����� � ������������
    if ((target_label->configuration & (1<<ZOP_BIT_CONFIGURATION)) == 0)
    {
      //������� ���(���)
      target_label->control_zop &= (unsigned int)(~CTR_ZOP_STATE);
   
      //������� ������� ���(���) � ����
      target_label->control_urov &= (unsigned int)(~CTR_UROV_STARTED_FROM_ZOP1);

      //������� ���� ������� ���(���)
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

      //������ �� ������� ��� ���������� �����, �� ���������� �� ���(���)
      for (int i = 0; i < NUMBER_DEFINED_BUTTONS; i++)
        target_label->ranguvannja_buttons[i] &= ~maska_2;
      //������ �� ������� ��� ���������� �����, �� ���������� �� ���(���)
      for (int i = 0; i < NUMBER_INPUTS; i++)
      {
        target_label->ranguvannja_inputs[N_SMALL*i  ] &= ~maska[0];
        target_label->ranguvannja_inputs[N_SMALL*i+1] &= ~maska[1];
      }
      //������ �� ������� ��� ���������� ������, �� ���������� �� ���(���)
      for (int i = 0; i < NUMBER_OUTPUTS; i++)
      {
        target_label->ranguvannja_outputs[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_outputs[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_outputs[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_outputs[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_outputs[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_outputs[N_BIG*i+5] &= ~maska_1[5];
      }
      //������ �� ������� ��� ���������� �������������, �� ���������� �� ���(���)
      for (int i = 0; i < NUMBER_LEDS; i++)
      {
        target_label->ranguvannja_leds[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_leds[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_leds[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_leds[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_leds[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_leds[N_BIG*i+5] &= ~maska_1[5];
      }
      //������ �� ������� ��� ���������� ����������� ����������, �� ���������� �� ���(���)
      target_label->ranguvannja_digital_registrator[0] &= ~maska_1[0];
      target_label->ranguvannja_digital_registrator[1] &= ~maska_1[1];
      target_label->ranguvannja_digital_registrator[2] &= ~maska_1[2];
      target_label->ranguvannja_digital_registrator[3] &= ~maska_1[3];
      target_label->ranguvannja_digital_registrator[4] &= ~maska_1[4];
      target_label->ranguvannja_digital_registrator[5] &= ~maska_1[5];
      //������ �� ������� ��� ���������� ����������� ����������, �� ���������� �� ���(���)
      target_label->ranguvannja_analog_registrator[0] &= ~maska_1[0];
      target_label->ranguvannja_analog_registrator[1] &= ~maska_1[1];
      target_label->ranguvannja_analog_registrator[2] &= ~maska_1[2];
      target_label->ranguvannja_analog_registrator[3] &= ~maska_1[3];
      target_label->ranguvannja_analog_registrator[4] &= ~maska_1[4];
      target_label->ranguvannja_analog_registrator[5] &= ~maska_1[5];
      //������ �� ������� ��� ���������� �������������� �������, �� ���������� �� ���(���)
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
      //������ �� ������� ��� ���������� �������������� ������, �� ���������� �� ���(���)
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

    //����������, �� Umin ����� ����� � ������������
    if ((target_label->configuration & (1<<UMIN_BIT_CONFIGURATION)) == 0)
    {
      //������� ������ Umin
      target_label->control_Umin &= (unsigned int)(~(CTR_UMIN1 | CTR_UMIN2));
   
      //������� ������ Umin � ����
      target_label->control_urov &= (unsigned int)(~(CTR_UROV_STARTED_FROM_UMIN1 | CTR_UROV_STARTED_FROM_UMIN2));
      
      //������� ����� ������� Umin
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

      //������ �� ������� ��� ���������� �����, �� ���������� �� Umin
      for (int i = 0; i < NUMBER_DEFINED_BUTTONS; i++)
        target_label->ranguvannja_buttons[i] &= ~maska_2;
      //������ �� ������� ��� ���������� �����, �� ���������� �� Umin
      for (int i = 0; i < NUMBER_INPUTS; i++)
      {
        target_label->ranguvannja_inputs[N_SMALL*i  ] &= ~maska[0];
        target_label->ranguvannja_inputs[N_SMALL*i+1] &= ~maska[1];
      }
      //������ �� ������� ��� ���������� ������, �� ���������� �� Umin
      for (int i = 0; i < NUMBER_OUTPUTS; i++)
      {
        target_label->ranguvannja_outputs[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_outputs[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_outputs[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_outputs[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_outputs[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_outputs[N_BIG*i+5] &= ~maska_1[5];
      }
      //������ �� ������� ��� ���������� �������������, �� ���������� �� Umin
      for (int i = 0; i < NUMBER_LEDS; i++)
      {
        target_label->ranguvannja_leds[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_leds[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_leds[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_leds[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_leds[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_leds[N_BIG*i+5] &= ~maska_1[5];
      }
      //������ �� ������� ��� ���������� ����������� ����������, �� ���������� �� Umin
      target_label->ranguvannja_digital_registrator[0] &= ~maska_1[0];
      target_label->ranguvannja_digital_registrator[1] &= ~maska_1[1];
      target_label->ranguvannja_digital_registrator[2] &= ~maska_1[2];
      target_label->ranguvannja_digital_registrator[3] &= ~maska_1[3];
      target_label->ranguvannja_digital_registrator[4] &= ~maska_1[4];
      target_label->ranguvannja_digital_registrator[5] &= ~maska_1[5];
      //������ �� ������� ��� ���������� ����������� ����������, �� ���������� �� Umin
      target_label->ranguvannja_analog_registrator[0] &= ~maska_1[0];
      target_label->ranguvannja_analog_registrator[1] &= ~maska_1[1];
      target_label->ranguvannja_analog_registrator[2] &= ~maska_1[2];
      target_label->ranguvannja_analog_registrator[3] &= ~maska_1[3];
      target_label->ranguvannja_analog_registrator[4] &= ~maska_1[4];
      target_label->ranguvannja_analog_registrator[5] &= ~maska_1[5];
      //������ �� ������� ��� ���������� �������������� �������, �� ���������� �� Umin
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
      //������ �� ������� ��� ���������� �������������� ������, �� ���������� �� Umin
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

    //����������, �� Umax ����� ����� � ������������
    if ((target_label->configuration & (1<<UMAX_BIT_CONFIGURATION)) == 0)
    {
      //������� ������ Umax
      target_label->control_Umax &= (unsigned int)(~(CTR_UMAX1 | CTR_UMAX2));

      //������� ������ Umin � ����
      target_label->control_urov &= (unsigned int)(~(CTR_UROV_STARTED_FROM_UMAX1 | CTR_UROV_STARTED_FROM_UMAX2));
   
      //������� ����� ������� Umax
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

      //������ �� ������� ��� ���������� �����, �� ���������� �� Umax
      for (int i = 0; i < NUMBER_DEFINED_BUTTONS; i++)
        target_label->ranguvannja_buttons[i] &= ~maska_2;
      //������ �� ������� ��� ���������� �����, �� ���������� �� Umax
      for (int i = 0; i < NUMBER_INPUTS; i++)
      {
        target_label->ranguvannja_inputs[N_SMALL*i  ] &= ~maska[0];
        target_label->ranguvannja_inputs[N_SMALL*i+1] &= ~maska[1];
      }
      //������ �� ������� ��� ���������� ������, �� ���������� �� Umax
      for (int i = 0; i < NUMBER_OUTPUTS; i++)
      {
        target_label->ranguvannja_outputs[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_outputs[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_outputs[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_outputs[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_outputs[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_outputs[N_BIG*i+5] &= ~maska_1[5];
      }
      //������ �� ������� ��� ���������� �������������, �� ���������� �� Umax
      for (int i = 0; i < NUMBER_LEDS; i++)
      {
        target_label->ranguvannja_leds[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_leds[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_leds[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_leds[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_leds[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_leds[N_BIG*i+5] &= ~maska_1[5];
      }
      //������ �� ������� ��� ���������� ����������� ����������, �� ���������� �� Umax
      target_label->ranguvannja_digital_registrator[0] &= ~maska_1[0];
      target_label->ranguvannja_digital_registrator[1] &= ~maska_1[1];
      target_label->ranguvannja_digital_registrator[2] &= ~maska_1[2];
      target_label->ranguvannja_digital_registrator[3] &= ~maska_1[3];
      target_label->ranguvannja_digital_registrator[4] &= ~maska_1[4];
      target_label->ranguvannja_digital_registrator[5] &= ~maska_1[5];
      //������ �� ������� ��� ���������� ����������� ����������, �� ���������� �� Umax
      target_label->ranguvannja_analog_registrator[0] &= ~maska_1[0];
      target_label->ranguvannja_analog_registrator[1] &= ~maska_1[1];
      target_label->ranguvannja_analog_registrator[2] &= ~maska_1[2];
      target_label->ranguvannja_analog_registrator[3] &= ~maska_1[3];
      target_label->ranguvannja_analog_registrator[4] &= ~maska_1[4];
      target_label->ranguvannja_analog_registrator[5] &= ~maska_1[5];
      //������ �� ������� ��� ���������� �������������� �������, �� ���������� �� Umax
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
      //������ �� ������� ��� ���������� �������������� ������, �� ���������� �� Umax
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

    //����������, �� ��� ����� ����� � ������������
    if ((target_label->configuration & (1<<AVR_BIT_CONFIGURATION)) == 0)
    {
      //������� ������ ���
      target_label->control_avr &= (unsigned int)(~CTR_AVR);
   
      //������� ����� ������� ���
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

      //������ �� ������� ��� ���������� �����, �� ���������� �� ���
      for (int i = 0; i < NUMBER_DEFINED_BUTTONS; i++)
        target_label->ranguvannja_buttons[i] &= ~maska_2;
      //������ �� ������� ��� ���������� �����, �� ���������� �� ���
      for (int i = 0; i < NUMBER_INPUTS; i++)
      {
        target_label->ranguvannja_inputs[N_SMALL*i  ] &= ~maska[0];
        target_label->ranguvannja_inputs[N_SMALL*i+1] &= ~maska[1];
      }
      //������ �� ������� ��� ���������� ������, �� ���������� �� ���
      for (int i = 0; i < NUMBER_OUTPUTS; i++)
      {
        target_label->ranguvannja_outputs[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_outputs[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_outputs[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_outputs[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_outputs[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_outputs[N_BIG*i+5] &= ~maska_1[5];
      }
      //������ �� ������� ��� ���������� �������������, �� ���������� �� ���
      for (int i = 0; i < NUMBER_LEDS; i++)
      {
        target_label->ranguvannja_leds[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_leds[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_leds[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_leds[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_leds[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_leds[N_BIG*i+5] &= ~maska_1[5];
      }
      //������ �� ������� ��� ���������� ����������� ����������, �� ���������� �� ���
      target_label->ranguvannja_digital_registrator[0] &= ~maska_1[0];
      target_label->ranguvannja_digital_registrator[1] &= ~maska_1[1];
      target_label->ranguvannja_digital_registrator[2] &= ~maska_1[2];
      target_label->ranguvannja_digital_registrator[3] &= ~maska_1[3];
      target_label->ranguvannja_digital_registrator[4] &= ~maska_1[4];
      target_label->ranguvannja_digital_registrator[5] &= ~maska_1[5];
      //������ �� ������� ��� ���������� ����������� ����������, �� ���������� �� ���
      target_label->ranguvannja_analog_registrator[0] &= ~maska_1[0];
      target_label->ranguvannja_analog_registrator[1] &= ~maska_1[1];
      target_label->ranguvannja_analog_registrator[2] &= ~maska_1[2];
      target_label->ranguvannja_analog_registrator[3] &= ~maska_1[3];
      target_label->ranguvannja_analog_registrator[4] &= ~maska_1[4];
      target_label->ranguvannja_analog_registrator[5] &= ~maska_1[5];
      //������ �� ������� ��� ���������� �������������� �������, �� ���������� �� ���
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
      //������ �� ������� ��� ���������� �������������� ������, �� ���������� �� ���
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

    //����������, �� "�������� ������� �/� ��������" ����� ����� � ������������
    if ((target_label->configuration & (1<<CONTROL_U_BIT_CONFIGURATION)) == 0)
    {
      //������� ������ "�������� ������� �/� ��������"
      target_label->control_control_U &= (unsigned int)(~(CTR_U_OL | CTR_U_RL));
   
      //������� ����� ������� "�������� ������� �/� ��������"
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

      //������ �� ������� ��� ���������� �����, �� ���������� �� "�������� ������� �/� ��������"
      for (int i = 0; i < NUMBER_DEFINED_BUTTONS; i++)
        target_label->ranguvannja_buttons[i] &= ~maska_2;
      //������ �� ������� ��� ���������� �����, �� ���������� �� "�������� ������� �/� ��������"
      for (int i = 0; i < NUMBER_INPUTS; i++)
      {
        target_label->ranguvannja_inputs[N_SMALL*i  ] &= ~maska[0];
        target_label->ranguvannja_inputs[N_SMALL*i+1] &= ~maska[1];
      }
      //������ �� ������� ��� ���������� ������, �� ���������� �� "�������� ������� �/� ��������"
      for (int i = 0; i < NUMBER_OUTPUTS; i++)
      {
        target_label->ranguvannja_outputs[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_outputs[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_outputs[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_outputs[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_outputs[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_outputs[N_BIG*i+5] &= ~maska_1[5];
      }
      //������ �� ������� ��� ���������� �������������, �� ���������� �� "�������� ������� �/� ��������"
      for (int i = 0; i < NUMBER_LEDS; i++)
      {
        target_label->ranguvannja_leds[N_BIG*i  ] &= ~maska_1[0];
        target_label->ranguvannja_leds[N_BIG*i+1] &= ~maska_1[1];
        target_label->ranguvannja_leds[N_BIG*i+2] &= ~maska_1[2];
        target_label->ranguvannja_leds[N_BIG*i+3] &= ~maska_1[3];
        target_label->ranguvannja_leds[N_BIG*i+4] &= ~maska_1[4];
        target_label->ranguvannja_leds[N_BIG*i+5] &= ~maska_1[5];
      }
      //������ �� ������� ��� ���������� ����������� ����������, �� ���������� �� "�������� ������� �/� ��������"
      target_label->ranguvannja_digital_registrator[0] &= ~maska_1[0];
      target_label->ranguvannja_digital_registrator[1] &= ~maska_1[1];
      target_label->ranguvannja_digital_registrator[2] &= ~maska_1[2];
      target_label->ranguvannja_digital_registrator[3] &= ~maska_1[3];
      target_label->ranguvannja_digital_registrator[4] &= ~maska_1[4];
      target_label->ranguvannja_digital_registrator[5] &= ~maska_1[5];
      //������ �� ������� ��� ���������� ����������� ����������, �� ���������� �� "�������� ������� �/� ��������"
      target_label->ranguvannja_analog_registrator[0] &= ~maska_1[0];
      target_label->ranguvannja_analog_registrator[1] &= ~maska_1[1];
      target_label->ranguvannja_analog_registrator[2] &= ~maska_1[2];
      target_label->ranguvannja_analog_registrator[3] &= ~maska_1[3];
      target_label->ranguvannja_analog_registrator[4] &= ~maska_1[4];
      target_label->ranguvannja_analog_registrator[5] &= ~maska_1[5];
      //������ �� ������� ��� ���������� �������������� �������, �� ���������� �� "�������� ������� �/� ��������"
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
      //������ �� ������� ��� ���������� �������������� ������, �� ���������� �� "�������� ������� �/� ��������"
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

    //����������, �� "���������� ���� �����������" ����� ����� � ������������
    if ((target_label->configuration & (1<<VMP_BIT_CONFIGURATION)) == 0)
    {
      //������� ���
      target_label->control_vmp &= (unsigned int)(~CTR_VMP_STATE);
    }
  }
  
  return error_window;
}
/*****************************************************/

/*****************************************************/
//������� ���������� ������ ��� ��� ���� ������� ������
/*****************************************************/
void action_after_changing_phase_line(__SETTINGS *target_label)
{
  if ((target_label->control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_3U0_Ubc_TN2) != 0)
  {
    //������� 3U0 � ���
    target_label->control_zz &= (unsigned int)(~(CTR_ZZ1_3U0_STATE | CTR_ZZ1_NZZ_STATE));
    
    //������� 3U0 � ��� � ����
    target_label->control_urov &= (unsigned int)(~(CTR_UROV_STARTED_FROM_3U0 | CTR_UROV_STARTED_FROM_NZZ));
      
    unsigned int /*maska[N_SMALL] = {0,0}, */maska_1[N_BIG] = {0, 0, 0, 0, 0, 0};
    
    _SET_BIT(maska_1, RANG_OUTPUT_LED_DF_REG_PO_NZZ);
    _SET_BIT(maska_1, RANG_OUTPUT_LED_DF_REG_NZZ);
    _SET_BIT(maska_1, RANG_OUTPUT_LED_DF_REG_PO_3U0);
    _SET_BIT(maska_1, RANG_OUTPUT_LED_DF_REG_3U0);
    _SET_BIT(maska_1, RANG_OUTPUT_LED_DF_REG_SECTOR_NZZ);
    
//    //������ �� ������� ��� ���������� �����, �� ���������� �� �������� ������ 3U0
//    for (int i = 0; i < NUMBER_DEFINED_BUTTONS; i++)
//      target_label->ranguvannja_buttons[i] &= ~maska_2;
    //������ �� ������� ��� ���������� �����, �� ���������� �� �������� ������ 3U0
//    for (int i = 0; i < NUMBER_INPUTS; i++)
//    {
//      target_label->ranguvannja_inputs[N_SMALL*i  ] &= ~maska[0];
//      target_label->ranguvannja_inputs[N_SMALL*i+1] &= ~maska[1];
//    }
    //������ �� ������� ��� ���������� ������, �� ���������� �� �������� ������ 3U0
    for (int i = 0; i < NUMBER_OUTPUTS; i++)
    {
      target_label->ranguvannja_outputs[N_BIG*i  ] &= ~maska_1[0];
      target_label->ranguvannja_outputs[N_BIG*i+1] &= ~maska_1[1];
      target_label->ranguvannja_outputs[N_BIG*i+2] &= ~maska_1[2];
      target_label->ranguvannja_outputs[N_BIG*i+3] &= ~maska_1[3];
      target_label->ranguvannja_outputs[N_BIG*i+4] &= ~maska_1[4];
      target_label->ranguvannja_outputs[N_BIG*i+5] &= ~maska_1[5];
    }
    //������ �� ������� ��� ���������� �������������, �� ���������� �� �������� ������ 3U0
    for (int i = 0; i < NUMBER_LEDS; i++)
    {
      target_label->ranguvannja_leds[N_BIG*i  ] &= ~maska_1[0];
      target_label->ranguvannja_leds[N_BIG*i+1] &= ~maska_1[1];
      target_label->ranguvannja_leds[N_BIG*i+2] &= ~maska_1[2];
      target_label->ranguvannja_leds[N_BIG*i+3] &= ~maska_1[3];
      target_label->ranguvannja_leds[N_BIG*i+4] &= ~maska_1[4];
      target_label->ranguvannja_leds[N_BIG*i+5] &= ~maska_1[5];
    }
    //������ �� ������� ��� ���������� ����������� ����������, �� ���������� �� �������� ������ 3U0
    target_label->ranguvannja_digital_registrator[0] &= ~maska_1[0];
    target_label->ranguvannja_digital_registrator[1] &= ~maska_1[1];
    target_label->ranguvannja_digital_registrator[2] &= ~maska_1[2];
    target_label->ranguvannja_digital_registrator[3] &= ~maska_1[3];
    target_label->ranguvannja_digital_registrator[4] &= ~maska_1[4];
    target_label->ranguvannja_digital_registrator[5] &= ~maska_1[5];
    //������ �� ������� ��� ���������� ����������� ����������, �� ���������� �� �������� ������ 3U0
    target_label->ranguvannja_analog_registrator[0] &= ~maska_1[0];
    target_label->ranguvannja_analog_registrator[1] &= ~maska_1[1];
    target_label->ranguvannja_analog_registrator[2] &= ~maska_1[2];
    target_label->ranguvannja_analog_registrator[3] &= ~maska_1[3];
    target_label->ranguvannja_analog_registrator[4] &= ~maska_1[4];
    target_label->ranguvannja_analog_registrator[5] &= ~maska_1[5];
    //������ �� ������� ��� ���������� �������������� �������, �� ���������� �� �������� ������ 3U0
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
    //������ �� ������� ��� ���������� �������������� ������, �� ���������� �� �������� ������ 3U0
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
//������� ���������� ������ ��� ��� ���� ���� 33/3I0
/*****************************************************/
void action_after_changing_zz1_type(__SETTINGS *target_label)
{
  if ((target_label->control_zz & CTR_ZZ1_TYPE) != 0)
  {
    //������� ��� � ������ ���
    target_label->control_zz &= (unsigned int)(~(CTR_ZZ1_NZZ_STATE/* | CTR_ZZ1_SECTOR*/));
    
    //������� ��� � ����
    target_label->control_urov &= (unsigned int)(~CTR_UROV_STARTED_FROM_NZZ);
      
    unsigned int /*maska[N_SMALL] = {0,0}, */maska_1[N_BIG] = {0, 0, 0, 0, 0, 0};
    
    _SET_BIT(maska_1, RANG_OUTPUT_LED_DF_REG_PO_NZZ);
    _SET_BIT(maska_1, RANG_OUTPUT_LED_DF_REG_NZZ);
    _SET_BIT(maska_1, RANG_OUTPUT_LED_DF_REG_SECTOR_NZZ);
    
//    //������ �� ������� ��� ���������� �����, �� ���������� �� �������� ������ 3U0
//    for (int i = 0; i < NUMBER_DEFINED_BUTTONS; i++)
//      target_label->ranguvannja_buttons[i] &= ~maska_2;
    //������ �� ������� ��� ���������� �����, �� ���������� �� �������� ������ 3U0
//    for (int i = 0; i < NUMBER_INPUTS; i++)
//    {
//      target_label->ranguvannja_inputs[N_SMALL*i  ] &= ~maska[0];
//      target_label->ranguvannja_inputs[N_SMALL*i+1] &= ~maska[1];
//    }
    //������ �� ������� ��� ���������� ������, �� ���������� �� �������� ������ 3U0
    for (int i = 0; i < NUMBER_OUTPUTS; i++)
    {
      target_label->ranguvannja_outputs[N_BIG*i  ] &= ~maska_1[0];
      target_label->ranguvannja_outputs[N_BIG*i+1] &= ~maska_1[1];
      target_label->ranguvannja_outputs[N_BIG*i+2] &= ~maska_1[2];
      target_label->ranguvannja_outputs[N_BIG*i+3] &= ~maska_1[3];
      target_label->ranguvannja_outputs[N_BIG*i+4] &= ~maska_1[4];
      target_label->ranguvannja_outputs[N_BIG*i+5] &= ~maska_1[5];
    }
    //������ �� ������� ��� ���������� �������������, �� ���������� �� �������� ������ 3U0
    for (int i = 0; i < NUMBER_LEDS; i++)
    {
      target_label->ranguvannja_leds[N_BIG*i  ] &= ~maska_1[0];
      target_label->ranguvannja_leds[N_BIG*i+1] &= ~maska_1[1];
      target_label->ranguvannja_leds[N_BIG*i+2] &= ~maska_1[2];
      target_label->ranguvannja_leds[N_BIG*i+3] &= ~maska_1[3];
      target_label->ranguvannja_leds[N_BIG*i+4] &= ~maska_1[4];
      target_label->ranguvannja_leds[N_BIG*i+5] &= ~maska_1[5];
    }
    //������ �� ������� ��� ���������� ����������� ����������, �� ���������� �� �������� ������ 3U0
    target_label->ranguvannja_digital_registrator[0] &= ~maska_1[0];
    target_label->ranguvannja_digital_registrator[1] &= ~maska_1[1];
    target_label->ranguvannja_digital_registrator[2] &= ~maska_1[2];
    target_label->ranguvannja_digital_registrator[3] &= ~maska_1[3];
    target_label->ranguvannja_digital_registrator[4] &= ~maska_1[4];
    target_label->ranguvannja_digital_registrator[5] &= ~maska_1[5];
    //������ �� ������� ��� ���������� ����������� ����������, �� ���������� �� �������� ������ 3U0
    target_label->ranguvannja_analog_registrator[0] &= ~maska_1[0];
    target_label->ranguvannja_analog_registrator[1] &= ~maska_1[1];
    target_label->ranguvannja_analog_registrator[2] &= ~maska_1[2];
    target_label->ranguvannja_analog_registrator[3] &= ~maska_1[3];
    target_label->ranguvannja_analog_registrator[4] &= ~maska_1[4];
    target_label->ranguvannja_analog_registrator[5] &= ~maska_1[5];
    //������ �� ������� ��� ���������� �������������� �������, �� ���������� �� �������� ������ 3U0
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
    //������ �� ������� ��� ���������� �������������� ������, �� ���������� �� �������� ������ 3U0
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
//�������, ��� ������� ������� �� ��������, ���� ����������� �� ������� � RS-485 ����� � ����������� �����������
/*****************************************************/
void calculate_namber_bit_waiting_for_rs_485(void)
{
  unsigned int number_bits_rs_485_waiting_tmp = 10;
  
  //ϳ��������� ������� �� � ����
  if (current_settings.pare_bit_RS485 > 0) number_bits_rs_485_waiting_tmp++;
  if (current_settings.number_stop_bit_RS485 > 0) number_bits_rs_485_waiting_tmp++;
  
  //���������� ��������
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
//�������, ��� ����� ���� � ���������� � ������� ����� ��������� � EEPROM
-----------------------------------------------------
setting_rang: 0 - ����� �������
              1 - ����� ����������

source:       0 - ������� ���������
              1 - ���������
              2 - USB
              3 - RS-485
---------------------------------------------------
******************************************************/
void fix_change_settings(unsigned int setting_rang, unsigned int source)
{
  unsigned char *point_to_target;
  
  if (setting_rang == 0) point_to_target = (&current_settings)->time_setpoints;
  else point_to_target = (&current_settings)->time_ranguvannja;
  
  //�������, �� �������� ���� ���������
  information_about_settings_changed |= ((1 << USB_RECUEST)|(1 << RS485_RECUEST));
  
  //�������� ��� ������� ���
  unsigned char *label_to_time_array;
  if (copying_time == 2) label_to_time_array = time_copy;
  else label_to_time_array = time;
  for (unsigned int i = 0; i < 7; i++) *(point_to_target + i) = *(label_to_time_array + i);
  *(point_to_target + 7) = (unsigned char)(source & 0xff);
  
  //�������, �� ������� �������� � �� ����� ���� � ������� ������� ��������� � ������� � ���� ������ ������� �������
  changed_settings = CHANGED_ETAP_ENDED;
  
  //��������� ����� � EEPROM
  _SET_BIT(control_i2c_taskes, TASK_START_WRITE_SETTINGS_EEPROM_BIT);
}
/*****************************************************/

/******************************************************
³��������� �������� �������
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
//������� ���� ���������� �� ����������
/*****************************************************/
void changing_diagnostyka_state(void)
{
  /*****
  ��������� ����� ���� ����������
  
  ��������:
  - ������� � �������� ������ ���, �� ����� ������� � �� ����� ��������� � 
    ����������
  - ϳ��� ����� ��������� ���� ��������� �������� ������ ��������� (�� 
    �������� �����!!!) ��� ��� � �������� ������
  - ���� , �� �� ������ ���������/��������������� ������� � ���������� ������
    (���� � ������ ����� ��������� ������������� ������� �������� �� 
    ������������� ��� ���, �� ���� �� ���������, � ����������� ��� ���������� 
    ������� ���� �������)

  - �������� ������� ��� � ���� ������������, �� �������� ��䳿 �� ������ 
    �������� �� ��������
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
  
  //���������, �� �������� ����
  unsigned int value_changes[3], diagnostyka_now[3];
  /*
  ������ ���� ��������� ����������, �� �� ������� ������ �� ���������� ��������,
  ���� �� ��� ������ ���� ��������� ��� ��������, �� �� �� ��������� � ��� �������
  */
  diagnostyka_now[0] = diagnostyka[0];
  diagnostyka_now[1] = diagnostyka[1];
  diagnostyka_now[2] = diagnostyka[2];
  value_changes[0] = diagnostyka_before[0] ^ diagnostyka_now[0];
  value_changes[1] = diagnostyka_before[1] ^ diagnostyka_now[1];
  value_changes[2] = diagnostyka_before[2] ^ diagnostyka_now[2];
  
  /*
  � ��������� ���������� ���� �� ������������ ����� ������� � ��������� ����� � ��������
  ����� ���� �� " ����� ����.    " � " ������� ����.  "
  ���� ������� � ��������� � ��������� �� �������� � ��� ���� �������� ���, �� ���� "��������������"
  */
  
  /*****/
  //���� " ����� ����.    "
  /*****/
  if (_CHECK_SET_BIT(value_changes, EVENT_START_SYSTEM_BIT) != 0)
  {
    //����������� �� ���� " ����� ����.    " ������ ��� ����
    if (_CHECK_SET_BIT(diagnostyka_now, EVENT_START_SYSTEM_BIT) == 0)
    {
      /*
      ����� ���� ��䳿 " ����� ����.    " � ���������� ����
      ���� ������ ���, ��� �� ���� �� ������ � ��������� ���������� ���� ����� ����������
      - ������ ������������ �� ��� ���� ����� ����������
      - ������ �����������, �� � ������������ ���� ���������� �� ���� ���� ��������
      - � �������� ���� ���������� ����� ����� �� �����, �� ��� ������ � ����������
      */
      _CLEAR_BIT(value_changes, EVENT_START_SYSTEM_BIT);
      _CLEAR_BIT(diagnostyka_before, EVENT_START_SYSTEM_BIT);
    }
  }
  /*****/
  
  /*****/
  //���� " ������� ����.  "
  /*****/
  if (_CHECK_SET_BIT(value_changes, EVENT_RESTART_SYSTEM_BIT) != 0)
  {
    //����������� �� ���� " ������� ����.  " ������ ��� ����
    if (_CHECK_SET_BIT(diagnostyka_now, EVENT_RESTART_SYSTEM_BIT) == 0)
    {
      /*
      ����� ���� ��䳿 " ������� ����.  " � ���������� ����
      ���� ������ ���, ��� �� ���� �� ������ � ��������� ���������� ���� ����� ����������
      - ������ ������������ �� ��� ���� ����� ����������
      - ������ �����������, �� � ������������ ���� ���������� �� ���� ���� ��������
      - � �������� ���� ���������� ����� ����� �� �����, �� ��� ������ � ����������
      */
      _CLEAR_BIT(value_changes, EVENT_RESTART_SYSTEM_BIT);
      _CLEAR_BIT(diagnostyka_before, EVENT_RESTART_SYSTEM_BIT);
    }
  }
  /*****/

  //����������, �� ����� ���������� 䳿 ��� ��� ����������
  if (
      (value_changes[0] != 0) ||
      (value_changes[1] != 0) ||
      (value_changes[2] != 0)
     )
  {
    //� ���, �� ����� ����������, ��� �����
    
    /*****/
    //��� ��������� ������� ����� � ��������� ���������� �������
    /*****/
    if (_CHECK_SET_BIT(diagnostyka, ERROR_PR_ERR_OVERLOAD_BIT) == 0)
    {
      /*
      ����� ����� ������ ����� ���, ���� ���������� �� ���� ����������� 
      ������������ ������, ������ ������, ���� ����� � ��������� ���������� ����
      ������ ���� ��� ������������ ������
      */
      
      //��������� ������� ��������� ������ � ����� ��� ���������� ���������� ����
      int number_empty_cells;
      unsigned int head = head_fifo_buffer_pr_err_records, tail = tail_fifo_buffer_pr_err_records;
      number_empty_cells = (int)(((unsigned int)tail) - ((unsigned int)head));
      while (number_empty_cells <= 0) number_empty_cells += MAX_NUMBER_RECORDS_PR_ERR_INTO_BUFFER;
      if (number_empty_cells == 1)
      {
        //�� � ������� ����� ������, �� �������, �� � ��� ������� ���������� ����� ���������� ������
        _SET_BIT(diagnostyka, ERROR_PR_ERR_OVERLOAD_BIT);
        /*
        �������� ���� ����� ����������, ��� ����� ��������� � ������ ������� ,����
        ������ ��������� ���� ��������� ����������, ��� ���� ��������� � � ���� �� ��������
        �� ���������� ��������� ����� ���������� �� ������� ���� ������� �
        ���������, �� ����� �� ������ ����������
        */
        diagnostyka_now[0] = diagnostyka[0];
        diagnostyka_now[1] = diagnostyka[1];
        diagnostyka_now[2] = diagnostyka[2];
        
        //ϳ��������� ���� ������� ��� � ����������
        value_changes[0] = diagnostyka_before[0] ^ diagnostyka_now[0];
        value_changes[1] = diagnostyka_before[1] ^ diagnostyka_now[1];
        value_changes[2] = diagnostyka_before[2] ^ diagnostyka_now[2];
      }

      //���������� ������� ��� �������
      unsigned int number_changes = 0;
      for(unsigned int i = 0; i < (8*sizeof(value_changes)); i++)
      {
        if (_CHECK_SET_BIT(value_changes, i) != 0) number_changes++;
      }

      if(number_changes != 0)
      {
        /*
        ���������� ���� ���� ��������, �� �� ������ ����������� ��� ������������ ������
        FIFO ��� ������ ���������� ���������� ����  � �� ���� ����� ����, ��� ��� �����
        � ����� ���� ����� ������, ���� �� ����� ��������� ����������� ��� ������������.
        ���� �� �� ������ ����� �� ����������� - ���� � �� ������ ������ ������ ������, 
        �� �������� � ���� ���� ����
        */
        
        //��������� ������ � ����� ������ ���������� ������� � ����� ���� ������ ����������� ���
        unsigned int index_into_buffer_pr_err = head*SIZE_ONE_RECORD_PR_ERR;
      
        //������� ���� ������� ������
        buffer_pr_err_records[index_into_buffer_pr_err + 0] = LABEL_START_RECORD_PR_ERR;

        //��� �������� ���� � ����������
        if(
           (_CHECK_SET_BIT(diagnostyka, EVENT_START_SYSTEM_BIT   ) == 0) &&
           (_CHECK_SET_BIT(diagnostyka, EVENT_RESTART_SYSTEM_BIT ) == 0) &&
           (_CHECK_SET_BIT(diagnostyka, EVENT_STOP_SYSTEM_BIT    ) == 0)
          )
        {
          //��� �������� ����� ����������� ���� - ����� ��������� ��� � ��� �
          unsigned char *label_to_time_array;
          if (copying_time == 2) label_to_time_array = time_copy;
          else label_to_time_array = time;
          for(unsigned int i = 0; i < 7; i++) buffer_pr_err_records[index_into_buffer_pr_err + 1 + i] = *(label_to_time_array + i);
        }
        else
        {
          //�� �� �������� ����� ����������� ���� - ���� ������ �� ���� �������� ������ 0xff, � ����, ���� ��������� ��� ���������, �� �� �� ���� ��������
          for(unsigned int i = 0; i < 7; i++)  buffer_pr_err_records[index_into_buffer_pr_err + 1 + i] = 0xff;
        }

        buffer_pr_err_records[index_into_buffer_pr_err + 8] = number_changes & 0xff;
      
        //�������� ��������� ���� ����������
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

        //�������� �������� ���� ����������
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
        � ��������� ���������� ���� �� ������������ ����� ������� � ��������� ����� � ��������
        ����� ��䳿 �� " �������.����.  " � �� ���� �� �� ���� �������� � ������� ����������,
        �� ��, ��������, ����, ��� ���� ���� �� ���������� ��������� ������� � ������.
        ����� �� ���� "������������ ������ ������"
        ���� ������� � ��������� � ������� �� ������� � ����� �������� ��� �� � �������� ���������,
        ��� ���� ����� ���� ���������� � �����. ���� ������� �� ��������� ���� ����������, ��� � � �����
        ����������, ���� ������� �� ������� ���� ���� ����������
        */
        if (_CHECK_SET_BIT(value_changes, EVENT_STOP_SYSTEM_BIT) != 0)
        {
          /*
          C��� ��䳿 " �������.����.  " ������� (����������� ����� ���������� �������������
          ���� � ��������� ����� � �������� ����)
          ���� ������ ��� ��������
          - ������ ������������ �� � �����, ���� ����� ���� ���������� � ����� ������������ �����
          - ������ ������������ �� � �����, ���� ������� �� ������� ���� ���� ����������
          */
          _CLEAR_BIT(diagnostyka_now, EVENT_STOP_SYSTEM_BIT);
          _CLEAR_BIT(diagnostyka, EVENT_STOP_SYSTEM_BIT);
        }

        //Գ����� ��������� ����, ���� �� ��� �������� � ������� ����� ������ ��������� ��� ����
        diagnostyka_before[0] = diagnostyka_now[0];
        diagnostyka_before[1] = diagnostyka_now[1];
        diagnostyka_before[2] = diagnostyka_now[2];

        //ϳ������������� �� ������� ������ � ��������� ���������� ����
          unsigned int next_index_into_fifo_buffer = head + 1;
          while(next_index_into_fifo_buffer >= MAX_NUMBER_RECORDS_PR_ERR_INTO_BUFFER) next_index_into_fifo_buffer -= MAX_NUMBER_RECORDS_PR_ERR_INTO_BUFFER;
          
          //������������ ���� �������� ������ ������ FIFO 
          head_fifo_buffer_pr_err_records = next_index_into_fifo_buffer;
      }
    }
    /*****/
  }
}
/*****************************************************/

/*****************************************************/
//ϳ�������� ������� ����������� �������� � ������ ���'�� ������� ��� ����������� ���������� source
/*****************************************************/
unsigned int count_number_set_bit(unsigned int* source, unsigned int total_number)
{
  unsigned int count = 0;
  unsigned int offset, shift;
  
  for (unsigned int i = 0; i < total_number; i++)  
  {
    offset = i >> 5; //�� �, ��������, ������ �� 32
    shift  = (i & (32 - 1)); //�� �, ��������, ���������� ������ �� ������ �� 32
    if ( ( (*(source + offset))  & ((unsigned int)(1 << shift)) ) != 0 ) count++;
  }

  return count;
}
/*****************************************************/

/*****************************************************/
//�������� ����������� ���������
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
    //�������� ����������� ������� ��������� ������� ������
    
    //������� ����������� � ���� ����������
    _SET_BIT(clear_diagnostyka, ERROR_SETTINGS_EEPROM_CONTROL_BIT);
  }
  else
  {
    //�������� ����������� ������� ��������� �� �������

    //���������� ����������� � ���� ����������
    _SET_BIT(set_diagnostyka, ERROR_SETTINGS_EEPROM_CONTROL_BIT);
  }
}
/*****************************************************/

/*****************************************************/
//�������� ����������� ���������
/*****************************************************/
void control_ustuvannja(void)
{
  unsigned char crc_ustuvannja_tmp = 0, temp_value_1, temp_value_2;
  unsigned char  *point_1; 
  unsigned char  *point_2; 
  unsigned int i = 0, difference = 0;

  /*
  � ��������� ���� ������� ������������� ���� ������ �������� �����������,
  ���� ����� ����� ���� unsigned int
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
  �� ����� ������������ ����������� ������� ������, ���� ������ � ����������� ��������,
  �� �������� �������, �� �� ������ ����������������� � ������������� �� ����� ��������,
  �� ���� ������ �� ����
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
    //�������� ����������� ��������� ������� ������
    
    //������� ����������� � ���� ����������
    _SET_BIT(clear_diagnostyka, ERROR_USTUVANNJA_EEPROM_CONTROL_BIT);
  }
  else
  {
    //�������� ����������� ��������� �� �������

    //���������� ����������� � ���� ����������
    _SET_BIT(set_diagnostyka, ERROR_USTUVANNJA_EEPROM_CONTROL_BIT);
  }
}
/*****************************************************/

/*****************************************************/
//�������� ����������� ������� ����������
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
    //�������� ����������� ��������� ������� ������
    
    //������� ����������� � ���� ����������
    _SET_BIT(clear_diagnostyka, ERROR_TRG_FUNC_EEPROM_CONTROL_BIT);
  }
  else
  {
    //�������� ����������� ��������� �� �������

    //���������� ����������� � ���� ����������
    _SET_BIT(set_diagnostyka, ERROR_TRG_FUNC_EEPROM_CONTROL_BIT);
  }
}
/*****************************************************/

/*****************************************************/
//�������� ����������� ���������� �� �����������
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
    //�������� ����������� ���������� ������� ������
    result = 1;    
  }
  else
  {
    //�������� ����������� ���������� �� �������
    result = 0;    
  }
  
  return result;
}
/*****************************************************/

/*****************************************************/
//�������� ����������� ��������� �������
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
    //�������� ����������� ������� ��������� ������� ������
    
    //������� ����������� � ���� ����������
    _SET_BIT(clear_diagnostyka, ERROR_RESURS_EEPROM_CONTROL_BIT);
  }
  else
  {
    //�������� ����������� ��������� �� �������

    //���������� ����������� � ���� ����������
    _SET_BIT(set_diagnostyka, ERROR_RESURS_EEPROM_CONTROL_BIT);
  }
  
}
/*****************************************************/

/*****************************************************/
//���������� ������ ����� � ��������� __DATE__
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
    i += 1; /*��� ��������� ������ ���� � "1", � �� � "0"*/
    return ((i / 10) << 4) + (i % 10);
  }
  else return 0;
}
/*****************************************************/

/*****************************************************/
/*****************************************************/
//
/*****************************************************/
