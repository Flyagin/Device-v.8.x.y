#include "header.h"

/*****************************************************/
//������� ����� ����������� ���������� ��� ���������� �� �������
/*****************************************************/
void make_ekran_vidkluchenja(void)
{
  int index_language = index_language_in_array(current_settings.language);
  
  //������� ������� �����
  for (unsigned int i = 0; i < MAX_ROW_LCD; i++)
  {
    for (unsigned int j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = ' ';
  }
  unsigned char *point = info_vidkluchennja_vymykachatime[current_ekran.index_position];

  //����
  working_ekran[VIDKL_ROW_Y_][VIDKL_COL_DY1] = ((*(point + 4)) >>  4) + 0x30;
  working_ekran[VIDKL_ROW_Y_][VIDKL_COL_DY2] = ((*(point + 4)) & 0xf) + 0x30;
  working_ekran[VIDKL_ROW_Y_][VIDKL_COL_DY2 + 1] = '-';

  //̳����
  working_ekran[VIDKL_ROW_Y_][VIDKL_COL_MY1] = ((*(point + 5)) >>  4) + 0x30;
  working_ekran[VIDKL_ROW_Y_][VIDKL_COL_MY2] = ((*(point + 5)) & 0xf) + 0x30;
  working_ekran[VIDKL_ROW_Y_][VIDKL_COL_MY2 + 1] = '-';

  //г�
  working_ekran[VIDKL_ROW_Y_][VIDKL_COL_SY1] = ((*(point + 6)) >>  4) + 0x30;
  working_ekran[VIDKL_ROW_Y_][VIDKL_COL_SY2] = ((*(point + 6)) & 0xf) + 0x30;

  //������
  working_ekran[VIDKL_ROW_T_][VIDKL_COL_HT1] = ((*(point + 3)) >>  4) + 0x30;
  working_ekran[VIDKL_ROW_T_][VIDKL_COL_HT2] = ((*(point + 3)) & 0xf) + 0x30;
  working_ekran[VIDKL_ROW_T_][VIDKL_COL_HT2 + 1] = ':';

  //�������
  working_ekran[VIDKL_ROW_T_][VIDKL_COL_MT1] = ((*(point + 2)) >>  4) + 0x30;
  working_ekran[VIDKL_ROW_T_][VIDKL_COL_MT2] = ((*(point + 2)) & 0xf) + 0x30;
  working_ekran[VIDKL_ROW_T_][VIDKL_COL_MT2 + 1] = ':';

  //�������
  working_ekran[VIDKL_ROW_T_][VIDKL_COL_ST1] = ((*(point + 1)) >>  4) + 0x30;
  working_ekran[VIDKL_ROW_T_][VIDKL_COL_ST2] = ((*(point + 1)) & 0xf) + 0x30;
  working_ekran[VIDKL_ROW_T_][VIDKL_COL_ST2 + 1] = '.';

  //��� ������
  working_ekran[VIDKL_ROW_T_][VIDKL_COL_HST1] = ((*(point + 0)) >>  4) + 0x30;
  working_ekran[VIDKL_ROW_T_][VIDKL_COL_HST2] = ((*(point + 0)) & 0xf) + 0x30;
  
  const unsigned char information_1[MAX_NAMBER_LANGUAGE][VYMKNENNJA_VID_MAX_NUMBER][7] = 
  {
    {"   ���1", "   ���2", "   ���3", "   ���4", "    ���", "    3I0", "    3U0", "    ���", " ��� ��", "    ���", "  ����1", "  ����2", "    ���", " �����1", " �����2", "�����c1", "�����c2", "    ���", " ������"},
    {"   �C�1", "   �C�2", "   �C�3", "   �C�4", "    ���", "    3I0", "    3U0", "    ���", " ��� �.", "    ���", "  ����1", "  ����2", "    ���", " ����1", " ����2", "�����c1", "�����c2", "    ���", "   ����"},
    {"   OCP1", "   OCP2", "   OCP3", "   OCP4", "    ���", "    3I0", "    3U0", "    ���", " ��� f.", "    ���", "  CBFP1", "  CBFP2", "   NPSP", "  Umin1", "  Umin2", "  Umax1", "  Umax2", "    ���", "  Other"},
    {"   ���1", "   ���2", "   ���3", "   ���4", "    ���", "    3I0", "    3U0", "    ���", " ��� ��", "    ���", "  ����1", "  ����2", "    ���", " �����1", " �����2", "�����c1", "�����c2", "    ���", " ������"}
  };
  point = (unsigned char *)information_1[index_language][current_ekran.index_position];
  for (unsigned int i = 0; i < 7; i++) working_ekran[VIDKL_ROW_Y_][VIDKL_COL_SY2 + 2 + i] = *(point + i);
  
  const unsigned char information_2[MAX_NAMBER_LANGUAGE][VYMKNENNJA_VID_MAX_NUMBER][4] = 
  {
    {"    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "  ��", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    "},
    {"    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "  ��", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    "},
    {"    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "  DI", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    "},
    {"    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "  ��", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    ", "    "},
  };
  point = (unsigned char *)information_2[index_language][current_ekran.index_position];
  for (unsigned int i = 0; i < 4; i++) working_ekran[VIDKL_ROW_T_][VIDKL_COL_HST2 + 2 + i] = *(point + i);

  //������ �� ���������� ������������ �� ������ �������
  current_ekran.position_cursor_x = 0;
  current_ekran.position_cursor_y = 0;
  //������ ���������
  current_ekran.cursor_on = 0;
  //������ �� ����
  current_ekran.cursor_blinking_on = 0;
  //�������� ������� ���� �����
  current_ekran.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
//
/*****************************************************/
/*****************************************************/
