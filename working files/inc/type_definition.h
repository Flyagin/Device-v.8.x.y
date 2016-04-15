#ifndef __TYPE_DEFINITION__
#define __TYPE_DEFINITION__

#define SRAM1 _Pragma("location=\"variables_RAM1\"")

typedef struct
{
  int current_level;                  //Текучий рівень відображуваного екрану
 
  int index_position;                 //Вказує на якій ми зараз є позиції

  int position_cursor_x;              //X - координата курсору
  int position_cursor_y;              //Y - координата курсору
  
  unsigned int edition;               //0 - вікно зараз не в режимі редагується;
                                      //1 - вікно зараз в режимі редагування;
                                      //2 - вікно чекає підтвердження редагування
                                      //3 - у вікні виведено повідомлення про те, що під час введення даних була зафіксована помилка величиниданих
  
  unsigned int cursor_on;             //1 - курсор відображається/ 0 - курсор не відображається
  unsigned int cursor_blinking_on;    //1 - курсор мигає/ 0 - курсор не мигає
  
  unsigned int current_action;        //Дія яку треба виконати з текучим екраном
                                      //0 - Нічого не виконувати
                                      //1 - Перемістити курсор, ш/або змінити стан його відображення
                                      //2 - Повністю обновити інформацію

} __CURRENT_EKRAN;

typedef struct
{
  int position_cursor_x;              //X - координата курсору

  unsigned int cursor_on;             //1 - курсор відображається/ 0 - курсор не відображається
  unsigned int cursor_blinking_on;    //1 - курсор мигає/ 0 - курсор не мигає
} __PREVIOUS_STATE_CURSOR;

typedef struct
{
  //Тип пристрою
  unsigned int device_id;
  
  //Дискретні входи
  unsigned int type_of_input;                          //Тип дискретного входу 0 - прямий, 1 - інверсний
  unsigned int type_of_input_signal;                   //Тип сигналу дискретного входу 0 - постійний , 1 - змінний
  unsigned int dopusk_dv[NUMBER_INPUTS];              //Допуски ДВ
    
  unsigned int ranguvannja_inputs[N_SMALL*NUMBER_INPUTS]; //Ранжування дискретних входів
  unsigned int ranguvannja_outputs[N_BIG*NUMBER_OUTPUTS]; //Ранжування дискретних вхиодів
  unsigned int ranguvannja_leds[N_BIG*NUMBER_LEDS];       //Ранжування свіотіндикаторів

  unsigned int ranguvannja_analog_registrator[N_BIG];     //Ранжування аналогового реєстратора
  unsigned int ranguvannja_digital_registrator[N_BIG];    //Ранжування дискретного реєстратора
  
  //Тип дискретних виходів
  unsigned int type_of_output;                        //Тип дискретних виходів
                                                      //0 - Командний
                                                      //1 - Сигналький
  
  //Тип світлоіндикаторів
  unsigned int type_of_led;                           //Тип світлоіндикаторі
                                                      //0 - Нормальний
                                                      //1 - Тригерний
    
  //Опреділювальні функції
  unsigned int type_df;                                                 //Тип опреділювальної функції
                                                                        //0 - Пряма
                                                                        //1 - Зворотня
  unsigned int timeout_pause_df[NUMBER_DEFINED_FUNCTIONS];              //Час затримки спрацюваня опреділювальної функції
  unsigned int timeout_work_df[NUMBER_DEFINED_FUNCTIONS];               //Час роботи опреділювальної функції
  unsigned int ranguvannja_df_source_plus[N_BIG*NUMBER_DEFINED_FUNCTIONS];  //Ранжування прямих команд опреділювальниї функцій
  unsigned int ranguvannja_df_source_minus[N_BIG*NUMBER_DEFINED_FUNCTIONS]; //Ранжування інверсних команд опреділювальниї функцій
  unsigned int ranguvannja_df_source_blk[N_BIG*NUMBER_DEFINED_FUNCTIONS];   //Ранжування команд блокування опреділювальниї функцій

  unsigned int ranguvannja_set_dt_source_plus[N_BIG*NUMBER_DEFINED_TRIGGERS];   //Ранжування прямих команд встановлення опреділювальних триґерів
  unsigned int ranguvannja_set_dt_source_minus[N_BIG*NUMBER_DEFINED_TRIGGERS];  //Ранжування інверсних команд встановлення опреділювальних триґерів
  unsigned int ranguvannja_reset_dt_source_plus[N_BIG*NUMBER_DEFINED_TRIGGERS]; //Ранжування прямих команд скидання опреділювальних триґерів
  unsigned int ranguvannja_reset_dt_source_minus[N_BIG*NUMBER_DEFINED_TRIGGERS];//Ранжування інверсних команд скидання опреділювальних триґерів
  
  unsigned int ranguvannja_buttons[NUMBER_DEFINED_BUTTONS];             //Ранжування опреділюваних кнопок
  
  unsigned int configuration;         //Конфігурація приладу
  
  unsigned int grupa_ustavok;         //Група уставок
                                      // 1 - Група 1
                                      // 2 - Група 2
                                      // 3 - Група 3
                                      // 4 - Група 4
  
  //МТЗ
  int type_mtz1;                                                //Тип МТЗ1 (0 - Проста, 1 - Направлена, 2 -  З пуском по напрузі)
  unsigned int setpoint_mtz_1[NUMBER_GROUP_USTAVOK];            //Уставка МТЗ першої ступені (проста)
  unsigned int setpoint_mtz_1_n_vpered[NUMBER_GROUP_USTAVOK];   //Уставка МТЗ першої ступені (направлена:вперед)
  unsigned int setpoint_mtz_1_n_nazad[NUMBER_GROUP_USTAVOK];    //Уставка МТЗ першої ступені (направлена:назад)
  unsigned int setpoint_mtz_1_angle[NUMBER_GROUP_USTAVOK];      //Уставка МТЗ першої ступені (кут довороту)
           int setpoint_mtz_1_angle_cos[NUMBER_GROUP_USTAVOK];  //Уставка МТЗ першої ступені (косинус кута довороту)
           int setpoint_mtz_1_angle_sin[NUMBER_GROUP_USTAVOK];  //Уставка МТЗ першої ступені (синус кута довороту)
  unsigned int setpoint_mtz_1_po_napruzi[NUMBER_GROUP_USTAVOK]; //Уставка МТЗ першої ступені (по напрузі)
  unsigned int setpoint_mtz_1_U[NUMBER_GROUP_USTAVOK];          //Уставка МТЗ першої ступені (напруга пуску)
  int type_mtz2;                                                //Тип МТЗ2 (0 - Проста, 1 - Направлена, 2 -  З пуском по напрузі, 3 - Залежна А, 4 - Залежна В, 5 - Залежна С, 6 - РТ-80, 7- РТВ-1)
  unsigned int setpoint_mtz_2[NUMBER_GROUP_USTAVOK];            //Уставка МТЗ другої ступені
  unsigned int setpoint_mtz_2_n_vpered[NUMBER_GROUP_USTAVOK];   //Уставка МТЗ другої ступені (направлена:вперед)
  unsigned int setpoint_mtz_2_n_nazad[NUMBER_GROUP_USTAVOK];    //Уставка МТЗ другої ступені (направлена:назад)
  unsigned int setpoint_mtz_2_angle[NUMBER_GROUP_USTAVOK];      //Уставка МТЗ другої ступені (кут довороту)
           int setpoint_mtz_2_angle_cos[NUMBER_GROUP_USTAVOK];  //Уставка МТЗ другої ступені (косинус кута довороту)
           int setpoint_mtz_2_angle_sin[NUMBER_GROUP_USTAVOK];  //Уставка МТЗ другої ступені (синус кута довороту)
  unsigned int setpoint_mtz_2_po_napruzi[NUMBER_GROUP_USTAVOK]; //Уставка МТЗ другої ступені (по напрузі)
  unsigned int setpoint_mtz_2_U[NUMBER_GROUP_USTAVOK];          //Уставка МТЗ другої ступені (напруга пуску)
  int type_mtz3;                                                //Тип МТЗ3 (0 - Проста, 1 - Направлена, 2 -  З пуском по напрузі)
  unsigned int setpoint_mtz_3[NUMBER_GROUP_USTAVOK];            //Уставка МТЗ третьої ступені
  unsigned int setpoint_mtz_3_n_vpered[NUMBER_GROUP_USTAVOK];   //Уставка МТЗ третьої ступені (направлена:вперед)
  unsigned int setpoint_mtz_3_n_nazad[NUMBER_GROUP_USTAVOK];    //Уставка МТЗ третьої ступені (направлена:назад)
  unsigned int setpoint_mtz_3_angle[NUMBER_GROUP_USTAVOK];      //Уставка МТЗ третьої ступені (кут довороту)
           int setpoint_mtz_3_angle_cos[NUMBER_GROUP_USTAVOK];  //Уставка МТЗ третьої ступені (косинус кута довороту)
           int setpoint_mtz_3_angle_sin[NUMBER_GROUP_USTAVOK];  //Уставка МТЗ третьої ступені (синус кута довороту)
  unsigned int setpoint_mtz_3_po_napruzi[NUMBER_GROUP_USTAVOK]; //Уставка МТЗ третьої ступені (по напрузі)
  unsigned int setpoint_mtz_3_U[NUMBER_GROUP_USTAVOK];          //Уставка МТЗ третьої ступені (напруга пуску)
  int type_mtz4;                                                //Тип МТЗ4 (0 - Проста, 1 - Направлена, 2 -  З пуском по напрузі)
  unsigned int setpoint_mtz_4[NUMBER_GROUP_USTAVOK];            //Уставка МТЗ четвертої ступені
  unsigned int setpoint_mtz_4_n_vpered[NUMBER_GROUP_USTAVOK];   //Уставка МТЗ четвертої ступені (направлена:вперед)
  unsigned int setpoint_mtz_4_n_nazad[NUMBER_GROUP_USTAVOK];    //Уставка МТЗ четвертої ступені (направлена:назад)
  unsigned int setpoint_mtz_4_angle[NUMBER_GROUP_USTAVOK];      //Уставка МТЗ четвертої ступені (кут довороту)
           int setpoint_mtz_4_angle_cos[NUMBER_GROUP_USTAVOK];  //Уставка МТЗ четвертої ступені (косинус кута довороту)
           int setpoint_mtz_4_angle_sin[NUMBER_GROUP_USTAVOK];  //Уставка МТЗ четвертої ступені (синус кута довороту)
  unsigned int setpoint_mtz_4_po_napruzi[NUMBER_GROUP_USTAVOK]; //Уставка МТЗ четвертої ступені (по напрузі)
  unsigned int setpoint_mtz_4_U[NUMBER_GROUP_USTAVOK];          //Уставка МТЗ четвертої ступені (напруга пуску)

  int timeout_mtz_1[NUMBER_GROUP_USTAVOK];                      //Витримка МТЗ першої ступені
  int timeout_mtz_1_n_vpered[NUMBER_GROUP_USTAVOK];             //Витримка МТЗ першої ступені (направлена:вперед)
  int timeout_mtz_1_n_nazad[NUMBER_GROUP_USTAVOK];              //Витримка МТЗ першої ступені (направлена:назад)
  int timeout_mtz_1_po_napruzi[NUMBER_GROUP_USTAVOK];           //Витримка МТЗ першої ступені (по напрузі)
  int timeout_mtz_2[NUMBER_GROUP_USTAVOK];                      //Витримка МТЗ другої ступені
  int timeout_mtz_2_pr[NUMBER_GROUP_USTAVOK];                   //Витримка присторення МТЗ другої ступені
  int timeout_mtz_2_n_vpered[NUMBER_GROUP_USTAVOK];             //Витримка МТЗ другої ступені (направлена:вперед)
  int timeout_mtz_2_n_vpered_pr[NUMBER_GROUP_USTAVOK];          //Витримка присторення МТЗ другої ступені (направлена:вперед)
  int timeout_mtz_2_n_nazad[NUMBER_GROUP_USTAVOK];              //Витримка МТЗ другої ступені (направлена:назад)
  int timeout_mtz_2_n_nazad_pr[NUMBER_GROUP_USTAVOK];           //Витримка присторення МТЗ другої ступені (направлена:назад)
  int timeout_mtz_2_po_napruzi[NUMBER_GROUP_USTAVOK];           //Витримка МТЗ другої ступені (по напрузі)
  int timeout_mtz_2_po_napruzi_pr[NUMBER_GROUP_USTAVOK];        //Витримка присторення МТЗ другої ступені (по напрузі)
  int timeout_mtz_2_vvid_pr[NUMBER_GROUP_USTAVOK];              //Витримка вводу присорення МТЗ2
  int timeout_mtz_3[NUMBER_GROUP_USTAVOK];                      //Витримка МТЗ третьої ступені
  int timeout_mtz_3_n_vpered[NUMBER_GROUP_USTAVOK];             //Витримка МТЗ третьої ступені (направлена:вперед)
  int timeout_mtz_3_n_nazad[NUMBER_GROUP_USTAVOK];              //Витримка МТЗ третьої ступені (направлена:назад)
  int timeout_mtz_3_po_napruzi[NUMBER_GROUP_USTAVOK];           //Витримка МТЗ третьої ступені (по напрузі)
  int timeout_mtz_4[NUMBER_GROUP_USTAVOK];                      //Витримка МТЗ четвертої ступені
  int timeout_mtz_4_n_vpered[NUMBER_GROUP_USTAVOK];             //Витримка МТЗ третьої ступені (направлена:вперед)
  int timeout_mtz_4_n_nazad[NUMBER_GROUP_USTAVOK];              //Витримка МТЗ третьої ступені (направлена:назад)
  int timeout_mtz_4_po_napruzi[NUMBER_GROUP_USTAVOK];           //Витримка МТЗ третьої ступені (по напрузі)

  unsigned int control_mtz;                                 //Поле для управління МТЗ
  
  //ЗДЗ
  unsigned int control_zdz;                                 //Поле для управління ЗДЗ

  //ЗЗ
  unsigned int setpoint_zz_3I0[NUMBER_GROUP_USTAVOK];       //уставка ЗЗ/3I0
  unsigned int setpoint_zz_3U0[NUMBER_GROUP_USTAVOK];       //уставка ЗЗ/3U0

  int timeout_zz_3I0[NUMBER_GROUP_USTAVOK];                 //Витримка ЗЗ/3I0
  int timeout_zz_3U0[NUMBER_GROUP_USTAVOK];                 //Витримка ЗЗ/3I0
  int timeout_nzz[NUMBER_GROUP_USTAVOK];                    //Витримка НЗЗ

   unsigned int control_zz;              //Поле для управління ЗЗ

  //АПВ
  int timeout_apv_1[NUMBER_GROUP_USTAVOK];                    //Витримка 1 Циклу АПВ
  int timeout_apv_2[NUMBER_GROUP_USTAVOK];                    //Витримка 2 Циклу АПВ
  int timeout_apv_3[NUMBER_GROUP_USTAVOK];                    //Витримка 3 Циклу АПВ
  int timeout_apv_4[NUMBER_GROUP_USTAVOK];                    //Витримка 4 Циклу АПВ
  int timeout_apv_block_vid_apv1[NUMBER_GROUP_USTAVOK];       //Блокування АПВ від роботи АПВ1
  int timeout_apv_block_vid_apv2[NUMBER_GROUP_USTAVOK];       //Блокування АПВ від роботи АПВ2
  int timeout_apv_block_vid_apv3[NUMBER_GROUP_USTAVOK];       //Блокування АПВ від роботи АПВ3
  int timeout_apv_block_vid_apv4[NUMBER_GROUP_USTAVOK];       //Блокування АПВ від роботи АПВ4
  int timeout_apv_block_vid_VV[NUMBER_GROUP_USTAVOK];         //Витримка блокування АПВ в момекнт включення вимикача
  unsigned int control_apv;             //Поле для управління АПВ
  
  //АПВ ЗМН
  unsigned int setpoint_apv_zmn1[NUMBER_GROUP_USTAVOK];       //уставка АПВ ЗМН1
  unsigned int setpoint_apv_zmn2[NUMBER_GROUP_USTAVOK];       //уставка АПВ ЗМН2
  unsigned int setpoint_kratn_apv_zmn[NUMBER_GROUP_USTAVOK];  //кратність АПВ ЗМН
  int timeout_apv_zmn_1[NUMBER_GROUP_USTAVOK];                //Витримка Циклу АПВ ЗМН1
  int timeout_apv_zmn_2[NUMBER_GROUP_USTAVOK];                //Витримка Циклу АПВ ЗМН2
  int timeout_apv_zmn_zavershennja[NUMBER_GROUP_USTAVOK];     //Витримка завершення роботи логіки АПВ-ЗМН (для одного процесу)
  unsigned int control_apv_zmn;                               //Поле для управління АПВ ЗМН
  
  //АЧР-ЧАПВ
  unsigned int setpoint_achr_f_rab[NUMBER_GROUP_USTAVOK];    //уставка FРаб АЧР частоты F1
  unsigned int setpoint_chapv_f_rab[NUMBER_GROUP_USTAVOK];   //уставка FРаб ЧАПВ частоты F1
  unsigned int setpoint_achr_chapv_uf1[NUMBER_GROUP_USTAVOK]; //уставка АЧР ЧАПВ UF1
  unsigned int setpoint_achr_chapv_uf2[NUMBER_GROUP_USTAVOK]; //уставка АЧР ЧАПВ UF2

  int timeout_achr_1[NUMBER_GROUP_USTAVOK];                   //Витримка Циклу АЧР1
  int timeout_chapv_1[NUMBER_GROUP_USTAVOK];                  //Витримка Циклу ЧАПВ1
  int timeout_achr_2[NUMBER_GROUP_USTAVOK];                   //Витримка Циклу АЧР2
  int timeout_chapv_2[NUMBER_GROUP_USTAVOK];                  //Витримка Циклу ЧАПВ2
  unsigned int control_achr_chapv;      //Поле для управління АЧР-ЧАПВ
  
  //УРОВ
  unsigned int setpoint_urov[NUMBER_GROUP_USTAVOK];         //уставка УРОВ
  int timeout_urov_1[NUMBER_GROUP_USTAVOK];                 //Витримка УРОВ першої ступені
  int timeout_urov_2[NUMBER_GROUP_USTAVOK];                 //Витримка УРОВ другої ступені
  unsigned int control_urov;                                //Поле для управління УРОВ

  //ЗОП(КОФ)
  unsigned int setpoint_zop[NUMBER_GROUP_USTAVOK];          //уставка ЗОП(КОФ)
  int timeout_zop[NUMBER_GROUP_USTAVOK];                    //Витримка  ЗОП(КОФ)
  unsigned int control_zop;                                 //Поле для управління ЗОП(КОФ)

  //Umin
  unsigned int setpoint_Umin1[NUMBER_GROUP_USTAVOK];        //уставка Umin1
  unsigned int setpoint_Umin1_Iblk[NUMBER_GROUP_USTAVOK];   //уставка блокування по струму Umin1
  unsigned int setpoint_Umin2[NUMBER_GROUP_USTAVOK];        //уставка Umin2
  unsigned int setpoint_Umin2_Iblk[NUMBER_GROUP_USTAVOK];   //уставка блокування по струму Umin2
  int timeout_Umin1[NUMBER_GROUP_USTAVOK];                    //Витримка  Umin1
  int timeout_Umin2[NUMBER_GROUP_USTAVOK];                    //Витримка  Umin2
  unsigned int control_Umin;                                 //Поле для управління Umin
  
  //Umax
  unsigned int setpoint_Umax1[NUMBER_GROUP_USTAVOK];        //уставка Umax1
  unsigned int setpoint_Umax2[NUMBER_GROUP_USTAVOK];        //уставка Umax2
  int timeout_Umax1[NUMBER_GROUP_USTAVOK];                  //Витримка  Umax1
  int timeout_Umax2[NUMBER_GROUP_USTAVOK];                  //Витримка  Umax2
  unsigned int control_Umax;                                //Поле для управління Umax

  //АВР
  unsigned int setpoint_avr_min1[NUMBER_GROUP_USTAVOK];       //уставка АВР min1
  unsigned int setpoint_avr_max1[NUMBER_GROUP_USTAVOK];       //уставка АВР max1
  unsigned int setpoint_avr_min2[NUMBER_GROUP_USTAVOK];       //уставка АВР min2
  unsigned int setpoint_avr_max2[NUMBER_GROUP_USTAVOK];       //уставка АВР max2
  unsigned int setpoint_kratn_avr[NUMBER_GROUP_USTAVOK];      //кратність АВР
  int timeout_avr_ol[NUMBER_GROUP_USTAVOK];                   //Витримка Циклу АВР ОЛ
  int timeout_avr_rl[NUMBER_GROUP_USTAVOK];                   //Витримка Циклу АВР РЛ
  int timeout_avr_zavershennja[NUMBER_GROUP_USTAVOK];         //Витримка завершення роботи логіки АВР (для одного процесу)
  int timeout_avr_reset_blk[NUMBER_GROUP_USTAVOK];            //Витримка скидання блокування АВР по захистам від появи на двох сторонах
  unsigned int control_avr;                                   //Поле для управління АВР

  //Контроль напруги лінії
  unsigned int setpoint_U_ol[NUMBER_GROUP_USTAVOK];           //уставка U РЛ
  unsigned int setpoint_U_rl[NUMBER_GROUP_USTAVOK];           //уставка U РЛ
  int timeout_U_ol[NUMBER_GROUP_USTAVOK];                     //Таймер U РЛ
  int timeout_U_rl[NUMBER_GROUP_USTAVOK];                     //Таймер U РЛ
  unsigned int control_control_U;            					  //Поле для управління U РЛ

  unsigned int T0;                      //Коефіцієнт трансформації для трансформатора 3I0
  unsigned int TCurrent;                //Коефіцієнт трансформації для трансформатора струмів
  unsigned int TVoltage;                //Коефіцієнт трансформації для трансформатора напруг
  
  unsigned int password1;                                       //Пароль для редагування з меню
  unsigned int password2;                                       //Пароль для очистки лічилчників енегії і ресурсу вимикача
  unsigned int timeout_deactivation_password_interface_USB;     //Час деактивації паролю для редагування з інтерфейсу USB
  unsigned int password_interface_USB;                          //Пароль для редагування з інтерфейсу USB
  unsigned int timeout_deactivation_password_interface_RS485;   //Час деактивації паролю для редагування з інтерфейсу RS485
  unsigned int password_interface_RS485;                        //Пароль для редагування з інтерфейсу RS485
  
  //Вимикач
  unsigned int setpoint_Inom;                   //Номінальний струм вимикача
  unsigned int setpoint_r_kom_st_Inom;          //Ресурс комунікаційної стійкості при номінальному струмі вимикача
  unsigned int setpoint_Inom_vymk;              //Номінальний струм вимкнення вимикача
  unsigned int setpoint_r_kom_st_Inom_vymk;     //Ресурс комунікаційної стійкості при номінальному струмі вимкнення вимикача
  unsigned int setpoint_pochatkovyj_resurs;     //Початковий ресурс вимикача
  unsigned int setpoint_krytychnyj_resurs;      //Критичний ресурс вимикача
  unsigned int setpoint_pochatkova_k_vymk;      //Початкова кількість вимкнень
  int timeout_swch_on;                          //Витримка T вкл.
  int timeout_swch_off;                         //Витримка T відкл.
  int timeout_swch_udl_blk_on;                  //Витримка T "удлинение сигнала блокировки включения"
  int timeout_pryvoda_VV;                       //Витримка T "Привіода ВВ"
  unsigned int control_switch;                  //Поле для управління вимикачем
  
  //Визначення місця пошкодження
  unsigned int lines[2];                        //Кількість ділянок
  unsigned int dovgyna[2][MAX_NUMBER_LINES_VMP];//Довжина ліній
  unsigned int opir[2][MAX_NUMBER_LINES_VMP];   //Питомий опір ліній
  unsigned int control_vmp;                     //Поле для управління ВМП
  
  //Аналоговий реєстратор
  unsigned int prefault_number_periods; //Час доаварійного масиву (кількість періодів промислової частоти)
  unsigned int postfault_number_periods;//Час післяарійного масиву (кількість періодів промислової частоти)

  //Комунікація
  unsigned int name_of_cell[MAX_CHAR_IN_NAME_OF_CELL];//І'мя ячейки
  unsigned int volatile address;                      //Адреса
  int speed_RS485;                                    //швидкість обміну
                                                        // 0 - 9600
                                                        // 1 - 14400
                                                        // 2 - 19200
                                                        // 3 - 28800
                                                        // 4 - 38400
                                                        // 5 - 57600
                                                        // 6 - 115200
  int pare_bit_RS485;                                 //паритет
                                                        // 0 - NONE
                                                        // 1 - ODD
                                                        // 2 - EVEN
  int number_stop_bit_RS485;                          //кількість стоп-біт
                                                        // 0 - 1 stop-bit
                                                        // 1 - 2 stop-bits
  unsigned int time_out_1_RS485;                        //time-out наступного символу = X/10 символу
  
  int language;                                         //мова меню  0= змінна мов не підтримується; 1=RU; 2=UA; 3=EN; 4=KZ; 5=др.
  
  unsigned int control_extra_settings_1;                //Поле для додаткових налаштувань

  
  unsigned char time_setpoints[7+1];                     //Час останніх змін уставок-витримок-управління
                                                         //Останній байт масиву сигналізує мітку звідки зміни були проведені
                                                            //0 - мінімальні параметри
                                                            //1 - клавіатура
                                                            //2 - USB
                                                            //3 - RS-485
  
  unsigned char time_ranguvannja[7+1];                    //Час останніх змін ранжування
                                                            //0 - мінімальні параметри
                                                            //1 - клавіатура
                                                            //2 - USB
                                                            //3 - RS-485
} __SETTINGS;

typedef struct
{
  //Стан обміну
  int state_execution;        //-1 - драйвер готовий до початку нових транзакцій
                              // 0 - відбувається обмін
                              // 1 - обмін завершений без помилок
                              // 2 - обмін завершений з помилками
  
  
  //Ідентифікатор пристрою, з яким ведетьсяобмін
  int device_id;              //-1 - пристрій не визначений
                              // EEPROM_ADDRESS - EEPROM
                              // RTC_ADDRESS - RTC
  //Код операції
  int action;                 //-1 - не визначений
                              // 0 - запис адреси для подальшого зчитування
                              // 1 - зчитування
                              // 2 - запис адреси і запис даних
  

  //Внутрішня адреса по якій буде іти звертання
  unsigned int internal_address;

  //Кількість байт для читання/запису (корисних)
  unsigned int number_bytes;
  
  //Вказівник на буфер (корисний)
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
  unsigned int state_execution;     //стан виконуваної заразоперації
  
  unsigned int code_operation;      //Код виконуваної операції

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
