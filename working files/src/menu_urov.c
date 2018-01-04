#include "header.h"

/*****************************************************/
//������� ����� ����������� ������� ����
/*****************************************************/
void make_ekran_setpoint_urov(unsigned int group)
{
  const unsigned char name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_SETPOINT_UROV][MAX_COL_LCD] = 
  {
    {
      "  ������� ����  "
    },
    {
      "  ������� ����  "
    },
    {
      "  CBFP Pickup   "
    },
    {
      "  ������� ����  "
    }
  };
  int index_language = index_language_in_array(current_settings.language);
  
  unsigned int position_temp = current_ekran.index_position;
  unsigned int index_of_ekran;
  unsigned int vaga, value, first_symbol;
  
  //�������� �� ��� �������� position_temp ������� ��� ����, �� �� ���� ������� �� ������������� ��� ����� (����� + ��������)
  index_of_ekran = ((position_temp<<1) >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;

  
  for (unsigned int i=0; i< MAX_ROW_LCD; i++)
  {
    //������� ����� ����� ���������, �� �� ����� ���������� � ������� ������������
    if (index_of_ekran < (MAX_ROW_FOR_SETPOINT_UROV<<1))//�������� �� ��� ��������� MAX_ROW_FOR_SETPOINT_UROV ������� ��� ����, �� �� ���� ������� �� ������������� ��� ����� (����� + ��������)
    {
      if ((i & 0x1) == 0)
      {
        //� ��������� ����� ����� �������� ���������
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][index_of_ekran>>1][j];

        vaga = 1000; //������������ ������� ���������� ��� �������� �������� ������� ��� ������� ����
        if (current_ekran.edition == 0) value = current_settings.setpoint_urov[group]; //� ����� value ������� �������� ������� ��
        else value = edition_settings.setpoint_urov[group];
        first_symbol = 0; //�������, �� �� ����� �������� ������ �� ���������
      }
      else
      {
        //� ������� ����� ����� �������� �������� �������
        for (unsigned int j = 0; j<MAX_COL_LCD; j++)
        {
          if (
              ((j < COL_SETPOINT_UROV_BEGIN) ||  (j > COL_SETPOINT_UROV_END )) &&
              (j != (COL_SETPOINT_UROV_END + 2))  
             )working_ekran[i][j] = ' ';
          else if (j == COL_SETPOINT_UROV_COMMA )working_ekran[i][j] = ',';
          else if (j == (COL_SETPOINT_UROV_END + 2)) working_ekran[i][j] = odynyci_vymirjuvannja[index_language][INDEX_A];
          else
            calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_SETPOINT_UROV_COMMA, 0);
        }
      }
    }
    else
      for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';

    index_of_ekran++;
  }

  //³���������� ������ �� �������� � ������ ������ �� ���� � ��� �� ��������� ������
  current_ekran.position_cursor_y = ((position_temp<<1) + 1) & (MAX_ROW_LCD - 1);
  //������ �� ���������� ������������ �� ������� ������ � �������, ���� �� �� � ����� �����������, ������ ������� ���� ��������� � ������ main_manu_function
  if (current_ekran.edition == 0)
  {
    current_ekran.position_cursor_x = COL_SETPOINT_UROV_BEGIN;
    int last_position_cursor_x = COL_SETPOINT_UROV_END;

    //ϳ������� ������ �� ������� �������
    while (((working_ekran[current_ekran.position_cursor_y][current_ekran.position_cursor_x + 1]) == ' ') && 
           (current_ekran.position_cursor_x < (last_position_cursor_x -1))) current_ekran.position_cursor_x++;
    
    //������ ������� ���, ��� �� ��� ����� ������
    if (((working_ekran[current_ekran.position_cursor_y][current_ekran.position_cursor_x]) != ' ') && 
        (current_ekran.position_cursor_x > 0)) current_ekran.position_cursor_x--;
  }
  //������ �������
  current_ekran.cursor_on = 1;
  //������ �� ����
  if(current_ekran.edition == 0)current_ekran.cursor_blinking_on = 0;
  else current_ekran.cursor_blinking_on = 1;
  //�������� ������� ���� �����
  current_ekran.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
//������� ����� ����������� �������� ����
/*****************************************************/
void make_ekran_timeout_urov(unsigned int group)
{
  const unsigned char name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_TIMEOUT_UROV][MAX_COL_LCD] = 
  {
    {
      " 1 ������� ���� ",
      " 2 ������� ���� "
    },
    {
      " 1 ������ ���� ",
      " 2 ������ ���� "
    },
    {
      "  CBFP Stage 1  ",
      "  CBFP Stage 2  "
    },
    {
      " 1 ������� ���� ",
      " 2 ������� ���� "
    }
  };
  int index_language = index_language_in_array(current_settings.language);
  
  unsigned int position_temp = current_ekran.index_position;
  unsigned int index_of_ekran;
  unsigned int vaga, value, first_symbol;
  
  //�������� �� ��� �������� position_temp ������� ��� ����, �� �� ���� ������� �� ������������� ��� ����� (����� + ��������)
  index_of_ekran = ((position_temp<<1) >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;

  
  for (unsigned int i=0; i< MAX_ROW_LCD; i++)
  {
    if (index_of_ekran < (MAX_ROW_FOR_TIMEOUT_UROV<<1))//�������� �� ��� ��������� MAX_ROW_FOR_TIMEOUT_UROV ������� ��� ����, �� �� ���� ������� �� ������������� ��� ����� (����� + ��������)
    {
      if ((i & 0x1) == 0)
      {
        //� ��������� ����� ����� �������� ���������
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][index_of_ekran>>1][j];
        if ((index_of_ekran>>1) == INDEX_ML_TMOUROV1)
        {
          vaga = 10000; //������������ ������� ���������� ��� �������� �������� ������� ��� �������� 1 ������ ����
          if (current_ekran.edition == 0) value = current_settings.timeout_urov_1[group]; //� ����� value ������� �������� �������� 1 ������ ����
          else value = edition_settings.timeout_urov_1[group];
          first_symbol = 0; //�������, �� �� ����� �������� ������ �� ���������
        }
        else if ((index_of_ekran>>1) == INDEX_ML_TMOUROV2)
        {
          vaga = 10000; //������������ ������� ���������� ��� �������� �������� ������� ��� �������� 2 ������ ����
          if (current_ekran.edition == 0) value = current_settings.timeout_urov_2[group]; //� ����� value ������� �������� �������� 2 ������ ����
          else value = edition_settings.timeout_urov_2[group];
          first_symbol = 0; //�������, �� �� ����� �������� ������ �� ���������
        }
      }
      else
      {
        //� ������� ����� ����� �������� �������� �������
        for (unsigned int j = 0; j<MAX_COL_LCD; j++)
        {
          if ((index_of_ekran>>1) == INDEX_ML_TMOUROV1)
          {
            if (
                ((j < COL_TMO_UROV_1_BEGIN) ||  (j > COL_TMO_UROV_1_END )) &&
                (j != (COL_TMO_UROV_1_END + 2))  
               )working_ekran[i][j] = ' ';
            else if (j == COL_TMO_UROV_1_COMMA )working_ekran[i][j] = ',';
            else if (j == (COL_TMO_UROV_1_END + 2)) working_ekran[i][j] = odynyci_vymirjuvannja[index_language][INDEX_SECOND];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_TMO_UROV_1_COMMA, 0);
          }
          else if ((index_of_ekran>>1) == INDEX_ML_TMOUROV2)
          {
            if (
                ((j < COL_TMO_UROV_2_BEGIN) ||  (j > COL_TMO_UROV_2_END )) &&
                (j != (COL_TMO_UROV_2_END + 2))  
               )working_ekran[i][j] = ' ';
            else if (j == COL_TMO_UROV_2_COMMA )working_ekran[i][j] = ',';
            else if (j == (COL_TMO_UROV_2_END + 2)) working_ekran[i][j] = odynyci_vymirjuvannja[index_language][INDEX_SECOND];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_TMO_UROV_2_COMMA, 0);
          }
        }
      }
        
    }
    else
      for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';

    index_of_ekran++;
  }

  //³���������� ������ �� �������� � ������ ������ �� ���� � ��� �� ��������� ������
  current_ekran.position_cursor_y = ((position_temp<<1) + 1) & (MAX_ROW_LCD - 1);
  //������ �� ���������� ������������ �� ������� ������ � �������, ���� �� �� � ����� �����������, ������ ������� ���� ��������� � ������ main_manu_function
  if (current_ekran.edition == 0)
  {
    int last_position_cursor_x = MAX_COL_LCD;
    if (current_ekran.index_position == INDEX_ML_TMOUROV1)
    {
      current_ekran.position_cursor_x = COL_TMO_UROV_1_BEGIN;
      last_position_cursor_x = COL_TMO_UROV_1_END;
    }
    else if (current_ekran.index_position == INDEX_ML_TMOUROV2)
    {
      current_ekran.position_cursor_x = COL_TMO_UROV_2_BEGIN;
      last_position_cursor_x = COL_TMO_UROV_2_END;
    }

    //ϳ������� ������ �� ������� �������
    while (((working_ekran[current_ekran.position_cursor_y][current_ekran.position_cursor_x + 1]) == ' ') && 
           (current_ekran.position_cursor_x < (last_position_cursor_x -1))) current_ekran.position_cursor_x++;

    //������ ������� ���, ��� �� ��� ����� ������
    if (((working_ekran[current_ekran.position_cursor_y][current_ekran.position_cursor_x]) != ' ') && 
        (current_ekran.position_cursor_x > 0)) current_ekran.position_cursor_x--;
  }
  //������ �������
  current_ekran.cursor_on = 1;
  //������ �� ����
  if(current_ekran.edition == 0)current_ekran.cursor_blinking_on = 0;
  else current_ekran.cursor_blinking_on = 1;
  //�������� ������� ���� �����
  current_ekran.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
//������� ����� ����������� �������� ����������� ���������� ��� ����
/*****************************************************/
void make_ekran_control_urov()
{
  const unsigned char name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_CONTROL_UROV][MAX_COL_LCD] = 
  {
    {
      "      ����      ",
      "  ���� �� ���1  ",
      "  ���� �� ���2  ",
      "  ���� �� ���3  ",
      "  ���� �� ���4  ",
      "  ���� �� ���   ",
      "  ���� �� 3I0   ",
      "  ���� �� 3U0   ",
      "  ���� �� ���   ",
      "���� �� ���(���)",
      " ���� �� �����1 ",
      " ���� �� �����2 ",
      " ���� �� ������1",
      " ���� �� ������2",
      "  ���� �� ���   "
    },
    {
      "      ����      ",
      " ���� �� ���1  ",
      " ���� �� ���2  ",
      " ���� �� ���3  ",
      " ���� �� ���4  ",
      "  ���� �� ���  ",
      "  ���� �� 3I0  ",
      "  ���� �� 3U0  ",
      "  ���� �� ���  ",
      " �.�� ���(���) ",
      " ���� �� ����1",
      " ���� �� ����2",
      "���� �� ������1",
      "���� �� ������2",
      "  ���� �� ���  "
    },
    {
      "      CBFP      ",
      " Start from OCP1",
      " Start from OCP2",
      " Start from OCP3",
      " Start from OCP4",
      "  ���� �� ���   ",
      " Start from 3I0 ",
      " Start from 3U0 ",
      "  ���� �� ���   ",
      " Start from NPSP",
      "Start from Umin1",
      "Start from Umin2",
      "Start from Umax1",
      "Start from Umax2",
      "  ���� �� ���   "
    },
    {
      "      ����      ",
      "  ���� �� ���1  ",
      "  ���� �� ���2  ",
      "  ���� �� ���3  ",
      "  ���� �� ���4  ",
      "  ���� �� ���   ",
      "  ���� �� 3I0   ",
      "  ���� �� 3U0   ",
      "  ���� �� ���   ",
      "���� �� ���(���)",
      " ���� �� �����1 ",
      " ���� �� �����2 ",
      " ���� �� ������1",
      " ���� �� ������2",
      "  ���� �� ���   "
    }
  };
  unsigned char name_string_tmp[MAX_ROW_FOR_CONTROL_UROV][MAX_COL_LCD];

  int index_language = index_language_in_array(current_settings.language);
  for(int index_1 = 0; index_1 < MAX_ROW_FOR_CONTROL_UROV; index_1++)
  {
    for(int index_2 = 0; index_2 < MAX_COL_LCD; index_2++)
      name_string_tmp[index_1][index_2] = name_string[index_language][index_1][index_2];
  }
  
  unsigned int temp_data;
  if(current_ekran.edition == 0) temp_data = current_settings.control_urov;
  else temp_data = edition_settings.control_urov;
        
  /******************************************/
  //��������� ����, �� �� ����� ����������
  /******************************************/
  int additional_current_mtz = 0, additional_current_zdz = 0, additional_current_zz = 0, additional_current_zop = 0, additional_current_Umin = 0, additional_current_Umax = 0, additional_current_achr = 0;
  int position_temp = current_ekran.index_position;
  int index_of_ekran;

  int additional_current = additional_current_mtz + additional_current_zdz + additional_current_zz + additional_current_zop + additional_current_Umin + additional_current_Umax + additional_current_achr;
  for (int current_index = 0; current_index < (MAX_ROW_FOR_CONTROL_UROV - additional_current); current_index++ )
  {

    if (
        (
         (
          (current_index == INDEX_ML_CTRUROV_STARTED_FROM_MTZ1) ||
          (current_index == INDEX_ML_CTRUROV_STARTED_FROM_MTZ2) ||
          (current_index == INDEX_ML_CTRUROV_STARTED_FROM_MTZ3) ||
          (current_index == INDEX_ML_CTRUROV_STARTED_FROM_MTZ4)
         )   
         &&
         ((current_settings.configuration & (1<<MTZ_BIT_CONFIGURATION)) == 0)
        )  
        ||
        (
         (
          (current_index == INDEX_ML_CTRUROV_STARTED_FROM_ZDZ)
         )   
         &&
         ((current_settings.configuration & (1<<ZDZ_BIT_CONFIGURATION)) == 0)
        )
        ||
        (
         (
          (current_index == INDEX_ML_CTRUROV_STARTED_FROM_3I0) ||
          (current_index == INDEX_ML_CTRUROV_STARTED_FROM_3U0) ||
          (current_index == INDEX_ML_CTRUROV_STARTED_FROM_NZZ)
         )   
         &&
         ((current_settings.configuration & (1<<ZZ_BIT_CONFIGURATION)) == 0)
        )
        ||
        (
         (
          (current_index == INDEX_ML_CTRUROV_STARTED_FROM_3U0) ||
          (current_index == INDEX_ML_CTRUROV_STARTED_FROM_NZZ)
         )
         &&  
         ((current_settings.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_3U0_Ubc_TN2) != 0)  
        )
        ||
        (
         (
          (current_index == INDEX_ML_CTRUROV_STARTED_FROM_NZZ)
         )
         &&  
         ((current_settings.control_zz & CTR_ZZ1_TYPE) != 0)  
        )
        ||
        (
         (
          (current_index == INDEX_ML_CTRUROV_STARTED_FROM_ZOP1)
         )   
         &&
         ((current_settings.configuration & (1<<ZOP_BIT_CONFIGURATION)) == 0)
        )
        ||
        (
         (
          (current_index == INDEX_ML_CTRUROV_STARTED_FROM_UMIN1) ||
          (current_index == INDEX_ML_CTRUROV_STARTED_FROM_UMIN2)
         )   
         &&
         ((current_settings.configuration & (1<<UMIN_BIT_CONFIGURATION)) == 0)
        )  
        ||
        (
         (
          (current_index == INDEX_ML_CTRUROV_STARTED_FROM_UMAX1) ||
          (current_index == INDEX_ML_CTRUROV_STARTED_FROM_UMAX2)
         )   
         &&
         ((current_settings.configuration & (1<<UMAX_BIT_CONFIGURATION)) == 0)
        )  
        ||
        (
         (
          (current_index == INDEX_ML_CTRUROV_STARTED_FROM_ACHR)
         )   
         &&
         ((current_settings.configuration & (1<<ACHR_CHAPV_BIT_CONFIGURATION)) == 0)
        )
       )   
    {
      int i = current_index - additional_current;
      unsigned int maska_1, maska_2;
      maska_1 = (1 << i) - 1;
      maska_2 = (unsigned int)(~maska_1);
    
      if ((i+1) <= position_temp) position_temp--;
      do
      {
        for(unsigned int j = 0; j < MAX_COL_LCD; j++)
        {
          if ((i+1) < (MAX_ROW_FOR_CONTROL_UROV - additional_current)) name_string_tmp[i][j] = name_string_tmp[i + 1][j];
          else name_string_tmp[i][j] = ' ';
        }
        i++;
      }
      while (i < (MAX_ROW_FOR_CONTROL_UROV -  additional_current));
    
      unsigned int temp_data_1 = (temp_data >> 1) & maska_2;
      temp_data = (temp_data & maska_1) | temp_data_1;

      if (
          (current_index == INDEX_ML_CTRUROV_STARTED_FROM_MTZ1) ||
          (current_index == INDEX_ML_CTRUROV_STARTED_FROM_MTZ2) ||
          (current_index == INDEX_ML_CTRUROV_STARTED_FROM_MTZ3) ||
          (current_index == INDEX_ML_CTRUROV_STARTED_FROM_MTZ4)
         )   
        additional_current_mtz++;

      if (
          (current_index == INDEX_ML_CTRUROV_STARTED_FROM_ZDZ)
         )   
        additional_current_zdz++;

      if (
          (current_index == INDEX_ML_CTRUROV_STARTED_FROM_3I0) ||
          (current_index == INDEX_ML_CTRUROV_STARTED_FROM_3U0) ||
          (current_index == INDEX_ML_CTRUROV_STARTED_FROM_NZZ)
         )   
        additional_current_zz++;

      if (
          (current_index == INDEX_ML_CTRUROV_STARTED_FROM_ZOP1)
         )   
        additional_current_zop++;

      if (
          (current_index == INDEX_ML_CTRUROV_STARTED_FROM_UMIN1) ||
          (current_index == INDEX_ML_CTRUROV_STARTED_FROM_UMIN2)
         )   
        additional_current_Umin++;

      if (
          (current_index == INDEX_ML_CTRUROV_STARTED_FROM_UMAX1) ||
          (current_index == INDEX_ML_CTRUROV_STARTED_FROM_UMAX2)
         )   
        additional_current_Umax++;

      if (
          (current_index == INDEX_ML_CTRUROV_STARTED_FROM_ACHR)
         )   
        additional_current_achr++;
      
      additional_current = additional_current_mtz + additional_current_zdz + additional_current_zz + additional_current_zop + additional_current_Umin + additional_current_Umax + additional_current_achr;
    }
  }
  /******************************************/
  
  //�������� �� ��� �������� position_temp ������� ��� ����, �� �� ���� ������� �� ������������� ��� ����� (����� + ��������)
  index_of_ekran = ((position_temp<<1) >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;

  
  for (unsigned int i=0; i< MAX_ROW_LCD; i++)
  {
    if (index_of_ekran < ((MAX_ROW_FOR_CONTROL_UROV - additional_current) << 1))//�������� �� ��� ��������� MAX_ROW_FOR_CONTROL_UROV ������� ��� ����, �� �� ���� ������� �� ������������� ��� ����� (����� + ��������)
    {
      if ((i & 0x1) == 0)
      {
        //� ��������� ����� ����� �������� ���������
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string_tmp[index_of_ekran>>1][j];
      }
      else
      {
        //� ������� ����� ����� �������� �������� �������
        const unsigned char information[MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD] = 
        {
          {"     ����.      ", "      ���.      "},
          {"     ����.      ", "     ����.     "},
          {"      Off       ", "       On       "},
          {"     њ��.      ", "     ����.      "}
        };
        const unsigned int cursor_x[MAX_NAMBER_LANGUAGE][2] = 
        {
         {4, 5},
         {4, 4},
         {5, 6},
         {4, 4}
        };
        
        unsigned int index_ctr = (index_of_ekran>>1);

        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = information[index_language][(temp_data >> index_ctr) & 0x1][j];
        current_ekran.position_cursor_x = cursor_x[index_language][(temp_data >> index_ctr) & 0x1];
      }
    }
    else
      for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';

    index_of_ekran++;
  }

  //³���������� ������ �� �������� � ������ ������ �� ���� � ��� �� ��������� ������
  current_ekran.position_cursor_y = ((position_temp<<1) + 1) & (MAX_ROW_LCD - 1);
  //������ �������
  current_ekran.cursor_on = 1;
  //������ �� ����
  if(current_ekran.edition == 0)current_ekran.cursor_blinking_on = 0;
  else current_ekran.cursor_blinking_on = 1;
  //�������� ������� ���� �����
  current_ekran.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
//
/*****************************************************/
/*****************************************************/
