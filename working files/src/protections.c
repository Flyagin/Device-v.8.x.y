#include "header.h"

/*****************************************************/
//ĳ��������� ���
/*****************************************************/
inline void diagnostyca_adc_execution(void)
{
  if (gnd_adc1 >0x51) _SET_BIT(set_diagnostyka, ERROR_GND_ADC1_TEST_BIT);
  else _SET_BIT(clear_diagnostyka, ERROR_GND_ADC1_TEST_BIT);

  if (gnd_adc2 >0x51) _SET_BIT(set_diagnostyka, ERROR_GND_ADC2_TEST_BIT);
  else _SET_BIT(clear_diagnostyka, ERROR_GND_ADC2_TEST_BIT);

  if ((vref_adc1 <0x709) || (vref_adc1 > 0x8f5)) _SET_BIT(set_diagnostyka, ERROR_VREF_ADC1_TEST_BIT);
  else _SET_BIT(clear_diagnostyka,ERROR_VREF_ADC1_TEST_BIT);

  if ((vref_adc2 <0x709) || (vref_adc2 > 0x8f5)) _SET_BIT(set_diagnostyka, ERROR_VREF_ADC2_TEST_BIT);
  else _SET_BIT(clear_diagnostyka,ERROR_VREF_ADC2_TEST_BIT);

  if ((vdd_adc1 <0x8F9) || (vdd_adc1 > 0xE13)) _SET_BIT(set_diagnostyka, ERROR_VDD_ADC1_TEST_BIT);
  else _SET_BIT(clear_diagnostyka, ERROR_VDD_ADC1_TEST_BIT);

  if ((vdd_adc2 <0x8F9) || (vdd_adc2 > 0xE13)) _SET_BIT(set_diagnostyka, ERROR_VDD_ADC2_TEST_BIT);
  else _SET_BIT(clear_diagnostyka, ERROR_VDD_ADC2_TEST_BIT);
}
/*****************************************************/

/*****************************************************/
//����� ���������� �����
/*****************************************************/
inline unsigned int norma_value(unsigned long long y)
{
  unsigned long long temp=y;
  unsigned int rezultat =0;
  if (temp == 0) return 0;

  while(temp !=0)
  {
    temp = temp>>1;
    rezultat++;
  }
  return rezultat-1;
}
/*****************************************************/

/*****************************************************/
//����� ���������� ����� ���� int
/*****************************************************/
inline unsigned int get_order(int value)
{
  unsigned int i = 0;

  if (value == 0) return 1;  
  if (value < 0) value =-value;

  while ((value >> (++i)) != 0); 

  return i;    
}
/*****************************************************/

/*****************************************************/
//���������� ������ ����������� ������� ����������� ������  � �������������� ���������� �����
/*****************************************************/
unsigned int sqrt_64(unsigned long long y)
{
   unsigned int b;
   unsigned int a;
   unsigned int c;
   unsigned int norma_rez;
   unsigned long long temp;
   
   norma_rez = norma_value(y)>>1;
   
   a = (1<<norma_rez) - 1;
   b = (1<<(norma_rez+1));
 
   do 
    {
     c = (a + b)>>1;
     temp = (unsigned long long)c*(unsigned long long)c; 
     if (temp != y)
       {
        if ( temp > y) b= c; else a= c;
       } 
     else return c;
    }
   while ((b-a)>1);

   c = (a + b)>>1;

   return c ;
}
/*****************************************************/

/*****************************************************/
//���������� ������ ����������� ������� ����������� ������  � �������������� ���������� �����
/*****************************************************/
inline unsigned int sqrt_32(unsigned int y)
{
   unsigned int b;
   unsigned int a;
   unsigned int c;
   unsigned int norma_rez;
   unsigned int temp;
   
   norma_rez = norma_value(y)>>1;
   
   a = (1<<norma_rez) - 1;
   b = (1<<(norma_rez+1));
 
   do 
    {
     c = (a + b)>>1;
     temp = c*c; 
     if (temp != y)
       {
        if ( temp > y) b= c; else a= c;
       } 
     else return c;
    }
   while ((b-a)>1);

   c = (a + b)>>1;

   return c ;
}
/*****************************************************/

/*****************************************************/
//���������� ������ ��������� �����������
/*****************************************************/
inline void velychyna_zvorotnoi_poslidovnosti(int ortogonal_local_calc[])
{
  int ortogonal_tmp[2];
  int mul_x1, mul_x2, mul_x3, mul_x4, mul_y1, mul_y2, mul_y3, mul_y4;
  
  mul_x1 = (      ortogonal_local_calc[2*FULL_ORT_Ib    ]>>1 );
  mul_y1 = (0x376*ortogonal_local_calc[2*FULL_ORT_Ib    ]>>10);

  mul_x2 = (0x376*ortogonal_local_calc[2*FULL_ORT_Ib + 1]>>10);
  mul_y2 = (      ortogonal_local_calc[2*FULL_ORT_Ib + 1]>>1 );

  mul_x3 = (      ortogonal_local_calc[2*FULL_ORT_Ic    ]>>1 );
  mul_y3 = (0x376*ortogonal_local_calc[2*FULL_ORT_Ic    ]>>10);

  mul_x4 = (0x376*ortogonal_local_calc[2*FULL_ORT_Ic + 1]>>10);
  mul_y4 = (      ortogonal_local_calc[2*FULL_ORT_Ic + 1]>>1 );

  //�������� �����������
  ortogonal_tmp[0] = ((int)(0x155*(ortogonal_local_calc[2*FULL_ORT_Ia    ] - mul_x1  + mul_x2  - mul_x3 - mul_x4)))>>10;
  ortogonal_tmp[1] = ((int)(0x155*(ortogonal_local_calc[2*FULL_ORT_Ia + 1] - mul_y1  - mul_y2  + mul_y3 - mul_y4)))>>10;
  measurement[IM_I2] = (unsigned int)((unsigned long long)( MNOGNYK_I_DIJUCHE  *(sqrt_32((unsigned int)ortogonal_tmp[0]*ortogonal_tmp[0] + (unsigned int)ortogonal_tmp[1]*ortogonal_tmp[1])) ) >> (VAGA_DILENNJA_I_DIJUCHE   + 4));

  //����� �����������
  ortogonal_tmp[0] = ((int)(0x155*(ortogonal_local_calc[2*FULL_ORT_Ia    ] - mul_x1  - mul_x2  - mul_x3 + mul_x4)))>>10;
  ortogonal_tmp[1] = ((int)(0x155*(ortogonal_local_calc[2*FULL_ORT_Ia + 1] + mul_y1  - mul_y2  - mul_y3 - mul_y4)))>>10;
  measurement[IM_I1] = (unsigned int)((unsigned long long)( MNOGNYK_I_DIJUCHE  *(sqrt_32((unsigned int)ortogonal_tmp[0]*ortogonal_tmp[0] + (unsigned int)ortogonal_tmp[1]*ortogonal_tmp[1])) ) >> (VAGA_DILENNJA_I_DIJUCHE   + 4));
}
/*****************************************************/

/*****************************************************
ort_i  - �������� �� ����������� 3I0
ort_u  - �������� �� ����������� 3U0
*****************************************************/
inline void detector_kuta_nzz(int ortogonal_local_calc[]) 
{
  int cos_fi, sin_fi;

#define SIN_3I0   ortogonal_local_calc[2*FULL_ORT_3I0    ]
#define COS_3I0   ortogonal_local_calc[2*FULL_ORT_3I0 + 1]
#define SIN_3U0   ortogonal_local_calc[2*FULL_ORT_3U0_Ubc_TN2    ]
#define COS_3U0   ortogonal_local_calc[2*FULL_ORT_3U0_Ubc_TN2 + 1]

  /***
  �������������� ���������� ������� ������ 
  ***/
  cos_fi = COS_3I0*COS_3U0 + SIN_3I0*SIN_3U0;
  sin_fi = -(SIN_3I0*COS_3U0 - COS_3I0*SIN_3U0);//� ������: "���������, ��� ����", ����� �� � �� ���� ��������
  /***/

#undef SIN_3I0
#undef COS_3I0
#undef SIN_3U0
#undef COS_3U0

  /*
  � ��������� ����������� ����������� � ������� ��������� ����� ������� (calc_measurement())
  �������, �� ����������� ������� ������� 3I0 � 3U0 � 15-��� ���� + ����.
  ��� COS � SIN ������ ��� ������� ���� ���� 31-���� �����
  �������� ���������� ������� ������� ������ 7-������ ������� + ����
  ��� ��� �� �������� ������������ ����� �����������, �� ���������� ������ �������
  COS � SIN ���� = 31 - (7 + 1) = 23
  7 - �� ���������� ��������� ������� ������� �������
  1 - �� ���������� �� �� ���������⳺�� ������� (ab+cd)
  */
  unsigned int order_cos, order_sin, max_order, shift = 0;
  order_cos = get_order(cos_fi);
  order_sin = get_order(sin_fi);
  if (order_cos > order_sin) max_order = order_cos; else max_order = order_sin;
  if (max_order > 23) shift = max_order - 23;
  
  /*
  ��� ���� � ����� ���� ���������� ��������� - �� ��� � ������ �� ����� ����������� ����,
  ��� ���� � �������� ������� ���������� ���������.
  ��� ���� ��� � ������������?..
  */

  /***
  ���������� ���������
  ***/
  int sin_fi1_minus_fi2;
  if ((cos_fi >= 0) && (sin_fi >= 0))
  {
    //1-�� ��������
    cos_fi = cos_fi >> shift;
    sin_fi = sin_fi >> shift;

#define COS_SECTOR sector_1[0]    
#define SIN_SECTOR sector_1[1]    

    sin_fi1_minus_fi2 = sin_fi*COS_SECTOR - cos_fi*SIN_SECTOR;
    sector_i_minus_u_1 = (sin_fi1_minus_fi2 < 0) ?  0 : 1;
    
#undef COS_SECTOR    
#undef SIN_SECTOR    

#define COS_SECTOR sector_2[0]    
#define SIN_SECTOR sector_2[1]    

    sin_fi1_minus_fi2 = sin_fi*COS_SECTOR - cos_fi*SIN_SECTOR;
    sector_i_minus_u_2 = (sin_fi1_minus_fi2 < 0) ?  0 : 1;
    
#undef COS_SECTOR    
#undef SIN_SECTOR    
  }
  else if ((cos_fi < 0) && (sin_fi >= 0))
  {
     //2-�� ��������
    cos_fi = cos_fi >> shift;
    sin_fi = sin_fi >> shift;

#define COS_SECTOR sector_1[2]    
#define SIN_SECTOR sector_1[3]    

    sin_fi1_minus_fi2 = sin_fi*COS_SECTOR - cos_fi*SIN_SECTOR;
    sector_i_minus_u_1 = (sin_fi1_minus_fi2 > 0) ?  0 : 2;
    
#undef COS_SECTOR    
#undef SIN_SECTOR    

#define COS_SECTOR sector_2[2]    
#define SIN_SECTOR sector_2[3]    

    sin_fi1_minus_fi2 = sin_fi*COS_SECTOR - cos_fi*SIN_SECTOR;
    sector_i_minus_u_2 = (sin_fi1_minus_fi2 > 0) ?  0 : 2;
    
#undef COS_SECTOR    
#undef SIN_SECTOR    
  }
  else if ((cos_fi < 0) && (sin_fi < 0))
  {
    //3-�� ��������
    cos_fi = cos_fi >> shift;
    sin_fi = sin_fi >> shift;

#define COS_SECTOR sector_1[4]    
#define SIN_SECTOR sector_1[5]    

    sin_fi1_minus_fi2 = sin_fi*COS_SECTOR - cos_fi*SIN_SECTOR;
    sector_i_minus_u_1 = (sin_fi1_minus_fi2 < 0) ?  0 : 3;
    
#undef COS_SECTOR    
#undef SIN_SECTOR    

#define COS_SECTOR sector_2[4]    
#define SIN_SECTOR sector_2[5]    

    sin_fi1_minus_fi2 = sin_fi*COS_SECTOR - cos_fi*SIN_SECTOR;
    sector_i_minus_u_2 = (sin_fi1_minus_fi2 < 0) ?  0 : 3;
    
#undef COS_SECTOR    
#undef SIN_SECTOR    
  }
  else
  {
    //4-�� ��������
    cos_fi = cos_fi >> shift;
    sin_fi = sin_fi >> shift;

#define COS_SECTOR sector_1[6]    
#define SIN_SECTOR sector_1[7]    

    sin_fi1_minus_fi2 = sin_fi*COS_SECTOR - cos_fi*SIN_SECTOR;
    sector_i_minus_u_1 = (sin_fi1_minus_fi2 > 0) ?  0 : 4;
    
#undef COS_SECTOR    
#undef SIN_SECTOR    

#define COS_SECTOR sector_2[6]    
#define SIN_SECTOR sector_2[7]    

    sin_fi1_minus_fi2 = sin_fi*COS_SECTOR - cos_fi*SIN_SECTOR;
    sector_i_minus_u_2 = (sin_fi1_minus_fi2 > 0) ?  0 : 4;
    
#undef COS_SECTOR    
#undef SIN_SECTOR    
  }
  /***/
}
/*****************************************************/

/*****************************************************/
//������������ ��� � ����������� �������
/*****************************************************/
inline void directional_mtz(int ortogonal_local_calc[], unsigned int number_group_stp) 
{
  for (unsigned int mtz = 0; mtz < 4; mtz++)
  {
    int a_cos_fi, a_sin_fi;
    switch (mtz)
    {
    case 0:
      {
        a_cos_fi = current_settings_prt.setpoint_mtz_1_angle_cos[number_group_stp];
        a_sin_fi = current_settings_prt.setpoint_mtz_1_angle_sin[number_group_stp];
        
        break;
      }
    case 1:
      {
        a_cos_fi = current_settings_prt.setpoint_mtz_2_angle_cos[number_group_stp];
        a_sin_fi = current_settings_prt.setpoint_mtz_2_angle_sin[number_group_stp];
        
        break;
      }
    case 2:
      {
        a_cos_fi = current_settings_prt.setpoint_mtz_3_angle_cos[number_group_stp];
        a_sin_fi = current_settings_prt.setpoint_mtz_3_angle_sin[number_group_stp];
        
        break;
      }
    case 3:
      {
        a_cos_fi = current_settings_prt.setpoint_mtz_4_angle_cos[number_group_stp];
        a_sin_fi = current_settings_prt.setpoint_mtz_4_angle_sin[number_group_stp];
        
        break;
      }
    default:
      {
        //���������� ����� ����� �� ���� � ����
        total_error_sw_fixed(54);
      }
    }
    a_sin_fi = -a_sin_fi; //� ������: "���������, ��� ����", ����� �� � �� ���� ��������

    //������ ��������� �� ������������ ���
    /*
    �� ����������� �������� ��� ���������� ����� ������� ���� ����������� � � ������ (15 �� + ����) = 16-�������� �����
    */
    int amp_cos_U_fi;
    int amp_sin_U_fi;
  
    for (unsigned int i = 0; i < 3; i++)
    {
      unsigned int index_I, index_U;
      unsigned int index_I_ort, index_U_ort;
      switch (i)
      {
      case 0:
        {
          index_I = IM_IA;
          index_U = IM_UBC;

          index_I_ort = FULL_ORT_Ia;
          index_U_ort = FULL_ORT_Ubc;

          break;
        }
      case 1:
        {
          index_I = IM_IB_r;
          index_U = IM_UCA;

          index_I_ort = FULL_ORT_Ib;
          index_U_ort = FULL_ORT_Uca;

          break;
        }
      case 2:
        {
          index_I = IM_IC;
          index_U = IM_UAB;

          index_I_ort = FULL_ORT_Ic;
          index_U_ort = FULL_ORT_Uab;

          break;
        }
      default:
        {
          //���������� ����� ����� �� ���� � ����
          total_error_sw_fixed(60);
        }
      }

      unsigned int porig_Uxy;
      if (Uxy_bilshe_porogu[i] == 0) porig_Uxy = PORIG_CHUTLYVOSTI_VOLTAGE*KOEF_POVERNENNJA_SECTOR_BLK/100;
      else porig_Uxy = PORIG_CHUTLYVOSTI_VOLTAGE;
      unsigned int Uxy_bilshe_porogu_tmp = Uxy_bilshe_porogu[i] = (measurement[index_U] >= porig_Uxy);
      
      unsigned int porig_Ix;
      if (Ix_bilshe_porogu[i] == 0) porig_Ix = PORIG_CHUTLYVOSTI_CURRENT*KOEF_POVERNENNJA_SECTOR_BLK/100;
      else porig_Ix = PORIG_CHUTLYVOSTI_CURRENT;
      unsigned int Ix_bilshe_porogu_tmp = Ix_bilshe_porogu[i]  = (measurement[index_I] >= porig_Ix );

      if (
          (Uxy_bilshe_porogu_tmp != 0) &&
          (Ix_bilshe_porogu_tmp  != 0)
         )
      {
#define SIN_I   ortogonal_local_calc[2*index_I_ort    ]
#define COS_I   ortogonal_local_calc[2*index_I_ort + 1]
#define SIN_U   ortogonal_local_calc[2*index_U_ort    ]
#define COS_U   ortogonal_local_calc[2*index_U_ort + 1]

        amp_cos_U_fi = (COS_U*a_cos_fi - SIN_U*a_sin_fi) >> AMPLITUDA_FI_VAGA; //� ����������� �� ��������� ���������� �������������
        amp_sin_U_fi = (SIN_U*a_cos_fi + COS_U*a_sin_fi) >> AMPLITUDA_FI_VAGA; //� ����������� �� ��������� ���������� �������������

        //���������� COS � SIN ���� ������ �� (U[i]+fi) � I[i]
        int cos_fi, sin_fi;
        /*
        � ��������� ����������� ����������� � ������� ��������� ����� ������� (calc_measurement())
        �������, �� ����������� �������� ������������� ��� ������ ���� ���� 0x6E51, ��� ����� ������� 
        0x120FC, �� ������� �� �� ���� 0x7C87B7BC  - 31 ���� ����� (���� ���� ���)
        ����� �� ���������� � ��� int.
        */
        cos_fi = amp_cos_U_fi*COS_I + amp_sin_U_fi*SIN_I;
        sin_fi = -(amp_sin_U_fi*COS_I - amp_cos_U_fi*SIN_I);//� ������: "���������, ��� ����", ����� �� � �� ���� ��������

#undef SIN_I
#undef COS_I
#undef SIN_U
#undef COS_U

        /*
        � ���� ��������� ����������� ��������, �� COS � SIN ������ ������ � ������� ���� ���� 31-���� �����
        ������� ���������� ������� ������� ������ 7-������ ������� + ����
        ��� ��� �� �������� ������������ ����� �����������, �� ���������� ������ �������
        COS � SIN ���� = 31 - (7 + 1) = 23
        7 - �� ���������� ��������� ������� ������� �������
        1 - �� ���������� �� �� ���������⳺�� ������� (ab+cd)
        */
        unsigned int order_cos, order_sin, max_order, shift = 0;
        order_cos = get_order(cos_fi);
        order_sin = get_order(sin_fi);
        if (order_cos > order_sin) max_order = order_cos; else max_order = order_sin;
        if (max_order > 23) shift = max_order - 23;
  
        /*
        ��� ���� � ����� ���� ���������� ��������� - �� ��� � ������ �� ����� ����������� ����,
        ��� ���� � �������� ������� ���������� ���������.
        ��� ���� ��� � ������������?..
        */

        //���������� �������
        int sin_fi1_minus_fi2;
        int *sector;
        if ((sin_fi >= 0) && (cos_fi >= 0))
        {
          //1-�� ��������
          cos_fi = cos_fi >> shift;
          sin_fi = sin_fi >> shift;
          
          if (sector_directional_mtz[mtz][i] != 1)
            sector = sector_1_mtz;
          else
            sector = sector_2_mtz;
          
#define COS_SECTOR sector[0]    
#define SIN_SECTOR sector[1]    

          sin_fi1_minus_fi2 = sin_fi*COS_SECTOR - cos_fi*SIN_SECTOR;
          sector_directional_mtz[mtz][i] = (sin_fi1_minus_fi2 <= 0) ?  1 : 0;
    
#undef COS_SECTOR    
#undef SIN_SECTOR   
        }
        else if ((sin_fi >= 0) && (cos_fi < 0))
        {
          //2-�� ��������
          cos_fi = cos_fi >> shift;
          sin_fi = sin_fi >> shift;

          if (sector_directional_mtz[mtz][i] != 2)
            sector = sector_1_mtz;
          else
            sector = sector_2_mtz;

#define COS_SECTOR sector[2]    
#define SIN_SECTOR sector[3]    

          sin_fi1_minus_fi2 = sin_fi*COS_SECTOR - cos_fi*SIN_SECTOR;
          sector_directional_mtz[mtz][i] = (sin_fi1_minus_fi2 >= 0) ?  2 : 0;
    
#undef COS_SECTOR    
#undef SIN_SECTOR    
        }
        else if ((sin_fi < 0) && (cos_fi < 0))
        {
          //3-�� ��������
          cos_fi = cos_fi >> shift;
          sin_fi = sin_fi >> shift;

          if (sector_directional_mtz[mtz][i] != 2)
            sector = sector_1_mtz;
          else
            sector = sector_2_mtz;

#define COS_SECTOR sector[4]    
#define SIN_SECTOR sector[5]    

          sin_fi1_minus_fi2 = sin_fi*COS_SECTOR - cos_fi*SIN_SECTOR;
          sector_directional_mtz[mtz][i] = (sin_fi1_minus_fi2 <= 0) ?  2 : 0;
    
#undef COS_SECTOR    
#undef SIN_SECTOR    
        }
        else
        {
          //4-�� ��������
          cos_fi = cos_fi >> shift;
          sin_fi = sin_fi >> shift;

          if (sector_directional_mtz[mtz][i] != 1)
            sector = sector_1_mtz;
          else
            sector = sector_2_mtz;

#define COS_SECTOR sector[6]    
#define SIN_SECTOR sector[7]    

          sin_fi1_minus_fi2 = sin_fi*COS_SECTOR - cos_fi*SIN_SECTOR;
          sector_directional_mtz[mtz][i] = (sin_fi1_minus_fi2 >= 0) ?  1 : 0;
    
#undef COS_SECTOR    
#undef SIN_SECTOR    
        }
      }
      else
      {
        sector_directional_mtz[mtz][i] = 0;
      }
    }
  }
}
/*****************************************************/

/*****************************************************/
//����������� �����
/*****************************************************/
inline void calc_resistance(int ortogonal_local_calc[], int resistance_output[]) 
{
  const unsigned int index_line_voltage[3]  = {FULL_ORT_Uab, FULL_ORT_Ubc, FULL_ORT_Uca};
  const unsigned int index_begin_current[3] = {FULL_ORT_Ia , FULL_ORT_Ib , FULL_ORT_Ic };
  const unsigned int index_end_current[3]   = {FULL_ORT_Ib , FULL_ORT_Ic , FULL_ORT_Ia };
  
  for (unsigned int i = 0; i < 3; i++)
  {
    //����������� ���������� ������ Ixy
    int _a2, _b2;
    /*
    � ��������� ����������� ����������� � ������� ��������� ����� ������� (calc_measurement())
    �������, �� ����������� �������� ������������� ��� ������ ���� ���� 0x6E51, ��� ����� ������� 
    0x120FC

    � ������ ������ �������������� ���� ������, ��, ���� ���������� �� ������� �������� � ��� �������, ��  �����������
    �������� ������������� ���� ����
    0x6E51*2 = 0xDCA2 �� � 16 ���� ����� (+ �������� ����) - ����� ����� �������� 17-����
    */
    
    _a2 = ortogonal_local_calc[2*index_begin_current[i] + 0] - ortogonal_local_calc[2*index_end_current[i] + 0];
    _b2 = ortogonal_local_calc[2*index_begin_current[i] + 1] - ortogonal_local_calc[2*index_end_current[i] + 1];

#define _A1     ortogonal_local_calc[2*index_line_voltage[i] + 0]
#define _B1     ortogonal_local_calc[2*index_line_voltage[i] + 1]
    
    long long mod = (long long)_a2*(long long)_a2 + (long long)_b2*(long long)_b2;
    
    //����������� �������� ������ Ixy
    unsigned int Ixy = ( MNOGNYK_I_DIJUCHE*(sqrt_64(mod)) ) >> (VAGA_DILENNJA_I_DIJUCHE + 4);
    
    if (Ixy >= PORIG_Ixy)
    {
      //����� ������������� �������� ���
      /*
       .
      Uxy   Re(Uxy) + iIm(Uxy)   a1 + ib1    (a1 + ib1)(a2 - ib2)    (a1a2 + b1b2) + i(a2b1 - a1b2)    a1a2 + b1b2      a2b1 - a1b2
      --- = ------------------ = --------- = --------------------- = ------------------------------ =  ------------ + i--------------
       .                                                                     2      2                     2      2         2      2
      Ixy   Re(Ixy) + iIm(Ixy)   a2 + ib2    (a2 + ib2)(a2 - ib2)          a2   + b2                    a2   + b2        a2   + b2
      */
      
      resistance_output[2*i    ] = (int)(MNOGNYK_R_FLOAT*((float)((long long)_A1*(long long)_a2 + (long long)_B1*(long long)_b2))/((float)mod));
      resistance_output[2*i + 1] = (int)(MNOGNYK_R_FLOAT*((float)((long long)_a2*(long long)_B1 - (long long)_A1*(long long)_b2))/((float)mod));
    }
    else
    {
      //�� ����� ������������� �������� ���
      resistance_output[2*i    ] = UNDEF_RESISTANCE;
      resistance_output[2*i + 1] = UNDEF_RESISTANCE;
    }
    
#undef _A1
#undef _B1
  }
}
/*****************************************************/

/*****************************************************/
//����������� ������ ���������
/*****************************************************/
inline void calc_power(int ortogonal_local_calc[]) 
{
  /*
  ����������� ����� � ����� ������� ��������� � ���������� ������
  
  .    .  .     .  .
  S = UabIa* - UbcIc*
  */
  
#define IA_SIN          ortogonal_local_calc[2*FULL_ORT_Ia + 1]
#define IA_COS          ortogonal_local_calc[2*FULL_ORT_Ia + 0]
#define UAB_SIN         ortogonal_local_calc[2*FULL_ORT_Uab + 1]
#define UAB_COS         ortogonal_local_calc[2*FULL_ORT_Uab + 0]
  
#define IC_SIN          ortogonal_local_calc[2*FULL_ORT_Ic + 1]
#define IC_COS          ortogonal_local_calc[2*FULL_ORT_Ic + 0]
#define UBC_SIN         ortogonal_local_calc[2*FULL_ORT_Ubc + 1]
#define UBC_COS         ortogonal_local_calc[2*FULL_ORT_Ubc + 0]
  
  long long Re_IaUab, Im_IaUab;
  if (measurement[IM_IA] >= PORIG_I_ENERGY)
  {
    Re_IaUab = UAB_COS*IA_COS + UAB_SIN*IA_SIN;
    Im_IaUab = UAB_SIN*IA_COS - UAB_COS*IA_SIN;
  
  }
  else
  {
    Re_IaUab = 0;
    Im_IaUab = 0;
  }

  long long Re_IcUbc, Im_IcUbc;
  if (measurement[IM_IC] >= PORIG_I_ENERGY)
  {  
    Re_IcUbc = UBC_COS*IC_COS + UBC_SIN*IC_SIN;
    Im_IcUbc = UBC_SIN*IC_COS - UBC_COS*IC_SIN;
  }
  else
  {
    Re_IcUbc = 0;
    Im_IcUbc = 0;
  }
#undef IA_SIN
#undef IA_COS
#undef UAB_SIN
#undef UAB_COS
  
#undef IC_SIN
#undef IC_COS
#undef UBC_SIN
#undef UBC_COS
  
  long long P_adc_x16 = Re_IaUab - Re_IcUbc; /*  ������� ��������� � ������� ��� � � �������� ���������, �� � ������� � 16 ����*/
  long long Q_adc_x16 = Im_IaUab - Im_IcUbc; /*��������� ��������� � ������� ��� � � �������� ���������, �� � ������� � 16 ����*/
  
  /*
  ���� ����������� �� ����������� MNOGNYK_I_DIJUCHE_FLOAT � MNOGNYK_U_DIJUCHE_FLOAT,
  � ���� ������� �� 16x16 - �� �������� ����� = ����/�����/����
  
  �� ������ ������� ����� � ���/����/���. 
  
  ��� ����� ������� �� �� 1000
  */
  
  //������� ���������
  double P_float = ((double)P_adc_x16) * ((double)(MNOGNYK_I_DIJUCHE_DOUBLE*MNOGNYK_U_DIJUCHE_DOUBLE/(1000.0*16.0*16.0)));
  int P_tmp = (int)(P_float); // � ������� �� ���

  //��������� ���������
  double Q_float = ((double)Q_adc_x16) * ((double)(MNOGNYK_I_DIJUCHE_DOUBLE*MNOGNYK_U_DIJUCHE_DOUBLE/(1000.0*16.0*16.0)));
  int Q_tmp  = (int)(Q_float); // � ������� �� ����

  unsigned int bank_for_enegry_tmp = bank_for_enegry;  
  int *energy_array;
  
  //������� ���������
  if (P_tmp >= 0) energy_array = P_plus;
  else energy_array = P_minus;
  *(energy_array + bank_for_enegry_tmp) += abs(P_tmp);
  
  //��������� ���������
  if     ((Q_tmp >= 0) && (P_tmp >= 0)) energy_array = Q_1q;
  else if((Q_tmp >= 0) && (P_tmp <  0)) energy_array = Q_2q;
  else if((Q_tmp <  0) && (P_tmp <  0)) energy_array = Q_3q;
  else                                  energy_array = Q_4q;
  *(energy_array + bank_for_enegry_tmp) += abs(Q_tmp);
  
  if (++lichylnyk_1s_po_20ms >= MAIN_FREQUENCY)
  {
    if (lichylnyk_1s_po_20ms > MAIN_FREQUENCY)
    {
      //���������� ����� ����� �� ���� � ����
      total_error_sw_fixed(64);
    }

    //����������� ���� ��� ���������� ����� ����� s ��������� �������� � ������ �����
    bank_for_enegry = bank_for_enegry_tmp = (bank_for_enegry_tmp + 1) & 0x1;
    P_plus[bank_for_enegry_tmp] = 0;
    P_minus[bank_for_enegry_tmp] = 0;
    Q_1q[bank_for_enegry_tmp] = 0;
    Q_2q[bank_for_enegry_tmp] = 0;
    Q_3q[bank_for_enegry_tmp] = 0;
    Q_4q[bank_for_enegry_tmp] = 0;
    
    lichylnyk_1s_po_20ms = 0;
    if (periodical_tasks_CALC_ENERGY_DATA == 0)
    {
      //������� ����������� � ���� ����������
      _SET_BIT(clear_diagnostyka, LOSE_ENERGY_DATA);
    }
    else
    {
      //���������� ����������� � ���� ����������
      _SET_BIT(set_diagnostyka, LOSE_ENERGY_DATA);
    }
    periodical_tasks_CALC_ENERGY_DATA = true;
  }
  
}
/*****************************************************/

/*****************************************************/
//���������� ���������
/*****************************************************/
inline void calc_measurement(unsigned int number_group_stp)
{
  int ortogonal_local[2*NUMBER_ANALOG_CANALES];
  unsigned long long sum_sqr_data_3I0_local;
  float value_3I0_i_float, value_3I0_f_float;

  //����������� ������� �������� ���������� ������� � ����������� �������
//  semaphore_measure_values = 1;

  //������� ����� �������� � ������� ����
  /*
  ������� ��� ����������� ������������ ��� ����������� ������� �� ����� ������� � ��������� �� 2 (��������� 2/�),
  �� �� �� ������ ������� ��������
  */
  /*
  �������� ���� ���������� ���������, �� ���� ����������� ������� ������� ������� �� �����/������� �� �����,
  � ���� ��������� ������� �� 2/� (������� �� ��������� �������, ��� ���� � ����� ����),
  �� ��������� ���������� ���������� ���� ���� ���������� ���������� �������� �������
  ����� ��� 3I0            - �� 19 �� + ���� = ((11 �� + ����)*16*16)
        ��� ������ ������ - �� 15 �� + ���� = ((11 �� + ����)*16   )
  ������� ��� �� ����� �� ����� ������� �� �������� � �� ���� �������� ����� ���������� � ���� ��������, ��
  ������ ����� ����� �������� �� �������� - ������������ �� ����, �� (15 �� *2) = 30 �� �� 32 �� unsigned int
  � �� ���� ������� ��������� �� 16, ��� �������� ������� ����������
  
  ��� 3I0 ������� ������������ - ���� ����� ���:
  1.  
  ����� 16-������ ��������� ������� ����� � ������������� ��� 3I0,
  ��� ����������� ������� �� ����� 15-���������� ����� + ����.
  ����� 16-������ ��������� ������� ��� � ����������� ���������
    
  2.����������� 64-���� ����������.
    
  �� 17 ��������� 2014 ���� ��������������� ������ �����.
  ��� �������� ������� ��� ���������� ����� ����� �������. ���������, �� ����� ����
  ��'����� � ���, �� ���� ���������� ������� ������� - �� ����� ����� �������� ������
  ����� ������ �� �������� �������� - � ��� �������� ����� ����� �������
    
  ���� ������ ����������� ������ ����� � 17 ��������� 2014 ����  
  
  ��� ���������� ������� � 18 ��������� 2014 ���� � ������� �������� sin/cos ���
  ����� ������ ������������
  */
  
  unsigned int bank_ortogonal_tmp = (bank_ortogonal + 1) & 0x1;
  for(unsigned int i=0; i<(2*NUMBER_ANALOG_CANALES); i++ )
  {
    ortogonal_local[i] = ortogonal[i][bank_ortogonal_tmp];
  }
  
  /*
  ������� ��� ������������� ���������� ���� �������� � ����� ������� �� �����, 
  �� ��� ����������� ������� �������� ������ �� ������� �������, �� �� �� ������ ����� � ������ ��������
  */
//  sum_sqr_data_3I0_period_local = sum_sqr_data_3I0_period;
  sum_sqr_data_3I0_local = sum_sqr_data_3I0[bank_ortogonal_tmp];

  bank_ortogonal = bank_ortogonal_tmp;
  
  //������ ������� �������� ���������� ������� � ����������� �������
//  semaphore_measure_values = 0;
  
  /*******************************************************/
  //����������, �� ���������� ���� ���������
  /*******************************************************/
  if (changed_ustuvannja == CHANGED_ETAP_ENDED_EXTRA_ETAP) /*�� � �����, �� ��� ��� ���������� ��� �������� �� � ������ �������� �������(� ��� ����� ����� ��� �� ���������)*/
  {
    //������� ����� ��������� � ���� ����� ������ ��� � ���� ������ (���� � �����) ����� ����������� ���������
    for(unsigned int i = 0; i < NUMBER_ANALOG_CANALES; i++) 
    {
      phi_ustuvannja_meas[i] = phi_ustuvannja[i];
      phi_ustuvannja_sin_cos_meas[2*i    ] = phi_ustuvannja_sin_cos[2*i    ];
      phi_ustuvannja_sin_cos_meas[2*i + 1] = phi_ustuvannja_sin_cos[2*i + 1];
    }
      
    //�������, �� ���� ������� �������� �������
    changed_ustuvannja = CHANGED_ETAP_NONE;
  }
  /*****************************************************/

  /***
  ��������� ���� � ������� ����������� ��� ����������������� �����
  ***/
  const unsigned int *point_to_index_converter;
  if ((current_settings_prt.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_PHASE_LINE) == 0)
    point_to_index_converter = index_converter_p;
  else
    point_to_index_converter = index_converter_l;

  unsigned int copy_to_low_tasks = (semaphore_measure_values_low == 0) ? true : false;
  for (unsigned int i = 0; i < NUMBER_ANALOG_CANALES; i++)
  {
    float sin_alpha = ((float)ortogonal_local[2*i    ])/((float)((1 << (VAGA_NUMBER_POINT - 1))));
    float cos_alpha = ((float)ortogonal_local[2*i + 1])/((float)((1 << (VAGA_NUMBER_POINT - 1))));
    
    float sin_beta =  phi_ustuvannja_sin_cos_meas[2*i    ];
    float cos_beta =  phi_ustuvannja_sin_cos_meas[2*i + 1];
    
    if (
        (i == I_Uab_TN2) ||
        (
         (i == I_3U0_Ubc_TN2) &&
         ((current_settings_prt.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_3U0_Ubc_TN2) != 0)
        ) 
       )   
    {
       unsigned int frequency_locking_bank_tmp = frequency_locking_bank & 0x1;
       sin_beta = phi_ustuvannja_sin_cos_meas[2*i    ]*frequency_locking_cos[frequency_locking_bank_tmp] + phi_ustuvannja_sin_cos_meas[2*i + 1]*frequency_locking_sin[frequency_locking_bank_tmp];
       cos_beta = phi_ustuvannja_sin_cos_meas[2*i + 1]*frequency_locking_cos[frequency_locking_bank_tmp] - phi_ustuvannja_sin_cos_meas[2*i    ]*frequency_locking_sin[frequency_locking_bank_tmp];
    }
    
    unsigned int new_index = *(point_to_index_converter + i);
    int ortogonal_sin = ortogonal_calc[2*new_index    ] = (int)(sin_alpha*cos_beta + cos_alpha*sin_beta);
    int ortogonal_cos = ortogonal_calc[2*new_index + 1] = (int)(cos_alpha*cos_beta - sin_alpha*sin_beta);

    
    //������� ����������� ��� ���������� ����
    if (copy_to_low_tasks == true)
    {
      ortogonal_calc_low[2*new_index    ] = ortogonal_sin;
      ortogonal_calc_low[2*new_index + 1] = ortogonal_cos;
    }
  }
  /***/
  
  /***/
  //����������� ���� �������� 3I0 �� ����������� �������
  /***/
  /*�������� ���������� �����*/
  sum_sqr_data_3I0_local = sqrt_64(sum_sqr_data_3I0_local);
  
  /*��� ���������� ����� �������� � �� ����� ��������� �� ��� ����������*/
  /*�� ������ ����� � ��������� � 256 ���, ���� ���� ���� �� 256*/
  /*��� ���� �����'������� �� �������� ��� ���������� ������ �������� ����� ���������*/

  /*
  �� ���� �� �������� ����� ������� �� ����� � NUMBER_POINT = 32 = 16*2
  ����� �� ���� ������� �� 4*sqrt(2)
  4 �� ������� �� 2
  ((MNOGNYK_3I0_D * X )>> VAGA_DILENNJA_3I0_D)/sqrt(2) �������
   (MNOGNYK_3I0_DIJUCHE_D * X )>> VAGA_DILENNJA_3I0_DIJUCHE_D 
  
  ���� ������ ����� ���� (MNOGNYK_3I0_DIJUCHE_D;VAGA_DILENNJA_3I0_DIJUCHE_D) � (MNOGNYK_3I0_D;VAGA_DILENNJA_3I0_D)
  �� ������ ������� ��� ���������� ����� �������.
  ���� ����� ��� �� ��� ��������� ������
  */
  value_3I0_i_float = (unsigned int)(MNOGNYK_3I0_FLOAT*((float)sum_sqr_data_3I0_local)/(1024.0f)); /*1024 = 4*256. 256 - �� ��������� ������ 3I0; 4 - �� sqrt(16), � 16 �������� � ����. �� 32 = 16*2 */
  measurement[IM_3I0_i] = (unsigned int)value_3I0_i_float; 
  /***/
  
  /*
  ---------------------------------------------------------------------------------------------------------
  150� (150 000��) - ������������ ������ �����
  ����������� ����������� � ��  - Koef_1 = 84,978173543997808495193432804655 ��� ������ ������ (5439/64 = 84,984375)
  
  ��� ��� 150� ����������� ������� �������� ������������� ���� ����
  150000/Koef_1 = 1765,0303364589078874793160507446
  ���� ���������, �� ������ � ��������� � 16 ���, �� ����������� �������� ������������� ���� ����
  16*150000/Koef_1 = 28240,485383342526199669056811914 < 28241(0x6E51) �� � 15 ���� ����� (+ �������� ����)
  ---------------------------------------------------------------------------------------------------------

  ---------------------------------------------------------------------------------------------------------
  150� (150 000��) - ����������� ����� �������
  ����������� ����������� � ��  - Koef_1 = 64,883134509545420915167731259667 ��� ������ ������ (4152/64 = 64,875)
  
  ��� ��� 150� ����������� ������� �������� ������������� ���� ����
  150000/Koef_1 = 2311,848851536795430557291797995
  ���� ���������, �� ������ � ��������� � 16 ���, �� ����������� �������� ������������� ���� ����
  16*150000/Koef_1 = 36989,581624588726888916668767919 < 36990(0x907E) �� � 16 ���� ����� (+ �������� ����) - ����� ����� �������� 17-����
  
  ���� � ����� ������� ������������� ����� �������, ��, ���� ���������� �� ������� �������� � ��� �������, ��  �����������
  �������� ������������� ���� ����
  2*16*150000/Koef_1 = 73979,163249177453777833337535838 < 73980(0x120FC) �� � 17 ���� ����� (+ �������� ����) - ����� ����� �������� 18-����
  ---------------------------------------------------------------------------------------------------------
  
  ---------------------------------------------------------------------------------------------------------
  2� (2 000�� * 10 = 20 000(������� ��)) - ������������ ����� 3I0
  ����������� ����������� � ����� ��  - Koef_1* = 169,95634708799561699038686560931 ��� 3I0  ��� 3I0 ��� �������� � ������� �������� (170/1 = 170)

  
  ��� ��� 2� ����������� ������� �������� ������������� ���� ����
  20000/Koef_1* = 117,67727621049018824880803941698
  ���� ���������, �� ������ � ��������� � 16 ��� (��������� � 256 ��� �� ��� �������� �� 16), �� ����������� �������� ������������� ���� ����
  16*20000/Koef_1* = 1882,8364193678430119809286306717 < 1883(0x075B) �� � 11 ���� ����� (+ �������� ����)
  ---------------------------------------------------------------------------------------------------------
  */
  
  /***/
  //����������� ���� �������� ����� ������������ ���'�
  /***/
  for(unsigned int i = 0; i < NUMBER_ANALOG_CANALES; i++)
  {
    if (i == I_3I0)
    {
      long long a, b;
      a = (long long)ortogonal_calc[2*FULL_ORT_3I0];
      b = (long long)ortogonal_calc[2*FULL_ORT_3I0 + 1];
      unsigned long long a2, b2, c;
      a2 = a*a;
      b2 = b*b;
      c = a2 + b2;
      unsigned int d;
      d = sqrt_64(c);
      value_3I0_f_float = (unsigned int)(MNOGNYK_3I0_FLOAT*((float)d)/(256.0f)); /*256 - �� ��������� ������� 3I0*/

      measurement[IM_3I0] = (unsigned int)value_3I0_f_float;
    }
    else if ((i >= I_Ia) && (i <= I_Ic))
    {
      unsigned int index_m, index_ort;
      switch (i)
      {
      case I_Ia:
        {
          index_m = IM_IA;
          index_ort = FULL_ORT_Ia;
          break;
        }
      case I_Ic:
        {
          index_m = IM_IC;
          index_ort = FULL_ORT_Ic;
          break;
        }
      default:
        {
          //���������� ����� ����� �� ���� � ����
          total_error_sw_fixed(66);
        }
      }
      
      measurement[index_m] = ( MNOGNYK_I_DIJUCHE*(sqrt_32((unsigned int)(ortogonal_calc[2*index_ort]*ortogonal_calc[2*index_ort]) + (unsigned int)(ortogonal_calc[2*index_ort+1]*ortogonal_calc[2*index_ort+1]))) ) >> (VAGA_DILENNJA_I_DIJUCHE + 4);
    }
    else
    {
      unsigned int index_m, index_ort;
      switch (i)
      {
      case I_Ua:
      case I_Ub:
      case I_Uc:
        {
          unsigned int delta_index = (i - I_Ua);
          if ((current_settings_prt.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_PHASE_LINE) == 0)
          {
            index_m = IM_UA + delta_index;
            index_ort = FULL_ORT_Ua + delta_index;
          }
          else
          {
            index_m = IM_UAB + delta_index;
            index_ort = FULL_ORT_Uab + delta_index;
          }
          break;
        }
      case I_3U0_Ubc_TN2:
      case I_Uab_TN2:
        {
          unsigned int delta_index = (i - I_3U0_Ubc_TN2);
          index_m = IM_3U0_UBC_TN2 + delta_index;
          index_ort = FULL_ORT_3U0_Ubc_TN2 + delta_index;
          break;
        }
      default:
        {
          //���������� ����� ����� �� ���� � ����
          total_error_sw_fixed(67);
        }
      }
      
      measurement[index_m] = ( MNOGNYK_U_DIJUCHE*(sqrt_32((unsigned int)(ortogonal_calc[2*index_ort]*ortogonal_calc[2*index_ort]) + (unsigned int)(ortogonal_calc[2*index_ort+1]*ortogonal_calc[2*index_ort+1]))) ) >> (VAGA_DILENNJA_U_DIJUCHE + 4);
    }
    
  }
  /***/

  /***/
  //����������� ���� �������� ����� ������� 3I0
  /***/
  if (value_3I0_i_float > value_3I0_f_float)
  {
    float in_square_root, out_square_root;
    in_square_root = value_3I0_i_float*value_3I0_i_float - value_3I0_f_float*value_3I0_f_float;
    if (arm_sqrt_f32(in_square_root, &out_square_root) == ARM_MATH_SUCCESS)
    {
      measurement[IM_3I0_other_g] = (unsigned int)out_square_root;
    }
    else
    {
      //���� ���� ����� ��������, ������� �������� ����������� �������, ���� ����� ��������� ��������, ��� ���� ���� �� ������������
      total_error_sw_fixed(59);
    }
  }
  else
    measurement[IM_3I0_other_g] = 0;
  /***/

  /***
  �������������� ������ ������ � Ib
  ***/
  int ortogonal_local_3I0[2];
  int _x, _y;
  
#if (4 + VAGA_DILENNJA_3I0_DIJUCHE_D_mA) >= VAGA_DILENNJA_I_DIJUCHE  
  ortogonal_local_3I0[0] = ((MNOGNYK_3I0_DIJUCHE_D_mA*ortogonal_calc[2*FULL_ORT_3I0 + 0]) >> (4 + VAGA_DILENNJA_3I0_DIJUCHE_D_mA - VAGA_DILENNJA_I_DIJUCHE))/MNOGNYK_I_DIJUCHE;
  ortogonal_local_3I0[1] = ((MNOGNYK_3I0_DIJUCHE_D_mA*ortogonal_calc[2*FULL_ORT_3I0 + 1]) >> (4 + VAGA_DILENNJA_3I0_DIJUCHE_D_mA - VAGA_DILENNJA_I_DIJUCHE))/MNOGNYK_I_DIJUCHE;
#else
  ortogonal_local_3I0[0] = ((MNOGNYK_3I0_DIJUCHE_D_mA*ortogonal_calc[2*FULL_ORT_3I0 + 0]) << (VAGA_DILENNJA_I_DIJUCHE - (VAGA_DILENNJA_3I0_DIJUCHE_D_mA + 4)))/MNOGNYK_I_DIJUCHE;
  ortogonal_local_3I0[1] = ((MNOGNYK_3I0_DIJUCHE_D_mA*ortogonal_calc[2*FULL_ORT_3I0 + 1]) << (VAGA_DILENNJA_I_DIJUCHE - (VAGA_DILENNJA_3I0_DIJUCHE_D_mA + 4)))/MNOGNYK_I_DIJUCHE;
#endif
  
  int T0 = (int)current_settings_prt.T0, TCurrent = (int)current_settings_prt.TCurrent;
  _x = ortogonal_calc[2*FULL_ORT_Ib + 0] = T0*ortogonal_local_3I0[0]/TCurrent - (ortogonal_calc[2*FULL_ORT_Ia + 0] + ortogonal_calc[2*FULL_ORT_Ic + 0]);
  _y = ortogonal_calc[2*FULL_ORT_Ib + 1] = T0*ortogonal_local_3I0[1]/TCurrent - (ortogonal_calc[2*FULL_ORT_Ia + 1] + ortogonal_calc[2*FULL_ORT_Ic + 1]);
  if (copy_to_low_tasks == true)
  {
    ortogonal_calc_low[2*FULL_ORT_Ib + 0] = _x;
    ortogonal_calc_low[2*FULL_ORT_Ib + 1] = _y;
  }
  measurement[IM_IB_r] = ( MNOGNYK_I_DIJUCHE*(sqrt_64((unsigned long long)((long long)_x*(long long)_x) + (unsigned long long)((long long)_y*(long long)_y))) ) >> (VAGA_DILENNJA_I_DIJUCHE + 4);

  if ((current_settings_prt.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_PHASE_LINE) == 0)
  {
    //Ubc
    _x = ortogonal_calc[2*FULL_ORT_Ubc + 0] = ortogonal_calc[2*FULL_ORT_Ub    ] - ortogonal_calc[2*FULL_ORT_Uc    ];
    _y = ortogonal_calc[2*FULL_ORT_Ubc + 1] = ortogonal_calc[2*FULL_ORT_Ub + 1] - ortogonal_calc[2*FULL_ORT_Uc + 1];
    if (copy_to_low_tasks == true)
    {
      ortogonal_calc_low[2*FULL_ORT_Ubc + 0] = _x;
      ortogonal_calc_low[2*FULL_ORT_Ubc + 1] = _y;
    }
    measurement[IM_UBC] = ( MNOGNYK_U_DIJUCHE*(sqrt_64((unsigned long long)((long long)_x*(long long)_x) + (unsigned long long)((long long)_y*(long long)_y))) ) >> (VAGA_DILENNJA_U_DIJUCHE + 4);
  
    //Uca
    _x = ortogonal_calc[2*FULL_ORT_Uca + 0] = ortogonal_calc[2*FULL_ORT_Uc    ] - ortogonal_calc[2*FULL_ORT_Ua    ];
    _y = ortogonal_calc[2*FULL_ORT_Uca + 1] = ortogonal_calc[2*FULL_ORT_Uc + 1] - ortogonal_calc[2*FULL_ORT_Ua + 1];
    if (copy_to_low_tasks == true)
    {
      ortogonal_calc_low[2*FULL_ORT_Uca + 0] = _x;
      ortogonal_calc_low[2*FULL_ORT_Uca + 1] = _y;
    }
    measurement[IM_UCA] = ( MNOGNYK_U_DIJUCHE*(sqrt_64((unsigned long long)((long long)_x*(long long)_x) + (unsigned long long)((long long)_y*(long long)_y))) ) >> (VAGA_DILENNJA_U_DIJUCHE + 4);

    //Uab
    _x = ortogonal_calc[2*FULL_ORT_Uab + 0] = ortogonal_calc[2*FULL_ORT_Ua    ] - ortogonal_calc[2*FULL_ORT_Ub    ];
    _y = ortogonal_calc[2*FULL_ORT_Uab + 1] = ortogonal_calc[2*FULL_ORT_Ua + 1] - ortogonal_calc[2*FULL_ORT_Ub + 1];
    if (copy_to_low_tasks == true)
    {
      ortogonal_calc_low[2*FULL_ORT_Uab + 0] = _x;
      ortogonal_calc_low[2*FULL_ORT_Uab + 1] = _y;
    }
    measurement[IM_UAB] = ( MNOGNYK_U_DIJUCHE*(sqrt_64((unsigned long long)((long long)_x*(long long)_x) + (unsigned long long)((long long)_y*(long long)_y))) ) >> (VAGA_DILENNJA_U_DIJUCHE + 4);
  }
  else
  {
    //Ua
    ortogonal_calc[2*FULL_ORT_Ua + 0] = 0;
    ortogonal_calc[2*FULL_ORT_Ua + 1] = 0;
    measurement[IM_UA] = 0;

    //Ub
    ortogonal_calc[2*FULL_ORT_Ub + 0] = 0;
    ortogonal_calc[2*FULL_ORT_Ub + 1] = 0;
    measurement[IM_UB] = 0;

    //Uc
    ortogonal_calc[2*FULL_ORT_Uc + 0] = 0;
    ortogonal_calc[2*FULL_ORT_Uc + 1] = 0;
    measurement[IM_UC] = 0;
    
    if (copy_to_low_tasks == true)
    {
      //Ua
      ortogonal_calc_low[2*FULL_ORT_Ua + 0] = 0;
      ortogonal_calc_low[2*FULL_ORT_Ua + 1] = 0;

      //Ub
      ortogonal_calc_low[2*FULL_ORT_Ub + 0] = 0;
      ortogonal_calc_low[2*FULL_ORT_Ub + 1] = 0;

      //Uc
      ortogonal_calc_low[2*FULL_ORT_Uc + 0] = 0;
      ortogonal_calc_low[2*FULL_ORT_Uc + 1] = 0;
    }
  
  }
  /***/
  if (copy_to_low_tasks == true) current_delta_phi();

  /***/
  //������������ ������� ��� ��� (��� �������)
  /***/
  directional_mtz(ortogonal_calc, number_group_stp);
  /***/
  
  if (
      ((current_settings_prt.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_3U0_Ubc_TN2) == 0) &&
      ((current_settings_prt.control_zz & CTR_ZZ1_TYPE) == 0)
     )   
  {
    detector_kuta_nzz(ortogonal_calc);
  }
  /***/
  
  /***/
  //����������� ����� ��������� �����������
  /***/
  velychyna_zvorotnoi_poslidovnosti(ortogonal_calc);
  /***/
  
  /***/
  //����������� �����
  /***/
  calc_resistance(ortogonal_calc, resistance);
  /***/

  if(++number_inputs_for_fix_one_period >= 20)
  {
    /***/
    //���������� ������� ����������� (��� �� 20��)
    /***/
    calc_power(ortogonal_calc);
    /***/
    
    number_inputs_for_fix_one_period = 0;
  }
}
/*****************************************************/

/*****************************************************/
//������ ������� ���������� �����
/*****************************************************/
inline void input_scan(void)
{
  unsigned int state_inputs_into_pin, temp_state_inputs_into_pin; //���� � ��� ������� �������� ����� ������� �� ����� ��������� (���)
  static unsigned int state_inputs_into_pin_trigger; //� ��� ����� ���������� ��������� ���� ���, � ������� ���� �� ���������� .�� ���������� ��� ���� �� ���� ���������� ������� �������

  /***************************/
  //� ��� ������ ������ ����� ����� ��������� (���), �� ���������� �� �������� �����
  /*
  -----------------------------
  �������� ��������� � �������� ��� ����� state_inputs_into_pin
    "�     ������ " - ������� ������������� ��� (1)
    "���� �������" - ������� ���������     ��� (0)
  -----------------------------
  */
  unsigned int temp_state_inputs_into_pin_1 = _DEVICE_REGISTER(Bank1_SRAM2_ADDR, OFFSET_INPUTS_1) & ((1 << NUMBER_INPUTS_1) - 1);
  unsigned int temp_state_inputs_into_pin_2 = _DEVICE_REGISTER(Bank1_SRAM2_ADDR, OFFSET_INPUTS_2) & ((1 << NUMBER_INPUTS_2) - 1);
  temp_state_inputs_into_pin = temp_state_inputs_into_pin_1 | (temp_state_inputs_into_pin_2 << NUMBER_INPUTS_1);
  
  //������� �������, ��� �������� ����� �������� ��������� �� ������
  state_inputs_into_pin = 0;
  for (unsigned int index = 0; index < NUMBER_INPUTS; index++)
  {
    if ((temp_state_inputs_into_pin & (1 << index)) != 0) 
    {
      if (index < NUMBER_INPUTS_1)
        state_inputs_into_pin |= 1 << (NUMBER_INPUTS_1 - index - 1);
      else
        state_inputs_into_pin |= 1 << index;
    }
  }
  /***************************/
  
  /***************************/
  //������� ������� ������� ���������� �����
  /***************************/
  for(unsigned int i = 0; i < NUMBER_INPUTS; i++)
  {
    unsigned int maska = 1<<i;
    int max_value_timer = current_settings_prt.dopusk_dv[i];

    if (global_timers[INDEX_TIMER_INPUT_START + i] < 0)
    {
      //������� �� ���� ����� ����������� ����� ����������� ����� ���, ���� �������� ������� � ��'�����
      //�� ������ �� ������ �� ��������� � ��������� ������
      
      //���������� �� ��������� ���� ����� ������� ������������ �����
      if ((state_inputs_into_pin & maska) != (state_inputs & maska))
      {
        //���� ���� ����� �������, �� �������� 䳿 �� ��� �����

        //1-��: �����'������� ������� ���� �����
        state_inputs_into_pin_trigger &= ~maska;
        state_inputs_into_pin_trigger |= (state_inputs_into_pin & maska);

        //2-��: ��������� ������ ������� ����������� �����
        global_timers[INDEX_TIMER_INPUT_START + i] = 0;
      }
    }
    else
    {
      //���� ������ ��������� �������� 䳿 � ��������
      if (global_timers[INDEX_TIMER_INPUT_START + i] < max_value_timer)
      {
        //���� ������ �� �� ����� �� ����� ���������, �� ������ �������� ���� ��������
        global_timers[INDEX_TIMER_INPUT_START + i] += DELTA_TIME_FOR_TIMERS;
        
        //� �������, ���� ��� ������� �� ���� �������� ������
        //� �� ���������� �� �� ������� ������� "� ������"->"���� �������"
        //�� ����� ������� �� ��� ���������� ������� ������� ������, �� ������ �� ���� � - 
        //� �� ������, �� ����� �������� n�����, �� �������� "� ������"->"���� �������" �� ������ ���������� ������� �� ����������� 
        if ((current_settings_prt.type_of_input_signal & maska) != 0)
        {
           if ((state_inputs_into_pin_trigger & maska) == 0)
           {
             if ((state_inputs_into_pin & maska) != 0)
               global_timers[INDEX_TIMER_INPUT_START + i] = -1;
           }
        }
      }
    }
    
    //���� �������� ������� ������� ����������� � ����� ������������� �������, �� ����������, �� �������� ������� ����� �����
    if (global_timers[INDEX_TIMER_INPUT_START + i] >= max_value_timer)
    {
      //����������, �� ���� ��� ������� � �������� �� ������, ���� ��� �� ������ ������� ������� ������� ����������� �����
      unsigned int state_1, state_2;
        
      state_1 = state_inputs_into_pin_trigger & maska;
      state_2 = state_inputs_into_pin  & maska;
        
      if (state_1 == state_2)
      {
        //���� ��� ����� ����������, �� �� �������, �� �������� ��� ����� ����������� ����� � ������� ����� ���� �����
        //��� ����� ��������� �� ��� �������    ����� 1 - �� �������� ����, � 0 - �� �������� ����
        //                        ��� ���������� ����� 0 - �� �������� ����, � 1 - �� �������� ����
          state_inputs &=  ~maska;
          state_inputs |=   state_2;
      }
        
      //� ����-����� ������, �� ������� ���� �����, �� �, � ������� ������ ������� ���������� �� ����, �� ������������� � �������� ��'���� ��������
      global_timers[INDEX_TIMER_INPUT_START + i] = -1;
    }
  }
  /***************************/
  
  /***************************/
  //���������, ���� ������ � ����� ��������
  /***************************/
  active_inputs = (state_inputs ^ current_settings_prt.type_of_input);
  /***************************/
  
}
/*****************************************************/

/*****************************************************/
//������� ������� �������
/*****************************************************/
inline void clocking_global_timers(void)
{
  //����������� �������� �����
  input_scan();
  
  //����������� �� ����� ������� �����
  for (unsigned int i = (INDEX_TIMER_INPUT_START + NUMBER_INPUTS); i < MAX_NUMBER_GLOBAL_TIMERS; i++)
  {
    if (global_timers[i] >= 0)
    {
      int max_value = 0;
      //������ ������ ����, �� ������ ����� ��������� � ��� ����, �� �������� ������� �� ��'����
      switch (i)
      {
        //� ����� ����� ����� ������� max_value ���������� �������� ������������� �������� ������� �� ����� �� ��� ����������
      case (INDEX_TIMER_DF_PROLONG_SET_FOR_BUTTON_INTERFACE_START + 0):
      case (INDEX_TIMER_DF_PROLONG_SET_FOR_BUTTON_INTERFACE_START + 1):
      case (INDEX_TIMER_DF_PROLONG_SET_FOR_BUTTON_INTERFACE_START + 2):
      case (INDEX_TIMER_DF_PROLONG_SET_FOR_BUTTON_INTERFACE_START + 3):
      case (INDEX_TIMER_DF_PROLONG_SET_FOR_BUTTON_INTERFACE_START + 4):
      case (INDEX_TIMER_DF_PROLONG_SET_FOR_BUTTON_INTERFACE_START + 5):
      case (INDEX_TIMER_DF_PROLONG_SET_FOR_BUTTON_INTERFACE_START + 6):
      case (INDEX_TIMER_DF_PROLONG_SET_FOR_BUTTON_INTERFACE_START + 7):
        {
          max_value =  current_settings_prt.timeout_pause_df[i - INDEX_TIMER_DF_PROLONG_SET_FOR_BUTTON_INTERFACE_START]/*TIMEOUT_DF_PAUSE_FOR_BUTTONS_INTERFACE*/;
          break;
        }
      case (INDEX_TIMER_DF_PAUSE_START + 0):
      case (INDEX_TIMER_DF_PAUSE_START + 1):
      case (INDEX_TIMER_DF_PAUSE_START + 2):
      case (INDEX_TIMER_DF_PAUSE_START + 3):
      case (INDEX_TIMER_DF_PAUSE_START + 4):
      case (INDEX_TIMER_DF_PAUSE_START + 5):
      case (INDEX_TIMER_DF_PAUSE_START + 6):
      case (INDEX_TIMER_DF_PAUSE_START + 7):
        {
          max_value =  current_settings_prt.timeout_pause_df[i - INDEX_TIMER_DF_PAUSE_START];
          break;
        }
      case (INDEX_TIMER_DF_WORK_START + 0):
      case (INDEX_TIMER_DF_WORK_START + 1):
      case (INDEX_TIMER_DF_WORK_START + 2):
      case (INDEX_TIMER_DF_WORK_START + 3):
      case (INDEX_TIMER_DF_WORK_START + 4):
      case (INDEX_TIMER_DF_WORK_START + 5):
      case (INDEX_TIMER_DF_WORK_START + 6):
      case (INDEX_TIMER_DF_WORK_START + 7):
        {
          max_value =  current_settings_prt.timeout_work_df[i - INDEX_TIMER_DF_WORK_START];
          break;
        }
      case INDEX_TIMER_MTZ1:
        {
          int max_value_pare1, max_value_pare2;
          max_value_pare1 =  (current_settings_prt.timeout_mtz_1[0] >= current_settings_prt.timeout_mtz_1[1]) ? current_settings_prt.timeout_mtz_1[0] : current_settings_prt.timeout_mtz_1[1];
          max_value_pare2 =  (current_settings_prt.timeout_mtz_1[2] >= current_settings_prt.timeout_mtz_1[3]) ? current_settings_prt.timeout_mtz_1[2] : current_settings_prt.timeout_mtz_1[3];
          max_value = (max_value_pare1 >= max_value_pare2) ? max_value_pare1 : max_value_pare2;
          break;
        }
      case INDEX_TIMER_MTZ1_N_VPERED:
        {
          int max_value_pare1, max_value_pare2;
          max_value_pare1 =  (current_settings_prt.timeout_mtz_1_n_vpered[0] >= current_settings_prt.timeout_mtz_1_n_vpered[1]) ? current_settings_prt.timeout_mtz_1_n_vpered[0] : current_settings_prt.timeout_mtz_1_n_vpered[1];
          max_value_pare2 =  (current_settings_prt.timeout_mtz_1_n_vpered[2] >= current_settings_prt.timeout_mtz_1_n_vpered[3]) ? current_settings_prt.timeout_mtz_1_n_vpered[2] : current_settings_prt.timeout_mtz_1_n_vpered[3];
          max_value = (max_value_pare1 >= max_value_pare2) ? max_value_pare1 : max_value_pare2;
          break;
        }
      case INDEX_TIMER_MTZ1_N_NAZAD:
        {
          int max_value_pare1, max_value_pare2;
          max_value_pare1 =  (current_settings_prt.timeout_mtz_1_n_nazad[0] >= current_settings_prt.timeout_mtz_1_n_nazad[1]) ? current_settings_prt.timeout_mtz_1_n_nazad[0] : current_settings_prt.timeout_mtz_1_n_nazad[1];
          max_value_pare2 =  (current_settings_prt.timeout_mtz_1_n_nazad[2] >= current_settings_prt.timeout_mtz_1_n_nazad[3]) ? current_settings_prt.timeout_mtz_1_n_nazad[2] : current_settings_prt.timeout_mtz_1_n_nazad[3];
          max_value = (max_value_pare1 >= max_value_pare2) ? max_value_pare1 : max_value_pare2;
          break;
        }
      case INDEX_TIMER_MTZ1_PO_NAPRUZI:
        {
          int max_value_pare1, max_value_pare2;
          max_value_pare1 =  (current_settings_prt.timeout_mtz_1_po_napruzi[0] >= current_settings_prt.timeout_mtz_1_po_napruzi[1]) ? current_settings_prt.timeout_mtz_1_po_napruzi[0] : current_settings_prt.timeout_mtz_1_po_napruzi[1];
          max_value_pare2 =  (current_settings_prt.timeout_mtz_1_po_napruzi[2] >= current_settings_prt.timeout_mtz_1_po_napruzi[3]) ? current_settings_prt.timeout_mtz_1_po_napruzi[2] : current_settings_prt.timeout_mtz_1_po_napruzi[3];
          max_value = (max_value_pare1 >= max_value_pare2) ? max_value_pare1 : max_value_pare2;
          break;
        }

      case INDEX_TIMER_MTZ2:
        {
          int max_value_pare1, max_value_pare2;
          max_value_pare1 =  (current_settings_prt.timeout_mtz_2[0] >= current_settings_prt.timeout_mtz_2[1]) ? current_settings_prt.timeout_mtz_2[0] : current_settings_prt.timeout_mtz_2[1];
          max_value_pare2 =  (current_settings_prt.timeout_mtz_2[2] >= current_settings_prt.timeout_mtz_2[3]) ? current_settings_prt.timeout_mtz_2[2] : current_settings_prt.timeout_mtz_2[3];
          max_value = (max_value_pare1 >= max_value_pare2) ? max_value_pare1 : max_value_pare2;
          break;
        }
      case INDEX_TIMER_MTZ2_DEPENDENT:
        {
          max_value =  TIMEOUT_MTZ2_MAX + 1;
          break;
        }
      case INDEX_TIMER_MTZ2_PR:
        {
          int max_value_pare1, max_value_pare2;
          max_value_pare1 =  (current_settings_prt.timeout_mtz_2_pr[0] >= current_settings_prt.timeout_mtz_2_pr[1]) ? current_settings_prt.timeout_mtz_2_pr[0] : current_settings_prt.timeout_mtz_2_pr[1];
          max_value_pare2 =  (current_settings_prt.timeout_mtz_2_pr[2] >= current_settings_prt.timeout_mtz_2_pr[3]) ? current_settings_prt.timeout_mtz_2_pr[2] : current_settings_prt.timeout_mtz_2_pr[3];
          max_value = (max_value_pare1 >= max_value_pare2) ? max_value_pare1 : max_value_pare2;
          break;
        }
      case INDEX_TIMER_MTZ2_N_VPERED:
        {
          int max_value_pare1, max_value_pare2;
          max_value_pare1 =  (current_settings_prt.timeout_mtz_2_n_vpered[0] >= current_settings_prt.timeout_mtz_2_n_vpered[1]) ? current_settings_prt.timeout_mtz_2_n_vpered[0] : current_settings_prt.timeout_mtz_2_n_vpered[1];
          max_value_pare2 =  (current_settings_prt.timeout_mtz_2_n_vpered[2] >= current_settings_prt.timeout_mtz_2_n_vpered[3]) ? current_settings_prt.timeout_mtz_2_n_vpered[2] : current_settings_prt.timeout_mtz_2_n_vpered[3];
          max_value = (max_value_pare1 >= max_value_pare2) ? max_value_pare1 : max_value_pare2;
          break;
        }
      case INDEX_TIMER_MTZ2_N_VPERED_PR:
        {
          int max_value_pare1, max_value_pare2;
          max_value_pare1 =  (current_settings_prt.timeout_mtz_2_n_vpered_pr[0] >= current_settings_prt.timeout_mtz_2_n_vpered_pr[1]) ? current_settings_prt.timeout_mtz_2_n_vpered_pr[0] : current_settings_prt.timeout_mtz_2_n_vpered_pr[1];
          max_value_pare2 =  (current_settings_prt.timeout_mtz_2_n_vpered_pr[2] >= current_settings_prt.timeout_mtz_2_n_vpered_pr[3]) ? current_settings_prt.timeout_mtz_2_n_vpered_pr[2] : current_settings_prt.timeout_mtz_2_n_vpered_pr[3];
          max_value = (max_value_pare1 >= max_value_pare2) ? max_value_pare1 : max_value_pare2;
          break;
        }
      case INDEX_TIMER_MTZ2_N_NAZAD:
        {
          int max_value_pare1, max_value_pare2;
          max_value_pare1 =  (current_settings_prt.timeout_mtz_2_n_nazad[0] >= current_settings_prt.timeout_mtz_2_n_nazad[1]) ? current_settings_prt.timeout_mtz_2_n_nazad[0] : current_settings_prt.timeout_mtz_2_n_nazad[1];
          max_value_pare2 =  (current_settings_prt.timeout_mtz_2_n_nazad[2] >= current_settings_prt.timeout_mtz_2_n_nazad[3]) ? current_settings_prt.timeout_mtz_2_n_nazad[2] : current_settings_prt.timeout_mtz_2_n_nazad[3];
          max_value = (max_value_pare1 >= max_value_pare2) ? max_value_pare1 : max_value_pare2;
          break;
        }
      case INDEX_TIMER_MTZ2_N_NAZAD_PR:
        {
          int max_value_pare1, max_value_pare2;
          max_value_pare1 =  (current_settings_prt.timeout_mtz_2_n_nazad_pr[0] >= current_settings_prt.timeout_mtz_2_n_nazad_pr[1]) ? current_settings_prt.timeout_mtz_2_n_nazad_pr[0] : current_settings_prt.timeout_mtz_2_n_nazad_pr[1];
          max_value_pare2 =  (current_settings_prt.timeout_mtz_2_n_nazad_pr[2] >= current_settings_prt.timeout_mtz_2_n_nazad_pr[3]) ? current_settings_prt.timeout_mtz_2_n_nazad_pr[2] : current_settings_prt.timeout_mtz_2_n_nazad_pr[3];
          max_value = (max_value_pare1 >= max_value_pare2) ? max_value_pare1 : max_value_pare2;
          break;
        }
      case INDEX_TIMER_MTZ2_PO_NAPRUZI:
        {
          int max_value_pare1, max_value_pare2;
          max_value_pare1 =  (current_settings_prt.timeout_mtz_2_po_napruzi[0] >= current_settings_prt.timeout_mtz_2_po_napruzi[1]) ? current_settings_prt.timeout_mtz_2_po_napruzi[0] : current_settings_prt.timeout_mtz_2_po_napruzi[1];
          max_value_pare2 =  (current_settings_prt.timeout_mtz_2_po_napruzi[2] >= current_settings_prt.timeout_mtz_2_po_napruzi[3]) ? current_settings_prt.timeout_mtz_2_po_napruzi[2] : current_settings_prt.timeout_mtz_2_po_napruzi[3];
          max_value = (max_value_pare1 >= max_value_pare2) ? max_value_pare1 : max_value_pare2;
          break;
        }
      case INDEX_TIMER_MTZ2_PO_NAPRUZI_PR:
        {
          int max_value_pare1, max_value_pare2;
          max_value_pare1 =  (current_settings_prt.timeout_mtz_2_po_napruzi_pr[0] >= current_settings_prt.timeout_mtz_2_po_napruzi_pr[1]) ? current_settings_prt.timeout_mtz_2_po_napruzi_pr[0] : current_settings_prt.timeout_mtz_2_po_napruzi_pr[1];
          max_value_pare2 =  (current_settings_prt.timeout_mtz_2_po_napruzi_pr[2] >= current_settings_prt.timeout_mtz_2_po_napruzi_pr[3]) ? current_settings_prt.timeout_mtz_2_po_napruzi_pr[2] : current_settings_prt.timeout_mtz_2_po_napruzi_pr[3];
          max_value = (max_value_pare1 >= max_value_pare2) ? max_value_pare1 : max_value_pare2;
          break;
        }
      case INDEX_TIMER_MTZ2_VVID_PR:
        {
          int max_value_pare1, max_value_pare2;
          max_value_pare1 =  (current_settings_prt.timeout_mtz_2_vvid_pr[0] >= current_settings_prt.timeout_mtz_2_vvid_pr[1]) ? current_settings_prt.timeout_mtz_2_vvid_pr[0] : current_settings_prt.timeout_mtz_2_vvid_pr[1];
          max_value_pare2 =  (current_settings_prt.timeout_mtz_2_vvid_pr[2] >= current_settings_prt.timeout_mtz_2_vvid_pr[3]) ? current_settings_prt.timeout_mtz_2_vvid_pr[2] : current_settings_prt.timeout_mtz_2_vvid_pr[3];
          max_value = (max_value_pare1 >= max_value_pare2) ? max_value_pare1 : max_value_pare2;
          break;
        }
      case INDEX_TIMER_MTZ3:
        {
          int max_value_pare1, max_value_pare2;
          max_value_pare1 =  (current_settings_prt.timeout_mtz_3[0] >= current_settings_prt.timeout_mtz_3[1]) ? current_settings_prt.timeout_mtz_3[0] : current_settings_prt.timeout_mtz_3[1];
          max_value_pare2 =  (current_settings_prt.timeout_mtz_3[2] >= current_settings_prt.timeout_mtz_3[3]) ? current_settings_prt.timeout_mtz_3[2] : current_settings_prt.timeout_mtz_3[3];
          max_value = (max_value_pare1 >= max_value_pare2) ? max_value_pare1 : max_value_pare2;
          break;
        }
      case INDEX_TIMER_MTZ3_N_VPERED:
        {
          int max_value_pare1, max_value_pare2;
          max_value_pare1 =  (current_settings_prt.timeout_mtz_3_n_vpered[0] >= current_settings_prt.timeout_mtz_3_n_vpered[1]) ? current_settings_prt.timeout_mtz_3_n_vpered[0] : current_settings_prt.timeout_mtz_3_n_vpered[1];
          max_value_pare2 =  (current_settings_prt.timeout_mtz_3_n_vpered[2] >= current_settings_prt.timeout_mtz_3_n_vpered[3]) ? current_settings_prt.timeout_mtz_3_n_vpered[2] : current_settings_prt.timeout_mtz_3_n_vpered[3];
          max_value = (max_value_pare1 >= max_value_pare2) ? max_value_pare1 : max_value_pare2;
          break;
        }
      case INDEX_TIMER_MTZ3_N_NAZAD:
        {
          int max_value_pare1, max_value_pare2;
          max_value_pare1 =  (current_settings_prt.timeout_mtz_3_n_nazad[0] >= current_settings_prt.timeout_mtz_3_n_nazad[1]) ? current_settings_prt.timeout_mtz_3_n_nazad[0] : current_settings_prt.timeout_mtz_3_n_nazad[1];
          max_value_pare2 =  (current_settings_prt.timeout_mtz_3_n_nazad[2] >= current_settings_prt.timeout_mtz_3_n_nazad[3]) ? current_settings_prt.timeout_mtz_3_n_nazad[2] : current_settings_prt.timeout_mtz_3_n_nazad[3];
          max_value = (max_value_pare1 >= max_value_pare2) ? max_value_pare1 : max_value_pare2;
          break;
        }
      case INDEX_TIMER_MTZ3_PO_NAPRUZI:
        {
          int max_value_pare1, max_value_pare2;
          max_value_pare1 =  (current_settings_prt.timeout_mtz_3_po_napruzi[0] >= current_settings_prt.timeout_mtz_3_po_napruzi[1]) ? current_settings_prt.timeout_mtz_3_po_napruzi[0] : current_settings_prt.timeout_mtz_3_po_napruzi[1];
          max_value_pare2 =  (current_settings_prt.timeout_mtz_3_po_napruzi[2] >= current_settings_prt.timeout_mtz_3_po_napruzi[3]) ? current_settings_prt.timeout_mtz_3_po_napruzi[2] : current_settings_prt.timeout_mtz_3_po_napruzi[3];
          max_value = (max_value_pare1 >= max_value_pare2) ? max_value_pare1 : max_value_pare2;
          break;
        }
      case INDEX_TIMER_MTZ4:
        {
          int max_value_pare1, max_value_pare2;
          max_value_pare1 =  (current_settings_prt.timeout_mtz_4[0] >= current_settings_prt.timeout_mtz_4[1]) ? current_settings_prt.timeout_mtz_4[0] : current_settings_prt.timeout_mtz_4[1];
          max_value_pare2 =  (current_settings_prt.timeout_mtz_4[2] >= current_settings_prt.timeout_mtz_4[3]) ? current_settings_prt.timeout_mtz_4[2] : current_settings_prt.timeout_mtz_4[3];
          max_value = (max_value_pare1 >= max_value_pare2) ? max_value_pare1 : max_value_pare2;
          break;
        }
      case INDEX_TIMER_MTZ4_N_VPERED:
        {
          int max_value_pare1, max_value_pare2;
          max_value_pare1 =  (current_settings_prt.timeout_mtz_4_n_vpered[0] >= current_settings_prt.timeout_mtz_4_n_vpered[1]) ? current_settings_prt.timeout_mtz_4_n_vpered[0] : current_settings_prt.timeout_mtz_4_n_vpered[1];
          max_value_pare2 =  (current_settings_prt.timeout_mtz_4_n_vpered[2] >= current_settings_prt.timeout_mtz_4_n_vpered[3]) ? current_settings_prt.timeout_mtz_4_n_vpered[2] : current_settings_prt.timeout_mtz_4_n_vpered[3];
          max_value = (max_value_pare1 >= max_value_pare2) ? max_value_pare1 : max_value_pare2;
          break;
        }
      case INDEX_TIMER_MTZ4_N_NAZAD:
        {
          int max_value_pare1, max_value_pare2;
          max_value_pare1 =  (current_settings_prt.timeout_mtz_4_n_nazad[0] >= current_settings_prt.timeout_mtz_4_n_nazad[1]) ? current_settings_prt.timeout_mtz_4_n_nazad[0] : current_settings_prt.timeout_mtz_4_n_nazad[1];
          max_value_pare2 =  (current_settings_prt.timeout_mtz_4_n_nazad[2] >= current_settings_prt.timeout_mtz_4_n_nazad[3]) ? current_settings_prt.timeout_mtz_4_n_nazad[2] : current_settings_prt.timeout_mtz_4_n_nazad[3];
          max_value = (max_value_pare1 >= max_value_pare2) ? max_value_pare1 : max_value_pare2;
          break;
        }
      case INDEX_TIMER_MTZ4_PO_NAPRUZI:
        {
          int max_value_pare1, max_value_pare2;
          max_value_pare1 =  (current_settings_prt.timeout_mtz_4_po_napruzi[0] >= current_settings_prt.timeout_mtz_4_po_napruzi[1]) ? current_settings_prt.timeout_mtz_4_po_napruzi[0] : current_settings_prt.timeout_mtz_4_po_napruzi[1];
          max_value_pare2 =  (current_settings_prt.timeout_mtz_4_po_napruzi[2] >= current_settings_prt.timeout_mtz_4_po_napruzi[3]) ? current_settings_prt.timeout_mtz_4_po_napruzi[2] : current_settings_prt.timeout_mtz_4_po_napruzi[3];
          max_value = (max_value_pare1 >= max_value_pare2) ? max_value_pare1 : max_value_pare2;
          break;
        }
      case INDEX_TIMER_ZZ_3I0:
        {
          int max_value_pare1, max_value_pare2;
          max_value_pare1 =  (current_settings_prt.timeout_zz_3I0[0] >= current_settings_prt.timeout_zz_3I0[1]) ? current_settings_prt.timeout_zz_3I0[0] : current_settings_prt.timeout_zz_3I0[1];
          max_value_pare2 =  (current_settings_prt.timeout_zz_3I0[2] >= current_settings_prt.timeout_zz_3I0[3]) ? current_settings_prt.timeout_zz_3I0[2] : current_settings_prt.timeout_zz_3I0[3];
          max_value = (max_value_pare1 >= max_value_pare2) ? max_value_pare1 : max_value_pare2;
          break;
        }
      case INDEX_TIMER_ZZ_3U0:
        {
          int max_value_pare1, max_value_pare2;
          max_value_pare1 =  (current_settings_prt.timeout_zz_3U0[0] >= current_settings_prt.timeout_zz_3U0[1]) ? current_settings_prt.timeout_zz_3U0[0] : current_settings_prt.timeout_zz_3U0[1];
          max_value_pare2 =  (current_settings_prt.timeout_zz_3U0[2] >= current_settings_prt.timeout_zz_3U0[3]) ? current_settings_prt.timeout_zz_3U0[2] : current_settings_prt.timeout_zz_3U0[3];
          max_value = (max_value_pare1 >= max_value_pare2) ? max_value_pare1 : max_value_pare2;
          break;
        }
      case INDEX_TIMER_NZZ:
        {
          int max_value_pare1, max_value_pare2;
          max_value_pare1 =  (current_settings_prt.timeout_nzz[0] >= current_settings_prt.timeout_nzz[1]) ? current_settings_prt.timeout_nzz[0] : current_settings_prt.timeout_nzz[1];
          max_value_pare2 =  (current_settings_prt.timeout_nzz[2] >= current_settings_prt.timeout_nzz[3]) ? current_settings_prt.timeout_nzz[2] : current_settings_prt.timeout_nzz[3];
          max_value = (max_value_pare1 >= max_value_pare2) ? max_value_pare1 : max_value_pare2;
          break;
        }
      case INDEX_TIMER_ZOP:
        {
          int max_value_pare1, max_value_pare2;
          max_value_pare1 =  (current_settings_prt.timeout_zop[0] >= current_settings_prt.timeout_zop[1]) ? current_settings_prt.timeout_zop[0] : current_settings_prt.timeout_zop[1];
          max_value_pare2 =  (current_settings_prt.timeout_zop[2] >= current_settings_prt.timeout_zop[3]) ? current_settings_prt.timeout_zop[2] : current_settings_prt.timeout_zop[3];
          max_value = (max_value_pare1 >= max_value_pare2) ? max_value_pare1 : max_value_pare2;
          break;
        }
      case INDEX_TIMER_UROV1:
        {
          int max_value_pare1, max_value_pare2;
          max_value_pare1 =  (current_settings_prt.timeout_urov_1[0] >= current_settings_prt.timeout_urov_1[1]) ? current_settings_prt.timeout_urov_1[0] : current_settings_prt.timeout_urov_1[1];
          max_value_pare2 =  (current_settings_prt.timeout_urov_1[2] >= current_settings_prt.timeout_urov_1[3]) ? current_settings_prt.timeout_urov_1[2] : current_settings_prt.timeout_urov_1[3];
          max_value = (max_value_pare1 >= max_value_pare2) ? max_value_pare1 : max_value_pare2;
          break;
        }
      case INDEX_TIMER_UROV2:
        {
          int max_value_pare1, max_value_pare2;
          max_value_pare1 =  (current_settings_prt.timeout_urov_2[0] >= current_settings_prt.timeout_urov_2[1]) ? current_settings_prt.timeout_urov_2[0] : current_settings_prt.timeout_urov_2[1];
          max_value_pare2 =  (current_settings_prt.timeout_urov_2[2] >= current_settings_prt.timeout_urov_2[3]) ? current_settings_prt.timeout_urov_2[2] : current_settings_prt.timeout_urov_2[3];
          max_value = (max_value_pare1 >= max_value_pare2) ? max_value_pare1 : max_value_pare2;
          break;
        }
      case INDEX_TIMER_APV_1:
        {
          int max_value_pare1, max_value_pare2;
          max_value_pare1 =  (current_settings_prt.timeout_apv_1[0] >= current_settings_prt.timeout_apv_1[1]) ? current_settings_prt.timeout_apv_1[0] : current_settings_prt.timeout_apv_1[1];
          max_value_pare2 =  (current_settings_prt.timeout_apv_1[2] >= current_settings_prt.timeout_apv_1[3]) ? current_settings_prt.timeout_apv_1[2] : current_settings_prt.timeout_apv_1[3];
          max_value = (max_value_pare1 >= max_value_pare2) ? max_value_pare1 : max_value_pare2;
          break;
        }
      case INDEX_TIMER_APV_2:
        {
          int max_value_pare1, max_value_pare2;
          max_value_pare1 =  (current_settings_prt.timeout_apv_2[0] >= current_settings_prt.timeout_apv_2[1]) ? current_settings_prt.timeout_apv_2[0] : current_settings_prt.timeout_apv_2[1];
          max_value_pare2 =  (current_settings_prt.timeout_apv_2[2] >= current_settings_prt.timeout_apv_2[3]) ? current_settings_prt.timeout_apv_2[2] : current_settings_prt.timeout_apv_2[3];
          max_value = (max_value_pare1 >= max_value_pare2) ? max_value_pare1 : max_value_pare2;
          break;
        }
      case INDEX_TIMER_APV_3:
        {
          int max_value_pare1, max_value_pare2;
          max_value_pare1 =  (current_settings_prt.timeout_apv_3[0] >= current_settings_prt.timeout_apv_3[1]) ? current_settings_prt.timeout_apv_3[0] : current_settings_prt.timeout_apv_3[1];
          max_value_pare2 =  (current_settings_prt.timeout_apv_3[2] >= current_settings_prt.timeout_apv_3[3]) ? current_settings_prt.timeout_apv_3[2] : current_settings_prt.timeout_apv_3[3];
          max_value = (max_value_pare1 >= max_value_pare2) ? max_value_pare1 : max_value_pare2;
          break;
        }
      case INDEX_TIMER_APV_4:
        {
          int max_value_pare1, max_value_pare2;
          max_value_pare1 =  (current_settings_prt.timeout_apv_4[0] >= current_settings_prt.timeout_apv_4[1]) ? current_settings_prt.timeout_apv_4[0] : current_settings_prt.timeout_apv_4[1];
          max_value_pare2 =  (current_settings_prt.timeout_apv_4[2] >= current_settings_prt.timeout_apv_4[3]) ? current_settings_prt.timeout_apv_4[2] : current_settings_prt.timeout_apv_4[3];
          max_value = (max_value_pare1 >= max_value_pare2) ? max_value_pare1 : max_value_pare2;
          break;
        }
      case INDEX_TIMER_APV_BLOCK_VID_APV1:
        {
          int max_value_pare1, max_value_pare2;
          max_value_pare1 =  (current_settings_prt.timeout_apv_block_vid_apv1[0] >= current_settings_prt.timeout_apv_block_vid_apv1[1]) ? current_settings_prt.timeout_apv_block_vid_apv1[0] : current_settings_prt.timeout_apv_block_vid_apv1[1];
          max_value_pare2 =  (current_settings_prt.timeout_apv_block_vid_apv1[2] >= current_settings_prt.timeout_apv_block_vid_apv1[3]) ? current_settings_prt.timeout_apv_block_vid_apv1[2] : current_settings_prt.timeout_apv_block_vid_apv1[3];
          max_value = (max_value_pare1 >= max_value_pare2) ? max_value_pare1 : max_value_pare2;
          break;
        }
      case INDEX_TIMER_APV_BLOCK_VID_APV2:
        {
          int max_value_pare1, max_value_pare2;
          max_value_pare1 =  (current_settings_prt.timeout_apv_block_vid_apv2[0] >= current_settings_prt.timeout_apv_block_vid_apv2[1]) ? current_settings_prt.timeout_apv_block_vid_apv2[0] : current_settings_prt.timeout_apv_block_vid_apv2[1];
          max_value_pare2 =  (current_settings_prt.timeout_apv_block_vid_apv2[2] >= current_settings_prt.timeout_apv_block_vid_apv2[3]) ? current_settings_prt.timeout_apv_block_vid_apv2[2] : current_settings_prt.timeout_apv_block_vid_apv2[3];
          max_value = (max_value_pare1 >= max_value_pare2) ? max_value_pare1 : max_value_pare2;
          break;
        }
      case INDEX_TIMER_APV_BLOCK_VID_APV3:
        {
          int max_value_pare1, max_value_pare2;
          max_value_pare1 =  (current_settings_prt.timeout_apv_block_vid_apv3[0] >= current_settings_prt.timeout_apv_block_vid_apv3[1]) ? current_settings_prt.timeout_apv_block_vid_apv3[0] : current_settings_prt.timeout_apv_block_vid_apv3[1];
          max_value_pare2 =  (current_settings_prt.timeout_apv_block_vid_apv3[2] >= current_settings_prt.timeout_apv_block_vid_apv3[3]) ? current_settings_prt.timeout_apv_block_vid_apv3[2] : current_settings_prt.timeout_apv_block_vid_apv3[3];
          max_value = (max_value_pare1 >= max_value_pare2) ? max_value_pare1 : max_value_pare2;
          break;
        }
      case INDEX_TIMER_APV_BLOCK_VID_APV4:
        {
          int max_value_pare1, max_value_pare2;
          max_value_pare1 =  (current_settings_prt.timeout_apv_block_vid_apv4[0] >= current_settings_prt.timeout_apv_block_vid_apv4[1]) ? current_settings_prt.timeout_apv_block_vid_apv4[0] : current_settings_prt.timeout_apv_block_vid_apv4[1];
          max_value_pare2 =  (current_settings_prt.timeout_apv_block_vid_apv4[2] >= current_settings_prt.timeout_apv_block_vid_apv4[3]) ? current_settings_prt.timeout_apv_block_vid_apv4[2] : current_settings_prt.timeout_apv_block_vid_apv4[3];
          max_value = (max_value_pare1 >= max_value_pare2) ? max_value_pare1 : max_value_pare2;
          break;
        }
      case INDEX_TIMER_APV_BLOCK_VID_VV:
        {
          int max_value_pare1, max_value_pare2;
          max_value_pare1 =  (current_settings_prt.timeout_apv_block_vid_VV[0] >= current_settings_prt.timeout_apv_block_vid_VV[1]) ? current_settings_prt.timeout_apv_block_vid_VV[0] : current_settings_prt.timeout_apv_block_vid_VV[1];
          max_value_pare2 =  (current_settings_prt.timeout_apv_block_vid_VV[2] >= current_settings_prt.timeout_apv_block_vid_VV[3]) ? current_settings_prt.timeout_apv_block_vid_VV[2] : current_settings_prt.timeout_apv_block_vid_VV[3];
          max_value = (max_value_pare1 >= max_value_pare2) ? max_value_pare1 : max_value_pare2;
          break;
        }
      case INDEX_TIMER_APV_TMP1:
        {
          max_value =  1;  /*1 ��*/
          break;
        }
      case INDEX_TIMER_ACHR_CHAPV:
        {
          max_value =  MAX_VALUE_TIMER_FOR_COUNT_SIGNAL_ACHR_CHAPV;
          break;
        }
      case INDEX_TIMER_VIDKL_VV:
        {
          max_value =  current_settings_prt.timeout_swch_off;
          break;
        }
      case INDEX_TIMER_BLK_VKL_VV:
        {
          max_value =  current_settings_prt.timeout_swch_udl_blk_on;
          break;
        }
      case INDEX_TIMER_VKL_VV:
        {
          max_value =  current_settings_prt.timeout_swch_on;
          break;
        }
      case INDEX_TIMER_PRYVOD_VV:
        {
          max_value =  current_settings_prt.timeout_pryvoda_VV;
          break;
        }
      case INDEX_TIMER_UMIN1:
        {
          int max_value_pare1, max_value_pare2;
          max_value_pare1 =  (current_settings_prt.timeout_Umin1[0] >= current_settings_prt.timeout_Umin1[1]) ? current_settings_prt.timeout_Umin1[0] : current_settings_prt.timeout_Umin1[1];
          max_value_pare2 =  (current_settings_prt.timeout_Umin1[2] >= current_settings_prt.timeout_Umin1[3]) ? current_settings_prt.timeout_Umin1[2] : current_settings_prt.timeout_Umin1[3];
          max_value = (max_value_pare1 >= max_value_pare2) ? max_value_pare1 : max_value_pare2;
          break;
        }
      case INDEX_TIMER_UMIN2:
        {
          int max_value_pare1, max_value_pare2;
          max_value_pare1 =  (current_settings_prt.timeout_Umin2[0] >= current_settings_prt.timeout_Umin2[1]) ? current_settings_prt.timeout_Umin2[0] : current_settings_prt.timeout_Umin2[1];
          max_value_pare2 =  (current_settings_prt.timeout_Umin2[2] >= current_settings_prt.timeout_Umin2[3]) ? current_settings_prt.timeout_Umin2[2] : current_settings_prt.timeout_Umin2[3];
          max_value = (max_value_pare1 >= max_value_pare2) ? max_value_pare1 : max_value_pare2;
          break;
        }
      case INDEX_TIMER_UMAX1:
        {
          int max_value_pare1, max_value_pare2;
          max_value_pare1 =  (current_settings_prt.timeout_Umax1[0] >= current_settings_prt.timeout_Umax1[1]) ? current_settings_prt.timeout_Umax1[0] : current_settings_prt.timeout_Umax1[1];
          max_value_pare2 =  (current_settings_prt.timeout_Umax1[2] >= current_settings_prt.timeout_Umax1[3]) ? current_settings_prt.timeout_Umax1[2] : current_settings_prt.timeout_Umax1[3];
          max_value = (max_value_pare1 >= max_value_pare2) ? max_value_pare1 : max_value_pare2;
          break;
        }
      case INDEX_TIMER_UMAX2:
        {
          int max_value_pare1, max_value_pare2;
          max_value_pare1 =  (current_settings_prt.timeout_Umax2[0] >= current_settings_prt.timeout_Umax2[1]) ? current_settings_prt.timeout_Umax2[0] : current_settings_prt.timeout_Umax2[1];
          max_value_pare2 =  (current_settings_prt.timeout_Umax2[2] >= current_settings_prt.timeout_Umax2[3]) ? current_settings_prt.timeout_Umax2[2] : current_settings_prt.timeout_Umax2[3];
          max_value = (max_value_pare1 >= max_value_pare2) ? max_value_pare1 : max_value_pare2;
          break;
        }
      case INDEX_TIMER_APV_ZMN1:
        {
          int max_value_pare1, max_value_pare2;
          max_value_pare1 =  (current_settings_prt.timeout_apv_zmn_1[0] >= current_settings_prt.timeout_apv_zmn_1[1]) ? current_settings_prt.timeout_apv_zmn_1[0] : current_settings_prt.timeout_apv_zmn_1[1];
          max_value_pare2 =  (current_settings_prt.timeout_apv_zmn_1[2] >= current_settings_prt.timeout_apv_zmn_1[3]) ? current_settings_prt.timeout_apv_zmn_1[2] : current_settings_prt.timeout_apv_zmn_1[3];
          max_value = (max_value_pare1 >= max_value_pare2) ? max_value_pare1 : max_value_pare2;
          break;
        }
      case INDEX_TIMER_APV_ZMN2:
        {
          int max_value_pare1, max_value_pare2;
          max_value_pare1 =  (current_settings_prt.timeout_apv_zmn_2[0] >= current_settings_prt.timeout_apv_zmn_2[1]) ? current_settings_prt.timeout_apv_zmn_2[0] : current_settings_prt.timeout_apv_zmn_2[1];
          max_value_pare2 =  (current_settings_prt.timeout_apv_zmn_2[2] >= current_settings_prt.timeout_apv_zmn_2[3]) ? current_settings_prt.timeout_apv_zmn_2[2] : current_settings_prt.timeout_apv_zmn_2[3];
          max_value = (max_value_pare1 >= max_value_pare2) ? max_value_pare1 : max_value_pare2;
          break;
        }
      case INDEX_TIMER_APV_ZMN3:
        {
          int max_value_pare1, max_value_pare2;
          max_value_pare1 =  (current_settings_prt.timeout_apv_zmn_zavershennja[0] >= current_settings_prt.timeout_apv_zmn_zavershennja[1]) ? current_settings_prt.timeout_apv_zmn_zavershennja[0] : current_settings_prt.timeout_apv_zmn_zavershennja[1];
          max_value_pare2 =  (current_settings_prt.timeout_apv_zmn_zavershennja[2] >= current_settings_prt.timeout_apv_zmn_zavershennja[3]) ? current_settings_prt.timeout_apv_zmn_zavershennja[2] : current_settings_prt.timeout_apv_zmn_zavershennja[3];
          max_value = (max_value_pare1 >= max_value_pare2) ? max_value_pare1 : max_value_pare2;
          break;
        }  
      case INDEX_TIMER_AVR_RL:
        {
          int max_value_pare1, max_value_pare2;
          max_value_pare1 =  (current_settings_prt.timeout_avr_rl[0] >= current_settings_prt.timeout_avr_rl[1]) ? current_settings_prt.timeout_avr_rl[0] : current_settings_prt.timeout_avr_rl[1];
          max_value_pare2 =  (current_settings_prt.timeout_avr_rl[2] >= current_settings_prt.timeout_avr_rl[3]) ? current_settings_prt.timeout_avr_rl[2] : current_settings_prt.timeout_avr_rl[3];
          max_value = (max_value_pare1 >= max_value_pare2) ? max_value_pare1 : max_value_pare2;
          break;
        }
      case INDEX_TIMER_AVR_OL:
        {
          int max_value_pare1, max_value_pare2;
          max_value_pare1 =  (current_settings_prt.timeout_avr_ol[0] >= current_settings_prt.timeout_avr_ol[1]) ? current_settings_prt.timeout_avr_ol[0] : current_settings_prt.timeout_avr_ol[1];
          max_value_pare2 =  (current_settings_prt.timeout_avr_ol[2] >= current_settings_prt.timeout_avr_ol[3]) ? current_settings_prt.timeout_avr_ol[2] : current_settings_prt.timeout_avr_ol[3];
          max_value = (max_value_pare1 >= max_value_pare2) ? max_value_pare1 : max_value_pare2;
          break;
        }
      case INDEX_TIMER_AVR_RESET_BLK:
        {
          int max_value_pare1, max_value_pare2;
          max_value_pare1 =  (current_settings_prt.timeout_avr_reset_blk[0] >= current_settings_prt.timeout_avr_reset_blk[1]) ? current_settings_prt.timeout_avr_reset_blk[0] : current_settings_prt.timeout_avr_reset_blk[1];
          max_value_pare2 =  (current_settings_prt.timeout_avr_reset_blk[2] >= current_settings_prt.timeout_avr_reset_blk[3]) ? current_settings_prt.timeout_avr_reset_blk[2] : current_settings_prt.timeout_avr_reset_blk[3];
          max_value = (max_value_pare1 >= max_value_pare2) ? max_value_pare1 : max_value_pare2;
          break;
        }
      case INDEX_TIMER_AVR_ZAVERSHENNJA:
        {
          int max_value_pare1, max_value_pare2;
          max_value_pare1 =  (current_settings_prt.timeout_avr_zavershennja[0] >= current_settings_prt.timeout_avr_zavershennja[1]) ? current_settings_prt.timeout_avr_zavershennja[0] : current_settings_prt.timeout_avr_zavershennja[1];
          max_value_pare2 =  (current_settings_prt.timeout_avr_zavershennja[2] >= current_settings_prt.timeout_avr_zavershennja[3]) ? current_settings_prt.timeout_avr_zavershennja[2] : current_settings_prt.timeout_avr_zavershennja[3];
          max_value = (max_value_pare1 >= max_value_pare2) ? max_value_pare1 : max_value_pare2;
          break;
        }
      case INDEX_TIMER_ACHR1:
        {
          int max_value_pare1, max_value_pare2;
          max_value_pare1 =  (current_settings_prt.timeout_achr_1[0] >= current_settings_prt.timeout_achr_1[1]) ? current_settings_prt.timeout_achr_1[0] : current_settings_prt.timeout_achr_1[1];
          max_value_pare2 =  (current_settings_prt.timeout_achr_1[2] >= current_settings_prt.timeout_achr_1[3]) ? current_settings_prt.timeout_achr_1[2] : current_settings_prt.timeout_achr_1[3];
          max_value = (max_value_pare1 >= max_value_pare2) ? max_value_pare1 : max_value_pare2;
          break;
        }
      case INDEX_TIMER_ACHR_CHAPV_100MS_1:
        {
          max_value = TIMEOUT_ACHR_CHAPV_100MS;
          break;
        }
      case INDEX_TIMER_ACHR_CHAPV_100MS_2:
        {
          max_value = TIMEOUT_ACHR_CHAPV_100MS;
          break;
        }
      case INDEX_TIMER_CHAPV_1MS:
        {
          max_value = TIMEOUT_CHAPV_1MS;
          break;
        }
      case INDEX_TIMER_BLOCK_CHAPV_5MS:
        {
          max_value = TIMEOUT_BLOCK_CHAPV_5MS;
          break;
        }
      case INDEX_TIMER_CHAPV1:
        {
          int max_value_pare1, max_value_pare2;
          max_value_pare1 =  (current_settings_prt.timeout_chapv_1[0] >= current_settings_prt.timeout_chapv_1[1]) ? current_settings_prt.timeout_chapv_1[0] : current_settings_prt.timeout_chapv_1[1];
          max_value_pare2 =  (current_settings_prt.timeout_chapv_1[2] >= current_settings_prt.timeout_chapv_1[3]) ? current_settings_prt.timeout_chapv_1[2] : current_settings_prt.timeout_chapv_1[3];
          max_value = (max_value_pare1 >= max_value_pare2) ? max_value_pare1 : max_value_pare2;
          break;
        }
      case INDEX_TIMER_ACHR2:
        {
          int max_value_pare1, max_value_pare2;
          max_value_pare1 =  (current_settings_prt.timeout_achr_2[0] >= current_settings_prt.timeout_achr_2[1]) ? current_settings_prt.timeout_achr_2[0] : current_settings_prt.timeout_achr_2[1];
          max_value_pare2 =  (current_settings_prt.timeout_achr_2[2] >= current_settings_prt.timeout_achr_2[3]) ? current_settings_prt.timeout_achr_2[2] : current_settings_prt.timeout_achr_2[3];
          max_value = (max_value_pare1 >= max_value_pare2) ? max_value_pare1 : max_value_pare2;
          break;
        }
      case INDEX_TIMER_CHAPV2:
        {
          int max_value_pare1, max_value_pare2;
          max_value_pare1 =  (current_settings_prt.timeout_chapv_2[0] >= current_settings_prt.timeout_chapv_2[1]) ? current_settings_prt.timeout_chapv_2[0] : current_settings_prt.timeout_chapv_2[1];
          max_value_pare2 =  (current_settings_prt.timeout_chapv_2[2] >= current_settings_prt.timeout_chapv_2[3]) ? current_settings_prt.timeout_chapv_2[2] : current_settings_prt.timeout_chapv_2[3];
          max_value = (max_value_pare1 >= max_value_pare2) ? max_value_pare1 : max_value_pare2;
          break;
        }
      case INDEX_TIMER_U_OL1:
      case INDEX_TIMER_U_OL2:
        {
          int max_value_pare1, max_value_pare2;
          max_value_pare1 =  (current_settings_prt.timeout_U_ol[0] >= current_settings_prt.timeout_U_ol[1]) ? current_settings_prt.timeout_U_ol[0] : current_settings_prt.timeout_U_ol[1];
          max_value_pare2 =  (current_settings_prt.timeout_U_ol[2] >= current_settings_prt.timeout_U_ol[3]) ? current_settings_prt.timeout_U_ol[2] : current_settings_prt.timeout_U_ol[3];
          max_value = (max_value_pare1 >= max_value_pare2) ? max_value_pare1 : max_value_pare2;
          break;
        }
      case INDEX_TIMER_U_RL1:
      case INDEX_TIMER_U_RL2:
        {
          int max_value_pare1, max_value_pare2;
          max_value_pare1 =  (current_settings_prt.timeout_U_rl[0] >= current_settings_prt.timeout_U_rl[1]) ? current_settings_prt.timeout_U_rl[0] : current_settings_prt.timeout_U_rl[1];
          max_value_pare2 =  (current_settings_prt.timeout_U_rl[2] >= current_settings_prt.timeout_U_rl[3]) ? current_settings_prt.timeout_U_rl[2] : current_settings_prt.timeout_U_rl[3];
          max_value = (max_value_pare1 >= max_value_pare2) ? max_value_pare1 : max_value_pare2;
          break;
        }
      default:
        break;
      }

      //���������� �� ����� ���������� �������� �������, ���� �� �� �� �������� ����� ���������
      if (global_timers[i] < max_value) global_timers[i] += DELTA_TIME_FOR_TIMERS;
    }
  }
      
}
/*****************************************************/

/*****************************************************/
//����������� ������������� ������� - �� ����������� ���� ������������� ����� ��� �������
/*****************************************************/
inline void df_handler(unsigned int *activated_functions, unsigned int *previous_stats_signals)
{
  /*
  ������� ��������� ������� � source_activation_df
  ������� ����� ��� �������� ������� � maska_active_df
  */
  unsigned int source_activation_df = 0, maska_active_df[N_BIG] = {0, 0, 0, 0, 0, 0};
  for (unsigned int i = 0; i < NUMBER_DEFINED_FUNCTIONS; i++)
  {
    unsigned int number_byte_in, number_bit_in, number_byte_out, number_bit_out;
    switch (i)
    {
    case 0:
      {
        number_byte_in = RANG_OUTPUT_LED_DF_REG_DF1_IN >> 5;
        number_bit_in = RANG_OUTPUT_LED_DF_REG_DF1_IN & 0x1f;

        number_byte_out = RANG_OUTPUT_LED_DF_REG_DF1_OUT >> 5;
        number_bit_out = RANG_OUTPUT_LED_DF_REG_DF1_OUT & 0x1f;
        
        break;
      }
    case 1:
      {
        number_byte_in = RANG_OUTPUT_LED_DF_REG_DF2_IN >> 5;
        number_bit_in = RANG_OUTPUT_LED_DF_REG_DF2_IN & 0x1f;

        number_byte_out = RANG_OUTPUT_LED_DF_REG_DF2_OUT >> 5;
        number_bit_out = RANG_OUTPUT_LED_DF_REG_DF2_OUT & 0x1f;
        
        break;
      }
    case 2:
      {
        number_byte_in = RANG_OUTPUT_LED_DF_REG_DF3_IN >> 5;
        number_bit_in = RANG_OUTPUT_LED_DF_REG_DF3_IN & 0x1f;

        number_byte_out = RANG_OUTPUT_LED_DF_REG_DF3_OUT >> 5;
        number_bit_out = RANG_OUTPUT_LED_DF_REG_DF3_OUT & 0x1f;
        
        break;
      }
    case 3:
      {
        number_byte_in = RANG_OUTPUT_LED_DF_REG_DF4_IN >> 5;
        number_bit_in = RANG_OUTPUT_LED_DF_REG_DF4_IN & 0x1f;

        number_byte_out = RANG_OUTPUT_LED_DF_REG_DF4_OUT >> 5;
        number_bit_out = RANG_OUTPUT_LED_DF_REG_DF4_OUT & 0x1f;
        
        break;
      }
    case 4:
      {
        number_byte_in = RANG_OUTPUT_LED_DF_REG_DF5_IN >> 5;
        number_bit_in = RANG_OUTPUT_LED_DF_REG_DF5_IN & 0x1f;

        number_byte_out = RANG_OUTPUT_LED_DF_REG_DF5_OUT >> 5;
        number_bit_out = RANG_OUTPUT_LED_DF_REG_DF5_OUT & 0x1f;
        
        break;
      }
    case 5:
      {
        number_byte_in = RANG_OUTPUT_LED_DF_REG_DF6_IN >> 5;
        number_bit_in = RANG_OUTPUT_LED_DF_REG_DF6_IN & 0x1f;

        number_byte_out = RANG_OUTPUT_LED_DF_REG_DF6_OUT >> 5;
        number_bit_out = RANG_OUTPUT_LED_DF_REG_DF6_OUT & 0x1f;
        
        break;
      }
    case 6:
      {
        number_byte_in = RANG_OUTPUT_LED_DF_REG_DF7_IN >> 5;
        number_bit_in = RANG_OUTPUT_LED_DF_REG_DF7_IN & 0x1f;

        number_byte_out = RANG_OUTPUT_LED_DF_REG_DF7_OUT >> 5;
        number_bit_out = RANG_OUTPUT_LED_DF_REG_DF7_OUT & 0x1f;
        
        break;
      }
    case 7:
      {
        number_byte_in = RANG_OUTPUT_LED_DF_REG_DF8_IN >> 5;
        number_bit_in = RANG_OUTPUT_LED_DF_REG_DF8_IN & 0x1f;

        number_byte_out = RANG_OUTPUT_LED_DF_REG_DF8_OUT >> 5;
        number_bit_out = RANG_OUTPUT_LED_DF_REG_DF8_OUT & 0x1f;
        
        break;
      }
    default:
      {
        //���������� ����� ����� �� ���� � ����
        total_error_sw_fixed(43);
        break;
      }
    }

    /***
    ������� ��������� ��-��
    ***/
    source_activation_df |= ((activated_functions[number_byte_in] & (1 << number_bit_in) ) >> number_bit_in ) << i;
    //���������� ��, �� �� ��� ���������� �������� ������� �� ����� ������-����������� (��� ��������� ����� ������ ��� ���������)
    if (global_timers[INDEX_TIMER_DF_PROLONG_SET_FOR_BUTTON_INTERFACE_START + i] >= 0)
    {
      //������ ���������, ��� ��� ���������
      //���� ������� ����� ������� ������, �� ��������� ���������� ����� ������, ��� ���������
      //���� ��� ������������ ������ ������ ����� �� ���� ������ ����� ������� �����������, �� ������� ��������� �������
      source_activation_df |= (1 << i);
      
      //³������, ������� ��������� ����������� � ��������� ���� � ����� ���������� �������
      activated_functions[number_byte_in] |= (1 << number_bit_in);
      
      //� �������, ���� ������ ����� �� ����� ������������ ��������, �� ������� ������ ����� �������
      if (global_timers[INDEX_TIMER_DF_PROLONG_SET_FOR_BUTTON_INTERFACE_START + i] >= ((int)current_settings_prt.timeout_pause_df[i]))
        global_timers[INDEX_TIMER_DF_PROLONG_SET_FOR_BUTTON_INTERFACE_START + i] = -1;
    }
    /***/

    /***
    ���������� ����� �� ����� ���� �������� ��-��
    ***/
    maska_active_df[number_byte_out] |= ((state_df & (1 << i)) >> i) << number_bit_out;
    /***/
  }
  
  //���������, �� ������������� ���������� ������� ����� ��� �������� �������-�������
  unsigned int source_blk_df = 0;
  for (unsigned int i = 0; i < NUMBER_DEFINED_FUNCTIONS; i++)
  {
    if (
        (current_settings_prt.ranguvannja_df_source_plus[N_BIG*i    ] !=0) || 
        (current_settings_prt.ranguvannja_df_source_plus[N_BIG*i + 1] !=0) ||
        (current_settings_prt.ranguvannja_df_source_plus[N_BIG*i + 2] !=0) ||
        (current_settings_prt.ranguvannja_df_source_plus[N_BIG*i + 3] !=0) ||
        (current_settings_prt.ranguvannja_df_source_plus[N_BIG*i + 4] !=0) ||
        (current_settings_prt.ranguvannja_df_source_plus[N_BIG*i + 5] !=0)
       )
    {
      //�������, ���� ������� ��������� �� ������� ������ �������
      if(
         ( ( current_settings_prt.ranguvannja_df_source_plus[N_BIG*i    ] & (activated_functions[0] | previous_stats_signals[0] | maska_active_df[0]) ) != 0) ||
         ( ( current_settings_prt.ranguvannja_df_source_plus[N_BIG*i + 1] & (activated_functions[1] | previous_stats_signals[1] | maska_active_df[1]) ) != 0) ||
         ( ( current_settings_prt.ranguvannja_df_source_plus[N_BIG*i + 2] & (activated_functions[2] | previous_stats_signals[2] | maska_active_df[2]) ) != 0) ||
         ( ( current_settings_prt.ranguvannja_df_source_plus[N_BIG*i + 3] & (activated_functions[3] | previous_stats_signals[3] | maska_active_df[3]) ) != 0) ||
         ( ( current_settings_prt.ranguvannja_df_source_plus[N_BIG*i + 4] & (activated_functions[4] | previous_stats_signals[4] | maska_active_df[4]) ) != 0) ||
         ( ( current_settings_prt.ranguvannja_df_source_plus[N_BIG*i + 5] & (activated_functions[5] | previous_stats_signals[5] | maska_active_df[5]) ) != 0) 
        )
      {
        source_activation_df |= (1 << i);
      }
    }

    if (
        (current_settings_prt.ranguvannja_df_source_minus[N_BIG*i    ] !=0) || 
        (current_settings_prt.ranguvannja_df_source_minus[N_BIG*i + 1] !=0) ||
        (current_settings_prt.ranguvannja_df_source_minus[N_BIG*i + 2] !=0) ||
        (current_settings_prt.ranguvannja_df_source_minus[N_BIG*i + 3] !=0) ||
        (current_settings_prt.ranguvannja_df_source_minus[N_BIG*i + 4] !=0) ||
        (current_settings_prt.ranguvannja_df_source_minus[N_BIG*i + 5] !=0)
       )
    {
      //�������, ���� ������� ��������� �� ������� ��������� �������
      if(
         ( ( current_settings_prt.ranguvannja_df_source_minus[N_BIG*i    ] & ((unsigned int)(~(activated_functions[0] | previous_stats_signals[0] | maska_active_df[0]))) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_df_source_minus[N_BIG*i + 1] & ((unsigned int)(~(activated_functions[1] | previous_stats_signals[1] | maska_active_df[1]))) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_df_source_minus[N_BIG*i + 2] & ((unsigned int)(~(activated_functions[2] | previous_stats_signals[2] | maska_active_df[2]))) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_df_source_minus[N_BIG*i + 3] & ((unsigned int)(~(activated_functions[3] | previous_stats_signals[3] | maska_active_df[3]))) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_df_source_minus[N_BIG*i + 4] & ((unsigned int)(~(activated_functions[4] | previous_stats_signals[4] | maska_active_df[4]))) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_df_source_minus[N_BIG*i + 5] & ((unsigned int)(~(activated_functions[5] | previous_stats_signals[5] | maska_active_df[5]))) ) != 0 )
        )
      {
        source_activation_df |= (1<< i);
      }
    }

    if (
        (current_settings_prt.ranguvannja_df_source_blk[N_BIG*i    ] !=0) || 
        (current_settings_prt.ranguvannja_df_source_blk[N_BIG*i + 1] !=0) ||
        (current_settings_prt.ranguvannja_df_source_blk[N_BIG*i + 2] !=0) ||
        (current_settings_prt.ranguvannja_df_source_blk[N_BIG*i + 3] !=0) ||
        (current_settings_prt.ranguvannja_df_source_blk[N_BIG*i + 4] !=0) ||
        (current_settings_prt.ranguvannja_df_source_blk[N_BIG*i + 5] !=0)
       )
    {
      //�������, ���� ������� ��������� �������� �� ������� ����������
      if(
         ( ( current_settings_prt.ranguvannja_df_source_blk[N_BIG*i    ] & (activated_functions[0] | previous_stats_signals[0] | maska_active_df[0]) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_df_source_blk[N_BIG*i + 1] & (activated_functions[1] | previous_stats_signals[1] | maska_active_df[1]) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_df_source_blk[N_BIG*i + 2] & (activated_functions[2] | previous_stats_signals[2] | maska_active_df[2]) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_df_source_blk[N_BIG*i + 3] & (activated_functions[3] | previous_stats_signals[3] | maska_active_df[3]) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_df_source_blk[N_BIG*i + 4] & (activated_functions[4] | previous_stats_signals[4] | maska_active_df[4]) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_df_source_blk[N_BIG*i + 5] & (activated_functions[5] | previous_stats_signals[5] | maska_active_df[5]) ) != 0 )
        )
      {
        source_blk_df |= (1<< i);
      }
    }
    
    //��������� � ������ ������� ���� ������ ����������� �������
    switch (etap_execution_df[i])
    {
    case NONE_DF:
      {
        if ((source_activation_df & (1<<i)) != 0)
        {
           if (current_settings_prt.timeout_pause_df[i] > 0)
           {
             //�������, ���� � ����� ���������� ��, ����� ��������� ������ �����
             //��������� ������������� ������� �����
             global_timers[INDEX_TIMER_DF_PAUSE_START + i] = 0;
             //������� ���� ��������� ������ ����� �� ���������� ���������� ���� �����
             etap_execution_df[i] = START_TIMER_PAUSE_DF;
           }
           else
           {
             //�������, ���� ������ ����� ����� ����, ����� ����� ����� ������������ �� � ��������� ������ ������

             if (
                 (current_settings_prt.timeout_work_df[i] > 0) ||
                 ((current_settings_prt.type_df & (1<<i)) != 0)
                )   
             {
               //������������ ���� ���� �� � "��������"
               state_df |= (1 << i);
               //��������� ������������� ������� ������
               global_timers[INDEX_TIMER_DF_WORK_START + i] = 0;
               //���������� �� ������������� ������� ������ - �������� ����� ���� �� ����������� ���������� (���� ���� ����� ����������)
               etap_execution_df[i] = EXECUTION_DF;
             }
             else etap_execution_df[i] = WAITING_DEACTIVATION_SOURCE_DF;
           }
        }
        break;
      }
    case START_TIMER_PAUSE_DF:
      {
        //����� ��� ���� ���� ������� �����
        //����������, �� �� �� ��������� � ���� ��������� ����� ��� �������
        if ((source_activation_df & (1<< i)) != 0)
        {
          //����������, �� ����������� ������ ������� �����
          if (global_timers[INDEX_TIMER_DF_PAUSE_START + i] >= ((int)current_settings_prt.timeout_pause_df[i]))
          {
            //���������� ��� ������ ������� �����
            global_timers[INDEX_TIMER_DF_PAUSE_START + i] = -1;
  
            if (
                (current_settings_prt.timeout_work_df[i] > 0) ||
                ((current_settings_prt.type_df & (1<<i)) != 0)
               )   
            {
              //������������ ���� ���� �� � "��������"
              state_df |= (1 << i);
              //��������� ������������� ������� ������
              global_timers[INDEX_TIMER_DF_WORK_START + i] = 0;
              //���������� �� ������������� ������� ������ - �������� ����� ���� �� ����������� ���������� (���� ���� ����� ����������)
              etap_execution_df[i] = EXECUTION_DF;
            }
            else etap_execution_df[i] = WAITING_DEACTIVATION_SOURCE_DF;
          }
        }
        else
        {
          //��������� ����� �� ���������� ������ ������� �����, ���� ������� ��� ������ �� ���� ������������ �������
          global_timers[INDEX_TIMER_DF_PAUSE_START + i] = -1;
          etap_execution_df[i] = NONE_DF;
        }
        break;
      }
    case EXECUTION_DF:
      {
        //�������� ������ ���� �� �������� �� ���� ��
        if ((current_settings_prt.type_df & (1<<i)) != 0)
        {
          //���� �� ��������
          //����� ������ ����� �������� �� ������ ������ �� ����������� ���� ����������� �������
          if ((source_activation_df & (1<< i)) != 0)
          {
            //������� �� � �������, � ���� ������ ������ �������� � ��������� �������
            global_timers[INDEX_TIMER_DF_WORK_START + i] = 0;
          }
        }

        //����������, �� ����������� ������ ������� ������
        /*
        ������ ����������� ��������� �� � ������� ���� �� �������� � ������� � ��������
        �������� �� ��� ������� ��� � ���� ��������� ���������, ��� � ���� �����, ����
        ������� � ��������� � ������� �������, �� ��� ���� ����� ������ ������ � 0, 
        ����� �� ���� ����������� � 0, ��� ���� ������� "������ ������" ��� ���� ������� ���� 0,
        �� �� ������ ������ ������� ������ ������� ���� ����������, �� �� ���������.
        ���� ��� �� � �������� ��������, �� �� �� ���� �������������� ����� ���� ������ ������
        �������� ���� ������� � ������� ���� � �� � ���������� � ������� � ��������
        */
        if (
            (global_timers[INDEX_TIMER_DF_WORK_START + i] >= ((int)current_settings_prt.timeout_work_df[i])) &&
            (
             !( 
               ((current_settings_prt.type_df & (1 << i)) != 0) && 
               ((source_activation_df         & (1 << i)) != 0) 
              )
            )  
           )
        {
          //���������� ��� ������ ������� ������
          global_timers[INDEX_TIMER_DF_WORK_START + i] = -1;
          //���������� �� � �������� ����
          state_df &= ~(1 << i);
          
          //����������, �� ��� ����� ������� � ���������� ����������� ������� ��, �� ������� � ��������� ����
          if ((source_activation_df & (1<< i)) == 0)
          {
            //���������� � ����� ��������� ����
            etap_execution_df[i] = NONE_DF;
          }
          else 
          {
            //���� ������� ������� ���� �� �� �������, �� ���������� �� ���������� ���� ����������
            etap_execution_df[i] = WAITING_DEACTIVATION_SOURCE_DF;
          }
        }
        break;
      }
    case WAITING_DEACTIVATION_SOURCE_DF:
      {
        //� ����� ����� �� ���������� ����, ���� ������� ��������� �� �� ���� �����
        if ((source_activation_df & (1 << i)) == 0)
        {
          //���������� � ����� ��������� ����
          etap_execution_df[i] = NONE_DF;
        }
        break;
      }
    default: break;
    }
  }

  //������������, ��� ������� �� � ����� �������, �� ����� ������ ��������������
  /*
  ��� ���� � ��������� �� ��'���� � ����, � ������� �������, �� � ������� �� �������������
  ����� activated_functions � ����� �� �� ���������� ������ ��-��, ���� �� ���� ��-��
  ������ ���� �������� ���������, ��� �������� ��������� ���� ���� �������� �������� ��, � �� ��,
  �� ����� ��������������. � �������� � ������� ����� �� ������������ �������� � �����
  activated_functions, �� ��������� ����� ����� ����, �� ��� �� ������ ��'������� ������������ ��������
  � ����������� �� ����� ���'����� (���� ������ ������ � ����� � ������ ���������/�����������)
  */
  for (unsigned int i = 0; i < NUMBER_DEFINED_FUNCTIONS; i++)
  {
    //������������, ��� ������� ��
    unsigned int index_df;
    switch (i)
    {
    case 0:
      {
       index_df = RANG_OUTPUT_LED_DF_REG_DF1_OUT;
        break;
      }
    case 1:
      {
        index_df = RANG_OUTPUT_LED_DF_REG_DF2_OUT;
        break;
      }
    case 2:
      {
        index_df = RANG_OUTPUT_LED_DF_REG_DF3_OUT;
        break;
      }
    case 3:
      {
        index_df = RANG_OUTPUT_LED_DF_REG_DF4_OUT;
        break;
      }
    case 4:
      {
        index_df = RANG_OUTPUT_LED_DF_REG_DF5_OUT;
        break;
      }
    case 5:
      {
        index_df = RANG_OUTPUT_LED_DF_REG_DF6_OUT;
        break;
      }
    case 6:
      {
        index_df = RANG_OUTPUT_LED_DF_REG_DF7_OUT;
        break;
      }
    case 7:
      {
        index_df = RANG_OUTPUT_LED_DF_REG_DF8_OUT;
        break;
      }
    default:
      {
        //���������� ����� ����� �� ���� � ����
        total_error_sw_fixed(44);
        break;
      }
    }
      
    if ((state_df & (1 << i)) != 0 )
    {
      /*
      �� ������� ����� � ��������
      ��� ����� ���, �� ��������� �������� ���� ���� ������� �� ����� ������ ���� - 
      ����������, �� �� ��� ���������� �� 
      */     
      if ((source_blk_df & (1<< i)) == 0 ) _SET_BIT(activated_functions, index_df);
      else _CLEAR_BIT(activated_functions, index_df);
    }
    else
    {
      _CLEAR_BIT(activated_functions, index_df);
    }
  }
}
/*****************************************************/

/*****************************************************/
//����������� ������������� ������ - �� ����������� ���� ������������� �������������� �������
/*****************************************************/
inline void dt_handler(unsigned int *activated_functions, unsigned int *previous_stats_signals)
{
  /*
  ��������� ���� ������������ ������ ������� � state_defined_triggers
  ������� ������������ ������� � source_set_dt
  ������� �������� ������� � source_reset_dt
  ������� ����� ��� �������� ������� � maska_active_dt
  */
  unsigned int state_defined_triggers = 0, source_set_dt = 0, source_reset_dt = 0, maska_active_dt[N_BIG];
  for (unsigned int i = 0; i < NUMBER_DEFINED_TRIGGERS; i++)
  {
    unsigned int number_byte_set, number_bit_set, number_byte_reset, number_bit_reset;
    unsigned int index_dt;
    switch (i)
    {
    case 0:
      {
        number_byte_set = RANG_OUTPUT_LED_DF_REG_DT1_SET >> 5;
        number_bit_set = RANG_OUTPUT_LED_DF_REG_DT1_SET & 0x1f;

        number_byte_reset = RANG_OUTPUT_LED_DF_REG_DT1_RESET >> 5;
        number_bit_reset = RANG_OUTPUT_LED_DF_REG_DT1_RESET & 0x1f;
        
        index_dt = RANG_OUTPUT_LED_DF_REG_DT1_OUT;
        
        break;
      }
    case 1:
      {
        number_byte_set = RANG_OUTPUT_LED_DF_REG_DT2_SET >> 5;
        number_bit_set = RANG_OUTPUT_LED_DF_REG_DT2_SET & 0x1f;

        number_byte_reset = RANG_OUTPUT_LED_DF_REG_DT2_RESET >> 5;
        number_bit_reset = RANG_OUTPUT_LED_DF_REG_DT2_RESET & 0x1f;
        
        index_dt = RANG_OUTPUT_LED_DF_REG_DT2_OUT;
        
        break;
      }
    case 2:
      {
        number_byte_set = RANG_OUTPUT_LED_DF_REG_DT3_SET >> 5;
        number_bit_set = RANG_OUTPUT_LED_DF_REG_DT3_SET & 0x1f;

        number_byte_reset = RANG_OUTPUT_LED_DF_REG_DT3_RESET >> 5;
        number_bit_reset = RANG_OUTPUT_LED_DF_REG_DT3_RESET & 0x1f;
        
        index_dt = RANG_OUTPUT_LED_DF_REG_DT3_OUT;
        
        break;
      }
    case 3:
      {
        number_byte_set = RANG_OUTPUT_LED_DF_REG_DT4_SET >> 5;
        number_bit_set = RANG_OUTPUT_LED_DF_REG_DT4_SET & 0x1f;

        number_byte_reset = RANG_OUTPUT_LED_DF_REG_DT4_RESET >> 5;
        number_bit_reset = RANG_OUTPUT_LED_DF_REG_DT4_RESET & 0x1f;
        
        index_dt = RANG_OUTPUT_LED_DF_REG_DT4_OUT;
        
        break;
      }
    default:
      {
        //���������� ����� ����� �� ���� � ����
        total_error_sw_fixed(55);
        break;
      }
    }

    state_defined_triggers |= ( (active_functions[index_dt >> 5] & ( 1 << (index_dt & 0x1f) ) ) >> (index_dt & 0x1f) ) << i;
    /***
    ������� ������������ � �������� ��
    ***/
    source_set_dt   |= ((activated_functions[number_byte_set  ] & (1 << number_bit_set  ) ) >> number_bit_set   ) << i;
    source_reset_dt |= ((activated_functions[number_byte_reset] & (1 << number_bit_reset) ) >> number_bit_reset ) << i;
    /***/
  }
  maska_active_dt[0] = active_functions[0] & MASKA_FOR_DF_TRIGGERS_SIGNALS_0;
  maska_active_dt[1] = active_functions[1] & MASKA_FOR_DF_TRIGGERS_SIGNALS_1;
  maska_active_dt[2] = active_functions[2] & MASKA_FOR_DF_TRIGGERS_SIGNALS_2;
  maska_active_dt[3] = active_functions[3] & MASKA_FOR_DF_TRIGGERS_SIGNALS_3;
  maska_active_dt[4] = active_functions[4] & MASKA_FOR_DF_TRIGGERS_SIGNALS_4;
  maska_active_dt[5] = active_functions[5] & MASKA_FOR_DF_TRIGGERS_SIGNALS_5;
  
  //���������, �� ��������������/���������� ���������� ������ ����� ��� �������� �������-�������
  for (unsigned int i = 0; i < NUMBER_DEFINED_TRIGGERS; i++)
  {
    if (
        (current_settings_prt.ranguvannja_set_dt_source_plus[N_BIG*i    ] !=0) || 
        (current_settings_prt.ranguvannja_set_dt_source_plus[N_BIG*i + 1] !=0) ||
        (current_settings_prt.ranguvannja_set_dt_source_plus[N_BIG*i + 2] !=0) ||
        (current_settings_prt.ranguvannja_set_dt_source_plus[N_BIG*i + 3] !=0) ||
        (current_settings_prt.ranguvannja_set_dt_source_plus[N_BIG*i + 4] !=0) ||
        (current_settings_prt.ranguvannja_set_dt_source_plus[N_BIG*i + 5] !=0)
       )
    {
      //�������, ���� ������� ��������� �� ������� ������ �������
      if(
         (( current_settings_prt.ranguvannja_set_dt_source_plus[N_BIG*i    ] & (activated_functions[0] | previous_stats_signals[0] | maska_active_dt[0])) != 0) ||
         (( current_settings_prt.ranguvannja_set_dt_source_plus[N_BIG*i + 1] & (activated_functions[1] | previous_stats_signals[1] | maska_active_dt[1])) != 0) ||
         (( current_settings_prt.ranguvannja_set_dt_source_plus[N_BIG*i + 2] & (activated_functions[2] | previous_stats_signals[2] | maska_active_dt[2])) != 0) ||
         (( current_settings_prt.ranguvannja_set_dt_source_plus[N_BIG*i + 3] & (activated_functions[3] | previous_stats_signals[3] | maska_active_dt[3])) != 0) ||
         (( current_settings_prt.ranguvannja_set_dt_source_plus[N_BIG*i + 4] & (activated_functions[4] | previous_stats_signals[4] | maska_active_dt[4])) != 0) ||
         (( current_settings_prt.ranguvannja_set_dt_source_plus[N_BIG*i + 5] & (activated_functions[5] | previous_stats_signals[5] | maska_active_dt[5])) != 0)
        )
      {
        source_set_dt |= (1 << i);
      }
    }

    if (
        (current_settings_prt.ranguvannja_set_dt_source_minus[N_BIG*i    ] !=0) || 
        (current_settings_prt.ranguvannja_set_dt_source_minus[N_BIG*i + 1] !=0) ||
        (current_settings_prt.ranguvannja_set_dt_source_minus[N_BIG*i + 2] !=0) ||
        (current_settings_prt.ranguvannja_set_dt_source_minus[N_BIG*i + 3] !=0) ||
        (current_settings_prt.ranguvannja_set_dt_source_minus[N_BIG*i + 4] !=0) ||
        (current_settings_prt.ranguvannja_set_dt_source_minus[N_BIG*i + 5] !=0)
       )
    {
      //�������, ���� ������� ��������� �� ������� ��������� �������
      if(
         ( ( current_settings_prt.ranguvannja_set_dt_source_minus[N_BIG*i    ] & ((unsigned int)(~(activated_functions[0] | previous_stats_signals[0] | maska_active_dt[0]))) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_set_dt_source_minus[N_BIG*i + 1] & ((unsigned int)(~(activated_functions[1] | previous_stats_signals[1] | maska_active_dt[1]))) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_set_dt_source_minus[N_BIG*i + 2] & ((unsigned int)(~(activated_functions[2] | previous_stats_signals[2] | maska_active_dt[2]))) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_set_dt_source_minus[N_BIG*i + 3] & ((unsigned int)(~(activated_functions[3] | previous_stats_signals[3] | maska_active_dt[3]))) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_set_dt_source_minus[N_BIG*i + 4] & ((unsigned int)(~(activated_functions[4] | previous_stats_signals[4] | maska_active_dt[4]))) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_set_dt_source_minus[N_BIG*i + 5] & ((unsigned int)(~(activated_functions[5] | previous_stats_signals[5] | maska_active_dt[5]))) ) != 0 )
        )
      {
        source_set_dt |= (1<< i);
      }
    }

    if (
        (current_settings_prt.ranguvannja_reset_dt_source_plus[N_BIG*i    ] !=0) || 
        (current_settings_prt.ranguvannja_reset_dt_source_plus[N_BIG*i + 1] !=0) ||
        (current_settings_prt.ranguvannja_reset_dt_source_plus[N_BIG*i + 2] !=0) ||
        (current_settings_prt.ranguvannja_reset_dt_source_plus[N_BIG*i + 3] !=0) ||
        (current_settings_prt.ranguvannja_reset_dt_source_plus[N_BIG*i + 4] !=0) ||
        (current_settings_prt.ranguvannja_reset_dt_source_plus[N_BIG*i + 5] !=0)
       )
    {
      //�������, ���� ������� ��������� �� ������� ������ �������
      if(
         (( current_settings_prt.ranguvannja_reset_dt_source_plus[N_BIG*i    ] & (activated_functions[0] | previous_stats_signals[0] | maska_active_dt[0])) != 0) ||
         (( current_settings_prt.ranguvannja_reset_dt_source_plus[N_BIG*i + 1] & (activated_functions[1] | previous_stats_signals[1] | maska_active_dt[1])) != 0) ||
         (( current_settings_prt.ranguvannja_reset_dt_source_plus[N_BIG*i + 2] & (activated_functions[2] | previous_stats_signals[2] | maska_active_dt[2])) != 0) ||
         (( current_settings_prt.ranguvannja_reset_dt_source_plus[N_BIG*i + 3] & (activated_functions[3] | previous_stats_signals[3] | maska_active_dt[3])) != 0) ||
         (( current_settings_prt.ranguvannja_reset_dt_source_plus[N_BIG*i + 4] & (activated_functions[4] | previous_stats_signals[4] | maska_active_dt[4])) != 0) ||
         (( current_settings_prt.ranguvannja_reset_dt_source_plus[N_BIG*i + 5] & (activated_functions[5] | previous_stats_signals[5] | maska_active_dt[5])) != 0)
        )
      {
        source_reset_dt |= (1 << i);
      }
    }

    if (
        (current_settings_prt.ranguvannja_reset_dt_source_minus[N_BIG*i    ] !=0) || 
        (current_settings_prt.ranguvannja_reset_dt_source_minus[N_BIG*i + 1] !=0) ||
        (current_settings_prt.ranguvannja_reset_dt_source_minus[N_BIG*i + 2] !=0) ||
        (current_settings_prt.ranguvannja_reset_dt_source_minus[N_BIG*i + 3] !=0) ||
        (current_settings_prt.ranguvannja_reset_dt_source_minus[N_BIG*i + 4] !=0) ||
        (current_settings_prt.ranguvannja_reset_dt_source_minus[N_BIG*i + 5] !=0)
       )
    {
      //�������, ���� ������� ��������� �� ������� ��������� �������
      if(
         ( ( current_settings_prt.ranguvannja_reset_dt_source_minus[N_BIG*i    ] & ((unsigned int)(~(activated_functions[0] | previous_stats_signals[0] | maska_active_dt[0]))) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_reset_dt_source_minus[N_BIG*i + 1] & ((unsigned int)(~(activated_functions[1] | previous_stats_signals[1] | maska_active_dt[1]))) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_reset_dt_source_minus[N_BIG*i + 2] & ((unsigned int)(~(activated_functions[2] | previous_stats_signals[2] | maska_active_dt[2]))) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_reset_dt_source_minus[N_BIG*i + 3] & ((unsigned int)(~(activated_functions[3] | previous_stats_signals[3] | maska_active_dt[3]))) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_reset_dt_source_minus[N_BIG*i + 4] & ((unsigned int)(~(activated_functions[4] | previous_stats_signals[4] | maska_active_dt[4]))) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_reset_dt_source_minus[N_BIG*i + 5] & ((unsigned int)(~(activated_functions[5] | previous_stats_signals[5] | maska_active_dt[5]))) ) != 0 )
        )
      {
        source_reset_dt |= (1<< i);
      }
    }

    //��������� � ������ ������� ����� ������ ������������� ������ (������������ �� ��������)
    if ((source_set_dt   & (1 << i)) != 0) state_defined_triggers |= (1 << i);
    if ((source_reset_dt & (1 << i)) != 0) state_defined_triggers &= (unsigned int)(~(1 << i));
  }

  //������������, ��� ������� �� � ����� �������, �� ����� ������ ��������������
  /*
  ��� ���� � ��������� �� ��'���� � ����, � ������� �������, �� � ������� �� �������������
  ����� activated_functions � ����� �� �� ���������� ������ ��-��, ���� �� ���� ��-��
  ������ ���� �������� ������������/��������, ��� �������� ������������/�������� ���� ���� �������� �������� ��, � �� ��,
  �� ����� ��������������. � �������� � ������� ����� �� ������������ �������� � �����
  activated_functions, �� ��������� ����� ����� ����, �� ��� �� ������ ��'������� ������������ ��������
  � ����������� �� ����� ���'����� (���� ������ ������ � ����� � ������ ������������/��������)
  */
  for (unsigned int i = 0; i < NUMBER_DEFINED_TRIGGERS; i++)
  {
    //������������, ��� ������� ��
    unsigned int index_dt;
    switch (i)
    {
    case 0:
      {
       index_dt = RANG_OUTPUT_LED_DF_REG_DT1_OUT;
        break;
      }
    case 1:
      {
       index_dt = RANG_OUTPUT_LED_DF_REG_DT2_OUT;
        break;
      }
    case 2:
      {
       index_dt = RANG_OUTPUT_LED_DF_REG_DT3_OUT;
        break;
      }
    case 3:
      {
       index_dt = RANG_OUTPUT_LED_DF_REG_DT4_OUT;
        break;
      }
    default:
      {
        //���������� ����� ����� �� ���� � ����
        total_error_sw_fixed(56);
        break;
      }
    }
      
    if ((state_defined_triggers & (1 << i)) != 0 ) _SET_BIT(activated_functions, index_dt);
    else _CLEAR_BIT(activated_functions, index_dt);
  }
}
/*****************************************************/

/*****************************************************/
//������������� ������ ��������  ��� ������� ���2 (����������� �������)
/*
-------------------------------------------------
�(c) = K*T�/( ((I/I�)^alpha) - 1 )
-------------------------------------------------
*/
/*****************************************************/
inline int timeout_dependent_general(unsigned int i, unsigned int number_group_stp)
{
  int timeout_result = 0;
  int type_mtz2_tmp = current_settings_prt.type_mtz2;
  
  if (
      (type_mtz2_tmp >= TYPE_MTZ_DEPENDENT_A) &&
      (type_mtz2_tmp <= TYPE_MTZ_DEPENDENT_RTV_I)
     )   
  {
    unsigned int Iust = current_settings_prt.setpoint_mtz_2[number_group_stp];
    if (i > Iust)
    {
      register float timeout = (((float)current_settings_prt.timeout_mtz_2[number_group_stp])/1000.0f);
      register float timeout_dependent = 0;
      
      if (
          (type_mtz2_tmp >= TYPE_MTZ_DEPENDENT_A) &&
          (type_mtz2_tmp <= TYPE_MTZ_DEPENDENT_C)
         )   
      {
        register float K;
        register float alpha;

        switch (type_mtz2_tmp)
        {
          case TYPE_MTZ_DEPENDENT_A:
          {
            K = 0.14f;
            alpha = 0.02f;
            break;
          }
        case TYPE_MTZ_DEPENDENT_B:
          {
            K = 13.5f;
            alpha = 1.0f;
            break;
          }
        case TYPE_MTZ_DEPENDENT_C:
          {
            K = 80.0f;
            alpha = 2.0f;
            break;
          }
        default:
          {
            //���������� ����� ����� �� ���� � ����
            total_error_sw_fixed(42);
          }
        }
    
        register float I_div_Iusy = ((float)i)/((float)Iust);
        register float rising_to_power = powf(I_div_Iusy, alpha);
        if (
            (isnan(rising_to_power) != 0) || 
            (isinf(rising_to_power) != 0) ||
            (rising_to_power <= 1)
          )
        {
          //���������� ����� ����� �� ���� � ����
          total_error_sw_fixed(57);
        }
  
        timeout_dependent = K*timeout/(rising_to_power - 1);
      }
      else if (
               (type_mtz2_tmp >= TYPE_MTZ_DEPENDENT_RT_80) &&
               (type_mtz2_tmp <= TYPE_MTZ_DEPENDENT_RTV_I)
              )   
      {
        register float I_div_Iusy = ((float)i)/((float)Iust);
        I_div_Iusy = I_div_Iusy - 1.0f;

        register float K;
        register float alpha;

        switch (type_mtz2_tmp)
        {
        case TYPE_MTZ_DEPENDENT_RT_80:
          {
            K = 20.0f;
            alpha = 1.8f;
          
            I_div_Iusy /= 6.0f;
            break;
          }
        case TYPE_MTZ_DEPENDENT_RTV_I:
          {
            K = 30.0f;
            alpha = 3.0f;
            break;
          } 
        default:
          {
            //���������� ����� ����� �� ���� � ����
            total_error_sw_fixed(87);
          }
        }
      
        register float rising_to_power = powf(I_div_Iusy, alpha);
        if (
            (isnan(rising_to_power) != 0) || 
            (isinf(rising_to_power) != 0) ||
            (rising_to_power <= 0)
           )
        {
          //���������� ����� ����� �� ���� � ����
          total_error_sw_fixed(86);
        }
      
        timeout_dependent = 1.0f/(K*rising_to_power)+ timeout;
      }

      int timeout_dependent_int = (int)timeout_dependent;
      if (timeout_dependent_int > (TIMEOUT_MTZ2_MAX/1000)) timeout_dependent = (TIMEOUT_MTZ2_MAX/1000);
      else if (timeout_dependent_int < 0) timeout_dependent = 0;
    
      timeout_result = (int)(timeout_dependent*1000.0f);
    }
    else timeout_result = TIMEOUT_MTZ2_MAX;
  }
  
  return timeout_result;
}
/*****************************************************/

/*****************************************************/
// ���
/*****************************************************/
inline void mtz_handler(unsigned int *activated_functions, unsigned int number_group_stp)
{
  unsigned int tmp_value;
  
  unsigned int po_mtz_x;
  unsigned int direction_ABC_tmp;
  unsigned int po_mtzn_x_vpered_setpoint;
  unsigned int po_mtzn_x_nazad_setpoint;
//  unsigned int po_block_u_mtzn_x_setpoint;
  unsigned int po_i_ncn_setpoint;
  unsigned int po_u_ncn_setpoint;
  unsigned int po_u_mtzpn_x_setpoint;
  unsigned int po_mtzpn_x_setpoint;
  
  /******������������� ����� ���������� ��� 4-� ��������*******/
  _Bool ctr_mtz_nespr_kil_napr = (current_settings_prt.control_mtz & CTR_MTZ_NESPR_KIL_NAPR) != 0; //������. ����. ���. (�)
  
  //�� I���
  po_i_ncn_setpoint = previous_state_mtz_po_incn ?
            i_nom_const * KOEF_POVERNENNJA_MTZ_I_DOWN / 100 :
            i_nom_const;
  
  previous_state_mtz_po_incn = ((measurement[IM_IA] <= po_i_ncn_setpoint)   &&
                                (measurement[IM_IB_r] <= po_i_ncn_setpoint) &&
                                (measurement[IM_IC] <= po_i_ncn_setpoint));
  
  //�� U���
  po_u_ncn_setpoint = previous_state_mtz_po_uncn ?
            u_linear_nom_const * U_DOWN / 100 :
            u_linear_nom_const;
  
  previous_state_mtz_po_uncn = ((measurement[IM_UAB] <= po_u_ncn_setpoint) ||
                                (measurement[IM_UBC] <= po_u_ncn_setpoint) ||
                                (measurement[IM_UCA] <= po_u_ncn_setpoint));
  
  ctr_mtz_nespr_kil_napr = ctr_mtz_nespr_kil_napr && previous_state_mtz_po_incn && previous_state_mtz_po_uncn; //������������� ����� ���������� (_AND3)
  
  //������������� ����� ����������
  if (ctr_mtz_nespr_kil_napr) {
    _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_NCN_MTZ);
  }
  /******������������� ����� ���������� ��� 4-� ��������*******/
  
  /******�� U ����. �����***********************/
  //������� �� U ����. ����� � ����������� ����������
  unsigned int po_block_u_mtzn_x_setpoint = (_CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_PO_BLOCK_U_MTZN) == 0) ? PORIG_CHUTLYVOSTI_VOLTAGE : PORIG_CHUTLYVOSTI_VOLTAGE * U_DOWN / 100;
  
  //�� U ����. �����
  if (
      (measurement[IM_UAB] <= po_block_u_mtzn_x_setpoint) ||
      (measurement[IM_UBC] <= po_block_u_mtzn_x_setpoint) ||
      (measurement[IM_UCA] <= po_block_u_mtzn_x_setpoint)
     )
  {
    _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_BLOCK_U_MTZN);
  }
  /******�� U ����. �����***********************/

  for (int mtz_level = 0; mtz_level < NUMBER_LEVEL_MTZ; mtz_level++) {
    //��� �������
//    if (mtz_level == 0) {
//      mtz_level = 0;
//    } else if (mtz_level == 1) {
//      mtz_level = 1;
//    } else if (mtz_level == 2) {
//      mtz_level = 2;
//    } else if (mtz_level == 3) {
//      mtz_level = 3;
//    }
    
    //�
    /*��������� ��� ���*/
    tmp_value = (*type_mtz_arr[mtz_level] == 1)                                  << 0; //������������
    tmp_value |= (*type_mtz_arr[mtz_level] == 2)                                 << 1; //� ������
    tmp_value |= (*type_mtz_arr[mtz_level] == 0)                                 << 2; //�������
    tmp_value |= (
                  (mtz_level == 1)
                  && (*type_mtz_arr[mtz_level] >= TYPE_MTZ_DEPENDENT_A)
                  && (*type_mtz_arr[mtz_level] <= TYPE_MTZ_DEPENDENT_RTV_I) 
                 )                                                               << 3; //��������� (���� mtz_level == 1 (2-� ������� ���))
    
    /******�� ����***********************/
    //������� �� ���� � ������ �����������
    po_mtz_x = (_CHECK_SET_BIT(active_functions, mtz_settings_prt[mtz_level][RANG_OUTPUT_LED_DF_REG_PO_MTZ]) != 0) ?
            *(setpoint_mtz[mtz_level] + number_group_stp) * KOEF_POVERNENNJA_MTZ_I_UP / 100 :
            *(setpoint_mtz[mtz_level] + number_group_stp);
    
    tmp_value |= ((measurement[IM_IA] >= po_mtz_x) ||
          (measurement[IM_IB_r] >= po_mtz_x) ||
          (measurement[IM_IC] >= po_mtz_x)) << 4; //�� ����
    /******�� ����***********************/
    
    //�
    tmp_value |= ((current_settings_prt.control_mtz & mtz_const_menu_settings_prt[mtz_level][CTR_MTZ]) != 0) << 5; //���� ���.
    //��
    tmp_value |= (_CHECK_SET_BIT(activated_functions, mtz_settings_prt[mtz_level][RANG_OUTPUT_LED_DF_REG_BLOCK_MTZ]) == 0) << 6; //���������� ����
    //�
    tmp_value |= ((current_settings_prt.control_mtz & mtz_const_menu_settings_prt[mtz_level][CTR_MTZ_VPERED]) != 0) << 7; //�����: ���. ����
    tmp_value |= ((current_settings_prt.control_mtz & mtz_const_menu_settings_prt[mtz_level][CTR_MTZ_NAZAD]) != 0) << 8; //�����: ���. ���
    
    /******������ ����� ������/�����**********/
    //�������� �������������� ��� �,�,�
    direction_ABC_tmp = (sector_directional_mtz[mtz_level][PHASE_A_INDEX] == MTZ_VPERED) << 0; //�������� �������������� ���� � ������
    direction_ABC_tmp |= (sector_directional_mtz[mtz_level][PHASE_B_INDEX] == MTZ_VPERED) << 1; //�������� �������������� ���� B ������
    direction_ABC_tmp |= (sector_directional_mtz[mtz_level][PHASE_C_INDEX] == MTZ_VPERED) << 2; //�������� �������������� ���� C ������
    
    _OR3(direction_ABC_tmp, 0, direction_ABC_tmp, 1, direction_ABC_tmp, 2, direction_ABC_tmp, 3);
    
    //������ ����� ������
    if (_GET_OUTPUT_STATE(direction_ABC_tmp, 3)) {
      _SET_BIT(activated_functions, mtz_settings_prt[mtz_level][RANG_OUTPUT_LED_DF_REG_SECTOR_VPERED_MTZN]);
    }
    
    direction_ABC_tmp |= (sector_directional_mtz[mtz_level][PHASE_A_INDEX] == MTZ_NAZAD) << 4; //�������� �������������� ���� � �����
    direction_ABC_tmp |= (sector_directional_mtz[mtz_level][PHASE_B_INDEX] == MTZ_NAZAD) << 5; //�������� �������������� ���� B �����
    direction_ABC_tmp |= (sector_directional_mtz[mtz_level][PHASE_C_INDEX] == MTZ_NAZAD) << 6; //�������� �������������� ���� C �����
    
    _OR3(direction_ABC_tmp, 4, direction_ABC_tmp, 5, direction_ABC_tmp, 6, direction_ABC_tmp, 7);
    
    //������ ����� �����
    if (_GET_OUTPUT_STATE(direction_ABC_tmp, 7)) {
      _SET_BIT(activated_functions, mtz_settings_prt[mtz_level][RANG_OUTPUT_LED_DF_REG_SECTOR_NAZAD_MTZN]);
    }
    
    //������� �� ����1 ����. � ������ �����������
    po_mtzn_x_vpered_setpoint = (_CHECK_SET_BIT(active_functions, mtz_settings_prt[mtz_level][RANG_OUTPUT_LED_DF_REG_PO_MTZN_VPERED]) != 0) ?
            *(setpoint_mtz_n_vpered[mtz_level] + number_group_stp) * KOEF_POVERNENNJA_MTZ_I_UP / 100 :
            *(setpoint_mtz_n_vpered[mtz_level] + number_group_stp);
    
    direction_ABC_tmp |= (measurement[IM_IA] >= po_mtzn_x_vpered_setpoint) << 8; //���������� � �������� ���� �� ���� � (������)
    direction_ABC_tmp |= (measurement[IM_IB_r] >= po_mtzn_x_vpered_setpoint) << 9; //���������� � �������� ���� �� ���� B (������)
    direction_ABC_tmp |= (measurement[IM_IC] >= po_mtzn_x_vpered_setpoint) << 10; //���������� � �������� ���� �� ���� C (������)
    
    //������� �� ����1 ����. � ������ �����������
    po_mtzn_x_nazad_setpoint = (_CHECK_SET_BIT(active_functions, mtz_settings_prt[mtz_level][RANG_OUTPUT_LED_DF_REG_PO_MTZN_NAZAD]) != 0) ?
            *(setpoint_mtz_n_nazad[mtz_level] + number_group_stp) * KOEF_POVERNENNJA_MTZ_I_UP / 100 :
            *(setpoint_mtz_n_nazad[mtz_level] + number_group_stp);
    
    direction_ABC_tmp |= (measurement[IM_IA] >= po_mtzn_x_nazad_setpoint) << 11; //���������� � �������� ���� �� ���� � (�����)
    direction_ABC_tmp |= (measurement[IM_IB_r] >= po_mtzn_x_nazad_setpoint) << 12; //���������� � �������� ���� �� ���� B (�����)
    direction_ABC_tmp |= (measurement[IM_IC] >= po_mtzn_x_nazad_setpoint) << 13; //���������� � �������� ���� �� ���� C (�����)
    
    _AND2(direction_ABC_tmp, 8, direction_ABC_tmp, 0, direction_ABC_tmp, 14);
    _AND2(direction_ABC_tmp, 9, direction_ABC_tmp, 1, direction_ABC_tmp, 15);
    _AND2(direction_ABC_tmp, 10, direction_ABC_tmp, 2, direction_ABC_tmp, 16);
    
    _AND2(direction_ABC_tmp, 11, direction_ABC_tmp, 4, direction_ABC_tmp, 17);
    _AND2(direction_ABC_tmp, 12, direction_ABC_tmp, 5, direction_ABC_tmp, 18);
    _AND2(direction_ABC_tmp, 13, direction_ABC_tmp, 6, direction_ABC_tmp, 19);
    
    _OR3(direction_ABC_tmp, 14, direction_ABC_tmp, 15, direction_ABC_tmp, 16, tmp_value, 12);
    _OR3(direction_ABC_tmp, 17, direction_ABC_tmp, 18, direction_ABC_tmp, 19, tmp_value, 13);
    /******������ ����� ������/�����**********/
    
//    /******�� U ����. �����***********************/
//    //������� �� U ����. ����� � ������ �����������
//    po_block_u_mtzn_x_setpoint = (_CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_PO_BLOCK_U_MTZN) != 0) ?
//           PORIG_CHUTLYVOSTI_VOLTAGE :
//           PORIG_CHUTLYVOSTI_VOLTAGE * U_DOWN / 100;
//    
//    tmp_value |= ((measurement[IM_UAB] <= po_block_u_mtzn_x_setpoint) ||
//                  (measurement[IM_UBC] <= po_block_u_mtzn_x_setpoint) ||
//                  (measurement[IM_UCA] <= po_block_u_mtzn_x_setpoint)) << 14; //�� U ����. �����
//    
//    //�� U ����. �����
//    if (_GET_OUTPUT_STATE(tmp_value, 14)) {
//      _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_BLOCK_U_MTZN);
//    }
//    /******�� U ����. �����***********************/
    tmp_value |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_BLOCK_U_MTZN) != 0) << 14;
    
    //������������� ����� ���������� ��� ������� ����
    tmp_value |= (
                   !(_CHECK_SET_BIT(active_functions, mtz_settings_prt[mtz_level][RANG_OUTPUT_LED_DF_REG_PO_MTZN_VPERED]) != 0 ||
                     _CHECK_SET_BIT(active_functions, mtz_settings_prt[mtz_level][RANG_OUTPUT_LED_DF_REG_PO_MTZN_NAZAD])  != 0 ||
                     _CHECK_SET_BIT(active_functions, mtz_settings_prt[mtz_level][RANG_OUTPUT_LED_DF_REG_PO_MTZPN])     != 0)
                   &&
                   ctr_mtz_nespr_kil_napr
                 ) << 15;
    
    /******�� U ������***********************/
    po_u_mtzpn_x_setpoint = (_CHECK_SET_BIT(active_functions, mtz_settings_prt[mtz_level][RANG_OUTPUT_LED_DF_REG_PO_U_MTZPN]) != 0) ?
            *(setpoint_mtz_U[mtz_level] + number_group_stp) * U_DOWN / 100:
            *(setpoint_mtz_U[mtz_level] + number_group_stp) ;
    
    tmp_value |= ((measurement[IM_UAB] <= po_u_mtzpn_x_setpoint) ||
                  (measurement[IM_UBC] <= po_u_mtzpn_x_setpoint) ||
                  (measurement[IM_UCA] <= po_u_mtzpn_x_setpoint)) << 16; //�� U ������
    
    //�� U ������
    if (_GET_OUTPUT_STATE(tmp_value, 16)) {
      _SET_BIT(activated_functions, mtz_settings_prt[mtz_level][RANG_OUTPUT_LED_DF_REG_PO_U_MTZPN]);
    }
    /******�� U ������***********************/
    
    /******�� ������***********************/
    po_mtzpn_x_setpoint = (_CHECK_SET_BIT(active_functions, mtz_settings_prt[mtz_level][RANG_OUTPUT_LED_DF_REG_PO_MTZPN]) != 0) ?
            *(setpoint_mtz_po_napruzi[mtz_level] + number_group_stp) * KOEF_POVERNENNJA_MTZ_I_UP / 100:
            *(setpoint_mtz_po_napruzi[mtz_level] + number_group_stp);
    
    tmp_value |= ((measurement[IM_IA] >= po_mtzpn_x_setpoint)   ||
                  (measurement[IM_IB_r] >= po_mtzpn_x_setpoint) ||
                  (measurement[IM_IC] >= po_mtzpn_x_setpoint)) << 17; //�� ������
    /******�� ������***********************/
    
    if (mtz_level == 1) { //������ ��� 2-�� �������
      //��
      tmp_value |= (_CHECK_SET_BIT(activated_functions, mtz_settings_prt[mtz_level][RANG_OUTPUT_LED_DF_REG_BLOCK_USK_MTZ]) == 0) << 9; //���������� ��������� ��� 2
      //�
      tmp_value |= ((current_settings_prt.control_mtz & CTR_MTZ_2_PRYSKORENA) != 0) << 10; //���2 ����������
      //��
      tmp_value |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_STATE_VV) != 0) << 18; //��������� ��
      //M
      tmp_value |= ((current_settings_prt.control_mtz & CTR_MTZ_2_PRYSKORENNJA) != 0) << 11; //��������� ���2 ���.
    }
    
    if (_GET_OUTPUT_STATE(tmp_value, 15)) { //���� ������������� ������������� ����� ���������� ��� ������� ����
      _CLEAR_STATE(tmp_value, 16); //������� �� U ������
    }
    
    _OR2_INVERTOR(tmp_value, 14, tmp_value, 15, tmp_value, 14);
    
    if (_CHECK_SET_BIT(active_functions, mtz_settings_prt[mtz_level][RANG_OUTPUT_LED_DF_REG_PO_MTZ]) != 0) {
      _SET_STATE(tmp_value, 19);
    } else {
      if (mtz_level == 1) {
        //������ ��� 2-�� ������� ��� ������������ 19-�� ������� ����� �����������
        //������ "���������" (tmp_value 3)
        if (_GET_OUTPUT_STATE(tmp_value, 14)) {
          _OR3(tmp_value, 2, tmp_value, 3, tmp_value, 15, tmp_value, 19);
        } else {
          _OR4(tmp_value, 0, tmp_value, 2, tmp_value, 3, tmp_value, 15, tmp_value, 19);
        }
      } else {
        if (_GET_OUTPUT_STATE(tmp_value, 14)) {
          _OR2(tmp_value, 2, tmp_value, 15, tmp_value, 19);
        } else {
          _OR3(tmp_value, 0, tmp_value, 2, tmp_value, 15, tmp_value, 19);
        }
      }
    }
    
    _AND2(tmp_value, 5, tmp_value, 6, tmp_value, 20);
    
    //�� ����
    _AND3(tmp_value, 19, tmp_value, 4, tmp_value, 20, tmp_value, 21);
    if (_GET_OUTPUT_STATE(tmp_value, 21)) {
      _SET_BIT(activated_functions, mtz_settings_prt[mtz_level][RANG_OUTPUT_LED_DF_REG_PO_MTZ]);
    }
    
    //�� ����� ������
    _AND5(tmp_value, 0, tmp_value, 20, tmp_value, 7, tmp_value, 12, tmp_value, 14, tmp_value, 22);
    if (_GET_OUTPUT_STATE(tmp_value, 22)) {
      _SET_BIT(activated_functions, mtz_settings_prt[mtz_level][RANG_OUTPUT_LED_DF_REG_PO_MTZN_VPERED]);
    }
    
    //�� ����� �����
    _AND5(tmp_value, 0, tmp_value, 20, tmp_value, 8, tmp_value, 13, tmp_value, 14, tmp_value, 23);
    if (_GET_OUTPUT_STATE(tmp_value, 23)) {
      _SET_BIT(activated_functions, mtz_settings_prt[mtz_level][RANG_OUTPUT_LED_DF_REG_PO_MTZN_NAZAD]);
    }
    
    //�� ������
    _AND4(tmp_value, 1, tmp_value, 20, tmp_value, 16, tmp_value, 17, tmp_value, 24);
    if (_GET_OUTPUT_STATE(tmp_value, 24)) {
      _SET_BIT(activated_functions, mtz_settings_prt[mtz_level][RANG_OUTPUT_LED_DF_REG_PO_MTZPN]);
    }
    
    if (mtz_level != 1) { //��� ���� �������� ����� 2-��
      _TIMER_T_0(mtz_tmr_const[mtz_level][INDEX_TIMER_MTZ], *(timeout_mtz[mtz_level] + number_group_stp), tmp_value, 21, tmp_value, 25);
      _TIMER_T_0(mtz_tmr_const[mtz_level][INDEX_TIMER_MTZ_N_VPERED], *(timeout_mtz_n_vpered[mtz_level] + number_group_stp), tmp_value, 22, tmp_value, 26);
      _TIMER_T_0(mtz_tmr_const[mtz_level][INDEX_TIMER_MTZ_N_NAZAD], *(timeout_mtz_n_nazad[mtz_level] + number_group_stp), tmp_value, 23, tmp_value, 27);
      _TIMER_T_0(mtz_tmr_const[mtz_level][INDEX_TIMER_MTZ_PO_NAPRUZI], *(timeout_mtz_po_napruzi[mtz_level] + number_group_stp), tmp_value, 24, tmp_value, 28);
      _OR4(tmp_value, 25, tmp_value, 26, tmp_value, 27, tmp_value, 28, tmp_value, 31);
    } else {
      unsigned int tmp = 0;
      _AND2(tmp_value, 18, tmp_value, 11, tmp, 0);
      _TIMER_IMPULSE(INDEX_TIMER_MTZ2_VVID_PR, current_settings_prt.timeout_mtz_2_vvid_pr[number_group_stp], temp_states_for_mtz, 0, tmp, 0, tmp, 1);
      _OR2(tmp, 1, tmp_value, 10, tmp, 2);
      _AND2(tmp_value, 9, tmp, 2, tmp, 3);
      _INVERTOR(tmp, 3, tmp, 4);
      _INVERTOR(tmp_value, 3, tmp, 23); /*��������� ������� � ��������� ��������*/
      _AND3(tmp, 4, tmp_value, 3, tmp_value, 21, tmp, 5);
      _AND2(tmp, 3, tmp_value, 21, tmp, 6);
      _AND3(tmp, 4, tmp_value, 21, tmp, 23, tmp, 7); /*������������ ������� � ��������� �������*/
      _AND2(tmp, 4, tmp_value, 22, tmp, 8);
      _AND2(tmp, 3, tmp_value, 22, tmp, 9);
      _AND2(tmp, 4, tmp_value, 23, tmp, 10);
      _AND2(tmp, 3, tmp_value, 23, tmp, 11);
      _AND2(tmp, 4, tmp_value, 24, tmp, 12);
      _AND2(tmp, 3, tmp_value, 24, tmp, 13);
      
      unsigned int i_max = measurement[IM_IA];
      if (i_max < measurement[IM_IB_r]) i_max = measurement[IM_IB_r];
      if (i_max < measurement[IM_IC]) i_max = measurement[IM_IC];
      _TIMER_T_0_LOCK(INDEX_TIMER_MTZ2_DEPENDENT, timeout_dependent_general(i_max, number_group_stp), tmp, 5, p_global_trigger_state_mtz2, 0);
      _TIMER_T_0(INDEX_TIMER_MTZ2_PR, current_settings_prt.timeout_mtz_2_pr[number_group_stp], tmp, 6, tmp, 15);
      _TIMER_T_0(INDEX_TIMER_MTZ2, current_settings_prt.timeout_mtz_2[number_group_stp], tmp, 7, tmp, 16);
      _TIMER_T_0(INDEX_TIMER_MTZ2_N_VPERED, current_settings_prt.timeout_mtz_2_n_vpered[number_group_stp], tmp, 8, tmp, 17);
      _TIMER_T_0(INDEX_TIMER_MTZ2_N_VPERED_PR, current_settings_prt.timeout_mtz_2_n_vpered_pr[number_group_stp], tmp, 9, tmp, 18);
      _TIMER_T_0(INDEX_TIMER_MTZ2_N_NAZAD, current_settings_prt.timeout_mtz_2_n_nazad[number_group_stp], tmp, 10, tmp, 19);
      _TIMER_T_0(INDEX_TIMER_MTZ2_N_NAZAD_PR, current_settings_prt.timeout_mtz_2_n_nazad_pr[number_group_stp], tmp, 11, tmp, 20);
      _TIMER_T_0(INDEX_TIMER_MTZ2_PO_NAPRUZI, current_settings_prt.timeout_mtz_2_po_napruzi[number_group_stp], tmp, 12, tmp, 21);
      _TIMER_T_0(INDEX_TIMER_MTZ2_PO_NAPRUZI_PR, current_settings_prt.timeout_mtz_2_po_napruzi_pr[number_group_stp], tmp, 13, tmp, 22);
      
      _OR6(p_global_trigger_state_mtz2, 0, tmp, 15, tmp, 16, tmp, 17, tmp, 18, tmp, 19, tmp_value, 29);
      _OR3(tmp, 20, tmp, 21, tmp, 22, tmp_value, 30);
      _OR2(tmp_value, 29, tmp_value, 30, tmp_value, 31);
    }
    
    //����.����
    if (_GET_OUTPUT_STATE(tmp_value, 31)) {
      _SET_BIT(activated_functions, mtz_settings_prt[mtz_level][RANG_OUTPUT_LED_DF_REG_MTZ]);
    }
  }
}
/*****************************************************/

/*****************************************************/
// ���
/*****************************************************/
inline void zdz_handler(unsigned int *activated_functions)
{
  unsigned int tmp_value;
  //M
  tmp_value = ((current_settings_prt.control_zdz & CTR_ZDZ_STARTED_FROM_MTZ1) != 0) << 0; //���� �� ���1 : ���/����
  tmp_value |= ((current_settings_prt.control_zdz & CTR_ZDZ_STARTED_FROM_MTZ2) != 0) << 1; //���� �� ���2 : ���/����
  tmp_value |= ((current_settings_prt.control_zdz & CTR_ZDZ_STARTED_FROM_MTZ3) != 0) << 2; //���� �� ���3 : ���/����
  tmp_value |= ((current_settings_prt.control_zdz & CTR_ZDZ_STARTED_FROM_MTZ4) != 0) << 3; //���� �� ���4 : ���/����
  
  for (int mtz_level = 0; mtz_level < NUMBER_LEVEL_MTZ; mtz_level++) {
    //����� �� �� active ������ ��� ������� �������������� �� ���������� ���� mtz_handler()
    tmp_value |= (_CHECK_SET_BIT(activated_functions, mtz_settings_prt[mtz_level][RANG_OUTPUT_LED_DF_REG_PO_MTZ]) != 0) << (4 + mtz_level); //�� ���x
    tmp_value |= (_CHECK_SET_BIT(activated_functions, mtz_settings_prt[mtz_level][RANG_OUTPUT_LED_DF_REG_PO_MTZN_VPERED]) != 0) << (8 + mtz_level); //�� ����� ������
    tmp_value |= (_CHECK_SET_BIT(activated_functions, mtz_settings_prt[mtz_level][RANG_OUTPUT_LED_DF_REG_PO_MTZN_NAZAD]) != 0) << (12 + mtz_level);  //�� ����� �����
    tmp_value |= (_CHECK_SET_BIT(activated_functions, mtz_settings_prt[mtz_level][RANG_OUTPUT_LED_DF_REG_PO_MTZPN]) != 0) << (16 + mtz_level); //�� ������
  }
  //�
  tmp_value |= ((current_settings_prt.control_zdz & CTR_ZDZ_STATE) != 0) << 20;
  //��
  tmp_value |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PUSK_ZDZ_VID_DV) != 0) << 21; //���� ��� �� ��
  
  _OR4(tmp_value, 4, tmp_value, 8, tmp_value, 12, tmp_value, 16, tmp_value, 22);
  _OR4(tmp_value, 5, tmp_value, 9, tmp_value, 13, tmp_value, 17, tmp_value, 23);
  _OR4(tmp_value, 6, tmp_value, 10, tmp_value, 14, tmp_value, 18, tmp_value, 24);
  _OR4(tmp_value, 7, tmp_value, 11, tmp_value, 15, tmp_value, 19, tmp_value, 25);
  
  _AND2(tmp_value, 0, tmp_value, 22, tmp_value, 26);
  _AND2(tmp_value, 1, tmp_value, 23, tmp_value, 27);
  _AND2(tmp_value, 2, tmp_value, 24, tmp_value, 28);
  _AND2(tmp_value, 3, tmp_value, 25, tmp_value, 29);
  
  _OR4(tmp_value, 26, tmp_value, 27, tmp_value, 28, tmp_value, 29, tmp_value, 30);
  
  unsigned int tmp_value2 = 0;
  _AND3(tmp_value, 30, tmp_value, 21, tmp_value, 20, tmp_value2, 0);
  _OR4_INVERTOR(tmp_value, 0, tmp_value, 1, tmp_value, 2, tmp_value, 3, tmp_value2, 1);
  _AND3(tmp_value2, 1, tmp_value, 21, tmp_value, 20, tmp_value2, 2);
  
  _OR2(tmp_value2, 0, tmp_value2, 2, tmp_value2, 3);
  
  //����. ���
  if (_GET_OUTPUT_STATE(tmp_value2, 3)) {
    _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_ZDZ);
  }
}
/*****************************************************/

/*****************************************************/
// ��
/*****************************************************/
inline void zz_handler(unsigned int *activated_functions, unsigned int number_group_stp)
{
  /********************************
  ������ ���

  "������ ���" ����������� ��� �������:
  
  ����� 3I0 (���������� � ������� ��������) > 5 (��)
  ����� 3U0 (���������� �         ���������) > 6 (�)
  
  *********************************/
  unsigned int porig_3I0;
  if (Nzz_3I0_bilshe_porogu == 0) porig_3I0 = PORIG_CHUTLYVOSTI_3I0*KOEF_POVERNENNJA_SECTOR_BLK/100;
  else porig_3I0 = PORIG_CHUTLYVOSTI_3I0;
  unsigned int Nzz_3I0_bilshe_porogu_tmp = Nzz_3I0_bilshe_porogu = (measurement[IM_3I0] >= porig_3I0);

  unsigned int porig_3U0;
  if (Nzz_3U0_bilshe_porogu == 0) porig_3U0 = PORIG_CHUTLYVOSTI_3U0*KOEF_POVERNENNJA_SECTOR_BLK/100;
  else porig_3U0 = PORIG_CHUTLYVOSTI_3U0;
  unsigned int Nzz_3U0_bilshe_porogu_tmp = Nzz_3U0_bilshe_porogu = (measurement[IM_3U0_UBC_TN2] >= porig_3U0);
      
  if (
      ((current_settings_prt.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_3U0_Ubc_TN2) == 0) &&
      ((current_settings_prt.control_zz & CTR_ZZ1_TYPE) == 0) &&
      (Nzz_3I0_bilshe_porogu_tmp != 0) &&
      (Nzz_3U0_bilshe_porogu_tmp != 0)
     )
  {
    unsigned int sector_i_minus_u;
    if (sector_NZZ == 0)
    {
      //�������� �� ������� ����������� ��� ���
      sector_i_minus_u = sector_i_minus_u_1;
    }
    else
    {
      //�������� �� ������� ���������� ��� ���
      sector_i_minus_u = sector_i_minus_u_2;
    }
  
    if ((current_settings_prt.control_zz & CTR_ZZ1_SECTOR) != 0)
    {
      //�������� �� ������� "������" (��������� 1 � 2 ��� "��� ������")
      if ((sector_i_minus_u == 1) || (sector_i_minus_u == 2))
      {
        /*
        ����-��� ��������� �������� ������, �� �� � ������ �����������
        */
        sector_NZZ = 0xff;
      }
      else
      {
        /*
        ������� �������� ������, �� �� �� � ������ �����������
        */
        sector_NZZ = 0;
      }
    }
    else
    {
      //�������� �� ������� "�����" (��������� 3 � 4 ��� "��� ������")
      if ((sector_i_minus_u == 3) || (sector_i_minus_u == 4))
      {
        /*
        ����-��� ��������� �������� ������, �� �� � ������ �����������
        */
        sector_NZZ = 0xff;
      }
      else
      {
        /*
        ������� �������� ������, �� �� �� � ������ �����������
        */
        sector_NZZ = 0;
      }
    }
  
    //������������ ������ "������ ���",���� �� �������� - � ������ ������� �� ��������
    if (sector_NZZ != 0)
      _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_SECTOR_NZZ);
  }
  else sector_NZZ = 0;
  /*******************************/

  /*******************************/
  //��������� �� ����� ���������� ������ ���������� � ���� ���������� ����������
  /*******************************/
  unsigned int max_3i0_current, koef_povernennja;
  
  if((current_settings_prt.control_zz & CTR_ZZ1_TYPE) == 0)
  {
    max_3i0_current = measurement[IM_3I0];
    koef_povernennja = KOEF_POVERNENNJA_GENERAL_UP;
  }
  else
  {
    max_3i0_current = measurement[IM_3I0_other_g];
    koef_povernennja = KOEF_POVERNENNJA_3I0_OTHER;
  }
  /*******************************/
  
  unsigned int setpoint;
  /********************************
  �� 3I0 (�� ��� ����������� ��������, ������� �����������/����������)
  ********************************/
  /*
  ������� ���������� � ��� � ������� �� ������� �������, � ������� � ��� � ���������,
  �� ������� ������ �� 10, ��� �������� �� ����� � ������� ��������
  */
  if (po_3I0 == 0)
  {
    //�������� �� ������� ����������� ��� 3I0
    setpoint = current_settings_prt.setpoint_zz_3I0[number_group_stp]*10;
  }
  else
  {
    //�������� �� ������� ���������� ��� 3I0
    /*
    ���������� ��������� ������
    setpoint = (current_settings_prt.setpoint_zz_3I0[number_group_stp]*koef_povernennja/100)*10 =  current_settings_prt.setpoint_zz_3I0[number_group_stp]*koef_povernennja/10
    */
    setpoint = current_settings_prt.setpoint_zz_3I0[number_group_stp]*koef_povernennja/10;
  }
  
  if (max_3i0_current >= setpoint)
  {
    /*
    ����-��� ��������� �������� ������, �� ��������� �������� ����-���� ������ ������������ �������
    */
    po_3I0 = 0xff;
  }
  else
  {
    /*
    ������� �������� ������, �� ��������� �������� ����� ������ ������������ �������
    */
    po_3I0 = 0;
  }
  /*******************************/

  if ((current_settings_prt.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_3U0_Ubc_TN2) == 0)
  {
    /********************************
    �� 3U0 (�� ��� ����������� ��������, ������� �����������/����������)
    ********************************/
    if (po_3U0 == 0)
    {
      //�������� �� ������� ����������� ��� 3U0
      setpoint = current_settings_prt.setpoint_zz_3U0[number_group_stp];
    }
    else
    {
      //�������� �� ������� ���������� ��� 3U0
      setpoint = current_settings_prt.setpoint_zz_3U0[number_group_stp]*KOEF_POVERNENNJA_3U0/100;
    }
  
    if (measurement[IM_3U0_UBC_TN2] >= setpoint)
    {
      /*
      ����-��� ��������� �������� ������, �� ��������� �������� ����-���� ������ ������������ �������
      */
      po_3U0 = 0xff;
    }
    else
    {
      /*
      ������� �������� ������, �� ��������� �������� ����� ������ ������������ �������
      */
      po_3U0 = 0;
    }
  }
  /*******************************/
  
  if (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_BLOCK_NZZ) == 0)
  {
    //���, ��/3I0 � ��/3U0 �� ��������� � ����������� �����
    /*******************************/
    //���
    /*******************************/
    if (
        ((current_settings_prt.control_zz & CTR_ZZ1_NZZ_STATE) != 0) &&
        ((current_settings_prt.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_3U0_Ubc_TN2) == 0) &&
        ((current_settings_prt.control_zz & CTR_ZZ1_TYPE) == 0)
       )   
    {
      //1 ������ ��/3U0 ��������, ��������� � �� ���������
    
      //������� �������� �������� ������� ��/3U0 � ���������� �����, ��� ���� ���� ��������� �� ������� ��� �������������
      //�� ������� ��� ����, ��� ���� � �����, �� ������ �� �� � ��������������� � ��������� - ��� �� ������� ��� �������� ��������  
      unsigned int maska[N_BIG] = {0, 0, 0, 0, 0, 0};
      _SET_BIT(maska, RANG_OUTPUT_LED_DF_REG_PO_NZZ);
      _SET_BIT(maska, RANG_OUTPUT_LED_DF_REG_NZZ);
      activated_functions[0] |= active_functions[0] & maska[0];
      activated_functions[1] |= active_functions[1] & maska[1];
      activated_functions[2] |= active_functions[2] & maska[2];
      activated_functions[3] |= active_functions[3] & maska[3];
      activated_functions[4] |= active_functions[4] & maska[4];
      activated_functions[5] |= active_functions[5] & maska[5];
    
      unsigned int previous_state_po_nzz = _CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_PO_NZZ);
    
      //�����������, ��� ������� ������ "�� NZZ"
      if (
          (po_3I0     != 0) &&
          (po_3U0     != 0) &&
          (sector_NZZ != 0)
         )
      {
        //���� ����� ������ �� ���
        if(previous_state_po_nzz == 0)
        {
          //������������ ������ "�� NZZ"
          _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_NZZ);
      
          //��������� ������ ���, ���� �� �� �� ���������
          global_timers[INDEX_TIMER_NZZ] = 0;
        }
      }
      else 
      {
        //�� ���� ����� ������ �� ���
        if(previous_state_po_nzz != 0)
        {
          //������� ������ "�� ���"
          _CLEAR_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_NZZ);
          //�� � ������ ����� �������� ������� "����. ���"
          _CLEAR_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_NZZ);
          //���� ������ �� �� ��������, �� ������� ����
          if ( global_timers[INDEX_TIMER_NZZ] >=0) global_timers[INDEX_TIMER_NZZ] = -1;
        }
      }
    
      if(global_timers[INDEX_TIMER_NZZ] >= current_settings_prt.timeout_nzz[number_group_stp])
      {
        //���� ��������� "�������� ���" �� ������������ ������ "����. ���"
        _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_NZZ);

        //������� ������ �� ���
        global_timers[INDEX_TIMER_NZZ] = -1;
      }
    }
    else
    {
      //���� ��� �� �����������, �� ����� ������� �� ������� � �������, �� �� �� ����������
      _CLEAR_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_NZZ);
      _CLEAR_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_NZZ);
      global_timers[INDEX_TIMER_NZZ] = -1;
    }  
    /*******************************/

    /*******************************/
    //1 ������ ��/3U0
    /*******************************/
    if (
        ((current_settings_prt.control_zz & CTR_ZZ1_3U0_STATE) != 0) &&
        ((current_settings_prt.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_3U0_Ubc_TN2) == 0)  
       )   
    {
      //1 ������ ��/3U0 �������� � �� ���������
    
      //������� �������� �������� ������� ��/3U0 � ���������� �����, ��� ���� ���� ��������� �� ������� ��� �������������
      //�� ������� ��� ����, ��� ���� � �����, �� ������ �� �� � ��������������� � ��������� - ��� �� ������� ��� �������� ��������  
      unsigned int maska[N_BIG] = {0, 0, 0, 0, 0, 0};
      _SET_BIT(maska, RANG_OUTPUT_LED_DF_REG_PO_3U0);
      _SET_BIT(maska, RANG_OUTPUT_LED_DF_REG_3U0);
      activated_functions[0] |= active_functions[0] & maska[0];
      activated_functions[1] |= active_functions[1] & maska[1];
      activated_functions[2] |= active_functions[2] & maska[2];
      activated_functions[3] |= active_functions[3] & maska[3];
      activated_functions[4] |= active_functions[4] & maska[4];
      activated_functions[5] |= active_functions[5] & maska[5];
    
      unsigned int previous_state_po_3U0 = _CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_PO_3U0);
    
      //�����������, ��� ������� ������ "�� ��/3U0"
      if (po_3U0 != 0)
      {
        //����������� ������� 3U0 �������� ���� �������
        if(previous_state_po_3U0 == 0)
        {
          //������������ ������ "�� ��/3U0"
          _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_3U0);
        
          //��������� ������ ��/3U0, ���� �� �� �� ���������
          global_timers[INDEX_TIMER_ZZ_3U0] = 0;
        }
      }
      else 
      {
        //����������� ������� 3I0 ����� �������
        if(previous_state_po_3U0 != 0)
        {
          //������� ������ "�� ��/3U0"
          _CLEAR_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_3U0);
          //�� � ������ ����� �������� ������� "����. ��/3U0"
          _CLEAR_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_3U0);
          //���� ������ �� �� ��������, �� ������� ����
          if ( global_timers[INDEX_TIMER_ZZ_3U0] >=0) global_timers[INDEX_TIMER_ZZ_3U0] = -1;
        }
      }
    
      if(global_timers[INDEX_TIMER_ZZ_3U0] >= current_settings_prt.timeout_zz_3U0[number_group_stp])
      {
        //���� ��������� "�������� ��/3U0" �� ������������ ������ "����. ��/3U0"
        _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_3U0);

        //������� ������ �� ��/3U0
        global_timers[INDEX_TIMER_ZZ_3U0] = -1;
      }
    }
    else
    {
      //���� 1 ������ ��/3U0 �� �����������, �� ����� ������� �� ������� � �������, �� �� �� ����������
      _CLEAR_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_3U0);
      _CLEAR_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_3U0);
      global_timers[INDEX_TIMER_ZZ_3U0] = -1;
    }    
    /*******************************/
  
    /*******************************/
    //1 ������ ��/3I0
    /*******************************/
    if ((current_settings_prt.control_zz & CTR_ZZ1_3I0_STATE) != 0)
    {
      //1 ������ ��/3I0 �������� � �� ���������
    
      //������� �������� �������� ������� ��/3I0 � ���������� �����, ��� ���� ���� ��������� �� ������� ��� �������������
      //�� ������� ��� ����, ��� ���� � �����, �� ������ �� �� � ��������������� � ��������� - ��� �� ������� ��� �������� ��������  
      unsigned int maska[N_BIG] = {0, 0, 0, 0, 0, 0};
      _SET_BIT(maska, RANG_OUTPUT_LED_DF_REG_PO_3I0);
      _SET_BIT(maska, RANG_OUTPUT_LED_DF_REG_3I0);
      activated_functions[0] |= active_functions[0] & maska[0];
      activated_functions[1] |= active_functions[1] & maska[1];
      activated_functions[2] |= active_functions[2] & maska[2];
      activated_functions[3] |= active_functions[3] & maska[3];
      activated_functions[4] |= active_functions[4] & maska[4];
      activated_functions[5] |= active_functions[5] & maska[5];
    
      unsigned int previous_state_po_3I0 = _CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_PO_3I0);
    
      //�����������, ��� ������� ������ "�� ��/3I0"
      if (po_3I0 != 0)
      {
        //������������ ���� 3I0 �������� ���� �������
        if(previous_state_po_3I0 == 0)
        {
          //������������ ������ "�� ��/3I0"
          _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_3I0);
      
          //��������� ������ ��/3I0, ���� �� �� �� ���������
          global_timers[INDEX_TIMER_ZZ_3I0] = 0;
        }
      }
      else 
      {
        //������������ ���� 3I0 ����� �������
        if(previous_state_po_3I0 != 0)
        {
          //������� ������ "�� ��/3I0"
          _CLEAR_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_3I0);
          //�� � ������ ����� �������� ������� "����. ��/3I0"
          _CLEAR_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_3I0);
          //���� ������ �� �� ��������, �� ������� ����
          if ( global_timers[INDEX_TIMER_ZZ_3I0] >=0) global_timers[INDEX_TIMER_ZZ_3I0] = -1;
        }
      }
    
      if(global_timers[INDEX_TIMER_ZZ_3I0] >= current_settings_prt.timeout_zz_3I0[number_group_stp])
      {
        //���� ��������� "�������� ��/3I0" �� ������������ ������ "����. ��"
        _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_3I0);

        //������� ������ �� ��/3I0
        global_timers[INDEX_TIMER_ZZ_3I0] = -1;
      }
    }
    else
    {
      //���� 1 ������ ��/3I0 �� �����������, �� ����� ������� �� ������� � �������, �� �� �� ����������
      _CLEAR_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_3I0);
      _CLEAR_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_3I0);
      global_timers[INDEX_TIMER_ZZ_3I0] = -1;
    }  
    /*******************************/
  }
  else
  {
    //������� ��/��� ��������� � ����������� �����, �� ����� ������� �� ������� � �������, �� �� ��� ����������
    _CLEAR_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_NZZ);
    _CLEAR_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_NZZ);
    _CLEAR_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_3I0);
    _CLEAR_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_3I0);
    _CLEAR_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_3U0);
    _CLEAR_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_3U0);

    global_timers[INDEX_TIMER_NZZ   ] = -1;
    global_timers[INDEX_TIMER_ZZ_3U0] = -1;
    global_timers[INDEX_TIMER_ZZ_3I0] = -1;
  }  
}
/*****************************************************/

/*****************************************************/
// ���(���)
/*****************************************************/
inline void zop_handler(unsigned int *activated_functions, unsigned int number_group_stp)
{
  /*******************************/
  //������� � �������� ����� ������ ������ ��������� ����������� � ����������������
  /*******************************/
  unsigned int i2_current = measurement[IM_I2], i1_current = measurement[IM_I1];
  /*******************************/
  
  /*******************************/
  //1 ������ ���(���)
  /*******************************/
  if ((current_settings_prt.control_zop & CTR_ZOP_STATE) != 0)
  {
    //1 ������ ���(���) ��������
    unsigned int setpoint; //������� - � ���� ���������� ����������� ��������
    unsigned int setpoint_i1, setpoint_i2;
    unsigned int previous_state_po_zop1;
    
    if (i1_bilshe_porogu == 0) setpoint_i1 = MIN_LIMIT_FOR_I1_AND_I2*KOEF_POVERNENNJA_ZOP_BLK/100;
    else setpoint_i1 = MIN_LIMIT_FOR_I1_AND_I2;
    unsigned int i1_bilshe_porogu_tmp = i1_bilshe_porogu = (i1_current >= setpoint_i1);
    
    if (i2_bilshe_porogu == 0) setpoint_i2 = MIN_LIMIT_FOR_I1_AND_I2*KOEF_POVERNENNJA_ZOP_BLK/100;
    else setpoint_i2 = MIN_LIMIT_FOR_I1_AND_I2;
    unsigned int i2_bilshe_porogu_tmp = i2_bilshe_porogu = (i2_current >= setpoint_i2);
    
    //������� �������� �������� ������� ���(���) � ���������� �����, ��� ���� ���� ��������� �� ������� ��� �������������
    //�� ������� ��� ����, ��� ���� � �����, �� ������ �� �� � ��������������� � ��������� - ��� �� ������� ��� �������� ��������  
    unsigned int maska[N_BIG] = {0, 0, 0, 0, 0, 0};
    _SET_BIT(maska, RANG_OUTPUT_LED_DF_REG_PO_ZOP);
    _SET_BIT(maska, RANG_OUTPUT_LED_DF_REG_ZOP);
    activated_functions[0] |= active_functions[0] & maska[0];
    activated_functions[1] |= active_functions[1] & maska[1];
    activated_functions[2] |= active_functions[2] & maska[2];
    activated_functions[3] |= active_functions[3] & maska[3];
    activated_functions[4] |= active_functions[4] & maska[4];
    activated_functions[5] |= active_functions[5] & maska[5];
    
    //���� �� ���(���) �� �� �������, �� ����� ��������� �� ������ ���������� - �������, ��� ��������� �� ������� � ������� ���� �� ��������� ����
    //���� �� ���(���) ��� ����������, �� ����� ��������� �� ������� ���������� - �������� ������� �� ������� ������ �� ����������� ����������
    if(( previous_state_po_zop1 = _CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_PO_ZOP) ) == 0 )
    {
      //�������� �� ������ �����������
      setpoint = current_settings_prt.setpoint_zop[number_group_stp];
    }
    else
    {
      //�������� �� ������ ����������
      setpoint = current_settings_prt.setpoint_zop[number_group_stp]*KOEF_POVERNENNJA_GENERAL_UP/100;
    }
    
    //�����������, ��� ������� ������ "�� ���"
    /*
    I2
    -- >= K
    I1
    ������� �������� ������ � ��� � ����������� �� 1000, ,�� 0,010 ������� 10, � 1,000 ������� 1000,
    �� K*1000 = SETPOINT =>
        SETPOINT
    K = --------  =>
         1000
    I2    SETPOINT
    -- >= ---------
    I1     1000
    
    ������ ��������� � ����� ����������� �� ����� � ���� �������������, �� ���� � � ��������� ��������� (��������), � ��� �������� �� ���������
    
    (I2*1000) >= (SETPOINT*I1)
    */
    if (
        (i1_bilshe_porogu_tmp != 0) &&
        (i2_bilshe_porogu_tmp != 0) &&
        ((i2_current*1000) >= (i1_current*setpoint))                            && 
        (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_BLOCK_ZOP) == 0)
       )
    {
      //���� ����� ��������� ��������� ������ ��������� �����������
      if(previous_state_po_zop1 == 0)
      {
        //������������ ������ "�� ���"
        _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_ZOP);
      
        //��������� ������ ���(���), ���� �� �� �� ���������
        global_timers[INDEX_TIMER_ZOP] = 0;
      }
    }
    else 
    {
      //�� ���� ����� ��������� ��������� ������ ��������� �����������
      if(previous_state_po_zop1 != 0)
      {
        //������� ������ "�� ���"
        _CLEAR_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_ZOP);
        //�� � ������ ����� �������� ������� "����. ���"
        _CLEAR_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_ZOP);
        //���� ������ �� �� ��������? �� ������� ����
        if ( global_timers[INDEX_TIMER_ZOP] >=0) global_timers[INDEX_TIMER_ZOP] = -1;
      }
    }
    
    if(global_timers[INDEX_TIMER_ZOP] >= current_settings_prt.timeout_zop[number_group_stp])
    {
      //���� ��������� �������� ���(���) �� ������������ ������ "����. ���"
      _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_ZOP);

      //������� ������ ���(���)
      global_timers[INDEX_TIMER_ZOP] = -1;
    }
  }
  else
  {
    //���� 1 ������ ���(���) �� �����������, �� ����� ������� �� ������� � �������, �� �� �� ����������
    if(( _CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_PO_ZOP) ) !=0 )
    {
      _CLEAR_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_ZOP);
      global_timers[INDEX_TIMER_ZOP] = -1;
    }
    _CLEAR_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_ZOP);
  }  
}
/*****************************************************/

/*****************************************************/
// �����1
/*****************************************************/
void umin1_handler(unsigned int *activated_functions, unsigned int number_group_stp)
{
  _Bool previous_state_po_umin1 = _CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_PO_UMIN1) > 0;
  _Bool previous_state_po_ublk_umin1 = _CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_PO_UBLK_UMIN1) > 0;
  _Bool previous_state_po_iblk_umin1 = _CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_PO_IBLK_UMIN1) > 0;
  
  unsigned int setpoint1 = previous_state_po_umin1 ?
          current_settings_prt.setpoint_Umin1[number_group_stp] * U_DOWN / 100 :
          current_settings_prt.setpoint_Umin1[number_group_stp];
  
  _Bool Uab_is_smaller_than_Umin1 = measurement[IM_UAB] <= setpoint1;
  _Bool Ubc_is_smaller_than_Umin1 = measurement[IM_UBC] <= setpoint1;
  _Bool Uca_is_smaller_than_Umin1 = measurement[IM_UCA] <= setpoint1;
  
  _Bool Ua_is_smaller_than_Umin1 = measurement[IM_UA] <= setpoint1;
  _Bool Ub_is_smaller_than_Umin1 = measurement[IM_UB] <= setpoint1;
  _Bool Uc_is_smaller_than_Umin1 = measurement[IM_UC] <= setpoint1;
  
  unsigned int setpoint2 = previous_state_po_ublk_umin1 ?
          KOEF_MIN_UMIN * U_DOWN_1 / 100 : KOEF_MIN_UMIN;
          
  _Bool Ua_or_Ub_or_Uc_is_smaller_than_250mV = (measurement[IM_UA] <= setpoint2) || (measurement[IM_UB] <= setpoint2) || (measurement[IM_UC] <= setpoint2);
  _Bool Uab_or_Ubc_or_Uca_is_smaller_than_250mV = (measurement[IM_UAB] <= setpoint2) || (measurement[IM_UBC] <= setpoint2) || (measurement[IM_UCA] <= setpoint2);
  
  unsigned int setpoint3 = previous_state_po_iblk_umin1 ?
          current_settings_prt.setpoint_Umin1_Iblk[number_group_stp] * KOEF_POVERNENNJA_GENERAL_DOWN / 100 :
          current_settings_prt.setpoint_Umin1_Iblk[number_group_stp];
  
  _Bool Ia_and_Ic_is_smaller_than_Iust = (measurement[IM_IA] <= setpoint3) &&
                                       (measurement[IM_IC] <= setpoint3);
  //�
  unsigned int tmp_value = ((current_settings_prt.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_PHASE_LINE) == 0)         << 0;
//  tmp_value |= ((current_settings_prt.control_Umin & CTR_EXTRA_SETTINGS_1_CTRL_PHASE_LINE) != 0)                                 << 1;
//  _INVERTOR(tmp_value, 1, tmp_value, 1);
  tmp_value |= ((current_settings_prt.control_Umin & CTR_UMIN1) != 0)                                                            << 2;
  tmp_value |= ((current_settings_prt.control_Umin & CTR_PO_UMIN1_OR_AND) != 0)                                                  << 3;
  tmp_value |= ((current_settings_prt.control_Umin & CTR_UMIN1_UBLK) != 0)                                                       << 4;
  tmp_value |= ((current_settings_prt.control_Umin & CTR_UMIN1_IBLK) != 0)                                                       << 5;
  
  //��
  tmp_value |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_BLOCK_UMIN1) != 0)                                    << 6;
  _INVERTOR(tmp_value, 6, tmp_value, 6);
  tmp_value |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_START_UMIN1) != 0)                                    << 7;
  
//  _AND2(tmp_value, 0, tmp_value, 1, tmp_value, 8);
  
  if (_GET_OUTPUT_STATE(tmp_value, 0)) {
    //������
    _AND4(Ua_is_smaller_than_Umin1, 0, Ub_is_smaller_than_Umin1, 0, Uc_is_smaller_than_Umin1, 0, tmp_value, 3, tmp_value, 9);
    _OR3(Ua_is_smaller_than_Umin1, 0, Ub_is_smaller_than_Umin1, 0, Uc_is_smaller_than_Umin1, 0, tmp_value, 10);
    _INVERTOR(tmp_value, 3, tmp_value, 3);
    _AND2(tmp_value, 10, tmp_value, 3, tmp_value, 11);
    _AND2(tmp_value, 5, Ia_and_Ic_is_smaller_than_Iust, 0, tmp_value, 12);
    _INVERTOR(tmp_value, 5, tmp_value, 5);
    _AND3(Ua_or_Ub_or_Uc_is_smaller_than_250mV, 0, tmp_value, 4, tmp_value, 5, tmp_value, 13);
    
    //�� U���. Umin1
    if (Ua_or_Ub_or_Uc_is_smaller_than_250mV) {
      _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_UBLK_UMIN1);
    }
    
  } else {
    //��������
    _AND4(Uab_is_smaller_than_Umin1, 0, Ubc_is_smaller_than_Umin1, 0, Uca_is_smaller_than_Umin1, 0, tmp_value, 3, tmp_value, 9);
    _OR3(Uab_is_smaller_than_Umin1, 0, Ubc_is_smaller_than_Umin1, 0, Uca_is_smaller_than_Umin1, 0, tmp_value, 10);
    _INVERTOR(tmp_value, 3, tmp_value, 3);
    _AND2(tmp_value, 10, tmp_value, 3, tmp_value, 11);
    _AND2(tmp_value, 5, Ia_and_Ic_is_smaller_than_Iust, 0, tmp_value, 12);
    _INVERTOR(tmp_value, 5, tmp_value, 5);
    _AND3(Uab_or_Ubc_or_Uca_is_smaller_than_250mV, 0, tmp_value, 4, tmp_value, 5, tmp_value, 13);
    
    //�� U���. Umin1
    if (Uab_or_Ubc_or_Uca_is_smaller_than_250mV) {
      _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_UBLK_UMIN1);
    }
  }
  _INVERTOR(tmp_value, 12, tmp_value, 12);
  _INVERTOR(tmp_value, 13, tmp_value, 13);
  _OR3(tmp_value, 7, tmp_value, 9, tmp_value, 11, tmp_value, 14);
  
  _AND5(tmp_value, 6, tmp_value, 2, tmp_value, 14, tmp_value, 13, tmp_value, 12, tmp_value, 15);
  
  //�� I���. Umin1
  if (Ia_and_Ic_is_smaller_than_Iust) {
    _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_IBLK_UMIN1);
  }
  
  //�� Umin1
  if (_GET_OUTPUT_STATE(tmp_value, 15)) {
    _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_UMIN1);
  }
  
  _TIMER_T_0(INDEX_TIMER_UMIN1, current_settings_prt.timeout_Umin1[number_group_stp], tmp_value, 15, tmp_value, 16);
  
  //����. Umin1
  if (_GET_OUTPUT_STATE(tmp_value, 16)) {
    _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_UMIN1);
  }
}
/*****************************************************/

/*****************************************************/
// �����2
/*****************************************************/
void umin2_handler(unsigned int *activated_functions, unsigned int number_group_stp)
{
  _Bool previous_state_po_umin2 = _CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_PO_UMIN2) > 0;
  _Bool previous_state_po_ublk_umin2 = _CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_PO_UBLK_UMIN2) > 0;
  _Bool previous_state_po_iblk_umin2 = _CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_PO_IBLK_UMIN2) > 0;
  
  unsigned int setpoint1 = previous_state_po_umin2 ?
          current_settings_prt.setpoint_Umin2[number_group_stp] * U_DOWN / 100 :
          current_settings_prt.setpoint_Umin2[number_group_stp];
  
  _Bool Uab_is_smaller_than_Umin2 = measurement[IM_UAB] <= setpoint1;
  _Bool Ubc_is_smaller_than_Umin2 = measurement[IM_UBC] <= setpoint1;
  _Bool Uca_is_smaller_than_Umin2 = measurement[IM_UCA] <= setpoint1;
  
  _Bool Ua_is_smaller_than_Umin2 = measurement[IM_UA] <= setpoint1;
  _Bool Ub_is_smaller_than_Umin2 = measurement[IM_UB] <= setpoint1;
  _Bool Uc_is_smaller_than_Umin2 = measurement[IM_UC] <= setpoint1;
  
  unsigned int setpoint2 = previous_state_po_ublk_umin2 ?
          KOEF_MIN_UMIN * U_DOWN_1 / 100 : KOEF_MIN_UMIN;
          
  _Bool Ua_or_Ub_or_Uc_is_smaller_than_250mV = (measurement[IM_UA] <= setpoint2) || (measurement[IM_UB] <= setpoint2) || (measurement[IM_UC] <= setpoint2);
  _Bool Uab_or_Ubc_or_Uca_is_smaller_than_250mV = (measurement[IM_UAB] <= setpoint2) || (measurement[IM_UBC] <= setpoint2) || (measurement[IM_UCA] <= setpoint2);
  
  unsigned int setpoint3 = previous_state_po_iblk_umin2 ?
          current_settings_prt.setpoint_Umin2_Iblk[number_group_stp] * KOEF_POVERNENNJA_GENERAL_DOWN / 100 :
          current_settings_prt.setpoint_Umin2_Iblk[number_group_stp];
  
  _Bool Ia_and_Ic_is_smaller_than_Iust = (measurement[IM_IA] <= setpoint3) &&
                                       (measurement[IM_IC] <= setpoint3);
  //�
  unsigned int tmp_value = ((current_settings_prt.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_PHASE_LINE) == 0)         << 0;
//  tmp_value |= ((current_settings_prt.control_Umin & CTR_EXTRA_SETTINGS_1_CTRL_PHASE_LINE) != 0)                                 << 1;
//  _INVERTOR(tmp_value, 1, tmp_value, 1);
  tmp_value |= ((current_settings_prt.control_Umin & CTR_UMIN2) != 0)                                                            << 2;
  tmp_value |= ((current_settings_prt.control_Umin & CTR_PO_UMIN2_OR_AND) != 0)                                                  << 3;
  tmp_value |= ((current_settings_prt.control_Umin & CTR_UMIN2_UBLK) != 0)                                                       << 4;
  tmp_value |= ((current_settings_prt.control_Umin & CTR_UMIN2_IBLK) != 0)                                                       << 5;
  
  //��
  tmp_value |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_BLOCK_UMIN2) != 0)                                    << 6;
  _INVERTOR(tmp_value, 6, tmp_value, 6);
  tmp_value |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_START_UMIN2) != 0)                                    << 7;
  
//  _AND2(tmp_value, 0, tmp_value, 1, tmp_value, 8);
  
  if (_GET_OUTPUT_STATE(tmp_value, 0)) {
    //������
    _AND4(Ua_is_smaller_than_Umin2, 0, Ub_is_smaller_than_Umin2, 0, Uc_is_smaller_than_Umin2, 0, tmp_value, 3, tmp_value, 9);
    _OR3(Ua_is_smaller_than_Umin2, 0, Ub_is_smaller_than_Umin2, 0, Uc_is_smaller_than_Umin2, 0, tmp_value, 10);
    _INVERTOR(tmp_value, 3, tmp_value, 3);
    _AND2(tmp_value, 10, tmp_value, 3, tmp_value, 11);
    _AND2(tmp_value, 5, Ia_and_Ic_is_smaller_than_Iust, 0, tmp_value, 12);
    _INVERTOR(tmp_value, 5, tmp_value, 5);
    _AND3(Ua_or_Ub_or_Uc_is_smaller_than_250mV, 0, tmp_value, 4, tmp_value, 5, tmp_value, 13);
    
    //�� U���. Umin2
    if (Ua_or_Ub_or_Uc_is_smaller_than_250mV) {
      _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_UBLK_UMIN2);
    }
    
  } else {
    //��������
    _AND4(Uab_is_smaller_than_Umin2, 0, Ubc_is_smaller_than_Umin2, 0, Uca_is_smaller_than_Umin2, 0, tmp_value, 3, tmp_value, 9);
    _OR3(Uab_is_smaller_than_Umin2, 0, Ubc_is_smaller_than_Umin2, 0, Uca_is_smaller_than_Umin2, 0, tmp_value, 10);
    _INVERTOR(tmp_value, 3, tmp_value, 3);
    _AND2(tmp_value, 10, tmp_value, 3, tmp_value, 11);
    _AND2(tmp_value, 5, Ia_and_Ic_is_smaller_than_Iust, 0, tmp_value, 12);
    _INVERTOR(tmp_value, 5, tmp_value, 5);
    _AND3(Uab_or_Ubc_or_Uca_is_smaller_than_250mV, 0, tmp_value, 4, tmp_value, 5, tmp_value, 13);
    
    //�� U���. Umin2
    if (Uab_or_Ubc_or_Uca_is_smaller_than_250mV) {
      _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_UBLK_UMIN2);
    }
  }
  _INVERTOR(tmp_value, 12, tmp_value, 12);
  _INVERTOR(tmp_value, 13, tmp_value, 13);
  _OR3(tmp_value, 7, tmp_value, 9, tmp_value, 11, tmp_value, 14);
  
  _AND5(tmp_value, 6, tmp_value, 2, tmp_value, 14, tmp_value, 13, tmp_value, 12, tmp_value, 15);
  
  //�� I���. Umin2
  if (Ia_and_Ic_is_smaller_than_Iust) {
    _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_IBLK_UMIN2);
  }
  
  //�� Umin2
  if (_GET_OUTPUT_STATE(tmp_value, 15)) {
    _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_UMIN2);
  }
  
  _TIMER_T_0(INDEX_TIMER_UMIN2, current_settings_prt.timeout_Umin2[number_group_stp], tmp_value, 15, tmp_value, 16);
  
  //����. Umin2
  if (_GET_OUTPUT_STATE(tmp_value, 16)) {
    _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_UMIN2);
  }
}
/*****************************************************/

/*****************************************************/
// ������1
/*****************************************************/
void umax1_handler(unsigned int *activated_functions, unsigned int number_group_stp)
{
  _Bool previous_state_po_umax1 = _CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_PO_UMAX1) > 0;
  
  unsigned int setpoint1 = previous_state_po_umax1 ?
          current_settings_prt.setpoint_Umax1[number_group_stp] * U_UP_UMAX / 100 :
          current_settings_prt.setpoint_Umax1[number_group_stp];
  
  _Bool Uab_is_larger_than_Umax1 = measurement[IM_UAB] >= setpoint1;
  _Bool Ubc_is_larger_than_Umax1 = measurement[IM_UBC] >= setpoint1;
  _Bool Uca_is_larger_than_Umax1 = measurement[IM_UCA] >= setpoint1;
  
  _Bool Ua_is_larger_than_Umax1 = measurement[IM_UA] >= setpoint1;
  _Bool Ub_is_larger_than_Umax1 = measurement[IM_UB] >= setpoint1;
  _Bool Uc_is_larger_than_Umax1 = measurement[IM_UC] >= setpoint1;
  
  //�
  unsigned int tmp_value = ((current_settings_prt.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_PHASE_LINE) == 0)         << 0;
//  tmp_value |= ((current_settings_prt.control_Umax & CTR_EXTRA_SETTINGS_1_CTRL_PHASE_LINE) != 0)                                 << 1;
//  _INVERTOR(tmp_value, 1, tmp_value, 1);
  tmp_value |= ((current_settings_prt.control_Umax & CTR_PO_UMAX1_OR_AND) != 0)                                                  << 2;
  tmp_value |= ((current_settings_prt.control_Umax & CTR_UMAX1) != 0)                                                            << 3;
  
  //��
  tmp_value |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_BLOCK_UMAX1) != 0)                                    << 4;
  
  if (_GET_OUTPUT_STATE(tmp_value, 0)) {
    _AND4(Ua_is_larger_than_Umax1, 0, Ub_is_larger_than_Umax1, 0, Uc_is_larger_than_Umax1, 0, tmp_value, 2, tmp_value, 5);
    _OR3(Ua_is_larger_than_Umax1, 0, Ub_is_larger_than_Umax1, 0, Uc_is_larger_than_Umax1, 0, tmp_value, 6);
  } else {
    _AND4(Uab_is_larger_than_Umax1, 0, Ubc_is_larger_than_Umax1, 0, Uca_is_larger_than_Umax1, 0, tmp_value, 2, tmp_value, 5);
    _OR3(Uab_is_larger_than_Umax1, 0, Ubc_is_larger_than_Umax1, 0, Uca_is_larger_than_Umax1, 0, tmp_value, 6);
  }
  
  _INVERTOR(tmp_value, 2, tmp_value, 2);
  _AND2(tmp_value, 6, tmp_value, 2, tmp_value, 7);
  _OR2(tmp_value, 5, tmp_value, 7, tmp_value, 8);
  _INVERTOR(tmp_value, 4, tmp_value, 4);
  _AND3(tmp_value, 8, tmp_value, 4, tmp_value, 3, tmp_value, 9);
  
  //�� Umax1
  if (_GET_OUTPUT_STATE(tmp_value, 9)) {
    _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_UMAX1);
  }
  
  _TIMER_T_0(INDEX_TIMER_UMAX1, current_settings_prt.timeout_Umax1[number_group_stp], tmp_value, 9, tmp_value, 10);
  
  //����. Umax1
  if (_GET_OUTPUT_STATE(tmp_value, 10)) {
    _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_UMAX1);
  }
}
/*****************************************************/

/*****************************************************/
// ������2
/*****************************************************/
void umax2_handler(unsigned int *activated_functions, unsigned int number_group_stp)
{
  _Bool previous_state_po_umax2 = _CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_PO_UMAX2) > 0;
  
  unsigned int setpoint1 = previous_state_po_umax2 ?
          current_settings_prt.setpoint_Umax2[number_group_stp] * U_UP_UMAX / 100 :
          current_settings_prt.setpoint_Umax2[number_group_stp];
  
  _Bool Uab_is_larger_than_Umax2 = measurement[IM_UAB] >= setpoint1;
  _Bool Ubc_is_larger_than_Umax2 = measurement[IM_UBC] >= setpoint1;
  _Bool Uca_is_larger_than_Umax2 = measurement[IM_UCA] >= setpoint1;
  
  _Bool Ua_is_larger_than_Umax2 = measurement[IM_UA] >= setpoint1;
  _Bool Ub_is_larger_than_Umax2 = measurement[IM_UB] >= setpoint1;
  _Bool Uc_is_larger_than_Umax2 = measurement[IM_UC] >= setpoint1;
  
  //�
  unsigned int tmp_value = ((current_settings_prt.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_PHASE_LINE) == 0)         << 0;
//  tmp_value |= ((current_settings_prt.control_Umax & CTR_EXTRA_SETTINGS_1_CTRL_PHASE_LINE) != 0)                                 << 1;
//  _INVERTOR(tmp_value, 1, tmp_value, 1);
  tmp_value |= ((current_settings_prt.control_Umax & CTR_PO_UMAX2_OR_AND) != 0)                                                  << 2;
  tmp_value |= ((current_settings_prt.control_Umax & CTR_UMAX2) != 0)                                                            << 3;
  
  //��
  tmp_value |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_BLOCK_UMAX2) != 0)                                    << 4;
  
  if (_GET_OUTPUT_STATE(tmp_value, 0)) {
    _AND4(Ua_is_larger_than_Umax2, 0, Ub_is_larger_than_Umax2, 0, Uc_is_larger_than_Umax2, 0, tmp_value, 2, tmp_value, 5);
    _OR3(Ua_is_larger_than_Umax2, 0, Ub_is_larger_than_Umax2, 0, Uc_is_larger_than_Umax2, 0, tmp_value, 6);
  } else {
    _AND4(Uab_is_larger_than_Umax2, 0, Ubc_is_larger_than_Umax2, 0, Uca_is_larger_than_Umax2, 0, tmp_value, 2, tmp_value, 5);
    _OR3(Uab_is_larger_than_Umax2, 0, Ubc_is_larger_than_Umax2, 0, Uca_is_larger_than_Umax2, 0, tmp_value, 6);
  }
  
  _INVERTOR(tmp_value, 2, tmp_value, 2);
  _AND2(tmp_value, 6, tmp_value, 2, tmp_value, 7);
  _OR2(tmp_value, 5, tmp_value, 7, tmp_value, 8);
  _INVERTOR(tmp_value, 4, tmp_value, 4);
  _AND3(tmp_value, 8, tmp_value, 4, tmp_value, 3, tmp_value, 9);
  
  //�� Umax1
  if (_GET_OUTPUT_STATE(tmp_value, 9)) {
    _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_UMAX2);
  }
  
  _TIMER_T_0(INDEX_TIMER_UMAX2, current_settings_prt.timeout_Umax2[number_group_stp], tmp_value, 9, tmp_value, 10);
  
  //����. Umax1
  if (_GET_OUTPUT_STATE(tmp_value, 10)) {
    _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_UMAX2);
  }
}
/*****************************************************/

/*****************************************************/
// ��� ���
/*****************************************************/
void apv_zmn_handler(unsigned int *activated_functions, unsigned int number_group_stp)
{
  _Bool previous_state_uapv_zmn1 = _CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_PO_UAPV_ZMN1);
  _Bool previous_state_uapv_zmn2 = _CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_PO_UAPV_ZMN2);
  
  unsigned int setpoint1 = previous_state_uapv_zmn1 ?
          current_settings_prt.setpoint_apv_zmn1[number_group_stp] * U_UP / 100 :
          current_settings_prt.setpoint_apv_zmn1[number_group_stp];
  
  _Bool Uab_and_Ubc_is_larger_than_Uapvzmn1 = (measurement[IM_UAB] >= setpoint1) &&
                                              (measurement[IM_UBC] >= setpoint1);
  
  unsigned int setpoint2 = previous_state_uapv_zmn2 ?
          current_settings_prt.setpoint_apv_zmn2[number_group_stp] * U_UP / 100 :
          current_settings_prt.setpoint_apv_zmn2[number_group_stp];
  
  _Bool Uab2_is_larger_than_Uapvzmn2 = measurement[IM_UAB_TN2] >= setpoint2;
  _Bool Ubc2_is_larger_than_Uapvzmn2 = measurement[IM_3U0_UBC_TN2] >= setpoint2;
  
  unsigned int tmp_value = (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_MTZ1) != 0)                       << 0;
  tmp_value |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_MTZ2) != 0)                                   << 1;
  tmp_value |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_MTZ3) != 0)                                   << 2;
  tmp_value |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_MTZ4) != 0)                                   << 3;
  tmp_value |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_3I0) != 0)                                    << 4;
  tmp_value |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_UROV1) != 0)                                  << 5;
  tmp_value |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_UROV2) != 0)                                  << 6;
  tmp_value |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_ZOP) != 0)                                    << 7;
  _Bool _3U0 = _CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_3U0);
  _Bool NZZ = _CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_NZZ);
  _Bool ACHR = _CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_ACHR_CHAPV);
  _Bool UMAX1 = _CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_UMAX1);
  _Bool UMAX2 = _CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_UMAX2);
  
  tmp_value |= (_CHECK_SET_BIT(active_functions,    RANG_OUTPUT_LED_DF_REG_WORK_BV) != 0)                                << 8;
  tmp_value |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_RESET_BLOCK_APV_ZMN) != 0)                    << 9;
//  tmp_value |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_RESET_KRATN_SPRAC_APV_ZMN) != 0)              << 10;
  
  //��
  tmp_value |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_BLOCK_APV_ZMN) != 0)                  << 11;
  
  tmp_value |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_STATE_VV) == 0)                       << 12;
  tmp_value |= (_CHECK_SET_BIT(active_functions,    RANG_OUTPUT_LED_DF_REG_WORK_BO) == 0)                        << 13;
  tmp_value |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_UMIN1) != 0)                          << 14;
  tmp_value |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_UMIN2) != 0)                          << 15;
  
  //�
  tmp_value |= ((current_settings_prt.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_3U0_Ubc_TN2) == 0)    << 16; //����� 3U0
  tmp_value |= ((current_settings_prt.control_apv_zmn & CTR_APV_ZMN) == 0)                                       << 17;
  
  //�� U ��� ���2
  if (_GET_OUTPUT_STATE(tmp_value, 16) /*�������� ������ 3U0*/) {
    if (Uab2_is_larger_than_Uapvzmn2) {
      _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_UAPV_ZMN2);
    }
  } else {
    if (Uab2_is_larger_than_Uapvzmn2 && Ubc2_is_larger_than_Uapvzmn2) {
      _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_UAPV_ZMN2);
    }
  }
  
  //�� U ��� ���1
  if (Uab_and_Ubc_is_larger_than_Uapvzmn1) {
    _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_UAPV_ZMN1);
  }
  
  _OR8(tmp_value, 0, tmp_value, 1, tmp_value, 2, tmp_value, 3, tmp_value, 4, tmp_value, 5, tmp_value, 6, tmp_value, 7, tmp_value, 7);
  _Bool _tmp_ = 0;
  _OR5(_3U0, 0, NZZ, 0, ACHR, 0, UMAX1, 0, UMAX2, 0, _tmp_, 0);
  _OR2(_tmp_, 0, tmp_value, 7, tmp_value, 7);
  _OR3(tmp_value, 8, tmp_value, 9, tmp_value, 17, tmp_value, 19);
  _D_TRIGGER(1,  0, _GET_OUTPUT_STATE(tmp_value, 19), previous_states_APV_ZMN_0, 0, tmp_value, 7, trigger_APV_ZMN_0, 0);
  
  //��.���-��� �� �.
  if (trigger_APV_ZMN_0) {
    _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_BLOCK_APV_ZMN_VID_ZAKHYSTIV);
  }
  
  if (_GET_OUTPUT_STATE(tmp_value, 16) /*�������� ������ 3U0*/) {
    _AND2(Uab_and_Ubc_is_larger_than_Uapvzmn1, 0, !Uab2_is_larger_than_Uapvzmn2, 0, tmp_value, 21);
    _AND2(Uab_and_Ubc_is_larger_than_Uapvzmn1, 0, Uab2_is_larger_than_Uapvzmn2, 0, tmp_value, 22);
    _AND2(!Uab_and_Ubc_is_larger_than_Uapvzmn1, 0, Uab2_is_larger_than_Uapvzmn2, 0, tmp_value, 23);
  } else {
    bool bool_value = Uab2_is_larger_than_Uapvzmn2 && Ubc2_is_larger_than_Uapvzmn2;
    _AND2(Uab_and_Ubc_is_larger_than_Uapvzmn1, 0, !bool_value, 0, tmp_value, 21);
    _AND2(Uab_and_Ubc_is_larger_than_Uapvzmn1, 0, bool_value, 0, tmp_value, 22);
    _AND2(!Uab_and_Ubc_is_larger_than_Uapvzmn1, 0, bool_value, 0, tmp_value, 23);
  }
  
  _OR3(trigger_APV_ZMN_0, 0, tmp_value, 11, tmp_value, 22, tmp_value, 24);
  _OR2_INVERTOR(tmp_value, 14, tmp_value, 15, tmp_value, 25);
    
  ////////////
  _Bool tmp = 0;
  do {
    _OR4(tmp_value, 24, tmp_value, 17, trigger_APV_ZMN_2, 0, previous_states_APV_ZMN_srab, 0, tmp_value, 26);
    _D_TRIGGER(1,  0, _GET_OUTPUT_STATE(tmp_value, 26), previous_states_APV_ZMN_1, 0, tmp_value, 25, trigger_APV_ZMN_1, 0);
    
//    if (trigger_APV_ZMN_1) {//��� �������
//      trigger_APV_ZMN_1 = 1;
//    } else {
//      trigger_APV_ZMN_1 = 0;
//    }
    
    _AND3(tmp_value, 12, tmp_value, 13, trigger_APV_ZMN_1, 0, tmp_value, 28);
    _AND2(tmp_value, 28, tmp_value, 21, tmp_value, 29);
    _AND2(tmp_value, 28, tmp_value, 23, tmp_value, 30);
    _OR2(tmp_value, 29, tmp_value, 30, tmp_value, 31);
    
    //�� ��� ���
    if (_GET_OUTPUT_STATE(tmp_value, 31)) {
      _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_APV_ZMN);
    }
    
    _TIMER_T_0(INDEX_TIMER_APV_ZMN1, current_settings_prt.timeout_apv_zmn_1[number_group_stp], tmp_value, 29, tmp_value, 0);
    _TIMER_T_0(INDEX_TIMER_APV_ZMN2, current_settings_prt.timeout_apv_zmn_2[number_group_stp], tmp_value, 30, tmp_value, 1);
    _OR2(tmp_value, 0, tmp_value, 1, tmp_value, 2);
    
    //����. ��� ���
    previous_states_APV_ZMN_srab = _GET_OUTPUT_STATE(tmp_value, 2);
    if (previous_states_APV_ZMN_srab) {
      _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_APV_ZMN);
    }
    
    _Bool tmr_apv_zmn_zavershennja = 0;
    _TIMER_T_0(INDEX_TIMER_APV_ZMN3, current_settings_prt.timeout_apv_zmn_zavershennja[number_group_stp],
               !previous_states_APV_ZMN_srab, 0, tmr_apv_zmn_zavershennja, 0);
    
    _Bool reset_counter = 0;
    _OR3(tmp_value, 9, tmr_apv_zmn_zavershennja, 0, trigger_APV_ZMN_2, 0, reset_counter, 0);
    
    _Bool counter_signal = 0;
    _COUNTER(_GET_OUTPUT_STATE(reset_counter, 0), previous_state_apv_zmn_counter, 0, previous_states_APV_ZMN_srab, 0,
             apv_zmn_counter, current_settings_prt.setpoint_kratn_apv_zmn[number_group_stp], counter_signal, 0);
    
    _D_TRIGGER(1, 0, _GET_OUTPUT_STATE(tmp_value, 9), previous_states_APV_ZMN_2, 0, counter_signal, 0, trigger_APV_ZMN_2, 0);
    
//    if (trigger_APV_ZMN_2) {//��� �������
//      trigger_APV_ZMN_2 = 1;
//    } else {
//      trigger_APV_ZMN_2 = 0;
//    }
    if (tmp == trigger_APV_ZMN_2) {
      break;
    }
    tmp = trigger_APV_ZMN_2;
  } while (1);
  /////////////
  
  //���������� �������� ���-���
  if (trigger_APV_ZMN_2) {
    _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_BLOCK_KRATN_APV_ZMN);
  }
  
}
/*****************************************************/

/*****************************************************/
// ���
/*****************************************************/
void avr_handler(unsigned int *activated_functions, unsigned int number_group_stp)
{
  _Bool previous_state_po_uavr_min1 = _CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_PO_UAVR_MIN1);
  _Bool previous_state_po_uavr_max1 = _CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_PO_UAVR_MAX1);
  _Bool previous_state_po_uavr_min2 = _CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_PO_UAVR_MIN2);
  _Bool previous_state_po_uavr_max2 = _CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_PO_UAVR_MAX2);
  
  unsigned int setpoint1 = previous_state_po_uavr_min1 ?
          current_settings_prt.setpoint_avr_min1[number_group_stp] * U_DOWN / 100 :
          current_settings_prt.setpoint_avr_min1[number_group_stp];
  
  _Bool Uab_and_Ubc_is_smaller_than_Uavrmin1 = (measurement[IM_UAB] <= setpoint1) &&
                                              (measurement[IM_UBC] <= setpoint1);
  
  unsigned int setpoint2 = previous_state_po_uavr_max1 ?
          current_settings_prt.setpoint_avr_max1[number_group_stp] * U_UP / 100 :
          current_settings_prt.setpoint_avr_max1[number_group_stp];
  
  _Bool Uab_and_Ubc_is_larger_than_Uavrmax1 = (measurement[IM_UAB] >= setpoint2) &&
                                              (measurement[IM_UBC] >= setpoint2);
  
  unsigned int setpoint3 = previous_state_po_uavr_min2 ?
          current_settings_prt.setpoint_avr_min2[number_group_stp] * U_DOWN / 100 :
          current_settings_prt.setpoint_avr_min2[number_group_stp];
  
  _Bool Uab2_is_smaller_than_Uavrmin2 = measurement[IM_UAB_TN2] <= setpoint3;
  _Bool Ubc2_is_smaller_than_Uavrmin2 = measurement[IM_3U0_UBC_TN2] <= setpoint3;
  
  unsigned int setpoint4 = previous_state_po_uavr_max2 ?
          current_settings_prt.setpoint_avr_max2[number_group_stp] * U_UP / 100 :
          current_settings_prt.setpoint_avr_max2[number_group_stp];
  
  _Bool Uab2_is_larger_than_Uavrmax2 = measurement[IM_UAB_TN2] >= setpoint4;
  _Bool Ubc2_is_larger_than_Uavrmax2 = measurement[IM_3U0_UBC_TN2] >= setpoint4;
  
  _Bool pryvid_vv = _CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PRYVID_VV);
  _Bool block_avr_vid_zovn_zakhystiv = _CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_OTKL_VID_ZOVN_ZAHYSTIV);
  _Bool vidkl_block_avr_vid_zahystiv = ((current_settings_prt.control_avr & CTR_AVR_OTKL_BLK_VID_ZAHYSTIV) != 0);
//  unsigned int tmp_value = (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_MTZ1) != 0)               << 0;
//  tmp_value |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_MTZ2) != 0)                           << 1;
//  tmp_value |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_MTZ3) != 0)                           << 2;
//  tmp_value |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_MTZ4) != 0)                           << 3;
  unsigned int tmp_value = (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_APV_WORK) != 0)           << 4;
  tmp_value |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_OTKL_VV) != 0)                        << 5;
  tmp_value |= (_CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_VIDKL_VID_ZAKHYSTIV) != 0)            << 6;
//  tmp_value |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_UMIN1) != 0)                          << 6;
//  tmp_value |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_UMIN2) != 0)                          << 7;
//  tmp_value |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_UMAX1) != 0)                          << 8;
//  tmp_value |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_UMAX2) != 0)                          << 9;
//  tmp_value |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_3I0) != 0)                            << 10;
  tmp_value |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_OTKL_AVR) != 0)                       << 11;
  tmp_value |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_SBROS_BLOCK_AVR) != 0)                << 12;
  tmp_value |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_STATE_VV) != 0)                       << 13;
  _INVERTOR(tmp_value, 13, tmp_value, 13);
  
  //��
  tmp_value |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_STAT_BLOCK_AVR) != 0)                 << 14;
  _INVERTOR(tmp_value, 14, tmp_value, 14);
  
  //�
  tmp_value |= ((current_settings_prt.control_avr & CTR_AVR) != 0)                                               << 15;
  tmp_value |= ((current_settings_prt.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_3U0_Ubc_TN2) == 0)    << 17; //����� 3U0
  
//  tmp_value |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_RESET_KRATN_SPRAC_AVR) != 0)          << 18;
  
  //�� U���min1
  if (Uab_and_Ubc_is_smaller_than_Uavrmin1) {
    _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_UAVR_MIN1);
  }
  
  //�� U���max1
  if (Uab_and_Ubc_is_larger_than_Uavrmax1) {
    _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_UAVR_MAX1);
  }
  
  if (_GET_OUTPUT_STATE(tmp_value, 17) /*�������� ������ 3U0*/) {
    //�� U���max2
    if (Uab2_is_larger_than_Uavrmax2) {
      _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_UAVR_MAX2);
    }
    //�� U�BPmin2
    if (Uab2_is_smaller_than_Uavrmin2) {
      _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_UAVR_MIN2);
    }
  } else {
    //�� U���max2
    if (Uab2_is_larger_than_Uavrmax2 && Ubc2_is_larger_than_Uavrmax2) {
      _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_UAVR_MAX2);
    }
    //�� U�BPmin2
    if (Uab2_is_smaller_than_Uavrmin2 && Ubc2_is_smaller_than_Uavrmin2) {
      _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_UAVR_MIN2);
    }
  }
  
//  _OR6(tmp_value, 0, tmp_value, 1, tmp_value, 2, tmp_value, 3, tmp_value, 4, tmp_value, 5, tmp_value, 19);
//  _OR6(tmp_value, 6, tmp_value, 7, tmp_value, 8, tmp_value, 9, tmp_value, 10, tmp_value, 11, tmp_value, 20);
  _OR6(tmp_value, 4, tmp_value, 5, tmp_value, 6, tmp_value, 11, block_avr_vid_zovn_zakhystiv, 0, pryvid_vv, 0, tmp_value, 21);
  
  if (_GET_OUTPUT_STATE(tmp_value, 17) /*�������� ������ 3U0*/) {
    _AND2(Uab_and_Ubc_is_smaller_than_Uavrmin1, 0, Uab2_is_larger_than_Uavrmax2, 0, tmp_value, 22);
    _AND2(Uab2_is_larger_than_Uavrmax2, 0, Uab_and_Ubc_is_larger_than_Uavrmax1, 0, tmp_value, 23);
    _AND2(Uab_and_Ubc_is_larger_than_Uavrmax1, 0, Uab2_is_smaller_than_Uavrmin2, 0, tmp_value, 24);
  } else {
    _Bool bool_value1 = Uab2_is_larger_than_Uavrmax2 && Ubc2_is_larger_than_Uavrmax2;
    _Bool bool_value2 = Uab2_is_smaller_than_Uavrmin2 && Ubc2_is_smaller_than_Uavrmin2;
    _AND2(Uab_and_Ubc_is_smaller_than_Uavrmin1, 0, bool_value1, 0, tmp_value, 22);
    _AND2(bool_value1, 0, Uab_and_Ubc_is_larger_than_Uavrmax1, 0, tmp_value, 23);
    _AND2(Uab_and_Ubc_is_larger_than_Uavrmax1, 0, bool_value2, 0, tmp_value, 24);
  }
  
  _Bool tmr_avr_reset_blk = 0;
  _TIMER_T_0(INDEX_TIMER_AVR_RESET_BLK, current_settings_prt.timeout_avr_reset_blk[number_group_stp],
               tmp_value, 23, tmr_avr_reset_blk, 0);
  
  _OR3(vidkl_block_avr_vid_zahystiv, 0, tmp_value, 12, tmr_avr_reset_blk, 0, tmp_value, 25);
  _D_TRIGGER(1,  0, _GET_OUTPUT_STATE(tmp_value, 25), previous_states_AVR_0, 0, tmp_value, 21, trigger_AVR_0, 0);
  
  //����. ��� �� �����
  if (_GET_OUTPUT_STATE(trigger_AVR_0, 0)) {
    _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_BLOCK_AVR_VID_ZAKHYSTIV);
  }
  
  _Bool tmp = 0;
  do {
    _AND5(!trigger_AVR_0, 0, tmp_value, 15, tmp_value, 13, tmp_value, 14, !trigger_AVR_1, 0, tmp_value, 27);
    _AND2(tmp_value, 27, tmp_value, 22, tmp_value, 29);
    _AND2(tmp_value, 27, tmp_value, 24, tmp_value, 30);
    _TIMER_T_0(INDEX_TIMER_AVR_RL, current_settings_prt.timeout_avr_rl[number_group_stp], tmp_value, 30, tmp_value, 31);
    _TIMER_T_0(INDEX_TIMER_AVR_OL, current_settings_prt.timeout_avr_ol[number_group_stp], tmp_value, 29, tmp_value, 0);
    _OR2(tmp_value, 31, tmp_value, 0, tmp_value, 1);
    //���� ���
    
    if (_GET_OUTPUT_STATE(tmp_value, 0 )) _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PUSK_AVR_1);
    if (_GET_OUTPUT_STATE(tmp_value, 31)) _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PUSK_AVR_2);
    _Bool pusk_avr = _GET_OUTPUT_STATE(tmp_value, 1);
    if (pusk_avr) {
      _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PUSK_AVR);
    }
    
    _Bool tmr_avr_zavershennja = 0;
    _TIMER_T_0(INDEX_TIMER_AVR_ZAVERSHENNJA, current_settings_prt.timeout_avr_zavershennja[number_group_stp],
               !pusk_avr, 0, tmr_avr_zavershennja, 0);
    
    _Bool reset_counter = 0;
    _OR3(tmp_value, 12, tmr_avr_zavershennja, 0, trigger_AVR_1, 0, reset_counter, 0);
    
    _Bool counter_signal = 0;
    _COUNTER(_GET_OUTPUT_STATE(reset_counter, 0), previous_state_avr_counter, 0, pusk_avr, 0,
             avr_counter, current_settings_prt.setpoint_kratn_avr[number_group_stp], counter_signal, 0);
    
    _D_TRIGGER(1, 0, _GET_OUTPUT_STATE(tmp_value, 12), previous_states_AVR_1, 0, counter_signal, 0, trigger_AVR_1, 0);
    if (tmp == trigger_AVR_1) {
      break;
    }
    tmp = trigger_AVR_1;
  } while(1);
  
  //���������� �������� ���
  if (trigger_AVR_1) {
    _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_BLOCK_KRATN_AVR);
  }
}
/*****************************************************/

/*****************************************************/
// ��� ����
/*****************************************************/
void achr_chapv_handler(unsigned int *activated_functions, unsigned int number_group_stp)
{
  _Bool previous_state_po_f1_achr = _CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_PO_F1_ACHR);
  _Bool previous_state_po_f1_chapv = _CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_PO_F1_CHAPV);
  _Bool previous_state_po_f2_achr = _CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_PO_F2_ACHR);
  _Bool previous_state_po_f2_chapv = _CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_PO_F2_CHAPV);
  
  unsigned int setpoint1 = previous_state_po_achr_chapv_uaf1 ?
          current_settings_prt.setpoint_achr_chapv_uf1[number_group_stp] * U_UP / 100 :
          current_settings_prt.setpoint_achr_chapv_uf1[number_group_stp];
  unsigned int setpoint2 = previous_state_po_achr_chapv_ubf1 ?
          current_settings_prt.setpoint_achr_chapv_uf1[number_group_stp] * U_UP / 100 :
          current_settings_prt.setpoint_achr_chapv_uf1[number_group_stp];
  unsigned int setpoint3 = previous_state_po_achr_chapv_ucf1 ?
          current_settings_prt.setpoint_achr_chapv_uf1[number_group_stp] * U_UP / 100 :
          current_settings_prt.setpoint_achr_chapv_uf1[number_group_stp];
  
  unsigned int setpoint4 = previous_state_po_achr_chapv_uaf2_uab2_ubc2 ?
          current_settings_prt.setpoint_achr_chapv_uf2[number_group_stp] * U_UP / 100 :
          current_settings_prt.setpoint_achr_chapv_uf2[number_group_stp];
  
  //��������
  _Bool Uab_is_larger_than_UF1 = measurement[IM_UAB] >= setpoint1;
  _Bool Ubc_is_larger_than_UF1 = measurement[IM_UBC] >= setpoint2;
  _Bool Uca_is_larger_than_UF1 = measurement[IM_UCA] >= setpoint3;
  
  //������
  _Bool Ua_is_larger_than_UF1 = measurement[IM_UA] >= setpoint1;
  _Bool Ub_is_larger_than_UF1 = measurement[IM_UB] >= setpoint2;
  _Bool Uc_is_larger_than_UF1 = measurement[IM_UC] >= setpoint3;
  
  _Bool Uab_is_larger_than_UF2 = measurement[IM_UAB_TN2] >= setpoint4;
  _Bool Ubc_is_larger_than_UF2 = measurement[IM_3U0_UBC_TN2] >= setpoint4;
  
  /*----------------����� ������/��������-------------------------------------*/
  _Bool UF1_phase = ((current_settings_prt.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_PHASE_LINE) == 0);
//  unsigned char select_phase_line = ((current_settings_prt.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_PHASE_LINE) != 0) << 0;
//  _INVERTOR(select_phase_line, 0, select_phase_line, 0);
//  select_phase_line |= ((current_settings_prt.control_achr_chapv & CTR_EXTRA_SETTINGS_1_CTRL_PHASE_LINE) != 0)                    << 1;
//  _INVERTOR(select_phase_line, 1, select_phase_line, 1);
//  _AND2(select_phase_line, 0, select_phase_line, 1, UF1_phase, 0);
  /*--------------------------------------------------------------------------*/
  
  /*----------------����� 3U0-------------------------------------------------*/
  _Bool _3U0_ = ((current_settings_prt.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_3U0_Ubc_TN2) == 0);
  /*--------------------------------------------------------------------------*/
  
  _Bool timer1 = 0;
  _Bool UF1_is_larger_than_U_setpoint_F1 = 0;
  _Bool UF1_is_smaller_than_U_setpoint_F1 = 0;
  if (UF1_phase) {
    //�� UAF1
    previous_state_po_achr_chapv_uaf1 = Ua_is_larger_than_UF1;
    //�� UBF1
    previous_state_po_achr_chapv_ubf1 = Ub_is_larger_than_UF1;
    //�� UCF1
    previous_state_po_achr_chapv_ucf1 = Uc_is_larger_than_UF1;
    _AND3(Ua_is_larger_than_UF1, 0, Ub_is_larger_than_UF1, 0, Uc_is_larger_than_UF1, 0, timer1, 0);
  } else {
    //�� UAF1
    previous_state_po_achr_chapv_uaf1 = Uab_is_larger_than_UF1;
    //�� UBF1
    previous_state_po_achr_chapv_ubf1 = Ubc_is_larger_than_UF1;
    //�� UCF1
    previous_state_po_achr_chapv_ucf1 = Uca_is_larger_than_UF1;
    _AND3(Uab_is_larger_than_UF1, 0, Ubc_is_larger_than_UF1, 0, Uca_is_larger_than_UF1, 0, timer1, 0);
  }
  _TIMER_T_0(INDEX_TIMER_ACHR_CHAPV_100MS_1, TIMEOUT_ACHR_CHAPV_100MS, timer1, 0, UF1_is_larger_than_U_setpoint_F1, 0);
  UF1_is_smaller_than_U_setpoint_F1 = !UF1_is_larger_than_U_setpoint_F1;
  
  _Bool timer2 = 0;
  _Bool UF2_is_larger_than_U_setpoint_F2 = 0;
  _Bool UF2_is_smaller_than_U_setpoint_F2 = 0;
  if (_3U0_) {
    timer2 = Uab_is_larger_than_UF2;
  } else {
    timer2 = Uab_is_larger_than_UF2 && Ubc_is_larger_than_UF2;
  }
  _TIMER_T_0(INDEX_TIMER_ACHR_CHAPV_100MS_2, TIMEOUT_ACHR_CHAPV_100MS, timer2, 0, UF2_is_larger_than_U_setpoint_F2, 0);
  UF2_is_smaller_than_U_setpoint_F2 = !UF2_is_larger_than_U_setpoint_F2;
  
  //�� UAF2 Uab2 Ubc2
  previous_state_po_achr_chapv_uaf2_uab2_ubc2 = UF2_is_larger_than_U_setpoint_F2;
  
  int F1 = (int) (frequency_val_1 * 100);
  int F2 = (int) (frequency_val_2 * 100);
  _Bool po_f1_achr_rab = F1 <= ((int)current_settings_prt.setpoint_achr_f_rab[number_group_stp]);
//  _Bool po_f1_achr_otp = F1 >= ((int)current_settings_prt.setpoint_achr_f_otp[number_group_stp]);
  _Bool po_f1_chapv_rab = F1 >= ((int)current_settings_prt.setpoint_chapv_f_rab[number_group_stp]);
//  _Bool po_f1_chapv_otp = F1 <= ((int)current_settings_prt.setpoint_chapv_f_otp[number_group_stp]);
  _Bool po_f2_achr_rab = F2 <= ((int)current_settings_prt.setpoint_achr_f_rab[number_group_stp]);
//  _Bool po_f2_achr_otp = F2 >= ((int)current_settings_prt.setpoint_achr_f_otp[number_group_stp]);
  _Bool po_f2_chapv_rab = F2 >= ((int)current_settings_prt.setpoint_chapv_f_rab[number_group_stp]);
//  _Bool po_f2_chapv_otp = F2 <= ((int)current_settings_prt.setpoint_chapv_f_otp[number_group_stp]);
  _Bool po_f1_achr = 0;
  _Bool po_f2_achr = 0;
  
  //��
  unsigned int tmp_value = (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_BLOCK_ACHR) != 0)                 << 0;
  _INVERTOR(tmp_value, 0, tmp_value, 0);
  
  //�
  tmp_value |= ((current_settings_prt.control_achr_chapv & CTR_ACHR) != 0)                                               << 1;
//  tmp_value |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_SBROS_CHAPV) != 0)                            << 2;
  
  _AND3_INVERTOR(tmp_value, 0, tmp_value, 1, UF1_is_larger_than_U_setpoint_F1, 0, tmp_value, 3);
  _AND3_INVERTOR(tmp_value, 0, tmp_value, 1, UF2_is_larger_than_U_setpoint_F2, 0, tmp_value, 4);
  
  if (!_GET_OUTPUT_STATE(tmp_value, 3)) {
    //�� ���1
    if (previous_state_po_f1_achr) {
//      if (!po_f1_achr_otp) {
      if (!po_f1_chapv_rab) {//����� �������� 1 ����� ��������� �� ��� ��� ���� �� ��������� po_f1_chapv_rab (������� ����������)
        _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_F1_ACHR);
        po_f1_achr = 1;
      }
    } else {
      if (po_f1_achr_rab) {
        _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_F1_ACHR);
        po_f1_achr = 1;
      }
    }
  }
  if (!_GET_OUTPUT_STATE(tmp_value, 4)) {
    //�� ���2
    if (previous_state_po_f2_achr) {
//      if (!po_f2_achr_otp) {
      if (!po_f2_chapv_rab) {//����� �������� 1 ����� ��������� �� ��� ��� ���� �� ��������� po_f2_chapv_rab (������� ����������)
        _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_F2_ACHR);
        po_f2_achr = 1;
      }
    } else {
      if (po_f2_achr_rab) {
        _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_F2_ACHR);
        po_f2_achr = 1;
      }
    }
  }
  
  //  if (previous_state_po_f1_achr) {
//    po_f1_achr = !po_f1_achr_otp;
//  } else {
//    po_f1_achr = po_f1_achr_rab;
//  }
//  if (previous_state_po_f1_chapv) {
//    po_f1_chapv = !po_f1_chapv_otp;
//  } else {
//    po_f1_chapv = po_f1_chapv_rab;
//  }
//  if (previous_state_po_f2_achr) {
//    po_f2_achr = !po_f2_achr_otp;
//  } else {
//    po_f2_achr = po_f2_achr_rab;
//  }
//  if (previous_state_po_f2_chapv) {
//    po_f2_chapv = !po_f2_chapv_otp;
//  } else {
//    po_f2_chapv = po_f2_chapv_rab;
//  }
  
  _TIMER_T_0(INDEX_TIMER_ACHR1, current_settings_prt.timeout_achr_1[number_group_stp], po_f1_achr, 0, tmp_value, 5);
  _TIMER_T_0(INDEX_TIMER_ACHR2, current_settings_prt.timeout_achr_2[number_group_stp], po_f2_achr, 0, tmp_value, 7);
  
//  //���/����1
//  if (_GET_OUTPUT_STATE(tmp_value, 5)) {
//    _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_ACHR_CHAPV_1);
//  }
//  
//  //���/����2
//  if (_GET_OUTPUT_STATE(tmp_value, 7)) {
//    _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_ACHR_CHAPV_2);
//  }
//  
//  _OR2(tmp_value, 5, tmp_value, 7, tmp_value, 20);
//  
//  //���� ���/����
//  if (_GET_OUTPUT_STATE(tmp_value, 20)) {
//    _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_ACHR_CHAPV);
//  }
  
  _AND2(UF1_is_larger_than_U_setpoint_F1, 0, UF2_is_smaller_than_U_setpoint_F2, 0, tmp_value, 9);
  _AND2(UF1_is_smaller_than_U_setpoint_F1, 0, UF2_is_larger_than_U_setpoint_F2, 0, tmp_value, 10);
  _OR2(tmp_value, 9, tmp_value, 10, tmp_value, 11);
  
  //���� ����
  if (_GET_OUTPUT_STATE(tmp_value, 11)) {
    _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_RAZR_CHAPV);
  }
  
  _Bool tmp1 = 0;
  do {
    _OR2(tmp_value, 3, !trigger_CHAPV1, 0, tmp_value, 30);
    
    //�� ����1
    _Bool po_f1_chapv = 0;
    if (previous_state_po_f1_chapv) {
      po_f1_chapv = !po_f1_achr_rab;
    } else {
      po_f1_chapv = po_f1_chapv_rab;
    }
    _Bool po_f1_chapv_tmp = (!_GET_OUTPUT_STATE(tmp_value, 30) && po_f1_chapv);
    if (po_f1_chapv_tmp) {
      _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_F1_CHAPV);
    }
    
    _TIMER_T_0(INDEX_TIMER_CHAPV1, current_settings_prt.timeout_chapv_1[number_group_stp], po_f1_chapv_tmp, 0, tmp_value, 6);
    _AND2(po_f1_achr, 0, !po_f1_chapv_tmp, 0, tmp_value, 12);
//    _Bool tmp__ = !_GET_OUTPUT_STATE(tmp_value, 13); //��� �������
    _OR2(tmp_value, 5, tmp_value, 6, tmp_value, 13);
//    if (tmp__ && _GET_OUTPUT_STATE(tmp_value, 13)) { //��� �������
//      tmp__ = 0;
//    }
//    _OR2(UF1_is_smaller_than_U_setpoint_F1, 0, tmp_value, 2, tmp_value, 14);
//    _D_TRIGGER(_GET_OUTPUT_STATE(tmp_value, 12), 0, _GET_OUTPUT_STATE(tmp_value, 14), previous_states_CHAPV1, 0, tmp_value, 13, trigger_CHAPV1, 0);
    _D_TRIGGER(_GET_OUTPUT_STATE(tmp_value, 12), 0, _GET_OUTPUT_STATE(UF1_is_smaller_than_U_setpoint_F1, 0), previous_states_CHAPV1, 0, tmp_value, 13, trigger_CHAPV1, 0);
    if (tmp1 == trigger_CHAPV1) {
      break;
    }
    tmp1 = trigger_CHAPV1;
  } while(1);
  
  _Bool tmp2 = 0;
  do {
    _OR2(tmp_value, 4, !trigger_CHAPV2, 0, tmp_value, 31);
    
    //�� ����2
    _Bool po_f2_chapv = 0;
    if (previous_state_po_f2_chapv) {
      po_f2_chapv = !po_f2_achr_rab;
    } else {
      po_f2_chapv = po_f2_chapv_rab;
    }
    _Bool po_f2_chapv_tmp = (!_GET_OUTPUT_STATE(tmp_value, 31) && po_f2_chapv);
    if (po_f2_chapv_tmp) {
      _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_F2_CHAPV);
    }
    
    _TIMER_T_0(INDEX_TIMER_CHAPV2, current_settings_prt.timeout_chapv_2[number_group_stp], po_f2_chapv_tmp, 0, tmp_value, 8);
    _AND2(po_f2_achr, 0, !po_f2_chapv_tmp, 0, tmp_value, 15);
    _OR2(tmp_value, 7, tmp_value, 8, tmp_value, 16);
//    _OR2(UF2_is_smaller_than_U_setpoint_F2, 0, tmp_value, 2, tmp_value, 17);
//    _D_TRIGGER(_GET_OUTPUT_STATE(tmp_value, 15), 0, _GET_OUTPUT_STATE(tmp_value, 17), previous_states_CHAPV2, 0, tmp_value, 16, trigger_CHAPV2, 0);
    _D_TRIGGER(_GET_OUTPUT_STATE(tmp_value, 15), 0, _GET_OUTPUT_STATE(UF2_is_smaller_than_U_setpoint_F2, 0), previous_states_CHAPV2, 0, tmp_value, 16, trigger_CHAPV2, 0);
    if (tmp2 == trigger_CHAPV2) {
      break;
    }
    tmp2 = trigger_CHAPV2;
  } while(1);
  
//  _AND2(trigger_CHAPV1, 0, UF2_is_smaller_than_U_setpoint_F2, 0, tmp_value, 21);
//  _AND2(trigger_CHAPV2, 0, UF1_is_smaller_than_U_setpoint_F1, 0, tmp_value, 22);
  _OR2(trigger_CHAPV1, 0, trigger_CHAPV2, 0, /*tmp_value, 21, tmp_value, 22,*/ tmp_value, 23);
  
  //���/����1
  if (_GET_OUTPUT_STATE(trigger_CHAPV1, 0/*tmp_value, 21*/)) {
    _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_F1_ACHR_CHAPV);
  }
  
  //���/����2
  if (_GET_OUTPUT_STATE(trigger_CHAPV2, 0/*tmp_value, 22*/)) {
    _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_F2_ACHR_CHAPV);
  }
  
  //���/����
  if (_GET_OUTPUT_STATE(tmp_value, 23)) {
    _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_ACHR_CHAPV);
  }
  
  _Bool chapv_timer_1ms = 0;
  _Bool razr_chapv_inv = 0;
  _TIMER_0_T(INDEX_TIMER_CHAPV_1MS, TIMEOUT_CHAPV_1MS, tmp_value, 23, chapv_timer_1ms, 0);
  _INVERTOR(tmp_value, 11, razr_chapv_inv, 0);
  _AND2(chapv_timer_1ms, 0, razr_chapv_inv, 0, tmp_value, 24);
  _TIMER_0_T(INDEX_TIMER_BLOCK_CHAPV_5MS, TIMEOUT_BLOCK_CHAPV_5MS, tmp_value, 24, tmp_value, 25);
  
  //Block CHAPV vid U
  if (_GET_OUTPUT_STATE(tmp_value, 25)) {
    _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_BLOCK_CHAPV_VID_U);
  }
}
/*****************************************************/

/**************************/
//�������� ���������� �������� �����
/**************************/
void control_U_OL(unsigned int *activated_functions, unsigned int number_group_stp)
{
  _Bool previous_state_po_u_ol = _CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_PO_U_OL);
  
  unsigned int setpoint = previous_state_po_u_ol ?
          current_settings_prt.setpoint_U_ol[number_group_stp] * U_UP / 100 :
          current_settings_prt.setpoint_U_ol[number_group_stp];
          
  _Bool Uab_is_larger_than_setpoint_u_ol = measurement[IM_UAB] >= setpoint;
  _Bool Ubc_is_larger_than_setpoint_u_ol = measurement[IM_UBC] >= setpoint;
  _Bool Uca_is_larger_than_setpoint_u_ol = measurement[IM_UCA] >= setpoint;
  
  _Bool Ua_is_larger_than_setpoint_u_ol = measurement[IM_UA] >= setpoint;
  _Bool Ub_is_larger_than_setpoint_u_ol = measurement[IM_UB] >= setpoint;
  _Bool Uc_is_larger_than_setpoint_u_ol = measurement[IM_UC] >= setpoint;
  
  /*----------------����� ������/��������-------------------------------------*/
  _Bool U_OL_phase = ((current_settings_prt.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_PHASE_LINE) == 0);
//  unsigned char select_phase_line = ((current_settings_prt.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_PHASE_LINE) != 0) << 0;
//  _INVERTOR(select_phase_line, 0, select_phase_line, 0);
//  select_phase_line |= ((current_settings_prt.control_achr_chapv & CTR_EXTRA_SETTINGS_1_CTRL_PHASE_LINE) != 0)                    << 1;
//  _INVERTOR(select_phase_line, 1, select_phase_line, 1);
//  _AND2(select_phase_line, 0, select_phase_line, 1, U_OL_phase, 0);
  /*--------------------------------------------------------------------------*/
  
  //�
  unsigned int tmp_value = ((current_settings_prt.control_control_U & CTR_U_OL) != 0) << 0;
  
  if (U_OL_phase) {
    _AND4(Ua_is_larger_than_setpoint_u_ol, 0, Ub_is_larger_than_setpoint_u_ol, 0, Uc_is_larger_than_setpoint_u_ol, 0, tmp_value, 0, tmp_value, 1);
  } else {
    _AND4(Uab_is_larger_than_setpoint_u_ol, 0, Ubc_is_larger_than_setpoint_u_ol, 0, Uca_is_larger_than_setpoint_u_ol, 0, tmp_value, 0, tmp_value, 1);
  }
  
  //�� U ��
  if (_GET_OUTPUT_STATE(tmp_value, 1)) {
    _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_U_OL);
  }
  
  _TIMER_T_0(INDEX_TIMER_U_OL1, current_settings_prt.timeout_U_ol[number_group_stp], tmp_value, 1, tmp_value, 2);
  _INVERTOR(tmp_value, 1, tmp_value, 1);
  _TIMER_T_0(INDEX_TIMER_U_OL2, current_settings_prt.timeout_U_ol[number_group_stp], tmp_value, 1, tmp_value, 3);
  
  unsigned int tmp = 0;
  _D_TRIGGER(0, _GET_OUTPUT_STATE(tmp_value, 2), _GET_OUTPUT_STATE(tmp_value, 3), tmp, 0, tmp, 0, trigger_u_ol, 0);
  
  //U ��
  if (trigger_u_ol) {
    _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_U_OL);
  }
}
/*****************************************************/

/*****************************************************/
// �������� ���������� ��������� �����
/*****************************************************/
void control_U_RL(unsigned int *activated_functions, unsigned int number_group_stp)
{
  _Bool previous_state_po_u_rl = _CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_PO_U_RL);
  
  unsigned int setpoint = previous_state_po_u_rl ?
          current_settings_prt.setpoint_U_rl[number_group_stp] * U_UP / 100 :
          current_settings_prt.setpoint_U_rl[number_group_stp];
          
  _Bool Uab_is_larger_than_setpoint_u_rl = measurement[IM_UAB_TN2] >= setpoint;
  _Bool Ubc_is_larger_than_setpoint_u_rl = measurement[IM_3U0_UBC_TN2] >= setpoint;
  
  if (measurement[IM_UAB_TN2] < setpoint) {
    Uab_is_larger_than_setpoint_u_rl = 0;
  } else {
    Uab_is_larger_than_setpoint_u_rl = 1;
  }
  
  /*----------------����� 3U0-------------------------------------------------*/
  _Bool _3U0_ = ((current_settings_prt.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_3U0_Ubc_TN2) == 0);
  /*--------------------------------------------------------------------------*/
  
  unsigned int tmp_value = 0;
  if (_3U0_) {
    tmp_value = Uab_is_larger_than_setpoint_u_rl;
  } else {
    tmp_value = (Uab_is_larger_than_setpoint_u_rl && Ubc_is_larger_than_setpoint_u_rl);
  }
  
  //�
  tmp_value |= ((current_settings_prt.control_control_U & CTR_U_RL) != 0) << 1;
  
  _AND2(tmp_value, 0, tmp_value, 1, tmp_value, 2);
  
  //�� U ��
  if (_GET_OUTPUT_STATE(tmp_value, 2)) {
    _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_U_RL);
  }
  
  _TIMER_T_0(INDEX_TIMER_U_RL1, current_settings_prt.timeout_U_rl[number_group_stp], tmp_value, 2, tmp_value, 3);
  _INVERTOR(tmp_value, 2, tmp_value, 2);
  _TIMER_T_0(INDEX_TIMER_U_RL2, current_settings_prt.timeout_U_rl[number_group_stp], tmp_value, 2, tmp_value, 4);
  
  unsigned int tmp = 0;
  _D_TRIGGER(0, _GET_OUTPUT_STATE(tmp_value, 3), _GET_OUTPUT_STATE(tmp_value, 4), tmp, 0, tmp, 0, trigger_u_rl, 0);
  
  //U ��
  if (trigger_u_rl) {
    _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_U_RL);
  }
}
/*****************************************************/

/*****************************************************/
// ���������� � ��
/*****************************************************/
void ready_tu(unsigned int *activated_functions)
{
  unsigned int tmp_value = (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PRYVID_VV) == 0)                  << 0;
  tmp_value |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_VIDKL_VID_ZAKHYSTIV) != 0)                    << 1;
  tmp_value |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_RESET_BLOCK_READY_TU_VID_ZAHYSTIV) != 0)      << 2;
  tmp_value |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_AVAR_DEFECT) == 0)                            << 3;
  tmp_value |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_MISCEVE_DYSTANCIJNE) == 0)                    << 6;
  
  _Bool ctrl_ready_tu = ((current_settings_prt.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_READY_TU) == 0);
  
  if (!previous_states_ready_tu && _GET_OUTPUT_STATE(tmp_value, 1)) {
    previous_states_ready_tu = 0;
  }
  
  _OR2(tmp_value, 2, ctrl_ready_tu, 0, tmp_value, 7);
  _D_TRIGGER(1, 0, _GET_OUTPUT_STATE(tmp_value, 7), previous_states_ready_tu, 0, tmp_value, 1, trigger_ready_tu, 0);
  
  _AND4(tmp_value, 0, tmp_value, 3, !trigger_ready_tu, 0, tmp_value, 6, tmp_value, 5);
  
  //���������� � ��
  if (_GET_OUTPUT_STATE(tmp_value, 5)) {
    _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_READY_TU);
  }
}
/*****************************************************/

/*****************************************************/
// ����
/*****************************************************/
inline void urov_handler(unsigned int *activated_functions, unsigned int number_group_stp)
{
  /*******************************/
  //��������� ������������ ������� ����� ��� ����
  /*******************************/
  unsigned int max_faze_current = measurement[IM_IA];
  if (max_faze_current < measurement[IM_IB_r]) max_faze_current = measurement[IM_IB_r];
  if (max_faze_current < measurement[IM_IC]) max_faze_current = measurement[IM_IC];
  /*******************************/
  
  /*******************************/
  if(
     (( current_settings_prt.control_urov & CTR_UROV_STATE) != 0) &&
     (
      ( ((current_settings_prt.control_urov & CTR_UROV_STARTED_FROM_MTZ1 ) != 0) && (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_MTZ1             ) != 0)) ||
      ( ((current_settings_prt.control_urov & CTR_UROV_STARTED_FROM_MTZ2 ) != 0) && (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_MTZ2             ) != 0)) ||
      ( ((current_settings_prt.control_urov & CTR_UROV_STARTED_FROM_MTZ3 ) != 0) && (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_MTZ3             ) != 0)) ||
      ( ((current_settings_prt.control_urov & CTR_UROV_STARTED_FROM_MTZ4 ) != 0) && (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_MTZ4             ) != 0)) ||
      ( ((current_settings_prt.control_urov & CTR_UROV_STARTED_FROM_ZDZ  ) != 0) && (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_ZDZ              ) != 0)) ||
      ( ((current_settings_prt.control_urov & CTR_UROV_STARTED_FROM_3I0  ) != 0) && (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_3I0              ) != 0)) ||
      ( ((current_settings_prt.control_urov & CTR_UROV_STARTED_FROM_3U0  ) != 0) && (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_3U0              ) != 0)) ||
      ( ((current_settings_prt.control_urov & CTR_UROV_STARTED_FROM_NZZ  ) != 0) && (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_NZZ              ) != 0)) ||
      ( ((current_settings_prt.control_urov & CTR_UROV_STARTED_FROM_ZOP1 ) != 0) && (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_ZOP              ) != 0)) ||
      ( ((current_settings_prt.control_urov & CTR_UROV_STARTED_FROM_UMIN1) != 0) && (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_UMIN1            ) != 0)) ||
      ( ((current_settings_prt.control_urov & CTR_UROV_STARTED_FROM_UMIN2) != 0) && (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_UMIN2            ) != 0)) ||
      ( ((current_settings_prt.control_urov & CTR_UROV_STARTED_FROM_UMAX1) != 0) && (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_UMAX1            ) != 0)) ||
      ( ((current_settings_prt.control_urov & CTR_UROV_STARTED_FROM_UMAX2) != 0) && (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_UMAX2            ) != 0)) ||
      ( ((current_settings_prt.control_urov & CTR_UROV_STARTED_FROM_ACHR ) != 0) && (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_ACHR_CHAPV       ) != 0)) ||
      (                                                                             (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PUSK_UROV_VID_DV ) != 0))
     )     
    )
  {
    //� ����� ������� ����
    
    unsigned int setpoint; //������� - � ���� ���������� ����������� ��������
    unsigned int previous_state_po_urov;
    
    //������� �������� �������� ������� ���� � ���������� �����, ��� ���� ���� ��������� �� ������� ��� �������������
    //�� ������� ��� ����, ��� ���� � �����, �� ������ �� �� � ��������������� � ��������� - ��� �� ������� ��� �������� ��������  
    unsigned int maska[N_BIG] = {0, 0, 0, 0, 0, 0};
    _SET_BIT(maska, RANG_OUTPUT_LED_DF_REG_PO_UROV);
    _SET_BIT(maska, RANG_OUTPUT_LED_DF_REG_UROV1);
    _SET_BIT(maska, RANG_OUTPUT_LED_DF_REG_UROV2);
    activated_functions[0] |= active_functions[0] & maska[0];
    activated_functions[1] |= active_functions[1] & maska[1];
    activated_functions[2] |= active_functions[2] & maska[2];
    activated_functions[3] |= active_functions[3] & maska[3];
    activated_functions[4] |= active_functions[4] & maska[4];
    activated_functions[5] |= active_functions[5] & maska[5];
    
    //���� �� ���� �� �� �������, �� ����� ��������� �� ������ ���������� - �������, ��� ��������� �� ������� � ������� ���� �� ��������� ����
    //���� �� ���� ��� ����������, �� ����� ��������� �� ������� ���������� - �������� ������� �� ������� ������ �� ����������� ����������
    if(( previous_state_po_urov = _CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_PO_UROV) ) ==0 )
    {
      //�������� �� ������ �����������
      setpoint = current_settings_prt.setpoint_urov[number_group_stp];
    }
    else
    {
      //�������� �� ������ ����������
      setpoint = current_settings_prt.setpoint_urov[number_group_stp]*KOEF_POVERNENNJA_GENERAL_UP/100;
    }
    
    //�����������, ��� ������� ������ "�� ����"
    if (max_faze_current >= setpoint)
    {
      //������������ ������ ���� �������� ���� �������
      if(previous_state_po_urov == 0)
      {
        //������������ ������ "�� ����"
        _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_UROV);
      
        //��������� ������� ����1 � ����2, ���� ���� �� �� �������
        global_timers[INDEX_TIMER_UROV1] = 0;
        global_timers[INDEX_TIMER_UROV2] = 0;
      }
    }
    else 
    {
      //������������ ������ ���� ����� �������
      if(previous_state_po_urov != 0)
      {
        //������� ������ "�� ����"
        _CLEAR_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_UROV);
        //�� � ������ ����� �������� ������� "����. ����1" � "����. ����2"
        _CLEAR_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_UROV1);
        _CLEAR_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_UROV2);
        //���� ������� �� �� ������, �� ������� ��
        if ( global_timers[INDEX_TIMER_UROV1] >=0) global_timers[INDEX_TIMER_UROV1] = -1;
        if ( global_timers[INDEX_TIMER_UROV2] >=0) global_timers[INDEX_TIMER_UROV2] = -1;
      }
    }
    
    //���������� �� ������ ����1 �������� �������� �� ��������
    if(global_timers[INDEX_TIMER_UROV1] >= current_settings_prt.timeout_urov_1[number_group_stp])
    {
      //���� ��������� �������� ����1 �� ������������ ������ "����. ����1"
      _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_UROV1);

      //������� ������ ����1
      global_timers[INDEX_TIMER_UROV1] = -1;
    }

    //���������� �� ������ ����2 �������� �������� �� ��������
    if(global_timers[INDEX_TIMER_UROV2] >= current_settings_prt.timeout_urov_2[number_group_stp])
    {
      //���� ��������� �������� ����2 �� ������������ ������ "����. ����2"
      _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_UROV2);

      //������� ������ ����2
      global_timers[INDEX_TIMER_UROV2] = -1;
    }
  }
  else
  {
    //���� 1 ������ ���� �� �����������, �� ����� ������� �� ������� � �������, �� �� �� ����������
    if(( _CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_PO_UROV) ) !=0 )
    {
      _CLEAR_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_UROV);
      global_timers[INDEX_TIMER_UROV1] = -1;
      global_timers[INDEX_TIMER_UROV2] = -1;
    }
    _CLEAR_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_UROV1);
    _CLEAR_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_UROV2);
  }  
}
  /*******************************/
/*****************************************************/

/*****************************************************/
//���
/*****************************************************/
inline void apv_handler(unsigned int *activated_functions, unsigned int number_group_stp)
{
  unsigned int logic_APV_0 = 0;
  unsigned int logic_APV_1 = 0;

  //������� ��������
  logic_APV_1 |= (start_restart != 0) << 19;
  //������� ����������� ��� ������� ��������
  start_restart = 0;

  //"�������� ����������"
  logic_APV_0 |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_STAT_BLK_APV) != 0) << 0;
  _INVERTOR(logic_APV_0, 0, logic_APV_0, 1);

  //�:"���� �� ���1"
  logic_APV_0 |= ((current_settings_prt.control_apv & CTR_APV_STARTED_FROM_MTZ1) != 0) << 2;
  //"���1"
  logic_APV_0 |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_MTZ1) != 0) << 3;
  _AND2(logic_APV_0, 2, logic_APV_0, 3, logic_APV_0, 4);

  //�:"���� �� ���2"
  logic_APV_0 |= ((current_settings_prt.control_apv & CTR_APV_STARTED_FROM_MTZ2) != 0) << 5;
  //"���2"
  logic_APV_0 |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_MTZ2) != 0) << 6;
  _AND2(logic_APV_0, 5, logic_APV_0, 6, logic_APV_0, 7);

  //�:"���� �� ���3"
  logic_APV_0 |= ((current_settings_prt.control_apv & CTR_APV_STARTED_FROM_MTZ3) != 0) << 8;
  //"���3"
  logic_APV_0 |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_MTZ3) != 0) << 9;
  _AND2(logic_APV_0, 8, logic_APV_0, 9, logic_APV_0, 10);

  //�:"���� �� ���4"
  logic_APV_0 |= ((current_settings_prt.control_apv & CTR_APV_STARTED_FROM_MTZ4) != 0) << 11;
  //"���4"
  logic_APV_0 |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_MTZ4) != 0) << 12;
  _AND2(logic_APV_0, 11, logic_APV_0, 12, logic_APV_0, 13);
  
  _OR4(logic_APV_0, 4, logic_APV_0, 7, logic_APV_0, 10, logic_APV_0, 13, logic_APV_0, 14);
  _TIMER_0_T(INDEX_TIMER_APV_TMP1, 1, logic_APV_0, 14, logic_APV_0, 15);

  //�:"����"
  logic_APV_0 |= ((current_settings_prt.control_achr_chapv & CTR_CHAPV) != 0) << 16;
  //"����"
  logic_APV_1 |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_ACHR_CHAPV) != 0) << 21;
  //"���� ����"
  logic_APV_1 |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_RAZR_CHAPV) != 0) << 20;

  //"���/���� �� ��"
  logic_APV_0 |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_ACHR_CHAPV_VID_DV) != 0) << 17;
  //�:"���� �� ��"
  logic_APV_1 |= ((current_settings_prt.control_achr_chapv & CTR_CHAPV_VID_DV) != 0) << 22;
  
  _AND3(logic_APV_0, 16, logic_APV_1, 21, logic_APV_1, 20, logic_APV_1, 23);
  _AND2(logic_APV_0, 17, logic_APV_1, 22, logic_APV_1, 24);
  _OR2(logic_APV_1, 23, logic_APV_1, 24, logic_APV_0, 18)

  //"����.���� �� U"
  logic_APV_1 |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_BLOCK_CHAPV_VID_U) != 0) << 25;
  _OR2(logic_APV_0, 18, logic_APV_1, 25, logic_APV_1, 26);
    
  _TIMER_0_T(INDEX_TIMER_ACHR_CHAPV, MAX_VALUE_TIMER_FOR_COUNT_SIGNAL_ACHR_CHAPV, logic_APV_0, 18, logic_APV_0, 19);

  _OR2_INVERTOR(logic_APV_0, 15, logic_APV_0, 19, logic_APV_0, 20);

  //"���� ��������"
  logic_APV_0 |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_STATE_VV) != 0) << 21;
  _TIMER_IMPULSE(INDEX_TIMER_APV_BLOCK_VID_VV, current_settings_prt.timeout_apv_block_vid_VV[number_group_stp], previous_states_APV_0, 0, logic_APV_0, 21, logic_APV_0, 22);

  //�:"���"
  logic_APV_0 |= ((current_settings_prt.control_apv & CTR_APV_STAGE_1) != 0) << 23;
  _INVERTOR(logic_APV_0, 23, logic_APV_0, 24);

  //�:"���2"
  logic_APV_0 |= ((current_settings_prt.control_apv & CTR_APV_STAGE_2) != 0) << 25;
  _INVERTOR(logic_APV_0, 25, logic_APV_0, 26);

  //�:"���3"
  logic_APV_0 |= ((current_settings_prt.control_apv & CTR_APV_STAGE_3) != 0) << 27;
  _INVERTOR(logic_APV_0, 27, logic_APV_0, 28);

  //�:"���4"
  logic_APV_0 |= ((current_settings_prt.control_apv & CTR_APV_STAGE_4) != 0) << 29;
  _INVERTOR(logic_APV_0, 29, logic_APV_0, 30);

  //������� �������� ����������� ���������� ���� �� ������� �� ������������� � ���������� ����
  logic_APV_0 |= _GET_OUTPUT_STATE(previous_states_APV_0, 1) << 31;
  logic_APV_1 |= _GET_OUTPUT_STATE(previous_states_APV_0, 2) <<  0;
  logic_APV_1 |= _GET_OUTPUT_STATE(previous_states_APV_0, 3) <<  1;
  logic_APV_1 |= _GET_OUTPUT_STATE(previous_states_APV_0, 4) <<  2;
  
  unsigned int previous_trigger_APV_0;
  
  do
  {
    /***
    Գ����� �������� ���� �������, �� ����, �������, �������� � �� ����
    ����� ���� �������� ���������� ������������ �������
    ***/
    _CLEAR_STATE(previous_states_APV_0, 1);
    previous_states_APV_0 |= _GET_OUTPUT_STATE(logic_APV_0, 31) << 1;
    _CLEAR_STATE(previous_states_APV_0, 2);
    previous_states_APV_0 |= _GET_OUTPUT_STATE(logic_APV_1,  0) << 2;
    _CLEAR_STATE(previous_states_APV_0, 3);
    previous_states_APV_0 |= _GET_OUTPUT_STATE(logic_APV_1,  1) << 3;
    _CLEAR_STATE(previous_states_APV_0, 4);
    previous_states_APV_0 |= _GET_OUTPUT_STATE(logic_APV_1,  2) << 4;
    
    previous_trigger_APV_0 = trigger_APV_0;
    /***/
    
    _OR2(logic_APV_1, 2, logic_APV_1, 1, logic_APV_1, 3);
    
    
    //���1
    _OR6(logic_APV_1, 19, logic_APV_0, 14,                   trigger_APV_0, 1, trigger_APV_0, 2, trigger_APV_0, 3, logic_APV_0, 31, logic_APV_1, 4);
    _OR6(logic_APV_1, 26, logic_APV_0, 22, logic_APV_0, 24, logic_APV_1, 3, logic_APV_1, 0, logic_APV_1, 4, logic_APV_1, 8);
    _D_TRIGGER(_GET_OUTPUT_STATE(logic_APV_0, 1),  0, _GET_OUTPUT_STATE(logic_APV_1, 8), previous_states_APV_0, 5, logic_APV_0, 20, trigger_APV_0, 0);                 
    _TIMER_T_0(INDEX_TIMER_APV_1, current_settings_prt.timeout_apv_1[number_group_stp], trigger_APV_0, 0, logic_APV_1, 9);
    /*
    ��� ������ ����������� � ����� activated_functions � ���� � ����������
    do-while, �� ��� �������� ����������� ��� ������, � ���� �� �����������, ��
    ��� ������ �� ������� ������ � ��� ������ ����������. ��� ������������ �� ��� "0"
    ���� ������������ "1" �� ���� � ����� ��� ������ � �� ���� ���� ����������� �� 
    �������� ������ ������� �������.
    */
    activated_functions[RANG_OUTPUT_LED_DF_REG_APV1 >> 5] |= (_GET_OUTPUT_STATE(logic_APV_1, 9) << (RANG_OUTPUT_LED_DF_REG_APV1 & 0x1f));
    _TIMER_0_T(INDEX_TIMER_APV_BLOCK_VID_APV1, current_settings_prt.timeout_apv_block_vid_apv1[number_group_stp], logic_APV_1, 9, logic_APV_0, 31);

    //���2
    _AND2_INVERTOR(logic_APV_0, 31, logic_APV_0, 15, logic_APV_1, 10);
    _OR6(logic_APV_1, 19, logic_APV_0, 14, trigger_APV_0, 0,                   trigger_APV_0, 2, trigger_APV_0, 3, logic_APV_1,  0, logic_APV_1, 5);
    _OR6(logic_APV_1, 26, logic_APV_0, 24, logic_APV_0, 26, logic_APV_1, 2, logic_APV_1, 1, logic_APV_1, 5, logic_APV_1, 11);
    _D_TRIGGER(1,  0, _GET_OUTPUT_STATE(logic_APV_1, 11), previous_states_APV_0, 6, logic_APV_1, 10, trigger_APV_0, 1);    
    _TIMER_T_0(INDEX_TIMER_APV_2, current_settings_prt.timeout_apv_2[number_group_stp], trigger_APV_0, 1, logic_APV_1, 12);
    /*
    ��� ������ ����������� � ����� activated_functions � ���� � ����������
    do-while, �� ��� �������� ����������� ��� ������, � ���� �� �����������, ��
    ��� ������ �� ������� ������ � ��� ������ ����������. ��� ������������ �� ��� "0"
    ���� ������������ "1" �� ���� � ����� ��� ������ � �� ���� ���� ����������� �� 
    �������� ������ ������� �������.
    */
    activated_functions[RANG_OUTPUT_LED_DF_REG_APV2 >> 5] |= (_GET_OUTPUT_STATE(logic_APV_1, 12) << (RANG_OUTPUT_LED_DF_REG_APV2 & 0x1f));
    _TIMER_0_T(INDEX_TIMER_APV_BLOCK_VID_APV2, current_settings_prt.timeout_apv_block_vid_apv2[number_group_stp], logic_APV_1, 12, logic_APV_1, 0);

    //���3
    _AND2_INVERTOR(logic_APV_1, 0, logic_APV_0, 15, logic_APV_1, 13);
    _OR6(logic_APV_1, 19, logic_APV_0, 14, trigger_APV_0, 0, trigger_APV_0, 1,                   trigger_APV_0, 3, logic_APV_1,  1, logic_APV_1, 6);
    _OR5(logic_APV_1, 26, logic_APV_0, 24, logic_APV_0, 28, logic_APV_1, 2, logic_APV_1, 6, logic_APV_1, 14);
    _D_TRIGGER(1,  0, _GET_OUTPUT_STATE(logic_APV_1, 14), previous_states_APV_0, 7, logic_APV_1, 13, trigger_APV_0, 2);                 
    _TIMER_T_0(INDEX_TIMER_APV_3, current_settings_prt.timeout_apv_3[number_group_stp], trigger_APV_0, 2, logic_APV_1, 15);
    /*
    ��� ������ ����������� � ����� activated_functions � ���� � ����������
    do-while, �� ��� �������� ����������� ��� ������, � ���� �� �����������, ��
    ��� ������ �� ������� ������ � ��� ������ ����������. ��� ������������ �� ��� "0"
    ���� ������������ "1" �� ���� � ����� ��� ������ � �� ���� ���� ����������� �� 
    �������� ������ ������� �������.
    */
    activated_functions[RANG_OUTPUT_LED_DF_REG_APV3 >> 5] |= (_GET_OUTPUT_STATE(logic_APV_1, 15) << (RANG_OUTPUT_LED_DF_REG_APV3 & 0x1f));
    _TIMER_0_T(INDEX_TIMER_APV_BLOCK_VID_APV3, current_settings_prt.timeout_apv_block_vid_apv3[number_group_stp], logic_APV_1, 15, logic_APV_1, 1);

    //���4
    _AND2_INVERTOR(logic_APV_1, 1, logic_APV_0, 15, logic_APV_1, 16);
    _OR6(logic_APV_1, 19, logic_APV_0, 14, trigger_APV_0, 0, trigger_APV_0, 1, trigger_APV_0, 2,                   logic_APV_1,  2, logic_APV_1, 7);
    _OR4(logic_APV_1, 26, logic_APV_0, 24, logic_APV_0, 30, logic_APV_1, 7, logic_APV_1, 17);
    _D_TRIGGER(1,  0, _GET_OUTPUT_STATE(logic_APV_1, 17), previous_states_APV_0, 8, logic_APV_1, 16, trigger_APV_0, 3);                 
    _TIMER_T_0(INDEX_TIMER_APV_4, current_settings_prt.timeout_apv_4[number_group_stp], trigger_APV_0, 3, logic_APV_1, 18);
    /*
    ��� ������ ����������� � ����� activated_functions � ���� � ����������
    do-while, �� ��� �������� ����������� ��� ������, � ���� �� �����������, ��
    ��� ������ �� ������� ������ � ��� ������ ����������. ��� ������������ �� ��� "0"
    ���� ������������ "1" �� ���� � ����� ��� ������ � �� ���� ���� ����������� �� 
    �������� ������ ������� �������.
    */
    activated_functions[RANG_OUTPUT_LED_DF_REG_APV4 >> 5] |= (_GET_OUTPUT_STATE(logic_APV_1, 18) << (RANG_OUTPUT_LED_DF_REG_APV4 & 0x1f));
    _TIMER_0_T(INDEX_TIMER_APV_BLOCK_VID_APV4, current_settings_prt.timeout_apv_block_vid_apv4[number_group_stp], logic_APV_1, 18, logic_APV_1, 2);
  }
  while (
         (_GET_OUTPUT_STATE(logic_APV_0, 31) != _GET_OUTPUT_STATE(previous_states_APV_0, 1)) ||
         (_GET_OUTPUT_STATE(logic_APV_1,  0) != _GET_OUTPUT_STATE(previous_states_APV_0, 2)) ||
         (_GET_OUTPUT_STATE(logic_APV_1,  1) != _GET_OUTPUT_STATE(previous_states_APV_0, 3)) ||
         (_GET_OUTPUT_STATE(logic_APV_1,  2) != _GET_OUTPUT_STATE(previous_states_APV_0, 4)) ||
         ( trigger_APV_0                     !=  previous_trigger_APV_0                    )  
        );
  
  _Bool work_apv = 0;
  _OR4(trigger_APV_0, 0, trigger_APV_0, 1, trigger_APV_0, 2, trigger_APV_0, 3, work_apv, 0);
  
  //������ ���
  if (work_apv) {
    _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_APV_WORK);
  }
  
}
/*****************************************************/

/*****************************************************/
//������� ��������� ������� ��������� � ����������
/*****************************************************/
inline void on_off_handler(unsigned int *activated_functions, unsigned int *previous_stats_signals)
{
  //������� �������� �������� ������� "������ ��" � "������ ��" � ���������� �����, ��� ���� ���� ��������� �� ������� ��� �������������
  //�� ������� ��� ����, ��� ���� � �����, �� ������ �� �� � ��������������� � ��������� - ��� �� ������� ��� �������� ��������  
  unsigned int maska[N_BIG] = {0, 0, 0, 0, 0, 0};
  _SET_BIT(maska, RANG_OUTPUT_LED_DF_REG_WORK_BO);
  _SET_BIT(maska, RANG_OUTPUT_LED_DF_REG_WORK_BV);
  activated_functions[0] |= active_functions[0] & maska[0];
  activated_functions[1] |= active_functions[1] & maska[1];
  activated_functions[2] |= active_functions[2] & maska[2];
  activated_functions[3] |= active_functions[3] & maska[3];
  activated_functions[4] |= active_functions[4] & maska[4];
  activated_functions[5] |= active_functions[5] & maska[5];

  /*********************/
  //�������� ����������� �������
  /*********************/
  //������  ����������
  if (global_timers[INDEX_TIMER_VIDKL_VV] >= 0)
  {
    //������ �� ����� �������� � �� ����� ����� ����� ��������� ���� ������
    if (global_timers[INDEX_TIMER_VIDKL_VV] >= current_settings_prt.timeout_swch_off)
    {
      //������ �������� ����� ������������� ��������
      global_timers[INDEX_TIMER_VIDKL_VV] = -1;
      //³������ � ����� �������, �� ����� �����������, �� ���� �� �� ���� ������������
      _CLEAR_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_WORK_BO);
    }
    //����������� ������ ����� �� ������, �� ������ ���������� �� �� ���� ��������� � ����������� � ����� ����������� �������,
    //��� �� ����� ���� �� ��������, ��� ���������� ��������� �������� �� ���� ��� � ������� ��������� ������ ����� ��
    global_timers[INDEX_TIMER_BLK_VKL_VV] = 0;
  }
    
  //������  ���������� ���������
  if (global_timers[INDEX_TIMER_BLK_VKL_VV] >= 0)
  {
    //������ ���������� ��������� �� ����� �������� � �� ����� ����� ����� ��������� ���� ������
    if (global_timers[INDEX_TIMER_BLK_VKL_VV] >= current_settings_prt.timeout_swch_udl_blk_on)
    {
      //������ �������� ����� ������������� ��������
      global_timers[INDEX_TIMER_BLK_VKL_VV] = -1;
    }
  }

  //������  ���������
  if (global_timers[INDEX_TIMER_VKL_VV] >= 0)
  {
    //������ �� ����� �������� � �� ����� ����� ����� ��������� ���� ������

    //���� �� ����� ������ ������ ��������� ������, ��� ����, �� ������� �� � ���������� ��������� �� �� ������, �� ������ ��������� ����� �������
    if ((global_timers[INDEX_TIMER_VIDKL_VV] >= 0) || (global_timers[INDEX_TIMER_BLK_VKL_VV] >=0))
    {
      global_timers[INDEX_TIMER_VKL_VV] = -1;
      //³������ � ����� �������, �� ����� �����������, �� ���� �B �� ���� ������������
      _CLEAR_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_WORK_BV);
    }
    else
    {
      //����������, �� ������ ��������� �� �������� ����� ������������ ��������
      if (global_timers[INDEX_TIMER_VKL_VV] >= current_settings_prt.timeout_swch_on)
      {
        //������ �������� ����� ������������� ��������
        global_timers[INDEX_TIMER_VKL_VV] = -1;
        //³������ � ����� �������, �� ����� �����������, �� ���� �B �� ���� ������������
        _CLEAR_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_WORK_BV);
      }
    }
  }
  /*********************/

  /*********************/
  //������ ������������ ���� ����������, �� �� ���� ��������� ��������� ��������
  /*********************/
  //������� ����� � �������� "������ ��", ��� �� ���������� ��� ������ �� ������� ��������� �� (��� �� ��� ���� �� ���������, �� ������, �� ����� ��� ����������� ������� ���� ���� ����������)
  maska[0] = 0;
  maska[1] = 0;
  maska[2] = 0;
  maska[3] = 0;
  maska[4] = 0;
  maska[5] = 0;
  _SET_BIT(maska, RANG_OUTPUT_LED_DF_REG_WORK_BO);

  //����������, �� ���� ����� ������� ��
  unsigned int i = 0;
  while ((i < NUMBER_OUTPUTS) && (global_timers[INDEX_TIMER_VIDKL_VV] != 0))
  {
    //�� ������� �������� ���� ���� �� ���������� �� ������, ��� ���� ���� �� �� ����������
    /*
    (���� ������ ����� ����� "0", �� ���� � �� ������ ��������� �� �� �� ������ ������� � 0,
    � ������ ������, �� ���� ���� ��������� �� DELTA_TIME_FOR_TIMERS, ��� "-1", ���� ������ �������� ��� ����������, ��� ������ �� ����������)
    */
      
    //� ���������� ����� ������� ���������� ������, ���� ����������� ��������� "i"
    unsigned int temp_array_of_outputs[N_BIG];
    temp_array_of_outputs[0] = current_settings_prt.ranguvannja_outputs[N_BIG*i    ];
    temp_array_of_outputs[1] = current_settings_prt.ranguvannja_outputs[N_BIG*i + 1];
    temp_array_of_outputs[2] = current_settings_prt.ranguvannja_outputs[N_BIG*i + 2];
    temp_array_of_outputs[3] = current_settings_prt.ranguvannja_outputs[N_BIG*i + 3];
    temp_array_of_outputs[4] = current_settings_prt.ranguvannja_outputs[N_BIG*i + 4];
    temp_array_of_outputs[5] = current_settings_prt.ranguvannja_outputs[N_BIG*i + 5];
      
    //���������� �� �� �����, ���� ����������� ��������� "i", ���������� ������ ��
    if(_CHECK_SET_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_WORK_BO) !=0)
    {
      //����������, �� � ����� ����� ��������� ������ (����-��� ������� ������� ��� ������� "������ ��")
      temp_array_of_outputs[0] &= ( (activated_functions[0] | previous_stats_signals[0]) & (~maska[0]) );
      temp_array_of_outputs[1] &= ( (activated_functions[1] | previous_stats_signals[1]) & (~maska[1]) );
      temp_array_of_outputs[2] &= ( (activated_functions[2] | previous_stats_signals[2]) & (~maska[2]) );
      temp_array_of_outputs[3] &= ( (activated_functions[3] | previous_stats_signals[3]) & (~maska[3]) );
      temp_array_of_outputs[4] &= ( (activated_functions[4] | previous_stats_signals[4]) & (~maska[4]) );
      temp_array_of_outputs[5] &= ( (activated_functions[5] | previous_stats_signals[5]) & (~maska[5]) );
      if (
          (temp_array_of_outputs[0] != 0) ||
          (temp_array_of_outputs[1] != 0) ||
          (temp_array_of_outputs[2] != 0) ||
          (temp_array_of_outputs[3] != 0) ||
          (temp_array_of_outputs[4] != 0) ||
          (temp_array_of_outputs[5] != 0)
         )
      {
        //�� ������ ����� ����� ������������ ����� �������, ��� � ��������� � �������� ��
          
        //³������ � ����� �������, �� ����� �����������, �� �� ����� ���������� ���� �� (���� �� �� �� ��������)
        _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_WORK_BO);

        //��������� (��� ���������� ���������� � 0, ���� �� ������� ������ ��������� ��) �������: ����� ��, ����������� ��.
        global_timers[INDEX_TIMER_VIDKL_VV  ] = 0;
        global_timers[INDEX_TIMER_BLK_VKL_VV] = 0;

        //������� ��������� ��
        _CLEAR_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_WORK_BV);
        //������� ������ ��
        global_timers[INDEX_TIMER_VKL_VV] = -1;  

        /*
        ������� ������ "³��������� �� �������" (�� ����� �������� ����� �������
        ��������� ������� "������ ��" ����-���� �������� �� ����������� "�����. ��")
        */
        maska[0] = 0;
        maska[1] = 0;
        maska[2] = 0;
        maska[3] = 0;
        maska[4] = 0;
        maska[5] = 0;
        _SET_BIT(maska, RANG_OUTPUT_LED_DF_REG_OTKL_VV);

        //����������, �� "������ ��" ������������ �������� "����.��" �� ������ �������� �������
        temp_array_of_outputs[0] &= (~maska[0]);
        temp_array_of_outputs[1] &= (~maska[1]);
        temp_array_of_outputs[2] &= (~maska[2]);
        temp_array_of_outputs[3] &= (~maska[3]);
        temp_array_of_outputs[4] &= (~maska[4]);
        temp_array_of_outputs[5] &= (~maska[5]);
        if (
            (temp_array_of_outputs[0] != 0) ||
            (temp_array_of_outputs[1] != 0) ||
            (temp_array_of_outputs[2] != 0) ||
            (temp_array_of_outputs[3] != 0) ||
            (temp_array_of_outputs[4] != 0) ||
            (temp_array_of_outputs[5] != 0)
          )
        {
          _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_VIDKL_VID_ZAKHYSTIV);
          
          /*****************************************************
          ��������� ���������� ��� ������� ���������� ��� ����
          *****************************************************/
          unsigned char *label_to_time_array;
          if (copying_time == 2) label_to_time_array = time_copy;
          else label_to_time_array = time;
          
          //���1
          if(
             (_CHECK_SET_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_MTZ1) != 0) &&
             (_CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_MTZ1) == 0) /*�����, �� ������ ����� ���������� (��� ����������� ��� ������)*/
            )   
          {
            info_vidkluchennja_vymykacha |= (1 << VYMKNENNJA_VID_MTZ1);
            for(unsigned int j = 0; j < 7; j++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_MTZ1][j] = *(label_to_time_array + j);

            _CLEAR_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_MTZ1);
          }
          
          //���2
          if(
             (_CHECK_SET_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_MTZ2) != 0) &&
             (_CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_MTZ2) == 0) /*�����, �� ������ ����� ���������� (��� ����������� ��� ������)*/
            )   
          {
            info_vidkluchennja_vymykacha |= (1 << VYMKNENNJA_VID_MTZ2);
            for(unsigned int j = 0; j < 7; j++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_MTZ2][j] = *(label_to_time_array + j);

            _CLEAR_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_MTZ2);
          }
          
          //���3
          if(
             (_CHECK_SET_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_MTZ3) != 0) &&
             (_CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_MTZ3) == 0) /*�����, �� ������ ����� ���������� (��� ����������� ��� ������)*/
            )   
          {
            info_vidkluchennja_vymykacha |= (1 << VYMKNENNJA_VID_MTZ3);
            for(unsigned int j = 0; j < 7; j++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_MTZ3][j] = *(label_to_time_array + j);

            _CLEAR_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_MTZ3);
          }
          
          //���4
          if(
             (_CHECK_SET_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_MTZ4) != 0) &&
             (_CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_MTZ4) == 0) /*�����, �� ������ ����� ���������� (��� ����������� ��� ������)*/
            )   
          {
            info_vidkluchennja_vymykacha |= (1 << VYMKNENNJA_VID_MTZ4);
            for(unsigned int j = 0; j < 7; j++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_MTZ4][j] = *(label_to_time_array + j);

            _CLEAR_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_MTZ4);
          }
          
          //���
          if(
             (_CHECK_SET_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_ZDZ) != 0) &&
             (_CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_ZDZ) == 0) /*�����, �� ������ ����� ���������� (��� ����������� ��� ������)*/
            )   
          {
            info_vidkluchennja_vymykacha |= (1 << VYMKNENNJA_VID_ZDZ);
            for(unsigned int j = 0; j < 7; j++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_ZDZ][j] = *(label_to_time_array + j);

            _CLEAR_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_ZDZ);
          }
          
          //��/3I0
          if(
             (_CHECK_SET_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_3I0) != 0) &&
             (_CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_3I0) == 0) /*�����, �� ������ ����� ���������� (��� ����������� ��� ������)*/
            )   
          {
            info_vidkluchennja_vymykacha |= (1 << VYMKNENNJA_VID_3I0);
            for(unsigned int j = 0; j < 7; j++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_3I0][j] = *(label_to_time_array + j);

            _CLEAR_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_3I0);
          }
          
          //��/3U0
          if(
             (_CHECK_SET_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_3U0) != 0) &&
             (_CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_3U0) == 0) /*�����, �� ������ ����� ���������� (��� ����������� ��� ������)*/
            )   
          {
            info_vidkluchennja_vymykacha |= (1 << VYMKNENNJA_VID_3U0);
            for(unsigned int j = 0; j < 7; j++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_3U0][j] = *(label_to_time_array + j);

            _CLEAR_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_3U0);
          }
          
          //���
          if(
             (_CHECK_SET_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_NZZ) != 0) &&
             (_CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_NZZ) == 0) /*�����, �� ������ ����� ���������� (��� ����������� ��� ������)*/
            )   
          {
            info_vidkluchennja_vymykacha |= (1 << VYMKNENNJA_VID_NZZ);
            for(unsigned int j = 0; j < 7; j++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_NZZ][j] = *(label_to_time_array + j);

            _CLEAR_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_NZZ);
          }
          
          //���/���� �� ��
          if(
             (_CHECK_SET_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_ACHR_CHAPV_VID_DV) != 0) &&
             (_CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_ACHR_CHAPV_VID_DV) == 0) /*�����, �� ������ ����� ���������� (��� ����������� ��� ������)*/
            )   
          {
            info_vidkluchennja_vymykacha |= (1 << VYMKNENNJA_VID_ACHR_CHAPV_VID_DV);
            for(unsigned int j = 0; j < 7; j++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_ACHR_CHAPV_VID_DV][j] = *(label_to_time_array + j);

            _CLEAR_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_ACHR_CHAPV_VID_DV);
          }
          
          //���/����
          if(
             (_CHECK_SET_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_ACHR_CHAPV) != 0) &&
             (_CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_ACHR_CHAPV) == 0) /*�����, �� ������ ����� ���������� (��� ����������� ��� ������)*/
            )   
          {
            info_vidkluchennja_vymykacha |= (1 << VYMKNENNJA_VID_ACHR_CHAPV);
            for(unsigned int j = 0; j < 7; j++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_ACHR_CHAPV][j] = *(label_to_time_array + j);

            _CLEAR_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_ACHR_CHAPV);
          }
          
          //����1
          if(
             (_CHECK_SET_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_UROV1) != 0) &&
             (_CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_UROV1) == 0) /*�����, �� ������ ����� ���������� (��� ����������� ��� ������)*/
            )   
          {
            info_vidkluchennja_vymykacha |= (1 << VYMKNENNJA_VID_UROV1);
            for(unsigned int j = 0; j < 7; j++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_UROV1][j] = *(label_to_time_array + j);

            _CLEAR_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_UROV1);
          }
          
          //����2
          if(
             (_CHECK_SET_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_UROV2) != 0) &&
             (_CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_UROV2) == 0) /*�����, �� ������ ����� ���������� (��� ����������� ��� ������)*/
            )   
          {
            info_vidkluchennja_vymykacha |= (1 << VYMKNENNJA_VID_UROV2);
            for(unsigned int j = 0; j < 7; j++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_UROV2][j] = *(label_to_time_array + j);

            _CLEAR_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_UROV2);
          }
          
          //���
          if(
             (_CHECK_SET_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_ZOP) != 0) &&
             (_CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_ZOP) == 0) /*�����, �� ������ ����� ���������� (��� ����������� ��� ������)*/
            )   
          {
            info_vidkluchennja_vymykacha |= (1 << VYMKNENNJA_VID_ZOP);
            for(unsigned int j = 0; j < 7; j++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_ZOP][j] = *(label_to_time_array + j);

            _CLEAR_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_ZOP);
          }
          
          //Umin1
          if(
             (_CHECK_SET_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_UMIN1) != 0) &&
             (_CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_UMIN1) == 0) /*�����, �� ������ ����� ���������� (��� ����������� ��� ������)*/
            )   
          {
            info_vidkluchennja_vymykacha |= (1 << VYMKNENNJA_VID_UMIN1);
            for(unsigned int j = 0; j < 7; j++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_UMIN1][j] = *(label_to_time_array + j);

            _CLEAR_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_UMIN1);
          }
          
          //Umin2
          if(
             (_CHECK_SET_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_UMIN2) != 0) &&
             (_CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_UMIN2) == 0) /*�����, �� ������ ����� ���������� (��� ����������� ��� ������)*/
            )   
          {
            info_vidkluchennja_vymykacha |= (1 << VYMKNENNJA_VID_UMIN2);
            for(unsigned int j = 0; j < 7; j++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_UMIN2][j] = *(label_to_time_array + j);

            _CLEAR_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_UMIN2);
          }
          
          //Umax1
          if(
             (_CHECK_SET_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_UMAX1) != 0) &&
             (_CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_UMAX1) == 0) /*�����, �� ������ ����� ���������� (��� ����������� ��� ������)*/
            )   
          {
            info_vidkluchennja_vymykacha |= (1 << VYMKNENNJA_VID_UMAX1);
            for(unsigned int j = 0; j < 7; j++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_UMAX1][j] = *(label_to_time_array + j);

            _CLEAR_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_UMAX1);
          }
          
          //Umax2
          if(
             (_CHECK_SET_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_UMAX2) != 0) &&
             (_CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_UMAX2) == 0) /*�����, �� ������ ����� ���������� (��� ����������� ��� ������)*/
            )   
          {
            info_vidkluchennja_vymykacha |= (1 << VYMKNENNJA_VID_UMAX2);
            for(unsigned int j = 0; j < 7; j++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_UMAX2][j] = *(label_to_time_array + j);

            _CLEAR_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_UMAX2);
          }
          
          //³��������� �� ������� �������
          if(
             (_CHECK_SET_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_OTKL_VID_ZOVN_ZAHYSTIV) != 0) &&
             (_CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_OTKL_VID_ZOVN_ZAHYSTIV) == 0) /*�����, �� ������ ����� ���������� (��� ����������� ��� ������)*/
            )   
          {
            info_vidkluchennja_vymykacha |= (1 << VYMKNENNJA_VID_ZOVNISHNIKH_ZAKHYSTIV);
            for(unsigned int j = 0; j < 7; j++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_ZOVNISHNIKH_ZAKHYSTIV][j] = *(label_to_time_array + j);

            _CLEAR_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_OTKL_VID_ZOVN_ZAHYSTIV);
          }
          
          //³��������� �� ����� ������� (��� ���������� �� ������� "����.��")
          if(
             (
              (temp_array_of_outputs[0] != 0) ||
              (temp_array_of_outputs[1] != 0) ||
              (temp_array_of_outputs[2] != 0) ||
              (temp_array_of_outputs[3] != 0) ||
              (temp_array_of_outputs[4] != 0) ||
              (temp_array_of_outputs[5] != 0)
             )
             &&
             (
              ((active_functions[0] & temp_array_of_outputs[0])!= temp_array_of_outputs[0]) ||
              ((active_functions[1] & temp_array_of_outputs[1])!= temp_array_of_outputs[1]) ||
              ((active_functions[2] & temp_array_of_outputs[2])!= temp_array_of_outputs[2]) ||
              ((active_functions[3] & temp_array_of_outputs[3])!= temp_array_of_outputs[3]) ||
              ((active_functions[4] & temp_array_of_outputs[4])!= temp_array_of_outputs[4]) ||
              ((active_functions[5] & temp_array_of_outputs[5])!= temp_array_of_outputs[5])
             ) 
            )   
          {
            info_vidkluchennja_vymykacha |= (1 << VYMKNENNJA_VID_INSHYKH_SYGNALIV);
            for(unsigned int j = 0; j < 7; j++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_INSHYKH_SYGNALIV][j] = *(label_to_time_array + j);
          }
          /*****************************************************/
        }
        /***/
      }
    }
    i++;
  }
  /*********************/

  /*********************/
  //���� ������������ ���� ���������
  /*********************/
  if (
      (global_timers[INDEX_TIMER_VIDKL_VV  ] < 0) && 
      (global_timers[INDEX_TIMER_BLK_VKL_VV] < 0) &&
      (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_BLOCK_VKL_VV) == 0)
     )
  {
    //������� �� �������� ������� �� � ���������� ��������� ��, � ����� ���� ������� ���������� ��������� ��
    //���� ����������, �� ���� ����� ������� ��

    //������� ����� � �������� "������ ��", ��� �� ���������� ��� ������ �� ������� ��������� �� (��� �� ��� ���� �� ���������, �� ������, �� ����� ��� ����������� ������� ���� ���� ����������)
    maska[0] = 0;
    maska[1] = 0;
    maska[2] = 0;
    maska[3] = 0;
    maska[4] = 0;
    maska[5] = 0;
    _SET_BIT(maska, RANG_OUTPUT_LED_DF_REG_WORK_BV);
    
    i = 0;
    while ((i < NUMBER_OUTPUTS) && (global_timers[INDEX_TIMER_VKL_VV] != 0))
    {
      //�� ������� �������� ���� ���� �� ���������� �� ������, ��� ���� ���� �� �� ����������
      /*
      (���� ������ ����� ����� "0", �� ���� � �� ������ ��������� �� �� �� ������ ������� � 0,
      � ������ ������, �� ���� ���� ��������� �� DELTA_TIME_FOR_TIMERS, ��� "-1", ���� ������ �������� ��� ����������, ��� ������ �� ����������)
      */

      //� ���������� ����� ������� ���������� ������, ���� ����������� ��������� "i"
      unsigned int temp_array_of_outputs[N_BIG];
      temp_array_of_outputs[0] = current_settings_prt.ranguvannja_outputs[N_BIG*i    ];
      temp_array_of_outputs[1] = current_settings_prt.ranguvannja_outputs[N_BIG*i + 1];
      temp_array_of_outputs[2] = current_settings_prt.ranguvannja_outputs[N_BIG*i + 2];
      temp_array_of_outputs[3] = current_settings_prt.ranguvannja_outputs[N_BIG*i + 3];
      temp_array_of_outputs[4] = current_settings_prt.ranguvannja_outputs[N_BIG*i + 4];
      temp_array_of_outputs[5] = current_settings_prt.ranguvannja_outputs[N_BIG*i + 5];
      
      //���������� �� �� �����, ���� ����������� ��������� "i", ���������� ������ ��
      if(_CHECK_SET_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_WORK_BV) !=0)
      {
        //����������, �� � ����� ����� ��������� ������ (����-��� ������� ������� ��� ������� "������ ��")
        temp_array_of_outputs[0] &= ( (activated_functions[0] | previous_stats_signals[0]) & (~maska[0]) );
        temp_array_of_outputs[1] &= ( (activated_functions[1] | previous_stats_signals[1]) & (~maska[1]) );
        temp_array_of_outputs[2] &= ( (activated_functions[2] | previous_stats_signals[2]) & (~maska[2]) );
        temp_array_of_outputs[3] &= ( (activated_functions[3] | previous_stats_signals[3]) & (~maska[3]) );
        temp_array_of_outputs[4] &= ( (activated_functions[4] | previous_stats_signals[4]) & (~maska[4]) );
        temp_array_of_outputs[5] &= ( (activated_functions[5] | previous_stats_signals[5]) & (~maska[5]) );
        if (
            (temp_array_of_outputs[0] != 0) ||
            (temp_array_of_outputs[1] != 0) ||
            (temp_array_of_outputs[2] != 0) ||
            (temp_array_of_outputs[3] != 0) ||
            (temp_array_of_outputs[4] != 0) ||
            (temp_array_of_outputs[5] != 0)
           )
        {
          //�� ������ ����� ����� ������������ ����� �������, ��� � ��������� � �������� ��
            
          //� ����� ������� ��, ��� �� ��������� ���������, �� ���� ����� �������� ��������� �� (���, ����������, ���� ��� ����������� �������, �� ���������� ������ �� ����� ���� �� ��� ������ ���������� ��������� �� �� ���� � ����)
          if ((global_timers[INDEX_TIMER_VIDKL_VV] < 0) && (global_timers[INDEX_TIMER_BLK_VKL_VV] < 0))
          {
            //³������ � ����� �������, �� ����� �����������, �� �� ����� ���������� ���� �� (���� �� �� �� ��������)
            _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_WORK_BV);

            //��������� (��� ���������� ���������� � 0, ���� �� ������� ������ ��������� ��) ������ ������ ��
            global_timers[INDEX_TIMER_VKL_VV] = 0;
          }
          else
          {
            //����������, ���� �������� ����� � �� ���� ������
            global_timers[INDEX_TIMER_VKL_VV] = -1;
            _CLEAR_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_WORK_BV);
          }
        }
      }
      i++;
    }
  }
  else
  {
    //�� ����� ������ ���� ���� ��� ����� ���� ���������� ��
    global_timers[INDEX_TIMER_VKL_VV] = -1;
    _CLEAR_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_WORK_BV);
  }
  /*********************/
}
/*****************************************************/

/*****************************************************/
//���������� ���� �� �����������
/*****************************************************/
inline void vmp_handler(unsigned int activated_functions[])
{
  //���������� �� ����� ���������� ����������� �� �� �� ������ ����
  if(
     ((activated_functions[0] & MASKA_MONITOTYNG_PHASE_SIGNALES_KZ_0) != 0) ||
     ((activated_functions[1] & MASKA_MONITOTYNG_PHASE_SIGNALES_KZ_1) != 0) ||
     ((activated_functions[2] & MASKA_MONITOTYNG_PHASE_SIGNALES_KZ_2) != 0) ||
     ((activated_functions[3] & MASKA_MONITOTYNG_PHASE_SIGNALES_KZ_3) != 0) ||
     ((activated_functions[4] & MASKA_MONITOTYNG_PHASE_SIGNALES_KZ_4) != 0) ||
     ((activated_functions[5] & MASKA_MONITOTYNG_PHASE_SIGNALES_KZ_5) != 0)
    )
  {
    //� ����� ��
    VMP_last_KZ = UNDEF_VMP; /*�������, �� ���������� ���� �� ����������� �� �� ���������*/
    
    //���������� �� �������� ������� �� ��������� �� ("������ ��")
    vymknennja_vid_KZ_prt = _CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_WORK_BO);

    
    //Գ����� ������������ ������ ����� ��� ��
    unsigned int max_faze_current = measurement[IM_IA];
    if (max_faze_current < measurement[IM_IB_r]) max_faze_current = measurement[IM_IB_r];
    if (max_faze_current < measurement[IM_IC]) max_faze_current = measurement[IM_IC];
    
    if (max_faze_current > I_max_KZ_prt)
    {
      //����������� ���� �������� ������������� ������� ������ ��� ��
      I_max_KZ_prt = max_faze_current;
      
      //��������� ������ ��� ���� ����� � ��
      unsigned int I_max_KZ_0_9 = (unsigned int)(0.9f*((float)max_faze_current));
      
      unsigned int number_of_phases_tmp = 0;
      if (measurement[IM_IA  ] >= I_max_KZ_0_9) number_of_phases_tmp++;
      if (measurement[IM_IB_r] >= I_max_KZ_0_9) number_of_phases_tmp++;
      if (measurement[IM_IC  ] >= I_max_KZ_0_9) number_of_phases_tmp++;
      number_of_phases_KZ_prt = number_of_phases_tmp;
        
      int X_resistance[3] = {resistance[X_AB], resistance[X_BC], resistance[X_CA]};
      if (
          (((unsigned int)X_resistance[0]) != ((unsigned int)UNDEF_RESISTANCE)) ||
          (((unsigned int)X_resistance[1]) != ((unsigned int)UNDEF_RESISTANCE)) ||
          (((unsigned int)X_resistance[2]) != ((unsigned int)UNDEF_RESISTANCE))
         )
      {
        //� ������� ���������� ������ �����

        //Գ����� ��������� �������� ���������� ��� ��� ��
        //���� 1: �������� ������ ���������� ��������� ��� � ������� ���� �������� �� ��������
        unsigned int min_interphase_X;
        int R_KZ_tmp;
        if (((unsigned int)X_resistance[0]) != ((unsigned int)UNDEF_RESISTANCE))
        {
          min_interphase_X = abs(X_resistance[0]);
          R_KZ_tmp = resistance[R_AB];
        }
        else if (((unsigned int)X_resistance[1]) != ((unsigned int)UNDEF_RESISTANCE))
        {
          min_interphase_X = abs(X_resistance[1]);
          R_KZ_tmp = resistance[R_BC];
        }
        else if (((unsigned int)X_resistance[2]) != ((unsigned int)UNDEF_RESISTANCE))
        {
          min_interphase_X = abs(X_resistance[2]);
          R_KZ_tmp = resistance[R_CA];
        }
        else
        {
          //���������� ����� ����� �� ���� � ����
          total_error_sw_fixed(68);
        }
      
        //���� 2: ����� ��� ���������� �������� ����� ��������� ��������
        unsigned int X_mod;
        if ((((unsigned int)X_resistance[0]) != ((unsigned int)UNDEF_RESISTANCE)) && (min_interphase_X > (X_mod = abs(X_resistance[0])))) 
        {
          min_interphase_X = X_mod;
          R_KZ_tmp = resistance[R_AB];
        }
        if ((((unsigned int)X_resistance[1]) != ((unsigned int)UNDEF_RESISTANCE)) && (min_interphase_X > (X_mod = abs(X_resistance[1]))))
        {
          min_interphase_X = X_mod;
          R_KZ_tmp = resistance[R_BC];
        }
        if ((((unsigned int)X_resistance[2]) != ((unsigned int)UNDEF_RESISTANCE)) && (min_interphase_X > (X_mod = abs(X_resistance[2]))))
        {
          min_interphase_X = X_mod;
          R_KZ_tmp = resistance[R_CA];
        }
      
        //����������� ��������� �������� ��������� ����� ��� ��
        X_min_KZ_prt = min_interphase_X;
        R_KZ_prt = R_KZ_tmp; //���� �� �� ����� ������� ����� ��� ���������� ����� (��� ��������� � ����� ������� �������� ��)

//        //���� 3: ���������� �� ��������� ��� �� ��� ������ �� � ��������� � ������� ���������� ��
//        if (
//            (X_min_KZ_prt == ((unsigned int)UNDEF_RESISTANCE)) || /*�� � �������, �� ��� ������ �� �� ������ ��� ������� ��������� ���, ���� � ���� �������� ������� �� ��������*/
//            (X_min_KZ_prt > min_interphase_X)
//           )
//        {
//          //����������� ���� �������� ���������� ��������� ����� ��� ��
//          X_min_KZ_prt = min_interphase_X;
//          R_KZ_prt = R_KZ_tmp; //���� �� �� ����� ������� ����� ��� ���������� ����� (��� ��������� � ����� ������� �������� ��)
//        }
      }
      else
      {
        X_min_KZ_prt = (unsigned int)UNDEF_RESISTANCE;
      }
    }
  }
  else
  {
    //�� ����� ������ ���� ������� ��
    if(
       (vymknennja_vid_KZ_prt != 0) &&  /*�����, �� ���������� ��������� �� ��� ���������� ��*/
       ((number_of_phases_last_KZ = number_of_phases_KZ_prt) > 1) && /*�����, �� �� � ��������*/
       ((current_settings_prt.control_vmp & CTR_VMP_STATE) != 0) && /*��� ��������*/ 
       (X_min_KZ_prt != ((unsigned int)UNDEF_RESISTANCE)) /*�����, �� ���� � ���� �������� ��� ��� ����������, � ���� � � ������������ ��������� ���������� �������� ���*/
      )
    {
      //��������� ������ �� ���� ����������� ���� �� ��� �������� 
      unsigned int X_tmp = X_min_KZ_prt*current_settings_prt.TVoltage/current_settings_prt.TCurrent; /*��������������� ��� �� �������� �������. �������� �������� � ���*/
      
      unsigned int forward_backward = (R_KZ_prt < 0);
      unsigned int lines_tmp = current_settings_prt.lines[forward_backward];
      unsigned int defined_VMP = false;
      unsigned int i = 0;
      int VMP_tmp = 0;
      while ((defined_VMP == false) && (i < lines_tmp))
      {
        unsigned int dovgyna_tmp = current_settings_prt.dovgyna[forward_backward][i];
        unsigned int opir_tmp = current_settings_prt.opir[forward_backward][i];
        unsigned int X_current_line = dovgyna_tmp*opir_tmp/1000; /*���������*[�]x[���/��] =  [�]x[���/1000�] =[���]/1000 */
        if (X_tmp <= X_current_line)
        {
          //�� ���� ������ ����������� �����������
//          VMP_tmp += (int)(((unsigned long long)dovgyna_tmp)*((unsigned long long)X_tmp)/((unsigned long long)X_current_line));
          VMP_tmp += X_tmp*1000/opir_tmp;
          defined_VMP = true;
        }
        else
        {
          //�� ���� ������ �� �� ����������� �����������
          VMP_tmp += dovgyna_tmp;
          X_tmp -= X_current_line;
        }
          
        i++;
      }
      
      //��������� ��������� ���
      equal_more_KZ = defined_VMP;
      if(forward_backward == 0) VMP_last_KZ = VMP_tmp;
      else VMP_last_KZ = -VMP_tmp;
    }

    /*
    ��������� �������� ������������ � ���� ���������� ������ ��
    
    �� �������� ���� � ����� ���� ���������� ����� ��� ���� ������������� ��,
    ��� �������  � �� ������ ��������� ��, � ����� ��������� ��� �� (������������ ��
    ���� �� �������� �� ���������, ��� ���� ������� ��������� �� �����������, � ��
    �� ���������) - �� ��� �� ������������ ��������, � ������ �� �������� ��������� ���� ���� ��
    � �����, �� �� �� ��� ������ � ���� � �� ���� ������ ������� ������ ���������
    */
    vymknennja_vid_KZ_prt = 0;
    I_max_KZ_prt = 0;
    number_of_phases_KZ_prt = 0;
    X_min_KZ_prt = (unsigned int)UNDEF_RESISTANCE;
    R_KZ_prt = 0;
  }
      
}
/*****************************************************/

/*****************************************************/
//�������� ������� ��������
/*****************************************************/
void control_VV(unsigned int *activated_functions)
{
  unsigned int logic_control_VV_0 = 0;

  //"�������� ���."
  logic_control_VV_0 |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_CTRL_VKL ) != 0) << 0;
  //"�������� ����."
  logic_control_VV_0 |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_CTRL_OTKL) != 0) << 1;
  
  _XOR_INVERTOR(logic_control_VV_0, 0, logic_control_VV_0, 1, logic_control_VV_0, 2);

  _TIMER_T_0(INDEX_TIMER_PRYVOD_VV, current_settings_prt.timeout_pryvoda_VV, logic_control_VV_0, 2, logic_control_VV_0, 3);

  //�:"�������� ��"
  logic_control_VV_0 |= ((current_settings_prt.control_switch & CTR_PRYVOD_VV) != 0) << 4;
  
  _AND2(logic_control_VV_0, 3, logic_control_VV_0, 4, logic_control_VV_0, 5);
  
  activated_functions[RANG_OUTPUT_LED_DF_REG_PRYVID_VV >> 5] |= (_GET_OUTPUT_STATE(logic_control_VV_0, 5) << (RANG_OUTPUT_LED_DF_REG_PRYVID_VV & 0x1f));
}
/*****************************************************/

/*****************************************************/
//���������� ������������ ��� ��������� ������� ��������
/*****************************************************/
void make_koef_for_resurs(void)
{
  float tmp_1, tmp_2;
  
  tmp_1 = (float)current_settings.setpoint_r_kom_st_Inom/(float)current_settings.setpoint_r_kom_st_Inom_vymk;
  tmp_1  = log10f(tmp_1);

  tmp_2 = (float)current_settings.setpoint_Inom_vymk/(float)current_settings.setpoint_Inom;
  tmp_2  = log10f(tmp_2);
  
  //�������, �� ����������� ��� ���������� ������� �������� ����� ������ �����
  koef_resurs_changed = CHANGED_ETAP_EXECUTION;

  K_resurs = tmp_1/tmp_2;
  
  //�������, �� ����������� ��� ���������� ������� �������� ����� � ������� �� ������ �������� �������
  koef_resurs_changed = CHANGED_ETAP_ENDED;
}
/*****************************************************/

/*****************************************************/
//˳������� �������
/*****************************************************/
inline void resurs_vymykacha_handler(unsigned int *activated_functions, unsigned int *active_functions_tmp)
{
  if (restart_counter != 0)
  {
    //����� ������ ������� ������� ������� ��������
    resurs_vymykacha = current_settings_prt.setpoint_pochatkovyj_resurs;
    resurs_vidkljuchennja = current_settings_prt.setpoint_pochatkova_k_vymk;
    
     restart_counter = 0;

    //��������� ����� � EEPROM
    _SET_BIT(control_eeprom_taskes, TASK_START_WRITE_RESURS_EEPROM_BIT);

    //�������, �� �������� ������� ������� ��������
    information_about_restart_counter |= ((1 << USB_RECUEST)|(1 << RS485_RECUEST));
  }
  
  /*******************************/
  //��������� ������������ ������� ����� �� ��� ������ ����� ��������� (��)
  /*******************************/
  static unsigned int max_faze_current_vv;
  if (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_WORK_BO) != 0)
  {
    unsigned int max_faze_current_tmp = measurement[IM_IA];
//      if (max_faze_current_tmp < measurement[IM_IB]) max_faze_current_tmp = measurement[IM_IB];
    if (max_faze_current_tmp < measurement[IM_IC]) max_faze_current_tmp = measurement[IM_IC];
    max_faze_current_tmp = max_faze_current_tmp*current_settings_prt.TCurrent/1000;
  
    if (_CHECK_SET_BIT(active_functions_tmp, RANG_OUTPUT_LED_DF_REG_WORK_BO) == 0)
    {
      //����������� ����� ������ ��
      max_faze_current_vv = max_faze_current_tmp;
    }
    else if (_CHECK_SET_BIT(active_functions_tmp, RANG_OUTPUT_LED_DF_REG_WORK_BO) != 0)
    {
      //�� �������� ���� ������
      if (max_faze_current_vv < max_faze_current_tmp) max_faze_current_vv = max_faze_current_tmp;
    }
    
    if (max_faze_current_vv > current_settings_prt.setpoint_Inom_vymk) 
    {
      _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PEREVYSHCHENNJA_Inom_VYMK);
    }
  }
  /*******************************/
  
  if (
      ((current_settings_prt.control_switch & CTR_RESURS_VV) != 0) &&
      (_CHECK_SET_BIT(active_functions_tmp, RANG_OUTPUT_LED_DF_REG_WORK_BO) != 0) &&
      (_CHECK_SET_BIT(activated_functions , RANG_OUTPUT_LED_DF_REG_WORK_BO) == 0)
     ) 
  {
    //����������� ���������� "������ ��"
    
    /*******************************/
    //������������ ������ �������a
    /*******************************/
    unsigned int N = 0;
    if (max_faze_current_vv >= current_settings_prt.setpoint_Inom_vymk) {
      N = (unsigned int) ceilf((float)current_settings_prt.setpoint_r_kom_st_Inom/(float)current_settings_prt.setpoint_r_kom_st_Inom_vymk);
    } else if (max_faze_current_vv <= current_settings_prt.setpoint_Inom) {
      N = 1;
    } else {
      float I_div_Inom = (float)max_faze_current_vv / (float)current_settings_prt.setpoint_Inom;
      float lg_I_div_Inom = log10f(I_div_Inom);
      float lg_N = K_resurs_prt * lg_I_div_Inom;
      float N_ = powf(10, lg_N);
      N = (unsigned int) ceilf(N_);
      if ((((float)N) - N_) >= 0.5f)
      {
        N--;
      }
      
    }
    
    if (resurs_vymykacha <= N) {
//      _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_VYCHERPANYJ_RESURS_VYMYKACHA);
      resurs_vymykacha = 0;
    } else {
      resurs_vymykacha -= N;
    }
    
    //�������� ����� �����������
    if ((0xffffffff - resurs_vidkljuchennja) >= 1)
    {
      //��������� ������� �� ������� ������������
      resurs_vidkljuchennja++;
    }

    //��������� ����� � EEPROM
    _SET_BIT(control_eeprom_taskes, TASK_START_WRITE_RESURS_EEPROM_BIT);
  }
  
  if (resurs_vymykacha <= current_settings_prt.setpoint_krytychnyj_resurs) {
    _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_KRYTYCHNYJ_RESURS_VYMYKACHA);
  }

  if (resurs_vymykacha == 0) {
    _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_VYCHERPANYJ_RESURS_VYMYKACHA);
  }
}
/*****************************************************/

/*****************************************************/
//�������� �� ����������� ���������� ������ �����������/����������� ����������
/*****************************************************/
inline unsigned int stop_regisrator(unsigned int* carrent_active_functions, unsigned int* ranguvannja_registrator, unsigned int number_group_stp)
{
  unsigned int stop = 0;

  {
    if (
        ((carrent_active_functions[0] & ranguvannja_registrator[0]) == 0) &&
        ((carrent_active_functions[1] & ranguvannja_registrator[1]) == 0) &&
        ((carrent_active_functions[2] & ranguvannja_registrator[2]) == 0) &&
        ((carrent_active_functions[3] & ranguvannja_registrator[3]) == 0) &&
        ((carrent_active_functions[4] & ranguvannja_registrator[4]) == 0) &&
        ((carrent_active_functions[5] & ranguvannja_registrator[5]) == 0)
      )
    {
      //�����������, �� � ���� ������� ��������� ���������� ����� �� �������
      
      if (
          ((carrent_active_functions[0] & MASKA_FOR_CONTINUE_GET_DR_ACTINE_WORD_0) == 0) &&
          ((carrent_active_functions[1] & MASKA_FOR_CONTINUE_GET_DR_ACTINE_WORD_1) == 0) &&
          ((carrent_active_functions[2] & MASKA_FOR_CONTINUE_GET_DR_ACTINE_WORD_2) == 0) &&
          ((carrent_active_functions[3] & MASKA_FOR_CONTINUE_GET_DR_ACTINE_WORD_3) == 0) &&
          ((carrent_active_functions[4] & MASKA_FOR_CONTINUE_GET_DR_ACTINE_WORD_4) == 0) &&
          ((carrent_active_functions[5] & MASKA_FOR_CONTINUE_GET_DR_ACTINE_WORD_5) == 0)
        )
      {
        //�����������, �� �� �������, �� ������ ���������� ��������� �������� ����� ������
          
        //����������, �� �� �������, �� ������� � ����� ����� ��������
        unsigned int global_timers_work = 0, i = INDEX_TIMER_DF_PAUSE_START;
        while ((i < NEXT_TIMER) && (global_timers_work == 0))
        {
          if (global_timers[i] >= 0) 
          {
            if (
                (
                 (i != INDEX_TIMER_PRYVOD_VV) ||
                 (  
                  ((current_settings_prt.control_switch & CTR_PRYVOD_VV) != 0) &&
                  (global_timers[i] < current_settings_prt.timeout_pryvoda_VV) 
                 )   
                ) &&
                (i != INDEX_TIMER_ACHR_CHAPV_100MS_1) && 
                (i != INDEX_TIMER_ACHR_CHAPV_100MS_2) &&
                (
                 (i != INDEX_TIMER_APV_ZMN3) ||
                 (global_timers[INDEX_TIMER_APV_ZMN3] < current_settings_prt.timeout_apv_zmn_zavershennja[number_group_stp])  
                ) &&
                (
                 (i != INDEX_TIMER_AVR_ZAVERSHENNJA) ||
                 (global_timers[INDEX_TIMER_AVR_ZAVERSHENNJA] < current_settings_prt.timeout_avr_zavershennja[number_group_stp])  
                ) &&
                (
                 (i != INDEX_TIMER_AVR_RESET_BLK) ||
                 (global_timers[INDEX_TIMER_AVR_RESET_BLK] < current_settings_prt.timeout_avr_reset_blk[number_group_stp])  
                ) &&
                (
                 (
                  (i != INDEX_TIMER_U_OL1) &&
                  (i != INDEX_TIMER_U_OL2)
                 ) ||   
                 (global_timers[i] < current_settings_prt.timeout_U_ol[number_group_stp])  
                ) &&
                (
                 (
                  (i != INDEX_TIMER_U_RL1) &&
                  (i != INDEX_TIMER_U_RL2)
                 ) ||   
                 (global_timers[i] < current_settings_prt.timeout_U_rl[number_group_stp])  
                )
               )
            global_timers_work = 1;
          }
          i++;
        }
          
        if (global_timers_work == 0)
        {
          //�����������, �� �� �������, �� �������� � ����� ��������
        
          //�������, �� ��������� ���� ���� ���������
          stop = 0xff;
        }
      }
    }
  }
  
  return stop;
}
/*****************************************************/

/*****************************************************/
//����������� ����������� ������� ������ ����������� ����������
/*****************************************************/
void fix_undefined_error_dr(unsigned int* carrent_active_functions)
{
  //����������� ������� � ������� � ��������� ���������
  _SET_BIT(set_diagnostyka, ERROR_DR_UNDEFINED_BIT);
  _SET_BIT(carrent_active_functions, RANG_OUTPUT_LED_DF_REG_DEFECT);
  //���������� ����� ������ � ����������� � ���� "�� ����� ������ ���� �� � ���������� ����������� �� ����������" 
  state_dr_record = STATE_DR_NO_RECORD;
  //������� ������ ������ ����������� ����������
  _CLEAR_BIT(carrent_active_functions, RANG_OUTPUT_LED_DF_REG_WORK_D_REJESTRATOR);
}
/*****************************************************/

/*****************************************************/
//������� ���������� ������������� ������� ������ 
/*****************************************************/
inline void start_monitoring_max_phase_current(unsigned int time_tmp)
{
  //�������� ������� ���������� ������� ������������� ������� ������
  number_max_phase_dr++;
  
  //�������, �� ����� �������� � ����, �� ����� �������� ����� ��������� �����������, ���� �������� �� �� ��������
  int frequency_val_1_int = (int)frequency_val_1;
  if (frequency_val_1_int >= 0) frequency_val_1_int = (int)(frequency_val_1*1000);
  
  int frequency_val_2_int = (int)frequency_val_2;
  if (frequency_val_2_int >= 0) frequency_val_2_int = (int)(frequency_val_2*1000);

  measurements_phase_max_dr[ 0] = measurement[IM_3I0];
  measurements_phase_max_dr[ 1] = measurement[IM_3I0_other_g];
  measurements_phase_max_dr[ 2] = measurement[IM_IA];
  measurements_phase_max_dr[ 3] = measurement[IM_IC];
  measurements_phase_max_dr[ 4] = measurement[IM_IB_r];
  measurements_phase_max_dr [5] = measurement[IM_I2];
  measurements_phase_max_dr[ 6] = measurement[IM_I1];
  measurements_phase_max_dr[ 7] = measurement[IM_UA];
  measurements_phase_max_dr[ 8] = measurement[IM_UB];
  measurements_phase_max_dr[ 9] = measurement[IM_UC];
  measurements_phase_max_dr[10] = measurement[IM_3U0_UBC_TN2];
  measurements_phase_max_dr[11] = measurement[IM_UAB_TN2];
  measurements_phase_max_dr[12] = measurement[IM_UAB];
  measurements_phase_max_dr[13] = measurement[IM_UBC];
  measurements_phase_max_dr[14] = measurement[IM_UCA];
  measurements_phase_max_dr[15] = (unsigned int)frequency_val_1_int;
  measurements_phase_max_dr[16] = (unsigned int)frequency_val_2_int;
  measurements_phase_max_dr[17] = (unsigned int)resistance[R_AB];
  measurements_phase_max_dr[18] = (unsigned int)resistance[X_AB];
  measurements_phase_max_dr[19] = (unsigned int)resistance[R_BC];
  measurements_phase_max_dr[20] = (unsigned int)resistance[X_BC];
  measurements_phase_max_dr[21] = (unsigned int)resistance[R_CA];
  measurements_phase_max_dr[22] = (unsigned int)resistance[X_CA];
  measurements_phase_max_dr[23] = (unsigned int)UNDEF_VMP;
  measurements_phase_max_dr[24] = 0;
  
  //��������� ����������� ������ ����� �� ������ ������
  max_phase_current_dr = measurements_phase_max_dr[2];
  if (max_phase_current_dr < measurements_phase_max_dr[3]) max_phase_current_dr = measurements_phase_max_dr[3];
  if (max_phase_current_dr < measurements_phase_max_dr[4]) max_phase_current_dr = measurements_phase_max_dr[4];

  //Գ����� ��� � ������� ������� ��������� ������
  measurements_phase_max_dr[25] = time_tmp;

  //�������, �� �� �� ���䳿 ���������� ������������� ������� ������
  state_current_monitoring |= (1<<IDENTIFIER_BIT_ARRAY_MAX_CURRENT_PHASE);
}
/*****************************************************/

/*****************************************************/
//����������� ���������� ������������� ������� ������
/*****************************************************/
inline void continue_monitoring_max_phase_current(unsigned int time_tmp)
{
  //��������, �� �� � ����� ������ ����� ������, �� ��� �� �������� ������������
  if (
      (max_phase_current_dr < measurement[IM_IA  ]) ||
      (max_phase_current_dr < measurement[IM_IB_r]) ||
      (max_phase_current_dr < measurement[IM_IC  ])
     )
  {
    //����������� ��� ��� ��������� �������� ����� � ������� ������� ������������� �� ���
    int frequency_val_1_int = (int)frequency_val_1;
    if (frequency_val_1_int >= 0) frequency_val_1_int = (int)(frequency_val_1*1000);
  
    int frequency_val_2_int = (int)frequency_val_2;
    if (frequency_val_2_int >= 0) frequency_val_2_int = (int)(frequency_val_2*1000);

    measurements_phase_max_dr[ 0] = measurement[IM_3I0];
    measurements_phase_max_dr[ 1] = measurement[IM_3I0_other_g];
    measurements_phase_max_dr[ 2] = measurement[IM_IA];
    measurements_phase_max_dr[ 3] = measurement[IM_IC];
    measurements_phase_max_dr[ 4] = measurement[IM_IB_r];
    measurements_phase_max_dr [5] = measurement[IM_I2];
    measurements_phase_max_dr[ 6] = measurement[IM_I1];
    measurements_phase_max_dr[ 7] = measurement[IM_UA];
    measurements_phase_max_dr[ 8] = measurement[IM_UB];
    measurements_phase_max_dr[ 9] = measurement[IM_UC];
    measurements_phase_max_dr[10] = measurement[IM_3U0_UBC_TN2];
    measurements_phase_max_dr[11] = measurement[IM_UAB_TN2];
    measurements_phase_max_dr[12] = measurement[IM_UAB];
    measurements_phase_max_dr[13] = measurement[IM_UBC];
    measurements_phase_max_dr[14] = measurement[IM_UCA];
    measurements_phase_max_dr[15] = (unsigned int)frequency_val_1_int;
    measurements_phase_max_dr[16] = (unsigned int)frequency_val_2_int;
    measurements_phase_max_dr[17] = (unsigned int)resistance[R_AB];
    measurements_phase_max_dr[18] = (unsigned int)resistance[X_AB];
    measurements_phase_max_dr[19] = (unsigned int)resistance[R_BC];
    measurements_phase_max_dr[20] = (unsigned int)resistance[X_BC];
    measurements_phase_max_dr[21] = (unsigned int)resistance[R_CA];
    measurements_phase_max_dr[22] = (unsigned int)resistance[X_CA];

    max_phase_current_dr = measurements_phase_max_dr[2];
    if (max_phase_current_dr < measurements_phase_max_dr[3]) max_phase_current_dr = measurements_phase_max_dr[3];
    if (max_phase_current_dr < measurements_phase_max_dr[4]) max_phase_current_dr = measurements_phase_max_dr[4];

    //Գ����� ��� � ������� ������� ��������� ������
    measurements_phase_max_dr[25] = time_tmp;
  }
}
/*****************************************************/

/*****************************************************/
//������� ���������� ������������� ������ 3I0
/*****************************************************/
inline void start_monitoring_max_3I0(unsigned int time_tmp)
{
  //�������� ������� ���������� ������� ������������� 3I0
  number_max_3I0_dr++;
  
  //�������, �� ����� �������� � ����, �� ����� �������� ����� ��������� �����������, ���� �������� �� �� ��������
  int frequency_val_1_int = (int)frequency_val_1;
  if (frequency_val_1_int >= 0) frequency_val_1_int = (int)(frequency_val_1*1000);
  
  int frequency_val_2_int = (int)frequency_val_2;
  if (frequency_val_2_int >= 0) frequency_val_2_int = (int)(frequency_val_2*1000);

  measurements_3I0_max_dr[ 0] = measurement[IM_3I0];
  measurements_3I0_max_dr[ 1] = measurement[IM_3I0_other_g];
  measurements_3I0_max_dr[ 2] = measurement[IM_IA];
  measurements_3I0_max_dr[ 3] = measurement[IM_IC];
  measurements_3I0_max_dr[ 4] = measurement[IM_IB_r];
  measurements_3I0_max_dr [5] = measurement[IM_I2];
  measurements_3I0_max_dr[ 6] = measurement[IM_I1];
  measurements_3I0_max_dr[ 7] = measurement[IM_UA];
  measurements_3I0_max_dr[ 8] = measurement[IM_UB];
  measurements_3I0_max_dr[ 9] = measurement[IM_UC];
  measurements_3I0_max_dr[10] = measurement[IM_3U0_UBC_TN2];
  measurements_3I0_max_dr[11] = measurement[IM_UAB_TN2];
  measurements_3I0_max_dr[12] = measurement[IM_UAB];
  measurements_3I0_max_dr[13] = measurement[IM_UBC];
  measurements_3I0_max_dr[14] = measurement[IM_UCA];
  measurements_3I0_max_dr[15] = (unsigned int)frequency_val_1_int;
  measurements_3I0_max_dr[16] = (unsigned int)frequency_val_2_int;
  measurements_3I0_max_dr[17] = (unsigned int)resistance[R_AB];
  measurements_3I0_max_dr[18] = (unsigned int)resistance[X_AB];
  measurements_3I0_max_dr[19] = (unsigned int)resistance[R_BC];
  measurements_3I0_max_dr[20] = (unsigned int)resistance[X_BC];
  measurements_3I0_max_dr[21] = (unsigned int)resistance[R_CA];
  measurements_3I0_max_dr[22] = (unsigned int)resistance[X_CA];
  measurements_3I0_max_dr[23] = (unsigned int)UNDEF_VMP;
  measurements_3I0_max_dr[24] = 0;
  
  //Գ����� ��� � ������� ������� ��������� ������
  measurements_3I0_max_dr[25] = time_tmp;
  
  //�������, �� �� �� ���䳿 ���������� ������������� ������ 3I0
  state_current_monitoring |= (1<<IDENTIFIER_BIT_ARRAY_MAX_CURRENT_3I0);
}
/*****************************************************/

/*****************************************************/
//����������� ���������� ������������� ������ 3I0
/*****************************************************/
inline void continue_monitoring_max_3I0(unsigned int time_tmp)
{
  //��������, �� �� � ����� ����� 3I0 ������, �� ��� �� �������� ������������
  if(
     ((current_settings_prt.control_zz & CTR_ZZ1_TYPE) == 0) && (measurements_3I0_max_dr[0] < measurement[IM_3I0])        ||
     ((current_settings_prt.control_zz & CTR_ZZ1_TYPE) != 0) && (measurements_3I0_max_dr[1] < measurement[IM_3I0_other_g])
    )
  {
    //����������� ��� ��� ��������� ����� 3I0 � ������� ������������� �� ���
    int frequency_val_1_int = (int)frequency_val_1;
    if (frequency_val_1_int >= 0) frequency_val_1_int = (int)(frequency_val_1*1000);
  
    int frequency_val_2_int = (int)frequency_val_2;
    if (frequency_val_2_int >= 0) frequency_val_2_int = (int)(frequency_val_2*1000);

    measurements_3I0_max_dr[ 0] = measurement[IM_3I0];
    measurements_3I0_max_dr[ 1] = measurement[IM_3I0_other_g];
    measurements_3I0_max_dr[ 2] = measurement[IM_IA];
    measurements_3I0_max_dr[ 3] = measurement[IM_IC];
    measurements_3I0_max_dr[ 4] = measurement[IM_IB_r];
    measurements_3I0_max_dr [5] = measurement[IM_I2];
    measurements_3I0_max_dr[ 6] = measurement[IM_I1];
    measurements_3I0_max_dr[ 7] = measurement[IM_UA];
    measurements_3I0_max_dr[ 8] = measurement[IM_UB];
    measurements_3I0_max_dr[ 9] = measurement[IM_UC];
    measurements_3I0_max_dr[10] = measurement[IM_3U0_UBC_TN2];
    measurements_3I0_max_dr[11] = measurement[IM_UAB_TN2];
    measurements_3I0_max_dr[12] = measurement[IM_UAB];
    measurements_3I0_max_dr[13] = measurement[IM_UBC];
    measurements_3I0_max_dr[14] = measurement[IM_UCA];
    measurements_3I0_max_dr[15] = (unsigned int)frequency_val_1_int;
    measurements_3I0_max_dr[16] = (unsigned int)frequency_val_2_int;
    measurements_3I0_max_dr[17] = (unsigned int)resistance[R_AB];
    measurements_3I0_max_dr[18] = (unsigned int)resistance[X_AB];
    measurements_3I0_max_dr[19] = (unsigned int)resistance[R_BC];
    measurements_3I0_max_dr[20] = (unsigned int)resistance[X_BC];
    measurements_3I0_max_dr[21] = (unsigned int)resistance[R_CA];
    measurements_3I0_max_dr[22] = (unsigned int)resistance[X_CA];

    //Գ����� ��� � ������� ������� ��������� ������
    measurements_3I0_max_dr[25] = time_tmp;
  }
}
/*****************************************************/

/*****************************************************/
//������� ���������� ����������� ������� 3U0
/*****************************************************/
inline void start_monitoring_max_3U0(unsigned int time_tmp)
{
  //�������� ������� ���������� ������� ����������� 3U0
  number_max_3U0_dr++;
  
  //�������, �� ����� �������� � ����, �� ����� �������� ����� ��������� �����������, ���� �������� �� �� ��������
  int frequency_val_1_int = (int)frequency_val_1;
  if (frequency_val_1_int >= 0) frequency_val_1_int = (int)(frequency_val_1*1000);
  
  int frequency_val_2_int = (int)frequency_val_2;
  if (frequency_val_2_int >= 0) frequency_val_2_int = (int)(frequency_val_2*1000);

  measurements_3U0_max_dr[ 0] = measurement[IM_3I0];
  measurements_3U0_max_dr[ 1] = measurement[IM_3I0_other_g];
  measurements_3U0_max_dr[ 2] = measurement[IM_IA];
  measurements_3U0_max_dr[ 3] = measurement[IM_IC];
  measurements_3U0_max_dr[ 4] = measurement[IM_IB_r];
  measurements_3U0_max_dr [5] = measurement[IM_I2];
  measurements_3U0_max_dr[ 6] = measurement[IM_I1];
  measurements_3U0_max_dr[ 7] = measurement[IM_UA];
  measurements_3U0_max_dr[ 8] = measurement[IM_UB];
  measurements_3U0_max_dr[ 9] = measurement[IM_UC];
  measurements_3U0_max_dr[10] = measurement[IM_3U0_UBC_TN2];
  measurements_3U0_max_dr[11] = measurement[IM_UAB_TN2];
  measurements_3U0_max_dr[12] = measurement[IM_UAB];
  measurements_3U0_max_dr[13] = measurement[IM_UBC];
  measurements_3U0_max_dr[14] = measurement[IM_UCA];
  measurements_3U0_max_dr[15] = (unsigned int)frequency_val_1_int;
  measurements_3U0_max_dr[16] = (unsigned int)frequency_val_2_int;
  measurements_3U0_max_dr[17] = (unsigned int)resistance[R_AB];
  measurements_3U0_max_dr[18] = (unsigned int)resistance[X_AB];
  measurements_3U0_max_dr[19] = (unsigned int)resistance[R_BC];
  measurements_3U0_max_dr[20] = (unsigned int)resistance[X_BC];
  measurements_3U0_max_dr[21] = (unsigned int)resistance[R_CA];
  measurements_3U0_max_dr[22] = (unsigned int)resistance[X_CA];
  measurements_3U0_max_dr[23] = (unsigned int)UNDEF_VMP;
  measurements_3U0_max_dr[24] = 0;
  
  //Գ����� ��� � ������� ������� ��������� ������
  measurements_3U0_max_dr[25] = time_tmp;
  
  //�������, �� �� �� ���䳿 ���������� ����������� ������� 3U0
  state_current_monitoring |= (1<<IDENTIFIER_BIT_ARRAY_MAX_VOLTAGE_3U0);
}
/*****************************************************/

/*****************************************************/
//����������� ���������� ������������� ������ 3U0
/*****************************************************/
inline void continue_monitoring_max_3U0(unsigned int time_tmp)
{
  //��������, �� �� � ����� ������� 3U0 �����, �� �� �� ������� ������������
  if(measurements_3U0_max_dr[10] < measurement[IM_3U0_UBC_TN2])
  {
    //����������� ��� ��� ��������� ����� 3I0 � ������� ������������� �� ���
    int frequency_val_1_int = (int)frequency_val_1;
    if (frequency_val_1_int >= 0) frequency_val_1_int = (int)(frequency_val_1*1000);
  
    int frequency_val_2_int = (int)frequency_val_2;
    if (frequency_val_2_int >= 0) frequency_val_2_int = (int)(frequency_val_2*1000);

    measurements_3U0_max_dr[ 0] = measurement[IM_3I0];
    measurements_3U0_max_dr[ 1] = measurement[IM_3I0_other_g];
    measurements_3U0_max_dr[ 2] = measurement[IM_IA];
    measurements_3U0_max_dr[ 3] = measurement[IM_IC];
    measurements_3U0_max_dr[ 4] = measurement[IM_IB_r];
    measurements_3U0_max_dr [5] = measurement[IM_I2];
    measurements_3U0_max_dr[ 6] = measurement[IM_I1];
    measurements_3U0_max_dr[ 7] = measurement[IM_UA];
    measurements_3U0_max_dr[ 8] = measurement[IM_UB];
    measurements_3U0_max_dr[ 9] = measurement[IM_UC];
    measurements_3U0_max_dr[10] = measurement[IM_3U0_UBC_TN2];
    measurements_3U0_max_dr[11] = measurement[IM_UAB_TN2];
    measurements_3U0_max_dr[12] = measurement[IM_UAB];
    measurements_3U0_max_dr[13] = measurement[IM_UBC];
    measurements_3U0_max_dr[14] = measurement[IM_UCA];
    measurements_3U0_max_dr[15] = (unsigned int)frequency_val_1_int;
    measurements_3U0_max_dr[16] = (unsigned int)frequency_val_2_int;
    measurements_3U0_max_dr[17] = (unsigned int)resistance[R_AB];
    measurements_3U0_max_dr[18] = (unsigned int)resistance[X_AB];
    measurements_3U0_max_dr[19] = (unsigned int)resistance[R_BC];
    measurements_3U0_max_dr[20] = (unsigned int)resistance[X_BC];
    measurements_3U0_max_dr[21] = (unsigned int)resistance[R_CA];
    measurements_3U0_max_dr[22] = (unsigned int)resistance[X_CA];

    //Գ����� ��� � ������� ������� ��������� ������
    measurements_3U0_max_dr[25] = time_tmp;
  }
}
/*****************************************************/

/*****************************************************/
//������� ���������� �������� �����/����� ������� 
/*****************************************************/
inline void start_monitoring_min_U(unsigned int time_tmp)
{
  //�������� ������� ���������� ������� �������� �����/����� �������
  number_min_U_dr++;
  
  //�������, �� ����� �������� � ����, �� ����� �������� ����� ��������� �����������, ���� �������� �� �� ��������
  int frequency_val_1_int = (int)frequency_val_1;
  if (frequency_val_1_int >= 0) frequency_val_1_int = (int)(frequency_val_1*1000);
  
  int frequency_val_2_int = (int)frequency_val_2;
  if (frequency_val_2_int >= 0) frequency_val_2_int = (int)(frequency_val_2*1000);

  measurements_U_min_dr[ 0] = measurement[IM_3I0];
  measurements_U_min_dr[ 1] = measurement[IM_3I0_other_g];
  measurements_U_min_dr[ 2] = measurement[IM_IA];
  measurements_U_min_dr[ 3] = measurement[IM_IC];
  measurements_U_min_dr[ 4] = measurement[IM_IB_r];
  measurements_U_min_dr [5] = measurement[IM_I2];
  measurements_U_min_dr[ 6] = measurement[IM_I1];
  measurements_U_min_dr[ 7] = measurement[IM_UA];
  measurements_U_min_dr[ 8] = measurement[IM_UB];
  measurements_U_min_dr[ 9] = measurement[IM_UC];
  measurements_U_min_dr[10] = measurement[IM_3U0_UBC_TN2];
  measurements_U_min_dr[11] = measurement[IM_UAB_TN2];
  measurements_U_min_dr[12] = measurement[IM_UAB];
  measurements_U_min_dr[13] = measurement[IM_UBC];
  measurements_U_min_dr[14] = measurement[IM_UCA];
  measurements_U_min_dr[15] = (unsigned int)frequency_val_1_int;
  measurements_U_min_dr[16] = (unsigned int)frequency_val_2_int;
  measurements_U_min_dr[17] = (unsigned int)resistance[R_AB];
  measurements_U_min_dr[18] = (unsigned int)resistance[X_AB];
  measurements_U_min_dr[19] = (unsigned int)resistance[R_BC];
  measurements_U_min_dr[20] = (unsigned int)resistance[X_BC];
  measurements_U_min_dr[21] = (unsigned int)resistance[R_CA];
  measurements_U_min_dr[22] = (unsigned int)resistance[X_CA];
  measurements_U_min_dr[23] = (unsigned int)UNDEF_VMP;
  measurements_U_min_dr[24] = 0;
  
  if ((current_settings_prt.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_PHASE_LINE) == 0)
  {
    //��������� �������� ����� ������� �� ������ ������
    min_voltage_dr = measurements_U_min_dr[7];
    if (min_voltage_dr > measurements_U_min_dr[8]) min_voltage_dr = measurements_U_min_dr[8];
    if (min_voltage_dr > measurements_U_min_dr[9]) min_voltage_dr = measurements_U_min_dr[9];
  }
  else
  {
    //��������� �������� ����� ������� �� ������ ������
    min_voltage_dr = measurements_U_min_dr[12];
    if (min_voltage_dr > measurements_U_min_dr[13]) min_voltage_dr = measurements_U_min_dr[13];
    if (min_voltage_dr > measurements_U_min_dr[14]) min_voltage_dr = measurements_U_min_dr[14];
  }

  //Գ����� ��� � ������� ������� ��������� ������
  measurements_U_min_dr[25] = time_tmp;

  //�������, �� �� �� ���䳿 ���������� �������� �����/����� �������
  state_current_monitoring |= (1<<IDENTIFIER_BIT_ARRAY_MIN_VOLTAGE);
}
/*****************************************************/

/*****************************************************/
//����������� ���������� �������� �����/����� �������
/*****************************************************/
inline void continue_monitoring_min_U(unsigned int time_tmp)
{
  //��������, �� �� � ����� ����������� ������ �����, �� �� �� ������� ���������
  if (
      (
       ((current_settings_prt.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_PHASE_LINE) == 0) &&
       (  
        (min_voltage_dr > measurement[IM_UA]) ||
        (min_voltage_dr > measurement[IM_UB]) ||
        (min_voltage_dr > measurement[IM_UC])
       )
      )   
      || 
      (
       ((current_settings_prt.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_PHASE_LINE) != 0) &&
       (  
        (min_voltage_dr > measurement[IM_UAB]) ||
        (min_voltage_dr > measurement[IM_UBC]) ||
        (min_voltage_dr > measurement[IM_UCA])
       )
     )
    )    
  {
    //����������� ��� ��� ��������� ����������� ������ � ������� ������� ������������� �� ���
    int frequency_val_1_int = (int)frequency_val_1;
    if (frequency_val_1_int >= 0) frequency_val_1_int = (int)(frequency_val_1*1000);
  
    int frequency_val_2_int = (int)frequency_val_2;
    if (frequency_val_2_int >= 0) frequency_val_2_int = (int)(frequency_val_2*1000);

    measurements_U_min_dr[ 0] = measurement[IM_3I0];
    measurements_U_min_dr[ 1] = measurement[IM_3I0_other_g];
    measurements_U_min_dr[ 2] = measurement[IM_IA];
    measurements_U_min_dr[ 3] = measurement[IM_IC];
    measurements_U_min_dr[ 4] = measurement[IM_IB_r];
    measurements_U_min_dr [5] = measurement[IM_I2];
    measurements_U_min_dr[ 6] = measurement[IM_I1];
    measurements_U_min_dr[ 7] = measurement[IM_UA];
    measurements_U_min_dr[ 8] = measurement[IM_UB];
    measurements_U_min_dr[ 9] = measurement[IM_UC];
    measurements_U_min_dr[10] = measurement[IM_3U0_UBC_TN2];
    measurements_U_min_dr[11] = measurement[IM_UAB_TN2];
    measurements_U_min_dr[12] = measurement[IM_UAB];
    measurements_U_min_dr[13] = measurement[IM_UBC];
    measurements_U_min_dr[14] = measurement[IM_UCA];
    measurements_U_min_dr[15] = (unsigned int)frequency_val_1_int;
    measurements_U_min_dr[16] = (unsigned int)frequency_val_2_int;
    measurements_U_min_dr[17] = (unsigned int)resistance[R_AB];
    measurements_U_min_dr[18] = (unsigned int)resistance[X_AB];
    measurements_U_min_dr[19] = (unsigned int)resistance[R_BC];
    measurements_U_min_dr[20] = (unsigned int)resistance[X_BC];
    measurements_U_min_dr[21] = (unsigned int)resistance[R_CA];
    measurements_U_min_dr[22] = (unsigned int)resistance[X_CA];

    if ((current_settings_prt.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_PHASE_LINE) == 0)
    {
      //��������� �������� ����� ������� �� ������ ������
      min_voltage_dr = measurements_U_min_dr[7];
      if (min_voltage_dr > measurements_U_min_dr[8]) min_voltage_dr = measurements_U_min_dr[8];
      if (min_voltage_dr > measurements_U_min_dr[9]) min_voltage_dr = measurements_U_min_dr[9];
    }
    else
    {
      //��������� �������� ����� ������� �� ������ ������
      min_voltage_dr = measurements_U_min_dr[12];
      if (min_voltage_dr > measurements_U_min_dr[13]) min_voltage_dr = measurements_U_min_dr[13];
      if (min_voltage_dr > measurements_U_min_dr[14]) min_voltage_dr = measurements_U_min_dr[14];
    }

    //Գ����� ��� � ������� ������� ��������� ������
    measurements_U_min_dr[25] = time_tmp;
  }
}
/*****************************************************/

/*****************************************************/
//������� ���������� ����������� �����/����� ������� 
/*****************************************************/
inline void start_monitoring_max_U(unsigned int time_tmp)
{
  //�������� ������� ���������� ������� ����������� �����/����� �������
  number_max_U_dr++;
  
  //�������, �� ����� �������� � ����, �� ����� �������� ����� ��������� �����������, ���� �������� �� �� ��������
  int frequency_val_1_int = (int)frequency_val_1;
  if (frequency_val_1_int >= 0) frequency_val_1_int = (int)(frequency_val_1*1000);
  
  int frequency_val_2_int = (int)frequency_val_2;
  if (frequency_val_2_int >= 0) frequency_val_2_int = (int)(frequency_val_2*1000);

  measurements_U_max_dr[ 0] = measurement[IM_3I0];
  measurements_U_max_dr[ 1] = measurement[IM_3I0_other_g];
  measurements_U_max_dr[ 2] = measurement[IM_IA];
  measurements_U_max_dr[ 3] = measurement[IM_IC];
  measurements_U_max_dr[ 4] = measurement[IM_IB_r];
  measurements_U_max_dr [5] = measurement[IM_I2];
  measurements_U_max_dr[ 6] = measurement[IM_I1];
  measurements_U_max_dr[ 7] = measurement[IM_UA];
  measurements_U_max_dr[ 8] = measurement[IM_UB];
  measurements_U_max_dr[ 9] = measurement[IM_UC];
  measurements_U_max_dr[10] = measurement[IM_3U0_UBC_TN2];
  measurements_U_max_dr[11] = measurement[IM_UAB_TN2];
  measurements_U_max_dr[12] = measurement[IM_UAB];
  measurements_U_max_dr[13] = measurement[IM_UBC];
  measurements_U_max_dr[14] = measurement[IM_UCA];
  measurements_U_max_dr[15] = (unsigned int)frequency_val_1_int;
  measurements_U_max_dr[16] = (unsigned int)frequency_val_2_int;
  measurements_U_max_dr[17] = (unsigned int)resistance[R_AB];
  measurements_U_max_dr[18] = (unsigned int)resistance[X_AB];
  measurements_U_max_dr[19] = (unsigned int)resistance[R_BC];
  measurements_U_max_dr[20] = (unsigned int)resistance[X_BC];
  measurements_U_max_dr[21] = (unsigned int)resistance[R_CA];
  measurements_U_max_dr[22] = (unsigned int)resistance[X_CA];
  measurements_U_max_dr[23] = (unsigned int)UNDEF_VMP;
  measurements_U_max_dr[24] = 0;
  
  if ((current_settings_prt.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_PHASE_LINE) == 0)
  {
    //��������� ���������� ����� ������� �� ������ ������
    max_voltage_dr = measurements_U_max_dr[7];
    if (max_voltage_dr < measurements_U_max_dr[8]) max_voltage_dr = measurements_U_max_dr[8];
    if (max_voltage_dr < measurements_U_max_dr[9]) max_voltage_dr = measurements_U_max_dr[9];
  }
  else
  {
    //��������� ���������� ����� ������� �� ������ ������
    max_voltage_dr = measurements_U_max_dr[12];
    if (max_voltage_dr < measurements_U_max_dr[13]) max_voltage_dr = measurements_U_max_dr[13];
    if (max_voltage_dr < measurements_U_max_dr[14]) max_voltage_dr = measurements_U_max_dr[14];
  }

  //Գ����� ��� � ������� ������� ��������� ������
  measurements_U_max_dr[25] = time_tmp;

  //�������, �� �� �� ���䳿 ���������� ����������� �����/����� �������
  state_current_monitoring |= (1<<IDENTIFIER_BIT_ARRAY_MAX_VOLTAGE);
}
/*****************************************************/

/*****************************************************/
//����������� ���������� ����������� �����/����� �������
/*****************************************************/
inline void continue_monitoring_max_U(unsigned int time_tmp)
{
  //��������, �� �� � ����� ����������� ������ �����, �� �� �� ������� ������������
  if (
      (
       ((current_settings_prt.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_PHASE_LINE) == 0) &&
       (  
        (max_voltage_dr < measurement[IM_UA]) ||
        (max_voltage_dr < measurement[IM_UB]) ||
        (max_voltage_dr < measurement[IM_UC])
       )
      )   
      || 
      (
       ((current_settings_prt.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_PHASE_LINE) != 0) &&
       (  
        (max_voltage_dr < measurement[IM_UAB]) ||
        (max_voltage_dr < measurement[IM_UBC]) ||
        (max_voltage_dr < measurement[IM_UCA])
       )
     )
    )    
  {
    //����������� ��� ��� ��������� ����������� ������ � ������� ������� ������������� �� ���
    int frequency_val_1_int = (int)frequency_val_1;
    if (frequency_val_1_int >= 0) frequency_val_1_int = (int)(frequency_val_1*1000);
  
    int frequency_val_2_int = (int)frequency_val_2;
    if (frequency_val_2_int >= 0) frequency_val_2_int = (int)(frequency_val_2*1000);

    measurements_U_max_dr[ 0] = measurement[IM_3I0];
    measurements_U_max_dr[ 1] = measurement[IM_3I0_other_g];
    measurements_U_max_dr[ 2] = measurement[IM_IA];
    measurements_U_max_dr[ 3] = measurement[IM_IC];
    measurements_U_max_dr[ 4] = measurement[IM_IB_r];
    measurements_U_max_dr [5] = measurement[IM_I2];
    measurements_U_max_dr[ 6] = measurement[IM_I1];
    measurements_U_max_dr[ 7] = measurement[IM_UA];
    measurements_U_max_dr[ 8] = measurement[IM_UB];
    measurements_U_max_dr[ 9] = measurement[IM_UC];
    measurements_U_max_dr[10] = measurement[IM_3U0_UBC_TN2];
    measurements_U_max_dr[11] = measurement[IM_UAB_TN2];
    measurements_U_max_dr[12] = measurement[IM_UAB];
    measurements_U_max_dr[13] = measurement[IM_UBC];
    measurements_U_max_dr[14] = measurement[IM_UCA];
    measurements_U_max_dr[15] = (unsigned int)frequency_val_1_int;
    measurements_U_max_dr[16] = (unsigned int)frequency_val_2_int;
    measurements_U_max_dr[17] = (unsigned int)resistance[R_AB];
    measurements_U_max_dr[18] = (unsigned int)resistance[X_AB];
    measurements_U_max_dr[19] = (unsigned int)resistance[R_BC];
    measurements_U_max_dr[20] = (unsigned int)resistance[X_BC];
    measurements_U_max_dr[21] = (unsigned int)resistance[R_CA];
    measurements_U_max_dr[22] = (unsigned int)resistance[X_CA];

    if ((current_settings_prt.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_PHASE_LINE) == 0)
    {
      //��������� ���������� ����� ������� �� ������ ������
      max_voltage_dr = measurements_U_max_dr[7];
      if (max_voltage_dr < measurements_U_max_dr[8]) max_voltage_dr = measurements_U_max_dr[8];
      if (max_voltage_dr < measurements_U_max_dr[9]) max_voltage_dr = measurements_U_max_dr[9];
    }
    else
    {
      //��������� ���������� ����� ������� �� ������ ������
      max_voltage_dr = measurements_U_max_dr[12];
      if (max_voltage_dr < measurements_U_max_dr[13]) max_voltage_dr = measurements_U_max_dr[13];
      if (max_voltage_dr < measurements_U_max_dr[14]) max_voltage_dr = measurements_U_max_dr[14];
    }

    //Գ����� ��� � ������� ������� ��������� ������
    measurements_U_max_dr[25] = time_tmp;
  }
}
/*****************************************************/

/*****************************************************/
//������� ���������� ������������� ������  ��������� �����������
/*****************************************************/
inline void start_monitoring_max_ZOP(unsigned int time_tmp)
{
  //�������� ������� ���������� ������� ������������� 3I0
  number_max_ZOP_dr++;
  
  //�������, �� ����� �������� � ����, �� ����� �������� ����� ��������� �����������, ���� �������� �� �� ��������
  int frequency_val_1_int = (int)frequency_val_1;
  if (frequency_val_1_int >= 0) frequency_val_1_int = (int)(frequency_val_1*1000);
  
  int frequency_val_2_int = (int)frequency_val_2;
  if (frequency_val_2_int >= 0) frequency_val_2_int = (int)(frequency_val_2*1000);

  measurements_ZOP_max_dr[ 0] = measurement[IM_3I0];
  measurements_ZOP_max_dr[ 1] = measurement[IM_3I0_other_g];
  measurements_ZOP_max_dr[ 2] = measurement[IM_IA];
  measurements_ZOP_max_dr[ 3] = measurement[IM_IC];
  measurements_ZOP_max_dr[ 4] = measurement[IM_IB_r];
  measurements_ZOP_max_dr [5] = measurement[IM_I2];
  measurements_ZOP_max_dr[ 6] = measurement[IM_I1];
  measurements_ZOP_max_dr[ 7] = measurement[IM_UA];
  measurements_ZOP_max_dr[ 8] = measurement[IM_UB];
  measurements_ZOP_max_dr[ 9] = measurement[IM_UC];
  measurements_ZOP_max_dr[10] = measurement[IM_3U0_UBC_TN2];
  measurements_ZOP_max_dr[11] = measurement[IM_UAB_TN2];
  measurements_ZOP_max_dr[12] = measurement[IM_UAB];
  measurements_ZOP_max_dr[13] = measurement[IM_UBC];
  measurements_ZOP_max_dr[14] = measurement[IM_UCA];
  measurements_ZOP_max_dr[15] = (unsigned int)frequency_val_1_int;
  measurements_ZOP_max_dr[16] = (unsigned int)frequency_val_2_int;
  measurements_ZOP_max_dr[17] = (unsigned int)resistance[R_AB];
  measurements_ZOP_max_dr[18] = (unsigned int)resistance[X_AB];
  measurements_ZOP_max_dr[19] = (unsigned int)resistance[R_BC];
  measurements_ZOP_max_dr[20] = (unsigned int)resistance[X_BC];
  measurements_ZOP_max_dr[21] = (unsigned int)resistance[R_CA];
  measurements_ZOP_max_dr[22] = (unsigned int)resistance[X_CA];
  measurements_ZOP_max_dr[23] = (unsigned int)UNDEF_VMP;
  measurements_ZOP_max_dr[24] = 0;

  //Գ����� ��� � ������� ������� ��������� ������
  measurements_ZOP_max_dr[25] = time_tmp;

  //�������, �� �� �� ���䳿 ���������� ������������� ������ ��������� �����������
  state_current_monitoring |= (1<<IDENTIFIER_BIT_ARRAY_MAX_CURRENT_ZOP);
}
/*****************************************************/

/*****************************************************/
//����������� ���������� ������������� ������ ��������� �����������
/*****************************************************/
inline void continue_monitoring_max_ZOP(unsigned int time_tmp)
{
  //��������, �� �� � ����� ����� ��������� ����������� ������, �� ��� �� �������� ������������
/*
      _I2 - ����� ��������� ����������� ��� ������������ ������������� ������������� �������� I2/I1
      _I1 - ����� ����� ����������� ��� ������������ ������������� ������������� �������� I2/I1
      
      I2 -  ������� ����� ��������� �����������
      I1 -  ������� ����� ����� �����������
      
      ����� ���������� ���������:
      _I2     I2
      ---  < --- /x �� _I1*I1  
      _I1     I1
      
      (_I2*I1 < I2*_I1)  - �� � �����, �� ����� � ����� ���(���) �� ��������� ���
*/
  unsigned int I2, I1, _I1, _I2;
   I2 = measurement[IM_I2];
   I1 = measurement[IM_I1];
  _I2 = measurements_ZOP_max_dr[5];
  _I1 = measurements_ZOP_max_dr[6];
  if (
      ( (_I1 >  0) && ( ((_I2*I1) < (I2*_I1)) || (I1 == 0) ) ) ||
      ( (_I1 == 0) && (I1 == 0) && ( _I2 < I2 ) ) 
     )
  {
    //����������� ��� ��� ��������� ����� ��������� ����������� � ������� ������� ������
    int frequency_val_1_int = (int)frequency_val_1;
    if (frequency_val_1_int >= 0) frequency_val_1_int = (int)(frequency_val_1*1000);
  
    int frequency_val_2_int = (int)frequency_val_2;
    if (frequency_val_2_int >= 0) frequency_val_2_int = (int)(frequency_val_2*1000);

    measurements_ZOP_max_dr[ 0] = measurement[IM_3I0];
    measurements_ZOP_max_dr[ 1] = measurement[IM_3I0_other_g];
    measurements_ZOP_max_dr[ 2] = measurement[IM_IA];
    measurements_ZOP_max_dr[ 3] = measurement[IM_IC];
    measurements_ZOP_max_dr[ 4] = measurement[IM_IB_r];
    measurements_ZOP_max_dr [5] = measurement[IM_I2];
    measurements_ZOP_max_dr[ 6] = measurement[IM_I1];
    measurements_ZOP_max_dr[ 7] = measurement[IM_UA];
    measurements_ZOP_max_dr[ 8] = measurement[IM_UB];
    measurements_ZOP_max_dr[ 9] = measurement[IM_UC];
    measurements_ZOP_max_dr[10] = measurement[IM_3U0_UBC_TN2];
    measurements_ZOP_max_dr[11] = measurement[IM_UAB_TN2];
    measurements_ZOP_max_dr[12] = measurement[IM_UAB];
    measurements_ZOP_max_dr[13] = measurement[IM_UBC];
    measurements_ZOP_max_dr[14] = measurement[IM_UCA];
    measurements_ZOP_max_dr[15] = (unsigned int)frequency_val_1_int;
    measurements_ZOP_max_dr[16] = (unsigned int)frequency_val_2_int;
    measurements_ZOP_max_dr[17] = (unsigned int)resistance[R_AB];
    measurements_ZOP_max_dr[18] = (unsigned int)resistance[X_AB];
    measurements_ZOP_max_dr[19] = (unsigned int)resistance[R_BC];
    measurements_ZOP_max_dr[20] = (unsigned int)resistance[X_BC];
    measurements_ZOP_max_dr[21] = (unsigned int)resistance[R_CA];
    measurements_ZOP_max_dr[22] = (unsigned int)resistance[X_CA];

    //Գ����� ��� � ������� ������� ��������� ������
    measurements_ZOP_max_dr[25] = time_tmp;
  }
}
/*****************************************************/

/*****************************************************/
//������� ���������� �������� ������� 1 
/*****************************************************/
inline void start_monitoring_min_f1(unsigned int time_tmp)
{
  //�������� ������� ���������� ������� �������� ������� 1
  number_min_f1_achr_dr++;
  
  //�������, �� ����� �������� � ����, �� ����� �������� ����� ��������� �����������, ���� �������� �� �� ��������
  int frequency_val_1_int = (int)frequency_val_1;
  if (frequency_val_1_int >= 0) frequency_val_1_int = (int)(frequency_val_1*1000);
  
  int frequency_val_2_int = (int)frequency_val_2;
  if (frequency_val_2_int >= 0) frequency_val_2_int = (int)(frequency_val_2*1000);

  measurements_f1_min_achr_dr[ 0] = measurement[IM_3I0];
  measurements_f1_min_achr_dr[ 1] = measurement[IM_3I0_other_g];
  measurements_f1_min_achr_dr[ 2] = measurement[IM_IA];
  measurements_f1_min_achr_dr[ 3] = measurement[IM_IC];
  measurements_f1_min_achr_dr[ 4] = measurement[IM_IB_r];
  measurements_f1_min_achr_dr [5] = measurement[IM_I2];
  measurements_f1_min_achr_dr[ 6] = measurement[IM_I1];
  measurements_f1_min_achr_dr[ 7] = measurement[IM_UA];
  measurements_f1_min_achr_dr[ 8] = measurement[IM_UB];
  measurements_f1_min_achr_dr[ 9] = measurement[IM_UC];
  measurements_f1_min_achr_dr[10] = measurement[IM_3U0_UBC_TN2];
  measurements_f1_min_achr_dr[11] = measurement[IM_UAB_TN2];
  measurements_f1_min_achr_dr[12] = measurement[IM_UAB];
  measurements_f1_min_achr_dr[13] = measurement[IM_UBC];
  measurements_f1_min_achr_dr[14] = measurement[IM_UCA];
  measurements_f1_min_achr_dr[15] = (unsigned int)frequency_val_1_int;
  measurements_f1_min_achr_dr[16] = (unsigned int)frequency_val_2_int;
  measurements_f1_min_achr_dr[17] = (unsigned int)resistance[R_AB];
  measurements_f1_min_achr_dr[18] = (unsigned int)resistance[X_AB];
  measurements_f1_min_achr_dr[19] = (unsigned int)resistance[R_BC];
  measurements_f1_min_achr_dr[20] = (unsigned int)resistance[X_BC];
  measurements_f1_min_achr_dr[21] = (unsigned int)resistance[R_CA];
  measurements_f1_min_achr_dr[22] = (unsigned int)resistance[X_CA];
  measurements_f1_min_achr_dr[23] = (unsigned int)UNDEF_VMP;
  measurements_f1_min_achr_dr[24] = 0;
  
  //Գ����� ��� � ������� ������� ��������� ������
  measurements_f1_min_achr_dr[25] = time_tmp;

  //�������, �� �� �� ���䳿 ���������� �������� �������
  state_current_monitoring |= (1<<IDENTIFIER_BIT_ARRAY_MIN_FREQUENCY_1_ACHR);
}
/*****************************************************/

/*****************************************************/
//����������� ���������� �������� ������� 1
/*****************************************************/
inline void continue_monitoring_min_f1(unsigned int time_tmp)
{
  if (((int)measurements_f1_min_achr_dr[15]) != (-2)) /*�� �����������, �� ������� ���� ����� ������ ����������� ���������� MIN_FREQUENCY - ������ ��� ��������� �������� ������� ���� �����*/
  {
    //��������, �� �� � ����� ����������� ������� �����, �� �� �� ������� ���������
    int frequency_val_1_int = (int)frequency_val_1;
    if (frequency_val_1_int >= 0) frequency_val_1_int = (int)(frequency_val_1*1000);
  
    int frequency_val_2_int = (int)frequency_val_2;
    if (frequency_val_2_int >= 0) frequency_val_2_int = (int)(frequency_val_2*1000);

    if(
       (frequency_val_1_int != (-1)) && /*������� �� ���������*/
       (frequency_val_1_int != (-3)) &&  /*������� ���� ������ ����������� ���������� MAX_FREQUENCY*/
       (
        (((int)measurements_f1_min_achr_dr[15]) > frequency_val_1_int) ||
        (frequency_val_1_int == (-2)) /*������� ����� ������ ����������� ���������� MIN_FREQUENCY - �� �������� ������, �� � ��������� ������ ���� ����� ��� �������� ������� ���� �� ����� -1 ��� -3*/
       )   
      )   
    {
      //����������� ��� ��� ��������� ����������� ������ � ������� ������� ������������� �� ���
      measurements_f1_min_achr_dr[ 0] = measurement[IM_3I0];
      measurements_f1_min_achr_dr[ 1] = measurement[IM_3I0_other_g];
      measurements_f1_min_achr_dr[ 2] = measurement[IM_IA];
      measurements_f1_min_achr_dr[ 3] = measurement[IM_IC];
      measurements_f1_min_achr_dr[ 4] = measurement[IM_IB_r];
      measurements_f1_min_achr_dr [5] = measurement[IM_I2];
      measurements_f1_min_achr_dr[ 6] = measurement[IM_I1];
      measurements_f1_min_achr_dr[ 7] = measurement[IM_UA];
      measurements_f1_min_achr_dr[ 8] = measurement[IM_UB];
      measurements_f1_min_achr_dr[ 9] = measurement[IM_UC];
      measurements_f1_min_achr_dr[10] = measurement[IM_3U0_UBC_TN2];
      measurements_f1_min_achr_dr[11] = measurement[IM_UAB_TN2];
      measurements_f1_min_achr_dr[12] = measurement[IM_UAB];
      measurements_f1_min_achr_dr[13] = measurement[IM_UBC];
      measurements_f1_min_achr_dr[14] = measurement[IM_UCA];
      measurements_f1_min_achr_dr[15] = (unsigned int)frequency_val_1_int;
      measurements_f1_min_achr_dr[16] = (unsigned int)frequency_val_2_int;
      measurements_f1_min_achr_dr[17] = (unsigned int)resistance[R_AB];
      measurements_f1_min_achr_dr[18] = (unsigned int)resistance[X_AB];
      measurements_f1_min_achr_dr[19] = (unsigned int)resistance[R_BC];
      measurements_f1_min_achr_dr[20] = (unsigned int)resistance[X_BC];
      measurements_f1_min_achr_dr[21] = (unsigned int)resistance[R_CA];
      measurements_f1_min_achr_dr[22] = (unsigned int)resistance[X_CA];

      //Գ����� ��� � ������� ������� ��������� ������
      measurements_f1_min_achr_dr[25] = time_tmp;
    }
  }
}
/*****************************************************/

/*****************************************************/
//������� ���������� �������� ������� 2 
/*****************************************************/
inline void start_monitoring_min_f2(unsigned int time_tmp)
{
  //�������� ������� ���������� ������� �������� ������� 2
  number_min_f2_achr_dr++;
  
  //�������, �� ����� �������� � ����, �� ����� �������� ����� ��������� �����������, ���� �������� �� �� ��������
  int frequency_val_1_int = (int)frequency_val_1;
  if (frequency_val_1_int >= 0) frequency_val_1_int = (int)(frequency_val_1*1000);
  
  int frequency_val_2_int = (int)frequency_val_2;
  if (frequency_val_2_int >= 0) frequency_val_2_int = (int)(frequency_val_2*1000);

  measurements_f2_min_achr_dr[ 0] = measurement[IM_3I0];
  measurements_f2_min_achr_dr[ 1] = measurement[IM_3I0_other_g];
  measurements_f2_min_achr_dr[ 2] = measurement[IM_IA];
  measurements_f2_min_achr_dr[ 3] = measurement[IM_IC];
  measurements_f2_min_achr_dr[ 4] = measurement[IM_IB_r];
  measurements_f2_min_achr_dr [5] = measurement[IM_I2];
  measurements_f2_min_achr_dr[ 6] = measurement[IM_I1];
  measurements_f2_min_achr_dr[ 7] = measurement[IM_UA];
  measurements_f2_min_achr_dr[ 8] = measurement[IM_UB];
  measurements_f2_min_achr_dr[ 9] = measurement[IM_UC];
  measurements_f2_min_achr_dr[10] = measurement[IM_3U0_UBC_TN2];
  measurements_f2_min_achr_dr[11] = measurement[IM_UAB_TN2];
  measurements_f2_min_achr_dr[12] = measurement[IM_UAB];
  measurements_f2_min_achr_dr[13] = measurement[IM_UBC];
  measurements_f2_min_achr_dr[14] = measurement[IM_UCA];
  measurements_f2_min_achr_dr[15] = (unsigned int)frequency_val_1_int;
  measurements_f2_min_achr_dr[16] = (unsigned int)frequency_val_2_int;
  measurements_f2_min_achr_dr[17] = (unsigned int)resistance[R_AB];
  measurements_f2_min_achr_dr[18] = (unsigned int)resistance[X_AB];
  measurements_f2_min_achr_dr[19] = (unsigned int)resistance[R_BC];
  measurements_f2_min_achr_dr[20] = (unsigned int)resistance[X_BC];
  measurements_f2_min_achr_dr[21] = (unsigned int)resistance[R_CA];
  measurements_f2_min_achr_dr[22] = (unsigned int)resistance[X_CA];
  measurements_f2_min_achr_dr[23] = (unsigned int)UNDEF_VMP;
  measurements_f2_min_achr_dr[24] = 0;
  
  //Գ����� ��� � ������� ������� ��������� ������
  measurements_f2_min_achr_dr[25] = time_tmp;

  //�������, �� �� �� ���䳿 ���������� �������� �������
  state_current_monitoring |= (1<<IDENTIFIER_BIT_ARRAY_MIN_FREQUENCY_2_ACHR);
}
/*****************************************************/

/*****************************************************/
//����������� ���������� �������� ������� 2
/*****************************************************/
inline void continue_monitoring_min_f2(unsigned int time_tmp)
{
  if (((int)measurements_f2_min_achr_dr[16]) != (-2)) /*�� �����������, �� ������� ���� ����� ������ ����������� ���������� MIN_FREQUENCY - ������ ��� ��������� �������� ������� ���� �����*/
  {
    //��������, �� �� � ����� ����������� ������� �����, �� �� �� ������� ���������
    int frequency_val_1_int = (int)frequency_val_1;
    if (frequency_val_1_int >= 0) frequency_val_1_int = (int)(frequency_val_1*1000);
  
    int frequency_val_2_int = (int)frequency_val_2;
    if (frequency_val_2_int >= 0) frequency_val_2_int = (int)(frequency_val_2*1000);

    if(
       (frequency_val_2_int != (-1)) && /*������� �� ���������*/
       (frequency_val_2_int != (-3)) &&  /*������� ���� ������ ����������� ���������� MAX_FREQUENCY*/
       (
        (((int)measurements_f2_min_achr_dr[16]) > frequency_val_2_int) ||
        (frequency_val_2_int == (-2)) /*������� ����� ������ ����������� ���������� MIN_FREQUENCY - �� �������� ������, �� � ��������� ������ ���� ����� ��� �������� ������� ���� �� ����� -1 ��� -3*/
       )   
      )   
    {
      //����������� ��� ��� ��������� ����������� ������ � ������� ������� ������������� �� ���
      measurements_f2_min_achr_dr[ 0] = measurement[IM_3I0];
      measurements_f2_min_achr_dr[ 1] = measurement[IM_3I0_other_g];
      measurements_f2_min_achr_dr[ 2] = measurement[IM_IA];
      measurements_f2_min_achr_dr[ 3] = measurement[IM_IC];
      measurements_f2_min_achr_dr[ 4] = measurement[IM_IB_r];
      measurements_f2_min_achr_dr [5] = measurement[IM_I2];
      measurements_f2_min_achr_dr[ 6] = measurement[IM_I1];
      measurements_f2_min_achr_dr[ 7] = measurement[IM_UA];
      measurements_f2_min_achr_dr[ 8] = measurement[IM_UB];
      measurements_f2_min_achr_dr[ 9] = measurement[IM_UC];
      measurements_f2_min_achr_dr[10] = measurement[IM_3U0_UBC_TN2];
      measurements_f2_min_achr_dr[11] = measurement[IM_UAB_TN2];
      measurements_f2_min_achr_dr[12] = measurement[IM_UAB];
      measurements_f2_min_achr_dr[13] = measurement[IM_UBC];
      measurements_f2_min_achr_dr[14] = measurement[IM_UCA];
      measurements_f2_min_achr_dr[15] = (unsigned int)frequency_val_1_int;
      measurements_f2_min_achr_dr[16] = (unsigned int)frequency_val_2_int;
      measurements_f2_min_achr_dr[17] = (unsigned int)resistance[R_AB];
      measurements_f2_min_achr_dr[18] = (unsigned int)resistance[X_AB];
      measurements_f2_min_achr_dr[19] = (unsigned int)resistance[R_BC];
      measurements_f2_min_achr_dr[20] = (unsigned int)resistance[X_BC];
      measurements_f2_min_achr_dr[21] = (unsigned int)resistance[R_CA];
      measurements_f2_min_achr_dr[22] = (unsigned int)resistance[X_CA];

      //Գ����� ��� � ������� ������� ��������� ������
      measurements_f2_min_achr_dr[25] = time_tmp;
    }
  }
}
/*****************************************************/

/*****************************************************/
//���������� ���������� ������������� ������
/*
  type_current == IDENTIFIER_BIT_ARRAY_MAX_CURRENT_PHASE        - ���������� ���������� ������������� ������� ������
  type_current == IDENTIFIER_BIT_ARRAY_MAX_CURRENT_3I0          - ���������� ���������� ������������� ������ 3I0
  type_current == IDENTIFIER_BIT_ARRAY_MAX_VOLTAGE_3U0          - ���������� ���������� ������������� ������ 3U0
  type_current == IDENTIFIER_BIT_ARRAY_MIN_VOLTAGE              - ���������� ���������� �������� �������
  type_current == IDENTIFIER_BIT_ARRAY_MAX_VOLTAGE              - ���������� ���������� ����������� �������
  type_current == IDENTIFIER_BIT_ARRAY_MAX_CURRENT_ZOP          - ���������� ���������� ������������� ������ ��������� �����������
  type_current == IDENTIFIER_BIT_ARRAY_MIN_FREQUENCY_1_ACHR     - ���������� ���������� �������� ������� 1 ��� ���
  type_current == IDENTIFIER_BIT_ARRAY_MIN_FREQUENCY_2_ACHR     - ���������� ���������� �������� ������� 2 ��� ���
  type_current == IDENTIFIER_BIT_ARRAY_FREQUENCY_1_CHAPV        - �������� ������� 1 ��� ����
  type_current == IDENTIFIER_BIT_ARRAY_FREQUENCY_2_CHAPV        - �������� ������� 2 ��� ����
*/
/*****************************************************/
inline void end_monitoring_min_max_measurement(unsigned int type_current, unsigned int* carrent_active_functions)
{
  if(
     (type_current == IDENTIFIER_BIT_ARRAY_MAX_CURRENT_PHASE   ) ||
     (type_current == IDENTIFIER_BIT_ARRAY_MAX_CURRENT_3I0     ) ||
     (type_current == IDENTIFIER_BIT_ARRAY_MAX_VOLTAGE_3U0     ) ||
     (type_current == IDENTIFIER_BIT_ARRAY_MIN_VOLTAGE         ) ||
     (type_current == IDENTIFIER_BIT_ARRAY_MAX_VOLTAGE         ) ||
     (type_current == IDENTIFIER_BIT_ARRAY_MAX_CURRENT_ZOP     ) ||
     (type_current == IDENTIFIER_BIT_ARRAY_MIN_FREQUENCY_1_ACHR) ||
     (type_current == IDENTIFIER_BIT_ARRAY_MIN_FREQUENCY_2_ACHR) ||
     (type_current == IDENTIFIER_BIT_ARRAY_FREQUENCY_1_CHAPV   ) ||
     (type_current == IDENTIFIER_BIT_ARRAY_FREQUENCY_2_CHAPV   )
    )
  {
    int step = number_max_phase_dr   + 
               number_max_3I0_dr     + 
               number_max_3U0_dr     + 
               number_min_U_dr       +
               number_max_U_dr       +
               number_max_ZOP_dr     +
               number_min_f1_achr_dr +
               number_min_f2_achr_dr +
               number_f1_chapv_dr    +
               number_f2_chapv_dr;
    
    //�������� �� ���������� ������ ����������� ������������
    if(
       ( (number_max_phase_dr   > 0) || ( (number_max_phase_dr   == 0) && ((state_current_monitoring & (1<< IDENTIFIER_BIT_ARRAY_MAX_CURRENT_PHASE   )) == 0) ) ) &&
       ( (number_max_3I0_dr     > 0) || ( (number_max_3I0_dr     == 0) && ((state_current_monitoring & (1<< IDENTIFIER_BIT_ARRAY_MAX_CURRENT_3I0     )) == 0) ) ) &&
       ( (number_max_3U0_dr     > 0) || ( (number_max_3U0_dr     == 0) && ((state_current_monitoring & (1<< IDENTIFIER_BIT_ARRAY_MAX_VOLTAGE_3U0     )) == 0) ) ) &&
       ( (number_min_U_dr       > 0) || ( (number_min_U_dr       == 0) && ((state_current_monitoring & (1<< IDENTIFIER_BIT_ARRAY_MIN_VOLTAGE         )) == 0) ) ) &&
       ( (number_max_U_dr       > 0) || ( (number_max_U_dr       == 0) && ((state_current_monitoring & (1<< IDENTIFIER_BIT_ARRAY_MAX_VOLTAGE         )) == 0) ) ) &&
       ( (number_max_ZOP_dr     > 0) || ( (number_max_ZOP_dr     == 0) && ((state_current_monitoring & (1<< IDENTIFIER_BIT_ARRAY_MAX_CURRENT_ZOP     )) == 0) ) ) &&
       ( (number_min_f1_achr_dr > 0) || ( (number_min_f1_achr_dr == 0) && ((state_current_monitoring & (1<< IDENTIFIER_BIT_ARRAY_MIN_FREQUENCY_1_ACHR)) == 0) ) ) &&
       ( (number_min_f2_achr_dr > 0) || ( (number_min_f2_achr_dr == 0) && ((state_current_monitoring & (1<< IDENTIFIER_BIT_ARRAY_MIN_FREQUENCY_2_ACHR)) == 0) ) ) &&
       ( (number_f1_chapv_dr    > 0) || ( (number_f1_chapv_dr    == 0) && ((state_current_monitoring & (1<< IDENTIFIER_BIT_ARRAY_FREQUENCY_1_CHAPV   )) == 0) ) ) &&
       ( (number_f2_chapv_dr    > 0) || ( (number_f2_chapv_dr    == 0) && ((state_current_monitoring & (1<< IDENTIFIER_BIT_ARRAY_FREQUENCY_2_CHAPV   )) == 0) ) ) &&
       ( (step > 0) && (step <= MAX_NUMBER_FIX_MAX_MEASUREMENTS)) 
      )
    {
      unsigned char *input_data_point, *output_data_point;
      
      //��������� ������� �����  ������ �������� ���
      if(type_current == IDENTIFIER_BIT_ARRAY_MAX_CURRENT_PHASE)
      {
        measurements_phase_max_dr[23] = (unsigned int)VMP_last_KZ;
        measurements_phase_max_dr[24] = equal_more_KZ;
        input_data_point = (unsigned char *)(measurements_phase_max_dr);
      }
      else if(type_current == IDENTIFIER_BIT_ARRAY_MAX_CURRENT_3I0)
      {
        measurements_3I0_max_dr[23] = (unsigned int)UNDEF_VMP;
        measurements_3I0_max_dr[24] = 0;
        input_data_point = (unsigned char *)(measurements_3I0_max_dr);
      }
      else if(type_current == IDENTIFIER_BIT_ARRAY_MAX_VOLTAGE_3U0)
      {
        measurements_3U0_max_dr[23] = (unsigned int)UNDEF_VMP;
        measurements_3U0_max_dr[24] = 0;
        input_data_point = (unsigned char *)(measurements_3U0_max_dr);
      }
      else if(type_current == IDENTIFIER_BIT_ARRAY_MIN_VOLTAGE)
      {
        measurements_U_min_dr[23] = (unsigned int)UNDEF_VMP;
        measurements_U_min_dr[24] = 0;
        input_data_point = (unsigned char *)(measurements_U_min_dr);
      }
      else if(type_current == IDENTIFIER_BIT_ARRAY_MAX_VOLTAGE)
      {
        measurements_U_max_dr[23] = (unsigned int)UNDEF_VMP;
        measurements_U_max_dr[24] = 0;
        input_data_point = (unsigned char *)(measurements_U_max_dr);
      }
      else if(type_current == IDENTIFIER_BIT_ARRAY_MAX_CURRENT_ZOP)
      {
        measurements_ZOP_max_dr[23] = (unsigned int)UNDEF_VMP;
        measurements_ZOP_max_dr[24] = 0;
        input_data_point = (unsigned char *)(measurements_ZOP_max_dr);
      }
      else if(type_current == IDENTIFIER_BIT_ARRAY_MIN_FREQUENCY_1_ACHR)
      {
        measurements_f1_min_achr_dr[23] = (unsigned int)UNDEF_VMP;
        measurements_f1_min_achr_dr[24] = 0;
        input_data_point = (unsigned char *)(measurements_f1_min_achr_dr);
      }
      else if(type_current == IDENTIFIER_BIT_ARRAY_MIN_FREQUENCY_2_ACHR)
      {
        measurements_f2_min_achr_dr[23] = (unsigned int)UNDEF_VMP;
        measurements_f2_min_achr_dr[24] = 0;
        input_data_point = (unsigned char *)(measurements_f2_min_achr_dr);
      }
      else if(type_current == IDENTIFIER_BIT_ARRAY_FREQUENCY_1_CHAPV)
      {
        measurements_f1_chapv_dr[23] = (unsigned int)UNDEF_VMP;
        measurements_f1_chapv_dr[24] = 0;
        input_data_point = (unsigned char *)(measurements_f1_chapv_dr);
      }
      else if(type_current == IDENTIFIER_BIT_ARRAY_FREQUENCY_2_CHAPV)
      {
        measurements_f2_chapv_dr[23] = (unsigned int)UNDEF_VMP;
        measurements_f2_chapv_dr[24] = 0;
        input_data_point = (unsigned char *)(measurements_f2_chapv_dr);
      }
      
      //��������� ������ ���� ��� ����� ��������
      step -= 1; //���� ��  ��������� ���������� � 0, � �� � 1 (step ����������� �� ����� 1(�� ��������� ����), ���� ��'������ ����� �� ���� ����)
      if(((state_current_monitoring & (1<< IDENTIFIER_BIT_ARRAY_MAX_CURRENT_PHASE)) != 0) && (type_current != IDENTIFIER_BIT_ARRAY_MAX_CURRENT_PHASE))
        step -= 1;
      if(((state_current_monitoring & (1<< IDENTIFIER_BIT_ARRAY_MAX_CURRENT_3I0     )) != 0) && (type_current != IDENTIFIER_BIT_ARRAY_MAX_CURRENT_3I0     ))
        step -= 1;
      if(((state_current_monitoring & (1<< IDENTIFIER_BIT_ARRAY_MAX_VOLTAGE_3U0     )) != 0) && (type_current != IDENTIFIER_BIT_ARRAY_MAX_VOLTAGE_3U0     ))
        step -= 1;
      if(((state_current_monitoring & (1<< IDENTIFIER_BIT_ARRAY_MIN_VOLTAGE         )) != 0) && (type_current != IDENTIFIER_BIT_ARRAY_MIN_VOLTAGE         ))
        step -= 1;
      if(((state_current_monitoring & (1<< IDENTIFIER_BIT_ARRAY_MAX_VOLTAGE         )) != 0) && (type_current != IDENTIFIER_BIT_ARRAY_MAX_VOLTAGE         ))
        step -= 1;
      if(((state_current_monitoring & (1<< IDENTIFIER_BIT_ARRAY_MAX_CURRENT_ZOP     )) != 0) && (type_current != IDENTIFIER_BIT_ARRAY_MAX_CURRENT_ZOP     ))
        step -= 1;
      if(((state_current_monitoring & (1<< IDENTIFIER_BIT_ARRAY_MIN_FREQUENCY_1_ACHR)) != 0) && (type_current != IDENTIFIER_BIT_ARRAY_MIN_FREQUENCY_1_ACHR))
        step -= 1;
      if(((state_current_monitoring & (1<< IDENTIFIER_BIT_ARRAY_MIN_FREQUENCY_2_ACHR)) != 0) && (type_current != IDENTIFIER_BIT_ARRAY_MIN_FREQUENCY_2_ACHR))
        step -= 1;
      if(((state_current_monitoring & (1<< IDENTIFIER_BIT_ARRAY_FREQUENCY_1_CHAPV   )) != 0) && (type_current != IDENTIFIER_BIT_ARRAY_FREQUENCY_1_CHAPV   ))
        step -= 1;
      if(((state_current_monitoring & (1<< IDENTIFIER_BIT_ARRAY_FREQUENCY_2_CHAPV   )) != 0) && (type_current != IDENTIFIER_BIT_ARRAY_FREQUENCY_2_CHAPV   ))
        step -= 1;
      
      if(step >= 0)
      {
        output_data_point = (buffer_for_save_dr_record + FIRST_INDEX_FIRST_BLOCK_DR +step*sizeof(unsigned int)*SIZE_ARRAY_FIX_MAX_MEASUREMENTS);
        
        for(unsigned int i = 0; i < (sizeof(unsigned int)*SIZE_ARRAY_FIX_MAX_MEASUREMENTS); i++)
        {
          if(i != (sizeof(unsigned int)*SIZE_ARRAY_FIX_MAX_MEASUREMENTS - 1))
          {
            *(output_data_point + i) = *(input_data_point + i);
          }
          else
          {
            //� ������� ���� ������, �� ������� ����� � Little-endian ������� �������� ����� ���������� �������� ������, ���� ���� ������, �� ����� ���������� ������������ �����
            *(output_data_point + i) = type_current;
          }
        }

        //������ ������, �� �� �� ���䳿 ���������� 
        state_current_monitoring &= ~(1<<type_current);
      }
      else
      {
        //³������� ���������� �������� - ���� �������� ���������� ����� �� ���� � ��������
        fix_undefined_error_dr(carrent_active_functions);
      }
    }
    else
    {
      //³������� ���������� �������� - ���� �������� ���������� ����� �� ���� � ��������
      fix_undefined_error_dr(carrent_active_functions);
    }
  }
  else
  {
    //³������� ���������� �������� - ���� �������� ���������� ����� �� ���� � ��������
    fix_undefined_error_dr(carrent_active_functions);
  }
}
/*****************************************************/

/*****************************************************/
//������ ������� ������ ����� � DataFalsh
/*****************************************************/
inline void command_start_saving_record_dr_into_dataflash(void)
{
  //� �������� �� ���������� ����� ���������� ����������� �����������, �� ������� ����� � �� �� ���������
  _SET_BIT(control_eeprom_taskes, TASK_START_WRITE_INFO_REJESTRATOR_DR_EEPROM_BIT);
  info_rejestrator_dr.saving_execution = 1;
        
  //����������� ����� ������� ������
  part_writing_dr_into_dataflash = 0;
  //����������� ������� ������ � ��������� DataFlash
  control_tasks_dataflash |= TASK_MAMORY_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_DR;
}
/*****************************************************/

/*****************************************************/
//������� ������� ����� ����������� ������ ����������� ����������
/*****************************************************/
inline void routine_for_queue_dr(void)
{
  if(
     (state_dr_record == STATE_DR_MAKE_RECORD)            || /*����� ����� ��������� ��� �������� �� ����� � DataFlsh ��� ���������� �������  ������ ������, �� ����� ���������� �����    ���������, � �� ������ ����� ����������� ���������� ������ ������������ ������*/
     (state_dr_record == STATE_DR_CUT_RECORD)             || /*����� ����� ��������� ��� �������� �� ����� � DataFlsh   � ���������  �������� ������ ������, �� ����� ���������� ����� �� ���������, �    ������ ����� ����������� ���������� ������ ������������ ������*/
     (number_records_dr_waiting_for_saving_operation != 0)  
    )
  {
    if ((control_tasks_dataflash & TASK_MAMORY_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_DR) == 0)
    {
      //�� ����� ������ ������ � Datafalsh �� �����������
      unsigned char *buffer_source, *buffer_target;
        
      if (number_records_dr_waiting_for_saving_operation == 0)
      {
        buffer_target = buffer_for_save_dr_record_level_2;
        buffer_source = buffer_for_save_dr_record;
        for(unsigned int i = 0; i < SIZE_BUFFER_FOR_DR_RECORD; i++) *(buffer_target +i ) = *(buffer_source + i);
        number_records_dr_waiting_for_saving_operation = 0;
      }
      else if (number_records_dr_waiting_for_saving_operation == 1)
      {
        buffer_target = buffer_for_save_dr_record_level_2;
        buffer_source = buffer_for_save_dr_record_level_1;
        for(unsigned int i = 0; i < SIZE_BUFFER_FOR_DR_RECORD; i++) *(buffer_target +i ) = *(buffer_source + i);
        
        if((state_dr_record == STATE_DR_MAKE_RECORD) || (state_dr_record == STATE_DR_CUT_RECORD))
        {
          buffer_target = buffer_for_save_dr_record_level_1;
          buffer_source = buffer_for_save_dr_record;
          for(unsigned int i = 0; i < SIZE_BUFFER_FOR_DR_RECORD; i++) *(buffer_target +i ) = *(buffer_source + i);
          number_records_dr_waiting_for_saving_operation = 1;
        }
        else number_records_dr_waiting_for_saving_operation = 0;
      }
      else
      {
        buffer_target = buffer_for_save_dr_record_level_2;
        buffer_source = buffer_for_save_dr_record_level_1;
        for(unsigned int i = 0; i < SIZE_BUFFER_FOR_DR_RECORD; i++) *(buffer_target +i ) = *(buffer_source + i);
        buffer_target = buffer_for_save_dr_record_level_1;
        buffer_source = buffer_for_save_dr_record;
        for(unsigned int i = 0; i < SIZE_BUFFER_FOR_DR_RECORD; i++) *(buffer_target +i ) = *(buffer_source + i);
        number_records_dr_waiting_for_saving_operation = 1;
      }
        
      //������ ������� ������ ����� � DataFalsh
      command_start_saving_record_dr_into_dataflash();
    }
    else
    {
      //�� ����� ������ ������ � Datafalsh �����������
      //����� ��� �������� ����� ��������� � �����
      if (number_records_dr_waiting_for_saving_operation == 0)
      {
        //�� ����� ������ ��� ����, ������ - � ����� ��� ������������ ����� � DataFalsh, ����� ����� ������ � ���� ����
        //��������� ������� ����� � ����� buffer_for_save_dr_record_level_1
        for(unsigned int i = 0; i < SIZE_BUFFER_FOR_DR_RECORD; i++) buffer_for_save_dr_record_level_1[i] = buffer_for_save_dr_record[i];
    
        //�������, �� ���� ����� ����� ������� ���� �� ������������ ����� � dataFalsh
        number_records_dr_waiting_for_saving_operation = 1;
      }
      else if (number_records_dr_waiting_for_saving_operation >= 1)
      {
         if((state_dr_record == STATE_DR_MAKE_RECORD) || (state_dr_record == STATE_DR_CUT_RECORD))
         {
          //�� ����� ������ ��� ����, ������ - � ����� ��� ������������ ����� � DataFalsh, �� ���� ����������� ����� ����� � ����� buffer_for_save_dr_record_level_1
          /*
          ���� ����� ����� �������� � ����� ������ ����� buffer_for_save_dr_record, ��� �������� ������� ������. �� ������ � ����
          � ���� ���� ������ ������ ����� �����, �� ������ ��������� ������� ������ �����
          */
          number_records_dr_waiting_for_saving_operation = 2;
         }
      }
    }
    
    if (state_dr_record == STATE_DR_MAKE_RECORD)
    {
      //�������, �� �� ����� �������� ��������� �����
      state_dr_record = STATE_DR_NO_RECORD;
    }
    else if (state_dr_record == STATE_DR_CUT_RECORD)
    {
      //�������, �� ����� ��������� ��������� ����� �����
      state_dr_record = STATE_DR_FORCE_START_NEW_RECORD;
    }
      
  }
}
/*****************************************************/

/*****************************************************/
//������� ������� ����� ����������� ����������
/*****************************************************/
inline void digital_registrator(unsigned int* carrent_active_functions, unsigned int volatile* previous_active_functions, unsigned int number_group_stp)
{
  static unsigned int number_items_dr;
  static unsigned int number_changes_into_dr_record;
  static unsigned int time_from_start_record_dr;
  static unsigned int blocking_continue_monitoring_min_U;
  
  //�� �������� �������� ����� � ���� �������, ���� ��� ������ ���������� ������ ������
  if(state_dr_record == STATE_DR_EXECUTING_RECORD)
  {
    //���������� �� �� ������� �����, �� ������� ���� ������ �������� ������������ ������
    unsigned int temp_value_for_max_min_fix_measurement = (
                                                            number_max_phase_dr   + 
                                                            number_max_3I0_dr     +
                                                            number_max_3U0_dr     +
                                                            number_min_U_dr       +
                                                            number_max_U_dr       +
                                                            number_max_ZOP_dr     +
                                                            number_min_f1_achr_dr +
                                                            number_min_f2_achr_dr +
                                                            number_f1_chapv_dr    +
                                                            number_f2_chapv_dr    
                                                      );
    if(temp_value_for_max_min_fix_measurement > MAX_NUMBER_FIX_MAX_MEASUREMENTS)
    {
      //����, ���������� �������� ���� �� ���� � ��������, ��� ���� ������, ������� ��������� ������ ����������� ����������
      fix_undefined_error_dr(carrent_active_functions);

      /*
      ������� ������ ������ ����������� ���������� � ����� ��������� �������� �������
      �� �� ������ ��� ����, ��� � ������� ����� ������ ������ ���� ����������� ��������� ������ ����������� ����������
      */
      _CLEAR_BIT(previous_active_functions, RANG_OUTPUT_LED_DF_REG_WORK_D_REJESTRATOR);
    }
    else
    {
      //���������� �� ����� ����� ������ ��������� ������������ ������ �����
      if(
         ((carrent_active_functions[0] & MASKA_MONITOTYNG_PHASE_SIGNALES_0) != 0) ||
         ((carrent_active_functions[1] & MASKA_MONITOTYNG_PHASE_SIGNALES_1) != 0) ||
         ((carrent_active_functions[2] & MASKA_MONITOTYNG_PHASE_SIGNALES_2) != 0) ||
         ((carrent_active_functions[3] & MASKA_MONITOTYNG_PHASE_SIGNALES_3) != 0) ||
         ((carrent_active_functions[4] & MASKA_MONITOTYNG_PHASE_SIGNALES_4) != 0) ||
         ((carrent_active_functions[5] & MASKA_MONITOTYNG_PHASE_SIGNALES_5) != 0)
        )
      {
        if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MAX_CURRENT_PHASE)) == 0)
        {
          //� ����� ������ ����� ��������� ������������� ������� ������
          temp_value_for_max_min_fix_measurement++;
        }
      }

      //���������� �� ����� ����� ������ ��������� ������������ ����� 3I0
      if(
         ((carrent_active_functions[0] & MASKA_MONITOTYNG_3I0_SIGNALES_0) != 0) ||
         ((carrent_active_functions[1] & MASKA_MONITOTYNG_3I0_SIGNALES_1) != 0) ||
         ((carrent_active_functions[2] & MASKA_MONITOTYNG_3I0_SIGNALES_2) != 0) ||
         ((carrent_active_functions[3] & MASKA_MONITOTYNG_3I0_SIGNALES_3) != 0) ||
         ((carrent_active_functions[4] & MASKA_MONITOTYNG_3I0_SIGNALES_4) != 0) ||
         ((carrent_active_functions[5] & MASKA_MONITOTYNG_3I0_SIGNALES_5) != 0)
      )
      {
        if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MAX_CURRENT_3I0)) == 0)
        {
          //� ����� ������ ����� ��������� ������������� ������ 3I0
          temp_value_for_max_min_fix_measurement++;
        }
      }
      
      //���������� �� ����� ����� ������ ��������� ����������� ������� 3U0
      if(
         ((carrent_active_functions[0] & MASKA_MONITOTYNG_3U0_SIGNALES_0) != 0) ||
         ((carrent_active_functions[1] & MASKA_MONITOTYNG_3U0_SIGNALES_1) != 0) ||
         ((carrent_active_functions[2] & MASKA_MONITOTYNG_3U0_SIGNALES_2) != 0) ||
         ((carrent_active_functions[3] & MASKA_MONITOTYNG_3U0_SIGNALES_3) != 0) ||
         ((carrent_active_functions[4] & MASKA_MONITOTYNG_3U0_SIGNALES_4) != 0) ||
         ((carrent_active_functions[5] & MASKA_MONITOTYNG_3U0_SIGNALES_5) != 0)
      )
      {
        if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MAX_VOLTAGE_3U0)) == 0)
        {
          //� ����� ������ ����� ��������� ����������� ������� 3U0
          temp_value_for_max_min_fix_measurement++;
        }
      }
      
      //���������� �� ����� ����� ������ ��������� �������� �������
      if (
          (blocking_continue_monitoring_min_U == 0) ||
          (_CHECK_SET_BIT(carrent_active_functions, RANG_OUTPUT_LED_DF_REG_WORK_BV) != 0)  
         )
      {
        if(
           ((carrent_active_functions[0] & MASKA_MONITOTYNG_UMIN_SIGNALES_0) != 0) ||
           ((carrent_active_functions[1] & MASKA_MONITOTYNG_UMIN_SIGNALES_1) != 0) ||
           ((carrent_active_functions[2] & MASKA_MONITOTYNG_UMIN_SIGNALES_2) != 0) ||
           ((carrent_active_functions[3] & MASKA_MONITOTYNG_UMIN_SIGNALES_3) != 0) ||
           ((carrent_active_functions[4] & MASKA_MONITOTYNG_UMIN_SIGNALES_4) != 0) ||
           ((carrent_active_functions[5] & MASKA_MONITOTYNG_UMIN_SIGNALES_5) != 0)
          )
        {
          if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MIN_VOLTAGE)) == 0)
          {
            //� ����� ������ ����� ��������� �������� ����� �������
            temp_value_for_max_min_fix_measurement++;
          }
        }
      }
      
      //���������� �� ����� ����� ������ ��������� ����������� �������
      if(
         ((carrent_active_functions[0] & MASKA_MONITOTYNG_UMAX_SIGNALES_0) != 0) ||
         ((carrent_active_functions[1] & MASKA_MONITOTYNG_UMAX_SIGNALES_1) != 0) ||
         ((carrent_active_functions[2] & MASKA_MONITOTYNG_UMAX_SIGNALES_2) != 0) ||
         ((carrent_active_functions[3] & MASKA_MONITOTYNG_UMAX_SIGNALES_3) != 0) ||
         ((carrent_active_functions[4] & MASKA_MONITOTYNG_UMAX_SIGNALES_4) != 0) ||
         ((carrent_active_functions[5] & MASKA_MONITOTYNG_UMAX_SIGNALES_5) != 0)
      )
      {
        if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MAX_VOLTAGE)) == 0)
        {
          //� ����� ������ ����� ��������� ����������� ����� �������
          temp_value_for_max_min_fix_measurement++;
        }
      }
      
      //���������� �� ����� ����� ������ ��������� ������������ ����� ��������� �����������
      if(
         ((carrent_active_functions[0] & MASKA_MONITOTYNG_ZOP_SIGNALES_0) != 0) ||
         ((carrent_active_functions[1] & MASKA_MONITOTYNG_ZOP_SIGNALES_1) != 0) ||
         ((carrent_active_functions[2] & MASKA_MONITOTYNG_ZOP_SIGNALES_2) != 0) ||
         ((carrent_active_functions[3] & MASKA_MONITOTYNG_ZOP_SIGNALES_3) != 0) ||
         ((carrent_active_functions[4] & MASKA_MONITOTYNG_ZOP_SIGNALES_4) != 0) ||
         ((carrent_active_functions[5] & MASKA_MONITOTYNG_ZOP_SIGNALES_5) != 0)
        )
      {
        if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MAX_CURRENT_ZOP)) == 0)
        {
          //� ����� ������ ����� ��������� ������������� ������ ���������� �����������
          temp_value_for_max_min_fix_measurement++;
        }
      }
    
      //���������� �� ����� ����� ������ ��������� �������� ������� 1 ��� ���
      if(
         ((carrent_active_functions[0] & MASKA_MONITOTYNG_F1_MIN_ACHR_SIGNALES_0) != 0) ||
         ((carrent_active_functions[1] & MASKA_MONITOTYNG_F1_MIN_ACHR_SIGNALES_1) != 0) ||
         ((carrent_active_functions[2] & MASKA_MONITOTYNG_F1_MIN_ACHR_SIGNALES_2) != 0) ||
         ((carrent_active_functions[3] & MASKA_MONITOTYNG_F1_MIN_ACHR_SIGNALES_3) != 0) ||
         ((carrent_active_functions[4] & MASKA_MONITOTYNG_F1_MIN_ACHR_SIGNALES_4) != 0) ||
         ((carrent_active_functions[5] & MASKA_MONITOTYNG_F1_MIN_ACHR_SIGNALES_5) != 0)
      )
      {
        if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MIN_FREQUENCY_1_ACHR)) == 0)
        {
          //� ����� ������ ����� ��������� �������� �������
          temp_value_for_max_min_fix_measurement++;
        }
      }
      
      //���������� �� ����� ����� ������ ��������� �������� ������� 2 ��� ���
      if(
         ((carrent_active_functions[0] & MASKA_MONITOTYNG_F2_MIN_ACHR_SIGNALES_0) != 0) ||
         ((carrent_active_functions[1] & MASKA_MONITOTYNG_F2_MIN_ACHR_SIGNALES_1) != 0) ||
         ((carrent_active_functions[2] & MASKA_MONITOTYNG_F2_MIN_ACHR_SIGNALES_2) != 0) ||
         ((carrent_active_functions[3] & MASKA_MONITOTYNG_F2_MIN_ACHR_SIGNALES_3) != 0) ||
         ((carrent_active_functions[4] & MASKA_MONITOTYNG_F2_MIN_ACHR_SIGNALES_4) != 0) ||
         ((carrent_active_functions[5] & MASKA_MONITOTYNG_F2_MIN_ACHR_SIGNALES_5) != 0)
      )
      {
        if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MIN_FREQUENCY_2_ACHR)) == 0)
        {
          //� ����� ������ ����� ��������� �������� �������
          temp_value_for_max_min_fix_measurement++;
        }
      }

      //� ����� ������� ������ ������� ����
      if (_CHECK_SET_BIT(carrent_active_functions , RANG_OUTPUT_LED_DF_REG_BLOCK_CHAPV_VID_U) == 0)
      {
        //���������� �� ����� ����� ����������� ������� 1 � ������� 2 ��� ���������� ����
        if(
           (_CHECK_SET_BIT(previous_active_functions, RANG_OUTPUT_LED_DF_REG_ACHR_CHAPV_VID_DV) != 0) &&
           (_CHECK_SET_BIT(carrent_active_functions , RANG_OUTPUT_LED_DF_REG_ACHR_CHAPV_VID_DV) == 0)
          )   
        {
          //� ����� ����������� ������� 1 � ������� 2 �� ���������� ����
          temp_value_for_max_min_fix_measurement += 2;
        }
        else if (_CHECK_SET_BIT(carrent_active_functions , RANG_OUTPUT_LED_DF_REG_RAZR_CHAPV) != 0)
        {
          //� ����� ������ ���� �� ��������� �����
          
          //���������� �� ����� ����� ����������� ������� 1 ��� ����
          if (  
              (_CHECK_SET_BIT(previous_active_functions, RANG_OUTPUT_LED_DF_REG_F1_ACHR_CHAPV  ) != 0) &&
              (_CHECK_SET_BIT(carrent_active_functions , RANG_OUTPUT_LED_DF_REG_F1_ACHR_CHAPV  ) == 0)
             )   
          {
            //� ����� ����������� ������� 1 �� ����
            temp_value_for_max_min_fix_measurement++;
          }

          //���������� �� ����� ����� ����������� ������� 2 ��� ����
          if (  
              (_CHECK_SET_BIT(previous_active_functions, RANG_OUTPUT_LED_DF_REG_F2_ACHR_CHAPV  ) != 0) &&
              (_CHECK_SET_BIT(carrent_active_functions , RANG_OUTPUT_LED_DF_REG_F2_ACHR_CHAPV  ) == 0)
             )   
          {
            //� ����� ����������� ������� 2 �� ����
            temp_value_for_max_min_fix_measurement++;
          }
        }
      }
          
      
      if(temp_value_for_max_min_fix_measurement > MAX_NUMBER_FIX_MAX_MEASUREMENTS)
      {
        //������� ��������, �� ������� ���� ������ �������� ������������ ���������
        //����� ��������� ��������� ������� ����� � ������ ��������� �����

        buffer_for_save_dr_record[FIRST_INDEX_NUMBER_ITEMS_DR      ] = number_items_dr;
        buffer_for_save_dr_record[FIRST_INDEX_NUMBER_CHANGES_DR    ] = number_changes_into_dr_record        & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_NUMBER_CHANGES_DR + 1] = (number_changes_into_dr_record >> 8) & 0xff;

        //���������� �� ����� ��������� ��������� ������������� ������� ������
        if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MAX_CURRENT_PHASE)) != 0)
          end_monitoring_min_max_measurement(IDENTIFIER_BIT_ARRAY_MAX_CURRENT_PHASE, carrent_active_functions);

        //���������� �� ����� ��������� ��������� ������������� ������ 3I0
        if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MAX_CURRENT_3I0)) != 0)
          end_monitoring_min_max_measurement(IDENTIFIER_BIT_ARRAY_MAX_CURRENT_3I0, carrent_active_functions);

        //���������� �� ����� ��������� ��������� ����������� ������� 3U0
        if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MAX_VOLTAGE_3U0)) != 0)
          end_monitoring_min_max_measurement(IDENTIFIER_BIT_ARRAY_MAX_VOLTAGE_3U0, carrent_active_functions);

        //���������� �� ����� ��������� ��������� �������� �������
        if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MIN_VOLTAGE)) != 0)
          end_monitoring_min_max_measurement(IDENTIFIER_BIT_ARRAY_MIN_VOLTAGE, carrent_active_functions);

        //���������� �� ����� ��������� ��������� ����������� �������
        if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MAX_VOLTAGE)) != 0)
          end_monitoring_min_max_measurement(IDENTIFIER_BIT_ARRAY_MAX_VOLTAGE, carrent_active_functions);

        //���������� �� ����� ��������� ��������� ������������� ������ �����������
        if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MAX_CURRENT_ZOP)) != 0)
          end_monitoring_min_max_measurement(IDENTIFIER_BIT_ARRAY_MAX_CURRENT_ZOP, carrent_active_functions);
        
        //���������� �� ����� ��������� ��������� �������� ������� 1 ��� ���
        if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MIN_FREQUENCY_1_ACHR)) != 0)
          end_monitoring_min_max_measurement(IDENTIFIER_BIT_ARRAY_MIN_FREQUENCY_1_ACHR, carrent_active_functions);

        //���������� �� ����� ��������� ��������� �������� ������� 2 ��� ���
        if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MIN_FREQUENCY_2_ACHR)) != 0)
          end_monitoring_min_max_measurement(IDENTIFIER_BIT_ARRAY_MIN_FREQUENCY_2_ACHR, carrent_active_functions);

        //������ 䳿 �������� ����� � ���� �������, ���� ������� end_monitoring_min_max_measurement �� ����������� ������� � �� ������� state_dr_record � STATE_DR_NO_RECORD
        if(state_dr_record != STATE_DR_NO_RECORD)
        {
          //�������� ������� ������������ ������������ ������ ��� ����
          buffer_for_save_dr_record[FIRST_INDEX_NUMBER_MAX_PHASE_DR  ] = number_max_phase_dr;
          buffer_for_save_dr_record[FIRST_INDEX_NUMBER_MAX_3I0_DR    ] = number_max_3I0_dr;
          buffer_for_save_dr_record[FIRST_INDEX_NUMBER_MAX_3U0_DR    ] = number_max_3U0_dr;
          buffer_for_save_dr_record[FIRST_INDEX_NUMBER_MIN_U_DR      ] = number_min_U_dr;
          buffer_for_save_dr_record[FIRST_INDEX_NUMBER_MAX_U_DR      ] = number_max_U_dr;
          buffer_for_save_dr_record[FIRST_INDEX_NUMBER_MAX_ZOP_DR    ] = number_max_ZOP_dr;
          buffer_for_save_dr_record[FIRST_INDEX_NUMBER_MIN_F1_ACHR_DR] = number_min_f1_achr_dr;
          buffer_for_save_dr_record[FIRST_INDEX_NUMBER_MIN_F2_ACHR_DR] = number_min_f2_achr_dr;
          buffer_for_save_dr_record[FIRST_INDEX_NUMBER_F1_CHAPV_DR   ] = number_f1_chapv_dr;
          buffer_for_save_dr_record[FIRST_INDEX_NUMBER_F2_CHAPV_DR   ] = number_f2_chapv_dr;

          //�������, �� ����� ��� ������ �� ����� ������ ����� �����, �� ��������� ����� ��� ��������� ���������
          state_dr_record = STATE_DR_CUT_RECORD;
        
          //������� ������ ������ ����������� ����������
          _CLEAR_BIT(carrent_active_functions, RANG_OUTPUT_LED_DF_REG_WORK_D_REJESTRATOR);
        
          //����������� ����� ������ � ����� ��� ������
          routine_for_queue_dr();
        }
        /*
        ������� ������ ������ ����������� ���������� � ����� ��������� �������� �������
        �� �� ������ ��� ����, ��� � ������� ����� ������ ������ ���� ����������� ��������� ������ ����������� ����������
        */
        _CLEAR_BIT(previous_active_functions, RANG_OUTPUT_LED_DF_REG_WORK_D_REJESTRATOR);
        
      }
    }
  }
  
  switch (state_dr_record)
  {
  case STATE_DR_NO_RECORD:
  case STATE_DR_FORCE_START_NEW_RECORD:
    {
      //���������� ������� ����������� �������  ������ ����������� ����������
      _SET_BIT(clear_diagnostyka, ERROR_DR_UNDEFINED_BIT);
      if(number_records_dr_waiting_for_saving_operation < (WIGHT_OF_DR_WAITING - 1))
      {
        //�� �������� ������, �� �� ����� �� ���� ����� ����� � ��� � ����� ���, ���� ������� ����������� ��� ������ �����
        _SET_BIT(clear_diagnostyka, ERROR_DR_TEMPORARY_BUSY_BIT);
      }
      
      //�� ������� ������ ������ �� ���������� ��������� �� ���������
      
      //��������, �� ����� ����� ������� ����������� ����������
      if (
          (
           ((carrent_active_functions[0] & current_settings_prt.ranguvannja_digital_registrator[0]) != 0) ||
           ((carrent_active_functions[1] & current_settings_prt.ranguvannja_digital_registrator[1]) != 0) ||
           ((carrent_active_functions[2] & current_settings_prt.ranguvannja_digital_registrator[2]) != 0) ||
           ((carrent_active_functions[3] & current_settings_prt.ranguvannja_digital_registrator[3]) != 0) ||
           ((carrent_active_functions[4] & current_settings_prt.ranguvannja_digital_registrator[4]) != 0) ||
           ((carrent_active_functions[5] & current_settings_prt.ranguvannja_digital_registrator[5]) != 0) ||
           (state_dr_record == STATE_DR_FORCE_START_NEW_RECORD)
          )   
         )
      {
        //� ����� ������� ����������� ����������
        
        //����������, �� ��� ������� ������ ������ �� �� �������� ��������� ����������
        if(number_records_dr_waiting_for_saving_operation < WIGHT_OF_DR_WAITING)
        {
          //����� �������� ����� �����
          
          //���������� ����� ������ �� ���������� ����������� � ���� "��� ������ ������ ����������"
          state_dr_record = STATE_DR_EXECUTING_RECORD;
          //����������� ������� �������
          _SET_BIT(carrent_active_functions, RANG_OUTPUT_LED_DF_REG_WORK_D_REJESTRATOR);
        
          //�������� ���� ������� ������
          buffer_for_save_dr_record[FIRST_INDEX_START_START_RECORD_DR] = LABEL_START_RECORD_DR;
         
          //�������� ��� ������� ������
          unsigned char *label_to_time_array;
          if (copying_time == 2) label_to_time_array = time_copy;
          else label_to_time_array = time;
          for(unsigned int i = 0; i < 7; i++) buffer_for_save_dr_record[FIRST_INDEX_DATA_TIME_DR + i] = *(label_to_time_array + i);
          
          //�������� ������������ ��� ���� ���� �������� ���������� ���������
          unsigned int control_extra_settings_1_tmp = current_settings_prt.control_extra_settings_1 & (CTR_EXTRA_SETTINGS_1_CTRL_3U0_Ubc_TN2 | CTR_EXTRA_SETTINGS_1_CTRL_PHASE_LINE);
          unsigned char *point_to_extra_settings = (unsigned char *)(&control_extra_settings_1_tmp);
          for (unsigned int i = 0; i < sizeof(control_extra_settings_1_tmp); i++)
            buffer_for_save_dr_record[FIRST_INDEX_EXTRA_SETTINGS_DR + i] = *(point_to_extra_settings + i);

           //�'�� ������
          for(unsigned int i=0; i< MAX_CHAR_IN_NAME_OF_CELL; i++) 
            buffer_for_save_dr_record[FIRST_INDEX_NAME_OF_CELL_DR + i] = current_settings_prt.name_of_cell[i] & 0xff;
          
          //������� ������ ���� ������� � ������� ������� ������
          time_from_start_record_dr = 0;
          
          //������� ������� �������� ������������ ������/������
          number_max_phase_dr = 0;
          number_max_3I0_dr = 0;
          number_max_3U0_dr = 0;
          number_min_U_dr = 0;
          number_max_U_dr = 0;
          number_max_ZOP_dr = 0;
          number_min_f1_achr_dr = 0;
          number_min_f2_achr_dr = 0;
          number_f1_chapv_dr = 0;
          number_f2_chapv_dr = 0;
          
          //������ ����������� ��� ��������� ������������ ������
          state_current_monitoring = 0;
          
          //���������� �� ����� ����� ��������� ������������ ������ �����
          if(
             ((carrent_active_functions[0] & MASKA_MONITOTYNG_PHASE_SIGNALES_0) != 0) ||
             ((carrent_active_functions[1] & MASKA_MONITOTYNG_PHASE_SIGNALES_1) != 0) ||
             ((carrent_active_functions[2] & MASKA_MONITOTYNG_PHASE_SIGNALES_2) != 0) ||
             ((carrent_active_functions[3] & MASKA_MONITOTYNG_PHASE_SIGNALES_3) != 0) ||
             ((carrent_active_functions[4] & MASKA_MONITOTYNG_PHASE_SIGNALES_4) != 0) ||
             ((carrent_active_functions[5] & MASKA_MONITOTYNG_PHASE_SIGNALES_5) != 0)
            )
          {
            start_monitoring_max_phase_current(time_from_start_record_dr);
          }

          //���������� �� ����� ����� ��������� ������������ ����� 3I0
          if(
             ((carrent_active_functions[0] & MASKA_MONITOTYNG_3I0_SIGNALES_0) != 0) ||
             ((carrent_active_functions[1] & MASKA_MONITOTYNG_3I0_SIGNALES_1) != 0) ||
             ((carrent_active_functions[2] & MASKA_MONITOTYNG_3I0_SIGNALES_2) != 0) ||
             ((carrent_active_functions[3] & MASKA_MONITOTYNG_3I0_SIGNALES_3) != 0) ||
             ((carrent_active_functions[4] & MASKA_MONITOTYNG_3I0_SIGNALES_4) != 0) ||
             ((carrent_active_functions[5] & MASKA_MONITOTYNG_3I0_SIGNALES_5) != 0)
            )
          {
            start_monitoring_max_3I0(time_from_start_record_dr);
          }

          //���������� �� ����� ����� ��������� ����������� ������� 3U0
          if(
             ((carrent_active_functions[0] & MASKA_MONITOTYNG_3U0_SIGNALES_0) != 0) ||
             ((carrent_active_functions[1] & MASKA_MONITOTYNG_3U0_SIGNALES_1) != 0) ||
             ((carrent_active_functions[2] & MASKA_MONITOTYNG_3U0_SIGNALES_2) != 0) ||
             ((carrent_active_functions[3] & MASKA_MONITOTYNG_3U0_SIGNALES_3) != 0) ||
             ((carrent_active_functions[4] & MASKA_MONITOTYNG_3U0_SIGNALES_4) != 0) ||
             ((carrent_active_functions[5] & MASKA_MONITOTYNG_3U0_SIGNALES_5) != 0)
            )
          {
            start_monitoring_max_3U0(time_from_start_record_dr);
          }

          //������ ���������� ���������� �������� �������
          blocking_continue_monitoring_min_U = 0;
          //���������� �� ����� ����� ��������� �������� �������
          if(
             ((carrent_active_functions[0] & MASKA_MONITOTYNG_UMIN_SIGNALES_0) != 0) ||
             ((carrent_active_functions[1] & MASKA_MONITOTYNG_UMIN_SIGNALES_1) != 0) ||
             ((carrent_active_functions[2] & MASKA_MONITOTYNG_UMIN_SIGNALES_2) != 0) ||
             ((carrent_active_functions[3] & MASKA_MONITOTYNG_UMIN_SIGNALES_3) != 0) ||
             ((carrent_active_functions[4] & MASKA_MONITOTYNG_UMIN_SIGNALES_4) != 0) ||
             ((carrent_active_functions[5] & MASKA_MONITOTYNG_UMIN_SIGNALES_5) != 0)
            )
          {
            start_monitoring_min_U(time_from_start_record_dr);
          }
          //����������, �� ����� ����� ��������� ��������� �������� ������� ���� ��������� ��������
          if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MIN_VOLTAGE)) != 0)
          {
            if (_CHECK_SET_BIT(carrent_active_functions, RANG_OUTPUT_LED_DF_REG_WORK_BO) != 0)
            {
              blocking_continue_monitoring_min_U = 0xff;
              end_monitoring_min_max_measurement(IDENTIFIER_BIT_ARRAY_MIN_VOLTAGE, carrent_active_functions);
            }
          }

          //���������� �� ����� ����� ��������� ����������� �������
          if(
             ((carrent_active_functions[0] & MASKA_MONITOTYNG_UMAX_SIGNALES_0) != 0) ||
             ((carrent_active_functions[1] & MASKA_MONITOTYNG_UMAX_SIGNALES_1) != 0) ||
             ((carrent_active_functions[2] & MASKA_MONITOTYNG_UMAX_SIGNALES_2) != 0) ||
             ((carrent_active_functions[3] & MASKA_MONITOTYNG_UMAX_SIGNALES_3) != 0) ||
             ((carrent_active_functions[4] & MASKA_MONITOTYNG_UMAX_SIGNALES_4) != 0) ||
             ((carrent_active_functions[5] & MASKA_MONITOTYNG_UMAX_SIGNALES_5) != 0)
            )
          {
            start_monitoring_max_U(time_from_start_record_dr);
          }

          //���������� �� ����� ����� ��������� ������������ ����� ��������� �����������
          if(
             ((carrent_active_functions[0] & MASKA_MONITOTYNG_ZOP_SIGNALES_0) != 0) ||
             ((carrent_active_functions[1] & MASKA_MONITOTYNG_ZOP_SIGNALES_1) != 0) ||
             ((carrent_active_functions[2] & MASKA_MONITOTYNG_ZOP_SIGNALES_2) != 0) ||
             ((carrent_active_functions[3] & MASKA_MONITOTYNG_ZOP_SIGNALES_3) != 0) ||
             ((carrent_active_functions[4] & MASKA_MONITOTYNG_ZOP_SIGNALES_4) != 0) ||
             ((carrent_active_functions[5] & MASKA_MONITOTYNG_ZOP_SIGNALES_5) != 0)
            )
          {
            start_monitoring_max_ZOP(time_from_start_record_dr);
          }
      
          //���������� �� ����� ����� ��������� �������� ������� 1
          if(
             ((carrent_active_functions[0] & MASKA_MONITOTYNG_F1_MIN_ACHR_SIGNALES_0) != 0) ||
             ((carrent_active_functions[1] & MASKA_MONITOTYNG_F1_MIN_ACHR_SIGNALES_1) != 0) ||
             ((carrent_active_functions[2] & MASKA_MONITOTYNG_F1_MIN_ACHR_SIGNALES_2) != 0) ||
             ((carrent_active_functions[3] & MASKA_MONITOTYNG_F1_MIN_ACHR_SIGNALES_3) != 0) ||
             ((carrent_active_functions[4] & MASKA_MONITOTYNG_F1_MIN_ACHR_SIGNALES_4) != 0) ||
             ((carrent_active_functions[5] & MASKA_MONITOTYNG_F1_MIN_ACHR_SIGNALES_5) != 0)
            )
          {
            start_monitoring_min_f1(time_from_start_record_dr);
          }

          if(
             ((carrent_active_functions[0] & MASKA_MONITOTYNG_F2_MIN_ACHR_SIGNALES_0) != 0) ||
             ((carrent_active_functions[1] & MASKA_MONITOTYNG_F2_MIN_ACHR_SIGNALES_1) != 0) ||
             ((carrent_active_functions[2] & MASKA_MONITOTYNG_F2_MIN_ACHR_SIGNALES_2) != 0) ||
             ((carrent_active_functions[3] & MASKA_MONITOTYNG_F2_MIN_ACHR_SIGNALES_3) != 0) ||
             ((carrent_active_functions[4] & MASKA_MONITOTYNG_F2_MIN_ACHR_SIGNALES_4) != 0) ||
             ((carrent_active_functions[5] & MASKA_MONITOTYNG_F2_MIN_ACHR_SIGNALES_5) != 0)
            )
          {
            start_monitoring_min_f2(time_from_start_record_dr);
          }
          
          /*
          �������� ����������� ������ �������� ��������� ��� ����� ���� ����������
          �� �������, ���� �� �� ����� ��������� ���������� ���������, � ����� ������
          ��������� ��� ������� ���� ���������� � ���� ���� � ���� ������ ����
          ������� ������� "��������"->"��������"
          */

          //�������� ��������� c��� ������� ����� �����
          //̳��� ���� ������������ ����� ������� �� ������� ������� ������
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR +  0] = 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR +  1] = 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR +  2] = 0xff;
          //��������� ����
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR +  3] =  previous_active_functions[0]        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR +  4] = (previous_active_functions[0] >> 8 ) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR +  5] = (previous_active_functions[0] >> 16) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR +  6] = (previous_active_functions[0] >> 24) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR +  7] =  previous_active_functions[1]        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR +  8] = (previous_active_functions[1] >> 8)  & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR +  9] = (previous_active_functions[1] >> 16) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 10] = (previous_active_functions[1] >> 24) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 11] =  previous_active_functions[2]        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 12] = (previous_active_functions[2] >> 8)  & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 13] = (previous_active_functions[2] >> 16) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 14] = (previous_active_functions[2] >> 24) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 15] =  previous_active_functions[3]        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 16] = (previous_active_functions[3] >> 8)  & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 17] = (previous_active_functions[3] >> 16) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 18] = (previous_active_functions[3] >> 24) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 19] =  previous_active_functions[4]        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 20] = (previous_active_functions[4] >> 8)  & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 21] = (previous_active_functions[4] >> 16) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 22] = (previous_active_functions[4] >> 24) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 23] =  previous_active_functions[5]        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 24] = (previous_active_functions[5] >> 8)  & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 25] = (previous_active_functions[5] >> 16) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 26] = (previous_active_functions[5] >> 24) & 0xff;
          //����� ��������� � ��� ������� ������� ���
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 27] = 0;

          //������� ������� ����� ����
          number_items_dr = 1;
      
          //���������� ������� ��� �������
          number_changes_into_dr_record = 0;
          unsigned int number_changes_into_current_item;
          _NUMBER_CHANGES_INTO_UNSIGNED_INT_ARRAY(previous_active_functions, carrent_active_functions, N_BIG, number_changes_into_current_item);
          number_changes_into_dr_record += number_changes_into_current_item;
      
          //�������� ������� c��� �������
          //̳��� ����
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*28 +  0] =  time_from_start_record_dr        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*28 +  1] = (time_from_start_record_dr >> 8 ) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*28 +  2] = (time_from_start_record_dr >> 16) & 0xff;
          //������� ���� �������
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*28 +  3] =  carrent_active_functions[0]        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*28 +  4] = (carrent_active_functions[0] >> 8 ) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*28 +  5] = (carrent_active_functions[0] >> 16) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*28 +  6] = (carrent_active_functions[0] >> 24) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*28 +  7] =  carrent_active_functions[1]        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*28 +  8] = (carrent_active_functions[1] >> 8 ) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*28 +  9] = (carrent_active_functions[1] >> 16) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*28 + 10] = (carrent_active_functions[1] >> 24) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*28 + 11] =  carrent_active_functions[2]        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*28 + 12] = (carrent_active_functions[2] >> 8 ) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*28 + 13] = (carrent_active_functions[2] >> 16) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*28 + 14] = (carrent_active_functions[2] >> 24) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*28 + 15] =  carrent_active_functions[3]        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*28 + 16] = (carrent_active_functions[3] >> 8 ) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*28 + 17] = (carrent_active_functions[3] >> 16) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*28 + 18] = (carrent_active_functions[3] >> 24) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*28 + 19] =  carrent_active_functions[4]        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*28 + 20] = (carrent_active_functions[4] >> 8 ) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*28 + 21] = (carrent_active_functions[4] >> 16) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*28 + 22] = (carrent_active_functions[4] >> 24) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*28 + 23] =  carrent_active_functions[5]        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*28 + 24] = (carrent_active_functions[5] >> 8 ) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*28 + 25] = (carrent_active_functions[5] >> 16) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*28 + 26] = (carrent_active_functions[5] >> 24) & 0xff;
          
          //ʳ������ ��� ������� � �������� �� ��������� ������
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*28 + 27] = number_changes_into_current_item & 0xff;
      
          //����� ������ �������, ��� � ����� �� ���� ���������� �� ��������� ������
          for(unsigned int i = FIRST_INDEX_FIRST_BLOCK_DR; i < FIRST_INDEX_FIRST_DATA_DR; i++)
            buffer_for_save_dr_record[i] = 0xff;
          for(unsigned int i = (FIRST_INDEX_FIRST_DATA_DR + (number_items_dr + 1)*28); i < SIZE_BUFFER_FOR_DR_RECORD; i++)
            buffer_for_save_dr_record[i] = 0xff;
        }
        else
        {
          //����������� �������, �� � ����� �� ������ ����������� ���������� ���, �� �� ���� ������ ������
          _SET_BIT(set_diagnostyka, ERROR_DR_TEMPORARY_BUSY_BIT);
          _SET_BIT(carrent_active_functions, RANG_OUTPUT_LED_DF_REG_DEFECT);
        }
      }
      else state_dr_record = STATE_DR_NO_RECORD;
      
      break;
    }
  case STATE_DR_EXECUTING_RECORD:
    {
      //�������� ��� � ������� ������� ������
      time_from_start_record_dr++;
      //������� �� ����� ���� ��� ������ ������

      //��������-�������� ������������ ���������� �������
      
      //���������� �� ����� ����� ��������� ������������ ������ �����
      if(
         ((carrent_active_functions[0] & MASKA_MONITOTYNG_PHASE_SIGNALES_0) != 0) ||
         ((carrent_active_functions[1] & MASKA_MONITOTYNG_PHASE_SIGNALES_1) != 0) ||
         ((carrent_active_functions[2] & MASKA_MONITOTYNG_PHASE_SIGNALES_2) != 0) ||
         ((carrent_active_functions[3] & MASKA_MONITOTYNG_PHASE_SIGNALES_3) != 0) ||
         ((carrent_active_functions[4] & MASKA_MONITOTYNG_PHASE_SIGNALES_4) != 0) ||
         ((carrent_active_functions[5] & MASKA_MONITOTYNG_PHASE_SIGNALES_5) != 0)
        )
      {
        if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MAX_CURRENT_PHASE)) != 0)
          continue_monitoring_max_phase_current(time_from_start_record_dr);
        else
          start_monitoring_max_phase_current(time_from_start_record_dr);
      }
      else
      {
        if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MAX_CURRENT_PHASE)) != 0)
          end_monitoring_min_max_measurement(IDENTIFIER_BIT_ARRAY_MAX_CURRENT_PHASE, carrent_active_functions);
      }

      //���������� �� ����� ����� ��������� ������������ ����� 3I0
      if(
         ((carrent_active_functions[0] & MASKA_MONITOTYNG_3I0_SIGNALES_0) != 0) ||
         ((carrent_active_functions[1] & MASKA_MONITOTYNG_3I0_SIGNALES_1) != 0) ||
         ((carrent_active_functions[2] & MASKA_MONITOTYNG_3I0_SIGNALES_2) != 0) ||
         ((carrent_active_functions[3] & MASKA_MONITOTYNG_3I0_SIGNALES_3) != 0) ||
         ((carrent_active_functions[4] & MASKA_MONITOTYNG_3I0_SIGNALES_4) != 0) ||
         ((carrent_active_functions[5] & MASKA_MONITOTYNG_3I0_SIGNALES_5) != 0)
        )
      {
        if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MAX_CURRENT_3I0)) != 0)
          continue_monitoring_max_3I0(time_from_start_record_dr);
        else
          start_monitoring_max_3I0(time_from_start_record_dr);
      }
      else
      {
        if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MAX_CURRENT_3I0)) != 0)
          end_monitoring_min_max_measurement(IDENTIFIER_BIT_ARRAY_MAX_CURRENT_3I0, carrent_active_functions);
      }
      
      //���������� �� ����� ����� ��������� ����������� ������� 3U0
      if(
         ((carrent_active_functions[0] & MASKA_MONITOTYNG_3U0_SIGNALES_0) != 0) ||
         ((carrent_active_functions[1] & MASKA_MONITOTYNG_3U0_SIGNALES_1) != 0) ||
         ((carrent_active_functions[2] & MASKA_MONITOTYNG_3U0_SIGNALES_2) != 0) ||
         ((carrent_active_functions[3] & MASKA_MONITOTYNG_3U0_SIGNALES_3) != 0) ||
         ((carrent_active_functions[4] & MASKA_MONITOTYNG_3U0_SIGNALES_4) != 0) ||
         ((carrent_active_functions[5] & MASKA_MONITOTYNG_3U0_SIGNALES_5) != 0)
        )
      {
        if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MAX_VOLTAGE_3U0)) != 0)
          continue_monitoring_max_3U0(time_from_start_record_dr);
        else
          start_monitoring_max_3U0(time_from_start_record_dr);
      }
      else
      {
        if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MAX_VOLTAGE_3U0)) != 0)
          end_monitoring_min_max_measurement(IDENTIFIER_BIT_ARRAY_MAX_VOLTAGE_3U0, carrent_active_functions);
      }
      
      //���������� �� ����� ����� �������� ��������� �������� �������
      if (_CHECK_SET_BIT(carrent_active_functions, RANG_OUTPUT_LED_DF_REG_WORK_BV) != 0)
      {
        //������ ���������� ���������� �������� �������
        blocking_continue_monitoring_min_U = 0;
      }
      //���������� �� ����� ����� ��������� �������� �������
      if (blocking_continue_monitoring_min_U == 0)
      {
        if(
           ((carrent_active_functions[0] & MASKA_MONITOTYNG_UMIN_SIGNALES_0) != 0) ||
           ((carrent_active_functions[1] & MASKA_MONITOTYNG_UMIN_SIGNALES_1) != 0) ||
           ((carrent_active_functions[2] & MASKA_MONITOTYNG_UMIN_SIGNALES_2) != 0) ||
           ((carrent_active_functions[3] & MASKA_MONITOTYNG_UMIN_SIGNALES_3) != 0) ||
           ((carrent_active_functions[4] & MASKA_MONITOTYNG_UMIN_SIGNALES_4) != 0) ||
           ((carrent_active_functions[5] & MASKA_MONITOTYNG_UMIN_SIGNALES_5) != 0)
          )
        {
          if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MIN_VOLTAGE)) != 0)
            continue_monitoring_min_U(time_from_start_record_dr);
          else
            start_monitoring_min_U(time_from_start_record_dr);
        }
        else
        {
          if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MIN_VOLTAGE)) != 0)
            end_monitoring_min_max_measurement(IDENTIFIER_BIT_ARRAY_MIN_VOLTAGE, carrent_active_functions);
        }
      }
      //����������, �� ����� ����� ��������� ��������� �������� ������� ���� ��������� ��������
      if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MIN_VOLTAGE)) != 0)
      {
        if (_CHECK_SET_BIT(carrent_active_functions, RANG_OUTPUT_LED_DF_REG_WORK_BO) != 0)
        {
          blocking_continue_monitoring_min_U = 0xff;
          end_monitoring_min_max_measurement(IDENTIFIER_BIT_ARRAY_MIN_VOLTAGE, carrent_active_functions);
        }
      }
      
      //���������� �� ����� ����� ��������� ����������� �������
      if(
         ((carrent_active_functions[0] & MASKA_MONITOTYNG_UMAX_SIGNALES_0) != 0) ||
         ((carrent_active_functions[1] & MASKA_MONITOTYNG_UMAX_SIGNALES_1) != 0) ||
         ((carrent_active_functions[2] & MASKA_MONITOTYNG_UMAX_SIGNALES_2) != 0) ||
         ((carrent_active_functions[3] & MASKA_MONITOTYNG_UMAX_SIGNALES_3) != 0) ||
         ((carrent_active_functions[4] & MASKA_MONITOTYNG_UMAX_SIGNALES_4) != 0) ||
         ((carrent_active_functions[5] & MASKA_MONITOTYNG_UMAX_SIGNALES_5) != 0)
        )
      {
        if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MAX_VOLTAGE)) != 0)
          continue_monitoring_max_U(time_from_start_record_dr);
        else
          start_monitoring_max_U(time_from_start_record_dr);
      }
      else
      {
        if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MAX_VOLTAGE)) != 0)
          end_monitoring_min_max_measurement(IDENTIFIER_BIT_ARRAY_MAX_VOLTAGE, carrent_active_functions);
      }
      
      //���������� �� ����� ����� ��������� ������������ ����� ��������� �����������
      if(
         ((carrent_active_functions[0] & MASKA_MONITOTYNG_ZOP_SIGNALES_0) != 0) ||
         ((carrent_active_functions[1] & MASKA_MONITOTYNG_ZOP_SIGNALES_1) != 0) ||
         ((carrent_active_functions[2] & MASKA_MONITOTYNG_ZOP_SIGNALES_2) != 0) ||
         ((carrent_active_functions[3] & MASKA_MONITOTYNG_ZOP_SIGNALES_3) != 0) ||
         ((carrent_active_functions[4] & MASKA_MONITOTYNG_ZOP_SIGNALES_4) != 0) ||
         ((carrent_active_functions[5] & MASKA_MONITOTYNG_ZOP_SIGNALES_5) != 0)
        )
      {
        if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MAX_CURRENT_ZOP)) != 0)
          continue_monitoring_max_ZOP(time_from_start_record_dr);
        else
          start_monitoring_max_ZOP(time_from_start_record_dr);
      }
      else
      {
        if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MAX_CURRENT_ZOP)) != 0)
          end_monitoring_min_max_measurement(IDENTIFIER_BIT_ARRAY_MAX_CURRENT_ZOP, carrent_active_functions);
      }
      
      //���������� �� ����� ����� ��������� �������� ������� 1 ��� ���
      if(
         ((carrent_active_functions[0] & MASKA_MONITOTYNG_F1_MIN_ACHR_SIGNALES_0) != 0) ||
         ((carrent_active_functions[1] & MASKA_MONITOTYNG_F1_MIN_ACHR_SIGNALES_1) != 0) ||
         ((carrent_active_functions[2] & MASKA_MONITOTYNG_F1_MIN_ACHR_SIGNALES_2) != 0) ||
         ((carrent_active_functions[3] & MASKA_MONITOTYNG_F1_MIN_ACHR_SIGNALES_3) != 0) ||
         ((carrent_active_functions[4] & MASKA_MONITOTYNG_F1_MIN_ACHR_SIGNALES_4) != 0) ||
         ((carrent_active_functions[5] & MASKA_MONITOTYNG_F1_MIN_ACHR_SIGNALES_5) != 0)
        )
      {
        if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MIN_FREQUENCY_1_ACHR)) != 0)
          continue_monitoring_min_f1(time_from_start_record_dr);
        else
          start_monitoring_min_f1(time_from_start_record_dr);
      }
      else
      {
        if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MIN_FREQUENCY_1_ACHR)) != 0)
          end_monitoring_min_max_measurement(IDENTIFIER_BIT_ARRAY_MIN_FREQUENCY_1_ACHR, carrent_active_functions);
      }
      
      //���������� �� ����� ����� ��������� �������� ������� 2 ��� ���
      if(
         ((carrent_active_functions[0] & MASKA_MONITOTYNG_F2_MIN_ACHR_SIGNALES_0) != 0) ||
         ((carrent_active_functions[1] & MASKA_MONITOTYNG_F2_MIN_ACHR_SIGNALES_1) != 0) ||
         ((carrent_active_functions[2] & MASKA_MONITOTYNG_F2_MIN_ACHR_SIGNALES_2) != 0) ||
         ((carrent_active_functions[3] & MASKA_MONITOTYNG_F2_MIN_ACHR_SIGNALES_3) != 0) ||
         ((carrent_active_functions[4] & MASKA_MONITOTYNG_F2_MIN_ACHR_SIGNALES_4) != 0) ||
         ((carrent_active_functions[5] & MASKA_MONITOTYNG_F2_MIN_ACHR_SIGNALES_5) != 0)
        )
      {
        if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MIN_FREQUENCY_2_ACHR)) != 0)
          continue_monitoring_min_f2(time_from_start_record_dr);
        else
          start_monitoring_min_f2(time_from_start_record_dr);
      }
      else
      {
        if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MIN_FREQUENCY_2_ACHR)) != 0)
          end_monitoring_min_max_measurement(IDENTIFIER_BIT_ARRAY_MIN_FREQUENCY_2_ACHR, carrent_active_functions);
      }
      
      //� ����� ������� ������ ������� ����
      if (_CHECK_SET_BIT(carrent_active_functions , RANG_OUTPUT_LED_DF_REG_BLOCK_CHAPV_VID_U) == 0)
      {
        //���������� �� ����� ����� ����������� ������� 1 � ������� 2 ��� ���������� ����
        if(
           (_CHECK_SET_BIT(previous_active_functions, RANG_OUTPUT_LED_DF_REG_ACHR_CHAPV_VID_DV) != 0) &&
           (_CHECK_SET_BIT(carrent_active_functions , RANG_OUTPUT_LED_DF_REG_ACHR_CHAPV_VID_DV) == 0)
          )   
        {
          //� ����� ����������� ������� 1 � ������� 2 �� ���������� ����
          
          //�������� ������� ���������� ������� ������� 1 � ������� 2 �� ����
          number_f1_chapv_dr++;
          number_f2_chapv_dr++;
  
          int frequency_val_1_int = (int)frequency_val_1;
          if (frequency_val_1_int >= 0) frequency_val_1_int = (int)(frequency_val_1*1000);
  
          int frequency_val_2_int = (int)frequency_val_2;
          if (frequency_val_2_int >= 0) frequency_val_2_int = (int)(frequency_val_2*1000);

          measurements_f2_chapv_dr[ 0] = measurements_f1_chapv_dr[ 0] = measurement[IM_3I0];
          measurements_f2_chapv_dr[ 1] = measurements_f1_chapv_dr[ 1] = measurement[IM_3I0_other_g];
          measurements_f2_chapv_dr[ 2] = measurements_f1_chapv_dr[ 2] = measurement[IM_IA];
          measurements_f2_chapv_dr[ 3] = measurements_f1_chapv_dr[ 3] = measurement[IM_IC];
          measurements_f2_chapv_dr[ 4] = measurements_f1_chapv_dr[ 4] = measurement[IM_IB_r];
          measurements_f2_chapv_dr[ 5] = measurements_f1_chapv_dr [5] = measurement[IM_I2];
          measurements_f2_chapv_dr[ 6] = measurements_f1_chapv_dr[ 6] = measurement[IM_I1];
          measurements_f2_chapv_dr[ 7] = measurements_f1_chapv_dr[ 7] = measurement[IM_UA];
          measurements_f2_chapv_dr[ 8] = measurements_f1_chapv_dr[ 8] = measurement[IM_UB];
          measurements_f2_chapv_dr[ 9] = measurements_f1_chapv_dr[ 9] = measurement[IM_UC];
          measurements_f2_chapv_dr[10] = measurements_f1_chapv_dr[10] = measurement[IM_3U0_UBC_TN2];
          measurements_f2_chapv_dr[11] = measurements_f1_chapv_dr[11] = measurement[IM_UAB_TN2];
          measurements_f2_chapv_dr[12] = measurements_f1_chapv_dr[12] = measurement[IM_UAB];
          measurements_f2_chapv_dr[13] = measurements_f1_chapv_dr[13] = measurement[IM_UBC];
          measurements_f2_chapv_dr[14] = measurements_f1_chapv_dr[14] = measurement[IM_UCA];
          measurements_f2_chapv_dr[15] = measurements_f1_chapv_dr[15] = (unsigned int)frequency_val_1_int;
          measurements_f2_chapv_dr[16] = measurements_f1_chapv_dr[16] = (unsigned int)frequency_val_2_int;
          measurements_f2_chapv_dr[17] = measurements_f1_chapv_dr[17] = (unsigned int)resistance[R_AB];
          measurements_f2_chapv_dr[18] = measurements_f1_chapv_dr[18] = (unsigned int)resistance[X_AB];
          measurements_f2_chapv_dr[19] = measurements_f1_chapv_dr[19] = (unsigned int)resistance[R_BC];
          measurements_f2_chapv_dr[20] = measurements_f1_chapv_dr[20] = (unsigned int)resistance[X_BC];
          measurements_f2_chapv_dr[21] = measurements_f1_chapv_dr[21] = (unsigned int)resistance[R_CA];
          measurements_f2_chapv_dr[22] = measurements_f1_chapv_dr[22] = (unsigned int)resistance[X_CA];
          measurements_f2_chapv_dr[23] = measurements_f1_chapv_dr[23] = (unsigned int)UNDEF_VMP;
          measurements_f2_chapv_dr[24] = measurements_f1_chapv_dr[24] = 0;
  
          //Գ����� ��� � ������� ������� ��������� ������
          measurements_f2_chapv_dr[25] = measurements_f1_chapv_dr[25] = time_from_start_record_dr;

          //�������, �� �� ������� ������ 1 � ������� 2 �� ����
          state_current_monitoring |= ((1<<IDENTIFIER_BIT_ARRAY_FREQUENCY_1_CHAPV) | (1<<IDENTIFIER_BIT_ARRAY_FREQUENCY_2_CHAPV));
            
          //����� �� ���� ������� � �����, ���� ����� �������� ����� (��� ������� 1)
          end_monitoring_min_max_measurement(IDENTIFIER_BIT_ARRAY_FREQUENCY_1_CHAPV, carrent_active_functions);
          //����� �� ���� ������� � �����, ���� ����� �������� ����� (��� ������� 2)
          end_monitoring_min_max_measurement(IDENTIFIER_BIT_ARRAY_FREQUENCY_2_CHAPV, carrent_active_functions);
        }
        else if (_CHECK_SET_BIT(carrent_active_functions , RANG_OUTPUT_LED_DF_REG_RAZR_CHAPV) != 0)
        {
          //� ����� ������ ���� �� ��������� �����
          
          //���������� �� ����� ����� ����������� ������� 1 ��� ����
          if (  
              (_CHECK_SET_BIT(previous_active_functions, RANG_OUTPUT_LED_DF_REG_F1_ACHR_CHAPV  ) != 0) &&
              (_CHECK_SET_BIT(carrent_active_functions , RANG_OUTPUT_LED_DF_REG_F1_ACHR_CHAPV  ) == 0)
             )   
          {
            //� ����� ����������� ������� 1 �� ����
            
            //�������� ������� ���������� ������� ������� 1 �� ����
            number_f1_chapv_dr++;
  
            int frequency_val_1_int = (int)frequency_val_1;
            if (frequency_val_1_int >= 0) frequency_val_1_int = (int)(frequency_val_1*1000);
  
            int frequency_val_2_int = (int)frequency_val_2;
            if (frequency_val_2_int >= 0) frequency_val_2_int = (int)(frequency_val_2*1000);

            measurements_f1_chapv_dr[ 0] = measurement[IM_3I0];
            measurements_f1_chapv_dr[ 1] = measurement[IM_3I0_other_g];
            measurements_f1_chapv_dr[ 2] = measurement[IM_IA];
            measurements_f1_chapv_dr[ 3] = measurement[IM_IC];
            measurements_f1_chapv_dr[ 4] = measurement[IM_IB_r];
            measurements_f1_chapv_dr [5] = measurement[IM_I2];
            measurements_f1_chapv_dr[ 6] = measurement[IM_I1];
            measurements_f1_chapv_dr[ 7] = measurement[IM_UA];
            measurements_f1_chapv_dr[ 8] = measurement[IM_UB];
            measurements_f1_chapv_dr[ 9] = measurement[IM_UC];
            measurements_f1_chapv_dr[10] = measurement[IM_3U0_UBC_TN2];
            measurements_f1_chapv_dr[11] = measurement[IM_UAB_TN2];
            measurements_f1_chapv_dr[12] = measurement[IM_UAB];
            measurements_f1_chapv_dr[13] = measurement[IM_UBC];
            measurements_f1_chapv_dr[14] = measurement[IM_UCA];
            measurements_f1_chapv_dr[15] = (unsigned int)frequency_val_1_int;
            measurements_f1_chapv_dr[16] = (unsigned int)frequency_val_2_int;
            measurements_f1_chapv_dr[17] = (unsigned int)resistance[R_AB];
            measurements_f1_chapv_dr[18] = (unsigned int)resistance[X_AB];
            measurements_f1_chapv_dr[19] = (unsigned int)resistance[R_BC];
            measurements_f1_chapv_dr[20] = (unsigned int)resistance[X_BC];
            measurements_f1_chapv_dr[21] = (unsigned int)resistance[R_CA];
            measurements_f1_chapv_dr[22] = (unsigned int)resistance[X_CA];
            measurements_f1_chapv_dr[23] = (unsigned int)UNDEF_VMP;
            measurements_f1_chapv_dr[24] = 0;
  
            //Գ����� ��� � ������� ������� ��������� ������
            measurements_f1_chapv_dr[25] = time_from_start_record_dr;

            //�������, �� �� ������� ������ 1 �� ����
            state_current_monitoring |= (1<<IDENTIFIER_BIT_ARRAY_FREQUENCY_1_CHAPV);
            
            //����� �� ���� ������� � �����, ���� ����� �������� �����
            end_monitoring_min_max_measurement(IDENTIFIER_BIT_ARRAY_FREQUENCY_1_CHAPV, carrent_active_functions);
          }

          //���������� �� ����� ����� ����������� ������� 2 ��� ����
          if (  
              (_CHECK_SET_BIT(previous_active_functions, RANG_OUTPUT_LED_DF_REG_F2_ACHR_CHAPV  ) != 0) &&
              (_CHECK_SET_BIT(carrent_active_functions , RANG_OUTPUT_LED_DF_REG_F2_ACHR_CHAPV  ) == 0)
             )   
          {
            //� ����� ����������� ������� 2 �� ����

            //�������� ������� ���������� ������� ������� 2 �� ����
            number_f2_chapv_dr++;
  
            int frequency_val_1_int = (int)frequency_val_1;
            if (frequency_val_1_int >= 0) frequency_val_1_int = (int)(frequency_val_1*1000);
  
            int frequency_val_2_int = (int)frequency_val_2;
            if (frequency_val_2_int >= 0) frequency_val_2_int = (int)(frequency_val_2*1000);

            measurements_f2_chapv_dr[ 0] = measurement[IM_3I0];
            measurements_f2_chapv_dr[ 1] = measurement[IM_3I0_other_g];
            measurements_f2_chapv_dr[ 2] = measurement[IM_IA];
            measurements_f2_chapv_dr[ 3] = measurement[IM_IC];
            measurements_f2_chapv_dr[ 4] = measurement[IM_IB_r];
            measurements_f2_chapv_dr [5] = measurement[IM_I2];
            measurements_f2_chapv_dr[ 6] = measurement[IM_I1];
            measurements_f2_chapv_dr[ 7] = measurement[IM_UA];
            measurements_f2_chapv_dr[ 8] = measurement[IM_UB];
            measurements_f2_chapv_dr[ 9] = measurement[IM_UC];
            measurements_f2_chapv_dr[10] = measurement[IM_3U0_UBC_TN2];
            measurements_f2_chapv_dr[11] = measurement[IM_UAB_TN2];
            measurements_f2_chapv_dr[12] = measurement[IM_UAB];
            measurements_f2_chapv_dr[13] = measurement[IM_UBC];
            measurements_f2_chapv_dr[14] = measurement[IM_UCA];
            measurements_f2_chapv_dr[15] = (unsigned int)frequency_val_1_int;
            measurements_f2_chapv_dr[16] = (unsigned int)frequency_val_2_int;
            measurements_f2_chapv_dr[17] = (unsigned int)resistance[R_AB];
            measurements_f2_chapv_dr[18] = (unsigned int)resistance[X_AB];
            measurements_f2_chapv_dr[19] = (unsigned int)resistance[R_BC];
            measurements_f2_chapv_dr[20] = (unsigned int)resistance[X_BC];
            measurements_f2_chapv_dr[21] = (unsigned int)resistance[R_CA];
            measurements_f2_chapv_dr[22] = (unsigned int)resistance[X_CA];
            measurements_f2_chapv_dr[23] = (unsigned int)UNDEF_VMP;
            measurements_f2_chapv_dr[24] = 0;
  
            //Գ����� ��� � ������� ������� ��������� ������
            measurements_f2_chapv_dr[25] = time_from_start_record_dr;

            //�������, �� �� ������� ������ 2 �� ����
            state_current_monitoring |= (1<<IDENTIFIER_BIT_ARRAY_FREQUENCY_2_CHAPV);
            
            //����� �� ���� ������� � �����, ���� ����� �������� �����
            end_monitoring_min_max_measurement(IDENTIFIER_BIT_ARRAY_FREQUENCY_2_CHAPV, carrent_active_functions);
          }
        }
      }
      
      //������ 䳿 �������� ����� � ���� �������, ���� ������� end_monitoring_min_max_measurement �� ����������� ������� � �� ������� state_dr_record � STATE_DR_NO_RECORD
      if(state_dr_record != STATE_DR_NO_RECORD)
      {
        //����������, �� �� ���� ����� ����������� ������
        //���� ���� ����� ���� - �� ������� ������ ���������� ����������� ����������, �� �� ����������� � ������� ��������
        if (stop_regisrator(carrent_active_functions, current_settings_prt.ranguvannja_digital_registrator, number_group_stp) != 0)
        {
          //������� ������ ������ ����������� ����������
          _CLEAR_BIT(carrent_active_functions, RANG_OUTPUT_LED_DF_REG_WORK_D_REJESTRATOR);

          //���������� ����� ������ �� ���������� ����������� � ���� "���������� ������������ ����� � ��������� DataFlash"
          state_dr_record = STATE_DR_MAKE_RECORD;
        }
      
        //���������� �� �������� ���� ������� � �������� �� ��������� ������. ���� ���� ���� �, �� ������ ����� ��� ������� � �����
        if (
            ((carrent_active_functions[0] != previous_active_functions[0])) ||
            ((carrent_active_functions[1] != previous_active_functions[1])) ||
            ((carrent_active_functions[2] != previous_active_functions[2])) ||
            ((carrent_active_functions[3] != previous_active_functions[3])) ||
            ((carrent_active_functions[4] != previous_active_functions[4])) ||
            ((carrent_active_functions[5] != previous_active_functions[5])) 
           )
        {
          //�������� ���� ������� �� ������� � ��������� ������ �������

          //�������� �� ���� ������� ����� ����
          number_items_dr++;
      
          //���������� ������� ��� �������
          unsigned int number_changes_into_current_item;
          _NUMBER_CHANGES_INTO_UNSIGNED_INT_ARRAY(previous_active_functions, carrent_active_functions, N_BIG, number_changes_into_current_item);
          number_changes_into_dr_record += number_changes_into_current_item;
      
          //�������� ������� c��� �������
          //̳��� ����
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*28 +  0] =  time_from_start_record_dr        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*28 +  1] = (time_from_start_record_dr >> 8 ) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*28 +  2] = (time_from_start_record_dr >> 16) & 0xff;
          //������� ���� �������
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*28 +  3] =  carrent_active_functions[0]        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*28 +  4] = (carrent_active_functions[0] >> 8 ) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*28 +  5] = (carrent_active_functions[0] >> 16) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*28 +  6] = (carrent_active_functions[0] >> 24) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*28 +  7] =  carrent_active_functions[1]        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*28 +  8] = (carrent_active_functions[1] >> 8 ) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*28 +  9] = (carrent_active_functions[1] >> 16) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*28 + 10] = (carrent_active_functions[1] >> 24) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*28 + 11] =  carrent_active_functions[2]        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*28 + 12] = (carrent_active_functions[2] >> 8 ) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*28 + 13] = (carrent_active_functions[2] >> 16) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*28 + 14] = (carrent_active_functions[2] >> 24) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*28 + 15] =  carrent_active_functions[3]        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*28 + 16] = (carrent_active_functions[3] >> 8 ) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*28 + 17] = (carrent_active_functions[3] >> 16) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*28 + 18] = (carrent_active_functions[3] >> 24) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*28 + 19] =  carrent_active_functions[4]        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*28 + 20] = (carrent_active_functions[4] >> 8 ) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*28 + 21] = (carrent_active_functions[4] >> 16) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*28 + 22] = (carrent_active_functions[4] >> 24) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*28 + 23] =  carrent_active_functions[5]        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*28 + 24] = (carrent_active_functions[5] >> 8 ) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*28 + 25] = (carrent_active_functions[5] >> 16) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*28 + 26] = (carrent_active_functions[5] >> 24) & 0xff;
          //ʳ������ ��� ������� � �������� �� ��������� ������
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*28 + 27] = number_changes_into_current_item & 0xff;
        }
        
        //����������, �� ����� ����� ���������� ������
        if (
            (state_dr_record == STATE_DR_MAKE_RECORD)                  ||
            (time_from_start_record_dr >= MAX_TIME_OFFSET_FROM_START)  ||  
            ((number_items_dr + 1)     >= MAX_EVENTS_IN_ONE_RECORD  )  
           )
        {
          //���� ����� ����������� ������, ��� � ����� ���������� ������ - ��������� ���������� ������ � ������ ������� �� �����
          buffer_for_save_dr_record[FIRST_INDEX_NUMBER_ITEMS_DR      ] = number_items_dr;
          buffer_for_save_dr_record[FIRST_INDEX_NUMBER_CHANGES_DR    ] =  number_changes_into_dr_record       & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_NUMBER_CHANGES_DR + 1] = (number_changes_into_dr_record >> 8) & 0xff;

          //���������� �� ����� ��������� ��������� ������������� ������� ������
          if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MAX_CURRENT_PHASE)) != 0)
            end_monitoring_min_max_measurement(IDENTIFIER_BIT_ARRAY_MAX_CURRENT_PHASE, carrent_active_functions);

          //���������� �� ����� ��������� ��������� ������������� ������ 3I0
          if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MAX_CURRENT_3I0)) != 0)
            end_monitoring_min_max_measurement(IDENTIFIER_BIT_ARRAY_MAX_CURRENT_3I0, carrent_active_functions);

          //���������� �� ����� ��������� ��������� ����������� ������� 3U0
          if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MAX_VOLTAGE_3U0)) != 0)
            end_monitoring_min_max_measurement(IDENTIFIER_BIT_ARRAY_MAX_VOLTAGE_3U0, carrent_active_functions);

          //���������� �� ����� ��������� ��������� �������� �������
          if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MIN_VOLTAGE)) != 0)
            end_monitoring_min_max_measurement(IDENTIFIER_BIT_ARRAY_MIN_VOLTAGE, carrent_active_functions);

          //���������� �� ����� ��������� ��������� ����������� �������
          if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MAX_VOLTAGE)) != 0)
            end_monitoring_min_max_measurement(IDENTIFIER_BIT_ARRAY_MAX_VOLTAGE, carrent_active_functions);

          //���������� �� ����� ��������� ��������� ������������� ������ �����������
          if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MAX_CURRENT_ZOP)) != 0)
            end_monitoring_min_max_measurement(IDENTIFIER_BIT_ARRAY_MAX_CURRENT_ZOP, carrent_active_functions);
        
          //���������� �� ����� ��������� ��������� �������� ������� 1 ��� ���
          if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MIN_FREQUENCY_1_ACHR)) != 0)
            end_monitoring_min_max_measurement(IDENTIFIER_BIT_ARRAY_MIN_FREQUENCY_1_ACHR, carrent_active_functions);

          //���������� �� ����� ��������� ��������� �������� ������� 2 ��� ���
          if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MIN_FREQUENCY_2_ACHR)) != 0)
            end_monitoring_min_max_measurement(IDENTIFIER_BIT_ARRAY_MIN_FREQUENCY_2_ACHR, carrent_active_functions);

          /*
          �������� ����������� ������ �������� ��������� ��� ����� ���� ����������
          �� �������, ���� �� ����� ��� �������� �� ����� ��������� �������� ������ ����������
          ��������� ������. ���� ���� �������� ������� ��� �� ����, �� �� ���� ����� ������������ ����
          � ���� ��������, �� ������������ ����� ������������ �������
          */

          //������ 䳿 �������� ����� � ���� �������, ���� ������� end_monitoring_min_max_measurement �� ����������� ������� � �� ������� state_dr_record � STATE_DR_NO_RECORD
          if(state_dr_record != STATE_DR_NO_RECORD)
          {
            //�������� ������� ������������ ������������ ��������� ��� ����
            buffer_for_save_dr_record[FIRST_INDEX_NUMBER_MAX_PHASE_DR  ] = number_max_phase_dr;
            buffer_for_save_dr_record[FIRST_INDEX_NUMBER_MAX_3I0_DR    ] = number_max_3I0_dr;
            buffer_for_save_dr_record[FIRST_INDEX_NUMBER_MAX_3U0_DR    ] = number_max_3U0_dr;
            buffer_for_save_dr_record[FIRST_INDEX_NUMBER_MIN_U_DR      ] = number_min_U_dr;
            buffer_for_save_dr_record[FIRST_INDEX_NUMBER_MAX_U_DR      ] = number_max_U_dr;
            buffer_for_save_dr_record[FIRST_INDEX_NUMBER_MAX_ZOP_DR    ] = number_max_ZOP_dr;
            buffer_for_save_dr_record[FIRST_INDEX_NUMBER_MIN_F1_ACHR_DR] = number_min_f1_achr_dr;
            buffer_for_save_dr_record[FIRST_INDEX_NUMBER_MIN_F2_ACHR_DR] = number_min_f2_achr_dr;
            buffer_for_save_dr_record[FIRST_INDEX_NUMBER_F1_CHAPV_DR   ] = number_f1_chapv_dr;
            buffer_for_save_dr_record[FIRST_INDEX_NUMBER_F2_CHAPV_DR   ] = number_f2_chapv_dr;

            //���������� ����� ������ �� ���������� ����������� � ���� "���������� ������������ ����� � DataFlash"
            if (state_dr_record != STATE_DR_MAKE_RECORD)
            {
              if (time_from_start_record_dr >= MAX_TIME_OFFSET_FROM_START)
              {
                //���� �������� ����������� �� ���� ������, �� ������ ������� ��������� ����� ��� ����������� ���� ����� ������ � ���������� �����
                state_dr_record = STATE_DR_MAKE_RECORD;
              }
              else
              {
                //���� �������� ����������� �� ��������� ����������� ������� ���� (��� ���� �������, ��� ������ �� ���������, ��� ���� �'������� � �����������), �� ������ ������� ��������� ����� ��� �� ���������� ������ ������ ����� �����
                state_dr_record = STATE_DR_CUT_RECORD;
              }
            }
          }
        
          //������� ������ ������ ����������� ����������
          _CLEAR_BIT(carrent_active_functions, RANG_OUTPUT_LED_DF_REG_WORK_D_REJESTRATOR);
        }
      }

      break;
    }
  default:
    {
      //�� ��� ���� �������� ����� �� ���� � �����
      fix_undefined_error_dr(carrent_active_functions);
      break;
    }
  }
  
  //����������, �� ����� ����� ����������� ����� �������� �� ����� � DataFlash
  routine_for_queue_dr();
}
/*****************************************************/

/*****************************************************/
//����������� ����������� ������� ������ ����������� ����������
/*****************************************************/
void fix_undefined_error_ar(unsigned int* carrent_active_functions)
{
  //����������� ������� � ������� � ��������� ���������
  _SET_BIT(set_diagnostyka, ERROR_AR_UNDEFINED_BIT);
  _SET_BIT(carrent_active_functions, RANG_OUTPUT_LED_DF_REG_DEFECT);
  //���������� ����� ������ � ����������� � ���� "�� ����� ������ ���� �� � ���������� ����������� �� ����������" 
  continue_previous_record_ar = 0; /*�������, �� �� �� ������ ����������� ��� ������ ��������� ����������� ����������*/
  state_ar_record = STATE_AR_NO_RECORD;
  //������� ������ ������ ����������� ����������
  _CLEAR_BIT(carrent_active_functions, RANG_OUTPUT_LED_DF_REG_WORK_A_REJESTRATOR);

  //����������� ������� ������ ��������� ��� ����������� ���������� � EEPROM
  _SET_BIT(control_eeprom_taskes, TASK_START_WRITE_INFO_REJESTRATOR_AR_EEPROM_BIT);
  //³��������� ������������ ��������� ��� ����������� ����������
  /*
  ������ �������� ���������, ����� ���� ��� � ����
  */
  info_rejestrator_ar.saving_execution = 0;
  /*
  ������� ������ ������ ����� ������ ������ ��������, � �� �������, ��, ���� ��� ���� ������ ���
  ������� ������, �� ���� �������. ���� ����� �������, �� ���� � ����������� ��������� �� ����� ���� ����
  ����������� ������� ������� ������, �� ����� ������� � ��� � ���������, ����� ������� ������ ����� 
  � ������ ������� �� ������� �����
  */
  unsigned int max_number_records_ar_tmp = max_number_records_ar;
  if (info_rejestrator_ar.number_records >= max_number_records_ar_tmp) 
    info_rejestrator_ar.number_records = max_number_records_ar_tmp - 1; /*����� ��� �� ���� ==, ��� ��� ��������������� �� ����������� ������� � �������� >=*/
}
/*****************************************************/

/*****************************************************/
//������� ������� ����� ����������� ����������
/*****************************************************/
inline void analog_registrator(unsigned int* carrent_active_functions)
{
  static unsigned int unsaved_bytes_of_header_ar;

  //���������� ������� ����������� �������  ������ ����������� ����������
  _SET_BIT(clear_diagnostyka, ERROR_AR_UNDEFINED_BIT);

  if (continue_previous_record_ar != 0)
  {
    /*
    �� �������� ������, �� ���� ��������� ������� ����������� ����������, �� ���������
    � ������ ���������� ���������, � ����� ��� ������������� ��������� ��������� ����� ����� �� 
    ������ ��������, �� �� ������� ��������� ������������� (� ����-���� ��� �� ��
    ���������� ����������� �������� ������ ����������� ����������, �� ��� ���� ����������
    �����������. �� ���� ������ ������������� ��������� ������ ������ ������)
    */
    if(
       ((carrent_active_functions[0] & current_settings_prt.ranguvannja_analog_registrator[0]) == 0) &&
       ((carrent_active_functions[1] & current_settings_prt.ranguvannja_analog_registrator[1]) == 0) &&
       ((carrent_active_functions[2] & current_settings_prt.ranguvannja_analog_registrator[2]) == 0) &&
       ((carrent_active_functions[3] & current_settings_prt.ranguvannja_analog_registrator[3]) == 0) &&
       ((carrent_active_functions[4] & current_settings_prt.ranguvannja_analog_registrator[4]) == 0) &&
       ((carrent_active_functions[5] & current_settings_prt.ranguvannja_analog_registrator[5]) == 0) 
      ) 
    {
      //����� ������������� ��������� ������� ������ ������ ��������
      continue_previous_record_ar = 0;
    }
  }

  switch (state_ar_record)
  {
  case STATE_AR_NO_RECORD:
    {
      if(semaphore_read_state_ar_record == 0)
      {
        /*
        ������� ���� ��������, �� ��� ��������� ����� ������ ����������� ���������� ���������� ���������� ������ ���������� ����������
        ������ ������� semaphore_read_state_ar_record ��� ����, �� ���� ������ ����������� ���������� STATE_AR_NO_RECORD ������,
        �� ����� ���� �������� �� ���� ������, ���� ������ ���������� ������� ���� ��� ��������� ����������� ������ ����������� ����������
        */
        _SET_BIT(clear_diagnostyka, ERROR_AR_TEMPORARY_BUSY_BIT);
      }

      //��������, �� ����� ����� ������� ����������� ����������
      if (
          (
           ((carrent_active_functions[0] & current_settings_prt.ranguvannja_analog_registrator[0]) != 0) ||
           ((carrent_active_functions[1] & current_settings_prt.ranguvannja_analog_registrator[1]) != 0) ||
           ((carrent_active_functions[2] & current_settings_prt.ranguvannja_analog_registrator[2]) != 0) ||
           ((carrent_active_functions[3] & current_settings_prt.ranguvannja_analog_registrator[3]) != 0) ||
           ((carrent_active_functions[4] & current_settings_prt.ranguvannja_analog_registrator[4]) != 0) ||
           ((carrent_active_functions[5] & current_settings_prt.ranguvannja_analog_registrator[5]) != 0)
          )
          &&  
          (continue_previous_record_ar == 0) /*��� ��������� ����� ��.���������� (���� ���� ����) ��� �� ������� ��������� ���� ���� � ����� ���� ����� �������*/ 
         )
      {
        //����������, �� ��� ������� ������ ������ � ��� �� ��� ������ �������������� ���������� ���������
        if(semaphore_read_state_ar_record == 0)
        {
          //� ����� ������� ����������� ����������
          continue_previous_record_ar = 0xff; /*������� ����-���� ������, �� ������������ �������� ��.����������, �� ��������� ������ ����������� ����������*/
    
          //����� �������� ����� �����
          
          //�������� ���� ������� ������
          header_ar.label_start_record = LABEL_START_RECORD_AR;
          //�������� ��� ������� ������
          unsigned char *label_to_time_array;
          if (copying_time == 2) label_to_time_array = time_copy;
          else label_to_time_array = time;
          for(unsigned int i = 0; i < 7; i++) header_ar.time[i] = *(label_to_time_array + i);
          //���������� ������������� T0
          header_ar.T0 = current_settings_prt.T0;
          //���������� ������������� TT
          header_ar.TCurrent = current_settings_prt.TCurrent;
          //���������� ������������� T�
          header_ar.TVoltage = current_settings_prt.TVoltage;
          //�������� ������������ ��� ���� ���� �������� ���������� ���������
          header_ar.control_extra_settings_1 = current_settings_prt.control_extra_settings_1 & (CTR_EXTRA_SETTINGS_1_CTRL_3U0_Ubc_TN2 | CTR_EXTRA_SETTINGS_1_CTRL_PHASE_LINE);
          //�'�� ������
          for(unsigned int i=0; i<MAX_CHAR_IN_NAME_OF_CELL; i++)
            header_ar.name_of_cell[i] = current_settings_prt.name_of_cell[i] & 0xff;
          
          //�������, �� �� �� �� �� "��������" ����� �������� � ����� ��� ����������� ����������
          copied_number_samples = 0;
          //��������� �������� ������� ������� �������, �� ����� ���� ������� � ��������� dataFlash2
          total_number_samples = ((current_settings_prt.prefault_number_periods + current_settings_prt.postfault_number_periods) << VAGA_NUMBER_POINT_AR)*(NUMBER_ANALOG_CANALES + number_word_digital_part_ar);

          //���������,�� ������ ��������� ����������� ���������� �� ����������� � ����� ����� ������ ��� ����������� ��� ��� ������ � DataFlash
          unsaved_bytes_of_header_ar = sizeof(__HEADER_AR);

          //��������� � ��� ������ ����������
          temporary_address_ar = info_rejestrator_ar.next_address;

          //���������, �� ���� �� ���� ������������ ����� ��� ������
          count_to_save = 0;
          //����������� ����-���� ���������� ������ ����� �� ��������� ����� ����� ��� ������
          permit_copy_new_data = 0xff;

          //����� ������ ������������ ��� ������� ��������� ����������� ����������� � ������������ ����� � ����� ��� ������ � DataFlash
          if (making_buffer_for_save_ar_record(&unsaved_bytes_of_header_ar) != 0)
          {
            //³������� ���������� �������� - ���� �������� ���������� ����� �� ���� � ��������
            fix_undefined_error_ar(carrent_active_functions);
          }
          else
          {
            //���������� ����� ������ �� ���������� ����������� � ���� "����� ������ ������"
            state_ar_record = STATE_AR_START;
            //����������� ������� �������
            _SET_BIT(carrent_active_functions, RANG_OUTPUT_LED_DF_REG_WORK_A_REJESTRATOR);

            //� �������� �� ���������� ����� ���������� ����������� �����������, �� ������� ����� � �� �� ���������
            _SET_BIT(control_eeprom_taskes, TASK_START_WRITE_INFO_REJESTRATOR_AR_EEPROM_BIT);
            info_rejestrator_ar.saving_execution = 1;
          }
        }
        else
        {
          //����������� �������, �� ��������� ���������� ��������� � ������� (���� ��, �� ��� �������� ������ ����� ��������)
          _SET_BIT(set_diagnostyka, ERROR_AR_TEMPORARY_BUSY_BIT);
          _SET_BIT(carrent_active_functions, RANG_OUTPUT_LED_DF_REG_DEFECT);
        }
      }
      break;
    }
  case STATE_AR_START:
    {
      //ͳ���� �� �� ��������, ���� �� ����������� ����� STATE_AR_SAVE_SRAM_AND_SAVE_FLASH,  ��� STATE_AR_ONLY_SAVE_FLASH
      break;
    }
  case STATE_AR_SAVE_SRAM_AND_SAVE_FLASH:
  case STATE_AR_ONLY_SAVE_FLASH:
    {
      if (state_ar_record == STATE_AR_ONLY_SAVE_FLASH)
      {
        /*
        ���� ������������ ����� ������������ �� ������
        */
        if (_CHECK_SET_BIT(carrent_active_functions, RANG_OUTPUT_LED_DF_REG_WORK_A_REJESTRATOR) != 0)
        {
          //������ ������ ������ ����������� ����������
          _CLEAR_BIT(carrent_active_functions, RANG_OUTPUT_LED_DF_REG_WORK_A_REJESTRATOR);
        }
        
        if (_CHECK_SET_BIT(carrent_active_functions, RANG_OUTPUT_LED_DF_REG_WORK_A_REJESTRATOR) == 0)
        {
          /*
          ��������� ����� ��� ������, ���� ������ ������� ������ ����������� ����������� ��� ������
          */
          if  (continue_previous_record_ar == 0)
          {
            /*
            ����������, �� ���� ����� ������� ������ ������� �� �������, 
            ���� �� ������ ����� �� ��������� �������
            */
            if (
                ((carrent_active_functions[0] & current_settings_prt.ranguvannja_analog_registrator[0]) != 0) ||
                ((carrent_active_functions[1] & current_settings_prt.ranguvannja_analog_registrator[1]) != 0) ||
                ((carrent_active_functions[2] & current_settings_prt.ranguvannja_analog_registrator[2]) != 0) ||
                ((carrent_active_functions[3] & current_settings_prt.ranguvannja_analog_registrator[3]) != 0) ||
                ((carrent_active_functions[4] & current_settings_prt.ranguvannja_analog_registrator[4]) != 0) ||
                ((carrent_active_functions[5] & current_settings_prt.ranguvannja_analog_registrator[5]) != 0)
               ) 
            {
              //����������� �������, �� ��������� ���������� ��������� � ������� (���� ��, �� ����������� ��������� �����)
              _SET_BIT(set_diagnostyka, ERROR_AR_TEMPORARY_BUSY_BIT);
              _SET_BIT(carrent_active_functions, RANG_OUTPUT_LED_DF_REG_DEFECT);
            }
          }
        }
      }
      
      if (permit_copy_new_data != 0)
      {
        /*
        ����� ������ ������������ ��� ������� ��������� ����������� ����������� 
        � ������������ ����� � ����� ��� ������ � DataFlash ����� ���, ���� � �����
        �� �� ��������
        */
        if (making_buffer_for_save_ar_record(&unsaved_bytes_of_header_ar) != 0)
        {
          //³������� ���������� �������� - ���� �������� ���������� ����� �� ���� � ��������
          fix_undefined_error_ar(carrent_active_functions);
        }
      }
      else
      {
        if (
            (copied_number_samples == total_number_samples) &&
            (count_to_save == 0                           ) && 
            (
             (control_tasks_dataflash &
              (
               TASK_MAMORY_PART_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_AR | 
               TASK_MAMORY_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_AR
              )
             ) == 0
            )   
           )
        {
          //����� ������� ������ ������������ ����������
          unsigned int index_array_ar_heat_tmp = index_array_ar_heat;/*�� ����� ��� ����, �� ��������� ���� ����������� ��� �������� ������ � ��������� volatile*/
          unsigned int index_array_ar_tail_tmp = index_array_ar_tail;/*�� ����� ��� ����, �� ��������� ���� ����������� ��� �������� ������ � ��������� volatile*/
          if(
             (index_array_ar_tail_tmp == index_array_ar_heat_tmp) &&
             (state_ar_record == STATE_AR_ONLY_SAVE_FLASH)  
            )  
          {
            //�������� ����� ������� ������ ����������� ����������
            state_ar_record = STATE_AR_NO_RECORD;

            //����������� ������� ������ ��������� ����������� ���������� � EEPROM
            _SET_BIT(control_eeprom_taskes, TASK_START_WRITE_INFO_REJESTRATOR_AR_EEPROM_BIT);
            //��������� ���� ������ ���������� ������, ���� ������� ������ � ������ �����������, �� ����� ��� �����
            if ((temporary_address_ar + size_one_ar_record) > (NUMBER_PAGES_INTO_DATAFLASH_2 << VAGA_SIZE_PAGE_DATAFLASH_2))
              temporary_address_ar = 0; 
            info_rejestrator_ar.next_address = temporary_address_ar;
            info_rejestrator_ar.saving_execution = 0;
            unsigned int max_number_records_ar_tmp = max_number_records_ar;
            if (info_rejestrator_ar.number_records < max_number_records_ar_tmp) info_rejestrator_ar.number_records += 1;
            else info_rejestrator_ar.number_records = max_number_records_ar_tmp;
          }
          else
          {
            /*� ������ ������ ����������� ���������� ������� ���, ���� �����
            �� ����������������� ���������� ������ ����������� ����������
            
            �� ������ ������ ������� �������� ����, �� �� ��������� ����������
            ����������� ������� ����������� ������� �������
            */
            fix_undefined_error_ar(carrent_active_functions);
          }
        }
        else
        {
          //����� ������ ������� �� ����� ������������ �����
          if (
              (count_to_save != 0 ) 
              && 
              (
               (control_tasks_dataflash &
                (
                 TASK_MAMORY_PART_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_AR | 
                 TASK_MAMORY_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_AR
                )
               ) == 0
              )   
             )
          {
            /*
            ������ ������� �� ����� ����� ����� ����� ��� ���� �� ��� ����� �����
            ���������� ����������� ����� � ���� � ��� ��� ��� ������
            */
            
            if (((temporary_address_ar & 0x1ff) + count_to_save) <= SIZE_PAGE_DATAFLASH_2)
            {
              //���� ������� ��� ��������� ������� ���� ��� ������ (� ���� ������� ��� ���������� � ������ ������)
              
              if (count_to_save == SIZE_PAGE_DATAFLASH_2) control_tasks_dataflash |= TASK_MAMORY_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_AR;
              else control_tasks_dataflash |= TASK_MAMORY_PART_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_AR;
            }
            else
            {
              //³������� ���������� �������� - ���� �������� ���������� ����� �� ���� � ��������
              fix_undefined_error_ar(carrent_active_functions);
            }
          }
        }

      }
      break;
    }
  case STATE_AR_TEMPORARY_BLOCK:
    {
      //�� ����� ������ ���� ������� �������� �������� ������ ����������� �����������
      //��������, �� ����� ����� ������� ����������� ����������
      if (
          ((carrent_active_functions[0] & current_settings_prt.ranguvannja_analog_registrator[0]) != 0) ||
          ((carrent_active_functions[1] & current_settings_prt.ranguvannja_analog_registrator[1]) != 0) ||
          ((carrent_active_functions[2] & current_settings_prt.ranguvannja_analog_registrator[2]) != 0) ||
          ((carrent_active_functions[3] & current_settings_prt.ranguvannja_analog_registrator[3]) != 0) ||
          ((carrent_active_functions[4] & current_settings_prt.ranguvannja_analog_registrator[4]) != 0) ||
          ((carrent_active_functions[5] & current_settings_prt.ranguvannja_analog_registrator[5]) != 0)
         )
      {
        //����������� �������, �� ��������� ���������� ��������� � �������
        _SET_BIT(set_diagnostyka, ERROR_AR_TEMPORARY_BUSY_BIT);
        _SET_BIT(carrent_active_functions, RANG_OUTPUT_LED_DF_REG_DEFECT);
      }
      break;
    }
  default:
    {
      //³������� ���������� �������� - ���� �������� ���������� ����� �� ���� � ��������
      fix_undefined_error_ar(carrent_active_functions);
      break;
    }
  }
}
/*****************************************************/


/*****************************************************/
//������� ������� � ��� ����������� �� ���� ��������
/*****************************************************/
inline void main_protection(void)
{
  unsigned int activated_functions[N_BIG] = {0, 0, 0, 0, 0, 0};
  
  /**************************/
  //��������, �� ����� �������� ������ �������
  /**************************/
  if (reset_trigger_function_from_interface !=0)
  {
    if ((reset_trigger_function_from_interface & (1 << USB_RECUEST)) != 0)
    {
      trigger_functions_USB[0] = 0;
      trigger_functions_USB[1] = 0;
      trigger_functions_USB[2] = 0;
      trigger_functions_USB[3] = 0;
      trigger_functions_USB[4] = 0;
      trigger_functions_USB[5] = 0;
      
      information_about_settings_changed &= (unsigned int)(~(1 << USB_RECUEST));
      information_about_restart_counter  &= (unsigned int)(~(1 << USB_RECUEST));
      information_about_clean_energy     &= (unsigned int)(~(1 << USB_RECUEST));
    }
    if ((reset_trigger_function_from_interface & (1 << RS485_RECUEST)) != 0)
    {
      trigger_functions_RS485[0] = 0;
      trigger_functions_RS485[1] = 0;
      trigger_functions_RS485[2] = 0;
      trigger_functions_RS485[3] = 0;
      trigger_functions_RS485[4] = 0;
      trigger_functions_RS485[5] = 0;
      
      information_about_settings_changed &= (unsigned int)(~(1 << RS485_RECUEST));
      information_about_restart_counter  &= (unsigned int)(~(1 << RS485_RECUEST));
      information_about_clean_energy     &= (unsigned int)(~(1 << RS485_RECUEST));
    }
    
    //������� �� �� �������� ������� �� �Ѳ� �����������
    reset_trigger_function_from_interface = 0;
  }
  /**************************/

  /**************************/
  //����������� �������� ������ - ����� ��������������� ����������, �� ��� ��� ����� �� ������������ ���������� ������� � ������
  /**************************/
  if ((pressed_buttons !=0) || (activation_function_from_interface != 0))
  {
    unsigned int temp_value_for_activated_function = 0;
    
    //��������� � �������
    if (pressed_buttons != 0)
    {
      for (unsigned int i = 0; i < NUMBER_DEFINED_BUTTONS; i++)
      {
        if ((pressed_buttons & (1 << i)) != 0)
          temp_value_for_activated_function |= current_settings_prt.ranguvannja_buttons[i];
      }

      //������� �������� ������, �� �� ��� ����������
      pressed_buttons =0;
    }
    
    //��������� � ����������
    if (activation_function_from_interface != 0)
    {
      temp_value_for_activated_function |= activation_function_from_interface;
      
      //������� ������ ��������� ������� � ���������, �� �� ��� ����������
      activation_function_from_interface = 0;
    }
    
    //����  ������� �������������� ����� ������ �� ���������� �� � ���������� ����� �������, �� ����� ���� ����� ���������
    if(temp_value_for_activated_function != 0) 
    {
      //���������� �������
      for (unsigned int i = 0; i < NUMBER_DEFINED_FUNCTIONS; i++)
      {
        unsigned int tmp_state_df = 0;
        switch (i)
        {
        case 0:
          {
            tmp_state_df = ((temp_value_for_activated_function & (1<<RANG_BUTTON_DF1_IN) )>>RANG_BUTTON_DF1_IN ) << (RANG_OUTPUT_LED_DF_REG_DF1_IN & 0x1f);

            if (tmp_state_df != 0)
              activated_functions[RANG_OUTPUT_LED_DF_REG_DF1_IN >> 5] |= tmp_state_df;
            
            break;
          }
        case 1:
          {
            tmp_state_df = ((temp_value_for_activated_function & (1<<RANG_BUTTON_DF2_IN) )>>RANG_BUTTON_DF2_IN ) << (RANG_OUTPUT_LED_DF_REG_DF2_IN & 0x1f);

            if (tmp_state_df != 0)
              activated_functions[RANG_OUTPUT_LED_DF_REG_DF2_IN >> 5] |= tmp_state_df;
            
            break;
          }
        case 2:
          {
            tmp_state_df = ((temp_value_for_activated_function & (1<<RANG_BUTTON_DF3_IN) )>>RANG_BUTTON_DF3_IN ) << (RANG_OUTPUT_LED_DF_REG_DF3_IN & 0x1f);

            if (tmp_state_df != 0)
              activated_functions[RANG_OUTPUT_LED_DF_REG_DF3_IN >> 5] |= tmp_state_df;

            break;
          }
        case 3:
          {
            tmp_state_df = ((temp_value_for_activated_function & (1<<RANG_BUTTON_DF4_IN) )>>RANG_BUTTON_DF4_IN ) << (RANG_OUTPUT_LED_DF_REG_DF4_IN & 0x1f);

            if (tmp_state_df != 0)
              activated_functions[RANG_OUTPUT_LED_DF_REG_DF4_IN >> 5] |= tmp_state_df;

            break;
          }
        case 4:
          {
            tmp_state_df = ((temp_value_for_activated_function & (1<<RANG_BUTTON_DF5_IN) )>>RANG_BUTTON_DF5_IN ) << (RANG_OUTPUT_LED_DF_REG_DF5_IN & 0x1f);

            if (tmp_state_df != 0)
              activated_functions[RANG_OUTPUT_LED_DF_REG_DF5_IN >> 5] |= tmp_state_df;

            break;
          }
        case 5:
          {
            tmp_state_df = ((temp_value_for_activated_function & (1<<RANG_BUTTON_DF6_IN) )>>RANG_BUTTON_DF6_IN ) << (RANG_OUTPUT_LED_DF_REG_DF6_IN & 0x1f);

            if (tmp_state_df != 0)
              activated_functions[RANG_OUTPUT_LED_DF_REG_DF6_IN >> 5] |= tmp_state_df;

            break;
          }
        case 6:
          {
            tmp_state_df = ((temp_value_for_activated_function & (1<<RANG_BUTTON_DF7_IN) )>>RANG_BUTTON_DF7_IN ) << (RANG_OUTPUT_LED_DF_REG_DF7_IN & 0x1f);

            if (tmp_state_df != 0)
              activated_functions[RANG_OUTPUT_LED_DF_REG_DF7_IN >> 5] |= tmp_state_df;

            break;
          }
        case 7:
          {
            tmp_state_df = ((temp_value_for_activated_function & (1<<RANG_BUTTON_DF8_IN) )>>RANG_BUTTON_DF8_IN ) << (RANG_OUTPUT_LED_DF_REG_DF8_IN & 0x1f);

            if (tmp_state_df != 0)
              activated_functions[RANG_OUTPUT_LED_DF_REG_DF8_IN >> 5] |= tmp_state_df;

            break;
          }
        default: break;
        }
        
        if (tmp_state_df != 0)
        {
          //����� �� ������������ ��x, ���� ����� ��������� ������ �� �����������,
          //��� ����, ��� ���� ��� ��� ����� ���� ������� � ����� ������� �����
          if (global_timers[INDEX_TIMER_DF_PROLONG_SET_FOR_BUTTON_INTERFACE_START + i] <0)
          {
            //��������� ������ ������ ����������� ���� ������� � ��������� ���� (������� ��������� �����)
            //������ ������ ����� �� ���� ��������, ���� �� �� �� �������
            global_timers[INDEX_TIMER_DF_PROLONG_SET_FOR_BUTTON_INTERFACE_START + i] = 0;
          }
        }
        
      }
      
      //���������� ������
      for (unsigned int i = 0; i < NUMBER_DEFINED_TRIGGERS; i++)
      {
        switch (i)
        {
        case 0:
          {
            activated_functions[RANG_OUTPUT_LED_DF_REG_DT1_SET   >> 5] |= ((temp_value_for_activated_function & (1<<RANG_BUTTON_DT1_SET  ) )>>RANG_BUTTON_DT1_SET   ) << (RANG_OUTPUT_LED_DF_REG_DT1_SET   & 0x1f);
            activated_functions[RANG_OUTPUT_LED_DF_REG_DT1_RESET >> 5] |= ((temp_value_for_activated_function & (1<<RANG_BUTTON_DT1_RESET) )>>RANG_BUTTON_DT1_RESET ) << (RANG_OUTPUT_LED_DF_REG_DT1_RESET & 0x1f);
            break;
          }
        case 1:
          {
            activated_functions[RANG_OUTPUT_LED_DF_REG_DT2_SET   >> 5] |= ((temp_value_for_activated_function & (1<<RANG_BUTTON_DT2_SET  ) )>>RANG_BUTTON_DT2_SET   ) << (RANG_OUTPUT_LED_DF_REG_DT2_SET   & 0x1f);
            activated_functions[RANG_OUTPUT_LED_DF_REG_DT2_RESET >> 5] |= ((temp_value_for_activated_function & (1<<RANG_BUTTON_DT2_RESET) )>>RANG_BUTTON_DT2_RESET ) << (RANG_OUTPUT_LED_DF_REG_DT2_RESET & 0x1f);
            break;
          }
        case 2:
          {
            activated_functions[RANG_OUTPUT_LED_DF_REG_DT3_SET   >> 5] |= ((temp_value_for_activated_function & (1<<RANG_BUTTON_DT3_SET  ) )>>RANG_BUTTON_DT3_SET   ) << (RANG_OUTPUT_LED_DF_REG_DT3_SET   & 0x1f);
            activated_functions[RANG_OUTPUT_LED_DF_REG_DT3_RESET >> 5] |= ((temp_value_for_activated_function & (1<<RANG_BUTTON_DT3_RESET) )>>RANG_BUTTON_DT3_RESET ) << (RANG_OUTPUT_LED_DF_REG_DT3_RESET & 0x1f);
            break;
          }
        case 3:
          {
            activated_functions[RANG_OUTPUT_LED_DF_REG_DT4_SET   >> 5] |= ((temp_value_for_activated_function & (1<<RANG_BUTTON_DT4_SET  ) )>>RANG_BUTTON_DT4_SET   ) << (RANG_OUTPUT_LED_DF_REG_DT4_SET   & 0x1f);
            activated_functions[RANG_OUTPUT_LED_DF_REG_DT4_RESET >> 5] |= ((temp_value_for_activated_function & (1<<RANG_BUTTON_DT4_RESET) )>>RANG_BUTTON_DT4_RESET ) << (RANG_OUTPUT_LED_DF_REG_DT4_RESET & 0x1f);
            break;
          }
        default: break;
        }
      }
      
      //�������� ��������� � ����
      activated_functions[RANG_OUTPUT_LED_DF_REG_RESET_LEDS  >> 5] |= ((temp_value_for_activated_function & (1<<RANG_BUTTON_RESET_LEDS ) )>>RANG_BUTTON_RESET_LEDS ) << (RANG_OUTPUT_LED_DF_REG_RESET_LEDS  & 0x1f);
      activated_functions[RANG_OUTPUT_LED_DF_REG_RESET_RELES >> 5] |= ((temp_value_for_activated_function & (1<<RANG_BUTTON_RESET_RELES) )>>RANG_BUTTON_RESET_RELES) << (RANG_OUTPUT_LED_DF_REG_RESET_RELES & 0x1f);

      //"̳�����/�����������" ���������
      if ((temp_value_for_activated_function & (1<<RANG_BUTTON_MISCEVE_DYSTANCIJNE )) != 0)
      {
        //���������� ������� � ������������� ������ "̳�����/�����������"
        misceve_dystancijne = (misceve_dystancijne ^ 0x1) & 0x1;
        //����������� ����������� ��� ��, �� � EEPROM ����� �������� ��� �������� ���������� ������ � ��������� ��������������
        _SET_BIT(control_eeprom_taskes, TASK_START_WRITE_TRG_FUNC_EEPROM_BIT);
      }
      
      //���������-���������� ��������
      activated_functions[RANG_OUTPUT_LED_DF_REG_VKL_VV  >> 5] |= ((temp_value_for_activated_function & (1<<RANG_BUTTON_VKL_VV ) )>>RANG_BUTTON_VKL_VV ) << (RANG_OUTPUT_LED_DF_REG_VKL_VV  & 0x1f);
      activated_functions[RANG_OUTPUT_LED_DF_REG_OTKL_VV >> 5] |= ((temp_value_for_activated_function & (1<<RANG_BUTTON_OTKL_VV) )>>RANG_BUTTON_OTKL_VV) << (RANG_OUTPUT_LED_DF_REG_OTKL_VV & 0x1f);

      //�������� ���������� ��������� �� ��
      activated_functions[RANG_OUTPUT_LED_DF_REG_RESET_BLOCK_READY_TU_VID_ZAHYSTIV >> 5] |= ((temp_value_for_activated_function & (1<<RANG_BUTTON_RESET_BLOCK_READY_TU_VID_ZAHYSTIV ) )>>RANG_BUTTON_RESET_BLOCK_READY_TU_VID_ZAHYSTIV ) << (RANG_OUTPUT_LED_DF_REG_RESET_BLOCK_READY_TU_VID_ZAHYSTIV  & 0x1f);
      
      //������� ���-���
      activated_functions[RANG_OUTPUT_LED_DF_REG_RESET_BLOCK_APV_ZMN >> 5] |= ((temp_value_for_activated_function & (1<<RANG_BUTTON_RESET_BLOCK_APV_ZMN ) )>>RANG_BUTTON_RESET_BLOCK_APV_ZMN ) << (RANG_OUTPUT_LED_DF_REG_RESET_BLOCK_APV_ZMN  & 0x1f);

      //������� ���
      activated_functions[RANG_OUTPUT_LED_DF_REG_OTKL_AVR              >> 5] |= ((temp_value_for_activated_function & (1<<RANG_BUTTON_OTKL_AVR              ) )>>RANG_BUTTON_OTKL_AVR              ) << (RANG_OUTPUT_LED_DF_REG_OTKL_AVR               & 0x1f);
      activated_functions[RANG_OUTPUT_LED_DF_REG_SBROS_BLOCK_AVR       >> 5] |= ((temp_value_for_activated_function & (1<<RANG_BUTTON_SBROS_BLOCK_AVR       ) )>>RANG_BUTTON_SBROS_BLOCK_AVR       ) << (RANG_OUTPUT_LED_DF_REG_SBROS_BLOCK_AVR        & 0x1f);
    }
  }
  /**************************/

  //"̳��./�������."  � �������������� ������ ����
  activated_functions[RANG_OUTPUT_LED_DF_REG_MISCEVE_DYSTANCIJNE >> 5] |= (misceve_dystancijne & 0x1) << (RANG_OUTPUT_LED_DF_REG_MISCEVE_DYSTANCIJNE & 0x1f);

  unsigned int blocking_commands_from_DI = 0;
  unsigned int active_inputs_grupa_ustavok = 0;
  /**************************/
  //����������� �������� �����
  /**************************/
  //���������� �� � ����� ������ �����
  if (active_inputs !=0)
  {
    //� ����� ������
    unsigned int temp_value_for_activated_function_2[N_SMALL] = {0,0};
    for (unsigned int i = 0; i < NUMBER_INPUTS; i++)
    {
      if ((active_inputs & (1 << i)) != 0)
      {
        temp_value_for_activated_function_2[0] |= current_settings_prt.ranguvannja_inputs[N_SMALL*i  ];
        temp_value_for_activated_function_2[1] |= current_settings_prt.ranguvannja_inputs[N_SMALL*i+1];
      }
    }
    
    //����  ������� �������������� ����� �� �� ���������� �� � ���������� ����� �������, �� ����� ���� ����� ���������
    if(
       (temp_value_for_activated_function_2[0] != 0) ||
       (temp_value_for_activated_function_2[1] != 0)
      ) 
    {
      //���������� �������
      for (unsigned int i = 0; i < NUMBER_DEFINED_FUNCTIONS; i++)
      {
        switch (i)
        {
        case 0:
          {
            activated_functions[RANG_OUTPUT_LED_DF_REG_DF1_IN >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_DF1_IN) != 0) << (RANG_OUTPUT_LED_DF_REG_DF1_IN & 0x1f);
            break;
          }
        case 1:
          {
            activated_functions[RANG_OUTPUT_LED_DF_REG_DF2_IN >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_DF2_IN) != 0) << (RANG_OUTPUT_LED_DF_REG_DF2_IN & 0x1f);
            break;
          }
        case 2:
          {
            activated_functions[RANG_OUTPUT_LED_DF_REG_DF3_IN >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_DF3_IN) != 0) << (RANG_OUTPUT_LED_DF_REG_DF3_IN & 0x1f);
            break;
          }
        case 3:
          {
            activated_functions[RANG_OUTPUT_LED_DF_REG_DF4_IN >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_DF4_IN) != 0) << (RANG_OUTPUT_LED_DF_REG_DF4_IN & 0x1f);
            break;
          }
        case 4:
          {
            activated_functions[RANG_OUTPUT_LED_DF_REG_DF5_IN >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_DF5_IN) != 0) << (RANG_OUTPUT_LED_DF_REG_DF5_IN & 0x1f);
            break;
          }
        case 5:
          {
            activated_functions[RANG_OUTPUT_LED_DF_REG_DF6_IN >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_DF6_IN) != 0) << (RANG_OUTPUT_LED_DF_REG_DF6_IN & 0x1f);
            break;
          }
        case 6:
          {
            activated_functions[RANG_OUTPUT_LED_DF_REG_DF7_IN >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_DF7_IN) != 0) << (RANG_OUTPUT_LED_DF_REG_DF7_IN & 0x1f);
            break;
          }
        case 7:
          {
            activated_functions[RANG_OUTPUT_LED_DF_REG_DF8_IN >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_DF8_IN) != 0) << (RANG_OUTPUT_LED_DF_REG_DF8_IN & 0x1f);
            break;
          }
        default: break;
        }
      }

      //���������� ������
      for (unsigned int i = 0; i < NUMBER_DEFINED_TRIGGERS; i++)
      {
        switch (i)
        {
        case 0:
          {
            activated_functions[RANG_OUTPUT_LED_DF_REG_DT1_SET   >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_DT1_SET  ) != 0) << (RANG_OUTPUT_LED_DF_REG_DT1_SET   & 0x1f);
            activated_functions[RANG_OUTPUT_LED_DF_REG_DT1_RESET >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_DT1_RESET) != 0) << (RANG_OUTPUT_LED_DF_REG_DT1_RESET & 0x1f);
            break;
          }
        case 1:
          {
            activated_functions[RANG_OUTPUT_LED_DF_REG_DT2_SET   >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_DT2_SET  ) != 0) << (RANG_OUTPUT_LED_DF_REG_DT2_SET   & 0x1f);
            activated_functions[RANG_OUTPUT_LED_DF_REG_DT2_RESET >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_DT2_RESET) != 0) << (RANG_OUTPUT_LED_DF_REG_DT2_RESET & 0x1f);
            break;
          }
        case 2:
          {
            activated_functions[RANG_OUTPUT_LED_DF_REG_DT3_SET   >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_DT3_SET  ) != 0) << (RANG_OUTPUT_LED_DF_REG_DT3_SET   & 0x1f);
            activated_functions[RANG_OUTPUT_LED_DF_REG_DT3_RESET >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_DT3_RESET) != 0) << (RANG_OUTPUT_LED_DF_REG_DT3_RESET & 0x1f);
            break;
          }
        case 3:
          {
            activated_functions[RANG_OUTPUT_LED_DF_REG_DT4_SET   >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_DT4_SET  ) != 0) << (RANG_OUTPUT_LED_DF_REG_DT4_SET   & 0x1f);
            activated_functions[RANG_OUTPUT_LED_DF_REG_DT4_RESET >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_DT4_RESET) != 0) << (RANG_OUTPUT_LED_DF_REG_DT4_RESET & 0x1f);
            break;
          }
        default: break;
        }
      }
      
      //������� ������� (��� ��-�� � �������, �� ������ ����������� � �������� ��������)
      activated_functions[RANG_OUTPUT_LED_DF_REG_DVERI_SHAFY_UPR_VIDKR             >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_DVERI_SHAFY_UPR_VIDKR            ) != 0) << (RANG_OUTPUT_LED_DF_REG_DVERI_SHAFY_UPR_VIDKR             & 0x1f);
      activated_functions[RANG_OUTPUT_LED_DF_REG_ACUMUL_BATAREJA_ROZRJADGENA       >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_ACUMUL_BATAREJA_ROZRJADGENA      ) != 0) << (RANG_OUTPUT_LED_DF_REG_ACUMUL_BATAREJA_ROZRJADGENA       & 0x1f);
      activated_functions[RANG_OUTPUT_LED_DF_REG_REZERVTE_GYVLENNJA                >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_REZERVTE_GYVLENNJA               ) != 0) << (RANG_OUTPUT_LED_DF_REG_REZERVTE_GYVLENNJA                & 0x1f);
      activated_functions[RANG_OUTPUT_LED_DF_REG_BLOCK_VKL_VV                      >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_BLOCK_VKL_VV                     ) != 0) << (RANG_OUTPUT_LED_DF_REG_BLOCK_VKL_VV                      & 0x1f);
      activated_functions[RANG_OUTPUT_LED_DF_REG_RESET_LEDS                        >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_RESET_LEDS                       ) != 0) << (RANG_OUTPUT_LED_DF_REG_RESET_LEDS                        & 0x1f);
      activated_functions[RANG_OUTPUT_LED_DF_REG_RESET_RELES                       >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_RESET_RELES                      ) != 0) << (RANG_OUTPUT_LED_DF_REG_RESET_RELES                       & 0x1f);
      activated_functions[RANG_OUTPUT_LED_DF_REG_MISCEVE_DYSTANCIJNE               >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_MISCEVE_DYSTANCIJNE              ) != 0) << (RANG_OUTPUT_LED_DF_REG_MISCEVE_DYSTANCIJNE               & 0x1f);
      activated_functions[RANG_OUTPUT_LED_DF_REG_STATE_VV                          >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_STATE_VV                         ) != 0) << (RANG_OUTPUT_LED_DF_REG_STATE_VV                          & 0x1f);
      activated_functions[RANG_OUTPUT_LED_DF_REG_CTRL_VKL                          >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_CTRL_VKL                         ) != 0) << (RANG_OUTPUT_LED_DF_REG_CTRL_VKL                          & 0x1f);
      activated_functions[RANG_OUTPUT_LED_DF_REG_CTRL_OTKL                         >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_CTRL_OTKL                        ) != 0) << (RANG_OUTPUT_LED_DF_REG_CTRL_OTKL                         & 0x1f);
      activated_functions[RANG_OUTPUT_LED_DF_REG_RESET_BLOCK_READY_TU_VID_ZAHYSTIV >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_RESET_BLOCK_READY_TU_VID_ZAHYSTIV) != 0) << (RANG_OUTPUT_LED_DF_REG_RESET_BLOCK_READY_TU_VID_ZAHYSTIV & 0x1f);
      activated_functions[RANG_OUTPUT_LED_DF_REG_OTKL_VID_ZOVN_ZAHYSTIV            >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_OTKL_VID_ZOVN_ZAHYSTIV           ) != 0) << (RANG_OUTPUT_LED_DF_REG_OTKL_VID_ZOVN_ZAHYSTIV            & 0x1f);

      active_inputs_grupa_ustavok |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_1_GRUPA_USTAVOK    ) != 0) << (RANG_INPUT_1_GRUPA_USTAVOK - RANG_INPUT_1_GRUPA_USTAVOK);
      active_inputs_grupa_ustavok |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_2_GRUPA_USTAVOK    ) != 0) << (RANG_INPUT_2_GRUPA_USTAVOK - RANG_INPUT_1_GRUPA_USTAVOK);
      active_inputs_grupa_ustavok |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_3_GRUPA_USTAVOK    ) != 0) << (RANG_INPUT_3_GRUPA_USTAVOK - RANG_INPUT_1_GRUPA_USTAVOK);
      active_inputs_grupa_ustavok |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_4_GRUPA_USTAVOK    ) != 0) << (RANG_INPUT_4_GRUPA_USTAVOK - RANG_INPUT_1_GRUPA_USTAVOK);
      
      //������� ������� (�� ����������� � �������� ��������)
      //��������� ��
      if (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_VKL_VV ))
      {
        if (
            (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_MISCEVE_DYSTANCIJNE )) &&
            (current_settings_prt.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_BLK_ON_CB_MISCEVE)
           ) 
        {
          //����� ���������� �������� "��������� ��" �� ���.
          blocking_commands_from_DI |= CTR_EXTRA_SETTINGS_1_BLK_ON_CB_MISCEVE;
        }
        else
          activated_functions[RANG_OUTPUT_LED_DF_REG_VKL_VV >> 5] |= 1 << (RANG_OUTPUT_LED_DF_REG_VKL_VV & 0x1f);
      }
      if (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_OTKL_VV ))
      {
        if (
            (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_MISCEVE_DYSTANCIJNE )) &&
            (current_settings_prt.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_BLK_OFF_CB_MISCEVE)
           ) 
        {
          //����� ���������� �������� "��������� ��" �� ���.
          blocking_commands_from_DI |= CTR_EXTRA_SETTINGS_1_BLK_OFF_CB_MISCEVE;
        }
        else
          activated_functions[RANG_OUTPUT_LED_DF_REG_OTKL_VV >> 5] |= 1 << (RANG_OUTPUT_LED_DF_REG_OTKL_VV & 0x1f);
      }

      //���� ��� ���
      activated_functions[RANG_OUTPUT_LED_DF_REG_BLOCK_MTZ1     >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_BLOCK_MTZ1    ) != 0) << (RANG_OUTPUT_LED_DF_REG_BLOCK_MTZ1     & 0x1f);
      activated_functions[RANG_OUTPUT_LED_DF_REG_BLOCK_MTZ2     >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_BLOCK_MTZ2    ) != 0) << (RANG_OUTPUT_LED_DF_REG_BLOCK_MTZ2     & 0x1f);
      activated_functions[RANG_OUTPUT_LED_DF_REG_BLOCK_USK_MTZ2 >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_BLOCK_USK_MTZ2) != 0) << (RANG_OUTPUT_LED_DF_REG_BLOCK_USK_MTZ2 & 0x1f);
      activated_functions[RANG_OUTPUT_LED_DF_REG_BLOCK_MTZ3     >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_BLOCK_MTZ3    ) != 0) << (RANG_OUTPUT_LED_DF_REG_BLOCK_MTZ3     & 0x1f);
      activated_functions[RANG_OUTPUT_LED_DF_REG_BLOCK_MTZ4     >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_BLOCK_MTZ4    ) != 0) << (RANG_OUTPUT_LED_DF_REG_BLOCK_MTZ4     & 0x1f);

      //���� ��� ���
      activated_functions[RANG_OUTPUT_LED_DF_REG_PUSK_ZDZ_VID_DV >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_PUSK_ZDZ_VID_DV) != 0) << (RANG_OUTPUT_LED_DF_REG_PUSK_ZDZ_VID_DV & 0x1f);

      //���� ���
      activated_functions[RANG_OUTPUT_LED_DF_REG_BLOCK_NZZ >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_BLOCK_NZZ) != 0) << (RANG_OUTPUT_LED_DF_REG_BLOCK_NZZ & 0x1f);

      //���� ���
      activated_functions[RANG_OUTPUT_LED_DF_REG_STAT_BLK_APV >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_STAT_BLK_APV) != 0) << (RANG_OUTPUT_LED_DF_REG_STAT_BLK_APV & 0x1f);
      
      //���� ��� ���
      activated_functions[RANG_OUTPUT_LED_DF_REG_RESET_BLOCK_APV_ZMN >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_RESET_BLOCK_APV_ZMN) != 0) << (RANG_OUTPUT_LED_DF_REG_RESET_BLOCK_APV_ZMN & 0x1f);
      activated_functions[RANG_OUTPUT_LED_DF_REG_BLOCK_APV_ZMN       >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_BLOCK_APV_ZMN      ) != 0) << (RANG_OUTPUT_LED_DF_REG_BLOCK_APV_ZMN       & 0x1f);

      //����
      activated_functions[RANG_OUTPUT_LED_DF_REG_BLOCK_ACHR         >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_BLOCK_ACHR       ) != 0) << (RANG_OUTPUT_LED_DF_REG_BLOCK_ACHR        & 0x1f);
      activated_functions[RANG_OUTPUT_LED_DF_REG_ACHR_CHAPV_VID_DV  >> 5] |=(_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_ACHR_CHAPV_VID_DV ) != 0) << (RANG_OUTPUT_LED_DF_REG_ACHR_CHAPV_VID_DV & 0x1f);

      //���� ��� ����
      activated_functions[RANG_OUTPUT_LED_DF_REG_PUSK_UROV_VID_DV >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_PUSK_UROV_VID_DV) != 0) << (RANG_OUTPUT_LED_DF_REG_PUSK_UROV_VID_DV & 0x1f);

      //���� ���(���)
      activated_functions[RANG_OUTPUT_LED_DF_REG_BLOCK_ZOP >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_BLOCK_ZOP) != 0) << (RANG_OUTPUT_LED_DF_REG_BLOCK_ZOP & 0x1f);

      //���� ��� Umin
      activated_functions[RANG_OUTPUT_LED_DF_REG_BLOCK_UMIN1 >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_BLOCK_UMIN1) != 0) << (RANG_OUTPUT_LED_DF_REG_BLOCK_UMIN1 & 0x1f);
      activated_functions[RANG_OUTPUT_LED_DF_REG_START_UMIN1 >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_START_UMIN1) != 0) << (RANG_OUTPUT_LED_DF_REG_START_UMIN1 & 0x1f);
      activated_functions[RANG_OUTPUT_LED_DF_REG_BLOCK_UMIN2 >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_BLOCK_UMIN2) != 0) << (RANG_OUTPUT_LED_DF_REG_BLOCK_UMIN2 & 0x1f);
      activated_functions[RANG_OUTPUT_LED_DF_REG_START_UMIN2 >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_START_UMIN2) != 0) << (RANG_OUTPUT_LED_DF_REG_START_UMIN2 & 0x1f);
      
      //���� ��� Umax
      activated_functions[RANG_OUTPUT_LED_DF_REG_BLOCK_UMAX1 >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_BLOCK_UMAX1) != 0) << (RANG_OUTPUT_LED_DF_REG_BLOCK_UMAX1 & 0x1f);
      activated_functions[RANG_OUTPUT_LED_DF_REG_BLOCK_UMAX2 >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_BLOCK_UMAX2) != 0) << (RANG_OUTPUT_LED_DF_REG_BLOCK_UMAX2 & 0x1f);
      
      //���� ��� ���
      activated_functions[RANG_OUTPUT_LED_DF_REG_OTKL_AVR              >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_OTKL_AVR              ) != 0) << (RANG_OUTPUT_LED_DF_REG_OTKL_AVR              & 0x1f);
      activated_functions[RANG_OUTPUT_LED_DF_REG_SBROS_BLOCK_AVR       >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_SBROS_BLOCK_AVR       ) != 0) << (RANG_OUTPUT_LED_DF_REG_SBROS_BLOCK_AVR       & 0x1f);
      activated_functions[RANG_OUTPUT_LED_DF_REG_STAT_BLOCK_AVR        >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_STAT_BLOCK_AVR        ) != 0) << (RANG_OUTPUT_LED_DF_REG_STAT_BLOCK_AVR        & 0x1f);
    }
  }
  /**************************/

  /**************************/
  //�������� ���������� ���������� ������ ��� ��� �������, �� ����� ������������ ����� �� ���������� �������
  /**************************/
  //������� ����� �������, �� ����� ���������, �� ������ ����� � ������ �������� � "0" � "1"
  unsigned int temp_maska_filter_function[N_BIG] = {0, 0, 0, 0, 0, 0};
  unsigned int temp_activated_functions[N_BIG] = {0, 0, 0, 0, 0, 0};
  
  //������ "����� ���������"
  _SET_BIT(temp_maska_filter_function, RANG_OUTPUT_LED_DF_REG_RESET_LEDS);
  
  //������ "����� ����"
  _SET_BIT(temp_maska_filter_function, RANG_OUTPUT_LED_DF_REG_RESET_RELES);

  //������ "�������� ��"
  _SET_BIT(temp_maska_filter_function, RANG_OUTPUT_LED_DF_REG_VKL_VV);
    
  //������ "��������� ��"
  _SET_BIT(temp_maska_filter_function, RANG_OUTPUT_LED_DF_REG_OTKL_VV);

  //������ "�������� ���������� ��������� �� ��"
  _SET_BIT(temp_maska_filter_function, RANG_OUTPUT_LED_DF_REG_RESET_BLOCK_READY_TU_VID_ZAHYSTIV);
  
  //������ "������� ����� ���������� ���-���"
  _SET_BIT(temp_maska_filter_function, RANG_OUTPUT_LED_DF_REG_RESET_BLOCK_APV_ZMN);

  //������ "������� ���������� ���"
  _SET_BIT(temp_maska_filter_function, RANG_OUTPUT_LED_DF_REG_OTKL_AVR);
  //������ "������� ����� ���������� ���"
  _SET_BIT(temp_maska_filter_function, RANG_OUTPUT_LED_DF_REG_SBROS_BLOCK_AVR);
  
  //� ������ ��������� ����� �������� ����� � �������, ��� ��� �������� ����� ��� � ������� �� � ���������� �����
  temp_activated_functions[0] = previous_activated_functions[0] & temp_maska_filter_function[0];
  temp_activated_functions[1] = previous_activated_functions[1] & temp_maska_filter_function[1];
  temp_activated_functions[2] = previous_activated_functions[2] & temp_maska_filter_function[2];
  temp_activated_functions[3] = previous_activated_functions[3] & temp_maska_filter_function[3];
  temp_activated_functions[4] = previous_activated_functions[4] & temp_maska_filter_function[4];
  temp_activated_functions[5] = previous_activated_functions[5] & temp_maska_filter_function[5];
  
  //� ����������� ����� �������� ����� � �������, � ���� ����������� ��� �������, ��� ����� ������
  temp_activated_functions[0] ^= (activated_functions[0] & temp_maska_filter_function[0]);
  temp_activated_functions[1] ^= (activated_functions[1] & temp_maska_filter_function[1]);
  temp_activated_functions[2] ^= (activated_functions[2] & temp_maska_filter_function[2]);
  temp_activated_functions[3] ^= (activated_functions[3] & temp_maska_filter_function[3]);
  temp_activated_functions[4] ^= (activated_functions[4] & temp_maska_filter_function[4]);
  temp_activated_functions[5] ^= (activated_functions[5] & temp_maska_filter_function[5]);
  
  //����� �������� � ����������� ����� ����� � ������� � ���� ����� �������� ������ ��� "1" (����� ������� ������� � "0" � "1")
  temp_activated_functions[0] &= activated_functions[0];
  temp_activated_functions[1] &= activated_functions[1];
  temp_activated_functions[2] &= activated_functions[2];
  temp_activated_functions[3] &= activated_functions[3];
  temp_activated_functions[4] &= activated_functions[4];
  temp_activated_functions[5] &= activated_functions[5];
  
  /*
  ����� ���, �� ������� � �������, �� � ����� ���� ������ ������ �� ������ 
  � ����������� ����, �� ���� ������� ����������� �� ���������� �����
  ������� ��������� ���� ������� (��� ���������� ������) � ���������� �����
  ��� ��� ���������� ����� ���� ��������� ��������� ���� �������� �������
  */ 
  previous_activated_functions[0] = activated_functions[0];
  previous_activated_functions[1] = activated_functions[1];
  previous_activated_functions[2] = activated_functions[2];
  previous_activated_functions[3] = activated_functions[3];
  previous_activated_functions[4] = activated_functions[4];
  previous_activated_functions[5] = activated_functions[5];

  //���������� ����� �������, �� ����� ����������� � ����������� ����, �� ����� �������� ������� ������ ��������� ����� ���� ����� �, � ���� ������� ��� � "0" � "1"
  activated_functions[0] = (activated_functions[0] & (~temp_maska_filter_function[0])) | temp_activated_functions[0];
  activated_functions[1] = (activated_functions[1] & (~temp_maska_filter_function[1])) | temp_activated_functions[1];
  activated_functions[2] = (activated_functions[2] & (~temp_maska_filter_function[2])) | temp_activated_functions[2];
  activated_functions[3] = (activated_functions[3] & (~temp_maska_filter_function[3])) | temp_activated_functions[3];
  activated_functions[4] = (activated_functions[4] & (~temp_maska_filter_function[4])) | temp_activated_functions[4];
  activated_functions[5] = (activated_functions[5] & (~temp_maska_filter_function[5])) | temp_activated_functions[5];
  /**************************/
  
  /**************************/
  //���� ����� �������
  /**************************/
  if (count_number_set_bit(&active_inputs_grupa_ustavok, NUMBER_GROUP_USTAVOK) > 1)
    _SET_BIT(set_diagnostyka, ERROR_SELECT_GRUPY_USRAVOK);
  else
    _SET_BIT(clear_diagnostyka, ERROR_SELECT_GRUPY_USRAVOK);
    
  if (
      (( _CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_WORK_BO   ) ) !=0 ) ||
      (( _CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_WORK_BV   ) ) !=0 ) ||
      (( _CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_PO_MTZ1   ) ) !=0 ) ||
      (( _CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_MTZ1      ) ) !=0 ) ||
      (( _CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_PO_MTZ2   ) ) !=0 ) ||
      (( _CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_MTZ2      ) ) !=0 ) ||
      (( _CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_PO_MTZ3   ) ) !=0 ) ||
      (( _CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_MTZ3      ) ) !=0 ) ||
      (( _CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_PO_MTZ4   ) ) !=0 ) ||
      (( _CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_MTZ4      ) ) !=0 ) ||
      (( _CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_PO_UMAX1  ) ) !=0 ) ||
      (( _CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_UMAX1     ) ) !=0 ) ||
      (( _CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_PO_UMAX2  ) ) !=0 ) ||
      (( _CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_UMAX2     ) ) !=0 ) ||
      (( _CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_PO_UMIN1  ) ) !=0 ) ||
      (( _CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_UMIN1     ) ) !=0 ) ||
      (( _CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_PO_UMIN2  ) ) !=0 ) ||
      (( _CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_UMIN2     ) ) !=0 ) ||
      (( _CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_PO_ZOP    ) ) !=0 ) ||
      (( _CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_ZOP       ) ) !=0 ) ||
      (( _CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_PO_F1_ACHR) ) !=0 ) ||
      (( _CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_PO_F2_ACHR) ) !=0 ) ||
      (( _CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_ACHR_CHAPV) ) !=0 ) ||
      (( _CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_PO_APV_ZMN) ) !=0 ) ||
      (( _CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_APV_ZMN   ) ) !=0 ) ||
      (( _CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_PUSK_AVR  ) ) !=0 ) ||
      (( _CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_APV_WORK  ) ) !=0 ) ||
      (( _CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_PO_UROV   ) ) !=0 ) ||
      (( _CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_UROV1     ) ) !=0 ) ||
      (( _CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_UROV2     ) ) !=0 ) ||
      (( _CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_PO_NZZ    ) ) !=0 ) ||
      (( _CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_NZZ       ) ) !=0 ) ||
      (( _CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_PO_3I0    ) ) !=0 ) ||
      (( _CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_3I0       ) ) !=0 ) ||
      (( _CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_PO_3U0    ) ) !=0 ) ||
      (( _CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_3U0       ) ) !=0 )
     ) 
  {
    //��� ���������� ���� ������� - ����� ������� ���������� ���, ��� ������� ����������
    _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_BLK_GRUP_USTAVOK_VID_ZACHYSTIV);

    unsigned int number_group_stp_tmp = 0;
    if(( _CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_1_GRUPA_USTAVOK) ) !=0 )
    {
      _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_1_GRUPA_USTAVOK);
      number_group_stp_tmp++;
    }

    if(( _CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_2_GRUPA_USTAVOK) ) !=0 )
    {
      _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_2_GRUPA_USTAVOK);
      number_group_stp_tmp++;
    }

    if(( _CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_3_GRUPA_USTAVOK) ) !=0 )
    {
      _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_3_GRUPA_USTAVOK);
      number_group_stp_tmp++;
    }

    if(( _CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_4_GRUPA_USTAVOK) ) !=0 )
    {
      _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_4_GRUPA_USTAVOK);
      number_group_stp_tmp++;
    }
    
    if (number_group_stp_tmp != 1)
    {
      //���������� ����� ����� �� ���� � ����
      total_error_sw_fixed(52);
    }
  }
  else
  {
    //����� �������� ����� ������� - ������� �� �������� �� ��������
    setpoints_selecting(activated_functions, active_inputs_grupa_ustavok);
  }

  unsigned int number_group_stp;
  if     (( _CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_1_GRUPA_USTAVOK) ) !=0 ) number_group_stp = 0;
  else if(( _CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_2_GRUPA_USTAVOK) ) !=0 ) number_group_stp = 1;
  else if(( _CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_3_GRUPA_USTAVOK) ) !=0 ) number_group_stp = 2;
  else if(( _CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_4_GRUPA_USTAVOK) ) !=0 ) number_group_stp = 3;
  else
  {
    //���������� ����� ����� �� ���� � ����
    total_error_sw_fixed(51);
  }
  /**************************/

  /***********************************************************/
  //���������� ���������
  /***********************************************************/
  calc_measurement(number_group_stp);

#ifdef DEBUG_TEST
  /***/
  //ҳ���� ��� �������
  /***/
  if (temp_value_3I0_1 != 0)
    measurement[IM_3I0]         = temp_value_3I0_1;
  if (temp_value_3I0_other != 0)
    measurement[IM_3I0_other_g] = temp_value_3I0_other;
  if (temp_value_IA != 0)
    measurement[IM_IA]          = temp_value_IA;
  if (temp_value_IC != 0)
    measurement[IM_IC]          = temp_value_IC;
  if (temp_value_UA != 0)
    measurement[IM_UA]          = temp_value_UA;
  if (temp_value_UB != 0)
    measurement[IM_UB]          = temp_value_UB;
  if (temp_value_UC != 0)
    measurement[IM_UC]          = temp_value_UC;
  if (temp_value_3U0_UBC_TN2 != 0)
    measurement[IM_3U0_UBC_TN2] = temp_value_3U0_UBC_TN2;
  if (temp_value_UAB_TN2 != 0)
    measurement[IM_UAB_TN2]     = temp_value_UAB_TN2;
  if (temp_value_I2 != 0)
    measurement[IM_I2]          = temp_value_I2;
  if (temp_value_I1 != 0)
    measurement[IM_I1]          = temp_value_I1;
  /***/
#endif
    
      
  //ĳ��������� ��������� ��� �� �����
  diagnostyca_adc_execution();
  
  //������� ���������� ��� ����������������� � ����������������� �������
  unsigned int bank_measurement_high_tmp = (bank_measurement_high ^ 0x1) & 0x1;
  if(semaphore_measure_values_low1 == 0)
  {
    for (unsigned int i = 0; i < (NUMBER_ANALOG_CANALES + 8); i++) 
    {
      measurement_high[bank_measurement_high_tmp][i] = measurement_middle[i] = measurement[i];
    }
    for (unsigned int i = 0; i < MAX_NUMBER_INDEXES_RESISTANCE; i++) resistance_middle[i] = resistance[i];
  }
  else
  {
    for (unsigned int i = 0; i < (NUMBER_ANALOG_CANALES + 8); i++) 
    {
      measurement_high[bank_measurement_high_tmp][i] = measurement[i];
    }
  }
  bank_measurement_high = bank_measurement_high_tmp;
  /***********************************************************/
  
  
  /**************************/
  //������ "������������ �����"
  /**************************/
  unsigned int diagnostyka_tmp[3];
  diagnostyka_tmp[0] = diagnostyka[0];
  diagnostyka_tmp[1] = diagnostyka[1];
  diagnostyka_tmp[2] = diagnostyka[2];

  diagnostyka_tmp[0] &= (unsigned int)(~clear_diagnostyka[0]); 
  diagnostyka_tmp[0] |= set_diagnostyka[0]; 

  diagnostyka_tmp[1] &= (unsigned int)(~clear_diagnostyka[1]); 
  diagnostyka_tmp[1] |= set_diagnostyka[1]; 

  diagnostyka_tmp[2] &= (unsigned int)(~clear_diagnostyka[2]); 
  diagnostyka_tmp[2] |= set_diagnostyka[2]; 
  
  diagnostyka_tmp[2] &= USED_BITS_IN_LAST_INDEX; 

  _CLEAR_BIT(diagnostyka_tmp, EVENT_START_SYSTEM_BIT);
  _CLEAR_BIT(diagnostyka_tmp, EVENT_DROP_POWER_BIT);
  if (
      (diagnostyka_tmp[0] != 0) ||
      (diagnostyka_tmp[1] != 0) ||
      (diagnostyka_tmp[2] != 0)
     )   
  {
    _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_DEFECT);
    /**************************/
    //������ "������������ ���������"
    /**************************/
    if (
        ((diagnostyka_tmp[0] & MASKA_AVAR_ERROR_0) != 0) ||
        ((diagnostyka_tmp[1] & MASKA_AVAR_ERROR_1) != 0) ||
        ((diagnostyka_tmp[2] & MASKA_AVAR_ERROR_2) != 0)
      )   
    {
      _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_AVAR_DEFECT);
    }
    else
    {     
      _CLEAR_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_AVAR_DEFECT);
    }
    /**************************/
  }
  else
  {
    _CLEAR_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_DEFECT);
    _CLEAR_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_AVAR_DEFECT);
  }
  /**************************/

  
  //����� ����� ����� ��������� ����� � ���� �������, ���� ��� ������� "��������� �������������"
  if (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_AVAR_DEFECT) == 0)
  {
    //������� �������� �� �����������
    
    /**************************/
    //�������� ������� ��
    /**************************/
    control_VV(activated_functions);
    /**************************/

    /**************************/
    //���
    /**************************/
    if ((current_settings_prt.configuration & (1 << MTZ_BIT_CONFIGURATION)) != 0)
    {
      mtz_handler(activated_functions, number_group_stp);
    }
    else
    {
      global_timers[INDEX_TIMER_MTZ1] = -1;
      global_timers[INDEX_TIMER_MTZ1_N_VPERED] = -1;
      global_timers[INDEX_TIMER_MTZ1_N_NAZAD] = -1;
      global_timers[INDEX_TIMER_MTZ1_PO_NAPRUZI] = -1;
      global_timers[INDEX_TIMER_MTZ2] = -1;
      global_timers[INDEX_TIMER_MTZ2_DEPENDENT] = -1;
      global_timers[INDEX_TIMER_MTZ2_PR] = -1;
      global_timers[INDEX_TIMER_MTZ2_N_VPERED] = -1;
      global_timers[INDEX_TIMER_MTZ2_N_VPERED_PR] = -1;
      global_timers[INDEX_TIMER_MTZ2_N_NAZAD] = -1;
      global_timers[INDEX_TIMER_MTZ2_N_NAZAD_PR] = -1;
      global_timers[INDEX_TIMER_MTZ2_PO_NAPRUZI] = -1;
      global_timers[INDEX_TIMER_MTZ2_PO_NAPRUZI_PR] = -1;
      global_timers[INDEX_TIMER_MTZ2_VVID_PR] = -1;
      global_timers[INDEX_TIMER_MTZ3] = -1;
      global_timers[INDEX_TIMER_MTZ3_N_VPERED] = -1;
      global_timers[INDEX_TIMER_MTZ3_N_NAZAD] = -1;
      global_timers[INDEX_TIMER_MTZ3_PO_NAPRUZI] = -1;
      global_timers[INDEX_TIMER_MTZ4] = -1;
      global_timers[INDEX_TIMER_MTZ4_N_VPERED] = -1;
      global_timers[INDEX_TIMER_MTZ4_N_NAZAD] = -1;
      global_timers[INDEX_TIMER_MTZ4_PO_NAPRUZI] = -1;
    }
    /**************************/
    
    /**************************/
    //���
    /**************************/
    if ((current_settings_prt.configuration & (1 << ZDZ_BIT_CONFIGURATION)) != 0)
    {
      zdz_handler(activated_functions);
    }
    /**************************/

    /**************************/
    //��
    /**************************/
    if ((current_settings_prt.configuration & (1 << ZZ_BIT_CONFIGURATION)) != 0)
    {
      zz_handler(activated_functions, number_group_stp);
    }
    else
    {
      global_timers[INDEX_TIMER_ZZ_3I0] = -1;
      global_timers[INDEX_TIMER_ZZ_3U0] = -1;
      global_timers[INDEX_TIMER_NZZ] = -1;
    }
    /**************************/
  
    /**************************/
    //���(���)
    /**************************/
    if ((current_settings_prt.configuration & (1 << ZOP_BIT_CONFIGURATION)) != 0)
    {
      zop_handler(activated_functions, number_group_stp);
    }
    else
    {
      global_timers[INDEX_TIMER_ZOP] = -1;
    }
    /**************************/
    
    if ((current_settings_prt.configuration & (1 << UMIN_BIT_CONFIGURATION)) > 0) {
      /**************************/
      //�����1
      /**************************/
      umin1_handler(activated_functions, number_group_stp);
      /**************************/
      
      /**************************/
      //�����2
      /**************************/
      umin2_handler(activated_functions, number_group_stp);
      /**************************/
    } else {
      global_timers[INDEX_TIMER_UMIN1] = -1;
      global_timers[INDEX_TIMER_UMIN2] = -1;
    }
    
    if ((current_settings_prt.configuration & (1 << UMAX_BIT_CONFIGURATION)) > 0) {
      /**************************/
      //������1
      /**************************/
      umax1_handler(activated_functions, number_group_stp);
      /**************************/
      
      /**************************/
      //������2
      /**************************/
      umax2_handler(activated_functions, number_group_stp);
      /**************************/
    } else {
      global_timers[INDEX_TIMER_UMAX1] = -1;
      global_timers[INDEX_TIMER_UMAX2] = -1;
    }
    
    if ((current_settings_prt.configuration & (1 << AVR_BIT_CONFIGURATION)) > 0) {
      /**************************/
      //���
      /**************************/
      avr_handler(activated_functions, number_group_stp);
      /**************************/
    } else {
      global_timers[INDEX_TIMER_AVR_ZAVERSHENNJA] = -1;
      global_timers[INDEX_TIMER_AVR_RESET_BLK] = -1;
      global_timers[INDEX_TIMER_AVR_RL] = -1;
      global_timers[INDEX_TIMER_AVR_OL] = -1;
      previous_states_AVR_0 = 0;
      previous_states_AVR_1 = 0;
      previous_state_avr_counter = 0;
      trigger_AVR_0 = 0;
      trigger_AVR_1 = 0;
      avr_counter = 0;
    }
    
    if ((current_settings_prt.configuration & (1 << APV_ZMN_BIT_CONFIGURATION)) > 0) {
      /**************************/
      //��� ���
      /**************************/
      apv_zmn_handler(activated_functions, number_group_stp);
      /**************************/
    } else {
      global_timers[INDEX_TIMER_APV_ZMN1] = -1;
      global_timers[INDEX_TIMER_APV_ZMN2] = -1;
      global_timers[INDEX_TIMER_APV_ZMN3] = -1;
      previous_states_APV_ZMN_0 = 0;
      previous_states_APV_ZMN_1 = 0;
      previous_states_APV_ZMN_2 = 0;
      previous_state_apv_zmn_counter = 0;
      trigger_APV_ZMN_0 = 0;
      trigger_APV_ZMN_1 = 0;
      trigger_APV_ZMN_2 = 0;
      apv_zmn_counter = 0;
    }
    
    if ((current_settings_prt.configuration & (1 << ACHR_CHAPV_BIT_CONFIGURATION)) > 0) {
      /**************************/
      //��� ����
      /**************************/
      achr_chapv_handler(activated_functions, number_group_stp);
      /**************************/
    } else {
      global_timers[INDEX_TIMER_ACHR_CHAPV_100MS_1] = -1;
      global_timers[INDEX_TIMER_ACHR_CHAPV_100MS_2] = -1;
      global_timers[INDEX_TIMER_ACHR1] = -1;
      global_timers[INDEX_TIMER_ACHR2] = -1;
      global_timers[INDEX_TIMER_CHAPV1] = -1;
      global_timers[INDEX_TIMER_CHAPV2] = -1;
      global_timers[INDEX_TIMER_ACHR_CHAPV_100MS_1] = -1;
      global_timers[INDEX_TIMER_ACHR_CHAPV_100MS_2] = -1;
      global_timers[INDEX_TIMER_CHAPV_1MS] = -1;
      global_timers[INDEX_TIMER_BLOCK_CHAPV_5MS] = -1;
      previous_state_po_achr_chapv_uaf1 = 0;
      previous_state_po_achr_chapv_ubf1 = 0;
      previous_state_po_achr_chapv_ucf1 = 0;
      previous_state_po_achr_chapv_uaf2_uab2_ubc2 = 0;
      previous_states_CHAPV1 = 0;
      previous_states_CHAPV2 = 0;
      trigger_CHAPV1 = 0;
      trigger_CHAPV2 = 0;
    }
    
    if ((current_settings_prt.configuration & (1 << CONTROL_U_BIT_CONFIGURATION)) > 0) {
      /**************************/
      //�������� ���������� �������� �����
      /**************************/
      control_U_OL(activated_functions, number_group_stp);
      /**************************/
      
      /**************************/
      //�������� ���������� ��������� �����
      /**************************/
      control_U_RL(activated_functions, number_group_stp);
      /**************************/
    } else {
      global_timers[INDEX_TIMER_U_OL1] = -1;
      global_timers[INDEX_TIMER_U_OL2] = -1;
      global_timers[INDEX_TIMER_U_RL1] = -1;
      global_timers[INDEX_TIMER_U_RL2] = -1;
      trigger_u_ol = 0;
      trigger_u_rl = 0;
    }
    
    /**************************/
    //����
    /**************************/
    if ((current_settings_prt.configuration & (1 << UROV_BIT_CONFIGURATION)) != 0)
    {
      urov_handler(activated_functions, number_group_stp);
    }
    else
    {
      global_timers[INDEX_TIMER_UROV1] = -1;
      global_timers[INDEX_TIMER_UROV2] = -1;
    }
    /**************************/

    /**************************/
    //���
    /**************************/
    if ((current_settings_prt.configuration & (1 << APV_BIT_CONFIGURATION)) != 0)
    {
      apv_handler(activated_functions, number_group_stp);
    }
    else
    {
      global_timers[INDEX_TIMER_APV_1] = -1;
      global_timers[INDEX_TIMER_APV_2] = -1;
      global_timers[INDEX_TIMER_APV_3] = -1;
      global_timers[INDEX_TIMER_APV_4] = -1;
      global_timers[INDEX_TIMER_APV_BLOCK_VID_APV1] = -1;
      global_timers[INDEX_TIMER_APV_BLOCK_VID_APV2] = -1;
      global_timers[INDEX_TIMER_APV_BLOCK_VID_APV3] = -1;
      global_timers[INDEX_TIMER_APV_BLOCK_VID_APV4] = -1;
      global_timers[INDEX_TIMER_APV_BLOCK_VID_VV] = -1;
      global_timers[INDEX_TIMER_APV_TMP1] = -1;

      previous_states_APV_0 = 0;
      trigger_APV_0 = 0;
    }
    /**************************/
    
    unsigned int previous_stats_signals[N_BIG];

    /**************************/
    //���������� ������������ �������
    /**************************/
    previous_stats_signals[0] = active_functions[0] & (MASKA_FOR_DF_TRIGGERS_SIGNALS_0 | MASKA_FOR_ON_OFF_SIGNALS_0 | MASKA_FOR_READY_TU_SIGNALS_0 | MASKA_FOR_RESURS_VV_SIGNALS_0 | MASKA_FOR_REJESTRATORS_AND_DEFECT_SIGNALS_0);
    previous_stats_signals[1] = active_functions[1] & (MASKA_FOR_DF_TRIGGERS_SIGNALS_1 | MASKA_FOR_ON_OFF_SIGNALS_1 | MASKA_FOR_READY_TU_SIGNALS_1 | MASKA_FOR_RESURS_VV_SIGNALS_1 | MASKA_FOR_REJESTRATORS_AND_DEFECT_SIGNALS_1);
    previous_stats_signals[2] = active_functions[2] & (MASKA_FOR_DF_TRIGGERS_SIGNALS_2 | MASKA_FOR_ON_OFF_SIGNALS_2 | MASKA_FOR_READY_TU_SIGNALS_2 | MASKA_FOR_RESURS_VV_SIGNALS_2 | MASKA_FOR_REJESTRATORS_AND_DEFECT_SIGNALS_2);
    previous_stats_signals[3] = active_functions[3] & (MASKA_FOR_DF_TRIGGERS_SIGNALS_3 | MASKA_FOR_ON_OFF_SIGNALS_3 | MASKA_FOR_READY_TU_SIGNALS_3 | MASKA_FOR_RESURS_VV_SIGNALS_3 | MASKA_FOR_REJESTRATORS_AND_DEFECT_SIGNALS_3);
    previous_stats_signals[4] = active_functions[4] & (MASKA_FOR_DF_TRIGGERS_SIGNALS_4 | MASKA_FOR_ON_OFF_SIGNALS_4 | MASKA_FOR_READY_TU_SIGNALS_4 | MASKA_FOR_RESURS_VV_SIGNALS_4 | MASKA_FOR_REJESTRATORS_AND_DEFECT_SIGNALS_4);
    previous_stats_signals[5] = active_functions[5] & (MASKA_FOR_DF_TRIGGERS_SIGNALS_5 | MASKA_FOR_ON_OFF_SIGNALS_5 | MASKA_FOR_READY_TU_SIGNALS_5 | MASKA_FOR_RESURS_VV_SIGNALS_5 | MASKA_FOR_REJESTRATORS_AND_DEFECT_SIGNALS_5);
    df_handler(activated_functions, previous_stats_signals);
    /**************************/

    /**************************/
    //���������� ������������ ������
    /**************************/
    previous_stats_signals[0] = active_functions[0] & (MASKA_FOR_ON_OFF_SIGNALS_0 | MASKA_FOR_READY_TU_SIGNALS_0 | MASKA_FOR_RESURS_VV_SIGNALS_0 | MASKA_FOR_REJESTRATORS_AND_DEFECT_SIGNALS_0);
    previous_stats_signals[1] = active_functions[1] & (MASKA_FOR_ON_OFF_SIGNALS_1 | MASKA_FOR_READY_TU_SIGNALS_1 | MASKA_FOR_RESURS_VV_SIGNALS_1 | MASKA_FOR_REJESTRATORS_AND_DEFECT_SIGNALS_1);
    previous_stats_signals[2] = active_functions[2] & (MASKA_FOR_ON_OFF_SIGNALS_2 | MASKA_FOR_READY_TU_SIGNALS_2 | MASKA_FOR_RESURS_VV_SIGNALS_2 | MASKA_FOR_REJESTRATORS_AND_DEFECT_SIGNALS_2);
    previous_stats_signals[3] = active_functions[3] & (MASKA_FOR_ON_OFF_SIGNALS_3 | MASKA_FOR_READY_TU_SIGNALS_3 | MASKA_FOR_RESURS_VV_SIGNALS_3 | MASKA_FOR_REJESTRATORS_AND_DEFECT_SIGNALS_3);
    previous_stats_signals[4] = active_functions[4] & (MASKA_FOR_ON_OFF_SIGNALS_4 | MASKA_FOR_READY_TU_SIGNALS_4 | MASKA_FOR_RESURS_VV_SIGNALS_4 | MASKA_FOR_REJESTRATORS_AND_DEFECT_SIGNALS_4);
    previous_stats_signals[5] = active_functions[5] & (MASKA_FOR_ON_OFF_SIGNALS_5 | MASKA_FOR_READY_TU_SIGNALS_5 | MASKA_FOR_RESURS_VV_SIGNALS_5 | MASKA_FOR_REJESTRATORS_AND_DEFECT_SIGNALS_5);
    dt_handler(activated_functions, previous_stats_signals);
    /**************************/

    /**************************/
    //���������-³���������
    /**************************/
    previous_stats_signals[0] = active_functions[0] & (MASKA_FOR_READY_TU_SIGNALS_0 | MASKA_FOR_RESURS_VV_SIGNALS_0 | MASKA_FOR_REJESTRATORS_AND_DEFECT_SIGNALS_0);
    previous_stats_signals[1] = active_functions[1] & (MASKA_FOR_READY_TU_SIGNALS_1 | MASKA_FOR_RESURS_VV_SIGNALS_1 | MASKA_FOR_REJESTRATORS_AND_DEFECT_SIGNALS_1);
    previous_stats_signals[2] = active_functions[2] & (MASKA_FOR_READY_TU_SIGNALS_2 | MASKA_FOR_RESURS_VV_SIGNALS_2 | MASKA_FOR_REJESTRATORS_AND_DEFECT_SIGNALS_2);
    previous_stats_signals[3] = active_functions[3] & (MASKA_FOR_READY_TU_SIGNALS_3 | MASKA_FOR_RESURS_VV_SIGNALS_3 | MASKA_FOR_REJESTRATORS_AND_DEFECT_SIGNALS_3);
    previous_stats_signals[4] = active_functions[4] & (MASKA_FOR_READY_TU_SIGNALS_4 | MASKA_FOR_RESURS_VV_SIGNALS_4 | MASKA_FOR_REJESTRATORS_AND_DEFECT_SIGNALS_4);
    previous_stats_signals[5] = active_functions[5] & (MASKA_FOR_READY_TU_SIGNALS_5 | MASKA_FOR_RESURS_VV_SIGNALS_5 | MASKA_FOR_REJESTRATORS_AND_DEFECT_SIGNALS_5);
    on_off_handler(activated_functions, previous_stats_signals);
    /**************************/
    
    /**************************/
    //��� (������ ����� ����� ����� ���������)
    /**************************/
    vmp_handler(activated_functions);
    /**************************/

    /**************************/
    //���������� � ��
    /**************************/
    ready_tu(activated_functions);
    /**************************/

    /**************************/
    //������ �������� (������ ����� ����� ����� ���������)
    /**************************/
    resurs_vymykacha_handler(activated_functions, (unsigned int *)active_functions);
    /**************************/
  }
  else
  {
    //������� �������� �����������
    
    //������� �� ������ �������, ��� �������������
    activated_functions[0] &= MASKA_INFO_SIGNALES_0;
    activated_functions[1] &= MASKA_INFO_SIGNALES_1;
    activated_functions[2] &= MASKA_INFO_SIGNALES_2;
    activated_functions[3] &= MASKA_INFO_SIGNALES_3;
    activated_functions[4] &= MASKA_INFO_SIGNALES_4;
    activated_functions[5] &= MASKA_INFO_SIGNALES_5;
    
    //������������ �� ����
    state_outputs = 0;
    
    //���������� � ���������� ���� ���� �������� ����
    previous_states_APV_0 = 0;
    trigger_APV_0 = 0;
    previous_states_APV_ZMN_0 = 0;
    previous_states_APV_ZMN_1 = 0;
    previous_states_APV_ZMN_2 = 0;
    apv_zmn_counter = 0;
    previous_state_apv_zmn_counter = 0;
    trigger_APV_ZMN_0 = 0;
    trigger_APV_ZMN_1 = 0;
    trigger_APV_ZMN_2 = 0;
    previous_states_AVR_0 = 0;
    previous_states_AVR_1 = 0;
    previous_state_avr_counter = 0;
    trigger_AVR_0 = 0;
    trigger_AVR_1 = 0;
    avr_counter = 0;
    previous_state_po_achr_chapv_uaf1 = 0;
    previous_state_po_achr_chapv_ubf1 = 0;
    previous_state_po_achr_chapv_ucf1 = 0;
    previous_state_po_achr_chapv_uaf2_uab2_ubc2 = 0;
    previous_states_CHAPV1 = 0;
    previous_states_CHAPV2 = 0;
    trigger_CHAPV1 = 0;
    trigger_CHAPV2 = 0;
    previous_states_ready_tu = 0;
    trigger_ready_tu = 0;
    trigger_u_ol = 0;
    trigger_u_rl = 0;
    
    //������� �� �������, �� ������� � �����
    for(unsigned int i = INDEX_TIMER_DF_PROLONG_SET_FOR_BUTTON_INTERFACE_START; i < MAX_NUMBER_GLOBAL_TIMERS; i++)
      global_timers[i] = -1;
    
    //���� ��� �� ���������� � ��������
    state_df = 0;
    
    //���� ��������� �� ���������� � ����������
    for(unsigned int i = 0; i < NUMBER_DEFINED_FUNCTIONS; i++)
    {
      etap_execution_df[i] = NONE_DF;
    }
  }

  /**************************/
  //ϳ�������� �� ������ ����������
  /**************************/
  //������� � ������ ������ ������� ��������� ���� ������� "������ ��.���."
  activated_functions[RANG_OUTPUT_LED_DF_REG_WORK_A_REJESTRATOR >> 5] |= active_functions[RANG_OUTPUT_LED_DF_REG_WORK_A_REJESTRATOR >> 5] & (unsigned int)(1 << (RANG_OUTPUT_LED_DF_REG_WORK_A_REJESTRATOR & 0x1f));
  
  //������� � ������ ������ ������� ��������� ���� ������� "������ �.���." ��� �� ��������� ��� ����� ������� ����������� ���������� �������� ������� ����� ������� � "1" � "0"/
  activated_functions[RANG_OUTPUT_LED_DF_REG_WORK_D_REJESTRATOR >> 5] |= active_functions[RANG_OUTPUT_LED_DF_REG_WORK_D_REJESTRATOR >> 5] & (unsigned int)(1 << (RANG_OUTPUT_LED_DF_REG_WORK_D_REJESTRATOR & 0x1f));
  /**************************/

  /**************************/
  //������� ����������� ����������
  /**************************/
  analog_registrator(activated_functions);
  /**************************/

  /**************************/
  //������� ����������� ����������
  /**************************/
  digital_registrator(activated_functions, active_functions, number_group_stp);
  /**************************/

  /**************************/
  //������ � ���������, �� ����� ������������ � ��������������� ���'���
  /**************************/
  unsigned int comparison_true = true;
  for (unsigned int i = 0; i < N_BIG; i++)
  {
    unsigned int tmp_data;
    if (trigger_active_functions[i] != (tmp_data = (activated_functions[i] & maska_trg_func_array[i])))
    {
      comparison_true = false;
      trigger_active_functions[i] = tmp_data;
    }
  }
  if (comparison_true != true)
  {
    /*
    �������, �������� ���� ���������� � ��������������� ���'1��� ��������.
    ������ ������� �� �� ����� � ��������������� ���'���
    */
    _SET_BIT(control_eeprom_taskes, TASK_START_WRITE_TRG_FUNC_EEPROM_BIT);
  }
  /**************************/

  /**************************/
  //����������� ��������� � ������ �������� � ��������� �������
  /**************************/
  copying_active_functions = 1; //�������, �� ����� ���������� �������� �������� �������
  
  active_functions[0] = activated_functions[0];
  trigger_functions_USB[0]   |= activated_functions[0];
  trigger_functions_RS485[0] |= activated_functions[0];

  active_functions[1] = activated_functions[1];
  trigger_functions_USB[1]   |= activated_functions[1];
  trigger_functions_RS485[1] |= activated_functions[1];

  active_functions[2] = activated_functions[2];
  trigger_functions_USB[2]   |= activated_functions[2];
  trigger_functions_RS485[2] |= activated_functions[2];

  active_functions[3] = activated_functions[3];
  trigger_functions_USB[3]   |= activated_functions[3];
  trigger_functions_RS485[3] |= activated_functions[3];

  active_functions[4] = activated_functions[4];
  trigger_functions_USB[4]   |= activated_functions[4];
  trigger_functions_RS485[4] |= activated_functions[4];

  active_functions[5] = activated_functions[5];
  trigger_functions_USB[5]   |= activated_functions[5];
  trigger_functions_RS485[5] |= activated_functions[5];

  copying_active_functions = 0; //�������, �� ���������� �������� �������� ������� ���������
  
  /*
  ������ ���� �������� �������� ������� ��� ����, ��� ���� �� ������� ������
  �����������, �� ����� ���� � ����� �������  (��� �� � ��'������� ����������
  ���������) ����� ��������, ��� ��������� ��������
  */
  active_functions_copy[0] = active_functions[0];
  active_functions_copy[1] = active_functions[1];
  active_functions_copy[2] = active_functions[2];
  active_functions_copy[3] = active_functions[3];
  active_functions_copy[4] = active_functions[4];
  active_functions_copy[5] = active_functions[5];
  /**************************/

  /**************************/
  //���� ���������� �� ������
  /**************************/
  //�������� ����������, �� �� �������������� ������� "����� ����" - � ���� ���, �� ���������� ������� �� ����
  if (_CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_RESET_RELES) !=0)
  {
    state_outputs = 0;
  }
  
  if (_CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_AVAR_DEFECT) == 0)
  {
    //�� ����������� ������� ��������, ���� ������������� ���� �����
    
    //���������, �� ���� ����� ����� ���� ����������
    for (unsigned int i = 0; i < NUMBER_OUTPUTS; i++)
    {
      //� ���������� ����� ������� ��ò��� � ���������� ������, ���� ����������� ��������� "i" � �������, �� ����� � ���������
      unsigned int temp_array_of_outputs[N_BIG];
    
      temp_array_of_outputs[0] = current_settings_prt.ranguvannja_outputs[N_BIG*i    ] & active_functions[0];
      temp_array_of_outputs[1] = current_settings_prt.ranguvannja_outputs[N_BIG*i + 1] & active_functions[1];
      temp_array_of_outputs[2] = current_settings_prt.ranguvannja_outputs[N_BIG*i + 2] & active_functions[2];
      temp_array_of_outputs[3] = current_settings_prt.ranguvannja_outputs[N_BIG*i + 3] & active_functions[3];
      temp_array_of_outputs[4] = current_settings_prt.ranguvannja_outputs[N_BIG*i + 4] & active_functions[4];
      temp_array_of_outputs[5] = current_settings_prt.ranguvannja_outputs[N_BIG*i + 5] & active_functions[5];

      //������ "������� �����������" ������ � ���������� �����: ������ ���� �� ����� ���������� � �������, ���� ����� ������ �� ��������
      if(_CHECK_SET_BIT((current_settings_prt.ranguvannja_outputs + N_BIG*i), RANG_OUTPUT_LED_DF_REG_AVAR_DEFECT) !=0)
      {
        //������ "A�������� �������������"  ������ ���������� �� ����� �����
        if (_CHECK_SET_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_AVAR_DEFECT) == 0)
        {
          //������ "A�������� �������������" �� � ��������
          //���������� ������������ ���� � �������� ���� � �����, ���� �  ��ò���� � ��������� ������, ���� ����������� ��������� "i" � �������, �� ����� � ���������
          _SET_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_AVAR_DEFECT);
        }
        else
        {
          //������ "A�������� �������������" � ��������
          //���������� ���������� ���� � �������� ���� � �����, ���� �  ��ò���� � ��������� ������, ���� ����������� ��������� "i" � �������, �� ����� � ���������
          _CLEAR_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_AVAR_DEFECT);
        }
      }
      
      //������ "�������� �����������" ������ � ���������� �����: ������ ���� �� ����� ���������� � �������, ���� ����� ������ �� ��������
      if(_CHECK_SET_BIT((current_settings_prt.ranguvannja_outputs + N_BIG*i), RANG_OUTPUT_LED_DF_REG_DEFECT) !=0)
      {
        //������ "�������� �����������"  ������ ���������� �� ����� �����
        if (_CHECK_SET_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_DEFECT) ==0)
        {
          //������ "�������� �����������" �� � ��������
          //���������� ������������ ���� � �������� ���� � �����, ���� �  ��ò���� � ��������� ������, ���� ����������� ��������� "i" � �������, �� ����� � ���������
          _SET_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_DEFECT);
        }
        else
        {
          //������ "�������� �����������" � ��������
          //���������� ���������� ���� � �������� ���� � �����, ���� �  ��ò���� � ��������� ������, ���� ����������� ��������� "i" � �������, �� ����� � ���������
          _CLEAR_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_DEFECT);
        }
      }

      //����������, �� � ��������� �� ����������� ��������� �� ����� ����� � ���������, �� ����� � ��������� - ����� ��������� ������
      if (
          (temp_array_of_outputs[0] !=0 ) ||
          (temp_array_of_outputs[1] != 0) ||
          (temp_array_of_outputs[2] != 0) ||
          (temp_array_of_outputs[3] != 0) ||
          (temp_array_of_outputs[4] != 0) ||
          (temp_array_of_outputs[5] != 0)
         )
      {
        //��� ����������� ���� �������� ���� ���������, � ��� ���������� ���������� �� ���� ������ ���������� ���� ��� ���� �� �� ����� �������� ���� ���������, ������� �� ����������
        if ((current_settings_prt.type_of_output & (1 << i)) != 0)
        {
          //����� ����������, ���� � ���� ����� ��� �������� ����
          //³������, �� ����� ����� - ���������
          state_outputs |= (1 << i);
        }
        else
        {
          //����� ���������, ���� ���������� �� �� ��� ������ ���������� ����, �� ��� �������� ��, ������� ���� �� � ������� ������ ���������� (����������)
          if (_CHECK_SET_BIT((current_settings_prt.ranguvannja_outputs + N_BIG*i), RANG_OUTPUT_LED_DF_REG_WORK_BV) ==0)
          {
            //�� ���� ���� �� ���������� ������ �� (���� ���������)
          
            //³������, �� ����� ����� - ���������
            state_outputs |= (1 << i);
          }
          else
          {
            //�� ���� ���� ���������� ������ �� (���� ���������)
          
            //³������, �� ����� ����� - ��������� ����� ���, ���� ������� �� ������� �����
            if (_CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_WORK_BV) !=0)
              state_outputs |= (1 << i);
            else
              state_outputs &= ~(1 << i);
          }
        }
      }
      else
      {
        //����������, �� ����� ���������, �� ����������
        if ((current_settings_prt.type_of_output & (1 << i)) == 0)
        {
          //����� ���������
        
          //³������, �� ����� ����� - ��ǲ�������
          state_outputs &= ~(1 << i);
        }
      }
    }
  }
  else
  {
    //����������� ������e ��������, ���� ���������� �� ����!!!

    //������������ �� ����
    state_outputs = 0;
  }
  
  //���������� �� ����� ���������� ���� ���������� ������ � EEPROM
  unsigned int temp_value_char_for_volatile = state_signal_outputs;
  if((state_outputs  & current_settings_prt.type_of_output) != temp_value_char_for_volatile)
  {
    state_signal_outputs = state_outputs  & current_settings_prt.type_of_output;
    //����������� ����������� ��� ��, �� � EEPROM ����� �������� ��� �������� ���������� ������ � ��������� ��������������
    _SET_BIT(control_eeprom_taskes, TASK_START_WRITE_STATE_LEDS_OUTPUTS_EEPROM_BIT);
  }
  
  //�������� ���������� �� ������� �� ��� ��������� (� ����������� �������)
  unsigned int temp_state_outputs = 0;
  for (unsigned int index = 0; index < NUMBER_OUTPUTS; index++)
  {
    if ((state_outputs & (1 << index)) != 0)
    {
      if (index < NUMBER_OUTPUTS_1)
        temp_state_outputs |= 1 << (NUMBER_OUTPUTS_1 - index - 1);
      else
        temp_state_outputs |= 1 << index;
    }
  }
  unsigned int temp_state_outputs_1 =  temp_state_outputs                      & ((1 << NUMBER_OUTPUTS_1) - 1);
  unsigned int temp_state_outputs_2 = (temp_state_outputs >> NUMBER_OUTPUTS_1) & ((1 << NUMBER_OUTPUTS_2) - 1);
  _DEVICE_REGISTER(Bank1_SRAM2_ADDR, OFFSET_OUTPUTS_1) = temp_state_outputs_1;
  _DEVICE_REGISTER(Bank1_SRAM2_ADDR, OFFSET_OUTPUTS_2) = temp_state_outputs_2;
  TIM_PRT_write_tick = TIM2->CNT;
  /**************************/

  /**************************/
  //���� ���������� �� ���������
  /**************************/
  //�������� ����������, �� �� �������������� ������� "����� ���������" - � ���� ���, �� ���������� ������� ��� ���������
  if (_CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_RESET_LEDS) !=0)
  {
    state_leds = 0;
  }
  
  //���������, �� �������������� ����� ����� ���� ���������
  for (unsigned int i = 0; i < NUMBER_LEDS; i++)
  {
    //� ���������� ����� ������� ���������� ��������������, ���� ����������� ��������� "i"
    unsigned int temp_array_of_leds[N_BIG];
    
    //����������, �� � ��������� �� ����������� ��������� �� ����� ������������� � ���������, �� ����� � ��������� - ����� ��������� ������
    temp_array_of_leds[0] = current_settings_prt.ranguvannja_leds[N_BIG*i    ] & active_functions[0];
    temp_array_of_leds[1] = current_settings_prt.ranguvannja_leds[N_BIG*i + 1] & active_functions[1];
    temp_array_of_leds[2] = current_settings_prt.ranguvannja_leds[N_BIG*i + 2] & active_functions[2];
    temp_array_of_leds[3] = current_settings_prt.ranguvannja_leds[N_BIG*i + 3] & active_functions[3];
    temp_array_of_leds[4] = current_settings_prt.ranguvannja_leds[N_BIG*i + 4] & active_functions[4];
    temp_array_of_leds[5] = current_settings_prt.ranguvannja_leds[N_BIG*i + 5] & active_functions[5];

    if (
        (temp_array_of_leds[0] != 0) ||
        (temp_array_of_leds[1] != 0) ||
        (temp_array_of_leds[2] != 0) ||
        (temp_array_of_leds[3] != 0) ||
        (temp_array_of_leds[4] != 0) ||
        (temp_array_of_leds[5] != 0)
       )
    {
      //³������, �� ����� ������������� - ������
      state_leds |= (1 << i);
    }
    else
    {
      //����������, �� ����� ������������� ����������, �� ���������
      if ((current_settings_prt.type_of_led & (1 << i)) == 0)
      {
        //������������� ����������

        //³������, �� ����� ������������� - ���������
        state_leds &= ~(1 << i);
      }
    }
  }
  //���������� �� ����� ���������� ���� ��������� �������������� � EEPROM
  temp_value_char_for_volatile = state_trigger_leds;
  if((state_leds  & current_settings_prt.type_of_led) != temp_value_char_for_volatile)
  {
    state_trigger_leds = state_leds  & current_settings_prt.type_of_led;
    //����������� ����������� ��� ��, �� � EEPROM ����� �������� ��� �������� ���������� ������ � ��������� ��������������
    _SET_BIT(control_eeprom_taskes, TASK_START_WRITE_STATE_LEDS_OUTPUTS_EEPROM_BIT);
  }

  //�������� ���������� �� ��������������� �� ���������
  _DEVICE_REGISTER(Bank1_SRAM2_ADDR, OFFSET_LEDS) = state_leds;
  /**************************/

  /**************************/
  //
  /**************************/
  /**************************/
}
/*****************************************************/

/*****************************************************/
//����������� �� ������� TIM2, ���� ��������� ������� �������
/*****************************************************/
void TIM2_IRQHandler(void)
{
#ifdef SYSTEM_VIEWER_ENABLE
  SEGGER_SYSVIEW_RecordEnterISR();
#endif
  
  if (TIM_GetITStatus(TIM2, TIM_IT_CC1) != RESET)
  {
    /***********************************************************************************************/
    //����������� �������� �� ������ 1, ���� ������ ����������� ���� 1 ��, ��� ��������������� ������� � ������ �������
    /***********************************************************************************************/
    TIM2->SR = (uint16_t)((~(uint32_t)TIM_IT_CC1) & 0xffff);
    uint32_t current_tick = TIM2->CCR1;
    
    /***********************************************************/
    //����������, �� ���������� ���� ���������
    /***********************************************************/
    if (
        (changed_settings == CHANGED_ETAP_ENDED) && /*�� � �����, �� ��� ��� ���������� ��� �������� �� � ������ �������� ������� (� ��� ����� ����� ��� �� ���������)*/
        (state_ar_record  != STATE_AR_START    )    /*�� � �����, �� �� ����� ������ �� ���� ��������� ����������� �� ����������� ������� (� ����� ���������� �� �������� ������� �������) � ������ ������� ���������� ������ ����������� ����������. �� ����� ���� ����� ������ ����������� � ������������� ������*/ 
       )   
    {
      //������� ������� ��������� � ���� ���� ������� ��� � ���� ������ (���� � �����) ����� ������� �������
      current_settings_prt = current_settings;
      
      //�������, �� ���� ������� �������� �������
      changed_settings = CHANGED_ETAP_NONE;
    }

    if (koef_resurs_changed == CHANGED_ETAP_ENDED)
    {
      //����������� ��� ��������� ������� ��������
      K_resurs_prt = K_resurs;

      //�������, �� ���� ������� �������� �������
      koef_resurs_changed = CHANGED_ETAP_NONE;
    }
    /***********************************************************/

    /***********************************************************/
    //���������� ����������� ������� ����������� � ����������� ����������
    /***********************************************************/
    //���������� ���������
    if (
        ((clean_rejestrators & CLEAN_AR) != 0 )
        &&  
        (state_ar_record == STATE_AR_NO_RECORD)
        &&  
        (
         (control_tasks_dataflash & (
                                     TASK_MAMORY_PART_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_AR |
                                     TASK_MAMORY_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_AR      |
                                     TASK_MAMORY_READ_DATAFLASH_FOR_AR_USB                         |
                                     TASK_MAMORY_READ_DATAFLASH_FOR_AR_RS485                       |
                                     TASK_MAMORY_READ_DATAFLASH_FOR_AR_MENU
                                    )
         ) == 0
        )   
       )
    {
      //���������� ������� �������� ����������� ����������

      //����������� ������� ������ ���� ��������� � EEPROM
      _SET_BIT(control_eeprom_taskes, TASK_START_WRITE_INFO_REJESTRATOR_AR_EEPROM_BIT);
    
      //������� ��������� ���������� �� ����������� ���������
      info_rejestrator_ar.next_address = MIN_ADDRESS_AR_AREA;
      info_rejestrator_ar.saving_execution = 0;
      info_rejestrator_ar.number_records = 0;
    
      //�������, �� ����� ������ �� ��������
      number_record_of_ar_for_menu = 0xffff;
      number_record_of_ar_for_USB = 0xffff;
      number_record_of_ar_for_RS485 = 0xffff;

      //������ ������� ������� ����������� ����������
      clean_rejestrators &= (unsigned int)(~CLEAN_AR);
    }
    
    //���������� ���������
    if (
        ((clean_rejestrators & CLEAN_DR) != 0)
        &&  
        (
         (control_tasks_dataflash & (
                                     TASK_MAMORY_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_DR | 
                                     TASK_MAMORY_READ_DATAFLASH_FOR_DR_USB                    |
                                     TASK_MAMORY_READ_DATAFLASH_FOR_DR_RS485                  |
                                     TASK_MAMORY_READ_DATAFLASH_FOR_DR_MENU
                                    )
         ) == 0
        )
       )   
    {
      //���������� ������� �������� ����������� ���������

      //����������� ������� ������ ���� ��������� � EEPROM
      _SET_BIT(control_eeprom_taskes, TASK_START_WRITE_INFO_REJESTRATOR_DR_EEPROM_BIT);

      //������� ��������� ���������� �� ����������� ���������
      info_rejestrator_dr.next_address = MIN_ADDRESS_DR_AREA;
      info_rejestrator_dr.saving_execution = 0;
      info_rejestrator_dr.number_records = 0;

      //�������, �� ����� ������ �� ��������
      number_record_of_dr_for_menu  = 0xffff;
      number_record_of_dr_for_USB   = 0xffff;
      number_record_of_dr_for_RS485 = 0xffff;

      //������ ������� ������� ����������� ����������
      clean_rejestrators &= (unsigned int)(~CLEAN_DR);
    }
    /***********************************************************/

    /***********************************************************/
    //���������� ������� �������� � ���������� ����� ����� ���� ��������� ������ ��������
    /***********************************************************/
    clocking_global_timers();
    /***********************************************************/
    
    /***********************************************************/
    //���������� ������� �������
    /***********************************************************/
    //ĳ��������� �����, ��� ����� ��������� ����� ��� ����� �������� ��������������� ����� ��������
    uint32_t TIM_PRT_read_tick = TIM2->CNT;

    uint64_t TIM_PRT_delta_write_read;
    if (TIM_PRT_read_tick < TIM_PRT_write_tick)
      TIM_PRT_delta_write_read = TIM_PRT_read_tick + 0x100000000 - TIM_PRT_write_tick;
    else TIM_PRT_delta_write_read = TIM_PRT_read_tick - TIM_PRT_write_tick;
    if (TIM_PRT_delta_write_read > (TIM2_MIN_PERIOD_WRITE_READ + 1))
    {
      unsigned int control_state_outputs_1 = (( (~((unsigned int)(_DEVICE_REGISTER(Bank1_SRAM2_ADDR, OFFSET_OUTPUTS_1)))) >> 8) & ((1 << NUMBER_OUTPUTS_1) - 1));
      unsigned int control_state_outputs_2 = (( (~((unsigned int)(_DEVICE_REGISTER(Bank1_SRAM2_ADDR, OFFSET_OUTPUTS_2)))) >> 8) & ((1 << NUMBER_OUTPUTS_2) - 1));
      unsigned int control_state_outputs = control_state_outputs_1 | (control_state_outputs_2 << NUMBER_OUTPUTS_1);
      //������� ����� ������ � ���������� �� ������ ���������
      unsigned int temp_state_outputs = 0;
      for (unsigned int index = 0; index < NUMBER_OUTPUTS; index++)
      {
        if ((state_outputs & (1 << index)) != 0) 
        {
          if (index < NUMBER_OUTPUTS_1)
            temp_state_outputs |= 1 << (NUMBER_OUTPUTS_1 - index - 1);
          else
            temp_state_outputs |= 1 << index;
        }
      }
      
      static uint32_t error_rele[NUMBER_OUTPUTS];
      if (control_state_outputs != temp_state_outputs) 
      {
        for (unsigned int index = 0; index < NUMBER_OUTPUTS; index++)
        {
          uint32_t maska;
          if (index < NUMBER_OUTPUTS_1)
            maska = 1 << (NUMBER_OUTPUTS_1 - index - 1);
          else
            maska = 1 << index;
        
          if ((control_state_outputs & maska) != (temp_state_outputs & maska))
          {
            if (error_rele[index] < 3) error_rele[index]++;
            if (error_rele[index] >= 3 ) _SET_BIT(set_diagnostyka, (ERROR_DIGITAL_OUTPUT_1_BIT + index));
          }
          else error_rele[index] = 0;
        }
      }
      else
      {
        for (unsigned int index = 0; index < NUMBER_OUTPUTS; index++) error_rele[index] = 0;
      }
    }
    
    //���������� ����������� ������� ��� ����������� ����������
    if (
        (state_ar_record  != STATE_AR_TEMPORARY_BLOCK) &&
        (changed_settings == CHANGED_ETAP_NONE       )  
       )   
    {
      //�������� ��������� ����� ���, ���� �� ��� ���� ������� ���������
      unsigned int size_one_ar_record_tmp = size_one_ar_record, max_number_records_ar_tmp = max_number_records_ar;
      if (
          ((number_word_digital_part_ar*8*sizeof(short int)) < NUMBER_TOTAL_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG)
          ||  
          (size_one_ar_record_tmp != (sizeof(__HEADER_AR) + ((current_settings_prt.prefault_number_periods + current_settings_prt.postfault_number_periods) << VAGA_NUMBER_POINT_AR)*(NUMBER_ANALOG_CANALES + number_word_digital_part_ar)*sizeof(short int)))
          ||
          (
           !(
             (size_one_ar_record_tmp* max_number_records_ar_tmp      <= ((NUMBER_PAGES_INTO_DATAFLASH_2 << VAGA_SIZE_PAGE_DATAFLASH_2))) &&
             (size_one_ar_record_tmp*(max_number_records_ar_tmp + 1) >  ((NUMBER_PAGES_INTO_DATAFLASH_2 << VAGA_SIZE_PAGE_DATAFLASH_2)))
            ) 
          ) 
         )
      {
        //���������� �� ������� ����� �� ����� ������������
        /*���� ������� ���� �������� �� ����� ��������� ���������, ��� ���� ���� �� ���������� - 
        �� �������� ����������� ���������� ������� � �������������� ���������� ����������� ����������.
        �� �������� ���� ���� �������, ���� � ��, ���������� ������ ����������� ������������ �� ��������!*/
        total_error_sw_fixed(5);
      }
    }

    //������� �������
    main_protection();
    /***********************************************************/

    /***********************************************************/
    //�������� �� ����������� ������� ������� ��ﳿ ����� ��� ������������
    /***********************************************************/
    //������� ����������
    if (periodical_tasks_TEST_TRG_FUNC != 0)
    {
      //����� � ���� ������� ������ ������� ������� ��ﳿ �����
      if ((state_eeprom_task & STATE_TRG_FUNC_EEPROM_GOOD) != 0)
      {
        //������ ���� ����� ���, ���� ������� ���������� ������ ������� � ���������� ���������� ����
        if (
            (_CHECK_SET_BIT(control_eeprom_taskes, TASK_START_WRITE_TRG_FUNC_EEPROM_BIT) == 0) &&
            (_CHECK_SET_BIT(control_eeprom_taskes, TASK_WRITING_TRG_FUNC_EEPROM_BIT    ) == 0) &&
            (_CHECK_SET_BIT(control_eeprom_taskes, TASK_START_READ_TRG_FUNC_EEPROM_BIT ) == 0) &&
            (_CHECK_SET_BIT(control_eeprom_taskes, TASK_READING_TRG_FUNC_EEPROM_BIT    ) == 0)
           ) 
        {
          //�� ����� ������� �� ��� �������-����� ������� ����������, ���� ����� �������� ���������
          misceve_dystancijne_ctrl = misceve_dystancijne;
          for (unsigned int i = 0; i < N_BIG; i++) trigger_active_functions_ctrl[i] = trigger_active_functions[i];
          crc_trg_func_ctrl = crc_trg_func;

          //������� ������� ������ ���������� �������� ��ﳿ 
          periodical_tasks_TEST_TRG_FUNC = false;
          //����������� ������� ������ �������� ����������� �� �������� ��ﳿ 
          periodical_tasks_TEST_TRG_FUNC_LOCK = true;
        }
      }
      else
      {
        //������� ������� ������ ���������� �������� ��ﳿ 
        periodical_tasks_TEST_TRG_FUNC = false;
      }
    }

    //���������� ���������
    if (periodical_tasks_TEST_INFO_REJESTRATOR_AR != 0)
    {
      //����� � ���� ������� ������ ������� ������� ��ﳿ �����
      if ((state_eeprom_task & STATE_INFO_REJESTRATOR_AR_EEPROM_GOOD) != 0)
      {
        //������ ���� ����� ���, ���� ��������� ���������� ���������� ������ ������� � ���������� ���������� ����
        if (
            (_CHECK_SET_BIT(control_eeprom_taskes, TASK_START_WRITE_INFO_REJESTRATOR_AR_EEPROM_BIT) == 0) &&
            (_CHECK_SET_BIT(control_eeprom_taskes, TASK_WRITING_INFO_REJESTRATOR_AR_EEPROM_BIT    ) == 0) &&
            (_CHECK_SET_BIT(control_eeprom_taskes, TASK_START_READ_INFO_REJESTRATOR_AR_EEPROM_BIT ) == 0) &&
            (_CHECK_SET_BIT(control_eeprom_taskes, TASK_READING_INFO_REJESTRATOR_AR_EEPROM_BIT    ) == 0)
           ) 
        {
          //�� ����� ������� �� ��� �������-����� ��������� ���������� ����������, ���� ����� �������� ���������
          info_rejestrator_ar_ctrl = info_rejestrator_ar;
          crc_info_rejestrator_ar_ctrl = crc_info_rejestrator_ar;

          //������� ������� ������ ���������� �������� ��ﳿ 
          periodical_tasks_TEST_INFO_REJESTRATOR_AR = false;
          //����������� ������� ������ �������� ����������� �� �������� ��ﳿ 
          periodical_tasks_TEST_INFO_REJESTRATOR_AR_LOCK = true;
        }
      }
      else
      {
        //������� ������� ������ ���������� �������� ��ﳿ 
        periodical_tasks_TEST_INFO_REJESTRATOR_AR = false;
      }
    }

    //���������� ���������
    if (periodical_tasks_TEST_INFO_REJESTRATOR_DR != 0)
    {
      //����� � ���� ������� ������ ������� ������� ��ﳿ �����
      if ((state_eeprom_task & STATE_INFO_REJESTRATOR_DR_EEPROM_GOOD) != 0)
      {
        //������ ���� ����� ���, ���� ��������� ���������� ���������� ������ ������� � ���������� ���������� ����
        if (
            (_CHECK_SET_BIT(control_eeprom_taskes, TASK_START_WRITE_INFO_REJESTRATOR_DR_EEPROM_BIT) == 0) &&
            (_CHECK_SET_BIT(control_eeprom_taskes, TASK_WRITING_INFO_REJESTRATOR_DR_EEPROM_BIT    ) == 0) &&
            (_CHECK_SET_BIT(control_eeprom_taskes, TASK_START_READ_INFO_REJESTRATOR_DR_EEPROM_BIT ) == 0) &&
            (_CHECK_SET_BIT(control_eeprom_taskes, TASK_READING_INFO_REJESTRATOR_DR_EEPROM_BIT    ) == 0)
           ) 
        {
          //�� ����� ������� �� ��� �������-����� ��������� ���������� ����������, ���� ����� �������� ���������
          info_rejestrator_dr_ctrl = info_rejestrator_dr;
          crc_info_rejestrator_dr_ctrl = crc_info_rejestrator_dr;

          //������� ������� ������ ���������� �������� ��ﳿ 
          periodical_tasks_TEST_INFO_REJESTRATOR_DR = false;
          //����������� ������� ������ �������� ����������� �� �������� ��ﳿ 
          periodical_tasks_TEST_INFO_REJESTRATOR_DR_LOCK = true;
        }
      }
      else
      {
        //������� ������� ������ ���������� �������� ��ﳿ 
        periodical_tasks_TEST_INFO_REJESTRATOR_DR = false;
      }
    }
    /***********************************************************/

    //˳������� �������
    if (periodical_tasks_TEST_RESURS != 0)
    {
      //����� � ���� ������� ������ ������� ������� ��ﳿ �����
      if ((state_eeprom_task & STATE_RESURS_EEPROM_GOOD) != 0)
      {
        //������ ���� ����� ���, ���� ���������z ������ ������� � ���������� ���������� ����
        if (
            (_CHECK_SET_BIT(control_eeprom_taskes, TASK_START_WRITE_RESURS_EEPROM_BIT) == 0) &&
            (_CHECK_SET_BIT(control_eeprom_taskes, TASK_WRITING_RESURS_EEPROM_BIT    ) == 0) &&
            (_CHECK_SET_BIT(control_eeprom_taskes, TASK_START_READ_RESURS_EEPROM_BIT ) == 0) &&
            (_CHECK_SET_BIT(control_eeprom_taskes, TASK_READING_RESURS_EEPROM_BIT    ) == 0)
           ) 
        {
          //�� ����� ������� �� ��� �������-����� ������� ��������, ���� ����� �������� ���������
          resurs_vymykacha_ctrl = resurs_vymykacha;          
          resurs_vidkljuchennja_ctrl = resurs_vidkljuchennja;
          crc_resurs_ctrl = crc_resurs;

          //������� ������� ������ ���������� �������� ��ﳿ 
          periodical_tasks_TEST_RESURS = false;
          //����������� ������� ������ �������� ����������� �� �������� ��ﳿ 
          periodical_tasks_TEST_RESURS_LOCK = true;
        }
      }
      else
      {
        //������� ������� ������ ���������� �������� ��ﳿ 
        periodical_tasks_TEST_RESURS = false;
      }
    }

    /***********************************************************/
    //������������ "�������� ��������� ��� ���������� �����������"
    /***********************************************************/
    uint32_t capture_new;
    unsigned int delta;
    TIM2->CCR1 = (capture_new = (current_tick + (delta = TIM2_CCR1_VAL)));
    
    unsigned int repeat;
    unsigned int previous_tick;
    do
    {
      repeat = 0;
      current_tick = TIM2->CNT;

      uint64_t delta_time = 0;
      if (capture_new < current_tick)
        delta_time = capture_new + 0x100000000 - current_tick;
      else delta_time = capture_new - current_tick;

      if ((delta_time > delta) || (delta_time == 0))
      {
        if (TIM_GetITStatus(TIM2, TIM_IT_CC1) == RESET)
        {
          if (delta < TIM2_CCR1_VAL)
          {
            uint64_t delta_tick;
            if (current_tick < previous_tick)
              delta_tick = current_tick + 0x100000000 - previous_tick;
            else delta_tick = current_tick - previous_tick;
              
            delta = delta_tick + 1;
          }
          else if (delta == TIM2_CCR1_VAL)
            delta = 1; /*����������, ��� ���� ���������� ����������� �� ����� ������*/
          else
          {
            //���������� ����� ����� �� ���� � ����
            total_error_sw_fixed(83);
          }
          TIM2->CCR1 = (capture_new = (TIM2->CNT +  delta));
          previous_tick = current_tick;
          repeat = 0xff;
        }
      }
    }
    while (repeat != 0);
    /***********************************************************/
    
    /***********************************************************/
    //����������� ����������� ��� ��, ������� ������ �������
    /***********************************************************/
    control_word_of_watchdog |= WATCHDOG_PROTECTION;
    /***********************************************************/
    /***********************************************************************************************/
  }
  else
  {
    total_error_sw_fixed(23);
  }
  
#ifdef SYSTEM_VIEWER_ENABLE
  SEGGER_SYSVIEW_RecordExitISR();
#endif
}
/*****************************************************/

/*****************************************************/
//���� ����� �������
/*****************************************************/
void setpoints_selecting(unsigned int *activated_functions, unsigned int act_inp_gr_ustavok) {
  unsigned int grupa_ustavok = 0;
  act_inp_gr_ustavok &= 0xf;
  if (current_settings_prt.grupa_ustavok < SETPOINT_GRUPA_USTAVOK_MIN ||
      current_settings_prt.grupa_ustavok > SETPOINT_GRUPA_USTAVOK_MAX) {
    //�������������� ������
    while (1);
  } else {
    grupa_ustavok = 1 << (current_settings_prt.grupa_ustavok - 1);
  }
  
  _OR4_INVERTOR(act_inp_gr_ustavok, 0, act_inp_gr_ustavok, 1, act_inp_gr_ustavok, 2, act_inp_gr_ustavok, 3, act_inp_gr_ustavok, 4);
  if (_GET_OUTPUT_STATE(act_inp_gr_ustavok, 4)) 
    _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_INVERS_DV_GRUPA_USTAVOK);
  else
    _CLEAR_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_INVERS_DV_GRUPA_USTAVOK);

  _AND2(grupa_ustavok, 0, act_inp_gr_ustavok, 4, grupa_ustavok, 4);
  _AND2(grupa_ustavok, 1, act_inp_gr_ustavok, 4, grupa_ustavok, 5);
  _AND2(grupa_ustavok, 2, act_inp_gr_ustavok, 4, grupa_ustavok, 6);
  _AND2(grupa_ustavok, 3, act_inp_gr_ustavok, 4, grupa_ustavok, 7);
  
  unsigned int tmp = gr_ustavok_tmp;
  do {
    _AND4(act_inp_gr_ustavok, 0, gr_ustavok_tmp, 1, gr_ustavok_tmp, 2, gr_ustavok_tmp, 3, act_inp_gr_ustavok, 5);
    _INVERTOR(act_inp_gr_ustavok, 5, tmp, 0);
    
    _AND4(tmp, 0, act_inp_gr_ustavok, 1, tmp, 2, tmp, 3, act_inp_gr_ustavok, 6);
    _INVERTOR(act_inp_gr_ustavok, 6, tmp, 1);
    
    _AND4(tmp, 0, tmp, 1, act_inp_gr_ustavok, 2, tmp, 3, act_inp_gr_ustavok, 7);
    _INVERTOR(act_inp_gr_ustavok, 7, tmp, 2);
    
    _AND4(tmp, 0, tmp, 1, tmp, 2, act_inp_gr_ustavok, 3, act_inp_gr_ustavok, 8);
    _INVERTOR(act_inp_gr_ustavok, 8, tmp, 3);
    if (tmp == gr_ustavok_tmp) {
      break;
    }
    gr_ustavok_tmp = tmp;
  } while (1);
  
  _OR2(grupa_ustavok, 4, act_inp_gr_ustavok, 5, grupa_ustavok, 8);
  _OR2(grupa_ustavok, 5, act_inp_gr_ustavok, 6, grupa_ustavok, 9);
  _OR2(grupa_ustavok, 6, act_inp_gr_ustavok, 7, grupa_ustavok, 10);
  _OR2(grupa_ustavok, 7, act_inp_gr_ustavok, 8, grupa_ustavok, 11);
  
  if (_GET_OUTPUT_STATE(grupa_ustavok, 8)) {
    _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_1_GRUPA_USTAVOK);
  }
  if (_GET_OUTPUT_STATE(grupa_ustavok, 9)) {
    _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_2_GRUPA_USTAVOK);
  }
  if (_GET_OUTPUT_STATE(grupa_ustavok, 10)) {
    _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_3_GRUPA_USTAVOK);
  }
  if (_GET_OUTPUT_STATE(grupa_ustavok, 11)) {
    _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_4_GRUPA_USTAVOK);
  }
}
/*****************************************************/

/*****************************************************/
