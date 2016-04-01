#ifndef __CONST_MENU_CHOSE_EXTRA_SETTINGS__
#define __CONST_MENU_CHOSE_EXTRA_SETTINGS__

#define EKRAN_CHOSE_EXTRA_SETTINGS        (EKRAN_LEVEL_SET_NEW_PASSWORD2 + 1)

#define MAX_ROW_FOR_CHOSE_EXTRA_SETTINGS  7

#define INDEX_ML_CTREXTRA_SETTINGS_1_CTRL_3U0_Ubc_TN2    0          
#define CTR_EXTRA_SETTINGS_1_CTRL_3U0_Ubc_TN2            (1 << INDEX_ML_CTREXTRA_SETTINGS_1_CTRL_3U0_Ubc_TN2)   
#define INDEX_ML_CTREXTRA_SETTINGS_1_CTRL_PHASE_LINE     1          
#define CTR_EXTRA_SETTINGS_1_CTRL_PHASE_LINE             (1 << INDEX_ML_CTREXTRA_SETTINGS_1_CTRL_PHASE_LINE)   
#define INDEX_ML_CTREXTRA_SETTINGS_1_CTRL_READY_TU       2          
#define CTR_EXTRA_SETTINGS_1_CTRL_READY_TU               (1 << INDEX_ML_CTREXTRA_SETTINGS_1_CTRL_READY_TU)   
#define INDEX_ML_CTREXTRA_SETTINGS_1_CTRL_WINDOW_OFF_CB  3          
#define CTR_EXTRA_SETTINGS_1_CTRL_WINDOW_OFF_CB          (1 << INDEX_ML_CTREXTRA_SETTINGS_1_CTRL_WINDOW_OFF_CB)   
#define INDEX_ML_CTREXTRA_SETTINGS_1_CTRL_FB_ACTIVATION  4          
#define CTR_EXTRA_SETTINGS_1_CTRL_FB_ACTIVATION          (1 << INDEX_ML_CTREXTRA_SETTINGS_1_CTRL_FB_ACTIVATION)   
#define INDEX_ML_CTREXTRA_SETTINGS_1_BLK_ON_CB_MISCEVE   5          
#define CTR_EXTRA_SETTINGS_1_BLK_ON_CB_MISCEVE           (1 << INDEX_ML_CTREXTRA_SETTINGS_1_BLK_ON_CB_MISCEVE)   
#define INDEX_ML_CTREXTRA_SETTINGS_1_BLK_OFF_CB_MISCEVE  6          
#define CTR_EXTRA_SETTINGS_1_BLK_OFF_CB_MISCEVE          (1 << INDEX_ML_CTREXTRA_SETTINGS_1_BLK_OFF_CB_MISCEVE)   

#define CTR_EXTRA_SETTINGS_1_MASKA                       (                                         \
                                                          CTR_EXTRA_SETTINGS_1_CTRL_3U0_Ubc_TN2   |\
                                                          CTR_EXTRA_SETTINGS_1_CTRL_PHASE_LINE    |\
                                                          CTR_EXTRA_SETTINGS_1_CTRL_READY_TU      |\
                                                          CTR_EXTRA_SETTINGS_1_CTRL_WINDOW_OFF_CB |\
                                                          CTR_EXTRA_SETTINGS_1_CTRL_FB_ACTIVATION |\
                                                          CTR_EXTRA_SETTINGS_1_BLK_ON_CB_MISCEVE  |\
                                                          CTR_EXTRA_SETTINGS_1_BLK_OFF_CB_MISCEVE  \
                                                         )

#endif
