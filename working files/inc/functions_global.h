#ifndef __GLOBAL_FUNCTIONS_H
#define __GLOBAL_FUNCTIONS_H

#include "stm32f2xx_it.h"

#ifdef USB_OTG_HS_INTERNAL_DMA_ENABLED
  #if defined ( __ICCARM__ ) /*!< IAR Compiler */
    #pragma data_alignment=4   
  #endif
#endif /* USB_OTG_HS_INTERNAL_DMA_ENABLED */
   
__ALIGN_BEGIN USB_OTG_CORE_HANDLE    USB_OTG_dev __ALIGN_END ;

void Configure_I2C(I2C_TypeDef*);
void FSMC_SRAM_Init(void);

int main(void);
void periodical_operations(void);
void global_vareiables_installation(void);
void start_settings_peripherals(void);
void start_tim4_canal2_for_interrupt_1mc(void);
void start_tim4_canal3_for_interrupt_10mkc(void);
void min_settings(__SETTINGS *);
void error_reading_with_eeprom(void);

void Interrupts_Config(void);

void lcd_init(void);
unsigned int wait_lcd_ready(void);
unsigned int clear_lcd(void);
unsigned int mode_viewing(unsigned int, unsigned int, unsigned int);
unsigned int hd44780_puts(unsigned char *, unsigned int);
unsigned int Win1251toHd44780 (unsigned int);
unsigned int write_data_to_lcd(unsigned char);
unsigned int write_command_to_lcd(unsigned char);
unsigned int hd44780_gotoxy(unsigned char, unsigned char);
unsigned int hd44780_puts_xy (unsigned char, unsigned char, unsigned char *);
void view_whole_ekran(void);
void check_state_key(GPIO_TypeDef*, uint16_t, unsigned int);
int index_language_in_array(int);

void inc_or_dec_value(unsigned int *, unsigned int);
unsigned int bcd_to_int(unsigned char);

void make_ekran_level_password(unsigned int password, unsigned int view);
void main_manu_function(void);
void make_ekran_main(void);
void make_ekran_time(void);
void edit_time(unsigned int);
void make_ekran_ask_rewrite(void);
unsigned int check_data_for_data_time_menu(void);
void make_ekran_about_error(const unsigned char [][MAX_COL_LCD]);
void make_ekran_about_activation_command(unsigned int, unsigned char [][MAX_NAMBER_LANGUAGE][MAX_COL_LCD]);
void make_ekran_configuration(unsigned int);
void make_ekran_measurement(void);
void make_ekran_measurement_voltage_type(void);
void make_ekran_current(unsigned int);
void make_ekran_voltage_phase(unsigned int);
void make_ekran_voltage_line(unsigned int);
void make_ekran_frequency(void);
void make_ekran_angle(void);
void make_ekran_power(unsigned int);
void make_ekran_resistance(unsigned int);
void convert_and_insert_char_for_measurement(unsigned int, unsigned int, unsigned int, unsigned int, unsigned char *, unsigned int);
void convert_and_insert_char_for_frequency(int, unsigned char *);
void make_ekran_chose_settings_any_protection(void);
void make_ekran_chose_settings_protection_with_groups(void);
void make_ekran_chose_setpoint_and_timeout(void);
void make_ekran_chose_timeout_control(void);
void make_ekran_chose_settings_vmp(void);
void make_ekran_chose_timeout(void);
void make_ekran_chose_control(void);
void make_ekran_chose_settings(void);
void make_ekran_chose_passwords(void);
void make_ekran_chose_extra_settings(void);
void make_ekran_setpoint_mtz(unsigned int);
void make_ekran_timeout_mtz(unsigned int);
void make_ekran_control_mtz(void);
void make_ekran_control_zdz(void);
void calc_symbol_and_put_into_working_ekran(unsigned char*, void*, void*, unsigned int*, unsigned int, unsigned int, unsigned int);
void calc_int_symbol_and_put_into_working_ekran(unsigned char*, unsigned int*, unsigned int*, unsigned int*);
unsigned int edit_setpoint(unsigned int,  unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
unsigned int check_data_setpoint(unsigned int, unsigned int, unsigned int);
void make_ekran_setpoint_zz(unsigned int);
void make_ekran_timeout_zz(unsigned int);
void make_ekran_control_zz(void);
void make_ekran_timeout_apv(unsigned int);
void make_ekran_control_apv(void);
void make_ekran_setpoint_apv_zmn(unsigned int);
void make_ekran_timeout_apv_zmn(unsigned int);
void make_ekran_control_apv_zmn(void);
void make_ekran_setpoint_achr_chapv(unsigned int);
void make_ekran_timeout_achr_chapv(unsigned int);
void make_ekran_control_achr_chapv(void);
void make_ekran_setpoint_urov(unsigned int);
void make_ekran_timeout_urov(unsigned int);
void make_ekran_control_urov(void);
void make_ekran_setpoint_zop(unsigned int);
void make_ekran_timeout_zop(unsigned int);
void make_ekran_control_zop(void);
void make_ekran_setpoint_Umin(unsigned int);
void make_ekran_timeout_Umin(unsigned int);
void make_ekran_control_Umin(void);
void make_ekran_setpoint_Umax(unsigned int);
void make_ekran_timeout_Umax(unsigned int);
void make_ekran_control_Umax(void);
void make_ekran_setpoint_avr(unsigned int);
void make_ekran_timeout_avr(unsigned int);
void make_ekran_control_avr(void);
void make_ekran_setpoint_control_U(unsigned int);
void make_ekran_timeout_control_U(unsigned int);
void make_ekran_control_control_U(void);
void make_ekran_chose_of_inputs_outputs_leds_df_buttons_for_ranguvannja(unsigned int);
void make_ekran_transformator(void);
void make_ekran_set_function_in_input(unsigned int);
void make_ekran_set_function_in_output_led_df_dt_reg(unsigned int, unsigned int);
void check_current_index_is_presented_in_configuration(unsigned int*, int*, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int);
void make_ekran_setpoint_switch(void);
void make_ekran_timeout_switch(void);
void make_ekran_control_switch(void);
void make_ekran_setpoint_VMP(int);
void make_ekran_control_VMP(void);
void make_ekran_chose_settings_uvv(void);
void make_ekran_dopusk_dv(void);
void make_ekran_type_input_uvv(unsigned int);
void make_ekran_type_output_uvv(void);
void make_ekran_type_led_uvv(void);
void correct_dopusk_dv_when_type_of_input_signal_is_changed(void);
void make_ekran_chose_communication_parameters(void);
void make_ekran_name_of_cell(void);
void make_ekran_address(void);
void make_ekran_chose_setting_rs485(void);
void make_ekran_speed_interface(void);
void make_ekran_pare_interface(void);
void make_ekran_stopbits_interface(void);
void make_ekran_timeout_interface(void);
void make_ekran_chose_registrators(void);
void make_ekran_settings_analog_registrators(void);
void make_ekran_timeout_analog_registrator(void);
void make_ekran_chose_settings_df(void);
void make_ekran_type_df(void);
void make_ekran_timeout_df(unsigned int);
void make_ekran_list_type_source_df(void);
void make_ekran_set_reset_trigger(void);
void make_ekran_list_type_source_dt(void);
void make_ekran_set_function_in_button(unsigned int);
void make_ekran_info(void);
void make_ekran_date_time_pz(void);
void make_ekran_chose_item_of_point_time_settings(void);
void make_ekran_time_settings(unsigned int);
void make_ekran_diagnostyka(unsigned int volatile*);
void make_ekran_list_inputs_outputs(void);
void make_ekran_state_inputs_or_outputs(unsigned int);
void make_ekran_list_registrators(void);
void make_ekran_list_records_registrator(unsigned int);
void make_ekran_list_titles_for_record_of_digital_registrator(void);
void make_ekran_data_and_time_of_records_registrator(unsigned int);
void make_ekran_title_analog_value_records_digital_registrator(void);
void make_ekran_analog_value_records_digital_registrator(void);
void make_ekran_changing_signals_digital_registrator(void);
void make_ekran_list_titles_for_record_of_pr_err_registrator(void);
void make_ekran_changing_diagnostics_pr_err_registrator(void);
void make_ekran_setting_language(void);
void make_ekran_resurs(void);
void make_ekran_energy(unsigned int);
void make_ekran_grupa_ustavok(void);
void make_ekran_vidkluchenja(void);

unsigned int action_after_changing_of_configuration(unsigned int, __SETTINGS *);
void action_after_changing_phase_line(__SETTINGS *);
void action_after_changing_zz1_type(__SETTINGS *);
void calculate_namber_bit_waiting_for_rs_485(void);
void fix_change_settings(unsigned int, unsigned int);
void restore_trigger_functions(unsigned int*);
void changing_diagnostyka_state(void);
unsigned int count_number_set_bit(unsigned int*, unsigned int);

void input_scan(void);
void clocking_global_timers(void);
void main_protection(void);
void df_handler(unsigned int*, unsigned int*);
void dt_handler(unsigned int*, unsigned int*);
void mtz_handler(unsigned int*, unsigned int);
void zdz_handler(unsigned int*);
int timeout_dependent_general(unsigned int, unsigned int);
void zz_handler(unsigned int*, unsigned int);
void zop_handler(unsigned int*, unsigned int);
void umin1_handler(unsigned int*, unsigned int);
void umin2_handler(unsigned int*, unsigned int);
void umax1_handler(unsigned int*, unsigned int);
void umax2_handler(unsigned int*, unsigned int);
void apv_zmn_handler(unsigned int*, unsigned int);
void avr_handler(unsigned int*, unsigned int);
void achr_chapv_handler(unsigned int*, unsigned int);
void control_U_OL(unsigned int*, unsigned int);
void control_U_RL(unsigned int*, unsigned int);
void ready_tu(unsigned int*);
void urov_handler(unsigned int*, unsigned int);
void apv_handler(unsigned int*, unsigned int);
void on_off_handler(unsigned int*, unsigned int*);
void vmp_handler(unsigned int*);
void control_VV(unsigned int*);
void make_koef_for_resurs(void);
void resurs_vymykacha_handler(unsigned int*, unsigned int*);
unsigned int stop_regisrator(unsigned int*, unsigned int*, unsigned int);
void fix_undefined_error_dr(unsigned int*);
void start_monitoring_max_phase_current(unsigned int);
void continue_monitoring_max_phase_current(unsigned int);
void start_monitoring_max_3I0(unsigned int);
void continue_monitoring_max_3I0(unsigned int);
void start_monitoring_max_3U0(unsigned int);
void continue_monitoring_max_3U0(unsigned int);
void start_monitoring_min_U(unsigned int);
void continue_monitoring_min_U(unsigned int);
void start_monitoring_max_U(unsigned int);
void continue_monitoring_max_U(unsigned int);
void start_monitoring_max_ZOP(unsigned int);
void continue_monitoring_max_ZOP(unsigned int);
void start_monitoring_min_f1(unsigned int);
void continue_monitoring_min_f1(unsigned int);
void start_monitoring_min_f2(unsigned int);
void continue_monitoring_min_f2(unsigned int);
void end_monitoring_min_max_measurement(unsigned int, unsigned int*);
void command_start_saving_record_dr_into_dataflash(void);
void routine_for_queue_dr(void);
void digital_registrator(unsigned int*, unsigned int volatile*, unsigned int);
void analog_registrator(unsigned int*);
void diagnostyca_adc_execution(void);

void Usb_routines(void);
void USART_RS485_Configure(void);
void restart_monitoring_RS485(void);
void start_transmint_data_via_RS_485(unsigned int);
unsigned short int  AddCRC(unsigned char, unsigned short int);
void modbus_rountines(unsigned int);
void Error_modbus(unsigned int, unsigned int, unsigned int, unsigned char *);
unsigned int Get_data(unsigned char *, unsigned int, unsigned int);
unsigned int Set_data(unsigned short int, unsigned int, unsigned int, unsigned int, unsigned int);
unsigned int Get_data_file(unsigned char*, unsigned char*, unsigned int*, unsigned int);
void convert_order_list_function_to_gmm(unsigned int*, unsigned short int*);
unsigned int convert_order_list_inputs_to_gmm(unsigned int, unsigned int);
unsigned int convert_order_list_oldr_to_gmm(unsigned int, unsigned int, unsigned int);
unsigned int convert_order_list_buttons_to_gmm(unsigned int, unsigned int);
void set_previous_ranguvannja(void);
unsigned int save_new_rang_inputs_from_gmm(unsigned int, unsigned int, unsigned short int, unsigned int);
unsigned int save_new_rang_oldr_from_gmm(unsigned int, unsigned int, unsigned int, unsigned short int, unsigned int);
unsigned int save_new_rang_buttons_from_gmm(unsigned int, unsigned int, unsigned short int, unsigned int);

ErrorStatus check_errors_i2c(void);
unsigned int start_write_buffer_via_I2C(uint32_t, uint32_t, uint8_t*, uint32_t);
unsigned int start_read_buffer_via_I2C(uint32_t, uint32_t, uint8_t*, uint32_t);
void main_routines_for_i2c(void);
void error_start_i2c(void);

void find_new_ADC_canal_to_read(unsigned int, unsigned int*);
void control_reading_ADCs(unsigned int);
void operate_test_ADCs(void);
void Fourier(unsigned int, unsigned int);
void fapch_val_1(unsigned int);
void fapch_val_2(unsigned int);
void delta_phi_routine(void);
void current_delta_phi(void);
void calc_measurement(unsigned int);
unsigned int norma_value(unsigned long long);
unsigned int sqrt_32(unsigned int);
unsigned int sqrt_64(unsigned long long);
unsigned int get_order(int);

void calc_angle(void);
void calc_power(int*);
void calc_power_and_energy(void);
void calc_resistance(int*, int*);

void velychyna_zvorotnoi_poslidovnosti(int*);
void detector_kuta_nzz(int*);

void directional_mtz(int*, unsigned int);

void main_routines_for_spi1(void);
void main_function_for_dataflash_resp(int);
void main_function_for_dataflash_req(int);
void start_checking_dataflash(void);
void start_exchange_via_spi(int, unsigned int);
void dataflash_status_read(int);
void dataflash_set_pagesize_256(int);
void dataflash_erase(int);
void dataflash_mamory_page_program_through_buffer(int);
void dataflash_mamory_read(int);
void dataflash_mamory_page_into_buffer(int);
void dataflash_mamory_write_buffer(int);
void dataflash_mamory_buffer_into_memory(int);
void analize_received_data_dataflash(int);

void actions_after_changing_tiomouts_ar(void);
void calc_size_and_max_number_records_ar(unsigned int, unsigned int);
unsigned int making_buffer_for_save_ar_record(unsigned int*);
void fix_undefined_error_ar(unsigned int*);

void control_settings(void);
void control_ustuvannja(void);
void control_trg_func(void);
unsigned int control_info_rejestrator(__INFO_REJESTRATOR*, unsigned char);
void control_resurs(void);

void test_external_SRAM(void);

void watchdog_routine(void);
void total_error_sw_fixed(unsigned int);

void setpoints_selecting(unsigned int*, unsigned int);

int str_to_int_DATE_Mmm(void);

#endif

