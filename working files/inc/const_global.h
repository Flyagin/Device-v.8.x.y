#ifndef __CONST_GLOBAL__
#define __CONST_GLOBAL__

#define N_BIG   6
#define N_SMALL 2

//Величина, яка необхідна для періодичної (період 1  мс   ) генерації переривань каналом 1 таймеру 2 з прескаллером 2000 = (1999 + 1)
#define TIM2_CCR1_VAL                   30
//Величина, яка необхідна для періодичної (період 10 мс   ) генерації переривань каналом 1 таймеру 4 з прескаллером 600 = (599 + 1)
#define TIM4_CCR1_VAL                   1000
//Величина, яка необхідна для періодичної (період 1 мс   ) генерації переривань каналом 2 таймеру 4 з прескаллером 600 = (599 + 1)
#define TIM4_CCR2_VAL                   100
//Величина, яка необхідна для періодичної (як мінімум, період 10 мкс   ) генерації переривань каналом 3 таймеру 4 з прескаллером 600 = (599 + 1)
#define TIM4_CCR3_VAL                   1
//Величина, яка необхідна для періодичної (період 0,625 мс) генерації переривань каналом 1 таймеру 3 з прескаллером 1 = (0 + 1)
#define TIM5_CCR1_2_3_VAL               37500

#define MAX_NUMBER_LINES_VMP            8

#define DELTA_TIME_FOR_TIMERS           1

#define NUMBER_ANALOG_CANALES_VAL_1     6
#define NUMBER_ANALOG_CANALES_VAL_2     1
#define NUMBER_ANALOG_CANALES_VAL_CONF  1

#define NUMBER_ANALOG_CANALES           (                                       \
                                         NUMBER_ANALOG_CANALES_VAL_1    +       \
                                         NUMBER_ANALOG_CANALES_VAL_CONF +       \
                                         NUMBER_ANALOG_CANALES_VAL_2            \
                                        )

#define NUMBER_INPUTS_1                 5
#define NUMBER_INPUTS_2                 5
#define NUMBER_INPUTS                   (NUMBER_INPUTS_1 + NUMBER_INPUTS_2)
#define NUMBER_OUTPUTS_1                6
#define NUMBER_OUTPUTS_2                4
#define NUMBER_OUTPUTS                  (NUMBER_OUTPUTS_1 + NUMBER_OUTPUTS_2)

#define NUMBER_LEDS                     8
#define NUMBER_DEFINED_FUNCTIONS        8
#define NUMBER_DEFINED_TRIGGERS         4
#define NUMBER_DEFINED_BUTTONS          6

#define NUMBER_GROUP_USTAVOK            4

enum _configuration {
MTZ_BIT_CONFIGURATION = 0,
ZDZ_BIT_CONFIGURATION,
ZZ_BIT_CONFIGURATION,
APV_BIT_CONFIGURATION,
APV_ZMN_BIT_CONFIGURATION,
ACHR_CHAPV_BIT_CONFIGURATION,
UROV_BIT_CONFIGURATION,
ZOP_BIT_CONFIGURATION,
UMIN_BIT_CONFIGURATION,
UMAX_BIT_CONFIGURATION,
AVR_BIT_CONFIGURATION,
CONTROL_U_BIT_CONFIGURATION,
VMP_BIT_CONFIGURATION,

TOTAL_NUMBER_PROTECTION
};

/*****************************************/
//Константи для ранжування функціональних кнопок
/*****************************************/
enum __rang_button {
RANG_BUTTON_DF1_IN = 0,
RANG_BUTTON_DF2_IN,
RANG_BUTTON_DF3_IN,
RANG_BUTTON_DF4_IN,
RANG_BUTTON_DF5_IN,
RANG_BUTTON_DF6_IN,
RANG_BUTTON_DF7_IN,
RANG_BUTTON_DF8_IN,
RANG_BUTTON_DT1_SET,
RANG_BUTTON_DT1_RESET,
RANG_BUTTON_DT2_SET,
RANG_BUTTON_DT2_RESET,
RANG_BUTTON_DT3_SET,
RANG_BUTTON_DT3_RESET,
RANG_BUTTON_DT4_SET,
RANG_BUTTON_DT4_RESET,
RANG_BUTTON_RESET_LEDS,
RANG_BUTTON_RESET_RELES,
RANG_BUTTON_MISCEVE_DYSTANCIJNE,
RANG_BUTTON_VKL_VV,
RANG_BUTTON_OTKL_VV,
RANG_BUTTON_RESET_BLOCK_READY_TU_VID_ZAHYSTIV,

RANG_BUTTON_RESET_BLOCK_APV_ZMN,

RANG_BUTTON_OTKL_AVR,
RANG_BUTTON_SBROS_BLOCK_AVR
};

#define NUMBER_GENERAL_SIGNAL_FOR_RANG_BUTTON     22
#define NUMBER_MTZ_SIGNAL_FOR_RANG_BUTTON         0
#define NUMBER_ZDZ_SIGNAL_FOR_RANG_BUTTON         0
#define NUMBER_ZZ_SIGNAL_FOR_RANG_BUTTON          0
#define NUMBER_APV_SIGNAL_FOR_RANG_BUTTON         0
#define NUMBER_APV_ZMN_SIGNAL_FOR_RANG_BUTTON     1
#define NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_BUTTON  0
#define NUMBER_UROV_SIGNAL_FOR_RANG_BUTTON        0
#define NUMBER_ZOP_SIGNAL_FOR_RANG_BUTTON         0
#define NUMBER_UMIN_SIGNAL_FOR_RANG_BUTTON        0
#define NUMBER_UMAX_SIGNAL_FOR_RANG_BUTTON        0
#define NUMBER_AVR_SIGNAL_FOR_RANG_BUTTON         2
#define NUMBER_CONTROL_U_SIGNAL_FOR_RANG_BUTTON   0
#define NUMBER_VMP_SIGNAL_FOR_RANG_BUTTON         0

#define NUMBER_TOTAL_SIGNAL_FOR_RANG_BUTTON       (                                           \
                                                   NUMBER_GENERAL_SIGNAL_FOR_RANG_BUTTON     + \
                                                   NUMBER_MTZ_SIGNAL_FOR_RANG_BUTTON         + \
                                                   NUMBER_ZDZ_SIGNAL_FOR_RANG_BUTTON         + \
                                                   NUMBER_ZZ_SIGNAL_FOR_RANG_BUTTON          + \
                                                   NUMBER_APV_SIGNAL_FOR_RANG_BUTTON         + \
                                                   NUMBER_APV_ZMN_SIGNAL_FOR_RANG_BUTTON     + \
                                                   NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_BUTTON  + \
                                                   NUMBER_UROV_SIGNAL_FOR_RANG_BUTTON        + \
                                                   NUMBER_ZOP_SIGNAL_FOR_RANG_BUTTON         + \
                                                   NUMBER_UMIN_SIGNAL_FOR_RANG_BUTTON        + \
                                                   NUMBER_UMAX_SIGNAL_FOR_RANG_BUTTON        + \
                                                   NUMBER_AVR_SIGNAL_FOR_RANG_BUTTON         + \
                                                   NUMBER_CONTROL_U_SIGNAL_FOR_RANG_BUTTON   + \
                                                   NUMBER_VMP_SIGNAL_FOR_RANG_BUTTON           \
                                                  ) 
/*****************************************/

/*****************************************/
//Константи для ранжування дискретних входів
/*****************************************/
enum __rang_input {
RANG_INPUT_DF1_IN = 0,
RANG_INPUT_DF2_IN,
RANG_INPUT_DF3_IN,
RANG_INPUT_DF4_IN,
RANG_INPUT_DF5_IN,
RANG_INPUT_DF6_IN,
RANG_INPUT_DF7_IN,
RANG_INPUT_DF8_IN,
RANG_INPUT_DT1_SET,
RANG_INPUT_DT1_RESET,
RANG_INPUT_DT2_SET,
RANG_INPUT_DT2_RESET,
RANG_INPUT_DT3_SET,
RANG_INPUT_DT3_RESET,
RANG_INPUT_DT4_SET,
RANG_INPUT_DT4_RESET,
RANG_INPUT_DVERI_SHAFY_UPR_VIDKR,
RANG_INPUT_ACUMUL_BATAREJA_ROZRJADGENA,
RANG_INPUT_REZERVTE_GYVLENNJA,
RANG_INPUT_BLOCK_VKL_VV,
RANG_INPUT_RESET_LEDS,
RANG_INPUT_RESET_RELES,
RANG_INPUT_MISCEVE_DYSTANCIJNE,
RANG_INPUT_STATE_VV,
RANG_INPUT_OTKL_VID_ZOVN_ZAHYSTIV,
RANG_INPUT_VKL_VV,
RANG_INPUT_CTRL_VKL,
RANG_INPUT_OTKL_VV,
RANG_INPUT_CTRL_OTKL,
RANG_INPUT_1_GRUPA_USTAVOK,
RANG_INPUT_2_GRUPA_USTAVOK,
RANG_INPUT_3_GRUPA_USTAVOK,
RANG_INPUT_4_GRUPA_USTAVOK,
RANG_INPUT_RESET_BLOCK_READY_TU_VID_ZAHYSTIV,

RANG_INPUT_BLOCK_MTZ1,
RANG_INPUT_BLOCK_MTZ2,
RANG_INPUT_BLOCK_USK_MTZ2,
RANG_INPUT_BLOCK_MTZ3,
RANG_INPUT_BLOCK_MTZ4,

RANG_INPUT_PUSK_ZDZ_VID_DV,

RANG_INPUT_BLOCK_NZZ,

RANG_INPUT_STAT_BLK_APV,

RANG_INPUT_RESET_BLOCK_APV_ZMN,
RANG_INPUT_BLOCK_APV_ZMN,

RANG_INPUT_BLOCK_ACHR,
RANG_INPUT_ACHR_CHAPV_VID_DV,

RANG_INPUT_PUSK_UROV_VID_DV,

RANG_INPUT_BLOCK_ZOP,

RANG_INPUT_BLOCK_UMIN1,
RANG_INPUT_START_UMIN1,
RANG_INPUT_BLOCK_UMIN2,
RANG_INPUT_START_UMIN2,

RANG_INPUT_BLOCK_UMAX1,
RANG_INPUT_BLOCK_UMAX2,

RANG_INPUT_OTKL_AVR,
RANG_INPUT_SBROS_BLOCK_AVR,
RANG_INPUT_STAT_BLOCK_AVR
};

#define NUMBER_GENERAL_SIGNAL_FOR_RANG_INPUT     34
#define NUMBER_MTZ_SIGNAL_FOR_RANG_INPUT         5
#define NUMBER_ZDZ_SIGNAL_FOR_RANG_INPUT         1
#define NUMBER_ZZ_SIGNAL_FOR_RANG_INPUT          1
#define NUMBER_APV_SIGNAL_FOR_RANG_INPUT         1
#define NUMBER_APV_ZMN_SIGNAL_FOR_RANG_INPUT     2
#define NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_INPUT  2
#define NUMBER_UROV_SIGNAL_FOR_RANG_INPUT        1
#define NUMBER_ZOP_SIGNAL_FOR_RANG_INPUT         1
#define NUMBER_UMIN_SIGNAL_FOR_RANG_INPUT        4
#define NUMBER_UMAX_SIGNAL_FOR_RANG_INPUT        2
#define NUMBER_AVR_SIGNAL_FOR_RANG_INPUT         3
#define NUMBER_CONTROL_U_SIGNAL_FOR_RANG_INPUT   0
#define NUMBER_VMP_SIGNAL_FOR_RANG_INPUT         0

#define NUMBER_TOTAL_SIGNAL_FOR_RANG_INPUT       (                                          \
                                                  NUMBER_GENERAL_SIGNAL_FOR_RANG_INPUT    + \
                                                  NUMBER_MTZ_SIGNAL_FOR_RANG_INPUT        + \
                                                  NUMBER_ZDZ_SIGNAL_FOR_RANG_INPUT        + \
                                                  NUMBER_ZZ_SIGNAL_FOR_RANG_INPUT         + \
                                                  NUMBER_APV_SIGNAL_FOR_RANG_INPUT        + \
                                                  NUMBER_APV_ZMN_SIGNAL_FOR_RANG_INPUT    + \
                                                  NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_INPUT + \
                                                  NUMBER_UROV_SIGNAL_FOR_RANG_INPUT       + \
                                                  NUMBER_ZOP_SIGNAL_FOR_RANG_INPUT        + \
                                                  NUMBER_UMIN_SIGNAL_FOR_RANG_INPUT       + \
                                                  NUMBER_UMAX_SIGNAL_FOR_RANG_INPUT       + \
                                                  NUMBER_AVR_SIGNAL_FOR_RANG_INPUT        + \
                                                  NUMBER_CONTROL_U_SIGNAL_FOR_RANG_INPUT  + \
                                                  NUMBER_VMP_SIGNAL_FOR_RANG_INPUT          \
                                                 ) 
/*****************************************/

/*****************************************/
//Константи для ранжування дискретних виходів-свтодіодів-О-функцій-реєстраторів
/*****************************************/
enum __rang_output_led_df_reg {
RANG_OUTPUT_LED_DF_REG_DF1_IN= 0,
RANG_OUTPUT_LED_DF_REG_DF1_OUT,
RANG_OUTPUT_LED_DF_REG_DF2_IN,
RANG_OUTPUT_LED_DF_REG_DF2_OUT,
RANG_OUTPUT_LED_DF_REG_DF3_IN,
RANG_OUTPUT_LED_DF_REG_DF3_OUT,
RANG_OUTPUT_LED_DF_REG_DF4_IN,
RANG_OUTPUT_LED_DF_REG_DF4_OUT,
RANG_OUTPUT_LED_DF_REG_DF5_IN,
RANG_OUTPUT_LED_DF_REG_DF5_OUT,
RANG_OUTPUT_LED_DF_REG_DF6_IN,
RANG_OUTPUT_LED_DF_REG_DF6_OUT,
RANG_OUTPUT_LED_DF_REG_DF7_IN,
RANG_OUTPUT_LED_DF_REG_DF7_OUT,
RANG_OUTPUT_LED_DF_REG_DF8_IN,
RANG_OUTPUT_LED_DF_REG_DF8_OUT,
RANG_OUTPUT_LED_DF_REG_DT1_SET,
RANG_OUTPUT_LED_DF_REG_DT1_RESET,
RANG_OUTPUT_LED_DF_REG_DT1_OUT,
RANG_OUTPUT_LED_DF_REG_DT2_SET,
RANG_OUTPUT_LED_DF_REG_DT2_RESET,
RANG_OUTPUT_LED_DF_REG_DT2_OUT,
RANG_OUTPUT_LED_DF_REG_DT3_SET,
RANG_OUTPUT_LED_DF_REG_DT3_RESET,
RANG_OUTPUT_LED_DF_REG_DT3_OUT,
RANG_OUTPUT_LED_DF_REG_DT4_SET,
RANG_OUTPUT_LED_DF_REG_DT4_RESET,
RANG_OUTPUT_LED_DF_REG_DT4_OUT,
RANG_OUTPUT_LED_DF_REG_DVERI_SHAFY_UPR_VIDKR,
RANG_OUTPUT_LED_DF_REG_ACUMUL_BATAREJA_ROZRJADGENA,
RANG_OUTPUT_LED_DF_REG_REZERVTE_GYVLENNJA,
RANG_OUTPUT_LED_DF_REG_BLOCK_VKL_VV,
RANG_OUTPUT_LED_DF_REG_RESET_LEDS,
RANG_OUTPUT_LED_DF_REG_RESET_RELES,
RANG_OUTPUT_LED_DF_REG_MISCEVE_DYSTANCIJNE,
RANG_OUTPUT_LED_DF_REG_STATE_VV,
RANG_OUTPUT_LED_DF_REG_OTKL_VID_ZOVN_ZAHYSTIV,
RANG_OUTPUT_LED_DF_REG_VKL_VV,
RANG_OUTPUT_LED_DF_REG_CTRL_VKL,
RANG_OUTPUT_LED_DF_REG_OTKL_VV,
RANG_OUTPUT_LED_DF_REG_CTRL_OTKL,
RANG_OUTPUT_LED_DF_REG_PRYVID_VV,
RANG_OUTPUT_LED_DF_REG_PEREVYSHCHENNJA_Inom_VYMK,
RANG_OUTPUT_LED_DF_REG_KRYTYCHNYJ_RESURS_VYMYKACHA,
RANG_OUTPUT_LED_DF_REG_VYCHERPANYJ_RESURS_VYMYKACHA,
RANG_OUTPUT_LED_DF_REG_DEFECT,
RANG_OUTPUT_LED_DF_REG_AVAR_DEFECT,
RANG_OUTPUT_LED_DF_REG_WORK_A_REJESTRATOR,
RANG_OUTPUT_LED_DF_REG_WORK_D_REJESTRATOR,
RANG_OUTPUT_LED_DF_REG_VIDKL_VID_ZAKHYSTIV,
RANG_OUTPUT_LED_DF_REG_WORK_BO,
RANG_OUTPUT_LED_DF_REG_WORK_BV,
RANG_OUTPUT_LED_DF_REG_1_GRUPA_USTAVOK,
RANG_OUTPUT_LED_DF_REG_2_GRUPA_USTAVOK,
RANG_OUTPUT_LED_DF_REG_3_GRUPA_USTAVOK,
RANG_OUTPUT_LED_DF_REG_4_GRUPA_USTAVOK,
RANG_OUTPUT_LED_DF_REG_INVERS_DV_GRUPA_USTAVOK,
RANG_OUTPUT_LED_DF_REG_BLK_GRUP_USTAVOK_VID_ZACHYSTIV,
RANG_OUTPUT_LED_DF_REG_RESET_BLOCK_READY_TU_VID_ZAHYSTIV,
RANG_OUTPUT_LED_DF_REG_READY_TU,

RANG_OUTPUT_LED_DF_REG_BLOCK_MTZ1,
RANG_OUTPUT_LED_DF_REG_BLOCK_MTZ2,
RANG_OUTPUT_LED_DF_REG_BLOCK_USK_MTZ2,
RANG_OUTPUT_LED_DF_REG_BLOCK_MTZ3,
RANG_OUTPUT_LED_DF_REG_BLOCK_MTZ4,
RANG_OUTPUT_LED_DF_REG_SECTOR_VPERED_MTZN1,
RANG_OUTPUT_LED_DF_REG_SECTOR_NAZAD_MTZN1,
RANG_OUTPUT_LED_DF_REG_PO_MTZ1,
RANG_OUTPUT_LED_DF_REG_PO_MTZN1_VPERED,
RANG_OUTPUT_LED_DF_REG_PO_MTZN1_NAZAD,
RANG_OUTPUT_LED_DF_REG_PO_U_MTZPN1,
RANG_OUTPUT_LED_DF_REG_PO_MTZPN1,
RANG_OUTPUT_LED_DF_REG_MTZ1,
RANG_OUTPUT_LED_DF_REG_SECTOR_VPERED_MTZN2,
RANG_OUTPUT_LED_DF_REG_SECTOR_NAZAD_MTZN2,
RANG_OUTPUT_LED_DF_REG_PO_MTZ2,
RANG_OUTPUT_LED_DF_REG_PO_MTZN2_VPERED,
RANG_OUTPUT_LED_DF_REG_PO_MTZN2_NAZAD,
RANG_OUTPUT_LED_DF_REG_PO_U_MTZPN2,
RANG_OUTPUT_LED_DF_REG_PO_MTZPN2,
RANG_OUTPUT_LED_DF_REG_MTZ2,
RANG_OUTPUT_LED_DF_REG_SECTOR_VPERED_MTZN3,
RANG_OUTPUT_LED_DF_REG_SECTOR_NAZAD_MTZN3,
RANG_OUTPUT_LED_DF_REG_PO_MTZ3,
RANG_OUTPUT_LED_DF_REG_PO_MTZN3_VPERED,
RANG_OUTPUT_LED_DF_REG_PO_MTZN3_NAZAD,
RANG_OUTPUT_LED_DF_REG_PO_U_MTZPN3,
RANG_OUTPUT_LED_DF_REG_PO_MTZPN3,
RANG_OUTPUT_LED_DF_REG_MTZ3,
RANG_OUTPUT_LED_DF_REG_SECTOR_VPERED_MTZN4,
RANG_OUTPUT_LED_DF_REG_SECTOR_NAZAD_MTZN4,
RANG_OUTPUT_LED_DF_REG_PO_MTZ4,
RANG_OUTPUT_LED_DF_REG_PO_MTZN4_VPERED,
RANG_OUTPUT_LED_DF_REG_PO_MTZN4_NAZAD,
RANG_OUTPUT_LED_DF_REG_PO_U_MTZPN4,
RANG_OUTPUT_LED_DF_REG_PO_MTZPN4,
RANG_OUTPUT_LED_DF_REG_MTZ4,
RANG_OUTPUT_LED_DF_REG_PO_BLOCK_U_MTZN,
RANG_OUTPUT_LED_DF_REG_NCN_MTZ,

RANG_OUTPUT_LED_DF_REG_PUSK_ZDZ_VID_DV,
RANG_OUTPUT_LED_DF_REG_ZDZ,

RANG_OUTPUT_LED_DF_REG_BLOCK_NZZ,
RANG_OUTPUT_LED_DF_REG_PO_NZZ,
RANG_OUTPUT_LED_DF_REG_NZZ,
RANG_OUTPUT_LED_DF_REG_PO_3I0,
RANG_OUTPUT_LED_DF_REG_3I0,
RANG_OUTPUT_LED_DF_REG_PO_3U0,
RANG_OUTPUT_LED_DF_REG_3U0,
RANG_OUTPUT_LED_DF_REG_SECTOR_NZZ,

RANG_OUTPUT_LED_DF_REG_STAT_BLK_APV,
RANG_OUTPUT_LED_DF_REG_APV1,
RANG_OUTPUT_LED_DF_REG_APV2,
RANG_OUTPUT_LED_DF_REG_APV3,
RANG_OUTPUT_LED_DF_REG_APV4,
RANG_OUTPUT_LED_DF_REG_APV_WORK,

RANG_OUTPUT_LED_DF_REG_RESET_BLOCK_APV_ZMN,
RANG_OUTPUT_LED_DF_REG_BLOCK_APV_ZMN,
RANG_OUTPUT_LED_DF_REG_BLOCK_KRATN_APV_ZMN,
RANG_OUTPUT_LED_DF_REG_BLOCK_APV_ZMN_VID_ZAKHYSTIV,
RANG_OUTPUT_LED_DF_REG_PO_UAPV_ZMN1,
RANG_OUTPUT_LED_DF_REG_PO_UAPV_ZMN2,
RANG_OUTPUT_LED_DF_REG_PO_APV_ZMN,
RANG_OUTPUT_LED_DF_REG_APV_ZMN,

RANG_OUTPUT_LED_DF_REG_BLOCK_ACHR,
RANG_OUTPUT_LED_DF_REG_RAZR_CHAPV,
RANG_OUTPUT_LED_DF_REG_BLOCK_CHAPV_VID_U,
RANG_OUTPUT_LED_DF_REG_PO_F1_ACHR,
RANG_OUTPUT_LED_DF_REG_F1_ACHR_CHAPV,
RANG_OUTPUT_LED_DF_REG_PO_F2_ACHR,
RANG_OUTPUT_LED_DF_REG_F2_ACHR_CHAPV,
RANG_OUTPUT_LED_DF_REG_ACHR_CHAPV,
RANG_OUTPUT_LED_DF_REG_PO_F1_CHAPV,
RANG_OUTPUT_LED_DF_REG_PO_F2_CHAPV,
RANG_OUTPUT_LED_DF_REG_ACHR_CHAPV_VID_DV,

RANG_OUTPUT_LED_DF_REG_PUSK_UROV_VID_DV,
RANG_OUTPUT_LED_DF_REG_PO_UROV,
RANG_OUTPUT_LED_DF_REG_UROV1,
RANG_OUTPUT_LED_DF_REG_UROV2,

RANG_OUTPUT_LED_DF_REG_BLOCK_ZOP,
RANG_OUTPUT_LED_DF_REG_PO_ZOP,
RANG_OUTPUT_LED_DF_REG_ZOP,

RANG_OUTPUT_LED_DF_REG_BLOCK_UMIN1,
RANG_OUTPUT_LED_DF_REG_START_UMIN1,
RANG_OUTPUT_LED_DF_REG_BLOCK_UMIN2,
RANG_OUTPUT_LED_DF_REG_START_UMIN2,
RANG_OUTPUT_LED_DF_REG_PO_UMIN1,
RANG_OUTPUT_LED_DF_REG_PO_UBLK_UMIN1,
RANG_OUTPUT_LED_DF_REG_PO_IBLK_UMIN1,
RANG_OUTPUT_LED_DF_REG_UMIN1,
RANG_OUTPUT_LED_DF_REG_PO_UMIN2,
RANG_OUTPUT_LED_DF_REG_PO_UBLK_UMIN2,
RANG_OUTPUT_LED_DF_REG_PO_IBLK_UMIN2,
RANG_OUTPUT_LED_DF_REG_UMIN2,

RANG_OUTPUT_LED_DF_REG_BLOCK_UMAX1,
RANG_OUTPUT_LED_DF_REG_PO_UMAX1,
RANG_OUTPUT_LED_DF_REG_UMAX1,
RANG_OUTPUT_LED_DF_REG_BLOCK_UMAX2,
RANG_OUTPUT_LED_DF_REG_PO_UMAX2,
RANG_OUTPUT_LED_DF_REG_UMAX2,

RANG_OUTPUT_LED_DF_REG_OTKL_AVR,
RANG_OUTPUT_LED_DF_REG_SBROS_BLOCK_AVR,
RANG_OUTPUT_LED_DF_REG_STAT_BLOCK_AVR,
RANG_OUTPUT_LED_DF_REG_BLOCK_AVR_VID_ZAKHYSTIV,
RANG_OUTPUT_LED_DF_REG_PO_UAVR_MIN1,
RANG_OUTPUT_LED_DF_REG_PO_UAVR_MAX1,
RANG_OUTPUT_LED_DF_REG_PO_UAVR_MIN2,
RANG_OUTPUT_LED_DF_REG_PO_UAVR_MAX2,
RANG_OUTPUT_LED_DF_REG_BLOCK_KRATN_AVR,
RANG_OUTPUT_LED_DF_REG_PUSK_AVR,
RANG_OUTPUT_LED_DF_REG_PUSK_AVR_1,
RANG_OUTPUT_LED_DF_REG_PUSK_AVR_2,

RANG_OUTPUT_LED_DF_REG_PO_U_OL,
RANG_OUTPUT_LED_DF_REG_U_OL,
RANG_OUTPUT_LED_DF_REG_PO_U_RL,
RANG_OUTPUT_LED_DF_REG_U_RL
};

#define NUMBER_GENERAL_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG     60
#define NUMBER_MTZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG         39
#define NUMBER_ZDZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG         2
#define NUMBER_ZZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG          8
#define NUMBER_APV_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG         6
#define NUMBER_APV_ZMN_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG     8
#define NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG  11
#define NUMBER_UROV_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG        4
#define NUMBER_ZOP_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG         3
#define NUMBER_UMIN_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG        12
#define NUMBER_UMAX_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG        6
#define NUMBER_AVR_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG         12
#define NUMBER_CONTROL_U_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG   4
#define NUMBER_VMP_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG         0

#define NUMBER_TOTAL_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG       (                                                      \
                                                              NUMBER_GENERAL_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG    + \
                                                              NUMBER_MTZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG        + \
                                                              NUMBER_ZDZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG        + \
                                                              NUMBER_ZZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG         + \
                                                              NUMBER_APV_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG        + \
                                                              NUMBER_APV_ZMN_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG    + \
                                                              NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + \
                                                              NUMBER_UROV_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG       + \
                                                              NUMBER_ZOP_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG        + \
                                                              NUMBER_UMIN_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG       + \
                                                              NUMBER_UMAX_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG       + \
                                                              NUMBER_AVR_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG        + \
                                                              NUMBER_CONTROL_U_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG  + \
                                                              NUMBER_VMP_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG          \
                                                             ) 

/*****************************************/

enum __mtz_const {
  RANG_OUTPUT_LED_DF_REG_BLOCK_MTZ = 0,
  RANG_OUTPUT_LED_DF_REG_BLOCK_USK_MTZ,
  RANG_OUTPUT_LED_DF_REG_SECTOR_VPERED_MTZN,
  RANG_OUTPUT_LED_DF_REG_SECTOR_NAZAD_MTZN,
  RANG_OUTPUT_LED_DF_REG_PO_MTZ,
  RANG_OUTPUT_LED_DF_REG_PO_MTZN_VPERED,
  RANG_OUTPUT_LED_DF_REG_PO_MTZN_NAZAD,
  RANG_OUTPUT_LED_DF_REG_PO_U_MTZPN,
  RANG_OUTPUT_LED_DF_REG_PO_MTZPN,
  RANG_OUTPUT_LED_DF_REG_MTZ,
  /*************************************/
  MTZ_SETTINGS_LENGTH
};

enum __mtz_levels_const {
  MTZ_LEVEL1 = 0,
  MTZ_LEVEL2,
  MTZ_LEVEL3,
  MTZ_LEVEL4,
  /*************************************/
  NUMBER_LEVEL_MTZ //Количество ступеней МТЗ
};

enum __mtz_abc_const {
  PHASE_A_INDEX = 0,
  PHASE_B_INDEX,
  PHASE_C_INDEX
};

enum __mtz_abc_direction_const {
  MTZ_NEVYZN = 0,
  MTZ_VPERED,
  MTZ_NAZAD
};

/*****************************************/
//Макски деяких сигналів сигналівяких треба брати попередній тсан
/*****************************************/
#define MASKA_FOR_DF_TRIGGERS_SIGNALS_0        (unsigned int)(                   \
     (1 << RANG_OUTPUT_LED_DF_REG_DT1_OUT)                               /*18*/  \
   | (1 << RANG_OUTPUT_LED_DF_REG_DT2_OUT)                               /*21*/  \
   | (1 << RANG_OUTPUT_LED_DF_REG_DT3_OUT)                               /*24*/  \
   | (1 << RANG_OUTPUT_LED_DF_REG_DT4_OUT)                               /*27*/  \
)     
#define MASKA_FOR_DF_TRIGGERS_SIGNALS_1                  0
#define MASKA_FOR_DF_TRIGGERS_SIGNALS_2                  0
#define MASKA_FOR_DF_TRIGGERS_SIGNALS_3                  0
#define MASKA_FOR_DF_TRIGGERS_SIGNALS_4                  0
#define MASKA_FOR_DF_TRIGGERS_SIGNALS_5                  0

#define MASKA_FOR_ON_OFF_SIGNALS_0                       0
#define MASKA_FOR_ON_OFF_SIGNALS_1        (unsigned int)(                        \
     (1 << (RANG_OUTPUT_LED_DF_REG_VIDKL_VID_ZAKHYSTIV - 32))            /*49*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_WORK_BO - 32))                        /*50*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_WORK_BV - 32))                        /*51*/  \
)     
#define MASKA_FOR_ON_OFF_SIGNALS_2                       0
#define MASKA_FOR_ON_OFF_SIGNALS_3                       0
#define MASKA_FOR_ON_OFF_SIGNALS_4                       0
#define MASKA_FOR_ON_OFF_SIGNALS_5                       0

#define MASKA_FOR_READY_TU_SIGNALS_0                     0
#define MASKA_FOR_READY_TU_SIGNALS_1        (unsigned int)(                      \
     (1 << (RANG_OUTPUT_LED_DF_REG_READY_TU - 32))                       /*59*/  \
)
#define MASKA_FOR_READY_TU_SIGNALS_2                     0
#define MASKA_FOR_READY_TU_SIGNALS_3                     0
#define MASKA_FOR_READY_TU_SIGNALS_4                     0
#define MASKA_FOR_READY_TU_SIGNALS_5                     0

#define MASKA_FOR_RESURS_VV_SIGNALS_0                    0
#define MASKA_FOR_RESURS_VV_SIGNALS_1     (unsigned int)(                        \
     (1 << (RANG_OUTPUT_LED_DF_REG_PEREVYSHCHENNJA_Inom_VYMK - 32))      /*42*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_KRYTYCHNYJ_RESURS_VYMYKACHA - 32))    /*43*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_VYCHERPANYJ_RESURS_VYMYKACHA - 32))   /*44*/  \
)
#define MASKA_FOR_RESURS_VV_SIGNALS_2                    0
#define MASKA_FOR_RESURS_VV_SIGNALS_3                    0
#define MASKA_FOR_RESURS_VV_SIGNALS_4                    0
#define MASKA_FOR_RESURS_VV_SIGNALS_5                    0

#define MASKA_FOR_REJESTRATORS_AND_DEFECT_SIGNALS_0      0
#define MASKA_FOR_REJESTRATORS_AND_DEFECT_SIGNALS_1     (unsigned int)(          \
     (1 << (RANG_OUTPUT_LED_DF_REG_DEFECT - 32))                         /*45*/ /*Загальна несправність встановлюватися може коли є нештатна робота реєстраторів, тому я її включив у цю групу. Всі інші несправностей у тому числі і фіксацію аварійної несправності визначається у програмі до запуску логіки, тому попередній стан брати не треба. Для загальної несправності, думаю, не буде нічого страгного, якщо будемо брати теперішнє і попереднє значення*/\
   | (1 << (RANG_OUTPUT_LED_DF_REG_WORK_A_REJESTRATOR - 32))             /*47*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_WORK_D_REJESTRATOR - 32))             /*48*/  \
)
#define MASKA_FOR_REJESTRATORS_AND_DEFECT_SIGNALS_2      0
#define MASKA_FOR_REJESTRATORS_AND_DEFECT_SIGNALS_3      0
#define MASKA_FOR_REJESTRATORS_AND_DEFECT_SIGNALS_4      0
#define MASKA_FOR_REJESTRATORS_AND_DEFECT_SIGNALS_5      0
/*****************************************/

/*****************************************/
//Макска сигналів, які мають записуватися у енергонезалежну пам'ять
/*****************************************/
#define MASKA_TRIGGER_SIGNALES_0               (unsigned int)(                   \
     (1 << RANG_OUTPUT_LED_DF_REG_DT1_OUT)                               /*18*/  \
   | (1 << RANG_OUTPUT_LED_DF_REG_DT2_OUT)                               /*21*/  \
   | (1 << RANG_OUTPUT_LED_DF_REG_DT3_OUT)                               /*24*/  \
   | (1 << RANG_OUTPUT_LED_DF_REG_DT4_OUT)                               /*27*/  \
)     

#define MASKA_TRIGGER_SIGNALES_1                  0
#define MASKA_TRIGGER_SIGNALES_2                  0

#define MASKA_TRIGGER_SIGNALES_3               (unsigned int)(                   \
     (1 << (RANG_OUTPUT_LED_DF_REG_BLOCK_KRATN_APV_ZMN - 96))           /*117*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_BLOCK_APV_ZMN_VID_ZAKHYSTIV - 96))   /*118*/  \
)

#define MASKA_TRIGGER_SIGNALES_4                  0

#define MASKA_TRIGGER_SIGNALES_5               (unsigned int)(                   \
     (1 << (RANG_OUTPUT_LED_DF_REG_BLOCK_AVR_VID_ZAKHYSTIV - 160))      /*162*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_BLOCK_KRATN_AVR         - 160))      /*167*/  \
)
/*****************************************/

/*****************************************/
//Макска інформативних сигналів
/*****************************************/
#define MASKA_INFO_SIGNALES_0                          (unsigned int)(  \
     (1 << RANG_OUTPUT_LED_DF_REG_DVERI_SHAFY_UPR_VIDKR)        /*28*/  \
   | (1 << RANG_OUTPUT_LED_DF_REG_ACUMUL_BATAREJA_ROZRJADGENA)  /*29*/  \
   | (1 << RANG_OUTPUT_LED_DF_REG_REZERVTE_GYVLENNJA)           /*30*/  \
)     

#define MASKA_INFO_SIGNALES_1                  (unsigned int)(         \
     (1 << (RANG_OUTPUT_LED_DF_REG_STATE_VV - 32))             /*35*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_DEFECT - 32))               /*45*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_AVAR_DEFECT - 32))          /*46*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_WORK_A_REJESTRATOR - 32))   /*47*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_WORK_D_REJESTRATOR - 32))   /*48*/  \
)     
#define MASKA_INFO_SIGNALES_2                  0
#define MASKA_INFO_SIGNALES_3                  0
#define MASKA_INFO_SIGNALES_4                  0
#define MASKA_INFO_SIGNALES_5                  0
/*****************************************/

/*****************************************/
/*
Макска для дискретного реєстратора, яка визначає, при активності яких функцій продовжувати утримувати дискретний реєстратор у активному стані
(якщо) він вже є активним до цього часу
*/
/*****************************************/
#define MASKA_FOR_CONTINUE_GET_DR_ACTINE_WORD_0        0

#define MASKA_FOR_CONTINUE_GET_DR_ACTINE_WORD_1 (unsigned int)(          \
     (1 << (RANG_OUTPUT_LED_DF_REG_OTKL_VID_ZOVN_ZAHYSTIV - 32))/* 36*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_VKL_VV - 32))                /* 37*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_OTKL_VV - 32))               /* 39*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_VIDKL_VID_ZAKHYSTIV - 32))   /* 49*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_WORK_BO - 32))               /* 50*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_WORK_BV - 32))               /* 51*/  \
)  

#define MASKA_FOR_CONTINUE_GET_DR_ACTINE_WORD_2 (unsigned int)(          \
     (1 << (RANG_OUTPUT_LED_DF_REG_PO_MTZ1 - 64))               /* 67*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_PO_MTZN1_VPERED - 64))       /* 68*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_PO_MTZN1_NAZAD - 64))        /* 69*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_PO_MTZPN1 - 64))             /* 71*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_MTZ1 - 64))                  /* 72*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_PO_MTZ2 - 64))               /* 75*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_PO_MTZN2_VPERED - 64))       /* 76*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_PO_MTZN2_NAZAD - 64))        /* 77*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_PO_MTZPN2 - 64))             /* 79*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_MTZ2 - 64))                  /* 80*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_PO_MTZ3 - 64))               /* 83*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_PO_MTZN3_VPERED - 64))       /* 84*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_PO_MTZN3_NAZAD - 64))        /* 85*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_PO_MTZPN3 - 64))             /* 87*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_MTZ3 - 64))                  /* 88*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_PO_MTZ4 - 64))               /* 91*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_PO_MTZN4_VPERED - 64))       /* 92*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_PO_MTZN4_NAZAD - 64))        /* 93*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_PO_MTZPN4 - 64))             /* 95*/  \
)            

#define MASKA_FOR_CONTINUE_GET_DR_ACTINE_WORD_3 (unsigned int)(          \
     (1 << (RANG_OUTPUT_LED_DF_REG_MTZ4 - 96))                  /* 96*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_PO_NZZ - 96))                /*102*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_NZZ - 96))                   /*103*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_PO_3I0 - 96))                /*104*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_3I0 - 96))                   /*105*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_APV1 - 96))                  /*110*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_APV2 - 96))                  /*111*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_APV3 - 96))                  /*112*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_APV4 - 96))                  /*113*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_APV_WORK - 96))              /*114*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_PO_APV_ZMN - 96))            /*121*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_APV_ZMN - 96))               /*122*/  \
)  

#define MASKA_FOR_CONTINUE_GET_DR_ACTINE_WORD_4 (unsigned int)(          \
     (1 << (RANG_OUTPUT_LED_DF_REG_PUSK_UROV_VID_DV - 128))     /*134*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_PO_UROV - 128))              /*135*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_UROV1 - 128))                /*136*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_UROV2 - 128))                /*137*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_PO_ZOP - 128))               /*139*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_ZOP - 128))                  /*140*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_PO_UMAX1 - 128))             /*154*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_UMAX1 - 128))                /*155*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_PO_UMAX2 - 128))             /*157*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_UMAX2 - 128))                /*158*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_OTKL_AVR - 128))             /*159*/  \
)  

#define MASKA_FOR_CONTINUE_GET_DR_ACTINE_WORD_5 (unsigned int)(          \
     (1 << (RANG_OUTPUT_LED_DF_REG_SBROS_BLOCK_AVR - 160))       /*160*/ \
   | (1 << (RANG_OUTPUT_LED_DF_REG_PUSK_AVR - 160))              /*168*/ \
)
/*****************************************/

/*****************************************/
//Макска моніторингу максимального фазного струму для дискретного реєстратора
/*****************************************/
#define MASKA_MONITOTYNG_PHASE_SIGNALES_0        0
#define MASKA_MONITOTYNG_PHASE_SIGNALES_1        0

#define MASKA_MONITOTYNG_PHASE_SIGNALES_2 (unsigned int)(                \
     (1 << (RANG_OUTPUT_LED_DF_REG_PO_MTZ1 - 64))               /* 67*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_PO_MTZN1_VPERED - 64))       /* 68*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_PO_MTZN1_NAZAD - 64))        /* 69*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_PO_MTZPN1 - 64))             /* 71*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_MTZ1 - 64))                  /* 72*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_PO_MTZ2 - 64))               /* 75*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_PO_MTZN2_VPERED - 64))       /* 76*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_PO_MTZN2_NAZAD - 64))        /* 77*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_PO_MTZPN2 - 64))             /* 79*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_MTZ2 - 64))                  /* 80*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_PO_MTZ3 - 64))               /* 83*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_PO_MTZN3_VPERED - 64))       /* 84*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_PO_MTZN3_NAZAD - 64))        /* 85*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_PO_MTZPN3 - 64))             /* 87*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_MTZ3 - 64))                  /* 89*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_PO_MTZ4 - 64))               /* 91*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_PO_MTZN4_VPERED - 64))       /* 92*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_PO_MTZN4_NAZAD - 64))        /* 93*/ \
   | (1 << (RANG_OUTPUT_LED_DF_REG_PO_MTZPN4 - 64))             /* 95*/ \
)

#define MASKA_MONITOTYNG_PHASE_SIGNALES_3 (unsigned int)(               \
     (1 << (RANG_OUTPUT_LED_DF_REG_MTZ4 - 96))                  /* 96*/ \
)
#define MASKA_MONITOTYNG_PHASE_SIGNALES_4        0
#define MASKA_MONITOTYNG_PHASE_SIGNALES_5        0
/*****************************************/

/*****************************************/
//Макска моніторингу максимального струму 3I0 для дискретного реєстратора
/*****************************************/
#define MASKA_MONITOTYNG_3I0_SIGNALES_0        0
#define MASKA_MONITOTYNG_3I0_SIGNALES_1        0
#define MASKA_MONITOTYNG_3I0_SIGNALES_2        0

#define MASKA_MONITOTYNG_3I0_SIGNALES_3        (unsigned int)(   \
     (1 << (RANG_OUTPUT_LED_DF_REG_PO_NZZ - 96))        /*102*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_NZZ - 96))           /*103*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_PO_3I0 - 96))        /*104*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_3I0 - 96))           /*105*/  \
)            

#define MASKA_MONITOTYNG_3I0_SIGNALES_4        0
#define MASKA_MONITOTYNG_3I0_SIGNALES_5        0
/*****************************************/

/*****************************************/
//Макска моніторингу максимального струму 3U0 для дискретного реєстратора
/*****************************************/
#define MASKA_MONITOTYNG_3U0_SIGNALES_0        0
#define MASKA_MONITOTYNG_3U0_SIGNALES_1        0
#define MASKA_MONITOTYNG_3U0_SIGNALES_2        0

#define MASKA_MONITOTYNG_3U0_SIGNALES_3        (unsigned int)(   \
     (1 << (RANG_OUTPUT_LED_DF_REG_PO_NZZ - 96))        /*102*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_NZZ - 96))           /*103*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_PO_3U0 - 96))        /*106*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_3U0 - 96))           /*107*/  \
)            

#define MASKA_MONITOTYNG_3U0_SIGNALES_4        0       
#define MASKA_MONITOTYNG_3U0_SIGNALES_5        0
/*****************************************/

/*****************************************/
//Макска моніторингу Umin для дискретного реєстратора
/*****************************************/
#define MASKA_MONITOTYNG_UMIN_SIGNALES_0        0
#define MASKA_MONITOTYNG_UMIN_SIGNALES_1        0
#define MASKA_MONITOTYNG_UMIN_SIGNALES_2        0
#define MASKA_MONITOTYNG_UMIN_SIGNALES_3        0

#define MASKA_MONITOTYNG_UMIN_SIGNALES_4 (unsigned int)(   \
     (1 << (RANG_OUTPUT_LED_DF_REG_PO_UMIN1 - 128))/*145*/ \
   | (1 << (RANG_OUTPUT_LED_DF_REG_UMIN1 - 128))   /*148*/ \
   | (1 << (RANG_OUTPUT_LED_DF_REG_PO_UMIN2 - 128))/*149*/ \
   | (1 << (RANG_OUTPUT_LED_DF_REG_UMIN2 - 128))   /*152*/ \
)

#define MASKA_MONITOTYNG_UMIN_SIGNALES_5        0
/*****************************************/

/*****************************************/
//Макска моніторингу Umax для дискретного реєстратора
/*****************************************/
#define MASKA_MONITOTYNG_UMAX_SIGNALES_0        0
#define MASKA_MONITOTYNG_UMAX_SIGNALES_1        0
#define MASKA_MONITOTYNG_UMAX_SIGNALES_2        0
#define MASKA_MONITOTYNG_UMAX_SIGNALES_3        0

#define MASKA_MONITOTYNG_UMAX_SIGNALES_4 (unsigned int)(   \
     (1 << (RANG_OUTPUT_LED_DF_REG_PO_UMAX1 - 128))/*154*/ \
   | (1 << (RANG_OUTPUT_LED_DF_REG_UMAX1 - 128))   /*155*/ \
   | (1 << (RANG_OUTPUT_LED_DF_REG_PO_UMAX2 - 128))/*157*/ \
   | (1 << (RANG_OUTPUT_LED_DF_REG_UMAX2 - 128))   /*158*/ \
)

#define MASKA_MONITOTYNG_UMAX_SIGNALES_5        0
/*****************************************/

/*****************************************/
//Макска моніторингу максимального струму зворотньої послідовності для дискретного реєстратора
/*****************************************/
#define MASKA_MONITOTYNG_ZOP_SIGNALES_0                  0
#define MASKA_MONITOTYNG_ZOP_SIGNALES_1                  0
#define MASKA_MONITOTYNG_ZOP_SIGNALES_2                  0
#define MASKA_MONITOTYNG_ZOP_SIGNALES_3                  0

#define MASKA_MONITOTYNG_ZOP_SIGNALES_4 (unsigned int)(   \
     (1 << (RANG_OUTPUT_LED_DF_REG_PO_ZOP - 128))/*139*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_ZOP - 128))   /*140*/  \
)

#define MASKA_MONITOTYNG_ZOP_SIGNALES_5                  0
/*****************************************/

/*****************************************/
//Макска моніторингу частоти 1 при АЧР для дискретного реєстратора
/*****************************************/
#define MASKA_MONITOTYNG_F1_MIN_ACHR_SIGNALES_0   0
#define MASKA_MONITOTYNG_F1_MIN_ACHR_SIGNALES_1   0
#define MASKA_MONITOTYNG_F1_MIN_ACHR_SIGNALES_2   0

#define MASKA_MONITOTYNG_F1_MIN_ACHR_SIGNALES_3   (unsigned int)(\
     (1 << (RANG_OUTPUT_LED_DF_REG_PO_F1_ACHR - 96))    /*126*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_F1_ACHR_CHAPV - 96)) /*127*/  \
)     

#define MASKA_MONITOTYNG_F1_MIN_ACHR_SIGNALES_4   0
#define MASKA_MONITOTYNG_F1_MIN_ACHR_SIGNALES_5   0
/*****************************************/

/*****************************************/
//Макска моніторингу частоти 2 при АЧР  для дискретного реєстратора
/*****************************************/
#define MASKA_MONITOTYNG_F2_MIN_ACHR_SIGNALES_0   0
#define MASKA_MONITOTYNG_F2_MIN_ACHR_SIGNALES_1   0
#define MASKA_MONITOTYNG_F2_MIN_ACHR_SIGNALES_2   0
#define MASKA_MONITOTYNG_F2_MIN_ACHR_SIGNALES_3   0

#define MASKA_MONITOTYNG_F2_MIN_ACHR_SIGNALES_4   (unsigned int)( \
     (1 << (RANG_OUTPUT_LED_DF_REG_PO_F2_ACHR - 128))   /*128*/   \
   | (1 << (RANG_OUTPUT_LED_DF_REG_F2_ACHR_CHAPV - 128))/*129*/   \
)     

#define MASKA_MONITOTYNG_F2_MIN_ACHR_SIGNALES_5   0
/*****************************************/

/*****************************************/
//Макска моніторингу максимального фазного для фіксації КЗ
/*****************************************/
#define MASKA_MONITOTYNG_PHASE_SIGNALES_KZ_0        0
#define MASKA_MONITOTYNG_PHASE_SIGNALES_KZ_1        0

#define MASKA_MONITOTYNG_PHASE_SIGNALES_KZ_2 (unsigned int)(             \
     (1 << (RANG_OUTPUT_LED_DF_REG_PO_MTZ1 - 64))               /* 67*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_PO_MTZN1_VPERED - 64))       /* 68*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_PO_MTZN1_NAZAD - 64))        /* 69*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_PO_MTZPN1 - 64))             /* 71*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_PO_MTZ2 - 64))               /* 75*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_PO_MTZN2_VPERED - 64))       /* 76*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_PO_MTZN2_NAZAD - 64))        /* 77*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_PO_MTZPN2 - 64))             /* 79*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_PO_MTZ3 - 64))               /* 83*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_PO_MTZN3_VPERED - 64))       /* 84*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_PO_MTZN3_NAZAD - 64))        /* 85*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_PO_MTZPN3 - 64))             /* 87*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_PO_MTZ4 - 64))               /* 91*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_PO_MTZN4_VPERED - 64))       /* 92*/  \
   | (1 << (RANG_OUTPUT_LED_DF_REG_PO_MTZN4_NAZAD - 64))        /* 93*/ \
   | (1 << (RANG_OUTPUT_LED_DF_REG_PO_MTZPN4 - 64))             /* 95*/ \
)

#define MASKA_MONITOTYNG_PHASE_SIGNALES_KZ_3        0
#define MASKA_MONITOTYNG_PHASE_SIGNALES_KZ_4        0
#define MASKA_MONITOTYNG_PHASE_SIGNALES_KZ_5        0
/*****************************************/


/*****************************************/
//ВІдключення від захистів
/*****************************************/
typedef enum __vymknennja_vid_zakhystiv__
{
  VYMKNENNJA_VID_MTZ1,
  VYMKNENNJA_VID_MTZ2,
  VYMKNENNJA_VID_MTZ3,
  VYMKNENNJA_VID_MTZ4,

  VYMKNENNJA_VID_ZDZ,

  VYMKNENNJA_VID_3I0,
  VYMKNENNJA_VID_3U0,
  VYMKNENNJA_VID_NZZ,

  VYMKNENNJA_VID_ACHR_CHAPV_VID_DV,
  VYMKNENNJA_VID_ACHR_CHAPV,

  VYMKNENNJA_VID_UROV1,
  VYMKNENNJA_VID_UROV2,

  VYMKNENNJA_VID_ZOP,

  VYMKNENNJA_VID_UMIN1,
  VYMKNENNJA_VID_UMIN2,

  VYMKNENNJA_VID_UMAX1,
  VYMKNENNJA_VID_UMAX2,

  VYMKNENNJA_VID_ZOVNISHNIKH_ZAKHYSTIV,
  
  VYMKNENNJA_VID_INSHYKH_SYGNALIV,
    
  VYMKNENNJA_VID_MAX_NUMBER  
  
}__vymknennja_vid_zakhystiv;
/*****************************************/

/*****************************************/
//Максимальна кількість сигналів (функцій), які можуть бути зранжовані на входи/виходи/світлоіндикатори/д.реєстратор/оф
/*****************************************/
#define VAGA_MAX_FUNCTIONS_IN_INPUT             3
#define MAX_FUNCTIONS_IN_INPUT                  (1 << VAGA_MAX_FUNCTIONS_IN_INPUT)
#define VAGA_MAX_FUNCTIONS_IN_OUTPUT            4
#define MAX_FUNCTIONS_IN_OUTPUT                 (1 << VAGA_MAX_FUNCTIONS_IN_OUTPUT)
#define VAGA_MAX_FUNCTIONS_IN_LED               3
#define MAX_FUNCTIONS_IN_LED                    (1 << VAGA_MAX_FUNCTIONS_IN_LED)
#define VAGA_MAX_FUNCTIONS_IN_DF                4
#define MAX_FUNCTIONS_IN_DF                     (1 << VAGA_MAX_FUNCTIONS_IN_DF)
#define MAX_FUNCTIONS_IN_DT                     6
#define VAGA_MAX_FUNCTIONS_IN_DB                3
#define MAX_FUNCTIONS_IN_DB                     (1 << VAGA_MAX_FUNCTIONS_IN_DB)
#define VAGA_MAX_FUNCTIONS_IN_AREG              5
#define MAX_FUNCTIONS_IN_AREG                   (1 << VAGA_MAX_FUNCTIONS_IN_AREG)
#define VAGA_MAX_FUNCTIONS_IN_DREG              5
#define MAX_FUNCTIONS_IN_DREG                   (1 << VAGA_MAX_FUNCTIONS_IN_DREG)
/*****************************************/


/*****************************************/
//Константи для комунікації
/*****************************************/
#define MAX_CHAR_IN_NAME_OF_CELL                              32
/*****************************************/

/*****************************************/
//Константи для фіксації зміни настройок
/*****************************************/
#define CHANGED_ETAP_NONE                                     0
#define CHANGED_ETAP_EXECUTION                                1
#define CHANGED_ETAP_ENDED                                    2
#define CHANGED_ETAP_ENDED_EXTRA_ETAP                         3
/*****************************************/

/*****************************************/
//Константи для ранжування функціональних кнопок
/*****************************************/
enum __odynyci_vymirjuvannja {
INDEX_A = 0,
INDEX_V,
INDEX_SECOND,

NUMBER_ODYNYCI_VYMIRJUVANNJA
};
/*****************************************/

///*****************************************/
////Запуск періодичних задач
///*****************************************/
//#define TEST_SETTINGS_BIT                                     0
//#define TEST_SETTINGS                                         (1 << TEST_SETTINGS_BIT)
//#define TEST_USTUVANNJA_BIT                                   1
//#define TEST_USTUVANNJA                                       (1 << TEST_USTUVANNJA_BIT)
//#define TEST_TRG_FUNC_BIT                                     2
//#define TEST_TRG_FUNC                                         (1 << TEST_TRG_FUNC_BIT)
//#define TEST_TRG_FUNC_LOCK_BIT                                3
//#define TEST_TRG_FUNC_LOCK                                    (1 << TEST_TRG_FUNC_LOCK_BIT)
//#define TEST_INFO_REJESTRATOR_AR_BIT                          4
//#define TEST_INFO_REJESTRATOR_AR                              (1 << TEST_INFO_REJESTRATOR_AR_BIT)
//#define TEST_INFO_REJESTRATOR_AR_LOCK_BIT                     5
//#define TEST_INFO_REJESTRATOR_AR_LOCK                         (1 << TEST_INFO_REJESTRATOR_AR_LOCK_BIT)
//#define TEST_INFO_REJESTRATOR_DR_BIT                          6
//#define TEST_INFO_REJESTRATOR_DR                              (1 << TEST_INFO_REJESTRATOR_DR_BIT)
//#define TEST_INFO_REJESTRATOR_DR_LOCK_BIT                     7
//#define TEST_INFO_REJESTRATOR_DR_LOCK                         (1 << TEST_INFO_REJESTRATOR_DR_LOCK_BIT)
//#define TEST_INFO_REJESTRATOR_PR_ERR_BIT                      8
//#define TEST_INFO_REJESTRATOR_PR_ERR                          (1 << TEST_INFO_REJESTRATOR_PR_ERR_BIT)
//#define TEST_INFO_REJESTRATOR_PR_ERR_LOCK_BIT                 9
//#define TEST_INFO_REJESTRATOR_PR_ERR_LOCK                     (1 << TEST_INFO_REJESTRATOR_PR_ERR_LOCK_BIT)
//#define TEST_RESURS_BIT                                       10
//#define TEST_RESURS                                           (1 << TEST_RESURS_BIT)
//#define TEST_RESURS_LOCK_BIT                                  11
//#define TEST_RESURS_LOCK                                      (1 << TEST_RESURS_LOCK_BIT)
//#define TEST_FLASH_MEMORY_BIT                                 12
//#define TEST_FLASH_MEMORY                                     (1 << TEST_FLASH_MEMORY_BIT)
//#define CALCULATION_ANGLE_BIT                                 13
//#define CALCULATION_ANGLE                                     (1 << CALCULATION_ANGLE_BIT)
//#define CALC_ENERGY_DATA_BIT                                  14
//#define CALC_ENERGY_DATA                                      (1 << CALC_ENERGY_DATA_BIT)
///*****************************************/


/*****************************************/
//Тип входів логічних елементів
/*****************************************/
#define TYPE_INPUT_0_1        0
#define TYPE_INPUT_1_0        1
/*****************************************/


/*****************************************/
//Індетифікатор типу набору юстуючих коефіцієнтів
/*****************************************/
//#define ADJUSTMENT_3I0_IA_IB_IC                             1
//#define ADJUSTMENT_3I0_IA_IC_3U0                            2
#define ADJUSTMENT_3I0_IA_IB_IC_UA_UB_UC_UABTN2             3
#define ADJUSTMENT_ID                                       ADJUSTMENT_3I0_IA_IB_IC_UA_UB_UC_UABTN2
/*****************************************/

/*****************************************/
//Версія програмного забезпечення
/*****************************************/
#define VERSIA_PZ                                             8
#define MODYFIKACIA_VERSII_PZ                                 3
#define ZBIRKA_VERSII_PZ                                      3
/*****************************************/

/*****************************************/
//Час компіляції
/*****************************************/
#define YEAR_VER                                              ((__DATE__[9] != ' ') ? (((__DATE__[9] - 0x30) << 4) | (__DATE__[10] - 0x30)) : (__DATE__[10] - 0x30))
#define MONTH_VER                                             str_to_int_DATE_Mmm()
#define DAY_VER                                               ((__DATE__[4] != ' ') ? (((__DATE__[4] - 0x30) << 4) | (__DATE__[5] - 0x30)) : (__DATE__[5] - 0x30))
#define HOUR_VER                                              (((__TIME__[0] - 0x30) << 4) | (__TIME__[1] - 0x30))
#define MINUTE_VER                                            (((__TIME__[3] - 0x30) << 4) | (__TIME__[4] - 0x30))
#define SECOND_VER                                            (((__TIME__[6] - 0x30) << 4) | (__TIME__[7] - 0x30))
/*****************************************/

/*****************************************/
//Версія універсальної карти памяті
/*****************************************/
#define VERSIA_GMM                                             6
#define MODYFIKACIA_VERSII_GMM                                 2
/*****************************************/
#endif
