#ifndef __CONST_MENU_CONTROL_U__
#define __CONST_MENU_CONTROL_U__

#define EKRAN_SETPOINT_CONTROL_U_GROUP1   (EKRAN_SETPOINT_AVR_GROUP4 + 1)
#define EKRAN_SETPOINT_CONTROL_U_GROUP2   (EKRAN_SETPOINT_CONTROL_U_GROUP1  + 1)
#define EKRAN_SETPOINT_CONTROL_U_GROUP3   (EKRAN_SETPOINT_CONTROL_U_GROUP2  + 1)
#define EKRAN_SETPOINT_CONTROL_U_GROUP4   (EKRAN_SETPOINT_CONTROL_U_GROUP3  + 1)
#define EKRAN_TIMEOUT_CONTROL_U_GROUP1    (EKRAN_TIMEOUT_AVR_GROUP4  + 1)
#define EKRAN_TIMEOUT_CONTROL_U_GROUP2    (EKRAN_TIMEOUT_CONTROL_U_GROUP1   + 1)
#define EKRAN_TIMEOUT_CONTROL_U_GROUP3    (EKRAN_TIMEOUT_CONTROL_U_GROUP2   + 1)
#define EKRAN_TIMEOUT_CONTROL_U_GROUP4    (EKRAN_TIMEOUT_CONTROL_U_GROUP3   + 1)
#define EKRAN_CONTROL_CONTROL_U           (EKRAN_CONTROL_AVR  + 1)

#define MAX_ROW_FOR_SETPOINT_CONTROL_U          2
#define MAX_ROW_FOR_TIMEOUT_CONTROL_U           2
#define MAX_ROW_FOR_CONTROL_CONTROL_U           2

#define INDEX_ML_STPCONTROL_U_OL                0
#define INDEX_ML_STPCONTROL_U_RL                1

#define INDEX_ML_TMOCONTROL_U_OL                0
#define INDEX_ML_TMOCONTROL_U_RT                1

#define COL_SETPOINT_CONTROL_U_OL_BEGIN         5
#define COL_SETPOINT_CONTROL_U_OL_COMMA         8
#define COL_SETPOINT_CONTROL_U_OL_END           9

#define COL_SETPOINT_CONTROL_U_RL_BEGIN         5
#define COL_SETPOINT_CONTROL_U_RL_COMMA         8
#define COL_SETPOINT_CONTROL_U_RL_END           9

#define COL_TMO_CONTROL_U_OL_BEGIN              4
#define COL_TMO_CONTROL_U_OL_COMMA              6
#define COL_TMO_CONTROL_U_OL_END                8

#define COL_TMO_CONTROL_U_RL_BEGIN              4
#define COL_TMO_CONTROL_U_RL_COMMA              6
#define COL_TMO_CONTROL_U_RL_END                8

#define INDEX_CTR_U_OL                          0          
#define CTR_U_OL                                (1 << INDEX_CTR_U_OL)
#define INDEX_CTR_U_RL                          1          
#define CTR_U_RL                                (1 << INDEX_CTR_U_RL)

#define CTR_CONTROL_U_MASKA                     (          \
                                                 CTR_U_OL |\
                                                 CTR_U_RL  \
                                                )

#endif

