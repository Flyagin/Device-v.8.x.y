#ifndef __CONST_MENU_DIAGNOSTYKA__
#define __CONST_MENU_DIAGNOSTYKA__

#define EKRAN_DIAGNOSTYKA                    (EKRAN_POINT_TIME_RANGUVANNJA + 1)

#define MAX_ROW_FOR_DIAGNOSTYKA              (8*(4 + 4 + 3))  /*2 ����� ���� unsigned int + �� ���� ����� ��� � ����� ����. ��� ����� ������ ������ ���������� ���������� ���� �� ��� ������ 32 �����. � ���� ����� - �� ������*/  

#define USED_BITS_IN_LAST_INDEX  0x00ffffff  

enum _error_id {
ERROR_START_VIA_I2C_BIT = 0,
ERROR_SETTINGS_EEPROM_BIT,
ERROR_SETTINGS_EEPROM_EMPTY_BIT,
ERROR_SETTINGS_EEPROM_COMPARISON_BIT,
ERROR_SETTINGS_EEPROM_CONTROL_BIT,
ERROR_SETTINGS_EEPROM_DEVICE_ID_FAIL_BIT,
ERROR_USTUVANNJA_EEPROM_BIT,
ERROR_USTUVANNJA_EEPROM_EMPTY_BIT,
ERROR_USTUVANNJA_EEPROM_COMPARISON_BIT,
ERROR_USTUVANNJA_EEPROM_CONTROL_BIT,
ERROR_USTUVANNJA_EEPROM_ADJUSTMENT_ID_FAIL_BIT,
ERROR_STATE_LEDS_EEPROM_BIT,
ERROR_STATE_OUTPUTS_EEPROM_BIT,
ERROR_STATE_LEDS_OUTPUTS_EEPROM_EMPTY_BIT,
ERROR_STATE_LEDS_OUTPUTS_EEPROM_COMPARISON_BIT,
ERROR_TRG_FUNC_EEPROM_BIT,
ERROR_TRG_FUNC_EEPROM_EMPTY_BIT,
ERROR_TRG_FUNC_EEPROM_COMPARISON_BIT,
ERROR_TRG_FUNC_EEPROM_CONTROL_BIT,
ERROR_INFO_REJESTRATOR_AR_EEPROM_BIT,
ERROR_INFO_REJESTRATOR_AR_EEPROM_EMPTY_BIT,
ERROR_INFO_REJESTRATOR_AR_COMPARISON_BIT,
ERROR_INFO_REJESTRATOR_AR_CONTROL_BIT,
ERROR_INFO_REJESTRATOR_DR_EEPROM_BIT,
ERROR_INFO_REJESTRATOR_DR_EEPROM_EMPTY_BIT,
ERROR_INFO_REJESTRATOR_DR_COMPARISON_BIT,
ERROR_INFO_REJESTRATOR_DR_CONTROL_BIT,
ERROR_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT,
ERROR_INFO_REJESTRATOR_PR_ERR_EEPROM_EMPTY_BIT,
ERROR_INFO_REJESTRATOR_PR_ERR_COMPARISON_BIT,
ERROR_INFO_REJESTRATOR_PR_ERR_CONTROL_BIT,
ERROR_RESURS_EEPROM_BIT,
ERROR_RESURS_EEPROM_EMPTY_BIT,
ERROR_RESURS_EEPROM_COMPARISON_BIT,
ERROR_RESURS_EEPROM_CONTROL_BIT,
ERROR_ENERGY_EEPROM_BIT,
ERROR_ENERGY_EEPROM_EMPTY_BIT,
ERROR_ENERGY_EEPROM_COMPARISON_BIT,

RTC_BATTERY_LOW_BIT,
RTC_OSCILLATOR_STOPED_BIT,
RTC_OSCILLATOR_FAIL_BIT,
RTC_UPDATING_HALTED_BIT,
RTC_WORK_FIELD_NOT_SET_BIT,

ERROR_GND_ADC1_TEST_BIT,
ERROR_VREF_ADC1_TEST_BIT,
ERROR_VDD_ADC1_TEST_BIT,
ERROR_GND_ADC1_TEST_COARSE_BIT,
ERROR_VREF_ADC1_TEST_COARSE_BIT,
ERROR_VDD_ADC1_TEST_COARSE_BIT,

ERROR_GND_ADC2_TEST_BIT,
ERROR_VREF_ADC2_TEST_BIT,
ERROR_VDD_ADC2_TEST_BIT,
ERROR_GND_ADC2_TEST_COARSE_BIT,
ERROR_VREF_ADC2_TEST_COARSE_BIT,
ERROR_VDD_ADC2_TEST_COARSE_BIT,

ERROR_SPI_ADC_BIT,

ERROR_OSCYLOJRAPH_OVERFLOW,

ERROR_DIGITAL_OUTPUT_1_BIT,

ERROR_AR_TEMPORARY_BUSY_BIT = ERROR_DIGITAL_OUTPUT_1_BIT + NUMBER_OUTPUTS,
ERROR_AR_OVERLOAD_BUFFER_BIT,
ERROR_AR_UNDEFINED_BIT,
ERROR_AR_LOSS_INFORMATION_BIT,

ERROR_DR_TEMPORARY_BUSY_BIT,
ERROR_DR_UNDEFINED_BIT,
ERROR_DR_LOSS_INFORMATION_BIT,

ERROR_PR_ERR_OVERLOAD_BIT,
ERROR_PR_ERR_LOSS_INFORMATION_BIT,

EVENT_START_SYSTEM_BIT,
EVENT_RESTART_SYSTEM_BIT,
EVENT_STOP_SYSTEM_BIT,
EVENT_DROP_POWER_BIT,

ERROR_LCD_BIT,
ERROR_SPI_DF_BIT,
ERROR_EXTERNAL_SRAM_BIT,
ERROR_INTERNAL_FLASH_BIT,

ERROR_SELECT_GRUPY_USRAVOK,

LOSE_ENERGY_DATA
};

#define MASKA_AVAR_ERROR_0        (unsigned int)(               \
    (1 << (ERROR_SETTINGS_EEPROM_BIT))                          \
  | (1 << (ERROR_SETTINGS_EEPROM_EMPTY_BIT))                    \
  | (1 << (ERROR_SETTINGS_EEPROM_COMPARISON_BIT) )              \
  | (1 << (ERROR_SETTINGS_EEPROM_CONTROL_BIT))                  \
  | (1 << (ERROR_USTUVANNJA_EEPROM_BIT) )                       \
  | (1 << (ERROR_USTUVANNJA_EEPROM_EMPTY_BIT))                  \
  | (1 << (ERROR_USTUVANNJA_EEPROM_COMPARISON_BIT))             \
  | (1 << (ERROR_USTUVANNJA_EEPROM_CONTROL_BIT))                \
  | (1 << (ERROR_USTUVANNJA_EEPROM_ADJUSTMENT_ID_FAIL_BIT))     \
  | (1 << (ERROR_TRG_FUNC_EEPROM_BIT))                          \
  | (1 << (ERROR_TRG_FUNC_EEPROM_EMPTY_BIT))                    \
  | (1 << (ERROR_TRG_FUNC_EEPROM_COMPARISON_BIT))               \
  | (1 << (ERROR_TRG_FUNC_EEPROM_CONTROL_BIT))                  \
)

#define MASKA_AVAR_ERROR_1        (unsigned int)(               \
    (1 << (ERROR_GND_ADC1_TEST_BIT - 32))                       \
  | (1 << (ERROR_VREF_ADC1_TEST_BIT - 32))                      \
  | (1 << (ERROR_VDD_ADC1_TEST_BIT - 32))                       \
  | (1 << (ERROR_GND_ADC1_TEST_COARSE_BIT - 32))                \
  | (1 << (ERROR_VREF_ADC1_TEST_COARSE_BIT - 32))               \
  | (1 << (ERROR_VDD_ADC1_TEST_COARSE_BIT - 32))                \
  | (1 << (ERROR_GND_ADC2_TEST_BIT - 32))                       \
  | (1 << (ERROR_VREF_ADC2_TEST_BIT - 32))                      \
  | (1 << (ERROR_VDD_ADC2_TEST_BIT - 32))                       \
  | (1 << (ERROR_GND_ADC2_TEST_COARSE_BIT - 32))                \
  | (1 << (ERROR_VREF_ADC2_TEST_COARSE_BIT - 32))               \
  | (1 << (ERROR_VDD_ADC2_TEST_COARSE_BIT - 32))                \
  | (1 << (ERROR_SPI_ADC_BIT - 32))                             \
  | (1 << (ERROR_DIGITAL_OUTPUT_1_BIT + 0 - 32))                \
  | (1 << (ERROR_DIGITAL_OUTPUT_1_BIT + 1 - 32))                \
  | (1 << (ERROR_DIGITAL_OUTPUT_1_BIT + 2 - 32))                \
  | (1 << (ERROR_DIGITAL_OUTPUT_1_BIT + 3 - 32))                \
  | (1 << (ERROR_DIGITAL_OUTPUT_1_BIT + 4 - 32))                \
  | (1 << (ERROR_DIGITAL_OUTPUT_1_BIT + 5 - 32))                \
  | (1 << (ERROR_DIGITAL_OUTPUT_1_BIT + 6 - 32))                \
)

#define MASKA_AVAR_ERROR_2        (unsigned int)(               \
    (1 << (ERROR_DIGITAL_OUTPUT_1_BIT + 7 - 64))                \
  | (1 << (ERROR_DIGITAL_OUTPUT_1_BIT + 8 - 64))                \
  | (1 << (ERROR_DIGITAL_OUTPUT_1_BIT + 9 - 64))                \
  | (1 << (ERROR_INTERNAL_FLASH_BIT - 64))                      \
)

# define NAME_DIAGN_RU  \
  " ��.I2C         ",   \
  " ��.��������    ",   \
  " �������� ���   ",   \
  " ��.���.�����.  ",   \
  " ��.�����.�����.",   \
  " ��.���� �����. ",   \
  " ��.����������� ",   \
  " ����������� ���",   \
  " ��.���.�����.  ",   \
  " ��.�����.�����.",   \
  " ��.�����.������",   \
  " ��.��c��.��.�� ",   \
  " ��.��c��.�.��� ",   \
  "���.���./��.��� ",   \
  " ��.���.���./��.",   \
  "  ��.����.���.  ",   \
  "  ����.���.���  ",   \
  "��.���.����.���.",   \
  "��.�����.����.�.",   \
  " ��.���.��.���. ",   \
  " ���.��.���.��� ",   \
  "��.���.�.��.���.",   \
  "��.�����.��.���.",   \
  " ��.���.�.���.  ",   \
  " ���.�.���.���  ",   \
  " ��.���.�.�.���.",   \
  " ��.�����.�.���.",   \
  "��.���.���.��.�.",   \
  "���.���.��.�.���",   \
  "��.���.�.�.��.�.",   \
  "��.�����.�.��.�.",   \
  " ��.���.��.���. ",   \
  " ���.��.���.��� ",   \
  " ��.���.��.���. ",   \
  "��.�����.��.���.",   \
  " ��.�.�.������� ",   \
  "  ������� ���   ",   \
  " ��.���.������� ",   \
  " ������� ������.",   \
  "��������� �����.",   \
  "����� ����������",   \
  " ���.������.RTC ",   \
  " �� ���.���� RTC",   \
  " ���� GND ���1  ",   \
  " ���� VREF ���1 ",   \
  " ���� VDD ���1  ",   \
  "���� GND ���1 ��",   \
  "���� VREF ���1��",   \
  "���� VDD ���1 ��",   \
  " ���� GND ���2  ",   \
  " ���� VREF ���2 ",   \
  " ���� VDD ���2  ",   \
  "���� GND ���2 ��",   \
  "���� VREF ���2��",   \
  "���� VDD ���2 ��",   \
  " ��. SPI ���    ",   \
  "�����.���.�.���.",   \
  " ��.���.���� 1  ",   \
  " ��.���.���� 2  ",   \
  " ��.���.���� 3  ",   \
  " ��.���.���� 4  ",   \
  " ��.���.���� 5  ",   \
  " ��.���.���� 6  ",   \
  " ��.���.���� 7  ",   \
  " ��.���.���� 8  ",   \
  " ��.���.���� 9  ",   \
  " ��.���.���� 10 ",   \
  "��.���.��.�����.",   \
  " ���.���.a�.���.",   \
  "�����.��.��.���.",   \
  "������ �.��.���.",   \
  " �.���.��.�����.",   \
  " �����.��.�.���.",   \
  " ������ �.�.���.",   \
  "�����.���.��.��.",   \
  " ������ �.��.��.",   \
  " ����� ����.    ",   \
  " ������� ����.  ",   \
  " �������.����.  ",   \
  " ������.������� ",   \
  " ����� ���      ",   \
  " ��.SPI_DF      ",   \
  " ��.������� SRAM",   \
  " ��.�����.FLASH ",   \
  " ��.���.��.���. ",   \
  " ���.�.�������  ",   \
  " ������ 87      ",   \
  " ������ 88      "

# define NAME_DIAGN_UA  \
  " ���.I2C        ",   \
  " ���.�����������",   \
  "����������� ����",   \
  " ���.���.������.",   \
  "���.�����.������",   \
  " ���.���� ������",   \
  " ���.���������  ",   \
  " ��������� ���� ",   \
  " ���.���.���.   ",   \
  " ���.�����.���. ",   \
  " ���.���.������ ",   \
  " ���.���.��.��.",   \
  " ���.���.�.���.",   \
  "���.���./��.����",   \
  "���.���.���./��.",   \
  " ���.���.���.  ",   \
  " ���.���.����  ",   \
  " ���.���.���.�.",   \
  "���.�����.���.�",   \
  " ���.���.��.�.  ",   \
  " ���.��.�.����  ",   \
  " ���.���.�.��.�.",   \
  " ���.�����.��.�.",   \
  " ���.���.�.�.   ",   \
  " ���.�.�.����   ",   \
  " ���.���.�.�.�. ",   \
  " ���.�����.�.�. ",   \
  " ���.���.�.��.�.",   \
  " ���.�.��.�.����",   \
  "���.���.�.�.��.�",   \
  "���.�����.�.��.�",   \
  " ���.���.��.�. ",   \
  " ���.��.�.���� ",   \
  " ���.���.��.�. ",   \
  "���.�����.��.�.",   \
  " ���.�.�.������",   \
  "  ������ ����  ",   \
  " ���.���.������",   \
  "������� �������.",   \
  " ��������� ���. ",   \
  " ³��.����������",   \
  " ���.������.RTC ",   \
  " �� ���.���� RTC",   \
  " ���� GND ���1  ",   \
  " ���� VREF ���1 ",   \
  " ���� VDD ���1  ",   \
  "���� GND ���1 ��",   \
  "���� VREF ���1��",   \
  "���� VDD ���1 ��",   \
  " ���� GND ���2  ",   \
  " ���� VREF ���2 ",   \
  " ���� VDD ���2  ",   \
  "���� GND ���2 ��",   \
  "���� VREF ���2��",   \
  "���� VDD ���2 ��",   \
  " ���.SPI ���    ",   \
  "�����.���.�.���.",   \
  " ���.���.���� 1 ",   \
  " ���.���.���� 2 ",   \
  " ���.���.���� 3 ",   \
  " ���.���.���� 4 ",   \
  " ���.���.���� 5 ",   \
  " ���.���.���� 6 ",   \
  " ���.���.���� 7 ",   \
  " ���.���.���� 8 ",   \
  " ���.���.���� 9 ",   \
  " ���.���.���� 10",   \
  "��.�.����.������",   \
  " �����.���.a�.�.",   \
  "������.���.��.�.",   \
  "������ �.��.�.  ",   \
  "�.�.����.������.",   \
  " ������.���.�.�.",   \
  " ������ �.�.�.  ",   \
  "�����.���.�.��.�",   \
  " ������ �.�.��.�",   \
  " ����� ������.  ",   \
  " ������� ������.",   \
  " ���.������.    ",   \
  " ������.��������",   \
  " ³����� �ʲ    ",   \
  " ���.SPI_DF     ",   \
  " ���.����.SRAM  ",   \
  " ���.�����.FLASH",   \
  " ���.���.��.���.",   \
  " ���.�.����㳿  ",   \
  " ������� 87     ",   \
  " ������� 88     "

# define NAME_DIAGN_EN  \
  " I2C Err.       ",   \
  " Settings Err.  ",   \
  " No settings    ",   \
  " Sett.W.Err.    ",   \
  " Sett.Ctrl.Err. ",   \
  " Sett.Type Err. ",   \
  " Adjust Err.    ",   \
  " No adjust      ",   \
  " Adjust W.Err.  ",   \
  "Adjust Ctrl.Err.",   \
  " Adjust-Set Err.",   \
  "Tr.LED Rest Err.",   \
  "Sign DO Rest Err",   \
  " No DO/LED Inf. ",   \
  " DO/LED W Err.  ",   \
  "  ��.����.���.  ",   \
  "  ����.���.���  ",   \
  "��.���.����.���.",   \
  "��.�����.����.�.",   \
  " An.Rec.Inf.Err.",   \
  " No An.Rec.Inf. ",   \
  "An.Rec.Inf.W.Err",   \
  "An.Rec.Ctrl.Err.",   \
  " D.Rec.Inf.Err. ",   \
  " No D.Rec.Inf.  ",   \
  "Inf.D.Rec.W.Err.",   \
  " D.Rec.Ctrl.Err.",   \
  " PER Inf.Err.   ",   \
  " No Inf.of PER  ",   \
  "Inf.W.Err.of PER",   \
  " PER Ctrl.Err.  ",   \
  " Res.C.Inf.Err. ",   \
  " No Res.C.Inf.  ",   \
  "Inf.Res.C.W.Err.",   \
  " Res.C.Ctrl.Err.",   \
  " ��.�.�.������� ",   \
  "  ������� ���   ",   \
  " ��.���.������� ",   \
  " RTC:Battery low",   \
  " RTC:Osc.stop   ",   \
  " RTC:Osc.fail   ",   \
  " RTC:Halt update",   \
  "RTC:No def.sett.",   \
  " ADC1:GND fail  ",   \
  " ADC1:VREF fail ",   \
  " ADC1:VDD fail  ",   \
  "ADC1:GND Test R.",   \
  "ADC1:VREF Test R",   \
  "ADC1:VDD Test R.",   \
  " ADC2:GND fail  ",   \
  " ADC2:VREF fail ",   \
  " ADC2:VDD fail  ",   \
  "ADC2:GND Test R.",   \
  "ADC2:VREF Test R",   \
  "ADC2:VDD Test R.",   \
  " ADC SPI Err.   ",   \
  "�����.���.�.���.",   \
  " DO1 Ctrl.Err.  ",   \
  " DO2 Ctrl.Err.  ",   \
  " DO3 Ctrl.Err.  ",   \
  " DO4 Ctrl.Err.  ",   \
  " DO5 Ctrl.Err.  ",   \
  " DO6 Ctrl.Err.  ",   \
  " DO7 Ctrl.Err.  ",   \
  " DO8 Ctrl.Err.  ",   \
  " DO9 Ctrl.Err.  ",   \
  " DO10 Ctrl.Err. ",   \
  " An.Rec.busy    ",   \
  " An.Rec.buff.OVF",   \
  "Undef.An.Rec.Err",   \
  "An.Rec.Data lost",   \
  " D.Rec.busy     ",   \
  "Undef.D.Rec.Err.",   \
  " D.Rec.Data lost",   \
  "OVF of PER buff.",   \
  " PER Data lost  ",   \
  " Device Start   ",   \
  " Device Restart ",   \
  " Device Stop    ",   \
  " ������.������� ",   \
  " LCD Fail       ",   \
  " DF SPI Err.    ",   \
  " Ext.SRAM Err.  ",   \
  " Int.FLASH Err. ",   \
  " ��.���.��.���. ",   \
  " ���.�.�������  ",   \
  " Error 87       ",   \
  " Error 88       "

# define NAME_DIAGN_KZ  \
  " ��.I2C         ",   \
  " ��.��������    ",   \
  " �������� ���   ",   \
  " ��.���.�����.  ",   \
  " ��.�����.�����.",   \
  " ��.���� �����. ",   \
  " ��.����������� ",   \
  " ����������� ���",   \
  " ��.���.�����.  ",   \
  " ��.�����.�����.",   \
  " ��.�����.������",   \
  " ��.��c��.��.�� ",   \
  " ��.��c��.�.��� ",   \
  "���.���./��.��� ",   \
  " ��.���.���./��.",   \
  "  ��.����.���.  ",   \
  "  ����.���.���  ",   \
  "��.���.����.���.",   \
  "��.�����.����.�.",   \
  " ��.���.��.���. ",   \
  " ���.��.���.��� ",   \
  "��.���.�.��.���.",   \
  "��.�����.��.���.",   \
  " ��.���.�.���.  ",   \
  " ���.�.���.���  ",   \
  " ��.���.�.�.���.",   \
  " ��.�����.�.���.",   \
  "��.���.���.��.�.",   \
  "���.���.��.�.���",   \
  "��.���.�.�.��.�.",   \
  "��.�����.�.��.�.",   \
  " ��.���.��.���. ",   \
  " ���.��.���.��� ",   \
  " ��.���.��.���. ",   \
  "��.�����.��.���.",   \
  " ��.�.�.������� ",   \
  "  ������� ���   ",   \
  " ��.���.������� ",   \
  " ������� ������.",   \
  "��������� �����.",   \
  "����� ����������",   \
  " ���.������.RTC ",   \
  " �� ���.���� RTC",   \
  " ���� GND ���1  ",   \
  " ���� VREF ���1 ",   \
  " ���� VDD ���1  ",   \
  " ���� GND ���1��",   \
  "���� VREF ���1��",   \
  "���� VDD ���1 ��",   \
  " ���� GND ���2  ",   \
  " ���� VREF ���2 ",   \
  " ���� VDD ���2  ",   \
  " ���� GND ���2��",   \
  "���� VREF ���2��",   \
  "���� VDD ���2 ��",   \
  " ��.SPI ���     ",   \
  "�����.���.�.���.",   \
  " ��.���.���� 1  ",   \
  " ��.���.���� 2  ",   \
  " ��.���.���� 3  ",   \
  " ��.���.���� 4  ",   \
  " ��.���.���� 5  ",   \
  " ��.���.���� 6  ",   \
  " ��.���.���� 7  ",   \
  " ��.���.���� 8  ",   \
  " ��.���.���� 9  ",   \
  " ��.���.���� 10 ",   \
  "��.���.��.�����.",   \
  " ���.���.a�.���.",   \
  "�����.��.��.���.",   \
  "������ �.��.���.",   \
  " �.���.��.�����.",   \
  " �����.��.�.���.",   \
  " ������ �.�.���.",   \
  "�����.���.��.��.",   \
  " ������ �.��.��.",   \
  " ����� ����.    ",   \
  " ������� ����.  ",   \
  " �������.����.  ",   \
  " ������.������� ",   \
  " ����� ���      ",   \
  " ��.SPI_DF      ",   \
  " ��.������� SRAM",   \
  " ��.�����.FLASH ",   \
  " ��.���.��.���. ",   \
  " ���.�.�������  ",   \
  " ������ 87      ",   \
  " ������ 88      "
    
#endif
