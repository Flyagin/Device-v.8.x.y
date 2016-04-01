#ifndef __CONST_MENU_ACHR_CHAPV__
#define __CONST_MENU_ACHR_CHAPV__


#define EKRAN_SETPOINT_ACHR_CHAPV_GROUP1   (EKRAN_SETPOINT_APV_ZMN_GROUP4 + 1)
#define EKRAN_SETPOINT_ACHR_CHAPV_GROUP2   (EKRAN_SETPOINT_ACHR_CHAPV_GROUP1 + 1)
#define EKRAN_SETPOINT_ACHR_CHAPV_GROUP3   (EKRAN_SETPOINT_ACHR_CHAPV_GROUP2 + 1)
#define EKRAN_SETPOINT_ACHR_CHAPV_GROUP4   (EKRAN_SETPOINT_ACHR_CHAPV_GROUP3 + 1)
#define EKRAN_TIMEOUT_ACHR_CHAPV_GROUP1    (EKRAN_TIMEOUT_APV_ZMN_GROUP4      + 1)
#define EKRAN_TIMEOUT_ACHR_CHAPV_GROUP2    (EKRAN_TIMEOUT_ACHR_CHAPV_GROUP1  + 1)
#define EKRAN_TIMEOUT_ACHR_CHAPV_GROUP3    (EKRAN_TIMEOUT_ACHR_CHAPV_GROUP2  + 1)
#define EKRAN_TIMEOUT_ACHR_CHAPV_GROUP4    (EKRAN_TIMEOUT_ACHR_CHAPV_GROUP3  + 1)
#define EKRAN_CONTROL_ACHR_CHAPV           (EKRAN_CONTROL_APV_ZMN  + 1)

#define MAX_ROW_FOR_SETPOINT_ACHR_CHAPV     4
#define MAX_ROW_FOR_TIMEOUT_ACHR_CHAPV      4
#define MAX_ROW_FOR_CONTROL_ACHR_CHAPV      3

#define INDEX_ML_STPACHR_F_RAB              0
#define INDEX_ML_STPCHAPV_F_RAB             1
#define INDEX_ML_STPACHR_CHAPV_UF1          2
#define INDEX_ML_STPACHR_CHAPV_UF2          3

#define INDEX_ML_TMOACHR1                   0
#define INDEX_ML_TMOCHAPV1                  1
#define INDEX_ML_TMOACHR2                   2
#define INDEX_ML_TMOCHAPV2                  3

#define COL_SETPOINT_ACHR_F_RAB_BEGIN       4
#define COL_SETPOINT_ACHR_F_RAB_COMMA       6
#define COL_SETPOINT_ACHR_F_RAB_END         7

#define COL_SETPOINT_CHAPV_F_RAB_BEGIN      4
#define COL_SETPOINT_CHAPV_F_RAB_COMMA      6
#define COL_SETPOINT_CHAPV_F_RAB_END        7

#define COL_SETPOINT_ACHR_CHAPV_UF1_BEGIN   5
#define COL_SETPOINT_ACHR_CHAPV_UF1_COMMA   8
#define COL_SETPOINT_ACHR_CHAPV_UF1_END     9

#define COL_SETPOINT_ACHR_CHAPV_UF2_BEGIN   5
#define COL_SETPOINT_ACHR_CHAPV_UF2_COMMA   8
#define COL_SETPOINT_ACHR_CHAPV_UF2_END     9

#define COL_TMO_ACHR1_BEGIN                 4
#define COL_TMO_ACHR1_COMMA                 6
#define COL_TMO_ACHR1_END                   8

#define COL_TMO_CHAPV1_BEGIN                4
#define COL_TMO_CHAPV1_COMMA                6
#define COL_TMO_CHAPV1_END                  8

#define COL_TMO_ACHR2_BEGIN                 4
#define COL_TMO_ACHR2_COMMA                 6
#define COL_TMO_ACHR2_END                   8

#define COL_TMO_CHAPV2_BEGIN                4
#define COL_TMO_CHAPV2_COMMA                6
#define COL_TMO_CHAPV2_END                  8

#define INDEX_CTR_ACHR                  0
#define CTR_ACHR                        (1 << INDEX_CTR_ACHR)
#define INDEX_CTR_CHAPV                 1
#define CTR_CHAPV                       (1 << INDEX_CTR_CHAPV)
#define INDEX_CTR_CHAPV_VID_DV          2
#define CTR_CHAPV_VID_DV                (1 << INDEX_CTR_CHAPV_VID_DV)

#define CTR_ACHR_CHAPV_MASKA            (                        \
                                         CTR_ACHR               |\
                                         CTR_CHAPV              |\
                                         CTR_CHAPV_VID_DV        \
                                        )

#endif
