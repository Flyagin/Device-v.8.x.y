#include "header.h"

/*****************************************************/
//������� ����� ������ ��/����/�� ��� ����������
/* 
-------------------------------------------------------
������� ��������
0 - �����
1 - ������
2 - ��������
3 - ������������ �������
4 - ������������ ������
5 - ������������ ������
-------------------------------------------------------
*/
/*****************************************************/
void make_ekran_chose_of_inputs_outputs_leds_df_buttons_for_ranguvannja(unsigned int type_of_window)
{
  const unsigned char information[MAX_NAMBER_LANGUAGE][6][MAX_COL_LCD] = 
  {
    {" ���            ", " ����           ", " ��             ", " �-�������      ", " F              ", " �-�������      "},
    {" ���            ", " ����           ", " ��             ", " �-�������      ", " F              ", " �-�����       "},
    {" DI             ", " DO             ", " LED            ", " UD Function    ", " F              ", " UD Flip-Flop   "},
    {" ���            ", " ����           ", " ��             ", " �-�������      ", " F              ", " �-�������      "}
  };

  const unsigned int first_index_number[MAX_NAMBER_LANGUAGE][6] = 
  {
    {4, 5, 3, 10, 2, 10},
    {4, 5, 3, 10, 2,  9},
    {3, 3, 4, 12, 2, 13},
    {4, 5, 3, 10, 2, 10}
  };
  
  const unsigned int max_row[6] =
  {
    MAX_ROW_LIST_INPUTS_FOR_RANGUVANNJA,
    MAX_ROW_LIST_OUTPUTS_FOR_RANGUVANNJA,
    MAX_ROW_LIST_LEDS_FOR_RANGUVANNJA,
    MAX_ROW_FOR_LIST_DF,
    MAX_ROW_LIST_BUTTONS_FOR_RANGUVANNJA,
    MAX_ROW_FOR_LIST_DT
  };
  int index_language = index_language_in_array(current_settings.language);
  unsigned int first_index_number_1 = first_index_number[index_language][type_of_window];
        
  unsigned int position_temp = current_ekran.index_position;
  unsigned int index_of_ekran = (position_temp >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;

  //������� �����  ����� � ������� �����
  for (unsigned int i=0; i< MAX_ROW_LCD; i++)
  {
    unsigned int number = index_of_ekran + 1;
    unsigned int tmp_1 = (number / 10), tmp_2 = number - tmp_1*10;

    //������� ����� ����� ���������, �� �� ����� ���������� � ������� ������������
    if (index_of_ekran < max_row[type_of_window])
    {
      for (unsigned int j = 0; j<MAX_COL_LCD; j++)
      {
        if ((j < first_index_number_1) || (j >= (first_index_number_1 + 2 + 3)))
           working_ekran[i][j] = information[index_language][type_of_window][j];
        else
        {
          if (j == first_index_number_1)
          {
            if (tmp_1 > 0 ) working_ekran[i][j] = tmp_1 + 0x30;
          }
          else if (j == (first_index_number_1 + 1))     
          {
            if (tmp_1 > 0 )
            {
              working_ekran[i][j] = tmp_2 + 0x30;
            }
            else
            {
              working_ekran[i][j - 1] = tmp_2 + 0x30;
              working_ekran[i][j] = '.';
            }
          }
          else
          {
            if (tmp_1 > 0 )
            {
              working_ekran[i][j] = '.';
            }
            else
            {
              if ( j < (first_index_number_1 + 2 + 3 - 1))
                working_ekran[i][j] = '.';
              else
                working_ekran[i][j] = ' ';
            }
          }
        }
      }
    }
    else
    {
      for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';
    }

    index_of_ekran++;
  }

  //������ �� ���������� ������������ �� ������ �������
  current_ekran.position_cursor_x = 0;
  //³���������� ������ �� ��������
  current_ekran.position_cursor_y = position_temp & (MAX_ROW_LCD - 1);
  //������ �������
  current_ekran.cursor_on = 1;
  //������ �� ����
  current_ekran.cursor_blinking_on = 0;
  //�������� ������� ���� �����
  current_ekran.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
//������� ����� ����������� ����������� ������� �� ������������� ������
/*****************************************************/
void make_ekran_set_function_in_button(unsigned int number_ekran)
{
#define NUMBER_ROW_FOR_NOTHING_INFORMATION 2
  
  const unsigned char name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_RANGUVANNJA_BUTTON + NUMBER_ROW_FOR_NOTHING_INFORMATION][MAX_COL_LCD] = 
  {
    {
      "      ���       ",
      "  ������������  ",
      " ��.�-�������1  ",
      " ��.�-�������2  ",
      " ��.�-�������3  ",
      " ��.�-�������4  ",
      " ��.�-�������5  ",
      " ��.�-�������6  ",
      " ��.�-�������7  ",
      " ��.�-�������8  ",
      " ���.�-��������1",
      " ���.�-��������1",
      " ���.�-��������2",
      " ���.�-��������2",
      " ���.�-��������3",
      " ���.�-��������3",
      " ���.�-��������4",
      " ���.�-��������4",
      " ����� ���������",
      "   ����� ����   ",
      " �����./�������.",
      "     ���.��     ",
      "    ����.��     ",
      " �.���.���.� �� ",
      " �.���.���-���  ",
      "  ��.����.���   ",
      " ����� ����.��� "
    },
    {
      "      ����      ",
      "   ����������   ",
      " ��.�-�������1  ",
      " ��.�-�������2  ",
      " ��.�-�������3  ",
      " ��.�-�������4  ",
      " ��.�-�������5  ",
      " ��.�-�������6  ",
      " ��.�-�������7  ",
      " ��.�-�������8  ",
      " ���.�-������1 ",
      " ��.�-������1  ",
      " ���.�-������2 ",
      " ��.�-������2  ",
      " ���.�-������3 ",
      " ��.�-������3  ",
      " ���.�-������4 ",
      " ��.�-������4  ",
      " ����.��������� ",
      "   ����.����    ",
      " ̳��./�������. ",
      "    ����.��    ",
      "    ����.��     ",
      " �.���.���.�� ��",
      " �.���.���-���  ",
      " ����.����.���  ",
      " ����.����.���  "
    },
    {
      "       No       ",
      "    ranking     ",
      "    UDF1 In     ",
      "    UDF2 In     ",
      "    UDF3 In     ",
      "    UDF4 In     ",
      "    UDF5 In     ",
      "    UDF6 In     ",
      "    UDF7 In     ",
      "    UDF8 In     ",
      "UD Flip-Flop1 S.",
      "UD Flip-Flop1 R.",
      "UD Flip-Flop2 S.",
      "UD Flip-Flop2 R.",
      "UD Flip-Flop3 S.",
      "UD Flip-Flop3 R.",
      "UD Flip-Flop4 S.",
      "UD Flip-Flop4 R.",
      "Indication Reset",
      "  Relay Reset   ",
      "  Local/Remote  ",
      "     On CB      ",
      "     Off CB     ",
      " �.���.���.� �� ",
      " �.���.���-���  ",
      "  ��.����.���   ",
      " ����� ����.��� "
    },
    {
      "      ���       ",
      "  ������������  ",
      " ��.�-�������1  ",
      " ��.�-�������2  ",
      " ��.�-�������3  ",
      " ��.�-�������4  ",
      " ��.�-�������5  ",
      " ��.�-�������6  ",
      " ��.�-�������7  ",
      " ��.�-�������8  ",
      " ���.�-��������1",
      " ���.�-��������1",
      " ���.�-��������2",
      " ���.�-��������2",
      " ���.�-��������3",
      " ���.�-��������3",
      " ���.�-��������4",
      " ���.�-��������4",
      " ����� ���������",
      "   ����� ����   ",
      " �����./�������.",
      "     ���.��     ",
      "    ����.��     ",
      " �.���.���.� �� ",
      " �.���.���-���  ",
      "  ��.����.���   ",
      " ����� ����.��� "
    }
  };
  unsigned char name_string_tmp[MAX_ROW_RANGUVANNJA_BUTTON + NUMBER_ROW_FOR_NOTHING_INFORMATION][MAX_COL_LCD];

  int index_language = index_language_in_array(current_settings.language);
  for(int index_1 = 0; index_1 < (MAX_ROW_RANGUVANNJA_BUTTON + NUMBER_ROW_FOR_NOTHING_INFORMATION); index_1++)
  {
    for(int index_2 = 0; index_2 < MAX_COL_LCD; index_2++)
      name_string_tmp[index_1][index_2] = name_string[index_language][index_1][index_2];
  }
  
  if(current_ekran.edition == 0)
  {
    //�������, ���� �� ������������� ��������� ������� �� ������
    unsigned int state_viewing_input = current_settings.ranguvannja_buttons[number_ekran - EKRAN_RANGUVANNJA_BUTTON_1];
    
    if (state_viewing_input == 0)
    {
      //�� ������, �� ����� �� ����������� �� ������
      
      //������ ������� � ������ ���������� �� ��� �������
      current_ekran.index_position = 0;
      position_in_current_level_menu[number_ekran] = 0;

      //�������  ����� � ������� �����
      for (unsigned int i=0; i< MAX_ROW_LCD; i++)
      {
        //������� � ������� ����� ����������, �� ����� �� �����������
        if (i < NUMBER_ROW_FOR_NOTHING_INFORMATION)
          for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string_tmp[i][j];
        else
          for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';
      }

      //³���������� ������ �� ��������
      current_ekran.position_cursor_y = 0;
      //������ ���������
      current_ekran.cursor_on = 0;
    }
    else
    {
      /************************************************************/
      //������� ������ �� �������, �� ������� ����������
      /************************************************************/
      unsigned int position_temp = current_ekran.index_position;
      unsigned int index_of_ekran;
      unsigned int i = 0, offset = 0;

      while ((i + offset) < MAX_ROW_RANGUVANNJA_BUTTON)
      {
        if ((state_viewing_input & (1<<(i + offset))) == 0)
        {
          for (unsigned int j = i; j < (MAX_ROW_RANGUVANNJA_BUTTON - offset); j++)
          {
            if ((j + 1) < (MAX_ROW_RANGUVANNJA_BUTTON - offset))
            {
              for (unsigned int k = 0; k<MAX_COL_LCD; k++)
                name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION][k] = name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION + 1][k];
            }
            else 
            {
              for (unsigned int k = 0; k<MAX_COL_LCD; k++)
                name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION][k] = ' ';
            }
          }
          if (current_ekran.index_position >= ((int)(i + offset))) position_temp--;
          offset++;
        }
        else i++;
      }
      /************************************************************/

    
      index_of_ekran = (position_temp >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;
      
      //�������  ����� � ������� �����
      for (i=0; i< MAX_ROW_LCD; i++)
      {
        //������� ����� ����� ���������, �� �� ����� ���������� � ������� ������������
        if (index_of_ekran < MAX_ROW_RANGUVANNJA_BUTTON)
        {
          for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string_tmp[index_of_ekran + NUMBER_ROW_FOR_NOTHING_INFORMATION][j];

          //ϳ������� �����, ��� �� ���� ������ ������ ������
          unsigned int iteration = 0;
          while (
                 (working_ekran[i][0] == ' ') &&
                 (working_ekran[i][1] == ' ') &&
                 (iteration < (MAX_COL_LCD - 1 - 1))
                )
          {
            for (unsigned int j = 1; j < MAX_COL_LCD; j++)
            {
              if ((j + 1) < MAX_COL_LCD)
                working_ekran[i][j] = working_ekran[i][j + 1];
              else
                working_ekran[i][j] = ' ';
            }
            iteration++;
          }
        }
        else
          for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';

        index_of_ekran++;
      }
      //³���������� ������ �� ��������
      current_ekran.position_cursor_y = position_temp & (MAX_ROW_LCD - 1);
      //������ �������
      current_ekran.cursor_on = 1;
    }
    
    //������ �� ���������� ������������ �� ������ �������
    current_ekran.position_cursor_x = 0;
    //������ �� ����
    current_ekran.cursor_blinking_on = 0;
  }
  else
  {
    unsigned int temp_data = edition_settings.ranguvannja_buttons[current_ekran.current_level - EKRAN_RANGUVANNJA_BUTTON_1];
    unsigned int position_temp = current_ekran.index_position;
    unsigned int index_of_ekran;
    unsigned int i, offset = 0;
    int min_max_number[TOTAL_NUMBER_PROTECTION][2] ={
                                                     {-1,-1},
                                                     {-1,-1},
                                                     {-1,-1},
                                                     {-1,-1},
                                                     {
                                                      (NUMBER_GENERAL_SIGNAL_FOR_RANG_BUTTON + NUMBER_MTZ_SIGNAL_FOR_RANG_BUTTON + NUMBER_ZDZ_SIGNAL_FOR_RANG_BUTTON + NUMBER_ZZ_SIGNAL_FOR_RANG_BUTTON + NUMBER_APV_SIGNAL_FOR_RANG_BUTTON),
                                                      (NUMBER_GENERAL_SIGNAL_FOR_RANG_BUTTON + NUMBER_MTZ_SIGNAL_FOR_RANG_BUTTON + NUMBER_ZDZ_SIGNAL_FOR_RANG_BUTTON + NUMBER_ZZ_SIGNAL_FOR_RANG_BUTTON + NUMBER_APV_SIGNAL_FOR_RANG_BUTTON + NUMBER_APV_ZMN_SIGNAL_FOR_RANG_BUTTON - 1)
                                                     },
                                                     {-1,-1},
                                                     {-1,-1},
                                                     {-1,-1},
                                                     {-1,-1},
                                                     {-1,-1},
                                                     {
                                                      (NUMBER_GENERAL_SIGNAL_FOR_RANG_BUTTON + NUMBER_MTZ_SIGNAL_FOR_RANG_BUTTON + NUMBER_ZDZ_SIGNAL_FOR_RANG_BUTTON + NUMBER_ZZ_SIGNAL_FOR_RANG_BUTTON + NUMBER_APV_SIGNAL_FOR_RANG_BUTTON + NUMBER_APV_ZMN_SIGNAL_FOR_RANG_BUTTON + NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_BUTTON  + NUMBER_UROV_SIGNAL_FOR_RANG_BUTTON + NUMBER_ZOP_SIGNAL_FOR_RANG_BUTTON + NUMBER_UMIN_SIGNAL_FOR_RANG_BUTTON + NUMBER_UMAX_SIGNAL_FOR_RANG_BUTTON),
                                                      (NUMBER_GENERAL_SIGNAL_FOR_RANG_BUTTON + NUMBER_MTZ_SIGNAL_FOR_RANG_BUTTON + NUMBER_ZDZ_SIGNAL_FOR_RANG_BUTTON + NUMBER_ZZ_SIGNAL_FOR_RANG_BUTTON + NUMBER_APV_SIGNAL_FOR_RANG_BUTTON + NUMBER_APV_ZMN_SIGNAL_FOR_RANG_BUTTON + NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_BUTTON  + NUMBER_UROV_SIGNAL_FOR_RANG_BUTTON + NUMBER_ZOP_SIGNAL_FOR_RANG_BUTTON + NUMBER_UMIN_SIGNAL_FOR_RANG_BUTTON + NUMBER_UMAX_SIGNAL_FOR_RANG_BUTTON + NUMBER_AVR_SIGNAL_FOR_RANG_BUTTON - 1)
                                                     },
                                                     {-1,-1},
                                                     {-1,-1}
                                                    };
      
    /*************************************************************/
    //Գ������� �������, ���� � ���� ������������ ���������
    /*************************************************************/
    //������� ���������� ����������� ���������� (���� ����������� � ������� ������), ���� �������� � ������� �������
    int index_in_list = NUMBER_GENERAL_SIGNAL_FOR_RANG_BUTTON;
    
    for (i = 0; i < TOTAL_NUMBER_PROTECTION; i++)
    {
      
      if((current_settings.configuration & (1 << i)) != 0)
      {
        /*
        ������ �����������, ���� ������� ����������� �� ������� - ���������� ������ �� ������� �������
        ������ ������� ������� �� ��������� �������, ���� ��� ��������� ������� ������� ���� ������� �������,
        �� ������ �� ��� ����������� �� ������ ���������� �������
        */
        if(min_max_number[i][0] >=0)
        {
          index_in_list += ((min_max_number[i][1] - min_max_number[i][0]) + 1);
        }
      }
      else if (min_max_number[i][0] >=0)
      {
        //³������� ����� ������� � ������ ��� ����� ����� � ���� �������, ���� ������� ������ � ������ ��� ���������� ��� ������ �������
        //������� ����� ��, �� �� ����� ��������� ��� ��������� ���� ����
        unsigned int maska = 0;
        for (unsigned int j = 0; j < (min_max_number[i][0] - offset); j++) maska = (maska << 1) + 0x1;
          
        //³������� ����� ������� �� ������, �� � �������
        while(index_in_list <= min_max_number[i][1])
        {
          unsigned int new_temp_data_1, new_temp_data_2;
          //������ ��� ����� ����������� ������� ����� �� �� �������
          new_temp_data_1 = temp_data & maska;
          new_temp_data_2 = temp_data & (~maska);
          new_temp_data_2 = new_temp_data_2 >>1;
          new_temp_data_2 &= (~maska);
          temp_data = new_temp_data_1 | new_temp_data_2;

          for (unsigned int j = (index_in_list - offset); j < MAX_ROW_RANGUVANNJA_INPUT; j++)
          {
            if ((j + 1) < MAX_ROW_RANGUVANNJA_BUTTON)
            {
              for (unsigned int k = 0; k<MAX_COL_LCD; k++)
                name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION][k] = name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION + 1][k];
            }
            else 
            {
              for (unsigned int k = 0; k<MAX_COL_LCD; k++)
                name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION][k] = ' ';
            }
          }
          if (current_ekran.index_position >= index_in_list) position_temp--;
          
          offset++;
          index_in_list++;
        }
      }
    }
    /*************************************************************/

    //�������� �� ��� �������� position_temp ������� ��� ����, �� �� ���� ������� �� ������������� ��� ����� (����� + ��������)
    index_of_ekran = ((position_temp<<1) >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;

    for (i=0; i< MAX_ROW_LCD; i++)
    {
     if (index_of_ekran < (MAX_ROW_RANGUVANNJA_BUTTON<<1))//�������� �� ��� ���������  MAX_ROW_RANGUVANNJA_BUTTON ������� ��� ����, �� �� ���� ������� �� ������������� ��� ����� (����� + ��������)
     {
       if ((i & 0x1) == 0)
       {
         //� ��������� ����� ����� �������� ���������
         for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string_tmp[(index_of_ekran>>1) + NUMBER_ROW_FOR_NOTHING_INFORMATION][j];
       }
       else
       {
         //� ������� ����� ����� �������� ��������
         const unsigned char information[MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD] = 
         {
           {"      ����      ", "      ���       "},
           {"      ����      ", "     �²��      "},
           {"      OFF       ", "       ON       "},
           {"      ъ��      ", "      ����      "}
        };
        unsigned int maska = 1 << (index_of_ekran >> 1);
          
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = information[index_language][((temp_data & maska) != 0)][j];
       }
     }
     else
      for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';

     index_of_ekran++;
    }

    const unsigned int cursor_x[MAX_NAMBER_LANGUAGE][2] = 
    {
      {5, 5},
      {5, 4},
      {5, 6},
      {5, 5}
    };

    //³���������� ������ �� �������� � ������ ������ �� ���� � ��� �� ��������� ������
    current_ekran.position_cursor_x =  cursor_x[index_language][((temp_data & (1 << position_temp)) != 0)];
    current_ekran.position_cursor_y = ((position_temp<<1) + 1) & (MAX_ROW_LCD - 1);
    
    //������ ����
    current_ekran.cursor_blinking_on = 1;
    //����� ����������� � ����� �����������
  }
  

  //�������� ������� ���� �����
  current_ekran.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;

#undef NUMBER_ROW_FOR_NOTHING_INFORMATION
}
/*****************************************************/

/*****************************************************/
//������� ����� ����������� ����������� ������� �� �������� ����
/*****************************************************/
void make_ekran_set_function_in_input(unsigned int number_ekran)
{
#define NUMBER_ROW_FOR_NOTHING_INFORMATION 2
  
  const unsigned char name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_RANGUVANNJA_INPUT + NUMBER_ROW_FOR_NOTHING_INFORMATION][MAX_COL_LCD] = 
  {
    {
      "      ���       ",
      "  ������������  ",
      " ��.�-�������1  ",
      " ��.�-�������2  ",
      " ��.�-�������3  ",
      " ��.�-�������4  ",
      " ��.�-�������5  ",
      " ��.�-�������6  ",
      " ��.�-�������7  ",
      " ��.�-�������8  ",
      " ���.�-��������1",
      " ���.�-��������1",
      " ���.�-��������2",
      " ���.�-��������2",
      " ���.�-��������3",
      " ���.�-��������3",
      " ���.�-��������4",
      " ���.�-��������4",
      " ��.��.���.����.",
      " ���.�����.����.",
      " ��������� ���. ",
      "  ����.���.��   ",
      " ����� ���������",
      "   ����� ����   ",
      " �����./�������.",
      "  ��������� ��  ",
      "����.�� ��.�����",
      "     ���.��     ",
      " �������� ���.  ",
      "    ����.��     ",
      " �������� ����. ",
      " 1-� ��.������� ",
      " 2-� ��.������� ",
      " 3-� ��.������� ",
      " 4-� ��.������� ",
      " �.���.���.� �� ",
      "   ����.���1    ",
      "   ����.���2    ",
      " ����.���.���2  ",
      "   ����.���3    ",
      "   ����.���4    ",
      " ���� ��� �� �� ",
      "    ����.���    ",
      " ����.����.���  ",
      " �.���.���-���  ",
      "  ����.���-���  ",
      "    ����.���    ",
      " ���/���� �� �� ",
      " ���� ���� �� ��",
      " ����.���(���)  ",
      "  ����.�����1   ",
      "  ���� �����1   ",
      "  ����.�����2   ",
      "  ���� �����2   ",
      "  ����.������1  ",
      "  ����.������2  ",
      "  ��.����.���   ",
      " ����� ����.��� ",
      " ����.����.���  "
    },
    {
      "      ����      ",
      "   ����������   ",
      " ��.�-�������1  ",
      " ��.�-�������2  ",
      " ��.�-�������3  ",
      " ��.�-�������4  ",
      " ��.�-�������5  ",
      " ��.�-�������6  ",
      " ��.�-�������7  ",
      " ��.�-�������8  ",
      " ���.�-������1 ",
      " ��.�-������1  ",
      " ���.�-������2 ",
      " ��.�-������2  ",
      " ���.�-������3 ",
      " ��.�-������3  ",
      " ���.�-������4 ",
      " ��.�-������4  ",
      " ��.�.���.����.",
      " ��.�����.����. ",
      " �������� ����. ",
      " ����.�����.�� ",
      " ����.��������� ",
      "   ����.����    ",
      " ̳��./�������. ",
      "    ���� ��     ",
      "����.�� ����.�.",
      "    ����.��    ",
      " �������� ����.",
      "    ����.��     ",
      " �������� ����. ",
      " 1-� ��.������� ",
      " 2-� ��.������� ",
      " 3-� ��.������� ",
      " 4-� ��.������� ",
      " �.���.���.�� ��",
      "   ����.���1    ",
      "   ����.���2    ",
      " ����.�����.���2",
      "   ����.���3    ",
      "   ����.���4    ",
      " ���� ��� �� ��",
      "    ����.���    ",
      " ����.����.���  ",
      " �.���.���-���  ",
      "  ����.���-���  ",
      "    ����.���    ",
      " ���/���� �� ��",
      "���� ���� �� ��",
      " ����.���(���)  ",
      "  ����.�����1   ",
      "  ���� �����1   ",
      "  ����.�����2   ",
      "  ���� �����2   ",
      "  ����.������1  ",
      "  ����.������2  ",
      " ����.����.���  ",
      " ����.����.���  ",
      " ����.����.���  "
    },
    {
      "       No       ",
      "    ranking     ",
      "    UDF1 In     ",
      "    UDF2 In     ",
      "    UDF3 In     ",
      "    UDF4 In     ",
      "    UDF5 In     ",
      "    UDF6 In     ",
      "    UDF7 In     ",
      "    UDF8 In     ",
      "UD Flip-Flop1 S.",
      "UD Flip-Flop1 R.",
      "UD Flip-Flop2 S.",
      "UD Flip-Flop2 R.",
      "UD Flip-Flop3 S.",
      "UD Flip-Flop3 R.",
      "UD Flip-Flop4 S.",
      "UD Flip-Flop4 R.",
      " ��.��.���.����.",
      " ���.�����.����.",
      " ��������� ���. ",
      " ON CB Blocking ",
      "Indication Reset",
      "  Relay Reset   ",
      "  Local/Remote  ",
      "  State of CB   ",
      "����.�� ��.�����",
      "     On CB      ",
      " On CB Control  ",
      "     Off CB     ",
      " Off CB Control ",
      " Pick-up Set 1  ",
      " Pick-up Set 2  ",
      " Pick-up Set 3  ",
      " Pick-up Set 4  ",
      " �.���.���.� �� ",
      "  Blc.of OCP1   ",
      "  Blc.of OCP2   ",
      "  OCP2 Acc.Blc. ",
      "  Blc.of OCP3   ",
      "  Blc.of OCP4   ",
      " ���� ��� �� �� ",
      "    ����.���    ",
      " ����.����.���  ",
      " �.���.���-���  ",
      "  ����.���-���  ",
      "    ����.���    ",
      " ���/���� �� �� ",
      " CBFP Start f.DI",
      "  Blc.of NPSP   ",
      "   ����.Umin1   ",
      "   ���� Umin1   ",
      "   ����.Umin2   ",
      "   ���� Umin2   ",
      "   ����.Umax1   ",
      "   ����.Umax2   ",
      "  ��.����.���   ",
      " ����� ����.��� ",
      " ����.����.���  "
    },
    {
      "      ���       ",
      "  ������������  ",
      " ��.�-�������1  ",
      " ��.�-�������2  ",
      " ��.�-�������3  ",
      " ��.�-�������4  ",
      " ��.�-�������5  ",
      " ��.�-�������6  ",
      " ��.�-�������7  ",
      " ��.�-�������8  ",
      " ���.�-��������1",
      " ���.�-��������1",
      " ���.�-��������2",
      " ���.�-��������2",
      " ���.�-��������3",
      " ���.�-��������3",
      " ���.�-��������4",
      " ���.�-��������4",
      " ��.��.���.����.",
      " ���.�����.����.",
      " ��������� ���. ",
      "  ����.���.��   ",
      " ����� ���������",
      "   ����� ����   ",
      " �����./�������.",
      "  ��������� ��  ",
      "����.�� ��.�����",
      "     ���.��     ",
      " �������� ���.  ",
      "    ����.��     ",
      " �������� ����. ",
      " 1-� ��.������� ",
      " 2-� ��.������� ",
      " 3-� ��.������� ",
      " 4-� ��.������� ",
      " �.���.���.� �� ",
      "   ����.���1    ",
      "   ����.���2    ",
      " ����.���.���2  ",
      "   ����.���3    ",
      "   ����.���4    ",
      " ���� ��� �� �� ",
      "    ����.���    ",
      " ����.����.���  ",
      " �.���.���-���  ",
      "  ����.���-���  ",
      "    ����.���    ",
      " ���/���� �� �� ",
      " ���� ���� �� ��",
      " ����.���(���)  ",
      "  ����.�����1   ",
      "  ���� �����1   ",
      "  ����.�����2   ",
      "  ���� �����2   ",
      "  ����.������1  ",
      "  ����.������2  ",
      "  ��.����.���   ",
      " ����� ����.��� ",
      " ����.����.���  "
    }
  };
  unsigned char name_string_tmp[MAX_ROW_RANGUVANNJA_INPUT + NUMBER_ROW_FOR_NOTHING_INFORMATION][MAX_COL_LCD];

  int index_language = index_language_in_array(current_settings.language);
  for(int index_1 = 0; index_1 < (MAX_ROW_RANGUVANNJA_INPUT + NUMBER_ROW_FOR_NOTHING_INFORMATION); index_1++)
  {
    for(int index_2 = 0; index_2 < MAX_COL_LCD; index_2++)
      name_string_tmp[index_1][index_2] = name_string[index_language][index_1][index_2];
  }
  
  if (
      ((current_settings.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_3U0_Ubc_TN2) != 0) ||
      ((current_settings.control_zz & CTR_ZZ1_TYPE) != 0)
     )   
  {
    const unsigned char name_block_zz[MAX_NAMBER_LANGUAGE][MAX_COL_LCD] = 
    {
      "    ����.��     ",
      "    ����.��     ",
      "    ����.��     ",
      "    ����.��     "
    };
    for (unsigned int index_1 = 0; index_1 < MAX_COL_LCD; index_1++)
    {
      name_string_tmp[RANG_INPUT_BLOCK_NZZ + NUMBER_ROW_FOR_NOTHING_INFORMATION][index_1] = name_block_zz[index_language][index_1];
    }
  }
  
  if(current_ekran.edition == 0)
  {
    //�������, ���� �� ������������� ��������� ������� �� ����
    unsigned int state_viewing_input[N_SMALL];
    
    state_viewing_input[0] = current_settings.ranguvannja_inputs[N_SMALL*(number_ekran - EKRAN_RANGUVANNJA_INPUT_1)    ];
    state_viewing_input[1] = current_settings.ranguvannja_inputs[N_SMALL*(number_ekran - EKRAN_RANGUVANNJA_INPUT_1) + 1];
    
    if (
        (state_viewing_input[0] == 0) &&
        (state_viewing_input[1] == 0)
       )
    {
      //�� ������, �� �� ����� ���� ����� �� �����������
      
      //������ ������� � ������ ���������� �� ��� �������
      current_ekran.index_position = 0;
      position_in_current_level_menu[number_ekran] = 0;

      //�������  ����� � ������� �����
      for (unsigned int i=0; i< MAX_ROW_LCD; i++)
      {
        //������� � ������� ����� ����������, �� ����� �� �����������
        if (i < NUMBER_ROW_FOR_NOTHING_INFORMATION)
          for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string_tmp[i][j];
        else
          for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';
      }

      //³���������� ������ �� ��������
      current_ekran.position_cursor_y = 0;
      //������ ���������
      current_ekran.cursor_on = 0;
    }
    else
    {
      /************************************************************/
      //������� ������ �� �������, �� ������� ����������
      /************************************************************/
      unsigned int position_temp = current_ekran.index_position;
      unsigned int index_of_ekran;
      unsigned int i = 0, offset = 0;
      unsigned int state_current_bit;

      while ((i + offset) < MAX_ROW_RANGUVANNJA_INPUT)
      {
        state_current_bit = state_viewing_input[(i + offset)>>5] & (1<<((i + offset) & 0x1f));

        if (state_current_bit == 0)
        {
          for (unsigned int j = i; j < (MAX_ROW_RANGUVANNJA_INPUT - offset); j++)
          {
            if ((j + 1) < (MAX_ROW_RANGUVANNJA_INPUT - offset))
            {
              for (unsigned int k = 0; k<MAX_COL_LCD; k++)
                name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION][k] = name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION + 1][k];
            }
            else 
            {
              for (unsigned int k = 0; k<MAX_COL_LCD; k++)
                name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION][k] = ' ';
            }
          }
          if (current_ekran.index_position >= ((int)(i + offset))) position_temp--;
          offset++;
        }
        else i++;
      }
      /************************************************************/

      index_of_ekran = (position_temp >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;
      
      //�������  ����� � ������� �����
      for (i=0; i< MAX_ROW_LCD; i++)
      {
        //������� ����� ����� ���������, �� �� ����� ���������� � ������� ������������
        if (index_of_ekran < MAX_ROW_RANGUVANNJA_INPUT)
        {
          for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string_tmp[index_of_ekran + NUMBER_ROW_FOR_NOTHING_INFORMATION][j];

          //ϳ������� �����, ��� �� ���� ������ ������ ������
          unsigned int iteration = 0;
          while (
                 (working_ekran[i][0] == ' ') &&
                 (working_ekran[i][1] == ' ') &&
                 (iteration < (MAX_COL_LCD - 1 - 1))
                )
          {
            for (unsigned int j = 1; j < MAX_COL_LCD; j++)
            {
              if ((j + 1) < MAX_COL_LCD)
                working_ekran[i][j] = working_ekran[i][j + 1];
              else
                working_ekran[i][j] = ' ';
            }
            iteration++;
          }
        }
        else
          for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';

        index_of_ekran++;
      }
      //³���������� ������ �� ��������
      current_ekran.position_cursor_y = position_temp & (MAX_ROW_LCD - 1);
      //������ �������
      current_ekran.cursor_on = 1;
    }
    
    //������ �� ���������� ������������ �� ������ �������
    current_ekran.position_cursor_x = 0;
    //������ �� ����
    current_ekran.cursor_blinking_on = 0;
  }
  else
  {
    unsigned int temp_data[N_SMALL];
    temp_data[0] = edition_settings.ranguvannja_inputs[N_SMALL*(current_ekran.current_level - EKRAN_RANGUVANNJA_INPUT_1)    ];
    temp_data[1] = edition_settings.ranguvannja_inputs[N_SMALL*(current_ekran.current_level - EKRAN_RANGUVANNJA_INPUT_1) + 1];
    
    unsigned int position_temp = current_ekran.index_position;
    unsigned int index_of_ekran;
    unsigned int i, offset = 0;
    int min_max_number[TOTAL_NUMBER_PROTECTION][2] =
    {
      {
       (NUMBER_GENERAL_SIGNAL_FOR_RANG_INPUT),
       (NUMBER_GENERAL_SIGNAL_FOR_RANG_INPUT + NUMBER_MTZ_SIGNAL_FOR_RANG_INPUT - 1)
      },
      {
       (NUMBER_GENERAL_SIGNAL_FOR_RANG_INPUT + NUMBER_MTZ_SIGNAL_FOR_RANG_INPUT),
       (NUMBER_GENERAL_SIGNAL_FOR_RANG_INPUT + NUMBER_MTZ_SIGNAL_FOR_RANG_INPUT + NUMBER_ZDZ_SIGNAL_FOR_RANG_INPUT - 1)
      },
      {
       (NUMBER_GENERAL_SIGNAL_FOR_RANG_INPUT + NUMBER_MTZ_SIGNAL_FOR_RANG_INPUT + NUMBER_ZDZ_SIGNAL_FOR_RANG_INPUT),
       (NUMBER_GENERAL_SIGNAL_FOR_RANG_INPUT + NUMBER_MTZ_SIGNAL_FOR_RANG_INPUT + NUMBER_ZDZ_SIGNAL_FOR_RANG_INPUT + NUMBER_ZZ_SIGNAL_FOR_RANG_INPUT - 1)
      },
      {
       (NUMBER_GENERAL_SIGNAL_FOR_RANG_INPUT + NUMBER_MTZ_SIGNAL_FOR_RANG_INPUT + NUMBER_ZDZ_SIGNAL_FOR_RANG_INPUT + NUMBER_ZZ_SIGNAL_FOR_RANG_INPUT),
       (NUMBER_GENERAL_SIGNAL_FOR_RANG_INPUT + NUMBER_MTZ_SIGNAL_FOR_RANG_INPUT + NUMBER_ZDZ_SIGNAL_FOR_RANG_INPUT + NUMBER_ZZ_SIGNAL_FOR_RANG_INPUT + NUMBER_APV_SIGNAL_FOR_RANG_INPUT - 1)
      },
      {
       (NUMBER_GENERAL_SIGNAL_FOR_RANG_INPUT + NUMBER_MTZ_SIGNAL_FOR_RANG_INPUT + NUMBER_ZDZ_SIGNAL_FOR_RANG_INPUT + NUMBER_ZZ_SIGNAL_FOR_RANG_INPUT + NUMBER_APV_SIGNAL_FOR_RANG_INPUT),
       (NUMBER_GENERAL_SIGNAL_FOR_RANG_INPUT + NUMBER_MTZ_SIGNAL_FOR_RANG_INPUT + NUMBER_ZDZ_SIGNAL_FOR_RANG_INPUT + NUMBER_ZZ_SIGNAL_FOR_RANG_INPUT + NUMBER_APV_SIGNAL_FOR_RANG_INPUT + NUMBER_APV_ZMN_SIGNAL_FOR_RANG_INPUT - 1)
      },
      {
       (NUMBER_GENERAL_SIGNAL_FOR_RANG_INPUT + NUMBER_MTZ_SIGNAL_FOR_RANG_INPUT + NUMBER_ZDZ_SIGNAL_FOR_RANG_INPUT + NUMBER_ZZ_SIGNAL_FOR_RANG_INPUT + NUMBER_APV_SIGNAL_FOR_RANG_INPUT + NUMBER_APV_ZMN_SIGNAL_FOR_RANG_INPUT),
       (NUMBER_GENERAL_SIGNAL_FOR_RANG_INPUT + NUMBER_MTZ_SIGNAL_FOR_RANG_INPUT + NUMBER_ZDZ_SIGNAL_FOR_RANG_INPUT + NUMBER_ZZ_SIGNAL_FOR_RANG_INPUT + NUMBER_APV_SIGNAL_FOR_RANG_INPUT + NUMBER_APV_ZMN_SIGNAL_FOR_RANG_INPUT + NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_INPUT - 1)
      },
      {
       (NUMBER_GENERAL_SIGNAL_FOR_RANG_INPUT + NUMBER_MTZ_SIGNAL_FOR_RANG_INPUT + NUMBER_ZDZ_SIGNAL_FOR_RANG_INPUT + NUMBER_ZZ_SIGNAL_FOR_RANG_INPUT + NUMBER_APV_SIGNAL_FOR_RANG_INPUT + NUMBER_APV_ZMN_SIGNAL_FOR_RANG_INPUT + NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_INPUT),
       (NUMBER_GENERAL_SIGNAL_FOR_RANG_INPUT + NUMBER_MTZ_SIGNAL_FOR_RANG_INPUT + NUMBER_ZDZ_SIGNAL_FOR_RANG_INPUT + NUMBER_ZZ_SIGNAL_FOR_RANG_INPUT + NUMBER_APV_SIGNAL_FOR_RANG_INPUT + NUMBER_APV_ZMN_SIGNAL_FOR_RANG_INPUT + NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_INPUT + NUMBER_UROV_SIGNAL_FOR_RANG_INPUT - 1)
      },
      {
       (NUMBER_GENERAL_SIGNAL_FOR_RANG_INPUT + NUMBER_MTZ_SIGNAL_FOR_RANG_INPUT + NUMBER_ZDZ_SIGNAL_FOR_RANG_INPUT + NUMBER_ZZ_SIGNAL_FOR_RANG_INPUT + NUMBER_APV_SIGNAL_FOR_RANG_INPUT + NUMBER_APV_ZMN_SIGNAL_FOR_RANG_INPUT + NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_INPUT + NUMBER_UROV_SIGNAL_FOR_RANG_INPUT),
       (NUMBER_GENERAL_SIGNAL_FOR_RANG_INPUT + NUMBER_MTZ_SIGNAL_FOR_RANG_INPUT + NUMBER_ZDZ_SIGNAL_FOR_RANG_INPUT + NUMBER_ZZ_SIGNAL_FOR_RANG_INPUT + NUMBER_APV_SIGNAL_FOR_RANG_INPUT + NUMBER_APV_ZMN_SIGNAL_FOR_RANG_INPUT + NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_INPUT + NUMBER_UROV_SIGNAL_FOR_RANG_INPUT + NUMBER_ZOP_SIGNAL_FOR_RANG_INPUT - 1)
      },
      {
       (NUMBER_GENERAL_SIGNAL_FOR_RANG_INPUT + NUMBER_MTZ_SIGNAL_FOR_RANG_INPUT + NUMBER_ZDZ_SIGNAL_FOR_RANG_INPUT + NUMBER_ZZ_SIGNAL_FOR_RANG_INPUT + NUMBER_APV_SIGNAL_FOR_RANG_INPUT + NUMBER_APV_ZMN_SIGNAL_FOR_RANG_INPUT + NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_INPUT + NUMBER_UROV_SIGNAL_FOR_RANG_INPUT + NUMBER_ZOP_SIGNAL_FOR_RANG_INPUT),
       (NUMBER_GENERAL_SIGNAL_FOR_RANG_INPUT + NUMBER_MTZ_SIGNAL_FOR_RANG_INPUT + NUMBER_ZDZ_SIGNAL_FOR_RANG_INPUT + NUMBER_ZZ_SIGNAL_FOR_RANG_INPUT + NUMBER_APV_SIGNAL_FOR_RANG_INPUT + NUMBER_APV_ZMN_SIGNAL_FOR_RANG_INPUT + NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_INPUT + NUMBER_UROV_SIGNAL_FOR_RANG_INPUT + NUMBER_ZOP_SIGNAL_FOR_RANG_INPUT + NUMBER_UMIN_SIGNAL_FOR_RANG_INPUT - 1)
      },
      {
       (NUMBER_GENERAL_SIGNAL_FOR_RANG_INPUT + NUMBER_MTZ_SIGNAL_FOR_RANG_INPUT + NUMBER_ZDZ_SIGNAL_FOR_RANG_INPUT + NUMBER_ZZ_SIGNAL_FOR_RANG_INPUT + NUMBER_APV_SIGNAL_FOR_RANG_INPUT + NUMBER_APV_ZMN_SIGNAL_FOR_RANG_INPUT + NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_INPUT + NUMBER_UROV_SIGNAL_FOR_RANG_INPUT + NUMBER_ZOP_SIGNAL_FOR_RANG_INPUT + NUMBER_UMIN_SIGNAL_FOR_RANG_INPUT),
       (NUMBER_GENERAL_SIGNAL_FOR_RANG_INPUT + NUMBER_MTZ_SIGNAL_FOR_RANG_INPUT + NUMBER_ZDZ_SIGNAL_FOR_RANG_INPUT + NUMBER_ZZ_SIGNAL_FOR_RANG_INPUT + NUMBER_APV_SIGNAL_FOR_RANG_INPUT + NUMBER_APV_ZMN_SIGNAL_FOR_RANG_INPUT + NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_INPUT + NUMBER_UROV_SIGNAL_FOR_RANG_INPUT + NUMBER_ZOP_SIGNAL_FOR_RANG_INPUT + NUMBER_UMIN_SIGNAL_FOR_RANG_INPUT + NUMBER_UMAX_SIGNAL_FOR_RANG_INPUT - 1)
      },
      {
       (NUMBER_GENERAL_SIGNAL_FOR_RANG_INPUT + NUMBER_MTZ_SIGNAL_FOR_RANG_INPUT + NUMBER_ZDZ_SIGNAL_FOR_RANG_INPUT + NUMBER_ZZ_SIGNAL_FOR_RANG_INPUT + NUMBER_APV_SIGNAL_FOR_RANG_INPUT + NUMBER_APV_ZMN_SIGNAL_FOR_RANG_INPUT + NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_INPUT + NUMBER_UROV_SIGNAL_FOR_RANG_INPUT + NUMBER_ZOP_SIGNAL_FOR_RANG_INPUT + NUMBER_UMIN_SIGNAL_FOR_RANG_INPUT + NUMBER_UMAX_SIGNAL_FOR_RANG_INPUT),
       (NUMBER_GENERAL_SIGNAL_FOR_RANG_INPUT + NUMBER_MTZ_SIGNAL_FOR_RANG_INPUT + NUMBER_ZDZ_SIGNAL_FOR_RANG_INPUT + NUMBER_ZZ_SIGNAL_FOR_RANG_INPUT + NUMBER_APV_SIGNAL_FOR_RANG_INPUT + NUMBER_APV_ZMN_SIGNAL_FOR_RANG_INPUT + NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_INPUT + NUMBER_UROV_SIGNAL_FOR_RANG_INPUT + NUMBER_ZOP_SIGNAL_FOR_RANG_INPUT + NUMBER_UMIN_SIGNAL_FOR_RANG_INPUT + NUMBER_UMAX_SIGNAL_FOR_RANG_INPUT + NUMBER_AVR_SIGNAL_FOR_RANG_INPUT - 1)
      },
      {-1,-1},
      {-1,-1}
     };
    
    /*************************************************************/
    //Գ������� �������, ���� � ���� ������������ ���������
    /*************************************************************/
    //������� ���������� ����������� ���������� (���� ����������� � ������� ������), ���� �������� � ������� �������
    int index_in_list = NUMBER_GENERAL_SIGNAL_FOR_RANG_INPUT;
    
    for (i = 0; i < TOTAL_NUMBER_PROTECTION; i++)
    {
      
      if((current_settings.configuration & (1 << i)) != 0)
      {
        //������ �����������, ���� ������� ����������� �� ������� - ���������� ������ �� ������� �������
        //������ �������� ������� �� ��������� �������, ���� ��� ��������� ������� ������� ���� ������� �������,
        //�� ������ �� ��� ����������� �� ������ ���������� �������
        if(min_max_number[i][0] >=0)
        {
          index_in_list += ((min_max_number[i][1] - min_max_number[i][0]) + 1);
        }
      }
      else if (min_max_number[i][0] >=0)
      {
        //³������� ����� ������� � ������ ��� ����� ����� � ���� �������, ���� ������� ������ � ������ ��� ���������� ��� ������ �������
        //������� ����� ��, �� �� ����� ��������� ��� ��������� ���� ����
        unsigned int maska[N_SMALL] = {0, 0};
        for (unsigned int j = 0; j < (min_max_number[i][0] - offset); j++) _SET_BIT(maska, j);
          
        //³������� ����� ������� �� ������, �� � �������
        while(index_in_list <= min_max_number[i][1])
        {
          /***/
          //������ ��� ����� ����������� ������� ����� �� �� �������
          /***/
          unsigned int new_temp_data_1[N_SMALL], new_temp_data_2[N_SMALL];

          new_temp_data_1[0] = temp_data[0] & maska[0];
          new_temp_data_1[1] = temp_data[1] & maska[1];

          new_temp_data_2[0] = temp_data[0] & (~maska[0]);
          new_temp_data_2[1] = temp_data[1] & (~maska[1]);

          new_temp_data_2[0] = (new_temp_data_2[0] >>1) | ((new_temp_data_2[1] & 0x1) << 31);
          new_temp_data_2[1] =  new_temp_data_2[1] >>1;

          new_temp_data_2[0] &= (~maska[0]);
          new_temp_data_2[1] &= (~maska[1]);

          temp_data[0] = new_temp_data_1[0] | new_temp_data_2[0];
          temp_data[1] = new_temp_data_1[1] | new_temp_data_2[1];
          /***/
          for (unsigned int j = (index_in_list - offset); j < MAX_ROW_RANGUVANNJA_INPUT; j++)
          {
            if ((j + 1) < MAX_ROW_RANGUVANNJA_INPUT)
            {
              for (unsigned int k = 0; k<MAX_COL_LCD; k++)
                name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION][k] = name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION + 1][k];
            }
            else 
            {
              for (unsigned int k = 0; k<MAX_COL_LCD; k++)
                name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION][k] = ' ';
            }
          }
          if (current_ekran.index_position >= index_in_list) position_temp--;
          
          offset++;
          index_in_list++;
        }
      }
    }
    /*************************************************************/
      
    //�������� �� ��� �������� position_temp ������� ��� ����, �� �� ���� ������� �� ������������� ��� ����� (����� + ��������)
    index_of_ekran = ((position_temp<<1) >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;

    for (i=0; i< MAX_ROW_LCD; i++)
    {
     if (index_of_ekran < (MAX_ROW_RANGUVANNJA_INPUT<<1))//�������� �� ��� ���������  MAX_ROW_RANGUVANNJA_INPUT ������� ��� ����, �� �� ���� ������� �� ������������� ��� ����� (����� + ��������)
     {
       if ((i & 0x1) == 0)
       {
         //� ��������� ����� ����� �������� ���������
         for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string_tmp[(index_of_ekran>>1) + NUMBER_ROW_FOR_NOTHING_INFORMATION][j];
       }
       else
       {
         //� ������� ����� ����� �������� ���� �������
         const unsigned char information[MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD] = 
         {
           {"      ����      ", "      ���       "},
           {"      ����      ", "     �²��      "},
           {"      OFF       ", "       ON       "},
           {"      ъ��      ", "      ����      "}
        };
        unsigned int index_bit = index_of_ekran >> 1;
          
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = information[index_language][((temp_data[index_bit >> 5] & ( 1<< (index_bit & 0x1f))) != 0)][j];
       }
     }
     else
      for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';

     index_of_ekran++;
    }
    
    const unsigned int cursor_x[MAX_NAMBER_LANGUAGE][2] = 
    {
      {5, 5},
      {5, 4},
      {5, 6},
      {5, 5}
    };

    //³���������� ������ �� �������� � ������ ������ �� ���� � ��� �� ���������
    current_ekran.position_cursor_x =  cursor_x[index_language][((temp_data[position_temp >> 5] & (1 << (position_temp & 0x1f))) != 0)];
    current_ekran.position_cursor_y = ((position_temp<<1) + 1) & (MAX_ROW_LCD - 1);
    
    //������ ����
    current_ekran.cursor_blinking_on = 1;
    //����� ����������� � ����� �����������
  }

  //�������� ������� ���� �����
  current_ekran.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;

#undef NUMBER_ROW_FOR_NOTHING_INFORMATION
}
/*****************************************************/

/*****************************************************/
//������� ����� ����������� ����������� ������� �� �������� �����-��������������-�-�������-����������
/*****************************************************/
void make_ekran_set_function_in_output_led_df_dt_reg(unsigned int number_ekran, unsigned int type_ekran)
{
#define NUMBER_ROW_FOR_NOTHING_INFORMATION 2
  
  unsigned int state_viewing_input[N_BIG];
  unsigned int max_row_ranguvannja;
  const unsigned char name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_RANGUVANNJA_OUTPUT + NUMBER_ROW_FOR_NOTHING_INFORMATION][MAX_COL_LCD] = 
  {
    {
      "      ���       ",
      "  ������������  ",
      " ��.�-�������1  ",
      " ���.�-�������1 ",
      " ��.�-�������2  ",
      " ���.�-�������2 ",
      " ��.�-�������3  ",
      " ���.�-�������3 ",
      " ��.�-�������4  ",
      " ���.�-�������4 ",
      " ��.�-�������5  ",
      " ���.�-�������5 ",
      " ��.�-�������6  ",
      " ���.�-�������6 ",
      " ��.�-�������7  ",
      " ���.�-�������7 ",
      " ��.�-�������8  ",
      " ���.�-�������8 ",
      " ���.�-��������1",
      " ���.�-��������1",
      " ���.�-��������1",
      " ���.�-��������2",
      " ���.�-��������2",
      " ���.�-��������2",
      " ���.�-��������3",
      " ���.�-��������3",
      " ���.�-��������3",
      " ���.�-��������4",
      " ���.�-��������4",
      " ���.�-��������4",
      " ��.��.���.����.",
      " ���.�����.����.",
      " ��������� ���. ",
      "  ����.���.��   ",
      " ����� ���������",
      "   ����� ����   ",
      " �����./�������.",
      "  ��������� ��  ",
      "����.�� ��.�����",
      "     ���.��     ",
      " �������� ���.  ",
      "    ����.��     ",
      " �������� ����. ",
      "   ������ ��    ",
      " ����.I��.���.  ",
      " ����.������ �� ",
      " ���.������ ��  ",
      "  ������.�����  ",
      "  ������.����.  ",
      " ������ ��.���. ",
      " ������ �.���.  ",
      " ����.�� �����  ",
      "   ������ ��    ",
      "   ������ ��    ",
      " 1-� ��.������� ",
      " 2-� ��.������� ",
      " 3-� ��.������� ",
      " 4-� ��.������� ",
      " ���.�� ��.���. ",
      "���.��.���.�� �.",
      " �.���.���.� �� ",
      " ���������� � ��",
      "   ����.���1    ",
      "   ����.���2    ",
      " ����.���.���2  ",
      "   ����.���3    ",
      "   ����.���4    ",
      " ����.����1 ��. ",
      " ����.����1 ���.",
      "    �� ���1     ",
      " �� ����1 �����",
      " �� ����1 ����� ",
      "  �� U �����1   ",
      "   �� �����1    ",
      "      ���1      ",
      " ����.����2 ��. ",
      " ����.����2 ���.",
      "    �� ���2     ",
      " �� ����2 �����",
      " �� ����2 ����� ",
      "  �� U �����2   ",
      "   �� �����2    ",
      "      ���2      ",
      " ����.����3 ��. ",
      " ����.����3 ���.",
      "    �� ���3     ",
      " �� ����3 �����",
      " �� ����3 ����� ",
      "  �� U �����3   ",
      "   �� �����3    ",
      "      ���3      ",
      " ����.����4 ��. ",
      " ����.����4 ���.",
      "    �� ���4     ",
      " �� ����4 �����",
      " �� ����4 ����� ",
      "  �� U �����4   ",
      "   �� �����4    ",
      "      ���4      ",
      " �� ����.U ���� ",
      "    ���-���     ",
      " ���� ��� �� �� ",
      "      ���       ",
      "    ����.���    ",
      "     �� ���     ",
      "      ���       ",
      "   �� ��(3I0)   ",
      "    ��(3I0)     ",
      "   �� ��(3U0)   ",
      "    ��(3U0)     ",
      "   ������ ���   ",
      " ����.����.���  ",
      "      ���       ",
      "      ���2      ",
      "      ���3      ",
      "      ���4      ",
      "   ������ ���   ",
      " �.���.���-���  ",
      "  ����.���-���  ",
      " ����.��.���-���",
      "��.���-��� �� �.",
      " �� U ���-��� 1 ",
      " �� U ���-��� 2 ",
      "   �� ���-���   ",
      "    ���-���     ",
      "    ����.���    ",
      "   ����.����    ",
      " ����.���� �� U ",
      "    �� ��� 1    ",
      "   ���/���� 1   ",
      "    �� ��� 2    ",
      "   ���/���� 2   ",
      "    ���/����    ",
      "   �� ���� 1    ",
      "   �� ���� 2    ",
      " ���/���� �� �� ",
      " ���� ���� �� ��",
      "    �� ����     ",
      "     ����1      ",
      "     ����2      ",
      " ����.���(���)  ",
      "  �� ���(���)   ",
      "    ���(���)    ",
      "  ����.�����1   ",
      "  ���� �����1   ",
      "  ����.�����2   ",
      "  ���� �����2   ",
      "   �� �����1    ",
      " �� U���.�����1 ",
      " �� I���.�����1 ",
      "     �����1     ",
      "     �� �����2  ",
      " �� U���.�����2 ",
      " �� I���.�����2 ",
      "     �����2     ",
      "  ����.������1  ",
      "   �� ������1   ",
      "    ������1     ",
      "  ����.������2  ",
      "   �� ������2   ",
      "    ������2     ",
      "  ��.����.���   ",
      " ����� ����.��� ",
      " ����.����.���  ",
      " ��.��� �� �����",
      " �� U ��� ���.1 ",
      " �� U ��� ����.1",
      " �� U ��� ���.2 ",
      " �� U ��� ����.2",
      "  ����.��.���   ",
      "    ���� ���    ",
      "   ���� ��� 1   ",
      "   ���� ��� 2   ",
      "    �� U ��     ",
      "      U ��      ",
      "    �� U ��     ",
      "      U ��      "
    },
    {
      "      ����      ",
      "   ����������   ",
      " ��.�-�������1  ",
      " ���.�-�������1 ",
      " ��.�-�������2  ",
      " ���.�-�������2 ",
      " ��.�-�������3  ",
      " ���.�-�������3 ",
      " ��.�-�������4  ",
      " ���.�-�������4 ",
      " ��.�-�������5  ",
      " ���.�-�������5 ",
      " ��.�-�������6  ",
      " ���.�-�������6 ",
      " ��.�-�������7  ",
      " ���.�-�������7 ",
      " ��.�-�������8  ",
      " ���.�-�������8 ",
      " ���.�-������1 ",
      " ��.�-������1  ",
      " ���.�-������1 ",
      " ���.�-������2 ",
      " ��.�-������2  ",
      " ���.�-������2 ",
      " ���.�-������3 ",
      " ��.�-������3  ",
      " ���.�-������3 ",
      " ���.�-������4 ",
      " ��.�-������4  ",
      " ���.�-������4 ",
      " ��.�.���.����.",
      " ��.�����.����. ",
      " �������� ����. ",
      " ����.�����.�� ",
      " ����.��������� ",
      "   ����.����    ",
      " ̳��./�������. ",
      "    ���� ��     ",
      "����.�� ����.�.",
      "    ����.��    ",
      " �������� ����.",
      "    ����.��     ",
      " �������� ����. ",
      "   ����� ��    ",
      " �����.I�.���.  ",
      " ����.������ �� ",
      " ���.������ ��  ",
      " �����.�������� ",
      "  �����.����.   ",
      " ���.��.�����. ",
      " ���.�.�����.  ",
      " ����.�� ���.  ",
      " ������ �����.  ",
      " ������ �����. ",
      " 1-� ��.������� ",
      " 2-� ��.������� ",
      " 3-� ��.������� ",
      " 4-� ��.������� ",
      " ���.�� ��.���. ",
      "��.��.���.�� �.",
      " �.���.���.�� ��",
      "��������� �� ��",
      "   ����.���1    ",
      "   ����.���2    ",
      " ����.�����.���2",
      "   ����.���3    ",
      "   ����.���4    ",
      " ����.����1 ��. ",
      " ����.����1 ���.",
      "    �� ���1     ",
      " �� ����1 ������",
      " �� ����1 ����� ",
      "  �� U �����1   ",
      "   �� �����1    ",
      "      ���1      ",
      " ����.����2 ��. ",
      " ����.����2 ���.",
      "    �� ���2     ",
      " �� ����2 ������",
      " �� ����2 ����� ",
      "  �� U �����2   ",
      "   �� �����2    ",
      "      ���2      ",
      " ����.����3 ��. ",
      " ����.����3 ���.",
      "    �� ���3     ",
      " �� ����3 ������",
      " �� ����3 ����� ",
      "  �� U �����3   ",
      "   �� �����3    ",
      "      ���3      ",
      " ����.����4 ��. ",
      " ����.����4 ���.",
      "    �� ���4     ",
      " �� ����4 ������",
      " �� ����4 ����� ",
      "  �� U �����4   ",
      "   �� �����4    ",
      "      ���4      ",
      " �� ����.U ���� ",
      "    ���-���     ",
      " ���� ��� �� ��",
      "      ���       ",
      "    ����.���    ",
      "     �� ���     ",
      "      ���       ",
      "   �� ��(3I0)   ",
      "    ��(3I0)     ",
      "   �� ��(3U0)   ",
      "    ��(3U0)     ",
      "   ������ ���   ",
      " ����.����.���  ",
      "      ���       ",
      "      ���2      ",
      "      ���3      ",
      "      ���4      ",
      "   ������ ���   ",
      " �.���.���-���  ",
      "  ����.���-���  ",
      " ����.��.���-���",
      "��.���-��� �� �",
      " �� U ���-��� 1 ",
      " �� U ���-��� 2 ",
      "   �� ���-���   ",
      "    ���-���     ",
      "    ����.���    ",
      "  ����� ����   ",
      " ����.���� �� U",
      "    �� ��� 1    ",
      "   ���/���� 1   ",
      "    �� ��� 2    ",
      "   ���/���� 2   ",
      "    ���/����    ",
      "   �� ���� 1    ",
      "   �� ���� 2    ",
      " ���/���� �� ��",
      "���� ���� �� ��",
      "    �� ����     ",
      "     ����1      ",
      "     ����2      ",
      " ����.���(���)  ",
      "  �� ���(���)   ",
      "    ���(���)    ",
      "  ����.����1   ",
      "  ���� ����1   ",
      "  ����.����2   ",
      "  ���� ����2   ",
      "   �� ����1    ",
      " �� U���.����1 ",
      " �� I���.����1 ",
      "     ����1     ",
      "     �� ����2  ",
      " �� U���.����2 ",
      " �� I���.����2 ",
      "     ����2     ",
      "  ����.������1  ",
      "   �� ������1   ",
      "    ������1     ",
      "  ����.������2  ",
      "   �� ������2   ",
      "    ������2     ",
      " ����.����.���  ",
      " ����.����.���  ",
      " ����.����.���  ",
      " ��.��� �� ���.",
      " �� U ��� ��.1 ",
      " �� U ��� ����.1",
      " �� U ��� ��.2 ",
      " �� U ��� ����.2",
      "  ����.��.���   ",
      "    ���� ���    ",
      "   ���� ��� 1   ",
      "   ���� ��� 2   ",
      "    �� U ��     ",
      "      U ��      ",
      "    �� U ��     ",
      "      U ��      "
    },
    {
      "       No       ",
      "    ranking     ",
      "    UDF1 In     ",
      "    UDF1 Out    ",
      "    UDF2 In     ",
      "    UDF2 Out    ",
      "    UDF3 In     ",
      "    UDF3 Out    ",
      "    UDF4 In     ",
      "    UDF4 Out    ",
      "    UDF5 In     ",
      "    UDF5 Out    ",
      "    UDF6 In     ",
      "    UDF6 Out    ",
      "    UDF7 In     ",
      "    UDF7 Out    ",
      "    UDF8 In     ",
      "    UDF8 Out    ",
      "UD Flip-Flop1 S.",
      "UD Flip-Flop1 R.",
      "UD Flip-Flop1 O.",
      "UD Flip-Flop2 S.",
      "UD Flip-Flop2 R.",
      "UD Flip-Flop2 O.",
      "UD Flip-Flop3 S.",
      "UD Flip-Flop3 R.",
      "UD Flip-Flop3 O.",
      "UD Flip-Flop4 S.",
      "UD Flip-Flop4 R.",
      "UD Flip-Flop4 O.",
      " ��.��.���.����.",
      " ���.�����.����.",
      " ��������� ���. ",
      " ON CB Blocking ",
      "Indication Reset",
      "  Relay Reset   ",
      "  Local/Remote  ",
      "  State of CB   ",
      "����.�� ��.�����",
      "     On CB      ",
      " On CB Control  ",
      "     Off CB     ",
      " Off CB Control ",
      "  CB Actuator   ",
      " ����.I��.���.  ",
      " ����.������ �� ",
      " ���.������ ��  ",
      "  Total Fault   ",
      " Emergence Fault",
      "An.Rec.Operation",
      " D.Rec.Operation",
      " ����.�� �����  ",
      "Off CB Operation",
      " On CB Operation",
      " Pick-up Set 1  ",
      " Pick-up Set 2  ",
      " Pick-up Set 3  ",
      " Pick-up Set 4  ",
      " ���.�� ��.���. ",
      "���.��.���.�� �.",
      " �.���.���.� �� ",
      " ���������� � ��",
      "  Blc.of OCP1   ",
      "  Blc.of OCP2   ",
      "  OCP2 Acc.Blc. ",
      "  Blc.of OCP3   ",
      "  Blc.of OCP4   ",
      " ����.����1 ��. ",
      " ����.����1 ���.",
      "    OCP1 SE     ",
      " �� ����1 �����",
      " �� ����1 ����� ",
      "  �� U �����1   ",
      "   �� �����1    ",
      "      OCP1      ",
      " ����.����2 ��. ",
      " ����.����2 ���.",
      "    OCP2 SE     ",
      " �� ����2 �����",
      " �� ����2 ����� ",
      "  �� U �����2   ",
      "   �� �����2    ",
      "      OCP2      ",
      " ����.����3 ��. ",
      " ����.����3 ���.",
      "    OCP3 SE     ",
      " �� ����3 �����",
      " �� ����3 ����� ",
      "  �� U �����3   ",
      "   �� �����3    ",
      "      OCP3      ",
      " ����.����4 ��. ",
      " ����.����4 ���.",
      "    OCP4 SE     ",
      " �� ����4 �����",
      " �� ����4 ����� ",
      "  �� U �����4   ",
      "   �� �����4    ",
      "      OCP4      ",
      " �� ����.U ���� ",
      "    ���-���     ",
      " ���� ��� �� �� ",
      "      ���       ",
      "    ����.���    ",
      "     �� ���     ",
      "      ���       ",
      "  SGFP(3Io) SE  ",
      "   SGFP(3Io)    ",
      "   �� ��(3U0)   ",
      "    ��(3U0)     ",
      "   ������ ���   ",
      "Static Blc.of AR",
      "       AR       ",
      "      AR2       ",
      "      AR3       ",
      "      AR4       ",
      "   ������ ���   ",
      " �.���.���-���  ",
      "  ����.���-���  ",
      " ����.��.���-���",
      "��.���-��� �� �.",
      " �� U ���-��� 1 ",
      " �� U ���-��� 2 ",
      "   �� ���-���   ",
      "    ���-���     ",
      "    ����.���    ",
      "   ����.����    ",
      " ����.���� �� U ",
      "    �� ��� 1    ",
      "   UFLS/FAR 1   ",
      "    �� ��� 2    ",
      "   UFLS/FAR 2   ",
      "    UFLS/FAR    ",
      "   �� ���� 1    ",
      "   �� ���� 2    ",
      " ���/���� �� �� ",
      " CBFP Start f.DI",
      "    CBFP SE     ",
      "     CBFP1      ",
      "     CBFP2      ",
      "  Blc.of NPSP   ",
      "    NPSP SE     ",
      "      NPSP      ",
      "   ����.Umin1   ",
      "   ���� Umin1   ",
      "   ����.Umin2   ",
      "   ���� Umin2   ",
      "    �� Umin1    ",
      " �� U���.Umin1  ",
      " �� I���.Umin1  ",
      "     Umin1      ",
      "    �� Umin2    ",
      " �� U���.Umin2  ",
      " �� I���.Umin2  ",
      "     Umin2      ",
      "   ����.Umax1   ",
      "    �� Umax1    ",
      "     Umax1      ",
      "   ����.Umax2   ",
      "    �� Umax2    ",
      "     Umax2      ",
      "  ��.����.���   ",
      " ����� ����.��� ",
      " ����.����.���  ",
      " ��.��� �� �����",
      " �� U ��� ���.1 ",
      " �� U ��� ����.1",
      " �� U ��� ���.2 ",
      " �� U ��� ����.2",
      "  ����.��.���   ",
      "    ���� ���    ",
      "   ���� ��� 1   ",
      "   ���� ��� 2   ",
      "    �� U ��     ",
      "      U ��      ",
      "    �� U ��     ",
      "      U ��      "
    },
    {
      "      ���       ",
      "  ������������  ",
      " ��.�-�������1  ",
      " ���.�-�������1 ",
      " ��.�-�������2  ",
      " ���.�-�������2 ",
      " ��.�-�������3  ",
      " ���.�-�������3 ",
      " ��.�-�������4  ",
      " ���.�-�������4 ",
      " ��.�-�������5  ",
      " ���.�-�������5 ",
      " ��.�-�������6  ",
      " ���.�-�������6 ",
      " ��.�-�������7  ",
      " ���.�-�������7 ",
      " ��.�-�������8  ",
      " ���.�-�������8 ",
      " ���.�-��������1",
      " ���.�-��������1",
      " ���.�-��������1",
      " ���.�-��������2",
      " ���.�-��������2",
      " ���.�-��������2",
      " ���.�-��������3",
      " ���.�-��������3",
      " ���.�-��������3",
      " ���.�-��������4",
      " ���.�-��������4",
      " ���.�-��������4",
      " ��.��.���.����.",
      " ���.�����.����.",
      " ��������� ���. ",
      "  ����.���.��   ",
      " ����� ���������",
      "   ����� ����   ",
      " �����./�������.",
      "  ��������� ��  ",
      "����.�� ��.�����",
      "     ���.��     ",
      " �������� ���.  ",
      "    ����.��     ",
      " �������� ����. ",
      "   ������ ��    ",
      " ����.I��.���.  ",
      " ����.������ �� ",
      " ���.������ ��  ",
      "  ������.�����  ",
      "  ������.����.  ",
      " ������ ��.���. ",
      " ������ �.���.  ",
      " ����.�� �����  ",
      "   ������ ��    ",
      "   ������ ��    ",
      " 1-� ��.������� ",
      " 2-� ��.������� ",
      " 3-� ��.������� ",
      " 4-� ��.������� ",
      " ���.�� ��.���. ",
      "���.��.���.�� �.",
      " �.���.���.� �� ",
      " ���������� � ��",
      "   ����.���1    ",
      "   ����.���2    ",
      " ����.���.���2  ",
      "   ����.���3    ",
      "   ����.���4    ",
      " ����.����1 ��. ",
      " ����.����1 ���.",
      "    �� ���1     ",
      " �� ����1 �����",
      " �� ����1 ����� ",
      "  �� U �����1   ",
      "   �� �����1    ",
      "      ���1      ",
      " ����.����2 ��. ",
      " ����.����2 ���.",
      "    �� ���2     ",
      " �� ����2 �����",
      " �� ����2 ����� ",
      "  �� U �����2   ",
      "   �� �����2    ",
      "      ���2      ",
      " ����.����3 ��. ",
      " ����.����3 ���.",
      "    �� ���3     ",
      " �� ����3 �����",
      " �� ����3 ����� ",
      "  �� U �����3   ",
      "   �� �����3    ",
      "      ���3      ",
      " ����.����4 ��. ",
      " ����.����4 ���.",
      "    �� ���4     ",
      " �� ����4 �����",
      " �� ����4 ����� ",
      "  �� U �����4   ",
      "   �� �����4    ",
      "      ���4      ",
      " �� ����.U ���� ",
      "    ���-���     ",
      " ���� ��� �� �� ",
      "      ���       ",
      "    ����.���    ",
      "     �� ���     ",
      "      ���       ",
      "   �� ��(3I0)   ",
      "    ��(3I0)     ",
      "   �� ��(3U0)   ",
      "    ��(3U0)     ",
      "   ������ ���   ",
      " ����.����.���  ",
      "      ���       ",
      "      ���2      ",
      "      ���3      ",
      "      ���4      ",
      "   ������ ���   ",
      " �.���.���-���  ",
      "  ����.���-���  ",
      " ����.��.���-���",
      "��.���-��� �� �.",
      " �� U ���-��� 1 ",
      " �� U ���-��� 2 ",
      "   �� ���-���   ",
      "    ���-���     ",
      "    ����.���    ",
      "   ����.����    ",
      " ����.���� �� U ",
      "    �� ��� 1    ",
      "   ���/���� 1   ",
      "    �� ��� 2    ",
      "   ���/���� 2   ",
      "    ���/����    ",
      "   �� ���� 1    ",
      "   �� ���� 2    ",
      " ���/���� �� �� ",
      " ���� ���� �� ��",
      "    �� ����     ",
      "     ����1      ",
      "     ����2      ",
      " ����.���(���)  ",
      "  �� ���(���)   ",
      "    ���(���)    ",
      "  ����.�����1   ",
      "  ���� �����1   ",
      "  ����.�����2   ",
      "  ���� �����2   ",
      "   �� �����1    ",
      " �� U���.�����1 ",
      " �� I���.�����1 ",
      "     �����1     ",
      "     �� �����2  ",
      " �� U���.�����2 ",
      " �� I���.�����2 ",
      "     �����2     ",
      "  ����.������1  ",
      "   �� ������1   ",
      "    ������1     ",
      "  ����.������2  ",
      "   �� ������2   ",
      "    ������2     ",
      "  ��.����.���   ",
      " ����� ����.��� ",
      " ����.����.���  ",
      " ��.��� �� �����",
      " �� U ��� ���.1 ",
      " �� U ��� ����.1",
      " �� U ��� ���.2 ",
      " �� U ��� ����.2",
      "  ����.��.���   ",
      "    ���� ���    ",
      "   ���� ��� 1   ",
      "   ���� ��� 2   ",
      "    �� U ��     ",
      "      U ��      ",
      "    �� U ��     ",
      "      U ��      "
    }
  };
  unsigned char name_string_tmp[MAX_ROW_RANGUVANNJA_OUTPUT + NUMBER_ROW_FOR_NOTHING_INFORMATION][MAX_COL_LCD];

  int index_language = index_language_in_array(current_settings.language);
  for(int index_1 = 0; index_1 < (MAX_ROW_RANGUVANNJA_OUTPUT + NUMBER_ROW_FOR_NOTHING_INFORMATION); index_1++)
  {
    for(int index_2 = 0; index_2 < MAX_COL_LCD; index_2++)
      name_string_tmp[index_1][index_2] = name_string[index_language][index_1][index_2];
  }
  
  if (
      ((current_settings.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_3U0_Ubc_TN2) != 0) ||
      ((current_settings.control_zz & CTR_ZZ1_TYPE) != 0)
     )   
  {
    const unsigned char name_block_zz[MAX_NAMBER_LANGUAGE][MAX_COL_LCD] = 
    {
      "    ����.��     ",
      "    ����.��     ",
      "    ����.��     ",
      "    ����.��     "
    };
    for (unsigned int index_1 = 0; index_1 < MAX_COL_LCD; index_1++)
    {
      name_string_tmp[RANG_OUTPUT_LED_DF_REG_BLOCK_NZZ + NUMBER_ROW_FOR_NOTHING_INFORMATION][index_1] = name_block_zz[index_language][index_1];
    }
  }

  if(type_ekran == INDEX_VIEWING_DF)
  {
    unsigned int index_in_ekran_list = number_ekran - EKRAN_RANGUVANNJA_DF1_PLUS;
    unsigned int type_source = index_in_ekran_list % 3;
    unsigned int index_of_df = index_in_ekran_list / 3;
    
    if(current_ekran.edition == 0)
    {
      if(type_source == 0)
      {
        state_viewing_input[0] = current_settings.ranguvannja_df_source_plus[N_BIG*index_of_df  ];
        state_viewing_input[1] = current_settings.ranguvannja_df_source_plus[N_BIG*index_of_df+1];
        state_viewing_input[2] = current_settings.ranguvannja_df_source_plus[N_BIG*index_of_df+2];
        state_viewing_input[3] = current_settings.ranguvannja_df_source_plus[N_BIG*index_of_df+3];
        state_viewing_input[4] = current_settings.ranguvannja_df_source_plus[N_BIG*index_of_df+4];
        state_viewing_input[5] = current_settings.ranguvannja_df_source_plus[N_BIG*index_of_df+5];
      }
      else if(type_source == 1)
      {
        state_viewing_input[0] = current_settings.ranguvannja_df_source_minus[N_BIG*index_of_df  ];
        state_viewing_input[1] = current_settings.ranguvannja_df_source_minus[N_BIG*index_of_df+1];
        state_viewing_input[2] = current_settings.ranguvannja_df_source_minus[N_BIG*index_of_df+2];
        state_viewing_input[3] = current_settings.ranguvannja_df_source_minus[N_BIG*index_of_df+3];
        state_viewing_input[4] = current_settings.ranguvannja_df_source_minus[N_BIG*index_of_df+4];
        state_viewing_input[5] = current_settings.ranguvannja_df_source_minus[N_BIG*index_of_df+5];
      }
      else
      {
        state_viewing_input[0] = current_settings.ranguvannja_df_source_blk[N_BIG*index_of_df  ];
        state_viewing_input[1] = current_settings.ranguvannja_df_source_blk[N_BIG*index_of_df+1];
        state_viewing_input[2] = current_settings.ranguvannja_df_source_blk[N_BIG*index_of_df+2];
        state_viewing_input[3] = current_settings.ranguvannja_df_source_blk[N_BIG*index_of_df+3];
        state_viewing_input[4] = current_settings.ranguvannja_df_source_blk[N_BIG*index_of_df+4];
        state_viewing_input[5] = current_settings.ranguvannja_df_source_blk[N_BIG*index_of_df+5];
      }
    }
    else
    {
      if(type_source == 0)
      {
        state_viewing_input[0] = edition_settings.ranguvannja_df_source_plus[N_BIG*index_of_df  ];
        state_viewing_input[1] = edition_settings.ranguvannja_df_source_plus[N_BIG*index_of_df+1];
        state_viewing_input[2] = edition_settings.ranguvannja_df_source_plus[N_BIG*index_of_df+2];
        state_viewing_input[3] = edition_settings.ranguvannja_df_source_plus[N_BIG*index_of_df+3];
        state_viewing_input[4] = edition_settings.ranguvannja_df_source_plus[N_BIG*index_of_df+4];
        state_viewing_input[5] = edition_settings.ranguvannja_df_source_plus[N_BIG*index_of_df+5];
      }
      else if(type_source == 1)
      {
        state_viewing_input[0] = edition_settings.ranguvannja_df_source_minus[N_BIG*index_of_df  ];
        state_viewing_input[1] = edition_settings.ranguvannja_df_source_minus[N_BIG*index_of_df+1];
        state_viewing_input[2] = edition_settings.ranguvannja_df_source_minus[N_BIG*index_of_df+2];
        state_viewing_input[3] = edition_settings.ranguvannja_df_source_minus[N_BIG*index_of_df+3];
        state_viewing_input[4] = edition_settings.ranguvannja_df_source_minus[N_BIG*index_of_df+4];
        state_viewing_input[5] = edition_settings.ranguvannja_df_source_minus[N_BIG*index_of_df+5];
      }
      else
      {
        state_viewing_input[0] = edition_settings.ranguvannja_df_source_blk[N_BIG*index_of_df  ];
        state_viewing_input[1] = edition_settings.ranguvannja_df_source_blk[N_BIG*index_of_df+1];
        state_viewing_input[2] = edition_settings.ranguvannja_df_source_blk[N_BIG*index_of_df+2];
        state_viewing_input[3] = edition_settings.ranguvannja_df_source_blk[N_BIG*index_of_df+3];
        state_viewing_input[4] = edition_settings.ranguvannja_df_source_blk[N_BIG*index_of_df+4];
        state_viewing_input[5] = edition_settings.ranguvannja_df_source_blk[N_BIG*index_of_df+5];
      }
    }
    max_row_ranguvannja = MAX_ROW_RANGUVANNJA_DF;
  }
  else if(type_ekran == INDEX_VIEWING_DT)
  {
    unsigned int index_in_ekran_list = number_ekran - EKRAN_RANGUVANNJA_SET_DT1_PLUS;
    unsigned int type_source = index_in_ekran_list % 2;
    unsigned int type_of_action = (index_in_ekran_list / 2) & 0x1;
    unsigned int index_of_dt = index_in_ekran_list / 4;
    
    if(current_ekran.edition == 0)
    {
      if (type_of_action == INDEX_ML_SET_DT)
      {
        if(type_source == INDEX_ML_LIST_TYPE_SOURCE_PLUS_DT)
        {
          state_viewing_input[0] = current_settings.ranguvannja_set_dt_source_plus[N_BIG*index_of_dt  ];
          state_viewing_input[1] = current_settings.ranguvannja_set_dt_source_plus[N_BIG*index_of_dt+1];
          state_viewing_input[2] = current_settings.ranguvannja_set_dt_source_plus[N_BIG*index_of_dt+2];
          state_viewing_input[3] = current_settings.ranguvannja_set_dt_source_plus[N_BIG*index_of_dt+3];
          state_viewing_input[4] = current_settings.ranguvannja_set_dt_source_plus[N_BIG*index_of_dt+4];
          state_viewing_input[5] = current_settings.ranguvannja_set_dt_source_plus[N_BIG*index_of_dt+5];
        }
        else
        {
          state_viewing_input[0] = current_settings.ranguvannja_set_dt_source_minus[N_BIG*index_of_dt  ];
          state_viewing_input[1] = current_settings.ranguvannja_set_dt_source_minus[N_BIG*index_of_dt+1];
          state_viewing_input[2] = current_settings.ranguvannja_set_dt_source_minus[N_BIG*index_of_dt+2];
          state_viewing_input[3] = current_settings.ranguvannja_set_dt_source_minus[N_BIG*index_of_dt+3];
          state_viewing_input[4] = current_settings.ranguvannja_set_dt_source_minus[N_BIG*index_of_dt+4];
          state_viewing_input[5] = current_settings.ranguvannja_set_dt_source_minus[N_BIG*index_of_dt+5];
        }
      }
      else
      {
        if(type_source == INDEX_ML_LIST_TYPE_SOURCE_PLUS_DT)
        {
          state_viewing_input[0] = current_settings.ranguvannja_reset_dt_source_plus[N_BIG*index_of_dt  ];
          state_viewing_input[1] = current_settings.ranguvannja_reset_dt_source_plus[N_BIG*index_of_dt+1];
          state_viewing_input[2] = current_settings.ranguvannja_reset_dt_source_plus[N_BIG*index_of_dt+2];
          state_viewing_input[3] = current_settings.ranguvannja_reset_dt_source_plus[N_BIG*index_of_dt+3];
          state_viewing_input[4] = current_settings.ranguvannja_reset_dt_source_plus[N_BIG*index_of_dt+4];
          state_viewing_input[5] = current_settings.ranguvannja_reset_dt_source_plus[N_BIG*index_of_dt+5];
        }
        else
        {
          state_viewing_input[0] = current_settings.ranguvannja_reset_dt_source_minus[N_BIG*index_of_dt  ];
          state_viewing_input[1] = current_settings.ranguvannja_reset_dt_source_minus[N_BIG*index_of_dt+1];
          state_viewing_input[2] = current_settings.ranguvannja_reset_dt_source_minus[N_BIG*index_of_dt+2];
          state_viewing_input[3] = current_settings.ranguvannja_reset_dt_source_minus[N_BIG*index_of_dt+3];
          state_viewing_input[4] = current_settings.ranguvannja_reset_dt_source_minus[N_BIG*index_of_dt+4];
          state_viewing_input[5] = current_settings.ranguvannja_reset_dt_source_minus[N_BIG*index_of_dt+5];
        }
      }
    }
    else
    {
      if (type_of_action == INDEX_ML_SET_DT)
      {
        if(type_source == INDEX_ML_LIST_TYPE_SOURCE_PLUS_DT)
        {
          state_viewing_input[0] = edition_settings.ranguvannja_set_dt_source_plus[N_BIG*index_of_dt  ];
          state_viewing_input[1] = edition_settings.ranguvannja_set_dt_source_plus[N_BIG*index_of_dt+1];
          state_viewing_input[2] = edition_settings.ranguvannja_set_dt_source_plus[N_BIG*index_of_dt+2];
          state_viewing_input[3] = edition_settings.ranguvannja_set_dt_source_plus[N_BIG*index_of_dt+3];
          state_viewing_input[4] = edition_settings.ranguvannja_set_dt_source_plus[N_BIG*index_of_dt+4];
          state_viewing_input[5] = edition_settings.ranguvannja_set_dt_source_plus[N_BIG*index_of_dt+5];
        }
        else
        { 
          state_viewing_input[0] = edition_settings.ranguvannja_set_dt_source_minus[N_BIG*index_of_dt  ];
          state_viewing_input[1] = edition_settings.ranguvannja_set_dt_source_minus[N_BIG*index_of_dt+1];
          state_viewing_input[2] = edition_settings.ranguvannja_set_dt_source_minus[N_BIG*index_of_dt+2];
          state_viewing_input[3] = edition_settings.ranguvannja_set_dt_source_minus[N_BIG*index_of_dt+3];
          state_viewing_input[4] = edition_settings.ranguvannja_set_dt_source_minus[N_BIG*index_of_dt+4];
          state_viewing_input[5] = edition_settings.ranguvannja_set_dt_source_minus[N_BIG*index_of_dt+5];
        }
      }
      else
      {
        if(type_source == INDEX_ML_LIST_TYPE_SOURCE_PLUS_DT)
        {
          state_viewing_input[0] = edition_settings.ranguvannja_reset_dt_source_plus[N_BIG*index_of_dt  ];
          state_viewing_input[1] = edition_settings.ranguvannja_reset_dt_source_plus[N_BIG*index_of_dt+1];
          state_viewing_input[2] = edition_settings.ranguvannja_reset_dt_source_plus[N_BIG*index_of_dt+2];
          state_viewing_input[3] = edition_settings.ranguvannja_reset_dt_source_plus[N_BIG*index_of_dt+3];
          state_viewing_input[4] = edition_settings.ranguvannja_reset_dt_source_plus[N_BIG*index_of_dt+4];
          state_viewing_input[5] = edition_settings.ranguvannja_reset_dt_source_plus[N_BIG*index_of_dt+5];
        }
        else
        { 
          state_viewing_input[0] = edition_settings.ranguvannja_reset_dt_source_minus[N_BIG*index_of_dt  ];
          state_viewing_input[1] = edition_settings.ranguvannja_reset_dt_source_minus[N_BIG*index_of_dt+1];
          state_viewing_input[2] = edition_settings.ranguvannja_reset_dt_source_minus[N_BIG*index_of_dt+2];
          state_viewing_input[3] = edition_settings.ranguvannja_reset_dt_source_minus[N_BIG*index_of_dt+3];
          state_viewing_input[4] = edition_settings.ranguvannja_reset_dt_source_minus[N_BIG*index_of_dt+4];
          state_viewing_input[5] = edition_settings.ranguvannja_reset_dt_source_minus[N_BIG*index_of_dt+5];
        }
      }
    }
    max_row_ranguvannja = MAX_ROW_RANGUVANNJA_DT;
  }
  else if(type_ekran == INDEX_VIEWING_OUTPUT)
  {
    if(current_ekran.edition == 0)
    {
      state_viewing_input[0] = current_settings.ranguvannja_outputs[N_BIG*(number_ekran - EKRAN_RANGUVANNJA_OUTPUT_1)  ];
      state_viewing_input[1] = current_settings.ranguvannja_outputs[N_BIG*(number_ekran - EKRAN_RANGUVANNJA_OUTPUT_1)+1];
      state_viewing_input[2] = current_settings.ranguvannja_outputs[N_BIG*(number_ekran - EKRAN_RANGUVANNJA_OUTPUT_1)+2];
      state_viewing_input[3] = current_settings.ranguvannja_outputs[N_BIG*(number_ekran - EKRAN_RANGUVANNJA_OUTPUT_1)+3];
      state_viewing_input[4] = current_settings.ranguvannja_outputs[N_BIG*(number_ekran - EKRAN_RANGUVANNJA_OUTPUT_1)+4];
      state_viewing_input[5] = current_settings.ranguvannja_outputs[N_BIG*(number_ekran - EKRAN_RANGUVANNJA_OUTPUT_1)+5];
    }
    else
    {
      state_viewing_input[0] = edition_settings.ranguvannja_outputs[N_BIG*(number_ekran - EKRAN_RANGUVANNJA_OUTPUT_1)  ];
      state_viewing_input[1] = edition_settings.ranguvannja_outputs[N_BIG*(number_ekran - EKRAN_RANGUVANNJA_OUTPUT_1)+1];
      state_viewing_input[2] = edition_settings.ranguvannja_outputs[N_BIG*(number_ekran - EKRAN_RANGUVANNJA_OUTPUT_1)+2];
      state_viewing_input[3] = edition_settings.ranguvannja_outputs[N_BIG*(number_ekran - EKRAN_RANGUVANNJA_OUTPUT_1)+3];
      state_viewing_input[4] = edition_settings.ranguvannja_outputs[N_BIG*(number_ekran - EKRAN_RANGUVANNJA_OUTPUT_1)+4];
      state_viewing_input[5] = edition_settings.ranguvannja_outputs[N_BIG*(number_ekran - EKRAN_RANGUVANNJA_OUTPUT_1)+5];
    }
    max_row_ranguvannja = MAX_ROW_RANGUVANNJA_OUTPUT;
  }
  else if(type_ekran == INDEX_VIEWING_LED)
  {
    if(current_ekran.edition == 0)
    {
      state_viewing_input[0] = current_settings.ranguvannja_leds[N_BIG*(number_ekran - EKRAN_RANGUVANNJA_LED_1)  ];
      state_viewing_input[1] = current_settings.ranguvannja_leds[N_BIG*(number_ekran - EKRAN_RANGUVANNJA_LED_1)+1];
      state_viewing_input[2] = current_settings.ranguvannja_leds[N_BIG*(number_ekran - EKRAN_RANGUVANNJA_LED_1)+2];
      state_viewing_input[3] = current_settings.ranguvannja_leds[N_BIG*(number_ekran - EKRAN_RANGUVANNJA_LED_1)+3];
      state_viewing_input[4] = current_settings.ranguvannja_leds[N_BIG*(number_ekran - EKRAN_RANGUVANNJA_LED_1)+4];
      state_viewing_input[5] = current_settings.ranguvannja_leds[N_BIG*(number_ekran - EKRAN_RANGUVANNJA_LED_1)+5];
    }
    else
    {
      state_viewing_input[0] = edition_settings.ranguvannja_leds[N_BIG*(number_ekran - EKRAN_RANGUVANNJA_LED_1)  ];
      state_viewing_input[1] = edition_settings.ranguvannja_leds[N_BIG*(number_ekran - EKRAN_RANGUVANNJA_LED_1)+1];
      state_viewing_input[2] = edition_settings.ranguvannja_leds[N_BIG*(number_ekran - EKRAN_RANGUVANNJA_LED_1)+2];
      state_viewing_input[3] = edition_settings.ranguvannja_leds[N_BIG*(number_ekran - EKRAN_RANGUVANNJA_LED_1)+3];
      state_viewing_input[4] = edition_settings.ranguvannja_leds[N_BIG*(number_ekran - EKRAN_RANGUVANNJA_LED_1)+4];
      state_viewing_input[5] = edition_settings.ranguvannja_leds[N_BIG*(number_ekran - EKRAN_RANGUVANNJA_LED_1)+5];
    }
    max_row_ranguvannja = MAX_ROW_RANGUVANNJA_LED;
  }
  else if(type_ekran == INDEX_VIEWING_A_REG)
  {
    if(current_ekran.edition == 0)
    {
      state_viewing_input[0] = current_settings.ranguvannja_analog_registrator[0];
      state_viewing_input[1] = current_settings.ranguvannja_analog_registrator[1];
      state_viewing_input[2] = current_settings.ranguvannja_analog_registrator[2];
      state_viewing_input[3] = current_settings.ranguvannja_analog_registrator[3];
      state_viewing_input[4] = current_settings.ranguvannja_analog_registrator[4];
      state_viewing_input[5] = current_settings.ranguvannja_analog_registrator[5];
    }
    else
    {
      state_viewing_input[0] = edition_settings.ranguvannja_analog_registrator[0];
      state_viewing_input[1] = edition_settings.ranguvannja_analog_registrator[1];
      state_viewing_input[2] = edition_settings.ranguvannja_analog_registrator[2];
      state_viewing_input[3] = edition_settings.ranguvannja_analog_registrator[3];
      state_viewing_input[4] = edition_settings.ranguvannja_analog_registrator[4];
      state_viewing_input[5] = edition_settings.ranguvannja_analog_registrator[5];
    }
    max_row_ranguvannja = MAX_ROW_RANGUVANNJA_ANALOG_REGISTRATOR;
  }
  else if(type_ekran == INDEX_VIEWING_D_REG)
  {
    if(current_ekran.edition == 0)
    {
      state_viewing_input[0] = current_settings.ranguvannja_digital_registrator[0];
      state_viewing_input[1] = current_settings.ranguvannja_digital_registrator[1];
      state_viewing_input[2] = current_settings.ranguvannja_digital_registrator[2];
      state_viewing_input[3] = current_settings.ranguvannja_digital_registrator[3];
      state_viewing_input[4] = current_settings.ranguvannja_digital_registrator[4];
      state_viewing_input[5] = current_settings.ranguvannja_digital_registrator[5];
    }
    else
    {
      state_viewing_input[0] = edition_settings.ranguvannja_digital_registrator[0];
      state_viewing_input[1] = edition_settings.ranguvannja_digital_registrator[1];
      state_viewing_input[2] = edition_settings.ranguvannja_digital_registrator[2];
      state_viewing_input[3] = edition_settings.ranguvannja_digital_registrator[3];
      state_viewing_input[4] = edition_settings.ranguvannja_digital_registrator[4];
      state_viewing_input[5] = edition_settings.ranguvannja_digital_registrator[5];
    }
    max_row_ranguvannja = MAX_ROW_RANGUVANNJA_DIGITAL_REGISTRATOR;
  }

  if(current_ekran.edition == 0)
  {
    //�������, ���� �� ������������� ��������� ������� �� ����
    if (
        (state_viewing_input[0] == 0) && 
        (state_viewing_input[1] == 0) &&
        (state_viewing_input[2] == 0) &&
        (state_viewing_input[3] == 0) &&
        (state_viewing_input[4] == 0) &&
        (state_viewing_input[5] == 0)
       )
    {
      //�� ������, �� �� ����� ���� ����� �� �����������
      
      //������ ������� � ������ ���������� �� ��� �������
      current_ekran.index_position = 0;
      position_in_current_level_menu[number_ekran] = 0;

      //�������  ����� � ������� �����
      for (unsigned int i=0; i< MAX_ROW_LCD; i++)
      {
        //������� � ������� ����� ����������, �� ����� �� �����������
        if (i < NUMBER_ROW_FOR_NOTHING_INFORMATION)
          for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string_tmp[i][j];
        else
          for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';
      }

      //³���������� ������� �� ��������
      current_ekran.position_cursor_y = 0;
      //������ ���������
      current_ekran.cursor_on = 0;
    }
    else
    {
      /************************************************************/
      //������� ������ �� �������, �� ������� ����������
      /************************************************************/
      unsigned int position_temp = current_ekran.index_position;
      unsigned int index_of_ekran;
      unsigned int i = 0, offset = 0;
      unsigned int state_current_bit;
      
      while ((i + offset) < max_row_ranguvannja)
      {
        state_current_bit = state_viewing_input[(i + offset)>>5] & (1<<((i + offset) & 0x1f));
          
        if (state_current_bit == 0)
        {
          for (unsigned int j = i; j < (max_row_ranguvannja - offset); j++)
          {
            if ((j + 1) < (max_row_ranguvannja - offset))
            {
              for (unsigned int k = 0; k<MAX_COL_LCD; k++)
                name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION][k] = name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION + 1][k];
            }
            else 
            {
              for (unsigned int k = 0; k<MAX_COL_LCD; k++)
                name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION][k] = ' ';
            }
          }
          if (current_ekran.index_position >= ((int)(i + offset))) position_temp--;
          offset++;
        }
        else i++;
      }
      /************************************************************/

      index_of_ekran = (position_temp >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;
      
      //�������  ����� � ������� �����
      for (i=0; i< MAX_ROW_LCD; i++)
      {
        //������� ����� ����� ���������, �� �� ����� ���������� � ������� �����������
        if (index_of_ekran < max_row_ranguvannja)
        {
          for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string_tmp[index_of_ekran + NUMBER_ROW_FOR_NOTHING_INFORMATION][j];

          //ϳ������� �����, ��� �� ���� ������ ������ ������
          unsigned int iteration = 0;
          while (
                 (working_ekran[i][0] == ' ') &&
                 (working_ekran[i][1] == ' ') &&
                 (iteration < (MAX_COL_LCD - 1 - 1))
                )
          {
            for (unsigned int j = 1; j < MAX_COL_LCD; j++)
            {
              if ((j + 1) < MAX_COL_LCD)
                working_ekran[i][j] = working_ekran[i][j + 1];
              else
                working_ekran[i][j] = ' ';
            }
            iteration++;
          }
        }
        else
          for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';

        index_of_ekran++;
      }
      //³���������� ������ �� ��������
      current_ekran.position_cursor_y = position_temp & (MAX_ROW_LCD - 1);
      //������ �������
      current_ekran.cursor_on = 1;
    }

    //������ �� ���������� ������������ �� ������ �������
    current_ekran.position_cursor_x = 0;
    //������ �� ����
    current_ekran.cursor_blinking_on = 0;
  }
  else
  {
    unsigned int position_temp = current_ekran.index_position;
    unsigned int index_of_ekran;
    unsigned int i, offset = 0;
    int min_max_number[TOTAL_NUMBER_PROTECTION][2] =
    {
      {
       (NUMBER_GENERAL_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG),
       (NUMBER_GENERAL_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_MTZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG - 1)
      },
      {
       (NUMBER_GENERAL_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_MTZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG),
       (NUMBER_GENERAL_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_MTZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_ZDZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG - 1)
      },
      {
       (NUMBER_GENERAL_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_MTZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_ZDZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG),
       (NUMBER_GENERAL_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_MTZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_ZDZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_ZZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG - 1)
      },
      {
       (NUMBER_GENERAL_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_MTZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_ZDZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_ZZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG),
       (NUMBER_GENERAL_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_MTZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_ZDZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_ZZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_APV_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG - 1)
      },
      {
       (NUMBER_GENERAL_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_MTZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_ZDZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_ZZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_APV_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG),
       (NUMBER_GENERAL_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_MTZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_ZDZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_ZZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_APV_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_APV_ZMN_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG - 1)
      },
      {
       (NUMBER_GENERAL_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_MTZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_ZDZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_ZZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_APV_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_APV_ZMN_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG),
       (NUMBER_GENERAL_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_MTZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_ZDZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_ZZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_APV_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_APV_ZMN_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG - 1)
      },
      {
       (NUMBER_GENERAL_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_MTZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_ZDZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_ZZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_APV_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_APV_ZMN_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG),
       (NUMBER_GENERAL_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_MTZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_ZDZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_ZZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_APV_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_APV_ZMN_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG  + NUMBER_UROV_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG - 1)
      },
      {
       (NUMBER_GENERAL_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_MTZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_ZDZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_ZZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_APV_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_APV_ZMN_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG  + NUMBER_UROV_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG),
       (NUMBER_GENERAL_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_MTZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_ZDZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_ZZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_APV_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_APV_ZMN_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG  + NUMBER_UROV_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_ZOP_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG - 1)
      },
      {
       (NUMBER_GENERAL_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_MTZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_ZDZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_ZZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_APV_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_APV_ZMN_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG  + NUMBER_UROV_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_ZOP_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG),
       (NUMBER_GENERAL_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_MTZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_ZDZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_ZZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_APV_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_APV_ZMN_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG  + NUMBER_UROV_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_ZOP_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_UMIN_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG - 1)
      },
      {
       (NUMBER_GENERAL_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_MTZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_ZDZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_ZZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_APV_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_APV_ZMN_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG  + NUMBER_UROV_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_ZOP_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_UMIN_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG),
       (NUMBER_GENERAL_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_MTZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_ZDZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_ZZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_APV_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_APV_ZMN_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG  + NUMBER_UROV_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_ZOP_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_UMIN_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_UMAX_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG - 1)
      },
      {
       (NUMBER_GENERAL_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_MTZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_ZDZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_ZZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_APV_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_APV_ZMN_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG  + NUMBER_UROV_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_ZOP_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_UMIN_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_UMAX_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG),
       (NUMBER_GENERAL_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_MTZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_ZDZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_ZZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_APV_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_APV_ZMN_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG  + NUMBER_UROV_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_ZOP_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_UMIN_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_UMAX_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_AVR_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG - 1)
      },
      {
       (NUMBER_GENERAL_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_MTZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_ZDZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_ZZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_APV_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_APV_ZMN_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG  + NUMBER_UROV_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_ZOP_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_UMIN_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_UMAX_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_AVR_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG),
       (NUMBER_GENERAL_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_MTZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_ZDZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_ZZ_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_APV_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_APV_ZMN_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG  + NUMBER_UROV_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_ZOP_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_UMIN_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_UMAX_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_AVR_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG + NUMBER_CONTROL_U_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG - 1)
      },
      {-1,-1}
    };
    
    /*************************************************************/
    //Գ������� �������, ���� � ���� ������������ ���������
    /*************************************************************/
    //������� ���������� ����������� ���������� (���� ����������� � ������� ������), ���� �������� � ������� �������
    int index_in_list = NUMBER_GENERAL_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG;
    
    for (i = 0; i < TOTAL_NUMBER_PROTECTION; i++)
    {
      
      if((current_settings.configuration & (1 << i)) != 0)
      {
        //������ �����������, ���� ������� ����������� �� ������� - ���������� ������ �� ������� �������
        //������ ������� ������� �� ��������� �������, ���� ��� ��������� ������� ������� ���� ������� �������,
        //�� ������ �� ��� ����������� �� ������ ���������� �������
        if(min_max_number[i][0] >=0)
        {
          if (
              (i == ZZ_BIT_CONFIGURATION) &&
              (
               ((current_settings.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_3U0_Ubc_TN2) != 0) ||
               ((current_settings.control_zz & CTR_ZZ1_TYPE) != 0)
              )   
             )
          {
            /*
            ������� ���� �������, �� ���������� �� 3U0 � ���  ��� ����� �� ��� ����� �������������
            */

            //³������� ����� ������� � ������ ��� ����� ����� � ���� �������, ���� ������� ������ � ������ ��� ���������� ��� ������ �������
            //������� ����� ��, �� �� ����� ��������� ��� ��������� ���� ����
            unsigned int maska[N_BIG] = {0, 0, 0, 0, 0, 0};
            unsigned int j1;
            for (j1 = 0; j1 < (min_max_number[i][0] - offset); j1++) _SET_BIT(maska, j1);
          
            //³������� ����� ������� �� ������, �� � �������
            while(index_in_list <= min_max_number[i][1])
            {
              if (
                  (index_in_list != RANG_OUTPUT_LED_DF_REG_BLOCK_NZZ) &&
                  (index_in_list != RANG_OUTPUT_LED_DF_REG_PO_3I0   ) &&
                  (index_in_list != RANG_OUTPUT_LED_DF_REG_3I0      ) &&
                  (
                   ((current_settings.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_3U0_Ubc_TN2) != 0) ||
                   (
                    (index_in_list != RANG_OUTPUT_LED_DF_REG_PO_3U0   ) &&
                    (index_in_list != RANG_OUTPUT_LED_DF_REG_3U0      )
                   )
                  )
                 )
              {
                /***/
                //������ ��� ����� ����������� ������� ����� �� �� �������
                /***/
                unsigned int new_temp_data_1[N_BIG], new_temp_data_2[N_BIG];

                new_temp_data_1[0] = state_viewing_input[0] & maska[0];
                new_temp_data_1[1] = state_viewing_input[1] & maska[1];
                new_temp_data_1[2] = state_viewing_input[2] & maska[2];
                new_temp_data_1[3] = state_viewing_input[3] & maska[3];
                new_temp_data_1[4] = state_viewing_input[4] & maska[4];
                new_temp_data_1[5] = state_viewing_input[5] & maska[5];

                new_temp_data_2[0] = state_viewing_input[0] & (~maska[0]);
                new_temp_data_2[1] = state_viewing_input[1] & (~maska[1]);
                new_temp_data_2[2] = state_viewing_input[2] & (~maska[2]);
                new_temp_data_2[3] = state_viewing_input[3] & (~maska[3]);
                new_temp_data_2[4] = state_viewing_input[4] & (~maska[4]);
                new_temp_data_2[5] = state_viewing_input[5] & (~maska[5]);

                new_temp_data_2[0] = (new_temp_data_2[0] >>1) | ((new_temp_data_2[1] & 0x1) << 31);
                new_temp_data_2[1] = (new_temp_data_2[1] >>1) | ((new_temp_data_2[2] & 0x1) << 31);
                new_temp_data_2[2] = (new_temp_data_2[2] >>1) | ((new_temp_data_2[3] & 0x1) << 31);
                new_temp_data_2[3] = (new_temp_data_2[3] >>1) | ((new_temp_data_2[4] & 0x1) << 31);
                new_temp_data_2[4] = (new_temp_data_2[4] >>1) | ((new_temp_data_2[5] & 0x1) << 31);
                new_temp_data_2[5] =  new_temp_data_2[5] >>1;

                new_temp_data_2[0] &= (~maska[0]);
                new_temp_data_2[1] &= (~maska[1]);
                new_temp_data_2[2] &= (~maska[2]);
                new_temp_data_2[3] &= (~maska[3]);
                new_temp_data_2[4] &= (~maska[4]);
                new_temp_data_2[5] &= (~maska[5]);

                state_viewing_input[0] = new_temp_data_1[0] | new_temp_data_2[0];
                state_viewing_input[1] = new_temp_data_1[1] | new_temp_data_2[1];
                state_viewing_input[2] = new_temp_data_1[2] | new_temp_data_2[2];
                state_viewing_input[3] = new_temp_data_1[3] | new_temp_data_2[3];
                state_viewing_input[4] = new_temp_data_1[4] | new_temp_data_2[4];
                state_viewing_input[5] = new_temp_data_1[5] | new_temp_data_2[5];
                /***/
                for (unsigned int j = (index_in_list - offset); j < max_row_ranguvannja; j++)
                {
                  if ((j + 1) < max_row_ranguvannja)
                  {
                    for (unsigned int k = 0; k<MAX_COL_LCD; k++)
                      name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION][k] = name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION + 1][k];
                  }
                  else 
                  {
                    for (unsigned int k = 0; k<MAX_COL_LCD; k++)
                      name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION][k] = ' ';
                  }
                }
                if (current_ekran.index_position >= index_in_list) position_temp--;
          
                offset++;
              }
              else
              {
                _SET_BIT(maska, j1);
                j1++;
              }
                
              index_in_list++;
            }
          }
          else
            index_in_list += ((min_max_number[i][1] - min_max_number[i][0]) + 1);
        }
      }
      else if (min_max_number[i][0] >=0)
      {
        //³������� ����� ������� � ������ ��� ����� ����� � ���� �������, ���� ������� ������ � ������ ��� ���������� ��� ������ �������
        //������� ����� ��, �� �� ����� ��������� ��� ��������� ���� ����
        unsigned int maska[N_BIG] = {0, 0, 0, 0, 0, 0};
        for (unsigned int j = 0; j < (min_max_number[i][0] - offset); j++) _SET_BIT(maska, j);
          
        //³������� ����� ������� �� ������, �� � �������
        while(index_in_list <= min_max_number[i][1])
        {
          /***/
          //������ ��� ����� ����������� ������� ����� �� �� �������
          /***/
          unsigned int new_temp_data_1[N_BIG], new_temp_data_2[N_BIG];

          new_temp_data_1[0] = state_viewing_input[0] & maska[0];
          new_temp_data_1[1] = state_viewing_input[1] & maska[1];
          new_temp_data_1[2] = state_viewing_input[2] & maska[2];
          new_temp_data_1[3] = state_viewing_input[3] & maska[3];
          new_temp_data_1[4] = state_viewing_input[4] & maska[4];
          new_temp_data_1[5] = state_viewing_input[5] & maska[5];

          new_temp_data_2[0] = state_viewing_input[0] & (~maska[0]);
          new_temp_data_2[1] = state_viewing_input[1] & (~maska[1]);
          new_temp_data_2[2] = state_viewing_input[2] & (~maska[2]);
          new_temp_data_2[3] = state_viewing_input[3] & (~maska[3]);
          new_temp_data_2[4] = state_viewing_input[4] & (~maska[4]);
          new_temp_data_2[5] = state_viewing_input[5] & (~maska[5]);

          new_temp_data_2[0] = (new_temp_data_2[0] >>1) | ((new_temp_data_2[1] & 0x1) << 31);
          new_temp_data_2[1] = (new_temp_data_2[1] >>1) | ((new_temp_data_2[2] & 0x1) << 31);
          new_temp_data_2[2] = (new_temp_data_2[2] >>1) | ((new_temp_data_2[3] & 0x1) << 31);
          new_temp_data_2[3] = (new_temp_data_2[3] >>1) | ((new_temp_data_2[4] & 0x1) << 31);
          new_temp_data_2[4] = (new_temp_data_2[4] >>1) | ((new_temp_data_2[5] & 0x1) << 31);
          new_temp_data_2[5] =  new_temp_data_2[5] >>1;

          new_temp_data_2[0] &= (~maska[0]);
          new_temp_data_2[1] &= (~maska[1]);
          new_temp_data_2[2] &= (~maska[2]);
          new_temp_data_2[3] &= (~maska[3]);
          new_temp_data_2[4] &= (~maska[4]);
          new_temp_data_2[5] &= (~maska[5]);

          state_viewing_input[0] = new_temp_data_1[0] | new_temp_data_2[0];
          state_viewing_input[1] = new_temp_data_1[1] | new_temp_data_2[1];
          state_viewing_input[2] = new_temp_data_1[2] | new_temp_data_2[2];
          state_viewing_input[3] = new_temp_data_1[3] | new_temp_data_2[3];
          state_viewing_input[4] = new_temp_data_1[4] | new_temp_data_2[4];
          state_viewing_input[5] = new_temp_data_1[5] | new_temp_data_2[5];
          /***/
          for (unsigned int j = (index_in_list - offset); j < max_row_ranguvannja; j++)
          {
            if ((j + 1) < max_row_ranguvannja)
            {
              for (unsigned int k = 0; k<MAX_COL_LCD; k++)
                name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION][k] = name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION + 1][k];
            }
            else 
            {
              for (unsigned int k = 0; k<MAX_COL_LCD; k++)
                name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION][k] = ' ';
            }
          }
          if (current_ekran.index_position >= index_in_list) position_temp--;
          
          offset++;
          index_in_list++;
        }
      }
    }
    /*************************************************************/

    if(
       (type_ekran == INDEX_VIEWING_A_REG) ||
       (type_ekran == INDEX_VIEWING_D_REG)
      )
    {
      /*************************************************************/
      //� �������, ���� ����������� ����������� ���� ����������� ���������� �� ����������� ����������, �� �������� � �������, �� �� ������ ���� ���������
      /*************************************************************/
      unsigned int index_deleted_function;
      
      if (type_ekran == INDEX_VIEWING_A_REG)
        index_deleted_function = RANG_OUTPUT_LED_DF_REG_WORK_A_REJESTRATOR;
      else
        index_deleted_function = RANG_OUTPUT_LED_DF_REG_WORK_D_REJESTRATOR;
      
      /*************************************************************/
      //³������� ��'� ���� ������� � ������ ���
      /*************************************************************/

      //������� ����� ��, �� �� ����� ��������� ��� ��������� ���� ����
      unsigned int maska[N_BIG] = {0, 0, 0, 0, 0, 0};
      for (unsigned int j = 0; j < index_deleted_function; j++) _SET_BIT(maska, j);
          
      /***/
      //������ ��� ����� ����������� ������� ����� �� �� �������
      /***/
      unsigned int new_temp_data_1[N_BIG], new_temp_data_2[N_BIG];

      new_temp_data_1[0] = state_viewing_input[0] & maska[0];
      new_temp_data_1[1] = state_viewing_input[1] & maska[1];
      new_temp_data_1[2] = state_viewing_input[2] & maska[2];
      new_temp_data_1[3] = state_viewing_input[3] & maska[3];
      new_temp_data_1[4] = state_viewing_input[4] & maska[4];
      new_temp_data_1[5] = state_viewing_input[5] & maska[5];

      new_temp_data_2[0] = state_viewing_input[0] & (~maska[0]);
      new_temp_data_2[1] = state_viewing_input[1] & (~maska[1]);
      new_temp_data_2[2] = state_viewing_input[2] & (~maska[2]);
      new_temp_data_2[3] = state_viewing_input[3] & (~maska[3]);
      new_temp_data_2[4] = state_viewing_input[4] & (~maska[4]);
      new_temp_data_2[5] = state_viewing_input[5] & (~maska[5]);

      new_temp_data_2[0] = (new_temp_data_2[0] >>1) | ((new_temp_data_2[1] & 0x1) << 31);
      new_temp_data_2[1] = (new_temp_data_2[1] >>1) | ((new_temp_data_2[2] & 0x1) << 31);
      new_temp_data_2[2] = (new_temp_data_2[2] >>1) | ((new_temp_data_2[3] & 0x1) << 31);
      new_temp_data_2[3] = (new_temp_data_2[3] >>1) | ((new_temp_data_2[4] & 0x1) << 31);
      new_temp_data_2[4] = (new_temp_data_2[4] >>1) | ((new_temp_data_2[5] & 0x1) << 31);
      new_temp_data_2[5] =  new_temp_data_2[5] >>1;

      new_temp_data_2[0] &= (~maska[0]);
      new_temp_data_2[1] &= (~maska[1]);
      new_temp_data_2[2] &= (~maska[2]);
      new_temp_data_2[3] &= (~maska[3]);
      new_temp_data_2[4] &= (~maska[4]);
      new_temp_data_2[5] &= (~maska[5]);

      state_viewing_input[0] = new_temp_data_1[0] | new_temp_data_2[0];
      state_viewing_input[1] = new_temp_data_1[1] | new_temp_data_2[1];
      state_viewing_input[2] = new_temp_data_1[2] | new_temp_data_2[2];
      state_viewing_input[3] = new_temp_data_1[3] | new_temp_data_2[3];
      state_viewing_input[4] = new_temp_data_1[4] | new_temp_data_2[4];
      state_viewing_input[5] = new_temp_data_1[5] | new_temp_data_2[5];
      /***/
      for (unsigned int j = index_deleted_function; j < max_row_ranguvannja; j++)
      {
        if ((j + 1) < max_row_ranguvannja)
        {
          for (unsigned int k = 0; k<MAX_COL_LCD; k++)
            name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION][k] = name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION + 1][k];
        }
        else 
        {
          for (unsigned int k = 0; k<MAX_COL_LCD; k++)
            name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION][k] = ' ';
        }
      }
      if (current_ekran.index_position >= ((int)index_deleted_function)) position_temp--;
      /*************************************************************/

      /*************************************************************/
    }
    else if(type_ekran == INDEX_VIEWING_DF)
    {
      /*************************************************************/
      //� �������, ���� ����������� ����������� ���� ������������ �������, �� �������� � �������, �� �� ������ ���� ���������
      /*************************************************************/
      
      unsigned int index_in_ekran_list = number_ekran - EKRAN_RANGUVANNJA_DF1_PLUS;
      unsigned int index_of_df = index_in_ekran_list / 3;
      
      /*************************************************************/
      //³������� ��'� ����� ������� � ������ ���
      /*************************************************************/
      for (i = 0; i < 2; i++)
      {
        unsigned int index_deleted_function;
        
        //��������� ������ �������, ��� ����� ���� ����������� �� �������
        //������ ��������� ������� � ������ �������, ��� ������ ������� � ����������� �����, ���� ��� ��������� ����� ���������� ���������
        if (i == 0)
        {
          if(index_of_df == 0)
            index_deleted_function = (RANG_OUTPUT_LED_DF_REG_DF1_OUT > RANG_OUTPUT_LED_DF_REG_DF1_IN) ? RANG_OUTPUT_LED_DF_REG_DF1_OUT : RANG_OUTPUT_LED_DF_REG_DF1_IN;
          else if(index_of_df == 1)
            index_deleted_function = (RANG_OUTPUT_LED_DF_REG_DF2_OUT > RANG_OUTPUT_LED_DF_REG_DF2_IN) ? RANG_OUTPUT_LED_DF_REG_DF2_OUT : RANG_OUTPUT_LED_DF_REG_DF2_IN;
          else if(index_of_df == 2)
            index_deleted_function = (RANG_OUTPUT_LED_DF_REG_DF3_OUT > RANG_OUTPUT_LED_DF_REG_DF3_IN) ? RANG_OUTPUT_LED_DF_REG_DF3_OUT : RANG_OUTPUT_LED_DF_REG_DF3_IN;
          else if(index_of_df == 3)
            index_deleted_function = (RANG_OUTPUT_LED_DF_REG_DF4_OUT > RANG_OUTPUT_LED_DF_REG_DF4_IN) ? RANG_OUTPUT_LED_DF_REG_DF4_OUT : RANG_OUTPUT_LED_DF_REG_DF4_IN;
          else if(index_of_df == 4)
            index_deleted_function = (RANG_OUTPUT_LED_DF_REG_DF5_OUT > RANG_OUTPUT_LED_DF_REG_DF5_IN) ? RANG_OUTPUT_LED_DF_REG_DF5_OUT : RANG_OUTPUT_LED_DF_REG_DF5_IN;
          else if(index_of_df == 5)
            index_deleted_function = (RANG_OUTPUT_LED_DF_REG_DF6_OUT > RANG_OUTPUT_LED_DF_REG_DF6_IN) ? RANG_OUTPUT_LED_DF_REG_DF6_OUT : RANG_OUTPUT_LED_DF_REG_DF6_IN;
          else if(index_of_df == 6)
            index_deleted_function = (RANG_OUTPUT_LED_DF_REG_DF7_OUT > RANG_OUTPUT_LED_DF_REG_DF7_IN) ? RANG_OUTPUT_LED_DF_REG_DF7_OUT : RANG_OUTPUT_LED_DF_REG_DF7_IN;
          else
            index_deleted_function = (RANG_OUTPUT_LED_DF_REG_DF8_OUT > RANG_OUTPUT_LED_DF_REG_DF8_IN) ? RANG_OUTPUT_LED_DF_REG_DF8_OUT : RANG_OUTPUT_LED_DF_REG_DF8_IN;
        }
        else
        {
          if(index_of_df == 0)
            index_deleted_function = (RANG_OUTPUT_LED_DF_REG_DF1_OUT > RANG_OUTPUT_LED_DF_REG_DF1_IN) ? RANG_OUTPUT_LED_DF_REG_DF1_IN : RANG_OUTPUT_LED_DF_REG_DF1_OUT;
          else if(index_of_df == 1)
            index_deleted_function = (RANG_OUTPUT_LED_DF_REG_DF2_OUT > RANG_OUTPUT_LED_DF_REG_DF2_IN) ? RANG_OUTPUT_LED_DF_REG_DF2_IN : RANG_OUTPUT_LED_DF_REG_DF2_OUT;
          else if(index_of_df == 2)
            index_deleted_function = (RANG_OUTPUT_LED_DF_REG_DF3_OUT > RANG_OUTPUT_LED_DF_REG_DF3_IN) ? RANG_OUTPUT_LED_DF_REG_DF3_IN : RANG_OUTPUT_LED_DF_REG_DF3_OUT;
          else if(index_of_df == 3)
            index_deleted_function = (RANG_OUTPUT_LED_DF_REG_DF4_OUT > RANG_OUTPUT_LED_DF_REG_DF4_IN) ? RANG_OUTPUT_LED_DF_REG_DF4_IN : RANG_OUTPUT_LED_DF_REG_DF4_OUT;
          else if(index_of_df == 4)
            index_deleted_function = (RANG_OUTPUT_LED_DF_REG_DF5_OUT > RANG_OUTPUT_LED_DF_REG_DF5_IN) ? RANG_OUTPUT_LED_DF_REG_DF5_IN : RANG_OUTPUT_LED_DF_REG_DF5_OUT;
          else if(index_of_df == 5)
            index_deleted_function = (RANG_OUTPUT_LED_DF_REG_DF6_OUT > RANG_OUTPUT_LED_DF_REG_DF6_IN) ? RANG_OUTPUT_LED_DF_REG_DF6_IN : RANG_OUTPUT_LED_DF_REG_DF6_OUT;
          else if(index_of_df == 6)
            index_deleted_function = (RANG_OUTPUT_LED_DF_REG_DF7_OUT > RANG_OUTPUT_LED_DF_REG_DF7_IN) ? RANG_OUTPUT_LED_DF_REG_DF7_IN : RANG_OUTPUT_LED_DF_REG_DF7_OUT;
          else
            index_deleted_function = (RANG_OUTPUT_LED_DF_REG_DF8_OUT > RANG_OUTPUT_LED_DF_REG_DF8_IN) ? RANG_OUTPUT_LED_DF_REG_DF8_IN : RANG_OUTPUT_LED_DF_REG_DF8_OUT;
        }
        
        //������� ����� ��, �� �� ����� ��������� ��� ��������� ���� ����
        unsigned int maska[N_BIG] = {0, 0, 0, 0, 0, 0};
        for (unsigned int j = 0; j < index_deleted_function; j++) _SET_BIT(maska, j);
          
        /***/
        //������ ��� ����� ����������� ������� ����� �� �� �������
        /***/
        unsigned int new_temp_data_1[N_BIG], new_temp_data_2[N_BIG];

        new_temp_data_1[0] = state_viewing_input[0] & maska[0];
        new_temp_data_1[1] = state_viewing_input[1] & maska[1];
        new_temp_data_1[2] = state_viewing_input[2] & maska[2];
        new_temp_data_1[3] = state_viewing_input[3] & maska[3];
        new_temp_data_1[4] = state_viewing_input[4] & maska[4];
        new_temp_data_1[5] = state_viewing_input[5] & maska[5];

        new_temp_data_2[0] = state_viewing_input[0] & (~maska[0]);
        new_temp_data_2[1] = state_viewing_input[1] & (~maska[1]);
        new_temp_data_2[2] = state_viewing_input[2] & (~maska[2]);
        new_temp_data_2[3] = state_viewing_input[3] & (~maska[3]);
        new_temp_data_2[4] = state_viewing_input[4] & (~maska[4]);
        new_temp_data_2[5] = state_viewing_input[5] & (~maska[5]);

        new_temp_data_2[0] = (new_temp_data_2[0] >>1) | ((new_temp_data_2[1] & 0x1) << 31);
        new_temp_data_2[1] = (new_temp_data_2[1] >>1) | ((new_temp_data_2[2] & 0x1) << 31);
        new_temp_data_2[2] = (new_temp_data_2[2] >>1) | ((new_temp_data_2[3] & 0x1) << 31);
        new_temp_data_2[3] = (new_temp_data_2[3] >>1) | ((new_temp_data_2[4] & 0x1) << 31);
        new_temp_data_2[4] = (new_temp_data_2[4] >>1) | ((new_temp_data_2[5] & 0x1) << 31);
        new_temp_data_2[5] =  new_temp_data_2[5] >>1;

        new_temp_data_2[0] &= (~maska[0]);
        new_temp_data_2[1] &= (~maska[1]);
        new_temp_data_2[2] &= (~maska[2]);
        new_temp_data_2[3] &= (~maska[3]);
        new_temp_data_2[4] &= (~maska[4]);
        new_temp_data_2[5] &= (~maska[5]);

        state_viewing_input[0] = new_temp_data_1[0] | new_temp_data_2[0];
        state_viewing_input[1] = new_temp_data_1[1] | new_temp_data_2[1];
        state_viewing_input[2] = new_temp_data_1[2] | new_temp_data_2[2];
        state_viewing_input[3] = new_temp_data_1[3] | new_temp_data_2[3];
        state_viewing_input[4] = new_temp_data_1[4] | new_temp_data_2[4];
        state_viewing_input[5] = new_temp_data_1[5] | new_temp_data_2[5];
        /***/
        for (unsigned int j = index_deleted_function; j < max_row_ranguvannja; j++)
        {
          if ((j + 1) < max_row_ranguvannja)
          {
            for (unsigned int k = 0; k<MAX_COL_LCD; k++)
              name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION][k] = name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION + 1][k];
          }
          else 
          {
            for (unsigned int k = 0; k<MAX_COL_LCD; k++)
              name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION][k] = ' ';
          }
        }
        if (current_ekran.index_position >= ((int)index_deleted_function)) position_temp--;
        /*************************************************************/
      }
      /*************************************************************/
    }
    else if(type_ekran == INDEX_VIEWING_DT)
    {
      /*************************************************************/
      //� �������, ���� ����������� ����������� ���� ������������ ������, �� �������� � �������, �� �� ������ ���� ���������
      /*************************************************************/
      
      unsigned int index_in_ekran_list = number_ekran - EKRAN_RANGUVANNJA_SET_DT1_PLUS;
      unsigned int index_of_dt = index_in_ekran_list / 4;
      
      /*************************************************************/
      //³������� ��'� ����� ������� � ������ ���
      /*************************************************************/
      for (i = 0; i < 3; i++)
      {
        unsigned int index_deleted_function;
        
        //��������� ������ �������, ��� ����� ���� ����������� �� �������
        //������ ��������� ������� � ������ �������, ��� �� ���� ������� � ����������� �����, ���� ��� ��������� ����� ���������� ���������
        if (i == 0)
        {
          if(index_of_dt == 0)
            index_deleted_function = RANG_OUTPUT_LED_DF_REG_DT1_OUT;
          else if(index_of_dt == 1)
            index_deleted_function = RANG_OUTPUT_LED_DF_REG_DT2_OUT;
          else if(index_of_dt == 2)
            index_deleted_function = RANG_OUTPUT_LED_DF_REG_DT3_OUT;
          else if(index_of_dt == 3)
            index_deleted_function = RANG_OUTPUT_LED_DF_REG_DT4_OUT;
        }
        else if (i == 1)
        {
          if(index_of_dt == 0)
            index_deleted_function = RANG_OUTPUT_LED_DF_REG_DT1_RESET;
          else if(index_of_dt == 1)
            index_deleted_function = RANG_OUTPUT_LED_DF_REG_DT2_RESET;
          else if(index_of_dt == 2)
            index_deleted_function = RANG_OUTPUT_LED_DF_REG_DT3_RESET;
          else if(index_of_dt == 3)
            index_deleted_function = RANG_OUTPUT_LED_DF_REG_DT4_RESET;
        }
        else
        {
          if(index_of_dt == 0)
            index_deleted_function = RANG_OUTPUT_LED_DF_REG_DT1_SET;
          else if(index_of_dt == 1)
            index_deleted_function = RANG_OUTPUT_LED_DF_REG_DT2_SET;
          else if(index_of_dt == 2)
            index_deleted_function = RANG_OUTPUT_LED_DF_REG_DT3_SET;
          else if(index_of_dt == 3)
            index_deleted_function = RANG_OUTPUT_LED_DF_REG_DT4_SET;
        }
        
        //������� ����� ��, �� �� ����� ��������� ��� ��������� ���� ����
        unsigned int maska[N_BIG] = {0, 0, 0, 0, 0, 0};
        for (unsigned int j = 0; j < index_deleted_function; j++) _SET_BIT(maska, j);
          
        /***/
        //������ ��� ����� ����������� ������� ����� �� �� �������
        /***/
        unsigned int new_temp_data_1[N_BIG], new_temp_data_2[N_BIG];

        new_temp_data_1[0] = state_viewing_input[0] & maska[0];
        new_temp_data_1[1] = state_viewing_input[1] & maska[1];
        new_temp_data_1[2] = state_viewing_input[2] & maska[2];
        new_temp_data_1[3] = state_viewing_input[3] & maska[3];
        new_temp_data_1[4] = state_viewing_input[4] & maska[4];
        new_temp_data_1[5] = state_viewing_input[5] & maska[5];

        new_temp_data_2[0] = state_viewing_input[0] & (~maska[0]);
        new_temp_data_2[1] = state_viewing_input[1] & (~maska[1]);
        new_temp_data_2[2] = state_viewing_input[2] & (~maska[2]);
        new_temp_data_2[3] = state_viewing_input[3] & (~maska[3]);
        new_temp_data_2[4] = state_viewing_input[4] & (~maska[4]);
        new_temp_data_2[5] = state_viewing_input[5] & (~maska[5]);

        new_temp_data_2[0] = (new_temp_data_2[0] >>1) | ((new_temp_data_2[1] & 0x1) << 31);
        new_temp_data_2[1] = (new_temp_data_2[1] >>1) | ((new_temp_data_2[2] & 0x1) << 31);
        new_temp_data_2[2] = (new_temp_data_2[2] >>1) | ((new_temp_data_2[3] & 0x1) << 31);
        new_temp_data_2[3] = (new_temp_data_2[3] >>1) | ((new_temp_data_2[4] & 0x1) << 31);
        new_temp_data_2[4] = (new_temp_data_2[4] >>1) | ((new_temp_data_2[5] & 0x1) << 31);
        new_temp_data_2[5] =  new_temp_data_2[5] >>1;

        new_temp_data_2[0] &= (~maska[0]);
        new_temp_data_2[1] &= (~maska[1]);
        new_temp_data_2[2] &= (~maska[2]);
        new_temp_data_2[3] &= (~maska[3]);
        new_temp_data_2[4] &= (~maska[4]);
        new_temp_data_2[5] &= (~maska[5]);

        state_viewing_input[0] = new_temp_data_1[0] | new_temp_data_2[0];
        state_viewing_input[1] = new_temp_data_1[1] | new_temp_data_2[1];
        state_viewing_input[2] = new_temp_data_1[2] | new_temp_data_2[2];
        state_viewing_input[3] = new_temp_data_1[3] | new_temp_data_2[3];
        state_viewing_input[4] = new_temp_data_1[4] | new_temp_data_2[4];
        state_viewing_input[5] = new_temp_data_1[5] | new_temp_data_2[5];
        /***/
        for (unsigned int j = index_deleted_function; j < max_row_ranguvannja; j++)
        {
          if ((j + 1) < max_row_ranguvannja)
          {
            for (unsigned int k = 0; k<MAX_COL_LCD; k++)
              name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION][k] = name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION + 1][k];
          }
          else 
          {
            for (unsigned int k = 0; k<MAX_COL_LCD; k++)
              name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION][k] = ' ';
          }
        }
        if (current_ekran.index_position >= ((int)index_deleted_function)) position_temp--;
        /*************************************************************/
      }
      /*************************************************************/
    }
    else if(type_ekran == INDEX_VIEWING_OUTPUT)
    {
      /*************************************************************/
      //� �������, ���� ����������� ����������� ���� ������, �� �������� � �������, �� �� ������ ���� ��������� �� ���������� �����
      /*
      � ��:
            "������ ��" - ���� ���� ��� � ����������� �� ���� ������ (�� ��� �� ����� ���������, ��� ���� ��������� ���� �����)
            "������ ��" - ���� ���� ��� � ����������� �� ���� ������ (�� ��� �� ����� ���������, ��� ���� ��������� ���� �����)
      */
      
      unsigned int current_number_output = number_ekran - EKRAN_RANGUVANNJA_OUTPUT_1;

      for (i = 0; i < 2; i++)
      {
        unsigned int index_deleted_function;
        unsigned int maska_func[N_BIG] = {0, 0, 0, 0, 0, 0};
        unsigned int need_filtration = 0;
        //��������� ������ �������, ��� ���������� ������� ����� ���� ����������� �� �������
        //������ ��������� ������� � ������ �������, ��� ������ ������� � ����������� ����� ,���� ��� ��������� ����� ���������� ���������
        if (i == 0)
        {
          index_deleted_function = (RANG_OUTPUT_LED_DF_REG_WORK_BV > RANG_OUTPUT_LED_DF_REG_WORK_BO) ? RANG_OUTPUT_LED_DF_REG_WORK_BV : RANG_OUTPUT_LED_DF_REG_WORK_BO;
        }
        else
        {
          index_deleted_function = (RANG_OUTPUT_LED_DF_REG_WORK_BV > RANG_OUTPUT_LED_DF_REG_WORK_BO) ? RANG_OUTPUT_LED_DF_REG_WORK_BO : RANG_OUTPUT_LED_DF_REG_WORK_BV;
        }
        
        //������� �����  ��� ���� �������
        _SET_BIT(maska_func, index_deleted_function);
        
        unsigned int index = 0;
        while ((need_filtration == 0) && (index < NUMBER_OUTPUTS))
        {
          //���������� ������� ����� ������, �� �� ����� ���� ������� �� ������������ �� ��� �����������
          if (index != current_number_output)
          {
            if (
                ((current_settings.ranguvannja_outputs[N_BIG*index    ] & maska_func[0]) != 0) ||
                ((current_settings.ranguvannja_outputs[N_BIG*index + 1] & maska_func[1]) != 0) ||
                ((current_settings.ranguvannja_outputs[N_BIG*index + 2] & maska_func[2]) != 0) ||
                ((current_settings.ranguvannja_outputs[N_BIG*index + 3] & maska_func[3]) != 0) ||
                ((current_settings.ranguvannja_outputs[N_BIG*index + 4] & maska_func[4]) != 0) ||
                ((current_settings.ranguvannja_outputs[N_BIG*index + 5] & maska_func[5]) != 0)
               )
            {
              need_filtration = 1;
            }
          }
          index++;
        }
        
        //� �������, ���� ������������ �� ���� ������� ����� �������������, �� �������� ��
        if (need_filtration != 0)
        {
          //������� ����� ��, �� �� ����� ��������� ��� ��������� ���� ����
          unsigned int maska[N_BIG] = {0, 0, 0, 0, 0, 0};
          for (unsigned int j = 0; j < index_deleted_function; j++) _SET_BIT(maska, j);
          
          /***/
          //������ ��� ����� ����������� ������� ����� �� �� �������
          /***/
          unsigned int new_temp_data_1[N_BIG], new_temp_data_2[N_BIG];

          new_temp_data_1[0] = state_viewing_input[0] & maska[0];
          new_temp_data_1[1] = state_viewing_input[1] & maska[1];
          new_temp_data_1[2] = state_viewing_input[2] & maska[2];
          new_temp_data_1[3] = state_viewing_input[3] & maska[3];
          new_temp_data_1[4] = state_viewing_input[4] & maska[4];
          new_temp_data_1[5] = state_viewing_input[5] & maska[5];

          new_temp_data_2[0] = state_viewing_input[0] & (~maska[0]);
          new_temp_data_2[1] = state_viewing_input[1] & (~maska[1]);
          new_temp_data_2[2] = state_viewing_input[2] & (~maska[2]);
          new_temp_data_2[3] = state_viewing_input[3] & (~maska[3]);
          new_temp_data_2[4] = state_viewing_input[4] & (~maska[4]);
          new_temp_data_2[5] = state_viewing_input[5] & (~maska[5]);

          new_temp_data_2[0] = (new_temp_data_2[0] >>1) | ((new_temp_data_2[1] & 0x1) << 31);
          new_temp_data_2[1] = (new_temp_data_2[1] >>1) | ((new_temp_data_2[2] & 0x1) << 31);
          new_temp_data_2[2] = (new_temp_data_2[2] >>1) | ((new_temp_data_2[3] & 0x1) << 31);
          new_temp_data_2[3] = (new_temp_data_2[3] >>1) | ((new_temp_data_2[4] & 0x1) << 31);
          new_temp_data_2[4] = (new_temp_data_2[4] >>1) | ((new_temp_data_2[5] & 0x1) << 31);
          new_temp_data_2[5] =  new_temp_data_2[5] >>1;

          new_temp_data_2[0] &= (~maska[0]);
          new_temp_data_2[1] &= (~maska[1]);
          new_temp_data_2[2] &= (~maska[2]);
          new_temp_data_2[3] &= (~maska[3]);
          new_temp_data_2[4] &= (~maska[4]);
          new_temp_data_2[5] &= (~maska[5]);

          state_viewing_input[0] = new_temp_data_1[0] | new_temp_data_2[0];
          state_viewing_input[1] = new_temp_data_1[1] | new_temp_data_2[1];
          state_viewing_input[2] = new_temp_data_1[2] | new_temp_data_2[2];
          state_viewing_input[3] = new_temp_data_1[3] | new_temp_data_2[3];
          state_viewing_input[4] = new_temp_data_1[4] | new_temp_data_2[4];
          state_viewing_input[5] = new_temp_data_1[5] | new_temp_data_2[5];
          /***/
          for (unsigned int j = index_deleted_function; j < max_row_ranguvannja; j++)
          {
            if ((j + 1) < max_row_ranguvannja)
            {
              for (unsigned int k = 0; k<MAX_COL_LCD; k++)
                name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION][k] = name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION + 1][k];
            }
            else 
            {
              for (unsigned int k = 0; k<MAX_COL_LCD; k++)
                name_string_tmp[j + NUMBER_ROW_FOR_NOTHING_INFORMATION][k] = ' ';
            }
          }
          if (current_ekran.index_position >= ((int)index_deleted_function)) position_temp--;
          /*************************************************************/
        }
      }
      /*************************************************************/
    }
    
    //�������� �� ��� �������� position_temp ������� ��� ����, �� �� ���� ������� �� ������������� ��� ����� (����� + ��������)
    index_of_ekran = ((position_temp<<1) >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;

    for (i=0; i< MAX_ROW_LCD; i++)
    {
     if (index_of_ekran < (max_row_ranguvannja<<1))//�������� �� ��� ���������  max_row_ranguvannja ������� ��� ����, �� �� ���� ������� �� ������������� ��� ����� (����� + ��������)
     {
       if ((i & 0x1) == 0)
       {
         //� ��������� ����� ����� �������� ���������
         for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string_tmp[(index_of_ekran>>1) + NUMBER_ROW_FOR_NOTHING_INFORMATION][j];
       }
       else
       {
         //� ������� ����� ����� �������� ���� �������
         const unsigned char information[MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD] = 
         {
           {"      ����      ", "      ���       "},
           {"      ����      ", "     �²��      "},
           {"      OFF       ", "       ON       "},
           {"      ъ��      ", "      ����      "}
         };
         unsigned int index_bit = index_of_ekran >> 1;
         
         for (unsigned int j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = information[index_language][((state_viewing_input[index_bit >> 5] & ( 1<< (index_bit & 0x1f))) != 0)][j];
       }
     }
     else
     for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';

     index_of_ekran++;
    }
    
    const unsigned int cursor_x[MAX_NAMBER_LANGUAGE][2] = 
    {
      {5, 5},
      {5, 4},
      {5, 6},
      {5, 5}
    };

    //³���������� ������ �� �������� � ������ ������ �� ���� � ��� �� ��������� ������
    current_ekran.position_cursor_x =  cursor_x[index_language][((state_viewing_input[position_temp >> 5] & (1 << (position_temp & 0x1f))) != 0)];
    current_ekran.position_cursor_y = ((position_temp<<1) + 1) & (MAX_ROW_LCD - 1);
    
    //������ ����
    current_ekran.cursor_blinking_on = 1;
    //����� ����������� � ����� �����������
  }
  

  //�������� ������� ���� �����
  current_ekran.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;

#undef NUMBER_ROW_FOR_NOTHING_INFORMATION
}
/*****************************************************/

/*****************************************************/
//��������, �� ������� ������ ����� �� �������, ��� �������� � ���� ������������
/*****************************************************/
void check_current_index_is_presented_in_configuration(
                                                         unsigned int* found_new_index_tmp,
                                                                  int* add_filter_point,
                                                                  int plus_minus,
                                                                  int number_general_function,
                                                                  int number_mtz_function,
                                                                  int number_zdz_function,
                                                                  int number_zz_function,
                                                                  int number_apv_function,
                                                                  int number_apv_zmn_function,
                                                                  int number_achr_chapv_function,
                                                                  int number_urov_function,
                                                                  int number_zop_function,
                                                                  int number_Umin_function,
                                                                  int number_Umax_function,
                                                                  int number_avr_function,
                                                                  int number_control_U_function,
                                                                  int number_vmp_function
                                                        )
{
  if(plus_minus == 1)
  {
    if (current_ekran.index_position < number_general_function) *found_new_index_tmp = 1;
    else
    {
      if (current_ekran.index_position < (number_general_function + number_mtz_function))
      {
        if ((current_settings.configuration & (1<<MTZ_BIT_CONFIGURATION)) != 0) *found_new_index_tmp = 1;
        else current_ekran.index_position = number_general_function + number_mtz_function;
      }
      else if (current_ekran.index_position < (number_general_function + number_mtz_function + number_zdz_function))
      {
        if ((current_settings.configuration & (1<<ZDZ_BIT_CONFIGURATION)) != 0) *found_new_index_tmp = 1;
        else current_ekran.index_position = number_general_function + number_mtz_function + number_zdz_function;
      }
      else if (current_ekran.index_position < (number_general_function + number_mtz_function + number_zdz_function + number_zz_function))
      {
        if ((current_settings.configuration & (1<<ZZ_BIT_CONFIGURATION)) != 0) *found_new_index_tmp = 1;
        else current_ekran.index_position = number_general_function + number_mtz_function + number_zdz_function + number_zz_function;
      }
      else if (current_ekran.index_position < (number_general_function + number_mtz_function + number_zdz_function + number_zz_function + number_apv_function))
      {
        if ((current_settings.configuration & (1<<APV_BIT_CONFIGURATION)) != 0) *found_new_index_tmp = 1;
        else current_ekran.index_position = number_general_function + number_mtz_function + number_zdz_function + number_zz_function + number_apv_function;
      }
      else if (current_ekran.index_position < (number_general_function + number_mtz_function + number_zdz_function + number_zz_function + number_apv_function + number_apv_zmn_function))
      {
        if ((current_settings.configuration & (1<<APV_ZMN_BIT_CONFIGURATION)) != 0) *found_new_index_tmp = 1;
        else current_ekran.index_position = number_general_function + number_mtz_function + number_zdz_function + number_zz_function + number_apv_function + number_apv_zmn_function;
      }
      else if (current_ekran.index_position < (number_general_function + number_mtz_function + number_zdz_function + number_zz_function + number_apv_function + number_apv_zmn_function + number_achr_chapv_function))
      {
        if ((current_settings.configuration & (1<<ACHR_CHAPV_BIT_CONFIGURATION)) != 0) *found_new_index_tmp = 1;
        else current_ekran.index_position = number_general_function + number_mtz_function + number_zdz_function + number_zz_function + number_apv_function + number_apv_zmn_function + number_achr_chapv_function;
      }
      else if (current_ekran.index_position < (number_general_function + number_mtz_function + number_zdz_function + number_zz_function + number_apv_function + number_apv_zmn_function + number_achr_chapv_function + number_urov_function))
      {
        if ((current_settings.configuration & (1<<UROV_BIT_CONFIGURATION)) != 0) *found_new_index_tmp = 1;
        else current_ekran.index_position = number_general_function + number_mtz_function + number_zdz_function + number_zz_function + number_apv_function + number_apv_zmn_function + number_achr_chapv_function + number_urov_function;
      }
      else if (current_ekran.index_position < (number_general_function + number_mtz_function + number_zdz_function + number_zz_function + number_apv_function + number_apv_zmn_function + number_achr_chapv_function + number_urov_function + number_zop_function))
      {
        if ((current_settings.configuration & (1<<ZOP_BIT_CONFIGURATION)) != 0) *found_new_index_tmp = 1;
        else current_ekran.index_position = number_general_function + number_mtz_function + number_zdz_function + number_zz_function + number_apv_function + number_apv_zmn_function + number_achr_chapv_function + number_urov_function + number_zop_function;
      }
      else if (current_ekran.index_position < (number_general_function + number_mtz_function + number_zdz_function + number_zz_function + number_apv_function + number_apv_zmn_function + number_achr_chapv_function + number_urov_function + number_zop_function + number_Umin_function))
      {
        if ((current_settings.configuration & (1<<UMIN_BIT_CONFIGURATION)) != 0) *found_new_index_tmp = 1;
        else current_ekran.index_position = number_general_function + number_mtz_function + number_zdz_function + number_zz_function + number_apv_function + number_apv_zmn_function + number_achr_chapv_function + number_urov_function + number_zop_function + number_Umin_function;
      }
      else if (current_ekran.index_position < (number_general_function + number_mtz_function + number_zdz_function + number_zz_function + number_apv_function + number_apv_zmn_function + number_achr_chapv_function + number_urov_function + number_zop_function + number_Umin_function + number_Umax_function))
      {
        if ((current_settings.configuration & (1<<UMAX_BIT_CONFIGURATION)) != 0) *found_new_index_tmp = 1;
        else current_ekran.index_position = number_general_function + number_mtz_function + number_zdz_function + number_zz_function + number_apv_function + number_apv_zmn_function + number_achr_chapv_function + number_urov_function + number_zop_function + number_Umin_function + number_Umax_function;
      }
      else if (current_ekran.index_position < (number_general_function + number_mtz_function + number_zdz_function + number_zz_function + number_apv_function + number_apv_zmn_function + number_achr_chapv_function + number_urov_function + number_zop_function + number_Umin_function + number_Umax_function + number_avr_function))
      {
        if ((current_settings.configuration & (1<<AVR_BIT_CONFIGURATION)) != 0) *found_new_index_tmp = 1;
        else current_ekran.index_position = number_general_function + number_mtz_function + number_zdz_function + number_zz_function + number_apv_function + number_apv_zmn_function + number_achr_chapv_function + number_urov_function + number_zop_function + number_Umin_function + number_Umax_function + number_avr_function;
      }
      else if (current_ekran.index_position < (number_general_function + number_mtz_function + number_zdz_function + number_zz_function + number_apv_function + number_apv_zmn_function + number_achr_chapv_function + number_urov_function + number_zop_function + number_Umin_function + number_Umax_function + number_avr_function + number_control_U_function))
      {
        if ((current_settings.configuration & (1<<CONTROL_U_BIT_CONFIGURATION)) != 0) *found_new_index_tmp = 1;
        else current_ekran.index_position = number_general_function + number_mtz_function + number_zdz_function + number_zz_function + number_apv_function + number_apv_zmn_function + number_achr_chapv_function + number_urov_function + number_zop_function + number_Umin_function + number_Umax_function + number_avr_function + number_control_U_function;
      }
      else if (current_ekran.index_position < (number_general_function + number_mtz_function + number_zdz_function + number_zz_function + number_apv_function + number_apv_zmn_function + number_achr_chapv_function + number_urov_function + number_zop_function + number_Umin_function + number_Umax_function + number_avr_function + number_control_U_function + number_vmp_function))
      {
        if ((current_settings.configuration & (1<<VMP_BIT_CONFIGURATION)) != 0) *found_new_index_tmp = 1;
        else current_ekran.index_position = number_general_function + number_mtz_function + number_zdz_function + number_zz_function + number_apv_function + number_apv_zmn_function + number_achr_chapv_function + number_urov_function + number_zop_function + number_Umin_function + number_Umax_function + number_avr_function + number_control_U_function + number_vmp_function;
      }
    }

    if (
        ((current_settings.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_3U0_Ubc_TN2) != 0) ||
        ((current_settings.control_zz & CTR_ZZ1_TYPE) != 0)  
       )   
    {
      unsigned int i = 0;
      while (
             (*found_new_index_tmp == 1) &&
             (add_filter_point[i]  >= 0)
            )
      {
        if (
            (
             ((current_settings.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_3U0_Ubc_TN2) != 0) ||
             (i >= 2)  
            )
            &&  
            (current_ekran.index_position == add_filter_point[i])
           )   
        {
          *found_new_index_tmp = 0;
          current_ekran.index_position++;
        }
        else i++;
      }
     }
  }
  else
  {
    if (current_ekran.index_position < number_general_function) *found_new_index_tmp = 1;
    else
    {
      if (current_ekran.index_position < (number_general_function + number_mtz_function))
      {
        if ((current_settings.configuration & (1<<MTZ_BIT_CONFIGURATION)) != 0) *found_new_index_tmp = 1;
        else current_ekran.index_position = number_general_function - 1;
      }
      else if (current_ekran.index_position < (number_general_function + number_mtz_function + number_zdz_function))
      {
        if ((current_settings.configuration & (1<<ZDZ_BIT_CONFIGURATION)) != 0) *found_new_index_tmp = 1;
        else current_ekran.index_position = number_general_function + number_mtz_function - 1;
      }
      else if (current_ekran.index_position < (number_general_function + number_mtz_function + number_zdz_function + number_zz_function))
      {
        if ((current_settings.configuration & (1<<ZZ_BIT_CONFIGURATION)) != 0) *found_new_index_tmp = 1;
        else current_ekran.index_position = number_general_function + number_mtz_function + number_zdz_function - 1;
      }
      else if (current_ekran.index_position < (number_general_function + number_mtz_function + number_zdz_function + number_zz_function + number_apv_function))
      {
        if ((current_settings.configuration & (1<<APV_BIT_CONFIGURATION)) != 0) *found_new_index_tmp = 1;
        else current_ekran.index_position = number_general_function + number_mtz_function + number_zdz_function + number_zz_function - 1;
      }
      else if (current_ekran.index_position < (number_general_function + number_mtz_function + number_zdz_function + number_zz_function + number_apv_function + number_apv_zmn_function))
      {
        if ((current_settings.configuration & (1<<APV_ZMN_BIT_CONFIGURATION)) != 0) *found_new_index_tmp = 1;
        else current_ekran.index_position = number_general_function + number_mtz_function + number_zdz_function + number_zz_function + number_apv_function - 1;
      }
      else if (current_ekran.index_position < (number_general_function + number_mtz_function + number_zdz_function + number_zz_function + number_apv_function + number_apv_zmn_function + number_achr_chapv_function))
      {
        if ((current_settings.configuration & (1<<ACHR_CHAPV_BIT_CONFIGURATION)) != 0) *found_new_index_tmp = 1;
        else current_ekran.index_position = number_general_function + number_mtz_function + number_zdz_function + number_zz_function + number_apv_function + number_apv_zmn_function - 1;
      }
      else if (current_ekran.index_position < (number_general_function + number_mtz_function + number_zdz_function + number_zz_function + number_apv_function + number_apv_zmn_function + number_achr_chapv_function + number_urov_function))
      {
        if ((current_settings.configuration & (1<<UROV_BIT_CONFIGURATION)) != 0) *found_new_index_tmp = 1;
        else current_ekran.index_position = number_general_function + number_mtz_function + number_zdz_function + number_zz_function + number_apv_function + number_apv_zmn_function + number_achr_chapv_function - 1;
      }
      else if (current_ekran.index_position < (number_general_function + number_mtz_function + number_zdz_function + number_zz_function + number_apv_function + number_apv_zmn_function + number_achr_chapv_function + number_urov_function + number_zop_function))
      {
        if ((current_settings.configuration & (1<<ZOP_BIT_CONFIGURATION)) != 0) *found_new_index_tmp = 1;
        else current_ekran.index_position = number_general_function + number_mtz_function + number_zdz_function + number_zz_function + number_apv_function + number_apv_zmn_function + number_achr_chapv_function + number_urov_function - 1;
      }
      else if (current_ekran.index_position < (number_general_function + number_mtz_function + number_zdz_function + number_zz_function + number_apv_function + number_apv_zmn_function + number_achr_chapv_function + number_urov_function + number_zop_function + number_Umin_function))
      {
        if ((current_settings.configuration & (1<<UMIN_BIT_CONFIGURATION)) != 0) *found_new_index_tmp = 1;
        else current_ekran.index_position = number_general_function + number_mtz_function + number_zdz_function + number_zz_function + number_apv_function + number_apv_zmn_function + number_achr_chapv_function + number_urov_function + number_zop_function - 1;
      }
      else if (current_ekran.index_position < (number_general_function + number_mtz_function + number_zdz_function + number_zz_function + number_apv_function + number_apv_zmn_function + number_achr_chapv_function + number_urov_function + number_zop_function + number_Umin_function + number_Umax_function))
      {
        if ((current_settings.configuration & (1<<UMAX_BIT_CONFIGURATION)) != 0) *found_new_index_tmp = 1;
        else current_ekran.index_position = number_general_function + number_mtz_function + number_zdz_function + number_zz_function + number_apv_function + number_apv_zmn_function + number_achr_chapv_function + number_urov_function + number_zop_function + number_Umin_function - 1;
      }
      else if (current_ekran.index_position < (number_general_function + number_mtz_function + number_zdz_function + number_zz_function + number_apv_function + number_apv_zmn_function + number_achr_chapv_function + number_urov_function + number_zop_function + number_Umin_function + number_Umax_function + number_avr_function))
      {
        if ((current_settings.configuration & (1<<AVR_BIT_CONFIGURATION)) != 0) *found_new_index_tmp = 1;
        else current_ekran.index_position = number_general_function + number_mtz_function + number_zdz_function + number_zz_function + number_apv_function + number_apv_zmn_function + number_achr_chapv_function + number_urov_function + number_zop_function + number_Umin_function + number_Umax_function - 1;
      }
      else if (current_ekran.index_position < (number_general_function + number_mtz_function + number_zdz_function + number_zz_function + number_apv_function + number_apv_zmn_function + number_achr_chapv_function + number_urov_function + number_zop_function + number_Umin_function + number_Umax_function + number_avr_function + number_control_U_function))
      {
        if ((current_settings.configuration & (1<<CONTROL_U_BIT_CONFIGURATION)) != 0) *found_new_index_tmp = 1;
        else current_ekran.index_position = number_general_function + number_mtz_function + number_zdz_function + number_zz_function + number_apv_function + number_apv_zmn_function + number_achr_chapv_function + number_urov_function + number_zop_function + number_Umin_function + number_Umax_function + number_avr_function - 1;
      }
      else if (current_ekran.index_position < (number_general_function + number_mtz_function + number_zdz_function + number_zz_function + number_apv_function + number_apv_zmn_function + number_achr_chapv_function + number_urov_function + number_zop_function + number_Umin_function + number_Umax_function + number_avr_function + number_control_U_function + number_vmp_function))
      {
        if ((current_settings.configuration & (1<<VMP_BIT_CONFIGURATION)) != 0) *found_new_index_tmp = 1;
        else current_ekran.index_position = number_general_function + number_mtz_function + number_zdz_function + number_zz_function + number_apv_function + number_apv_zmn_function + number_achr_chapv_function + number_urov_function + number_zop_function + number_Umin_function + number_Umax_function + number_avr_function + number_control_U_function - 1;
      }
    }

    if (
        ((current_settings.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_3U0_Ubc_TN2) != 0) ||
        ((current_settings.control_zz & CTR_ZZ1_TYPE) != 0)
       )   
    {
      unsigned int i = 0;
      while (
             (*found_new_index_tmp == 1) &&
             (add_filter_point[i]  >= 0)
            )
      {
        if (
            (
             ((current_settings.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_3U0_Ubc_TN2) != 0) ||
             (i >= 2)  
            )
            &&  
            (current_ekran.index_position == add_filter_point[i])
           )   
        {
          *found_new_index_tmp = 0;
          current_ekran.index_position--;
        }
        else i++;
      }
    }
  }
}
/*****************************************************/

/*****************************************************/
//
/*****************************************************/
/*****************************************************/
