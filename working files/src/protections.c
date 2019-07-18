#include "header.h"

/*****************************************************/
//Діагностика АЦП
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
//Пошук розрядності числа
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
//Пошук розрядності числа типу int
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
//Розрахунок кореня квадратного методом половинного ділення  з прогнозуванням розрядності числа
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
//Розрахунок кореня квадратного методом половинного ділення  з прогнозуванням розрядності числа
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
//Розрахунок струму зворотньої послідовності
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

  //Зворотня послідовність
  ortogonal_tmp[0] = ((int)(0x155*(ortogonal_local_calc[2*FULL_ORT_Ia    ] - mul_x1  + mul_x2  - mul_x3 - mul_x4)))>>10;
  ortogonal_tmp[1] = ((int)(0x155*(ortogonal_local_calc[2*FULL_ORT_Ia + 1] - mul_y1  - mul_y2  + mul_y3 - mul_y4)))>>10;
  measurement[IM_I2] = (unsigned int)((unsigned long long)( MNOGNYK_I_DIJUCHE  *(sqrt_32((unsigned int)ortogonal_tmp[0]*ortogonal_tmp[0] + (unsigned int)ortogonal_tmp[1]*ortogonal_tmp[1])) ) >> (VAGA_DILENNJA_I_DIJUCHE   + 4));

  //Пряма послідовність
  ortogonal_tmp[0] = ((int)(0x155*(ortogonal_local_calc[2*FULL_ORT_Ia    ] - mul_x1  - mul_x2  - mul_x3 + mul_x4)))>>10;
  ortogonal_tmp[1] = ((int)(0x155*(ortogonal_local_calc[2*FULL_ORT_Ia + 1] + mul_y1  - mul_y2  - mul_y3 - mul_y4)))>>10;
  measurement[IM_I1] = (unsigned int)((unsigned long long)( MNOGNYK_I_DIJUCHE  *(sqrt_32((unsigned int)ortogonal_tmp[0]*ortogonal_tmp[0] + (unsigned int)ortogonal_tmp[1]*ortogonal_tmp[1])) ) >> (VAGA_DILENNJA_I_DIJUCHE   + 4));
}
/*****************************************************/

/*****************************************************
ort_i  - вказівник на ортогональні 3I0
ort_u  - вказівник на ортогональні 3U0
*****************************************************/
inline void detector_kuta_nzz(int ortogonal_local_calc[]) 
{
  int cos_fi, sin_fi;

#define SIN_3I0   ortogonal_local_calc[2*FULL_ORT_3I0    ]
#define COS_3I0   ortogonal_local_calc[2*FULL_ORT_3I0 + 1]
#define SIN_3U0   ortogonal_local_calc[2*FULL_ORT_3U0_Ubc_TN2    ]
#define COS_3U0   ortogonal_local_calc[2*FULL_ORT_3U0_Ubc_TN2 + 1]

  /***
  Тригонометричні координати вектора різниці 
  ***/
  cos_fi = COS_3I0*COS_3U0 + SIN_3I0*SIN_3U0;
  sin_fi = -(SIN_3I0*COS_3U0 - COS_3I0*SIN_3U0);//З розділу: "Неймовірно, але факт", тобто що я не можу пояснити
  /***/

#undef SIN_3I0
#undef COS_3I0
#undef SIN_3U0
#undef COS_3U0

  /*
  З наведених теоретичних роззрахунків у функції обрахунку діючих значень (calc_measurement())
  випливає, що ортогональні складові векторів 3I0 і 3U0 є 15-бітні чилс + знак.
  Тоді COS і SIN різниці цих векторів може бути 31-бітне число
  Вектьорні координати границь секторів задано 7-бінтими числами + знак
  Тоді щоб не отримати переповнення треба гарантувати, що розрядність різниці векторів
  COS і SIN буде = 31 - (7 + 1) = 23
  7 - це розрядність координат векторів границь секторів
  1 - це врахування що ми використовіємо формулу (ab+cd)
  */
  unsigned int order_cos, order_sin, max_order, shift = 0;
  order_cos = get_order(cos_fi);
  order_sin = get_order(sin_fi);
  if (order_cos > order_sin) max_order = order_cos; else max_order = order_sin;
  if (max_order > 23) shift = max_order - 23;
  
  /*
  Сам зсув я роблю після визначення квадранта - це хоч і втрата на розмірі програмного коду,
  але мало б підвищити точність визначення квадранту.
  Хоч може тут я перемудровую?..
  */

  /***
  Визначення квадранта
  ***/
  int sin_fi1_minus_fi2;
  if ((cos_fi >= 0) && (sin_fi >= 0))
  {
    //1-ий квадрант
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
     //2-ий квадрант
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
    //3-ій квадрант
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
    //4-ий квадрант
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
//Направленість МТЗ з визначенням секторів
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
        //Теоретично цього ніколи не мало б бути
        total_error_sw_fixed(54);
      }
    }
    a_sin_fi = -a_sin_fi; //З розділу: "Неймовірно, але факт", тобто що я не можу пояснити

    //Робимо доповорот на встановлений кут
    /*
    За розрахунком описаним при розрахунку діючих значень наші ортогональні є у ворматі (15 біт + знак) = 16-розряжне число
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
          //Теоретично цього ніколи не мало б бути
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

        amp_cos_U_fi = (COS_U*a_cos_fi - SIN_U*a_sin_fi) >> AMPLITUDA_FI_VAGA; //З поверненням до початкової розрядності ортогональних
        amp_sin_U_fi = (SIN_U*a_cos_fi + COS_U*a_sin_fi) >> AMPLITUDA_FI_VAGA; //З поверненням до початкової розрядності ортогональних

        //Вираховуємо COS і SIN кута різниці між (U[i]+fi) і I[i]
        int cos_fi, sin_fi;
        /*
        З наведених теоретичних роззрахунків у функції обрахунку діючих значень (calc_measurement())
        випливає, що максимальне значення ортогональних для струму може бути 0x6E51, для лінійної напруги 
        0x120FC, то добуток їх має дати 0x7C87B7BC  - 31 бітне число (плюс знак біту)
        Тобто ми акладаємося у тип int.
        */
        cos_fi = amp_cos_U_fi*COS_I + amp_sin_U_fi*SIN_I;
        sin_fi = -(amp_sin_U_fi*COS_I - amp_cos_U_fi*SIN_I);//З розділу: "Неймовірно, але факт", тобто що я не можу пояснити

#undef SIN_I
#undef COS_I
#undef SIN_U
#undef COS_U

        /*
        З вище наведених розрахункыв виходить, що COS і SIN різниці струму і напруги може бути 31-бітне число
        Векторні координати границь секторів задано 7-бінтими числами + знак
        Тоді щоб не отримати переповнення треба гарантувати, що розрядність різниці векторів
        COS і SIN буде = 31 - (7 + 1) = 23
        7 - це розрядність координат векторів границь секторів
        1 - це врахування що ми використовіємо формулу (ab+cd)
        */
        unsigned int order_cos, order_sin, max_order, shift = 0;
        order_cos = get_order(cos_fi);
        order_sin = get_order(sin_fi);
        if (order_cos > order_sin) max_order = order_cos; else max_order = order_sin;
        if (max_order > 23) shift = max_order - 23;
  
        /*
        Сам зсув я роблю після визначення квадранта - це хоч і втрата на розмірі програмного коду,
        але мало б підвищити точність визначення квадранту.
        Хоч може тут я перемудровую?..
        */

        //Визначення сектору
        int sin_fi1_minus_fi2;
        int *sector;
        if ((sin_fi >= 0) && (cos_fi >= 0))
        {
          //1-ий квадрант
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
          //2-ий квадрант
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
          //3-ий квадрант
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
          //4-ий квадрант
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
//Визначенням опорів
/*****************************************************/
inline void calc_resistance(int ortogonal_local_calc[], int resistance_output[]) 
{
  const unsigned int index_line_voltage[3]  = {FULL_ORT_Uab, FULL_ORT_Ubc, FULL_ORT_Uca};
  const unsigned int index_begin_current[3] = {FULL_ORT_Ia , FULL_ORT_Ib , FULL_ORT_Ic };
  const unsigned int index_end_current[3]   = {FULL_ORT_Ib , FULL_ORT_Ic , FULL_ORT_Ia };
  
  for (unsigned int i = 0; i < 3; i++)
  {
    //Розраховуємо координати струму Ixy
    int _a2, _b2;
    /*
    З наведених теоретичних роззрахунків у функції обрахунку діючих значень (calc_measurement())
    випливає, що максимальне значення ортогональних для струму може бути 0x6E51, для лінійної напруги 
    0x120FC

    З фазних струмів розраховуються лінійні струми, то, якщо припустити що вектори розврнуті у різні сторони, то  максимальне
    значення ортогональних може бути
    0x6E51*2 = 0xDCA2 це є 16 бітне число (+ можливий знак) - тобто число виходить 17-бітне
    */
    
    _a2 = ortogonal_local_calc[2*index_begin_current[i] + 0] - ortogonal_local_calc[2*index_end_current[i] + 0];
    _b2 = ortogonal_local_calc[2*index_begin_current[i] + 1] - ortogonal_local_calc[2*index_end_current[i] + 1];

#define _A1     ortogonal_local_calc[2*index_line_voltage[i] + 0]
#define _B1     ortogonal_local_calc[2*index_line_voltage[i] + 1]
    
    long long mod = (long long)_a2*(long long)_a2 + (long long)_b2*(long long)_b2;
    
    //Розраховуємо амплітуду струму Ixy
    unsigned int Ixy = ( MNOGNYK_I_DIJUCHE*(sqrt_64(mod)) ) >> (VAGA_DILENNJA_I_DIJUCHE + 4);
    
    if (Ixy >= PORIG_Ixy)
    {
      //Можна розраховувати міжфазний опір
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
      //Не можна розраховувати міжфазний опір
      resistance_output[2*i    ] = UNDEF_RESISTANCE;
      resistance_output[2*i + 1] = UNDEF_RESISTANCE;
    }
    
#undef _A1
#undef _B1
  }
}
/*****************************************************/

/*****************************************************/
//Визначенням миттєвої потужності
/*****************************************************/
inline void calc_power(int ortogonal_local_calc[]) 
{
  /*
  Розраховуємо дійсну і уявну частину потужності у компдексній площині
  
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
  
  long long P_adc_x16 = Re_IaUab - Re_IcUbc; /*  активна потужність у поділках АЦП і з вхідними сигналами, які є підсилені у 16 разів*/
  long long Q_adc_x16 = Im_IaUab - Im_IcUbc; /*реактивна потужність у поділках АЦП і з вхідними сигналами, які є підсилені у 16 разів*/
  
  /*
  Коли перемножимо на коефіцієнти MNOGNYK_I_DIJUCHE_FLOAT і MNOGNYK_U_DIJUCHE_FLOAT,
  а потім поділемо на 16x16 - то отримаємо мАхмВ = мкВт/мкВАр/мкВА
  
  Ми хочемо тримати число у мВт/мВАр/мВА. 
  
  Тоді треба поділити ще на 1000
  */
  
  //Активна потужність
  double P_float = ((double)P_adc_x16) * ((double)(MNOGNYK_I_DIJUCHE_DOUBLE*MNOGNYK_U_DIJUCHE_DOUBLE/(1000.0*16.0*16.0)));
  int P_tmp = (int)(P_float); // з точністю до мВт

  //Реактивна потужність
  double Q_float = ((double)Q_adc_x16) * ((double)(MNOGNYK_I_DIJUCHE_DOUBLE*MNOGNYK_U_DIJUCHE_DOUBLE/(1000.0*16.0*16.0)));
  int Q_tmp  = (int)(Q_float); // з точністю до мВАр

  unsigned int bank_for_enegry_tmp = bank_for_enegry;  
  int *energy_array;
  
  //Активна потужність
  if (P_tmp >= 0) energy_array = P_plus;
  else energy_array = P_minus;
  *(energy_array + bank_for_enegry_tmp) += abs(P_tmp);
  
  //Реактивна потужність
  if     ((Q_tmp >= 0) && (P_tmp >= 0)) energy_array = Q_1q;
  else if((Q_tmp >= 0) && (P_tmp <  0)) energy_array = Q_2q;
  else if((Q_tmp <  0) && (P_tmp <  0)) energy_array = Q_3q;
  else                                  energy_array = Q_4q;
  *(energy_array + bank_for_enegry_tmp) += abs(Q_tmp);
  
  if (++lichylnyk_1s_po_20ms >= MAIN_FREQUENCY)
  {
    if (lichylnyk_1s_po_20ms > MAIN_FREQUENCY)
    {
      //Теоретично цього ніколи не мало б бути
      total_error_sw_fixed(64);
    }

    //Переключаємо банк для збереження нових даних s обнулюємо значення у новому банку
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
      //Скидаємо повідомлення у слові діагностики
      _SET_BIT(clear_diagnostyka, LOSE_ENERGY_DATA);
    }
    else
    {
      //Виствляємо повідомлення у слові діагностики
      _SET_BIT(set_diagnostyka, LOSE_ENERGY_DATA);
    }
    periodical_tasks_CALC_ENERGY_DATA = true;
  }
  
}
/*****************************************************/

/*****************************************************/
//Розрахунки віимірювань
/*****************************************************/
inline void calc_measurement(unsigned int number_group_stp)
{
  int ortogonal_local[2*NUMBER_ANALOG_CANALES];
  unsigned long long sum_sqr_data_3I0_local;
  float value_3I0_i_float, value_3I0_f_float;

  //Виставляємо семафор заборони обновлення значень з вимірювальної системи
//  semaphore_measure_values = 1;

  //Копіюємо вхідні велечини у локальні змінні
  /*
  оскільки для дискретного перетворення Фурє коефіцієнти діляться на число виборок і множиться на 2 (еквівалент 2/Т),
  то це ми можемо зробити зміщенням
  */
  /*
  Проведені мною розрахунки показують, що якщо просумувати добуток миттєвих значень на синус/косинус за період,
  а потім результат поділити на 2/Т (зробити це відповідним зсуваом, про який я писав вище),
  то максимана розрядність резутьтату буде рівна макисальній розрядності вхідного сигналу
  Тобто для 3I0            - це 19 біт + знак = ((11 біт + знак)*16*16)
        для фазних струмів - це 15 біт + знак = ((11 біт + знак)*16   )
  оскільки нам ще треба це число піднімати до квадрату а аж потім добувати корінь квадратний з суми квадратів, то
  фазний струм можна підносити до кваррату - переповнення не буде, бо (15 біт *2) = 30 біт Бо 32 біт unsigned int
  А аж потім забрати множенння на 16, щоб збільшити точність вимірювання
  
  Для 3I0 можливе переповнення - тому треба або:
  1.  
  Перше 16-кратне підсилення забрати прямо з ортогональних для 3I0,
  тоді ортогоанльні стануть не більше 15-розрядного числа + знак.
  Друге 16-кратне підсилення забрати вже в остаточному результаті
    
  2.Використати 64-бітну арифметику.
    
  До 17 листопада 2014 року використовуввся перший метод.
  Але виникала похибка при розрахунку стуму вищих гармонік. Припускаю, що могло бути
  зв'язане з тим, що коли відкидадися молодші розряди - то струм першої гармоніки ставав
  трохи меншим за ремальне значення - а тоді виростав струм вищих гармонік
    
  Тому пробую використати другий метод з 17 листопада 2014 року  
  
  Для покращення точності з 18 листопада 2014 року я забираю амплітуду sin/cos вже
  перед самими розрахунками
  */
  
  unsigned int bank_ortogonal_tmp = (bank_ortogonal + 1) & 0x1;
  for(unsigned int i=0; i<(2*NUMBER_ANALOG_CANALES); i++ )
  {
    ortogonal_local[i] = ortogonal[i][bank_ortogonal_tmp];
  }
  
  /*
  Оскільки для інтеградбного розгахунку сума квадратів з період ділиться на період, 
  що для дискретного випадку аналогічн діленню на кількість виборок, то ми це ділення якраз і робимо зміщенням
  */
//  sum_sqr_data_3I0_period_local = sum_sqr_data_3I0_period;
  sum_sqr_data_3I0_local = sum_sqr_data_3I0[bank_ortogonal_tmp];

  bank_ortogonal = bank_ortogonal_tmp;
  
  //Знімаємо семафор заборони обновлення значень з вимірювальної системи
//  semaphore_measure_values = 0;
  
  /*******************************************************/
  //Перевіряємо, чи відбувалися зміни юстування
  /*******************************************************/
  if (changed_ustuvannja == CHANGED_ETAP_ENDED_EXTRA_ETAP) /*Це є умова, що нові дані підготовлені для передачі їх у роботу системою захистів(і при цьому зараз дані не змінюються)*/
  {
    //Копіюємо масив юстування у копію цього масиву але з яким працює (читає і змінює) тільки вимірювальна захистема
    for(unsigned int i = 0; i < NUMBER_ANALOG_CANALES; i++) 
    {
      phi_ustuvannja_meas[i] = phi_ustuvannja[i];
      phi_ustuvannja_sin_cos_meas[2*i    ] = phi_ustuvannja_sin_cos[2*i    ];
      phi_ustuvannja_sin_cos_meas[2*i + 1] = phi_ustuvannja_sin_cos[2*i + 1];
    }
      
    //Помічаємо, що зміни прийняті системою захистів
    changed_ustuvannja = CHANGED_ETAP_NONE;
  }
  /*****************************************************/

  /***
  Довертаємо кути і копіюємо ортогональні для низькопріоритетних задач
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

    
    //Копіюємо ортогональні для розрахунку кутів
    if (copy_to_low_tasks == true)
    {
      ortogonal_calc_low[2*new_index    ] = ortogonal_sin;
      ortogonal_calc_low[2*new_index + 1] = ortogonal_cos;
    }
  }
  /***/
  
  /***/
  //Розраховуємо діюче значення 3I0 по інтегральній сформулі
  /***/
  /*Добуваємо квадратний корінь*/
  sum_sqr_data_3I0_local = sqrt_64(sum_sqr_data_3I0_local);
  
  /*Для приведення цього значення у мА треба помножити на свій коефіцієнт*/
  /*Ще сигнал зараз є підсиленим у 256 раз, тому ділим його на 256*/
  /*Крім того запам'ятовуємо це значенян для розрахунку діючого значення ішних гармонфік*/

  /*
  Ми маємо ще отримане число поділити на корнь з NUMBER_POINT = 32 = 16*2
  Тобто ми маємо поділити на 4*sqrt(2)
  4 це зміщення на 2
  ((MNOGNYK_3I0_D * X )>> VAGA_DILENNJA_3I0_D)/sqrt(2) тотожне
   (MNOGNYK_3I0_DIJUCHE_D * X )>> VAGA_DILENNJA_3I0_DIJUCHE_D 
  
  Якщо робити через пари (MNOGNYK_3I0_DIJUCHE_D;VAGA_DILENNJA_3I0_DIJUCHE_D) і (MNOGNYK_3I0_D;VAGA_DILENNJA_3I0_D)
  то виникає похибка при розрахунку вищих гармонік.
  Тому треба іти на такі спрощення виразів
  */
  value_3I0_i_float = (unsigned int)(MNOGNYK_3I0_FLOAT*((float)sum_sqr_data_3I0_local)/(1024.0f)); /*1024 = 4*256. 256 - це підсилення каналу 3I0; 4 - це sqrt(16), а 16 береться з того. що 32 = 16*2 */
  measurement[IM_3I0_i] = (unsigned int)value_3I0_i_float; 
  /***/
  
  /*
  ---------------------------------------------------------------------------------------------------------
  150А (150 000мА) - максимальний фазний струм
  Коефіцієнст переведення в мА  - Koef_1 = 84,978173543997808495193432804655 для фазних струмів (5439/64 = 84,984375)
  
  Тоді для 150А максимально можливе значення ортогональних може бути
  150000/Koef_1 = 1765,0303364589078874793160507446
  Якщо врахувати, що сигнал є підсиленим у 16 раз, то максимальне значення ортогональних може бути
  16*150000/Koef_1 = 28240,485383342526199669056811914 < 28241(0x6E51) це є 15 бітне число (+ можливий знак)
  ---------------------------------------------------------------------------------------------------------

  ---------------------------------------------------------------------------------------------------------
  150В (150 000мВ) - максимальна фазна напруга
  Коефіцієнст переведення в мВ  - Koef_1 = 64,883134509545420915167731259667 для фазних напруг (4152/64 = 64,875)
  
  Тоді для 150В максимально можливе значення ортогональних може бути
  150000/Koef_1 = 2311,848851536795430557291797995
  Якщо врахувати, що сигнал є підсиленим у 16 раз, то максимальне значення ортогональних може бути
  16*150000/Koef_1 = 36989,581624588726888916668767919 < 36990(0x907E) це є 16 бітне число (+ можливий знак) - тобто число виходить 17-бітне
  
  Якщо з фазної напруги розраховується лінійна напруга, то, якзо припустити що вектори розврнуті у різні сторони, то  максимальне
  значення ортогональних може бути
  2*16*150000/Koef_1 = 73979,163249177453777833337535838 < 73980(0x120FC) це є 17 бітне число (+ можливий знак) - тобто число виходить 18-бітне
  ---------------------------------------------------------------------------------------------------------
  
  ---------------------------------------------------------------------------------------------------------
  2А (2 000мА * 10 = 20 000(десятих мА)) - максимальний струм 3I0
  Коефіцієнст переведення в десяті мА  - Koef_1* = 169,95634708799561699038686560931 для 3I0  для 3I0 при вираженні у десятих міліамперів (170/1 = 170)

  
  Тоді для 2А максимально можливе значення ортогональних може бути
  20000/Koef_1* = 117,67727621049018824880803941698
  Якщо врахувати, що сигнал є підсиленим у 16 раз (підсилення в 256 раз ми вже зменшили до 16), то максимальне значення ортогональних може бути
  16*20000/Koef_1* = 1882,8364193678430119809286306717 < 1883(0x075B) це є 11 бітне число (+ можливий знак)
  ---------------------------------------------------------------------------------------------------------
  */
  
  /***/
  //Розраховуємо діюче значення через перетворення Фур'є
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
      value_3I0_f_float = (unsigned int)(MNOGNYK_3I0_FLOAT*((float)d)/(256.0f)); /*256 - це підсиланне сигналу 3I0*/

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
          //Теоретично цього ніколи не мало б бути
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
          //Теоретично цього ніколи не мало б бути
          total_error_sw_fixed(67);
        }
      }
      
      measurement[index_m] = ( MNOGNYK_U_DIJUCHE*(sqrt_32((unsigned int)(ortogonal_calc[2*index_ort]*ortogonal_calc[2*index_ort]) + (unsigned int)(ortogonal_calc[2*index_ort+1]*ortogonal_calc[2*index_ort+1]))) ) >> (VAGA_DILENNJA_U_DIJUCHE + 4);
    }
    
  }
  /***/

  /***/
  //Розраховуємо діюче значення вищих гармонік 3I0
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
      //Якщо сюди дійшла програма, значить відбулася недопустива помилка, тому треба зациклити програму, щоб вона пішла на перезагрузку
      total_error_sw_fixed(59);
    }
  }
  else
    measurement[IM_3I0_other_g] = 0;
  /***/

  /***
  Дорозраховунок лінійних напруг і Ib
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
  //Фазочутливий елемент для МТЗ (всіх ступенів)
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
  //Розраховуємо струм зворотньої послідовності
  /***/
  velychyna_zvorotnoi_poslidovnosti(ortogonal_calc);
  /***/
  
  /***/
  //Розраховуємо опори
  /***/
  calc_resistance(ortogonal_calc, resistance);
  /***/

  if(++number_inputs_for_fix_one_period >= 20)
  {
    /***/
    //Розрахунок миттєвих потужностей (раз на 20мс)
    /***/
    calc_power(ortogonal_calc);
    /***/
    
    number_inputs_for_fix_one_period = 0;
  }
}
/*****************************************************/

/*****************************************************/
//Модуль обробки дискретних входів
/*****************************************************/
inline void input_scan(void)
{
  unsigned int state_inputs_into_pin, temp_state_inputs_into_pin; //Змінні у якій формуємо значення входів отримані із входів процесора (пінів)
  static unsigned int state_inputs_into_pin_trigger; //У цій змінній зберігається попередній стан піна, у випадку коли ми перевіряємо .чи утримається цей стан до кінця тактування таймера допуску

  /***************************/
  //У цій частині знімаємо стани входів процесора (пінів), які відповідають за дискретні входи
  /*
  -----------------------------
  значення поміщається у відпорвідні біти змінної state_inputs_into_pin
    "є     сигнал " - відповідає встановленому біту (1)
    "немає сигналу" - відповідає скинутому     біту (0)
  -----------------------------
  */
  unsigned int temp_state_inputs_into_pin_1 = _DEVICE_REGISTER(Bank1_SRAM2_ADDR, OFFSET_INPUTS_1) & ((1 << NUMBER_INPUTS_1) - 1);
  unsigned int temp_state_inputs_into_pin_2 = _DEVICE_REGISTER(Bank1_SRAM2_ADDR, OFFSET_INPUTS_2) & ((1 << NUMBER_INPUTS_2) - 1);
  temp_state_inputs_into_pin = temp_state_inputs_into_pin_1 | (temp_state_inputs_into_pin_2 << NUMBER_INPUTS_1);
  
  //Змінюємо порядок, щоб наймений номер відповідав нумерації на приладі
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
  //Обробка таймерів допуску дискретних входів
  /***************************/
  for(unsigned int i = 0; i < NUMBER_INPUTS; i++)
  {
    unsigned int maska = 1<<i;
    int max_value_timer = current_settings_prt.dopusk_dv[i];

    if (global_timers[INDEX_TIMER_INPUT_START + i] < 0)
    {
      //Провірка на зміну стану дискретного входу здійснюється тільки тоді, коли величина таймере є від'ємною
      //Що означає що таймер не запущений у попередній момент
      
      //Перевіряємо чи таеперішній стан входу відповідає попердньомук стану
      if ((state_inputs_into_pin & maska) != (state_inputs & maska))
      {
        //Якщо стан входу змінився, то виконуємо дії по зміні стану

        //1-дія: Запям'ятовуємо текучий стан входу
        state_inputs_into_pin_trigger &= ~maska;
        state_inputs_into_pin_trigger |= (state_inputs_into_pin & maska);

        //2-дія: Запускаємо таймер допуску дискретного входу
        global_timers[INDEX_TIMER_INPUT_START + i] = 0;
      }
    }
    else
    {
      //Якщо таймер запущений виконуємо дії з таймером
      if (global_timers[INDEX_TIMER_INPUT_START + i] < max_value_timer)
      {
        //Якщо таймер ще не дійшов до свого макисмуму, то просто збільшуємо його величину
        global_timers[INDEX_TIMER_INPUT_START + i] += DELTA_TIME_FOR_TIMERS;
        
        //У випадку, якщо тип сигналу на вхід подається змінний
        //і ми перевіряємо чи не відбувся перехід "є сигнал"->"немає сигналу"
        //то поява сигналу під час тактування таймера допуску означає, що сигнал на вході є - 
        //а це означає, що треба зупинити nаймер, бо переходу "є сигнал"->"немає сигналу" на протязі тактування таймеру не зафіксовано 
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
    
    //Якщо величина таймера допуска знаходиться у свому максимальному значенні, то перевіряємо, чи фактично змінився стано входу
    if (global_timers[INDEX_TIMER_INPUT_START + i] >= max_value_timer)
    {
      //Перевіряємо, чи стан піна змінився у порівнянні із станом, який був на момент запуску таймера допуску дискретного входу
      unsigned int state_1, state_2;
        
      state_1 = state_inputs_into_pin_trigger & maska;
      state_2 = state_inputs_into_pin  & maska;
        
      if (state_1 == state_2)
      {
        //Якщо два стани співпадають, то ми вважаємо, що відбулася зіна стану дискретного входу і формуємо новий стан входу
        //При цьому враховуємо що для прявого    входу 1 - це активний вхід, а 0 - це пасивний вхід
        //                        для інверсного входу 0 - це активний вхід, а 1 - це пасивний вхід
          state_inputs &=  ~maska;
          state_inputs |=   state_2;
      }
        
      //У будь-якому випадк, чи змінився стан входу, чи ні, а оскілька таймер допуску дотактував до кінця, то скидаємотаймер у висхідне від'ємне занчення
      global_timers[INDEX_TIMER_INPUT_START + i] = -1;
    }
  }
  /***************************/
  
  /***************************/
  //Визначаємо, який сигнал є зараз активним
  /***************************/
  active_inputs = (state_inputs ^ current_settings_prt.type_of_input);
  /***************************/
  
}
/*****************************************************/

/*****************************************************/
//Функція обробки таймерів
/*****************************************************/
inline void clocking_global_timers(void)
{
  //Опрацьовуємо дискретні входи
  input_scan();
  
  //опрацьовуємо всі решта таймери логіки
  for (unsigned int i = (INDEX_TIMER_INPUT_START + NUMBER_INPUTS); i < MAX_NUMBER_GLOBAL_TIMERS; i++)
  {
    if (global_timers[i] >= 0)
    {
      int max_value = 0;
      //Першою умовою того, що таймер треба тактувати є той факт, що величина таймеру не від'ємна
      switch (i)
      {
        //У цьому блоці треба величині max_value встановити значення максимального значення таймеру до якого має йти тактування
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
          max_value =  1;  /*1 мс*/
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

      //Перевіряємо чи треба збільшувати величину таймеру, якщо він ще не досягнув свого максимуму
      if (global_timers[i] < max_value) global_timers[i] += DELTA_TIME_FOR_TIMERS;
    }
  }
      
}
/*****************************************************/

/*****************************************************/
//Опрацювання Ориділювальних функцій - має запускатися після відкрпацювання блоків всіх захистів
/*****************************************************/
inline void df_handler(unsigned int *activated_functions, unsigned int *previous_stats_signals)
{
  /*
  Джерела активації формуємо в source_activation_df
  Формуємо маску вже активних функцій у maska_active_df
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
        //Теоретично цього ніколи не мало б бути
        total_error_sw_fixed(43);
        break;
      }
    }

    /***
    Джерело активації ОФ-ії
    ***/
    source_activation_df |= ((activated_functions[number_byte_in] & (1 << number_bit_in) ) >> number_bit_in ) << i;
    //Перевіряємо ще, чи не іде утимування активним джерела ОФ через таймер-утримування (для активації через кнопки або інтерфейс)
    if (global_timers[INDEX_TIMER_DF_PROLONG_SET_FOR_BUTTON_INTERFACE_START + i] >= 0)
    {
      //Таймер запущений, або вже зупинився
      //Факт запуску цього таймеру означає, що активація відбувалася через кнопку, або інтерфейс
      //Тому для забеспечення роботи логічної схеми до кінця роботи цього таймеру виставляємо, що джерело активації активне
      source_activation_df |= (1 << i);
      
      //Відмічаємо, джерело активації утримуємться у активному стані у масиві активуючих функцій
      activated_functions[number_byte_in] |= (1 << number_bit_in);
      
      //У випадку, якщо таймер дійшов до свого макисального значення, то скидаємо роботу цього таймеру
      if (global_timers[INDEX_TIMER_DF_PROLONG_SET_FOR_BUTTON_INTERFACE_START + i] >= ((int)current_settings_prt.timeout_pause_df[i]))
        global_timers[INDEX_TIMER_DF_PROLONG_SET_FOR_BUTTON_INTERFACE_START + i] = -1;
    }
    /***/

    /***
    Формування маски до цього часу активних ОФ-ій
    ***/
    maska_active_df[number_byte_out] |= ((state_df & (1 << i)) >> i) << number_bit_out;
    /***/
  }
  
  //Визначаємо, чи активовуються опреділювані функції через свої ранжовані функції-джерела
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
      //Випадок, якщо функції зранжовані на джерело прямих функцій
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
      //Випадок, якщо функції зранжовані на джерело інверсних функцій
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
      //Випадок, якщо функції зранжовані насправді на джерело блокування
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
    
    //Запускаємо у роботу лоргічну хему роботи опреділюваної функції
    switch (etap_execution_df[i])
    {
    case NONE_DF:
      {
        if ((source_activation_df & (1<<i)) != 0)
        {
           if (current_settings_prt.timeout_pause_df[i] > 0)
           {
             //Випадок, коли є перед активацією ОФ, треба витримати таймер павзи
             //Запускаємо відраховування таймера паузи
             global_timers[INDEX_TIMER_DF_PAUSE_START + i] = 0;
             //Змінюємо етап виконання логічної схеми на очікування завершення часу павзи
             etap_execution_df[i] = START_TIMER_PAUSE_DF;
           }
           else
           {
             //Випадок, коли таймер павзи рівний нулю, тобто треба зразу активовувати ОФ і запускати таймер роботи

             if (
                 (current_settings_prt.timeout_work_df[i] > 0) ||
                 ((current_settings_prt.type_df & (1<<i)) != 0)
                )   
             {
               //Встановлюємо стан даної ОФ в "АКТИВНИЙ"
               state_df |= (1 << i);
               //Запускаємо відраховування таймера роботи
               global_timers[INDEX_TIMER_DF_WORK_START + i] = 0;
               //Переходимо на відраховування таймеру роботи - протягом цього часу ОФ гарантовано активується (якщо немає умови блокування)
               etap_execution_df[i] = EXECUTION_DF;
             }
             else etap_execution_df[i] = WAITING_DEACTIVATION_SOURCE_DF;
           }
        }
        break;
      }
    case START_TIMER_PAUSE_DF:
      {
        //Зараз іде відлік часу таймеру павзи
        //Перевіряємо, чи ОФ ще утимується в стані активації через своє джерело
        if ((source_activation_df & (1<< i)) != 0)
        {
          //Перевіряємо, чи завершилася робота таймеру павзи
          if (global_timers[INDEX_TIMER_DF_PAUSE_START + i] >= ((int)current_settings_prt.timeout_pause_df[i]))
          {
            //Завершився час роботи таймеру павзи
            global_timers[INDEX_TIMER_DF_PAUSE_START + i] = -1;
  
            if (
                (current_settings_prt.timeout_work_df[i] > 0) ||
                ((current_settings_prt.type_df & (1<<i)) != 0)
               )   
            {
              //Встановлюємо стан даної ОФ в "АКТИВНИЙ"
              state_df |= (1 << i);
              //Запускаємо відраховування таймера роботи
              global_timers[INDEX_TIMER_DF_WORK_START + i] = 0;
              //Переходимо на відраховування таймеру роботи - протягом цього часу ОФ гарантовано активується (якщо немає умови блокування)
              etap_execution_df[i] = EXECUTION_DF;
            }
            else etap_execution_df[i] = WAITING_DEACTIVATION_SOURCE_DF;
          }
        }
        else
        {
          //Активація знята до завершення роботи таймеру павзи, тому скидаємо всю роботу по даній оприділюваеній функції
          global_timers[INDEX_TIMER_DF_PAUSE_START + i] = -1;
          etap_execution_df[i] = NONE_DF;
        }
        break;
      }
    case EXECUTION_DF:
      {
        //Подальша робота даної ОФ залежить від типу ОФ
        if ((current_settings_prt.type_df & (1<<i)) != 0)
        {
          //Дана ОФ ЗВОРОТНЯ
          //Згідно логічної схеми утримуємо ОФ таймер роботи має запуститися після деактивації джерела
          if ((source_activation_df & (1<< i)) != 0)
          {
            //Джерело ще є активне, а тому таймер роботи утримуємо у нульовому значенні
            global_timers[INDEX_TIMER_DF_WORK_START + i] = 0;
          }
        }

        //Перевіряємо, чи завершилася робота таймеру роботи
        /*
        Умовою продовження активації ОФ є випадок коли ОФ зворотня і джерело є активним
        Впринципі на рівні таймеру все б мало працювати правильно, але є один нюанс, коли
        функція є звороньою і джерело активне, то код вище скине таймер роботи в 0, 
        тобто він буде гарантовано в 0, але коли уставка "Таймер роботи" для даної функції буде 0,
        то по аналізу самого таймеру робота функції може зупинитися, що не правильно.
        Тому тут ще я добавляю перевірку, що ОФ не може деактивуватися навіть коли таймер роботи
        перевищує свою уставку у випадку коли і ОФ є зворотньою і джерело є активним
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
          //Завершився час роботи таймеру роботи
          global_timers[INDEX_TIMER_DF_WORK_START + i] = -1;
          //Переводимо ОФ у ПАСИВНИЙ стан
          state_df &= ~(1 << i);
          
          //Перевіряємо, чи нам треба перейти в очікування деактивації джерела ОФ, чи перейти у висхідний стан
          if ((source_activation_df & (1<< i)) == 0)
          {
            //Переходимо у режим висхідний стан
            etap_execution_df[i] = NONE_DF;
          }
          else 
          {
            //Якщо джерело запуску цієї ОФ ще активне, то переходимо на оцікування його завершення
            etap_execution_df[i] = WAITING_DEACTIVATION_SOURCE_DF;
          }
        }
        break;
      }
    case WAITING_DEACTIVATION_SOURCE_DF:
      {
        //У цьому режимі ми перебуваємо доти, поки джерело активації ОФ не буде зняте
        if ((source_activation_df & (1 << i)) == 0)
        {
          //Переходимо у режим висхідний стан
          etap_execution_df[i] = NONE_DF;
        }
        break;
      }
    default: break;
    }
  }

  //Установлюємо, або скидаємо ОФ у масиві функцій, які зараз будуть активовуватися
  /*
  Цей цикл і попередній не об'єднаі в один, а навпаки розєднані, бо у першому ми використовуємо
  масив activated_functions у якому ще не встановлені виходи ОФ-ій, тому що інші ОФ-ії
  можуть бути джерелом активації, але джерелом активації може буте попереднє значення ОФ, а не те,
  що зараз встановлюється. А оскілдьки у другому масиві ми встановлюємо значення у масиві
  activated_functions, які набувають зараз тільки ваги, то щоб не вийшло об'єднання попереднього значення
  і теперішнього то цикли роз'єднані (цикл аналізу джерел і логіки з циклом активації/деактивації)
  */
  for (unsigned int i = 0; i < NUMBER_DEFINED_FUNCTIONS; i++)
  {
    //Установлюємо, або скидаємо ОФ
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
        //Теоретично цього ніколи не мало б бути
        total_error_sw_fixed(44);
        break;
      }
    }
      
    if ((state_df & (1 << i)) != 0 )
    {
      /*
      ОФ функція зараз є активною
      але перед тим, як виставити реальний стан цієї функції на даний момент часу - 
      перевіряєио, чи не йде блокування її 
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
//Опрацювання Ориділювальних триґерів - має запускатися після відкрпацювання опреділювальних функцій
/*****************************************************/
inline void dt_handler(unsigned int *activated_functions, unsigned int *previous_stats_signals)
{
  /*
  Попередній стан визначуваних триґерів формуємо у state_defined_triggers
  Джерела встановлення формуємо в source_set_dt
  Джерела скидання формуємо в source_reset_dt
  Формуємо маску вже активних функцій у maska_active_dt
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
        //Теоретично цього ніколи не мало б бути
        total_error_sw_fixed(55);
        break;
      }
    }

    state_defined_triggers |= ( (active_functions[index_dt >> 5] & ( 1 << (index_dt & 0x1f) ) ) >> (index_dt & 0x1f) ) << i;
    /***
    Джерела встановлення і скидання ОТ
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
  
  //Визначаємо, чи встановлюються/скидаються опреділювані триґери через свої ранжовані функції-джерела
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
      //Випадок, якщо функції зранжовані на джерело прямих функцій
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
      //Випадок, якщо функції зранжовані на джерело інверсних функцій
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
      //Випадок, якщо функції зранжовані на джерело прямих функцій
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
      //Випадок, якщо функції зранжовані на джерело інверсних функцій
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

    //Запускаємо у роботу лоргічну схему роботи опреділюваного триґера (встановлення має пріоритет)
    if ((source_set_dt   & (1 << i)) != 0) state_defined_triggers |= (1 << i);
    if ((source_reset_dt & (1 << i)) != 0) state_defined_triggers &= (unsigned int)(~(1 << i));
  }

  //Установлюємо, або скидаємо ОТ у масиві функцій, які зараз будуть активовуватися
  /*
  Цей цикл і попередній не об'єднаі в один, а навпаки розєднані, бо у першому ми використовуємо
  масив activated_functions у якому ще не встановлені виходи ОТ-ій, тому що інші ОТ-ії
  можуть бути джерелом встановлення/скидання, але джерелом встановлення/скидання може буте попереднє значення ОТ, а не те,
  що зараз встановлюється. А оскілдьки у другому масиві ми встановлюємо значення у масиві
  activated_functions, які набувають зараз тільки ваги, то щоб не вийшло об'єднання попереднього значення
  і теперішнього то цикли роз'єднані (цикл аналізу джерел і логіки з циклом встановлення/скидання)
  */
  for (unsigned int i = 0; i < NUMBER_DEFINED_TRIGGERS; i++)
  {
    //Установлюємо, або скидаємо ОТ
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
        //Теоретично цього ніколи не мало б бути
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
//Вираховування часової витримки  для залежної МТЗ2 (універсальна формула)
/*
-------------------------------------------------
Т(c) = K*Tу/( ((I/Iу)^alpha) - 1 )
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
            //Теоретично цього ніколи не мало б бути
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
          //Теоретично цього ніколи не мало б бути
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
            //Теоретично цього ніколи не мало б бути
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
          //Теоретично цього ніколи не мало б бути
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
// МТЗ
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
  
  /******Неисправность цепей напряжения для 4-х ступеней*******/
  _Bool ctr_mtz_nespr_kil_napr = (current_settings_prt.control_mtz & CTR_MTZ_NESPR_KIL_NAPR) != 0; //Неиспр. Напр. Вкл. (М)
  
  //ПО Iнцн
  po_i_ncn_setpoint = previous_state_mtz_po_incn ?
            i_nom_const * KOEF_POVERNENNJA_MTZ_I_DOWN / 100 :
            i_nom_const;
  
  previous_state_mtz_po_incn = ((measurement[IM_IA] <= po_i_ncn_setpoint)   &&
                                (measurement[IM_IB_r] <= po_i_ncn_setpoint) &&
                                (measurement[IM_IC] <= po_i_ncn_setpoint));
  
  //ПО Uнцн
  po_u_ncn_setpoint = previous_state_mtz_po_uncn ?
            u_linear_nom_const * U_DOWN / 100 :
            u_linear_nom_const;
  
  previous_state_mtz_po_uncn = ((measurement[IM_UAB] <= po_u_ncn_setpoint) ||
                                (measurement[IM_UBC] <= po_u_ncn_setpoint) ||
                                (measurement[IM_UCA] <= po_u_ncn_setpoint));
  
  ctr_mtz_nespr_kil_napr = ctr_mtz_nespr_kil_napr && previous_state_mtz_po_incn && previous_state_mtz_po_uncn; //Неисправность цепей напряжения (_AND3)
  
  //Неисправность цепей напряжения
  if (ctr_mtz_nespr_kil_napr) {
    _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_NCN_MTZ);
  }
  /******Неисправность цепей напряжения для 4-х ступеней*******/
  
  /******ПО U блок. МТЗНх***********************/
  //Уставка ПО U блок. МТЗНх з врахуванням гістерезису
  unsigned int po_block_u_mtzn_x_setpoint = (_CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_PO_BLOCK_U_MTZN) == 0) ? PORIG_CHUTLYVOSTI_VOLTAGE : PORIG_CHUTLYVOSTI_VOLTAGE * U_DOWN / 100;
  
  //ПО U блок. МТЗНх
  if (
      (measurement[IM_UAB] <= po_block_u_mtzn_x_setpoint) ||
      (measurement[IM_UBC] <= po_block_u_mtzn_x_setpoint) ||
      (measurement[IM_UCA] <= po_block_u_mtzn_x_setpoint)
     )
  {
    _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_BLOCK_U_MTZN);
  }
  /******ПО U блок. МТЗНх***********************/

  for (int mtz_level = 0; mtz_level < NUMBER_LEVEL_MTZ; mtz_level++) {
    //Для отладки
//    if (mtz_level == 0) {
//      mtz_level = 0;
//    } else if (mtz_level == 1) {
//      mtz_level = 1;
//    } else if (mtz_level == 2) {
//      mtz_level = 2;
//    } else if (mtz_level == 3) {
//      mtz_level = 3;
//    }
    
    //М
    /*Проверяем тип МТЗ*/
    tmp_value = (*type_mtz_arr[mtz_level] == 1)                                  << 0; //Направленная
    tmp_value |= (*type_mtz_arr[mtz_level] == 2)                                 << 1; //С пуском
    tmp_value |= (*type_mtz_arr[mtz_level] == 0)                                 << 2; //Простая
    tmp_value |= (
                  (mtz_level == 1)
                  && (*type_mtz_arr[mtz_level] >= TYPE_MTZ_DEPENDENT_A)
                  && (*type_mtz_arr[mtz_level] <= TYPE_MTZ_DEPENDENT_RTV_I) 
                 )                                                               << 3; //Зависимая (если mtz_level == 1 (2-я ступень МТЗ))
    
    /******ПО МТЗх***********************/
    //Уставка ПО МТЗх с учетом гистерезиса
    po_mtz_x = (_CHECK_SET_BIT(active_functions, mtz_settings_prt[mtz_level][RANG_OUTPUT_LED_DF_REG_PO_MTZ]) != 0) ?
            *(setpoint_mtz[mtz_level] + number_group_stp) * KOEF_POVERNENNJA_MTZ_I_UP / 100 :
            *(setpoint_mtz[mtz_level] + number_group_stp);
    
    tmp_value |= ((measurement[IM_IA] >= po_mtz_x) ||
          (measurement[IM_IB_r] >= po_mtz_x) ||
          (measurement[IM_IC] >= po_mtz_x)) << 4; //ПО МТЗх
    /******ПО МТЗх***********************/
    
    //М
    tmp_value |= ((current_settings_prt.control_mtz & mtz_const_menu_settings_prt[mtz_level][CTR_MTZ]) != 0) << 5; //МТЗх Вкл.
    //ДВ
    tmp_value |= (_CHECK_SET_BIT(activated_functions, mtz_settings_prt[mtz_level][RANG_OUTPUT_LED_DF_REG_BLOCK_MTZ]) == 0) << 6; //Блокировка МТЗх
    //М
    tmp_value |= ((current_settings_prt.control_mtz & mtz_const_menu_settings_prt[mtz_level][CTR_MTZ_VPERED]) != 0) << 7; //МТЗНх: Вкл. прям
    tmp_value |= ((current_settings_prt.control_mtz & mtz_const_menu_settings_prt[mtz_level][CTR_MTZ_NAZAD]) != 0) << 8; //МТЗНх: Вкл. обр
    
    /******Сектор МТЗНх Вперед/Назад**********/
    //Проверка направленности фаз А,В,С
    direction_ABC_tmp = (sector_directional_mtz[mtz_level][PHASE_A_INDEX] == MTZ_VPERED) << 0; //Проверка направленности фазы А вперед
    direction_ABC_tmp |= (sector_directional_mtz[mtz_level][PHASE_B_INDEX] == MTZ_VPERED) << 1; //Проверка направленности фазы B вперед
    direction_ABC_tmp |= (sector_directional_mtz[mtz_level][PHASE_C_INDEX] == MTZ_VPERED) << 2; //Проверка направленности фазы C вперед
    
    _OR3(direction_ABC_tmp, 0, direction_ABC_tmp, 1, direction_ABC_tmp, 2, direction_ABC_tmp, 3);
    
    //Сектор МТЗНх Вперед
    if (_GET_OUTPUT_STATE(direction_ABC_tmp, 3)) {
      _SET_BIT(activated_functions, mtz_settings_prt[mtz_level][RANG_OUTPUT_LED_DF_REG_SECTOR_VPERED_MTZN]);
    }
    
    direction_ABC_tmp |= (sector_directional_mtz[mtz_level][PHASE_A_INDEX] == MTZ_NAZAD) << 4; //Проверка направленности фазы А назад
    direction_ABC_tmp |= (sector_directional_mtz[mtz_level][PHASE_B_INDEX] == MTZ_NAZAD) << 5; //Проверка направленности фазы B назад
    direction_ABC_tmp |= (sector_directional_mtz[mtz_level][PHASE_C_INDEX] == MTZ_NAZAD) << 6; //Проверка направленности фазы C назад
    
    _OR3(direction_ABC_tmp, 4, direction_ABC_tmp, 5, direction_ABC_tmp, 6, direction_ABC_tmp, 7);
    
    //Сектор МТЗНх Назад
    if (_GET_OUTPUT_STATE(direction_ABC_tmp, 7)) {
      _SET_BIT(activated_functions, mtz_settings_prt[mtz_level][RANG_OUTPUT_LED_DF_REG_SECTOR_NAZAD_MTZN]);
    }
    
    //Уставка ПО МТЗН1 прям. с учетом гистерезиса
    po_mtzn_x_vpered_setpoint = (_CHECK_SET_BIT(active_functions, mtz_settings_prt[mtz_level][RANG_OUTPUT_LED_DF_REG_PO_MTZN_VPERED]) != 0) ?
            *(setpoint_mtz_n_vpered[mtz_level] + number_group_stp) * KOEF_POVERNENNJA_MTZ_I_UP / 100 :
            *(setpoint_mtz_n_vpered[mtz_level] + number_group_stp);
    
    direction_ABC_tmp |= (measurement[IM_IA] >= po_mtzn_x_vpered_setpoint) << 8; //Сравниваем с уставкой тока по фазе А (вперед)
    direction_ABC_tmp |= (measurement[IM_IB_r] >= po_mtzn_x_vpered_setpoint) << 9; //Сравниваем с уставкой тока по фазе B (вперед)
    direction_ABC_tmp |= (measurement[IM_IC] >= po_mtzn_x_vpered_setpoint) << 10; //Сравниваем с уставкой тока по фазе C (вперед)
    
    //Уставка ПО МТЗН1 прям. с учетом гистерезиса
    po_mtzn_x_nazad_setpoint = (_CHECK_SET_BIT(active_functions, mtz_settings_prt[mtz_level][RANG_OUTPUT_LED_DF_REG_PO_MTZN_NAZAD]) != 0) ?
            *(setpoint_mtz_n_nazad[mtz_level] + number_group_stp) * KOEF_POVERNENNJA_MTZ_I_UP / 100 :
            *(setpoint_mtz_n_nazad[mtz_level] + number_group_stp);
    
    direction_ABC_tmp |= (measurement[IM_IA] >= po_mtzn_x_nazad_setpoint) << 11; //Сравниваем с уставкой тока по фазе А (назад)
    direction_ABC_tmp |= (measurement[IM_IB_r] >= po_mtzn_x_nazad_setpoint) << 12; //Сравниваем с уставкой тока по фазе B (назад)
    direction_ABC_tmp |= (measurement[IM_IC] >= po_mtzn_x_nazad_setpoint) << 13; //Сравниваем с уставкой тока по фазе C (назад)
    
    _AND2(direction_ABC_tmp, 8, direction_ABC_tmp, 0, direction_ABC_tmp, 14);
    _AND2(direction_ABC_tmp, 9, direction_ABC_tmp, 1, direction_ABC_tmp, 15);
    _AND2(direction_ABC_tmp, 10, direction_ABC_tmp, 2, direction_ABC_tmp, 16);
    
    _AND2(direction_ABC_tmp, 11, direction_ABC_tmp, 4, direction_ABC_tmp, 17);
    _AND2(direction_ABC_tmp, 12, direction_ABC_tmp, 5, direction_ABC_tmp, 18);
    _AND2(direction_ABC_tmp, 13, direction_ABC_tmp, 6, direction_ABC_tmp, 19);
    
    _OR3(direction_ABC_tmp, 14, direction_ABC_tmp, 15, direction_ABC_tmp, 16, tmp_value, 12);
    _OR3(direction_ABC_tmp, 17, direction_ABC_tmp, 18, direction_ABC_tmp, 19, tmp_value, 13);
    /******Сектор МТЗНх Вперед/Назад**********/
    
//    /******ПО U блок. МТЗНх***********************/
//    //Уставка ПО U блок. МТЗНх с учетом гистерезиса
//    po_block_u_mtzn_x_setpoint = (_CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_PO_BLOCK_U_MTZN) != 0) ?
//           PORIG_CHUTLYVOSTI_VOLTAGE :
//           PORIG_CHUTLYVOSTI_VOLTAGE * U_DOWN / 100;
//    
//    tmp_value |= ((measurement[IM_UAB] <= po_block_u_mtzn_x_setpoint) ||
//                  (measurement[IM_UBC] <= po_block_u_mtzn_x_setpoint) ||
//                  (measurement[IM_UCA] <= po_block_u_mtzn_x_setpoint)) << 14; //ПО U блок. МТЗНх
//    
//    //ПО U блок. МТЗНх
//    if (_GET_OUTPUT_STATE(tmp_value, 14)) {
//      _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_BLOCK_U_MTZN);
//    }
//    /******ПО U блок. МТЗНх***********************/
    tmp_value |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_BLOCK_U_MTZN) != 0) << 14;
    
    //Неисправность цепей напряжения для ступени МТЗх
    tmp_value |= (
                   !(_CHECK_SET_BIT(active_functions, mtz_settings_prt[mtz_level][RANG_OUTPUT_LED_DF_REG_PO_MTZN_VPERED]) != 0 ||
                     _CHECK_SET_BIT(active_functions, mtz_settings_prt[mtz_level][RANG_OUTPUT_LED_DF_REG_PO_MTZN_NAZAD])  != 0 ||
                     _CHECK_SET_BIT(active_functions, mtz_settings_prt[mtz_level][RANG_OUTPUT_LED_DF_REG_PO_MTZPN])     != 0)
                   &&
                   ctr_mtz_nespr_kil_napr
                 ) << 15;
    
    /******ПО U МТЗПНх***********************/
    po_u_mtzpn_x_setpoint = (_CHECK_SET_BIT(active_functions, mtz_settings_prt[mtz_level][RANG_OUTPUT_LED_DF_REG_PO_U_MTZPN]) != 0) ?
            *(setpoint_mtz_U[mtz_level] + number_group_stp) * U_DOWN / 100:
            *(setpoint_mtz_U[mtz_level] + number_group_stp) ;
    
    tmp_value |= ((measurement[IM_UAB] <= po_u_mtzpn_x_setpoint) ||
                  (measurement[IM_UBC] <= po_u_mtzpn_x_setpoint) ||
                  (measurement[IM_UCA] <= po_u_mtzpn_x_setpoint)) << 16; //ПО U МТЗПНх
    
    //ПО U МТЗПНх
    if (_GET_OUTPUT_STATE(tmp_value, 16)) {
      _SET_BIT(activated_functions, mtz_settings_prt[mtz_level][RANG_OUTPUT_LED_DF_REG_PO_U_MTZPN]);
    }
    /******ПО U МТЗПНх***********************/
    
    /******ПО МТЗПНх***********************/
    po_mtzpn_x_setpoint = (_CHECK_SET_BIT(active_functions, mtz_settings_prt[mtz_level][RANG_OUTPUT_LED_DF_REG_PO_MTZPN]) != 0) ?
            *(setpoint_mtz_po_napruzi[mtz_level] + number_group_stp) * KOEF_POVERNENNJA_MTZ_I_UP / 100:
            *(setpoint_mtz_po_napruzi[mtz_level] + number_group_stp);
    
    tmp_value |= ((measurement[IM_IA] >= po_mtzpn_x_setpoint)   ||
                  (measurement[IM_IB_r] >= po_mtzpn_x_setpoint) ||
                  (measurement[IM_IC] >= po_mtzpn_x_setpoint)) << 17; //ПО МТЗПНх
    /******ПО МТЗПНх***********************/
    
    if (mtz_level == 1) { //только для 2-ой ступени
      //ДВ
      tmp_value |= (_CHECK_SET_BIT(activated_functions, mtz_settings_prt[mtz_level][RANG_OUTPUT_LED_DF_REG_BLOCK_USK_MTZ]) == 0) << 9; //Блокировка ускорения МТЗ 2
      //М
      tmp_value |= ((current_settings_prt.control_mtz & CTR_MTZ_2_PRYSKORENA) != 0) << 10; //МТЗ2 Ускоренная
      //ДВ
      tmp_value |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_STATE_VV) != 0) << 18; //Положение ВВ
      //M
      tmp_value |= ((current_settings_prt.control_mtz & CTR_MTZ_2_PRYSKORENNJA) != 0) << 11; //Ускорение МТЗ2 вкл.
    }
    
    if (_GET_OUTPUT_STATE(tmp_value, 15)) { //Если зафиксирована неисправность цепей напряжения для ступени МТЗх
      _CLEAR_STATE(tmp_value, 16); //Очистка ПО U МТЗПНх
    }
    
    _OR2_INVERTOR(tmp_value, 14, tmp_value, 15, tmp_value, 14);
    
    if (_CHECK_SET_BIT(active_functions, mtz_settings_prt[mtz_level][RANG_OUTPUT_LED_DF_REG_PO_MTZ]) != 0) {
      _SET_STATE(tmp_value, 19);
    } else {
      if (mtz_level == 1) {
        //только для 2-ой ступени при формировании 19-го сигнала будет учитываться
        //сигнал "Зависимая" (tmp_value 3)
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
    
    //ПО МТЗх
    _AND3(tmp_value, 19, tmp_value, 4, tmp_value, 20, tmp_value, 21);
    if (_GET_OUTPUT_STATE(tmp_value, 21)) {
      _SET_BIT(activated_functions, mtz_settings_prt[mtz_level][RANG_OUTPUT_LED_DF_REG_PO_MTZ]);
    }
    
    //ПО МТЗНх вперед
    _AND5(tmp_value, 0, tmp_value, 20, tmp_value, 7, tmp_value, 12, tmp_value, 14, tmp_value, 22);
    if (_GET_OUTPUT_STATE(tmp_value, 22)) {
      _SET_BIT(activated_functions, mtz_settings_prt[mtz_level][RANG_OUTPUT_LED_DF_REG_PO_MTZN_VPERED]);
    }
    
    //ПО МТЗНх назад
    _AND5(tmp_value, 0, tmp_value, 20, tmp_value, 8, tmp_value, 13, tmp_value, 14, tmp_value, 23);
    if (_GET_OUTPUT_STATE(tmp_value, 23)) {
      _SET_BIT(activated_functions, mtz_settings_prt[mtz_level][RANG_OUTPUT_LED_DF_REG_PO_MTZN_NAZAD]);
    }
    
    //ПО МТЗПНх
    _AND4(tmp_value, 1, tmp_value, 20, tmp_value, 16, tmp_value, 17, tmp_value, 24);
    if (_GET_OUTPUT_STATE(tmp_value, 24)) {
      _SET_BIT(activated_functions, mtz_settings_prt[mtz_level][RANG_OUTPUT_LED_DF_REG_PO_MTZPN]);
    }
    
    if (mtz_level != 1) { //для всех ступеней кроме 2-ой
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
      _INVERTOR(tmp_value, 3, tmp, 23); /*Добавлено Тарасом у Богданову програму*/
      _AND3(tmp, 4, tmp_value, 3, tmp_value, 21, tmp, 5);
      _AND2(tmp, 3, tmp_value, 21, tmp, 6);
      _AND3(tmp, 4, tmp_value, 21, tmp, 23, tmp, 7); /*Модифіковано Тарасом у Богдановій програмі*/
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
    
    //Сраб.МТЗх
    if (_GET_OUTPUT_STATE(tmp_value, 31)) {
      _SET_BIT(activated_functions, mtz_settings_prt[mtz_level][RANG_OUTPUT_LED_DF_REG_MTZ]);
    }
  }
}
/*****************************************************/

/*****************************************************/
// ЗДЗ
/*****************************************************/
inline void zdz_handler(unsigned int *activated_functions)
{
  unsigned int tmp_value;
  //M
  tmp_value = ((current_settings_prt.control_zdz & CTR_ZDZ_STARTED_FROM_MTZ1) != 0) << 0; //Пуск от МТЗ1 : Вкл/Откл
  tmp_value |= ((current_settings_prt.control_zdz & CTR_ZDZ_STARTED_FROM_MTZ2) != 0) << 1; //Пуск от МТЗ2 : Вкл/Откл
  tmp_value |= ((current_settings_prt.control_zdz & CTR_ZDZ_STARTED_FROM_MTZ3) != 0) << 2; //Пуск от МТЗ3 : Вкл/Откл
  tmp_value |= ((current_settings_prt.control_zdz & CTR_ZDZ_STARTED_FROM_MTZ4) != 0) << 3; //Пуск от МТЗ4 : Вкл/Откл
  
  for (int mtz_level = 0; mtz_level < NUMBER_LEVEL_MTZ; mtz_level++) {
    //берем не из active потому что сигналы сформировались на предыдущем шаге mtz_handler()
    tmp_value |= (_CHECK_SET_BIT(activated_functions, mtz_settings_prt[mtz_level][RANG_OUTPUT_LED_DF_REG_PO_MTZ]) != 0) << (4 + mtz_level); //ПО МТЗx
    tmp_value |= (_CHECK_SET_BIT(activated_functions, mtz_settings_prt[mtz_level][RANG_OUTPUT_LED_DF_REG_PO_MTZN_VPERED]) != 0) << (8 + mtz_level); //ПО МТЗНх вперед
    tmp_value |= (_CHECK_SET_BIT(activated_functions, mtz_settings_prt[mtz_level][RANG_OUTPUT_LED_DF_REG_PO_MTZN_NAZAD]) != 0) << (12 + mtz_level);  //ПО МТЗНх назад
    tmp_value |= (_CHECK_SET_BIT(activated_functions, mtz_settings_prt[mtz_level][RANG_OUTPUT_LED_DF_REG_PO_MTZPN]) != 0) << (16 + mtz_level); //ПО МТЗПНх
  }
  //М
  tmp_value |= ((current_settings_prt.control_zdz & CTR_ZDZ_STATE) != 0) << 20;
  //ДВ
  tmp_value |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PUSK_ZDZ_VID_DV) != 0) << 21; //Пуск ЗДЗ от ДВ
  
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
  
  //Сраб. ЗДЗ
  if (_GET_OUTPUT_STATE(tmp_value2, 3)) {
    _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_ZDZ);
  }
}
/*****************************************************/

/*****************************************************/
// ЗЗ
/*****************************************************/
inline void zz_handler(unsigned int *activated_functions, unsigned int number_group_stp)
{
  /********************************
  Сектор НЗЗ

  "Сектор НЗЗ" визначається при порогах:
  
  Струм 3I0 (вимірюється у десятих міліамперів) > 5 (мА)
  Струм 3U0 (вимірюється у         мілівольтах) > 6 (В)
  
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
      //Працюємо по сектору спрацювання для НЗЗ
      sector_i_minus_u = sector_i_minus_u_1;
    }
    else
    {
      //Працюємо по сектору відпускання для НЗЗ
      sector_i_minus_u = sector_i_minus_u_2;
    }
  
    if ((current_settings_prt.control_zz & CTR_ZZ1_SECTOR) != 0)
    {
      //Працюємо по сектору "ВПЕРЕД" (квадранти 1 і 2 без "сірої області")
      if ((sector_i_minus_u == 1) || (sector_i_minus_u == 2))
      {
        /*
        Будь-яке ненульове значення означає, що ми в секторі спрацювання
        */
        sector_NZZ = 0xff;
      }
      else
      {
        /*
        Нульове значення означає, що ми не в секторі спрацювання
        */
        sector_NZZ = 0;
      }
    }
    else
    {
      //Працюємо по сектору "НАЗАД" (квадранти 3 і 4 без "сірої області")
      if ((sector_i_minus_u == 3) || (sector_i_minus_u == 4))
      {
        /*
        Будь-яке ненульове значення означає, що ми в секторі спрацювання
        */
        sector_NZZ = 0xff;
      }
      else
      {
        /*
        Нульове значення означає, що ми не в секторі спрацювання
        */
        sector_NZZ = 0;
      }
    }
  
    //Встановлюємо сигнал "Сектор НЗЗ",якщо він потрібний - у іншому випадку він скинутий
    if (sector_NZZ != 0)
      _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_SECTOR_NZZ);
  }
  else sector_NZZ = 0;
  /*******************************/

  /*******************************/
  //Визначаємо по якому вимірюванню будемо аналізувати і який коефіцієнт повернення
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
  ПО 3I0 (на рівні вимірювальної величини, уставкм спрацювання/відпускання)
  ********************************/
  /*
  Оскільки вимірювання у нас з точністю до десятих міліампер, а уставка у нас у міліамперах,
  то множимо устаку на 10, щоб отримати її також у десятих міліамперів
  */
  if (po_3I0 == 0)
  {
    //Працюємо по уставці спрацювання для 3I0
    setpoint = current_settings_prt.setpoint_zz_3I0[number_group_stp]*10;
  }
  else
  {
    //Працюємо по уставці відпускання для 3I0
    /*
    Алгебраїчне спрощення виразу
    setpoint = (current_settings_prt.setpoint_zz_3I0[number_group_stp]*koef_povernennja/100)*10 =  current_settings_prt.setpoint_zz_3I0[number_group_stp]*koef_povernennja/10
    */
    setpoint = current_settings_prt.setpoint_zz_3I0[number_group_stp]*koef_povernennja/10;
  }
  
  if (max_3i0_current >= setpoint)
  {
    /*
    Будь-яке ненульове значення означає, що вимірюване значення вище-рівне порогу порівнювальної уставки
    */
    po_3I0 = 0xff;
  }
  else
  {
    /*
    Нульове значення означає, що вимірюване значення нижче порогу порівнювальної уставки
    */
    po_3I0 = 0;
  }
  /*******************************/

  if ((current_settings_prt.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_3U0_Ubc_TN2) == 0)
  {
    /********************************
    ПО 3U0 (на рівні вимірювальної величини, уставкм спрацювання/відпускання)
    ********************************/
    if (po_3U0 == 0)
    {
      //Працюємо по уставці спрацювання для 3U0
      setpoint = current_settings_prt.setpoint_zz_3U0[number_group_stp];
    }
    else
    {
      //Працюємо по уставці відпускання для 3U0
      setpoint = current_settings_prt.setpoint_zz_3U0[number_group_stp]*KOEF_POVERNENNJA_3U0/100;
    }
  
    if (measurement[IM_3U0_UBC_TN2] >= setpoint)
    {
      /*
      Будь-яке ненульове значення означає, що вимірюване значення вище-рівне порогу порівнювальної уставки
      */
      po_3U0 = 0xff;
    }
    else
    {
      /*
      Нульове значення означає, що вимірюване значення нижче порогу порівнювальної уставки
      */
      po_3U0 = 0;
    }
  }
  /*******************************/
  
  if (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_BLOCK_NZZ) == 0)
  {
    //НЗЗ, ЗЗ/3I0 і ЗЗ/3U0 не блокується з дискретного входу
    /*******************************/
    //НЗЗ
    /*******************************/
    if (
        ((current_settings_prt.control_zz & CTR_ZZ1_NZZ_STATE) != 0) &&
        ((current_settings_prt.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_3U0_Ubc_TN2) == 0) &&
        ((current_settings_prt.control_zz & CTR_ZZ1_TYPE) == 0)
       )   
    {
      //1 ступінь ЗЗ/3U0 включена, дозволена і не блокується
    
      //Копіюємо попередні значення сигналів ЗЗ/3U0 у тимчавовий масив, щоб потім мати можливість їх скидати або встановлювати
      //Це потрібно для того, щоб коли є умова, що сигнал не має ні встановлюватися ні скидатися - щоб він приймав своє попереднє значення  
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
    
      //Виставляємо, або скидаємо сигнал "ПО NZZ"
      if (
          (po_3I0     != 0) &&
          (po_3U0     != 0) &&
          (sector_NZZ != 0)
         )
      {
        //Існує умова роботи ПО НЗЗ
        if(previous_state_po_nzz == 0)
        {
          //Встановлюємо сигнал "ПО NZZ"
          _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_NZZ);
      
          //Запускаємо таймер НЗЗ, якщо він ще не запущений
          global_timers[INDEX_TIMER_NZZ] = 0;
        }
      }
      else 
      {
        //Не існує умова роботи ПО НЗЗ
        if(previous_state_po_nzz != 0)
        {
          //Скидаємо сигнал "ПО НЗЗ"
          _CLEAR_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_NZZ);
          //Це є умовою також скидання сигналу "Сраб. НЗЗ"
          _CLEAR_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_NZZ);
          //Якщо таймер ще не скинутий, то скидаємо його
          if ( global_timers[INDEX_TIMER_NZZ] >=0) global_timers[INDEX_TIMER_NZZ] = -1;
        }
      }
    
      if(global_timers[INDEX_TIMER_NZZ] >= current_settings_prt.timeout_nzz[number_group_stp])
      {
        //Якщо витримана "Витримка НЗЗ" то встановлюємо сигнал "Сраб. НЗЗ"
        _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_NZZ);

        //Скидаємо таймер ПО НЗЗ
        global_timers[INDEX_TIMER_NZZ] = -1;
      }
    }
    else
    {
      //Якщо НЗЗ не встановлена, то треба скинути всі таймери і сигнали, які за неї відповідають
      _CLEAR_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_NZZ);
      _CLEAR_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_NZZ);
      global_timers[INDEX_TIMER_NZZ] = -1;
    }  
    /*******************************/

    /*******************************/
    //1 ступінь ЗЗ/3U0
    /*******************************/
    if (
        ((current_settings_prt.control_zz & CTR_ZZ1_3U0_STATE) != 0) &&
        ((current_settings_prt.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_3U0_Ubc_TN2) == 0)  
       )   
    {
      //1 ступінь ЗЗ/3U0 включена і не блокується
    
      //Копіюємо попередні значення сигналів ЗЗ/3U0 у тимчавовий масив, щоб потім мати можливість їх скидати або встановлювати
      //Це потрібно для того, щоб коли є умова, що сигнал не має ні встановлюватися ні скидатися - щоб він приймав своє попереднє значення  
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
    
      //Виставляємо, або скидаємо сигнал "ПО ЗЗ/3U0"
      if (po_3U0 != 0)
      {
        //Максимальна напругу 3U0 перевищує свою уставку
        if(previous_state_po_3U0 == 0)
        {
          //Встановлюємо сигнал "ПО ЗЗ/3U0"
          _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_3U0);
        
          //Запускаємо таймер ЗЗ/3U0, якщо він ще не запущений
          global_timers[INDEX_TIMER_ZZ_3U0] = 0;
        }
      }
      else 
      {
        //Максимальна напругу 3I0 нижче уставки
        if(previous_state_po_3U0 != 0)
        {
          //Скидаємо сигнал "ПО ЗЗ/3U0"
          _CLEAR_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_3U0);
          //Це є умовою також скидання сигналу "Сраб. ЗЗ/3U0"
          _CLEAR_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_3U0);
          //Якщо таймер ще не скинутий, то скидаємо його
          if ( global_timers[INDEX_TIMER_ZZ_3U0] >=0) global_timers[INDEX_TIMER_ZZ_3U0] = -1;
        }
      }
    
      if(global_timers[INDEX_TIMER_ZZ_3U0] >= current_settings_prt.timeout_zz_3U0[number_group_stp])
      {
        //Якщо витримана "Витримка ЗЗ/3U0" то встановлюємо сигнал "Сраб. ЗЗ/3U0"
        _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_3U0);

        //Скидаємо таймер ПО ЗЗ/3U0
        global_timers[INDEX_TIMER_ZZ_3U0] = -1;
      }
    }
    else
    {
      //Якщо 1 ступінь ЗЗ/3U0 не встановлена, то треба скинути всі таймери і сигнали, які за неї відповідають
      _CLEAR_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_3U0);
      _CLEAR_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_3U0);
      global_timers[INDEX_TIMER_ZZ_3U0] = -1;
    }    
    /*******************************/
  
    /*******************************/
    //1 ступінь ЗЗ/3I0
    /*******************************/
    if ((current_settings_prt.control_zz & CTR_ZZ1_3I0_STATE) != 0)
    {
      //1 ступінь ЗЗ/3I0 включена і не блокується
    
      //Копіюємо попередні значення сигналів ЗЗ/3I0 у тимчавовий масив, щоб потім мати можливість їх скидати або встановлювати
      //Це потрібно для того, щоб коли є умова, що сигнал не має ні встановлюватися ні скидатися - щоб він приймав своє попереднє значення  
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
    
      //Виставляємо, або скидаємо сигнал "ПО ЗЗ/3I0"
      if (po_3I0 != 0)
      {
        //Максимальний стум 3I0 перевищує свою уставку
        if(previous_state_po_3I0 == 0)
        {
          //Встановлюємо сигнал "ПО ЗЗ/3I0"
          _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_3I0);
      
          //Запускаємо таймер ЗЗ/3I0, якщо він ще не запущений
          global_timers[INDEX_TIMER_ZZ_3I0] = 0;
        }
      }
      else 
      {
        //Максимальний стум 3I0 нижче уставки
        if(previous_state_po_3I0 != 0)
        {
          //Скидаємо сигнал "ПО ЗЗ/3I0"
          _CLEAR_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_3I0);
          //Це є умовою також скидання сигналу "Сраб. ЗЗ/3I0"
          _CLEAR_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_3I0);
          //Якщо таймер ще не скинутий, то скидаємо його
          if ( global_timers[INDEX_TIMER_ZZ_3I0] >=0) global_timers[INDEX_TIMER_ZZ_3I0] = -1;
        }
      }
    
      if(global_timers[INDEX_TIMER_ZZ_3I0] >= current_settings_prt.timeout_zz_3I0[number_group_stp])
      {
        //Якщо витримана "Витримка ЗЗ/3I0" то встановлюємо сигнал "Сраб. ЗЗ"
        _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_3I0);

        //Скидаємо таймер ПО ЗЗ/3I0
        global_timers[INDEX_TIMER_ZZ_3I0] = -1;
      }
    }
    else
    {
      //Якщо 1 ступінь ЗЗ/3I0 не встановлена, то треба скинути всі таймери і сигнали, які за неї відповідають
      _CLEAR_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_3I0);
      _CLEAR_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_3I0);
      global_timers[INDEX_TIMER_ZZ_3I0] = -1;
    }  
    /*******************************/
  }
  else
  {
    //Захисти ЗЗ/НЗЗ блокується з дискретного входу, то треба скинути всі таймери і сигнали, які за них відповідають
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
// ЗОП(КОФ)
/*****************************************************/
inline void zop_handler(unsigned int *activated_functions, unsigned int number_group_stp)
{
  /*******************************/
  //Фуксуємо у локальній змінній текучі струми зворотньої послідовності і прямоїпослідовності
  /*******************************/
  unsigned int i2_current = measurement[IM_I2], i1_current = measurement[IM_I1];
  /*******************************/
  
  /*******************************/
  //1 ступінь ЗОП(КОФ)
  /*******************************/
  if ((current_settings_prt.control_zop & CTR_ZOP_STATE) != 0)
  {
    //1 ступінь ЗОП(КОФ) включена
    unsigned int setpoint; //уставка - з якою зрівнюється вимірювальна величина
    unsigned int setpoint_i1, setpoint_i2;
    unsigned int previous_state_po_zop1;
    
    if (i1_bilshe_porogu == 0) setpoint_i1 = MIN_LIMIT_FOR_I1_AND_I2*KOEF_POVERNENNJA_ZOP_BLK/100;
    else setpoint_i1 = MIN_LIMIT_FOR_I1_AND_I2;
    unsigned int i1_bilshe_porogu_tmp = i1_bilshe_porogu = (i1_current >= setpoint_i1);
    
    if (i2_bilshe_porogu == 0) setpoint_i2 = MIN_LIMIT_FOR_I1_AND_I2*KOEF_POVERNENNJA_ZOP_BLK/100;
    else setpoint_i2 = MIN_LIMIT_FOR_I1_AND_I2;
    unsigned int i2_bilshe_porogu_tmp = i2_bilshe_porogu = (i2_current >= setpoint_i2);
    
    //Копіюємо попередні значення сигналів ЗОП(КОФ) у тимчавовий масив, щоб потім мати можливість їх скидати або встановлювати
    //Це потрібно для того, щоб коли є умова, що сигнал не має ні встановлюватися ні скидатися - щоб він приймав своє попереднє значення  
    unsigned int maska[N_BIG] = {0, 0, 0, 0, 0, 0};
    _SET_BIT(maska, RANG_OUTPUT_LED_DF_REG_PO_ZOP);
    _SET_BIT(maska, RANG_OUTPUT_LED_DF_REG_ZOP);
    activated_functions[0] |= active_functions[0] & maska[0];
    activated_functions[1] |= active_functions[1] & maska[1];
    activated_functions[2] |= active_functions[2] & maska[2];
    activated_functions[3] |= active_functions[3] & maska[3];
    activated_functions[4] |= active_functions[4] & maska[4];
    activated_functions[5] |= active_functions[5] & maska[5];
    
    //Якщо ПО ЗОП(КОФ) ще не активне, то треба працювати по устаці спацювання - уставці, яка вводиться як основна з системи меню чи верхнього рівня
    //Якщо ПО ЗОП(КОФ) вже спрацювало, то треба працювати по уставці відпускання - береться процент від основної утанки по коефіцієнту повернення
    if(( previous_state_po_zop1 = _CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_PO_ZOP) ) == 0 )
    {
      //Працюємо по утавці спрацювання
      setpoint = current_settings_prt.setpoint_zop[number_group_stp];
    }
    else
    {
      //Працюємо по утавці відпускання
      setpoint = current_settings_prt.setpoint_zop[number_group_stp]*KOEF_POVERNENNJA_GENERAL_UP/100;
    }
    
    //Виставляємо, або скидаємо сигнал "ПО КОФ"
    /*
    I2
    -- >= K
    I1
    оскільки величина устаки у нас є перемножена на 1000, ,бо 0,010 відповідає 10, а 1,000 відповідає 1000,
    то K*1000 = SETPOINT =>
        SETPOINT
    K = --------  =>
         1000
    I2    SETPOINT
    -- >= ---------
    I1     1000
    
    струми зворотньої і прямої послідовності не треба ні нащо перемножувати, бо вони є у однакових величинах (міліампери), а нас цікавить їх відношення
    
    (I2*1000) >= (SETPOINT*I1)
    */
    if (
        (i1_bilshe_porogu_tmp != 0) &&
        (i2_bilshe_porogu_tmp != 0) &&
        ((i2_current*1000) >= (i1_current*setpoint))                            && 
        (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_BLOCK_ZOP) == 0)
       )
    {
      //Існує умова активного пускового органу зворотньої послідовності
      if(previous_state_po_zop1 == 0)
      {
        //Встановлюємо сигнал "ПО КОФ"
        _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_ZOP);
      
        //Запускаємо таймер ЗОП(КОФ), якщо він ще не запущений
        global_timers[INDEX_TIMER_ZOP] = 0;
      }
    }
    else 
    {
      //Не існує умови активного пускового органу зворотньої послідовності
      if(previous_state_po_zop1 != 0)
      {
        //Скидаємо сигнал "ПО КОФ"
        _CLEAR_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_ZOP);
        //Це є умовою також скидання сигналу "Сраб. КОФ"
        _CLEAR_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_ZOP);
        //Якщо таймер ще не скинутий? то скидаємо його
        if ( global_timers[INDEX_TIMER_ZOP] >=0) global_timers[INDEX_TIMER_ZOP] = -1;
      }
    }
    
    if(global_timers[INDEX_TIMER_ZOP] >= current_settings_prt.timeout_zop[number_group_stp])
    {
      //Якщо витримана Витримка ЗОП(КОФ) то встановлюємо сигнал "Сраб. КОФ"
      _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_ZOP);

      //Скидаємо таймер ЗОП(КОФ)
      global_timers[INDEX_TIMER_ZOP] = -1;
    }
  }
  else
  {
    //Якщо 1 ступінь ЗОП(КОФ) не встановлена, то треба скинути всі таймери і сигнали, які за неї відповідають
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
// ЗНМИН1
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
  //М
  unsigned int tmp_value = ((current_settings_prt.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_PHASE_LINE) == 0)         << 0;
//  tmp_value |= ((current_settings_prt.control_Umin & CTR_EXTRA_SETTINGS_1_CTRL_PHASE_LINE) != 0)                                 << 1;
//  _INVERTOR(tmp_value, 1, tmp_value, 1);
  tmp_value |= ((current_settings_prt.control_Umin & CTR_UMIN1) != 0)                                                            << 2;
  tmp_value |= ((current_settings_prt.control_Umin & CTR_PO_UMIN1_OR_AND) != 0)                                                  << 3;
  tmp_value |= ((current_settings_prt.control_Umin & CTR_UMIN1_UBLK) != 0)                                                       << 4;
  tmp_value |= ((current_settings_prt.control_Umin & CTR_UMIN1_IBLK) != 0)                                                       << 5;
  
  //ДВ
  tmp_value |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_BLOCK_UMIN1) != 0)                                    << 6;
  _INVERTOR(tmp_value, 6, tmp_value, 6);
  tmp_value |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_START_UMIN1) != 0)                                    << 7;
  
//  _AND2(tmp_value, 0, tmp_value, 1, tmp_value, 8);
  
  if (_GET_OUTPUT_STATE(tmp_value, 0)) {
    //Фазные
    _AND4(Ua_is_smaller_than_Umin1, 0, Ub_is_smaller_than_Umin1, 0, Uc_is_smaller_than_Umin1, 0, tmp_value, 3, tmp_value, 9);
    _OR3(Ua_is_smaller_than_Umin1, 0, Ub_is_smaller_than_Umin1, 0, Uc_is_smaller_than_Umin1, 0, tmp_value, 10);
    _INVERTOR(tmp_value, 3, tmp_value, 3);
    _AND2(tmp_value, 10, tmp_value, 3, tmp_value, 11);
    _AND2(tmp_value, 5, Ia_and_Ic_is_smaller_than_Iust, 0, tmp_value, 12);
    _INVERTOR(tmp_value, 5, tmp_value, 5);
    _AND3(Ua_or_Ub_or_Uc_is_smaller_than_250mV, 0, tmp_value, 4, tmp_value, 5, tmp_value, 13);
    
    //ПО Uблк. Umin1
    if (Ua_or_Ub_or_Uc_is_smaller_than_250mV) {
      _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_UBLK_UMIN1);
    }
    
  } else {
    //Линейные
    _AND4(Uab_is_smaller_than_Umin1, 0, Ubc_is_smaller_than_Umin1, 0, Uca_is_smaller_than_Umin1, 0, tmp_value, 3, tmp_value, 9);
    _OR3(Uab_is_smaller_than_Umin1, 0, Ubc_is_smaller_than_Umin1, 0, Uca_is_smaller_than_Umin1, 0, tmp_value, 10);
    _INVERTOR(tmp_value, 3, tmp_value, 3);
    _AND2(tmp_value, 10, tmp_value, 3, tmp_value, 11);
    _AND2(tmp_value, 5, Ia_and_Ic_is_smaller_than_Iust, 0, tmp_value, 12);
    _INVERTOR(tmp_value, 5, tmp_value, 5);
    _AND3(Uab_or_Ubc_or_Uca_is_smaller_than_250mV, 0, tmp_value, 4, tmp_value, 5, tmp_value, 13);
    
    //ПО Uблк. Umin1
    if (Uab_or_Ubc_or_Uca_is_smaller_than_250mV) {
      _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_UBLK_UMIN1);
    }
  }
  _INVERTOR(tmp_value, 12, tmp_value, 12);
  _INVERTOR(tmp_value, 13, tmp_value, 13);
  _OR3(tmp_value, 7, tmp_value, 9, tmp_value, 11, tmp_value, 14);
  
  _AND5(tmp_value, 6, tmp_value, 2, tmp_value, 14, tmp_value, 13, tmp_value, 12, tmp_value, 15);
  
  //ПО Iблк. Umin1
  if (Ia_and_Ic_is_smaller_than_Iust) {
    _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_IBLK_UMIN1);
  }
  
  //ПО Umin1
  if (_GET_OUTPUT_STATE(tmp_value, 15)) {
    _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_UMIN1);
  }
  
  _TIMER_T_0(INDEX_TIMER_UMIN1, current_settings_prt.timeout_Umin1[number_group_stp], tmp_value, 15, tmp_value, 16);
  
  //Сраб. Umin1
  if (_GET_OUTPUT_STATE(tmp_value, 16)) {
    _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_UMIN1);
  }
}
/*****************************************************/

/*****************************************************/
// ЗНМИН2
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
  //М
  unsigned int tmp_value = ((current_settings_prt.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_PHASE_LINE) == 0)         << 0;
//  tmp_value |= ((current_settings_prt.control_Umin & CTR_EXTRA_SETTINGS_1_CTRL_PHASE_LINE) != 0)                                 << 1;
//  _INVERTOR(tmp_value, 1, tmp_value, 1);
  tmp_value |= ((current_settings_prt.control_Umin & CTR_UMIN2) != 0)                                                            << 2;
  tmp_value |= ((current_settings_prt.control_Umin & CTR_PO_UMIN2_OR_AND) != 0)                                                  << 3;
  tmp_value |= ((current_settings_prt.control_Umin & CTR_UMIN2_UBLK) != 0)                                                       << 4;
  tmp_value |= ((current_settings_prt.control_Umin & CTR_UMIN2_IBLK) != 0)                                                       << 5;
  
  //ДВ
  tmp_value |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_BLOCK_UMIN2) != 0)                                    << 6;
  _INVERTOR(tmp_value, 6, tmp_value, 6);
  tmp_value |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_START_UMIN2) != 0)                                    << 7;
  
//  _AND2(tmp_value, 0, tmp_value, 1, tmp_value, 8);
  
  if (_GET_OUTPUT_STATE(tmp_value, 0)) {
    //Фазные
    _AND4(Ua_is_smaller_than_Umin2, 0, Ub_is_smaller_than_Umin2, 0, Uc_is_smaller_than_Umin2, 0, tmp_value, 3, tmp_value, 9);
    _OR3(Ua_is_smaller_than_Umin2, 0, Ub_is_smaller_than_Umin2, 0, Uc_is_smaller_than_Umin2, 0, tmp_value, 10);
    _INVERTOR(tmp_value, 3, tmp_value, 3);
    _AND2(tmp_value, 10, tmp_value, 3, tmp_value, 11);
    _AND2(tmp_value, 5, Ia_and_Ic_is_smaller_than_Iust, 0, tmp_value, 12);
    _INVERTOR(tmp_value, 5, tmp_value, 5);
    _AND3(Ua_or_Ub_or_Uc_is_smaller_than_250mV, 0, tmp_value, 4, tmp_value, 5, tmp_value, 13);
    
    //ПО Uблк. Umin2
    if (Ua_or_Ub_or_Uc_is_smaller_than_250mV) {
      _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_UBLK_UMIN2);
    }
    
  } else {
    //Линейные
    _AND4(Uab_is_smaller_than_Umin2, 0, Ubc_is_smaller_than_Umin2, 0, Uca_is_smaller_than_Umin2, 0, tmp_value, 3, tmp_value, 9);
    _OR3(Uab_is_smaller_than_Umin2, 0, Ubc_is_smaller_than_Umin2, 0, Uca_is_smaller_than_Umin2, 0, tmp_value, 10);
    _INVERTOR(tmp_value, 3, tmp_value, 3);
    _AND2(tmp_value, 10, tmp_value, 3, tmp_value, 11);
    _AND2(tmp_value, 5, Ia_and_Ic_is_smaller_than_Iust, 0, tmp_value, 12);
    _INVERTOR(tmp_value, 5, tmp_value, 5);
    _AND3(Uab_or_Ubc_or_Uca_is_smaller_than_250mV, 0, tmp_value, 4, tmp_value, 5, tmp_value, 13);
    
    //ПО Uблк. Umin2
    if (Uab_or_Ubc_or_Uca_is_smaller_than_250mV) {
      _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_UBLK_UMIN2);
    }
  }
  _INVERTOR(tmp_value, 12, tmp_value, 12);
  _INVERTOR(tmp_value, 13, tmp_value, 13);
  _OR3(tmp_value, 7, tmp_value, 9, tmp_value, 11, tmp_value, 14);
  
  _AND5(tmp_value, 6, tmp_value, 2, tmp_value, 14, tmp_value, 13, tmp_value, 12, tmp_value, 15);
  
  //ПО Iблк. Umin2
  if (Ia_and_Ic_is_smaller_than_Iust) {
    _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_IBLK_UMIN2);
  }
  
  //ПО Umin2
  if (_GET_OUTPUT_STATE(tmp_value, 15)) {
    _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_UMIN2);
  }
  
  _TIMER_T_0(INDEX_TIMER_UMIN2, current_settings_prt.timeout_Umin2[number_group_stp], tmp_value, 15, tmp_value, 16);
  
  //Сраб. Umin2
  if (_GET_OUTPUT_STATE(tmp_value, 16)) {
    _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_UMIN2);
  }
}
/*****************************************************/

/*****************************************************/
// ЗНМАКС1
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
  
  //М
  unsigned int tmp_value = ((current_settings_prt.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_PHASE_LINE) == 0)         << 0;
//  tmp_value |= ((current_settings_prt.control_Umax & CTR_EXTRA_SETTINGS_1_CTRL_PHASE_LINE) != 0)                                 << 1;
//  _INVERTOR(tmp_value, 1, tmp_value, 1);
  tmp_value |= ((current_settings_prt.control_Umax & CTR_PO_UMAX1_OR_AND) != 0)                                                  << 2;
  tmp_value |= ((current_settings_prt.control_Umax & CTR_UMAX1) != 0)                                                            << 3;
  
  //ДВ
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
  
  //ПО Umax1
  if (_GET_OUTPUT_STATE(tmp_value, 9)) {
    _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_UMAX1);
  }
  
  _TIMER_T_0(INDEX_TIMER_UMAX1, current_settings_prt.timeout_Umax1[number_group_stp], tmp_value, 9, tmp_value, 10);
  
  //Сраб. Umax1
  if (_GET_OUTPUT_STATE(tmp_value, 10)) {
    _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_UMAX1);
  }
}
/*****************************************************/

/*****************************************************/
// ЗНМАКС2
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
  
  //М
  unsigned int tmp_value = ((current_settings_prt.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_PHASE_LINE) == 0)         << 0;
//  tmp_value |= ((current_settings_prt.control_Umax & CTR_EXTRA_SETTINGS_1_CTRL_PHASE_LINE) != 0)                                 << 1;
//  _INVERTOR(tmp_value, 1, tmp_value, 1);
  tmp_value |= ((current_settings_prt.control_Umax & CTR_PO_UMAX2_OR_AND) != 0)                                                  << 2;
  tmp_value |= ((current_settings_prt.control_Umax & CTR_UMAX2) != 0)                                                            << 3;
  
  //ДВ
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
  
  //ПО Umax1
  if (_GET_OUTPUT_STATE(tmp_value, 9)) {
    _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_UMAX2);
  }
  
  _TIMER_T_0(INDEX_TIMER_UMAX2, current_settings_prt.timeout_Umax2[number_group_stp], tmp_value, 9, tmp_value, 10);
  
  //Сраб. Umax1
  if (_GET_OUTPUT_STATE(tmp_value, 10)) {
    _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_UMAX2);
  }
}
/*****************************************************/

/*****************************************************/
// АПВ ЗМН
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
  
  //ДВ
  tmp_value |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_BLOCK_APV_ZMN) != 0)                  << 11;
  
  tmp_value |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_STATE_VV) == 0)                       << 12;
  tmp_value |= (_CHECK_SET_BIT(active_functions,    RANG_OUTPUT_LED_DF_REG_WORK_BO) == 0)                        << 13;
  tmp_value |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_UMIN1) != 0)                          << 14;
  tmp_value |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_UMIN2) != 0)                          << 15;
  
  //М
  tmp_value |= ((current_settings_prt.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_3U0_Ubc_TN2) == 0)    << 16; //Выбор 3U0
  tmp_value |= ((current_settings_prt.control_apv_zmn & CTR_APV_ZMN) == 0)                                       << 17;
  
  //ПО U АПВ ЗМН2
  if (_GET_OUTPUT_STATE(tmp_value, 16) /*Проверка выбора 3U0*/) {
    if (Uab2_is_larger_than_Uapvzmn2) {
      _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_UAPV_ZMN2);
    }
  } else {
    if (Uab2_is_larger_than_Uapvzmn2 && Ubc2_is_larger_than_Uapvzmn2) {
      _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_UAPV_ZMN2);
    }
  }
  
  //ПО U АПВ ЗМН1
  if (Uab_and_Ubc_is_larger_than_Uapvzmn1) {
    _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_UAPV_ZMN1);
  }
  
  _OR8(tmp_value, 0, tmp_value, 1, tmp_value, 2, tmp_value, 3, tmp_value, 4, tmp_value, 5, tmp_value, 6, tmp_value, 7, tmp_value, 7);
  _Bool _tmp_ = 0;
  _OR5(_3U0, 0, NZZ, 0, ACHR, 0, UMAX1, 0, UMAX2, 0, _tmp_, 0);
  _OR2(_tmp_, 0, tmp_value, 7, tmp_value, 7);
  _OR3(tmp_value, 8, tmp_value, 9, tmp_value, 17, tmp_value, 19);
  _D_TRIGGER(1,  0, _GET_OUTPUT_STATE(tmp_value, 19), previous_states_APV_ZMN_0, 0, tmp_value, 7, trigger_APV_ZMN_0, 0);
  
  //Бл.АПВ-ЗМН от з.
  if (trigger_APV_ZMN_0) {
    _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_BLOCK_APV_ZMN_VID_ZAKHYSTIV);
  }
  
  if (_GET_OUTPUT_STATE(tmp_value, 16) /*Проверка выбора 3U0*/) {
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
    
//    if (trigger_APV_ZMN_1) {//для отладки
//      trigger_APV_ZMN_1 = 1;
//    } else {
//      trigger_APV_ZMN_1 = 0;
//    }
    
    _AND3(tmp_value, 12, tmp_value, 13, trigger_APV_ZMN_1, 0, tmp_value, 28);
    _AND2(tmp_value, 28, tmp_value, 21, tmp_value, 29);
    _AND2(tmp_value, 28, tmp_value, 23, tmp_value, 30);
    _OR2(tmp_value, 29, tmp_value, 30, tmp_value, 31);
    
    //ПО АПВ ЗМН
    if (_GET_OUTPUT_STATE(tmp_value, 31)) {
      _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_APV_ZMN);
    }
    
    _TIMER_T_0(INDEX_TIMER_APV_ZMN1, current_settings_prt.timeout_apv_zmn_1[number_group_stp], tmp_value, 29, tmp_value, 0);
    _TIMER_T_0(INDEX_TIMER_APV_ZMN2, current_settings_prt.timeout_apv_zmn_2[number_group_stp], tmp_value, 30, tmp_value, 1);
    _OR2(tmp_value, 0, tmp_value, 1, tmp_value, 2);
    
    //Сраб. АПВ ЗМН
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
    
//    if (trigger_APV_ZMN_2) {//для отладки
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
  
  //Блокування кратності АПВ-ЗМН
  if (trigger_APV_ZMN_2) {
    _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_BLOCK_KRATN_APV_ZMN);
  }
  
}
/*****************************************************/

/*****************************************************/
// АВР
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
  
  //ДВ
  tmp_value |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_STAT_BLOCK_AVR) != 0)                 << 14;
  _INVERTOR(tmp_value, 14, tmp_value, 14);
  
  //М
  tmp_value |= ((current_settings_prt.control_avr & CTR_AVR) != 0)                                               << 15;
  tmp_value |= ((current_settings_prt.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_3U0_Ubc_TN2) == 0)    << 17; //Выбор 3U0
  
//  tmp_value |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_RESET_KRATN_SPRAC_AVR) != 0)          << 18;
  
  //ПО UАВРmin1
  if (Uab_and_Ubc_is_smaller_than_Uavrmin1) {
    _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_UAVR_MIN1);
  }
  
  //ПО UАВРmax1
  if (Uab_and_Ubc_is_larger_than_Uavrmax1) {
    _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_UAVR_MAX1);
  }
  
  if (_GET_OUTPUT_STATE(tmp_value, 17) /*Проверка выбора 3U0*/) {
    //ПО UАВРmax2
    if (Uab2_is_larger_than_Uavrmax2) {
      _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_UAVR_MAX2);
    }
    //ПО UАBPmin2
    if (Uab2_is_smaller_than_Uavrmin2) {
      _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_UAVR_MIN2);
    }
  } else {
    //ПО UАВРmax2
    if (Uab2_is_larger_than_Uavrmax2 && Ubc2_is_larger_than_Uavrmax2) {
      _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_UAVR_MAX2);
    }
    //ПО UАBPmin2
    if (Uab2_is_smaller_than_Uavrmin2 && Ubc2_is_smaller_than_Uavrmin2) {
      _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_UAVR_MIN2);
    }
  }
  
//  _OR6(tmp_value, 0, tmp_value, 1, tmp_value, 2, tmp_value, 3, tmp_value, 4, tmp_value, 5, tmp_value, 19);
//  _OR6(tmp_value, 6, tmp_value, 7, tmp_value, 8, tmp_value, 9, tmp_value, 10, tmp_value, 11, tmp_value, 20);
  _OR6(tmp_value, 4, tmp_value, 5, tmp_value, 6, tmp_value, 11, block_avr_vid_zovn_zakhystiv, 0, pryvid_vv, 0, tmp_value, 21);
  
  if (_GET_OUTPUT_STATE(tmp_value, 17) /*Проверка выбора 3U0*/) {
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
  
  //Блок. АВР от защит
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
    //Пуск АВР
    
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
  
  //Блокування кратності АВР
  if (trigger_AVR_1) {
    _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_BLOCK_KRATN_AVR);
  }
}
/*****************************************************/

/*****************************************************/
// АЧР ЧАПВ
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
  
  //Линейные
  _Bool Uab_is_larger_than_UF1 = measurement[IM_UAB] >= setpoint1;
  _Bool Ubc_is_larger_than_UF1 = measurement[IM_UBC] >= setpoint2;
  _Bool Uca_is_larger_than_UF1 = measurement[IM_UCA] >= setpoint3;
  
  //Фазные
  _Bool Ua_is_larger_than_UF1 = measurement[IM_UA] >= setpoint1;
  _Bool Ub_is_larger_than_UF1 = measurement[IM_UB] >= setpoint2;
  _Bool Uc_is_larger_than_UF1 = measurement[IM_UC] >= setpoint3;
  
  _Bool Uab_is_larger_than_UF2 = measurement[IM_UAB_TN2] >= setpoint4;
  _Bool Ubc_is_larger_than_UF2 = measurement[IM_3U0_UBC_TN2] >= setpoint4;
  
  /*----------------Выбор фазные/линейные-------------------------------------*/
  _Bool UF1_phase = ((current_settings_prt.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_PHASE_LINE) == 0);
//  unsigned char select_phase_line = ((current_settings_prt.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_PHASE_LINE) != 0) << 0;
//  _INVERTOR(select_phase_line, 0, select_phase_line, 0);
//  select_phase_line |= ((current_settings_prt.control_achr_chapv & CTR_EXTRA_SETTINGS_1_CTRL_PHASE_LINE) != 0)                    << 1;
//  _INVERTOR(select_phase_line, 1, select_phase_line, 1);
//  _AND2(select_phase_line, 0, select_phase_line, 1, UF1_phase, 0);
  /*--------------------------------------------------------------------------*/
  
  /*----------------Выбор 3U0-------------------------------------------------*/
  _Bool _3U0_ = ((current_settings_prt.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_3U0_Ubc_TN2) == 0);
  /*--------------------------------------------------------------------------*/
  
  _Bool timer1 = 0;
  _Bool UF1_is_larger_than_U_setpoint_F1 = 0;
  _Bool UF1_is_smaller_than_U_setpoint_F1 = 0;
  if (UF1_phase) {
    //ПО UAF1
    previous_state_po_achr_chapv_uaf1 = Ua_is_larger_than_UF1;
    //ПО UBF1
    previous_state_po_achr_chapv_ubf1 = Ub_is_larger_than_UF1;
    //ПО UCF1
    previous_state_po_achr_chapv_ucf1 = Uc_is_larger_than_UF1;
    _AND3(Ua_is_larger_than_UF1, 0, Ub_is_larger_than_UF1, 0, Uc_is_larger_than_UF1, 0, timer1, 0);
  } else {
    //ПО UAF1
    previous_state_po_achr_chapv_uaf1 = Uab_is_larger_than_UF1;
    //ПО UBF1
    previous_state_po_achr_chapv_ubf1 = Ubc_is_larger_than_UF1;
    //ПО UCF1
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
  
  //ПО UAF2 Uab2 Ubc2
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
  
  //ДВ
  unsigned int tmp_value = (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_BLOCK_ACHR) != 0)                 << 0;
  _INVERTOR(tmp_value, 0, tmp_value, 0);
  
  //М
  tmp_value |= ((current_settings_prt.control_achr_chapv & CTR_ACHR) != 0)                                               << 1;
//  tmp_value |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_SBROS_CHAPV) != 0)                            << 2;
  
  _AND3_INVERTOR(tmp_value, 0, tmp_value, 1, UF1_is_larger_than_U_setpoint_F1, 0, tmp_value, 3);
  _AND3_INVERTOR(tmp_value, 0, tmp_value, 1, UF2_is_larger_than_U_setpoint_F2, 0, tmp_value, 4);
  
  if (!_GET_OUTPUT_STATE(tmp_value, 3)) {
    //ПО АЧР1
    if (previous_state_po_f1_achr) {
//      if (!po_f1_achr_otp) {
      if (!po_f1_chapv_rab) {//после сработки 1 будет держаться до тех пор пока не сработает po_f1_chapv_rab (условие отпускания)
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
    //ПО АЧР2
    if (previous_state_po_f2_achr) {
//      if (!po_f2_achr_otp) {
      if (!po_f2_chapv_rab) {//после сработки 1 будет держаться до тех пор пока не сработает po_f2_chapv_rab (условие отпускания)
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
  
//  //АЧР/ЧАПВ1
//  if (_GET_OUTPUT_STATE(tmp_value, 5)) {
//    _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_ACHR_CHAPV_1);
//  }
//  
//  //АЧР/ЧАПВ2
//  if (_GET_OUTPUT_STATE(tmp_value, 7)) {
//    _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_ACHR_CHAPV_2);
//  }
//  
//  _OR2(tmp_value, 5, tmp_value, 7, tmp_value, 20);
//  
//  //Сраб АЧР/ЧАПВ
//  if (_GET_OUTPUT_STATE(tmp_value, 20)) {
//    _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_ACHR_CHAPV);
//  }
  
  _AND2(UF1_is_larger_than_U_setpoint_F1, 0, UF2_is_smaller_than_U_setpoint_F2, 0, tmp_value, 9);
  _AND2(UF1_is_smaller_than_U_setpoint_F1, 0, UF2_is_larger_than_U_setpoint_F2, 0, tmp_value, 10);
  _OR2(tmp_value, 9, tmp_value, 10, tmp_value, 11);
  
  //Разр ЧАПВ
  if (_GET_OUTPUT_STATE(tmp_value, 11)) {
    _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_RAZR_CHAPV);
  }
  
  _Bool tmp1 = 0;
  do {
    _OR2(tmp_value, 3, !trigger_CHAPV1, 0, tmp_value, 30);
    
    //ПО ЧАПВ1
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
//    _Bool tmp__ = !_GET_OUTPUT_STATE(tmp_value, 13); //для отладки
    _OR2(tmp_value, 5, tmp_value, 6, tmp_value, 13);
//    if (tmp__ && _GET_OUTPUT_STATE(tmp_value, 13)) { //для отладки
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
    
    //ПО ЧАПВ2
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
  
  //АЧР/ЧАПВ1
  if (_GET_OUTPUT_STATE(trigger_CHAPV1, 0/*tmp_value, 21*/)) {
    _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_F1_ACHR_CHAPV);
  }
  
  //АЧР/ЧАПВ2
  if (_GET_OUTPUT_STATE(trigger_CHAPV2, 0/*tmp_value, 22*/)) {
    _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_F2_ACHR_CHAPV);
  }
  
  //АЧР/ЧАПВ
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
//Контроль напряжения основной линии
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
  
  /*----------------Выбор фазные/линейные-------------------------------------*/
  _Bool U_OL_phase = ((current_settings_prt.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_PHASE_LINE) == 0);
//  unsigned char select_phase_line = ((current_settings_prt.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_PHASE_LINE) != 0) << 0;
//  _INVERTOR(select_phase_line, 0, select_phase_line, 0);
//  select_phase_line |= ((current_settings_prt.control_achr_chapv & CTR_EXTRA_SETTINGS_1_CTRL_PHASE_LINE) != 0)                    << 1;
//  _INVERTOR(select_phase_line, 1, select_phase_line, 1);
//  _AND2(select_phase_line, 0, select_phase_line, 1, U_OL_phase, 0);
  /*--------------------------------------------------------------------------*/
  
  //М
  unsigned int tmp_value = ((current_settings_prt.control_control_U & CTR_U_OL) != 0) << 0;
  
  if (U_OL_phase) {
    _AND4(Ua_is_larger_than_setpoint_u_ol, 0, Ub_is_larger_than_setpoint_u_ol, 0, Uc_is_larger_than_setpoint_u_ol, 0, tmp_value, 0, tmp_value, 1);
  } else {
    _AND4(Uab_is_larger_than_setpoint_u_ol, 0, Ubc_is_larger_than_setpoint_u_ol, 0, Uca_is_larger_than_setpoint_u_ol, 0, tmp_value, 0, tmp_value, 1);
  }
  
  //ПО U ОЛ
  if (_GET_OUTPUT_STATE(tmp_value, 1)) {
    _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_U_OL);
  }
  
  _TIMER_T_0(INDEX_TIMER_U_OL1, current_settings_prt.timeout_U_ol[number_group_stp], tmp_value, 1, tmp_value, 2);
  _INVERTOR(tmp_value, 1, tmp_value, 1);
  _TIMER_T_0(INDEX_TIMER_U_OL2, current_settings_prt.timeout_U_ol[number_group_stp], tmp_value, 1, tmp_value, 3);
  
  unsigned int tmp = 0;
  _D_TRIGGER(0, _GET_OUTPUT_STATE(tmp_value, 2), _GET_OUTPUT_STATE(tmp_value, 3), tmp, 0, tmp, 0, trigger_u_ol, 0);
  
  //U ОЛ
  if (trigger_u_ol) {
    _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_U_OL);
  }
}
/*****************************************************/

/*****************************************************/
// Контроль напряжения резервной линии
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
  
  /*----------------Выбор 3U0-------------------------------------------------*/
  _Bool _3U0_ = ((current_settings_prt.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_3U0_Ubc_TN2) == 0);
  /*--------------------------------------------------------------------------*/
  
  unsigned int tmp_value = 0;
  if (_3U0_) {
    tmp_value = Uab_is_larger_than_setpoint_u_rl;
  } else {
    tmp_value = (Uab_is_larger_than_setpoint_u_rl && Ubc_is_larger_than_setpoint_u_rl);
  }
  
  //М
  tmp_value |= ((current_settings_prt.control_control_U & CTR_U_RL) != 0) << 1;
  
  _AND2(tmp_value, 0, tmp_value, 1, tmp_value, 2);
  
  //ПО U РЛ
  if (_GET_OUTPUT_STATE(tmp_value, 2)) {
    _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_U_RL);
  }
  
  _TIMER_T_0(INDEX_TIMER_U_RL1, current_settings_prt.timeout_U_rl[number_group_stp], tmp_value, 2, tmp_value, 3);
  _INVERTOR(tmp_value, 2, tmp_value, 2);
  _TIMER_T_0(INDEX_TIMER_U_RL2, current_settings_prt.timeout_U_rl[number_group_stp], tmp_value, 2, tmp_value, 4);
  
  unsigned int tmp = 0;
  _D_TRIGGER(0, _GET_OUTPUT_STATE(tmp_value, 3), _GET_OUTPUT_STATE(tmp_value, 4), tmp, 0, tmp, 0, trigger_u_rl, 0);
  
  //U РЛ
  if (trigger_u_rl) {
    _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_U_RL);
  }
}
/*****************************************************/

/*****************************************************/
// Готовность к ТУ
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
  
  //Готовность к ТУ
  if (_GET_OUTPUT_STATE(tmp_value, 5)) {
    _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_READY_TU);
  }
}
/*****************************************************/

/*****************************************************/
// УРОВ
/*****************************************************/
inline void urov_handler(unsigned int *activated_functions, unsigned int number_group_stp)
{
  /*******************************/
  //Визначаємо максимальний фазовий струм для УРОВ
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
    //Є умова запуску УРОВ
    
    unsigned int setpoint; //уставка - з якою зрівнюється вимірювальна величина
    unsigned int previous_state_po_urov;
    
    //Копіюємо попередні значення сигналів УРОВ у тимчавовий масив, щоб потім мати можливість їх скидати або встановлювати
    //Це потрібно для того, щоб коли є умова, що сигнал не має ні встановлюватися ні скидатися - щоб він приймав своє попереднє значення  
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
    
    //Якщо ПО УРОВ ще не активне, то треба працювати по устаці спацювання - уставці, яка вводиться як основна з системи меню чи верхнього рівня
    //Якщо ПО УРОВ вже спрацювало, то треба працювати по уставці відпускання - береться процент від основної утанки по коефіцієнту повернення
    if(( previous_state_po_urov = _CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_PO_UROV) ) ==0 )
    {
      //Працюємо по утавці спрацювання
      setpoint = current_settings_prt.setpoint_urov[number_group_stp];
    }
    else
    {
      //Працюємо по утавці відпускання
      setpoint = current_settings_prt.setpoint_urov[number_group_stp]*KOEF_POVERNENNJA_GENERAL_UP/100;
    }
    
    //Виставляємо, або скидаємо сигнал "ПО УРОВ"
    if (max_faze_current >= setpoint)
    {
      //Максимальний фазний стум перевищує свою уставку
      if(previous_state_po_urov == 0)
      {
        //Встановлюємо сигнал "ПО УРОВ"
        _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_UROV);
      
        //Запускаємо таймери УРОВ1 і УРОВ2, якщо вони ще не запущені
        global_timers[INDEX_TIMER_UROV1] = 0;
        global_timers[INDEX_TIMER_UROV2] = 0;
      }
    }
    else 
    {
      //Максимальний фазний стум нижче уставки
      if(previous_state_po_urov != 0)
      {
        //Скидаємо сигнал "ПО УРОВ"
        _CLEAR_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_PO_UROV);
        //Це є умовою також скидання сигналів "Сраб. УРОВ1" і "Сраб. УРОВ2"
        _CLEAR_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_UROV1);
        _CLEAR_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_UROV2);
        //Якщо таймери ще не скинуті, то скидаємо їх
        if ( global_timers[INDEX_TIMER_UROV1] >=0) global_timers[INDEX_TIMER_UROV1] = -1;
        if ( global_timers[INDEX_TIMER_UROV2] >=0) global_timers[INDEX_TIMER_UROV2] = -1;
      }
    }
    
    //Перевіряємо чи таймер УРОВ1 досягнув значення своєї витримки
    if(global_timers[INDEX_TIMER_UROV1] >= current_settings_prt.timeout_urov_1[number_group_stp])
    {
      //Якщо витримана Витримка УРОВ1 то встановлюємо сигнал "Сраб. УРОВ1"
      _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_UROV1);

      //Скидаємо таймер УРОВ1
      global_timers[INDEX_TIMER_UROV1] = -1;
    }

    //Перевіряємо чи таймер УРОВ2 досягнув значення своєї витримки
    if(global_timers[INDEX_TIMER_UROV2] >= current_settings_prt.timeout_urov_2[number_group_stp])
    {
      //Якщо витримана Витримка УРОВ2 то встановлюємо сигнал "Сраб. УРОВ2"
      _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_UROV2);

      //Скидаємо таймер УРОВ2
      global_timers[INDEX_TIMER_UROV2] = -1;
    }
  }
  else
  {
    //Якщо 1 ступінь УРОВ не встановлена, то треба скинути всі таймери і сигнали, які за неї відповідають
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
//АПВ
/*****************************************************/
inline void apv_handler(unsigned int *activated_functions, unsigned int number_group_stp)
{
  unsigned int logic_APV_0 = 0;
  unsigned int logic_APV_1 = 0;

  //Рестарт пристрою
  logic_APV_1 |= (start_restart != 0) << 19;
  //Очищаємо повідомлення про рестрат пристрою
  start_restart = 0;

  //"Статичне блокування"
  logic_APV_0 |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_STAT_BLK_APV) != 0) << 0;
  _INVERTOR(logic_APV_0, 0, logic_APV_0, 1);

  //М:"Пуск від МТЗ1"
  logic_APV_0 |= ((current_settings_prt.control_apv & CTR_APV_STARTED_FROM_MTZ1) != 0) << 2;
  //"МТЗ1"
  logic_APV_0 |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_MTZ1) != 0) << 3;
  _AND2(logic_APV_0, 2, logic_APV_0, 3, logic_APV_0, 4);

  //М:"Пуск від МТЗ2"
  logic_APV_0 |= ((current_settings_prt.control_apv & CTR_APV_STARTED_FROM_MTZ2) != 0) << 5;
  //"МТЗ2"
  logic_APV_0 |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_MTZ2) != 0) << 6;
  _AND2(logic_APV_0, 5, logic_APV_0, 6, logic_APV_0, 7);

  //М:"Пуск від МТЗ3"
  logic_APV_0 |= ((current_settings_prt.control_apv & CTR_APV_STARTED_FROM_MTZ3) != 0) << 8;
  //"МТЗ3"
  logic_APV_0 |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_MTZ3) != 0) << 9;
  _AND2(logic_APV_0, 8, logic_APV_0, 9, logic_APV_0, 10);

  //М:"Пуск від МТЗ4"
  logic_APV_0 |= ((current_settings_prt.control_apv & CTR_APV_STARTED_FROM_MTZ4) != 0) << 11;
  //"МТЗ4"
  logic_APV_0 |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_MTZ4) != 0) << 12;
  _AND2(logic_APV_0, 11, logic_APV_0, 12, logic_APV_0, 13);
  
  _OR4(logic_APV_0, 4, logic_APV_0, 7, logic_APV_0, 10, logic_APV_0, 13, logic_APV_0, 14);
  _TIMER_0_T(INDEX_TIMER_APV_TMP1, 1, logic_APV_0, 14, logic_APV_0, 15);

  //М:"ЧАПВ"
  logic_APV_0 |= ((current_settings_prt.control_achr_chapv & CTR_CHAPV) != 0) << 16;
  //"ЧАПВ"
  logic_APV_1 |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_ACHR_CHAPV) != 0) << 21;
  //"Разр ЧАПВ"
  logic_APV_1 |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_RAZR_CHAPV) != 0) << 20;

  //"АЧР/ЧАПВ від ДВ"
  logic_APV_0 |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_ACHR_CHAPV_VID_DV) != 0) << 17;
  //М:"ЧАПВ від ДВ"
  logic_APV_1 |= ((current_settings_prt.control_achr_chapv & CTR_CHAPV_VID_DV) != 0) << 22;
  
  _AND3(logic_APV_0, 16, logic_APV_1, 21, logic_APV_1, 20, logic_APV_1, 23);
  _AND2(logic_APV_0, 17, logic_APV_1, 22, logic_APV_1, 24);
  _OR2(logic_APV_1, 23, logic_APV_1, 24, logic_APV_0, 18)

  //"Блок.ЧАПВ від U"
  logic_APV_1 |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_BLOCK_CHAPV_VID_U) != 0) << 25;
  _OR2(logic_APV_0, 18, logic_APV_1, 25, logic_APV_1, 26);
    
  _TIMER_0_T(INDEX_TIMER_ACHR_CHAPV, MAX_VALUE_TIMER_FOR_COUNT_SIGNAL_ACHR_CHAPV, logic_APV_0, 18, logic_APV_0, 19);

  _OR2_INVERTOR(logic_APV_0, 15, logic_APV_0, 19, logic_APV_0, 20);

  //"Стан вимикача"
  logic_APV_0 |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_STATE_VV) != 0) << 21;
  _TIMER_IMPULSE(INDEX_TIMER_APV_BLOCK_VID_VV, current_settings_prt.timeout_apv_block_vid_VV[number_group_stp], previous_states_APV_0, 0, logic_APV_0, 21, logic_APV_0, 22);

  //М:"АПВ"
  logic_APV_0 |= ((current_settings_prt.control_apv & CTR_APV_STAGE_1) != 0) << 23;
  _INVERTOR(logic_APV_0, 23, logic_APV_0, 24);

  //М:"АПВ2"
  logic_APV_0 |= ((current_settings_prt.control_apv & CTR_APV_STAGE_2) != 0) << 25;
  _INVERTOR(logic_APV_0, 25, logic_APV_0, 26);

  //М:"АПВ3"
  logic_APV_0 |= ((current_settings_prt.control_apv & CTR_APV_STAGE_3) != 0) << 27;
  _INVERTOR(logic_APV_0, 27, logic_APV_0, 28);

  //М:"АПВ4"
  logic_APV_0 |= ((current_settings_prt.control_apv & CTR_APV_STAGE_4) != 0) << 29;
  _INVERTOR(logic_APV_0, 29, logic_APV_0, 30);

  //Наступні операції виконуються ітераційно поки всі сигнали не встановляться у фіксований стан
  logic_APV_0 |= _GET_OUTPUT_STATE(previous_states_APV_0, 1) << 31;
  logic_APV_1 |= _GET_OUTPUT_STATE(previous_states_APV_0, 2) <<  0;
  logic_APV_1 |= _GET_OUTPUT_STATE(previous_states_APV_0, 3) <<  1;
  logic_APV_1 |= _GET_OUTPUT_STATE(previous_states_APV_0, 4) <<  2;
  
  unsigned int previous_trigger_APV_0;
  
  do
  {
    /***
    Фіксуємо теперішній стан сигналів, які потім, можливо, зміняться і від зміни
    стану яких залежить завершення ітераційного процесу
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
    
    
    //АПВ1
    _OR6(logic_APV_1, 19, logic_APV_0, 14,                   trigger_APV_0, 1, trigger_APV_0, 2, trigger_APV_0, 3, logic_APV_0, 31, logic_APV_1, 4);
    _OR6(logic_APV_1, 26, logic_APV_0, 22, logic_APV_0, 24, logic_APV_1, 3, logic_APV_1, 0, logic_APV_1, 4, logic_APV_1, 8);
    _D_TRIGGER(_GET_OUTPUT_STATE(logic_APV_0, 1),  0, _GET_OUTPUT_STATE(logic_APV_1, 8), previous_states_APV_0, 5, logic_APV_0, 20, trigger_APV_0, 0);                 
    _TIMER_T_0(INDEX_TIMER_APV_1, current_settings_prt.timeout_apv_1[number_group_stp], trigger_APV_0, 0, logic_APV_1, 9);
    /*
    Цей сигнал встановлюмо в масив activated_functions в циклі з післяумовою
    do-while, бо нас цікавить зафіксувати цей сигнал, а коли він виставиться, то
    піде сигнал на очистку триґера і цей сигнал очиститься. Але встановлення по АБО "0"
    після встановлення "1" не мало б зняти цей сигнал і ми його маємо зафіксувати до 
    наступної роботи системи захистів.
    */
    activated_functions[RANG_OUTPUT_LED_DF_REG_APV1 >> 5] |= (_GET_OUTPUT_STATE(logic_APV_1, 9) << (RANG_OUTPUT_LED_DF_REG_APV1 & 0x1f));
    _TIMER_0_T(INDEX_TIMER_APV_BLOCK_VID_APV1, current_settings_prt.timeout_apv_block_vid_apv1[number_group_stp], logic_APV_1, 9, logic_APV_0, 31);

    //АПВ2
    _AND2_INVERTOR(logic_APV_0, 31, logic_APV_0, 15, logic_APV_1, 10);
    _OR6(logic_APV_1, 19, logic_APV_0, 14, trigger_APV_0, 0,                   trigger_APV_0, 2, trigger_APV_0, 3, logic_APV_1,  0, logic_APV_1, 5);
    _OR6(logic_APV_1, 26, logic_APV_0, 24, logic_APV_0, 26, logic_APV_1, 2, logic_APV_1, 1, logic_APV_1, 5, logic_APV_1, 11);
    _D_TRIGGER(1,  0, _GET_OUTPUT_STATE(logic_APV_1, 11), previous_states_APV_0, 6, logic_APV_1, 10, trigger_APV_0, 1);    
    _TIMER_T_0(INDEX_TIMER_APV_2, current_settings_prt.timeout_apv_2[number_group_stp], trigger_APV_0, 1, logic_APV_1, 12);
    /*
    Цей сигнал встановлюмо в масив activated_functions в циклі з післяумовою
    do-while, бо нас цікавить зафіксувати цей сигнал, а коли він виставиться, то
    піде сигнал на очистку триґера і цей сигнал очиститься. Але встановлення по АБО "0"
    після встановлення "1" не мало б зняти цей сигнал і ми його маємо зафіксувати до 
    наступної роботи системи захистів.
    */
    activated_functions[RANG_OUTPUT_LED_DF_REG_APV2 >> 5] |= (_GET_OUTPUT_STATE(logic_APV_1, 12) << (RANG_OUTPUT_LED_DF_REG_APV2 & 0x1f));
    _TIMER_0_T(INDEX_TIMER_APV_BLOCK_VID_APV2, current_settings_prt.timeout_apv_block_vid_apv2[number_group_stp], logic_APV_1, 12, logic_APV_1, 0);

    //АПВ3
    _AND2_INVERTOR(logic_APV_1, 0, logic_APV_0, 15, logic_APV_1, 13);
    _OR6(logic_APV_1, 19, logic_APV_0, 14, trigger_APV_0, 0, trigger_APV_0, 1,                   trigger_APV_0, 3, logic_APV_1,  1, logic_APV_1, 6);
    _OR5(logic_APV_1, 26, logic_APV_0, 24, logic_APV_0, 28, logic_APV_1, 2, logic_APV_1, 6, logic_APV_1, 14);
    _D_TRIGGER(1,  0, _GET_OUTPUT_STATE(logic_APV_1, 14), previous_states_APV_0, 7, logic_APV_1, 13, trigger_APV_0, 2);                 
    _TIMER_T_0(INDEX_TIMER_APV_3, current_settings_prt.timeout_apv_3[number_group_stp], trigger_APV_0, 2, logic_APV_1, 15);
    /*
    Цей сигнал встановлюмо в масив activated_functions в циклі з післяумовою
    do-while, бо нас цікавить зафіксувати цей сигнал, а коли він виставиться, то
    піде сигнал на очистку триґера і цей сигнал очиститься. Але встановлення по АБО "0"
    після встановлення "1" не мало б зняти цей сигнал і ми його маємо зафіксувати до 
    наступної роботи системи захистів.
    */
    activated_functions[RANG_OUTPUT_LED_DF_REG_APV3 >> 5] |= (_GET_OUTPUT_STATE(logic_APV_1, 15) << (RANG_OUTPUT_LED_DF_REG_APV3 & 0x1f));
    _TIMER_0_T(INDEX_TIMER_APV_BLOCK_VID_APV3, current_settings_prt.timeout_apv_block_vid_apv3[number_group_stp], logic_APV_1, 15, logic_APV_1, 1);

    //АПВ4
    _AND2_INVERTOR(logic_APV_1, 1, logic_APV_0, 15, logic_APV_1, 16);
    _OR6(logic_APV_1, 19, logic_APV_0, 14, trigger_APV_0, 0, trigger_APV_0, 1, trigger_APV_0, 2,                   logic_APV_1,  2, logic_APV_1, 7);
    _OR4(logic_APV_1, 26, logic_APV_0, 24, logic_APV_0, 30, logic_APV_1, 7, logic_APV_1, 17);
    _D_TRIGGER(1,  0, _GET_OUTPUT_STATE(logic_APV_1, 17), previous_states_APV_0, 8, logic_APV_1, 16, trigger_APV_0, 3);                 
    _TIMER_T_0(INDEX_TIMER_APV_4, current_settings_prt.timeout_apv_4[number_group_stp], trigger_APV_0, 3, logic_APV_1, 18);
    /*
    Цей сигнал встановлюмо в масив activated_functions в циклі з післяумовою
    do-while, бо нас цікавить зафіксувати цей сигнал, а коли він виставиться, то
    піде сигнал на очистку триґера і цей сигнал очиститься. Але встановлення по АБО "0"
    після встановлення "1" не мало б зняти цей сигнал і ми його маємо зафіксувати до 
    наступної роботи системи захистів.
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
  
  //Работа АПВ
  if (work_apv) {
    _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_APV_WORK);
  }
  
}
/*****************************************************/

/*****************************************************/
//Функція управління блоками включення і відключення
/*****************************************************/
inline void on_off_handler(unsigned int *activated_functions, unsigned int *previous_stats_signals)
{
  //Копіюємо попередні значення сигналів "Робота БО" і "Робота БВ" у тимчавовий масив, щоб потім мати можливість їх скидати або встановлювати
  //Це потрібно для того, щоб коли є умова, що сигнал не має ні встановлюватися ні скидатися - щоб він приймав своє попереднє значення  
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
  //Спочатку опрацьовуємо таймери
  /*********************/
  //Таймер  відключення
  if (global_timers[INDEX_TIMER_VIDKL_VV] >= 0)
  {
    //Таймер БО зараз активний і як мінімум тільки зараз завершить свою роботу
    if (global_timers[INDEX_TIMER_VIDKL_VV] >= current_settings_prt.timeout_swch_off)
    {
      //Таймер досягнув свого максимального значення
      global_timers[INDEX_TIMER_VIDKL_VV] = -1;
      //Відмічаємо у масиві функцій, які зараз активуються, що блок БО має бути деативованим
      _CLEAR_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_WORK_BO);
    }
    //Незавершена робота блоку БО означає, що таймер блокування БВ має бути запущений і знаходитися у свому початковому значенні,
    //щоб як тільки блок БО відпрацює, щоб блокування включення почалося на весь час з моменту закінчення роботи блоку БО
    global_timers[INDEX_TIMER_BLK_VKL_VV] = 0;
  }
    
  //Таймер  блокування включення
  if (global_timers[INDEX_TIMER_BLK_VKL_VV] >= 0)
  {
    //Таймер блокування включення БВ зараз активний і як мінімум тільки зараз завершить свою роботу
    if (global_timers[INDEX_TIMER_BLK_VKL_VV] >= current_settings_prt.timeout_swch_udl_blk_on)
    {
      //Таймер досягнув свого максимального значення
      global_timers[INDEX_TIMER_BLK_VKL_VV] = -1;
    }
  }

  //Таймер  включення
  if (global_timers[INDEX_TIMER_VKL_VV] >= 0)
  {
    //Таймер БВ зараз активний і як мінімум тільки зараз завершить свою роботу

    //Якщо по якійсь причині таймер включення працює, при умові, що таймери БО і блокування включення ще не скинуті, то таймер включення треба скинути
    if ((global_timers[INDEX_TIMER_VIDKL_VV] >= 0) || (global_timers[INDEX_TIMER_BLK_VKL_VV] >=0))
    {
      global_timers[INDEX_TIMER_VKL_VV] = -1;
      //Відмічаємо у масиві функцій, які зараз активуються, що блок БB має бути деативованим
      _CLEAR_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_WORK_BV);
    }
    else
    {
      //Перевіряємо, чи таймер включення не досягнув свого масимального значення
      if (global_timers[INDEX_TIMER_VKL_VV] >= current_settings_prt.timeout_swch_on)
      {
        //Таймер досягнув свого максимального значення
        global_timers[INDEX_TIMER_VKL_VV] = -1;
        //Відмічаємо у масиві функцій, які зараз активуються, що блок БB має бути деативованим
        _CLEAR_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_WORK_BV);
      }
    }
  }
  /*********************/

  /*********************/
  //Першим розглядається блок відключення, бо він може блокувати включення вимикача
  /*********************/
  //Формуємо маску з сигналом "Робота БО", щоб не розглядати цей сигнал як джерело активації БО (щоб він сам себе не генерував, бо інакше, як тільки раз запуститься постійно буде себе генерувати)
  maska[0] = 0;
  maska[1] = 0;
  maska[2] = 0;
  maska[3] = 0;
  maska[4] = 0;
  maska[5] = 0;
  _SET_BIT(maska, RANG_OUTPUT_LED_DF_REG_WORK_BO);

  //Перевіряємо, чи немає умови запуску БО
  unsigned int i = 0;
  while ((i < NUMBER_OUTPUTS) && (global_timers[INDEX_TIMER_VIDKL_VV] != 0))
  {
    //Цю провірку виконуємо доти поки не переберемо всі виходи, або поки блок БО не активується
    /*
    (його таймер стане рівним "0", бо коли є ще сигнал активації БО то ми таймер скидаємо в 0,
    а інакше таймер, як мініму буде збільшений на DELTA_TIME_FOR_TIMERS, або "-1", якщо таймер завершив своє тактування, або взагалі не запускався)
    */
      
    //У тимчасовий масив копіюємо ранжування виходу, який індексується інедексом "i"
    unsigned int temp_array_of_outputs[N_BIG];
    temp_array_of_outputs[0] = current_settings_prt.ranguvannja_outputs[N_BIG*i    ];
    temp_array_of_outputs[1] = current_settings_prt.ranguvannja_outputs[N_BIG*i + 1];
    temp_array_of_outputs[2] = current_settings_prt.ranguvannja_outputs[N_BIG*i + 2];
    temp_array_of_outputs[3] = current_settings_prt.ranguvannja_outputs[N_BIG*i + 3];
    temp_array_of_outputs[4] = current_settings_prt.ranguvannja_outputs[N_BIG*i + 4];
    temp_array_of_outputs[5] = current_settings_prt.ranguvannja_outputs[N_BIG*i + 5];
      
    //Перевіряємо чи на вихід, який індексується інедексом "i", зранжована робота БО
    if(_CHECK_SET_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_WORK_BO) !=0)
    {
      //Перевіряємо, чи є зараз умова активації виходу (будь-яка активна функція крім функції "Робота БО")
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
        //На даному виході зараз активовується якась функція, яка є одночасно і джерелом БО
          
        //Відмічаємо у масиві функцій, які зараз активуються, що ще треба активувати блок БО (якщо він ще не активний)
        _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_WORK_BO);

        //Запускаємо (або продовжуємо утримувати у 0, поки не пропаде сигнал активації БО) таймери: блоку БО, блокуванння БВ.
        global_timers[INDEX_TIMER_VIDKL_VV  ] = 0;
        global_timers[INDEX_TIMER_BLK_VKL_VV] = 0;

        //Скидаємо активацію БВ
        _CLEAR_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_WORK_BV);
        //Скидаємо таймер БВ
        global_timers[INDEX_TIMER_VKL_VV] = -1;  

        /*
        Формуємо сигнал "Відключення від захистів" (він рівний наявності умови команди
        активації команди "Робота БО" будь-якою командою за виключенняв "Вимкн. ВВ")
        */
        maska[0] = 0;
        maska[1] = 0;
        maska[2] = 0;
        maska[3] = 0;
        maska[4] = 0;
        maska[5] = 0;
        _SET_BIT(maska, RANG_OUTPUT_LED_DF_REG_OTKL_VV);

        //Перевіряємо, чи "Робота БО" активувалася командою "Вимк.ВВ" чи іншими фунціями захистів
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
          Формуванні інформації про причину відключення для меню
          *****************************************************/
          unsigned char *label_to_time_array;
          if (copying_time == 2) label_to_time_array = time_copy;
          else label_to_time_array = time;
          
          //МТЗ1
          if(
             (_CHECK_SET_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_MTZ1) != 0) &&
             (_CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_MTZ1) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
            )   
          {
            info_vidkluchennja_vymykacha |= (1 << VYMKNENNJA_VID_MTZ1);
            for(unsigned int j = 0; j < 7; j++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_MTZ1][j] = *(label_to_time_array + j);

            _CLEAR_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_MTZ1);
          }
          
          //МТЗ2
          if(
             (_CHECK_SET_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_MTZ2) != 0) &&
             (_CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_MTZ2) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
            )   
          {
            info_vidkluchennja_vymykacha |= (1 << VYMKNENNJA_VID_MTZ2);
            for(unsigned int j = 0; j < 7; j++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_MTZ2][j] = *(label_to_time_array + j);

            _CLEAR_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_MTZ2);
          }
          
          //МТЗ3
          if(
             (_CHECK_SET_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_MTZ3) != 0) &&
             (_CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_MTZ3) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
            )   
          {
            info_vidkluchennja_vymykacha |= (1 << VYMKNENNJA_VID_MTZ3);
            for(unsigned int j = 0; j < 7; j++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_MTZ3][j] = *(label_to_time_array + j);

            _CLEAR_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_MTZ3);
          }
          
          //МТЗ4
          if(
             (_CHECK_SET_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_MTZ4) != 0) &&
             (_CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_MTZ4) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
            )   
          {
            info_vidkluchennja_vymykacha |= (1 << VYMKNENNJA_VID_MTZ4);
            for(unsigned int j = 0; j < 7; j++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_MTZ4][j] = *(label_to_time_array + j);

            _CLEAR_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_MTZ4);
          }
          
          //ЗДЗ
          if(
             (_CHECK_SET_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_ZDZ) != 0) &&
             (_CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_ZDZ) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
            )   
          {
            info_vidkluchennja_vymykacha |= (1 << VYMKNENNJA_VID_ZDZ);
            for(unsigned int j = 0; j < 7; j++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_ZDZ][j] = *(label_to_time_array + j);

            _CLEAR_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_ZDZ);
          }
          
          //ЗЗ/3I0
          if(
             (_CHECK_SET_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_3I0) != 0) &&
             (_CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_3I0) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
            )   
          {
            info_vidkluchennja_vymykacha |= (1 << VYMKNENNJA_VID_3I0);
            for(unsigned int j = 0; j < 7; j++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_3I0][j] = *(label_to_time_array + j);

            _CLEAR_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_3I0);
          }
          
          //ЗЗ/3U0
          if(
             (_CHECK_SET_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_3U0) != 0) &&
             (_CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_3U0) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
            )   
          {
            info_vidkluchennja_vymykacha |= (1 << VYMKNENNJA_VID_3U0);
            for(unsigned int j = 0; j < 7; j++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_3U0][j] = *(label_to_time_array + j);

            _CLEAR_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_3U0);
          }
          
          //НЗЗ
          if(
             (_CHECK_SET_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_NZZ) != 0) &&
             (_CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_NZZ) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
            )   
          {
            info_vidkluchennja_vymykacha |= (1 << VYMKNENNJA_VID_NZZ);
            for(unsigned int j = 0; j < 7; j++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_NZZ][j] = *(label_to_time_array + j);

            _CLEAR_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_NZZ);
          }
          
          //АЧР/ЧАПВ від ДВ
          if(
             (_CHECK_SET_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_ACHR_CHAPV_VID_DV) != 0) &&
             (_CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_ACHR_CHAPV_VID_DV) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
            )   
          {
            info_vidkluchennja_vymykacha |= (1 << VYMKNENNJA_VID_ACHR_CHAPV_VID_DV);
            for(unsigned int j = 0; j < 7; j++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_ACHR_CHAPV_VID_DV][j] = *(label_to_time_array + j);

            _CLEAR_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_ACHR_CHAPV_VID_DV);
          }
          
          //АЧР/ЧАПВ
          if(
             (_CHECK_SET_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_ACHR_CHAPV) != 0) &&
             (_CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_ACHR_CHAPV) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
            )   
          {
            info_vidkluchennja_vymykacha |= (1 << VYMKNENNJA_VID_ACHR_CHAPV);
            for(unsigned int j = 0; j < 7; j++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_ACHR_CHAPV][j] = *(label_to_time_array + j);

            _CLEAR_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_ACHR_CHAPV);
          }
          
          //УРОВ1
          if(
             (_CHECK_SET_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_UROV1) != 0) &&
             (_CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_UROV1) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
            )   
          {
            info_vidkluchennja_vymykacha |= (1 << VYMKNENNJA_VID_UROV1);
            for(unsigned int j = 0; j < 7; j++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_UROV1][j] = *(label_to_time_array + j);

            _CLEAR_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_UROV1);
          }
          
          //УРОВ2
          if(
             (_CHECK_SET_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_UROV2) != 0) &&
             (_CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_UROV2) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
            )   
          {
            info_vidkluchennja_vymykacha |= (1 << VYMKNENNJA_VID_UROV2);
            for(unsigned int j = 0; j < 7; j++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_UROV2][j] = *(label_to_time_array + j);

            _CLEAR_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_UROV2);
          }
          
          //ЗОП
          if(
             (_CHECK_SET_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_ZOP) != 0) &&
             (_CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_ZOP) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
            )   
          {
            info_vidkluchennja_vymykacha |= (1 << VYMKNENNJA_VID_ZOP);
            for(unsigned int j = 0; j < 7; j++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_ZOP][j] = *(label_to_time_array + j);

            _CLEAR_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_ZOP);
          }
          
          //Umin1
          if(
             (_CHECK_SET_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_UMIN1) != 0) &&
             (_CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_UMIN1) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
            )   
          {
            info_vidkluchennja_vymykacha |= (1 << VYMKNENNJA_VID_UMIN1);
            for(unsigned int j = 0; j < 7; j++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_UMIN1][j] = *(label_to_time_array + j);

            _CLEAR_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_UMIN1);
          }
          
          //Umin2
          if(
             (_CHECK_SET_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_UMIN2) != 0) &&
             (_CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_UMIN2) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
            )   
          {
            info_vidkluchennja_vymykacha |= (1 << VYMKNENNJA_VID_UMIN2);
            for(unsigned int j = 0; j < 7; j++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_UMIN2][j] = *(label_to_time_array + j);

            _CLEAR_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_UMIN2);
          }
          
          //Umax1
          if(
             (_CHECK_SET_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_UMAX1) != 0) &&
             (_CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_UMAX1) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
            )   
          {
            info_vidkluchennja_vymykacha |= (1 << VYMKNENNJA_VID_UMAX1);
            for(unsigned int j = 0; j < 7; j++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_UMAX1][j] = *(label_to_time_array + j);

            _CLEAR_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_UMAX1);
          }
          
          //Umax2
          if(
             (_CHECK_SET_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_UMAX2) != 0) &&
             (_CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_UMAX2) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
            )   
          {
            info_vidkluchennja_vymykacha |= (1 << VYMKNENNJA_VID_UMAX2);
            for(unsigned int j = 0; j < 7; j++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_UMAX2][j] = *(label_to_time_array + j);

            _CLEAR_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_UMAX2);
          }
          
          //Відключення від зовнішніх захистів
          if(
             (_CHECK_SET_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_OTKL_VID_ZOVN_ZAHYSTIV) != 0) &&
             (_CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_OTKL_VID_ZOVN_ZAHYSTIV) == 0) /*умова, що сигнал тільки активується (щоб зафіксувати час старту)*/
            )   
          {
            info_vidkluchennja_vymykacha |= (1 << VYMKNENNJA_VID_ZOVNISHNIKH_ZAKHYSTIV);
            for(unsigned int j = 0; j < 7; j++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_ZOVNISHNIKH_ZAKHYSTIV][j] = *(label_to_time_array + j);

            _CLEAR_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_OTKL_VID_ZOVN_ZAHYSTIV);
          }
          
          //Відключення від інших сигналів (крім відключення від сигналу "Вимк.ВВ")
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
  //Потім розглядається блок включення
  /*********************/
  if (
      (global_timers[INDEX_TIMER_VIDKL_VV  ] < 0) && 
      (global_timers[INDEX_TIMER_BLK_VKL_VV] < 0) &&
      (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_BLOCK_VKL_VV) == 0)
     )
  {
    //Оскільки не працюють таймери БО і блокування включення БВ, а також немає сигналу блокування включення ВВ
    //тому перевіряємо, чи немає умови запуску БВ

    //Формуємо маску з сигналом "Робота БВ", щоб не розглядати цей сигнал як джерело активації БВ (щоб він сам себе не генерував, бо інакше, як тільки раз запуститься постійно буде себе генерувати)
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
      //Цю провірку виконуємо доти поки не переберемо всі виходи, або поки блок БВ не активується
      /*
      (його таймер стане рівним "0", бо коли є ще сигнал активації БВ то ми таймер скидаємо в 0,
      а інакше таймер, як мініму буде збільшений на DELTA_TIME_FOR_TIMERS, або "-1", якщо таймер заверший своє тактування, або взагалі не запускався)
      */

      //У тимчасовий масив копіюємо ранжування виходу, який індексується інедексом "i"
      unsigned int temp_array_of_outputs[N_BIG];
      temp_array_of_outputs[0] = current_settings_prt.ranguvannja_outputs[N_BIG*i    ];
      temp_array_of_outputs[1] = current_settings_prt.ranguvannja_outputs[N_BIG*i + 1];
      temp_array_of_outputs[2] = current_settings_prt.ranguvannja_outputs[N_BIG*i + 2];
      temp_array_of_outputs[3] = current_settings_prt.ranguvannja_outputs[N_BIG*i + 3];
      temp_array_of_outputs[4] = current_settings_prt.ranguvannja_outputs[N_BIG*i + 4];
      temp_array_of_outputs[5] = current_settings_prt.ranguvannja_outputs[N_BIG*i + 5];
      
      //Перевіряємо чи на вихід, який індексується інедексом "i", зранжована робота БВ
      if(_CHECK_SET_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_WORK_BV) !=0)
      {
        //Перевіряємо, чи є зараз умова активації виходу (будь-яка активна функція крім функції "Робота БО")
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
          //На даному виході зараз активовується якась функція, яка є одночасно і джерелом БВ
            
          //Є умова запуску БВ, але ще додатково провіряємо, чи немає умови заборони включення БВ (хоч, теоретично, якщо тут знаходиться прорама, то блокування роботи БВ через блок БО або таймер блокування включення БВ не мало б бути)
          if ((global_timers[INDEX_TIMER_VIDKL_VV] < 0) && (global_timers[INDEX_TIMER_BLK_VKL_VV] < 0))
          {
            //Відмічаємо у масиві функцій, які зараз активуються, що ще треба активувати блок БВ (якщо він ще не активний)
            _SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_WORK_BV);

            //Запускаємо (або продовжуємо утримувати у 0, поки не пропаде сигнал активації БВ) таймер роботи БВ
            global_timers[INDEX_TIMER_VKL_VV] = 0;
          }
          else
          {
            //Теоретично, сюди програма ніколи б не мала прийти
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
    //На даний момент існує одна або більше умов блокування БВ
    global_timers[INDEX_TIMER_VKL_VV] = -1;
    _CLEAR_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_WORK_BV);
  }
  /*********************/
}
/*****************************************************/

/*****************************************************/
//Визначення місця до пошкодження
/*****************************************************/
inline void vmp_handler(unsigned int activated_functions[])
{
  //Перевіряємо чи стоїть фіксуються спрацювання від КЗ на фазних лініях
  if(
     ((activated_functions[0] & MASKA_MONITOTYNG_PHASE_SIGNALES_KZ_0) != 0) ||
     ((activated_functions[1] & MASKA_MONITOTYNG_PHASE_SIGNALES_KZ_1) != 0) ||
     ((activated_functions[2] & MASKA_MONITOTYNG_PHASE_SIGNALES_KZ_2) != 0) ||
     ((activated_functions[3] & MASKA_MONITOTYNG_PHASE_SIGNALES_KZ_3) != 0) ||
     ((activated_functions[4] & MASKA_MONITOTYNG_PHASE_SIGNALES_KZ_4) != 0) ||
     ((activated_functions[5] & MASKA_MONITOTYNG_PHASE_SIGNALES_KZ_5) != 0)
    )
  {
    //Є фазне КЗ
    VMP_last_KZ = UNDEF_VMP; /*Помічаємо, що визначення місця до пошкодження ще не визначене*/
    
    //Перевіряємо чи подається команда на вимкнення ВВ ("Робота БО")
    vymknennja_vid_KZ_prt = _CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_WORK_BO);

    
    //Фіксуємо максимальний фазний струм при КЗ
    unsigned int max_faze_current = measurement[IM_IA];
    if (max_faze_current < measurement[IM_IB_r]) max_faze_current = measurement[IM_IB_r];
    if (max_faze_current < measurement[IM_IC]) max_faze_current = measurement[IM_IC];
    
    if (max_faze_current > I_max_KZ_prt)
    {
      //Зафіксовано нове значення максимального фазного струму при КЗ
      I_max_KZ_prt = max_faze_current;
      
      //Визначаємо скільки фаз бере учать у КЗ
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
        //Є реально розраховані міжфазні опори

        //Фіксуємо мінімальний міжфазний реактивний опір при КЗ
        //Етап 1: Знаходим перший визначений фіжфазний опір і помічаємо його значення як найменше
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
          //Теоретично цього ніколи не мало б бути
          total_error_sw_fixed(68);
        }
      
        //Етап 2: Серед всіх визначених міжфазних опорів знаходимо найменше
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
      
        //Зафіксовано мінімальное значення міжфазного опору при КЗ
        X_min_KZ_prt = min_interphase_X;
        R_KZ_prt = R_KZ_tmp; //Поки що це число потрібно тільки для визначення знаку (щоб визначити у якому напямку відбулося КЗ)

//        //Етап 3: Перевіряємо чи мінімальний опір на цей момент не є мінімальним з початку виникнення КЗ
//        if (
//            (X_min_KZ_prt == ((unsigned int)UNDEF_RESISTANCE)) || /*Це є ознакою, що для даного КЗ ми перший раз фіксуємо мінімальний опір, тому і його значення помічаємо як мінімальне*/
//            (X_min_KZ_prt > min_interphase_X)
//           )
//        {
//          //Зафіксовано нове значення мінімального міжфазного опору при КЗ
//          X_min_KZ_prt = min_interphase_X;
//          R_KZ_prt = R_KZ_tmp; //Поки що це число потрібно тільки для визначення знаку (щоб визначити у якому напямку відбулося КЗ)
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
    //На даний момент немає фазного КЗ
    if(
       (vymknennja_vid_KZ_prt != 0) &&  /*Умова, що відбувалося вимкнення під час останнього КЗ*/
       ((number_of_phases_last_KZ = number_of_phases_KZ_prt) > 1) && /*Умова, що КЗ є міжфазним*/
       ((current_settings_prt.control_vmp & CTR_VMP_STATE) != 0) && /*ВМП ввімкнено*/ 
       (X_min_KZ_prt != ((unsigned int)UNDEF_RESISTANCE)) /*Умова, що хоча б один міжфазний опір був визначений, а тому і є зафіксований мінімальний реактивний міжфазний опір*/
      )
    {
      //Визначаємо віддаль до мсця пошкодження поки що без напрямку 
      unsigned int X_tmp = X_min_KZ_prt*current_settings_prt.TVoltage/current_settings_prt.TCurrent; /*Перерозраховуємо опір на первинну обмотку. Значення залишаємо у мОм*/
      
      unsigned int forward_backward = (R_KZ_prt < 0);
      unsigned int lines_tmp = current_settings_prt.lines[forward_backward];
      unsigned int defined_VMP = false;
      unsigned int i = 0;
      int VMP_tmp = 0;
      while ((defined_VMP == false) && (i < lines_tmp))
      {
        unsigned int dovgyna_tmp = current_settings_prt.dovgyna[forward_backward][i];
        unsigned int opir_tmp = current_settings_prt.opir[forward_backward][i];
        unsigned int X_current_line = dovgyna_tmp*opir_tmp/1000; /*розмірності*[м]x[мОм/км] =  [м]x[мОм/1000м] =[мОм]/1000 */
        if (X_tmp <= X_current_line)
        {
          //На даній ділянці зафіксовано пошкодження
//          VMP_tmp += (int)(((unsigned long long)dovgyna_tmp)*((unsigned long long)X_tmp)/((unsigned long long)X_current_line));
          VMP_tmp += X_tmp*1000/opir_tmp;
          defined_VMP = true;
        }
        else
        {
          //На даній ділянці ще не зафіксовано пошкодження
          VMP_tmp += dovgyna_tmp;
          X_tmp -= X_current_line;
        }
          
        i++;
      }
      
      //Остаточно визначаємо ВМП
      equal_more_KZ = defined_VMP;
      if(forward_backward == 0) VMP_last_KZ = VMP_tmp;
      else VMP_last_KZ = -VMP_tmp;
    }

    /*
    Повертаємо пограмне забезпечення у стан очікування нового КЗ
    
    Цю операцію може б треба було виконувати тільки раз після попереднрього КЗ,
    але оскільки  я не фіксую наявнясть КЗ, а тільки вимкнення при КЗ (короткочасне КЗ
    може не привести до вимкнення, або якщо сигнали працювали на сигналізацію, а не
    на вимкнення) - то щоб не ускладнювати програму, я зробив ці операції постійними коли немає КЗ
    Я думаю, що їх не так багато і вони б не мали сильно знизити ресурс процесора
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
//Контроль приводу вимикача
/*****************************************************/
void control_VV(unsigned int *activated_functions)
{
  unsigned int logic_control_VV_0 = 0;

  //"Контроль Вкл."
  logic_control_VV_0 |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_CTRL_VKL ) != 0) << 0;
  //"Контроль Откл."
  logic_control_VV_0 |= (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_CTRL_OTKL) != 0) << 1;
  
  _XOR_INVERTOR(logic_control_VV_0, 0, logic_control_VV_0, 1, logic_control_VV_0, 2);

  _TIMER_T_0(INDEX_TIMER_PRYVOD_VV, current_settings_prt.timeout_pryvoda_VV, logic_control_VV_0, 2, logic_control_VV_0, 3);

  //М:"Контроль ВВ"
  logic_control_VV_0 |= ((current_settings_prt.control_switch & CTR_PRYVOD_VV) != 0) << 4;
  
  _AND2(logic_control_VV_0, 3, logic_control_VV_0, 4, logic_control_VV_0, 5);
  
  activated_functions[RANG_OUTPUT_LED_DF_REG_PRYVID_VV >> 5] |= (_GET_OUTPUT_STATE(logic_control_VV_0, 5) << (RANG_OUTPUT_LED_DF_REG_PRYVID_VV & 0x1f));
}
/*****************************************************/

/*****************************************************/
//Розрахунок коефіцієнтрів для підрахунку ресурсу вимикача
/*****************************************************/
void make_koef_for_resurs(void)
{
  float tmp_1, tmp_2;
  
  tmp_1 = (float)current_settings.setpoint_r_kom_st_Inom/(float)current_settings.setpoint_r_kom_st_Inom_vymk;
  tmp_1  = log10f(tmp_1);

  tmp_2 = (float)current_settings.setpoint_Inom_vymk/(float)current_settings.setpoint_Inom;
  tmp_2  = log10f(tmp_2);
  
  //Помічаємо, що коефіцієнти для розрахунку ресурсу вимикача зараз будуть змінені
  koef_resurs_changed = CHANGED_ETAP_EXECUTION;

  K_resurs = tmp_1/tmp_2;
  
  //Помічаємо, що коефіцієнти для розрахунку ресурсу вимикача змінені і чекають на прийом системою захистів
  koef_resurs_changed = CHANGED_ETAP_ENDED;
}
/*****************************************************/

/*****************************************************/
//Лічильник ресурсу
/*****************************************************/
inline void resurs_vymykacha_handler(unsigned int *activated_functions, unsigned int *active_functions_tmp)
{
  if (restart_counter != 0)
  {
    //Треба подати команду очистки ресурсу вимикача
    resurs_vymykacha = current_settings_prt.setpoint_pochatkovyj_resurs;
    resurs_vidkljuchennja = current_settings_prt.setpoint_pochatkova_k_vymk;
    
     restart_counter = 0;

    //Запускаємо запис у EEPROM
    _SET_BIT(control_eeprom_taskes, TASK_START_WRITE_RESURS_EEPROM_BIT);

    //Помічаємо, що відбулася очистка ресурсу вимикача
    information_about_restart_counter |= ((1 << USB_RECUEST)|(1 << RS485_RECUEST));
  }
  
  /*******************************/
  //Визначаємо максимальний фазовий струм під час роботи Блоку Вимкнення (БО)
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
      //Зафіксовано старт роботи БО
      max_faze_current_vv = max_faze_current_tmp;
    }
    else if (_CHECK_SET_BIT(active_functions_tmp, RANG_OUTPUT_LED_DF_REG_WORK_BO) != 0)
    {
      //БО продовжує свою роботу
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
    //Зафіксовано завершення "Робота БО"
    
    /*******************************/
    //Обчислюється ресурс вимикачa
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
    
    //Загальне число переключень
    if ((0xffffffff - resurs_vidkljuchennja) >= 1)
    {
      //Додавання одиниці не викличе переповнення
      resurs_vidkljuchennja++;
    }

    //Запускаємо запис у EEPROM
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
//Перевірка на необхідність завершення роботи аналогового/дискретного реєстраторів
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
      //Зафіксовано, що ні одне джерело активації реєстратора зараз не активне
      
      if (
          ((carrent_active_functions[0] & MASKA_FOR_CONTINUE_GET_DR_ACTINE_WORD_0) == 0) &&
          ((carrent_active_functions[1] & MASKA_FOR_CONTINUE_GET_DR_ACTINE_WORD_1) == 0) &&
          ((carrent_active_functions[2] & MASKA_FOR_CONTINUE_GET_DR_ACTINE_WORD_2) == 0) &&
          ((carrent_active_functions[3] & MASKA_FOR_CONTINUE_GET_DR_ACTINE_WORD_3) == 0) &&
          ((carrent_active_functions[4] & MASKA_FOR_CONTINUE_GET_DR_ACTINE_WORD_4) == 0) &&
          ((carrent_active_functions[5] & MASKA_FOR_CONTINUE_GET_DR_ACTINE_WORD_5) == 0)
        )
      {
        //Зафіксовано, що всі функції, які можуть утримувати реєстратор активним зараз скинуті
          
        //Перевіряємо, чи всі таймери, які працють у логіці схеми виключені
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
          //Зафіксовано, що всі таймери, які працюють у лозіці неактивні
        
          //Помічаємо, що реєстратор може бути зупиненим
          stop = 0xff;
        }
      }
    }
  }
  
  return stop;
}
/*****************************************************/

/*****************************************************/
//Зафіксована невизначена помилка роботи дискретного реєстратора
/*****************************************************/
void fix_undefined_error_dr(unsigned int* carrent_active_functions)
{
  //Виставляємо помилку з записом в дисретний реєстратор
  _SET_BIT(set_diagnostyka, ERROR_DR_UNDEFINED_BIT);
  _SET_BIT(carrent_active_functions, RANG_OUTPUT_LED_DF_REG_DEFECT);
  //Переводимо режим роботи з реєстратором у сатн "На даний момент ніких дій з дискретним реєстратором не виконується" 
  state_dr_record = STATE_DR_NO_RECORD;
  //Скидаєсо сигнал роботи дискретного реєстратора
  _CLEAR_BIT(carrent_active_functions, RANG_OUTPUT_LED_DF_REG_WORK_D_REJESTRATOR);
}
/*****************************************************/

/*****************************************************/
//Початок моніторингу максимального фазного струму 
/*****************************************************/
inline void start_monitoring_max_phase_current(unsigned int time_tmp)
{
  //Збільшуємо кількість фіксованих значень максимального фазного струму
  number_max_phase_dr++;
  
  //Помічаємо, що будем виходити з того, що зараз значення тільки починають моніторитися, тому приймаємо їх за найбільші
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
  
  //Визначаємо макисальний фазний струм між трьома фазами
  max_phase_current_dr = measurements_phase_max_dr[2];
  if (max_phase_current_dr < measurements_phase_max_dr[3]) max_phase_current_dr = measurements_phase_max_dr[3];
  if (max_phase_current_dr < measurements_phase_max_dr[4]) max_phase_current_dr = measurements_phase_max_dr[4];

  //Фіксуємо час з моменту початку аварійного запису
  measurements_phase_max_dr[25] = time_tmp;

  //Помічаємо, що ми на стадії моніторингу максимального фазного струму
  state_current_monitoring |= (1<<IDENTIFIER_BIT_ARRAY_MAX_CURRENT_PHASE);
}
/*****************************************************/

/*****************************************************/
//Продовження моніторингу максимального фазного струму
/*****************************************************/
inline void continue_monitoring_max_phase_current(unsigned int time_tmp)
{
  //Перевірка, чи не є зарза фазний струм більший, ніж той що помічений максимальним
  if (
      (max_phase_current_dr < measurement[IM_IA  ]) ||
      (max_phase_current_dr < measurement[IM_IB_r]) ||
      (max_phase_current_dr < measurement[IM_IC  ])
     )
  {
    //Зафіксовано зріз при найвищому фазовому струмі з моменту початку спостереження за ним
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

    //Фіксуємо час з моменту початку аварійного запису
    measurements_phase_max_dr[25] = time_tmp;
  }
}
/*****************************************************/

/*****************************************************/
//Початок моніторингу максимального струму 3I0
/*****************************************************/
inline void start_monitoring_max_3I0(unsigned int time_tmp)
{
  //Збільшуємо кількість фіксованих значень максимального 3I0
  number_max_3I0_dr++;
  
  //Помічаємо, що будем виходити з того, що зараз значення тільки починають моніторитися, тому приймаємо їх за найбільші
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
  
  //Фіксуємо час з моменту початку аварійного запису
  measurements_3I0_max_dr[25] = time_tmp;
  
  //Помічаємо, що ми на стадії моніторингу максимального струму 3I0
  state_current_monitoring |= (1<<IDENTIFIER_BIT_ARRAY_MAX_CURRENT_3I0);
}
/*****************************************************/

/*****************************************************/
//Продовження моніторингу максимального струму 3I0
/*****************************************************/
inline void continue_monitoring_max_3I0(unsigned int time_tmp)
{
  //Перевірка, чи не є зарза струм 3I0 більший, ніж той що помічений максимальним
  if(
     ((current_settings_prt.control_zz & CTR_ZZ1_TYPE) == 0) && (measurements_3I0_max_dr[0] < measurement[IM_3I0])        ||
     ((current_settings_prt.control_zz & CTR_ZZ1_TYPE) != 0) && (measurements_3I0_max_dr[1] < measurement[IM_3I0_other_g])
    )
  {
    //Зафіксовано зріз при найвищому струмі 3I0 з моменту спостереження за ним
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

    //Фіксуємо час з моменту початку аварійного запису
    measurements_3I0_max_dr[25] = time_tmp;
  }
}
/*****************************************************/

/*****************************************************/
//Початок моніторингу максимальну напругу 3U0
/*****************************************************/
inline void start_monitoring_max_3U0(unsigned int time_tmp)
{
  //Збільшуємо кількість фіксованих значень максимальної 3U0
  number_max_3U0_dr++;
  
  //Помічаємо, що будем виходити з того, що зараз значення тільки починають моніторитися, тому приймаємо їх за найбільші
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
  
  //Фіксуємо час з моменту початку аварійного запису
  measurements_3U0_max_dr[25] = time_tmp;
  
  //Помічаємо, що ми на стадії моніторингу максимальної напруги 3U0
  state_current_monitoring |= (1<<IDENTIFIER_BIT_ARRAY_MAX_VOLTAGE_3U0);
}
/*****************************************************/

/*****************************************************/
//Продовження моніторингу максимального струму 3U0
/*****************************************************/
inline void continue_monitoring_max_3U0(unsigned int time_tmp)
{
  //Перевірка, чи не є зарза напруга 3U0 більша, ніж та що помічена максимальною
  if(measurements_3U0_max_dr[10] < measurement[IM_3U0_UBC_TN2])
  {
    //Зафіксовано зріз при найвищому струмі 3I0 з моменту спостереження за ним
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

    //Фіксуємо час з моменту початку аварійного запису
    measurements_3U0_max_dr[25] = time_tmp;
  }
}
/*****************************************************/

/*****************************************************/
//Початок моніторингу мінімальної фазної/лінійної напруги 
/*****************************************************/
inline void start_monitoring_min_U(unsigned int time_tmp)
{
  //Збільшуємо кількість фіксованих значень мінімальної фазної/лінійної напруги
  number_min_U_dr++;
  
  //Помічаємо, що будем виходити з того, що зараз значення тільки починають моніторитися, тому приймаємо їх за найменші
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
    //Визначаємо мінімальної фазну напругу між трьома фазами
    min_voltage_dr = measurements_U_min_dr[7];
    if (min_voltage_dr > measurements_U_min_dr[8]) min_voltage_dr = measurements_U_min_dr[8];
    if (min_voltage_dr > measurements_U_min_dr[9]) min_voltage_dr = measurements_U_min_dr[9];
  }
  else
  {
    //Визначаємо мінімальної лінійну напругу між трьома фазами
    min_voltage_dr = measurements_U_min_dr[12];
    if (min_voltage_dr > measurements_U_min_dr[13]) min_voltage_dr = measurements_U_min_dr[13];
    if (min_voltage_dr > measurements_U_min_dr[14]) min_voltage_dr = measurements_U_min_dr[14];
  }

  //Фіксуємо час з моменту початку аварійного запису
  measurements_U_min_dr[25] = time_tmp;

  //Помічаємо, що ми на стадії моніторингу мінімальної фазної/лінійної напруги
  state_current_monitoring |= (1<<IDENTIFIER_BIT_ARRAY_MIN_VOLTAGE);
}
/*****************************************************/

/*****************************************************/
//Продовження моніторингу мінімальної фазної/лінійної напруги
/*****************************************************/
inline void continue_monitoring_min_U(unsigned int time_tmp)
{
  //Перевірка, чи не є зарза досліджувана напуга менша, ніж та що помічена мінімальною
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
    //Зафіксовано зріз при найнижчій досліджуваній напрузі з моменту початку спостереження за нею
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
      //Визначаємо мінімальну фазну напругу між трьома фазами
      min_voltage_dr = measurements_U_min_dr[7];
      if (min_voltage_dr > measurements_U_min_dr[8]) min_voltage_dr = measurements_U_min_dr[8];
      if (min_voltage_dr > measurements_U_min_dr[9]) min_voltage_dr = measurements_U_min_dr[9];
    }
    else
    {
      //Визначаємо мінімальну лінійну напругу між трьома фазами
      min_voltage_dr = measurements_U_min_dr[12];
      if (min_voltage_dr > measurements_U_min_dr[13]) min_voltage_dr = measurements_U_min_dr[13];
      if (min_voltage_dr > measurements_U_min_dr[14]) min_voltage_dr = measurements_U_min_dr[14];
    }

    //Фіксуємо час з моменту початку аварійного запису
    measurements_U_min_dr[25] = time_tmp;
  }
}
/*****************************************************/

/*****************************************************/
//Початок моніторингу максимальної фазної/лінійної напруги 
/*****************************************************/
inline void start_monitoring_max_U(unsigned int time_tmp)
{
  //Збільшуємо кількість фіксованих значень максимальної фазної/лінійної напруги
  number_max_U_dr++;
  
  //Помічаємо, що будем виходити з того, що зараз значення тільки починають моніторитися, тому приймаємо їх за найбільші
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
    //Визначаємо макисальну фазну напругу між трьома фазами
    max_voltage_dr = measurements_U_max_dr[7];
    if (max_voltage_dr < measurements_U_max_dr[8]) max_voltage_dr = measurements_U_max_dr[8];
    if (max_voltage_dr < measurements_U_max_dr[9]) max_voltage_dr = measurements_U_max_dr[9];
  }
  else
  {
    //Визначаємо макисальну лінійну напругу між трьома фазами
    max_voltage_dr = measurements_U_max_dr[12];
    if (max_voltage_dr < measurements_U_max_dr[13]) max_voltage_dr = measurements_U_max_dr[13];
    if (max_voltage_dr < measurements_U_max_dr[14]) max_voltage_dr = measurements_U_max_dr[14];
  }

  //Фіксуємо час з моменту початку аварійного запису
  measurements_U_max_dr[25] = time_tmp;

  //Помічаємо, що ми на стадії моніторингу максимальної фазної/лінійної напруги
  state_current_monitoring |= (1<<IDENTIFIER_BIT_ARRAY_MAX_VOLTAGE);
}
/*****************************************************/

/*****************************************************/
//Продовження моніторингу максимальної фазної/лінійної напруги
/*****************************************************/
inline void continue_monitoring_max_U(unsigned int time_tmp)
{
  //Перевірка, чи не є зарза досліджувана напуга більша, ніж та що помічена максимальною
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
    //Зафіксовано зріз при найвищійу досліджуваній напрузі з моменту початку спостереження за нею
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
      //Визначаємо макисальну фазну напругу між трьома фазами
      max_voltage_dr = measurements_U_max_dr[7];
      if (max_voltage_dr < measurements_U_max_dr[8]) max_voltage_dr = measurements_U_max_dr[8];
      if (max_voltage_dr < measurements_U_max_dr[9]) max_voltage_dr = measurements_U_max_dr[9];
    }
    else
    {
      //Визначаємо макисальну лінійну напругу між трьома фазами
      max_voltage_dr = measurements_U_max_dr[12];
      if (max_voltage_dr < measurements_U_max_dr[13]) max_voltage_dr = measurements_U_max_dr[13];
      if (max_voltage_dr < measurements_U_max_dr[14]) max_voltage_dr = measurements_U_max_dr[14];
    }

    //Фіксуємо час з моменту початку аварійного запису
    measurements_U_max_dr[25] = time_tmp;
  }
}
/*****************************************************/

/*****************************************************/
//Початок моніторингу максимального струму  зворотньої послідовності
/*****************************************************/
inline void start_monitoring_max_ZOP(unsigned int time_tmp)
{
  //Збільшуємо кількість фіксованих значень максимального 3I0
  number_max_ZOP_dr++;
  
  //Помічаємо, що будем виходити з того, що зараз значення тільки починають моніторитися, тому приймаємо їх за найбільші
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

  //Фіксуємо час з моменту початку аварійного запису
  measurements_ZOP_max_dr[25] = time_tmp;

  //Помічаємо, що ми на стадії моніторингу максимального струму зворотньої послідовності
  state_current_monitoring |= (1<<IDENTIFIER_BIT_ARRAY_MAX_CURRENT_ZOP);
}
/*****************************************************/

/*****************************************************/
//Продовження моніторингу максимального струму зворотньої послідовності
/*****************************************************/
inline void continue_monitoring_max_ZOP(unsigned int time_tmp)
{
  //Перевірка, чи не є зарза струм зворотньої послідовності більший, ніж той що помічений максимальним
/*
      _I2 - струм зворотньої послідовності при попередньому зафіксованому максимальному відношенні I2/I1
      _I1 - струм прямої послідовності при попередньому зафіксованому максимальному відношенні I2/I1
      
      I2 -  текучий струм зворотньої послідовності
      I1 -  текучий струм прямої послідовності
      
      Умова перезапису параметрів:
      _I2     I2
      ---  < --- /x на _I1*I1  
      _I1     I1
      
      (_I2*I1 < I2*_I1)  - це є умова, що зараз є більше ЗОП(КОФ) ніж попередній раз
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
    //Зафіксовано зріз при найвищому струмі зворотньої послідовності з моменту початку запису
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

    //Фіксуємо час з моменту початку аварійного запису
    measurements_ZOP_max_dr[25] = time_tmp;
  }
}
/*****************************************************/

/*****************************************************/
//Початок моніторингу мінімальної частоти 1 
/*****************************************************/
inline void start_monitoring_min_f1(unsigned int time_tmp)
{
  //Збільшуємо кількість фіксованих значень мінімальної частоти 1
  number_min_f1_achr_dr++;
  
  //Помічаємо, що будем виходити з того, що зараз значення тільки починають моніторитися, тому приймаємо їх за найменші
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
  
  //Фіксуємо час з моменту початку аварійного запису
  measurements_f1_min_achr_dr[25] = time_tmp;

  //Помічаємо, що ми на стадії моніторингу мінімальної частоти
  state_current_monitoring |= (1<<IDENTIFIER_BIT_ARRAY_MIN_FREQUENCY_1_ACHR);
}
/*****************************************************/

/*****************************************************/
//Продовження моніторингу мінімальної частоти 1
/*****************************************************/
inline void continue_monitoring_min_f1(unsigned int time_tmp)
{
  if (((int)measurements_f1_min_achr_dr[15]) != (-2)) /*Не зафіксовано, що частота була нижче порогу визначеного константою MIN_FREQUENCY - інакше далі моніторити мінімальну частоту немає сенсу*/
  {
    //Перевірка, чи не є зарза досліджувана частота менша, ніж та що помічена мінімальною
    int frequency_val_1_int = (int)frequency_val_1;
    if (frequency_val_1_int >= 0) frequency_val_1_int = (int)(frequency_val_1*1000);
  
    int frequency_val_2_int = (int)frequency_val_2;
    if (frequency_val_2_int >= 0) frequency_val_2_int = (int)(frequency_val_2*1000);

    if(
       (frequency_val_1_int != (-1)) && /*Частота не визначена*/
       (frequency_val_1_int != (-3)) &&  /*Частота вище порогу визначеного константою MAX_FREQUENCY*/
       (
        (((int)measurements_f1_min_achr_dr[15]) > frequency_val_1_int) ||
        (frequency_val_1_int == (-2)) /*Частота нижче порогу визначеного константою MIN_FREQUENCY - цю перевірку робимо, бо у попередній момент часу могло крім значення частоти бути ще числа -1 або -3*/
       )   
      )   
    {
      //Зафіксовано зріз при найнижчій досліджуваній частоті з моменту початку спостереження за нею
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

      //Фіксуємо час з моменту початку аварійного запису
      measurements_f1_min_achr_dr[25] = time_tmp;
    }
  }
}
/*****************************************************/

/*****************************************************/
//Початок моніторингу мінімальної частоти 2 
/*****************************************************/
inline void start_monitoring_min_f2(unsigned int time_tmp)
{
  //Збільшуємо кількість фіксованих значень мінімальної частоти 2
  number_min_f2_achr_dr++;
  
  //Помічаємо, що будем виходити з того, що зараз значення тільки починають моніторитися, тому приймаємо їх за найменші
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
  
  //Фіксуємо час з моменту початку аварійного запису
  measurements_f2_min_achr_dr[25] = time_tmp;

  //Помічаємо, що ми на стадії моніторингу мінімальної частоти
  state_current_monitoring |= (1<<IDENTIFIER_BIT_ARRAY_MIN_FREQUENCY_2_ACHR);
}
/*****************************************************/

/*****************************************************/
//Продовження моніторингу мінімальної частоти 2
/*****************************************************/
inline void continue_monitoring_min_f2(unsigned int time_tmp)
{
  if (((int)measurements_f2_min_achr_dr[16]) != (-2)) /*Не зафіксовано, що частота була нижче порогу визначеного константою MIN_FREQUENCY - інакше далі моніторити мінімальну частоту немає сенсу*/
  {
    //Перевірка, чи не є зарза досліджувана частота менша, ніж та що помічена мінімальною
    int frequency_val_1_int = (int)frequency_val_1;
    if (frequency_val_1_int >= 0) frequency_val_1_int = (int)(frequency_val_1*1000);
  
    int frequency_val_2_int = (int)frequency_val_2;
    if (frequency_val_2_int >= 0) frequency_val_2_int = (int)(frequency_val_2*1000);

    if(
       (frequency_val_2_int != (-1)) && /*Частота не визначена*/
       (frequency_val_2_int != (-3)) &&  /*Частота вище порогу визначеного константою MAX_FREQUENCY*/
       (
        (((int)measurements_f2_min_achr_dr[16]) > frequency_val_2_int) ||
        (frequency_val_2_int == (-2)) /*Частота нижче порогу визначеного константою MIN_FREQUENCY - цю перевірку робимо, бо у попередній момент часу могло крім значення частоти бути ще числа -1 або -3*/
       )   
      )   
    {
      //Зафіксовано зріз при найнижчій досліджуваній частоті з моменту початку спостереження за нею
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

      //Фіксуємо час з моменту початку аварійного запису
      measurements_f2_min_achr_dr[25] = time_tmp;
    }
  }
}
/*****************************************************/

/*****************************************************/
//Завершення моніторингу максимального струму
/*
  type_current == IDENTIFIER_BIT_ARRAY_MAX_CURRENT_PHASE        - завершення моніторингу максимального фазного струму
  type_current == IDENTIFIER_BIT_ARRAY_MAX_CURRENT_3I0          - завершення моніторингу максимального струму 3I0
  type_current == IDENTIFIER_BIT_ARRAY_MAX_VOLTAGE_3U0          - завершення моніторингу максимального струму 3U0
  type_current == IDENTIFIER_BIT_ARRAY_MIN_VOLTAGE              - завершення моніторингу мінімальної напруги
  type_current == IDENTIFIER_BIT_ARRAY_MAX_VOLTAGE              - завершення моніторингу максимальної напруги
  type_current == IDENTIFIER_BIT_ARRAY_MAX_CURRENT_ZOP          - завершення моніторингу максимального струму зворотньої послідовності
  type_current == IDENTIFIER_BIT_ARRAY_MIN_FREQUENCY_1_ACHR     - завершення моніторингу мінімальної частоти 1 для АЧР
  type_current == IDENTIFIER_BIT_ARRAY_MIN_FREQUENCY_2_ACHR     - завершення моніторингу мінімальної частоти 2 для АЧР
  type_current == IDENTIFIER_BIT_ARRAY_FREQUENCY_1_CHAPV        - фіксація частоти 1 для ЧАПВ
  type_current == IDENTIFIER_BIT_ARRAY_FREQUENCY_2_CHAPV        - фіксація частоти 2 для ЧАПВ
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
    
    //Перевірка на коректність роботи програмного забеспечення
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
      
      //Визначаємо джерело звідки  будемо копіювати дані
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
      
      //Визначаємо адресу киди дані треба копіювати
      step -= 1; //Тому що  нумерація починається з 0, а не з 1 (step гарантовано не менше 1(це перевірено вище), тому від'ємного числа не може бути)
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
            //У останній байт масиву, що відповідає згідно з Little-endian формату старшову байту останнього елементу масиву, мітку типу струму, по якому фіксувався максимальний струм
            *(output_data_point + i) = type_current;
          }
        }

        //Знімаємо помітку, що ми на стадії моніторингу 
        state_current_monitoring &= ~(1<<type_current);
      }
      else
      {
        //Відбулася незрозуміла ситуація - сюди програма теоретично ніколи не мала б заходити
        fix_undefined_error_dr(carrent_active_functions);
      }
    }
    else
    {
      //Відбулася незрозуміла ситуація - сюди програма теоретично ніколи не мала б заходити
      fix_undefined_error_dr(carrent_active_functions);
    }
  }
  else
  {
    //Відбулася незрозуміла ситуація - сюди програма теоретично ніколи не мала б заходити
    fix_undefined_error_dr(carrent_active_functions);
  }
}
/*****************************************************/

/*****************************************************/
//Подача команди почати запис у DataFalsh
/*****************************************************/
inline void command_start_saving_record_dr_into_dataflash(void)
{
  //У структурі по інформації стану реєстраторів виставляємо повідомлення, що почався запис і ще не закінчився
  _SET_BIT(control_eeprom_taskes, TASK_START_WRITE_INFO_REJESTRATOR_DR_EEPROM_BIT);
  info_rejestrator_dr.saving_execution = 1;
        
  //Виставляємо першу частину запису
  part_writing_dr_into_dataflash = 0;
  //Виставляємо команду запису у мікросхему DataFlash
  control_tasks_dataflash |= TASK_MAMORY_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_DR;
}
/*****************************************************/

/*****************************************************/
//Функція обробки черги зформованих записів дискретного реєстратора
/*****************************************************/
inline void routine_for_queue_dr(void)
{
  if(
     (state_dr_record == STATE_DR_MAKE_RECORD)            || /*Стоїть умова сформовані дані передати на запис у DataFlsh без повторного початку  нового запису, бо умова завершення запиу    досягнкта, а не стояла умова примусового завершення даного сформованого запису*/
     (state_dr_record == STATE_DR_CUT_RECORD)             || /*Стоїть умова сформовані дані передати на запис у DataFlsh   з повторним  початком нового запису, бо умова завершення запиу не досягнкта, а    стояла умова примусового завершення даного сформованого запису*/
     (number_records_dr_waiting_for_saving_operation != 0)  
    )
  {
    if ((control_tasks_dataflash & TASK_MAMORY_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_DR) == 0)
    {
      //На даний момент запису у Datafalsh не проводиться
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
        
      //Подаємо команду почати запис у DataFalsh
      command_start_saving_record_dr_into_dataflash();
    }
    else
    {
      //На даний момент запису у Datafalsh проводиться
      //Треба наш теперішній запис поставити у чергу
      if (number_records_dr_waiting_for_saving_operation == 0)
      {
        //На даний момент крім того, буфера - з якого іде безпосередній запис у DataFalsh, більше ніяких записів у черзі немає
        //Переміщаємо текучий запис у буфер buffer_for_save_dr_record_level_1
        for(unsigned int i = 0; i < SIZE_BUFFER_FOR_DR_RECORD; i++) buffer_for_save_dr_record_level_1[i] = buffer_for_save_dr_record[i];
    
        //Помічаємо, що один запис очікує передау його на безпосередній запис у dataFalsh
        number_records_dr_waiting_for_saving_operation = 1;
      }
      else if (number_records_dr_waiting_for_saving_operation >= 1)
      {
         if((state_dr_record == STATE_DR_MAKE_RECORD) || (state_dr_record == STATE_DR_CUT_RECORD))
         {
          //На даний момент крім того, буфера - з якого іде безпосередній запис у DataFalsh, ще один сформований запис стоїть у буфері buffer_for_save_dr_record_level_1
          /*
          Тому даний запис залишаємо у цьому самому буфері buffer_for_save_dr_record, але збільшуємо кількість записів. які стоять у черзі
          і якщо буде спроба почати новий запис, то будемо фіксувати помилку втрати даних
          */
          number_records_dr_waiting_for_saving_operation = 2;
         }
      }
    }
    
    if (state_dr_record == STATE_DR_MAKE_RECORD)
    {
      //Помічаємо, що ми готові приймати наступний запис
      state_dr_record = STATE_DR_NO_RECORD;
    }
    else if (state_dr_record == STATE_DR_CUT_RECORD)
    {
      //Помічаємо, що треба примусово запустити новий запис
      state_dr_record = STATE_DR_FORCE_START_NEW_RECORD;
    }
      
  }
}
/*****************************************************/

/*****************************************************/
//Функція обробки логіки дискретного реєстратора
/*****************************************************/
inline void digital_registrator(unsigned int* carrent_active_functions, unsigned int volatile* previous_active_functions, unsigned int number_group_stp)
{
  static unsigned int number_items_dr;
  static unsigned int number_changes_into_dr_record;
  static unsigned int time_from_start_record_dr;
  static unsigned int blocking_continue_monitoring_min_U;
  
  //Цю перевірку виконуємо тільки у тому випадку, коли іде процес формування нового запису
  if(state_dr_record == STATE_DR_EXECUTING_RECORD)
  {
    //Перевіряємо чи не виникла умова, що зарараз буде перебір фіксації максимальних струмів
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
      //Сюди, теоретично програма нікол не мала б заходити, але якщо зайшла, тоиреба перервати роботу дискретного реєстратора
      fix_undefined_error_dr(carrent_active_functions);

      /*
      Скидаємо сигнал роботи дискретного реєстратора у масиві попередніх активних функцій
      Це ми робимо для того, щоб у першому записі нового запису було зафіксовано активацію роботу дискретного реєстратора
      */
      _CLEAR_BIT(previous_active_functions, RANG_OUTPUT_LED_DF_REG_WORK_D_REJESTRATOR);
    }
    else
    {
      //Перевіряємо чи стоїть умова почати моніторити максимальний фазний струм
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
          //Є умова почати новий моніторинг максимального фазного струму
          temp_value_for_max_min_fix_measurement++;
        }
      }

      //Перевіряємо чи стоїть умова почати моніторити максимальний струм 3I0
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
          //Є умова почати новий моніторинг максимального струму 3I0
          temp_value_for_max_min_fix_measurement++;
        }
      }
      
      //Перевіряємо чи стоїть умова почати моніторити максимальну напругу 3U0
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
          //Є умова почати новий моніторинг максимальну напругу 3U0
          temp_value_for_max_min_fix_measurement++;
        }
      }
      
      //Перевіряємо чи стоїть умова почати моніторити мінімальну напругу
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
            //Є умова почати новий моніторинг мінімальну фазну напругу
            temp_value_for_max_min_fix_measurement++;
          }
        }
      }
      
      //Перевіряємо чи стоїть умова почати моніторити максимальну напругу
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
          //Є умова почати новий моніторинг максимальну фазну напругу
          temp_value_for_max_min_fix_measurement++;
        }
      }
      
      //Перевіряємо чи стоїть умова почати моніторити максимальний струм зворотньої послідовності
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
          //Є умова почати новий моніторинг максимального струму зворотнньої послідовності
          temp_value_for_max_min_fix_measurement++;
        }
      }
    
      //Перевіряємо чи стоїть умова почати моніторити мінімальну частоту 1 для АЧР
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
          //Є умова почати новий моніторинг мінімальну частоту
          temp_value_for_max_min_fix_measurement++;
        }
      }
      
      //Перевіряємо чи стоїть умова почати моніторити мінімальну частоту 2 для АЧР
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
          //Є умова почати новий моніторинг мінімальну частоту
          temp_value_for_max_min_fix_measurement++;
        }
      }

      //Є умова дозволу подачі команди ЧАПВ
      if (_CHECK_SET_BIT(carrent_active_functions , RANG_OUTPUT_LED_DF_REG_BLOCK_CHAPV_VID_U) == 0)
      {
        //Перевіряємо чи стоїть умова зафіксувати частоту 1 і частоту 2 для зовнішнього ЧАПВ
        if(
           (_CHECK_SET_BIT(previous_active_functions, RANG_OUTPUT_LED_DF_REG_ACHR_CHAPV_VID_DV) != 0) &&
           (_CHECK_SET_BIT(carrent_active_functions , RANG_OUTPUT_LED_DF_REG_ACHR_CHAPV_VID_DV) == 0)
          )   
        {
          //Є умова зафіксувати частоту 1 і частоту 2 від зовнішнього ЧАПВ
          temp_value_for_max_min_fix_measurement += 2;
        }
        else if (_CHECK_SET_BIT(carrent_active_functions , RANG_OUTPUT_LED_DF_REG_RAZR_CHAPV) != 0)
        {
          //Є дозвіл роботи ЧАПВ від внутрішньої логіки
          
          //Перевіряємо чи стоїть умова зафіксувати частоту 1 для ЧАПВ
          if (  
              (_CHECK_SET_BIT(previous_active_functions, RANG_OUTPUT_LED_DF_REG_F1_ACHR_CHAPV  ) != 0) &&
              (_CHECK_SET_BIT(carrent_active_functions , RANG_OUTPUT_LED_DF_REG_F1_ACHR_CHAPV  ) == 0)
             )   
          {
            //Є умова зафіксувати частоту 1 від ЧАПВ
            temp_value_for_max_min_fix_measurement++;
          }

          //Перевіряємо чи стоїть умова зафіксувати частоту 2 для ЧАПВ
          if (  
              (_CHECK_SET_BIT(previous_active_functions, RANG_OUTPUT_LED_DF_REG_F2_ACHR_CHAPV  ) != 0) &&
              (_CHECK_SET_BIT(carrent_active_functions , RANG_OUTPUT_LED_DF_REG_F2_ACHR_CHAPV  ) == 0)
             )   
          {
            //Є умова зафіксувати частоту 2 від ЧАПВ
            temp_value_for_max_min_fix_measurement++;
          }
        }
      }
          
      
      if(temp_value_for_max_min_fix_measurement > MAX_NUMBER_FIX_MAX_MEASUREMENTS)
      {
        //Виникла ситуація, що зарараз буде перебір фіксації максимальних вимірювань
        //Треба примусово завершити текучий запис і почати наступний запис

        buffer_for_save_dr_record[FIRST_INDEX_NUMBER_ITEMS_DR      ] = number_items_dr;
        buffer_for_save_dr_record[FIRST_INDEX_NUMBER_CHANGES_DR    ] = number_changes_into_dr_record        & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_NUMBER_CHANGES_DR + 1] = (number_changes_into_dr_record >> 8) & 0xff;

        //Перевіряємо чи треба завершити моніторинг максимального фазного струму
        if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MAX_CURRENT_PHASE)) != 0)
          end_monitoring_min_max_measurement(IDENTIFIER_BIT_ARRAY_MAX_CURRENT_PHASE, carrent_active_functions);

        //Перевіряємо чи треба завершити моніторинг максимального струму 3I0
        if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MAX_CURRENT_3I0)) != 0)
          end_monitoring_min_max_measurement(IDENTIFIER_BIT_ARRAY_MAX_CURRENT_3I0, carrent_active_functions);

        //Перевіряємо чи треба завершити моніторинг максимальної напруги 3U0
        if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MAX_VOLTAGE_3U0)) != 0)
          end_monitoring_min_max_measurement(IDENTIFIER_BIT_ARRAY_MAX_VOLTAGE_3U0, carrent_active_functions);

        //Перевіряємо чи треба завершити моніторинг мінімальної напруги
        if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MIN_VOLTAGE)) != 0)
          end_monitoring_min_max_measurement(IDENTIFIER_BIT_ARRAY_MIN_VOLTAGE, carrent_active_functions);

        //Перевіряємо чи треба завершити моніторинг максимальної напруги
        if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MAX_VOLTAGE)) != 0)
          end_monitoring_min_max_measurement(IDENTIFIER_BIT_ARRAY_MAX_VOLTAGE, carrent_active_functions);

        //Перевіряємо чи треба завершити моніторинг максимального струму послідовності
        if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MAX_CURRENT_ZOP)) != 0)
          end_monitoring_min_max_measurement(IDENTIFIER_BIT_ARRAY_MAX_CURRENT_ZOP, carrent_active_functions);
        
        //Перевіряємо чи треба завершити моніторинг мінімальної частоти 1 для АЧР
        if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MIN_FREQUENCY_1_ACHR)) != 0)
          end_monitoring_min_max_measurement(IDENTIFIER_BIT_ARRAY_MIN_FREQUENCY_1_ACHR, carrent_active_functions);

        //Перевіряємо чи треба завершити моніторинг мінімальної частоти 2 для АЧР
        if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MIN_FREQUENCY_2_ACHR)) != 0)
          end_monitoring_min_max_measurement(IDENTIFIER_BIT_ARRAY_MIN_FREQUENCY_2_ACHR, carrent_active_functions);

        //Дальші дії виконуємо тіьлки у тому випадку, якщо функція end_monitoring_min_max_measurement не зафіксувала помилку і не скинула state_dr_record у STATE_DR_NO_RECORD
        if(state_dr_record != STATE_DR_NO_RECORD)
        {
          //Записуємо кількість зафіксованих максимальних струмів всіх типів
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

          //Помічаємо, що треба при першій же нагоді почати новий запис, бо попередній запис був примусово зупинений
          state_dr_record = STATE_DR_CUT_RECORD;
        
          //Скидаємо сигнал роботи дискретного реєстратора
          _CLEAR_BIT(carrent_active_functions, RANG_OUTPUT_LED_DF_REG_WORK_D_REJESTRATOR);
        
          //Сформований запис ставим в чергу для запису
          routine_for_queue_dr();
        }
        /*
        Скидаємо сигнал роботи дискретного реєстратора у масиві попередніх активних функцій
        Це ми робимо для того, щоб у першому записі нового запису було зафіксовано активацію роботу дискретного реєстратора
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
      //Попередньо скидаємо невизначену помилку  роботи дискретного реєстратора
      _SET_BIT(clear_diagnostyka, ERROR_DR_UNDEFINED_BIT);
      if(number_records_dr_waiting_for_saving_operation < (WIGHT_OF_DR_WAITING - 1))
      {
        //Ця ситуація означає, що як мінімум на один новий запис у нас є вільне місц, тому скидаємо сигналізацію про втрату даних
        _SET_BIT(clear_diagnostyka, ERROR_DR_TEMPORARY_BUSY_BIT);
      }
      
      //На початок аналізу покищо ще дискретний реєстратор не запущений
      
      //Аналізуємо, чи стоїть умова запуску дискретного реєстратора
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
        //Є умова запуску дискретного реєстратора
        
        //Перевіряємо, чи при початку нового запису ми не втратимо попередню інформацію
        if(number_records_dr_waiting_for_saving_operation < WIGHT_OF_DR_WAITING)
        {
          //Можна починати новий запис
          
          //Переводимо режим роботи із дискретним реєстратором у стан "Іде процес запису реєстратора"
          state_dr_record = STATE_DR_EXECUTING_RECORD;
          //Виставляємо активну функцію
          _SET_BIT(carrent_active_functions, RANG_OUTPUT_LED_DF_REG_WORK_D_REJESTRATOR);
        
          //Записуємо мітку початку запису
          buffer_for_save_dr_record[FIRST_INDEX_START_START_RECORD_DR] = LABEL_START_RECORD_DR;
         
          //Записуємо час початку запису
          unsigned char *label_to_time_array;
          if (copying_time == 2) label_to_time_array = time_copy;
          else label_to_time_array = time;
          for(unsigned int i = 0; i < 7; i++) buffer_for_save_dr_record[FIRST_INDEX_DATA_TIME_DR + i] = *(label_to_time_array + i);
          
          //Додаткові налаштування при яких було запущено дискретний реєстратор
          unsigned int control_extra_settings_1_tmp = current_settings_prt.control_extra_settings_1 & (CTR_EXTRA_SETTINGS_1_CTRL_3U0_Ubc_TN2 | CTR_EXTRA_SETTINGS_1_CTRL_PHASE_LINE);
          unsigned char *point_to_extra_settings = (unsigned char *)(&control_extra_settings_1_tmp);
          for (unsigned int i = 0; i < sizeof(control_extra_settings_1_tmp); i++)
            buffer_for_save_dr_record[FIRST_INDEX_EXTRA_SETTINGS_DR + i] = *(point_to_extra_settings + i);

           //І'мя комірки
          for(unsigned int i=0; i< MAX_CHAR_IN_NAME_OF_CELL; i++) 
            buffer_for_save_dr_record[FIRST_INDEX_NAME_OF_CELL_DR + i] = current_settings_prt.name_of_cell[i] & 0xff;
          
          //Помічаємо скільки часу пройшло з початку запуску запису
          time_from_start_record_dr = 0;
          
          //Скидаємо кількість фіксацій максимальних струмів/напруг
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
          
          //Знімаємо повідомлення про моніторинг максимальних струмів
          state_current_monitoring = 0;
          
          //Перевіряємо чи стоїть умова моніторити максимальний фазний струм
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

          //Перевіряємо чи стоїть умова моніторити максимальний струм 3I0
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

          //Перевіряємо чи стоїть умова моніторити максимальну напругу 3U0
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

          //Знімаємо блокування моніторингу мінімальної напруги
          blocking_continue_monitoring_min_U = 0;
          //Перевіряємо чи стоїть умова моніторити мінімальну напругу
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
          //Перевіряємо, чи стоїть умова припинити моніторинг мінімальної напруги після вимкнення вимикача
          if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MIN_VOLTAGE)) != 0)
          {
            if (_CHECK_SET_BIT(carrent_active_functions, RANG_OUTPUT_LED_DF_REG_WORK_BO) != 0)
            {
              blocking_continue_monitoring_min_U = 0xff;
              end_monitoring_min_max_measurement(IDENTIFIER_BIT_ARRAY_MIN_VOLTAGE, carrent_active_functions);
            }
          }

          //Перевіряємо чи стоїть умова моніторити максимальну напругу
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

          //Перевіряємо чи стоїть умова моніторити максимальний струм зворотньої послідовності
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
      
          //Перевіряємо чи стоїть умова моніторити мінімальну частоту 1
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
          Перевірку необхідності запису фіксація вимірювань при роботі ЧАПВ здійснювати
          не потрібно, тому що ми тільки запустили дискретний реєстратор, а умова запису
          вимірювань при запуску ЧАПВ складається з двох зрізів у яких чиснал ЧАПВ
          здійснює перехід "Активний"->"Пасивний"
          */

          //Записуємо попередній cтан сигналів перед аварією
          //Мітка часу попереднього стану сигналів до моменту початку запису
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR +  0] = 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR +  1] = 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR +  2] = 0xff;
          //Попередній стан
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
          //Нулем позначаємо у цій позиції кількість змін
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 27] = 0;

          //Помічаємо кількість нових зрізів
          number_items_dr = 1;
      
          //Вираховуємо кількість змін сигналів
          number_changes_into_dr_record = 0;
          unsigned int number_changes_into_current_item;
          _NUMBER_CHANGES_INTO_UNSIGNED_INT_ARRAY(previous_active_functions, carrent_active_functions, N_BIG, number_changes_into_current_item);
          number_changes_into_dr_record += number_changes_into_current_item;
      
          //Записуємо текучий cтан сигналів
          //Мітка часу
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*28 +  0] =  time_from_start_record_dr        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*28 +  1] = (time_from_start_record_dr >> 8 ) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*28 +  2] = (time_from_start_record_dr >> 16) & 0xff;
          //Текучий стан сигналів
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
          
          //Кількість змін сигналів у порівнянні із попереднім станом
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*28 + 27] = number_changes_into_current_item & 0xff;
      
          //Решту масиву очищаємо, щоб у запис не пішла інформація із попередніх записів
          for(unsigned int i = FIRST_INDEX_FIRST_BLOCK_DR; i < FIRST_INDEX_FIRST_DATA_DR; i++)
            buffer_for_save_dr_record[i] = 0xff;
          for(unsigned int i = (FIRST_INDEX_FIRST_DATA_DR + (number_items_dr + 1)*28); i < SIZE_BUFFER_FOR_DR_RECORD; i++)
            buffer_for_save_dr_record[i] = 0xff;
        }
        else
        {
          //Виставляємо помилку, що є умова на роботу дискретного реєстратора тоді, як всі вільні буфери зайняті
          _SET_BIT(set_diagnostyka, ERROR_DR_TEMPORARY_BUSY_BIT);
          _SET_BIT(carrent_active_functions, RANG_OUTPUT_LED_DF_REG_DEFECT);
        }
      }
      else state_dr_record = STATE_DR_NO_RECORD;
      
      break;
    }
  case STATE_DR_EXECUTING_RECORD:
    {
      //Збільшуємо час з початку запуску запису
      time_from_start_record_dr++;
      //Включно до цього часу іде процес запису

      //Контроль-фіксація максимальних аналогових сигналів
      
      //Перевіряємо чи стоїть умова моніторити максимальний фазний струм
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

      //Перевіряємо чи стоїть умова моніторити максимальний струм 3I0
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
      
      //Перевіряємо чи стоїть умова моніторити максимальну напругу 3U0
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
      
      //Перевіряємо чи стоїть умова відновити моніторинг мінімальної напруги
      if (_CHECK_SET_BIT(carrent_active_functions, RANG_OUTPUT_LED_DF_REG_WORK_BV) != 0)
      {
        //Знімаємо блокування моніторингу мінімальної напруги
        blocking_continue_monitoring_min_U = 0;
      }
      //Перевіряємо чи стоїть умова моніторити мінімальну напругу
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
      //Перевіряємо, чи стоїть умова припинити моніторинг мінімальної напруги після вимкнення вимикача
      if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MIN_VOLTAGE)) != 0)
      {
        if (_CHECK_SET_BIT(carrent_active_functions, RANG_OUTPUT_LED_DF_REG_WORK_BO) != 0)
        {
          blocking_continue_monitoring_min_U = 0xff;
          end_monitoring_min_max_measurement(IDENTIFIER_BIT_ARRAY_MIN_VOLTAGE, carrent_active_functions);
        }
      }
      
      //Перевіряємо чи стоїть умова моніторити максимальну напругу
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
      
      //Перевіряємо чи стоїть умова моніторити максимальний струм зворотньої послідовності
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
      
      //Перевіряємо чи стоїть умова моніторити мінімальну частоту 1 для АЧР
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
      
      //Перевіряємо чи стоїть умова моніторити мінімальну частоту 2 для АЧР
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
      
      //Є умова дозволу подачі команди ЧАПВ
      if (_CHECK_SET_BIT(carrent_active_functions , RANG_OUTPUT_LED_DF_REG_BLOCK_CHAPV_VID_U) == 0)
      {
        //Перевіряємо чи стоїть умова зафіксувати частоту 1 і частоту 2 для зовнішнього ЧАПВ
        if(
           (_CHECK_SET_BIT(previous_active_functions, RANG_OUTPUT_LED_DF_REG_ACHR_CHAPV_VID_DV) != 0) &&
           (_CHECK_SET_BIT(carrent_active_functions , RANG_OUTPUT_LED_DF_REG_ACHR_CHAPV_VID_DV) == 0)
          )   
        {
          //Є умова зафіксувати частоту 1 і частоту 2 від зовнішнього ЧАПВ
          
          //Збільшуємо кількість фіксованих значень частоти 1 і частоти 2 від ЧАПВ
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
  
          //Фіксуємо час з моменту початку аварійного запису
          measurements_f2_chapv_dr[25] = measurements_f1_chapv_dr[25] = time_from_start_record_dr;

          //Помічаємо, що ми фіксуємо чатоту 1 і частоту 2 від ЧАПВ
          state_current_monitoring |= ((1<<IDENTIFIER_BIT_ARRAY_FREQUENCY_1_CHAPV) | (1<<IDENTIFIER_BIT_ARRAY_FREQUENCY_2_CHAPV));
            
          //Зразу цю подію фіксуємо у масив, який формує поточний запис (для частоти 1)
          end_monitoring_min_max_measurement(IDENTIFIER_BIT_ARRAY_FREQUENCY_1_CHAPV, carrent_active_functions);
          //Зразу цю подію фіксуємо у масив, який формує поточний запис (для частоти 2)
          end_monitoring_min_max_measurement(IDENTIFIER_BIT_ARRAY_FREQUENCY_2_CHAPV, carrent_active_functions);
        }
        else if (_CHECK_SET_BIT(carrent_active_functions , RANG_OUTPUT_LED_DF_REG_RAZR_CHAPV) != 0)
        {
          //Є дозвіл роботи ЧАПВ від внутрішньої логіки
          
          //Перевіряємо чи стоїть умова зафіксувати частоту 1 для ЧАПВ
          if (  
              (_CHECK_SET_BIT(previous_active_functions, RANG_OUTPUT_LED_DF_REG_F1_ACHR_CHAPV  ) != 0) &&
              (_CHECK_SET_BIT(carrent_active_functions , RANG_OUTPUT_LED_DF_REG_F1_ACHR_CHAPV  ) == 0)
             )   
          {
            //Є умова зафіксувати частоту 1 від ЧАПВ
            
            //Збільшуємо кількість фіксованих значень частоти 1 від ЧАПВ
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
  
            //Фіксуємо час з моменту початку аварійного запису
            measurements_f1_chapv_dr[25] = time_from_start_record_dr;

            //Помічаємо, що ми фіксуємо чатоту 1 від ЧАПВ
            state_current_monitoring |= (1<<IDENTIFIER_BIT_ARRAY_FREQUENCY_1_CHAPV);
            
            //Зразу цю подію фіксуємо у масив, який формує поточний запис
            end_monitoring_min_max_measurement(IDENTIFIER_BIT_ARRAY_FREQUENCY_1_CHAPV, carrent_active_functions);
          }

          //Перевіряємо чи стоїть умова зафіксувати частоту 2 для ЧАПВ
          if (  
              (_CHECK_SET_BIT(previous_active_functions, RANG_OUTPUT_LED_DF_REG_F2_ACHR_CHAPV  ) != 0) &&
              (_CHECK_SET_BIT(carrent_active_functions , RANG_OUTPUT_LED_DF_REG_F2_ACHR_CHAPV  ) == 0)
             )   
          {
            //Є умова зафіксувати частоту 2 від ЧАПВ

            //Збільшуємо кількість фіксованих значень частоти 2 від ЧАПВ
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
  
            //Фіксуємо час з моменту початку аварійного запису
            measurements_f2_chapv_dr[25] = time_from_start_record_dr;

            //Помічаємо, що ми фіксуємо чатоту 2 від ЧАПВ
            state_current_monitoring |= (1<<IDENTIFIER_BIT_ARRAY_FREQUENCY_2_CHAPV);
            
            //Зразу цю подію фіксуємо у масив, який формує поточний запис
            end_monitoring_min_max_measurement(IDENTIFIER_BIT_ARRAY_FREQUENCY_2_CHAPV, carrent_active_functions);
          }
        }
      }
      
      //Дальші дії виконуємо тіьлки у тому випадку, якщо функція end_monitoring_min_max_measurement не зафіксувала помилку і не скинула state_dr_record у STATE_DR_NO_RECORD
      if(state_dr_record != STATE_DR_NO_RECORD)
      {
        //Перевіряємо, чи ще існує умова продовження запису
        //Якщо такої умови немає - то скидаємо сигнал запущеного дискретного реєстратора, що це зафіксувати у змінених сигналах
        if (stop_regisrator(carrent_active_functions, current_settings_prt.ranguvannja_digital_registrator, number_group_stp) != 0)
        {
          //Скидаємо сигнал роботи дискретного реєстратора
          _CLEAR_BIT(carrent_active_functions, RANG_OUTPUT_LED_DF_REG_WORK_D_REJESTRATOR);

          //Переводимо режим роботи із дискретним реєстратором у стан "Виконується безпосередній запис у послідовну DataFlash"
          state_dr_record = STATE_DR_MAKE_RECORD;
        }
      
        //Перевіряємо чи відбуласа зміна сигналів у порівнянні із попереднім станом. Якщо така зміна є, то формуєм новий зріз сигналів у записі
        if (
            ((carrent_active_functions[0] != previous_active_functions[0])) ||
            ((carrent_active_functions[1] != previous_active_functions[1])) ||
            ((carrent_active_functions[2] != previous_active_functions[2])) ||
            ((carrent_active_functions[3] != previous_active_functions[3])) ||
            ((carrent_active_functions[4] != previous_active_functions[4])) ||
            ((carrent_active_functions[5] != previous_active_functions[5])) 
           )
        {
          //Теперішній стан сигналів не співпадає з попереднім станом сигналів

          //Збільшуємо на один кількість нових зрізів
          number_items_dr++;
      
          //Вираховуємо кількість змін сигналів
          unsigned int number_changes_into_current_item;
          _NUMBER_CHANGES_INTO_UNSIGNED_INT_ARRAY(previous_active_functions, carrent_active_functions, N_BIG, number_changes_into_current_item);
          number_changes_into_dr_record += number_changes_into_current_item;
      
          //Записуємо текучий cтан сигналів
          //Мітка часу
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*28 +  0] =  time_from_start_record_dr        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*28 +  1] = (time_from_start_record_dr >> 8 ) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*28 +  2] = (time_from_start_record_dr >> 16) & 0xff;
          //Текучий стан сигналів
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
          //Кількість змін сигналів у порівнянні із попереднім станом
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*28 + 27] = number_changes_into_current_item & 0xff;
        }
        
        //Перевіряємо, чи стоїть умова завершення запису
        if (
            (state_dr_record == STATE_DR_MAKE_RECORD)                  ||
            (time_from_start_record_dr >= MAX_TIME_OFFSET_FROM_START)  ||  
            ((number_items_dr + 1)     >= MAX_EVENTS_IN_ONE_RECORD  )  
           )
        {
          //Немає умови продовження запису, або є умова завершення запису - завершуємо формування запису і подаємо команду на запис
          buffer_for_save_dr_record[FIRST_INDEX_NUMBER_ITEMS_DR      ] = number_items_dr;
          buffer_for_save_dr_record[FIRST_INDEX_NUMBER_CHANGES_DR    ] =  number_changes_into_dr_record       & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_NUMBER_CHANGES_DR + 1] = (number_changes_into_dr_record >> 8) & 0xff;

          //Перевіряємо чи треба завершити моніторинг максимального фазного струму
          if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MAX_CURRENT_PHASE)) != 0)
            end_monitoring_min_max_measurement(IDENTIFIER_BIT_ARRAY_MAX_CURRENT_PHASE, carrent_active_functions);

          //Перевіряємо чи треба завершити моніторинг максимального струму 3I0
          if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MAX_CURRENT_3I0)) != 0)
            end_monitoring_min_max_measurement(IDENTIFIER_BIT_ARRAY_MAX_CURRENT_3I0, carrent_active_functions);

          //Перевіряємо чи треба завершити моніторинг максимальну напругу 3U0
          if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MAX_VOLTAGE_3U0)) != 0)
            end_monitoring_min_max_measurement(IDENTIFIER_BIT_ARRAY_MAX_VOLTAGE_3U0, carrent_active_functions);

          //Перевіряємо чи треба завершити моніторинг мінімальну напругу
          if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MIN_VOLTAGE)) != 0)
            end_monitoring_min_max_measurement(IDENTIFIER_BIT_ARRAY_MIN_VOLTAGE, carrent_active_functions);

          //Перевіряємо чи треба завершити моніторинг максимальну напругу
          if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MAX_VOLTAGE)) != 0)
            end_monitoring_min_max_measurement(IDENTIFIER_BIT_ARRAY_MAX_VOLTAGE, carrent_active_functions);

          //Перевіряємо чи треба завершити моніторинг максимального струму послідовності
          if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MAX_CURRENT_ZOP)) != 0)
            end_monitoring_min_max_measurement(IDENTIFIER_BIT_ARRAY_MAX_CURRENT_ZOP, carrent_active_functions);
        
          //Перевіряємо чи треба завершити моніторинг мінімальну частоту 1 для АЧР
          if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MIN_FREQUENCY_1_ACHR)) != 0)
            end_monitoring_min_max_measurement(IDENTIFIER_BIT_ARRAY_MIN_FREQUENCY_1_ACHR, carrent_active_functions);

          //Перевіряємо чи треба завершити моніторинг мінімальну частоту 2 для АЧР
          if((state_current_monitoring & (1<<IDENTIFIER_BIT_ARRAY_MIN_FREQUENCY_2_ACHR)) != 0)
            end_monitoring_min_max_measurement(IDENTIFIER_BIT_ARRAY_MIN_FREQUENCY_2_ACHR, carrent_active_functions);

          /*
          Перевірку необхідності запису фіксація вимірювань при роботі ЧАПВ здійснювати
          не потрібно, тому що зараз іде перевірка чи треба примусово зупинити робити формування
          поточного запису. Якщо була ситуація заауску АПВ від ЧАПВ, то ця подія малаб зафіксованою бути
          у місці програми, де аналізувалися блоки інтегральних величин
          */

          //Дальші дії виконуємо тіьлки у тому випадку, якщо функція end_monitoring_min_max_measurement не зафіксувала помилку і не скинула state_dr_record у STATE_DR_NO_RECORD
          if(state_dr_record != STATE_DR_NO_RECORD)
          {
            //Записуємо кількість зафіксованих максимальних вимірювань всіх типів
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

            //Переводимо режим роботи із дискретним реєстратором у стан "Виконується безпосередній запис у DataFlash"
            if (state_dr_record != STATE_DR_MAKE_RECORD)
            {
              if (time_from_start_record_dr >= MAX_TIME_OFFSET_FROM_START)
              {
                //Якщо відбулося перевищення по часу запису, то подаємо команду завершити запис без продовження потім цього запису у наступному записі
                state_dr_record = STATE_DR_MAKE_RECORD;
              }
              else
              {
                //Якщо відбулося перевищення по досягнкнні максимальної кількості зрізів (або іншої причини, яка покищо не оговорена, але може з'явитися у майбутньому), то подаємо команду завершити запис але на наступному проході почати новий запис
                state_dr_record = STATE_DR_CUT_RECORD;
              }
            }
          }
        
          //Скидаємо сигнал роботи дискретного реєстратора
          _CLEAR_BIT(carrent_active_functions, RANG_OUTPUT_LED_DF_REG_WORK_D_REJESTRATOR);
        }
      }

      break;
    }
  default:
    {
      //По ідеї сюди програма ніколи не мала б зайти
      fix_undefined_error_dr(carrent_active_functions);
      break;
    }
  }
  
  //Перевіряємо, чи стоїть умова сформований запис передати на запис у DataFlash
  routine_for_queue_dr();
}
/*****************************************************/

/*****************************************************/
//Зафіксована невизначена помилка роботи аналогового реєстратора
/*****************************************************/
void fix_undefined_error_ar(unsigned int* carrent_active_functions)
{
  //Виставляємо помилку з записом в дисретний реєстратор
  _SET_BIT(set_diagnostyka, ERROR_AR_UNDEFINED_BIT);
  _SET_BIT(carrent_active_functions, RANG_OUTPUT_LED_DF_REG_DEFECT);
  //Переводимо режим роботи з реєстратором у сатн "На даний момент ніких дій з дискретним реєстратором не виконується" 
  continue_previous_record_ar = 0; /*помічаємо, що ми не чикаємо деактивації всіх джерел активації аналогового реєстратора*/
  state_ar_record = STATE_AR_NO_RECORD;
  //Скидаєсо сигнал роботи аналогового реєстратора
  _CLEAR_BIT(carrent_active_functions, RANG_OUTPUT_LED_DF_REG_WORK_A_REJESTRATOR);

  //Виставляємо команду запису структуру для аналогового реєстратора у EEPROM
  _SET_BIT(control_eeprom_taskes, TASK_START_WRITE_INFO_REJESTRATOR_AR_EEPROM_BIT);
  //Відновлюємо інформаційну структуру для аналогового реєстратора
  /*
  Адресу залишаємо попередню, тобто така яка і була
  */
  info_rejestrator_ar.saving_execution = 0;
  /*
  оскільки скоріше всього якась частна запису відбулася, а це значить, що, якщо там були корисні дані
  якогось запису, то вони зіпсовані. Тому треба помітити, що якщо у аналоговому реєстраторі до цього часу була
  максимально можлива кількість записів, то зараз оснанній з них є зіпсований, тобто кількість записів стала 
  у такому випадку на одиницю менша
  */
  unsigned int max_number_records_ar_tmp = max_number_records_ar;
  if (info_rejestrator_ar.number_records >= max_number_records_ar_tmp) 
    info_rejestrator_ar.number_records = max_number_records_ar_tmp - 1; /*Умова мал аб бути ==, але щоб перестахуватися на невизначену помилку я поставив >=*/
}
/*****************************************************/

/*****************************************************/
//Функція обробки логіки дискретного реєстратора
/*****************************************************/
inline void analog_registrator(unsigned int* carrent_active_functions)
{
  static unsigned int unsaved_bytes_of_header_ar;

  //Попередньо скидаємо невизначену помилку  роботи аналогового реєстратора
  _SET_BIT(clear_diagnostyka, ERROR_AR_UNDEFINED_BIT);

  if (continue_previous_record_ar != 0)
  {
    /*
    Ця ситуація означає, що були активними джерела аналогового реєстратора, які запустили
    в роботу аналоговий реєстратор, і тепер для розблокування можливості запускати новий запис ми 
    чекаємо ситуації, що всі джерела активації деактивуються (у будь-який час чи до
    завершення записування текучого запису аналогового реєстратора, чи вже після завершення
    записування. Це буде умовою розблокування можливості запису нового запису)
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
      //Умова розблокування можливості початку нового запису виконана
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
        Можливо була ситуація, що при попередній роботі модуля аналогового реєстратора відбувалося блокування роботи аналоговго реєстратора
        Знятий семафор semaphore_read_state_ar_record при умові, що стан роботи аналогового реєстратора STATE_AR_NO_RECORD означає,
        що зараз немає перешкод на його запуск, тому знімаємо теоретично можливу подію про тимчасову неготовність роботи аналогового реєстратора
        */
        _SET_BIT(clear_diagnostyka, ERROR_AR_TEMPORARY_BUSY_BIT);
      }

      //Аналізуємо, чи стоїть умова запуску аналогового реєстратора
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
          (continue_previous_record_ar == 0) /*при попередній роботі ан.реєстротора (якщо така була) вже всі джерела активації були зняті і зароз вони знову виникли*/ 
         )
      {
        //Перевіряємо, чи при початку нового запису у нас не іде спроба переналаштвати аналоговий реєстратор
        if(semaphore_read_state_ar_record == 0)
        {
          //Є умова запуску аналогового реєстратора
          continue_previous_record_ar = 0xff; /*помічаємо будь-яким числом, що активувалися дзжерела ан.реєстратора, які запустили роботц аналогового реєстратора*/
    
          //Можна починати новий запис
          
          //Записуємо мітку початку запису
          header_ar.label_start_record = LABEL_START_RECORD_AR;
          //Записуємо час початку запису
          unsigned char *label_to_time_array;
          if (copying_time == 2) label_to_time_array = time_copy;
          else label_to_time_array = time;
          for(unsigned int i = 0; i < 7; i++) header_ar.time[i] = *(label_to_time_array + i);
          //Коефіцієнт трансформації T0
          header_ar.T0 = current_settings_prt.T0;
          //Коефіцієнт трансформації TT
          header_ar.TCurrent = current_settings_prt.TCurrent;
          //Коефіцієнт трансформації TН
          header_ar.TVoltage = current_settings_prt.TVoltage;
          //Додаткові налаштування при яких було запущено аналоговий реєстратор
          header_ar.control_extra_settings_1 = current_settings_prt.control_extra_settings_1 & (CTR_EXTRA_SETTINGS_1_CTRL_3U0_Ubc_TN2 | CTR_EXTRA_SETTINGS_1_CTRL_PHASE_LINE);
          //І'мя ячейки
          for(unsigned int i=0; i<MAX_CHAR_IN_NAME_OF_CELL; i++)
            header_ar.name_of_cell[i] = current_settings_prt.name_of_cell[i] & 0xff;
          
          //Помічаємо, що ще ми ще не "відбирали" миттєві значення з масив для аналогового реєстратора
          copied_number_samples = 0;
          //Визначаємо загальну кількість миттєвих значень, які мають бути записані у мікросхему dataFlash2
          total_number_samples = ((current_settings_prt.prefault_number_periods + current_settings_prt.postfault_number_periods) << VAGA_NUMBER_POINT_AR)*(NUMBER_ANALOG_CANALES + number_word_digital_part_ar);

          //Визначаємо,що покищо заготовок аналогового реєстратора не скопійоманий у масив звідки будуть дані забирватися вже для запису у DataFlash
          unsaved_bytes_of_header_ar = sizeof(__HEADER_AR);

          //Визначаємо з якої адреси записувати
          temporary_address_ar = info_rejestrator_ar.next_address;

          //Визначаєом, що поки що немає підготовлених даних для запису
          count_to_save = 0;
          //Виставляємо будь-яким ненульовим числом дозвіл на підготовку нових даних для запису
          permit_copy_new_data = 0xff;

          //Робим спробу перекопіювати хоч частину заголовку аналогового реєстраторра і підготовлених даних у масив для запису в DataFlash
          if (making_buffer_for_save_ar_record(&unsaved_bytes_of_header_ar) != 0)
          {
            //Відбулася незрозуміла ситуація - сюди програма теоретично ніколи не мала б заходити
            fix_undefined_error_ar(carrent_active_functions);
          }
          else
          {
            //Переводимо режим роботи із аналоговим реєстратором у стан "Запус нового запису"
            state_ar_record = STATE_AR_START;
            //Виставляємо активну функцію
            _SET_BIT(carrent_active_functions, RANG_OUTPUT_LED_DF_REG_WORK_A_REJESTRATOR);

            //У структурі по інформації стану реєстраторів виставляємо повідомлення, що почався запис і ще не закінчився
            _SET_BIT(control_eeprom_taskes, TASK_START_WRITE_INFO_REJESTRATOR_AR_EEPROM_BIT);
            info_rejestrator_ar.saving_execution = 1;
          }
        }
        else
        {
          //Виставляємо помилку, що тимчасово аналоговий реєстратор є занятий (черз те, що іде намаганні змінити часові витримки)
          _SET_BIT(set_diagnostyka, ERROR_AR_TEMPORARY_BUSY_BIT);
          _SET_BIT(carrent_active_functions, RANG_OUTPUT_LED_DF_REG_DEFECT);
        }
      }
      break;
    }
  case STATE_AR_START:
    {
      //Ніяких дій не виконуємо, поки не встанвиться режим STATE_AR_SAVE_SRAM_AND_SAVE_FLASH,  або STATE_AR_ONLY_SAVE_FLASH
      break;
    }
  case STATE_AR_SAVE_SRAM_AND_SAVE_FLASH:
  case STATE_AR_ONLY_SAVE_FLASH:
    {
      if (state_ar_record == STATE_AR_ONLY_SAVE_FLASH)
      {
        /*
        Весь післяаварійний масив підготовлений до запису
        */
        if (_CHECK_SET_BIT(carrent_active_functions, RANG_OUTPUT_LED_DF_REG_WORK_A_REJESTRATOR) != 0)
        {
          //Знімаємо сигнал роботи аналогового реєстратора
          _CLEAR_BIT(carrent_active_functions, RANG_OUTPUT_LED_DF_REG_WORK_A_REJESTRATOR);
        }
        
        if (_CHECK_SET_BIT(carrent_active_functions, RANG_OUTPUT_LED_DF_REG_WORK_A_REJESTRATOR) == 0)
        {
          /*
          Враховуємо також той момент, коли сигнал запуску роботи аналогового реєсстратора був знятий
          */
          if  (continue_previous_record_ar == 0)
          {
            /*
            Перевіряємо, чи немає умови запуску нового заппису до моменту, 
            поки ще старий запис не закінчився повністю
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
              //Виставляємо помилку, що тимчасово аналоговий реєстратор є занятий (черз те, що завершується попередній запис)
              _SET_BIT(set_diagnostyka, ERROR_AR_TEMPORARY_BUSY_BIT);
              _SET_BIT(carrent_active_functions, RANG_OUTPUT_LED_DF_REG_DEFECT);
            }
          }
        }
      }
      
      if (permit_copy_new_data != 0)
      {
        /*
        Робим спробу перекопіювати хоч частину заголовку аналогового реєстраторра 
        і підготовлених даних у масив для запису в DataFlash тільки тоді, коли є дозвіл
        на цю операцію
        */
        if (making_buffer_for_save_ar_record(&unsaved_bytes_of_header_ar) != 0)
        {
          //Відбулася незрозуміла ситуація - сюди програма теоретично ніколи не мала б заходити
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
          //Умова зупинки роботи анаалогового реєстратора
          unsigned int index_array_ar_heat_tmp = index_array_ar_heat;/*це робим для того, бо компілятор видає завуваження при порівнянні змінних з префіксом volatile*/
          unsigned int index_array_ar_tail_tmp = index_array_ar_tail;/*це робим для того, бо компілятор видає завуваження при порівнянні змінних з префіксом volatile*/
          if(
             (index_array_ar_tail_tmp == index_array_ar_heat_tmp) &&
             (state_ar_record == STATE_AR_ONLY_SAVE_FLASH)  
            )  
          {
            //Коректна умова зупинки роботи аналогового реєстратора
            state_ar_record = STATE_AR_NO_RECORD;

            //Виставляємо команду запису структури аналогового реєстратора у EEPROM
            _SET_BIT(control_eeprom_taskes, TASK_START_WRITE_INFO_REJESTRATOR_AR_EEPROM_BIT);
            //Визначаємо нову адресу наступного запису, нову кількість записів і знімаємо сигналізацію, що зараз іде запис
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
            /*В процесі роботи аналогового реєстратора відбувся збій, який привів
            до непередбачуваного завершення роботи аналогового реєстратора
            
            Це скоріше всього виникло внаслідок того, що ми досягнули передчасно
            максимальної кількості зкопійованих миттєвих значень
            */
            fix_undefined_error_ar(carrent_active_functions);
          }
        }
        else
        {
          //Треба подати команду на запис підготовлених даних
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
            Подаємо команду на запис нових даних тільки тоді коли не іде зараз запис
            попередньо підготованих даних і коли є нові дані для запису
            */
            
            if (((temporary_address_ar & 0x1ff) + count_to_save) <= SIZE_PAGE_DATAFLASH_2)
            {
              //Немає помилки при фомауванні кількості байт для запису (в одну сторінку дані поміщаються з текучої адреси)
              
              if (count_to_save == SIZE_PAGE_DATAFLASH_2) control_tasks_dataflash |= TASK_MAMORY_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_AR;
              else control_tasks_dataflash |= TASK_MAMORY_PART_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_AR;
            }
            else
            {
              //Відбулася незрозуміла ситуація - сюди програма теоретично ніколи не мала б заходити
              fix_undefined_error_ar(carrent_active_functions);
            }
          }
        }

      }
      break;
    }
  case STATE_AR_TEMPORARY_BLOCK:
    {
      //На даний момент певні внутрішні операції блокують роботу аналогового реєстратрора
      //Аналізуємо, чи стоїть умова запуску аналогового реєстратора
      if (
          ((carrent_active_functions[0] & current_settings_prt.ranguvannja_analog_registrator[0]) != 0) ||
          ((carrent_active_functions[1] & current_settings_prt.ranguvannja_analog_registrator[1]) != 0) ||
          ((carrent_active_functions[2] & current_settings_prt.ranguvannja_analog_registrator[2]) != 0) ||
          ((carrent_active_functions[3] & current_settings_prt.ranguvannja_analog_registrator[3]) != 0) ||
          ((carrent_active_functions[4] & current_settings_prt.ranguvannja_analog_registrator[4]) != 0) ||
          ((carrent_active_functions[5] & current_settings_prt.ranguvannja_analog_registrator[5]) != 0)
         )
      {
        //Виставляємо помилку, що тимчасово аналоговий реєстратор є занятий
        _SET_BIT(set_diagnostyka, ERROR_AR_TEMPORARY_BUSY_BIT);
        _SET_BIT(carrent_active_functions, RANG_OUTPUT_LED_DF_REG_DEFECT);
      }
      break;
    }
  default:
    {
      //Відбулася незрозуміла ситуація - сюди програма теоретично ніколи не мала б заходити
      fix_undefined_error_ar(carrent_active_functions);
      break;
    }
  }
}
/*****************************************************/


/*****************************************************/
//Функція захистів з якої здійснюються всі інші операції
/*****************************************************/
inline void main_protection(void)
{
  unsigned int activated_functions[N_BIG] = {0, 0, 0, 0, 0, 0};
  
  /**************************/
  //Перевірка, чи треба очистити трігерні функції
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
    
    //Помічаємо що ми виконали очистку по ВСІХ інтерфейсах
    reset_trigger_function_from_interface = 0;
  }
  /**************************/

  /**************************/
  //Опрацьовуємо натиснуті кнопки - Мають опрацьовуватися найпершими, бо тут іде аналіз чи активовується опреділювані функції з кнопок
  /**************************/
  if ((pressed_buttons !=0) || (activation_function_from_interface != 0))
  {
    unsigned int temp_value_for_activated_function = 0;
    
    //Активація з кнопуки
    if (pressed_buttons != 0)
    {
      for (unsigned int i = 0; i < NUMBER_DEFINED_BUTTONS; i++)
      {
        if ((pressed_buttons & (1 << i)) != 0)
          temp_value_for_activated_function |= current_settings_prt.ranguvannja_buttons[i];
      }

      //Очищаємо натиснуті кнопка, які ми вже опрацювали
      pressed_buttons =0;
    }
    
    //Активація з інтерфейсу
    if (activation_function_from_interface != 0)
    {
      temp_value_for_activated_function |= activation_function_from_interface;
      
      //Очищаємо помітку активації функцій з інетфейсу, які ми вже опрацювали
      activation_function_from_interface = 0;
    }
    
    //Якщо  функції активовувалися через кнопки то переносимо їх у тимчасовий масив функцій, які мають бути зараз активавані
    if(temp_value_for_activated_function != 0) 
    {
      //Опреділювані функції
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
          //Зараз має активуватися ОФx, тому треба запустити таймер її утримування,
          //для того, щоб потім час цей можна було зрівняти з часом таймера павзи
          if (global_timers[INDEX_TIMER_DF_PROLONG_SET_FOR_BUTTON_INTERFACE_START + i] <0)
          {
            //Запускаємо таймер таймер утримування цієї функції в активному стані (емітація активного входу)
            //Запуск робимо тільки ту тому випадкук, якщо він ще не почався
            global_timers[INDEX_TIMER_DF_PROLONG_SET_FOR_BUTTON_INTERFACE_START + i] = 0;
          }
        }
        
      }
      
      //Опреділювані триґери
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
      
      //Скидання світлодіодів і реле
      activated_functions[RANG_OUTPUT_LED_DF_REG_RESET_LEDS  >> 5] |= ((temp_value_for_activated_function & (1<<RANG_BUTTON_RESET_LEDS ) )>>RANG_BUTTON_RESET_LEDS ) << (RANG_OUTPUT_LED_DF_REG_RESET_LEDS  & 0x1f);
      activated_functions[RANG_OUTPUT_LED_DF_REG_RESET_RELES >> 5] |= ((temp_value_for_activated_function & (1<<RANG_BUTTON_RESET_RELES) )>>RANG_BUTTON_RESET_RELES) << (RANG_OUTPUT_LED_DF_REG_RESET_RELES & 0x1f);

      //"Місцеве/Дистанційне" управління
      if ((temp_value_for_activated_function & (1<<RANG_BUTTON_MISCEVE_DYSTANCIJNE )) != 0)
      {
        //Активована команда з функціональної кнопки "Місцеве/Дистанційне"
        misceve_dystancijne = (misceve_dystancijne ^ 0x1) & 0x1;
        //Виставляємо повідомлення про те, що в EEPROM треба записати нові значення сигнальних виходів і тригерних світлоіндикаторів
        _SET_BIT(control_eeprom_taskes, TASK_START_WRITE_TRG_FUNC_EEPROM_BIT);
      }
      
      //Включення-виключення вимикача
      activated_functions[RANG_OUTPUT_LED_DF_REG_VKL_VV  >> 5] |= ((temp_value_for_activated_function & (1<<RANG_BUTTON_VKL_VV ) )>>RANG_BUTTON_VKL_VV ) << (RANG_OUTPUT_LED_DF_REG_VKL_VV  & 0x1f);
      activated_functions[RANG_OUTPUT_LED_DF_REG_OTKL_VV >> 5] |= ((temp_value_for_activated_function & (1<<RANG_BUTTON_OTKL_VV) )>>RANG_BUTTON_OTKL_VV) << (RANG_OUTPUT_LED_DF_REG_OTKL_VV & 0x1f);

      //скидання блокування готовності до ТУ
      activated_functions[RANG_OUTPUT_LED_DF_REG_RESET_BLOCK_READY_TU_VID_ZAHYSTIV >> 5] |= ((temp_value_for_activated_function & (1<<RANG_BUTTON_RESET_BLOCK_READY_TU_VID_ZAHYSTIV ) )>>RANG_BUTTON_RESET_BLOCK_READY_TU_VID_ZAHYSTIV ) << (RANG_OUTPUT_LED_DF_REG_RESET_BLOCK_READY_TU_VID_ZAHYSTIV  & 0x1f);
      
      //Команди АПВ-ЗМН
      activated_functions[RANG_OUTPUT_LED_DF_REG_RESET_BLOCK_APV_ZMN >> 5] |= ((temp_value_for_activated_function & (1<<RANG_BUTTON_RESET_BLOCK_APV_ZMN ) )>>RANG_BUTTON_RESET_BLOCK_APV_ZMN ) << (RANG_OUTPUT_LED_DF_REG_RESET_BLOCK_APV_ZMN  & 0x1f);

      //Команди АВР
      activated_functions[RANG_OUTPUT_LED_DF_REG_OTKL_AVR              >> 5] |= ((temp_value_for_activated_function & (1<<RANG_BUTTON_OTKL_AVR              ) )>>RANG_BUTTON_OTKL_AVR              ) << (RANG_OUTPUT_LED_DF_REG_OTKL_AVR               & 0x1f);
      activated_functions[RANG_OUTPUT_LED_DF_REG_SBROS_BLOCK_AVR       >> 5] |= ((temp_value_for_activated_function & (1<<RANG_BUTTON_SBROS_BLOCK_AVR       ) )>>RANG_BUTTON_SBROS_BLOCK_AVR       ) << (RANG_OUTPUT_LED_DF_REG_SBROS_BLOCK_AVR        & 0x1f);
    }
  }
  /**************************/

  //"Місц./Дистанц."  з функціональних кнопок меню
  activated_functions[RANG_OUTPUT_LED_DF_REG_MISCEVE_DYSTANCIJNE >> 5] |= (misceve_dystancijne & 0x1) << (RANG_OUTPUT_LED_DF_REG_MISCEVE_DYSTANCIJNE & 0x1f);

  unsigned int blocking_commands_from_DI = 0;
  unsigned int active_inputs_grupa_ustavok = 0;
  /**************************/
  //Опрацьовуємо дискретні входи
  /**************************/
  //Перевіряємо чи є зараз активні входи
  if (active_inputs !=0)
  {
    //Є входи активні
    unsigned int temp_value_for_activated_function_2[N_SMALL] = {0,0};
    for (unsigned int i = 0; i < NUMBER_INPUTS; i++)
    {
      if ((active_inputs & (1 << i)) != 0)
      {
        temp_value_for_activated_function_2[0] |= current_settings_prt.ranguvannja_inputs[N_SMALL*i  ];
        temp_value_for_activated_function_2[1] |= current_settings_prt.ranguvannja_inputs[N_SMALL*i+1];
      }
    }
    
    //Якщо  функції активовувалися через ДВ то переносимо їх у тимчасовий масив функцій, які мають бути зараз активавані
    if(
       (temp_value_for_activated_function_2[0] != 0) ||
       (temp_value_for_activated_function_2[1] != 0)
      ) 
    {
      //Опреділювані функції
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

      //Опреділювані триґери
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
      
      //Загальні функції (без ОФ-ій і функцій, які можуть блокуватися у місцевому управлінні)
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
      
      //Загальні функції (які блокувються у місцевому управлінні)
      //Ввімкнення ВВ
      if (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_VKL_VV ))
      {
        if (
            (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_MISCEVE_DYSTANCIJNE )) &&
            (current_settings_prt.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_BLK_ON_CB_MISCEVE)
           ) 
        {
          //Умова блокування командви "Ввімкнення ВВ" від ДВх.
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
          //Умова блокування командви "Вимкнення ВВ" від ДВх.
          blocking_commands_from_DI |= CTR_EXTRA_SETTINGS_1_BLK_OFF_CB_MISCEVE;
        }
        else
          activated_functions[RANG_OUTPUT_LED_DF_REG_OTKL_VV >> 5] |= 1 << (RANG_OUTPUT_LED_DF_REG_OTKL_VV & 0x1f);
      }

      //Блок для МТЗ
      activated_functions[RANG_OUTPUT_LED_DF_REG_BLOCK_MTZ1     >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_BLOCK_MTZ1    ) != 0) << (RANG_OUTPUT_LED_DF_REG_BLOCK_MTZ1     & 0x1f);
      activated_functions[RANG_OUTPUT_LED_DF_REG_BLOCK_MTZ2     >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_BLOCK_MTZ2    ) != 0) << (RANG_OUTPUT_LED_DF_REG_BLOCK_MTZ2     & 0x1f);
      activated_functions[RANG_OUTPUT_LED_DF_REG_BLOCK_USK_MTZ2 >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_BLOCK_USK_MTZ2) != 0) << (RANG_OUTPUT_LED_DF_REG_BLOCK_USK_MTZ2 & 0x1f);
      activated_functions[RANG_OUTPUT_LED_DF_REG_BLOCK_MTZ3     >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_BLOCK_MTZ3    ) != 0) << (RANG_OUTPUT_LED_DF_REG_BLOCK_MTZ3     & 0x1f);
      activated_functions[RANG_OUTPUT_LED_DF_REG_BLOCK_MTZ4     >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_BLOCK_MTZ4    ) != 0) << (RANG_OUTPUT_LED_DF_REG_BLOCK_MTZ4     & 0x1f);

      //Блок для ЗДЗ
      activated_functions[RANG_OUTPUT_LED_DF_REG_PUSK_ZDZ_VID_DV >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_PUSK_ZDZ_VID_DV) != 0) << (RANG_OUTPUT_LED_DF_REG_PUSK_ZDZ_VID_DV & 0x1f);

      //Блок НЗЗ
      activated_functions[RANG_OUTPUT_LED_DF_REG_BLOCK_NZZ >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_BLOCK_NZZ) != 0) << (RANG_OUTPUT_LED_DF_REG_BLOCK_NZZ & 0x1f);

      //Блок АПВ
      activated_functions[RANG_OUTPUT_LED_DF_REG_STAT_BLK_APV >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_STAT_BLK_APV) != 0) << (RANG_OUTPUT_LED_DF_REG_STAT_BLK_APV & 0x1f);
      
      //Блок АПВ ЗМН
      activated_functions[RANG_OUTPUT_LED_DF_REG_RESET_BLOCK_APV_ZMN >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_RESET_BLOCK_APV_ZMN) != 0) << (RANG_OUTPUT_LED_DF_REG_RESET_BLOCK_APV_ZMN & 0x1f);
      activated_functions[RANG_OUTPUT_LED_DF_REG_BLOCK_APV_ZMN       >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_BLOCK_APV_ZMN      ) != 0) << (RANG_OUTPUT_LED_DF_REG_BLOCK_APV_ZMN       & 0x1f);

      //ЧАПВ
      activated_functions[RANG_OUTPUT_LED_DF_REG_BLOCK_ACHR         >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_BLOCK_ACHR       ) != 0) << (RANG_OUTPUT_LED_DF_REG_BLOCK_ACHR        & 0x1f);
      activated_functions[RANG_OUTPUT_LED_DF_REG_ACHR_CHAPV_VID_DV  >> 5] |=(_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_ACHR_CHAPV_VID_DV ) != 0) << (RANG_OUTPUT_LED_DF_REG_ACHR_CHAPV_VID_DV & 0x1f);

      //Блок для УРОВ
      activated_functions[RANG_OUTPUT_LED_DF_REG_PUSK_UROV_VID_DV >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_PUSK_UROV_VID_DV) != 0) << (RANG_OUTPUT_LED_DF_REG_PUSK_UROV_VID_DV & 0x1f);

      //Блок ЗОП(КОФ)
      activated_functions[RANG_OUTPUT_LED_DF_REG_BLOCK_ZOP >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_BLOCK_ZOP) != 0) << (RANG_OUTPUT_LED_DF_REG_BLOCK_ZOP & 0x1f);

      //Блок для Umin
      activated_functions[RANG_OUTPUT_LED_DF_REG_BLOCK_UMIN1 >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_BLOCK_UMIN1) != 0) << (RANG_OUTPUT_LED_DF_REG_BLOCK_UMIN1 & 0x1f);
      activated_functions[RANG_OUTPUT_LED_DF_REG_START_UMIN1 >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_START_UMIN1) != 0) << (RANG_OUTPUT_LED_DF_REG_START_UMIN1 & 0x1f);
      activated_functions[RANG_OUTPUT_LED_DF_REG_BLOCK_UMIN2 >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_BLOCK_UMIN2) != 0) << (RANG_OUTPUT_LED_DF_REG_BLOCK_UMIN2 & 0x1f);
      activated_functions[RANG_OUTPUT_LED_DF_REG_START_UMIN2 >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_START_UMIN2) != 0) << (RANG_OUTPUT_LED_DF_REG_START_UMIN2 & 0x1f);
      
      //Блок для Umax
      activated_functions[RANG_OUTPUT_LED_DF_REG_BLOCK_UMAX1 >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_BLOCK_UMAX1) != 0) << (RANG_OUTPUT_LED_DF_REG_BLOCK_UMAX1 & 0x1f);
      activated_functions[RANG_OUTPUT_LED_DF_REG_BLOCK_UMAX2 >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_BLOCK_UMAX2) != 0) << (RANG_OUTPUT_LED_DF_REG_BLOCK_UMAX2 & 0x1f);
      
      //Блок для АВР
      activated_functions[RANG_OUTPUT_LED_DF_REG_OTKL_AVR              >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_OTKL_AVR              ) != 0) << (RANG_OUTPUT_LED_DF_REG_OTKL_AVR              & 0x1f);
      activated_functions[RANG_OUTPUT_LED_DF_REG_SBROS_BLOCK_AVR       >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_SBROS_BLOCK_AVR       ) != 0) << (RANG_OUTPUT_LED_DF_REG_SBROS_BLOCK_AVR       & 0x1f);
      activated_functions[RANG_OUTPUT_LED_DF_REG_STAT_BLOCK_AVR        >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function_2, RANG_INPUT_STAT_BLOCK_AVR        ) != 0) << (RANG_OUTPUT_LED_DF_REG_STAT_BLOCK_AVR        & 0x1f);
    }
  }
  /**************************/

  /**************************/
  //Виконуємо фільтрацію переднього фронту для тих сигналів, які мають активуватися тільки по передньому фронтові
  /**************************/
  //Формуємо маску сигналів, які треба позначити, як активні тільки в момент переходу з "0" в "1"
  unsigned int temp_maska_filter_function[N_BIG] = {0, 0, 0, 0, 0, 0};
  unsigned int temp_activated_functions[N_BIG] = {0, 0, 0, 0, 0, 0};
  
  //Сигнал "Сблос индикации"
  _SET_BIT(temp_maska_filter_function, RANG_OUTPUT_LED_DF_REG_RESET_LEDS);
  
  //Сигнал "Сблос реле"
  _SET_BIT(temp_maska_filter_function, RANG_OUTPUT_LED_DF_REG_RESET_RELES);

  //Сигнал "Включить ВВ"
  _SET_BIT(temp_maska_filter_function, RANG_OUTPUT_LED_DF_REG_VKL_VV);
    
  //Сигнал "Отключить ВВ"
  _SET_BIT(temp_maska_filter_function, RANG_OUTPUT_LED_DF_REG_OTKL_VV);

  //Сигнал "Скидання блокування готовності до ТУ"
  _SET_BIT(temp_maska_filter_function, RANG_OUTPUT_LED_DF_REG_RESET_BLOCK_READY_TU_VID_ZAHYSTIV);
  
  //Сигнал "Внешний сброс блокировки АПВ-ЗМН"
  _SET_BIT(temp_maska_filter_function, RANG_OUTPUT_LED_DF_REG_RESET_BLOCK_APV_ZMN);

  //Сигнал "Внешний отключение АВР"
  _SET_BIT(temp_maska_filter_function, RANG_OUTPUT_LED_DF_REG_OTKL_AVR);
  //Сигнал "Внешний сброс блокировки АВР"
  _SET_BIT(temp_maska_filter_function, RANG_OUTPUT_LED_DF_REG_SBROS_BLOCK_AVR);
  
  //З масиву попередніх станів виділяємо тільки ті функції, якиї нас цікавить фронт змін і поміщаємо їх у тимчасовий масив
  temp_activated_functions[0] = previous_activated_functions[0] & temp_maska_filter_function[0];
  temp_activated_functions[1] = previous_activated_functions[1] & temp_maska_filter_function[1];
  temp_activated_functions[2] = previous_activated_functions[2] & temp_maska_filter_function[2];
  temp_activated_functions[3] = previous_activated_functions[3] & temp_maska_filter_function[3];
  temp_activated_functions[4] = previous_activated_functions[4] & temp_maska_filter_function[4];
  temp_activated_functions[5] = previous_activated_functions[5] & temp_maska_filter_function[5];
  
  //У тимчасовому масиві виділяємо тільки ті функції, у яких зафіксовано або передній, або задній фронти
  temp_activated_functions[0] ^= (activated_functions[0] & temp_maska_filter_function[0]);
  temp_activated_functions[1] ^= (activated_functions[1] & temp_maska_filter_function[1]);
  temp_activated_functions[2] ^= (activated_functions[2] & temp_maska_filter_function[2]);
  temp_activated_functions[3] ^= (activated_functions[3] & temp_maska_filter_function[3]);
  temp_activated_functions[4] ^= (activated_functions[4] & temp_maska_filter_function[4]);
  temp_activated_functions[5] ^= (activated_functions[5] & temp_maska_filter_function[5]);
  
  //Тепер виділяємо у тимчасовому масиві тільки ті функції у яких зараз значення стоять рівні "1" (тобто відбувся перехід з "0" в "1")
  temp_activated_functions[0] &= activated_functions[0];
  temp_activated_functions[1] &= activated_functions[1];
  temp_activated_functions[2] &= activated_functions[2];
  temp_activated_functions[3] &= activated_functions[3];
  temp_activated_functions[4] &= activated_functions[4];
  temp_activated_functions[5] &= activated_functions[5];
  
  /*
  Перед тим, як виділити ті функції, які у цьому циклі будуть відмічені як активні 
  з урахуванням того, що деякі функції активоються по передньому фронті
  копіюємо статичний стан функцій (без врахування фронтів) у тимчасовий масив
  щоб при наступному аналізі мати попередній статичний стан активних функцій
  */ 
  previous_activated_functions[0] = activated_functions[0];
  previous_activated_functions[1] = activated_functions[1];
  previous_activated_functions[2] = activated_functions[2];
  previous_activated_functions[3] = activated_functions[3];
  previous_activated_functions[4] = activated_functions[4];
  previous_activated_functions[5] = activated_functions[5];

  //Обновляємо масив функцій, які зараз активуються з врахуванням того, що серед виділених функцій маскою активними мають юути тільки ті, у яких перехід був з "0" в "1"
  activated_functions[0] = (activated_functions[0] & (~temp_maska_filter_function[0])) | temp_activated_functions[0];
  activated_functions[1] = (activated_functions[1] & (~temp_maska_filter_function[1])) | temp_activated_functions[1];
  activated_functions[2] = (activated_functions[2] & (~temp_maska_filter_function[2])) | temp_activated_functions[2];
  activated_functions[3] = (activated_functions[3] & (~temp_maska_filter_function[3])) | temp_activated_functions[3];
  activated_functions[4] = (activated_functions[4] & (~temp_maska_filter_function[4])) | temp_activated_functions[4];
  activated_functions[5] = (activated_functions[5] & (~temp_maska_filter_function[5])) | temp_activated_functions[5];
  /**************************/
  
  /**************************/
  //Вибір групи уставок
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
    //Іде блокування груп уставок - група уставок залишається тою, яка вибрана попередньо
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
      //Теоретично цього ніколи не мало б бути
      total_error_sw_fixed(52);
    }
  }
  else
  {
    //Можна вибирати групу уставок - захисти цю операцію не блокують
    setpoints_selecting(activated_functions, active_inputs_grupa_ustavok);
  }

  unsigned int number_group_stp;
  if     (( _CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_1_GRUPA_USTAVOK) ) !=0 ) number_group_stp = 0;
  else if(( _CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_2_GRUPA_USTAVOK) ) !=0 ) number_group_stp = 1;
  else if(( _CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_3_GRUPA_USTAVOK) ) !=0 ) number_group_stp = 2;
  else if(( _CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_4_GRUPA_USTAVOK) ) !=0 ) number_group_stp = 3;
  else
  {
    //Теоретично цього ніколи не мало б бути
    total_error_sw_fixed(51);
  }
  /**************************/

  /***********************************************************/
  //Розрахунок вимірювань
  /***********************************************************/
  calc_measurement(number_group_stp);

#ifdef DEBUG_TEST
  /***/
  //Тільки для відладки
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
    
      
  //Діагностика справності раз на період
  diagnostyca_adc_execution();
  
  //Копіюємо вимірювання для низькопріоритетних і високопріоритетних завдань
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
  //Сигнал "Несправность Общая"
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
    //Сигнал "Несправность Аварийная"
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

  
  //Логічні схеми мають працювати тільки у тому випадку, якщо немє сигналу "Аварийная неисправность"
  if (_CHECK_SET_BIT(activated_functions, RANG_OUTPUT_LED_DF_REG_AVAR_DEFECT) == 0)
  {
    //Аварійна ситуація не зафіксована
    
    /**************************/
    //Контроль привода ВВ
    /**************************/
    control_VV(activated_functions);
    /**************************/

    /**************************/
    //МТЗ
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
    //ЗДЗ
    /**************************/
    if ((current_settings_prt.configuration & (1 << ZDZ_BIT_CONFIGURATION)) != 0)
    {
      zdz_handler(activated_functions);
    }
    /**************************/

    /**************************/
    //ЗЗ
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
    //ЗОП(КОФ)
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
      //ЗНМИН1
      /**************************/
      umin1_handler(activated_functions, number_group_stp);
      /**************************/
      
      /**************************/
      //ЗНМИН2
      /**************************/
      umin2_handler(activated_functions, number_group_stp);
      /**************************/
    } else {
      global_timers[INDEX_TIMER_UMIN1] = -1;
      global_timers[INDEX_TIMER_UMIN2] = -1;
    }
    
    if ((current_settings_prt.configuration & (1 << UMAX_BIT_CONFIGURATION)) > 0) {
      /**************************/
      //ЗНМАКС1
      /**************************/
      umax1_handler(activated_functions, number_group_stp);
      /**************************/
      
      /**************************/
      //ЗНМАКС2
      /**************************/
      umax2_handler(activated_functions, number_group_stp);
      /**************************/
    } else {
      global_timers[INDEX_TIMER_UMAX1] = -1;
      global_timers[INDEX_TIMER_UMAX2] = -1;
    }
    
    if ((current_settings_prt.configuration & (1 << AVR_BIT_CONFIGURATION)) > 0) {
      /**************************/
      //АВР
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
      //АПВ ЗМН
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
      //АЧР ЧАПВ
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
      //Контроль напряжения основной линии
      /**************************/
      control_U_OL(activated_functions, number_group_stp);
      /**************************/
      
      /**************************/
      //Контроль напряжения резервной линии
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
    //УРОВ
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
    //АПВ
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
    //Опрцювання опреділюваних функцій
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
    //Опрцювання опреділюваних триґерів
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
    //Включення-Відключення
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
    //ВМП (завжди пісяля логіки Блоку вимикання)
    /**************************/
    vmp_handler(activated_functions);
    /**************************/

    /**************************/
    //Готовность к ТУ
    /**************************/
    ready_tu(activated_functions);
    /**************************/

    /**************************/
    //Ресурс вимикача (завжди пісяля логіки Блоку вимикання)
    /**************************/
    resurs_vymykacha_handler(activated_functions, (unsigned int *)active_functions);
    /**************************/
  }
  else
  {
    //Аварійна ситуація зафіксована
    
    //Скидаємо всі активні функції, крім інформативних
    activated_functions[0] &= MASKA_INFO_SIGNALES_0;
    activated_functions[1] &= MASKA_INFO_SIGNALES_1;
    activated_functions[2] &= MASKA_INFO_SIGNALES_2;
    activated_functions[3] &= MASKA_INFO_SIGNALES_3;
    activated_functions[4] &= MASKA_INFO_SIGNALES_4;
    activated_functions[5] &= MASKA_INFO_SIGNALES_5;
    
    //Деактивовуємо всі реле
    state_outputs = 0;
    
    //Переводимо у початковий стан деякі глобальні змінні
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
    
    //Скидаємо всі таймери, які присутні у лозіці
    for(unsigned int i = INDEX_TIMER_DF_PROLONG_SET_FOR_BUTTON_INTERFACE_START; i < MAX_NUMBER_GLOBAL_TIMERS; i++)
      global_timers[i] = -1;
    
    //Стан всіх ОФ переводимо у пасивний
    state_df = 0;
    
    //Стан виконання ОФ переводимо у початковий
    for(unsigned int i = 0; i < NUMBER_DEFINED_FUNCTIONS; i++)
    {
      etap_execution_df[i] = NONE_DF;
    }
  }

  /**************************/
  //Підготовка до роботи реєстраторів
  /**************************/
  //Копіюємо в текучі активні функції попередній стан сигналу "Работа Ан.Рег."
  activated_functions[RANG_OUTPUT_LED_DF_REG_WORK_A_REJESTRATOR >> 5] |= active_functions[RANG_OUTPUT_LED_DF_REG_WORK_A_REJESTRATOR >> 5] & (unsigned int)(1 << (RANG_OUTPUT_LED_DF_REG_WORK_A_REJESTRATOR & 0x1f));
  
  //Копіюємо в текучі активні функції попередній стан сигналу "Работа Д.Рег." щоб не фіксувавсі при роботі функції дискретного реєстратора постійний перехів цього сигналу з "1" в "0"/
  activated_functions[RANG_OUTPUT_LED_DF_REG_WORK_D_REJESTRATOR >> 5] |= active_functions[RANG_OUTPUT_LED_DF_REG_WORK_D_REJESTRATOR >> 5] & (unsigned int)(1 << (RANG_OUTPUT_LED_DF_REG_WORK_D_REJESTRATOR & 0x1f));
  /**************************/

  /**************************/
  //Обробка аналогового реєстратора
  /**************************/
  analog_registrator(activated_functions);
  /**************************/

  /**************************/
  //Обробка дискретного реєстратора
  /**************************/
  digital_registrator(activated_functions, active_functions, number_group_stp);
  /**************************/

  /**************************/
  //Робота з функціями, які мають записуватися у енергонезалежну пам'ять
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
    Сигнали, значення яких записується у енергонезалежну пам'1ять змінилися.
    Подаємо команду на їх запис у енергонезалежну пам'ять
    */
    _SET_BIT(control_eeprom_taskes, TASK_START_WRITE_TRG_FUNC_EEPROM_BIT);
  }
  /**************************/

  /**************************/
  //Перекидання інфомації у масиви активних і тригерних функцій
  /**************************/
  copying_active_functions = 1; //Помічаємо, що зараз обновляємо значення активних функцій
  
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

  copying_active_functions = 0; //Помічаємо, що обновлення значення активних функцій завершене
  
  /*
  Робимо копію значення активних функцій для того, щоб коли ці знаення будуть
  обновлятися, то можна було б іншим модулям  (зап ис у об'єднаний аналоговий
  реєстратор) взяти попереднє, але достовірне значення
  */
  active_functions_copy[0] = active_functions[0];
  active_functions_copy[1] = active_functions[1];
  active_functions_copy[2] = active_functions[2];
  active_functions_copy[3] = active_functions[3];
  active_functions_copy[4] = active_functions[4];
  active_functions_copy[5] = active_functions[5];
  /**************************/

  /**************************/
  //Вивід інформації на виходи
  /**************************/
  //Спочатку перевіряємо, чи не активовувалвся команда "Сблос реле" - і якщо так, то попередньо скидаємо всі реле
  if (_CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_RESET_RELES) !=0)
  {
    state_outputs = 0;
  }
  
  if (_CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_AVAR_DEFECT) == 0)
  {
    //Не зафіксовано аварійної ситуації, тому встановлювати реле можна
    
    //Визначаємо, які реле зараз мають бути замкнутими
    for (unsigned int i = 0; i < NUMBER_OUTPUTS; i++)
    {
      //У тимчасовий масив поміщаємо ЛОГІЧНЕ І ранжування виходу, який індексується інедексом "i" і функцій, які зараз є активними
      unsigned int temp_array_of_outputs[N_BIG];
    
      temp_array_of_outputs[0] = current_settings_prt.ranguvannja_outputs[N_BIG*i    ] & active_functions[0];
      temp_array_of_outputs[1] = current_settings_prt.ranguvannja_outputs[N_BIG*i + 1] & active_functions[1];
      temp_array_of_outputs[2] = current_settings_prt.ranguvannja_outputs[N_BIG*i + 2] & active_functions[2];
      temp_array_of_outputs[3] = current_settings_prt.ranguvannja_outputs[N_BIG*i + 3] & active_functions[3];
      temp_array_of_outputs[4] = current_settings_prt.ranguvannja_outputs[N_BIG*i + 4] & active_functions[4];
      temp_array_of_outputs[5] = current_settings_prt.ranguvannja_outputs[N_BIG*i + 5] & active_functions[5];

      //Сигнал "Аварійна несправність" працює у інверсному режимі: замикає реле на якому зранжована у випадку, коли даний сигнал не активинй
      if(_CHECK_SET_BIT((current_settings_prt.ranguvannja_outputs + N_BIG*i), RANG_OUTPUT_LED_DF_REG_AVAR_DEFECT) !=0)
      {
        //Сигнал "Aварийная неисправность"  справді зранжовано на даний вихід
        if (_CHECK_SET_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_AVAR_DEFECT) == 0)
        {
          //Сигнал "Aварийная неисправность" не є активним
          //Приимусово встановлюємо його у активний стан у масиві, який є  ЛОГІЧНИМ І анжування виходу, який індексується інедексом "i" і функцій, які зараз є активними
          _SET_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_AVAR_DEFECT);
        }
        else
        {
          //Сигнал "Aварийная неисправность" є активним
          //Приимусово переводимо його у пасивний стан у масиві, який є  ЛОГІЧНИМ І анжування виходу, який індексується інедексом "i" і функцій, які зараз є активними
          _CLEAR_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_AVAR_DEFECT);
        }
      }
      
      //Сигнал "Загальна несправність" працює у інверсному режимі: замикає реле на якому зранжована у випадку, коли даний сигнал не активинй
      if(_CHECK_SET_BIT((current_settings_prt.ranguvannja_outputs + N_BIG*i), RANG_OUTPUT_LED_DF_REG_DEFECT) !=0)
      {
        //Сигнал "Загальна несправність"  справді зранжовано на даний вихід
        if (_CHECK_SET_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_DEFECT) ==0)
        {
          //Сигнал "Загальна несправність" не є активним
          //Приимусово встановлюємо його у активний стан у масиві, який є  ЛОГІЧНИМ І анжування виходу, який індексується інедексом "i" і функцій, які зараз є активними
          _SET_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_DEFECT);
        }
        else
        {
          //Сигнал "Загальна несправність" є активним
          //Приимусово переводимо його у пасивний стан у масиві, який є  ЛОГІЧНИМ І анжування виходу, який індексується інедексом "i" і функцій, які зараз є активними
          _CLEAR_BIT(temp_array_of_outputs, RANG_OUTPUT_LED_DF_REG_DEFECT);
        }
      }

      //Перевіряємо, чи є співпадіння між ранжованими функціями на цьому виході і функціями, які зараз є активними - умова активації виходу
      if (
          (temp_array_of_outputs[0] !=0 ) ||
          (temp_array_of_outputs[1] != 0) ||
          (temp_array_of_outputs[2] != 0) ||
          (temp_array_of_outputs[3] != 0) ||
          (temp_array_of_outputs[4] != 0) ||
          (temp_array_of_outputs[5] != 0)
         )
      {
        //Для сигнального реле виконуємо його замикання, а для командного перевіряємо чи нема спроби активувати реле при умові що на нього заведено блок включення, причому він блокований
        if ((current_settings_prt.type_of_output & (1 << i)) != 0)
        {
          //Вихід сигнальний, тому у буль якому разі замикаємо реле
          //Відмічаємо, що даний вихід - ЗАМКНУТИЙ
          state_outputs |= (1 << i);
        }
        else
        {
          //Вихід командний, тому перевіряємо чи не йде спроба активувати реле, на яке заведено БВ, причому блок БВ з пеквних причин блокований (неактивний)
          if (_CHECK_SET_BIT((current_settings_prt.ranguvannja_outputs + N_BIG*i), RANG_OUTPUT_LED_DF_REG_WORK_BV) ==0)
          {
            //На дане реле не заводиться сигнал БВ (блок включення)
          
            //Відмічаємо, що даний вихід - ЗАМКНУТИЙ
            state_outputs |= (1 << i);
          }
          else
          {
            //На дане реле заводиться сигнал БВ (блок включення)
          
            //Відмічаємо, що даний вихід - ЗАМКНУТИЙ тільки тоді, коли функція БВ активна зараз
            if (_CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_WORK_BV) !=0)
              state_outputs |= (1 << i);
            else
              state_outputs &= ~(1 << i);
          }
        }
      }
      else
      {
        //Перевіряємо, чи вихід командний, чи сигнальний
        if ((current_settings_prt.type_of_output & (1 << i)) == 0)
        {
          //Вихід командний
        
          //Відмічаємо, що даний вихід - РОЗІМКНУТИЙ
          state_outputs &= ~(1 << i);
        }
      }
    }
  }
  else
  {
    //Зафіксовано аварійнe ситуацію, тому деактивуємо всі реле!!!

    //Деактивовуємо всі реле
    state_outputs = 0;
  }
  
  //Перевіряємо чи треба записувати стан сигнальних виходів у EEPROM
  unsigned int temp_value_char_for_volatile = state_signal_outputs;
  if((state_outputs  & current_settings_prt.type_of_output) != temp_value_char_for_volatile)
  {
    state_signal_outputs = state_outputs  & current_settings_prt.type_of_output;
    //Виставляємо повідомлення про те, що в EEPROM треба записати нові значення сигнальних виходів і тригерних світлоіндикаторів
    _SET_BIT(control_eeprom_taskes, TASK_START_WRITE_STATE_LEDS_OUTPUTS_EEPROM_BIT);
  }
  
  //Виводимо інформацію по виходах на піни процесора (у зворотньому порядку)
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
  //Вивід інформації на світлодіоди
  /**************************/
  //Спочатку перевіряємо, чи не активовувалвся команда "Сблос индикации" - і якщо так, то попередньо скидаємо всю індикацію
  if (_CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_RESET_LEDS) !=0)
  {
    state_leds = 0;
  }
  
  //Визначаємо, які світлоіндикатори зараз мають бути активними
  for (unsigned int i = 0; i < NUMBER_LEDS; i++)
  {
    //У тимчасовий масив копіюємо ранжування світлоіндикатора, який індексується інедексом "i"
    unsigned int temp_array_of_leds[N_BIG];
    
    //Перевіряємо, чи є співпадіння між ранжованими функціями на цьому світлоіндикаторі і функціями, які зараз є активними - умова активації виходу
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
      //Відмічаємо, що даний світлоіндикатор - ГОРИТЬ
      state_leds |= (1 << i);
    }
    else
    {
      //Перевіряємо, чи даний світлоіндикатор нормальний, чи тригерний
      if ((current_settings_prt.type_of_led & (1 << i)) == 0)
      {
        //Світлоіндикатор нормальний

        //Відмічаємо, що даний світлоіндикатор - ПОГАШЕНИЙ
        state_leds &= ~(1 << i);
      }
    }
  }
  //Перевіряємо чи треба записувати стан тригерних світлоіндикаторів у EEPROM
  temp_value_char_for_volatile = state_trigger_leds;
  if((state_leds  & current_settings_prt.type_of_led) != temp_value_char_for_volatile)
  {
    state_trigger_leds = state_leds  & current_settings_prt.type_of_led;
    //Виставляємо повідомлення про те, що в EEPROM треба записати нові значення сигнальних виходів і тригерних світлоіндикаторів
    _SET_BIT(control_eeprom_taskes, TASK_START_WRITE_STATE_LEDS_OUTPUTS_EEPROM_BIT);
  }

  //Виводимо інформацію по світлоіндикаторах на світлодіоди
  _DEVICE_REGISTER(Bank1_SRAM2_ADDR, OFFSET_LEDS) = state_leds;
  /**************************/

  /**************************/
  //
  /**************************/
  /**************************/
}
/*****************************************************/

/*****************************************************/
//Переривання від таймеру TIM2, який обслуговує систему захистів
/*****************************************************/
void TIM2_IRQHandler(void)
{
#ifdef SYSTEM_VIEWER_ENABLE
  SEGGER_SYSVIEW_RecordEnterISR();
#endif
  
  if (TIM_GetITStatus(TIM2, TIM_IT_CC1) != RESET)
  {
    /***********************************************************************************************/
    //Переривання відбулося вік каналу 1, який генерує переривання кожні 1 мс, для опраціьовування таймерів і систем захистів
    /***********************************************************************************************/
    TIM2->SR = (uint16_t)((~(uint32_t)TIM_IT_CC1) & 0xffff);
    uint32_t current_tick = TIM2->CCR1;
    
    /***********************************************************/
    //Перевіряємо, чи відбувалися зміни настройок
    /***********************************************************/
    if (
        (changed_settings == CHANGED_ETAP_ENDED) && /*Це є умова, що нові дані підготовлені для передачі їх у роботу системою захистів (і при цьому зараз дані не змінюються)*/
        (state_ar_record  != STATE_AR_START    )    /*Це є умова, що на даний момент не може виникнути переривання від вимірювальної системи (з вищим пріоритетом за пріоритет системи захистів) з умовою початку формування запису аналогового реєстратора. де треба буде взяти ширину доаварійного і післяаварійного масивів*/ 
       )   
    {
      //Копіюємо таблицю настройок у копію цієї таблиці але з якою працює (читає і змінює) тільки система захистів
      current_settings_prt = current_settings;
      
      //Помічаємо, що зміни прийняті системою захистів
      changed_settings = CHANGED_ETAP_NONE;
    }

    if (koef_resurs_changed == CHANGED_ETAP_ENDED)
    {
      //Коефіцієнти для підрахунку ресурсу вимикача
      K_resurs_prt = K_resurs;

      //Помічаємо, що зміни прийняті системою захистів
      koef_resurs_changed = CHANGED_ETAP_NONE;
    }
    /***********************************************************/

    /***********************************************************/
    //Перевіряємо необхідність очистки аналогового і дискретного реєстраторів
    /***********************************************************/
    //Аналоговий реєстратор
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
      //Виставлено каманда очистити аналогового реєстратора

      //Виставляємо команду запису цієї структури у EEPROM
      _SET_BIT(control_eeprom_taskes, TASK_START_WRITE_INFO_REJESTRATOR_AR_EEPROM_BIT);
    
      //Очищаємо структуру інформації по дискретному реєстраторі
      info_rejestrator_ar.next_address = MIN_ADDRESS_AR_AREA;
      info_rejestrator_ar.saving_execution = 0;
      info_rejestrator_ar.number_records = 0;
    
      //Помічаємо, що номер запису не вибраний
      number_record_of_ar_for_menu = 0xffff;
      number_record_of_ar_for_USB = 0xffff;
      number_record_of_ar_for_RS485 = 0xffff;

      //Знімаємо команду очистки аналогового реєстратора
      clean_rejestrators &= (unsigned int)(~CLEAN_AR);
    }
    
    //Дискретний реєстратор
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
      //Виставлено каманда очистити дискретного реєстратор

      //Виставляємо команду запису цієї структури у EEPROM
      _SET_BIT(control_eeprom_taskes, TASK_START_WRITE_INFO_REJESTRATOR_DR_EEPROM_BIT);

      //Очищаємо структуру інформації по дискретному реєстраторі
      info_rejestrator_dr.next_address = MIN_ADDRESS_DR_AREA;
      info_rejestrator_dr.saving_execution = 0;
      info_rejestrator_dr.number_records = 0;

      //Помічаємо, що номер запису не вибраний
      number_record_of_dr_for_menu  = 0xffff;
      number_record_of_dr_for_USB   = 0xffff;
      number_record_of_dr_for_RS485 = 0xffff;

      //Знімаємо команду очистки дискретного реєстратора
      clean_rejestrators &= (unsigned int)(~CLEAN_DR);
    }
    /***********************************************************/

    /***********************************************************/
    //Опрцювання логічних тайменрів і дискретних входів тільки коли настройки успішно прочитані
    /***********************************************************/
    clocking_global_timers();
    /***********************************************************/
    
    /***********************************************************/
    //Опрцювання функцій захистів
    /***********************************************************/
    //Діагностика вузлів, яку треба проводити кожен раз перед початком опрацьовуванням логіки пристрою
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
      //Формуємо стани виходів у відповідності до зміненої нумерації
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
    
    //Перевіряємо достовірність значень для аналогового реєстратора
    if (
        (state_ar_record  != STATE_AR_TEMPORARY_BLOCK) &&
        (changed_settings == CHANGED_ETAP_NONE       )  
       )   
    {
      //Перевірку здійснюємо тільки тоді, коли не іде зміна часових параметрів
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
        //Теоретично ця помилка ніколи не малаб реєструватися
        /*Якщо виникла така ситуація то треба зациклити ропаграму, щоб вона пішла на перезапуск - 
        бо відбулася недопустима незрозуміла помилка у розраховуваних параметрах аналогового реєстратора.
        Не зрозумілу чого вона виникла, коли і де, коректність роботи пригоамного забезпечення під питанням!*/
        total_error_sw_fixed(5);
      }
    }

    //Функції захистів
    main_protection();
    /***********************************************************/

    /***********************************************************/
    //Перевірка на необхідність зроботи резервні копії даних для самоконтролю
    /***********************************************************/
    //Триґерна інформація
    if (periodical_tasks_TEST_TRG_FUNC != 0)
    {
      //Стоїть у черзі активна задача зроботи резервні копії даних
      if ((state_eeprom_task & STATE_TRG_FUNC_EEPROM_GOOD) != 0)
      {
        //Робимо копію тільки тоді, коли триґерна інформація успішно зчитана і сформована контрольна сума
        if (
            (_CHECK_SET_BIT(control_eeprom_taskes, TASK_START_WRITE_TRG_FUNC_EEPROM_BIT) == 0) &&
            (_CHECK_SET_BIT(control_eeprom_taskes, TASK_WRITING_TRG_FUNC_EEPROM_BIT    ) == 0) &&
            (_CHECK_SET_BIT(control_eeprom_taskes, TASK_START_READ_TRG_FUNC_EEPROM_BIT ) == 0) &&
            (_CHECK_SET_BIT(control_eeprom_taskes, TASK_READING_TRG_FUNC_EEPROM_BIT    ) == 0)
           ) 
        {
          //На даний моммент не іде читання-запис триґерної інформації, тому можна здійснити копіювання
          misceve_dystancijne_ctrl = misceve_dystancijne;
          for (unsigned int i = 0; i < N_BIG; i++) trigger_active_functions_ctrl[i] = trigger_active_functions[i];
          crc_trg_func_ctrl = crc_trg_func;

          //Скидаємо активну задачу формування резервної копії 
          periodical_tasks_TEST_TRG_FUNC = false;
          //Виставляємо активну задачу контролю достовірності по резервній копії 
          periodical_tasks_TEST_TRG_FUNC_LOCK = true;
        }
      }
      else
      {
        //Скидаємо активну задачу формування резервної копії 
        periodical_tasks_TEST_TRG_FUNC = false;
      }
    }

    //Аналоговий реєстратор
    if (periodical_tasks_TEST_INFO_REJESTRATOR_AR != 0)
    {
      //Стоїть у черзі активна задача зроботи резервні копії даних
      if ((state_eeprom_task & STATE_INFO_REJESTRATOR_AR_EEPROM_GOOD) != 0)
      {
        //Робимо копію тільки тоді, коли структура інформації реєстратора успішно зчитана і сформована контрольна сума
        if (
            (_CHECK_SET_BIT(control_eeprom_taskes, TASK_START_WRITE_INFO_REJESTRATOR_AR_EEPROM_BIT) == 0) &&
            (_CHECK_SET_BIT(control_eeprom_taskes, TASK_WRITING_INFO_REJESTRATOR_AR_EEPROM_BIT    ) == 0) &&
            (_CHECK_SET_BIT(control_eeprom_taskes, TASK_START_READ_INFO_REJESTRATOR_AR_EEPROM_BIT ) == 0) &&
            (_CHECK_SET_BIT(control_eeprom_taskes, TASK_READING_INFO_REJESTRATOR_AR_EEPROM_BIT    ) == 0)
           ) 
        {
          //На даний моммент не іде читання-запис структури інформації реєстратора, тому можна здійснити копіювання
          info_rejestrator_ar_ctrl = info_rejestrator_ar;
          crc_info_rejestrator_ar_ctrl = crc_info_rejestrator_ar;

          //Скидаємо активну задачу формування резервної копії 
          periodical_tasks_TEST_INFO_REJESTRATOR_AR = false;
          //Виставляємо активну задачу контролю достовірності по резервній копії 
          periodical_tasks_TEST_INFO_REJESTRATOR_AR_LOCK = true;
        }
      }
      else
      {
        //Скидаємо активну задачу формування резервної копії 
        periodical_tasks_TEST_INFO_REJESTRATOR_AR = false;
      }
    }

    //Дискретний реєстратор
    if (periodical_tasks_TEST_INFO_REJESTRATOR_DR != 0)
    {
      //Стоїть у черзі активна задача зроботи резервні копії даних
      if ((state_eeprom_task & STATE_INFO_REJESTRATOR_DR_EEPROM_GOOD) != 0)
      {
        //Робимо копію тільки тоді, коли структура інформації реєстратора успішно зчитана і сформована контрольна сума
        if (
            (_CHECK_SET_BIT(control_eeprom_taskes, TASK_START_WRITE_INFO_REJESTRATOR_DR_EEPROM_BIT) == 0) &&
            (_CHECK_SET_BIT(control_eeprom_taskes, TASK_WRITING_INFO_REJESTRATOR_DR_EEPROM_BIT    ) == 0) &&
            (_CHECK_SET_BIT(control_eeprom_taskes, TASK_START_READ_INFO_REJESTRATOR_DR_EEPROM_BIT ) == 0) &&
            (_CHECK_SET_BIT(control_eeprom_taskes, TASK_READING_INFO_REJESTRATOR_DR_EEPROM_BIT    ) == 0)
           ) 
        {
          //На даний моммент не іде читання-запис структури інформації реєстратора, тому можна здійснити копіювання
          info_rejestrator_dr_ctrl = info_rejestrator_dr;
          crc_info_rejestrator_dr_ctrl = crc_info_rejestrator_dr;

          //Скидаємо активну задачу формування резервної копії 
          periodical_tasks_TEST_INFO_REJESTRATOR_DR = false;
          //Виставляємо активну задачу контролю достовірності по резервній копії 
          periodical_tasks_TEST_INFO_REJESTRATOR_DR_LOCK = true;
        }
      }
      else
      {
        //Скидаємо активну задачу формування резервної копії 
        periodical_tasks_TEST_INFO_REJESTRATOR_DR = false;
      }
    }
    /***********************************************************/

    //Лічильник ресурсу
    if (periodical_tasks_TEST_RESURS != 0)
    {
      //Стоїть у черзі активна задача зроботи резервні копії даних
      if ((state_eeprom_task & STATE_RESURS_EEPROM_GOOD) != 0)
      {
        //Робимо копію тільки тоді, коли інформаціz успішно зчитана і сформована контрольна сума
        if (
            (_CHECK_SET_BIT(control_eeprom_taskes, TASK_START_WRITE_RESURS_EEPROM_BIT) == 0) &&
            (_CHECK_SET_BIT(control_eeprom_taskes, TASK_WRITING_RESURS_EEPROM_BIT    ) == 0) &&
            (_CHECK_SET_BIT(control_eeprom_taskes, TASK_START_READ_RESURS_EEPROM_BIT ) == 0) &&
            (_CHECK_SET_BIT(control_eeprom_taskes, TASK_READING_RESURS_EEPROM_BIT    ) == 0)
           ) 
        {
          //На даний моммент не іде читання-запис ресурсу вимикача, тому можна здійснити копіювання
          resurs_vymykacha_ctrl = resurs_vymykacha;          
          resurs_vidkljuchennja_ctrl = resurs_vidkljuchennja;
          crc_resurs_ctrl = crc_resurs;

          //Скидаємо активну задачу формування резервної копії 
          periodical_tasks_TEST_RESURS = false;
          //Виставляємо активну задачу контролю достовірності по резервній копії 
          periodical_tasks_TEST_RESURS_LOCK = true;
        }
      }
      else
      {
        //Скидаємо активну задачу формування резервної копії 
        periodical_tasks_TEST_RESURS = false;
      }
    }

    /***********************************************************/
    //Встановлюємо "значення лічильника для наступного переривання"
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
            delta = 1; /*Намагаємося, щоб нове переивання запустилося як омога скоріше*/
          else
          {
            //Теоретично цього ніколи не мало б бути
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
    //Виставляємо повідомлення про те, система захисів праціює
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
//Вибір групи уставок
/*****************************************************/
void setpoints_selecting(unsigned int *activated_functions, unsigned int act_inp_gr_ustavok) {
  unsigned int grupa_ustavok = 0;
  act_inp_gr_ustavok &= 0xf;
  if (current_settings_prt.grupa_ustavok < SETPOINT_GRUPA_USTAVOK_MIN ||
      current_settings_prt.grupa_ustavok > SETPOINT_GRUPA_USTAVOK_MAX) {
    //Неопределенная ошибка
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
