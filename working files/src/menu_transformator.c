#include "header.h"

/*****************************************************/
//������������ ������ ������� � �������� ���� � ������� �����
/*****************************************************/
void calc_int_symbol_and_put_into_working_ekran(unsigned char* point_in_working_ekran, unsigned int* point_value, unsigned int* point_vaga, unsigned int* point_first_symbol)
{
  unsigned int temp_data;
  temp_data = (*point_value) / (*point_vaga); //�������� �����, ��� ����� ����������� � ������ � �������� � ���� ������� ������
  *point_value %= *(point_vaga); //���������� ����� ��� �������, ���� �� ����� ������ �������� �� �����
  *point_vaga /=10; //�������� ������� ���������� � 10 ����
  if(current_ekran.edition != 0) *point_in_working_ekran = temp_data + 0x30;
  else
  {
    //� �������, ���� �� �� � ����� �����������, �� ��� ����� ���������� �������� ������ ���������
    if ((temp_data !=0) || ((*point_first_symbol) != 0))
    {
      *point_in_working_ekran = temp_data + 0x30;
      if ((*point_first_symbol) == 0) *point_first_symbol = 1;
    }
    else
    {
      //���� �������� ����� � ���� �������, ���� �� � ������ ������� ����� (������ ���� ����� ���� 1)
      if ((*point_vaga) >= 1 ) *point_in_working_ekran = ' ';
      else
      {
        *point_in_working_ekran = temp_data + 0x30;
        if ((*point_first_symbol) == 0) *point_first_symbol = 1;
      }
    }
  }
}
/*****************************************************/

/*****************************************************/
//������� ����� ����������� ����������� �������������
/*****************************************************/
void make_ekran_transformator()
{
  const unsigned char name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_TRANSFORMATOR_INFO][MAX_COL_LCD] = 
  {
    {
      " ����.������.�0 ",
      " ����.������.�� ",
      " ����.������.�� "
    },
    {
      " ����.������.�0 ",
      " ����.������.�� ",
      " ����.������.�� "
    },
    {
      "  3I0 T Ratio   ",
      "    CT Ratio    ",
      "    VT Ratio    "
    },
    {
      " ����.������.�0 ",
      " ����.������.�� ",
      " ����.������.�� "
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
    if (index_of_ekran < (MAX_ROW_FOR_TRANSFORMATOR_INFO<<1))//�������� �� ��� ��������� MAX_ROW_FOR_TRANSFORMATOR_INFO ������� ��� ����, �� ����� ������� �� ������������� ��� ����� (����� + ��������)
    {
      if ((i & 0x1) == 0)
      {
        //� ��������� ����� ����� �������� ���������
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][index_of_ekran>>1][j];
        if ((index_of_ekran>>1) == INDEX_ML_T0)
        {
          vaga = 100; //������������ ������� ���������� ��� ����������� ������������� T0
          if (current_ekran.edition == 0) value = current_settings.T0; //� ����� value ������� �������� ����������� ������������� T0
          else value = edition_settings.T0;
          first_symbol = 0; //�������, �� �� ����� �������� ������ �� ���������
        }
        else if ((index_of_ekran>>1) == INDEX_ML_TT)
        {
          vaga = 1000; //������������ ������� ���������� ��� ����������� ������������� TT
          if (current_ekran.edition == 0) value = current_settings.TCurrent; //� ����� value ������� �������� ���������� ������������� TT
          else value = edition_settings.TCurrent;
          first_symbol = 0; //�������, �� �� ����� �������� ������ �� ���������
        }
        else if ((index_of_ekran>>1) == INDEX_ML_TN)
        {
          vaga = 100; //������������ ������� ���������� ��� ����������� ������������� T�
          if (current_ekran.edition == 0) value = current_settings.TVoltage; //� ����� value ������� �������� ����������� ������������� T�
          else value = edition_settings.TVoltage;
          first_symbol = 0; //�������, �� �� ����� �������� ������ �� ���������
        }
      }
      else 
      {
        //� ������� ����� ����� �������� �������� �������
        for (unsigned int j = 0; j<MAX_COL_LCD; j++)
        {
          if ((index_of_ekran>>1) == INDEX_ML_T0)
          {
            if ((j < COL_T0_BEGIN) ||  (j > COL_T0_END ))working_ekran[i][j] = ' ';
            else
              calc_int_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol);
          }
          else if ((index_of_ekran>>1) == INDEX_ML_TT)
          {
            if ((j < COL_TT_BEGIN) ||  (j > COL_TT_END ))working_ekran[i][j] = ' ';
            else
              calc_int_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol);
          }
          else if ((index_of_ekran>>1) == INDEX_ML_TN)
          {
            if ((j < COL_TN_BEGIN) ||  (j > COL_TN_END ))working_ekran[i][j] = ' ';
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
    if (current_ekran.index_position == INDEX_ML_T0)
    {
      current_ekran.position_cursor_x = COL_T0_BEGIN;
      last_position_cursor_x = COL_T0_END;
    }
    else if (current_ekran.index_position == INDEX_ML_TT)
    {
      current_ekran.position_cursor_x = COL_TT_BEGIN;
      last_position_cursor_x = COL_TT_END;
    }
    else if (current_ekran.index_position == INDEX_ML_TN)
    {
      current_ekran.position_cursor_x = COL_TN_BEGIN;
      last_position_cursor_x = COL_TN_END;
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
//
/*****************************************************/
/*****************************************************/
