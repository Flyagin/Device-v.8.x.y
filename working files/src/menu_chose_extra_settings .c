#include "header.h"

/*****************************************************/
//������� ����� ����������� ��������� ���������
/*****************************************************/
void make_ekran_chose_extra_settings(void)
{
  const unsigned char name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_CHOSE_EXTRA_SETTINGS][MAX_COL_LCD] = 
  {
    {
      "  3U0/Ubc-��2   ",
      " ��.����������  ",
      "��.���.� �� �� �",
      " ���.�� ������. ",
      " �����.���.��   ",
      " ��.���.�� �� ��",
      "��.����.�� �� ��"
    },
    {
      "  3U0/Ubc-��2   ",
      " ����� ������� ",
      "��.���.�� �� �.�",
      "���.��� �������.",
      " �����.���.��   ",
      " ��.����.�� ��",
      " ��.����.�� �� "
    },
    {
      "  3U0/Ubc-��2   ",
      " ��.����������  ",
      "��.���.� �� �� �",
      " ���.�� ������. ",
      " FK activ.Ctrl  ",
      " Blc.On CB fr.DI", 
      "Blc.Off CB fr.DI"
    },
    {
      "  3U0/Ubc-��2   ",
      " ��.����������  ",
      "��.���.� �� �� �",
      " ���.�� ������. ",
      " �����.���.��   ",
      " ��.���.�� �� ��",
      "��.����.�� �� ��"
    },
  };
  int index_language = index_language_in_array(current_settings.language);
  
  unsigned int position_temp = current_ekran.index_position;
  unsigned int index_of_ekran;
  
  //�������� �� ��� �������� position_temp ������� ��� ����, �� �� ���� ������� �� ������������� ��� ����� (����� + ��������)
  index_of_ekran = ((position_temp<<1) >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;
  
  for (unsigned int i=0; i< MAX_ROW_LCD; i++)
  {
    if (index_of_ekran < (MAX_ROW_FOR_CHOSE_EXTRA_SETTINGS<<1))//�������� �� ��� ��������� MAX_ROW_FOR_CHOSE_EXTRA_SETTINGS ������� ��� ����, �� �� ���� ������� �� ������������� ��� ����� (����� + ��������)
    {
      if ((i & 0x1) == 0)
      {
        //� ��������� ����� ����� �������� ���������
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][index_of_ekran>>1][j];
      }
      else
      {
        //� ������� ����� ����� �������� ����
        const unsigned char information[MAX_ROW_FOR_CHOSE_EXTRA_SETTINGS][MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD] = 
        {
          {
            {"      3U0       ", "    Ubc-��2     "},
            {"      3U0       ", "    Ubc-��2     "},
            {"      3U0       ", "    Ubc-��2     "},
            {"      3U0       ", "    Ubc-��2     "}
          },
          {
            {"     ������     ", "    ��������    "},
            {"     ����      ", "    ˳���     "},
            {"     ������     ", "    ��������    "},
            {"     ������     ", "    ��������    "}
          },
          {
            {"     ����.      ", "      ���.      "},
            {"     ����.      ", "     ����.     "},
            {"      Off       ", "       On       "},
            {"     њ��.      ", "     ����.      "}
          },
          {
            {"     ����.      ", "      ���.      "},
            {"     ����.      ", "     ����.     "},
            {"      Off       ", "       On       "},
            {"     њ��.      ", "     ����.      "}
          },
          {
            {"     ����.      ", "      ���.      "},
            {"     ����.      ", "     ����.     "},
            {"      Off       ", "       On       "},
            {"     њ��.      ", "     ����.      "}
          },
          {
            {"     ����.      ", "      ���.      "},
            {"     ����.      ", "     ����.     "},
            {"      Off       ", "       On       "},
            {"     њ��.      ", "     ����.      "}
          },
          {
            {"     ����.      ", "      ���.      "},
            {"     ����.      ", "     ����.     "},
            {"      Off       ", "       On       "},
            {"     њ��.      ", "     ����.      "}
          }
        };
        const unsigned int cursor_x[MAX_ROW_FOR_CHOSE_EXTRA_SETTINGS][MAX_NAMBER_LANGUAGE][2] = 
        {
          {
            {5, 3},
            {5, 3},
            {5, 3},
            {5, 3}
          },
          {
            {4, 3},
            {4, 3},
            {4, 3},
            {4, 3}
          },
          {
            {4, 5},
            {4, 4},
            {5, 6},
            {4, 4}
          },
          {
            {4, 5},
            {4, 4},
            {5, 6},
            {4, 4}
          },
          {
            {4, 5},
            {4, 4},
            {5, 6},
            {4, 4}
          },
          {
            {4, 5},
            {4, 4},
            {5, 6},
            {4, 4}
          },
          {
            {4, 5},
            {4, 4},
            {5, 6},
            {4, 4}
          }
        };
        
        unsigned int index_ctr = (index_of_ekran>>1);

        unsigned int temp_data;
        if(current_ekran.edition == 0) temp_data = current_settings.control_extra_settings_1;
        else temp_data = edition_settings.control_extra_settings_1;
          
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
  //�������� ������� ���� �����
  current_ekran.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
//
/*****************************************************/
/*****************************************************/
