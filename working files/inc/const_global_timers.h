#ifndef __CONST_GLOBAL_TIMERS__
#define __CONST_GLOBAL_TIMERS__

#define MAX_VALUE_TIMER_FOR_COUNT_SIGNAL_ACHR_CHAPV            4 //мс - досягнення цього значення є умовою спроби запустити сигнал АПВ (якщо він не блокується)
#define TIMEOUT_ACHR_CHAPV_100MS                               100 //мс
#define TIMEOUT_CHAPV_1MS                                      1
#define TIMEOUT_BLOCK_CHAPV_5MS                                5

#define INDEX_TIMER_INPUT_START                                 0
#define INDEX_TIMER_DF_PROLONG_SET_FOR_BUTTON_INTERFACE_START  (INDEX_TIMER_INPUT_START + NUMBER_INPUTS)
#define INDEX_TIMER_DF_PAUSE_START                             (INDEX_TIMER_DF_PROLONG_SET_FOR_BUTTON_INTERFACE_START + NUMBER_DEFINED_FUNCTIONS)
#define INDEX_TIMER_DF_WORK_START                              (INDEX_TIMER_DF_PAUSE_START + NUMBER_DEFINED_FUNCTIONS)
#define INDEX_TIMER_MTZ1                                       (INDEX_TIMER_DF_WORK_START + NUMBER_DEFINED_FUNCTIONS)
#define INDEX_TIMER_MTZ1_N_VPERED                              (INDEX_TIMER_MTZ1 + 1)
#define INDEX_TIMER_MTZ1_N_NAZAD                               (INDEX_TIMER_MTZ1_N_VPERED + 1)
#define INDEX_TIMER_MTZ1_PO_NAPRUZI                            (INDEX_TIMER_MTZ1_N_NAZAD + 1)
#define INDEX_TIMER_MTZ2                                       (INDEX_TIMER_MTZ1_PO_NAPRUZI + 1)
#define INDEX_TIMER_MTZ2_DEPENDENT                             (INDEX_TIMER_MTZ2 + 1)
#define INDEX_TIMER_MTZ2_PR                                    (INDEX_TIMER_MTZ2_DEPENDENT + 1)
#define INDEX_TIMER_MTZ2_N_VPERED                              (INDEX_TIMER_MTZ2_PR + 1)
#define INDEX_TIMER_MTZ2_N_VPERED_PR                           (INDEX_TIMER_MTZ2_N_VPERED + 1)
#define INDEX_TIMER_MTZ2_N_NAZAD                               (INDEX_TIMER_MTZ2_N_VPERED_PR + 1)
#define INDEX_TIMER_MTZ2_N_NAZAD_PR                            (INDEX_TIMER_MTZ2_N_NAZAD + 1)
#define INDEX_TIMER_MTZ2_PO_NAPRUZI                            (INDEX_TIMER_MTZ2_N_NAZAD_PR + 1)
#define INDEX_TIMER_MTZ2_PO_NAPRUZI_PR                         (INDEX_TIMER_MTZ2_PO_NAPRUZI + 1)
#define INDEX_TIMER_MTZ2_VVID_PR                               (INDEX_TIMER_MTZ2_PO_NAPRUZI_PR + 1)
#define INDEX_TIMER_MTZ3                                       (INDEX_TIMER_MTZ2_VVID_PR + 1)
#define INDEX_TIMER_MTZ3_N_VPERED                              (INDEX_TIMER_MTZ3 + 1)
#define INDEX_TIMER_MTZ3_N_NAZAD                               (INDEX_TIMER_MTZ3_N_VPERED + 1)
#define INDEX_TIMER_MTZ3_PO_NAPRUZI                            (INDEX_TIMER_MTZ3_N_NAZAD + 1)
#define INDEX_TIMER_MTZ4                                       (INDEX_TIMER_MTZ3_PO_NAPRUZI + 1)
#define INDEX_TIMER_MTZ4_N_VPERED                              (INDEX_TIMER_MTZ4 + 1)
#define INDEX_TIMER_MTZ4_N_NAZAD                               (INDEX_TIMER_MTZ4_N_VPERED + 1)
#define INDEX_TIMER_MTZ4_PO_NAPRUZI                            (INDEX_TIMER_MTZ4_N_NAZAD + 1)
#define INDEX_TIMER_ZZ_3I0                                     (INDEX_TIMER_MTZ4_PO_NAPRUZI + 1)
#define INDEX_TIMER_ZZ_3U0                                     (INDEX_TIMER_ZZ_3I0 + 1)
#define INDEX_TIMER_NZZ                                        (INDEX_TIMER_ZZ_3U0 + 1)
#define INDEX_TIMER_ZOP                                        (INDEX_TIMER_NZZ + 1)
#define INDEX_TIMER_UROV1                                      (INDEX_TIMER_ZOP + 1)
#define INDEX_TIMER_UROV2                                      (INDEX_TIMER_UROV1 + 1)
#define INDEX_TIMER_APV_1                                      (INDEX_TIMER_UROV2 + 1)
#define INDEX_TIMER_APV_2                                      (INDEX_TIMER_APV_1 + 1)
#define INDEX_TIMER_APV_3                                      (INDEX_TIMER_APV_2 + 1)
#define INDEX_TIMER_APV_4                                      (INDEX_TIMER_APV_3 + 1)
#define INDEX_TIMER_APV_BLOCK_VID_APV1                         (INDEX_TIMER_APV_4 + 1)
#define INDEX_TIMER_APV_BLOCK_VID_APV2                         (INDEX_TIMER_APV_BLOCK_VID_APV1 + 1)
#define INDEX_TIMER_APV_BLOCK_VID_APV3                         (INDEX_TIMER_APV_BLOCK_VID_APV2 + 1)
#define INDEX_TIMER_APV_BLOCK_VID_APV4                         (INDEX_TIMER_APV_BLOCK_VID_APV3 + 1)
#define INDEX_TIMER_APV_BLOCK_VID_VV                           (INDEX_TIMER_APV_BLOCK_VID_APV4 + 1)
#define INDEX_TIMER_APV_TMP1                                   (INDEX_TIMER_APV_BLOCK_VID_VV + 1)
#define INDEX_TIMER_ACHR_CHAPV                                 (INDEX_TIMER_APV_TMP1 + 1)
#define INDEX_TIMER_VIDKL_VV                                   (INDEX_TIMER_ACHR_CHAPV + 1)
#define INDEX_TIMER_BLK_VKL_VV                                 (INDEX_TIMER_VIDKL_VV + 1)
#define INDEX_TIMER_VKL_VV                                     (INDEX_TIMER_BLK_VKL_VV + 1)
#define INDEX_TIMER_PRYVOD_VV                                  (INDEX_TIMER_VKL_VV + 1)
#define INDEX_TIMER_UMIN1                                      (INDEX_TIMER_PRYVOD_VV + 1)
#define INDEX_TIMER_UMIN2                                      (INDEX_TIMER_UMIN1 + 1)
#define INDEX_TIMER_UMAX1                                      (INDEX_TIMER_UMIN2 + 1)
#define INDEX_TIMER_UMAX2                                      (INDEX_TIMER_UMAX1 + 1)
#define INDEX_TIMER_APV_ZMN1                                   (INDEX_TIMER_UMAX2 + 1)
#define INDEX_TIMER_APV_ZMN2                                   (INDEX_TIMER_APV_ZMN1 + 1)
#define INDEX_TIMER_APV_ZMN3                                   (INDEX_TIMER_APV_ZMN2 + 1)
#define INDEX_TIMER_AVR_RESET_BLK                              (INDEX_TIMER_APV_ZMN3 + 1)
#define INDEX_TIMER_AVR_ZAVERSHENNJA                           (INDEX_TIMER_AVR_RESET_BLK + 1)
#define INDEX_TIMER_AVR_RL                                     (INDEX_TIMER_AVR_ZAVERSHENNJA + 1)
#define INDEX_TIMER_AVR_OL                                     (INDEX_TIMER_AVR_RL + 1)
#define INDEX_TIMER_ACHR_CHAPV_100MS_1                         (INDEX_TIMER_AVR_OL + 1)
#define INDEX_TIMER_ACHR_CHAPV_100MS_2                         (INDEX_TIMER_ACHR_CHAPV_100MS_1 + 1)
#define INDEX_TIMER_CHAPV_1MS                                  (INDEX_TIMER_ACHR_CHAPV_100MS_2 + 1)
#define INDEX_TIMER_BLOCK_CHAPV_5MS                            (INDEX_TIMER_CHAPV_1MS + 1)
#define INDEX_TIMER_ACHR1                                      (INDEX_TIMER_BLOCK_CHAPV_5MS + 1)
#define INDEX_TIMER_CHAPV1                                     (INDEX_TIMER_ACHR1 + 1)
#define INDEX_TIMER_ACHR2                                      (INDEX_TIMER_CHAPV1 + 1)
#define INDEX_TIMER_CHAPV2                                     (INDEX_TIMER_ACHR2 + 1)
#define INDEX_TIMER_U_OL1                                      (INDEX_TIMER_CHAPV2 + 1)
#define INDEX_TIMER_U_OL2                                      (INDEX_TIMER_U_OL1 + 1)
#define INDEX_TIMER_U_RL1                                      (INDEX_TIMER_U_OL2 + 1)
#define INDEX_TIMER_U_RL2                                      (INDEX_TIMER_U_RL1 + 1)
#define NEXT_TIMER                                             (INDEX_TIMER_U_RL2 + 1)

enum __mtz_tmr_const {
  INDEX_TIMER_MTZ = 0,
  INDEX_TIMER_MTZ_N_VPERED,
  INDEX_TIMER_MTZ_N_NAZAD,
  INDEX_TIMER_MTZ_PO_NAPRUZI,
  /*************************************/
  NUMBER_LEVEL_TMR_CONST
};

#define MAX_NUMBER_GLOBAL_TIMERS                               NEXT_TIMER   //Максимальна кількість таймерів

#endif
