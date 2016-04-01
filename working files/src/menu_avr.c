#include "header.h"

/*****************************************************/
//������� ����� ����������� ������� ���
/*****************************************************/
void make_ekran_setpoint_avr(unsigned int group)
{
  const unsigned char name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_SETPOINT_AVR][MAX_COL_LCD] = 
  {
    {
      " ���.U ��� ���.1",
      "���.U ��� ����.1",
      " ���.U ��� ���.2",
      "���.U ��� ����.2",
      "   �����.���    "
    },
    {
      " ���.U ��� ��.1",
      "���.U ��� ����.1",
      " ���.U ��� ��.2",
      "���.U ��� ����.2",
      "   �����.���    "
    },
    {
      " ���.U ��� ���.1",
      "���.U ��� ����.1",
      " ���.U ��� ���.2",
      "���.U ��� ����.2",
      "   �����.���    "
    },
    {
      " ���.U ��� ���.1",
      "���.U ��� ����.1",
      " ���.U ��� ���.2",
      "���.U ��� ����.2",
      "   �����.���    "
    }
  };
  int index_language = index_language_in_array(current_settings.language);
  
  unsigned int position_temp = current_ekran.index_position;
  unsigned int index_of_ekran;
  unsigned int vaga, value, first_symbol;
  
  //�������� �� ��� �������� position_temp ������� ��� ����, �� ����� ������� �� ������������� ��� ����� (����� + ��������)
  index_of_ekran = ((position_temp<<1) >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;
  
  for (unsigned int i=0; i< MAX_ROW_LCD; i++)
  {
    if (index_of_ekran < (MAX_ROW_FOR_SETPOINT_AVR<<1))//�������� �� ��� ��������� MAX_ROW_FOR_SETPOINT_AVR ������� ��� ����, �� ����� ������� �� ������������� ��� ����� (����� + ��������)
    {
      if ((i & 0x1) == 0)
      {
        //� ��������� ����� ����� �������� ���������
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][index_of_ekran>>1][j];
        if ((index_of_ekran>>1) == INDEX_ML_STPAVR_MIN1)
        {
          vaga = 100000; //������������ ������� ���������� ��� �������� �������� ������� ��� �������
          if (current_ekran.edition == 0) value = current_settings.setpoint_avr_min1[group]; //� ����� value ������� �������� �������
          else value = edition_settings.setpoint_avr_min1[group];
          first_symbol = 0; //�������, �� �� ����� �������� ������ �� ���������
        }
        else if ((index_of_ekran>>1) == INDEX_ML_STPAVR_MAX1)
        {
          vaga = 100000; //������������ ������� ���������� ��� �������� �������� ������� ��� �������
          if (current_ekran.edition == 0) value = current_settings.setpoint_avr_max1[group]; //� ����� value ������� �������� �������
          else value = edition_settings.setpoint_avr_max1[group];
          first_symbol = 0; //�������, �� �� ����� �������� ������ �� ���������
        }
        else if ((index_of_ekran>>1) == INDEX_ML_STPAVR_MIN2)
        {
          vaga = 100000; //������������ ������� ���������� ��� �������� �������� ������� ��� �������
          if (current_ekran.edition == 0) value = current_settings.setpoint_avr_min2[group]; //� ����� value ������� �������� �������
          else value = edition_settings.setpoint_avr_min2[group];
          first_symbol = 0; //�������, �� �� ����� �������� ������ �� ���������
        }
        else if ((index_of_ekran>>1) == INDEX_ML_STPAVR_MAX2)
        {
          vaga = 100000; //������������ ������� ���������� ��� �������� �������� ������� ��� �������
          if (current_ekran.edition == 0) value = current_settings.setpoint_avr_max2[group]; //� ����� value ������� �������� �������
          else value = edition_settings.setpoint_avr_max2[group];
          first_symbol = 0; //�������, �� �� ����� �������� ������ �� ���������
        }
        else if ((index_of_ekran>>1) == INDEX_ML_STPAVR_MAX_KRATN)
        {
          vaga = 100; //������������ ������� ���������� ��� �������� �������� ������� ��� �������
          if (current_ekran.edition == 0) value = current_settings.setpoint_kratn_avr[group]; //� ����� value ������� �������� �������
          else value = edition_settings.setpoint_kratn_avr[group];
          first_symbol = 0; //�������, �� �� ����� �������� ������ �� ���������
        }
      }
      else
      {
        //� ������� ����� ����� �������� �������� �������
        for (unsigned int j = 0; j<MAX_COL_LCD; j++)
        {
          if ((index_of_ekran>>1) == INDEX_ML_STPAVR_MIN1)
          {
            if (
                ((j < COL_SETPOINT_AVR_MIN1_BEGIN) ||  (j > COL_SETPOINT_AVR_MIN1_END ))  &&
                (j != (COL_SETPOINT_AVR_MIN1_END + 2))  
               )working_ekran[i][j] = ' ';
            else if (j == COL_SETPOINT_AVR_MIN1_COMMA )working_ekran[i][j] = ',';
            else if (j == (COL_SETPOINT_AVR_MIN1_END + 2)) working_ekran[i][j] = odynyci_vymirjuvannja[index_language][INDEX_V];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_SETPOINT_AVR_MIN1_COMMA, 0);
          }
          else if ((index_of_ekran>>1) == INDEX_ML_STPAVR_MAX1)
          {
            if (
                ((j < COL_SETPOINT_AVR_MAX1_BEGIN) ||  (j > COL_SETPOINT_AVR_MAX1_END ))  &&
                (j != (COL_SETPOINT_AVR_MAX1_END + 2))  
               )working_ekran[i][j] = ' ';
            else if (j == COL_SETPOINT_AVR_MAX1_COMMA )working_ekran[i][j] = ',';
            else if (j == (COL_SETPOINT_AVR_MAX1_END + 2)) working_ekran[i][j] = odynyci_vymirjuvannja[index_language][INDEX_V];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_SETPOINT_AVR_MAX1_COMMA, 0);
          }
          else if ((index_of_ekran>>1) == INDEX_ML_STPAVR_MIN2)
          {
            if (
                ((j < COL_SETPOINT_AVR_MIN2_BEGIN) ||  (j > COL_SETPOINT_AVR_MIN2_END )) &&
                (j != (COL_SETPOINT_AVR_MIN2_END + 2))  
               )working_ekran[i][j] = ' ';
            else if (j == COL_SETPOINT_AVR_MIN2_COMMA )working_ekran[i][j] = ',';
            else if (j == (COL_SETPOINT_AVR_MIN2_END + 2)) working_ekran[i][j] = odynyci_vymirjuvannja[index_language][INDEX_V];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_SETPOINT_AVR_MIN2_COMMA, 0);
          }
          else if ((index_of_ekran>>1) == INDEX_ML_STPAVR_MAX2)
          {
            if (
                ((j < COL_SETPOINT_AVR_MAX2_BEGIN) ||  (j > COL_SETPOINT_AVR_MAX2_END ))  &&
                (j != (COL_SETPOINT_AVR_MAX2_END + 2))  
               )working_ekran[i][j] = ' ';
            else if (j == COL_SETPOINT_AVR_MAX2_COMMA )working_ekran[i][j] = ',';
            else if (j == (COL_SETPOINT_AVR_MAX2_END + 2)) working_ekran[i][j] = odynyci_vymirjuvannja[index_language][INDEX_V];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_SETPOINT_AVR_MAX2_COMMA, 0);
          }
          else if ((index_of_ekran>>1) == INDEX_ML_STPAVR_MAX_KRATN)
          {
            if ((j < COL_SETPOINT_AVR_MAX_KRATN_BEGIN) ||  (j > COL_SETPOINT_AVR_MAX_KRATN_END ))working_ekran[i][j] = ' ';
            else
              calc_int_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol);
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
    if (current_ekran.index_position == INDEX_ML_STPAVR_MIN1)
    {
      current_ekran.position_cursor_x = COL_SETPOINT_AVR_MIN1_BEGIN;
      last_position_cursor_x = COL_SETPOINT_AVR_MIN1_END;
    }
    else if (current_ekran.index_position == INDEX_ML_STPAVR_MAX1)
    {
      current_ekran.position_cursor_x = COL_SETPOINT_AVR_MAX1_BEGIN;
      last_position_cursor_x = COL_SETPOINT_AVR_MAX1_END;
    }
    else if (current_ekran.index_position == INDEX_ML_STPAVR_MIN2) 
    {
      current_ekran.position_cursor_x = COL_SETPOINT_AVR_MIN2_BEGIN;
      last_position_cursor_x = COL_SETPOINT_AVR_MIN2_END;
    }
    else if (current_ekran.index_position == INDEX_ML_STPAVR_MAX2)
    {
      current_ekran.position_cursor_x = COL_SETPOINT_AVR_MAX2_BEGIN;
      last_position_cursor_x = COL_SETPOINT_AVR_MAX2_END;
    }
    else if (current_ekran.index_position == INDEX_ML_STPAVR_MAX_KRATN) 
    {
      current_ekran.position_cursor_x = COL_SETPOINT_AVR_MAX_KRATN_BEGIN;
      last_position_cursor_x = COL_SETPOINT_AVR_MAX_KRATN_END;
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
//������� ����� ����������� �������� ���
/*****************************************************/
void make_ekran_timeout_avr(unsigned int group)
{
  const unsigned char name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_TIMEOUT_AVR][MAX_COL_LCD] = 
  {
    {
      "    � ��� ��    ",
      "    � ��� ��    ",
      "   � ���.���    ",
      "  � ���.��.���  "
    },
    {
      "    � ��� ��    ",
      "    � ��� ��    ",
      "   � ���.���    ",
      "  � ��.��.���   "
    },
    {
      "    � ��� ��    ",
      "    � ��� ��    ",
      "   � ���.���    ",
      "  � ���.��.���  "
    },
    {
      "    � ��� ��    ",
      "    � ��� ��    ",
      "   � ���.���    ",
      "  � ���.��.���  "
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
    if (index_of_ekran < (MAX_ROW_FOR_TIMEOUT_AVR<<1))//�������� �� ��� ��������� MAX_ROW_FOR_TIMEOUT_AVR ������� ��� ����, �� �� ���� ������� �� ������������� ��� ����� (����� + ��������)
    {
      if ((i & 0x1) == 0)
      {
        //� ��������� ����� ����� �������� ���������
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][index_of_ekran>>1][j];
        if ((index_of_ekran>>1) == INDEX_ML_TMOAVR_OL)
        {
          vaga = 10000; //������������ ������� ���������� ��� �������� �������� ������� ��� ��������
          if (current_ekran.edition == 0) value = current_settings.timeout_avr_ol[group]; //� ����� value ������� �������� ��������
          else value = edition_settings.timeout_avr_ol[group];
          first_symbol = 0; //�������, �� �� ����� �������� ������ �� ���������
        }
        else if ((index_of_ekran>>1) == INDEX_ML_TMOAVR_RL)
        {
          vaga = 10000; //������������ ������� ���������� ��� �������� �������� ������� ��� ��������
          if (current_ekran.edition == 0) value = current_settings.timeout_avr_rl[group]; //� ����� value ������� �������� ��������
          else value = edition_settings.timeout_avr_rl[group];
          first_symbol = 0; //�������, �� �� ����� �������� ������ �� ���������
        }
        else if ((index_of_ekran>>1) == INDEX_ML_TMOAVR_ZAVERSHENNJA)
        {
          vaga = 100000; //������������ ������� ���������� ��� �������� �������� ������� ��� ��������
          if (current_ekran.edition == 0) value = current_settings.timeout_avr_zavershennja[group]; //� ����� value ������� �������� ��������
          else value = edition_settings.timeout_avr_zavershennja[group];
          first_symbol = 0; //�������, �� �� ����� �������� ������ �� ���������
        }
        else if ((index_of_ekran>>1) == INDEX_ML_TMOAVR_RESET_BLK)
        {
          vaga = 10000; //������������ ������� ���������� ��� �������� �������� ������� ��� ��������
          if (current_ekran.edition == 0) value = current_settings.timeout_avr_reset_blk[group]; //� ����� value ������� �������� ��������
          else value = edition_settings.timeout_avr_reset_blk[group];
          first_symbol = 0; //�������, �� �� ����� �������� ������ �� ���������
        }
      }
      else
      {
        //� ������� ����� ����� �������� �������� �������
        for (unsigned int j = 0; j<MAX_COL_LCD; j++)
        {
          if ((index_of_ekran>>1) == INDEX_ML_TMOAVR_OL)
          {
            if (
                ((j < COL_TMO_AVR_OL_BEGIN) ||  (j > COL_TMO_AVR_OL_END )) &&
                (j != (COL_TMO_AVR_OL_END + 2))  
               )working_ekran[i][j] = ' ';
            else if (j == COL_TMO_AVR_OL_COMMA )working_ekran[i][j] = ',';
            else if (j == (COL_TMO_AVR_OL_END + 2)) working_ekran[i][j] = odynyci_vymirjuvannja[index_language][INDEX_SECOND];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_TMO_AVR_OL_COMMA, 0);
          }
          else if ((index_of_ekran>>1) == INDEX_ML_TMOAVR_RL)
          {
            if (
                ((j < COL_TMO_AVR_RL_BEGIN) ||  (j > COL_TMO_AVR_RL_END )) &&
                (j != (COL_TMO_AVR_RL_END + 2))  
               )working_ekran[i][j] = ' ';
            else if (j == COL_TMO_AVR_RL_COMMA )working_ekran[i][j] = ',';
            else if (j == (COL_TMO_AVR_RL_END + 2)) working_ekran[i][j] = odynyci_vymirjuvannja[index_language][INDEX_SECOND];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_TMO_AVR_RL_COMMA, 0);
          }
          else if ((index_of_ekran>>1) == INDEX_ML_TMOAVR_ZAVERSHENNJA)
          {
            if (
                ((j < COL_TMO_AVR_ZAVERSHENNJA_BEGIN) ||  (j > COL_TMO_AVR_ZAVERSHENNJA_END )) &&
                (j != (COL_TMO_AVR_ZAVERSHENNJA_END + 2))  
               )working_ekran[i][j] = ' ';
            else if (j == COL_TMO_AVR_ZAVERSHENNJA_COMMA )working_ekran[i][j] = ',';
            else if (j == (COL_TMO_AVR_ZAVERSHENNJA_END + 2)) working_ekran[i][j] = odynyci_vymirjuvannja[index_language][INDEX_SECOND];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_TMO_AVR_ZAVERSHENNJA_COMMA, 0);
          }
          else if ((index_of_ekran>>1) == INDEX_ML_TMOAVR_RESET_BLK)
          {
            if (
                ((j < COL_TMO_AVR_RESET_BLK_BEGIN) ||  (j > COL_TMO_AVR_RESET_BLK_END )) &&
                (j != (COL_TMO_AVR_RESET_BLK_END + 2))  
               )working_ekran[i][j] = ' ';
            else if (j == COL_TMO_AVR_RESET_BLK_COMMA )working_ekran[i][j] = ',';
            else if (j == (COL_TMO_AVR_RESET_BLK_END + 2)) working_ekran[i][j] = odynyci_vymirjuvannja[index_language][INDEX_SECOND];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_TMO_AVR_RESET_BLK_COMMA, 0);
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
    if (current_ekran.index_position == INDEX_ML_TMOAVR_OL) 
    {
      current_ekran.position_cursor_x = COL_TMO_AVR_OL_BEGIN;
      last_position_cursor_x = COL_TMO_AVR_OL_END;
    }
    else if (current_ekran.index_position == INDEX_ML_TMOAVR_RL) 
    {
      current_ekran.position_cursor_x = COL_TMO_AVR_RL_BEGIN;
      last_position_cursor_x = COL_TMO_AVR_RL_END;
    }
    else if (current_ekran.index_position == INDEX_ML_TMOAVR_ZAVERSHENNJA) 
    {
      current_ekran.position_cursor_x = COL_TMO_AVR_ZAVERSHENNJA_BEGIN;
      last_position_cursor_x = COL_TMO_AVR_ZAVERSHENNJA_END;
    }
    else if (current_ekran.index_position == INDEX_ML_TMOAVR_RESET_BLK) 
    {
      current_ekran.position_cursor_x = COL_TMO_AVR_RESET_BLK_BEGIN;
      last_position_cursor_x = COL_TMO_AVR_RESET_BLK_END;
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
//������� ����� ����������� �������� ����������� ���������� ��� ���
/*****************************************************/
void make_ekran_control_avr()
{
  const unsigned char name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_CONTROL_AVR][MAX_COL_LCD] = 
  {
    {
      "      ���       ",
      "����.�.��� �� �."
    },
    {
      "      ���       ",
      "����.�.��� �� �"
    },
    {
      "      ���       ",
      "����.�.��� �� �."
    },
    {
      "      ���       ",
      "����.�.��� �� �."
    }
  };
  int index_language = index_language_in_array(current_settings.language);
  
  unsigned int position_temp = current_ekran.index_position;
  unsigned int index_of_ekran;
  
  //�������� �� ��� �������� position_temp ������� ��� ����, �� �� ���� ������� �� ������������� ��� ����� (����� + ��������)
  index_of_ekran = ((position_temp<<1) >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;

  
  for (unsigned int i=0; i< MAX_ROW_LCD; i++)
  {
    if (index_of_ekran < (MAX_ROW_FOR_CONTROL_AVR<<1))//�������� �� ��� ��������� MAX_ROW_FOR_CONTROL_AVR ������� ��� ����, �� �� ���� ������� �� ������������� ��� ����� (����� + ��������)
    {
      if ((i & 0x1) == 0)
      {
        //� ��������� ����� ����� �������� ���������
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][index_of_ekran>>1][j];
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

        unsigned int temp_data;
        if(current_ekran.edition == 0) temp_data = current_settings.control_avr;
        else temp_data = edition_settings.control_avr;
          
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
