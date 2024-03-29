#ifndef __CONST_MENU_ZZ__
#define __CONST_MENU_ZZ__

#define EKRAN_SETPOINT_ZZ_GROUP1    (EKRAN_SETPOINT_MTZ_GROUP4 + 1)
#define EKRAN_SETPOINT_ZZ_GROUP2    (EKRAN_SETPOINT_ZZ_GROUP1 + 1)
#define EKRAN_SETPOINT_ZZ_GROUP3    (EKRAN_SETPOINT_ZZ_GROUP2 + 1)
#define EKRAN_SETPOINT_ZZ_GROUP4    (EKRAN_SETPOINT_ZZ_GROUP3 + 1)
#define EKRAN_TIMEOUT_ZZ_GROUP1     (EKRAN_TIMEOUT_MTZ_GROUP4 + 1)
#define EKRAN_TIMEOUT_ZZ_GROUP2     (EKRAN_TIMEOUT_ZZ_GROUP1 + 1)
#define EKRAN_TIMEOUT_ZZ_GROUP3     (EKRAN_TIMEOUT_ZZ_GROUP2 + 1)
#define EKRAN_TIMEOUT_ZZ_GROUP4     (EKRAN_TIMEOUT_ZZ_GROUP3 + 1)
#define EKRAN_CONTROL_ZZ            (EKRAN_CONTROL_ZDZ + 1)


#define MAX_ROW_FOR_SETPOINT_ZZ    2
#define MAX_ROW_FOR_TIMEOUT_ZZ     3
#define MAX_ROW_FOR_CONTROL_ZZ     5

#define INDEX_ML_STPZZ1_3I0        0
#define INDEX_ML_STPZZ1_3U0        1

#define INDEX_ML_TMOZZ1_3I0        0
#define INDEX_ML_TMOZZ1_3U0        1
#define INDEX_ML_TMOZZ1_NZZ        2

#define COL_SETPOINT_ZZ1_3I0_BEGIN 5
#define COL_SETPOINT_ZZ1_3I0_COMMA 6
#define COL_SETPOINT_ZZ1_3I0_END   9

#define COL_SETPOINT_ZZ1_3U0_BEGIN 3
#define COL_SETPOINT_ZZ1_3U0_COMMA 6
#define COL_SETPOINT_ZZ1_3U0_END   8

#define COL_TMO_ZZ1_3I0_BEGIN      4
#define COL_TMO_ZZ1_3I0_COMMA      6
#define COL_TMO_ZZ1_3I0_END        8

#define COL_TMO_ZZ1_3U0_BEGIN      4
#define COL_TMO_ZZ1_3U0_COMMA      6
#define COL_TMO_ZZ1_3U0_END        8

#define COL_TMO_ZZ1_NZZ_BEGIN      4
#define COL_TMO_ZZ1_NZZ_COMMA      6
#define COL_TMO_ZZ1_NZZ_END        8

#define INDEX_ML_CTR_ZZ1_3I0_STATE      0          
#define CTR_ZZ1_3I0_STATE               (1 << INDEX_ML_CTR_ZZ1_3I0_STATE)   
#define INDEX_ML_CTR_ZZ1_TYPE_BIT       1          
#define CTR_ZZ1_TYPE                    (1 << INDEX_ML_CTR_ZZ1_TYPE_BIT)          
#define INDEX_ML_CTR_ZZ1_3U0_STATE      2          
#define CTR_ZZ1_3U0_STATE               (1 << INDEX_ML_CTR_ZZ1_3U0_STATE)   
#define INDEX_ML_CTR_ZZ1_NZZ_STATE      3          
#define CTR_ZZ1_NZZ_STATE               (1 << INDEX_ML_CTR_ZZ1_NZZ_STATE)   
#define INDEX_ML_CTR_ZZ1_SECTOR         4          
#define CTR_ZZ1_SECTOR                  (1 << INDEX_ML_CTR_ZZ1_SECTOR)   

#define CTR_ZZ_MASKA              (CTR_ZZ1_3I0_STATE | CTR_ZZ1_TYPE | CTR_ZZ1_3U0_STATE | CTR_ZZ1_NZZ_STATE | CTR_ZZ1_SECTOR)


#endif
