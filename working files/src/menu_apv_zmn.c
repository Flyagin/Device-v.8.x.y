#include "header.h"

/*****************************************************/
//������� ����� ����������� ������� ���-���
/*****************************************************/
void make_ekran_setpoint_apv_zmn(unsigned int group)
{
  const unsigned char name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_SETPOINT_APV_ZMN][MAX_COL_LCD] = 
  {
    {
      " ���.U ��� ���1 ",
      " ���.U ��� ���2 ",
      " �����. ��� ��� "
    },
    {
      " ���.U ��� ���1 ",
      " ���.U ��� ���2 ",
      " �����. ��� ��� "
    },
    {
      " ���.U ��� ���1 ",
      " ���.U ��� ���2 ",
      " �����. ��� ��� "
    },
    {
      " ���.U ��� ���1 ",
      " ���.U ��� ���2 ",
      " �����. ��� ��� "
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
    if (index_of_ekran < (MAX_ROW_FOR_SETPOINT_APV_ZMN<<1))//�������� �� ��� ��������� MAX_ROW_FOR_SETPOINT_APV_ZMN ������� ��� ����, �� ����� ������� �� ������������� ��� ����� (����� + ��������)
    {
      if ((i & 0x1) == 0)
      {
        //� ��������� ����� ����� �������� ���������
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][index_of_ekran>>1][j];
        if ((index_of_ekran>>1) == INDEX_ML_STPAPV_ZMN1)
        {
          vaga = 100000; //������������ ������� ���������� ��� �������� �������� ������� ��� �������
          if (current_ekran.edition == 0) value = current_settings.setpoint_apv_zmn1[group]; //� ����� value ������� �������� �������
          else value = edition_settings.setpoint_apv_zmn1[group];
          first_symbol = 0; //�������, �� �� ������ �������� ������ �� ���������
        }
        else if ((index_of_ekran>>1) == INDEX_ML_STPAPV_ZMN2)
        {
          vaga = 100000; //������������ ������� ���������� ��� �������� �������� ������� ��� �������
          if (current_ekran.edition == 0) value = current_settings.setpoint_apv_zmn2[group]; //� ����� value ������� �������� �������
          else value = edition_settings.setpoint_apv_zmn2[group];
          first_symbol = 0; //�������, �� �� ������ �������� ������ �� ���������
        }
        else if ((index_of_ekran>>1) == INDEX_ML_STPAPV_ZMN_MAX_KRATN)
        {
          vaga = 100; //������������ ������� ���������� ��� �������� �������� ������� ��� �������
          if (current_ekran.edition == 0) value = current_settings.setpoint_kratn_apv_zmn[group]; //� ����� value ������� �������� �������
          else value = edition_settings.setpoint_kratn_apv_zmn[group];
          first_symbol = 0; //�������, �� �� ������ �������� ������ �� ���������
        }
      }
      else
      {
        //� ������� ����� ����� �������� �������� �������
        for (unsigned int j = 0; j<MAX_COL_LCD; j++)
        {
          if ((index_of_ekran>>1) == INDEX_ML_STPAPV_ZMN1)
          {
            if (
                ((j < COL_SETPOINT_APV_ZMN1_BEGIN) ||  (j > COL_SETPOINT_APV_ZMN1_END ))  &&
                (j != (COL_SETPOINT_APV_ZMN1_END + 2))  
               )working_ekran[i][j] = ' ';
            else if (j == COL_SETPOINT_APV_ZMN1_COMMA )working_ekran[i][j] = ',';
            else if (j == (COL_SETPOINT_APV_ZMN1_END + 2)) working_ekran[i][j] = odynyci_vymirjuvannja[index_language][INDEX_V];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_SETPOINT_APV_ZMN1_COMMA, 0);
          }
          else if ((index_of_ekran>>1) == INDEX_ML_STPAPV_ZMN2)
          {
            if (
                ((j < COL_SETPOINT_APV_ZMN2_BEGIN) ||  (j > COL_SETPOINT_APV_ZMN2_END )) &&
                (j != (COL_SETPOINT_APV_ZMN2_END + 2))  
               )working_ekran[i][j] = ' ';
            else if (j == COL_SETPOINT_APV_ZMN2_COMMA )working_ekran[i][j] = ',';
            else if (j == (COL_SETPOINT_APV_ZMN2_END + 2)) working_ekran[i][j] = odynyci_vymirjuvannja[index_language][INDEX_V];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_SETPOINT_APV_ZMN2_COMMA, 0);
          }
          else if ((index_of_ekran>>1) == INDEX_ML_STPAPV_ZMN_MAX_KRATN)
          {
            if ((j < COL_SETPOINT_APV_ZMN_MAX_KRATN_BEGIN) ||  (j > COL_SETPOINT_APV_ZMN_MAX_KRATN_END ))working_ekran[i][j] = ' ';
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
    if (current_ekran.index_position == INDEX_ML_STPAPV_ZMN1)
    {
      current_ekran.position_cursor_x = COL_SETPOINT_APV_ZMN1_BEGIN;
      last_position_cursor_x = COL_SETPOINT_APV_ZMN1_END;
    }
    else if (current_ekran.index_position == INDEX_ML_STPAPV_ZMN2) 
    {
      current_ekran.position_cursor_x = COL_SETPOINT_APV_ZMN2_BEGIN;
      last_position_cursor_x = COL_SETPOINT_APV_ZMN2_END;
    }
    else if (current_ekran.index_position == INDEX_ML_STPAPV_ZMN_MAX_KRATN) 
    {
      current_ekran.position_cursor_x = COL_SETPOINT_APV_ZMN_MAX_KRATN_BEGIN;
      last_position_cursor_x = COL_SETPOINT_APV_ZMN_MAX_KRATN_END;
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
  //�������� �������� ���� �����
  current_ekran.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
//������� ����� ����������� �������� ���-���
/*****************************************************/
void make_ekran_timeout_apv_zmn(unsigned int group)
{
  const unsigned char name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_TIMEOUT_APV_ZMN][MAX_COL_LCD] = 
  {
    {
      "  � ��� ��� 1   ",
      "  � ��� ��� 2   ",
      " � ���.��� ���  "
    },
    {
      "  � ��� ��� 1   ",
      "  � ��� ��� 2   ",
      " � ���.��� ���  "
    },
    {
      "  � ��� ��� 1   ",
      "  � ��� ��� 2   ",
      " � ���.��� ���  "
    },
    {
      "  � ��� ��� 1   ",
      "  � ��� ��� 2   ",
      " � ���.��� ���  "
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
    if (index_of_ekran < (MAX_ROW_FOR_TIMEOUT_APV_ZMN<<1))//�������� �� ��� ��������� MAX_ROW_FOR_TIMEOUT_APV_ZMN ������� ��� ����, �� �� ���� ������� �� ������������� ��� ����� (����� + ��������)
    {
      if ((i & 0x1) == 0)
      {
        //� ��������� ����� ����� �������� ���������
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][index_of_ekran>>1][j];
        if ((index_of_ekran>>1) == INDEX_ML_TMOAPV_ZMN1)
        {
          vaga = 10000; //������������ ������� ���������� ��� �������� �������� ������� ��� ��������
          if (current_ekran.edition == 0) value = current_settings.timeout_apv_zmn_1[group]; //� ����� value ������� �������� ��������
          else value = edition_settings.timeout_apv_zmn_1[group];
          first_symbol = 0; //�������, �� �� ������ �������� ������ �� ���������
        }
        else if ((index_of_ekran>>1) == INDEX_ML_TMOAPV_ZMN2)
        {
          vaga = 10000; //������������ ������� ���������� ��� �������� �������� ������� ��� ��������
          if (current_ekran.edition == 0) value = current_settings.timeout_apv_zmn_2[group]; //� ����� value ������� �������� ��������
          else value = edition_settings.timeout_apv_zmn_2[group];
          first_symbol = 0; //�������, �� �� ������ �������� ������ �� ���������
        }
        else if ((index_of_ekran>>1) == INDEX_ML_TMOAPV_ZMN_ZAVERSHENNJA)
        {
          vaga = 100000; //������������ ������� ���������� ��� �������� �������� ������� ��� ��������
          if (current_ekran.edition == 0) value = current_settings.timeout_apv_zmn_zavershennja[group]; //� ����� value ������� �������� ��������
          else value = edition_settings.timeout_apv_zmn_zavershennja[group];
          first_symbol = 0; //�������, �� �� ������ �������� ������ �� ���������
        }
      }
      else
      {
        //� ������� ����� ����� �������� �������� �������
        for (unsigned int j = 0; j<MAX_COL_LCD; j++)
        {
          if ((index_of_ekran>>1) == INDEX_ML_TMOAPV_ZMN1)
          {
            if (
                ((j < COL_TMO_APV_ZMN1_BEGIN) ||  (j > COL_TMO_APV_ZMN1_END )) &&
                (j != (COL_TMO_APV_ZMN1_END + 2))  
               )working_ekran[i][j] = ' ';
            else if (j == COL_TMO_APV_ZMN1_COMMA )working_ekran[i][j] = ',';
            else if (j == (COL_TMO_APV_ZMN1_END + 2)) working_ekran[i][j] = odynyci_vymirjuvannja[index_language][INDEX_SECOND];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_TMO_APV_ZMN1_COMMA, 0);
          }
          else if ((index_of_ekran>>1) == INDEX_ML_TMOAPV_ZMN2)
          {
            if (
                ((j < COL_TMO_APV_ZMN2_BEGIN) ||  (j > COL_TMO_APV_ZMN2_END )) &&
                (j != (COL_TMO_APV_ZMN2_END + 2))  
               )working_ekran[i][j] = ' ';
            else if (j == COL_TMO_APV_ZMN2_COMMA )working_ekran[i][j] = ',';
            else if (j == (COL_TMO_APV_ZMN2_END + 2)) working_ekran[i][j] = odynyci_vymirjuvannja[index_language][INDEX_SECOND];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_TMO_APV_ZMN2_COMMA, 0);
          }
          else if ((index_of_ekran>>1) == INDEX_ML_TMOAPV_ZMN_ZAVERSHENNJA)
          {
            if (
                ((j < COL_TMO_APV_ZMN_ZAVERSHENNJA_BEGIN) ||  (j > COL_TMO_APV_ZMN_ZAVERSHENNJA_END )) &&
                (j != (COL_TMO_APV_ZMN_ZAVERSHENNJA_END + 2))  
               )working_ekran[i][j] = ' ';
            else if (j == COL_TMO_APV_ZMN_ZAVERSHENNJA_COMMA )working_ekran[i][j] = ',';
            else if (j == (COL_TMO_APV_ZMN_ZAVERSHENNJA_END + 2)) working_ekran[i][j] = odynyci_vymirjuvannja[index_language][INDEX_SECOND];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_TMO_APV_ZMN_ZAVERSHENNJA_COMMA, 0);
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
    if (current_ekran.index_position == INDEX_ML_TMOAPV_ZMN1) 
    {
      current_ekran.position_cursor_x = COL_TMO_APV_ZMN1_BEGIN;
      last_position_cursor_x = COL_TMO_APV_ZMN1_END;
    }
    else if (current_ekran.index_position == INDEX_ML_TMOAPV_ZMN2) 
    {
      current_ekran.position_cursor_x = COL_TMO_APV_ZMN2_BEGIN;
      last_position_cursor_x = COL_TMO_APV_ZMN2_END;
    }
    else if (current_ekran.index_position == INDEX_ML_TMOAPV_ZMN_ZAVERSHENNJA) 
    {
      current_ekran.position_cursor_x = COL_TMO_APV_ZMN_ZAVERSHENNJA_BEGIN;
      last_position_cursor_x = COL_TMO_APV_ZMN_ZAVERSHENNJA_END;
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
  //�������� �������� ���� �����
  current_ekran.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
//������� ����� ����������� �������� ����������� ���������� ��� ���-���
/*****************************************************/
void make_ekran_control_apv_zmn()
{
  const unsigned char name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_CONTROL_APV_ZMN][MAX_COL_LCD] = 
  {
    {
      "    ���-���     "
    },
    {
      "    ���-���     "
    },
    {
      "    ���-���     "
    },
    {
      "    ���-���     "
    }
  };
  int index_language = index_language_in_array(current_settings.language);
  
  unsigned int position_temp = current_ekran.index_position;
  unsigned int index_of_ekran;
  
  //�������� �� ��� �������� position_temp ������� ��� ����, �� �� ���� ������� �� ������������� ��� ����� (����� + ��������)
  index_of_ekran = ((position_temp<<1) >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;

  
  for (unsigned int i=0; i< MAX_ROW_LCD; i++)
  {
    if (index_of_ekran < (MAX_ROW_FOR_CONTROL_APV_ZMN<<1))//�������� �� ��� ��������� MAX_ROW_FOR_CONTROL_APV_ZMN ������� ��� ����, �� �� ���� ������� �� ������������� ��� ����� (����� + ��������)
    {
      if ((i & 0x1) == 0)
      {
        //� ��������� ����� ����� �������� ���������
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][index_of_ekran>>1][j];
      }
      else
      {
        //� ������� ����� ����� �������� �������� �������
        const unsigned char information[MAX_ROW_FOR_CONTROL_APV_ZMN][MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD] = 
        {
          {
            {"     ����.      ", "      ���.      "},
            {"     ����.      ", "     ����.     "},
            {"      Off       ", "       On       "},
            {"     њ��.      ", "     ����.      "}
          }
        };
        const unsigned int cursor_x[MAX_ROW_FOR_CONTROL_APV_ZMN][MAX_NAMBER_LANGUAGE][2] = 
        {
          {
            {4, 5},
            {4, 4},
            {5, 6},
            {4, 4}
          }
        };
        
        unsigned int index_ctr = (index_of_ekran>>1);

        unsigned int temp_data;
        if(current_ekran.edition == 0) temp_data = current_settings.control_apv_zmn;
        else temp_data = edition_settings.control_apv_zmn;
          
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = information[index_ctr][index_language][(temp_data >> index_ctr) & 0x1][j];
        current_ekran.position_cursor_x = cursor_x[index_ctr][index_language][(temp_data >> index_ctr) & 0x1];
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
  //�������� �������� ���� �����
  current_ekran.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
//
/*****************************************************/
/*****************************************************/
