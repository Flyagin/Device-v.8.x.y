#ifndef __GLOBAL_VARIABLES_H
#define __GLOBAL_VARIABLES_H

//����������� �������
volatile unsigned int semaphore_adc_irq = false;
volatile unsigned int adc_VAL_1_read = false;
volatile unsigned int adc_VAL_2_read = false;
volatile unsigned int adc_TEST_VAL_read = false;
volatile unsigned int status_adc_read_work = 0;
const unsigned int input_adc[NUMBER_INPUTs_ADCs][2]={
                                                     {1,0x8370},
                                                     {1,0x8770},
                                                     {1,0x8b70},
                                                     {1,0x8f70},
                                                     {1,0x9370},
                                                     {1,0x9770},
                                                     {1,0x9b70},
                                                     {1,0x9f70},
                                                     {1,0xa370},
                                                     {1,0xa770},
                                                     {1,0xab70},
                                                     {1,0xaf70},
                                                     {1,0xb370},
                                                     {1,0xb770},
                                                     {1,0xbb70},
                                                     {1,0xbf70},
                                                     {2,0x8370},
                                                     {2,0x8770},
                                                     {2,0x8b70},
                                                     {2,0x8f70},
                                                     {2,0x9370},
                                                     {2,0x9770},
                                                     {2,0x9b70},
                                                     {2,0x9f70},
                                                     {2,0xa370},
                                                     {2,0xa770},
                                                     {2,0xab70},
                                                     {2,0xaf70},
                                                     {2,0xb370},
                                                     {2,0xb770},
                                                     {2,0xbb70},
                                                     {2,0xbf70}
                                                    };
EXTENDED_OUTPUT_DATA output_adc[NUMBER_INPUTs_ADCs];
ROZSHYRENA_VYBORKA rozshyrena_vyborka;

unsigned int command_word_adc = 0, command_word_adc_work = 0, active_index_command_word_adc = 0;
unsigned int state_reading_ADCs = STATE_READING_ADCs_NONE;

uint32_t step_val_1 = TIM5_CCR1_2_3_VAL;
uint32_t step_val_2 = TIM5_CCR1_2_3_VAL;
uint32_t penultimate_tick_VAL_1 = 0, previous_tick_VAL_1 = 0;
uint32_t penultimate_tick_VAL_2 = 0, previous_tick_VAL_2 = 0;

DATA_FOR_OSCYLOGRAPH data_for_oscylograph[MAX_INDEX_DATA_FOR_OSCYLOGRAPH];
unsigned int head_data_for_oscylograph = 0;
unsigned int tail_data_for_oscylograph = 0, VAL_1_tail_data_for_oscylograph = 0, VAL_2_tail_data_for_oscylograph = 0;

VYBORKA_XY perechid_cherez_nul[MAX_INDEX_PhK][2];
unsigned int fix_perechid_cherez_nul[MAX_INDEX_PhK];
unsigned int fix_perechid_cherez_nul_TN1_TN2 = 0, fix_perechid_cherez_nul_TN1_TN2_work = 0;
POPEREDNJY_PERECHID poperednij_perechid;

volatile unsigned int semaphore_delta_phi = 0;

int delta_phi_index_1 = -1, delta_phi_index_2 = -1;
int delta_phi_index_1_work_middle = -1, delta_phi_index_2_work_middle = -1;
int delta_phi_index_1_work_low = -1, delta_phi_index_2_work_low = -1;
int delta_phi[2] = {UNDEF_PHI, UNDEF_PHI}, delta_phi_synchro = UNDEF_PHI, delta_phi_min, delta_phi_max; 
unsigned int bank_delta_phi = 0;
unsigned int reset_delta_phi = false;
int speed_delta_phi[2] = {UNDEF_SPEED_PHI, UNDEF_SPEED_PHI};
unsigned int tick_0[2];

int frequency_locking_phi = 0;
unsigned int frequency_locking_bank = 0;
float frequency_locking_cos[2] = {1.0f, 1.0f}, frequency_locking_sin[2] = {0.0f, 0.0f};

//unsigned int tick_val_1 = 0;
unsigned int maska_canaliv_fapch_1 = 0;
float frequency_val_1 = -1, frequency_val_1_work = -1;
unsigned int tick_period_1 = (TIM5_CCR1_2_3_VAL*NUMBER_POINT), tick_period_1_work = (TIM5_CCR1_2_3_VAL*NUMBER_POINT);
unsigned int tick_c1, tick_c1_work;

//unsigned int tick_val_2 = 0;
unsigned int maska_canaliv_fapch_2 = 0;
float frequency_val_2 = -1, frequency_val_2_work = -1;
unsigned int tick_period_2 = (TIM5_CCR1_2_3_VAL*NUMBER_POINT), tick_period_2_work = (TIM5_CCR1_2_3_VAL*NUMBER_POINT);
unsigned int tick_c2, tick_c2_work;

float frequency_val_1_min = 50, frequency_val_1_max = 50;
float frequency_val_2_min = 50, frequency_val_2_max = 50;
unsigned int command_restart_monitoring_frequency = 0;

const unsigned int index_GND_ADC1[NUMBER_GND_ADC1] = {C_GND_ADC1_1, C_GND_ADC1_2, C_GND_ADC1_3, C_GND_ADC1_4, C_GND_ADC1_5};
unsigned int gnd_adc1_moment_value[NUMBER_GND_ADC1][NUMBER_POINT];
unsigned int gnd_adc1_averange_sum[NUMBER_GND_ADC1];
unsigned int gnd_adc1_averange[NUMBER_GND_ADC1];
unsigned int gnd_adc1;

const unsigned int index_GND_ADC2[NUMBER_GND_ADC2] = {C_GND_ADC2_1, C_GND_ADC2_2, C_GND_ADC2_3};
unsigned int gnd_adc2_moment_value[NUMBER_GND_ADC2][NUMBER_POINT];
unsigned int gnd_adc2_averange_sum[NUMBER_GND_ADC2];
unsigned int gnd_adc2_averange[NUMBER_GND_ADC2];
unsigned int gnd_adc2;

unsigned int vref_adc1_moment_value[NUMBER_POINT];
unsigned int vref_adc1_averange_sum = VREF_NORMAL_VALUE*NUMBER_POINT;
unsigned int vref_adc1 = VREF_NORMAL_VALUE;

const unsigned int index_VREF_ADC2[NUMBER_GND_ADC2] = {C_VREF_ADC2_1, C_VREF_ADC2_2, C_VREF_ADC2_3};
unsigned int vref_adc2_moment_value[NUMBER_VREF_ADC2][NUMBER_POINT];
unsigned int vref_adc2_averange_sum[NUMBER_VREF_ADC2];
unsigned int vref_adc2_averange[NUMBER_VREF_ADC2];
unsigned int vref_adc2;

unsigned int vdd_adc1_moment_value[NUMBER_POINT];
unsigned int vdd_adc1_averange_sum = VDD_NORMAL_VALUE*NUMBER_POINT;
unsigned int vdd_adc1 = VDD_NORMAL_VALUE;

unsigned int vdd_adc2_moment_value[NUMBER_POINT];
unsigned int vdd_adc2_averange_sum = VDD_NORMAL_VALUE*NUMBER_POINT;
unsigned int vdd_adc2 = VDD_NORMAL_VALUE;

unsigned int index_array_of_one_value = 0;
unsigned int index_array_of_one_value_fourier = 0;

EXTENDED_SAMPLE ADCs_data_raw[NUMBER_ANALOG_CANALES];
int ADCs_data[NUMBER_ANALOG_CANALES];
int current_data[NUMBER_ANALOG_CANALES*NUMBER_POINT*NUMBER_PERIOD_TRANSMIT];
unsigned long long sqr_current_data_3I0[NUMBER_POINT];
unsigned int index_array_of_current_data_value = 0;

volatile unsigned int changed_ustuvannja = CHANGED_ETAP_NONE; 
unsigned char crc_ustuvannja;
unsigned int ustuvannja_meas[NUMBER_ANALOG_CANALES], ustuvannja[NUMBER_ANALOG_CANALES], edit_ustuvannja[NUMBER_ANALOG_CANALES];
int phi_ustuvannja_meas[NUMBER_ANALOG_CANALES], phi_ustuvannja[NUMBER_ANALOG_CANALES], phi_edit_ustuvannja[NUMBER_ANALOG_CANALES];
float phi_ustuvannja_sin_cos_meas[2*NUMBER_ANALOG_CANALES], phi_ustuvannja_sin_cos[2*NUMBER_ANALOG_CANALES], phi_edit_ustuvannja_sin_cos[2*NUMBER_ANALOG_CANALES];

const float sin_data_f[NUMBER_POINT] = {
                                         0.000000000000000000000000000000f,
                                         0.195090322016128000000000000000f,
                                         0.382683432365090000000000000000f,
                                         0.555570233019602000000000000000f,
                                         0.707106781186547000000000000000f,
                                         0.831469612302545000000000000000f,
                                         0.923879532511287000000000000000f,
                                         0.980785280403230000000000000000f,
                                         1.000000000000000000000000000000f,
                                         0.980785280403230000000000000000f,
                                         0.923879532511287000000000000000f,
                                         0.831469612302545000000000000000f,
                                         0.707106781186548000000000000000f,
                                         0.555570233019602000000000000000f,
                                         0.382683432365090000000000000000f,
                                         0.195090322016129000000000000000f,
                                         0.000000000000000122514845490862f,
                                        -0.195090322016128000000000000000f,
                                        -0.382683432365090000000000000000f,
                                        -0.555570233019602000000000000000f,
                                        -0.707106781186547000000000000000f,
                                        -0.831469612302545000000000000000f,
                                        -0.923879532511287000000000000000f,
                                        -0.980785280403230000000000000000f,
                                        -1.000000000000000000000000000000f,
                                        -0.980785280403230000000000000000f,
                                        -0.923879532511287000000000000000f,
                                        -0.831469612302545000000000000000f,
                                        -0.707106781186548000000000000000f,
                                        -0.555570233019602000000000000000f,
                                        -0.382683432365090000000000000000f,
                                        -0.195090322016129000000000000000f
};

const float cos_data_f[NUMBER_POINT] = {
                                         1.000000000000000000000000000000f,
                                         0.980785280403230000000000000000f,
                                         0.923879532511287000000000000000f,
                                         0.831469612302545000000000000000f,
                                         0.707106781186548000000000000000f,
                                         0.555570233019602000000000000000f,
                                         0.382683432365090000000000000000f,
                                         0.195090322016129000000000000000f,
                                         0.000000000000000122514845490862f,
                                        -0.195090322016128000000000000000f,
                                        -0.382683432365090000000000000000f,
                                        -0.555570233019602000000000000000f,
                                        -0.707106781186547000000000000000f,
                                        -0.831469612302545000000000000000f,
                                        -0.923879532511287000000000000000f,
                                        -0.980785280403230000000000000000f,
                                        -1.000000000000000000000000000000f,
                                        -0.980785280403230000000000000000f,
                                        -0.923879532511287000000000000000f,
                                        -0.831469612302545000000000000000f,
                                        -0.707106781186548000000000000000f,
                                        -0.555570233019602000000000000000f,
                                        -0.382683432365090000000000000000f,
                                        -0.195090322016129000000000000000f,
                                         0.000000000000000000000000000000f,
                                         0.195090322016128000000000000000f,
                                         0.382683432365090000000000000000f,
                                         0.555570233019602000000000000000f,
                                         0.707106781186547000000000000000f,
                                         0.831469612302545000000000000000f,
                                         0.923879532511287000000000000000f,
                                         0.980785280403230000000000000000f
};

unsigned int index_sin_cos_array[NUMBER_ADCs] = {0, 0};
unsigned int index_data_sin_cos_array[NUMBER_ADCs] = {0, 0};
int data_sin_val_1[NUMBER_POINT*(NUMBER_ANALOG_CANALES_VAL_1 + NUMBER_ANALOG_CANALES_VAL_CONF)];
int data_cos_val_1[NUMBER_POINT*(NUMBER_ANALOG_CANALES_VAL_1 + NUMBER_ANALOG_CANALES_VAL_CONF)];
int data_sin_val_2[NUMBER_POINT*(NUMBER_ANALOG_CANALES_VAL_2 + NUMBER_ANALOG_CANALES_VAL_CONF)];
int data_cos_val_2[NUMBER_POINT*(NUMBER_ANALOG_CANALES_VAL_2 + NUMBER_ANALOG_CANALES_VAL_CONF)];
unsigned int canal_3U0_Ubc_TN2_global = 0;
int ortogonal_irq[2*NUMBER_ANALOG_CANALES];
int ortogonal[2*NUMBER_ANALOG_CANALES][2];
unsigned int bank_ortogonal = 0;
unsigned long long sum_sqr_data_3I0_irq = 0;
unsigned long long sum_sqr_data_3I0[2] = {0, 0};
//volatile unsigned int semaphore_measure_values = 0;
volatile unsigned int semaphore_measure_values_low = 0;

volatile unsigned int semaphore_measure_values_low1 = 0;

unsigned int number_inputs_for_fix_one_second = 0;
unsigned int number_inputs_for_fix_one_period = 0;
volatile unsigned int measurement[NUMBER_ANALOG_CANALES + 8] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; 
unsigned int measurement_high[2][NUMBER_ANALOG_CANALES + 8] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}}, bank_measurement_high = 0; 
unsigned int measurement_middle[NUMBER_ANALOG_CANALES + 8] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; 
unsigned int measurement_low[NUMBER_ANALOG_CANALES + 8] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; 

const unsigned int index_converter_p[NUMBER_ANALOG_CANALES] = {FULL_ORT_3I0, FULL_ORT_Ia, FULL_ORT_Ic, FULL_ORT_Ua , FULL_ORT_Ub , FULL_ORT_Uc , FULL_ORT_3U0_Ubc_TN2, FULL_ORT_Uab_TN2};
const unsigned int index_converter_l[NUMBER_ANALOG_CANALES] = {FULL_ORT_3I0, FULL_ORT_Ia, FULL_ORT_Ic, FULL_ORT_Uab, FULL_ORT_Ubc, FULL_ORT_Uca, FULL_ORT_3U0_Ubc_TN2, FULL_ORT_Uab_TN2};
int ortogonal_calc[2*FULL_ORT_MAX];
int ortogonal_calc_low[2*FULL_ORT_MAX];
int phi_angle[FULL_ORT_MAX] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int base_index_for_angle = -1;

int P_plus[2] = {0, 0};
int P_minus[2] = {0, 0};
int Q_1q[2] = {0, 0};
int Q_2q[2] = {0, 0};
int Q_3q[2] = {0, 0};
int Q_4q[2] = {0, 0};
unsigned int lichylnyk_1s_po_20ms = 0;
volatile unsigned int bank_for_enegry = 0;
int P = 0, Q = 0, cos_phi_x1000 = 0;
unsigned int S = 0;
double energy[MAX_NUMBER_INDEXES_ENERGY] = {0, 0, 0, 0, 0, 0};
unsigned int clean_energy = 0;
unsigned int information_about_clean_energy = 0;

int resistance[MAX_NUMBER_INDEXES_RESISTANCE] = {0, 0, 0, 0, 0, 0}; //������{ Rab, Zab, Rbc, Zbc, Rca, Xca}
int resistance_middle[MAX_NUMBER_INDEXES_RESISTANCE] = {0, 0, 0, 0, 0, 0};
int resistance_low[MAX_NUMBER_INDEXES_RESISTANCE] = {0, 0, 0, 0, 0, 0};

//���������� ���
int sector_1_mtz[8];
int sector_2_mtz[8];
unsigned int sector_directional_mtz[4][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
unsigned int Uxy_bilshe_porogu[3] = {0, 0, 0};
unsigned int Ix_bilshe_porogu[3] = {0, 0, 0};
unsigned int temp_states_for_mtz = 0;

//���
int sector_1[8];
int sector_2[8];
volatile unsigned int sector_i_minus_u_1 = 0;
volatile unsigned int sector_i_minus_u_2 = 0;
unsigned int po_3I0     = 0; /*0 - ���������� � �������� �����������, ������ �� ���� - ���������� � �������� ����������*/
unsigned int po_3U0     = 0; /*0 - ���������� � �������� �����������, ������ �� ���� - ���������� � �������� ����������*/
unsigned int sector_NZZ = 0; /*0 - ���������� � �������� �����������, ������ �� ���� - ���������� � �������� ����������*/
/*
0  - ��� ������ ������� 3I0 � 3U0 � "���" ������
1  - ��� ������ ������� 3I0 � 3U0 � 1-��� ��������
2  - ��� ������ ������� 3I0 � 3U0 � 2-��� ��������
3  - ��� ������ ������� 3I0 � 3U0 � 3-��� ��������
4  - ��� ������ ������� 3I0 � 3U0 � 4-��� ��������
*/
unsigned int Nzz_3U0_bilshe_porogu = 0, Nzz_3I0_bilshe_porogu = 0;

unsigned int i1_bilshe_porogu = 0, i2_bilshe_porogu = 0;

volatile unsigned int state_inputs = 0; //"� ������ " - ������� ������������� ��� (1); "���� �������" - ������� ��������� ��� (0)
volatile unsigned int active_inputs = 0; //"���� ��������" - ������� ������������� ��� (1); "���� ��������" - ������� ��������� ��� (0)
volatile unsigned int state_outputs = 0;
volatile unsigned int state_signal_outputs = 0;
volatile unsigned int state_leds = 0;
volatile unsigned int state_trigger_leds = 0;
volatile unsigned int active_functions[N_BIG]  = {0, 0, 0, 0, 0, 0};
const unsigned int maska_trg_func_array[N_BIG] = {MASKA_TRIGGER_SIGNALES_0, MASKA_TRIGGER_SIGNALES_1, MASKA_TRIGGER_SIGNALES_2, MASKA_TRIGGER_SIGNALES_3, MASKA_TRIGGER_SIGNALES_4, MASKA_TRIGGER_SIGNALES_5};
unsigned int misceve_dystancijne = 0, misceve_dystancijne_ctrl;
unsigned int trigger_active_functions[N_BIG]  = {0, 0, 0, 0, 0, 0}, trigger_active_functions_ctrl[N_BIG];
unsigned char crc_trg_func, crc_trg_func_ctrl;
volatile unsigned int trigger_functions_USB[N_BIG] = {0, 0, 0, 0, 0, 0};
volatile unsigned int trigger_functions_RS485[N_BIG] = {0, 0, 0, 0, 0, 0};
volatile unsigned int previous_activated_functions[N_BIG] = {0, 0, 0, 0, 0, 0}; //�����, � ����� ��������� �������� �������, �� ��������������� ��������+������� � ���� �������� ������� ������� ����� ���� ���������
unsigned int copying_active_functions = 0;
volatile unsigned int active_functions_copy[N_BIG]  = {0, 0, 0, 0, 0, 0};
volatile unsigned int active_functions_trg[N_BIG]  = {0, 0, 0, 0, 0, 0};
unsigned int pressed_buttons = 0;
volatile unsigned int activation_function_from_interface = 0;
volatile unsigned int reset_trigger_function_from_interface = 0;
unsigned int diagnostyka_before[3] = {0, 0, 0};
volatile unsigned int diagnostyka[3] = {0, 0, 0};
volatile unsigned int set_diagnostyka[3] = {0, 0, 0};
volatile unsigned int clear_diagnostyka[3] = {0, 0, 0};

int global_timers[MAX_NUMBER_GLOBAL_TIMERS]; //����� ���������� �������
unsigned int etap_execution_df[NUMBER_DEFINED_FUNCTIONS]; //���� ��������� ����������� �������
unsigned int state_df = 0; //������� ���� ������������ �������

unsigned int previous_states_APV_0 = 0;
unsigned int trigger_APV_0 = 0;

_Bool previous_states_APV_ZMN_0 = 0;
_Bool previous_states_APV_ZMN_1 = 0;
_Bool previous_states_APV_ZMN_2 = 0;
_Bool previous_states_APV_ZMN_srab = 0;
_Bool trigger_APV_ZMN_0 = 0;
_Bool trigger_APV_ZMN_1 = 0;
_Bool trigger_APV_ZMN_2 = 0;
_Bool previous_state_apv_zmn_counter = 0;
unsigned int apv_zmn_counter = 0;

_Bool previous_states_AVR_0 = 0;
_Bool previous_states_AVR_1 = 0;
_Bool trigger_AVR_0 = 0;
_Bool trigger_AVR_1 = 0;
_Bool previous_state_avr_counter = 0;
unsigned int avr_counter = 0;

_Bool previous_state_po_achr_chapv_uaf1 = 0;
_Bool previous_state_po_achr_chapv_ubf1 = 0;
_Bool previous_state_po_achr_chapv_ucf1 = 0;
_Bool previous_state_po_achr_chapv_uaf2_uab2_ubc2 = 0;
_Bool previous_states_CHAPV1 = 0;
_Bool previous_states_CHAPV2 = 0;
_Bool trigger_CHAPV1 = 0;
_Bool trigger_CHAPV2 = 0;

_Bool previous_states_ready_tu = 0;
_Bool trigger_ready_tu = 0;

_Bool trigger_u_ol = 0;
_Bool trigger_u_rl = 0;

unsigned int start_restart = 0xff;

unsigned char working_ekran[MAX_ROW_LCD][MAX_COL_LCD];
unsigned int rewrite_ekran_once_more = 0;

volatile unsigned int new_state_keyboard = 0;
unsigned int new_state_keyboard_for_db = 0;
unsigned char time_set_keyboard[NUMBER_KEY_KEYBOARD];

unsigned int time_rewrite = 0; //��� ���� ������� ���� ���������� ����������

__CURRENT_EKRAN current_ekran;
int position_in_current_level_menu[MAX_LEVEL_MENU]; //����� � ����� ���������� ������ �������������
int previous_level_in_current_level_menu[MAX_LEVEL_MENU]; //����� � ����� ���������� �������� ��������� ������ ��� ������ ���� ����

volatile unsigned int periodical_tasks_TEST_SETTINGS = false;
volatile unsigned int periodical_tasks_TEST_USTUVANNJA = false;
volatile unsigned int periodical_tasks_TEST_TRG_FUNC = false;
volatile unsigned int periodical_tasks_TEST_TRG_FUNC_LOCK = false;
volatile unsigned int periodical_tasks_TEST_INFO_REJESTRATOR_AR = false;
volatile unsigned int periodical_tasks_TEST_INFO_REJESTRATOR_AR_LOCK = false;
volatile unsigned int periodical_tasks_TEST_INFO_REJESTRATOR_DR = false;
volatile unsigned int periodical_tasks_TEST_INFO_REJESTRATOR_DR_LOCK = false;
volatile unsigned int periodical_tasks_TEST_INFO_REJESTRATOR_PR_ERR = false;
volatile unsigned int periodical_tasks_TEST_INFO_REJESTRATOR_PR_ERR_LOCK = false;
volatile unsigned int periodical_tasks_TEST_RESURS = false;
volatile unsigned int periodical_tasks_TEST_RESURS_LOCK = false;
volatile unsigned int periodical_tasks_TEST_FLASH_MEMORY = false;
volatile unsigned int periodical_tasks_CALCULATION_ANGLE = false;
volatile unsigned int periodical_tasks_CALC_ENERGY_DATA = false;
volatile unsigned int periodical_tasks_CALC_DELTA_PHI = false;

const unsigned char odynyci_vymirjuvannja[MAX_NAMBER_LANGUAGE][NUMBER_ODYNYCI_VYMIRJUVANNJA] =
{
  {'�', '�', '�'},
  {'�', '�', '�'},
  {'A', 'V', 's'},
  {'�', '�', '�'}
};

unsigned int fixed_power_down_into_RTC = 0; 
unsigned char time[7]; 
unsigned char time_copy[7]; 
unsigned char calibration;
unsigned char calibration_copy;
unsigned int copying_time = 0;
unsigned char time_edit[7]; 
unsigned char calibration_edit;
unsigned int copy_register8_RTC;
int etap_reset_of_bit = ETAP_CLEAR_OF_NONE;
int etap_settings_test_frequency = -1;
unsigned char temp_register_rtc[2];

volatile unsigned int changed_settings = CHANGED_ETAP_NONE; 
unsigned char crc_settings;
__SETTINGS current_settings_prt, current_settings, edition_settings;
unsigned int mtz_settings_prt[NUMBER_LEVEL_MTZ][MTZ_SETTINGS_LENGTH];
unsigned int mtz_tmr_const[NUMBER_LEVEL_MTZ][NUMBER_LEVEL_TMR_CONST];
int * type_mtz_arr[NUMBER_LEVEL_MTZ];
unsigned int mtz_const_menu_settings_prt[NUMBER_LEVEL_MTZ][MTZ_CONST_MENU_SETTINGS_LENGTH];
unsigned int i_nom_const;
unsigned int u_linear_nom_const;
unsigned int * setpoint_mtz[NUMBER_LEVEL_MTZ];
unsigned int * setpoint_mtz_n_vpered[NUMBER_LEVEL_MTZ];
unsigned int * setpoint_mtz_n_nazad[NUMBER_LEVEL_MTZ];
unsigned int * setpoint_mtz_U[NUMBER_LEVEL_MTZ];
unsigned int * setpoint_mtz_po_napruzi[NUMBER_LEVEL_MTZ];
int * timeout_mtz[NUMBER_LEVEL_MTZ];
int * timeout_mtz_n_vpered[NUMBER_LEVEL_MTZ];
int * timeout_mtz_n_nazad[NUMBER_LEVEL_MTZ];
int * timeout_mtz_po_napruzi[NUMBER_LEVEL_MTZ];
_Bool previous_state_mtz_po_incn = 0;
_Bool previous_state_mtz_po_uncn = 0;
unsigned int p_global_trigger_state_mtz2 = 0;

//���������� ������ � ������� � �����
unsigned int number_seconds = 0;
volatile unsigned int number_minutes = 0;

//������++
volatile unsigned int restart_resurs_count = 0;
unsigned int resurs_temp = 0;
unsigned int resurs_global = 0;
unsigned int resurs_global_min;
unsigned int resurs_global_max = 0;

unsigned int restart_timing_watchdog = 0;
unsigned int time_1_watchdog_input = 0;
unsigned int time_2_watchdog_input = 0;
unsigned int time_delta_watchdog_input = 0;
unsigned int time_delta_watchdog_input_min = 0xffff*10;
unsigned int time_delta_watchdog_input_max = 0;

unsigned int time_1_watchdog_output = 0;
unsigned int time_2_watchdog_output = 0;
unsigned int time_delta_watchdog_output = 0;
unsigned int time_delta_watchdog_output_min = 0xffff*10;
unsigned int time_delta_watchdog_output_max = 0;


//I2C
unsigned char Temporaty_I2C_Buffer[SIZE_PAGE_EEPROM + 2];
unsigned int number_busy_state = 0;
unsigned int type_error_of_exchanging_via_i2c = 0;
unsigned int low_speed_i2c = 0;
__DRIVER_I2C driver_i2c;
unsigned int control_i2c_taskes[2]  = {0,0};
unsigned int comparison_writing = 0; /*�������� �� ������, �� ��� ���������� � ������� ��'���, ������������ �� ������ �� ��� ��������� �������� ���������� ���� �������� ������*/
unsigned int state_i2c_task = STATE_FIRST_READING_RTC;
unsigned char read_write_i2c_buffer[SIZE_BUFFER_FOR_EEPROM_EXCHNGE];

//DataFlash
unsigned char RxBuffer_SPI_DF[SIZE_PAGE_DATAFLASH_MAX + 10];
unsigned char TxBuffer_SPI_DF[SIZE_PAGE_DATAFLASH_MAX + 10];
unsigned int number_bytes_transfer_spi_df;
unsigned int number_bytes_transfer_spi_df_copy;
unsigned char TxBuffer_SPI_DF_copy[SIZE_PAGE_DATAFLASH_MAX + 10];
unsigned int code_operation_copy;
int number_chip_dataflsh_exchange = -1;
__DRIVER_SPI_DF driver_spi_df[NUMBER_DATAFLASH_CHIP] = {
                                                        {TRANSACTION_EXECUTING_NONE, CODE_OPERATION_NONE},
                                                        {TRANSACTION_EXECUTING_NONE, CODE_OPERATION_NONE}
                                                       };
volatile unsigned int error_into_spi_df = 0;/*�������� �������� ������, �� ����������� ������� ��� ������/�������� ����� SPI_DF*/
unsigned int dataflash_not_busy = 0;
volatile unsigned int control_tasks_dataflash = 0;
unsigned char buffer_for_manu_read_record[SIZE_BUFFER_FOR_DR_RECORD];
unsigned char buffer_for_USB_read_record_ar[SIZE_PAGE_DATAFLASH_2];
unsigned char buffer_for_RS485_read_record_ar[SIZE_PAGE_DATAFLASH_2];
unsigned char buffer_for_USB_read_record_dr[SIZE_BUFFER_FOR_DR_RECORD];
unsigned char buffer_for_RS485_read_record_dr[SIZE_BUFFER_FOR_DR_RECORD];
unsigned char buffer_for_USB_read_record_pr_err[SIZE_ONE_RECORD_PR_ERR];
unsigned char buffer_for_RS485_read_record_pr_err[SIZE_ONE_RECORD_PR_ERR];

unsigned int what_we_are_reading_from_dataflash_1;
unsigned int what_we_are_reading_from_dataflash_2;

//���������� ���������
unsigned char crc_info_rejestrator_ar;
volatile __INFO_REJESTRATOR info_rejestrator_ar;
unsigned char crc_info_rejestrator_ar_ctrl;
__INFO_REJESTRATOR info_rejestrator_ar_ctrl;
volatile unsigned int size_one_ar_record = 0;
unsigned int number_word_digital_part_ar;
volatile unsigned int max_number_records_ar = 0; //����������� ������� ������ � ����������� ��������� ��� �������� ��������� (������������� � �������� ����������� � ������������� ����)
volatile unsigned int semaphore_read_state_ar_record = 0; //���� ��� ������� ������������, �� ���� �� ��� �����, �� ����� ����� �� ����� ��������, � ���� ���, �� ����� ������������ �����
unsigned int continue_previous_record_ar = 0; //��������, �� ���� ��� �� ������� ������� ����������� ���������� ���� ���� ����6�������� �������
volatile int state_ar_record = STATE_AR_NO_RECORD;
SRAM1 short int array_ar[SIZE_BUFFER_FOR_AR];
SRAM1 short int word_SRAM1;
unsigned int index_array_ar_current = 0;
volatile unsigned int index_array_ar_heat;
volatile unsigned int index_array_ar_tail;
unsigned int prescaler_ar = 0; //�������� ��� ����, ��� � 32 ������� �� ������� ������� 16 ������� �� �������
__HEADER_AR header_ar;
unsigned char buffer_for_save_ar_record[SIZE_PAGE_DATAFLASH_2];
unsigned int temporary_address_ar;
volatile unsigned int count_to_save;
volatile unsigned int permit_copy_new_data;
unsigned int copied_number_samples, total_number_samples;
unsigned int etap_writing_part_page_ar_into_dataflash = ETAP_NONE;
unsigned int number_record_of_ar_for_menu = 0xffff; //�� ����� ������, �� ����� ������ �� ��������
unsigned int number_record_of_ar_for_USB = 0xffff; //�� ����� ������, �� ����� ������ �� ��������
unsigned int number_record_of_ar_for_RS485 = 0xffff; //�� ����� ������, �� ����� ������ �� ��������
int first_number_time_sample_for_USB;// -1 - ��������� ������ ��.�.; 0 - ������ ������� ��� ����������� ������ � �.�.
int last_number_time_sample_for_USB;// -1 - ��������� ������ ��.�.; 0 - ������ ������� ��� ����������� ������ � �.�.
int first_number_time_sample_for_RS485;// -1 - ��������� ������ ��.�.; 0 - ������ ������� ��� ����������� ������ � �.�.
int last_number_time_sample_for_RS485;// -1 - ��������� ������ ��.�.; 0 - ������ ������� ��� ����������� ������ � �.�.

//���������� ���������
unsigned char crc_info_rejestrator_dr;
volatile __INFO_REJESTRATOR info_rejestrator_dr;
unsigned char crc_info_rejestrator_dr_ctrl;
__INFO_REJESTRATOR info_rejestrator_dr_ctrl;
unsigned int state_dr_record = STATE_DR_NO_RECORD;
unsigned int number_records_dr_waiting_for_saving_operation = 0;
unsigned char buffer_for_save_dr_record[SIZE_BUFFER_FOR_DR_RECORD];
unsigned char buffer_for_save_dr_record_level_1[SIZE_BUFFER_FOR_DR_RECORD];
unsigned char buffer_for_save_dr_record_level_2[SIZE_BUFFER_FOR_DR_RECORD];
unsigned int part_writing_dr_into_dataflash;
unsigned int number_record_of_dr_for_menu = 0xffff; //�� ����� ������, �� ����� ������ �� ��������
unsigned int number_record_of_dr_for_USB = 0xffff; //�� ����� ������, �� ����� ������ �� ��������
unsigned int number_record_of_dr_for_RS485 = 0xffff; //�� ����� ������, �� ����� ������ �� ��������
unsigned int part_reading_dr_from_dataflash_for_menu = 0;
unsigned int part_reading_dr_from_dataflash_for_USB = 0;
unsigned int part_reading_dr_from_dataflash_for_RS485 = 0;
unsigned int state_current_monitoring;
unsigned int measurements_phase_max_dr[SIZE_ARRAY_FIX_MAX_MEASUREMENTS];        //������� + ����������� �������� + �������� ���� unsigned int (���������� ���� - �� ���� ���� �������, � ����� ���� - �� ���� ����)
unsigned int measurements_3I0_max_dr[SIZE_ARRAY_FIX_MAX_MEASUREMENTS];          //������� + ����������� �������� + �������� ���� unsigned int (���������� ���� - �� ���� ���� �������, � ����� ���� - �� ���� ����)
unsigned int measurements_3U0_max_dr[SIZE_ARRAY_FIX_MAX_MEASUREMENTS];          //������� + ����������� �������� + �������� ���� unsigned int (���������� ���� - �� ���� ���� �������, � ����� ���� - �� ���� ����)
unsigned int measurements_U_min_dr[SIZE_ARRAY_FIX_MAX_MEASUREMENTS];            //������� + ����������� �������� + �������� ���� unsigned int (���������� ���� - �� ���� ���� �������, � ����� ���� - �� ���� ����)
unsigned int measurements_U_max_dr[SIZE_ARRAY_FIX_MAX_MEASUREMENTS];            //������� + ����������� �������� + �������� ���� unsigned int (���������� ���� - �� ���� ���� �������, � ����� ���� - �� ���� ����)
unsigned int measurements_ZOP_max_dr[SIZE_ARRAY_FIX_MAX_MEASUREMENTS];          //������� + ����������� �������� + �������� ���� unsigned int (���������� ���� - �� ���� ���� �������, � ����� ���� - �� ���� ����)
unsigned int measurements_f1_min_achr_dr[SIZE_ARRAY_FIX_MAX_MEASUREMENTS];      //������� + ����������� �������� + �������� ���� unsigned int (���������� ���� - �� ���� ���� �������, � ����� ���� - �� ���� ����)
unsigned int measurements_f2_min_achr_dr[SIZE_ARRAY_FIX_MAX_MEASUREMENTS];      //������� + ����������� �������� + �������� ���� unsigned int (���������� ���� - �� ���� ���� �������, � ����� ���� - �� ���� ����)
unsigned int measurements_f1_chapv_dr[SIZE_ARRAY_FIX_MAX_MEASUREMENTS];         //������� + ����������� �������� + �������� ���� unsigned int (���������� ���� - �� ���� ���� �������, � ����� ���� - �� ���� ����)
unsigned int measurements_f2_chapv_dr[SIZE_ARRAY_FIX_MAX_MEASUREMENTS];         //������� + ����������� �������� + �������� ���� unsigned int (���������� ���� - �� ���� ���� �������, � ����� ���� - �� ���� ����)
unsigned int max_phase_current_dr;   //������������ ������ �����
unsigned int min_voltage_dr;  //��������� �����/����� �������
unsigned int max_voltage_dr;  //����������� �����/����� �������
unsigned int number_max_phase_dr;
unsigned int number_max_3I0_dr;
unsigned int number_max_3U0_dr;
unsigned int number_min_U_dr;
unsigned int number_max_U_dr;
unsigned int number_max_ZOP_dr;
unsigned int number_min_f1_achr_dr, number_min_f2_achr_dr;
unsigned int number_f1_chapv_dr, number_f2_chapv_dr;
unsigned int type_view_max_values_dr;
int index_cell_into_array_for_min_max_measurement_dr;
unsigned int control_extra_settings_1_dr_for_manu;

//��������� ���������� �������
unsigned char crc_info_rejestrator_pr_err;
volatile __INFO_REJESTRATOR info_rejestrator_pr_err;
unsigned char crc_info_rejestrator_pr_err_ctrl;
__INFO_REJESTRATOR info_rejestrator_pr_err_ctrl;
unsigned char buffer_pr_err_records[SIZE_BUFFER_FOR_PR_ERR];
volatile unsigned int head_fifo_buffer_pr_err_records = 0;
volatile unsigned int tail_fifo_buffer_pr_err_records = 0;
volatile unsigned int temporary_block_writing_records_pr_err_into_DataFlash = 0;
unsigned int etap_writing_pr_err_into_dataflash = ETAP_NONE;
unsigned int number_recods_writing_into_dataflash_now = 0;
unsigned int number_record_of_pr_err_into_menu = 0xffff;
unsigned int number_record_of_pr_err_into_USB = 0xffff;
unsigned int number_record_of_pr_err_into_RS485 = 0xffff;

//������� ���������� �� �����������
volatile unsigned int clean_rejestrators = 0;

//˳������� �������
unsigned int koef_resurs_changed = CHANGED_ETAP_NONE;
float K_resurs_prt, K_resurs;
unsigned int resurs_vymykacha = 0, resurs_vymykacha_ctrl;
unsigned int resurs_vidkljuchennja = 0, resurs_vidkljuchennja_ctrl;
unsigned char crc_resurs, crc_resurs_ctrl;
unsigned int restart_counter = 0;

//���������� ���� �� �����������
unsigned int vymknennja_vid_KZ_prt = 0;
unsigned int I_max_KZ_prt = 0;
unsigned int number_of_phases_KZ_prt = 0;
unsigned int X_min_KZ_prt = (unsigned int)UNDEF_RESISTANCE;
int R_KZ_prt = 0;

unsigned int number_of_phases_last_KZ = 0;
int VMP_last_KZ = UNDEF_VMP;
int unsigned equal_more_KZ = 0;


//RS-485
unsigned char TxBuffer_RS485[BUFFER_RS485];
unsigned char RxBuffer_RS485[BUFFER_RS485];
int TxBuffer_RS485_count = 0;
int volatile RxBuffer_RS485_count = 0;
int RxBuffer_RS485_count_previous = 0;
unsigned int time_last_receive_byte;
unsigned int max_reaction_time_rs_485 = 0;
unsigned int make_reconfiguration_RS_485 = 0;
volatile unsigned int number_bits_rs_485_waiting = 0;
unsigned int mark_current_tick_RS_485 = 0;
unsigned int timeout_idle_RS485;

//USB
uint8_t  USART_Rx_Buffer[USART_RX_DATA_SIZE]; 
uint32_t USART_Rx_ptr_in = 0;
uint32_t USART_Rx_ptr_out = 0;
uint32_t USART_Rx_length  = 0;

extern uint8_t  USB_Tx_State;

//��� UDP
u32 volatile count_out = 0;
u32 count_out_previous = 0;
uint16_t previous_count_tim4_USB;
u8 buffer_out[BUFFER_USB];
unsigned char usb_received[BUFFER_USB];
unsigned char usb_transmiting[BUFFER_USB];
int usb_received_count = 0;
int usb_transmiting_count = 0;
unsigned char data_usb_transmiting = false;
unsigned int timeout_idle_USB;

//MODBUS-RTU
unsigned int registers_address_read =0x20000000;
unsigned int registers_address_write =0x20000000;
unsigned int data_write_to_memory;
unsigned int number_registers_read = 0;
unsigned short int registers_values[64]/* @ "variables_RAM1"*/;
unsigned int action_is_continued = false;
unsigned int part_transmit_carrent_data = 0;
unsigned int command_to_receive_current_data = false;
int current_data_transmit[NUMBER_ANALOG_CANALES*NUMBER_POINT*NUMBER_PERIOD_TRANSMIT] /*@ "variables_RAM1"*/; 
volatile unsigned int wait_of_receiving_current_data  = false; 
unsigned int password_set_USB = 1, password_set_RS485 = 1;
unsigned int previous_password_interface;
unsigned int password_ustuvannja = 0;
unsigned int information_about_settings_changed = 0;
unsigned int information_about_restart_counter = 0;
unsigned int *point_to_edited_rang = NULL;
unsigned int number_32bit_in_target = 0;
unsigned int clear_array_rang[N_BIG] = {0, 0, 0, 0, 0, 0};
unsigned int set_array_rang[N_BIG]   = {0, 0, 0, 0, 0, 0};
unsigned int restart_timeout_interface = 0;

unsigned int serial_number_dev = 0;                         //���������� ����� ��������
unsigned int edit_serial_number_dev;

//��� ����������� ���������� ��� ������� ����������
unsigned int info_vidkluchennja_vymykacha = 0;
unsigned char info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_MAX_NUMBER][7]; 

volatile unsigned int control_word_of_watchdog = 0;
unsigned int test_watchdogs = 0;

/**************************************************************
 * ����� ��������������� � ������� ������ ����� �������:
 * protections.c --> setpoints_selecting()
 **************************************************************/
unsigned int gr_ustavok_tmp = 0xf;

//����� ��������� �������
unsigned int total_error;

const unsigned char letters[69][2] =
{
{ 176, 223 },  //�
{ 178, 73  }, // �
{ 179, 105 }, // �
{ 192, 65  }, // �
{ 193, 160 }, // �
{ 194, 66  }, // �
{ 195, 161 }, // �
{ 196, 224 }, // �
{ 197, 69  }, // �
{ 168, 162 }, // �
{ 198, 163 }, // �
{ 199, 164 }, // �
{ 200, 165 }, // �
{ 201, 166 }, // �
{ 202, 75  }, // �
{ 203, 167 }, // �
{ 204, 77  }, // �
{ 205, 72  }, // �
{ 206, 79  }, // �
{ 207, 168 }, // �
{ 208, 80  }, // �
{ 209, 67  }, // �
{ 210, 84  }, // �
{ 211, 169 }, // �
{ 212, 170 }, // �
{ 213, 88  }, // �
{ 214, 225 }, // �
{ 215, 171 }, // �
{ 216, 172 }, // �
{ 217, 226 }, // �
{ 218, 173 }, // �
{ 220, 98  }, // �
{ 219, 174 }, // �
{ 221, 175 }, // �
{ 222, 176 }, // �
{ 223, 177 }, // �
{ 224, 97  }, // �
{ 225, 178 }, // �
{ 226, 179 }, // �
{ 227, 180 }, // �
{ 228, 227 }, // �
{ 229, 101 }, // �
{ 184, 181 }, // �
{ 230, 182 }, // �
{ 231, 183 }, // �
{ 232, 184 }, // �
{ 233, 185 }, // �
{ 234, 186 }, // �
{ 235, 187 }, // �
{ 236, 188 }, // �
{ 237, 189 }, // �
{ 238, 111 }, // �
{ 239, 190 }, // �
{ 240, 112 }, // �
{ 241, 99  }, // �
{ 242, 191 }, // �
{ 243, 121 }, // �
{ 244, 228 }, // �
{ 245, 120 }, // �
{ 246, 229 }, // �
{ 247, 192 }, // �
{ 248, 193 }, // �
{ 249, 230 }, // �
{ 250, 194 }, // �
{ 252, 196 }, // �
{ 251, 195 }, // �
{ 253, 197 }, // �
{ 254, 198 }, // �
{ 255, 199 } // �
};

const unsigned char extra_letters[12][1 + MAX_NAMBER_LANGUAGE] =
{
/*CODE   RU    UA    EN    KZ     */  
{ 0xAF, 0xFF, 0x00, 0x00, 0xFF}, // � ��� ������ ���� ����� ��� ��������� ��������� ���������
{ 0xBF, 0xFF, 0x01, 0xFF, 0xFF}, // �
{ 0xA5, 0xFF, 0x02, 0xFF, 0xFF}, // �
{ 0xB4, 0xFF, 0x03, 0xFF, 0xFF}, // �
{ 0xAA, 0xFF, 0x04, 0xFF, 0xFF}, // �
{ 0xBA, 0xFF, 0x05, 0xFF, 0xFF}, // �
{ 0x8A, 0xFF, 0xFF, 0xFF, 0x00}, // � - ������� ������ � ����� ����� ��� WIN1251
{ 0x9A, 0xFF, 0xFF, 0xFF, 0x01}, // � - ������� ������ � ����� ����� ��� WIN1251
{ 0xBD, 0xFF, 0xFF, 0xFF, 0x02}, // � - ������� ������ � ����� ����� ��� WIN1251
{ 0xBE, 0xFF, 0xFF, 0xFF, 0x03}, // � - ������� ������ � ����� ����� ��� WIN1251
{ 0x80, 0xFF, 0xFF, 0xFF, 0x04}, // � - ������� ������ � ����� ����� ��� WIN1251
{ 0x90, 0xFF, 0xFF, 0xFF, 0x05}  // � - ������� ������ � ����� ����� ��� WIN1251
};

int current_language = LANGUAGE_ABSENT;

extern unsigned short const __checksum;
extern unsigned int __checksum_begin;
extern unsigned int __checksum_end;

extern unsigned int __ICFEDIT_region_RAM1_start__;
extern unsigned int __ICFEDIT_region_RAM1_size__;

#ifdef DEBUG_TEST
//unsigned int time_1 = 0xffff0000, time_2 = 0xffff0000, max_delay = 0;

//�������� ����
//unsigned int temp_value_for_debbuging_1 = 0;
//unsigned int temp_value_for_debbuging_2 = 0;
//unsigned int temp_value_for_debbuging_3 = 0;

unsigned int temp_value_3I0_1 = 0;
unsigned int temp_value_3I0_other = 0;
unsigned int temp_value_IA = 0;
unsigned int temp_value_IC = 0;
unsigned int temp_value_UA = 0;
unsigned int temp_value_UB = 0;
unsigned int temp_value_UC = 0;
unsigned int temp_value_3U0_UBC_TN2 = 0;
unsigned int temp_value_UAB_TN2 = 0;
unsigned int temp_value_I2 = 0;
unsigned int temp_value_I1 = 0;

#endif


#endif
