#ifndef __CONST_MODBUS_MEMORY_MAP__
#define __CONST_MODBUS_MEMORY_MAP__

#define SET_DATA_INTO_EDIT_TABLE          0
#define SET_DATA_IMMEDITATE               1

/*****************************************************/
/* Адресний простір тільки для читання (Блок 1) */
/*****************************************************/
#define M_ADDRESS_FIRST_RO_BLOCK_1        0

#define MA_SERIAL_NUMBER                  0
#define MA_NAME_CHAR_1_2                  1
#define MA_NAME_CHAR_3_4                  2
#define MA_NAME_CHAR_5_6                  3
#define MA_NAME_CHAR_7_8                  4
#define MA_NAME_CHAR_9_10                 5
#define MA_NAME_CHAR_11_12                6
#define MA_NAME_CHAR_13_14                7
#define MA_NAME_CHAR_15_16                8
#define MA_NAME_CHAR_17_18                9
#define MA_VERSION_SW                     10
#define MA_DATA_COMP_1                    11
#define MA_DATA_COMP_2                    12
#define MA_TIME_COMP                      13
#define MA_VERSION_GMM                    14
#define MA_ZBIRKA_SW                      15

#define M_ADDRESS_LAST_RO_BLOCK_1         15
/*****************************************************/

/*****************************************************/
/* Адресний простір виходів  */
/*****************************************************/
#define MA_OUTPUTS                        100
#define BIT_MA_OUTPUTS_BASE                   100
#define BIT_MA_OUTPUTS_FIRST                  100
#define BIT_MA_OUTPUTS_LAST                   (BIT_MA_OUTPUTS_FIRST + NUMBER_OUTPUTS - 1)
/*****************************************************/

/*****************************************************/
/* Адресний простір входів  */
/*****************************************************/
#define MA_INPUTS                         200
#define BIT_MA_INPUTS_BASE                    200
#define BIT_MA_INPUTS_FIRST                   200
#define BIT_MA_INPUTS_LAST                    (BIT_MA_INPUTS_FIRST + NUMBER_INPUTS - 1)
/*****************************************************/

/*****************************************************/
/* Адресний простір світлоіндикаторів  */
/*****************************************************/
#define MA_LEDS                           232
#define BIT_MA_LEDS_BASE                      232
#define BIT_MA_LEDS_FIRST                     232
#define BIT_MA_LEDS_LAST                      (BIT_MA_LEDS_FIRST + NUMBER_LEDS - 1)
/*****************************************************/

/*****************************************************/
/* Адресний простір встановлення уставок і витримок */
/*****************************************************/
#define M_ADDRESS_FIRST_SETPOINTS_PART1 300

#define MA_GROUP_USTAVOK                  300

#define MA_TYPE_MTZ1                      301
#define MA_TYPE_MTZ2                      302
#define MA_TYPE_MTZ3                      303
#define MA_TYPE_MTZ4                      304

#define M_ADDRESS_LAST_SETPOINTS_PART1    304

#define M_ADDRESS_FIRST_SETPOINTS_ZACHYSTIV 305
#define SHIFT_G1        0
#define SHIFT_G2        (2305 - M_ADDRESS_FIRST_SETPOINTS_ZACHYSTIV)
#define SHIFT_G3        (2438 - M_ADDRESS_FIRST_SETPOINTS_ZACHYSTIV)
#define SHIFT_G4        (2571 - M_ADDRESS_FIRST_SETPOINTS_ZACHYSTIV)

#define MA_STP_MTZ1                       305
#define MA_STP_MTZ1_N_VPERED              306
#define MA_STP_MTZ1_N_NAZAD               307
#define MA_STP_MTZ1_PO_NAPRUZI            308
#define MA_STP_MTZ1_U                     309
#define MA_STP_MTZ1_ANGLE                 310
#define MA_TO_MTZ1                        311
#define MA_TO_MTZ1_N_VPERED               312
#define MA_TO_MTZ1_N_NAZAD                313
#define MA_TO_MTZ1_PO_NAPRUZI             314
#define MA_STP_MTZ2                       315
#define MA_STP_MTZ2_N_VPERED              316
#define MA_STP_MTZ2_N_NAZAD               317
#define MA_STP_MTZ2_PO_NAPRUZI            318
#define MA_STP_MTZ2_U                     319
#define MA_STP_MTZ2_ANGLE                 320
#define MA_TO_MTZ2                        321
#define MA_TO_MTZ2_N_VPERED               322
#define MA_TO_MTZ2_N_NAZAD                323
#define MA_TO_MTZ2_PO_NAPRUZI             324
#define MA_TO_MTZ2_VVID_PR                325
#define MA_TO_MTZ2_PR                     326
#define MA_TO_MTZ2_N_VPERED_PR            327
#define MA_TO_MTZ2_N_NAZAD_PR             328
#define MA_TO_MTZ2_PO_NAPRUZI_PR          329
#define MA_STP_MTZ3                       330
#define MA_STP_MTZ3_N_VPERED              331
#define MA_STP_MTZ3_N_NAZAD               332
#define MA_STP_MTZ3_PO_NAPRUZI            333
#define MA_STP_MTZ3_U                     334
#define MA_STP_MTZ3_ANGLE                 335
#define MA_TO_MTZ3                        336
#define MA_TO_MTZ3_N_VPERED               337
#define MA_TO_MTZ3_N_NAZAD                338
#define MA_TO_MTZ3_PO_NAPRUZI             339
#define MA_STP_MTZ4                       340
#define MA_STP_MTZ4_N_VPERED              341
#define MA_STP_MTZ4_N_NAZAD               342
#define MA_STP_MTZ4_PO_NAPRUZI            343
#define MA_STP_MTZ4_U                     344
#define MA_STP_MTZ4_ANGLE                 345
#define MA_TO_MTZ4                        346
#define MA_TO_MTZ4_N_VPERED               347
#define MA_TO_MTZ4_N_NAZAD                348
#define MA_TO_MTZ4_PO_NAPRUZI             349

#define MA_STP_NZZ1_3I0                   352
#define MA_TO_NZZ1_3I0                    353

#define MA_STP_NZZ1_3U0                   356
#define MA_TO_NZZ1_3U0                    357

#define MA_TO_NZZ1                        359

#define MA_STP_ZOP1                       372
#define MA_TO_ZOP1                        373

#define MA_STP_UMIN1                      378
#define MA_TO_UMIN1                       379
#define MA_STP_UMIN2                      380
#define MA_TO_UMIN2                       381
#define MA_STP_BLK_UMIN1_BY_I             382
#define MA_STP_BLK_UMIN2_BY_I             383

#define MA_STP_UMAX1                      384
#define MA_TO_UMAX1                       385
#define MA_STP_UMAX2                      386
#define MA_TO_UMAX2                       387

#define MA_STP_U_OL                       391
#define MA_STP_U_RL                       392
#define MA_TO_U_OL                        393
#define MA_TO_U_RL                        394

#define MA_STP_UROV                       403
#define MA_TO_UROV1                       404
#define MA_TO_UROV2                       405

#define MA_STP_AVR_MIN1                   406
#define MA_STP_AVR_MAX1                   407
#define MA_STP_AVR_MIN2                   408
#define MA_STP_AVR_MAX2                   409
#define MA_TO_AVR_RL                      410
#define MA_TO_AVR_OL                      411
#define MA_STP_KRATN_AVR                  412
#define MA_TO_AVR_ZAVERSHENNJA            413
#define MA_TO_AVR_RESET_BLK               414

#define MA_TO_APV_BLOCK_VID_VV            415
#define MA_TO_APV_CYCLE_1                 416
#define MA_TO_APV_CYCLE_2                 417
#define MA_TO_APV_CYCLE_3                 418
#define MA_TO_APV_CYCLE_4                 419
#define MA_TO_APV_BLOCK_VID_APV1          420
#define MA_TO_APV_BLOCK_VID_APV2          421
#define MA_TO_APV_BLOCK_VID_APV3          422
#define MA_TO_APV_BLOCK_VID_APV4          423

#define MA_STP_APV_ZMN1                   424
#define MA_STP_APV_ZMN2                   425
#define MA_TO_APV_ZMN1                    426
#define MA_TO_APV_ZMN2                    427
#define MA_STP_KRATN_APV_ZMN              428
#define MA_TO_APV_ZMN_ZAVERSHENNJA        429

#define MA_STP_ACHR_F_RAB                 430
#define MA_STP_CHAPV_F_RAB                431
#define MA_STP_ACHR_CHAPV_UF1             432
#define MA_STP_ACHR_CHAPV_UF2             433
#define MA_TO_ACHR_1                      434
#define MA_TO_ACHR_2                      435
#define MA_TO_CHAPV_1                     436
#define MA_TO_CHAPV_2                     437

#define M_ADDRESS_LAST_SETPOINTS_ZACHYSTIV 437

#define M_ADDRESS_FIRST_SETPOINTS_CONTINUE 438

#define MA_LINE_1                         440
#define MA_DOVGYNA_1_1                    441
#define MA_OPIR_1_1                       442
#define MA_DOVGYNA_1_2                    443
#define MA_OPIR_1_2                       444
#define MA_DOVGYNA_1_3                    445
#define MA_OPIR_1_3                       446
#define MA_DOVGYNA_1_4                    447
#define MA_OPIR_1_4                       448
#define MA_DOVGYNA_1_5                    449
#define MA_OPIR_1_5                       450
#define MA_DOVGYNA_1_6                    451
#define MA_OPIR_1_6                       452
#define MA_DOVGYNA_1_7                    453
#define MA_OPIR_1_7                       454
#define MA_DOVGYNA_1_8                    455
#define MA_OPIR_1_8                       456
#define MA_LINE_2                         457
#define MA_DOVGYNA_2_1                    458
#define MA_OPIR_2_1                       459
#define MA_DOVGYNA_2_2                    460
#define MA_OPIR_2_2                       461
#define MA_DOVGYNA_2_3                    462
#define MA_OPIR_2_3                       463
#define MA_DOVGYNA_2_4                    464
#define MA_OPIR_2_4                       465
#define MA_DOVGYNA_2_5                    466
#define MA_OPIR_2_5                       467
#define MA_DOVGYNA_2_6                    468
#define MA_OPIR_2_6                       469
#define MA_DOVGYNA_2_7                    470
#define MA_OPIR_2_7                       471
#define MA_DOVGYNA_2_8                    472
#define MA_OPIR_2_8                       473

#define MA_TN1                            475

#define MA_TT                             477
#define MA_T0                             478

#define MA_TO_SWCH_UDL_BLK_ON             479
#define MA_TO_SWCH_ON                     480
#define MA_TO_SWCH_OFF                    481
#define MA_TO_FAULT_CONTROL_CIRCUIT       482

#define MA_STP_Inom                       484
#define MA_STP_RKS_Inom                   485
#define MA_STP_Inom_vymk                  486
#define MA_STP_RKS_Inom_vymk              487
#define MA_STP_POCHATKOVYJ_RESURS_LSW     488
#define MA_STP_POCHATKOVYJ_RESURS_MSW     489
#define MA_STP_KRYTYCHNYJ_RESURS          490
#define MA_POCHATKOVA_K_VYMK_LSW          491
#define MA_POCHATKOVA_K_VYMK_MSW          492

#define MA_UVV_TYPE_SIGNAL_INPUT          500
#define MA_UVV_TYPE_INPUT                 501
#define MA_UVV_TYPE_OUTPUT                502
#define MA_TYPE_DF                        503
#define MA_UVV_TYPE_LED                   504

#define MA_DOPUSK_DV_1                    508
#define MA_DOPUSK_DV_2                    509
#define MA_DOPUSK_DV_3                    510
#define MA_DOPUSK_DV_4                    511
#define MA_DOPUSK_DV_5                    512
#define MA_DOPUSK_DV_6                    513
#define MA_DOPUSK_DV_7                    514
#define MA_DOPUSK_DV_8                    515
#define MA_DOPUSK_DV_9                    516
#define MA_DOPUSK_DV_10                   517

#define MA_DF_PAUSE_1                     524
#define MA_DF_PAUSE_2                     525
#define MA_DF_PAUSE_3                     526
#define MA_DF_PAUSE_4                     527
#define MA_DF_PAUSE_5                     528
#define MA_DF_PAUSE_6                     529
#define MA_DF_PAUSE_7                     530
#define MA_DF_PAUSE_8                     531
#define MA_DF_WORK_1                      532
#define MA_DF_WORK_2                      533
#define MA_DF_WORK_3                      534
#define MA_DF_WORK_4                      535
#define MA_DF_WORK_5                      536
#define MA_DF_WORK_6                      537
#define MA_DF_WORK_7                      538
#define MA_DF_WORK_8                      539

#define MA_CONTROL_BASE                   550
#define BIT_MA_CONTROL_BASE                   55000

#define MA_CONTROL_MTZ                    550
#define BIT_MA_CONTROL_MTZ_BASE               55000
#define BIT_MA_CONTROL_MTZ1                   55000
#define BIT_MA_CONTROL_MTZ2                   55001
#define BIT_MA_CONTROL_MTZ3                   55002
#define BIT_MA_CONTROL_MTZ4                   55003
#define BIT_MA_CONTROL_MTZ2_PRYSKORENNJA      55004
#define BIT_MA_CONTROL_MTZ2_PRYSKORENA        55005
#define BIT_MA_CONTROL_MTZ1_N_VPERED          55006
#define BIT_MA_CONTROL_MTZ1_N_NAZAD           55007
#define BIT_MA_CONTROL_MTZ2_N_VPERED          55008
#define BIT_MA_CONTROL_MTZ2_N_NAZAD           55009
#define BIT_MA_CONTROL_MTZ3_N_VPERED          55010
#define BIT_MA_CONTROL_MTZ3_N_NAZAD           55011
#define BIT_MA_CONTROL_MTZ4_N_VPERED          55012
#define BIT_MA_CONTROL_MTZ4_N_NAZAD           55013
#define BIT_MA_CONTROL_MTZ_NESPR_KIL_NAPR     55014     

#define MA_CONTROL_ZDZ                    551
#define BIT_MA_CONTROL_ZDZ_BASE               55016
#define BIT_MA_CONTROL_ZDZ                    55016
#define BIT_MA_CONTROL_ZDZ_STARTED_FROM_MTZ1  55017
#define BIT_MA_CONTROL_ZDZ_STARTED_FROM_MTZ2  55018
#define BIT_MA_CONTROL_ZDZ_STARTED_FROM_MTZ3  55019
#define BIT_MA_CONTROL_ZDZ_STARTED_FROM_MTZ4  55020

#define MA_CONTROL_NZZ                    552
#define BIT_MA_CONTROL_NZZ_BASE               55032
#define BIT_MA_CONTROL_NZZ_3I0                55032

#define BIT_MA_CONTROL_NZZ_SECTOR             55034
#define BIT_MA_CONTROL_NZZ                    55035
#define BIT_MA_CONTROL_NZZ_3U0                55036
#define BIT_MA_CONTROL_NZZ_TYPE               55037

#define MA_CONTROL_ZOP                    554
#define BIT_MA_CONTROL_ZOP_BASE               55064
#define BIT_MA_CONTROL_ZOP1                   55064

#define MA_CONTROL_ACHR_CHAPV             555
#define BIT_MA_CONTROL_ACHR_CHAPV_BASE        55080
#define BIT_MA_CONTROL_ACHR_STATE             55080
#define BIT_MA_CONTROL_CHAPV_STATE            55081
#define BIT_MA_CONTROL_CHAPV_VID_DV_STATE     55082

#define MA_CONTROL_UMIN                   556
#define BIT_MA_CONTROL_UMIN_BASE              55096
#define BIT_MA_CONTROL_UMIN1                  55096
#define BIT_MA_CONTROL_UMIN2                  55097
#define BIT_MA_CONTROL_PO_UMIN1_AND_OR        55098
#define BIT_MA_CONTROL_PO_UMIN2_AND_OR        55099
#define BIT_MA_CONTROL_BLK_UMIN1_BY_U         55100
#define BIT_MA_CONTROL_BLK_UMIN2_BY_U         55101
#define BIT_MA_CONTROL_BLK_UMIN1_BY_I         55102
#define BIT_MA_CONTROL_BLK_UMIN2_BY_I         55103

#define MA_CONTROL_UMAX                   557
#define BIT_MA_CONTROL_UMAX_BASE              55112
#define BIT_MA_CONTROL_UMAX1                  55112
#define BIT_MA_CONTROL_UMAX2                  55113
#define BIT_MA_CONTROL_PO_UMAX1_AND_OR        55114
#define BIT_MA_CONTROL_PO_UMAX2_AND_OR        55115

#define MA_CONTROL_558                    558
#define BIT_MA_CONTROL_558_BASE               55128

#define BIT_MA_CONTROL_PHASE_LINE             55129
#define BIT_MA_CONTROL_3U0_Ubc_TN2            55130
#define BIT_MA_CONTROL_APV_ZMN                55131
#define BIT_MA_CONTROL_U_OL                   55132
#define BIT_MA_CONTROL_U_RL                   55133

#define MA_CONTROL_APV                    560
#define BIT_MA_CONTROL_APV_BASE               55160
#define BIT_MA_CONTROL_APV_CYCLE1             55160
#define BIT_MA_CONTROL_APV_CYCLE2             55161
#define BIT_MA_CONTROL_APV_CYCLE3             55162
#define BIT_MA_CONTROL_APV_CYCLE4             55163
#define BIT_MA_CONTROL_APV_STARTED_FROM_MTZ1  55164
#define BIT_MA_CONTROL_APV_STARTED_FROM_MTZ2  55165
#define BIT_MA_CONTROL_APV_STARTED_FROM_MTZ3  55166
#define BIT_MA_CONTROL_APV_STARTED_FROM_MTZ4  55167

#define MA_CONTROL_UROV_PART1             561
#define BIT_MA_CONTROL_UROV_BASE_PART1        55176
#define BIT_MA_CONTROL_UROV_STATE             55176
#define BIT_MA_CONTROL_UROV_STARTED_FROM_MTZ1 55177
#define BIT_MA_CONTROL_UROV_STARTED_FROM_MTZ2 55178
#define BIT_MA_CONTROL_UROV_STARTED_FROM_MTZ3 55179
#define BIT_MA_CONTROL_UROV_STARTED_FROM_MTZ4 55180
#define BIT_MA_CONTROL_UROV_STARTED_FROM_UMAX1  55181
#define BIT_MA_CONTROL_UROV_STARTED_FROM_UMAX2  55182
#define BIT_MA_CONTROL_UROV_STARTED_FROM_UMIN1  55183
#define BIT_MA_CONTROL_UROV_STARTED_FROM_UMIN2  55184
#define BIT_MA_CONTROL_UROV_STARTED_FROM_ZOP1 55185

#define BIT_MA_CONTROL_UROV_STARTED_FROM_NZZ  55187
#define BIT_MA_CONTROL_UROV_STARTED_FROM_3I0  55188

#define BIT_MA_CONTROL_UROV_STARTED_FROM_3U0  55190

#define MA_CONTROL_UROV_PART2             562
#define BIT_MA_CONTROL_UROV_BASE_PART2        55192

#define BIT_MA_CONTROL_UROV_STARTED_FROM_ZDZ  55194
#define BIT_MA_CONTROL_UROV_STARTED_FROM_ACHR 55195

#define MA_CONTROL_AVR                    563
#define BIT_MA_CONTROL_AVR_BASE               55208
#define BIT_MA_CONTROL_AVR                    55208
#define BIT_MA_CONTROL_AVR_OTKL_BLK_VID_ZAHYSTIV 55209

#define MA_CONTROL_CTRL_VV                564
#define BIT_MA_CONTROL_CTRL_VV_BASE            55224
#define BIT_MA_CONTROL_CTRL_VV_STATE           55224

#define BIT_MA_CONTROL_CTRL_BLK_ON_CB_MISCEVE  55227
#define BIT_MA_CONTROL_CTRL_BLK_OFF_CB_MISCEVE 55228
#define BIT_MA_CONTROL_CTRL_FB_ACTIVATION      55229
#define BIT_MA_CONTROL_CTRL_RESURS_VV          55230
#define BIT_MA_CONTROL_CTRL_READY_TU           55231
#define BIT_MA_CONTROL_CTRL_WINDOW_OFF_CB      55232

#define MA_CONTROL_VMP                    565
#define BIT_MA_CONTROL_VMP_BASE                55240
#define BIT_MA_CONTROL_VMP_STATE               55240

#define MA_CONFIGURATION_PART1            566
#define BIT_MA_CONFIGURATION_BASE_PART1        55256
#define BIT_MA_CONFIGURATION_MTZ               55256
#define BIT_MA_CONFIGURATION_ZDZ               55257
#define BIT_MA_CONFIGURATION_ZZ                55258

#define BIT_MA_CONFIGURATION_ZOP               55260
#define BIT_MA_CONFIGURATION_ACHR_CHAPV        55261
#define BIT_MA_CONFIGURATION_UMIN              55262
#define BIT_MA_CONFIGURATION_UMAX              55263

#define BIT_MA_CONFIGURATION_APV_ZMN           55266
#define BIT_MA_CONFIGURATION_KROL              55267

#define BIT_MA_CONFIGURATION_APV               55269
#define BIT_MA_CONFIGURATION_UROV              55270
#define BIT_MA_CONFIGURATION_AVR               55271

#define MA_CONFIGURATION_PART2            567
#define BIT_MA_CONFIGURATION_BASE_PART2        55272
#define BIT_MA_CONFIGURATION_VMP               55272

#define MA_CONTROL_LAST                   567
#define BIT_MA_CONTROL_LAST                   (BIT_MA_CONTROL_BASE + ((MA_CONTROL_LAST - MA_CONTROL_BASE + 1) << 4) - 1)

/***/
#define MA_TO_DEACTIVATION_PASSWORD_INTERFACE 569
#define MA_PASSWORD_INTERFACE                 570
/***/

#define MA_LANGUAGE_MENU                      571


#define MA_SPEED_RS485                        573
#define MA_STOP_BITS_RS485                    574
#define MA_PARE_RS485                         575
#define MA_TIMEOUT_RS485                      576
#define MA_LOGICAL_ADDRESS                    577

#define MA_NAME_OF_CELL_CHARS_01_02           585
#define MA_NAME_OF_CELL_CHARS_03_04           586
#define MA_NAME_OF_CELL_CHARS_05_06           587
#define MA_NAME_OF_CELL_CHARS_07_08           588
#define MA_NAME_OF_CELL_CHARS_09_10           589
#define MA_NAME_OF_CELL_CHARS_11_12           590
#define MA_NAME_OF_CELL_CHARS_13_14           591
#define MA_NAME_OF_CELL_CHARS_15_16           592

#define M_ADDRESS_LAST_SETPOINTS_CONTINUE     592
/*****************************************************/

/*****************************************************/
/* Адресний простір дати і часу */
/*****************************************************/
#define M_ADDRESS_FIRST_TIME_AND_DATA         593

#define MA_YEAR                               593
#define MA_MONTH                              594
#define MA_DAY                                595
#define MA_HOUR                               596
#define MA_MINUTE                             597
#define MA_SECOND                             598
#define MA_MILISECOND                         599

#define M_ADDRESS_LAST_TIME_AND_DATA          599
/*****************************************************/

/*****************************************************/
/* Текучі активні функції */
/*****************************************************/
#define M_ADDRESS_FIRST_CURRENT_AF            600
#define BIT_MA_CURRENT_AF_BASE                  60000

#define BIT_MA_1_GRUPA_USTAVOK                  60000
#define BIT_MA_2_GRUPA_USTAVOK                  60001
#define BIT_MA_3_GRUPA_USTAVOK                  60002
#define BIT_MA_4_GRUPA_USTAVOK                  60003
#define BIT_MA_BLOCK_MTZ1                       60004
#define BIT_MA_MTZ1                             60005
#define BIT_MA_PO_MTZ1                          60006
#define BIT_MA_PO_MTZPN1                        60007
#define BIT_MA_PO_MTZN1_VPERED                  60008
#define BIT_MA_PO_MTZN1_NAZAD                   60009
#define BIT_MA_SECTOR_VPERED_MTZN1              60010
#define BIT_MA_SECTOR_NAZAD_MTZN1               60011
#define BIT_MA_PO_U_MTZPN1                      60012

#define BIT_MA_BLOCK_MTZ2                       60016
#define BIT_MA_MTZ2                             60017
#define BIT_MA_PO_MTZ2                          60018
#define BIT_MA_PO_MTZPN2                        60019
#define BIT_MA_PO_MTZN2_VPERED                  60020
#define BIT_MA_PO_MTZN2_NAZAD                   60021
#define BIT_MA_SECTOR_VPERED_MTZN2              60022
#define BIT_MA_SECTOR_NAZAD_MTZN2               60023
#define BIT_MA_PO_U_MTZPN2                      60024
#define BIT_MA_BLOCK_USK_MTZ2                   60025

#define BIT_MA_BLOCK_MTZ3                       60032
#define BIT_MA_MTZ3                             60033
#define BIT_MA_PO_MTZ3                          60034
#define BIT_MA_PO_MTZPN3                        60035
#define BIT_MA_PO_MTZN3_VPERED                  60036
#define BIT_MA_PO_MTZN3_NAZAD                   60037
#define BIT_MA_SECTOR_VPERED_MTZN3              60038
#define BIT_MA_SECTOR_NAZAD_MTZN3               60039
#define BIT_MA_PO_U_MTZPN3                      60040

#define BIT_MA_BLOCK_MTZ4                       60048
#define BIT_MA_MTZ4                             60049
#define BIT_MA_PO_MTZ4                          60050
#define BIT_MA_PO_MTZPN4                        60051
#define BIT_MA_PO_MTZN4_VPERED                  60052
#define BIT_MA_PO_MTZN4_NAZAD                   60053
#define BIT_MA_SECTOR_VPERED_MTZN4              60054
#define BIT_MA_SECTOR_NAZAD_MTZN4               60055
#define BIT_MA_PO_U_MTZPN4                      60056

#define BIT_MA_NCN_MTZ                          60058
#define BIT_MA_PO_BLOCK_U_MTZN                  60059

#define BIT_MA_PUSK_ZDZ_VID_DV                  60061
#define BIT_MA_ZDZ                              60062

#define BIT_MA_BLOCK_NZZ                        60064
#define BIT_MA_PO_NZZ                           60065
#define BIT_MA_NZZ                              60066
#define BIT_MA_PO_ZZ1_3I0                       60067
#define BIT_MA_ZZ1_3I0                          60068

#define BIT_MA_PO_ZZ_3U0                        60071
#define BIT_MA_ZZ_3U0                           60072
#define BIT_MA_SECTOR_NZZ                       60073

#define BIT_MA_BLOCK_ZOP                        60096
#define BIT_MA_ZOP                              60097
#define BIT_MA_PO_ZOP                           60098

#define BIT_MA_BLOCK_UMIN1                      60112
#define BIT_MA_PO_UBLK_UMIN1                    60113
#define BIT_MA_PO_IBLK_UMIN1                    60114
#define BIT_MA_UMIN1                            60115
#define BIT_MA_PO_UMIN1                         60116
#define BIT_MA_BLOCK_UMIN2                      60117
#define BIT_MA_PO_UBLK_UMIN2                    60118
#define BIT_MA_PO_IBLK_UMIN2                    60119
#define BIT_MA_UMIN2                            60120
#define BIT_MA_PO_UMIN2                         60121
#define BIT_MA_START_UMIN1                      60122
#define BIT_MA_START_UMIN2                      60123

#define BIT_MA_BLOCK_UMAX1                      60128
#define BIT_MA_UMAX1                            60129
#define BIT_MA_PO_UMAX1                         60130
#define BIT_MA_BLOCK_UMAX2                      60131
#define BIT_MA_UMAX2                            60132
#define BIT_MA_PO_UMAX2                         60133

#define M_ADDRESS_APV_ZMN                     610
#define BIT_MA_APV_ZMN_BASE                     60160
#define BIT_MA_RESET_BLOCK_APV_ZMN              60160
#define BIT_MA_BLOCK_APV_ZMN                    60161
#define BIT_MA_PO_UAPV_ZMN1                     60162
#define BIT_MA_PO_UAPV_ZMN2                     60163
#define BIT_MA_PO_APV_ZMN                       60164
#define BIT_MA_APV_ZMN                          60165
#define BIT_MA_BLOCK_KRATN_APV_ZMN              60166
#define BIT_MA_BLOCK_APV_ZMN_VID_ZAKHYSTIV      60167

#define BIT_MA_PO_U_OL                          60176
#define BIT_MA_U_OL                             60177
#define BIT_MA_PO_U_RL                          60178
#define BIT_MA_U_RL                             60179

#define BIT_MA_STAT_BLK_APV                     60208
#define BIT_MA_APV                              60209
#define BIT_MA_APV2                             60210
#define BIT_MA_APV3                             60211
#define BIT_MA_APV4                             60212
#define BIT_MA_APV_WORK                         60213

#define BIT_MA_PUSK_UROV_VID_DV                 60224
#define BIT_MA_UROV1                            60225
#define BIT_MA_UROV2                            60226
#define BIT_MA_PO_UROV                          60227

#define M_ADDRESS_AVR                         615
#define BIT_MA_AVR_BASE                         60240
#define BIT_MA_OTKL_AVR                         60240
#define BIT_MA_SBROS_BLOCK_AVR                  60241
#define BIT_MA_STAT_BLOCK_AVR                   60242
#define BIT_MA_PO_UAVR_MIN1                     60243
#define BIT_MA_PO_UAVR_MAX1                     60244
#define BIT_MA_PO_UAVR_MIN2                     60245
#define BIT_MA_PO_UAVR_MAX2                     60246
#define BIT_MA_BLOCK_AVR_VID_ZAKHYSTIV          60247
#define BIT_MA_BLOCK_KRATN_AVR                  60248
#define BIT_MA_PUSK_AVR                         60249

#define BIT_MA_ACHR_CHAPV_VID_DV                60256
#define BIT_MA_BLOCK_ACHR                       60257
#define BIT_MA_BLOCK_CHAPV_VID_U                60258
#define BIT_MA_PO_F1_ACHR                       60259
#define BIT_MA_PO_F2_ACHR                       60260
#define BIT_MA_F1_ACHR_CHAPV                    60261
#define BIT_MA_F2_ACHR_CHAPV                    60262
#define BIT_MA_ACHR_CHAPV                       60263
#define BIT_MA_RAZR_CHAPV                       60264
#define BIT_MA_PO_F1_CHAPV                      60265
#define BIT_MA_PO_F2_CHAPV                      60266

#define M_ADDRESS_DF                          617
#define BIT_MA_DF_BASE                          60272
#define BIT_MA_INPUT_DF1                        60272
#define BIT_MA_INPUT_DF2                        60273
#define BIT_MA_INPUT_DF3                        60274
#define BIT_MA_INPUT_DF4                        60275
#define BIT_MA_INPUT_DF5                        60276
#define BIT_MA_INPUT_DF6                        60277
#define BIT_MA_INPUT_DF7                        60278
#define BIT_MA_INPUT_DF8                        60279
#define BIT_MA_OUTPUT_DF1                       60280
#define BIT_MA_OUTPUT_DF2                       60281
#define BIT_MA_OUTPUT_DF3                       60282
#define BIT_MA_OUTPUT_DF4                       60283
#define BIT_MA_OUTPUT_DF5                       60284
#define BIT_MA_OUTPUT_DF6                       60285
#define BIT_MA_OUTPUT_DF7                       60286
#define BIT_MA_OUTPUT_DF8                       60287

#define M_ADDRESS_DT                          618
#define BIT_MA_DT_BASE                          60288
#define BIT_MA_DT1_SET                          60288
#define BIT_MA_DT1_RESET                        60289
#define BIT_MA_DT2_SET                          60290
#define BIT_MA_DT2_RESET                        60291
#define BIT_MA_DT3_SET                          60292
#define BIT_MA_DT3_RESET                        60293
#define BIT_MA_DT4_SET                          60294
#define BIT_MA_DT4_RESET                        60295
#define BIT_MA_DT1_OUT                          60296
#define BIT_MA_DT2_OUT                          60297
#define BIT_MA_DT3_OUT                          60298
#define BIT_MA_DT4_OUT                          60299

#define M_ADDRESS_COMMAND_BASE                619
#define BIT_MA_COMMAND_BASE                     60304
#define BIT_MA_VKL_VV                           60304
#define BIT_MA_OTKL_VV                          60305
#define BIT_MA_BLOCK_VKL_VV                     60306

#define BIT_MA_WORK_BO                          60308
#define BIT_MA_WORK_BV                          60309
#define BIT_MA_STATE_VV                         60310
#define BIT_MA_GEAR_VV                          60311
#define BIT_MA_CONTROL_VKL                      60312
#define BIT_MA_CONTROL_VIDKL                    60313
#define BIT_MA_PEREVYSHCHENNJA_Inom_VYMK        60314
#define BIT_MA_KRYTYCHNYJ_RESURS_VYMYKACHA      60315
#define BIT_MA_VYCHERPANYJ_RESURS_VYMYKACHA     60316
#define BIT_MA_DEFECT                           60317
#define BIT_MA_AVAR_DEFECT                      60318
#define BIT_MA_RESET_LEDS                       60319
#define BIT_MA_RESET_RELES                      60320
#define BIT_MA_RESET_GENERAL_AF                 60321
#define BIT_MA_RESET_RESURS_VYMYKACHA           60322
#define BIT_MA_SETTINGS_CHANGED                 60323
#define BIT_MA_PASSWORD_SET                     60324
#define BIT_MA_MISCEVE_DYSTANCIJNE              60325
#define BIT_MA_WORK_A_REJESTRATOR               60326
#define BIT_MA_WORK_D_REJESTRATOR               60327

#define BIT_MA_OTKL_VID_ZOVN_ZAHYSTIV           60332                         

#define BIT_MA_DVERI_SHAFY_UPR_VIDKR            60336
#define BIT_MA_ACUMUL_BATAREJA_ROZRJADGENA      60337
#define BIT_MA_REZERVTE_GYVLENNJA               60338
#define BIT_MA_VIDKL_VID_ZAKHYSTIV              60339
#define BIT_MA_BLK_GRUP_USTAVOK_VID_ZACHYSTIV   60340
#define BIT_MA_INVERS_DV_GRUPA_USTAVOK          60341
#define BIT_MA_READY_TU                         60342
#define BIT_MA_RESET_BLOCK_READY_TU_VID_ZAHYSTIV 60343

#define M_ADDRESS_LAST_CURRENT_AF             621
#define BIT_MA_CURRENT_AF_LAST                  (BIT_MA_CURRENT_AF_BASE + ((M_ADDRESS_LAST_CURRENT_AF - M_ADDRESS_FIRST_CURRENT_AF + 1) << 4) - 1)
/*****************************************************/

/*****************************************************/
/* Загальні активні функції */
/*****************************************************/
#define M_ADDRESS_FIRST_GENERAL_AF            622
#define BIT_MA_GENERAL_AF_BASE                  60352

#define M_ADDRESS_LAST_GENERAL_AF             643
#define BIT_MA_GENERAL_AF_LAST                  (BIT_MA_GENERAL_AF_BASE + ((M_ADDRESS_LAST_GENERAL_AF - M_ADDRESS_FIRST_GENERAL_AF + 1) << 4) - 1)
/*****************************************************/

/*****************************************************/
/* Митєві вимірювання розраховані фетодом перетворення Фур'є */
/*****************************************************/
#define M_ADDRESS_FIRST_MEASUREMENTS_1        644

#define OFFSET_MEASUREMENT_UA_1                 0
#define OFFSET_MEASUREMENT_UB_1                 1
#define OFFSET_MEASUREMENT_UC_1                 2
#define OFFSET_MEASUREMENT_IA_1                 3
#define OFFSET_MEASUREMENT_IB_1                 4
#define OFFSET_MEASUREMENT_IC_1                 5
#define OFFSET_ACTIVE_POWER                     6
#define OFFSET_REACTIVE_POWER                   7
#define OFFSET_FULL_POWER                       8
#define OFFSET_COS_PHI                          9
#define OFFSET_MEASUREMENT_3I0                  10
#define OFFSET_FREQUENCY_1                      11
#define OFFSET_EA_PLUS_LWB                      12
#define OFFSET_EA_PLUS_MWB                      13
#define OFFSET_EA_MINUS_LWB                     14
#define OFFSET_EA_MINUS_MWB                     15
#define OFFSET_ER_1_LWB                         16
#define OFFSET_ER_1_MWB                         17
#define OFFSET_ER_2_LWB                         18
#define OFFSET_ER_2_MWB                         19
#define OFFSET_ER_3_LWB                         20
#define OFFSET_ER_3_MWB                         21
#define OFFSET_ER_4_LWB                         22
#define OFFSET_ER_4_MWB                         23
#define OFFSET_MEASUREMENT_UAB_1                24
#define OFFSET_MEASUREMENT_UBC_1                25
#define OFFSET_MEASUREMENT_UCA_1                26
#define OFFSET_MEASUREMENT_3U0_1                27

#define OFFSET_MEASUREMENT_3I0_HIGH_GARM        29
#define OFFSET_MEASUREMENT_I1                   30
#define OFFSET_MEASUREMENT_I2                   31


#define OFFSET_MEASUREMENT_UAB_2                34
#define OFFSET_MEASUREMENT_UBC_2                35

#define OFFSET_FREQUENCY_2                      38

#define OFFSET_BASE_CANAL_FOR_ANGLE             40
#define OFFSET_ANGLE_UA_1                       41
#define OFFSET_ANGLE_UB_1                       42
#define OFFSET_ANGLE_UC_1                       43
#define OFFSET_ANGLE_UAB_1                      44
#define OFFSET_ANGLE_UBC_1                      45
#define OFFSET_ANGLE_UCA_1                      46
#define OFFSET_ANGLE_3U0_1                      47
#define OFFSET_ANGLE_UAB_2                      48
#define OFFSET_ANGLE_UBC_2                      49
#define OFFSET_ANGLE_IA_1                       50
#define OFFSET_ANGLE_IB_1                       51
#define OFFSET_ANGLE_IC_1                       52
#define OFFSET_ANGLE_3I0                        53

//#define OFFSET_ANGLE_3I0_3U0                    56


#define M_ADDRESS_LAST_MEASUREMENTS_1         702
/*****************************************************/

/**************Лічильник ресурсів********************/
#define M_COUNTER_FIRST                       703

#define MA_COUNTER_VIDKLJUCHENNJA_LSW         703
#define MA_COUNTER_VIDKLJUCHENNJA_MSW         704
#define MA_COUNTER_VYMYKACHA_LSW              705
#define MA_COUNTER_VYMYKACHA_MSW              706

#define M_COUNTER_LAST                        706

/*****************************************************/

/*****************************************************/
/* Вимірювання в момент роботи дискретного реєстратора*/
/*****************************************************/
#define MEASUREMENTS_DR_WIDTH                 28 
#define M_ADDRESS_FIRST_MEASUREMENTS_DR       707

#define DR_OFFSET_MEASUREMENT_UA_1            0
#define DR_OFFSET_MEASUREMENT_UB_1            1
#define DR_OFFSET_MEASUREMENT_UC_1            2
#define DR_OFFSET_MEASUREMENT_IA_1            3
#define DR_OFFSET_MEASUREMENT_IB_1            4
#define DR_OFFSET_MEASUREMENT_IC_1            5
#define DR_OFFSET_MEASUREMENT_UAB_1           6
#define DR_OFFSET_MEASUREMENT_UBC_1           7
#define DR_OFFSET_MEASUREMENT_UCA_1           8
#define DR_OFFSET_MEASUREMENT_3U0_1           9
#define DR_OFFSET_MEASUREMENT_3I0             10

#define DR_OFFSET_MEASUREMENT_3I0_HIGH_GARM   12
#define DR_OFFSET_MEASUREMENT_I1              13
#define DR_OFFSET_MEASUREMENT_I2              14
#define DR_OFFSET_FREQUENCY_1                 15

#define DR_OFFSET_MEASUREMENT_UAB_2           18
#define DR_OFFSET_MEASUREMENT_UBC_2           19

#define DR_OFFSET_FREQUENCY_2                 22

#define DR_OFFSET_VMP                         24

#define DR_OFFSET_LABEL_TIME_LSW              25
#define DR_OFFSET_LABEL_TIME_MSW              26
#define DR_OFFSET_LABEL_PROTECT               27

#define BLOCK_PROTECTION_MTZ                  1
#define BLOCK_PROTECTION_3I0                  2
#define BLOCK_PROTECTION_3U0                  3
#define BLOCK_PROTECTION_UMIN                 4
#define BLOCK_PROTECTION_UMAX                 5
#define BLOCK_PROTECTION_ZOP                  6

#define BLOCK_PROTECTION_FREQUENCY_1_ACHR     9
#define BLOCK_PROTECTION_FREQUENCY_1_CAPV     10
#define BLOCK_PROTECTION_FREQUENCY_2_ACHR     11
#define BLOCK_PROTECTION_FREQUENCY_2_CAPV     12

#define M_ADDRESS_LAST_MEASUREMENTS_DR        1014
/*****************************************************/

/* Адресний простір вcтановлення ранжування (крів реєстраторів) */
/*****************************************************/
#define M_ADDRESS_FIRST_SETPOINTS_RANG        1016

#define M_ADDRESS_FIRST_DO_RANG               1100
#define M_ADDRESS_LAST_DO_RANG                1323

#define M_ADDRESS_FIRST_DI_RANG               1324
#define M_ADDRESS_LAST_DI_RANG                1451

#define M_ADDRESS_FIRST_LED_RANG              1452
#define M_ADDRESS_LAST_LED_RANG               1515

#define M_ADDRESS_FIRST_DF_RANG               1516
#define M_ADDRESS_LAST_DF_RANG                1899

#define M_ADDRESS_FIRST_DB_RANG               1900
#define M_ADDRESS_LAST_DB_RANG                1963

#define M_ADDRESS_FIRST_DT_RANG               1964
#define M_ADDRESS_LAST_DT_RANG                2059

#define M_ADDRESS_LAST_SETPOINTS_RANG         2059
/*****************************************************/

/*****************************************************/
/* Адресний простір настроювання аналогового реєстратора */
/*****************************************************/
#define M_ADDRESS_FIRST_SETPOINTS_RANG_AR     3000
#define M_ADDRESS_LAST_SETPOINTS_RANG_AR      (M_ADDRESS_FIRST_SETPOINTS_RANG_AR + MAX_FUNCTIONS_IN_AREG - 1)

#define MA_PREFAULT_INTERVAL_AR               3032
#define MA_POSTFAULT_INTERVAL_AR              3033
#define MA_TOTAL_NUMBER_RECORDS_AR            3034
#define MA_CURRENT_NUMBER_RECORD_AR           3035
/*****************************************************/

/*****************************************************/
/* Адресний простір настроювання дискретного реєстратора */
/*****************************************************/
#define M_ADDRESS_FIRST_SETPOINTS_RANG_DR     3036
#define M_ADDRESS_LAST_SETPOINTS_RANG_DR      (M_ADDRESS_FIRST_SETPOINTS_RANG_DR + MAX_FUNCTIONS_IN_DREG - 1)

#define MA_TOTAL_NUMBER_RECORDS_DR            3070
#define MA_CURRENT_NUMBER_RECORD_DR           3071
/*****************************************************/

/*****************************************************/
/* Адресний простір очистки аналогового і дискретного реєстраторів */
/*****************************************************/
#define MA_CLEAR_NUMBER_RECORD_AR     3074
#define CMD_WORD_CLEAR_AR                     0x1312
#define MA_CLEAR_NUMBER_RECORD_DR     3075
#define CMD_WORD_CLEAR_DR                     0x1012
/*****************************************************/

/*****************************************************/
/* Митєві вимірювання розраховані фетодом квадратного кореня суми квадратів миттєвих значень за період */
/*****************************************************/
#define M_ADDRESS_FIRST_MEASUREMENTS_2        61904

#define OFFSET_MEASUREMENT_3I0_I              3

#define M_ADDRESS_LAST_MEASUREMENTS_2         61921
/*****************************************************/

/*****************************************************/
/* Адрексний простір вводу серійного номеру          */
/*****************************************************/
#define MA_SET_SERIAL_NUMBER                  61948
/*****************************************************/

/*****************************************************/
/* Адресний простір реєстратора програмних подій     */
/*****************************************************/
#define MA_CLEAR_NUMBER_RECORD_PR_ERR         61949
#define MA_CURRENT_NUMBER_RECORD_PR_ERR       61950
#define MA_TOTAL_NUMBER_RECORDS_PR_ERR        61951
#define MA_FIRST_ADR_PR_ERR_WINDOW            61952
#define MA_LASR_ADR_PR_ERR_WINDOW             61964
/*****************************************************/

/*****************************************************/
/* Адрексний простір внутрішнього користування       */
/*****************************************************/
#define MA_POSSIBILITY_USTUVANNJA             61967
#define MA_ADDRESS_FIRST_USTUVANNJA           61968
#define MA_ADDRESS_LAST_USTUVANNJA            (MA_ADDRESS_FIRST_USTUVANNJA  + NUMBER_ANALOG_CANALES - 1)
#define MA_ADDRESS_FIRST_PHI_USTUVANNJA       (MA_ADDRESS_LAST_USTUVANNJA + 1)
#define MA_ADDRESS_LAST_PHI_USTUVANNJA        (MA_ADDRESS_FIRST_PHI_USTUVANNJA  + NUMBER_ANALOG_CANALES - 1)
/*****************************************************/

/*****************************************************/
/* Адреса подачі команди скинути настройки у мінімальні параметри */
/*****************************************************/
#define MA_DEFAULT_SETTINGS                   62100
#define CMD_WORD_SET_DEFAULT_SETTINGS         0x1111
/*****************************************************/

/*****************************************************/
/* Адреса подачі команди скинути покази технічного обліку електроенергії */
/*****************************************************/
#define MA_CLEAR_ENERGY                       63001
#define CMD_WORD_CLEAR_ENERGY                 0x1234
/*****************************************************/

#define MA_CMD_RESET_RESURS_MIN_MAX           63002
#define MA_LSW_GLOBAL_RESURS_MIN              63003
#define MA_MSW_GLOBAL_RESURS_MIN              63004
#define MA_LSW_GLOBAL_RESURS_MAX              63005
#define MA_MSW_GLOBAL_RESURS_MAX              63006
#define MA_LSW_GLOBAL_RESURS                  63007
#define MA_MSW_GLOBAL_RESURS                  63008
#define MA_LSW_ADR_MEMORY_TO_WRITE            63009
#define MA_MSW_ADR_MEMORY_TO_WRITE            63010
#define MA_LSW_DATA_MEMORY_TO_WRITE           63011
#define MA_MSW_DATA_MEMORY_TO_WRITE           63012
#define MA_NB_REG_FROM_MEM_READ               63013
#define MA_LSW_ADR_MEMORY_TO_READ             63014
#define MA_MSW_ADR_MEMORY_TO_READ             63015

#define M_ADDRESS_FIRST_READ_DAMP_MEM         63016
#define NUMBER_REGISTER_IN_DUMP_MEMORY        128
#define M_ADDRESS_LAST_READ_DAMP_MEM          (M_ADDRESS_FIRST_READ_DAMP_MEM + NUMBER_REGISTER_IN_DUMP_MEMORY)

#define M_ADDRESS_FIRST_TMP_MEASURMENTS       63256
#define NUMBER_REGISTER_TMP_MEASURMENTS       ((NUMBER_ANALOG_CANALES + 3)<<1)
#define M_ADDRESS_LAST_TMP_MEASURMENTS        (M_ADDRESS_FIRST_TMP_MEASURMENTS + NUMBER_REGISTER_TMP_MEASURMENTS)

#define MA_PART_RECEIVE_DIG_OSCILOGRAPH       63303
#define M_ADDRESS_FIRST_DIG_OSCILOGRAPH       63304
#define NUMBER_REGISTER_DIG_OSCILOGRAPH       16
#define M_ADDRESS_LAST_DIG_OSCILOGRAPH        (M_ADDRESS_FIRST_DIG_OSCILOGRAPH + NUMBER_REGISTER_DIG_OSCILOGRAPH)

#define MA_TEST_WATCHDOGS                     63472
#define CMD_TEST_EXTERNAL_WATCHDOG            0xCDEF
/*****************************************************/

#define SOURCE_OUTPUTS_RANG                   0
#define SOURCE_LEDS_RANG                      1
#define SOURCE_DF_PLUS_RANG                   2
#define SOURCE_DF_MINUS_RANG                  3
#define SOURCE_DF_BLK_RANG                    4
#define SOURCE_AR_RANG                        5
#define SOURCE_DR_RANG                        6
#define SOURCE_SET_DT_PLUS_RANG               7
#define SOURCE_SET_DT_MINUS_RANG              8
#define SOURCE_RESET_DT_PLUS_RANG             9
#define SOURCE_RESET_DT_MINUS_RANG            10

#endif
