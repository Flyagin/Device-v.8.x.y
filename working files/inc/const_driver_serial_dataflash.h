#ifndef __CONST_DRIVER_SERIAL_FLASH__
#define __CONST_DRIVER_SERIAL_FLASH__

#define NUMBER_DATAFLASH_CHIP      2

#define INDEX_DATAFLASH_1           0
#define INDEX_DATAFLASH_2           1
#define INDEX_EEPROM                3

#define VAGA_SIZE_PAGE_DATAFLASH_1      8 //�� ��������� ������� ����� ��� ����, ��� ����� ���� ����� ������� �� 256 � ����� �� 256
#define SIZE_PAGE_DATAFLASH_1           (1 << VAGA_SIZE_PAGE_DATAFLASH_1) //256 ����
#define NUMBER_PAGES_INTO_DATAFLASH_1   512

#define VAGA_SIZE_PAGE_DATAFLASH_2      9 //�� ��������� ������� ����� ��� ����, ��� ����� ���� ����� ������� �� 512 � ����� �� 512
#define SIZE_PAGE_DATAFLASH_2           (1 << VAGA_SIZE_PAGE_DATAFLASH_2) //512 ����
#define NUMBER_PAGES_INTO_DATAFLASH_2   4096

#if SIZE_PAGE_DATAFLASH_2 >= SIZE_PAGE_DATAFLASH_1
#define SIZE_PAGE_DATAFLASH_MAX         SIZE_PAGE_DATAFLASH_2
#else
#define SIZE_PAGE_DATAFLASH_MAX         SIZE_PAGE_DATAFLASH_1
#endif

#define NUMBER_PAGES_INTO_AR            NUMBER_PAGES_INTO_DATAFLASH_2
#define NUMBER_PAGES_INTO_DR            432
#define NUMBER_PAGES_INTO_PR_ERR        (NUMBER_PAGES_INTO_DATAFLASH_1 - NUMBER_PAGES_INTO_DR)

#define NUMBER_PAGES_IN_ONE_DR_RECORD         9
#define SIZE_BUFFER_FOR_DR_RECORD             (SIZE_PAGE_DATAFLASH_1*NUMBER_PAGES_IN_ONE_DR_RECORD) 
#define MAX_NUMBER_RECORDS_INTO_DR            48
#define MIN_ADDRESS_DR_AREA                   0x0
#define SIZE_DR_AREA                          (NUMBER_PAGES_INTO_DR<<VAGA_SIZE_PAGE_DATAFLASH_1)
#define MAX_ADDRESS_DR_AREA                   (MIN_ADDRESS_DR_AREA + SIZE_DR_AREA - 1)

#define FIRST_INDEX_START_START_RECORD_DR     0
#define FIRST_INDEX_DATA_TIME_DR              1
#define FIRST_INDEX_EXTRA_SETTINGS_DR         8
#define FIRST_INDEX_NAME_OF_CELL_DR           12
#define FIRST_INDEX_NUMBER_ITEMS_DR           44
#define FIRST_INDEX_NUMBER_CHANGES_DR         45
#define FIRST_INDEX_NUMBER_MAX_PHASE_DR       47
#define FIRST_INDEX_NUMBER_MAX_3I0_DR         48
#define FIRST_INDEX_NUMBER_MAX_3U0_DR         49
#define FIRST_INDEX_NUMBER_MIN_U_DR           50
#define FIRST_INDEX_NUMBER_MAX_U_DR           51
#define FIRST_INDEX_NUMBER_MAX_ZOP_DR         52
#define FIRST_INDEX_NUMBER_MIN_F1_ACHR_DR     53
#define FIRST_INDEX_NUMBER_MIN_F2_ACHR_DR     54
#define FIRST_INDEX_NUMBER_F1_CHAPV_DR        55
#define FIRST_INDEX_NUMBER_F2_CHAPV_DR        56
#define FIRST_INDEX_FIRST_BLOCK_DR            57
#define FIRST_INDEX_FIRST_DATA_DR             1097

#define VAGA_SIZE_ONE_RECORD_PR_ERR           5
#define SIZE_ONE_RECORD_PR_ERR                (1<<VAGA_SIZE_ONE_RECORD_PR_ERR)
#define NUMBER_RECORDS_PR_ERR_INTO_PAGE       (SIZE_PAGE_DATAFLASH_1>>VAGA_SIZE_ONE_RECORD_PR_ERR) //������� ������ ���������� ���� � ���� �������� ��������� ��������� DataFlash
#define MAX_NUMBER_RECORDS_PR_ERR_INTO_BUFFER 32 //������������������ ������ � ����� ���� FIFO, �� ������� �� ������ DataFlash
#define SIZE_BUFFER_FOR_PR_ERR                (SIZE_ONE_RECORD_PR_ERR*MAX_NUMBER_RECORDS_PR_ERR_INTO_BUFFER)
#define MAX_NUMBER_RECORDS_INTO_PR_ERR        (NUMBER_PAGES_INTO_PR_ERR*NUMBER_RECORDS_PR_ERR_INTO_PAGE)
#define MIN_ADDRESS_PR_ERR_AREA               (MAX_ADDRESS_DR_AREA + 1)
#define SIZE_PR_ERR_AREA                      (NUMBER_PAGES_INTO_PR_ERR<<VAGA_SIZE_PAGE_DATAFLASH_1)
#define MAX_ADDRESS_PR_ERR_AREA               (MIN_ADDRESS_PR_ERR_AREA + SIZE_PR_ERR_AREA - 1)

#define MASKA_BIT_FOR_PRESCALER               0x1
#define VAGA_NUMBER_POINT_AR                  (VAGA_NUMBER_POINT - 1)
#define NUMBER_POINT_AR                       (1 << VAGA_NUMBER_POINT_AR)
#define MIN_ADDRESS_AR_AREA                   0x0
#define SIZE_AR_AREA                          (NUMBER_PAGES_INTO_AR<<VAGA_SIZE_PAGE_DATAFLASH_2)
#define MAX_ADDRESS_AR_AREA                   (MIN_ADDRESS_AR_AREA + SIZE_AR_AREA - 1)


#define TRANSACTION_EXECUTING_NONE              0
#define TRANSACTION_EXECUTING                   1
#define TRANSACTION_EXECUTED_WAIT_ANALIZE       2

#define CODE_OPERATION_NONE                                 0
#define CODE_OPERATION_STATUS_READ                          1
#define CODE_OPERATION_PAGESIZE_256                         2
#define CODE_OPERATION_ERASE                                3
#define CODE_OPERATION_WRITE_PAGE_THROUGH_BUFFER            4
#define CODE_OPERATION_READ_HIGH_FREQ                       5
#define CODE_OPERATION_READ_PAGE_INTO_BUFFER                6
#define CODE_OPERATION_WRITE_BUFFER                         7
#define CODE_OPERATION_WRITE_BUFFER_INTO_MEMORY_WITH_ERASE  8

/*���� 0-15 �������� �� ��������� DataFlash ����������� ���������� � ���������� ���������� ����*/
#define TASK_ERASE_DATAFLASH_1_BIT                                          0
#define TASK_ERASE_DATAFLASH_1                                              (1<<TASK_ERASE_DATAFLASH_1_BIT)
#define TASK_WRITE_PR_ERR_RECORDS_INTO_DATAFLASH_BIT                        1
#define TASK_WRITE_PR_ERR_RECORDS_INTO_DATAFLASH                            (1<<TASK_WRITE_PR_ERR_RECORDS_INTO_DATAFLASH_BIT)
#define TASK_MAMORY_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_DR_BIT        2
#define TASK_MAMORY_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_DR            (1<<TASK_MAMORY_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_DR_BIT)
#define TASK_MAMORY_READ_DATAFLASH_FOR_DR_MENU_BIT                          3
#define TASK_MAMORY_READ_DATAFLASH_FOR_DR_MENU                              (1<<TASK_MAMORY_READ_DATAFLASH_FOR_DR_MENU_BIT)
#define TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_MENU_BIT                      4
#define TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_MENU                          (1<<TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_MENU_BIT)
#define TASK_MAMORY_READ_DATAFLASH_FOR_DR_USB_BIT                           5
#define TASK_MAMORY_READ_DATAFLASH_FOR_DR_USB                               (1<<TASK_MAMORY_READ_DATAFLASH_FOR_DR_USB_BIT)
#define TASK_MAMORY_READ_DATAFLASH_FOR_DR_RS485_BIT                         6
#define TASK_MAMORY_READ_DATAFLASH_FOR_DR_RS485                             (1<<TASK_MAMORY_READ_DATAFLASH_FOR_DR_RS485_BIT)
#define TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_USB_BIT                       7
#define TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_USB                           (1<<TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_USB_BIT)
#define TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_RS485_BIT                     8
#define TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_RS485                         (1<<TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_RS485_BIT)

#define  SEPARATOR_BIT_TASKS_DATADLASH1_AND_TASKS_DATADLASH2                16

/*���� 16-31 �������� �� ��������� DataFlash ����������� ����������*/
#define TASK_ERASE_DATAFLASH_2_BIT                                          (0 + SEPARATOR_BIT_TASKS_DATADLASH1_AND_TASKS_DATADLASH2)
#define TASK_ERASE_DATAFLASH_2                                              (1<<TASK_ERASE_DATAFLASH_2_BIT)
#define TASK_MAMORY_PART_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_AR_BIT   (1 + SEPARATOR_BIT_TASKS_DATADLASH1_AND_TASKS_DATADLASH2)
#define TASK_MAMORY_PART_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_AR       (1<<TASK_MAMORY_PART_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_AR_BIT)
#define TASK_MAMORY_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_AR_BIT        (2 + SEPARATOR_BIT_TASKS_DATADLASH1_AND_TASKS_DATADLASH2)
#define TASK_MAMORY_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_AR            (1<<TASK_MAMORY_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_AR_BIT)
#define TASK_MAMORY_READ_DATAFLASH_FOR_AR_MENU_BIT                          (3 + SEPARATOR_BIT_TASKS_DATADLASH1_AND_TASKS_DATADLASH2)
#define TASK_MAMORY_READ_DATAFLASH_FOR_AR_MENU                              (1<<TASK_MAMORY_READ_DATAFLASH_FOR_AR_MENU_BIT)
#define TASK_MAMORY_READ_DATAFLASH_FOR_AR_USB_BIT                           (5 + SEPARATOR_BIT_TASKS_DATADLASH1_AND_TASKS_DATADLASH2)
#define TASK_MAMORY_READ_DATAFLASH_FOR_AR_USB                               (1<<TASK_MAMORY_READ_DATAFLASH_FOR_AR_USB_BIT)
#define TASK_MAMORY_READ_DATAFLASH_FOR_AR_RS485_BIT                         (6 + SEPARATOR_BIT_TASKS_DATADLASH1_AND_TASKS_DATADLASH2)
#define TASK_MAMORY_READ_DATAFLASH_FOR_AR_RS485                             (1<<TASK_MAMORY_READ_DATAFLASH_FOR_AR_RS485_BIT)

#define WIGHT_OF_DR_WAITING                       2

#define STATE_DR_NO_RECORD                        0 //�� ����� ������ ���� �� � ���������� ����������� �� ����������
#define STATE_DR_FORCE_START_NEW_RECORD           1 //�������� ��䳿 �������� �� �����, ��� �� �� ��������� ����� ���������� ������ ����������� ���������� ���� ��� ���������� ������ ��������� ����� �����
#define STATE_DR_EXECUTING_RECORD                 2 //��� ������ ������ ����������
#define STATE_DR_MAKE_RECORD                      3 //�������� ����� ���  ������ � Dataflash
#define STATE_DR_CUT_RECORD                       4 //�������� ��䳿 �������� �� �����, ��� �� �� ��������� ����� ���������� ������ ����������� ���������� ���� ��� ���������� ������ ��������� ����� �����

#define MAX_TIME_OFFSET_FROM_START                      0xFFFFFF // 4 ���. 39 ��. 37 ���. 215 �����.
#define MAX_EVENTS_IN_ONE_RECORD                        43
#define MAX_NUMBER_FIX_MAX_MEASUREMENTS                 10
#define SIZE_ARRAY_FIX_MAX_MEASUREMENTS                 (NUMBER_ANALOG_CANALES + 18)

#define LABEL_START_RECORD_DR           0xA5

#define IDENTIFIER_BIT_ARRAY_MAX_CURRENT_PHASE          1
#define IDENTIFIER_BIT_ARRAY_MAX_CURRENT_3I0            2
#define IDENTIFIER_BIT_ARRAY_MAX_VOLTAGE_3U0            3
#define IDENTIFIER_BIT_ARRAY_MIN_VOLTAGE                4
#define IDENTIFIER_BIT_ARRAY_MAX_VOLTAGE                5
#define IDENTIFIER_BIT_ARRAY_MAX_CURRENT_ZOP            6
#define IDENTIFIER_BIT_ARRAY_MIN_FREQUENCY_1_ACHR       7
#define IDENTIFIER_BIT_ARRAY_MIN_FREQUENCY_2_ACHR       8
#define IDENTIFIER_BIT_ARRAY_FREQUENCY_1_CHAPV          9
#define IDENTIFIER_BIT_ARRAY_FREQUENCY_2_CHAPV          10

#define READING_DR_FOR_MENU             1
#define READING_DR_FOR_USB              2
#define READING_DR_FOR_RS485            3
#define READING_PR_ERR_FOR_MENU         4
#define READING_PR_ERR_FOR_USB          5
#define READING_PR_ERR_FOR_RS485        6

#define READING_AR_FOR_MENU             1
#define READING_AR_FOR_USB              2
#define READING_AR_FOR_RS485            3

#define LABEL_START_RECORD_PR_ERR       0x5A

#define ETAP_NONE                                 0
#define ETAP_READ_MEMORY_INTO_BUFFER              1
#define ETAP_HAVE_READ_MEMORY_INTO_BUFFER         2
#define ETAP_MODIFY_AND_WRITE_BUFFER              3
#define ETAP_MODIFIED_AND_WRITTEN_BUFFER          4
#define ETAP_WRITE_BUFFER_INTO_MEMORY             5
#define ETAP_ERROR_BEFALLEN                       6

#define LABEL_START_RECORD_AR           0xAB

#define STATE_AR_TEMPORARY_BLOCK                  -1//�� ����� ������ ���� ������� �������� �������� ������ ����������� �����������
#define STATE_AR_NO_RECORD                        0 //�� ����� ������ ����� �� � ���������� ����������� �� ����������
#define STATE_AR_START                            1 //������ ������ ������ ����������� ����������
#define STATE_AR_SAVE_SRAM_AND_SAVE_FLASH         2 //���� ������ ����������� ���������� "�������� � ��������"
#define STATE_AR_ONLY_SAVE_FLASH                  3 //���� ������ ����������� ���������� "����� ��������", �� "��������" ��� ����������

/*
�������� � ����, �� ����������� �������� ���������� ����� ���� ���� 5�(����������
�����) + 25�(������������ �����) = 30�
��� ������ ��'�� ����
30(�)�50(������)�16(������� �� �����)�(8(������) + 11(�������� ����� ���������� �������))
�2(����� �� �����) = 912000(�����)
�� �� ���� 1(���� ���� ������� ������ )+7(����� ���� ����)+4(����� ����.��.�0)+
4(����� ����.��.��)+4(����� ����.��.��)+4(����� ���.�����������)+32(����� ���� ������) = 56 �����

!!!����� ��������� ���������� ����������� ����'������ �� ���� ������ �������� 2, 
��� �� ������ ���, �� ���� �� ������� ����� ��� ������ � DataFlash (����� ������ 
256 ����), �� �� �������� �������� ���� ������ ������� (����� 2-� ����): ��� � 
������� ��������, �� ���� ���� ����� ������ ����� �����������, � ����� ���� - 
��� ������ �����������. �� �������� ���� � ���������� ������ � ���������� �����������. 
���� ����� ���� �������� �������� ���� ����� ������� � ����� ������/������� 
��������� dataFlash � ������� 2, ����� ������ ������� � ������� 2, �� � ����� 
��������� ����������� ���������� �� ���� ������� 2.!!!
56 � ������� 2 - ���� ��� ���������!

����� ����� ������������� ����������� ������ 912000+56 = 912056(�����)
� ����������� ����, �� ����� ������� DF ��������� 512 ����, �� ������������
���������� ����� ��������� 912056/512 = 1781,359375 �������. ������� ���� ������� 
����� � 1782 ������� DF.

������� �������� SRAM ��������� 85(��)  - �� ������� � ��������� FSMC. ��� ��� ��������� 512 
���� � �������� SRAM � �������� SRAM ��������� 512(����)�85(��)=43,52(���)

DF(DataFlsh) ���������� � ����������� ��������������� ����� SPI1, ���� ���������
�� �������� ����� 30����/� � ������ 8 �� ����������. ����� �������� ����� 
��������� 3,75������/�.

� ����������� �������� ����� � ����� ������ ������� ��� ����

1)����� 512 ���� � DF ��������� "Main Memory Page Program Through Buffer" < 40,138(��)
2)������� ������� � ����� ��������� "Main Memory Page to Buffer Transfer" < 202(���)
3)����������� �� 512 ���� � ����� DF ��������� "Buffer Write" < 138(���)
4)����� ������ DF � DF ��������� "Buffer to Main Memory Page Program with 
Built-in Erase" < 40,002(��)

��� ������ ���� ������� ����� �������� ��������:
��������� 512 ���� � �������� SRAM � �������� SRAM < 43,52(���)
�������� ������� "Main Memory Page Program Through Buffer" < 40,070(��)
��������� ������ �� �������, ���� ������������� ���� 2�� (�� ��� ����������
DataFlash1/DataFlash2). ���� �� 41 �� �� ������� �� ����������� ����������.
��� ������������� �������� �������� 45 ��.

��� ����������� �� 512 ���� �� ���� ������� �����:
��������� 512 ���� � �������� SRAM � �������� SRAM < 43,52(���)
�������� ������� "Main Memory Page to Buffer Transfer" < 202(���)

����� 2(��) ����������� �������� �������� ��� ������� (���. ��������� ����) ���� 
���������� �� ���� � ����������� ���� �� 202(���) < 2 (�c)
�� ����� 2(�� (���. ��������� ����) ����� ��������� �������� ��������������� � �����.
����� �������� �� ���������� ������ 4(��)
����� ������� �������� ���� �� 202(���), � 4(��)

�������� ����������� ���� � ����� DF < 138(���) 

����� 2(��) ���������� �������� �������� ��� ������� (���. ��������� ����) ���� 
���������� �� ���� � ����������� ���� �� 202(���) < 2 (�c)
�� ����� 2(��) (���. ��������� ����) ����� ��������� �������� ������ � �����.
����� �������� �� ���������� ������ 4(��)
����� ������� �������� ���� �� 138(���), � 4(��)

�������� ������� "Buffer to Main Memory Page Program with 
Built-in Erase" < 40,002(��)
��������� ������ �� �������, ���� ������������� ���� 2�� (���. ��������� ����).
���� �� 41 �� �� ������� �� ����������� ����������.
�������� ���:
43,46(���)+4(��)+4(��)+41(��) = 50(��)
��� ������������� �������� �������� 51 ��.

���������� ����� ����� � ������� ������� ������ ������������ ������ ���������
(� ������������ ��������� ������) � �� ����� ������ ������������ ��������
���������, ��� ��� ����������� �� ���� ������������ - ������� ����������, ���� �������
����������� � ������ ����� - 51(��)

��� ��� ������ 1782 ������� ����� ����
1782(�������)�51(��) = 90�882(��)=90,882(�)

����� ������ ������ ������������� ����������� ������ ���� ������� 90,882(�)

�������� "����������" �������� ��������� � ����������� ��������� � ����������� �������:
(8(������) + 11(�������� ����� ���������� �������))�2(����� �� ��������)/1,25(��
- �������� �� ��������� ��� ������ 50�� � 16 ������� �� �����) =30,4 (����/��)
������� �� �������� � ������, �� �� �� ������ ��� ����� ��������� �� ������������

������� "��������" ������ ����������� ���������� � DF:
1782(�������)�512(���� �� �������)/90882(��) = 10,039215686274509803921568627451 (����/��)
������� �� �������� �� � ������, ���� �� �� ��� ������ ������������. �����, �������,
������� �� ���� �� �����, �� ������������ �������� � 
������� ��������� ������� ����� �� ������ �� ���� ����, �������, �� �� ������� 
���������� �� 51(��) - ��� �������� ������ ����� ����������� ��������� ������(
���. ��������� ����)).

���������� ��������� ������ ��� "���������" �� ��������� �� "��������
���� ������������ � ��������: 30,4 - 10,039215686274509803921568627451 = 20,360784313725490196078431372549(����/��)
�� ���������� ���� ������������� ���� ���������� "����������", ����� �����������
�������� ��� 25(�)  -������������ ��� ������������� ������.
25000(��)*20,360784313725490196078431372549(����/��) = 509019,60784313725490196078431373(����) < 509020(����)
509020(����)/512(����/����.) = 994,1796875(�������) < 995(�������)

��� ���� ����� ���� �� ���� ��, �� � ����� ����������� ���������� � 56 ����
���������� �� ������ (����� ������� ������, ���, ����������� �������������, ��'�
������). ��� ���� ������ ���������� "����������" � "��������" �� ������ �� �����
���������� "����������" � ����� �������� "��������" ���� � ����������. ��� ����, ��
������� "��������" ���� ������ �� ������� "����������" - �� � ����� "��������"
������ "����������" � ���� ��������� �� �� ����� �����.

�� ����� �������������� ������� � ����� �������, �� ����� ������ ����������� 
��������� ������� ������� ���� � ���������� � (����� ����������� ������ + 
(995 + 1) ������� DF). �� ���� ������� �� 996 ���������� ������������ � ����� 
��� ������������.

����� ����� �� ����
5(� - ����. ������. ���.)�50(����.�������)�16(����. �����.�� ���. ��� ��.�.)�(8(������) + 11(�������� ����� ���������� �������)) +996*[512(����)/2(���� �� ���� ������ ��������)](������� ������� ������� �� �������)=
= 76000 +996�256 = 330976

����� �� ���� ������� (������� ���������� ������ + ������� ���������� ��� ���������� �������).
�� ����� ��� ����, ��� �� ��������� ��� ������� ����� �� �� �� ������ �� �����, � 
��� �������� ���������� ��� ����� ������ ����
������ ������� ����������� � ������� ������� (������� ���������� ������ + 
������� ���������� ��� ���������� �������), �� �� ���������
���������, ���� ���������� "������� ��.������ + �������� ����� ���������� �������"
���� ����� �������� �� ������ ��������
996(�������)�256(���) = 254976 (���)

254976/(8 + 11)= 13419,789473684210526315789473684
���� ������ �� � ���� �����, �� ����� �������� ��������, ��� �/(8 + 11)
������ ���� �����, ������� � > 254976 - ����� ������ ��������� ����� X = 254980

����� �����
76000 + 254980 = 330980

!!!������������� �� ��� ������� ������ ������ ���������� 330980 �������� (����������,
��� �� ����� ������� ���������� �� ���� ����)!!!

*/

#define SIZE_BUFFER_FOR_AR    131062/*330980*/

#define CLEAN_AR_BIT          0
#define CLEAN_AR              (1 << CLEAN_AR_BIT)
#define CLEAN_DR_BIT          1
#define CLEAN_DR              (1 << CLEAN_DR_BIT)
#define CLEAN_PR_ERR_BIT      2
#define CLEAN_PR_ERR          (1 << CLEAN_PR_ERR_BIT)

#endif
