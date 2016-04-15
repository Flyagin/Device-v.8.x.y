#ifndef __TYPE_DEFINITION__
#define __TYPE_DEFINITION__

#define SRAM1 _Pragma("location=\"variables_RAM1\"")

typedef struct
{
  int current_level;                  //������� ����� �������������� ������
 
  int index_position;                 //����� �� ��� �� ����� � �������

  int position_cursor_x;              //X - ���������� �������
  int position_cursor_y;              //Y - ���������� �������
  
  unsigned int edition;               //0 - ���� ����� �� � ����� ����������;
                                      //1 - ���� ����� � ����� �����������;
                                      //2 - ���� ���� ������������ �����������
                                      //3 - � ��� �������� ����������� ��� ��, �� �� ��� �������� ����� ���� ����������� ������� �������������
  
  unsigned int cursor_on;             //1 - ������ ������������/ 0 - ������ �� ������������
  unsigned int cursor_blinking_on;    //1 - ������ ����/ 0 - ������ �� ����
  
  unsigned int current_action;        //ĳ� ��� ����� �������� � ������� �������
                                      //0 - ͳ���� �� ����������
                                      //1 - ���������� ������, �/��� ������ ���� ���� �����������
                                      //2 - ������� �������� ����������

} __CURRENT_EKRAN;

typedef struct
{
  int position_cursor_x;              //X - ���������� �������

  unsigned int cursor_on;             //1 - ������ ������������/ 0 - ������ �� ������������
  unsigned int cursor_blinking_on;    //1 - ������ ����/ 0 - ������ �� ����
} __PREVIOUS_STATE_CURSOR;

typedef struct
{
  //��� ��������
  unsigned int device_id;
  
  //�������� �����
  unsigned int type_of_input;                          //��� ����������� ����� 0 - ������, 1 - ���������
  unsigned int type_of_input_signal;                   //��� ������� ����������� ����� 0 - �������� , 1 - ������
  unsigned int dopusk_dv[NUMBER_INPUTS];              //������� ��
    
  unsigned int ranguvannja_inputs[N_SMALL*NUMBER_INPUTS]; //���������� ���������� �����
  unsigned int ranguvannja_outputs[N_BIG*NUMBER_OUTPUTS]; //���������� ���������� ������
  unsigned int ranguvannja_leds[N_BIG*NUMBER_LEDS];       //���������� �������������

  unsigned int ranguvannja_analog_registrator[N_BIG];     //���������� ����������� ����������
  unsigned int ranguvannja_digital_registrator[N_BIG];    //���������� ����������� ����������
  
  //��� ���������� ������
  unsigned int type_of_output;                        //��� ���������� ������
                                                      //0 - ���������
                                                      //1 - ����������
  
  //��� ��������������
  unsigned int type_of_led;                           //��� �������������
                                                      //0 - ����������
                                                      //1 - ���������
    
  //������������ �������
  unsigned int type_df;                                                 //��� ������������� �������
                                                                        //0 - �����
                                                                        //1 - ��������
  unsigned int timeout_pause_df[NUMBER_DEFINED_FUNCTIONS];              //��� �������� ���������� ������������� �������
  unsigned int timeout_work_df[NUMBER_DEFINED_FUNCTIONS];               //��� ������ ������������� �������
  unsigned int ranguvannja_df_source_plus[N_BIG*NUMBER_DEFINED_FUNCTIONS];  //���������� ������ ������ ������������� �������
  unsigned int ranguvannja_df_source_minus[N_BIG*NUMBER_DEFINED_FUNCTIONS]; //���������� ��������� ������ ������������� �������
  unsigned int ranguvannja_df_source_blk[N_BIG*NUMBER_DEFINED_FUNCTIONS];   //���������� ������ ���������� ������������� �������

  unsigned int ranguvannja_set_dt_source_plus[N_BIG*NUMBER_DEFINED_TRIGGERS];   //���������� ������ ������ ������������ �������������� ������
  unsigned int ranguvannja_set_dt_source_minus[N_BIG*NUMBER_DEFINED_TRIGGERS];  //���������� ��������� ������ ������������ �������������� ������
  unsigned int ranguvannja_reset_dt_source_plus[N_BIG*NUMBER_DEFINED_TRIGGERS]; //���������� ������ ������ �������� �������������� ������
  unsigned int ranguvannja_reset_dt_source_minus[N_BIG*NUMBER_DEFINED_TRIGGERS];//���������� ��������� ������ �������� �������������� ������
  
  unsigned int ranguvannja_buttons[NUMBER_DEFINED_BUTTONS];             //���������� ������������ ������
  
  unsigned int configuration;         //������������ �������
  
  unsigned int grupa_ustavok;         //����� �������
                                      // 1 - ����� 1
                                      // 2 - ����� 2
                                      // 3 - ����� 3
                                      // 4 - ����� 4
  
  //���
  int type_mtz1;                                                //��� ���1 (0 - ������, 1 - ����������, 2 -  � ������ �� ������)
  unsigned int setpoint_mtz_1[NUMBER_GROUP_USTAVOK];            //������� ��� ����� ������ (������)
  unsigned int setpoint_mtz_1_n_vpered[NUMBER_GROUP_USTAVOK];   //������� ��� ����� ������ (����������:������)
  unsigned int setpoint_mtz_1_n_nazad[NUMBER_GROUP_USTAVOK];    //������� ��� ����� ������ (����������:�����)
  unsigned int setpoint_mtz_1_angle[NUMBER_GROUP_USTAVOK];      //������� ��� ����� ������ (��� ��������)
           int setpoint_mtz_1_angle_cos[NUMBER_GROUP_USTAVOK];  //������� ��� ����� ������ (������� ���� ��������)
           int setpoint_mtz_1_angle_sin[NUMBER_GROUP_USTAVOK];  //������� ��� ����� ������ (����� ���� ��������)
  unsigned int setpoint_mtz_1_po_napruzi[NUMBER_GROUP_USTAVOK]; //������� ��� ����� ������ (�� ������)
  unsigned int setpoint_mtz_1_U[NUMBER_GROUP_USTAVOK];          //������� ��� ����� ������ (������� �����)
  int type_mtz2;                                                //��� ���2 (0 - ������, 1 - ����������, 2 -  � ������ �� ������, 3 - ������� �, 4 - ������� �, 5 - ������� �, 6 - ��-80, 7- ���-1)
  unsigned int setpoint_mtz_2[NUMBER_GROUP_USTAVOK];            //������� ��� ����� ������
  unsigned int setpoint_mtz_2_n_vpered[NUMBER_GROUP_USTAVOK];   //������� ��� ����� ������ (����������:������)
  unsigned int setpoint_mtz_2_n_nazad[NUMBER_GROUP_USTAVOK];    //������� ��� ����� ������ (����������:�����)
  unsigned int setpoint_mtz_2_angle[NUMBER_GROUP_USTAVOK];      //������� ��� ����� ������ (��� ��������)
           int setpoint_mtz_2_angle_cos[NUMBER_GROUP_USTAVOK];  //������� ��� ����� ������ (������� ���� ��������)
           int setpoint_mtz_2_angle_sin[NUMBER_GROUP_USTAVOK];  //������� ��� ����� ������ (����� ���� ��������)
  unsigned int setpoint_mtz_2_po_napruzi[NUMBER_GROUP_USTAVOK]; //������� ��� ����� ������ (�� ������)
  unsigned int setpoint_mtz_2_U[NUMBER_GROUP_USTAVOK];          //������� ��� ����� ������ (������� �����)
  int type_mtz3;                                                //��� ���3 (0 - ������, 1 - ����������, 2 -  � ������ �� ������)
  unsigned int setpoint_mtz_3[NUMBER_GROUP_USTAVOK];            //������� ��� ������ ������
  unsigned int setpoint_mtz_3_n_vpered[NUMBER_GROUP_USTAVOK];   //������� ��� ������ ������ (����������:������)
  unsigned int setpoint_mtz_3_n_nazad[NUMBER_GROUP_USTAVOK];    //������� ��� ������ ������ (����������:�����)
  unsigned int setpoint_mtz_3_angle[NUMBER_GROUP_USTAVOK];      //������� ��� ������ ������ (��� ��������)
           int setpoint_mtz_3_angle_cos[NUMBER_GROUP_USTAVOK];  //������� ��� ������ ������ (������� ���� ��������)
           int setpoint_mtz_3_angle_sin[NUMBER_GROUP_USTAVOK];  //������� ��� ������ ������ (����� ���� ��������)
  unsigned int setpoint_mtz_3_po_napruzi[NUMBER_GROUP_USTAVOK]; //������� ��� ������ ������ (�� ������)
  unsigned int setpoint_mtz_3_U[NUMBER_GROUP_USTAVOK];          //������� ��� ������ ������ (������� �����)
  int type_mtz4;                                                //��� ���4 (0 - ������, 1 - ����������, 2 -  � ������ �� ������)
  unsigned int setpoint_mtz_4[NUMBER_GROUP_USTAVOK];            //������� ��� �������� ������
  unsigned int setpoint_mtz_4_n_vpered[NUMBER_GROUP_USTAVOK];   //������� ��� �������� ������ (����������:������)
  unsigned int setpoint_mtz_4_n_nazad[NUMBER_GROUP_USTAVOK];    //������� ��� �������� ������ (����������:�����)
  unsigned int setpoint_mtz_4_angle[NUMBER_GROUP_USTAVOK];      //������� ��� �������� ������ (��� ��������)
           int setpoint_mtz_4_angle_cos[NUMBER_GROUP_USTAVOK];  //������� ��� �������� ������ (������� ���� ��������)
           int setpoint_mtz_4_angle_sin[NUMBER_GROUP_USTAVOK];  //������� ��� �������� ������ (����� ���� ��������)
  unsigned int setpoint_mtz_4_po_napruzi[NUMBER_GROUP_USTAVOK]; //������� ��� �������� ������ (�� ������)
  unsigned int setpoint_mtz_4_U[NUMBER_GROUP_USTAVOK];          //������� ��� �������� ������ (������� �����)

  int timeout_mtz_1[NUMBER_GROUP_USTAVOK];                      //�������� ��� ����� ������
  int timeout_mtz_1_n_vpered[NUMBER_GROUP_USTAVOK];             //�������� ��� ����� ������ (����������:������)
  int timeout_mtz_1_n_nazad[NUMBER_GROUP_USTAVOK];              //�������� ��� ����� ������ (����������:�����)
  int timeout_mtz_1_po_napruzi[NUMBER_GROUP_USTAVOK];           //�������� ��� ����� ������ (�� ������)
  int timeout_mtz_2[NUMBER_GROUP_USTAVOK];                      //�������� ��� ����� ������
  int timeout_mtz_2_pr[NUMBER_GROUP_USTAVOK];                   //�������� ����������� ��� ����� ������
  int timeout_mtz_2_n_vpered[NUMBER_GROUP_USTAVOK];             //�������� ��� ����� ������ (����������:������)
  int timeout_mtz_2_n_vpered_pr[NUMBER_GROUP_USTAVOK];          //�������� ����������� ��� ����� ������ (����������:������)
  int timeout_mtz_2_n_nazad[NUMBER_GROUP_USTAVOK];              //�������� ��� ����� ������ (����������:�����)
  int timeout_mtz_2_n_nazad_pr[NUMBER_GROUP_USTAVOK];           //�������� ����������� ��� ����� ������ (����������:�����)
  int timeout_mtz_2_po_napruzi[NUMBER_GROUP_USTAVOK];           //�������� ��� ����� ������ (�� ������)
  int timeout_mtz_2_po_napruzi_pr[NUMBER_GROUP_USTAVOK];        //�������� ����������� ��� ����� ������ (�� ������)
  int timeout_mtz_2_vvid_pr[NUMBER_GROUP_USTAVOK];              //�������� ����� ���������� ���2
  int timeout_mtz_3[NUMBER_GROUP_USTAVOK];                      //�������� ��� ������ ������
  int timeout_mtz_3_n_vpered[NUMBER_GROUP_USTAVOK];             //�������� ��� ������ ������ (����������:������)
  int timeout_mtz_3_n_nazad[NUMBER_GROUP_USTAVOK];              //�������� ��� ������ ������ (����������:�����)
  int timeout_mtz_3_po_napruzi[NUMBER_GROUP_USTAVOK];           //�������� ��� ������ ������ (�� ������)
  int timeout_mtz_4[NUMBER_GROUP_USTAVOK];                      //�������� ��� �������� ������
  int timeout_mtz_4_n_vpered[NUMBER_GROUP_USTAVOK];             //�������� ��� ������ ������ (����������:������)
  int timeout_mtz_4_n_nazad[NUMBER_GROUP_USTAVOK];              //�������� ��� ������ ������ (����������:�����)
  int timeout_mtz_4_po_napruzi[NUMBER_GROUP_USTAVOK];           //�������� ��� ������ ������ (�� ������)

  unsigned int control_mtz;                                 //���� ��� ��������� ���
  
  //���
  unsigned int control_zdz;                                 //���� ��� ��������� ���

  //��
  unsigned int setpoint_zz_3I0[NUMBER_GROUP_USTAVOK];       //������� ��/3I0
  unsigned int setpoint_zz_3U0[NUMBER_GROUP_USTAVOK];       //������� ��/3U0

  int timeout_zz_3I0[NUMBER_GROUP_USTAVOK];                 //�������� ��/3I0
  int timeout_zz_3U0[NUMBER_GROUP_USTAVOK];                 //�������� ��/3I0
  int timeout_nzz[NUMBER_GROUP_USTAVOK];                    //�������� ���

   unsigned int control_zz;              //���� ��� ��������� ��

  //���
  int timeout_apv_1[NUMBER_GROUP_USTAVOK];                    //�������� 1 ����� ���
  int timeout_apv_2[NUMBER_GROUP_USTAVOK];                    //�������� 2 ����� ���
  int timeout_apv_3[NUMBER_GROUP_USTAVOK];                    //�������� 3 ����� ���
  int timeout_apv_4[NUMBER_GROUP_USTAVOK];                    //�������� 4 ����� ���
  int timeout_apv_block_vid_apv1[NUMBER_GROUP_USTAVOK];       //���������� ��� �� ������ ���1
  int timeout_apv_block_vid_apv2[NUMBER_GROUP_USTAVOK];       //���������� ��� �� ������ ���2
  int timeout_apv_block_vid_apv3[NUMBER_GROUP_USTAVOK];       //���������� ��� �� ������ ���3
  int timeout_apv_block_vid_apv4[NUMBER_GROUP_USTAVOK];       //���������� ��� �� ������ ���4
  int timeout_apv_block_vid_VV[NUMBER_GROUP_USTAVOK];         //�������� ���������� ��� � ������� ��������� ��������
  unsigned int control_apv;             //���� ��� ��������� ���
  
  //��� ���
  unsigned int setpoint_apv_zmn1[NUMBER_GROUP_USTAVOK];       //������� ��� ���1
  unsigned int setpoint_apv_zmn2[NUMBER_GROUP_USTAVOK];       //������� ��� ���2
  unsigned int setpoint_kratn_apv_zmn[NUMBER_GROUP_USTAVOK];  //�������� ��� ���
  int timeout_apv_zmn_1[NUMBER_GROUP_USTAVOK];                //�������� ����� ��� ���1
  int timeout_apv_zmn_2[NUMBER_GROUP_USTAVOK];                //�������� ����� ��� ���2
  int timeout_apv_zmn_zavershennja[NUMBER_GROUP_USTAVOK];     //�������� ���������� ������ ����� ���-��� (��� ������ �������)
  unsigned int control_apv_zmn;                               //���� ��� ��������� ��� ���
  
  //���-����
  unsigned int setpoint_achr_f_rab[NUMBER_GROUP_USTAVOK];    //������� F��� ��� ������� F1
  unsigned int setpoint_chapv_f_rab[NUMBER_GROUP_USTAVOK];   //������� F��� ���� ������� F1
  unsigned int setpoint_achr_chapv_uf1[NUMBER_GROUP_USTAVOK]; //������� ��� ���� UF1
  unsigned int setpoint_achr_chapv_uf2[NUMBER_GROUP_USTAVOK]; //������� ��� ���� UF2

  int timeout_achr_1[NUMBER_GROUP_USTAVOK];                   //�������� ����� ���1
  int timeout_chapv_1[NUMBER_GROUP_USTAVOK];                  //�������� ����� ����1
  int timeout_achr_2[NUMBER_GROUP_USTAVOK];                   //�������� ����� ���2
  int timeout_chapv_2[NUMBER_GROUP_USTAVOK];                  //�������� ����� ����2
  unsigned int control_achr_chapv;      //���� ��� ��������� ���-����
  
  //����
  unsigned int setpoint_urov[NUMBER_GROUP_USTAVOK];         //������� ����
  int timeout_urov_1[NUMBER_GROUP_USTAVOK];                 //�������� ���� ����� ������
  int timeout_urov_2[NUMBER_GROUP_USTAVOK];                 //�������� ���� ����� ������
  unsigned int control_urov;                                //���� ��� ��������� ����

  //���(���)
  unsigned int setpoint_zop[NUMBER_GROUP_USTAVOK];          //������� ���(���)
  int timeout_zop[NUMBER_GROUP_USTAVOK];                    //��������  ���(���)
  unsigned int control_zop;                                 //���� ��� ��������� ���(���)

  //Umin
  unsigned int setpoint_Umin1[NUMBER_GROUP_USTAVOK];        //������� Umin1
  unsigned int setpoint_Umin1_Iblk[NUMBER_GROUP_USTAVOK];   //������� ���������� �� ������ Umin1
  unsigned int setpoint_Umin2[NUMBER_GROUP_USTAVOK];        //������� Umin2
  unsigned int setpoint_Umin2_Iblk[NUMBER_GROUP_USTAVOK];   //������� ���������� �� ������ Umin2
  int timeout_Umin1[NUMBER_GROUP_USTAVOK];                    //��������  Umin1
  int timeout_Umin2[NUMBER_GROUP_USTAVOK];                    //��������  Umin2
  unsigned int control_Umin;                                 //���� ��� ��������� Umin
  
  //Umax
  unsigned int setpoint_Umax1[NUMBER_GROUP_USTAVOK];        //������� Umax1
  unsigned int setpoint_Umax2[NUMBER_GROUP_USTAVOK];        //������� Umax2
  int timeout_Umax1[NUMBER_GROUP_USTAVOK];                  //��������  Umax1
  int timeout_Umax2[NUMBER_GROUP_USTAVOK];                  //��������  Umax2
  unsigned int control_Umax;                                //���� ��� ��������� Umax

  //���
  unsigned int setpoint_avr_min1[NUMBER_GROUP_USTAVOK];       //������� ��� min1
  unsigned int setpoint_avr_max1[NUMBER_GROUP_USTAVOK];       //������� ��� max1
  unsigned int setpoint_avr_min2[NUMBER_GROUP_USTAVOK];       //������� ��� min2
  unsigned int setpoint_avr_max2[NUMBER_GROUP_USTAVOK];       //������� ��� max2
  unsigned int setpoint_kratn_avr[NUMBER_GROUP_USTAVOK];      //�������� ���
  int timeout_avr_ol[NUMBER_GROUP_USTAVOK];                   //�������� ����� ��� ��
  int timeout_avr_rl[NUMBER_GROUP_USTAVOK];                   //�������� ����� ��� ��
  int timeout_avr_zavershennja[NUMBER_GROUP_USTAVOK];         //�������� ���������� ������ ����� ��� (��� ������ �������)
  int timeout_avr_reset_blk[NUMBER_GROUP_USTAVOK];            //�������� �������� ���������� ��� �� �������� �� ����� �� ���� ��������
  unsigned int control_avr;                                   //���� ��� ��������� ���

  //�������� ������� ��
  unsigned int setpoint_U_ol[NUMBER_GROUP_USTAVOK];           //������� U ��
  unsigned int setpoint_U_rl[NUMBER_GROUP_USTAVOK];           //������� U ��
  int timeout_U_ol[NUMBER_GROUP_USTAVOK];                     //������ U ��
  int timeout_U_rl[NUMBER_GROUP_USTAVOK];                     //������ U ��
  unsigned int control_control_U;            					  //���� ��� ��������� U ��

  unsigned int T0;                      //���������� ������������� ��� �������������� 3I0
  unsigned int TCurrent;                //���������� ������������� ��� �������������� ������
  unsigned int TVoltage;                //���������� ������������� ��� �������������� ������
  
  unsigned int password1;                                       //������ ��� ����������� � ����
  unsigned int password2;                                       //������ ��� ������� ��������� ���㳿 � ������� ��������
  unsigned int timeout_deactivation_password_interface_USB;     //��� ����������� ������ ��� ����������� � ���������� USB
  unsigned int password_interface_USB;                          //������ ��� ����������� � ���������� USB
  unsigned int timeout_deactivation_password_interface_RS485;   //��� ����������� ������ ��� ����������� � ���������� RS485
  unsigned int password_interface_RS485;                        //������ ��� ����������� � ���������� RS485
  
  //�������
  unsigned int setpoint_Inom;                   //���������� ����� ��������
  unsigned int setpoint_r_kom_st_Inom;          //������ ������������ ������� ��� ����������� ����� ��������
  unsigned int setpoint_Inom_vymk;              //���������� ����� ��������� ��������
  unsigned int setpoint_r_kom_st_Inom_vymk;     //������ ������������ ������� ��� ����������� ����� ��������� ��������
  unsigned int setpoint_pochatkovyj_resurs;     //���������� ������ ��������
  unsigned int setpoint_krytychnyj_resurs;      //��������� ������ ��������
  unsigned int setpoint_pochatkova_k_vymk;      //��������� ������� ��������
  int timeout_swch_on;                          //�������� T ���.
  int timeout_swch_off;                         //�������� T ����.
  int timeout_swch_udl_blk_on;                  //�������� T "��������� ������� ���������� ���������"
  int timeout_pryvoda_VV;                       //�������� T "������� ��"
  unsigned int control_switch;                  //���� ��� ��������� ���������
  
  //���������� ���� �����������
  unsigned int lines[2];                        //ʳ������ ������
  unsigned int dovgyna[2][MAX_NUMBER_LINES_VMP];//������� ���
  unsigned int opir[2][MAX_NUMBER_LINES_VMP];   //������� ��� ���
  unsigned int control_vmp;                     //���� ��� ��������� ���
  
  //���������� ���������
  unsigned int prefault_number_periods; //��� ����������� ������ (������� ������ ���������� �������)
  unsigned int postfault_number_periods;//��� ����������� ������ (������� ������ ���������� �������)

  //����������
  unsigned int name_of_cell[MAX_CHAR_IN_NAME_OF_CELL];//�'�� ������
  unsigned int volatile address;                      //������
  int speed_RS485;                                    //�������� �����
                                                        // 0 - 9600
                                                        // 1 - 14400
                                                        // 2 - 19200
                                                        // 3 - 28800
                                                        // 4 - 38400
                                                        // 5 - 57600
                                                        // 6 - 115200
  int pare_bit_RS485;                                 //�������
                                                        // 0 - NONE
                                                        // 1 - ODD
                                                        // 2 - EVEN
  int number_stop_bit_RS485;                          //������� ����-��
                                                        // 0 - 1 stop-bit
                                                        // 1 - 2 stop-bits
  unsigned int time_out_1_RS485;                        //time-out ���������� ������� = X/10 �������
  
  int language;                                         //���� ����  0= ����� ��� �� �����������; 1=RU; 2=UA; 3=EN; 4=KZ; 5=��.
  
  unsigned int control_extra_settings_1;                //���� ��� ���������� �����������

  
  unsigned char time_setpoints[7+1];                     //��� ������� ��� �������-��������-���������
                                                         //������� ���� ������ �������� ���� ����� ���� ���� ��������
                                                            //0 - ������� ���������
                                                            //1 - ���������
                                                            //2 - USB
                                                            //3 - RS-485
  
  unsigned char time_ranguvannja[7+1];                    //��� ������� ��� ����������
                                                            //0 - ������� ���������
                                                            //1 - ���������
                                                            //2 - USB
                                                            //3 - RS-485
} __SETTINGS;

typedef struct
{
  //���� �����
  int state_execution;        //-1 - ������� ������� �� ������� ����� ����������
                              // 0 - ���������� ����
                              // 1 - ���� ���������� ��� �������
                              // 2 - ���� ���������� � ���������
  
  
  //������������� ��������, � ���� ������������
  int device_id;              //-1 - ������� �� ����������
                              // EEPROM_ADDRESS - EEPROM
                              // RTC_ADDRESS - RTC
  //��� ��������
  int action;                 //-1 - �� ����������
                              // 0 - ����� ������ ��� ���������� ����������
                              // 1 - ����������
                              // 2 - ����� ������ � ����� �����
  

  //�������� ������ �� ��� ���� ��� ���������
  unsigned int internal_address;

  //ʳ������ ���� ��� �������/������ (��������)
  unsigned int number_bytes;
  
  //�������� �� ����� (��������)
  uint8_t volatile* point_buffer;

} __DRIVER_I2C;

typedef struct
{
  unsigned int next_address;
  unsigned int saving_execution;
  unsigned int number_records;
} __INFO_REJESTRATOR;

typedef struct
{
  unsigned int state_execution;     //���� ���������� �������������
  
  unsigned int code_operation;      //��� ���������� ��������

} __DRIVER_SPI_DF;

typedef struct
{
  unsigned char label_start_record;
  unsigned char time[7]; 
  unsigned int T0;
  unsigned int TCurrent;
  unsigned int TVoltage;
  unsigned int control_extra_settings_1;
  unsigned char name_of_cell[MAX_CHAR_IN_NAME_OF_CELL];
} __HEADER_AR;

typedef enum __STATE_READING_ADCs {
STATE_READING_ADCs_NONE = 0,
STATE_READING_WRITE,
STATE_READING_WRITE_READ,
STATE_READING_READ
} STATE_READING_ADCs;

typedef enum _full_ort_index __full_ort_index;
typedef enum _index_energy __index_energy;

typedef struct
{
  uint32_t tick;
  unsigned int value;

} EXTENDED_OUTPUT_DATA;

typedef struct
{
  uint32_t tick;
  int value;
} EXTENDED_SAMPLE;

typedef struct
{
  unsigned int VAL_1_time_p;
  int VAL_1_data_p[NUMBER_ANALOG_CANALES_VAL_1 + NUMBER_ANALOG_CANALES_VAL_CONF];

  unsigned int VAL_1_time_c;
  int VAL_1_data_c[NUMBER_ANALOG_CANALES_VAL_1 + NUMBER_ANALOG_CANALES_VAL_CONF];

  unsigned int VAL_2_time_p;
  int VAL_2_data_p[NUMBER_ANALOG_CANALES_VAL_2 + NUMBER_ANALOG_CANALES_VAL_CONF];

  unsigned int VAL_2_time_c;
  int VAL_2_data_c[NUMBER_ANALOG_CANALES_VAL_2 + NUMBER_ANALOG_CANALES_VAL_CONF];
} ROZSHYRENA_VYBORKA;

typedef struct
{
  unsigned int time_stemp;
  unsigned int VAL_1_fix;
  unsigned int VAL_2_fix;
  int data [NUMBER_ANALOG_CANALES];
  unsigned int active_functions[N_BIG];
  int state_ar_record;
  
} DATA_FOR_OSCYLOGRAPH;


typedef struct 
{
  unsigned int x1;
  int y1;

  unsigned int x2;
  int y2;

} VYBORKA_XY;

typedef struct
{
  unsigned int Ua_x1;
  int Ua_y1;
  unsigned int Ua_x2;
  int Ua_y2;

  unsigned int Ub_x1;
  int Ub_y1;
  unsigned int Ub_x2;
  int Ub_y2;

  unsigned int Uc_x1;
  int Uc_y1;  
  unsigned int Uc_x2;
  int Uc_y2;  

  unsigned int U0_Ubc_TN2_x1;
  int U0_Ubc_TN2_y1;
  unsigned int U0_Ubc_TN2_x2;
  int U0_Ubc_TN2_y2;

  unsigned int Uab_TN2_x1;
  int Uab_TN2_y1;
  unsigned int Uab_TN2_x2;
  int Uab_TN2_y2;
  
} POPEREDNJY_PERECHID;

#endif
