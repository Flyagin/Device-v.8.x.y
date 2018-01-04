#include "header.h"

/***********************************************************************************/
//��������� ����� �� CRC ����
/***********************************************************************************/
inline unsigned short int  AddCRC(unsigned char inpbyte, unsigned short int oldCRC)
{
  unsigned short int v,temp;
  int i;
  unsigned char bt,m;

  bt = inpbyte;
  v  = oldCRC;

  for (i=0; i<8;i++)
    {
      temp = v;
      v = v >> 1;
      m = bt >> i;
      if (((temp ^m) & 1)== 1) v = v ^ 0xa001;
    }
  return v;
}
/***********************************************************************************/

/***********************************************************************************/
//������� ������ �� ��������� Modbus-RTU �� �������
/***********************************************************************************/
inline void Error_modbus(unsigned int address, unsigned int function, unsigned int error, unsigned char *output_data)
  {
   unsigned short CRC_sum;

   *output_data       = address & 0xff;
   *(output_data + 1) = 0x80 | (function & 0xff);
   *(output_data + 2) = error & 0xff;

   CRC_sum = 0xffff;
   for (int index = 0; index < 3; index++) CRC_sum = AddCRC((*(output_data + index)) ,CRC_sum);
   *(output_data + 3)  = CRC_sum & 0xff;
   *(output_data + 4)  = CRC_sum >> 8;
   
  }
/***********************************************************************************/

/***********************************************************************************/
//���������� ������� �� ���������� �������� ��� "����������� ����� ���'��"
/***********************************************************************************/
void convert_order_list_function_to_gmm(unsigned int* input_array, unsigned short int* output_array)
{
  //����� �������
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_1_GRUPA_USTAVOK    , (BIT_MA_1_GRUPA_USTAVOK  - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_2_GRUPA_USTAVOK    , (BIT_MA_2_GRUPA_USTAVOK  - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_3_GRUPA_USTAVOK    , (BIT_MA_3_GRUPA_USTAVOK  - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_4_GRUPA_USTAVOK    , (BIT_MA_4_GRUPA_USTAVOK  - BIT_MA_CURRENT_AF_BASE));

  //���
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_BLOCK_MTZ1         , (BIT_MA_BLOCK_MTZ1          - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_MTZ1               , (BIT_MA_MTZ1                - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_PO_MTZ1            , (BIT_MA_PO_MTZ1             - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_PO_MTZPN1          , (BIT_MA_PO_MTZPN1           - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_PO_MTZN1_VPERED    , (BIT_MA_PO_MTZN1_VPERED     - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_PO_MTZN1_NAZAD     , (BIT_MA_PO_MTZN1_NAZAD      - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_SECTOR_VPERED_MTZN1, (BIT_MA_SECTOR_VPERED_MTZN1 - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_SECTOR_NAZAD_MTZN1 , (BIT_MA_SECTOR_NAZAD_MTZN1  - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_PO_U_MTZPN1        , (BIT_MA_PO_U_MTZPN1         - BIT_MA_CURRENT_AF_BASE));

  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_BLOCK_MTZ2         , (BIT_MA_BLOCK_MTZ2          - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_MTZ2               , (BIT_MA_MTZ2                - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_PO_MTZ2            , (BIT_MA_PO_MTZ2             - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_PO_MTZPN2          , (BIT_MA_PO_MTZPN2           - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_PO_MTZN2_VPERED    , (BIT_MA_PO_MTZN2_VPERED     - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_PO_MTZN2_NAZAD     , (BIT_MA_PO_MTZN2_NAZAD      - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_SECTOR_VPERED_MTZN2, (BIT_MA_SECTOR_VPERED_MTZN2 - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_SECTOR_NAZAD_MTZN2 , (BIT_MA_SECTOR_NAZAD_MTZN2  - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_PO_U_MTZPN2        , (BIT_MA_PO_U_MTZPN2         - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_BLOCK_USK_MTZ2     , (BIT_MA_BLOCK_USK_MTZ2      - BIT_MA_CURRENT_AF_BASE));

  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_BLOCK_MTZ3         , (BIT_MA_BLOCK_MTZ3          - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_MTZ3               , (BIT_MA_MTZ3                - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_PO_MTZ3            , (BIT_MA_PO_MTZ3             - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_PO_MTZPN3          , (BIT_MA_PO_MTZPN3           - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_PO_MTZN3_VPERED    , (BIT_MA_PO_MTZN3_VPERED     - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_PO_MTZN3_NAZAD     , (BIT_MA_PO_MTZN3_NAZAD      - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_SECTOR_VPERED_MTZN3, (BIT_MA_SECTOR_VPERED_MTZN3 - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_SECTOR_NAZAD_MTZN3 , (BIT_MA_SECTOR_NAZAD_MTZN3  - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_PO_U_MTZPN3        , (BIT_MA_PO_U_MTZPN3         - BIT_MA_CURRENT_AF_BASE));

  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_BLOCK_MTZ4         , (BIT_MA_BLOCK_MTZ4          - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_MTZ4               , (BIT_MA_MTZ4                - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_PO_MTZ4            , (BIT_MA_PO_MTZ4             - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_PO_MTZPN4          , (BIT_MA_PO_MTZPN4           - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_PO_MTZN4_VPERED    , (BIT_MA_PO_MTZN4_VPERED     - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_PO_MTZN4_NAZAD     , (BIT_MA_PO_MTZN4_NAZAD      - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_SECTOR_VPERED_MTZN4, (BIT_MA_SECTOR_VPERED_MTZN4 - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_SECTOR_NAZAD_MTZN4 , (BIT_MA_SECTOR_NAZAD_MTZN4  - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_PO_U_MTZPN4        , (BIT_MA_PO_U_MTZPN4         - BIT_MA_CURRENT_AF_BASE));

  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_PO_BLOCK_U_MTZN   , (BIT_MA_PO_BLOCK_U_MTZN      - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_NCN_MTZ            , (BIT_MA_NCN_MTZ             - BIT_MA_CURRENT_AF_BASE));

  //��
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_BLOCK_NZZ , (BIT_MA_BLOCK_NZZ  - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_PO_NZZ    , (BIT_MA_PO_NZZ     - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_NZZ       , (BIT_MA_NZZ        - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_PO_3I0    , (BIT_MA_PO_ZZ1_3I0 - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_3I0       , (BIT_MA_ZZ1_3I0    - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_PO_3U0    , (BIT_MA_PO_ZZ_3U0  - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_3U0       , (BIT_MA_ZZ_3U0     - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_SECTOR_NZZ, (BIT_MA_SECTOR_NZZ - BIT_MA_CURRENT_AF_BASE));

  //���
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_BLOCK_ZOP , (BIT_MA_BLOCK_ZOP  - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_ZOP       , (BIT_MA_ZOP        - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_PO_ZOP    , (BIT_MA_PO_ZOP     - BIT_MA_CURRENT_AF_BASE));
  
  //Umin
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_BLOCK_UMIN1  , (BIT_MA_BLOCK_UMIN1   - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_START_UMIN1  , (BIT_MA_START_UMIN1   - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_BLOCK_UMIN2  , (BIT_MA_BLOCK_UMIN2   - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_START_UMIN2  , (BIT_MA_START_UMIN2   - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_PO_UMIN1     , (BIT_MA_PO_UMIN1      - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_PO_UBLK_UMIN1, (BIT_MA_PO_UBLK_UMIN1 - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_PO_IBLK_UMIN1, (BIT_MA_PO_IBLK_UMIN1 - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_UMIN1        , (BIT_MA_UMIN1         - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_PO_UMIN2     , (BIT_MA_PO_UMIN2      - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_PO_UBLK_UMIN2, (BIT_MA_PO_UBLK_UMIN2 - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_PO_IBLK_UMIN2, (BIT_MA_PO_IBLK_UMIN2 - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_UMIN2        , (BIT_MA_UMIN2         - BIT_MA_CURRENT_AF_BASE));

  //Umax
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_BLOCK_UMAX1, (BIT_MA_BLOCK_UMAX1 - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_PO_UMAX1   , (BIT_MA_PO_UMAX1    - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_UMAX1      , (BIT_MA_UMAX1       - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_BLOCK_UMAX2, (BIT_MA_BLOCK_UMAX2 - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_PO_UMAX2   , (BIT_MA_PO_UMAX2    - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_UMAX2      , (BIT_MA_UMAX2       - BIT_MA_CURRENT_AF_BASE));
  
  //���-���
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_RESET_BLOCK_APV_ZMN        , (BIT_MA_RESET_BLOCK_APV_ZMN         - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_BLOCK_APV_ZMN              , (BIT_MA_BLOCK_APV_ZMN               - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_BLOCK_KRATN_APV_ZMN        , (BIT_MA_BLOCK_KRATN_APV_ZMN         - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_PO_UAPV_ZMN1               , (BIT_MA_PO_UAPV_ZMN1                - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_PO_UAPV_ZMN2               , (BIT_MA_PO_UAPV_ZMN2                - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_PO_APV_ZMN                 , (BIT_MA_PO_APV_ZMN                  - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_APV_ZMN                    , (BIT_MA_APV_ZMN                     - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_BLOCK_APV_ZMN_VID_ZAKHYSTIV, (BIT_MA_BLOCK_APV_ZMN_VID_ZAKHYSTIV - BIT_MA_CURRENT_AF_BASE));

  //�����
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_PO_U_OL, (BIT_MA_PO_U_OL - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_U_OL   , (BIT_MA_U_OL    - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_PO_U_RL, (BIT_MA_PO_U_RL - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_U_RL   , (BIT_MA_U_RL    - BIT_MA_CURRENT_AF_BASE));
  
  //���
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_STAT_BLK_APV, (BIT_MA_STAT_BLK_APV - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_APV1        , (BIT_MA_APV          - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_APV2        , (BIT_MA_APV2         - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_APV3        , (BIT_MA_APV3         - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_APV4        , (BIT_MA_APV4         - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_APV_WORK    , (BIT_MA_APV_WORK     - BIT_MA_CURRENT_AF_BASE));

  //����
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_PUSK_UROV_VID_DV, (BIT_MA_PUSK_UROV_VID_DV - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_UROV1           , (BIT_MA_UROV1            - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_UROV2           , (BIT_MA_UROV2            - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_PO_UROV         , (BIT_MA_PO_UROV          - BIT_MA_CURRENT_AF_BASE));

  //���
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_OTKL_AVR               , (BIT_MA_OTKL_AVR                - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_SBROS_BLOCK_AVR        , (BIT_MA_SBROS_BLOCK_AVR         - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_STAT_BLOCK_AVR         , (BIT_MA_STAT_BLOCK_AVR          - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_BLOCK_AVR_VID_ZAKHYSTIV, (BIT_MA_BLOCK_AVR_VID_ZAKHYSTIV - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_PO_UAVR_MIN1           , (BIT_MA_PO_UAVR_MIN1            - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_PO_UAVR_MAX1           , (BIT_MA_PO_UAVR_MAX1            - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_PO_UAVR_MIN2           , (BIT_MA_PO_UAVR_MIN2            - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_PO_UAVR_MAX2           , (BIT_MA_PO_UAVR_MAX2            - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_BLOCK_KRATN_AVR        , (BIT_MA_BLOCK_KRATN_AVR         - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_PUSK_AVR               , (BIT_MA_PUSK_AVR                - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_PUSK_AVR_1             , (BIT_MA_PUSK_AVR_1              - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_PUSK_AVR_2             , (BIT_MA_PUSK_AVR_2              - BIT_MA_CURRENT_AF_BASE));

  //���/����
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_ACHR_CHAPV_VID_DV, (BIT_MA_ACHR_CHAPV_VID_DV - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_BLOCK_ACHR       , (BIT_MA_BLOCK_ACHR        - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_BLOCK_CHAPV_VID_U, (BIT_MA_BLOCK_CHAPV_VID_U - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_PO_F1_ACHR       , (BIT_MA_PO_F1_ACHR        - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_PO_F2_ACHR       , (BIT_MA_PO_F2_ACHR        - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_F1_ACHR_CHAPV    , (BIT_MA_F1_ACHR_CHAPV     - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_F2_ACHR_CHAPV    , (BIT_MA_F2_ACHR_CHAPV     - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_ACHR_CHAPV       , (BIT_MA_ACHR_CHAPV        - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_RAZR_CHAPV       , (BIT_MA_RAZR_CHAPV        - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_PO_F1_CHAPV      , (BIT_MA_PO_F1_CHAPV       - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_PO_F2_CHAPV      , (BIT_MA_PO_F2_CHAPV       - BIT_MA_CURRENT_AF_BASE));

  //��
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_DF1_IN , (BIT_MA_INPUT_DF1  - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_DF2_IN , (BIT_MA_INPUT_DF2  - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_DF3_IN , (BIT_MA_INPUT_DF3  - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_DF4_IN , (BIT_MA_INPUT_DF4  - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_DF5_IN , (BIT_MA_INPUT_DF5  - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_DF6_IN , (BIT_MA_INPUT_DF6  - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_DF7_IN , (BIT_MA_INPUT_DF7  - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_DF8_IN , (BIT_MA_INPUT_DF8  - BIT_MA_CURRENT_AF_BASE));

  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_DF1_OUT, (BIT_MA_OUTPUT_DF1 - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_DF2_OUT, (BIT_MA_OUTPUT_DF2 - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_DF3_OUT, (BIT_MA_OUTPUT_DF3 - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_DF4_OUT, (BIT_MA_OUTPUT_DF4 - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_DF5_OUT, (BIT_MA_OUTPUT_DF5 - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_DF6_OUT, (BIT_MA_OUTPUT_DF6 - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_DF7_OUT, (BIT_MA_OUTPUT_DF7 - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_DF8_OUT, (BIT_MA_OUTPUT_DF8 - BIT_MA_CURRENT_AF_BASE));

  //��
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_DT1_SET  , (BIT_MA_DT1_SET   - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_DT1_RESET, (BIT_MA_DT1_RESET - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_DT2_SET  , (BIT_MA_DT2_SET   - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_DT2_RESET, (BIT_MA_DT2_RESET - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_DT3_SET  , (BIT_MA_DT3_SET   - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_DT3_RESET, (BIT_MA_DT3_RESET - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_DT4_SET  , (BIT_MA_DT4_SET   - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_DT4_RESET, (BIT_MA_DT4_RESET - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_DT1_OUT  , (BIT_MA_DT1_OUT   - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_DT2_OUT  , (BIT_MA_DT2_OUT   - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_DT3_OUT  , (BIT_MA_DT3_OUT   - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_DT4_OUT  , (BIT_MA_DT4_OUT   - BIT_MA_CURRENT_AF_BASE));
  
  //������� ���������� ������������
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_VKL_VV                      , (BIT_MA_VKL_VV                       - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_OTKL_VV                     , (BIT_MA_OTKL_VV                      - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_BLOCK_VKL_VV                , (BIT_MA_BLOCK_VKL_VV                 - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_WORK_BO                     , (BIT_MA_WORK_BO                      - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_WORK_BV                     , (BIT_MA_WORK_BV                      - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_STATE_VV                    , (BIT_MA_STATE_VV                     - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_OTKL_VID_ZOVN_ZAHYSTIV      , (BIT_MA_OTKL_VID_ZOVN_ZAHYSTIV       - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_PRYVID_VV                   , (BIT_MA_GEAR_VV                      - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_CTRL_VKL                    , (BIT_MA_CONTROL_VKL                  - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_CTRL_OTKL                   , (BIT_MA_CONTROL_VIDKL                - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_PEREVYSHCHENNJA_Inom_VYMK   , (BIT_MA_PEREVYSHCHENNJA_Inom_VYMK    - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_KRYTYCHNYJ_RESURS_VYMYKACHA , (BIT_MA_KRYTYCHNYJ_RESURS_VYMYKACHA  - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_VYCHERPANYJ_RESURS_VYMYKACHA, (BIT_MA_VYCHERPANYJ_RESURS_VYMYKACHA - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_DEFECT                      , (BIT_MA_DEFECT                       - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_AVAR_DEFECT                 , (BIT_MA_AVAR_DEFECT                  - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_RESET_LEDS                  , (BIT_MA_RESET_LEDS                   - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_RESET_RELES                 , (BIT_MA_RESET_RELES                  - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_MISCEVE_DYSTANCIJNE         , (BIT_MA_MISCEVE_DYSTANCIJNE          - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_WORK_A_REJESTRATOR          , (BIT_MA_WORK_A_REJESTRATOR           - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_WORK_D_REJESTRATOR          , (BIT_MA_WORK_D_REJESTRATOR           - BIT_MA_CURRENT_AF_BASE));

  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_DVERI_SHAFY_UPR_VIDKR            , (BIT_MA_DVERI_SHAFY_UPR_VIDKR             - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_ACUMUL_BATAREJA_ROZRJADGENA      , (BIT_MA_ACUMUL_BATAREJA_ROZRJADGENA       - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_REZERVTE_GYVLENNJA               , (BIT_MA_REZERVTE_GYVLENNJA                - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_VIDKL_VID_ZAKHYSTIV              , (BIT_MA_VIDKL_VID_ZAKHYSTIV               - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_INVERS_DV_GRUPA_USTAVOK          , (BIT_MA_INVERS_DV_GRUPA_USTAVOK           - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_BLK_GRUP_USTAVOK_VID_ZACHYSTIV   , (BIT_MA_BLK_GRUP_USTAVOK_VID_ZACHYSTIV    - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_RESET_BLOCK_READY_TU_VID_ZAHYSTIV, (BIT_MA_RESET_BLOCK_READY_TU_VID_ZAHYSTIV - BIT_MA_CURRENT_AF_BASE));
  _CONVERT_SIGNAL_TO_GMM(input_array, output_array, RANG_OUTPUT_LED_DF_REG_READY_TU                         , (BIT_MA_READY_TU                          - BIT_MA_CURRENT_AF_BASE));
}
/***********************************************************************************/

/***********************************************************************************/
/*
���������������� ���������� �������������� ������
���� ���������� �������� ������� � ������ ��� "����������� ����� ���'��"
*/
/***********************************************************************************/
unsigned int convert_order_list_buttons_to_gmm(unsigned int number, unsigned int number_position)
{
  unsigned int input_value =current_settings.ranguvannja_buttons[number];
  unsigned int index_in_gmm = 0;
  unsigned int rezultat = 0;
  
  //������ �������� ������ ������� � ��� ������ ���������
  unsigned int i = 0;
  while ( (i < NUMBER_TOTAL_SIGNAL_FOR_RANG_BUTTON) && (index_in_gmm < number_position) )
  {
    if ((input_value & (1 << i)) != 0) index_in_gmm++;
    if (index_in_gmm < number_position) i++;
  }

  //��������� ��� ������� ��� ������������� � "����������� ���� ���'��"
  if (index_in_gmm == number_position)
  {
    switch (i)
    {
    case RANG_BUTTON_DF1_IN:
      {
        rezultat = BIT_MA_INPUT_DF1;
        break;
      }
    case RANG_BUTTON_DF2_IN:
      {
        rezultat = BIT_MA_INPUT_DF2;
        break;
      }
    case RANG_BUTTON_DF3_IN:
      {
        rezultat = BIT_MA_INPUT_DF3;
        break;
      }
    case RANG_BUTTON_DF4_IN:
      {
        rezultat = BIT_MA_INPUT_DF4;
        break;
      }
    case RANG_BUTTON_DF5_IN:
      {
        rezultat = BIT_MA_INPUT_DF5;
        break;
      }
    case RANG_BUTTON_DF6_IN:
      {
        rezultat = BIT_MA_INPUT_DF6;
        break;
      }
    case RANG_BUTTON_DF7_IN:
      {
        rezultat = BIT_MA_INPUT_DF7;
        break;
      }
    case RANG_BUTTON_DF8_IN:
      {
        rezultat = BIT_MA_INPUT_DF8;
        break;
      }
    case RANG_BUTTON_DT1_SET:
      {
        rezultat = BIT_MA_DT1_SET;
        break;
      }
    case RANG_BUTTON_DT1_RESET:
      {
        rezultat = BIT_MA_DT1_RESET;
        break;
      }
    case RANG_BUTTON_DT2_SET:
      {
        rezultat = BIT_MA_DT2_SET;
        break;
      }
    case RANG_BUTTON_DT2_RESET:
      {
        rezultat = BIT_MA_DT2_RESET;
        break;
      }
    case RANG_BUTTON_DT3_SET:
      {
        rezultat = BIT_MA_DT3_SET;
        break;
      }
    case RANG_BUTTON_DT3_RESET:
      {
        rezultat = BIT_MA_DT3_RESET;
        break;
      }
    case RANG_BUTTON_DT4_SET:
      {
        rezultat = BIT_MA_DT4_SET;
        break;
      }
    case RANG_BUTTON_DT4_RESET:
      {
        rezultat = BIT_MA_DT4_RESET;
        break;
      }
    case RANG_BUTTON_RESET_LEDS:
      {
        rezultat = BIT_MA_RESET_LEDS;
        break;
      }
    case RANG_BUTTON_RESET_RELES:
      {
        rezultat = BIT_MA_RESET_RELES;
        break;
      }
    case RANG_BUTTON_MISCEVE_DYSTANCIJNE:
      {
        rezultat = BIT_MA_MISCEVE_DYSTANCIJNE;
        break;
      }
    case RANG_BUTTON_VKL_VV:
      {
        rezultat = BIT_MA_VKL_VV;
        break;
      }
    case RANG_BUTTON_OTKL_VV:
      {
        rezultat = BIT_MA_OTKL_VV;
        break;
      }
    case RANG_BUTTON_RESET_BLOCK_APV_ZMN:
      {
        rezultat = BIT_MA_RESET_BLOCK_APV_ZMN;
        break;
      }
    case RANG_BUTTON_OTKL_AVR:
      {
        rezultat = BIT_MA_OTKL_AVR;
        break;
      }
    case RANG_BUTTON_SBROS_BLOCK_AVR:
      {
        rezultat = BIT_MA_SBROS_BLOCK_AVR;
        break;
      }
    case RANG_BUTTON_RESET_BLOCK_READY_TU_VID_ZAHYSTIV:
      {
        rezultat = BIT_MA_RESET_BLOCK_READY_TU_VID_ZAHYSTIV;
        break;
      }
    default: break;
    }
  }
    
  return rezultat;
}
/***********************************************************************************/

/***********************************************************************************/
/*
���������������� ���������� �����
���� ���������� �������� ������� � ������ ��� "����������� ����� ���'��"
*/
/***********************************************************************************/
unsigned int convert_order_list_inputs_to_gmm(unsigned int number, unsigned int number_position)
{
  unsigned int input_value[N_SMALL];
  input_value[0] =current_settings.ranguvannja_inputs[2*number    ];
  input_value[1] =current_settings.ranguvannja_inputs[2*number + 1];
  unsigned int index_in_gmm = 0;
  unsigned int rezultat = 0;
  
  //������ �������� ������ ������� � ��� ������ ���������
  unsigned int i = 0;
  while ( (i < NUMBER_TOTAL_SIGNAL_FOR_RANG_INPUT) && (index_in_gmm < number_position) )
  {
    unsigned int offset, shift;
    offset = i >> 5; //�� �, ��������, ������ �� 32
    shift  = (i & (32 - 1)); //�� �, ��������, ���������� ������ �� ������ �� 32

    if ((input_value[offset] & (1 << shift)) != 0) index_in_gmm++;
    if (index_in_gmm < number_position) i++;
  }

  //��������� ��� ������� ��� ������������� � "����������� ���� ���'��"
  if (index_in_gmm == number_position)
  {
    switch (i)
    {
    case RANG_INPUT_DF1_IN:
      {
        rezultat = BIT_MA_INPUT_DF1;
        break;
      }
    case RANG_INPUT_DF2_IN:
      {
        rezultat = BIT_MA_INPUT_DF2;
        break;
      }
    case RANG_INPUT_DF3_IN:
      {
        rezultat = BIT_MA_INPUT_DF3;
        break;
      }
    case RANG_INPUT_DF4_IN:
      {
        rezultat = BIT_MA_INPUT_DF4;
        break;
      }
    case RANG_INPUT_DF5_IN:
      {
        rezultat = BIT_MA_INPUT_DF5;
        break;
      }
    case RANG_INPUT_DF6_IN:
      {
        rezultat = BIT_MA_INPUT_DF6;
        break;
      }
    case RANG_INPUT_DF7_IN:
      {
        rezultat = BIT_MA_INPUT_DF7;
        break;
      }
    case RANG_INPUT_DF8_IN:
      {
        rezultat = BIT_MA_INPUT_DF8;
        break;
      }
    case RANG_INPUT_DT1_SET:
      {
        rezultat = BIT_MA_DT1_SET;
        break;
      }
    case RANG_INPUT_DT1_RESET:
      {
        rezultat = BIT_MA_DT1_RESET;
        break;
      }
    case RANG_INPUT_DT2_SET:
      {
        rezultat = BIT_MA_DT2_SET;
        break;
      }
    case RANG_INPUT_DT2_RESET:
      {
        rezultat = BIT_MA_DT2_RESET;
        break;
      }
    case RANG_INPUT_DT3_SET:
      {
        rezultat = BIT_MA_DT3_SET;
        break;
      }
    case RANG_INPUT_DT3_RESET:
      {
        rezultat = BIT_MA_DT3_RESET;
        break;
      }
    case RANG_INPUT_DT4_SET:
      {
        rezultat = BIT_MA_DT4_SET;
        break;
      }
    case RANG_INPUT_DT4_RESET:
      {
        rezultat = BIT_MA_DT4_RESET;
        break;
      }
    case RANG_INPUT_BLOCK_VKL_VV:
      {
        rezultat = BIT_MA_BLOCK_VKL_VV;
        break;
      }
    case RANG_INPUT_RESET_LEDS:
      {
        rezultat = BIT_MA_RESET_LEDS;
        break;
      }
    case RANG_INPUT_RESET_RELES:
      {
        rezultat = BIT_MA_RESET_RELES;
        break;
      }
    case RANG_INPUT_MISCEVE_DYSTANCIJNE:
      {
        rezultat = BIT_MA_MISCEVE_DYSTANCIJNE;
        break;
      }
    case RANG_INPUT_STATE_VV:
      {
        rezultat = BIT_MA_STATE_VV;
        break;
      }
    case RANG_INPUT_OTKL_VID_ZOVN_ZAHYSTIV:
      {
        rezultat = BIT_MA_OTKL_VID_ZOVN_ZAHYSTIV;
        break;
      }
    case RANG_INPUT_VKL_VV:
      {
        rezultat = BIT_MA_VKL_VV;
        break;
      }
    case RANG_INPUT_CTRL_VKL:
      {
        rezultat = BIT_MA_CONTROL_VKL;
        break;
      }
    case RANG_INPUT_OTKL_VV:
      {
        rezultat = BIT_MA_OTKL_VV;
        break;
      }
    case RANG_INPUT_CTRL_OTKL:
      {
        rezultat = BIT_MA_CONTROL_VIDKL;
        break;
      }
    case RANG_INPUT_1_GRUPA_USTAVOK:
      {
        rezultat = BIT_MA_1_GRUPA_USTAVOK;
        break;
      }
    case RANG_INPUT_2_GRUPA_USTAVOK:
      {
        rezultat = BIT_MA_2_GRUPA_USTAVOK;
        break;
      }
    case RANG_INPUT_3_GRUPA_USTAVOK:
      {
        rezultat = BIT_MA_3_GRUPA_USTAVOK;
        break;
      }
    case RANG_INPUT_4_GRUPA_USTAVOK:
      {
        rezultat = BIT_MA_4_GRUPA_USTAVOK;
        break;
      }
    case RANG_INPUT_DVERI_SHAFY_UPR_VIDKR:
      {
        rezultat = BIT_MA_DVERI_SHAFY_UPR_VIDKR;
        break;
      }
    case RANG_INPUT_ACUMUL_BATAREJA_ROZRJADGENA:
      {
        rezultat = BIT_MA_ACUMUL_BATAREJA_ROZRJADGENA;
        break;
      }
    case RANG_INPUT_REZERVTE_GYVLENNJA:
      {
        rezultat = BIT_MA_REZERVTE_GYVLENNJA;
        break;
      }
    case RANG_INPUT_RESET_BLOCK_READY_TU_VID_ZAHYSTIV:
      {
        rezultat = BIT_MA_RESET_BLOCK_READY_TU_VID_ZAHYSTIV;
        break;
      }
    case RANG_INPUT_BLOCK_MTZ1:
      {
        rezultat = BIT_MA_BLOCK_MTZ1;
        break;
      }
    case RANG_INPUT_BLOCK_MTZ2:
      {
        rezultat = BIT_MA_BLOCK_MTZ2;
        break;
      }
    case RANG_INPUT_BLOCK_USK_MTZ2:
      {
        rezultat = BIT_MA_BLOCK_USK_MTZ2;
        break;
      }
    case RANG_INPUT_BLOCK_MTZ3:
      {
        rezultat = BIT_MA_BLOCK_MTZ3;
        break;
      }
    case RANG_INPUT_BLOCK_MTZ4:
      {
        rezultat = BIT_MA_BLOCK_MTZ4;
        break;
      }
    case RANG_INPUT_PUSK_ZDZ_VID_DV:
      {
        rezultat = BIT_MA_PUSK_ZDZ_VID_DV;
        break;
      }
    case RANG_INPUT_BLOCK_NZZ:
      {
        rezultat = BIT_MA_BLOCK_NZZ;
        break;
      }
    case RANG_INPUT_STAT_BLK_APV:
      {
        rezultat = BIT_MA_STAT_BLK_APV;
        break;
      }
    case RANG_INPUT_RESET_BLOCK_APV_ZMN:
      {
        rezultat = BIT_MA_RESET_BLOCK_APV_ZMN;
        break;
      }
    case RANG_INPUT_BLOCK_APV_ZMN:
      {
        rezultat = BIT_MA_BLOCK_APV_ZMN;
        break;
      }
    case RANG_INPUT_BLOCK_ACHR:
      {
        rezultat = BIT_MA_BLOCK_ACHR;
        break;
      }
    case RANG_INPUT_ACHR_CHAPV_VID_DV:
      {
        rezultat = BIT_MA_ACHR_CHAPV_VID_DV;
        break;
      }
    case RANG_INPUT_PUSK_UROV_VID_DV:
      {
        rezultat = BIT_MA_PUSK_UROV_VID_DV;
        break;
      }
    case RANG_INPUT_BLOCK_ZOP:
      {
        rezultat = BIT_MA_BLOCK_ZOP;
        break;
      }
    case RANG_INPUT_BLOCK_UMIN1:
      {
        rezultat = BIT_MA_BLOCK_UMIN1;
        break;
      }
    case RANG_INPUT_START_UMIN1:
      {
        rezultat = BIT_MA_START_UMIN1;
        break;
      }
    case RANG_INPUT_BLOCK_UMIN2:
      {
        rezultat = BIT_MA_BLOCK_UMIN2;
        break;
      }
    case RANG_INPUT_START_UMIN2:
      {
        rezultat = BIT_MA_START_UMIN2;
        break;
      }
    case RANG_INPUT_BLOCK_UMAX1:
      {
        rezultat = BIT_MA_BLOCK_UMAX1;
        break;
      }
    case RANG_INPUT_BLOCK_UMAX2:
      {
        rezultat = BIT_MA_BLOCK_UMAX2;
        break;
      }
    case RANG_INPUT_OTKL_AVR:
      {
        rezultat = BIT_MA_OTKL_AVR;
        break;
      }
    case RANG_INPUT_SBROS_BLOCK_AVR:
      {
        rezultat = BIT_MA_SBROS_BLOCK_AVR;
        break;
      }
    case RANG_INPUT_STAT_BLOCK_AVR:
      {
        rezultat = BIT_MA_STAT_BLOCK_AVR;
        break;
      }
    default: break;
    }
  }
    
  return rezultat;
}
/***********************************************************************************/

/***********************************************************************************/
/*
���������������� ���������� ������
���� ���������� �������� ������� � ������ ��� "����������� ����� ���'��"
*/
/***********************************************************************************/
unsigned int convert_order_list_oldr_to_gmm(unsigned int number, unsigned int number_position, unsigned int source)
{
  unsigned int input_value[N_BIG];
  unsigned int index_in_gmm = 0;
  unsigned short rezultat = 0;
  
  //��������� �������� .��� ����� ������������ � ���� "����������� ����� ���'��"
  if (source == SOURCE_OUTPUTS_RANG)
  {
    input_value[0] = current_settings.ranguvannja_outputs[N_BIG*number    ];
    input_value[1] = current_settings.ranguvannja_outputs[N_BIG*number + 1];
    input_value[2] = current_settings.ranguvannja_outputs[N_BIG*number + 2];
    input_value[3] = current_settings.ranguvannja_outputs[N_BIG*number + 3];
    input_value[4] = current_settings.ranguvannja_outputs[N_BIG*number + 4];
    input_value[5] = current_settings.ranguvannja_outputs[N_BIG*number + 5];
  }
  else if (source == SOURCE_LEDS_RANG)
  {
    input_value[0] = current_settings.ranguvannja_leds[N_BIG*number    ];
    input_value[1] = current_settings.ranguvannja_leds[N_BIG*number + 1];
    input_value[2] = current_settings.ranguvannja_leds[N_BIG*number + 2];
    input_value[3] = current_settings.ranguvannja_leds[N_BIG*number + 3];
    input_value[4] = current_settings.ranguvannja_leds[N_BIG*number + 4];
    input_value[5] = current_settings.ranguvannja_leds[N_BIG*number + 5];
  }
  else if (source == SOURCE_DF_PLUS_RANG)
  {
    input_value[0] = current_settings.ranguvannja_df_source_plus[N_BIG*number    ];
    input_value[1] = current_settings.ranguvannja_df_source_plus[N_BIG*number + 1];
    input_value[2] = current_settings.ranguvannja_df_source_plus[N_BIG*number + 2];
    input_value[3] = current_settings.ranguvannja_df_source_plus[N_BIG*number + 3];
    input_value[4] = current_settings.ranguvannja_df_source_plus[N_BIG*number + 4];
    input_value[5] = current_settings.ranguvannja_df_source_plus[N_BIG*number + 5];
  }
  else if (source == SOURCE_DF_MINUS_RANG)
  {
    input_value[0] = current_settings.ranguvannja_df_source_minus[N_BIG*number    ];
    input_value[1] = current_settings.ranguvannja_df_source_minus[N_BIG*number + 1];
    input_value[2] = current_settings.ranguvannja_df_source_minus[N_BIG*number + 2];
    input_value[3] = current_settings.ranguvannja_df_source_minus[N_BIG*number + 3];
    input_value[4] = current_settings.ranguvannja_df_source_minus[N_BIG*number + 4];
    input_value[5] = current_settings.ranguvannja_df_source_minus[N_BIG*number + 5];
  }
  else if (source == SOURCE_DF_BLK_RANG)
  {
    input_value[0] = current_settings.ranguvannja_df_source_blk[N_BIG*number    ];
    input_value[1] = current_settings.ranguvannja_df_source_blk[N_BIG*number + 1];
    input_value[2] = current_settings.ranguvannja_df_source_blk[N_BIG*number + 2];
    input_value[3] = current_settings.ranguvannja_df_source_blk[N_BIG*number + 3];
    input_value[4] = current_settings.ranguvannja_df_source_blk[N_BIG*number + 4];
    input_value[5] = current_settings.ranguvannja_df_source_blk[N_BIG*number + 5];
  }
  else if (source == SOURCE_AR_RANG)
  {
    input_value[0] = current_settings.ranguvannja_analog_registrator[0];
    input_value[1] = current_settings.ranguvannja_analog_registrator[1];
    input_value[2] = current_settings.ranguvannja_analog_registrator[2];
    input_value[3] = current_settings.ranguvannja_analog_registrator[3];
    input_value[4] = current_settings.ranguvannja_analog_registrator[4];
    input_value[5] = current_settings.ranguvannja_analog_registrator[5];
  }
  else if (source == SOURCE_DR_RANG)
  {
    input_value[0] = current_settings.ranguvannja_digital_registrator[0];
    input_value[1] = current_settings.ranguvannja_digital_registrator[1];
    input_value[2] = current_settings.ranguvannja_digital_registrator[2];
    input_value[3] = current_settings.ranguvannja_digital_registrator[3];
    input_value[4] = current_settings.ranguvannja_digital_registrator[4];
    input_value[5] = current_settings.ranguvannja_digital_registrator[5];
  }
  else if (source == SOURCE_SET_DT_PLUS_RANG)
  {
    input_value[0] = current_settings.ranguvannja_set_dt_source_plus[N_BIG*number    ];
    input_value[1] = current_settings.ranguvannja_set_dt_source_plus[N_BIG*number + 1];
    input_value[2] = current_settings.ranguvannja_set_dt_source_plus[N_BIG*number + 2];
    input_value[3] = current_settings.ranguvannja_set_dt_source_plus[N_BIG*number + 3];
    input_value[4] = current_settings.ranguvannja_set_dt_source_plus[N_BIG*number + 4];
    input_value[5] = current_settings.ranguvannja_set_dt_source_plus[N_BIG*number + 5];
  }
  else if (source == SOURCE_SET_DT_MINUS_RANG)
  {
    input_value[0] = current_settings.ranguvannja_set_dt_source_minus[N_BIG*number    ];
    input_value[1] = current_settings.ranguvannja_set_dt_source_minus[N_BIG*number + 1];
    input_value[2] = current_settings.ranguvannja_set_dt_source_minus[N_BIG*number + 2];
    input_value[3] = current_settings.ranguvannja_set_dt_source_minus[N_BIG*number + 3];
    input_value[4] = current_settings.ranguvannja_set_dt_source_minus[N_BIG*number + 4];
    input_value[5] = current_settings.ranguvannja_set_dt_source_minus[N_BIG*number + 5];
  }
  else if (source == SOURCE_RESET_DT_PLUS_RANG)
  {
    input_value[0] = current_settings.ranguvannja_reset_dt_source_plus[N_BIG*number    ];
    input_value[1] = current_settings.ranguvannja_reset_dt_source_plus[N_BIG*number + 1];
    input_value[2] = current_settings.ranguvannja_reset_dt_source_plus[N_BIG*number + 2];
    input_value[3] = current_settings.ranguvannja_reset_dt_source_plus[N_BIG*number + 3];
    input_value[4] = current_settings.ranguvannja_reset_dt_source_plus[N_BIG*number + 4];
    input_value[5] = current_settings.ranguvannja_reset_dt_source_plus[N_BIG*number + 5];
  }
  else if (source == SOURCE_RESET_DT_MINUS_RANG)
  {
    input_value[0] = current_settings.ranguvannja_reset_dt_source_minus[N_BIG*number    ];
    input_value[1] = current_settings.ranguvannja_reset_dt_source_minus[N_BIG*number + 1];
    input_value[2] = current_settings.ranguvannja_reset_dt_source_minus[N_BIG*number + 2];
    input_value[3] = current_settings.ranguvannja_reset_dt_source_minus[N_BIG*number + 3];
    input_value[4] = current_settings.ranguvannja_reset_dt_source_minus[N_BIG*number + 4];
    input_value[5] = current_settings.ranguvannja_reset_dt_source_minus[N_BIG*number + 5];
  }
  
  //������ �������� ������ ������� � ��� ������ ���������
  unsigned int i = 0;
  while ( (i < NUMBER_TOTAL_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG) && (index_in_gmm < number_position) )
  {
    unsigned int offset, shift;
    offset = i >> 5; //�� �, ��������, ������ �� 32
    shift  = (i & (32 - 1)); //�� �, ��������, ���������� ������ �� ������ �� 32

    if ((input_value[offset] & (1 << shift)) != 0) index_in_gmm++;
    if (index_in_gmm < number_position) i++;
  }
  
  //��������� ��� ������� ��� ������������� � "����������� ���� ���'��"
  if (index_in_gmm == number_position)
  {
    switch (i)
    {
    case RANG_OUTPUT_LED_DF_REG_DF1_IN:
      {
        rezultat =  BIT_MA_INPUT_DF1;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_DF1_OUT:
      {
        rezultat =  BIT_MA_OUTPUT_DF1;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_DF2_IN:
      {
        rezultat = BIT_MA_INPUT_DF2;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_DF2_OUT:
      {
        rezultat =  BIT_MA_OUTPUT_DF2;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_DF3_IN:
      {
        rezultat = BIT_MA_INPUT_DF3;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_DF3_OUT:
      {
        rezultat =  BIT_MA_OUTPUT_DF3;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_DF4_IN:
      {
        rezultat = BIT_MA_INPUT_DF4;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_DF4_OUT:
      {
        rezultat =  BIT_MA_OUTPUT_DF4;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_DF5_IN:
      {
        rezultat = BIT_MA_INPUT_DF5;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_DF5_OUT:
      {
        rezultat =  BIT_MA_OUTPUT_DF5;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_DF6_IN:
      {
        rezultat = BIT_MA_INPUT_DF6;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_DF6_OUT:
      {
        rezultat =  BIT_MA_OUTPUT_DF6;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_DF7_IN:
      {
        rezultat = BIT_MA_INPUT_DF7;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_DF7_OUT:
      {
        rezultat =  BIT_MA_OUTPUT_DF7;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_DF8_IN:
      {
        rezultat = BIT_MA_INPUT_DF8;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_DF8_OUT:
      {
        rezultat =  BIT_MA_OUTPUT_DF8;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_DT1_SET:
      {
        rezultat = BIT_MA_DT1_SET;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_DT1_RESET:
      {
        rezultat = BIT_MA_DT1_RESET;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_DT1_OUT:
      {
        rezultat = BIT_MA_DT1_OUT;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_DT2_SET:
      {
        rezultat = BIT_MA_DT2_SET;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_DT2_RESET:
      {
        rezultat = BIT_MA_DT2_RESET;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_DT2_OUT:
      {
        rezultat = BIT_MA_DT2_OUT;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_DT3_SET:
      {
        rezultat = BIT_MA_DT3_SET;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_DT3_RESET:
      {
        rezultat = BIT_MA_DT3_RESET;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_DT3_OUT:
      {
        rezultat = BIT_MA_DT3_OUT;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_DT4_SET:
      {
        rezultat = BIT_MA_DT4_SET;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_DT4_RESET:
      {
        rezultat = BIT_MA_DT4_RESET;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_DT4_OUT:
      {
        rezultat = BIT_MA_DT4_OUT;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_BLOCK_VKL_VV:
      {
        rezultat = BIT_MA_BLOCK_VKL_VV;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_RESET_LEDS:
      {
        rezultat = BIT_MA_RESET_LEDS;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_RESET_RELES:
      {
        rezultat = BIT_MA_RESET_RELES;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_MISCEVE_DYSTANCIJNE:
      {
        rezultat = BIT_MA_MISCEVE_DYSTANCIJNE;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_STATE_VV:
      {
        rezultat = BIT_MA_STATE_VV;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_OTKL_VID_ZOVN_ZAHYSTIV:
      {
        rezultat = BIT_MA_OTKL_VID_ZOVN_ZAHYSTIV;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_VKL_VV:
      {
        rezultat = BIT_MA_VKL_VV;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_CTRL_VKL:
      {
        rezultat = BIT_MA_CONTROL_VKL;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_OTKL_VV:
      {
        rezultat = BIT_MA_OTKL_VV;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_CTRL_OTKL:
      {
        rezultat = BIT_MA_CONTROL_VIDKL;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_PRYVID_VV:
      {
        rezultat = BIT_MA_GEAR_VV;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_PEREVYSHCHENNJA_Inom_VYMK:
      {
        rezultat = BIT_MA_PEREVYSHCHENNJA_Inom_VYMK;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_KRYTYCHNYJ_RESURS_VYMYKACHA:
      {
        rezultat = BIT_MA_KRYTYCHNYJ_RESURS_VYMYKACHA;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_VYCHERPANYJ_RESURS_VYMYKACHA:
      {
        rezultat = BIT_MA_VYCHERPANYJ_RESURS_VYMYKACHA;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_DEFECT:
      {
        rezultat = BIT_MA_DEFECT;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_AVAR_DEFECT:
      {
        rezultat = BIT_MA_AVAR_DEFECT;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_WORK_A_REJESTRATOR:
      {
        rezultat = BIT_MA_WORK_A_REJESTRATOR;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_WORK_D_REJESTRATOR:
      {
        rezultat = BIT_MA_WORK_D_REJESTRATOR;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_WORK_BO:
      {
        rezultat = BIT_MA_WORK_BO;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_WORK_BV:
      {
        rezultat = BIT_MA_WORK_BV;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_1_GRUPA_USTAVOK:
      {
        rezultat = BIT_MA_1_GRUPA_USTAVOK;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_2_GRUPA_USTAVOK:
      {
        rezultat = BIT_MA_2_GRUPA_USTAVOK;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_3_GRUPA_USTAVOK:
      {
        rezultat = BIT_MA_3_GRUPA_USTAVOK;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_4_GRUPA_USTAVOK:
      {
        rezultat = BIT_MA_4_GRUPA_USTAVOK;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_DVERI_SHAFY_UPR_VIDKR:
      {
        rezultat = BIT_MA_DVERI_SHAFY_UPR_VIDKR;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_ACUMUL_BATAREJA_ROZRJADGENA:
      {
        rezultat = BIT_MA_ACUMUL_BATAREJA_ROZRJADGENA;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_REZERVTE_GYVLENNJA:
      {
        rezultat = BIT_MA_REZERVTE_GYVLENNJA;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_VIDKL_VID_ZAKHYSTIV:
      {
        rezultat = BIT_MA_VIDKL_VID_ZAKHYSTIV;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_BLK_GRUP_USTAVOK_VID_ZACHYSTIV:
      {
        rezultat = BIT_MA_BLK_GRUP_USTAVOK_VID_ZACHYSTIV;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_INVERS_DV_GRUPA_USTAVOK:
      {
        rezultat = BIT_MA_INVERS_DV_GRUPA_USTAVOK;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_READY_TU:
      {
        rezultat = BIT_MA_READY_TU;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_RESET_BLOCK_READY_TU_VID_ZAHYSTIV:
      {
        rezultat = BIT_MA_RESET_BLOCK_READY_TU_VID_ZAHYSTIV;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_BLOCK_MTZ1:
      {
        rezultat = BIT_MA_BLOCK_MTZ1;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_BLOCK_MTZ2:
      {
        rezultat = BIT_MA_BLOCK_MTZ2;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_BLOCK_USK_MTZ2:
      {
        rezultat = BIT_MA_BLOCK_USK_MTZ2;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_BLOCK_MTZ3:
      {
        rezultat = BIT_MA_BLOCK_MTZ3;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_BLOCK_MTZ4:
      {
        rezultat = BIT_MA_BLOCK_MTZ4;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_SECTOR_VPERED_MTZN1:
      {
        rezultat = BIT_MA_SECTOR_VPERED_MTZN1;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_SECTOR_NAZAD_MTZN1:
      {
        rezultat = BIT_MA_SECTOR_NAZAD_MTZN1;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_PO_MTZ1:
      {
        rezultat = BIT_MA_PO_MTZ1;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_PO_MTZN1_VPERED:
      {
        rezultat = BIT_MA_PO_MTZN1_VPERED;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_PO_MTZN1_NAZAD:
      {
        rezultat = BIT_MA_PO_MTZN1_NAZAD;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_PO_U_MTZPN1:
      {
        rezultat = BIT_MA_PO_U_MTZPN1;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_PO_MTZPN1:
      {
        rezultat = BIT_MA_PO_MTZPN1;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_MTZ1:
      {
        rezultat = BIT_MA_MTZ1;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_SECTOR_VPERED_MTZN2:
      {
        rezultat = BIT_MA_SECTOR_VPERED_MTZN2;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_SECTOR_NAZAD_MTZN2:
      {
        rezultat = BIT_MA_SECTOR_NAZAD_MTZN2;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_PO_MTZ2:
      {
        rezultat = BIT_MA_PO_MTZ2;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_PO_MTZN2_VPERED:
      {
        rezultat = BIT_MA_PO_MTZN2_VPERED;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_PO_MTZN2_NAZAD:
      {
        rezultat = BIT_MA_PO_MTZN2_NAZAD;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_PO_U_MTZPN2:
      {
        rezultat = BIT_MA_PO_U_MTZPN2;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_PO_MTZPN2:
      {
        rezultat = BIT_MA_PO_MTZPN2;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_MTZ2:
      {
        rezultat = BIT_MA_MTZ2;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_SECTOR_VPERED_MTZN3:
      {
        rezultat = BIT_MA_SECTOR_VPERED_MTZN3;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_SECTOR_NAZAD_MTZN3:
      {
        rezultat = BIT_MA_SECTOR_NAZAD_MTZN3;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_PO_MTZ3:
      {
        rezultat = BIT_MA_PO_MTZ3;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_PO_MTZN3_VPERED:
      {
        rezultat = BIT_MA_PO_MTZN3_VPERED;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_PO_MTZN3_NAZAD:
      {
        rezultat = BIT_MA_PO_MTZN3_NAZAD;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_PO_U_MTZPN3:
      {
        rezultat = BIT_MA_PO_U_MTZPN3;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_PO_MTZPN3:
      {
        rezultat = BIT_MA_PO_MTZPN3;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_MTZ3:
      {
        rezultat = BIT_MA_MTZ3;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_SECTOR_VPERED_MTZN4:
      {
        rezultat = BIT_MA_SECTOR_VPERED_MTZN4;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_SECTOR_NAZAD_MTZN4:
      {
        rezultat = BIT_MA_SECTOR_NAZAD_MTZN4;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_PO_MTZ4:
      {
        rezultat = BIT_MA_PO_MTZ4;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_PO_MTZN4_VPERED:
      {
        rezultat = BIT_MA_PO_MTZN4_VPERED;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_PO_MTZN4_NAZAD:
      {
        rezultat = BIT_MA_PO_MTZN4_NAZAD;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_PO_U_MTZPN4:
      {
        rezultat = BIT_MA_PO_U_MTZPN4;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_PO_MTZPN4:
      {
        rezultat = BIT_MA_PO_MTZPN4;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_MTZ4:
      {
        rezultat = BIT_MA_MTZ4;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_PO_BLOCK_U_MTZN:
      {
        rezultat = BIT_MA_PO_BLOCK_U_MTZN;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_NCN_MTZ:
      {
        rezultat = BIT_MA_NCN_MTZ;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_PUSK_ZDZ_VID_DV:
      {
        rezultat = BIT_MA_PUSK_ZDZ_VID_DV;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_ZDZ:
      {
        rezultat = BIT_MA_ZDZ;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_BLOCK_NZZ:
      {
        rezultat = BIT_MA_BLOCK_NZZ;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_PO_NZZ:
      {
        rezultat = BIT_MA_PO_NZZ;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_NZZ:
      {
        rezultat = BIT_MA_NZZ;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_PO_3I0:
      {
        rezultat = BIT_MA_PO_ZZ1_3I0;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_3I0:
      {
        rezultat = BIT_MA_ZZ1_3I0;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_PO_3U0:
      {
        rezultat = BIT_MA_PO_ZZ_3U0;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_3U0:
      {
        rezultat = BIT_MA_ZZ_3U0;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_SECTOR_NZZ:
      {
        rezultat = BIT_MA_SECTOR_NZZ;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_STAT_BLK_APV:
      {
        rezultat = BIT_MA_STAT_BLK_APV;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_APV1:
      {
        rezultat = BIT_MA_APV;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_APV2:
      {
        rezultat = BIT_MA_APV2;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_APV3:
      {
        rezultat = BIT_MA_APV3;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_APV4:
      {
        rezultat = BIT_MA_APV4;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_APV_WORK:
      {
        rezultat = BIT_MA_APV_WORK;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_RESET_BLOCK_APV_ZMN:
      {
        rezultat = BIT_MA_RESET_BLOCK_APV_ZMN;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_BLOCK_APV_ZMN:
      {
        rezultat = BIT_MA_BLOCK_APV_ZMN;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_BLOCK_KRATN_APV_ZMN:
      {
        rezultat = BIT_MA_BLOCK_KRATN_APV_ZMN;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_BLOCK_APV_ZMN_VID_ZAKHYSTIV:
      {
        rezultat = BIT_MA_BLOCK_APV_ZMN_VID_ZAKHYSTIV;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_PO_UAPV_ZMN1:
      {
        rezultat = BIT_MA_PO_UAPV_ZMN1;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_PO_UAPV_ZMN2:
      {
        rezultat = BIT_MA_PO_UAPV_ZMN2;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_PO_APV_ZMN:
      {
        rezultat = BIT_MA_PO_APV_ZMN;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_APV_ZMN:
      {
        rezultat = BIT_MA_APV_ZMN;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_BLOCK_ACHR:
      {
        rezultat = BIT_MA_BLOCK_ACHR;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_RAZR_CHAPV:
      {
        rezultat = BIT_MA_RAZR_CHAPV;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_BLOCK_CHAPV_VID_U:
      {
        rezultat = BIT_MA_BLOCK_CHAPV_VID_U;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_PO_F1_ACHR:
      {
        rezultat = BIT_MA_PO_F1_ACHR;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_F1_ACHR_CHAPV:
      {
        rezultat = BIT_MA_F1_ACHR_CHAPV;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_PO_F2_ACHR:
      {
        rezultat = BIT_MA_PO_F2_ACHR;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_F2_ACHR_CHAPV:
      {
        rezultat = BIT_MA_F2_ACHR_CHAPV;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_ACHR_CHAPV:
      {
        rezultat = BIT_MA_ACHR_CHAPV;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_PO_F1_CHAPV:
      {
        rezultat = BIT_MA_PO_F1_CHAPV;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_PO_F2_CHAPV:
      {
        rezultat = BIT_MA_PO_F2_CHAPV;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_ACHR_CHAPV_VID_DV:
      {
        rezultat = BIT_MA_ACHR_CHAPV_VID_DV;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_PUSK_UROV_VID_DV:
      {
        rezultat = BIT_MA_PUSK_UROV_VID_DV;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_PO_UROV:
      {
        rezultat = BIT_MA_PO_UROV;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_UROV1:
      {
        rezultat = BIT_MA_UROV1;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_UROV2:
      {
        rezultat = BIT_MA_UROV2;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_BLOCK_ZOP:
      {
        rezultat = BIT_MA_BLOCK_ZOP;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_PO_ZOP:
      {
        rezultat = BIT_MA_PO_ZOP;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_ZOP:
      {
        rezultat = BIT_MA_ZOP;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_BLOCK_UMIN1:
      {
        rezultat = BIT_MA_BLOCK_UMIN1;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_START_UMIN1:
      {
        rezultat = BIT_MA_START_UMIN1;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_BLOCK_UMIN2:
      {
        rezultat = BIT_MA_BLOCK_UMIN2;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_START_UMIN2:
      {
        rezultat = BIT_MA_START_UMIN2;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_PO_UMIN1:
      {
        rezultat = BIT_MA_PO_UMIN1;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_PO_UBLK_UMIN1:
      {
        rezultat = BIT_MA_PO_UBLK_UMIN1;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_PO_IBLK_UMIN1:
      {
        rezultat = BIT_MA_PO_IBLK_UMIN1;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_UMIN1:
      {
        rezultat = BIT_MA_UMIN1;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_PO_UMIN2:
      {
        rezultat = BIT_MA_PO_UMIN2;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_PO_UBLK_UMIN2:
      {
        rezultat = BIT_MA_PO_UBLK_UMIN2;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_PO_IBLK_UMIN2:
      {
        rezultat = BIT_MA_PO_IBLK_UMIN2;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_UMIN2:
      {
        rezultat = BIT_MA_UMIN2;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_BLOCK_UMAX1:
      {
        rezultat = BIT_MA_BLOCK_UMAX1;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_PO_UMAX1:
      {
        rezultat = BIT_MA_PO_UMAX1;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_UMAX1:
      {
        rezultat = BIT_MA_UMAX1;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_BLOCK_UMAX2:
      {
        rezultat = BIT_MA_BLOCK_UMAX2;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_PO_UMAX2:
      {
        rezultat = BIT_MA_PO_UMAX2;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_UMAX2:
      {
        rezultat = BIT_MA_UMAX2;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_OTKL_AVR:
      {
        rezultat = BIT_MA_OTKL_AVR;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_SBROS_BLOCK_AVR:
      {
        rezultat = BIT_MA_SBROS_BLOCK_AVR;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_STAT_BLOCK_AVR:
      {
        rezultat = BIT_MA_STAT_BLOCK_AVR;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_BLOCK_AVR_VID_ZAKHYSTIV:
      {
        rezultat = BIT_MA_BLOCK_AVR_VID_ZAKHYSTIV;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_PO_UAVR_MIN1:
      {
        rezultat = BIT_MA_PO_UAVR_MIN1;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_PO_UAVR_MAX1:
      {
        rezultat = BIT_MA_PO_UAVR_MAX1;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_PO_UAVR_MIN2:
      {
        rezultat = BIT_MA_PO_UAVR_MIN2;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_PO_UAVR_MAX2:
      {
        rezultat = BIT_MA_PO_UAVR_MAX2;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_BLOCK_KRATN_AVR:
      {
        rezultat = BIT_MA_BLOCK_KRATN_AVR;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_PUSK_AVR:
      {
        rezultat = BIT_MA_PUSK_AVR;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_PUSK_AVR_1:
      {
        rezultat = BIT_MA_PUSK_AVR_1;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_PUSK_AVR_2:
      {
        rezultat = BIT_MA_PUSK_AVR_2;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_PO_U_OL:
      {
        rezultat = BIT_MA_PO_U_OL;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_U_OL:
      {
        rezultat = BIT_MA_U_OL;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_PO_U_RL:
      {
        rezultat = BIT_MA_PO_U_RL;
        break;
      }
    case RANG_OUTPUT_LED_DF_REG_U_RL:
      {
        rezultat = BIT_MA_U_RL;
        break;
      }
    default: break;
    }
  }

  return rezultat;
}
/***********************************************************************************/

/***********************************************************************************/
//��������� ���������� ������� ����������
/***********************************************************************************/
void set_previous_ranguvannja(void)
{
  //�������� ������� ������ �������, �� ��� ����� ���� �������, � ���� ����������� �, �� ����� ���������
  for (unsigned int i = 0; i < number_32bit_in_target; i++)
  {
    *(point_to_edited_rang + i) &= ~clear_array_rang[i];
    *(point_to_edited_rang + i) |=    set_array_rang[i];
  }
  
  //��������� ������� ���� � ��������� ����
  clear_array_rang[0] = 0;
  clear_array_rang[1] = 0;
  clear_array_rang[2] = 0;
  clear_array_rang[3] = 0;
  clear_array_rang[4] = 0;
  clear_array_rang[5] = 0;
  
  set_array_rang[0]   = 0;
  set_array_rang[1]   = 0;
  set_array_rang[2]   = 0;
  set_array_rang[3]   = 0;
  set_array_rang[4]   = 0;
  set_array_rang[5]   = 0;
  
  point_to_edited_rang = NULL;
}
/***********************************************************************************/

/***********************************************************************************/
// ��������� ���������� ����������� �����
/***********************************************************************************/
unsigned int save_new_rang_inputs_from_gmm(unsigned int number, unsigned int number_position, unsigned short int data, unsigned int method_setting)
{
  __SETTINGS *target_label;
  if (method_setting == SET_DATA_IMMEDITATE) target_label = &current_settings;
  else target_label = &edition_settings;
  
  unsigned int *point_to_target;
  unsigned int input_value[N_SMALL];
  input_value[0] = current_settings.ranguvannja_inputs[2*number    ];
  input_value[1] = current_settings.ranguvannja_inputs[2*number + 1];
  unsigned int number_function_in_source = 0, index_function_in_source;
  unsigned short error = 0;
  
  //������������ ���� �� ��'��, ���� ����� ����������
  point_to_target = (unsigned int *)target_label->ranguvannja_inputs + N_SMALL*number;

  //����������, �� ����� �������� ���� (���� ��� ����) ������ � �������� �����
  if (point_to_edited_rang != NULL)
  {
    //��� ���������� ���������� ���������� � ����� ������ ���� ����������
    if (point_to_edited_rang != point_to_target)
    {
      //����� �� ���������� �� ���������� ������ �����, ���� �������� ���������� ����� ������ � ��������� ����
      set_previous_ranguvannja();
      
      point_to_edited_rang = point_to_target;
    }
  }
  else
  {
    //�� � ����� �������� �� ���������� � ������ ���� ����������
    point_to_edited_rang = point_to_target;
  }
  
  number_32bit_in_target = N_SMALL;
  
  //����������, �� ���� ������� ����� �������������
  if (data != 0)
  {
    //���� data == 0, �� �� ������, �� ����� ����� ������� �������
    
    if (
        (data == BIT_MA_INPUT_DF1             ) ||
        (data == BIT_MA_INPUT_DF2             ) || 
        (data == BIT_MA_INPUT_DF3             ) || 
        (data == BIT_MA_INPUT_DF4             ) ||
        (data == BIT_MA_INPUT_DF5             ) || 
        (data == BIT_MA_INPUT_DF6             ) || 
        (data == BIT_MA_INPUT_DF7             ) || 
        (data == BIT_MA_INPUT_DF8             ) || 
        (data == BIT_MA_DT1_SET               ) ||
        (data == BIT_MA_DT1_RESET             ) ||
        (data == BIT_MA_DT2_SET               ) ||
        (data == BIT_MA_DT2_RESET             ) ||
        (data == BIT_MA_DT3_SET               ) ||
        (data == BIT_MA_DT3_RESET             ) ||
        (data == BIT_MA_DT4_SET               ) ||
        (data == BIT_MA_DT4_RESET             ) ||
        (data == BIT_MA_BLOCK_VKL_VV          ) || 
        (data == BIT_MA_RESET_LEDS            ) || 
        (data == BIT_MA_RESET_RELES           ) ||
        (data == BIT_MA_MISCEVE_DYSTANCIJNE   ) ||
        (data == BIT_MA_STATE_VV              ) || 
        (data == BIT_MA_OTKL_VID_ZOVN_ZAHYSTIV) ||
        (data == BIT_MA_VKL_VV                ) || 
        (data == BIT_MA_CONTROL_VKL           ) || 
        (data == BIT_MA_OTKL_VV               ) ||
        (data == BIT_MA_CONTROL_VIDKL         ) || 
        (data == BIT_MA_1_GRUPA_USTAVOK       ) || 
        (data == BIT_MA_2_GRUPA_USTAVOK       ) || 
        (data == BIT_MA_3_GRUPA_USTAVOK       ) || 
        (data == BIT_MA_4_GRUPA_USTAVOK       ) ||
        (data == BIT_MA_DVERI_SHAFY_UPR_VIDKR            ) ||
        (data == BIT_MA_ACUMUL_BATAREJA_ROZRJADGENA      ) ||
        (data == BIT_MA_REZERVTE_GYVLENNJA               ) ||
        (data == BIT_MA_RESET_BLOCK_READY_TU_VID_ZAHYSTIV)
       )
    {
      //����� � ��������� ���������� �������� ������ � ����� �� � ����������
      error = 0;
    }
    else if (
             (data == BIT_MA_BLOCK_MTZ1      ) || 
             (data == BIT_MA_BLOCK_MTZ2      ) || 
             (data == BIT_MA_BLOCK_USK_MTZ2  ) ||
             (data == BIT_MA_BLOCK_MTZ3      ) || 
             (data == BIT_MA_BLOCK_MTZ4      ) 
            )
    {
      //����� � ��������� ���������� ������ ��� � ����� �� � ����������
      if ((target_label->configuration & (1 << MTZ_BIT_CONFIGURATION)) !=0 ) error = 0;
      else error = ERROR_ILLEGAL_DATA_VALUE;
    }
    else if (
             (data == BIT_MA_PUSK_ZDZ_VID_DV)
            )
    {
      //����� � ��������� ���������� ������ ��� � ����� �� � ����������
      if ((target_label->configuration & (1 << ZDZ_BIT_CONFIGURATION)) !=0 ) error = 0;
      else error = ERROR_ILLEGAL_DATA_VALUE;
    }
    else if (
             (data == BIT_MA_BLOCK_NZZ)
            )
    {
      //����� � ��������� ���������� ������ ��� � ����� �� � ����������
      if (
          ((target_label->configuration & (1 << ZZ_BIT_CONFIGURATION)) != 0)
         ) error = 0;
      else error = ERROR_ILLEGAL_DATA_VALUE;
    }
    else if (
             (data == BIT_MA_STAT_BLK_APV)
            )
    {
      //����� � ��������� ���������� ������ ��� � ����� �� � ����������
      if ((target_label->configuration & (1 << APV_BIT_CONFIGURATION)) !=0 ) error = 0;
      else error = ERROR_ILLEGAL_DATA_VALUE;
    }
    else if (
             (data == BIT_MA_RESET_BLOCK_APV_ZMN) ||
             (data == BIT_MA_BLOCK_APV_ZMN      )
            )
    {
      //����� � ��������� ���������� ������ ���-��� � ����� �� � ����������
      if ((target_label->configuration & (1 << APV_ZMN_BIT_CONFIGURATION)) !=0 ) error = 0;
      else error = ERROR_ILLEGAL_DATA_VALUE;
    }
    else if (
             (data == BIT_MA_ACHR_CHAPV_VID_DV) ||
             (data == BIT_MA_BLOCK_ACHR       )
            )
    {
      //����� � ��������� ���������� ������ ���/���� � ����� �� � ����������
      if ((target_label->configuration & (1 << ACHR_CHAPV_BIT_CONFIGURATION)) !=0 ) error = 0;
      else error = ERROR_ILLEGAL_DATA_VALUE;
    }
    else if (
             (data == BIT_MA_PUSK_UROV_VID_DV)
            )
    {
      //����� � ��������� ���������� ������ ���� � ����� �� � ����������
      if ((target_label->configuration & (1 << UROV_BIT_CONFIGURATION)) !=0 ) error = 0;
      else error = ERROR_ILLEGAL_DATA_VALUE;
    }
    else if (
             (data == BIT_MA_BLOCK_ZOP)
            )
    {
      //����� � ��������� ���������� ������ ���(���) � ����� �� � ����������
      if ((target_label->configuration & (1 << ZOP_BIT_CONFIGURATION)) !=0 ) error = 0;
      else error = ERROR_ILLEGAL_DATA_VALUE;
    }
    else if (
             (data == BIT_MA_BLOCK_UMIN1) ||
             (data == BIT_MA_BLOCK_UMIN2) ||
             (data == BIT_MA_START_UMIN1) ||
             (data == BIT_MA_START_UMIN2)
            )
    {
      //����� � ��������� ���������� ������ Umin � ����� �� � ����������
      if ((target_label->configuration & (1 << UMIN_BIT_CONFIGURATION)) !=0 ) error = 0;
      else error = ERROR_ILLEGAL_DATA_VALUE;
    }
    else if (
             (data == BIT_MA_BLOCK_UMAX1) ||
             (data == BIT_MA_BLOCK_UMAX2)
            )
    {
      //����� � ��������� ���������� ������ Umax � ����� �� � ����������
      if ((target_label->configuration & (1 << UMAX_BIT_CONFIGURATION)) !=0 ) error = 0;
      else error = ERROR_ILLEGAL_DATA_VALUE;
    }
    else if (
             (data == BIT_MA_OTKL_AVR       ) ||
             (data == BIT_MA_SBROS_BLOCK_AVR) ||
             (data == BIT_MA_STAT_BLOCK_AVR )
            )
    {
      //����� � ��������� ���������� ������ ��� � ����� �� � ����������
      if ((target_label->configuration & (1 << AVR_BIT_CONFIGURATION)) !=0 ) error = 0;
      else error = ERROR_ILLEGAL_DATA_VALUE;
    }
    else
    {
      error = ERROR_ILLEGAL_DATA_VALUE;
    }
  }
  
  //���� ����� ������� � ������������, �� �������� ������� ���������� ���� �����
  if (error != 0) return error;
  
  //ϳ��������� ������� �������, �� ��������� �� ����� ����
  if (
      (input_value[0] != 0) ||
      (input_value[1] != 0)
     )
  {
    //���� �� �������� �� �������, �� �� ������, �� ���� ������� ���������
    //������ ������� ������� ���������� ����� 0, ���� ����� number_function_in_source ������������ ��� ����
    for (unsigned int i = 0; i < NUMBER_TOTAL_SIGNAL_FOR_RANG_INPUT; i++)
    {
      unsigned int offset, shift;
      offset = i >> 5;          //�� �, ��������, ������ �� 32
      shift  = (i & (32 - 1));  //�� �, ��������, ���������� ������ �� ������ �� 32
      if ((input_value[offset] & (1 << shift)) != 0) number_function_in_source++;
    }
  }
  
  if (number_position <= number_function_in_source)
  {
    //��� ������� ������, �� ����� ������ ����� ��� ����������� ������� ��������� ������
    //������ ������ ���������� ���� ������� � ���� �������
    
    //�����, ��� ����� ������ �������, ��� ������� �� ������� ������������� ��� ���������� ������� �  �������� ������� ��� ��
    //� ���� ���������� ���� �������  

    //������ ������� � ������� ��� ����� (�������), ���� ������� ������ ������ ������� Modbus-RTU
    unsigned int i = 0;
    index_function_in_source = 0;
    while ( (i < NUMBER_TOTAL_SIGNAL_FOR_RANG_INPUT) && (index_function_in_source < number_position) )
    {
      unsigned int offset, shift;
      offset = i >> 5;          //�� �, ��������, ������ �� 32
      shift  = (i & (32 - 1));  //�� �, ��������, ���������� ������ �� ������ �� 32
      if ((input_value[offset] & (1 << shift)) != 0) index_function_in_source++;
      if (index_function_in_source < number_position) i++;
    }
    
    if(index_function_in_source == number_position)
    {
      //���� ���� ����� ��������, �� �� ������, �� ��������� �� ���������
      //������� �� ������ ���� ������� ���� ��������������� ���� �������
      _SET_BIT(clear_array_rang, i);
    }
  }
  
  if (data != 0)
  {
    //������������ �������� �������
    switch (data)
    {
    case BIT_MA_INPUT_DF1:
      {
        _SET_BIT(set_array_rang, RANG_INPUT_DF1_IN);
        break;
      }
    case BIT_MA_INPUT_DF2:
      {
        _SET_BIT(set_array_rang, RANG_INPUT_DF2_IN);
        break;
      }
    case BIT_MA_INPUT_DF3:
      {
        _SET_BIT(set_array_rang, RANG_INPUT_DF3_IN);
        break;
      }
    case BIT_MA_INPUT_DF4:
      {
        _SET_BIT(set_array_rang, RANG_INPUT_DF4_IN);
        break;
      }
    case BIT_MA_INPUT_DF5:
      {
        _SET_BIT(set_array_rang, RANG_INPUT_DF5_IN);
        break;
      }
    case BIT_MA_INPUT_DF6:
      {
        _SET_BIT(set_array_rang, RANG_INPUT_DF6_IN);
        break;
      }
    case BIT_MA_INPUT_DF7:
      {
        _SET_BIT(set_array_rang, RANG_INPUT_DF7_IN);
        break;
      }
    case BIT_MA_INPUT_DF8:
      {
        _SET_BIT(set_array_rang, RANG_INPUT_DF8_IN);
        break;
      }
    case BIT_MA_DT1_SET:
      {
        _SET_BIT(set_array_rang, RANG_INPUT_DT1_SET);
        break;
      }
    case BIT_MA_DT1_RESET:
      {
        _SET_BIT(set_array_rang, RANG_INPUT_DT1_RESET);
        break;
      }
    case BIT_MA_DT2_SET:
      {
        _SET_BIT(set_array_rang, RANG_INPUT_DT2_SET);
        break;
      }
    case BIT_MA_DT2_RESET:
      {
        _SET_BIT(set_array_rang, RANG_INPUT_DT2_RESET);
        break;
      }
    case BIT_MA_DT3_SET:
      {
        _SET_BIT(set_array_rang, RANG_INPUT_DT3_SET);
        break;
      }
    case BIT_MA_DT3_RESET:
      {
        _SET_BIT(set_array_rang, RANG_INPUT_DT3_RESET);
        break;
      }
    case BIT_MA_DT4_SET:
      {
        _SET_BIT(set_array_rang, RANG_INPUT_DT4_SET);
        break;
      }
    case BIT_MA_DT4_RESET:
      {
        _SET_BIT(set_array_rang, RANG_INPUT_DT4_RESET);
        break;
      }
    case BIT_MA_BLOCK_VKL_VV:
      {
        _SET_BIT(set_array_rang, RANG_INPUT_BLOCK_VKL_VV);
        break;
      }
    case BIT_MA_RESET_LEDS:
      {
        _SET_BIT(set_array_rang, RANG_INPUT_RESET_LEDS);
        break;
      }
    case BIT_MA_RESET_RELES:
      {
        _SET_BIT(set_array_rang, RANG_INPUT_RESET_RELES);
        break;
      }
    case BIT_MA_MISCEVE_DYSTANCIJNE:
      {
        _SET_BIT(set_array_rang, RANG_INPUT_MISCEVE_DYSTANCIJNE);
        break;
      }
    case BIT_MA_STATE_VV:
      {
        _SET_BIT(set_array_rang, RANG_INPUT_STATE_VV);
        break;
      }
    case BIT_MA_OTKL_VID_ZOVN_ZAHYSTIV:
      {
        _SET_BIT(set_array_rang, RANG_INPUT_OTKL_VID_ZOVN_ZAHYSTIV);
        break;
      }
    case BIT_MA_VKL_VV:
      {
        _SET_BIT(set_array_rang, RANG_INPUT_VKL_VV);
        break;
      }
    case BIT_MA_CONTROL_VKL:
      {
        _SET_BIT(set_array_rang, RANG_INPUT_CTRL_VKL);
        break;
      }
    case BIT_MA_OTKL_VV:
      {
        _SET_BIT(set_array_rang, RANG_INPUT_OTKL_VV);
        break;
      }
    case BIT_MA_CONTROL_VIDKL:
      {
        _SET_BIT(set_array_rang, RANG_INPUT_CTRL_OTKL);
        break;
      }
    case BIT_MA_1_GRUPA_USTAVOK:
      {
        _SET_BIT(set_array_rang, RANG_INPUT_1_GRUPA_USTAVOK);
        break;
      }
    case BIT_MA_2_GRUPA_USTAVOK:
      {
        _SET_BIT(set_array_rang, RANG_INPUT_2_GRUPA_USTAVOK);
        break;
      }
    case BIT_MA_3_GRUPA_USTAVOK:
      {
        _SET_BIT(set_array_rang, RANG_INPUT_3_GRUPA_USTAVOK);
        break;
      }
    case BIT_MA_4_GRUPA_USTAVOK:
      {
        _SET_BIT(set_array_rang, RANG_INPUT_4_GRUPA_USTAVOK);
        break;
      }
    case BIT_MA_DVERI_SHAFY_UPR_VIDKR:
      {
        _SET_BIT(set_array_rang, RANG_INPUT_DVERI_SHAFY_UPR_VIDKR);
        break;
      }
    case BIT_MA_ACUMUL_BATAREJA_ROZRJADGENA:
      {
        _SET_BIT(set_array_rang, RANG_INPUT_ACUMUL_BATAREJA_ROZRJADGENA);
        break;
      }
    case BIT_MA_REZERVTE_GYVLENNJA:
      {
        _SET_BIT(set_array_rang, RANG_INPUT_REZERVTE_GYVLENNJA);
        break;
      }
    case BIT_MA_RESET_BLOCK_READY_TU_VID_ZAHYSTIV:
      {
        _SET_BIT(set_array_rang, RANG_INPUT_RESET_BLOCK_READY_TU_VID_ZAHYSTIV);
        break;
      }
    case BIT_MA_BLOCK_MTZ1:
      {
        _SET_BIT(set_array_rang, RANG_INPUT_BLOCK_MTZ1);
        break;
      }
    case BIT_MA_BLOCK_MTZ2:
      {
        _SET_BIT(set_array_rang, RANG_INPUT_BLOCK_MTZ2);
        break;
      }
    case BIT_MA_BLOCK_USK_MTZ2:
      {
        _SET_BIT(set_array_rang, RANG_INPUT_BLOCK_USK_MTZ2);
        break;
      }
    case BIT_MA_BLOCK_MTZ3:
      {
        _SET_BIT(set_array_rang, RANG_INPUT_BLOCK_MTZ3);
        break;
      }
    case BIT_MA_BLOCK_MTZ4:
      {
        _SET_BIT(set_array_rang, RANG_INPUT_BLOCK_MTZ4);
        break;
      }
    case BIT_MA_PUSK_ZDZ_VID_DV:
      {
        _SET_BIT(set_array_rang, RANG_INPUT_PUSK_ZDZ_VID_DV);
        break;
      }
    case BIT_MA_BLOCK_NZZ:
      {
        _SET_BIT(set_array_rang, RANG_INPUT_BLOCK_NZZ);
        break;
      }
    case BIT_MA_STAT_BLK_APV:
      {
        _SET_BIT(set_array_rang, RANG_INPUT_STAT_BLK_APV);
        break;
      }
    case BIT_MA_RESET_BLOCK_APV_ZMN:
      {
        _SET_BIT(set_array_rang, RANG_INPUT_RESET_BLOCK_APV_ZMN);
        break;
      }
    case BIT_MA_BLOCK_APV_ZMN:
      {
        _SET_BIT(set_array_rang, RANG_INPUT_BLOCK_APV_ZMN);
        break;
      }
    case BIT_MA_ACHR_CHAPV_VID_DV:
      {
        _SET_BIT(set_array_rang, RANG_INPUT_ACHR_CHAPV_VID_DV);
        break;
      }
    case BIT_MA_BLOCK_ACHR:
      {
        _SET_BIT(set_array_rang, RANG_INPUT_BLOCK_ACHR);
        break;
      }
    case BIT_MA_PUSK_UROV_VID_DV:
      {
        _SET_BIT(set_array_rang, RANG_INPUT_PUSK_UROV_VID_DV);
        break;
      }
    case BIT_MA_BLOCK_ZOP:
      {
        _SET_BIT(set_array_rang, RANG_INPUT_BLOCK_ZOP);
        break;
      }
    case BIT_MA_BLOCK_UMIN1:
      {
        _SET_BIT(set_array_rang, RANG_INPUT_BLOCK_UMIN1);
        break;
      }
    case BIT_MA_BLOCK_UMIN2:
      {
        _SET_BIT(set_array_rang, RANG_INPUT_BLOCK_UMIN2);
        break;
      }
    case BIT_MA_START_UMIN1:
      {
        _SET_BIT(set_array_rang, RANG_INPUT_START_UMIN1);
        break;
      }
    case BIT_MA_START_UMIN2:
      {
        _SET_BIT(set_array_rang, RANG_INPUT_START_UMIN2);
        break;
      }
    case BIT_MA_BLOCK_UMAX1:
      {
        _SET_BIT(set_array_rang, RANG_INPUT_BLOCK_UMAX1);
        break;
      }
    case BIT_MA_BLOCK_UMAX2:
      {
        _SET_BIT(set_array_rang, RANG_INPUT_BLOCK_UMAX2);
        break;
      }
    case BIT_MA_OTKL_AVR:
      {
        _SET_BIT(set_array_rang, RANG_INPUT_OTKL_AVR);
        break;
      }
    case BIT_MA_SBROS_BLOCK_AVR:
      {
        _SET_BIT(set_array_rang, RANG_INPUT_SBROS_BLOCK_AVR);
        break;
      }
    case BIT_MA_STAT_BLOCK_AVR:
      {
        _SET_BIT(set_array_rang, RANG_INPUT_STAT_BLOCK_AVR);
        break;
      }
    default:
      {
        //���������� ���� � �������� ����� �� ���� � ��������
        //��� ���� �����, �� ����������� ����������� ��� �������
        error = ERROR_ILLEGAL_DATA_VALUE;
        break;
      }
    }
  }
    
  return error;
}

/***********************************************************************************/

/***********************************************************************************/
// ��������� ���������� ����������� ������ ��� ��������������, ��� ����������� �������, ��� ����������
/***********************************************************************************/
unsigned int save_new_rang_oldr_from_gmm(unsigned int number, unsigned int number_position, unsigned int source, unsigned short int data, unsigned int method_setting)
{
  __SETTINGS *target_label;
  if (method_setting == SET_DATA_IMMEDITATE) target_label = &current_settings;
  else target_label = &edition_settings;
  
  unsigned int *point_to_source, *point_to_target;
  unsigned int input_value[N_BIG];
  unsigned int number_function_in_source = 0, index_function_in_source;
  unsigned short error = 0;
  
  if (source == SOURCE_OUTPUTS_RANG)
  {
    point_to_source = (unsigned int *)current_settings.ranguvannja_outputs + N_BIG*number;
    point_to_target = (unsigned int *)target_label->ranguvannja_outputs + N_BIG*number;
  }
  else if (source == SOURCE_LEDS_RANG)
  {
    point_to_source = (unsigned int *)current_settings.ranguvannja_leds + N_BIG*number;
    point_to_target = (unsigned int *)target_label->ranguvannja_leds + N_BIG*number;
  }
  else if (source == SOURCE_DF_PLUS_RANG)
  {
    point_to_source = (unsigned int *)current_settings.ranguvannja_df_source_plus + N_BIG*number;
    point_to_target = (unsigned int *)target_label->ranguvannja_df_source_plus + N_BIG*number;
  }
  else if (source == SOURCE_DF_MINUS_RANG)
  {
    point_to_source = (unsigned int *)current_settings.ranguvannja_df_source_minus + N_BIG*number;
    point_to_target = (unsigned int *)target_label->ranguvannja_df_source_minus + N_BIG*number;
  }
  else if (source == SOURCE_DF_BLK_RANG)
  {
    point_to_source = (unsigned int *)current_settings.ranguvannja_df_source_blk + N_BIG*number;
    point_to_target = (unsigned int *)target_label->ranguvannja_df_source_blk + N_BIG*number;
  }
  else if (source == SOURCE_AR_RANG)
  {
    point_to_source = (unsigned int *)current_settings.ranguvannja_analog_registrator;
    point_to_target = (unsigned int *)target_label->ranguvannja_analog_registrator;
  }
  else if (source == SOURCE_DR_RANG)
  {
    point_to_source = (unsigned int *)current_settings.ranguvannja_digital_registrator;
    point_to_target = (unsigned int *)target_label->ranguvannja_digital_registrator;
  }
  else if (source == SOURCE_SET_DT_PLUS_RANG)
  {
    point_to_source = (unsigned int *)current_settings.ranguvannja_set_dt_source_plus + N_BIG*number;
    point_to_target = (unsigned int *)target_label->ranguvannja_set_dt_source_plus + N_BIG*number;
  }
  else if (source == SOURCE_SET_DT_MINUS_RANG)
  {
    point_to_source = (unsigned int *)current_settings.ranguvannja_set_dt_source_minus + N_BIG*number;
    point_to_target = (unsigned int *)target_label->ranguvannja_set_dt_source_minus + N_BIG*number;
  }
  else if (source == SOURCE_RESET_DT_PLUS_RANG)
  {
    point_to_source = (unsigned int *)current_settings.ranguvannja_reset_dt_source_plus + N_BIG*number;
    point_to_target = (unsigned int *)target_label->ranguvannja_reset_dt_source_plus + N_BIG*number;
  }
  else if (source == SOURCE_RESET_DT_MINUS_RANG)
  {
    point_to_source = (unsigned int *)current_settings.ranguvannja_reset_dt_source_minus + N_BIG*number;
    point_to_target = (unsigned int *)target_label->ranguvannja_reset_dt_source_minus + N_BIG*number;
  }

  //����������, �� ����� �������� ���� (���� ��� ����) ������ � �������� �����
  if (point_to_edited_rang != NULL)
  {
    //��� ���������� ���������� ���������� � ����� ������ ���� ����������
    if (point_to_edited_rang != point_to_target)
    {
      //����� �� ���������� �� ���������� ������ ��'����, ���� �������� ���������� ����� ������ � �������  ��'���
      set_previous_ranguvannja();
      
      point_to_edited_rang = point_to_target;
    }
  }
  else
  {
    //�� � ����� �������� �� ���������� � ������ ���� ����������
    point_to_edited_rang = point_to_target;
  }
  
  //������������ ���� �� ��'��, ���� ����� ����������
  number_32bit_in_target = N_BIG;
  
  input_value[0] = *(point_to_source    );
  input_value[1] = *(point_to_source + 1);
  input_value[2] = *(point_to_source + 2);
  input_value[3] = *(point_to_source + 3);
  input_value[4] = *(point_to_source + 4);
  input_value[5] = *(point_to_source + 5);

  //����������, �� ���� ������� ����� �������������
  if (data != 0)
  {
    //���� data == 0, �� �� ������, �� ����� ����� ������� �������
    
    if (
        (data == BIT_MA_INPUT_DF1             ) || 
        (data == BIT_MA_OUTPUT_DF1            ) || 
        (data == BIT_MA_INPUT_DF2             ) || 
        (data == BIT_MA_OUTPUT_DF2            ) ||
        (data == BIT_MA_INPUT_DF3             ) || 
        (data == BIT_MA_OUTPUT_DF3            ) || 
        (data == BIT_MA_INPUT_DF4             ) || 
        (data == BIT_MA_OUTPUT_DF4            ) ||
        (data == BIT_MA_INPUT_DF5             ) || 
        (data == BIT_MA_OUTPUT_DF5            ) || 
        (data == BIT_MA_INPUT_DF6             ) || 
        (data == BIT_MA_OUTPUT_DF6            ) || 
        (data == BIT_MA_INPUT_DF7             ) || 
        (data == BIT_MA_OUTPUT_DF7            ) || 
        (data == BIT_MA_INPUT_DF8             ) || 
        (data == BIT_MA_OUTPUT_DF8            ) || 
        (data == BIT_MA_DT1_SET               ) ||
        (data == BIT_MA_DT1_RESET             ) ||
        (data == BIT_MA_DT1_OUT               ) ||
        (data == BIT_MA_DT2_SET               ) ||
        (data == BIT_MA_DT2_RESET             ) ||
        (data == BIT_MA_DT2_OUT               ) ||
        (data == BIT_MA_DT3_SET               ) ||
        (data == BIT_MA_DT3_RESET             ) ||
        (data == BIT_MA_DT3_OUT               ) ||
        (data == BIT_MA_DT4_SET               ) ||
        (data == BIT_MA_DT4_RESET             ) ||
        (data == BIT_MA_DT4_OUT               ) ||
        (data == BIT_MA_BLOCK_VKL_VV          ) || 
        (data == BIT_MA_RESET_LEDS            ) ||
        (data == BIT_MA_RESET_RELES           ) || 
        (data == BIT_MA_MISCEVE_DYSTANCIJNE   ) || 
        (data == BIT_MA_STATE_VV              ) || 
        (data == BIT_MA_OTKL_VID_ZOVN_ZAHYSTIV) ||
        (data == BIT_MA_VKL_VV                ) || 
        (data == BIT_MA_CONTROL_VKL           ) || 
        (data == BIT_MA_OTKL_VV               ) || 
        (data == BIT_MA_CONTROL_VIDKL         ) || 
        (data == BIT_MA_GEAR_VV               ) || 
        (data == BIT_MA_PEREVYSHCHENNJA_Inom_VYMK   ) || 
        (data == BIT_MA_KRYTYCHNYJ_RESURS_VYMYKACHA ) || 
        (data == BIT_MA_VYCHERPANYJ_RESURS_VYMYKACHA) || 
        (data == BIT_MA_DEFECT                ) || 
        (data == BIT_MA_AVAR_DEFECT           ) || 
        (data == BIT_MA_WORK_A_REJESTRATOR    ) || 
        (data == BIT_MA_WORK_D_REJESTRATOR    ) || 
        (data == BIT_MA_WORK_BO               ) || 
        (data == BIT_MA_WORK_BV               ) || 
        (data == BIT_MA_1_GRUPA_USTAVOK       ) || 
        (data == BIT_MA_2_GRUPA_USTAVOK       ) || 
        (data == BIT_MA_3_GRUPA_USTAVOK       ) || 
        (data == BIT_MA_4_GRUPA_USTAVOK       ) || 
        (data == BIT_MA_DVERI_SHAFY_UPR_VIDKR            ) || 
        (data == BIT_MA_ACUMUL_BATAREJA_ROZRJADGENA      ) || 
        (data == BIT_MA_REZERVTE_GYVLENNJA               ) || 
        (data == BIT_MA_VIDKL_VID_ZAKHYSTIV              ) || 
        (data == BIT_MA_BLK_GRUP_USTAVOK_VID_ZACHYSTIV   ) || 
        (data == BIT_MA_INVERS_DV_GRUPA_USTAVOK          ) || 
        (data == BIT_MA_READY_TU                         ) || 
        (data == BIT_MA_RESET_BLOCK_READY_TU_VID_ZAHYSTIV) 
       )
    {
      //����� � ��������� ���������� �������� ������ � ����� �� � ����������

      //����������, �� ����� �� ������� ����������� �� ���� �������
      if (
          (
           (
            (source == SOURCE_DF_PLUS_RANG)  ||
            (source == SOURCE_DF_MINUS_RANG) ||
            (source == SOURCE_DF_BLK_RANG)
           )   
           &
           (
            ((number == 0) && ((data == BIT_MA_INPUT_DF1) || (data == BIT_MA_OUTPUT_DF1))) ||
            ((number == 1) && ((data == BIT_MA_INPUT_DF2) || (data == BIT_MA_OUTPUT_DF2))) ||
            ((number == 2) && ((data == BIT_MA_INPUT_DF3) || (data == BIT_MA_OUTPUT_DF3))) ||
            ((number == 3) && ((data == BIT_MA_INPUT_DF4) || (data == BIT_MA_OUTPUT_DF4))) ||
            ((number == 4) && ((data == BIT_MA_INPUT_DF5) || (data == BIT_MA_OUTPUT_DF5))) ||
            ((number == 5) && ((data == BIT_MA_INPUT_DF6) || (data == BIT_MA_OUTPUT_DF6))) ||
            ((number == 6) && ((data == BIT_MA_INPUT_DF7) || (data == BIT_MA_OUTPUT_DF7))) ||
            ((number == 7) && ((data == BIT_MA_INPUT_DF8) || (data == BIT_MA_OUTPUT_DF8)))
           )
          )
          ||
          (
           (
            (source == SOURCE_SET_DT_PLUS_RANG)    ||
            (source == SOURCE_SET_DT_MINUS_RANG)   ||
            (source == SOURCE_RESET_DT_PLUS_RANG)  ||
            (source == SOURCE_RESET_DT_MINUS_RANG)
           )
           &
           (
            ( (number == 0) && ((data == BIT_MA_DT1_SET) || (data == BIT_MA_DT1_RESET) || (data == BIT_MA_DT1_OUT) ) ) ||
            ( (number == 1) && ((data == BIT_MA_DT2_SET) || (data == BIT_MA_DT2_RESET) || (data == BIT_MA_DT2_OUT) ) ) ||
            ( (number == 2) && ((data == BIT_MA_DT3_SET) || (data == BIT_MA_DT3_RESET) || (data == BIT_MA_DT3_OUT) ) ) ||
            ( (number == 3) && ((data == BIT_MA_DT4_SET) || (data == BIT_MA_DT4_RESET) || (data == BIT_MA_DT4_OUT) ) )
           )
          )
          ||
          (
           (source == SOURCE_AR_RANG) & (data == BIT_MA_WORK_A_REJESTRATOR)
          )
          ||
          (
           (source == SOURCE_DR_RANG) & (data == BIT_MA_WORK_D_REJESTRATOR)
          )
         ) error = ERROR_ILLEGAL_DATA_VALUE;  
      else if(
              (
               (source == SOURCE_OUTPUTS_RANG)
               &&
               (method_setting == SET_DATA_IMMEDITATE)
               &&
               ((data == BIT_MA_WORK_BO) || (data == BIT_MA_WORK_BV))
              )
             )   
      {
        /*
        ����� � ������ ���������� "������ ��" ��� "������ ��" �� ���������� �����
        ������� ������� ���������� (����� ����������� � ���� ���������� ����� �� ����
        ������ ����� ������������ ���������� ��� ������� �� ��� �������� ������, �� ����
        ���� ���� ��� �������� ������� 16, ���� �������� ������������ ����� �������, � ���� ������
        �� ���� ������� � ������ ���� ��� �������� �� "��������������" � ������ �����)
        ����� ���������, �� �� ������ ����� ���� ��������� �� �
        ���� ��������� �� ���� ���������� � ������������ � ����� ��������� ��� �������
        */
        unsigned int maska_function[N_BIG] = {0, 0, 0, 0, 0, 0};
        if (data == BIT_MA_WORK_BO)
        {
           _SET_BIT(maska_function, RANG_OUTPUT_LED_DF_REG_WORK_BO);
        }
        else
        {
           _SET_BIT(maska_function, RANG_OUTPUT_LED_DF_REG_WORK_BV);
        }
        
        unsigned int flag_fix_setting_function = 0;
        unsigned int i = 0;
        while ((i < NUMBER_OUTPUTS) && (flag_fix_setting_function == 0))
        {
          if (i != number)
          {
            //���������� ����� � ������ �� ����� �� ����������
            if (
                (((*(target_label->ranguvannja_outputs + N_BIG*i    )) & maska_function[0]) != 0)
                ||
                (((*(target_label->ranguvannja_outputs + N_BIG*i + 1)) & maska_function[1]) != 0)
                ||
                (((*(target_label->ranguvannja_outputs + N_BIG*i + 2)) & maska_function[2]) != 0)
                ||
                (((*(target_label->ranguvannja_outputs + N_BIG*i + 3)) & maska_function[3]) != 0)
                ||
                (((*(target_label->ranguvannja_outputs + N_BIG*i + 4)) & maska_function[4]) != 0)
                ||
                (((*(target_label->ranguvannja_outputs + N_BIG*i + 5)) & maska_function[5]) != 0)
               ) 
              flag_fix_setting_function = 1;
          }
          
          i++;
        }
        
        //�����������, �� ��� ���� ������� ����������� �� ����� �������, ���� ����������� ��� �������
        if (flag_fix_setting_function != 0) error = ERROR_ILLEGAL_DATA_VALUE;
      }
    }
    else if (
             (data == BIT_MA_BLOCK_MTZ1         ) || 
             (data == BIT_MA_BLOCK_MTZ2         ) || 
             (data == BIT_MA_BLOCK_USK_MTZ2     ) || 
             (data == BIT_MA_BLOCK_MTZ3         ) || 
             (data == BIT_MA_BLOCK_MTZ4         ) || 
             (data == BIT_MA_SECTOR_VPERED_MTZN1) || 
             (data == BIT_MA_SECTOR_NAZAD_MTZN1 ) || 
             (data == BIT_MA_PO_MTZ1            ) || 
             (data == BIT_MA_PO_MTZN1_VPERED    ) || 
             (data == BIT_MA_PO_MTZN1_NAZAD     ) || 
             (data == BIT_MA_PO_U_MTZPN1        ) || 
             (data == BIT_MA_PO_MTZPN1          ) || 
             (data == BIT_MA_MTZ1               ) ||
             (data == BIT_MA_SECTOR_VPERED_MTZN2) || 
             (data == BIT_MA_SECTOR_NAZAD_MTZN2 ) || 
             (data == BIT_MA_PO_MTZ2            ) || 
             (data == BIT_MA_PO_MTZN2_VPERED    ) || 
             (data == BIT_MA_PO_MTZN2_NAZAD     ) || 
             (data == BIT_MA_PO_U_MTZPN2        ) || 
             (data == BIT_MA_PO_MTZPN2          ) || 
             (data == BIT_MA_MTZ2               ) || 
             (data == BIT_MA_SECTOR_VPERED_MTZN3) || 
             (data == BIT_MA_SECTOR_NAZAD_MTZN3 ) || 
             (data == BIT_MA_PO_MTZ3            ) || 
             (data == BIT_MA_PO_MTZN3_VPERED    ) || 
             (data == BIT_MA_PO_MTZN3_NAZAD     ) || 
             (data == BIT_MA_PO_U_MTZPN3        ) || 
             (data == BIT_MA_PO_MTZPN3          ) || 
             (data == BIT_MA_MTZ3               ) ||
             (data == BIT_MA_SECTOR_VPERED_MTZN4) || 
             (data == BIT_MA_SECTOR_NAZAD_MTZN4 ) || 
             (data == BIT_MA_PO_MTZ4            ) || 
             (data == BIT_MA_PO_MTZN4_VPERED    ) || 
             (data == BIT_MA_PO_MTZN4_NAZAD     ) || 
             (data == BIT_MA_PO_U_MTZPN4        ) || 
             (data == BIT_MA_PO_MTZPN4          ) || 
             (data == BIT_MA_MTZ4               ) ||
             (data == BIT_MA_PO_BLOCK_U_MTZN    ) || 
             (data == BIT_MA_NCN_MTZ            ) 
            )
    {
      //����� � ��������� ���������� ������ ��� � ����� �� � ����������
      if ((target_label->configuration & (1 << MTZ_BIT_CONFIGURATION)) !=0 ) error = 0;
      else error = ERROR_ILLEGAL_DATA_VALUE;
    }
    else if (
             (data == BIT_MA_PUSK_ZDZ_VID_DV) || 
             (data == BIT_MA_ZDZ            )
            )
    {
      //����� � ��������� ���������� ������ ��� � ����� �� � ����������
      if ((target_label->configuration & (1 << ZDZ_BIT_CONFIGURATION)) !=0 ) error = 0;
      else error = ERROR_ILLEGAL_DATA_VALUE;
    }
    else if (
             (data == BIT_MA_BLOCK_NZZ ) || 
             (data == BIT_MA_PO_NZZ    ) || 
             (data == BIT_MA_NZZ       ) || 
             (data == BIT_MA_PO_ZZ1_3I0) || 
             (data == BIT_MA_ZZ1_3I0   ) ||
             (data == BIT_MA_PO_ZZ_3U0 ) || 
             (data == BIT_MA_ZZ_3U0    ) || 
             (data == BIT_MA_SECTOR_NZZ) 
            )
    {
      //����� � ��������� ���������� ������ �� � ����� �� � ����������
      if (
          ((target_label->configuration & (1 << ZZ_BIT_CONFIGURATION)) !=0 )
          &&  
          (
           (data == BIT_MA_BLOCK_NZZ ) || 
           (data == BIT_MA_PO_ZZ1_3I0) || 
           (data == BIT_MA_ZZ1_3I0   ) ||
           (
            ((target_label->control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_3U0_Ubc_TN2) == 0) &&
            (
            (data == BIT_MA_PO_ZZ_3U0) || 
            (data == BIT_MA_ZZ_3U0   ) ||
            ((target_label->control_zz & CTR_ZZ1_TYPE) == 0)  
            ) 
           ) 
          ) 
         )   
      {
        error = 0;
      }
      else error = ERROR_ILLEGAL_DATA_VALUE;
    }
    else if (
             (data == BIT_MA_STAT_BLK_APV) || 
             (data == BIT_MA_APV         ) ||
             (data == BIT_MA_APV2        ) ||
             (data == BIT_MA_APV3        ) ||
             (data == BIT_MA_APV4        ) ||
             (data == BIT_MA_APV_WORK    )
            )
    {
      //����� � ��������� ���������� ������ ��� � ����� �� � ����������
      if ((target_label->configuration & (1 << APV_BIT_CONFIGURATION)) !=0 ) error = 0;
      else error = ERROR_ILLEGAL_DATA_VALUE;
    }
    else if (
             (data == BIT_MA_RESET_BLOCK_APV_ZMN        ) || 
             (data == BIT_MA_BLOCK_APV_ZMN              ) ||
             (data == BIT_MA_PO_UAPV_ZMN1               ) ||
             (data == BIT_MA_PO_UAPV_ZMN2               ) ||
             (data == BIT_MA_PO_APV_ZMN                 ) ||
             (data == BIT_MA_APV_ZMN                    ) ||
             (data == BIT_MA_BLOCK_KRATN_APV_ZMN        ) ||
             (data == BIT_MA_BLOCK_APV_ZMN_VID_ZAKHYSTIV)
            )
    {
      //����� � ��������� ���������� ������ ���-��� � ����� �� � ����������
      if ((target_label->configuration & (1 << APV_ZMN_BIT_CONFIGURATION)) !=0 ) error = 0;
      else error = ERROR_ILLEGAL_DATA_VALUE;
    }
    else if (
             (data == BIT_MA_ACHR_CHAPV_VID_DV) ||
             (data == BIT_MA_BLOCK_ACHR       ) ||
             (data == BIT_MA_BLOCK_CHAPV_VID_U) ||
             (data == BIT_MA_PO_F1_ACHR       ) ||
             (data == BIT_MA_PO_F2_ACHR       ) ||
             (data == BIT_MA_F1_ACHR_CHAPV    ) ||
             (data == BIT_MA_F2_ACHR_CHAPV    ) ||
             (data == BIT_MA_ACHR_CHAPV       ) ||
             (data == BIT_MA_RAZR_CHAPV       ) ||
             (data == BIT_MA_PO_F1_CHAPV      ) ||
             (data == BIT_MA_PO_F2_CHAPV      )
            )
    {
      //����� � ��������� ���������� ������ ���/���� � ����� �� � ����������
      if ((target_label->configuration & (1 << ACHR_CHAPV_BIT_CONFIGURATION)) !=0 ) error = 0;
      else error = ERROR_ILLEGAL_DATA_VALUE;
    }
    else if (
             (data == BIT_MA_PUSK_UROV_VID_DV) || 
             (data == BIT_MA_PO_UROV         ) || 
             (data == BIT_MA_UROV1           ) || 
             (data == BIT_MA_UROV2           )
            )
    {
      //����� � ��������� ���������� ������ ���� � ����� �� � ����������
      if ((target_label->configuration & (1 << UROV_BIT_CONFIGURATION)) !=0 ) error = 0;
      else error = ERROR_ILLEGAL_DATA_VALUE;
    }
    else if (
             (data == BIT_MA_BLOCK_ZOP) || 
             (data == BIT_MA_PO_ZOP   ) || 
             (data == BIT_MA_ZOP      )
            )
    {
      //����� � ��������� ���������� ������ ���(���) � ����� �� � ����������
      if ((target_label->configuration & (1 << ZOP_BIT_CONFIGURATION)) !=0 ) error = 0;
      else error = ERROR_ILLEGAL_DATA_VALUE;
    }
    else if (
             (data == BIT_MA_BLOCK_UMIN1  ) || 
             (data == BIT_MA_PO_UBLK_UMIN1) || 
             (data == BIT_MA_PO_IBLK_UMIN1) || 
             (data == BIT_MA_UMIN1        ) || 
             (data == BIT_MA_PO_UMIN1     ) || 
             (data == BIT_MA_BLOCK_UMIN2  ) || 
             (data == BIT_MA_UMIN2        ) || 
             (data == BIT_MA_PO_UMIN2     ) || 
             (data == BIT_MA_START_UMIN1  ) || 
             (data == BIT_MA_START_UMIN2  ) ||
             (data == BIT_MA_PO_UBLK_UMIN2) ||
             (data == BIT_MA_PO_IBLK_UMIN2)
            )
    {
      //����� � ��������� ���������� ������ Umin � ����� �� � ����������
      if ((target_label->configuration & (1 << UMIN_BIT_CONFIGURATION)) !=0 ) error = 0;
      else error = ERROR_ILLEGAL_DATA_VALUE;
    }
    else if (
             (data == BIT_MA_BLOCK_UMAX1) || 
             (data == BIT_MA_PO_UMAX1   ) || 
             (data == BIT_MA_UMAX1      ) || 
             (data == BIT_MA_BLOCK_UMAX2) || 
             (data == BIT_MA_PO_UMAX2   ) || 
             (data == BIT_MA_UMAX2      )
            )
    {
      //����� � ��������� ���������� ������ Umax � ����� �� � ����������
      if ((target_label->configuration & (1 << UMAX_BIT_CONFIGURATION)) !=0 ) error = 0;
      else error = ERROR_ILLEGAL_DATA_VALUE;
    }
    else if (
             (data == BIT_MA_OTKL_AVR               ) || 
             (data == BIT_MA_SBROS_BLOCK_AVR        ) || 
             (data == BIT_MA_STAT_BLOCK_AVR         ) || 
             (data == BIT_MA_PO_UAVR_MIN1           ) || 
             (data == BIT_MA_PO_UAVR_MAX1           ) || 
             (data == BIT_MA_PO_UAVR_MIN2           ) || 
             (data == BIT_MA_PO_UAVR_MAX2           ) || 
             (data == BIT_MA_BLOCK_AVR_VID_ZAKHYSTIV) || 
             (data == BIT_MA_BLOCK_KRATN_AVR        ) || 
             (data == BIT_MA_PUSK_AVR               ) ||
             (data == BIT_MA_PUSK_AVR_1             ) ||
             (data == BIT_MA_PUSK_AVR_2             )
            )
    {
      //����� � ��������� ���������� ������ ��� � ����� �� � ����������
      if ((target_label->configuration & (1 << AVR_BIT_CONFIGURATION)) !=0 ) error = 0;
      else error = ERROR_ILLEGAL_DATA_VALUE;
    }
    else if (
             (data == BIT_MA_PO_U_OL) || 
             (data == BIT_MA_U_OL   ) ||
             (data == BIT_MA_PO_U_RL) ||
             (data == BIT_MA_U_RL   )
            )
    {
      //����� � ��������� ���������� ������ ����� � ����� �� � ����������
      if ((target_label->configuration & (1 << CONTROL_U_BIT_CONFIGURATION)) !=0 ) error = 0;
      else error = ERROR_ILLEGAL_DATA_VALUE;
    }
    else
    {
      error = ERROR_ILLEGAL_DATA_VALUE;
    }
  }
  
  //���� ����� ������� � ������������, �� �������� ������� ���������� ���� �����
  if (error != 0) return error;
  
  //ϳ��������� ������� �������, �� ��������� �� ����� ����
  if (
      (input_value[0] != 0) ||
      (input_value[1] != 0) ||
      (input_value[2] != 0) ||
      (input_value[3] != 0) ||
      (input_value[4] != 0) ||
      (input_value[5] != 0)
     )
  {
    //���� �� �������� �� �������, �� �� ������, �� ���� ������� ���������
    //������ ������� ������� ���������� ����� 0, ���� ����� number_function_in_source ������������ ��� ����
    for (unsigned int i = 0; i < NUMBER_TOTAL_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG; i++)
    {
      unsigned int offset, shift;
      offset = i >> 5;          //�� �, ��������, ������ �� 32
      shift  = (i & (32 - 1));  //�� �, ��������, ���������� ������ �� ������ �� 32
      if ((input_value[offset] & (1 << shift)) != 0) number_function_in_source++;
    }
  }
  
  if (number_position <= number_function_in_source)
  {
    //��� ������� ������, �� ����� ������ ����� ��� ����������� ������� ��������� ������
    //������ ������ ���������� ���� ������� � ���� �������
    
    //�����, ��� ����� ������ �������, ��� ������� �� ������� ������������� ��� ���������� ������� �  �������� ������� ��� ��
    //� ���� ���������� ���� �������  

    //������ ������� � ������� ��� ����� (�������), ���� ������� ������ ������ ������� Modbus-RTU
    unsigned int i = 0;
    index_function_in_source = 0;
    while ( (i < NUMBER_TOTAL_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG) && (index_function_in_source < number_position) )
    {
      unsigned int offset, shift;
      offset = i >> 5;          //�� �, ��������, ������ �� 32
      shift  = (i & (32 - 1));  //�� �, ��������, ���������� ������ �� ������ �� 32
      if ((input_value[offset] & (1 << shift)) != 0) index_function_in_source++;
      if (index_function_in_source < number_position) i++;
    }
    
    if(index_function_in_source == number_position)
    {
      //���� ���� ����� ��������, �� �� ������, �� ��������� �� ���������
      //������� �� ������ ���� ������� ���� ��������������� ���� �������
      _SET_BIT(clear_array_rang, i);
    }
  }
  
  if (data != 0)
  {
    //������������ �������� �������
    switch (data)
    {
    case BIT_MA_INPUT_DF1:
      {
         _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_DF1_IN);
        break;
      }
    case BIT_MA_OUTPUT_DF1:
      {
         _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_DF1_OUT);
        break;
      }
    case BIT_MA_INPUT_DF2:
      {
         _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_DF2_IN);
        break;
      }
    case BIT_MA_OUTPUT_DF2:
      {
         _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_DF2_OUT);
        break;
      }
    case BIT_MA_INPUT_DF3:
      {
         _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_DF3_IN);
        break;
      }
    case BIT_MA_OUTPUT_DF3:
      {
         _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_DF3_OUT);
        break;
      }
    case BIT_MA_INPUT_DF4:
      {
         _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_DF4_IN);
        break;
      }
    case BIT_MA_OUTPUT_DF4:
      {
         _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_DF4_OUT);
        break;
      }
    case BIT_MA_INPUT_DF5:
      {
         _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_DF5_IN);
        break;
      }
    case BIT_MA_OUTPUT_DF5:
      {
         _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_DF5_OUT);
        break;
      }
    case BIT_MA_INPUT_DF6:
      {
         _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_DF6_IN);
        break;
      }
    case BIT_MA_OUTPUT_DF6:
      {
         _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_DF6_OUT);
        break;
      }
    case BIT_MA_INPUT_DF7:
      {
         _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_DF7_IN);
        break;
      }
    case BIT_MA_OUTPUT_DF7:
      {
         _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_DF7_OUT);
        break;
      }
    case BIT_MA_INPUT_DF8:
      {
         _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_DF8_IN);
        break;
      }
    case BIT_MA_OUTPUT_DF8:
      {
         _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_DF8_OUT);
        break;
      }
    case BIT_MA_DT1_SET:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_DT1_SET);
        break;
      }
    case BIT_MA_DT1_RESET:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_DT1_RESET);
        break;
      }
    case BIT_MA_DT1_OUT:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_DT1_OUT);
        break;
      }
    case BIT_MA_DT2_SET:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_DT2_SET);
        break;
      }
    case BIT_MA_DT2_RESET:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_DT2_RESET);
        break;
      }
    case BIT_MA_DT2_OUT:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_DT2_OUT);
        break;
      }
    case BIT_MA_DT3_SET:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_DT3_SET);
        break;
      }
    case BIT_MA_DT3_RESET:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_DT3_RESET);
        break;
      }
    case BIT_MA_DT3_OUT:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_DT3_OUT);
        break;
      }
    case BIT_MA_DT4_SET:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_DT4_SET);
        break;
      }
    case BIT_MA_DT4_RESET:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_DT4_RESET);
        break;
      }
    case BIT_MA_DT4_OUT:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_DT4_OUT);
        break;
      }
    case BIT_MA_BLOCK_VKL_VV:
      {
         _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_BLOCK_VKL_VV);
        break;
      }
    case BIT_MA_RESET_LEDS:
      {
         _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_RESET_LEDS);
        break;
      }
    case BIT_MA_RESET_RELES:
      {
         _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_RESET_RELES);
        break;
      }
    case BIT_MA_MISCEVE_DYSTANCIJNE:
      {
         _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_MISCEVE_DYSTANCIJNE);
        break;
      }
    case BIT_MA_STATE_VV:
      {
         _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_STATE_VV);
        break;
      }
    case BIT_MA_OTKL_VID_ZOVN_ZAHYSTIV:
      {
         _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_OTKL_VID_ZOVN_ZAHYSTIV);
        break;
      }
    case BIT_MA_VKL_VV:
      {
         _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_VKL_VV);
        break;
      }
    case BIT_MA_CONTROL_VKL:
      {
         _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_CTRL_VKL);
        break;
      }
    case BIT_MA_OTKL_VV:
      {
         _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_OTKL_VV);
        break;
      }
    case BIT_MA_CONTROL_VIDKL:
      {
         _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_CTRL_OTKL);
        break;
      }
    case BIT_MA_GEAR_VV:
      {
         _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_PRYVID_VV);
        break;
      }
    case BIT_MA_PEREVYSHCHENNJA_Inom_VYMK:
      {
         _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_PEREVYSHCHENNJA_Inom_VYMK);
        break;
      }
    case BIT_MA_KRYTYCHNYJ_RESURS_VYMYKACHA:
      {
         _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_KRYTYCHNYJ_RESURS_VYMYKACHA);
        break;
      }
    case BIT_MA_VYCHERPANYJ_RESURS_VYMYKACHA:
      {
         _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_VYCHERPANYJ_RESURS_VYMYKACHA);
        break;
      }
    case BIT_MA_DEFECT:
      {
         _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_DEFECT);
        break;
      }
    case BIT_MA_AVAR_DEFECT:
      {
         _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_AVAR_DEFECT);
        break;
      }
    case BIT_MA_WORK_A_REJESTRATOR:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_WORK_A_REJESTRATOR);
        break;
      }
    case BIT_MA_WORK_D_REJESTRATOR:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_WORK_D_REJESTRATOR);
        break;
      }
    case BIT_MA_WORK_BO:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_WORK_BO);
        break;
      }
    case BIT_MA_WORK_BV:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_WORK_BV);
        break;
      }
    case BIT_MA_1_GRUPA_USTAVOK:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_1_GRUPA_USTAVOK);
        break;
      }
    case BIT_MA_2_GRUPA_USTAVOK:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_2_GRUPA_USTAVOK);
        break;
      }
    case BIT_MA_3_GRUPA_USTAVOK:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_3_GRUPA_USTAVOK);
        break;
      }
    case BIT_MA_4_GRUPA_USTAVOK:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_4_GRUPA_USTAVOK);
        break;
      }
    case BIT_MA_DVERI_SHAFY_UPR_VIDKR:
      {
         _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_DVERI_SHAFY_UPR_VIDKR);
        break;
      }
    case BIT_MA_ACUMUL_BATAREJA_ROZRJADGENA:
      {
         _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_ACUMUL_BATAREJA_ROZRJADGENA);
        break;
      }
    case BIT_MA_REZERVTE_GYVLENNJA:
      {
         _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_REZERVTE_GYVLENNJA);
        break;
      }
    case BIT_MA_VIDKL_VID_ZAKHYSTIV:
      {
         _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_VIDKL_VID_ZAKHYSTIV);
        break;
      }
    case BIT_MA_BLK_GRUP_USTAVOK_VID_ZACHYSTIV:
      {
         _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_BLK_GRUP_USTAVOK_VID_ZACHYSTIV);
        break;
      }
    case BIT_MA_INVERS_DV_GRUPA_USTAVOK:
      {
         _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_INVERS_DV_GRUPA_USTAVOK);
        break;
      }
    case BIT_MA_READY_TU:
      {
         _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_READY_TU);
        break;
      }
    case BIT_MA_RESET_BLOCK_READY_TU_VID_ZAHYSTIV:
      {
         _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_RESET_BLOCK_READY_TU_VID_ZAHYSTIV);
        break;
      }
    case BIT_MA_BLOCK_MTZ1:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_BLOCK_MTZ1);
        break;
      }
    case BIT_MA_BLOCK_MTZ2:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_BLOCK_MTZ2);
        break;
      }
    case BIT_MA_BLOCK_USK_MTZ2:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_BLOCK_USK_MTZ2);
        break;
      }
    case BIT_MA_BLOCK_MTZ3:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_BLOCK_MTZ3);
        break;
      }
    case BIT_MA_BLOCK_MTZ4:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_BLOCK_MTZ4);
        break;
      }
    case BIT_MA_SECTOR_VPERED_MTZN1:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_SECTOR_VPERED_MTZN1);
        break;
      }
    case BIT_MA_SECTOR_NAZAD_MTZN1:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_SECTOR_NAZAD_MTZN1);
        break;
      }
    case BIT_MA_PO_MTZ1:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_PO_MTZ1);
        break;
      }
    case BIT_MA_PO_MTZN1_VPERED:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_PO_MTZN1_VPERED);
        break;
      }
    case BIT_MA_PO_MTZN1_NAZAD:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_PO_MTZN1_NAZAD);
        break;
      }
    case BIT_MA_PO_U_MTZPN1:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_PO_U_MTZPN1);
        break;
      }
    case BIT_MA_PO_MTZPN1:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_PO_MTZPN1);
        break;
      }
    case BIT_MA_MTZ1:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_MTZ1);
        break;
      }
    case BIT_MA_SECTOR_VPERED_MTZN2:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_SECTOR_VPERED_MTZN2);
        break;
      }
    case BIT_MA_SECTOR_NAZAD_MTZN2:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_SECTOR_NAZAD_MTZN2);
        break;
      }
    case BIT_MA_PO_MTZ2:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_PO_MTZ2);
        break;
      }
    case BIT_MA_PO_MTZN2_VPERED:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_PO_MTZN2_VPERED);
        break;
      }
    case BIT_MA_PO_MTZN2_NAZAD:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_PO_MTZN2_NAZAD);
        break;
      }
    case BIT_MA_PO_U_MTZPN2:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_PO_U_MTZPN2);
        break;
      }
    case BIT_MA_PO_MTZPN2:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_PO_MTZPN2);
        break;
      }
    case BIT_MA_MTZ2:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_MTZ2);
        break;
      }
    case BIT_MA_SECTOR_VPERED_MTZN3:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_SECTOR_VPERED_MTZN3);
        break;
      }
    case BIT_MA_SECTOR_NAZAD_MTZN3:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_SECTOR_NAZAD_MTZN3);
        break;
      }
    case BIT_MA_PO_MTZ3:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_PO_MTZ3);
        break;
      }
    case BIT_MA_PO_MTZN3_VPERED:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_PO_MTZN3_VPERED);
        break;
      }
    case BIT_MA_PO_MTZN3_NAZAD:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_PO_MTZN3_NAZAD);
        break;
      }
    case BIT_MA_PO_U_MTZPN3:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_PO_U_MTZPN3);
        break;
      }
    case BIT_MA_PO_MTZPN3:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_PO_MTZPN3);
        break;
      }
    case BIT_MA_MTZ3:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_MTZ3);
        break;
      }
    case BIT_MA_SECTOR_VPERED_MTZN4:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_SECTOR_VPERED_MTZN4);
        break;
      }
    case BIT_MA_SECTOR_NAZAD_MTZN4:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_SECTOR_NAZAD_MTZN4);
        break;
      }
    case BIT_MA_PO_MTZ4:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_PO_MTZ4);
        break;
      }
    case BIT_MA_PO_MTZN4_VPERED:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_PO_MTZN4_VPERED);
        break;
      }
    case BIT_MA_PO_MTZN4_NAZAD:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_PO_MTZN4_NAZAD);
        break;
      }
    case BIT_MA_PO_U_MTZPN4:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_PO_U_MTZPN4);
        break;
      }
    case BIT_MA_PO_MTZPN4:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_PO_MTZPN4);
        break;
      }
    case BIT_MA_MTZ4:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_MTZ4);
        break;
      }
    case BIT_MA_PO_BLOCK_U_MTZN:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_PO_BLOCK_U_MTZN);
        break;
      }
    case BIT_MA_NCN_MTZ:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_NCN_MTZ);
        break;
      }
    case BIT_MA_PUSK_ZDZ_VID_DV:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_PUSK_ZDZ_VID_DV);
        break;
      }
    case BIT_MA_ZDZ:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_ZDZ);
        break;
      }
    case BIT_MA_BLOCK_NZZ:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_BLOCK_NZZ);
        break;
      }
    case BIT_MA_PO_NZZ:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_PO_NZZ);
        break;
      }
    case BIT_MA_NZZ:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_NZZ);
        break;
      }
    case BIT_MA_PO_ZZ1_3I0:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_PO_3I0);
        break;
      }
    case BIT_MA_ZZ1_3I0:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_3I0);
        break;
      }
    case BIT_MA_PO_ZZ_3U0:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_PO_3U0);
        break;
      }
    case BIT_MA_ZZ_3U0:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_3U0);
        break;
      }
    case BIT_MA_SECTOR_NZZ:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_SECTOR_NZZ);
        break;
      }
    case BIT_MA_STAT_BLK_APV:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_STAT_BLK_APV);
        break;
      }
    case BIT_MA_APV:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_APV1);
        break;
      }
    case BIT_MA_APV2:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_APV2);
        break;
      }
    case BIT_MA_APV3:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_APV3);
        break;
      }
    case BIT_MA_APV4:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_APV4);
        break;
      }
    case BIT_MA_APV_WORK:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_APV_WORK);
        break;
      }
    case BIT_MA_RESET_BLOCK_APV_ZMN:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_RESET_BLOCK_APV_ZMN);
        break;
      }
    case BIT_MA_BLOCK_APV_ZMN:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_BLOCK_APV_ZMN);
        break;
      }
    case BIT_MA_PO_UAPV_ZMN1:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_PO_UAPV_ZMN1);
        break;
      }
    case BIT_MA_PO_UAPV_ZMN2:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_PO_UAPV_ZMN2);
        break;
      }
    case BIT_MA_PO_APV_ZMN:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_PO_APV_ZMN);
        break;
      }
    case BIT_MA_APV_ZMN:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_APV_ZMN);
        break;
      }
    case BIT_MA_BLOCK_KRATN_APV_ZMN:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_BLOCK_KRATN_APV_ZMN);
        break;
      }
    case BIT_MA_BLOCK_APV_ZMN_VID_ZAKHYSTIV:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_BLOCK_APV_ZMN_VID_ZAKHYSTIV);
        break;
      }
    case BIT_MA_ACHR_CHAPV_VID_DV:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_ACHR_CHAPV_VID_DV);
        break;
      }
    case BIT_MA_BLOCK_ACHR:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_BLOCK_ACHR);
        break;
      }
    case BIT_MA_BLOCK_CHAPV_VID_U:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_BLOCK_CHAPV_VID_U);
        break;
      }
    case BIT_MA_PO_F1_ACHR:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_PO_F1_ACHR);
        break;
      }
    case BIT_MA_PO_F2_ACHR:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_PO_F2_ACHR);
        break;
      }
    case BIT_MA_F1_ACHR_CHAPV:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_F1_ACHR_CHAPV);
        break;
      }
    case BIT_MA_F2_ACHR_CHAPV:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_F2_ACHR_CHAPV);
        break;
      }
    case BIT_MA_ACHR_CHAPV:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_ACHR_CHAPV);
        break;
      }
    case BIT_MA_RAZR_CHAPV:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_RAZR_CHAPV);
        break;
      }
    case BIT_MA_PO_F1_CHAPV:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_PO_F1_CHAPV);
        break;
      }
    case BIT_MA_PO_F2_CHAPV:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_PO_F2_CHAPV);
        break;
      }
    case BIT_MA_PUSK_UROV_VID_DV:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_PUSK_UROV_VID_DV);
        break;
      }
    case BIT_MA_PO_UROV:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_PO_UROV);
        break;
      }
    case BIT_MA_UROV1:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_UROV1);
        break;
      }
    case BIT_MA_UROV2:
      {
        _SET_BIT(set_array_rang,RANG_OUTPUT_LED_DF_REG_UROV2);
        break;
      }
    case BIT_MA_BLOCK_ZOP:
      {
        _SET_BIT(set_array_rang,RANG_OUTPUT_LED_DF_REG_BLOCK_ZOP);
        break;
      }
    case BIT_MA_PO_ZOP:
      {
        _SET_BIT(set_array_rang,RANG_OUTPUT_LED_DF_REG_PO_ZOP);
        break;
      }
    case BIT_MA_ZOP:
      {
        _SET_BIT(set_array_rang,RANG_OUTPUT_LED_DF_REG_ZOP);
        break;
      }
    case BIT_MA_BLOCK_UMIN1:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_BLOCK_UMIN1);
        break;
      }
    case BIT_MA_PO_UBLK_UMIN1:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_PO_UBLK_UMIN1);
        break;
      }
    case BIT_MA_PO_IBLK_UMIN1:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_PO_IBLK_UMIN1);
        break;
      }
    case BIT_MA_UMIN1:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_UMIN1);
        break;
      }
    case BIT_MA_PO_UMIN1:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_PO_UMIN1);
        break;
      }
    case BIT_MA_BLOCK_UMIN2:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_BLOCK_UMIN2);
        break;
      }
    case BIT_MA_UMIN2:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_UMIN2);
        break;
      }
    case BIT_MA_PO_UMIN2:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_PO_UMIN2);
        break;
      }
    case BIT_MA_START_UMIN1:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_START_UMIN1);
        break;
      }
    case BIT_MA_START_UMIN2:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_START_UMIN2);
        break;
      }
    case BIT_MA_PO_UBLK_UMIN2:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_PO_UBLK_UMIN2);
        break;
      }
    case BIT_MA_PO_IBLK_UMIN2:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_PO_IBLK_UMIN2);
        break;
      }
    case BIT_MA_BLOCK_UMAX1:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_BLOCK_UMAX1);
        break;
      }
    case BIT_MA_PO_UMAX1:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_PO_UMAX1);
        break;
      }
    case BIT_MA_UMAX1:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_UMAX1);
        break;
      }
    case BIT_MA_BLOCK_UMAX2:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_BLOCK_UMAX2);
        break;
      }
    case BIT_MA_PO_UMAX2:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_PO_UMAX2);
        break;
      }
    case BIT_MA_UMAX2:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_UMAX2);
        break;
      }
    case BIT_MA_OTKL_AVR:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_OTKL_AVR);
        break;
      }
    case BIT_MA_SBROS_BLOCK_AVR:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_SBROS_BLOCK_AVR);
        break;
      }
    case BIT_MA_STAT_BLOCK_AVR:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_STAT_BLOCK_AVR);
        break;
      }
    case BIT_MA_PO_UAVR_MIN1:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_PO_UAVR_MIN1);
        break;
      }
    case BIT_MA_PO_UAVR_MAX1:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_PO_UAVR_MAX1);
        break;
      }
    case BIT_MA_PO_UAVR_MIN2:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_PO_UAVR_MIN2);
        break;
      }
    case BIT_MA_PO_UAVR_MAX2:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_PO_UAVR_MAX2);
        break;
      }
    case BIT_MA_BLOCK_AVR_VID_ZAKHYSTIV:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_BLOCK_AVR_VID_ZAKHYSTIV);
        break;
      }
    case BIT_MA_BLOCK_KRATN_AVR:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_BLOCK_KRATN_AVR);
        break;
      }
    case BIT_MA_PUSK_AVR:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_PUSK_AVR);
        break;
      }
    case BIT_MA_PUSK_AVR_1:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_PUSK_AVR_1);
        break;
      }
    case BIT_MA_PUSK_AVR_2:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_PUSK_AVR_2);
        break;
      }
    case BIT_MA_PO_U_OL:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_PO_U_OL);
        break;
      }
    case BIT_MA_U_OL:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_U_OL);
        break;
      }
    case BIT_MA_PO_U_RL:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_PO_U_RL);
        break;
      }
    case BIT_MA_U_RL:
      {
        _SET_BIT(set_array_rang, RANG_OUTPUT_LED_DF_REG_U_RL);
        break;
      }
    default:
      {
        //���������� ���� � �������� ����� �� ���� � ��������
        //��� ���� �����, �� ����������� ����������� ��� �������
        error = ERROR_ILLEGAL_DATA_VALUE;
        break;
      }
    }
  }
  return error;
}
/***********************************************************************************/

/***********************************************************************************/
// ��������� ���������� �������������� ������
/***********************************************************************************/
unsigned int save_new_rang_buttons_from_gmm(unsigned int number, unsigned int number_position, unsigned short int data, unsigned int method_setting)
{
  __SETTINGS *target_label;
  if (method_setting == SET_DATA_IMMEDITATE) target_label = &current_settings;
  else target_label = &edition_settings;
  
  unsigned int *point_to_target;
  unsigned int input_value = current_settings.ranguvannja_buttons[number];
  unsigned int number_function_in_source = 0, index_function_in_source;
  unsigned short error = 0;
  
  //������������ ���� �� ��'��, ���� ����� ����������
  point_to_target = (unsigned int *)target_label->ranguvannja_buttons + number;

  //����������, �� ����� �������� ���� (���� ��� ����) ������ � �������� �����
  if (point_to_edited_rang != NULL)
  {
    //��� ���������� ���������� ���������� � ����� ������ ���� ����������
    if (point_to_edited_rang != point_to_target)
    {
      //����� �� ���������� �� ���������� ������ �����, ���� �������� ���������� ����� ������ � ��������� ����
      set_previous_ranguvannja();
      
      point_to_edited_rang = point_to_target;
    }
  }
  else
  {
    //�� � ����� �������� �� ���������� � ������ ���� ����������
    point_to_edited_rang = point_to_target;
  }
  
  number_32bit_in_target = 1;
  
  //����������, �� ���� ������� ����� �������������
  if (data != 0)
  {
    //���� data == 0, �� �� ������, �� ����� ����� ������� �������
    
    if (
        (data == BIT_MA_INPUT_DF1          ) || 
        (data == BIT_MA_INPUT_DF2          ) || 
        (data == BIT_MA_INPUT_DF3          ) || 
        (data == BIT_MA_INPUT_DF4          ) ||
        (data == BIT_MA_INPUT_DF5          ) || 
        (data == BIT_MA_INPUT_DF6          ) || 
        (data == BIT_MA_INPUT_DF7          ) || 
        (data == BIT_MA_INPUT_DF8          ) || 
        (data == BIT_MA_DT1_SET            ) ||
        (data == BIT_MA_DT1_RESET          ) ||
        (data == BIT_MA_DT2_SET            ) ||
        (data == BIT_MA_DT2_RESET          ) ||
        (data == BIT_MA_DT3_SET            ) ||
        (data == BIT_MA_DT3_RESET          ) ||
        (data == BIT_MA_DT4_SET            ) ||
        (data == BIT_MA_DT4_RESET          ) ||
        (data == BIT_MA_RESET_LEDS         ) || 
        (data == BIT_MA_RESET_RELES        ) || 
        (data == BIT_MA_MISCEVE_DYSTANCIJNE) || 
        (data == BIT_MA_VKL_VV             ) ||
        (data == BIT_MA_OTKL_VV            ) ||
        (data == BIT_MA_RESET_BLOCK_READY_TU_VID_ZAHYSTIV) 
       )
    {
      //����� � ��������� ���������� �������� ������ � ����� �� � ����������
      error = 0;
    }
    else if (
             (data == BIT_MA_RESET_BLOCK_APV_ZMN)
            )
    {
      //����� � ��������� ���������� ������ ���-��� � ����� �� � ����������
      if ((target_label->configuration & (1 << APV_ZMN_BIT_CONFIGURATION)) !=0 ) error = 0;
      else error = ERROR_ILLEGAL_DATA_VALUE;
    }
    else if (
             (data == BIT_MA_OTKL_AVR       ) ||
             (data == BIT_MA_SBROS_BLOCK_AVR)
            )
    {
      //����� � ��������� ���������� ������ ��� � ����� �� � ����������
      if ((target_label->configuration & (1 << AVR_BIT_CONFIGURATION)) !=0 ) error = 0;
      else error = ERROR_ILLEGAL_DATA_VALUE;
    }
    else
    {
      error = ERROR_ILLEGAL_DATA_VALUE;
    }
  }
  
  //���� ����� ������� � ������������, �� �������� ������� ���������� ���� �����
  if (error != 0) return error;
  
  //ϳ��������� ������� �������, �� ��������� �� ����� ����
  if (input_value !=0)
  {
    //���� �� �������� �� �������, �� �� ������, �� ���� ������� ���������
    //������ ������� ������� ���������� ����� 0, ���� ����� number_function_in_source ������������ ��� ����
    for (unsigned int i = 0; i < NUMBER_TOTAL_SIGNAL_FOR_RANG_BUTTON; i++)
    {
      if ((input_value & ((unsigned int)(1 << i))) != 0) number_function_in_source++;
    }
  }
  
  if (number_position <= number_function_in_source)
  {
    //��� ������� ������, �� ����� ������ ����� ��� ����������� ������� ��������� ������
    //������ ������ ���������� ���� ������� � ���� �������
    
    //�����, ��� ����� ������ �������, ��� ������� �� ������� ������������� ��� ���������� ������� �  �������� ������� ��� ��
    //� ���� ���������� ���� �������  

    //������ ������� � ������� ��� ����� (�������), ���� ������� ������ ������ ������� Modbus-RTU
    unsigned int i = 0;
    index_function_in_source = 0;
    while ( (i < NUMBER_TOTAL_SIGNAL_FOR_RANG_BUTTON) && (index_function_in_source < number_position) )
    {
      if ((input_value & ((unsigned int)(1 << i))) != 0) index_function_in_source++;
      if (index_function_in_source < number_position) i++;
    }
    
    if(index_function_in_source == number_position)
    {
      //���� ���� ����� ��������, �� �� ������, �� ��������� �� ���������
      //������� �� ������ ���� ������� ���� ��������������� ���� �������
      _SET_BIT(clear_array_rang, i);
    }
  }
  
  if (data != 0)
  {
    //������������ �������� �������
    switch (data)
    {
    case BIT_MA_INPUT_DF1:
      {
        _SET_BIT(set_array_rang,RANG_BUTTON_DF1_IN);
        break;
      }
    case BIT_MA_INPUT_DF2:
      {
        _SET_BIT(set_array_rang,RANG_BUTTON_DF2_IN);
        break;
      }
    case BIT_MA_INPUT_DF3:
      {
        _SET_BIT(set_array_rang,RANG_BUTTON_DF3_IN);
        break;
      }
    case BIT_MA_INPUT_DF4:
      {
        _SET_BIT(set_array_rang,RANG_BUTTON_DF4_IN);
        break;
      }
    case BIT_MA_INPUT_DF5:
      {
        _SET_BIT(set_array_rang,RANG_BUTTON_DF5_IN);
        break;
      }
    case BIT_MA_INPUT_DF6:
      {
        _SET_BIT(set_array_rang,RANG_BUTTON_DF6_IN);
        break;
      }
    case BIT_MA_INPUT_DF7:
      {
        _SET_BIT(set_array_rang,RANG_BUTTON_DF7_IN);
        break;
      }
    case BIT_MA_INPUT_DF8:
      {
        _SET_BIT(set_array_rang,RANG_BUTTON_DF8_IN);
        break;
      }
    case BIT_MA_DT1_SET:
      {
        set_array_rang[0] |= ((unsigned int)(1 << RANG_BUTTON_DT1_SET));
        break;
      }
    case BIT_MA_DT1_RESET:
      {
        set_array_rang[0] |= ((unsigned int)(1 << RANG_BUTTON_DT1_RESET));
        break;
      }
    case BIT_MA_DT2_SET:
      {
        set_array_rang[0] |= ((unsigned int)(1 << RANG_BUTTON_DT2_SET));
        break;
      }
    case BIT_MA_DT2_RESET:
      {
        set_array_rang[0] |= ((unsigned int)(1 << RANG_BUTTON_DT2_RESET));
        break;
      }
    case BIT_MA_DT3_SET:
      {
        set_array_rang[0] |= ((unsigned int)(1 << RANG_BUTTON_DT3_SET));
        break;
      }
    case BIT_MA_DT3_RESET:
      {
        set_array_rang[0] |= ((unsigned int)(1 << RANG_BUTTON_DT3_RESET));
        break;
      }
    case BIT_MA_DT4_SET:
      {
        set_array_rang[0] |= ((unsigned int)(1 << RANG_BUTTON_DT4_SET));
        break;
      }
    case BIT_MA_DT4_RESET:
      {
        set_array_rang[0] |= ((unsigned int)(1 << RANG_BUTTON_DT4_RESET));
        break;
      }
    case BIT_MA_RESET_LEDS:
      {
        _SET_BIT(set_array_rang,RANG_BUTTON_RESET_LEDS);
        break;
      }
    case BIT_MA_RESET_RELES:
      {
        _SET_BIT(set_array_rang,RANG_BUTTON_RESET_RELES);
        break;
      }
    case BIT_MA_MISCEVE_DYSTANCIJNE:
      {
        _SET_BIT(set_array_rang,RANG_BUTTON_MISCEVE_DYSTANCIJNE);
        break;
      }
    case BIT_MA_VKL_VV:
      {
        _SET_BIT(set_array_rang,RANG_BUTTON_VKL_VV);
        break;
      }
    case BIT_MA_OTKL_VV:
      {
        _SET_BIT(set_array_rang,RANG_BUTTON_OTKL_VV);
        break;
      }
    case BIT_MA_RESET_BLOCK_READY_TU_VID_ZAHYSTIV:
      {
        _SET_BIT(set_array_rang,RANG_BUTTON_RESET_BLOCK_READY_TU_VID_ZAHYSTIV);
        break;
      }
    case BIT_MA_RESET_BLOCK_APV_ZMN:
      {
        _SET_BIT(set_array_rang, RANG_BUTTON_RESET_BLOCK_APV_ZMN);
        break;
      }
    case BIT_MA_OTKL_AVR:
      {
        _SET_BIT(set_array_rang, RANG_BUTTON_OTKL_AVR);
        break;
      }
    case BIT_MA_SBROS_BLOCK_AVR:
      {
        _SET_BIT(set_array_rang, RANG_BUTTON_SBROS_BLOCK_AVR);
        break;
      }
    default:
      {
        //���������� ���� � �������� ����� �� ���� � ��������
        //��� ���� �����, �� ����������� ����������� ��� �������
        error = ERROR_ILLEGAL_DATA_VALUE;
        break;
      }
    }
  }
    
  return error;
}

/***********************************************************************************/

/***********************************************************************************/
//������� �����
/***********************************************************************************/
inline unsigned int Get_data(unsigned char *data, unsigned int address_data, unsigned int type_interface)
{
  unsigned int error = 0, temp_value = 0;
  
  if(address_data <= M_ADDRESS_LAST_RO_BLOCK_1)
  {
    //������������� �������
    switch (address_data)
    {
    case MA_SERIAL_NUMBER:
      {
        temp_value = serial_number_dev;
        break;
      }
    case MA_NAME_CHAR_1_2:
      {
        temp_value = ('K' << 8) + 'i';
        break;
      }
    case MA_NAME_CHAR_3_4:
      {
        temp_value = ('e' << 8) + 'v';
        break;
      }
    case MA_NAME_CHAR_5_6:
      {
        temp_value = ('p' << 8) + 'r';
        break;
      }
    case MA_NAME_CHAR_7_8:
      {
        temp_value = ('i' << 8) + 'b';
        break;
      }
    case MA_NAME_CHAR_9_10:
      {
        temp_value = ('o' << 8) + 'r';
        break;
      }
    case MA_NAME_CHAR_11_12:
      {
        temp_value = ('M' << 8) + 'R';
        break;
      }
    case MA_NAME_CHAR_13_14:
      {
        temp_value = ('Z' << 8) + 'S';
        break;
      }
    case MA_NAME_CHAR_15_16:
      {
        temp_value = ('0' << 8) + '5';
        break;
      }
    case MA_NAME_CHAR_17_18:
      {
        temp_value = ('L' << 8) + '_';
        break;
      }
    case MA_VERSION_SW:
      {
        temp_value = (VERSIA_PZ << 8) + MODYFIKACIA_VERSII_PZ;
        break;
      }
    case MA_DATA_COMP_1:
      {
        temp_value = (YEAR_VER << 8) + MONTH_VER;
        break;
      }
    case MA_DATA_COMP_2:
      {
        temp_value = (DAY_VER << 8);
        break;
      }
    case MA_TIME_COMP:
      {
        temp_value = (HOUR_VER << 8) + MINUTE_VER;
        break;
      }
    case MA_VERSION_GMM:
      {
        temp_value = (VERSIA_GMM << 8) + MODYFIKACIA_VERSII_GMM;
        break;
      }
    case MA_ZBIRKA_SW:
      {
        temp_value = (ZBIRKA_VERSII_PZ << 8) + ZBIRKA_PIDVERSII_PZ;
        break;
      }
    default:
      {
        //�� ���� �� � ���� ������������ ���� ��������� ������
        temp_value = 0;
        break;
      }
    }
  }
  else if (address_data == MA_OUTPUTS)
  {
    temp_value = state_outputs & ((1 << NUMBER_OUTPUTS) - 1);
  }
  else if (address_data == MA_INPUTS)
  {
    temp_value = active_inputs & ((1 << NUMBER_INPUTS) - 1);
  }
  else if (address_data == MA_LEDS)
  {
    temp_value = state_leds & ((1 << NUMBER_LEDS) - 1);
  }
  else if ((address_data >= M_ADDRESS_FIRST_SETPOINTS_PART1) && (address_data <= M_ADDRESS_LAST_SETPOINTS_PART1))
  {
    switch (address_data)
    {
    case MA_GROUP_USTAVOK:
      {
        temp_value = current_settings.grupa_ustavok;
        break;
      }
    case MA_TYPE_MTZ1:
      {
        temp_value = current_settings.type_mtz1;
        break;
      }
    case MA_TYPE_MTZ2:
      {
        temp_value = current_settings.type_mtz2;
        break;
      }
    case MA_TYPE_MTZ3:
      {
        temp_value = current_settings.type_mtz3;
        break;
      }
    case MA_TYPE_MTZ4:
      {
        temp_value = current_settings.type_mtz4;
        break;
      }
    default:
      {
        temp_value = 0;
        break;
      }
    }
  }
  else if (
           ((address_data >= (M_ADDRESS_FIRST_SETPOINTS_ZACHYSTIV + SHIFT_G1)) && (address_data <= (M_ADDRESS_LAST_SETPOINTS_ZACHYSTIV + SHIFT_G1))) ||
           ((address_data >= (M_ADDRESS_FIRST_SETPOINTS_ZACHYSTIV + SHIFT_G2)) && (address_data <= (M_ADDRESS_LAST_SETPOINTS_ZACHYSTIV + SHIFT_G2))) ||
           ((address_data >= (M_ADDRESS_FIRST_SETPOINTS_ZACHYSTIV + SHIFT_G3)) && (address_data <= (M_ADDRESS_LAST_SETPOINTS_ZACHYSTIV + SHIFT_G3))) ||
           ((address_data >= (M_ADDRESS_FIRST_SETPOINTS_ZACHYSTIV + SHIFT_G4)) && (address_data <= (M_ADDRESS_LAST_SETPOINTS_ZACHYSTIV + SHIFT_G4)))
          )
  {
    //�������, ��������, �� ����� ������� ���� �������
     unsigned int num_gr, address_data_tmp = address_data;
     if ((address_data >= (M_ADDRESS_FIRST_SETPOINTS_ZACHYSTIV + SHIFT_G1)) && (address_data <= (M_ADDRESS_LAST_SETPOINTS_ZACHYSTIV + SHIFT_G1)))
     {
       num_gr = 0;
       address_data_tmp -= SHIFT_G1;
     }
     else if ((address_data >= (M_ADDRESS_FIRST_SETPOINTS_ZACHYSTIV + SHIFT_G2)) && (address_data <= (M_ADDRESS_LAST_SETPOINTS_ZACHYSTIV + SHIFT_G2)))
     {
       num_gr = 1;
       address_data_tmp -= SHIFT_G2;
     }
     else if ((address_data >= (M_ADDRESS_FIRST_SETPOINTS_ZACHYSTIV + SHIFT_G3)) && (address_data <= (M_ADDRESS_LAST_SETPOINTS_ZACHYSTIV + SHIFT_G3)))
     {
       num_gr = 2;
       address_data_tmp -= SHIFT_G3;
     }
     else
     {
       num_gr = 3;
       address_data_tmp -= SHIFT_G4;
     }
        
    switch (address_data_tmp)
    {
    case MA_STP_MTZ1:
      {
        temp_value = current_settings.setpoint_mtz_1[num_gr]/10;
        break;
      }
    case MA_STP_MTZ1_N_VPERED:
      {
        temp_value = current_settings.setpoint_mtz_1_n_vpered[num_gr]/10;
        break;
      }
    case MA_STP_MTZ1_N_NAZAD:
      {
        temp_value = current_settings.setpoint_mtz_1_n_nazad[num_gr]/10;
        break;
      }
    case MA_STP_MTZ1_PO_NAPRUZI:
      {
        temp_value = current_settings.setpoint_mtz_1_po_napruzi[num_gr]/10;
        break;
      }
    case MA_STP_MTZ1_U:
      {
        temp_value = current_settings.setpoint_mtz_1_U[num_gr]/10;
        break;
      }
    case MA_STP_MTZ1_ANGLE:
      {
        temp_value = current_settings.setpoint_mtz_1_angle[num_gr];
        break;
      }
    case MA_TO_MTZ1:
      {
        temp_value = current_settings.timeout_mtz_1[num_gr]/10;
        break;
      }
    case MA_TO_MTZ1_N_VPERED:
      {
        temp_value = current_settings.timeout_mtz_1_n_vpered[num_gr]/10;
        break;
      }
    case MA_TO_MTZ1_N_NAZAD:
      {
        temp_value = current_settings.timeout_mtz_1_n_nazad[num_gr]/10;
        break;
      }
    case MA_TO_MTZ1_PO_NAPRUZI:
      {
        temp_value = current_settings.timeout_mtz_1_po_napruzi[num_gr]/10;
        break;
      }
    case MA_STP_MTZ2:
      {
        temp_value = current_settings.setpoint_mtz_2[num_gr]/10;
        break;
      }
    case MA_STP_MTZ2_N_VPERED:
      {
        temp_value = current_settings.setpoint_mtz_2_n_vpered[num_gr]/10;
        break;
      }
    case MA_STP_MTZ2_N_NAZAD:
      {
        temp_value = current_settings.setpoint_mtz_2_n_nazad[num_gr]/10;
        break;
      }
    case MA_STP_MTZ2_PO_NAPRUZI:
      {
        temp_value = current_settings.setpoint_mtz_2_po_napruzi[num_gr]/10;
        break;
      }
    case MA_STP_MTZ2_U:
      {
        temp_value = current_settings.setpoint_mtz_2_U[num_gr]/10;
        break;
      }
    case MA_STP_MTZ2_ANGLE:
      {
        temp_value = current_settings.setpoint_mtz_2_angle[num_gr];
        break;
      }
    case MA_TO_MTZ2:
      {
        temp_value = current_settings.timeout_mtz_2[num_gr]/10;
        break;
      }
    case MA_TO_MTZ2_N_VPERED:
      {
        temp_value = current_settings.timeout_mtz_2_n_vpered[num_gr]/10;
        break;
      }
    case MA_TO_MTZ2_N_NAZAD:
      {
        temp_value = current_settings.timeout_mtz_2_n_nazad[num_gr]/10;
        break;
      }
    case MA_TO_MTZ2_PO_NAPRUZI:
      {
        temp_value = current_settings.timeout_mtz_2_po_napruzi[num_gr]/10;
        break;
      }
    case MA_TO_MTZ2_VVID_PR:
      {
        temp_value = current_settings.timeout_mtz_2_vvid_pr[num_gr]/10;
        break;
      }
    case MA_TO_MTZ2_PR:
      {
        temp_value = current_settings.timeout_mtz_2_pr[num_gr]/10;
        break;
      }
    case MA_TO_MTZ2_N_VPERED_PR:
      {
        temp_value = current_settings.timeout_mtz_2_n_vpered_pr[num_gr]/10;
        break;
      }
    case MA_TO_MTZ2_N_NAZAD_PR:
      {
        temp_value = current_settings.timeout_mtz_2_n_nazad_pr[num_gr]/10;
        break;
      }
    case MA_TO_MTZ2_PO_NAPRUZI_PR:
      {
        temp_value = current_settings.timeout_mtz_2_po_napruzi_pr[num_gr]/10;
        break;
      }
    case MA_STP_MTZ3:
      {
        temp_value = current_settings.setpoint_mtz_3[num_gr]/10;
        break;
      }
    case MA_STP_MTZ3_N_VPERED:
      {
        temp_value = current_settings.setpoint_mtz_3_n_vpered[num_gr]/10;
        break;
      }
    case MA_STP_MTZ3_N_NAZAD:
      {
        temp_value = current_settings.setpoint_mtz_3_n_nazad[num_gr]/10;
        break;
      }
    case MA_STP_MTZ3_PO_NAPRUZI:
      {
        temp_value = current_settings.setpoint_mtz_3_po_napruzi[num_gr]/10;
        break;
      }
    case MA_STP_MTZ3_U:
      {
        temp_value = current_settings.setpoint_mtz_3_U[num_gr]/10;
        break;
      }
    case MA_STP_MTZ3_ANGLE:
      {
        temp_value = current_settings.setpoint_mtz_3_angle[num_gr];
        break;
      }
    case MA_TO_MTZ3:
      {
        temp_value = current_settings.timeout_mtz_3[num_gr]/10;
        break;
      }
    case MA_TO_MTZ3_N_VPERED:
      {
        temp_value = current_settings.timeout_mtz_3_n_vpered[num_gr]/10;
        break;
      }
    case MA_TO_MTZ3_N_NAZAD:
      {
        temp_value = current_settings.timeout_mtz_3_n_nazad[num_gr]/10;
        break;
      }
    case MA_TO_MTZ3_PO_NAPRUZI:
      {
        temp_value = current_settings.timeout_mtz_3_po_napruzi[num_gr]/10;
        break;
      }
    case MA_STP_MTZ4:
      {
        temp_value = current_settings.setpoint_mtz_4[num_gr]/10;
        break;
      }
    case MA_STP_MTZ4_N_VPERED:
      {
        temp_value = current_settings.setpoint_mtz_4_n_vpered[num_gr]/10;
        break;
      }
    case MA_STP_MTZ4_N_NAZAD:
      {
        temp_value = current_settings.setpoint_mtz_4_n_nazad[num_gr]/10;
        break;
      }
    case MA_STP_MTZ4_PO_NAPRUZI:
      {
        temp_value = current_settings.setpoint_mtz_4_po_napruzi[num_gr]/10;
        break;
      }
    case MA_STP_MTZ4_U:
      {
        temp_value = current_settings.setpoint_mtz_4_U[num_gr]/10;
        break;
      }
    case MA_STP_MTZ4_ANGLE:
      {
        temp_value = current_settings.setpoint_mtz_4_angle[num_gr];
        break;
      }
    case MA_TO_MTZ4:
      {
        temp_value = current_settings.timeout_mtz_4[num_gr]/10;
        break;
      }
    case MA_TO_MTZ4_N_VPERED:
      {
        temp_value = current_settings.timeout_mtz_4_n_vpered[num_gr]/10;
        break;
      }
    case MA_TO_MTZ4_N_NAZAD:
      {
        temp_value = current_settings.timeout_mtz_4_n_nazad[num_gr]/10;
        break;
      }
    case MA_TO_MTZ4_PO_NAPRUZI:
      {
        temp_value = current_settings.timeout_mtz_4_po_napruzi[num_gr]/10;
        break;
      }
    case MA_STP_NZZ1_3I0:
      {
        temp_value = current_settings.setpoint_zz_3I0[num_gr];
        break;
      }
    case MA_TO_NZZ1_3I0:
      {
        temp_value = current_settings.timeout_zz_3I0[num_gr]/10;
        break;
      }
    case MA_STP_NZZ1_3U0:
      {
        temp_value = current_settings.setpoint_zz_3U0[num_gr]/10;
        break;
      }
    case MA_TO_NZZ1_3U0:
      {
        temp_value = current_settings.timeout_zz_3U0[num_gr]/10;
        break;
      }
    case MA_TO_NZZ1:
      {
        temp_value = current_settings.timeout_nzz[num_gr]/10;
        break;
      }
    case MA_STP_ZOP1:
      {
        temp_value = current_settings.setpoint_zop[num_gr];
        break;
      }
    case MA_TO_ZOP1:
      {
        temp_value = current_settings.timeout_zop[num_gr]/10;
        break;
      }
    case MA_STP_UMIN1:
      {
        temp_value = current_settings.setpoint_Umin1[num_gr]/100;
        break;
      }
    case MA_TO_UMIN1:
      {
        temp_value = current_settings.timeout_Umin1[num_gr]/10;
        break;
      }
    case MA_STP_UMIN2:
      {
        temp_value = current_settings.setpoint_Umin2[num_gr]/100;
        break;
      }
    case MA_TO_UMIN2:
      {
        temp_value = current_settings.timeout_Umin2[num_gr]/10;
        break;
      }
    case MA_STP_BLK_UMIN1_BY_I:
      {
        temp_value = current_settings.setpoint_Umin1_Iblk[num_gr]/10;
        break;
      }
    case MA_STP_BLK_UMIN2_BY_I:
      {
        temp_value = current_settings.setpoint_Umin2_Iblk[num_gr]/10;
        break;
      }
    case MA_STP_UMAX1:
      {
        temp_value = current_settings.setpoint_Umax1[num_gr]/100;
        break;
      }
    case MA_TO_UMAX1:
      {
        temp_value = current_settings.timeout_Umax1[num_gr]/10;
        break;
      }
    case MA_STP_UMAX2:
      {
        temp_value = current_settings.setpoint_Umax2[num_gr]/100;
        break;
      }
    case MA_TO_UMAX2:
      {
        temp_value = current_settings.timeout_Umax2[num_gr]/10;
        break;
      }
    case MA_STP_APV_ZMN1:
      {
        temp_value = current_settings.setpoint_apv_zmn1[num_gr]/100;
        break;
      }
    case MA_STP_APV_ZMN2:
      {
        temp_value = current_settings.setpoint_apv_zmn2[num_gr]/100;
        break;
      }
    case MA_TO_APV_ZMN1:
      {
        temp_value = current_settings.timeout_apv_zmn_1[num_gr]/10;
        break;
      }
    case MA_TO_APV_ZMN2:
      {
        temp_value = current_settings.timeout_apv_zmn_2[num_gr]/10;
        break;
      }
    case MA_STP_U_OL:
      {
        temp_value = current_settings.setpoint_U_ol[num_gr]/100;
        break;
      }
    case MA_STP_U_RL:
      {
        temp_value = current_settings.setpoint_U_rl[num_gr]/100;
        break;
      }
    case MA_TO_U_OL:
      {
        temp_value = current_settings.timeout_U_ol[num_gr]/10;
        break;
      }
    case MA_TO_U_RL:
      {
        temp_value = current_settings.timeout_U_rl[num_gr]/10;
        break;
      }
    case MA_STP_UROV:
      {
        temp_value = current_settings.setpoint_urov[num_gr]/10;
        break;
      }
    case MA_TO_UROV1:
      {
        temp_value = current_settings.timeout_urov_1[num_gr]/10;
        break;
      }
    case MA_TO_UROV2:
      {
        temp_value = current_settings.timeout_urov_2[num_gr]/10;
        break;
      }
    case MA_STP_AVR_MIN1:
      {
        temp_value = current_settings.setpoint_avr_min1[num_gr]/100;
        break;
      }
    case MA_STP_AVR_MAX1:
      {
        temp_value = current_settings.setpoint_avr_max1[num_gr]/100;
        break;
      }
    case MA_STP_AVR_MIN2:
      {
        temp_value = current_settings.setpoint_avr_min2[num_gr]/100;
        break;
      }
    case MA_STP_AVR_MAX2:
      {
        temp_value = current_settings.setpoint_avr_max2[num_gr]/100;
        break;
      }
    case MA_STP_KRATN_AVR:
      {
        temp_value = current_settings.setpoint_kratn_avr[num_gr];
        break;
      }
    case MA_TO_AVR_RL:
      {
        temp_value = current_settings.timeout_avr_rl[num_gr]/10;
        break;
      }
    case MA_TO_AVR_OL:
      {
        temp_value = current_settings.timeout_avr_ol[num_gr]/10;
        break;
      }
    case MA_TO_AVR_ZAVERSHENNJA:
      {
        temp_value = current_settings.timeout_avr_zavershennja[num_gr]/10;
        break;
      }
    case MA_TO_AVR_RESET_BLK:
      {
        temp_value = current_settings.timeout_avr_reset_blk[num_gr]/10;
        break;
      }
    case MA_TO_APV_BLOCK_VID_VV:
      {
        temp_value = current_settings.timeout_apv_block_vid_VV[num_gr]/10;
        break;
      }
    case MA_TO_APV_CYCLE_1:
      {
        temp_value = current_settings.timeout_apv_1[num_gr]/10;
        break;
      }
    case MA_TO_APV_CYCLE_2:
      {
        temp_value = current_settings.timeout_apv_2[num_gr]/10;
        break;
      }
    case MA_TO_APV_CYCLE_3:
      {
        temp_value = current_settings.timeout_apv_3[num_gr]/10;
        break;
      }
    case MA_TO_APV_CYCLE_4:
      {
        temp_value = current_settings.timeout_apv_4[num_gr]/10;
        break;
      }
    case MA_TO_APV_BLOCK_VID_APV1:
      {
        temp_value = current_settings.timeout_apv_block_vid_apv1[num_gr]/10;
        break;
      }
    case MA_TO_APV_BLOCK_VID_APV2:
      {
        temp_value = current_settings.timeout_apv_block_vid_apv2[num_gr]/10;
        break;
      }
    case MA_TO_APV_BLOCK_VID_APV3:
      {
        temp_value = current_settings.timeout_apv_block_vid_apv3[num_gr]/10;
        break;
      }
    case MA_TO_APV_BLOCK_VID_APV4:
      {
        temp_value = current_settings.timeout_apv_block_vid_apv4[num_gr]/10;
        break;
      }
    case MA_STP_KRATN_APV_ZMN:
      {
        temp_value = current_settings.setpoint_kratn_apv_zmn[num_gr];
        break;
      }
    case MA_TO_APV_ZMN_ZAVERSHENNJA:
      {
        temp_value = current_settings.timeout_apv_zmn_zavershennja[num_gr]/10;
        break;
      }
    case MA_STP_ACHR_F_RAB:
      {
        temp_value = current_settings.setpoint_achr_f_rab[num_gr]/10;
        break;
      }
    case MA_STP_CHAPV_F_RAB:
      {
        temp_value = current_settings.setpoint_chapv_f_rab[num_gr]/10;
        break;
      }
    case MA_STP_ACHR_CHAPV_UF1:
      {
        temp_value = current_settings.setpoint_achr_chapv_uf1[num_gr]/100;
        break;
      }
    case MA_STP_ACHR_CHAPV_UF2:
      {
        temp_value = current_settings.setpoint_achr_chapv_uf2[num_gr]/100;
        break;
      }
    case MA_TO_ACHR_1:
      {
        temp_value = current_settings.timeout_achr_1[num_gr]/10;
        break;
      }
    case MA_TO_ACHR_2:
      {
        temp_value = current_settings.timeout_achr_2[num_gr]/10;
        break;
      }
    case MA_TO_CHAPV_1:
      {
        temp_value = current_settings.timeout_chapv_1[num_gr]/10;
        break;
      }
    case MA_TO_CHAPV_2:
      {
        temp_value = current_settings.timeout_chapv_2[num_gr]/10;
        break;
      }
    default:
      {
        temp_value = 0;
        break;
      }
    }
  }
  else if ((address_data >= M_ADDRESS_FIRST_SETPOINTS_CONTINUE) && (address_data <= M_ADDRESS_LAST_SETPOINTS_CONTINUE))
  {
    //������� � �������� (�����������), ���������
    switch (address_data)
    {
    case MA_LINE_1:
    case MA_DOVGYNA_1_1:
    case MA_OPIR_1_1:
    case MA_DOVGYNA_1_2:
    case MA_OPIR_1_2:
    case MA_DOVGYNA_1_3:
    case MA_OPIR_1_3:
    case MA_DOVGYNA_1_4:
    case MA_OPIR_1_4:
    case MA_DOVGYNA_1_5:
    case MA_OPIR_1_5:
    case MA_DOVGYNA_1_6:
    case MA_OPIR_1_6:
    case MA_DOVGYNA_1_7:
    case MA_OPIR_1_7:
    case MA_DOVGYNA_1_8:
    case MA_OPIR_1_8:
    case MA_LINE_2:
    case MA_DOVGYNA_2_1:
    case MA_OPIR_2_1:
    case MA_DOVGYNA_2_2:
    case MA_OPIR_2_2:
    case MA_DOVGYNA_2_3:
    case MA_OPIR_2_3:
    case MA_DOVGYNA_2_4:
    case MA_OPIR_2_4:
    case MA_DOVGYNA_2_5:
    case MA_OPIR_2_5:
    case MA_DOVGYNA_2_6:
    case MA_OPIR_2_6:
    case MA_DOVGYNA_2_7:
    case MA_OPIR_2_7:
    case MA_DOVGYNA_2_8:
    case MA_OPIR_2_8:
      {
        unsigned int base_address, line;
        if(address_data < MA_LINE_2)
        {
          base_address = MA_LINE_1;
          line = 0;
        }
        else
        {
          base_address = MA_LINE_2;
          line = 1;
        }
        
        unsigned int shift_address =  address_data - base_address;
        if (shift_address == 0) temp_value = current_settings.lines[line];
        else
        {
          shift_address--;
          if ((shift_address & 0x1) == 0)
          {
            //������� ��
            temp_value = current_settings.dovgyna[line][shift_address >> 1];
          }
          else
          {
            //��� ��
            temp_value = current_settings.opir[line][shift_address >> 1];
          }
        }
        
        break;
      }
    case MA_TN1:
      {
        temp_value = current_settings.TVoltage;
        break;
      }
    case MA_TT:
      {
        temp_value = current_settings.TCurrent;
        break;
      }
    case MA_T0:
      {
        temp_value = current_settings.T0;
        break;
      }
    case MA_TO_SWCH_ON:
      {
        temp_value = current_settings.timeout_swch_on/10;
        break;
      }
    case MA_TO_SWCH_OFF:
      {
        temp_value = current_settings.timeout_swch_off/10;
        break;
      }
    case MA_TO_SWCH_UDL_BLK_ON:
      {
        temp_value = current_settings.timeout_swch_udl_blk_on/10;
        break;
      }
    case MA_TO_FAULT_CONTROL_CIRCUIT:
      {
        temp_value = current_settings.timeout_pryvoda_VV/10;
        break;
      }
    case MA_STP_Inom:
      {
        temp_value = current_settings.setpoint_Inom;
        break;
      }
    case MA_STP_RKS_Inom:
      {
        temp_value = current_settings.setpoint_r_kom_st_Inom/10;
        break;
      }
    case MA_STP_Inom_vymk:
      {
        temp_value = current_settings.setpoint_Inom_vymk;
        break;
      }
    case MA_STP_RKS_Inom_vymk:
      {
        temp_value = current_settings.setpoint_r_kom_st_Inom_vymk;
        break;
      }
    case MA_STP_POCHATKOVYJ_RESURS_LSW:
      {
        temp_value = current_settings.setpoint_pochatkovyj_resurs & 0xffff;
        break;
      }
    case MA_STP_POCHATKOVYJ_RESURS_MSW:
      {
        temp_value = (current_settings.setpoint_pochatkovyj_resurs >> 16) & 0xffff;
        break;
      }
    case MA_STP_KRYTYCHNYJ_RESURS:
      {
        temp_value = current_settings.setpoint_krytychnyj_resurs;
        break;
      }
    case MA_POCHATKOVA_K_VYMK_LSW:
      {
        temp_value = current_settings.setpoint_pochatkova_k_vymk & 0xffff;
        break;
      }
    case MA_POCHATKOVA_K_VYMK_MSW:
      {
        temp_value = (current_settings.setpoint_pochatkova_k_vymk >> 16) & 0xffff;
        break;
      }
    case MA_UVV_TYPE_SIGNAL_INPUT:
      {
        temp_value = current_settings.type_of_input_signal & ((1 << NUMBER_INPUTS) - 1);
        break;
      }
    case MA_UVV_TYPE_INPUT:
      {
        temp_value = ((unsigned int)(~current_settings.type_of_input)) & ((1 << NUMBER_INPUTS) - 1);
        break;
      }
    case MA_UVV_TYPE_OUTPUT:
      {
        temp_value = current_settings.type_of_output & ((1 << NUMBER_OUTPUTS) - 1);
        break;
      }
    case MA_TYPE_DF:
      {
        temp_value = current_settings.type_df & ((1 << NUMBER_DEFINED_FUNCTIONS) - 1);
        break;
      }
    case MA_UVV_TYPE_LED:
      {
        temp_value = current_settings.type_of_led & ((1 << NUMBER_LEDS) - 1);
        break;
      }
    case MA_DOPUSK_DV_1:
    case MA_DOPUSK_DV_2:
    case MA_DOPUSK_DV_3:
    case MA_DOPUSK_DV_4:
    case MA_DOPUSK_DV_5:
    case MA_DOPUSK_DV_6:
    case MA_DOPUSK_DV_7:
    case MA_DOPUSK_DV_8:
    case MA_DOPUSK_DV_9:
    case MA_DOPUSK_DV_10:
      {
        temp_value = current_settings.dopusk_dv[address_data - MA_DOPUSK_DV_1];
        break;
      }
    case MA_DF_PAUSE_1:
    case MA_DF_PAUSE_2:
    case MA_DF_PAUSE_3:
    case MA_DF_PAUSE_4:
    case MA_DF_PAUSE_5:
    case MA_DF_PAUSE_6:
    case MA_DF_PAUSE_7:
    case MA_DF_PAUSE_8:
      {
        temp_value = current_settings.timeout_pause_df[address_data - MA_DF_PAUSE_1]/10;
        break;
      }
    case MA_DF_WORK_1:
    case MA_DF_WORK_2:
    case MA_DF_WORK_3:
    case MA_DF_WORK_4:
    case MA_DF_WORK_5:
    case MA_DF_WORK_6:
    case MA_DF_WORK_7:
    case MA_DF_WORK_8:
      {
        temp_value = current_settings.timeout_work_df[address_data - MA_DF_WORK_1]/10;
        break;
      }
    case MA_CONTROL_MTZ:
      {
        int input_value = current_settings.control_mtz;
        
        temp_value = (((input_value >> N_BIT_CTRMTZ_1                ) & 0x1 ) << (BIT_MA_CONTROL_MTZ1               - BIT_MA_CONTROL_MTZ_BASE) ) |
                     (((input_value >> N_BIT_CTRMTZ_2                ) & 0x1 ) << (BIT_MA_CONTROL_MTZ2               - BIT_MA_CONTROL_MTZ_BASE) ) | 
                     (((input_value >> N_BIT_CTRMTZ_3                ) & 0x1 ) << (BIT_MA_CONTROL_MTZ3               - BIT_MA_CONTROL_MTZ_BASE) ) |
                     (((input_value >> N_BIT_CTRMTZ_4                ) & 0x1 ) << (BIT_MA_CONTROL_MTZ4               - BIT_MA_CONTROL_MTZ_BASE) ) |
                     (((input_value >> N_BIT_CTRMTZ_2_PRYSKORENNJA   ) & 0x1 ) << (BIT_MA_CONTROL_MTZ2_PRYSKORENNJA  - BIT_MA_CONTROL_MTZ_BASE) ) |
                     (((input_value >> N_BIT_CTRMTZ_2_PRYSKORENA     ) & 0x1 ) << (BIT_MA_CONTROL_MTZ2_PRYSKORENA    - BIT_MA_CONTROL_MTZ_BASE) ) |
                     (((input_value >> N_BIT_CTRMTZ_1_VPERED         ) & 0x1 ) << (BIT_MA_CONTROL_MTZ1_N_VPERED      - BIT_MA_CONTROL_MTZ_BASE) ) |
                     (((input_value >> N_BIT_CTRMTZ_1_NAZAD          ) & 0x1 ) << (BIT_MA_CONTROL_MTZ1_N_NAZAD       - BIT_MA_CONTROL_MTZ_BASE) ) |
                     (((input_value >> N_BIT_CTRMTZ_2_VPERED         ) & 0x1 ) << (BIT_MA_CONTROL_MTZ2_N_VPERED      - BIT_MA_CONTROL_MTZ_BASE) ) |
                     (((input_value >> N_BIT_CTRMTZ_2_NAZAD          ) & 0x1 ) << (BIT_MA_CONTROL_MTZ2_N_NAZAD       - BIT_MA_CONTROL_MTZ_BASE) ) |
                     (((input_value >> N_BIT_CTRMTZ_3_VPERED         ) & 0x1 ) << (BIT_MA_CONTROL_MTZ3_N_VPERED      - BIT_MA_CONTROL_MTZ_BASE) ) |
                     (((input_value >> N_BIT_CTRMTZ_3_NAZAD          ) & 0x1 ) << (BIT_MA_CONTROL_MTZ3_N_NAZAD       - BIT_MA_CONTROL_MTZ_BASE) ) |
                     (((input_value >> N_BIT_CTRMTZ_4_VPERED         ) & 0x1 ) << (BIT_MA_CONTROL_MTZ4_N_VPERED      - BIT_MA_CONTROL_MTZ_BASE) ) |
                     (((input_value >> N_BIT_CTRMTZ_4_NAZAD          ) & 0x1 ) << (BIT_MA_CONTROL_MTZ4_N_NAZAD       - BIT_MA_CONTROL_MTZ_BASE) ) |
                     (((input_value >> N_BIT_CTRMTZ_NESPR_KIL_NAPR   ) & 0x1 ) << (BIT_MA_CONTROL_MTZ_NESPR_KIL_NAPR - BIT_MA_CONTROL_MTZ_BASE) );
        break;
      }
    case MA_CONTROL_ZDZ:
      {
        int input_value = current_settings.control_zdz;
        
        temp_value = (((input_value >> INDEX_ML_CTRZDZ_STATE             ) & 0x1 ) << (BIT_MA_CONTROL_ZDZ                   - BIT_MA_CONTROL_ZDZ_BASE)) |
                     (((input_value >> INDEX_ML_CTRZDZ_STARTED_FROM_MTZ1 ) & 0x1 ) << (BIT_MA_CONTROL_ZDZ_STARTED_FROM_MTZ1 - BIT_MA_CONTROL_ZDZ_BASE)) |
                     (((input_value >> INDEX_ML_CTRZDZ_STARTED_FROM_MTZ2 ) & 0x1 ) << (BIT_MA_CONTROL_ZDZ_STARTED_FROM_MTZ2 - BIT_MA_CONTROL_ZDZ_BASE)) |
                     (((input_value >> INDEX_ML_CTRZDZ_STARTED_FROM_MTZ3 ) & 0x1 ) << (BIT_MA_CONTROL_ZDZ_STARTED_FROM_MTZ3 - BIT_MA_CONTROL_ZDZ_BASE)) |
                     (((input_value >> INDEX_ML_CTRZDZ_STARTED_FROM_MTZ4 ) & 0x1 ) << (BIT_MA_CONTROL_ZDZ_STARTED_FROM_MTZ4 - BIT_MA_CONTROL_ZDZ_BASE));
        break;
      }
    case MA_CONTROL_NZZ:
      {
        int input_value = current_settings.control_zz;
        
        temp_value = (((input_value >> INDEX_ML_CTR_ZZ1_3I0_STATE) & 0x1 ) << (BIT_MA_CONTROL_NZZ_3I0    - BIT_MA_CONTROL_NZZ_BASE)) |
                     (((input_value >> INDEX_ML_CTR_ZZ1_SECTOR   ) & 0x1 ) << (BIT_MA_CONTROL_NZZ_SECTOR - BIT_MA_CONTROL_NZZ_BASE)) |
                     (((input_value >> INDEX_ML_CTR_ZZ1_NZZ_STATE) & 0x1 ) << (BIT_MA_CONTROL_NZZ        - BIT_MA_CONTROL_NZZ_BASE)) |
                     (((input_value >> INDEX_ML_CTR_ZZ1_3U0_STATE) & 0x1 ) << (BIT_MA_CONTROL_NZZ_3U0    - BIT_MA_CONTROL_NZZ_BASE)) |
                     (((input_value >> INDEX_ML_CTR_ZZ1_TYPE_BIT ) & 0x1 ) << (BIT_MA_CONTROL_NZZ_TYPE   - BIT_MA_CONTROL_NZZ_BASE));
        break;
      }
    case MA_CONTROL_ZOP:
      {
        int input_value = current_settings.control_zop;
        
        temp_value = (((input_value >> CTR_ZOP_STATE_BIT) & 0x1 ) << (BIT_MA_CONTROL_ZOP1 - BIT_MA_CONTROL_ZOP_BASE));
        break;
      }
    case MA_CONTROL_UMIN:
      {
        int input_value = current_settings.control_Umin;
        
        temp_value = (((input_value >> INDEX_CTR_UMIN1          ) & 0x1 ) << (BIT_MA_CONTROL_UMIN1           - BIT_MA_CONTROL_UMIN_BASE)) |
                     (((input_value >> INDEX_CTR_UMIN2          ) & 0x1 ) << (BIT_MA_CONTROL_UMIN2           - BIT_MA_CONTROL_UMIN_BASE)) |
                     (((input_value >> INDEX_CTR_PO_UMIN1_OR_AND) & 0x1 ) << (BIT_MA_CONTROL_PO_UMIN1_AND_OR - BIT_MA_CONTROL_UMIN_BASE)) |
                     (((input_value >> INDEX_CTR_PO_UMIN2_OR_AND) & 0x1 ) << (BIT_MA_CONTROL_PO_UMIN2_AND_OR - BIT_MA_CONTROL_UMIN_BASE)) |
                     (((input_value >> INDEX_CTR_UMIN1_UBLK     ) & 0x1 ) << (BIT_MA_CONTROL_BLK_UMIN1_BY_U  - BIT_MA_CONTROL_UMIN_BASE)) |
                     (((input_value >> INDEX_CTR_UMIN2_UBLK     ) & 0x1 ) << (BIT_MA_CONTROL_BLK_UMIN2_BY_U  - BIT_MA_CONTROL_UMIN_BASE)) |
                     (((input_value >> INDEX_CTR_UMIN1_IBLK     ) & 0x1 ) << (BIT_MA_CONTROL_BLK_UMIN1_BY_I  - BIT_MA_CONTROL_UMIN_BASE)) |
                     (((input_value >> INDEX_CTR_UMIN2_IBLK     ) & 0x1 ) << (BIT_MA_CONTROL_BLK_UMIN2_BY_I  - BIT_MA_CONTROL_UMIN_BASE));
        break;
      }
    case MA_CONTROL_UMAX:
      {
        int input_value = current_settings.control_Umax;
        
        temp_value = (((input_value >> INDEX_CTR_UMAX1          ) & 0x1 ) << (BIT_MA_CONTROL_UMAX1           - BIT_MA_CONTROL_UMAX_BASE)) |
                     (((input_value >> INDEX_CTR_UMAX2          ) & 0x1 ) << (BIT_MA_CONTROL_UMAX2           - BIT_MA_CONTROL_UMAX_BASE)) |
                     (((input_value >> INDEX_CTR_PO_UMAX1_OR_AND) & 0x1 ) << (BIT_MA_CONTROL_PO_UMAX1_AND_OR - BIT_MA_CONTROL_UMAX_BASE)) |
                     (((input_value >> INDEX_CTR_PO_UMAX2_OR_AND) & 0x1 ) << (BIT_MA_CONTROL_PO_UMAX2_AND_OR - BIT_MA_CONTROL_UMAX_BASE));
        break;
      }
    case MA_CONTROL_558:
      {
        int input_value1 = current_settings.control_extra_settings_1;
        int input_value2 = current_settings.control_apv_zmn;
        int input_value3 = current_settings.control_control_U;
        
        temp_value = (((input_value1 >> INDEX_ML_CTREXTRA_SETTINGS_1_CTRL_PHASE_LINE ) & 0x1 ) << (BIT_MA_CONTROL_PHASE_LINE                - BIT_MA_CONTROL_558_BASE)) |
                     (((input_value1 >> INDEX_ML_CTREXTRA_SETTINGS_1_CTRL_3U0_Ubc_TN2) & 0x1 ) << (BIT_MA_CONTROL_3U0_Ubc_TN2               - BIT_MA_CONTROL_558_BASE)) |
                     (((input_value2 >> INDEX_CTR_APV_ZMN                            ) & 0x1 ) << (BIT_MA_CONTROL_APV_ZMN                   - BIT_MA_CONTROL_558_BASE)) |
                     (((input_value3 >> INDEX_CTR_U_OL                               ) & 0x1 ) << (BIT_MA_CONTROL_U_OL                      - BIT_MA_CONTROL_558_BASE)) |
                     (((input_value3 >> INDEX_CTR_U_RL                               ) & 0x1 ) << (BIT_MA_CONTROL_U_RL                      - BIT_MA_CONTROL_558_BASE));
        break;
      }
    case MA_CONTROL_UROV_PART1:
      {
        int input_value = current_settings.control_urov;
        
        temp_value = (((input_value >> INDEX_ML_CTRUROV_STATE              ) & 0x1 ) << (BIT_MA_CONTROL_UROV_STATE               - BIT_MA_CONTROL_UROV_BASE_PART1)) |
                     (((input_value >> INDEX_ML_CTRUROV_STARTED_FROM_MTZ1  ) & 0x1 ) << (BIT_MA_CONTROL_UROV_STARTED_FROM_MTZ1   - BIT_MA_CONTROL_UROV_BASE_PART1)) |
                     (((input_value >> INDEX_ML_CTRUROV_STARTED_FROM_MTZ2  ) & 0x1 ) << (BIT_MA_CONTROL_UROV_STARTED_FROM_MTZ2   - BIT_MA_CONTROL_UROV_BASE_PART1)) |
                     (((input_value >> INDEX_ML_CTRUROV_STARTED_FROM_MTZ3  ) & 0x1 ) << (BIT_MA_CONTROL_UROV_STARTED_FROM_MTZ3   - BIT_MA_CONTROL_UROV_BASE_PART1)) |
                     (((input_value >> INDEX_ML_CTRUROV_STARTED_FROM_MTZ4  ) & 0x1 ) << (BIT_MA_CONTROL_UROV_STARTED_FROM_MTZ4   - BIT_MA_CONTROL_UROV_BASE_PART1)) |
                     (((input_value >> INDEX_ML_CTRUROV_STARTED_FROM_UMAX1 ) & 0x1 ) << (BIT_MA_CONTROL_UROV_STARTED_FROM_UMAX1  - BIT_MA_CONTROL_UROV_BASE_PART1)) |
                     (((input_value >> INDEX_ML_CTRUROV_STARTED_FROM_UMAX2 ) & 0x1 ) << (BIT_MA_CONTROL_UROV_STARTED_FROM_UMAX2  - BIT_MA_CONTROL_UROV_BASE_PART1)) |
                     (((input_value >> INDEX_ML_CTRUROV_STARTED_FROM_UMIN1 ) & 0x1 ) << (BIT_MA_CONTROL_UROV_STARTED_FROM_UMIN1  - BIT_MA_CONTROL_UROV_BASE_PART1)) |
                     (((input_value >> INDEX_ML_CTRUROV_STARTED_FROM_UMIN2 ) & 0x1 ) << (BIT_MA_CONTROL_UROV_STARTED_FROM_UMIN2  - BIT_MA_CONTROL_UROV_BASE_PART1)) |
                     (((input_value >> INDEX_ML_CTRUROV_STARTED_FROM_ZOP1  ) & 0x1 ) << (BIT_MA_CONTROL_UROV_STARTED_FROM_ZOP1   - BIT_MA_CONTROL_UROV_BASE_PART1)) |
                     (((input_value >> INDEX_ML_CTRUROV_STARTED_FROM_3I0   ) & 0x1 ) << (BIT_MA_CONTROL_UROV_STARTED_FROM_3I0    - BIT_MA_CONTROL_UROV_BASE_PART1)) |
                     (((input_value >> INDEX_ML_CTRUROV_STARTED_FROM_3U0   ) & 0x1 ) << (BIT_MA_CONTROL_UROV_STARTED_FROM_3U0    - BIT_MA_CONTROL_UROV_BASE_PART1)) |
                     (((input_value >> INDEX_ML_CTRUROV_STARTED_FROM_NZZ   ) & 0x1 ) << (BIT_MA_CONTROL_UROV_STARTED_FROM_NZZ    - BIT_MA_CONTROL_UROV_BASE_PART1));
        break;
      }
    case MA_CONTROL_UROV_PART2:
      {
        int input_value = current_settings.control_urov;
        
        temp_value = (((input_value >> INDEX_ML_CTRUROV_STARTED_FROM_ZDZ ) & 0x1 ) << (BIT_MA_CONTROL_UROV_STARTED_FROM_ZDZ  - BIT_MA_CONTROL_UROV_BASE_PART2)) |
                     (((input_value >> INDEX_ML_CTRUROV_STARTED_FROM_ACHR) & 0x1 ) << (BIT_MA_CONTROL_UROV_STARTED_FROM_ACHR  - BIT_MA_CONTROL_UROV_BASE_PART2));
        break;
      }
    case MA_CONTROL_AVR:
      {
        int input_value = current_settings.control_avr;
        
        temp_value = (((input_value >> INDEX_CTR_AVR                      ) & 0x1 ) << (BIT_MA_CONTROL_AVR                       - BIT_MA_CONTROL_AVR_BASE)) |
                     (((input_value >> INDEX_CTR_AVR_OTKL_BLK_VID_ZAHYSTIV) & 0x1 ) << (BIT_MA_CONTROL_AVR_OTKL_BLK_VID_ZAHYSTIV - BIT_MA_CONTROL_AVR_BASE));
        break;
      }
    case MA_CONTROL_APV:
      {
        int input_value = current_settings.control_apv;
        
        temp_value = (((input_value >> INDEX_ML_CTRAPV_STAGE_1           ) & 0x1 ) << (BIT_MA_CONTROL_APV_CYCLE1            - BIT_MA_CONTROL_APV_BASE)) |
                     (((input_value >> INDEX_ML_CTRAPV_STAGE_2           ) & 0x1 ) << (BIT_MA_CONTROL_APV_CYCLE2            - BIT_MA_CONTROL_APV_BASE)) |
                     (((input_value >> INDEX_ML_CTRAPV_STAGE_3           ) & 0x1 ) << (BIT_MA_CONTROL_APV_CYCLE3            - BIT_MA_CONTROL_APV_BASE)) |
                     (((input_value >> INDEX_ML_CTRAPV_STAGE_4           ) & 0x1 ) << (BIT_MA_CONTROL_APV_CYCLE4            - BIT_MA_CONTROL_APV_BASE)) |
                     (((input_value >> INDEX_ML_CTRAPV_STARTED_FROM_MTZ1 ) & 0x1 ) << (BIT_MA_CONTROL_APV_STARTED_FROM_MTZ1 - BIT_MA_CONTROL_APV_BASE)) |
                     (((input_value >> INDEX_ML_CTRAPV_STARTED_FROM_MTZ2 ) & 0x1 ) << (BIT_MA_CONTROL_APV_STARTED_FROM_MTZ2 - BIT_MA_CONTROL_APV_BASE)) |
                     (((input_value >> INDEX_ML_CTRAPV_STARTED_FROM_MTZ3 ) & 0x1 ) << (BIT_MA_CONTROL_APV_STARTED_FROM_MTZ3 - BIT_MA_CONTROL_APV_BASE)) |
                     (((input_value >> INDEX_ML_CTRAPV_STARTED_FROM_MTZ4 ) & 0x1 ) << (BIT_MA_CONTROL_APV_STARTED_FROM_MTZ4 - BIT_MA_CONTROL_APV_BASE));
        break;
      }
    case MA_CONTROL_ACHR_CHAPV:
      {
        int input_value = current_settings.control_achr_chapv;
        
        temp_value = (((input_value >> INDEX_CTR_ACHR        ) & 0x1 ) << (BIT_MA_CONTROL_ACHR_STATE         - BIT_MA_CONTROL_ACHR_CHAPV_BASE)) |
                     (((input_value >> INDEX_CTR_CHAPV       ) & 0x1 ) << (BIT_MA_CONTROL_CHAPV_STATE        - BIT_MA_CONTROL_ACHR_CHAPV_BASE)) |
                     (((input_value >> INDEX_CTR_CHAPV_VID_DV) & 0x1 ) << (BIT_MA_CONTROL_CHAPV_VID_DV_STATE - BIT_MA_CONTROL_ACHR_CHAPV_BASE));
        break;
      }
    case MA_CONTROL_CTRL_VV:
      {
        int input_value1 = current_settings.control_switch;
        int input_value2 = current_settings.control_extra_settings_1;
        
        temp_value = (((input_value1 >> INDEX_ML_CTRPRYVOD_VV                          ) & 0x1 ) << (BIT_MA_CONTROL_CTRL_VV_STATE           - BIT_MA_CONTROL_CTRL_VV_BASE)) |
                     (((input_value2 >> INDEX_ML_CTREXTRA_SETTINGS_1_BLK_ON_CB_MISCEVE ) & 0x1 ) << (BIT_MA_CONTROL_CTRL_BLK_ON_CB_MISCEVE  - BIT_MA_CONTROL_CTRL_VV_BASE)) |
                     (((input_value2 >> INDEX_ML_CTREXTRA_SETTINGS_1_BLK_OFF_CB_MISCEVE) & 0x1 ) << (BIT_MA_CONTROL_CTRL_BLK_OFF_CB_MISCEVE - BIT_MA_CONTROL_CTRL_VV_BASE)) |
                     (((input_value2 >> INDEX_ML_CTREXTRA_SETTINGS_1_CTRL_FB_ACTIVATION) & 0x1 ) << (BIT_MA_CONTROL_CTRL_FB_ACTIVATION      - BIT_MA_CONTROL_CTRL_VV_BASE)) |
                     (((input_value1 >> INDEX_ML_CTRRESURS_VV                          ) & 0x1 ) << (BIT_MA_CONTROL_CTRL_RESURS_VV          - BIT_MA_CONTROL_CTRL_VV_BASE)) |
                     (((input_value2 >> INDEX_ML_CTREXTRA_SETTINGS_1_CTRL_READY_TU     ) & 0x1 ) << (BIT_MA_CONTROL_CTRL_READY_TU           - BIT_MA_CONTROL_CTRL_VV_BASE)) |
                     (((input_value2 >> INDEX_ML_CTREXTRA_SETTINGS_1_CTRL_WINDOW_OFF_CB) & 0x1 ) << (BIT_MA_CONTROL_CTRL_WINDOW_OFF_CB      - BIT_MA_CONTROL_CTRL_VV_BASE));
        break;
      }
    case MA_CONTROL_VMP:
      {
        int input_value = current_settings.control_vmp;
        
        temp_value = (((input_value >> INDEX_CTR_VMP_STATE) & 0x1 ) << (BIT_MA_CONTROL_VMP_STATE - BIT_MA_CONTROL_VMP_BASE));
        break;
      }
    case MA_CONFIGURATION_PART1:
      {
        int input_value = current_settings.configuration;
        
        temp_value = (((input_value >> MTZ_BIT_CONFIGURATION       ) & 0x1 ) << (BIT_MA_CONFIGURATION_MTZ        - BIT_MA_CONFIGURATION_BASE_PART1)) |
                     (((input_value >> ZDZ_BIT_CONFIGURATION       ) & 0x1 ) << (BIT_MA_CONFIGURATION_ZDZ        - BIT_MA_CONFIGURATION_BASE_PART1)) |
                     (((input_value >> ZZ_BIT_CONFIGURATION        ) & 0x1 ) << (BIT_MA_CONFIGURATION_ZZ         - BIT_MA_CONFIGURATION_BASE_PART1)) |
                     (((input_value >> ZOP_BIT_CONFIGURATION       ) & 0x1 ) << (BIT_MA_CONFIGURATION_ZOP        - BIT_MA_CONFIGURATION_BASE_PART1)) |
                     (((input_value >> ACHR_CHAPV_BIT_CONFIGURATION) & 0x1 ) << (BIT_MA_CONFIGURATION_ACHR_CHAPV - BIT_MA_CONFIGURATION_BASE_PART1)) |
                     (((input_value >> UMIN_BIT_CONFIGURATION      ) & 0x1 ) << (BIT_MA_CONFIGURATION_UMIN       - BIT_MA_CONFIGURATION_BASE_PART1)) |
                     (((input_value >> UMAX_BIT_CONFIGURATION      ) & 0x1 ) << (BIT_MA_CONFIGURATION_UMAX       - BIT_MA_CONFIGURATION_BASE_PART1)) |
                     (((input_value >> APV_ZMN_BIT_CONFIGURATION   ) & 0x1 ) << (BIT_MA_CONFIGURATION_APV_ZMN    - BIT_MA_CONFIGURATION_BASE_PART1)) |
                     (((input_value >> CONTROL_U_BIT_CONFIGURATION ) & 0x1 ) << (BIT_MA_CONFIGURATION_KROL       - BIT_MA_CONFIGURATION_BASE_PART1)) |
                     (((input_value >> APV_BIT_CONFIGURATION       ) & 0x1 ) << (BIT_MA_CONFIGURATION_APV        - BIT_MA_CONFIGURATION_BASE_PART1)) |
                     (((input_value >> UROV_BIT_CONFIGURATION      ) & 0x1 ) << (BIT_MA_CONFIGURATION_UROV       - BIT_MA_CONFIGURATION_BASE_PART1)) |
                     (((input_value >> AVR_BIT_CONFIGURATION       ) & 0x1 ) << (BIT_MA_CONFIGURATION_AVR        - BIT_MA_CONFIGURATION_BASE_PART1));
        break;
      }
    case MA_CONFIGURATION_PART2:
      {
        int input_value = current_settings.configuration;
        
        temp_value = (((input_value >> VMP_BIT_CONFIGURATION       ) & 0x1 ) << (BIT_MA_CONFIGURATION_VMP        - BIT_MA_CONFIGURATION_BASE_PART2));
        break;
      }
    case MA_TO_DEACTIVATION_PASSWORD_INTERFACE:
      {
          if (type_interface == USB_RECUEST)
          {
            temp_value = current_settings.timeout_deactivation_password_interface_USB;
          }
          else if (type_interface == RS485_RECUEST)
          {
            temp_value = current_settings.timeout_deactivation_password_interface_RS485;
          }
          else error = ERROR_SLAVE_DEVICE_FAILURE;
      
          break;
      }
    case MA_LANGUAGE_MENU:
      {
        temp_value = current_settings.language;
        break;
      }
    case MA_SPEED_RS485:
      {
        temp_value = current_settings.speed_RS485;
        break;
      }
    case MA_STOP_BITS_RS485:
      {
        temp_value = current_settings.number_stop_bit_RS485 + 1;
        break;
      }
    case MA_PARE_RS485:
      {
        temp_value = current_settings.pare_bit_RS485;
        break;
      }
    case MA_TIMEOUT_RS485:
      {
        temp_value = current_settings.time_out_1_RS485;
        break;
      }
    case MA_LOGICAL_ADDRESS:
      {
        temp_value = current_settings.address;
        break;
      }
    case MA_NAME_OF_CELL_CHARS_01_02:
    case MA_NAME_OF_CELL_CHARS_03_04:
    case MA_NAME_OF_CELL_CHARS_05_06:
    case MA_NAME_OF_CELL_CHARS_07_08:
    case MA_NAME_OF_CELL_CHARS_09_10:
    case MA_NAME_OF_CELL_CHARS_11_12:
    case MA_NAME_OF_CELL_CHARS_13_14:
    case MA_NAME_OF_CELL_CHARS_15_16:
      {
        unsigned int two_char_index = (address_data - MA_NAME_OF_CELL_CHARS_01_02) << 1;
        temp_value = (current_settings.name_of_cell[two_char_index] & 0xff) | ((current_settings.name_of_cell[two_char_index + 1] & 0xff) << 8);
        break;
      }
    default:
      {
        temp_value = 0;
        break;
      }
    }
  }
  else if ((address_data >= M_ADDRESS_FIRST_TIME_AND_DATA) && (address_data <= M_ADDRESS_LAST_TIME_AND_DATA))
  {
    unsigned char *label_to_time_array;
    
    if (copying_time == 0) label_to_time_array = time;
    else label_to_time_array = time_copy;
    
    switch (address_data)
    {
    case MA_YEAR:
      {
        temp_value = *(label_to_time_array + 6);
        break;
      }
    case MA_MONTH:
      {
        temp_value = *(label_to_time_array + 5);
        break;
      }
    case MA_DAY:
      {
        temp_value = *(label_to_time_array + 4);
        break;
      }
    case MA_HOUR:
      {
        temp_value = *(label_to_time_array + 3);
        break;
      }
    case MA_MINUTE:
      {
        temp_value = *(label_to_time_array + 2);
        break;
      }
    case MA_SECOND:
      {
        temp_value = *(label_to_time_array + 1);
        break;
      }
    case MA_MILISECOND:
      {
        temp_value = *(label_to_time_array + 0);
        break;
      }
    default:
      {
        temp_value = 0;
        break;
      }
    }
  }
  else if (
           (address_data >= M_ADDRESS_FIRST_CURRENT_AF ) && (address_data <= M_ADDRESS_LAST_CURRENT_AF) ||
           (address_data >= M_ADDRESS_FIRST_GENERAL_AF ) && (address_data <= M_ADDRESS_LAST_GENERAL_AF)
          )
  {
    //���� ������� �������� ������� ��� ��������� �������
    unsigned int input_array[N_BIG], base_address;
    unsigned short int output_array[22];
    
    //�������� ������� ���� �������� �����
    for (unsigned int i = 0; i< 22; i++ )output_array[i] = 0;

    if ((information_about_settings_changed & (1 << type_interface)) != 0)
    {
      output_array[(BIT_MA_SETTINGS_CHANGED - BIT_MA_CURRENT_AF_BASE) >> 4] |= 
        (0x1 << ((BIT_MA_SETTINGS_CHANGED - BIT_MA_CURRENT_AF_BASE) & 0xf));
    }

    //������� ������ ����������
    if ((address_data >= M_ADDRESS_FIRST_CURRENT_AF ) && (address_data <= M_ADDRESS_LAST_CURRENT_AF))
    {
      input_array[0] = active_functions[0];
      input_array[1] = active_functions[1];
      input_array[2] = active_functions[2];
      input_array[3] = active_functions[3];
      input_array[4] = active_functions[4];
      input_array[5] = active_functions[5];
      
      unsigned int password_set_tmp;
      if (type_interface == USB_RECUEST) password_set_tmp = password_set_USB;
      else if (type_interface == RS485_RECUEST) password_set_tmp = password_set_RS485;
        
      if (password_set_tmp != 0) 
      {
        output_array[(BIT_MA_PASSWORD_SET - BIT_MA_CURRENT_AF_BASE) >> 4] |= 
          (0x1 << ((BIT_MA_PASSWORD_SET - BIT_MA_CURRENT_AF_BASE) & 0xf));
      }
        
      base_address = M_ADDRESS_FIRST_CURRENT_AF;
    }
    else
    {
      if ((information_about_restart_counter & (1 << type_interface)) != 0)
      {
        output_array[(BIT_MA_RESET_RESURS_VYMYKACHA - BIT_MA_CURRENT_AF_BASE) >> 4] |= 
          (0x1 << ((BIT_MA_RESET_RESURS_VYMYKACHA - BIT_MA_CURRENT_AF_BASE) & 0xf));
      }

      if (type_interface == USB_RECUEST)
      {
        input_array[0] = trigger_functions_USB[0];
        input_array[1] = trigger_functions_USB[1];
        input_array[2] = trigger_functions_USB[2];
        input_array[3] = trigger_functions_USB[3];
        input_array[4] = trigger_functions_USB[4];
        input_array[5] = trigger_functions_USB[5];
      }
      else if (type_interface == RS485_RECUEST)
      {
        input_array[0] = trigger_functions_RS485[0];
        input_array[1] = trigger_functions_RS485[1];
        input_array[2] = trigger_functions_RS485[2];
        input_array[3] = trigger_functions_RS485[3];
        input_array[4] = trigger_functions_RS485[4];
        input_array[5] = trigger_functions_RS485[5];
      }
      else
      {
          //���������� ����� ����� �� ���� � ����
          total_error_sw_fixed(48);
      }
      base_address = M_ADDRESS_FIRST_GENERAL_AF;
    }
    
    //���������� ��������� ��������� � ������� "����������� ����� ���'��"
    convert_order_list_function_to_gmm(input_array, output_array);
    /*****************************************************/
    
    temp_value  = output_array[address_data - base_address];
  }
  else if ((address_data >= M_ADDRESS_FIRST_MEASUREMENTS_1) && (address_data <= M_ADDRESS_LAST_MEASUREMENTS_1))
  {
    //���� ���������� ���������� ������� ������������ ���'�
    switch (address_data)
    {
    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_MEASUREMENT_UA_1):
      {
        if ((current_settings.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_PHASE_LINE) == 0)
          temp_value = measurement_low[IM_UA] >> 3;
        else temp_value = 0;

        break;
      }
    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_MEASUREMENT_UB_1):
      {
        if ((current_settings.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_PHASE_LINE) == 0)
          temp_value = measurement_low[IM_UB] >> 3;
        else temp_value = 0;

        break;
      }
    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_MEASUREMENT_UC_1):
      {
        if ((current_settings.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_PHASE_LINE) == 0)
          temp_value = measurement_low[IM_UC] >> 3;
        else temp_value = 0;

        break;
      }
    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_MEASUREMENT_UAB_1):
      {
        temp_value = measurement_low[IM_UAB] >> 3;
        break;
      }
    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_MEASUREMENT_UBC_1):
      {
        temp_value = measurement_low[IM_UBC] >> 3;
        break;
      }
    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_MEASUREMENT_UCA_1):
      {
        temp_value = measurement_low[IM_UCA] >> 3;
        break;
      }
    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_MEASUREMENT_3U0_1):
      {
        if ((current_settings.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_3U0_Ubc_TN2) == 0)
          temp_value = measurement_low[IM_3U0_UBC_TN2] >> 3;
        else temp_value = 0;

        break;
      }
    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_MEASUREMENT_UAB_2):
      {
        temp_value = measurement_low[IM_UAB_TN2] >> 3;
        break;
      }
    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_MEASUREMENT_UBC_2):
      {
        if ((current_settings.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_3U0_Ubc_TN2) != 0)
          temp_value = measurement_low[IM_3U0_UBC_TN2] >> 3;
        else temp_value = 0;

        break;
      }
    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_MEASUREMENT_IA_1):
      {
        temp_value = measurement_low[IM_IA] >> 2;
        break;
      }
    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_MEASUREMENT_IB_1):
      {
        temp_value = measurement_low[IM_IB_r] >> 2;
        break;
      }
    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_MEASUREMENT_IC_1):
      {
        temp_value = measurement_low[IM_IC] >> 2;
        break;
      }
    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_MEASUREMENT_3I0):
      {
        temp_value = measurement_low[IM_3I0];
        break;
      }
    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_MEASUREMENT_3I0_HIGH_GARM):
      {
        temp_value = measurement_low[IM_3I0_other_g];
        break;
      }
    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_MEASUREMENT_I1):
      {
        temp_value = measurement_low[IM_I1] >> 2;
        break;
      }
    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_MEASUREMENT_I2):
      {
        temp_value = measurement_low[IM_I2] >> 2;
        break;
      }
    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_ACTIVE_POWER):
      {
        temp_value = P/50;
        break;
      }
    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_REACTIVE_POWER):
      {
        temp_value = Q/50;
        break;
      }
    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_FULL_POWER):
      {
        temp_value = S/50;
        break;
      }
    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_COS_PHI):
      {
        if (S != 0)
          temp_value = cos_phi_x1000;
        else
          temp_value = 0x0;
          
        break;
      }
    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_FREQUENCY_1):
    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_FREQUENCY_2):
      {
        int int_frequency;
        if (address_data == (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_FREQUENCY_1))int_frequency = (int)(frequency_val_1*100);
        else int_frequency = (int)(frequency_val_2*100);
        
        if (int_frequency > 0 /*�� ����� ������ - ������� �� ���������*/)
          temp_value = int_frequency;
        else
        {
          if (int_frequency == (-1*100))
            temp_value = (unsigned int)(-1);
          else if (int_frequency == (-2*100))
            temp_value = (unsigned int)(-2);
          else if (int_frequency == (-3*100))
            temp_value = (unsigned int)(-3);
          else
            temp_value = (unsigned int)(-4);
        }
        break;
      }
    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_EA_PLUS_LWB):
    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_EA_PLUS_MWB):
    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_EA_MINUS_LWB):
    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_EA_MINUS_MWB):
    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_ER_1_LWB):
    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_ER_1_MWB):
    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_ER_2_LWB):
    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_ER_2_MWB):
    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_ER_3_LWB):
    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_ER_3_MWB):
    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_ER_4_LWB):
    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_ER_4_MWB):
      {
        unsigned int shift = address_data - (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_EA_PLUS_LWB);
        unsigned int energy_x_1000 = (unsigned int)(energy[shift >> 1]*1000.0);
        if ((shift & 0x1) == 0)
        {
          //�������� ������� �����
          temp_value = energy_x_1000 & 0xffff;
        }
        else
        {
          //�������� ������ �����
          temp_value = (energy_x_1000 >> 16) & 0xffff;
        }

        break;
      }
    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_BASE_CANAL_FOR_ANGLE):
      {
        if (base_index_for_angle < FULL_ORT_3U0_Ubc_TN2) temp_value = base_index_for_angle + 1;
        else if (base_index_for_angle == FULL_ORT_3U0_Ubc_TN2)
        {
          if ((current_settings.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_3U0_Ubc_TN2) == 0)
            temp_value = base_index_for_angle + 1;
          else
            temp_value = base_index_for_angle + 2;
        }
        else if (base_index_for_angle == FULL_ORT_Uab_TN2) temp_value = base_index_for_angle + 2;
        else
        {
          //���������� ����� ����� �� ���� � ����
          total_error_sw_fixed(72);
        }

        break;
      }
    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_ANGLE_UA_1):
      {
        temp_value = (unsigned int)phi_angle[FULL_ORT_Ua];
        break;
      }
    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_ANGLE_UB_1):
      {
        temp_value = (unsigned int)phi_angle[FULL_ORT_Ub];
        break;
      }
    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_ANGLE_UC_1):
      {
        temp_value = (unsigned int)phi_angle[FULL_ORT_Uc];
        break;
      }
    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_ANGLE_UAB_1):
      {
        temp_value = (unsigned int)phi_angle[FULL_ORT_Uab];
        break;
      }
    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_ANGLE_UBC_1):
      {
        temp_value = (unsigned int)phi_angle[FULL_ORT_Ubc];
        break;
      }
    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_ANGLE_UCA_1):
      {
        temp_value = (unsigned int)phi_angle[FULL_ORT_Uca];
        break;
      }
    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_ANGLE_3U0_1):
      {
        if ((current_settings.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_3U0_Ubc_TN2) == 0)
          temp_value = (unsigned int)phi_angle[FULL_ORT_3U0_Ubc_TN2];
        else
          temp_value = (unsigned int)(-1);

        break;
      }
    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_ANGLE_UAB_2):
      {
        temp_value = (unsigned int)phi_angle[FULL_ORT_Uab_TN2];
        break;
      }
    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_ANGLE_UBC_2):
      {
        if ((current_settings.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_3U0_Ubc_TN2) != 0)
          temp_value = (unsigned int)phi_angle[FULL_ORT_3U0_Ubc_TN2];
        else
          temp_value = (unsigned int)(-1);

        break;
      }
    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_ANGLE_IA_1):
      {
        temp_value = (unsigned int)phi_angle[FULL_ORT_Ia];
        break;
      }
    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_ANGLE_IB_1):
      {
        temp_value = (unsigned int)phi_angle[FULL_ORT_Ib];
        break;
      }
    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_ANGLE_IC_1):
      {
        temp_value = (unsigned int)phi_angle[FULL_ORT_Ic];
        break;
      }
    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_ANGLE_3I0):
      {
        temp_value = (unsigned int)phi_angle[FULL_ORT_3I0];
        break;
      }
//    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_ANGLE_3I0_3U0):
//      {
//        if ((current_settings.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_3U0_Ubc_TN2) == 0)
//          temp_value = angle_3I0_3U0;
//        else temp_value = 0;
//
//        break;
//      }
    default:
      {
        temp_value = 0;
        break;
      }
    }
  }
  else if ((address_data >= M_COUNTER_FIRST) && (address_data <= M_COUNTER_LAST))
  {
    switch (address_data)
    {
    case MA_COUNTER_VIDKLJUCHENNJA_LSW:
      {
        temp_value = resurs_vidkljuchennja & 0xffff;
        break;
      }
    case MA_COUNTER_VIDKLJUCHENNJA_MSW:
      {
        temp_value = (resurs_vidkljuchennja >> 16) & 0xffff;
        break;
      }
    case MA_COUNTER_VYMYKACHA_LSW:
      {
        temp_value = resurs_vymykacha & 0xffff;
        break;
      }
    case MA_COUNTER_VYMYKACHA_MSW:
      {
        temp_value = (resurs_vymykacha >> 16) & 0xffff;
        break;
      }
    default:
      {
        //���������� ���� � �������� ����� �� ���� � ��������
        //��� ���� �����, �� ����������� ����������� ��� �������
        error = ERROR_ILLEGAL_DATA_VALUE;
        break;
      }
    }
  }  
  else if ((address_data >= M_ADDRESS_FIRST_MEASUREMENTS_DR) && (address_data <= M_ADDRESS_LAST_MEASUREMENTS_DR))
  {
    //����������, �� ���������� �� ��� ������ ����������� ����������
    if ((type_interface != USB_RECUEST) && (type_interface != RS485_RECUEST))
    {
      //���������� ������ ���� �� ���� � �����
      error = ERROR_SLAVE_DEVICE_FAILURE;
    }
    else if (
             ((type_interface == USB_RECUEST  ) && (number_record_of_dr_for_USB   == 0xffff)) ||
             ((type_interface == RS485_RECUEST) && (number_record_of_dr_for_RS485 == 0xffff))
            )
    {
      //�� ������ ����������������� ����������� ���������� ������ ����������� ����������
      error = ERROR_ILLEGAL_DATA_ADDRESS;
    }
    else if (
             ((clean_rejestrators & CLEAN_DR) != 0) ||
             (
              ((type_interface == USB_RECUEST  ) && ((control_tasks_dataflash & TASK_MAMORY_READ_DATAFLASH_FOR_DR_USB  ) != 0)) ||
              ((type_interface == RS485_RECUEST) && ((control_tasks_dataflash & TASK_MAMORY_READ_DATAFLASH_FOR_DR_RS485) != 0))
             ) 
            )
    {
      //����� ��� ���������� ��� ���������� ������ ����������� ����������, ��� ������� ����, ���� �� �������� � ��������� �����������
      error = ERROR_SLAVE_DEVICE_BUSY;
    }
    else
    {
      //����� ������ ���
      int number_block, offset;
      unsigned char *point_to_buffer;
      number_block = (address_data - M_ADDRESS_FIRST_MEASUREMENTS_DR) / MEASUREMENTS_DR_WIDTH;
      offset = (address_data - M_ADDRESS_FIRST_MEASUREMENTS_DR) - number_block*MEASUREMENTS_DR_WIDTH;
      if (type_interface == USB_RECUEST) point_to_buffer = buffer_for_USB_read_record_dr;
      else point_to_buffer = buffer_for_RS485_read_record_dr;
      
      if (
          number_block < (
                          (*(point_to_buffer + FIRST_INDEX_NUMBER_MAX_PHASE_DR  )) + 
                          (*(point_to_buffer + FIRST_INDEX_NUMBER_MAX_3I0_DR    )) + 
                          (*(point_to_buffer + FIRST_INDEX_NUMBER_MAX_3U0_DR    )) + 
                          (*(point_to_buffer + FIRST_INDEX_NUMBER_MIN_U_DR      )) + 
                          (*(point_to_buffer + FIRST_INDEX_NUMBER_MAX_U_DR      )) + 
                          (*(point_to_buffer + FIRST_INDEX_NUMBER_MAX_ZOP_DR    )) +
                          (*(point_to_buffer + FIRST_INDEX_NUMBER_MIN_F1_ACHR_DR)) +
                          (*(point_to_buffer + FIRST_INDEX_NUMBER_MIN_F2_ACHR_DR)) +
                          (*(point_to_buffer + FIRST_INDEX_NUMBER_F1_CHAPV_DR   )) +
                          (*(point_to_buffer + FIRST_INDEX_NUMBER_F2_CHAPV_DR   ))
                         )
         )
      {  
        unsigned int value, index;
        unsigned int control_extra_settings_1_tmp = *((unsigned int *)(point_to_buffer + FIRST_INDEX_EXTRA_SETTINGS_DR));
        
        switch (offset)
        {
        case DR_OFFSET_MEASUREMENT_IA_1:
          {
            index = FIRST_INDEX_FIRST_BLOCK_DR + (number_block*SIZE_ARRAY_FIX_MAX_MEASUREMENTS + 2)*sizeof(unsigned int);
            value = *((unsigned int *)(point_to_buffer + index));
            
            temp_value = value >> 2;
            break;
          }
        case DR_OFFSET_MEASUREMENT_IB_1:
          {
            index = FIRST_INDEX_FIRST_BLOCK_DR + (number_block*SIZE_ARRAY_FIX_MAX_MEASUREMENTS + 4)*sizeof(unsigned int);
            value = *((unsigned int *)(point_to_buffer + index));
            
            temp_value = value >> 2;
            break;
          }
        case DR_OFFSET_MEASUREMENT_IC_1:
          {
            index = FIRST_INDEX_FIRST_BLOCK_DR + (number_block*SIZE_ARRAY_FIX_MAX_MEASUREMENTS + 3)*sizeof(unsigned int);
            value = *((unsigned int *)(point_to_buffer + index));
            
            temp_value = value >> 2;
            break;
          }
        case DR_OFFSET_MEASUREMENT_3I0:
          {
            index = FIRST_INDEX_FIRST_BLOCK_DR + (number_block*SIZE_ARRAY_FIX_MAX_MEASUREMENTS + 0)*sizeof(unsigned int);
            value = *((unsigned int *)(point_to_buffer + index));
            
            temp_value = value;
            break;
          }
        case DR_OFFSET_MEASUREMENT_3I0_HIGH_GARM:
          {
            index = FIRST_INDEX_FIRST_BLOCK_DR + (number_block*SIZE_ARRAY_FIX_MAX_MEASUREMENTS + 1)*sizeof(unsigned int);
            value = *((unsigned int *)(point_to_buffer + index));
            
            temp_value = value;
            break;
          }
        case DR_OFFSET_MEASUREMENT_I1:
          {
            index = FIRST_INDEX_FIRST_BLOCK_DR + (number_block*SIZE_ARRAY_FIX_MAX_MEASUREMENTS + 6)*sizeof(unsigned int);
            value = *((unsigned int *)(point_to_buffer + index));
            
            temp_value = value >> 2;
            break;
          }
        case DR_OFFSET_MEASUREMENT_I2:
          {
            index = FIRST_INDEX_FIRST_BLOCK_DR + (number_block*SIZE_ARRAY_FIX_MAX_MEASUREMENTS + 5)*sizeof(unsigned int);
            value = *((unsigned int *)(point_to_buffer + index));
            
            temp_value = value >> 2;
            break;
          }
        case DR_OFFSET_MEASUREMENT_UAB_1:
          {
            index = FIRST_INDEX_FIRST_BLOCK_DR + (number_block*SIZE_ARRAY_FIX_MAX_MEASUREMENTS + 12)*sizeof(unsigned int);
            value = *((unsigned int *)(point_to_buffer + index));
            
            temp_value = value >> 3;
            break;
          }
        case DR_OFFSET_MEASUREMENT_UBC_1:
          {
            index = FIRST_INDEX_FIRST_BLOCK_DR + (number_block*SIZE_ARRAY_FIX_MAX_MEASUREMENTS + 13)*sizeof(unsigned int);
            value = *((unsigned int *)(point_to_buffer + index));
            
            temp_value = value >> 3;
            break;
          }
        case DR_OFFSET_MEASUREMENT_UCA_1:
          {
            index = FIRST_INDEX_FIRST_BLOCK_DR + (number_block*SIZE_ARRAY_FIX_MAX_MEASUREMENTS + 14)*sizeof(unsigned int);
            value = *((unsigned int *)(point_to_buffer + index));
            
            temp_value = value >> 3;
            break;
          }
        case DR_OFFSET_MEASUREMENT_UA_1:
          {
            if ((control_extra_settings_1_tmp & CTR_EXTRA_SETTINGS_1_CTRL_PHASE_LINE) == 0)
            {
              index = FIRST_INDEX_FIRST_BLOCK_DR + (number_block*SIZE_ARRAY_FIX_MAX_MEASUREMENTS + 7)*sizeof(unsigned int);
              value = *((unsigned int *)(point_to_buffer + index));
            
              temp_value = value >> 3;
            }
            else
            {
              temp_value = 0;
            }
            break;
          }
        case DR_OFFSET_MEASUREMENT_UB_1:
          {
            if ((control_extra_settings_1_tmp & CTR_EXTRA_SETTINGS_1_CTRL_PHASE_LINE) == 0)
            {
              index = FIRST_INDEX_FIRST_BLOCK_DR + (number_block*SIZE_ARRAY_FIX_MAX_MEASUREMENTS + 8)*sizeof(unsigned int);
              value = *((unsigned int *)(point_to_buffer + index));
            
              temp_value = value >> 3;
            }
            else
            {
              temp_value = 0;
            }
            break;
          }
        case DR_OFFSET_MEASUREMENT_UC_1:
          {
            if ((control_extra_settings_1_tmp & CTR_EXTRA_SETTINGS_1_CTRL_PHASE_LINE) == 0)
            {
              index = FIRST_INDEX_FIRST_BLOCK_DR + (number_block*SIZE_ARRAY_FIX_MAX_MEASUREMENTS + 9 )*sizeof(unsigned int);
              value = *((unsigned int *)(point_to_buffer + index));
            
              temp_value = value >> 3;
            }
            else
            {
              temp_value = 0;
            }
            break;
          }
        case DR_OFFSET_MEASUREMENT_3U0_1:
          {
            if ((control_extra_settings_1_tmp & CTR_EXTRA_SETTINGS_1_CTRL_3U0_Ubc_TN2) == 0)
            {
              index = FIRST_INDEX_FIRST_BLOCK_DR + (number_block*SIZE_ARRAY_FIX_MAX_MEASUREMENTS + 10)*sizeof(unsigned int);
              value = *((unsigned int *)(point_to_buffer + index));
            
              temp_value = value >> 3;
            }
            else
            {
              temp_value = 0;
            }
            break;
          }
        case DR_OFFSET_MEASUREMENT_UAB_2:
          {
            index = FIRST_INDEX_FIRST_BLOCK_DR + (number_block*SIZE_ARRAY_FIX_MAX_MEASUREMENTS + 11)*sizeof(unsigned int);
            value = *((unsigned int *)(point_to_buffer + index));
            
            temp_value = value >> 3;
            break;
          }
        case DR_OFFSET_MEASUREMENT_UBC_2:
          {
            if ((control_extra_settings_1_tmp & CTR_EXTRA_SETTINGS_1_CTRL_3U0_Ubc_TN2) != 0)
            {
              index = FIRST_INDEX_FIRST_BLOCK_DR + (number_block*SIZE_ARRAY_FIX_MAX_MEASUREMENTS + 10)*sizeof(unsigned int);
              value = *((unsigned int *)(point_to_buffer + index));
            
              temp_value = value >> 3;
            }
            else
            {
              temp_value = 0;
            }
            break;
          }
        case DR_OFFSET_FREQUENCY_1:
          {
            index = FIRST_INDEX_FIRST_BLOCK_DR + (number_block*SIZE_ARRAY_FIX_MAX_MEASUREMENTS + 15)*sizeof(unsigned int);
            value = *((unsigned int *)(point_to_buffer + index));
            
            temp_value = value / 10;
            break;
          }
        case DR_OFFSET_FREQUENCY_2:
          {
            index = FIRST_INDEX_FIRST_BLOCK_DR + (number_block*SIZE_ARRAY_FIX_MAX_MEASUREMENTS + 16)*sizeof(unsigned int);
            value = *((unsigned int *)(point_to_buffer + index));
            
            temp_value = value / 10;
            break;
          }
        case DR_OFFSET_VMP:
          {
            index = FIRST_INDEX_FIRST_BLOCK_DR + (number_block*SIZE_ARRAY_FIX_MAX_MEASUREMENTS + 23)*sizeof(unsigned int);
            int value_int = *((int *)(point_to_buffer + index));

            if (((unsigned int)value_int) != ((unsigned int)UNDEF_VMP))
            {
              if (abs(value_int) >= 10)
                temp_value = value_int/10;
              else
              {
                if (value_int >= 0)
                  temp_value = 1;
                else
                  temp_value = (unsigned int)(-1);
              }
            }
            else temp_value = 0;

            break;
          }
        case DR_OFFSET_LABEL_TIME_LSW:
        case DR_OFFSET_LABEL_TIME_MSW:
        case DR_OFFSET_LABEL_PROTECT:
          {
            index = FIRST_INDEX_FIRST_BLOCK_DR + (number_block*SIZE_ARRAY_FIX_MAX_MEASUREMENTS + 25)*sizeof(unsigned int);
            
            if (offset == DR_OFFSET_LABEL_TIME_LSW)
            {
              temp_value = (*(point_to_buffer + index + 0)) | ((*(point_to_buffer + index + 1)) << 8 );
            }
            else if (offset ==DR_OFFSET_LABEL_TIME_MSW)
            {
              temp_value =  *(point_to_buffer + index + 2);
            }
            else
            {
              value = *(point_to_buffer + index + 3);
              switch (value)
              {
              case IDENTIFIER_BIT_ARRAY_MAX_CURRENT_PHASE:
                {
                  temp_value = BLOCK_PROTECTION_MTZ;
                  break;
                }
              case IDENTIFIER_BIT_ARRAY_MAX_CURRENT_3I0:
                {
                  temp_value = BLOCK_PROTECTION_3I0;
                  break;
                }
              case IDENTIFIER_BIT_ARRAY_MAX_VOLTAGE_3U0:
                {
                  temp_value = BLOCK_PROTECTION_3U0;
                  break;
                }
              case IDENTIFIER_BIT_ARRAY_MIN_VOLTAGE:
                {
                  temp_value = BLOCK_PROTECTION_UMIN;
                  break;
                }
              case IDENTIFIER_BIT_ARRAY_MAX_VOLTAGE:
                {
                  temp_value = BLOCK_PROTECTION_UMAX;
                  break;
                }
              case IDENTIFIER_BIT_ARRAY_MAX_CURRENT_ZOP:
                {
                  temp_value = BLOCK_PROTECTION_ZOP;
                  break;
                }
              case IDENTIFIER_BIT_ARRAY_MIN_FREQUENCY_1_ACHR:
                {
                  temp_value = BLOCK_PROTECTION_FREQUENCY_1_ACHR;
                  break;
                }
              case IDENTIFIER_BIT_ARRAY_MIN_FREQUENCY_2_ACHR:
                {
                  temp_value = BLOCK_PROTECTION_FREQUENCY_2_ACHR;
                  break;
                }
              case IDENTIFIER_BIT_ARRAY_FREQUENCY_1_CHAPV:
                {
                  temp_value = BLOCK_PROTECTION_FREQUENCY_1_CAPV;
                  break;
                }
              case IDENTIFIER_BIT_ARRAY_FREQUENCY_2_CHAPV:
                {
                  temp_value = BLOCK_PROTECTION_FREQUENCY_2_CAPV;
                  break;
                }
              default:
                {
                  //���� ���� �������, �� ���� � �������� �� ���� ��������
                  temp_value = 0;
                  break;
                }
                  
              }
            }
            
            break;
          }
        default:
          {
            temp_value = 0;
            break;
          }
        }
      }
      else
      {
        if ((offset == DR_OFFSET_LABEL_TIME_LSW) || (offset == DR_OFFSET_LABEL_TIME_MSW)) temp_value = 0xffff;
        else temp_value = 0;
      }
    }
  }
  else if ((address_data >= M_ADDRESS_FIRST_DI_RANG) && (address_data <= M_ADDRESS_LAST_DI_RANG))
  {
    //��������, ���� ���� ����� ������ ����� ���������� ���������
    unsigned int number_input = (address_data - M_ADDRESS_FIRST_DI_RANG)>> VAGA_MAX_FUNCTIONS_IN_INPUT;
    
    if(number_input < NUMBER_INPUTS)
    {
      temp_value = convert_order_list_inputs_to_gmm(number_input, (((address_data - M_ADDRESS_FIRST_DI_RANG) & (MAX_FUNCTIONS_IN_INPUT - 1)) + 1));
    }
    else temp_value = 0;
  }
  else if ((address_data >= M_ADDRESS_FIRST_DO_RANG) && (address_data <= M_ADDRESS_LAST_DO_RANG))
  {
    //��������, ���� ����� ����� ������ ����� ���������� ���������
    unsigned int number_output = (address_data - M_ADDRESS_FIRST_DO_RANG)>>VAGA_MAX_FUNCTIONS_IN_OUTPUT;
    
    if(number_output < NUMBER_OUTPUTS)
    {
      temp_value = convert_order_list_oldr_to_gmm(number_output, (((address_data - M_ADDRESS_FIRST_DO_RANG) & (MAX_FUNCTIONS_IN_OUTPUT - 1)) + 1), SOURCE_OUTPUTS_RANG);
    }
    else temp_value = 0;
  }
  else if ((address_data >= M_ADDRESS_FIRST_LED_RANG) && (address_data <= M_ADDRESS_LAST_LED_RANG))
  {
    //��������, ���� �������� ����� ������ ����� ���������� ���������
    unsigned int number_led = (address_data - M_ADDRESS_FIRST_LED_RANG)>>VAGA_MAX_FUNCTIONS_IN_LED;
    
    if(number_led < NUMBER_LEDS)
    {
      temp_value = convert_order_list_oldr_to_gmm(number_led, (((address_data - M_ADDRESS_FIRST_LED_RANG) & (MAX_FUNCTIONS_IN_LED - 1)) + 1), SOURCE_LEDS_RANG);
    }
    else temp_value = 0;
  }
  else if ((address_data >=  M_ADDRESS_FIRST_DF_RANG) && (address_data <= M_ADDRESS_LAST_DF_RANG))
  {
    //��������, ��� 0-������� ����� ������ ����� ���������� ���������
    unsigned int number_df_mul_3 = (address_data -  M_ADDRESS_FIRST_DF_RANG)>>VAGA_MAX_FUNCTIONS_IN_DF;
    
    if(number_df_mul_3 <  (NUMBER_DEFINED_FUNCTIONS*3))
    {
      temp_value = convert_order_list_oldr_to_gmm((number_df_mul_3 / 3), (((address_data -  M_ADDRESS_FIRST_DF_RANG) & (MAX_FUNCTIONS_IN_DF - 1)) + 1), (SOURCE_DF_PLUS_RANG + (number_df_mul_3 % 3)));
    }
    else temp_value = 0;
  }
  else if ((address_data >= M_ADDRESS_FIRST_DB_RANG) && (address_data <= M_ADDRESS_LAST_DB_RANG))
  {
    //��������, ��� �-������ ����� ������ ����� ���������� ���������
    unsigned int number_db = (address_data - M_ADDRESS_FIRST_DB_RANG)>> VAGA_MAX_FUNCTIONS_IN_DB;
    
    if(number_db < NUMBER_DEFINED_BUTTONS)
    {
      temp_value = convert_order_list_buttons_to_gmm(number_db, (((address_data - M_ADDRESS_FIRST_DB_RANG) & (MAX_FUNCTIONS_IN_DB - 1)) + 1));
    }
    else temp_value = 0;
  }
  else if ((address_data >= M_ADDRESS_FIRST_DT_RANG) && (address_data <= M_ADDRESS_LAST_DT_RANG))
  {
    //���������, ���� ������� ����� ������ ����� ���������� ���������
    unsigned int number_defined_triggers = (address_data - M_ADDRESS_FIRST_DT_RANG) / MAX_FUNCTIONS_IN_DT;
    
    if(number_defined_triggers < (NUMBER_DEFINED_TRIGGERS << 2))
    {
      temp_value = convert_order_list_oldr_to_gmm((number_defined_triggers >> 2),
                               (((address_data -  M_ADDRESS_FIRST_DT_RANG) % MAX_FUNCTIONS_IN_DT) + 1),
                               (SOURCE_SET_DT_PLUS_RANG + (number_defined_triggers % 4)));
    }
    else temp_value = 0;
  }
  else if ((address_data >= M_ADDRESS_FIRST_SETPOINTS_RANG_AR) && (address_data <= M_ADDRESS_LAST_SETPOINTS_RANG_AR))
  {
    temp_value  = convert_order_list_oldr_to_gmm(0, (((address_data - M_ADDRESS_FIRST_SETPOINTS_RANG_AR) & (MAX_FUNCTIONS_IN_AREG - 1)) + 1), SOURCE_AR_RANG);
  }
  else if (address_data == MA_PREFAULT_INTERVAL_AR)
  {
    //������� ������� ����������� ������ (������� ������ ���������� �������)
    temp_value = current_settings.prefault_number_periods;
  }
  else if (address_data == MA_POSTFAULT_INTERVAL_AR)
  {
    //������� ������� ������������� ������ (������� ������ ���������� �������)
    temp_value = current_settings.postfault_number_periods;
  }
  else if (address_data == MA_TOTAL_NUMBER_RECORDS_AR)
  {
    temp_value = info_rejestrator_ar.number_records;
  }
  else if (address_data == MA_CURRENT_NUMBER_RECORD_AR)
  {
    if (type_interface == USB_RECUEST) temp_value = number_record_of_ar_for_USB;
    else if (type_interface == RS485_RECUEST) temp_value = number_record_of_ar_for_RS485;
    else
    {
      //���������� ������ ���� �� ���� � �����
      error = ERROR_SLAVE_DEVICE_FAILURE;
    }
  }
  else if ((address_data >= M_ADDRESS_FIRST_SETPOINTS_RANG_DR) && (address_data <= M_ADDRESS_LAST_SETPOINTS_RANG_DR))
  {
    temp_value  = convert_order_list_oldr_to_gmm(0, (((address_data - M_ADDRESS_FIRST_SETPOINTS_RANG_DR) & (MAX_FUNCTIONS_IN_DREG - 1)) + 1), SOURCE_DR_RANG);
  }
  else if (address_data == MA_TOTAL_NUMBER_RECORDS_DR)
  {
    temp_value = info_rejestrator_dr.number_records;
  }
  else if (address_data == MA_CURRENT_NUMBER_RECORD_DR)
  {
    if (type_interface == USB_RECUEST) temp_value = number_record_of_dr_for_USB;
    else if (type_interface == RS485_RECUEST) temp_value = number_record_of_dr_for_RS485;
    else
    {
      //���������� ������ ���� �� ���� � �����
      error = ERROR_SLAVE_DEVICE_FAILURE;
    }
  }
  else if (address_data == MA_TOTAL_NUMBER_RECORDS_PR_ERR)
  {
    temp_value = info_rejestrator_pr_err.number_records;
  }
  else if (address_data == MA_CURRENT_NUMBER_RECORD_PR_ERR)
  {
    if (type_interface == USB_RECUEST) temp_value = number_record_of_pr_err_into_USB;
    else if (type_interface == RS485_RECUEST) temp_value = number_record_of_pr_err_into_RS485;
    else
    {
      //���������� ������ ���� �� ���� � �����
      error = ERROR_SLAVE_DEVICE_FAILURE;
    }
  }
  else if ((address_data >= MA_FIRST_ADR_PR_ERR_WINDOW) && (address_data <= MA_LASR_ADR_PR_ERR_WINDOW))
  {
    if ((type_interface != USB_RECUEST) && (type_interface != RS485_RECUEST))
    {
      //���������� ������ ���� �� ���� � �����
      error = ERROR_SLAVE_DEVICE_FAILURE;
    }
    else if (
             ((type_interface == USB_RECUEST  ) && (number_record_of_pr_err_into_USB   == 0xffff)) ||
             ((type_interface == RS485_RECUEST) && (number_record_of_pr_err_into_RS485 == 0xffff))
            )
    {
      //�� ������ ����������������� ����������� ���������� ������ ���������� ���������� ����
      error = ERROR_ILLEGAL_DATA_ADDRESS;
    }
    else if (
             ((clean_rejestrators & CLEAN_PR_ERR) != 0) ||
             (
              ((type_interface == USB_RECUEST  ) && ((control_tasks_dataflash & TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_USB  ) != 0)) ||
              ((type_interface == RS485_RECUEST) && ((control_tasks_dataflash & TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_RS485) != 0))
             ) 
            )
    {
      //����� ��� ���������� ��� ���������� ������ ���������� ���������� ����, ��� ������� ����, ���� �� �������� � ��������� �����������
      error = ERROR_SLAVE_DEVICE_BUSY;
    }
    else if (
             (
              (type_interface == USB_RECUEST)
              && 
              (
               (number_record_of_pr_err_into_USB >= info_rejestrator_pr_err.number_records) ||
               (number_record_of_pr_err_into_USB >= MAX_NUMBER_RECORDS_INTO_PR_ERR        ) /*��� ���������� �� ����� �� ������������� ������ ������ ������*/ 
              )   
             )
             ||   
             (
              (type_interface == RS485_RECUEST)
              && 
              (
               (number_record_of_pr_err_into_RS485 >= info_rejestrator_pr_err.number_records) ||
               (number_record_of_pr_err_into_RS485 >= MAX_NUMBER_RECORDS_INTO_PR_ERR        ) /*��� ���������� �� ����� �� ������������� ������ ������ ������*/ 
              )   
             )
            )    
    {
      //����������� ����������� �������
      error = ERROR_SLAVE_DEVICE_FAILURE;
      
     //�������, �� ����� ������ �� ��������
      if (type_interface == USB_RECUEST) number_record_of_pr_err_into_USB = 0xffff;
      else if (type_interface == RS485_RECUEST) number_record_of_pr_err_into_RS485 = 0xffff;
    }
    else
    {
      unsigned char *point_to_buffer;
      if (type_interface == USB_RECUEST) point_to_buffer = buffer_for_USB_read_record_pr_err;
      else point_to_buffer = buffer_for_RS485_read_record_pr_err;

      if ( (*(point_to_buffer + 0)) != LABEL_START_RECORD_PR_ERR)
      {
        //����������� ���������� ���
        error = ERROR_SLAVE_DEVICE_FAILURE;
      }
      else
      {
        unsigned int temp_address = address_data - MA_FIRST_ADR_PR_ERR_WINDOW;
        switch (temp_address)
        {
        case 0:
          {
            temp_value = ((*(point_to_buffer + 7))  << 8) | (*(point_to_buffer + 6));
            break;
          }
        case 1:
          {
            temp_value =  (*(point_to_buffer + 5))  << 8;
            break;
          }
        case 2:
          {
            temp_value = ((*(point_to_buffer + 4))  << 8) | (*(point_to_buffer + 3));
            break;
          }
        case 3:
          {
            temp_value = ((*(point_to_buffer + 2))  << 8) | (*(point_to_buffer + 1));
            break;
          }
        case 4:
          {
            temp_value = ((*(point_to_buffer + 10))  << 8) | (*(point_to_buffer + 9));
            break;
          }
        case 5:
          {
            temp_value = ((*(point_to_buffer + 12))  << 8) | (*(point_to_buffer + 11));
            break;
          }
        case 6:
          {
            temp_value = ((*(point_to_buffer + 14))  << 8) | (*(point_to_buffer + 13));
            break;
          }
        case 7:
          {
            temp_value = ((*(point_to_buffer + 16))  << 8) | (*(point_to_buffer + 15));
            break;
          }
        case 8:
          {
            temp_value = ((*(point_to_buffer + 18))  << 8) | (*(point_to_buffer + 17));
            break;
          }
        case 9:
          {
            temp_value = ((*(point_to_buffer + 20))  << 8) | (*(point_to_buffer + 19));
            break;
          }
        case 10:
          {
            temp_value = ((*(point_to_buffer + 22))  << 8) | (*(point_to_buffer + 21));
            break;
          }
        case 11:
          {
            temp_value = ((*(point_to_buffer + 24))  << 8) | (*(point_to_buffer + 23));
            break;
          }
        case 12:
          {
            temp_value = ((*(point_to_buffer + 26))  << 8) | (*(point_to_buffer + 25));
            break;
          }
        case 13:
          {
            temp_value = ((*(point_to_buffer + 28))  << 8) | (*(point_to_buffer + 27));
            break;
          }
        case 14:
          {
            temp_value = ((*(point_to_buffer + 30))  << 8) | (*(point_to_buffer + 29));
            break;
          }
        default:
          {
            //���� ���� �������, �� ���� � �������� �� ���� ��������
            temp_value = 0;
            break;
          }
        }
      }
    }
  }
  else if (address_data == MA_POSSIBILITY_USTUVANNJA)
  {
    //����������� ��� ��, �� ����� ��������� ������� ���������
    /*
     0 - �������� ��������� � �����������
     1 - �������� ��������� � ����������
    */
    if (password_ustuvannja == 0x1978) temp_value = 1;
    else temp_value = 0;
  }
  else if ((address_data >= MA_ADDRESS_FIRST_USTUVANNJA ) && (address_data <= MA_ADDRESS_LAST_USTUVANNJA))
  {
    temp_value = ustuvannja[address_data - MA_ADDRESS_FIRST_USTUVANNJA ];
  }
  else if ((address_data >= MA_ADDRESS_FIRST_PHI_USTUVANNJA ) && (address_data <= MA_ADDRESS_LAST_PHI_USTUVANNJA))
  {
    temp_value = phi_ustuvannja[address_data - MA_ADDRESS_FIRST_PHI_USTUVANNJA ];
  }
  else if ((address_data >= M_ADDRESS_FIRST_MEASUREMENTS_2) && (address_data <= M_ADDRESS_LAST_MEASUREMENTS_2))
  {
    //���� ���������� ���������� ������� ����������� ������ ���� �������� ������� ������� �� �����
    switch (address_data)
    {
    case (M_ADDRESS_FIRST_MEASUREMENTS_2 + OFFSET_MEASUREMENT_3I0_I):
      {
        temp_value = measurement_low[IM_3I0_i];
        break;
      }
    default:
      {
        temp_value = 0;
        break;
      }
    }
  }
  else if (address_data == MA_LSW_GLOBAL_RESURS_MIN)
  {
    temp_value = resurs_global_min & 0xffff;
  }
  else if (address_data == MA_MSW_GLOBAL_RESURS_MIN)
  {
    temp_value = resurs_global_min >> 16;
  }
  else if (address_data == MA_LSW_GLOBAL_RESURS_MAX)
  {
    temp_value = resurs_global_max & 0xffff;
  }
  else if (address_data == MA_MSW_GLOBAL_RESURS_MAX)
  {
    temp_value = resurs_global_max >> 16;
  }
  else if (address_data == MA_LSW_GLOBAL_RESURS)
  {
    temp_value = resurs_global & 0xffff;
  }
  else if (address_data == MA_MSW_GLOBAL_RESURS)
  {
    temp_value = resurs_global >> 16;
  }
  else if (address_data == MA_LSW_ADR_MEMORY_TO_WRITE)
  {
    temp_value = registers_address_write & 0xffff;
  }
  else if (address_data == MA_MSW_ADR_MEMORY_TO_WRITE)
  {
    temp_value = registers_address_write >> 16;
  }
  else if (address_data == MA_NB_REG_FROM_MEM_READ)
  {
    temp_value = number_registers_read;
  }
  else if (address_data == MA_LSW_ADR_MEMORY_TO_READ)
  {
    temp_value = registers_address_read & 0xffff;
  }
  else if (address_data == MA_MSW_ADR_MEMORY_TO_READ)
  {
    temp_value = registers_address_read >> 16;
  }
  else if((address_data >= M_ADDRESS_FIRST_READ_DAMP_MEM) && (address_data < M_ADDRESS_LAST_READ_DAMP_MEM))
  {
    temp_value = registers_values [address_data - M_ADDRESS_FIRST_READ_DAMP_MEM];
  }
  else if ((address_data >= M_ADDRESS_FIRST_TMP_MEASURMENTS) && (address_data < M_ADDRESS_LAST_TMP_MEASURMENTS))
  {
    if((address_data & 0x1) == 0)
    {
      temp_value = measurement_low[(address_data - M_ADDRESS_FIRST_TMP_MEASURMENTS)>>1] >> 16;
    }
    else
    {
      temp_value = measurement_low[(address_data - M_ADDRESS_FIRST_TMP_MEASURMENTS)>>1] & 0xffff;
    }
  }
  else if((address_data >= M_ADDRESS_FIRST_DIG_OSCILOGRAPH)&& (address_data < M_ADDRESS_LAST_DIG_OSCILOGRAPH))
  {
    if(action_is_continued == true) error = ERROR_SLAVE_DEVICE_BUSY;
    else
    {
      int temp_value_32bit = current_data_transmit[(part_transmit_carrent_data<<3) + ((address_data - M_ADDRESS_FIRST_DIG_OSCILOGRAPH) >> 1)];
      if ( ((address_data - M_ADDRESS_FIRST_DIG_OSCILOGRAPH) & 0x1)  == 0)
      {
        //������ �����
        temp_value = (((unsigned int)temp_value_32bit) >> 16) & 0xffff;
      }
      else
      {
        //������� �����
        temp_value = (((unsigned int)temp_value_32bit)      ) & 0xffff;
      }
    }
  }
  else
  {
    error = ERROR_ILLEGAL_DATA_ADDRESS;
  }
  
  //���������� � ����� ������ ��� � ������� ��������� ��������� ������� (��� �������. ���� ���� �����������)
  if (error == 0)
  {
    *data      = (temp_value >> 8) & 0xff;
    *(data +1) =  temp_value       & 0xff;
  }
  
  return error;
}
/***********************************************************************************/

/***********************************************************************************/
//����� �����
/***********************************************************************************/
inline unsigned int Set_data(unsigned short int data, unsigned int address_data, unsigned int method_setting, unsigned int to_be_continue, unsigned int type_interface)
{
  unsigned int error = 0, temp_value;
  
  __SETTINGS *target_label;
  if (method_setting == SET_DATA_IMMEDITATE) target_label = &current_settings;
  else target_label = &edition_settings;

  if (address_data == MA_PASSWORD_INTERFACE)
  {
    //������������/������ ������ �������
    if (type_interface == USB_RECUEST)
    {
      if (password_set_USB != 0)
      {
        if ((data == target_label->password_interface_USB) || (data == 0x1978)) password_set_USB = 0;
        else error = ERROR_ILLEGAL_DATA_VALUE;
      }
      else if (password_set_USB == 0)
      {
        previous_password_interface = target_label->password_interface_USB;
        target_label->password_interface_USB = data;
        if (data != 0) password_set_USB = 1;
      }
    }
    else if (type_interface == RS485_RECUEST)
    {
      if (password_set_RS485 != 0)
      {
        if ((data == target_label->password_interface_RS485) || (data == 0x1978)) password_set_RS485 = 0;
        else error = ERROR_ILLEGAL_DATA_VALUE;
      }
      else if (password_set_RS485 == 0)
      {
        previous_password_interface = target_label->password_interface_RS485;
        target_label->password_interface_RS485 = data;
        if (data != 0) password_set_RS485 = 1;
      }
    }
    else error = ERROR_SLAVE_DEVICE_FAILURE;
  }
  else if ((address_data >= M_ADDRESS_FIRST_SETPOINTS_PART1) && (address_data <= M_ADDRESS_LAST_SETPOINTS_PART1))
  {
    switch (address_data)
    {
    case MA_GROUP_USTAVOK:
      {
        temp_value = data;
        
#if (SETPOINT_GRUPA_USTAVOK_MIN != 0)          
        if ((temp_value >= SETPOINT_GRUPA_USTAVOK_MIN) && (temp_value <= SETPOINT_GRUPA_USTAVOK_MAX))
#else
        if (temp_value <= SETPOINT_GRUPA_USTAVOK_MAX)
#endif            
          target_label->grupa_ustavok = temp_value;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_TYPE_MTZ1:
      {
        temp_value = data;
        
#if (TYPE_MTZ_SIMPLE != 0)          
        if ((temp_value >= TYPE_MTZ_SIMPLE) && (temp_value <= TYPE_MTZ_VOLTAGE))
#else
        if (temp_value <= TYPE_MTZ_VOLTAGE)
#endif            
          target_label->type_mtz1 = temp_value;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_TYPE_MTZ2:
      {
        temp_value = data;
        
#if (TYPE_MTZ_SIMPLE != 0)          
        if ((temp_value >= TYPE_MTZ_SIMPLE) && (temp_value <= TYPE_MTZ_DEPENDENT_RTV_I))
#else
        if (temp_value <= TYPE_MTZ_DEPENDENT_RTV_I)
#endif            
          target_label->type_mtz2 = temp_value;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_TYPE_MTZ3:
      {
        temp_value = data;
        
#if (TYPE_MTZ_SIMPLE != 0)          
        if ((temp_value >= TYPE_MTZ_SIMPLE) && (temp_value <= TYPE_MTZ_VOLTAGE))
#else
        if (temp_value <= TYPE_MTZ_VOLTAGE)
#endif            
          target_label->type_mtz3 = temp_value;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_TYPE_MTZ4:
      {
        temp_value = data;
        
#if (TYPE_MTZ_SIMPLE != 0)          
        if ((temp_value >= TYPE_MTZ_SIMPLE) && (temp_value <= TYPE_MTZ_VOLTAGE))
#else
        if (temp_value <= TYPE_MTZ_VOLTAGE)
#endif            
          target_label->type_mtz4 = temp_value;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    default: break;
    }
  }
  else if (
           ((address_data >= (M_ADDRESS_FIRST_SETPOINTS_ZACHYSTIV + SHIFT_G1)) && (address_data <= (M_ADDRESS_LAST_SETPOINTS_ZACHYSTIV + SHIFT_G1))) ||
           ((address_data >= (M_ADDRESS_FIRST_SETPOINTS_ZACHYSTIV + SHIFT_G2)) && (address_data <= (M_ADDRESS_LAST_SETPOINTS_ZACHYSTIV + SHIFT_G2))) ||
           ((address_data >= (M_ADDRESS_FIRST_SETPOINTS_ZACHYSTIV + SHIFT_G3)) && (address_data <= (M_ADDRESS_LAST_SETPOINTS_ZACHYSTIV + SHIFT_G3))) ||
           ((address_data >= (M_ADDRESS_FIRST_SETPOINTS_ZACHYSTIV + SHIFT_G4)) && (address_data <= (M_ADDRESS_LAST_SETPOINTS_ZACHYSTIV + SHIFT_G4)))
          )   
  {
    //�������, ��������, �� ����� ������� ���� �������
     unsigned int num_gr, address_data_tmp = address_data;
     if ((address_data >= (M_ADDRESS_FIRST_SETPOINTS_ZACHYSTIV + SHIFT_G1)) && (address_data <= (M_ADDRESS_LAST_SETPOINTS_ZACHYSTIV + SHIFT_G1)))
     {
       num_gr = 0;
       address_data_tmp -= SHIFT_G1;
     }
     else if ((address_data >= (M_ADDRESS_FIRST_SETPOINTS_ZACHYSTIV + SHIFT_G2)) && (address_data <= (M_ADDRESS_LAST_SETPOINTS_ZACHYSTIV + SHIFT_G2)))
     {
       num_gr = 1;
       address_data_tmp -= SHIFT_G2;
     }
     else if ((address_data >= (M_ADDRESS_FIRST_SETPOINTS_ZACHYSTIV + SHIFT_G3)) && (address_data <= (M_ADDRESS_LAST_SETPOINTS_ZACHYSTIV + SHIFT_G3)))
     {
       num_gr = 2;
       address_data_tmp -= SHIFT_G3;
     }
     else
     {
       num_gr = 3;
       address_data_tmp -= SHIFT_G4;
     }
     
    switch (address_data_tmp)
    {
    case MA_STP_MTZ1:
      {
        temp_value = data*10;
    
        if ((temp_value >= SETPOINT_MTZ1_MIN) && (temp_value <= SETPOINT_MTZ1_MAX))
          target_label->setpoint_mtz_1[num_gr] = temp_value;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_STP_MTZ1_N_VPERED:
      {
        temp_value = data*10;
    
        if ((temp_value >= SETPOINT_MTZ1_N_VPERED_MIN) && (temp_value <= SETPOINT_MTZ1_N_VPERED_MAX))
          target_label->setpoint_mtz_1_n_vpered[num_gr] = temp_value;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_STP_MTZ1_N_NAZAD:
      {
        temp_value = data*10;
    
        if ((temp_value >= SETPOINT_MTZ1_N_NAZAD_MIN) && (temp_value <= SETPOINT_MTZ1_N_NAZAD_MAX))
          target_label->setpoint_mtz_1_n_nazad[num_gr] = temp_value;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_STP_MTZ1_PO_NAPRUZI:
      {
        temp_value = data*10;
    
        if ((temp_value >= SETPOINT_MTZ1_PO_NAPRUZI_MIN) && (temp_value <= SETPOINT_MTZ1_PO_NAPRUZI_MAX))
          target_label->setpoint_mtz_1_po_napruzi[num_gr] = temp_value;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_STP_MTZ1_U:
      {
        temp_value = data*10;
    
        if ((temp_value >= SETPOINT_MTZ1_U_MIN) && (temp_value <= SETPOINT_MTZ1_U_MAX))
          target_label->setpoint_mtz_1_U[num_gr] = temp_value;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_STP_MTZ1_ANGLE:
      {
        temp_value = data;
        
#if (SETPOINT_MTZ1_ANGLE_MIN != 0)          
        if ((temp_value >= SETPOINT_MTZ1_ANGLE_MIN) && (temp_value <= SETPOINT_MTZ1_ANGLE_MAX))
#else
        if (temp_value <= SETPOINT_MTZ1_ANGLE_MAX)
#endif            
        {
          target_label->setpoint_mtz_1_angle[num_gr] = temp_value;

          float temp_value_f = (float)temp_value;
          target_label->setpoint_mtz_1_angle_cos[num_gr] = (int) (AMPLITUDA_FI*/*cos*/arm_cos_f32(/*(double)*/(PI*temp_value_f/180.0f)));
          target_label->setpoint_mtz_1_angle_sin[num_gr] = (int) (AMPLITUDA_FI*/*sin*/arm_sin_f32(/*(double)*/(PI*temp_value_f/180.0f)));
        }
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_TO_MTZ1:
      {
        temp_value = data*10;
        
#if (TIMEOUT_MTZ1_MIN != 0)          
        if ((temp_value >= TIMEOUT_MTZ1_MIN) && (temp_value <= TIMEOUT_MTZ1_MAX))
#else
        if (temp_value <= TIMEOUT_MTZ1_MAX)
#endif            
        {
          target_label->timeout_mtz_1[num_gr] = temp_value;
        }
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_TO_MTZ1_N_VPERED:
      {
        temp_value = data*10;
        
#if (TIMEOUT_MTZ1_N_VPERED_MIN != 0)          
        if ((temp_value >= TIMEOUT_MTZ1_N_VPERED_MIN) && (temp_value <= TIMEOUT_MTZ1_N_VPERED_MAX))
#else
        if (temp_value <= TIMEOUT_MTZ1_N_VPERED_MAX)
#endif            
        {
          target_label->timeout_mtz_1_n_vpered[num_gr] = temp_value;
        }
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_TO_MTZ1_N_NAZAD:
      {
        temp_value = data*10;
        
#if (TIMEOUT_MTZ1_N_NAZAD_MIN != 0)          
        if ((temp_value >= TIMEOUT_MTZ1_N_NAZAD_MIN) && (temp_value <= TIMEOUT_MTZ1_N_NAZAD_MAX))
#else
        if (temp_value <= TIMEOUT_MTZ1_N_NAZAD_MAX)
#endif            
        {
          target_label->timeout_mtz_1_n_nazad[num_gr] = temp_value;
        }
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_TO_MTZ1_PO_NAPRUZI:
      {
        temp_value = data*10;
        
#if (TIMEOUT_MTZ1_PO_NAPRUZI_MIN != 0)          
        if ((temp_value >= TIMEOUT_MTZ1_PO_NAPRUZI_MIN) && (temp_value <= TIMEOUT_MTZ1_PO_NAPRUZI_MAX))
#else
        if (temp_value <= TIMEOUT_MTZ1_PO_NAPRUZI_MAX)
#endif            
        {
          target_label->timeout_mtz_1_po_napruzi[num_gr] = temp_value;
        }
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_STP_MTZ2:
      {
        temp_value = data*10;
    
        if ((temp_value >= SETPOINT_MTZ2_MIN) && (temp_value <= SETPOINT_MTZ2_MAX))
          target_label->setpoint_mtz_2[num_gr] = temp_value;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_STP_MTZ2_N_VPERED:
      {
        temp_value = data*10;
    
        if ((temp_value >= SETPOINT_MTZ2_N_VPERED_MIN) && (temp_value <= SETPOINT_MTZ2_N_VPERED_MAX))
          target_label->setpoint_mtz_2_n_vpered[num_gr] = temp_value;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_STP_MTZ2_N_NAZAD:
      {
        temp_value = data*10;
    
        if ((temp_value >= SETPOINT_MTZ2_N_NAZAD_MIN) && (temp_value <= SETPOINT_MTZ2_N_NAZAD_MAX))
          target_label->setpoint_mtz_2_n_nazad[num_gr] = temp_value;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_STP_MTZ2_PO_NAPRUZI:
      {
        temp_value = data*10;
    
        if ((temp_value >= SETPOINT_MTZ2_PO_NAPRUZI_MIN) && (temp_value <= SETPOINT_MTZ2_PO_NAPRUZI_MAX))
          target_label->setpoint_mtz_2_po_napruzi[num_gr] = temp_value;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_STP_MTZ2_U:
      {
        temp_value = data*10;
    
        if ((temp_value >= SETPOINT_MTZ2_U_MIN) && (temp_value <= SETPOINT_MTZ2_U_MAX))
          target_label->setpoint_mtz_2_U[num_gr] = temp_value;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_STP_MTZ2_ANGLE:
      {
        temp_value = data;
        
#if (SETPOINT_MTZ2_ANGLE_MIN != 0)          
        if ((temp_value >= SETPOINT_MTZ2_ANGLE_MIN) && (temp_value <= SETPOINT_MTZ2_ANGLE_MAX))
#else
        if (temp_value <= SETPOINT_MTZ2_ANGLE_MAX)
#endif            
        {
          target_label->setpoint_mtz_2_angle[num_gr] = temp_value;

          float temp_value_f = (float)temp_value;
          target_label->setpoint_mtz_2_angle_cos[num_gr] = (int) (AMPLITUDA_FI*/*cos*/arm_cos_f32(/*(double)*/(PI*temp_value_f/180.0f)));
          target_label->setpoint_mtz_2_angle_sin[num_gr] = (int) (AMPLITUDA_FI*/*sin*/arm_sin_f32(/*(double)*/(PI*temp_value_f/180.0f)));
        }
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_TO_MTZ2:
      {
        temp_value = data*10;
        
#if (TIMEOUT_MTZ2_MIN != 0)          
        if ((temp_value >= TIMEOUT_MTZ2_MIN) && (temp_value <= TIMEOUT_MTZ2_MAX))
#else
        if (temp_value <= TIMEOUT_MTZ2_MAX)
#endif            
        {
          target_label->timeout_mtz_2[num_gr] = temp_value;
        }
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_TO_MTZ2_N_VPERED:
      {
        temp_value = data*10;
        
#if (TIMEOUT_MTZ2_N_VPERED_MIN != 0)          
        if ((temp_value >= TIMEOUT_MTZ2_N_VPERED_MIN) && (temp_value <= TIMEOUT_MTZ2_N_VPERED_MAX))
#else
        if (temp_value <= TIMEOUT_MTZ2_N_VPERED_MAX)
#endif            
        {
          target_label->timeout_mtz_2_n_vpered[num_gr] = temp_value;
        }
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_TO_MTZ2_N_NAZAD:
      {
        temp_value = data*10;
        
#if (TIMEOUT_MTZ2_N_NAZAD_MIN != 0)          
        if ((temp_value >= TIMEOUT_MTZ2_N_NAZAD_MIN) && (temp_value <= TIMEOUT_MTZ2_N_NAZAD_MAX))
#else
        if (temp_value <= TIMEOUT_MTZ2_N_NAZAD_MAX)
#endif            
        {
          target_label->timeout_mtz_2_n_nazad[num_gr] = temp_value;
        }
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_TO_MTZ2_PO_NAPRUZI:
      {
        temp_value = data*10;
        
#if (TIMEOUT_MTZ2_PO_NAPRUZI_MIN != 0)          
        if ((temp_value >= TIMEOUT_MTZ2_PO_NAPRUZI_MIN) && (temp_value <= TIMEOUT_MTZ2_PO_NAPRUZI_MAX))
#else
        if (temp_value <= TIMEOUT_MTZ2_PO_NAPRUZI_MAX)
#endif            
        {
          target_label->timeout_mtz_2_po_napruzi[num_gr] = temp_value;
        }
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_TO_MTZ2_VVID_PR:
      {
        temp_value = data*10;
        
#if (TIMEOUT_MTZ2_VVID_PR_MIN != 0)          
        if ((temp_value >= TIMEOUT_MTZ2_VVID_PR_MIN) && (temp_value <= TIMEOUT_MTZ2_VVID_PR_MAX))
#else
        if (temp_value <= TIMEOUT_MTZ2_VVID_PR_MAX)
#endif            
        {
          target_label->timeout_mtz_2_vvid_pr[num_gr] = temp_value;
        }
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_TO_MTZ2_PR:
      {
        temp_value = data*10;
        
#if (TIMEOUT_MTZ2_PR_MIN != 0)          
        if ((temp_value >= TIMEOUT_MTZ2_PR_MIN) && (temp_value <= TIMEOUT_MTZ2_PR_MAX))
#else
        if (temp_value <= TIMEOUT_MTZ2_PR_MAX)
#endif            
        {
          target_label->timeout_mtz_2_pr[num_gr] = temp_value;
        }
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_TO_MTZ2_N_VPERED_PR:
      {
        temp_value = data*10;
        
#if (TIMEOUT_MTZ2_N_VPERED_PR_MIN != 0)          
        if ((temp_value >= TIMEOUT_MTZ2_N_VPERED_PR_MIN) && (temp_value <= TIMEOUT_MTZ2_N_VPERED_PR_MAX))
#else
        if (temp_value <= TIMEOUT_MTZ2_N_VPERED_PR_MAX)
#endif            
        {
          target_label->timeout_mtz_2_n_vpered_pr[num_gr] = temp_value;
        }
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_TO_MTZ2_N_NAZAD_PR:
      {
        temp_value = data*10;
        
#if (TIMEOUT_MTZ2_N_NAZAD_PR_MIN != 0)          
        if ((temp_value >= TIMEOUT_MTZ2_N_NAZAD_PR_MIN) && (temp_value <= TIMEOUT_MTZ2_N_NAZAD_PR_MAX))
#else
        if (temp_value <= TIMEOUT_MTZ2_N_NAZAD_PR_MAX)
#endif            
        {
          target_label->timeout_mtz_2_n_nazad_pr[num_gr] = temp_value;
        }
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_TO_MTZ2_PO_NAPRUZI_PR:
      {
        temp_value = data*10;
        
#if (TIMEOUT_MTZ2_PO_NAPRUZI_PR_MIN != 0)          
        if ((temp_value >= TIMEOUT_MTZ2_PO_NAPRUZI_PR_MIN) && (temp_value <= TIMEOUT_MTZ2_PO_NAPRUZI_PR_MAX))
#else
        if (temp_value <= TIMEOUT_MTZ2_PO_NAPRUZI_PR_MAX)
#endif            
        {
          target_label->timeout_mtz_2_po_napruzi_pr[num_gr] = temp_value;
        }
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_STP_MTZ3:
      {
        temp_value = data*10;
    
        if ((temp_value >= SETPOINT_MTZ3_MIN) && (temp_value <= SETPOINT_MTZ3_MAX))
          target_label->setpoint_mtz_3[num_gr] = temp_value;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_STP_MTZ3_N_VPERED:
      {
        temp_value = data*10;
    
        if ((temp_value >= SETPOINT_MTZ3_N_VPERED_MIN) && (temp_value <= SETPOINT_MTZ3_N_VPERED_MAX))
          target_label->setpoint_mtz_3_n_vpered[num_gr] = temp_value;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_STP_MTZ3_N_NAZAD:
      {
        temp_value = data*10;
    
        if ((temp_value >= SETPOINT_MTZ3_N_NAZAD_MIN) && (temp_value <= SETPOINT_MTZ3_N_NAZAD_MAX))
          target_label->setpoint_mtz_3_n_nazad[num_gr] = temp_value;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_STP_MTZ3_PO_NAPRUZI:
      {
        temp_value = data*10;
    
        if ((temp_value >= SETPOINT_MTZ3_PO_NAPRUZI_MIN) && (temp_value <= SETPOINT_MTZ3_PO_NAPRUZI_MAX))
          target_label->setpoint_mtz_3_po_napruzi[num_gr] = temp_value;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_STP_MTZ3_U:
      {
        temp_value = data*10;
    
        if ((temp_value >= SETPOINT_MTZ3_U_MIN) && (temp_value <= SETPOINT_MTZ3_U_MAX))
          target_label->setpoint_mtz_3_U[num_gr] = temp_value;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_STP_MTZ3_ANGLE:
      {
        temp_value = data;
        
#if (SETPOINT_MTZ3_ANGLE_MIN != 0)          
        if ((temp_value >= SETPOINT_MTZ3_ANGLE_MIN) && (temp_value <= SETPOINT_MTZ3_ANGLE_MAX))
#else
        if (temp_value <= SETPOINT_MTZ3_ANGLE_MAX)
#endif            
        {
          target_label->setpoint_mtz_3_angle[num_gr] = temp_value;

          float temp_value_f = (float)temp_value;
          target_label->setpoint_mtz_3_angle_cos[num_gr] = (int) (AMPLITUDA_FI*/*cos*/arm_cos_f32(/*(double)*/(PI*temp_value_f/180.0f)));
          target_label->setpoint_mtz_3_angle_sin[num_gr] = (int) (AMPLITUDA_FI*/*sin*/arm_sin_f32(/*(double)*/(PI*temp_value_f/180.0f)));
        }
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_TO_MTZ3:
      {
        temp_value = data*10;
        
#if (TIMEOUT_MTZ3_MIN != 0)          
        if ((temp_value >= TIMEOUT_MTZ3_MIN) && (temp_value <= TIMEOUT_MTZ3_MAX))
#else
        if (temp_value <= TIMEOUT_MTZ3_MAX)
#endif            
        {
          target_label->timeout_mtz_3[num_gr] = temp_value;
        }
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_TO_MTZ3_N_VPERED:
      {
        temp_value = data*10;
        
#if (TIMEOUT_MTZ3_N_VPERED_MIN != 0)          
        if ((temp_value >= TIMEOUT_MTZ3_N_VPERED_MIN) && (temp_value <= TIMEOUT_MTZ3_N_VPERED_MAX))
#else
        if (temp_value <= TIMEOUT_MTZ3_N_VPERED_MAX)
#endif            
        {
          target_label->timeout_mtz_3_n_vpered[num_gr] = temp_value;
        }
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_TO_MTZ3_N_NAZAD:
      {
        temp_value = data*10;
        
#if (TIMEOUT_MTZ3_N_NAZAD_MIN != 0)          
        if ((temp_value >= TIMEOUT_MTZ3_N_NAZAD_MIN) && (temp_value <= TIMEOUT_MTZ3_N_NAZAD_MAX))
#else
        if (temp_value <= TIMEOUT_MTZ3_N_NAZAD_MAX)
#endif            
        {
          target_label->timeout_mtz_3_n_nazad[num_gr] = temp_value;
        }
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_TO_MTZ3_PO_NAPRUZI:
      {
        temp_value = data*10;
        
#if (TIMEOUT_MTZ3_PO_NAPRUZI_MIN != 0)          
        if ((temp_value >= TIMEOUT_MTZ3_PO_NAPRUZI_MIN) && (temp_value <= TIMEOUT_MTZ3_PO_NAPRUZI_MAX))
#else
        if (temp_value <= TIMEOUT_MTZ3_PO_NAPRUZI_MAX)
#endif            
        {
          target_label->timeout_mtz_3_po_napruzi[num_gr] = temp_value;
        }
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_STP_MTZ4:
      {
        temp_value = data*10;
    
        if ((temp_value >= SETPOINT_MTZ4_MIN) && (temp_value <= SETPOINT_MTZ4_MAX))
          target_label->setpoint_mtz_4[num_gr] = temp_value;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_STP_MTZ4_N_VPERED:
      {
        temp_value = data*10;
    
        if ((temp_value >= SETPOINT_MTZ4_N_VPERED_MIN) && (temp_value <= SETPOINT_MTZ4_N_VPERED_MAX))
          target_label->setpoint_mtz_4_n_vpered[num_gr] = temp_value;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_STP_MTZ4_N_NAZAD:
      {
        temp_value = data*10;
    
        if ((temp_value >= SETPOINT_MTZ4_N_NAZAD_MIN) && (temp_value <= SETPOINT_MTZ4_N_NAZAD_MAX))
          target_label->setpoint_mtz_4_n_nazad[num_gr] = temp_value;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_STP_MTZ4_PO_NAPRUZI:
      {
        temp_value = data*10;
    
        if ((temp_value >= SETPOINT_MTZ4_PO_NAPRUZI_MIN) && (temp_value <= SETPOINT_MTZ4_PO_NAPRUZI_MAX))
          target_label->setpoint_mtz_4_po_napruzi[num_gr] = temp_value;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_STP_MTZ4_U:
      {
        temp_value = data*10;
    
        if ((temp_value >= SETPOINT_MTZ4_U_MIN) && (temp_value <= SETPOINT_MTZ4_U_MAX))
          target_label->setpoint_mtz_4_U[num_gr] = temp_value;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_STP_MTZ4_ANGLE:
      {
        temp_value = data;
        
#if (SETPOINT_MTZ4_ANGLE_MIN != 0)          
        if ((temp_value >= SETPOINT_MTZ4_ANGLE_MIN) && (temp_value <= SETPOINT_MTZ4_ANGLE_MAX))
#else
        if (temp_value <= SETPOINT_MTZ4_ANGLE_MAX)
#endif            
        {
          target_label->setpoint_mtz_4_angle[num_gr] = temp_value;

          float temp_value_f = (float)temp_value;
          target_label->setpoint_mtz_4_angle_cos[num_gr] = (int) (AMPLITUDA_FI*/*cos*/arm_cos_f32(/*(double)*/(PI*temp_value_f/180.0f)));
          target_label->setpoint_mtz_4_angle_sin[num_gr] = (int) (AMPLITUDA_FI*/*sin*/arm_sin_f32(/*(double)*/(PI*temp_value_f/180.0f)));
        }
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_TO_MTZ4:
      {
        temp_value = data*10;
        
#if (TIMEOUT_MTZ4_MIN != 0)          
        if ((temp_value >= TIMEOUT_MTZ4_MIN) && (temp_value <= TIMEOUT_MTZ4_MAX))
#else
        if (temp_value <= TIMEOUT_MTZ4_MAX)
#endif            
        {
          target_label->timeout_mtz_4[num_gr] = temp_value;
        }
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_TO_MTZ4_N_VPERED:
      {
        temp_value = data*10;
        
#if (TIMEOUT_MTZ4_N_VPERED_MIN != 0)          
        if ((temp_value >= TIMEOUT_MTZ4_N_VPERED_MIN) && (temp_value <= TIMEOUT_MTZ4_N_VPERED_MAX))
#else
        if (temp_value <= TIMEOUT_MTZ4_N_VPERED_MAX)
#endif            
        {
          target_label->timeout_mtz_4_n_vpered[num_gr] = temp_value;
        }
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_TO_MTZ4_N_NAZAD:
      {
        temp_value = data*10;
        
#if (TIMEOUT_MTZ4_N_NAZAD_MIN != 0)          
        if ((temp_value >= TIMEOUT_MTZ4_N_NAZAD_MIN) && (temp_value <= TIMEOUT_MTZ4_N_NAZAD_MAX))
#else
        if (temp_value <= TIMEOUT_MTZ4_N_NAZAD_MAX)
#endif            
        {
          target_label->timeout_mtz_4_n_nazad[num_gr] = temp_value;
        }
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_TO_MTZ4_PO_NAPRUZI:
      {
        temp_value = data*10;
        
#if (TIMEOUT_MTZ4_PO_NAPRUZI_MIN != 0)          
        if ((temp_value >= TIMEOUT_MTZ4_PO_NAPRUZI_MIN) && (temp_value <= TIMEOUT_MTZ4_PO_NAPRUZI_MAX))
#else
        if (temp_value <= TIMEOUT_MTZ4_PO_NAPRUZI_MAX)
#endif            
        {
          target_label->timeout_mtz_4_po_napruzi[num_gr] = temp_value;
        }
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_STP_NZZ1_3I0:
      {
        temp_value = data;
    
        if ((temp_value >= SETPOINT_ZZ_3I0_MIN) && (temp_value <= SETPOINT_ZZ_3I0_MAX))
          target_label->setpoint_zz_3I0[num_gr] = temp_value;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_TO_NZZ1_3I0:
      {
        temp_value = data*10;
        
#if (TIMEOUT_ZZ_3I0_MIN != 0)          
        if ((temp_value >= TIMEOUT_ZZ_3I0_MIN) && (temp_value <= TIMEOUT_ZZ_3I0_MAX))
#else
        if (temp_value <= TIMEOUT_ZZ_3I0_MAX)
#endif            
        {
          target_label->timeout_zz_3I0[num_gr] = temp_value;
        }
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_STP_NZZ1_3U0:
      {
        temp_value = data*10;
    
        if ((temp_value >= SETPOINT_ZZ_3U0_MIN) && (temp_value <= SETPOINT_ZZ_3U0_MAX))
          target_label->setpoint_zz_3U0[num_gr] = temp_value;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_TO_NZZ1_3U0:
      {
        temp_value = data*10;
        
#if (TIMEOUT_ZZ_3U0_MIN != 0)          
        if ((temp_value >= TIMEOUT_ZZ_3U0_MIN) && (temp_value <= TIMEOUT_ZZ_3U0_MAX))
#else
        if (temp_value <= TIMEOUT_ZZ_3U0_MAX)
#endif            
        {
          target_label->timeout_zz_3U0[num_gr] = temp_value;
        }
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_TO_NZZ1:
      {
        temp_value = data*10;
        
#if (TIMEOUT_ZZ_3U0_MIN != 0)          
        if ((temp_value >= TIMEOUT_NZZ_MIN) && (temp_value <= TIMEOUT_NZZ_MAX))
#else
        if (temp_value <= TIMEOUT_NZZ_MAX)
#endif            
        {
          target_label->timeout_nzz[num_gr] = temp_value;
        }
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_STP_ZOP1:
      {
        temp_value = data;
    
        if ((temp_value >= SETPOINT_ZOP_MIN) && (temp_value <= SETPOINT_ZOP_MAX))
          target_label->setpoint_zop[num_gr] = temp_value;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_TO_ZOP1:
      {
        temp_value = data*10;
        
#if (TIMEOUT_ZOP_MIN != 0)          
        if ((temp_value >= TIMEOUT_ZOP_MIN) && (temp_value <= TIMEOUT_ZOP_MAX))
#else
        if (temp_value <= TIMEOUT_ZOP_MAX)
#endif            
        {
          target_label->timeout_zop[num_gr] = temp_value;
        }
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_STP_UMIN1:
      {
        temp_value = data*100;
    
        if ((temp_value >= SETPOINT_UMIN1_MIN) && (temp_value <= SETPOINT_UMIN1_MAX))
          target_label->setpoint_Umin1[num_gr] = temp_value;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_TO_UMIN1:
      {
        temp_value = data*10;
        
#if (TIMEOUT_UMIN1_MIN != 0)          
        if ((temp_value >= TIMEOUT_UMIN1_MIN) && (temp_value <= TIMEOUT_UMIN1_MAX))
#else
        if (temp_value <= TIMEOUT_UMIN1_MAX)
#endif            
        {
          target_label->timeout_Umin1[num_gr] = temp_value;
        }
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_STP_UMIN2:
      {
        temp_value = data*100;
    
        if ((temp_value >= SETPOINT_UMIN2_MIN) && (temp_value <= SETPOINT_UMIN2_MAX))
          target_label->setpoint_Umin2[num_gr] = temp_value;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_TO_UMIN2:
      {
        temp_value = data*10;
        
#if (TIMEOUT_UMIN1_MIN != 0)          
        if ((temp_value >= TIMEOUT_UMIN2_MIN) && (temp_value <= TIMEOUT_UMIN2_MAX))
#else
        if (temp_value <= TIMEOUT_UMIN2_MAX)
#endif            
        {
          target_label->timeout_Umin2[num_gr] = temp_value;
        }
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_STP_BLK_UMIN1_BY_I:
      {
        temp_value = data*10;
    
        if ((temp_value >= SETPOINT_UMIN1_IBLK_MIN) && (temp_value <= SETPOINT_UMIN1_IBLK_MAX))
          target_label->setpoint_Umin1_Iblk[num_gr] = temp_value;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_STP_BLK_UMIN2_BY_I:
      {
        temp_value = data*10;
    
        if ((temp_value >= SETPOINT_UMIN2_IBLK_MIN) && (temp_value <= SETPOINT_UMIN2_IBLK_MAX))
          target_label->setpoint_Umin2_Iblk[num_gr] = temp_value;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_STP_UMAX1:
      {
        temp_value = data*100;
    
        if ((temp_value >= SETPOINT_UMAX1_MIN) && (temp_value <= SETPOINT_UMAX1_MAX))
          target_label->setpoint_Umax1[num_gr] = temp_value;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_TO_UMAX1:
      {
        temp_value = data*10;
        
#if (TIMEOUT_UMAX1_MIN != 0)          
        if ((temp_value >= TIMEOUT_UMAX1_MIN) && (temp_value <= TIMEOUT_UMAX1_MAX))
#else
        if (temp_value <= TIMEOUT_UMAX1_MAX)
#endif            
        {
          target_label->timeout_Umax1[num_gr] = temp_value;
        }
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_STP_UMAX2:
      {
        temp_value = data*100;
    
        if ((temp_value >= SETPOINT_UMAX2_MIN) && (temp_value <= SETPOINT_UMAX2_MAX))
          target_label->setpoint_Umax2[num_gr] = temp_value;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_TO_UMAX2:
      {
        temp_value = data*10;
        
#if (TIMEOUT_UMAX2_MIN != 0)          
        if ((temp_value >= TIMEOUT_UMAX2_MIN) && (temp_value <= TIMEOUT_UMAX2_MAX))
#else
        if (temp_value <= TIMEOUT_UMAX2_MAX)
#endif            
        {
          target_label->timeout_Umax2[num_gr] = temp_value;
        }
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_STP_APV_ZMN1:
      {
        temp_value = data*100;
    
        if ((temp_value >= SETPOINT_APV_ZMN1_MIN) && (temp_value <= SETPOINT_APV_ZMN1_MAX))
          target_label->setpoint_apv_zmn1[num_gr] = temp_value;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_STP_APV_ZMN2:
      {
        temp_value = data*100;
    
        if ((temp_value >= SETPOINT_APV_ZMN2_MIN) && (temp_value <= SETPOINT_APV_ZMN2_MAX))
          target_label->setpoint_apv_zmn2[num_gr] = temp_value;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_TO_APV_ZMN1:
      {
        temp_value = data*10;
        
#if (TIMEOUT_APV_ZMN1_MIN != 0)          
        if ((temp_value >= TIMEOUT_APV_ZMN1_MIN) && (temp_value <= TIMEOUT_APV_ZMN1_MAX))
#else
        if (temp_value <= TIMEOUT_APV_ZMN1_MAX)
#endif            
        {
          target_label->timeout_apv_zmn_1[num_gr] = temp_value;
        }
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_TO_APV_ZMN2:
      {
        temp_value = data*10;
        
#if (TIMEOUT_APV_ZMN2_MIN != 0)          
        if ((temp_value >= TIMEOUT_APV_ZMN2_MIN) && (temp_value <= TIMEOUT_APV_ZMN2_MAX))
#else
        if (temp_value <= TIMEOUT_APV_ZMN2_MAX)
#endif            
        {
          target_label->timeout_apv_zmn_2[num_gr] = temp_value;
        }
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_STP_U_OL:
      {
        temp_value = data*100;
    
        if ((temp_value >= SETPOINT_U_OL_MIN) && (temp_value <= SETPOINT_U_OL_MAX))
          target_label->setpoint_U_ol[num_gr] = temp_value;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_STP_U_RL:
      {
        temp_value = data*100;
    
        if ((temp_value >= SETPOINT_U_RL_MIN) && (temp_value <= SETPOINT_U_RL_MAX))
          target_label->setpoint_U_rl[num_gr] = temp_value;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_TO_U_OL:
      {
        temp_value = data*10;
        
#if (TIMEOUT_U_OL_MIN != 0)          
        if ((temp_value >= TIMEOUTU_OL_MIN) && (temp_value <= TIMEOUT_U_OL_MAX))
#else
        if (temp_value <= TIMEOUT_U_OL_MAX)
#endif            
        {
          target_label->timeout_U_ol[num_gr] = temp_value;
        }
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_TO_U_RL:
      {
        temp_value = data*10;
        
#if (TIMEOUT_U_RL_MIN != 0)          
        if ((temp_value >= TIMEOUTU_RL_MIN) && (temp_value <= TIMEOUT_U_RL_MAX))
#else
        if (temp_value <= TIMEOUT_U_RL_MAX)
#endif            
        {
          target_label->timeout_U_rl[num_gr] = temp_value;
        }
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_STP_UROV:
      {
        temp_value = data*10;
    
        if ((temp_value >= SETPOINT_UROV_MIN) && (temp_value <= SETPOINT_UROV_MAX))
          target_label->setpoint_urov[num_gr] = temp_value;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_TO_UROV1:
      {
        temp_value = data*10;
        
#if (TIMEOUT_UROV1_MIN != 0)          
        if ((temp_value >= TIMEOUT_UROV1_MIN) && (temp_value <= TIMEOUT_UROV1_MAX))
#else
        if (temp_value <= TIMEOUT_UROV1_MAX)
#endif            
        {
          target_label->timeout_urov_1[num_gr] = temp_value;
        }
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_TO_UROV2:
      {
        temp_value = data*10;
        
#if (TIMEOUT_UROV2_MIN != 0)          
        if ((temp_value >= TIMEOUT_UROV2_MIN) && (temp_value <= TIMEOUT_UROV2_MAX))
#else
        if (temp_value <= TIMEOUT_UROV2_MAX)
#endif            
        {
          target_label->timeout_urov_2[num_gr] = temp_value;
        }
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_STP_AVR_MIN1:
      {
        temp_value = data*100;
    
        if ((temp_value >= SETPOINT_AVR1_MIN) && (temp_value <= SETPOINT_AVR1_MAX))
          target_label->setpoint_avr_min1[num_gr] = temp_value;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_STP_AVR_MAX1:
      {
        temp_value = data*100;
    
        if ((temp_value >= SETPOINT_AVR1_MIN) && (temp_value <= SETPOINT_AVR1_MAX))
          target_label->setpoint_avr_max1[num_gr] = temp_value;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_STP_AVR_MIN2:
      {
        temp_value = data*100;
    
        if ((temp_value >= SETPOINT_AVR2_MIN) && (temp_value <= SETPOINT_AVR2_MAX))
          target_label->setpoint_avr_min2[num_gr] = temp_value;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_STP_AVR_MAX2:
      {
        temp_value = data*100;
    
        if ((temp_value >= SETPOINT_AVR2_MIN) && (temp_value <= SETPOINT_AVR2_MAX))
          target_label->setpoint_avr_max2[num_gr] = temp_value;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_STP_KRATN_AVR:
      {
        temp_value = data;
    
        if ((temp_value >= SETPOINT_AVR_KRATN_MIN) && (temp_value <= SETPOINT_AVR_KRATN_MAX))
          target_label->setpoint_kratn_avr[num_gr] = temp_value;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_TO_AVR_RL:
      {
        temp_value = data*10;
        
#if (TIMEOUT_AVR_RL_MIN != 0)          
        if ((temp_value >= TIMEOUT_AVR_RL_MIN) && (temp_value <= TIMEOUT_AVR_RL_MAX))
#else
        if (temp_value <= TIMEOUT_AVR_RL_MAX)
#endif            
        {
          target_label->timeout_avr_rl[num_gr] = temp_value;
        }
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_TO_AVR_OL:
      {
        temp_value = data*10;
        
#if (TIMEOUT_AVR_OL_MIN != 0)          
        if ((temp_value >= TIMEOUT_AVR_OL_MIN) && (temp_value <= TIMEOUT_AVR_OL_MAX))
#else
        if (temp_value <= TIMEOUT_AVR_OL_MAX)
#endif            
        {
          target_label->timeout_avr_ol[num_gr] = temp_value;
        }
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_TO_AVR_ZAVERSHENNJA:
      {
        temp_value = data*10;
        
#if (TIMEOUT_AVR_ZAVERSHENNJA_MIN != 0)          
        if ((temp_value >= TIMEOUT_AVR_ZAVERSHENNJA_MIN) && (temp_value <= TIMEOUT_AVR_ZAVERSHENNJA_MAX))
#else
        if (temp_value <= TIMEOUT_AVR_ZAVERSHENNJA_MAX)
#endif            
        {
          target_label->timeout_avr_zavershennja[num_gr] = temp_value;
        }
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_TO_AVR_RESET_BLK:
      {
        temp_value = data*10;
        
#if (TIMEOUT_AVR_RESET_BLK_MIN != 0)          
        if ((temp_value >= TIMEOUT_AVR_RESET_BLK_MIN) && (temp_value <= TIMEOUT_AVR_RESET_BLK_MAX))
#else
        if (temp_value <= TIMEOUT_AVR_RESET_BLK_MAX)
#endif            
        {
          target_label->timeout_avr_reset_blk[num_gr] = temp_value;
        }
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_TO_APV_BLOCK_VID_VV:
      {
        temp_value = data*10;

#if (TIMEOUT_APV_BLOCK_VID_VV_MIN != 0)          
        if ((temp_value >= TIMEOUT_APV_BLOCK_VID_VV_MIN) && (temp_value <= TIMEOUT_APV_BLOCK_VID_VV_MAX))
#else
        if (temp_value <= TIMEOUT_APV_BLOCK_VID_VV_MAX)
#endif            
        {
          target_label->timeout_apv_block_vid_VV[num_gr] = temp_value;
        }
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_TO_APV_CYCLE_1:
      {
        temp_value = data*10;

#if (TIMEOUT_APV1_MIN != 0)          
        if ((temp_value >= TIMEOUT_APV1_MIN) && (temp_value <= TIMEOUT_APV1_MAX))
#else
        if (temp_value <= TIMEOUT_APV1_MAX)
#endif            
        {
          target_label->timeout_apv_1[num_gr] = temp_value;
        }
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_TO_APV_CYCLE_2:
      {
        temp_value = data*10;

#if (TIMEOUT_APV2_MIN != 0)          
        if ((temp_value >= TIMEOUT_APV2_MIN) && (temp_value <= TIMEOUT_APV2_MAX))
#else
        if (temp_value <= TIMEOUT_APV2_MAX)
#endif            
        {
          target_label->timeout_apv_2[num_gr] = temp_value;
        }
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_TO_APV_CYCLE_3:
      {
        temp_value = data*10;

#if (TIMEOUT_APV3_MIN != 0)          
        if ((temp_value >= TIMEOUT_APV3_MIN) && (temp_value <= TIMEOUT_APV3_MAX))
#else
        if (temp_value <= TIMEOUT_APV3_MAX)
#endif            
        {
          target_label->timeout_apv_3[num_gr] = temp_value;
        }
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_TO_APV_CYCLE_4:
      {
        temp_value = data*10;

#if (TIMEOUT_APV4_MIN != 0)          
        if ((temp_value >= TIMEOUT_APV4_MIN) && (temp_value <= TIMEOUT_APV4_MAX))
#else
        if (temp_value <= TIMEOUT_APV4_MAX)
#endif            
        {
          target_label->timeout_apv_4[num_gr] = temp_value;
        }
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_TO_APV_BLOCK_VID_APV1:
      {
        temp_value = data*10;

#if (TIMEOUT_APV_BLOCK_VID_APV1_MIN != 0)          
        if ((temp_value >= TIMEOUT_APV_BLOCK_VID_APV1_MIN) && (temp_value <= TIMEOUT_APV_BLOCK_VID_APV1_MAX))
#else
        if (temp_value <= TIMEOUT_APV_BLOCK_VID_APV1_MAX)
#endif            
        {
          target_label->timeout_apv_block_vid_apv1[num_gr] = temp_value;
        }
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_TO_APV_BLOCK_VID_APV2:
      {
        temp_value = data*10;

#if (TIMEOUT_APV_BLOCK_VID_APV2_MIN != 0)          
        if ((temp_value >= TIMEOUT_APV_BLOCK_VID_APV2_MIN) && (temp_value <= TIMEOUT_APV_BLOCK_VID_APV2_MAX))
#else
        if (temp_value <= TIMEOUT_APV_BLOCK_VID_APV2_MAX)
#endif            
        {
          target_label->timeout_apv_block_vid_apv2[num_gr] = temp_value;
        }
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_TO_APV_BLOCK_VID_APV3:
      {
        temp_value = data*10;

#if (TIMEOUT_APV_BLOCK_VID_APV3_MIN != 0)          
        if ((temp_value >= TIMEOUT_APV_BLOCK_VID_APV3_MIN) && (temp_value <= TIMEOUT_APV_BLOCK_VID_APV3_MAX))
#else
        if (temp_value <= TIMEOUT_APV_BLOCK_VID_APV3_MAX)
#endif            
        {
          target_label->timeout_apv_block_vid_apv3[num_gr] = temp_value;
        }
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_TO_APV_BLOCK_VID_APV4:
      {
        temp_value = data*10;

#if (TIMEOUT_APV_BLOCK_VID_APV4_MIN != 0)          
        if ((temp_value >= TIMEOUT_APV_BLOCK_VID_APV4_MIN) && (temp_value <= TIMEOUT_APV_BLOCK_VID_APV4_MAX))
#else
        if (temp_value <= TIMEOUT_APV_BLOCK_VID_APV4_MAX)
#endif            
        {
          target_label->timeout_apv_block_vid_apv4[num_gr] = temp_value;
        }
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_STP_KRATN_APV_ZMN:
      {
        temp_value = data;
    
        if ((temp_value >= SETPOINT_APV_ZMN_KRATN_MIN) && (temp_value <= SETPOINT_APV_ZMN_KRATN_MAX))
          target_label->setpoint_kratn_apv_zmn[num_gr] = temp_value;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_TO_APV_ZMN_ZAVERSHENNJA:
      {
        temp_value = data*10;
        
#if (TIMEOUT_APV_ZMN_ZAVERSHENNJA_MIN != 0)          
        if ((temp_value >= TIMEOUT_APV_ZMN_ZAVERSHENNJA_MIN) && (temp_value <= TIMEOUT_APV_ZMN_ZAVERSHENNJA_MAX))
#else
        if (temp_value <= TIMEOUT_APV_ZMN_ZAVERSHENNJA_MAX)
#endif            
        {
          target_label->timeout_apv_zmn_zavershennja[num_gr] = temp_value;
        }
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_STP_ACHR_F_RAB:
      {
        temp_value = data*10;
    
        if ((temp_value >= SETPOINT_ACHR_F_RAB_MIN) && (temp_value <= SETPOINT_ACHR_F_RAB_MAX))
          target_label->setpoint_achr_f_rab[num_gr] = temp_value;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_STP_CHAPV_F_RAB:
      {
        temp_value = data*10;
    
        if ((temp_value >= SETPOINT_CHAPV_F_RAB_MIN) && (temp_value <= SETPOINT_CHAPV_F_RAB_MAX))
          target_label->setpoint_chapv_f_rab[num_gr] = temp_value;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_STP_ACHR_CHAPV_UF1:
      {
        temp_value = data*100;
    
        if ((temp_value >= SETPOINT_ACHR_CHAPV_UF1_MIN) && (temp_value <= SETPOINT_ACHR_CHAPV_UF1_MAX))
          target_label->setpoint_achr_chapv_uf1[num_gr] = temp_value;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_STP_ACHR_CHAPV_UF2:
      {
        temp_value = data*100;
    
        if ((temp_value >= SETPOINT_ACHR_CHAPV_UF2_MIN) && (temp_value <= SETPOINT_ACHR_CHAPV_UF2_MAX))
          target_label->setpoint_achr_chapv_uf2[num_gr] = temp_value;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_TO_ACHR_1:
      {
        temp_value = data*10;

#if (TIMEOUT_ACHR1_MIN != 0)          
        if ((temp_value >= TIMEOUT_ACHR1_MIN) && (temp_value <= TIMEOUT_ACHR1_MAX))
#else
        if (temp_value <= TIMEOUT_ACHR1_MAX)
#endif            
        {
          target_label->timeout_achr_1[num_gr] = temp_value;
        }
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_TO_ACHR_2:
      {
        temp_value = data*10;

#if (TIMEOUT_ACHR2_MIN != 0)          
        if ((temp_value >= TIMEOUT_ACHR2_MIN) && (temp_value <= TIMEOUT_ACHR2_MAX))
#else
        if (temp_value <= TIMEOUT_ACHR2_MAX)
#endif            
        {
          target_label->timeout_achr_2[num_gr] = temp_value;
        }
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_TO_CHAPV_1:
      {
        temp_value = data*10;

#if (TIMEOUT_CHAPV1_MIN != 0)          
        if ((temp_value >= TIMEOUT_CHAPV1_MIN) && (temp_value <= TIMEOUT_CHAPV1_MAX))
#else
        if (temp_value <= TIMEOUT_CHAPV1_MAX)
#endif            
        {
          target_label->timeout_chapv_1[num_gr] = temp_value;
        }
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_TO_CHAPV_2:
      {
        temp_value = data*10;

#if (TIMEOUT_CHAPV2_MIN != 0)          
        if ((temp_value >= TIMEOUT_CHAPV2_MIN) && (temp_value <= TIMEOUT_CHAPV2_MAX))
#else
        if (temp_value <= TIMEOUT_CHAPV2_MAX)
#endif            
        {
          target_label->timeout_chapv_2[num_gr] = temp_value;
        }
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    default: break;
    }
  }
  else if ((address_data >= M_ADDRESS_FIRST_SETPOINTS_CONTINUE) && (address_data <= M_ADDRESS_LAST_SETPOINTS_CONTINUE))
  {
    //������� � �������� (�����������), ������������
    switch (address_data)
    {
    case MA_LINE_1:
    case MA_DOVGYNA_1_1:
    case MA_OPIR_1_1:
    case MA_DOVGYNA_1_2:
    case MA_OPIR_1_2:
    case MA_DOVGYNA_1_3:
    case MA_OPIR_1_3:
    case MA_DOVGYNA_1_4:
    case MA_OPIR_1_4:
    case MA_DOVGYNA_1_5:
    case MA_OPIR_1_5:
    case MA_DOVGYNA_1_6:
    case MA_OPIR_1_6:
    case MA_DOVGYNA_1_7:
    case MA_OPIR_1_7:
    case MA_DOVGYNA_1_8:
    case MA_OPIR_1_8:
    case MA_LINE_2:
    case MA_DOVGYNA_2_1:
    case MA_OPIR_2_1:
    case MA_DOVGYNA_2_2:
    case MA_OPIR_2_2:
    case MA_DOVGYNA_2_3:
    case MA_OPIR_2_3:
    case MA_DOVGYNA_2_4:
    case MA_OPIR_2_4:
    case MA_DOVGYNA_2_5:
    case MA_OPIR_2_5:
    case MA_DOVGYNA_2_6:
    case MA_OPIR_2_6:
    case MA_DOVGYNA_2_7:
    case MA_OPIR_2_7:
    case MA_DOVGYNA_2_8:
    case MA_OPIR_2_8:
      {
        temp_value = data;
        
        unsigned int base_address, line;
        if(address_data < MA_LINE_2)
        {
          base_address = MA_LINE_1;
          line = 0;
        }
        else
        {
          base_address = MA_LINE_2;
          line = 1;
        }

        unsigned int shift_address =  address_data - base_address;
        if (shift_address == 0) 
        {
          unsigned int min_value = (line == 0) ? NUMBER_LINES_FORWARD_MIN : NUMBER_LINES_BACKWARD_MIN;

          if ((temp_value >= min_value) && (temp_value <= NUMBER_LINES_MAX))
            target_label->lines[line] = temp_value;
          else
            error = ERROR_ILLEGAL_DATA_VALUE;
        }
        else
        {
          shift_address--;
          if ((shift_address & 0x1) == 0)
          {
            //������� ��
            if ((temp_value >= SETPOINT_DOVGYNA_VMP_MIN) && (temp_value <= SETPOINT_DOVGYNA_VMP_MAX))
              target_label->dovgyna[line][shift_address >> 1] = temp_value;
            else
              error = ERROR_ILLEGAL_DATA_VALUE;
          }
          else
          {
            //��� ��
            if ((temp_value >= SETPOINT_OPIR_VMP_MIN) && (temp_value <= SETPOINT_OPIR_VMP_MAX))
              target_label->opir[line][shift_address >> 1] = temp_value;
            else
              error = ERROR_ILLEGAL_DATA_VALUE;
          }
        }
        
        break;
      }
    case MA_TN1:
      {
        temp_value = data;
    
        if ((temp_value >= KOEF_TN_MIN) && (temp_value <= KOEF_TN_MAX))
          target_label->TVoltage = temp_value;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_TT:
      {
        temp_value = data;
    
        if ((temp_value >= KOEF_TT_MIN) && (temp_value <= KOEF_TT_MAX))
          target_label->TCurrent = temp_value;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_T0:
      {
        temp_value = data;
    
        if ((temp_value >= KOEF_TO_MIN) && (temp_value <= KOEF_TO_MAX))
          target_label->T0 = temp_value;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_TO_SWCH_ON:
      {
        temp_value = data*10;
        
#if (TIMEOUT_SWCH_ON_MIN != 0)          
        if ((temp_value >= TIMEOUT_SWCH_ON_MIN) && (temp_value <= TIMEOUT_SWCH_ON_MAX))
#else
        if (temp_value <= TIMEOUT_SWCH_ON_MAX)
#endif            
        {
          target_label->timeout_swch_on = temp_value;
        }
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_TO_SWCH_OFF:
      {
        temp_value = data*10;
        
#if (TIMEOUT_SWCH_OFF_MIN != 0)          
        if ((temp_value >= TIMEOUT_SWCH_OFF_MIN) && (temp_value <= TIMEOUT_SWCH_OFF_MAX))
#else
        if (temp_value <= TIMEOUT_SWCH_OFF_MAX)
#endif            
        {
          target_label->timeout_swch_off = temp_value;
        }
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_TO_SWCH_UDL_BLK_ON:
      {
        temp_value = data*10;
        
#if (TIMEOUT_SWCH_UDL_BLK_ON_MIN != 0)          
        if ((temp_value >= TIMEOUT_SWCH_UDL_BLK_ON_MIN) && (temp_value <= TIMEOUT_SWCH_UDL_BLK_ON_MAX))
#else
        if (temp_value <= TIMEOUT_SWCH_UDL_BLK_ON_MAX)
#endif            
        {
          target_label->timeout_swch_udl_blk_on = temp_value;
        }
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_TO_FAULT_CONTROL_CIRCUIT:
      {
        temp_value = data*10;
        
#if (TIMEOUT_PRYVODA_VV_MIN != 0)          
        if ((temp_value >= TIMEOUT_PRYVODA_VV_MIN) && (temp_value <= TIMEOUT_PRYVODA_VV_MAX))
#else
        if (temp_value <= TIMEOUT_PRYVODA_VV_MAX)
#endif            
        {
          target_label->timeout_pryvoda_VV = temp_value;
        }
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_STP_Inom:
      {
        temp_value = data;
    
        if ((temp_value >= SETPOINT_Inom_MIN) && (temp_value <= SETPOINT_Inom_MAX))
          target_label->setpoint_Inom = temp_value;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_STP_RKS_Inom:
      {
        temp_value = data*10;
    
        if ((temp_value >= SETPOINT_RKS_Inom_MIN) && (temp_value <= SETPOINT_RKS_Inom_MAX))
          target_label->setpoint_r_kom_st_Inom = temp_value;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_STP_Inom_vymk:
      {
        temp_value = data;
    
        if ((temp_value >= SETPOINT_Inom_vymk_MIN) && (temp_value <= SETPOINT_Inom_vymk_MAX))
          target_label->setpoint_Inom_vymk = temp_value;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_STP_RKS_Inom_vymk:
      {
        temp_value = data;
    
        if ((temp_value >= SETPOINT_RKS_Inom_vymk_MIN) && (temp_value <= SETPOINT_RKS_Inom_vymk_MAX))
          target_label->setpoint_r_kom_st_Inom_vymk = temp_value;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_STP_POCHATKOVYJ_RESURS_LSW:
      {
        temp_value = (target_label->setpoint_pochatkovyj_resurs & 0xffff0000) | (data & 0x0000ffff);
    
        unsigned int chastka = target_label->setpoint_r_kom_st_Inom/target_label->setpoint_r_kom_st_Inom_vymk;
        if (
            (to_be_continue == true) ||
            ((temp_value >= (2*chastka)) && (temp_value <= target_label->setpoint_r_kom_st_Inom))
           )   
          target_label->setpoint_pochatkovyj_resurs = temp_value;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_STP_POCHATKOVYJ_RESURS_MSW:
      {
        temp_value = (data << 16) | (target_label->setpoint_pochatkovyj_resurs & 0x0000ffff);
    
        unsigned int chastka = target_label->setpoint_r_kom_st_Inom/target_label->setpoint_r_kom_st_Inom_vymk;
        if ((temp_value >= (2*chastka)) && (temp_value <= target_label->setpoint_r_kom_st_Inom))
          target_label->setpoint_pochatkovyj_resurs = temp_value;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_STP_KRYTYCHNYJ_RESURS:
      {
        temp_value = data;
    
        unsigned int chastka = target_label->setpoint_r_kom_st_Inom/target_label->setpoint_r_kom_st_Inom_vymk;
        if ((temp_value >= chastka) && (temp_value <= (2*chastka)))
          target_label->setpoint_krytychnyj_resurs = temp_value;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_POCHATKOVA_K_VYMK_LSW:
      {
        temp_value = (target_label->setpoint_pochatkova_k_vymk & 0xffff0000) | (data & 0x0000ffff);

        if (
            (to_be_continue == true) ||
            (temp_value <= target_label->setpoint_r_kom_st_Inom)
           )   
          target_label->setpoint_pochatkova_k_vymk = temp_value;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;
        
        break;
      }
    case MA_POCHATKOVA_K_VYMK_MSW:
      {
        temp_value = (data << 16) | (target_label->setpoint_pochatkova_k_vymk & 0x0000ffff);

        if (temp_value <= target_label->setpoint_r_kom_st_Inom)
          target_label->setpoint_pochatkova_k_vymk = temp_value;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;
        
        break;
      }
    case MA_UVV_TYPE_SIGNAL_INPUT:
      {
        if (data <= ((1 << NUMBER_INPUTS) - 1)) 
        {
          target_label->type_of_input_signal = data;
          
          //��������� ������ �����
          for(unsigned int i = 0; i < NUMBER_INPUTS; i++)
          {
            if ((target_label->type_of_input_signal & (1 << i)) !=0)
            {
              if ((target_label->dopusk_dv[i] % 10) != 0)
              {
                target_label->dopusk_dv[i] = (target_label->dopusk_dv[i] / 10)*10;
              }

              if (target_label->dopusk_dv[i] < KOEF_DOPUSK_DV_ZMIN_MIN)
                target_label->dopusk_dv[i] = KOEF_DOPUSK_DV_ZMIN_MIN;
            }
          }
        }
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_UVV_TYPE_INPUT:
      {
        temp_value = ((~(unsigned int)data)) & ((1 << NUMBER_INPUTS) - 1);

        if (data <= ((1 << NUMBER_INPUTS) - 1)) 
          target_label->type_of_input = temp_value;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_UVV_TYPE_OUTPUT:
      {
        if (data <= ((1 << NUMBER_OUTPUTS) - 1)) 
          target_label->type_of_output = data;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_TYPE_DF:
      {
        if (data <= ((1 << NUMBER_DEFINED_FUNCTIONS) - 1)) 
          target_label->type_df = data;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_UVV_TYPE_LED:
      {
        if (data <= ((1 << NUMBER_LEDS) - 1)) 
          target_label->type_of_led = data;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_DOPUSK_DV_1:
    case MA_DOPUSK_DV_2:
    case MA_DOPUSK_DV_3:
    case MA_DOPUSK_DV_4:
    case MA_DOPUSK_DV_5:
    case MA_DOPUSK_DV_6:
    case MA_DOPUSK_DV_7:
    case MA_DOPUSK_DV_8:
    case MA_DOPUSK_DV_9:
    case MA_DOPUSK_DV_10:
      {
        if (data <= KOEF_DOPUSK_DV_MAX)
        {
          //��������� ���������� ����� ���� � ������� � ����, ���� ��� ������� � ������ ������
          if (
              ((target_label->type_of_input_signal & (1 << (address_data - MA_DOPUSK_DV_1))) == 0) ||
              (
               ((target_label->type_of_input_signal & (1 << (address_data - MA_DOPUSK_DV_1))) != 0) &&
               ( data >= KOEF_DOPUSK_DV_ZMIN_MIN)                                                   &&
               ((data % 10) == 0)  
              )
             )
          {
            target_label->dopusk_dv[address_data - MA_DOPUSK_DV_1] = data;
          }
          else
            error = ERROR_ILLEGAL_DATA_VALUE;
        }
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_DF_PAUSE_1:
    case MA_DF_PAUSE_2:
    case MA_DF_PAUSE_3:
    case MA_DF_PAUSE_4:
    case MA_DF_PAUSE_5:
    case MA_DF_PAUSE_6:
    case MA_DF_PAUSE_7:
    case MA_DF_PAUSE_8:
      {
        temp_value = data*10;
        
#if (TIMEOUT_DF_PAUSE_MIN != 0)          
        if ((temp_value >= TIMEOUT_DF_PAUSE_MIN) && (temp_value <= TIMEOUT_DF_PAUSE_MAX))
#else
        if (temp_value <= TIMEOUT_DF_PAUSE_MAX)
#endif            
        {
          target_label->timeout_pause_df[address_data - MA_DF_PAUSE_1] = temp_value;
        }
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_DF_WORK_1:
    case MA_DF_WORK_2:
    case MA_DF_WORK_3:
    case MA_DF_WORK_4:
    case MA_DF_WORK_5:
    case MA_DF_WORK_6:
    case MA_DF_WORK_7:
    case MA_DF_WORK_8:
      {
        temp_value = data*10;
        
#if (TIMEOUT_DF_WORK_MIN != 0)          
        if ((temp_value >= TIMEOUT_DF_WORK_MIN) && (temp_value <= TIMEOUT_DF_WORK_MAX))
#else
        if (temp_value <= TIMEOUT_DF_WORK_MAX)
#endif            
        {
          target_label->timeout_work_df[address_data - MA_DF_WORK_1] = temp_value;
        }
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_CONTROL_MTZ:
      {
        if ((target_label->configuration & (1 << MTZ_BIT_CONFIGURATION)) !=0 )
        {
          int output_value = 0;

          output_value |= ((data >> (BIT_MA_CONTROL_MTZ1               - BIT_MA_CONTROL_MTZ_BASE)) & 0x1) << N_BIT_CTRMTZ_1;
          output_value |= ((data >> (BIT_MA_CONTROL_MTZ2               - BIT_MA_CONTROL_MTZ_BASE)) & 0x1) << N_BIT_CTRMTZ_2;
          output_value |= ((data >> (BIT_MA_CONTROL_MTZ3               - BIT_MA_CONTROL_MTZ_BASE)) & 0x1) << N_BIT_CTRMTZ_3;
          output_value |= ((data >> (BIT_MA_CONTROL_MTZ4               - BIT_MA_CONTROL_MTZ_BASE)) & 0x1) << N_BIT_CTRMTZ_4;
          output_value |= ((data >> (BIT_MA_CONTROL_MTZ2_PRYSKORENNJA  - BIT_MA_CONTROL_MTZ_BASE)) & 0x1) << N_BIT_CTRMTZ_2_PRYSKORENNJA;
          output_value |= ((data >> (BIT_MA_CONTROL_MTZ2_PRYSKORENA    - BIT_MA_CONTROL_MTZ_BASE)) & 0x1) << N_BIT_CTRMTZ_2_PRYSKORENA;
          output_value |= ((data >> (BIT_MA_CONTROL_MTZ1_N_VPERED      - BIT_MA_CONTROL_MTZ_BASE)) & 0x1) << N_BIT_CTRMTZ_1_VPERED;
          output_value |= ((data >> (BIT_MA_CONTROL_MTZ1_N_NAZAD       - BIT_MA_CONTROL_MTZ_BASE)) & 0x1) << N_BIT_CTRMTZ_1_NAZAD;
          output_value |= ((data >> (BIT_MA_CONTROL_MTZ2_N_VPERED      - BIT_MA_CONTROL_MTZ_BASE)) & 0x1) << N_BIT_CTRMTZ_2_VPERED;
          output_value |= ((data >> (BIT_MA_CONTROL_MTZ2_N_NAZAD       - BIT_MA_CONTROL_MTZ_BASE)) & 0x1) << N_BIT_CTRMTZ_2_NAZAD;
          output_value |= ((data >> (BIT_MA_CONTROL_MTZ3_N_VPERED      - BIT_MA_CONTROL_MTZ_BASE)) & 0x1) << N_BIT_CTRMTZ_3_VPERED;
          output_value |= ((data >> (BIT_MA_CONTROL_MTZ3_N_NAZAD       - BIT_MA_CONTROL_MTZ_BASE)) & 0x1) << N_BIT_CTRMTZ_3_NAZAD;
          output_value |= ((data >> (BIT_MA_CONTROL_MTZ4_N_VPERED      - BIT_MA_CONTROL_MTZ_BASE)) & 0x1) << N_BIT_CTRMTZ_4_VPERED;
          output_value |= ((data >> (BIT_MA_CONTROL_MTZ4_N_NAZAD       - BIT_MA_CONTROL_MTZ_BASE)) & 0x1) << N_BIT_CTRMTZ_4_NAZAD;
          output_value |= ((data >> (BIT_MA_CONTROL_MTZ_NESPR_KIL_NAPR - BIT_MA_CONTROL_MTZ_BASE)) & 0x1) << N_BIT_CTRMTZ_NESPR_KIL_NAPR;
        
          target_label->control_mtz = output_value;
        }
        else
          error = ERROR_ILLEGAL_DATA_ADDRESS;

        break;
      }
    case MA_CONTROL_ZDZ:
      {
        if (
            ((target_label->configuration & (1 << ZDZ_BIT_CONFIGURATION)) != 0)
            &&
            (
             ((target_label->configuration & (1 << MTZ_BIT_CONFIGURATION)) != 0)
             ||
             (
              ((target_label->configuration & (1 << MTZ_BIT_CONFIGURATION)) == 0)  
              &&
              (
               (((data >> (BIT_MA_CONTROL_ZDZ_STARTED_FROM_MTZ1 - BIT_MA_CONTROL_ZDZ_BASE)) & 0x1) == 0) &&
               (((data >> (BIT_MA_CONTROL_ZDZ_STARTED_FROM_MTZ2 - BIT_MA_CONTROL_ZDZ_BASE)) & 0x1) == 0) &&
               (((data >> (BIT_MA_CONTROL_ZDZ_STARTED_FROM_MTZ3 - BIT_MA_CONTROL_ZDZ_BASE)) & 0x1) == 0) &&
               (((data >> (BIT_MA_CONTROL_ZDZ_STARTED_FROM_MTZ4 - BIT_MA_CONTROL_ZDZ_BASE)) & 0x1) == 0)
              ) 
             ) 
            )
           )   
        {
          int output_value = 0;

          output_value |= ((data >> (BIT_MA_CONTROL_ZDZ                   - BIT_MA_CONTROL_ZDZ_BASE)) & 0x1) << INDEX_ML_CTRZDZ_STATE;
          output_value |= ((data >> (BIT_MA_CONTROL_ZDZ_STARTED_FROM_MTZ1 - BIT_MA_CONTROL_ZDZ_BASE)) & 0x1) << INDEX_ML_CTRZDZ_STARTED_FROM_MTZ1;
          output_value |= ((data >> (BIT_MA_CONTROL_ZDZ_STARTED_FROM_MTZ2 - BIT_MA_CONTROL_ZDZ_BASE)) & 0x1) << INDEX_ML_CTRZDZ_STARTED_FROM_MTZ2;
          output_value |= ((data >> (BIT_MA_CONTROL_ZDZ_STARTED_FROM_MTZ3 - BIT_MA_CONTROL_ZDZ_BASE)) & 0x1) << INDEX_ML_CTRZDZ_STARTED_FROM_MTZ3;
          output_value |= ((data >> (BIT_MA_CONTROL_ZDZ_STARTED_FROM_MTZ4 - BIT_MA_CONTROL_ZDZ_BASE)) & 0x1) << INDEX_ML_CTRZDZ_STARTED_FROM_MTZ4;
        
          target_label->control_zdz = output_value;
        }
        else
        {
          if ((target_label->configuration & (1 << ZDZ_BIT_CONFIGURATION)) == 0) error = ERROR_ILLEGAL_DATA_ADDRESS;
          else  error = ERROR_ILLEGAL_DATA_VALUE;
        }

        break;
      }
    case MA_CONTROL_NZZ:
      {
        if (
            ((target_label->configuration & (1 << ZZ_BIT_CONFIGURATION)) != 0 )
            &&  
            (
             ((target_label->control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_3U0_Ubc_TN2) == 0)
             ||
             (
              (((data >> (BIT_MA_CONTROL_NZZ        - BIT_MA_CONTROL_NZZ_BASE)) & 0x1) == 0) &&
              (((data >> (BIT_MA_CONTROL_NZZ_3U0    - BIT_MA_CONTROL_NZZ_BASE)) & 0x1) == 0)
             )   
            )
            &&  
            (
             (((data >> (BIT_MA_CONTROL_NZZ_TYPE - BIT_MA_CONTROL_NZZ_BASE)) & 0x1) == 0)
             ||
             (((data >> (BIT_MA_CONTROL_NZZ - BIT_MA_CONTROL_NZZ_BASE)) & 0x1) == 0)
            )
           )   
        {
          int output_value = 0;

          output_value |= ((data >> (BIT_MA_CONTROL_NZZ_3I0    - BIT_MA_CONTROL_NZZ_BASE)) & 0x1) << INDEX_ML_CTR_ZZ1_3I0_STATE;
          output_value |= ((data >> (BIT_MA_CONTROL_NZZ_SECTOR - BIT_MA_CONTROL_NZZ_BASE)) & 0x1) << INDEX_ML_CTR_ZZ1_SECTOR;
          output_value |= ((data >> (BIT_MA_CONTROL_NZZ        - BIT_MA_CONTROL_NZZ_BASE)) & 0x1) << INDEX_ML_CTR_ZZ1_NZZ_STATE;
          output_value |= ((data >> (BIT_MA_CONTROL_NZZ_3U0    - BIT_MA_CONTROL_NZZ_BASE)) & 0x1) << INDEX_ML_CTR_ZZ1_3U0_STATE;
          output_value |= ((data >> (BIT_MA_CONTROL_NZZ_TYPE   - BIT_MA_CONTROL_NZZ_BASE)) & 0x1) << INDEX_ML_CTR_ZZ1_TYPE_BIT;
        
          target_label->control_zz = output_value;

          //���������� ��������
          action_after_changing_zz1_type(target_label);
        }
        else
        {
          if ((target_label->configuration & (1 << ZZ_BIT_CONFIGURATION)) == 0) error = ERROR_ILLEGAL_DATA_ADDRESS;
          else  error = ERROR_ILLEGAL_DATA_VALUE;
        }

        break;
      }
    case MA_CONTROL_ZOP:
      {
        if ((target_label->configuration & (1 << ZOP_BIT_CONFIGURATION)) !=0 )
        {
          int output_value = 0;

          output_value |= ((data >> (BIT_MA_CONTROL_ZOP1 - BIT_MA_CONTROL_ZOP_BASE)) & 0x1) << CTR_ZOP_STATE_BIT;
        
          target_label->control_zop = output_value;
        }
        else
          error = ERROR_ILLEGAL_DATA_ADDRESS;

        break;
      }
    case MA_CONTROL_UMIN:
      {
        if ((target_label->configuration & (1 << UMIN_BIT_CONFIGURATION)) !=0 )
        {
          int output_value = 0;

          output_value |= ((data >> (BIT_MA_CONTROL_UMIN1           - BIT_MA_CONTROL_UMIN_BASE)) & 0x1) << INDEX_CTR_UMIN1;
          output_value |= ((data >> (BIT_MA_CONTROL_UMIN2           - BIT_MA_CONTROL_UMIN_BASE)) & 0x1) << INDEX_CTR_UMIN2;
          output_value |= ((data >> (BIT_MA_CONTROL_PO_UMIN1_AND_OR - BIT_MA_CONTROL_UMIN_BASE)) & 0x1) << INDEX_CTR_PO_UMIN1_OR_AND;
          output_value |= ((data >> (BIT_MA_CONTROL_PO_UMIN2_AND_OR - BIT_MA_CONTROL_UMIN_BASE)) & 0x1) << INDEX_CTR_PO_UMIN2_OR_AND;
          output_value |= ((data >> (BIT_MA_CONTROL_BLK_UMIN1_BY_U  - BIT_MA_CONTROL_UMIN_BASE)) & 0x1) << INDEX_CTR_UMIN1_UBLK;
          output_value |= ((data >> (BIT_MA_CONTROL_BLK_UMIN2_BY_U  - BIT_MA_CONTROL_UMIN_BASE)) & 0x1) << INDEX_CTR_UMIN2_UBLK;
          output_value |= ((data >> (BIT_MA_CONTROL_BLK_UMIN1_BY_I  - BIT_MA_CONTROL_UMIN_BASE)) & 0x1) << INDEX_CTR_UMIN1_IBLK;
          output_value |= ((data >> (BIT_MA_CONTROL_BLK_UMIN2_BY_I  - BIT_MA_CONTROL_UMIN_BASE)) & 0x1) << INDEX_CTR_UMIN2_IBLK;
        
          target_label->control_Umin = output_value;
        }
        else
        {
          if ((target_label->configuration & (1 << UMIN_BIT_CONFIGURATION)) == 0) error = ERROR_ILLEGAL_DATA_ADDRESS;
          else  error = ERROR_ILLEGAL_DATA_VALUE;
        }

        break;
      }
    case MA_CONTROL_UMAX:
      {
        if ((target_label->configuration & (1 << UMAX_BIT_CONFIGURATION)) !=0 )
        {
          int output_value = 0;

          output_value |= ((data >> (BIT_MA_CONTROL_UMAX1           - BIT_MA_CONTROL_UMAX_BASE)) & 0x1) << INDEX_CTR_UMAX1;
          output_value |= ((data >> (BIT_MA_CONTROL_UMAX2           - BIT_MA_CONTROL_UMAX_BASE)) & 0x1) << INDEX_CTR_UMAX2;
          output_value |= ((data >> (BIT_MA_CONTROL_PO_UMAX1_AND_OR - BIT_MA_CONTROL_UMAX_BASE)) & 0x1) << INDEX_CTR_PO_UMAX1_OR_AND;
          output_value |= ((data >> (BIT_MA_CONTROL_PO_UMAX2_AND_OR - BIT_MA_CONTROL_UMAX_BASE)) & 0x1) << INDEX_CTR_PO_UMAX2_OR_AND;
        
          target_label->control_Umax = output_value;
        }
        else
        {
          if ((target_label->configuration & (1 << UMAX_BIT_CONFIGURATION)) == 0) error = ERROR_ILLEGAL_DATA_ADDRESS;
          else  error = ERROR_ILLEGAL_DATA_VALUE;
        }

        break;
      }
    case MA_CONTROL_558:
      {
        if (
            (
             ((target_label->configuration & (1 << APV_ZMN_BIT_CONFIGURATION)) != 0)
             ||
             (
              ((target_label->configuration & (1 << APV_ZMN_BIT_CONFIGURATION)) == 0)  
              &&
              (((data >> (BIT_MA_CONTROL_APV_ZMN - BIT_MA_CONTROL_558_BASE)) & 0x1) == 0)
             ) 
            )
            &&
            (
             ((target_label->configuration & (1 << CONTROL_U_BIT_CONFIGURATION)) != 0)
             ||
             (
              ((target_label->configuration & (1 << CONTROL_U_BIT_CONFIGURATION)) == 0)  
              &&
              (
               (((data >> (BIT_MA_CONTROL_U_OL - BIT_MA_CONTROL_558_BASE)) & 0x1) == 0) &&
               (((data >> (BIT_MA_CONTROL_U_RL - BIT_MA_CONTROL_558_BASE)) & 0x1) == 0)
              ) 
             ) 
            )
           )   
        {
          int output_value = target_label->control_extra_settings_1 & ((unsigned int)(~(CTR_EXTRA_SETTINGS_1_CTRL_3U0_Ubc_TN2 | CTR_EXTRA_SETTINGS_1_CTRL_PHASE_LINE)));
          output_value |= ((data >> (BIT_MA_CONTROL_PHASE_LINE  - BIT_MA_CONTROL_558_BASE)) & 0x1) << INDEX_ML_CTREXTRA_SETTINGS_1_CTRL_PHASE_LINE;
          output_value |= ((data >> (BIT_MA_CONTROL_3U0_Ubc_TN2 - BIT_MA_CONTROL_558_BASE)) & 0x1) << INDEX_ML_CTREXTRA_SETTINGS_1_CTRL_3U0_Ubc_TN2;
          target_label->control_extra_settings_1 = output_value;

          output_value = 0;
          output_value |= ((data >> (BIT_MA_CONTROL_APV_ZMN                   - BIT_MA_CONTROL_558_BASE)) & 0x1) << INDEX_CTR_APV_ZMN;
          target_label->control_apv_zmn = output_value;

          output_value = 0;
          output_value |= ((data >> (BIT_MA_CONTROL_U_OL - BIT_MA_CONTROL_558_BASE)) & 0x1) << INDEX_CTR_U_OL;
          output_value |= ((data >> (BIT_MA_CONTROL_U_RL - BIT_MA_CONTROL_558_BASE)) & 0x1) << INDEX_CTR_U_RL;
          target_label->control_control_U = output_value;

          //���������� ��������
          action_after_changing_phase_line(target_label);
        }
        else
        {
          if (
              (
               ((target_label->configuration & (1 << APV_ZMN_BIT_CONFIGURATION)) == 0)  
               &&
               (((data >> (BIT_MA_CONTROL_APV_ZMN - BIT_MA_CONTROL_558_BASE)) & 0x1) != 0)
              )
              ||
              (
               (
                ((target_label->configuration & (1 << CONTROL_U_BIT_CONFIGURATION)) == 0)  
                &&
                (
                 (((data >> (BIT_MA_CONTROL_U_OL - BIT_MA_CONTROL_558_BASE)) & 0x1) != 0) ||
                 (((data >> (BIT_MA_CONTROL_U_RL - BIT_MA_CONTROL_558_BASE)) & 0x1) != 0)
                ) 
               ) 
              )
             )   
          {
            error = ERROR_ILLEGAL_DATA_ADDRESS;
          }
          else
          {
            error = ERROR_ILLEGAL_DATA_VALUE;
          }
        }

        break;
      }
    case MA_CONTROL_UROV_PART1:
      {
        if (
            ((target_label->configuration & (1 << UROV_BIT_CONFIGURATION)) != 0)
            &&
            (
             ((target_label->configuration & (1 << MTZ_BIT_CONFIGURATION)) != 0)
             ||
             (
              (((data >> (BIT_MA_CONTROL_UROV_STARTED_FROM_MTZ1 - BIT_MA_CONTROL_UROV_BASE_PART1)) & 0x1) == 0) &&
              (((data >> (BIT_MA_CONTROL_UROV_STARTED_FROM_MTZ2 - BIT_MA_CONTROL_UROV_BASE_PART1)) & 0x1) == 0) &&
              (((data >> (BIT_MA_CONTROL_UROV_STARTED_FROM_MTZ3 - BIT_MA_CONTROL_UROV_BASE_PART1)) & 0x1) == 0) &&
              (((data >> (BIT_MA_CONTROL_UROV_STARTED_FROM_MTZ4 - BIT_MA_CONTROL_UROV_BASE_PART1)) & 0x1) == 0)
             ) 
            )
            &&  
            (
             ((target_label->configuration & (1 << ZZ_BIT_CONFIGURATION)) != 0)
             ||
             (
              (((data >> (BIT_MA_CONTROL_UROV_STARTED_FROM_3I0 - BIT_MA_CONTROL_UROV_BASE_PART1)) & 0x1) == 0) &&
              (((data >> (BIT_MA_CONTROL_UROV_STARTED_FROM_3U0 - BIT_MA_CONTROL_UROV_BASE_PART1)) & 0x1) == 0) &&
              (((data >> (BIT_MA_CONTROL_UROV_STARTED_FROM_NZZ - BIT_MA_CONTROL_UROV_BASE_PART1)) & 0x1) == 0)
             ) 
            )
            &&  
            (
             ((target_label->control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_3U0_Ubc_TN2) == 0)
             ||
             (
              (((data >> (BIT_MA_CONTROL_UROV_STARTED_FROM_3U0 - BIT_MA_CONTROL_UROV_BASE_PART1)) & 0x1) == 0) &&
              (((data >> (BIT_MA_CONTROL_UROV_STARTED_FROM_NZZ - BIT_MA_CONTROL_UROV_BASE_PART1)) & 0x1) == 0)
             )   
            )
            &&  
            (
             ((target_label->control_zz & CTR_ZZ1_TYPE) == 0)
             ||
             (
              (((data >> (BIT_MA_CONTROL_UROV_STARTED_FROM_NZZ - BIT_MA_CONTROL_UROV_BASE_PART1)) & 0x1) == 0)
             )   
            )
            &&  
            (
             ((target_label->configuration & (1 << ZOP_BIT_CONFIGURATION)) != 0)
             ||
             (
              (((data >> (BIT_MA_CONTROL_UROV_STARTED_FROM_ZOP1 - BIT_MA_CONTROL_UROV_BASE_PART1)) & 0x1) == 0)
             )   
            )
            &&  
            (
             ((target_label->configuration & (1 << UMIN_BIT_CONFIGURATION)) != 0)
             ||
             (
              (((data >> (BIT_MA_CONTROL_UROV_STARTED_FROM_UMIN1 - BIT_MA_CONTROL_UROV_BASE_PART1)) & 0x1) == 0) &&
              (((data >> (BIT_MA_CONTROL_UROV_STARTED_FROM_UMIN2 - BIT_MA_CONTROL_UROV_BASE_PART1)) & 0x1) == 0)
             )   
            )
            &&  
            (
             ((target_label->configuration & (1 << UMAX_BIT_CONFIGURATION)) != 0)
             ||
             (
              (((data >> (BIT_MA_CONTROL_UROV_STARTED_FROM_UMAX1 - BIT_MA_CONTROL_UROV_BASE_PART1)) & 0x1) == 0) &&
              (((data >> (BIT_MA_CONTROL_UROV_STARTED_FROM_UMAX2 - BIT_MA_CONTROL_UROV_BASE_PART1)) & 0x1) == 0)
             )   
            )
           )   
        {
          int output_value = target_label->control_urov & 
                            (unsigned int)(~(
                                             CTR_UROV_STATE              | 
                                             CTR_UROV_STARTED_FROM_MTZ1  | 
                                             CTR_UROV_STARTED_FROM_MTZ2  | 
                                             CTR_UROV_STARTED_FROM_MTZ3  | 
                                             CTR_UROV_STARTED_FROM_MTZ4  |
                                             CTR_UROV_STARTED_FROM_UMAX1 | 
                                             CTR_UROV_STARTED_FROM_UMAX2 | 
                                             CTR_UROV_STARTED_FROM_UMIN1 | 
                                             CTR_UROV_STARTED_FROM_UMIN2 |
                                             CTR_UROV_STARTED_FROM_ZOP1  | 
                                             CTR_UROV_STARTED_FROM_NZZ   | 
                                             CTR_UROV_STARTED_FROM_3I0   | 
                                             CTR_UROV_STARTED_FROM_3U0
                                          ));

          output_value |= ((data >> (BIT_MA_CONTROL_UROV_STATE              - BIT_MA_CONTROL_UROV_BASE_PART1)) & 0x1) << INDEX_ML_CTRUROV_STATE;
          output_value |= ((data >> (BIT_MA_CONTROL_UROV_STARTED_FROM_MTZ1  - BIT_MA_CONTROL_UROV_BASE_PART1)) & 0x1) << INDEX_ML_CTRUROV_STARTED_FROM_MTZ1;
          output_value |= ((data >> (BIT_MA_CONTROL_UROV_STARTED_FROM_MTZ2  - BIT_MA_CONTROL_UROV_BASE_PART1)) & 0x1) << INDEX_ML_CTRUROV_STARTED_FROM_MTZ2;
          output_value |= ((data >> (BIT_MA_CONTROL_UROV_STARTED_FROM_MTZ3  - BIT_MA_CONTROL_UROV_BASE_PART1)) & 0x1) << INDEX_ML_CTRUROV_STARTED_FROM_MTZ3;
          output_value |= ((data >> (BIT_MA_CONTROL_UROV_STARTED_FROM_MTZ4  - BIT_MA_CONTROL_UROV_BASE_PART1)) & 0x1) << INDEX_ML_CTRUROV_STARTED_FROM_MTZ4;
          output_value |= ((data >> (BIT_MA_CONTROL_UROV_STARTED_FROM_UMAX1 - BIT_MA_CONTROL_UROV_BASE_PART1)) & 0x1) << INDEX_ML_CTRUROV_STARTED_FROM_UMAX1;
          output_value |= ((data >> (BIT_MA_CONTROL_UROV_STARTED_FROM_UMAX2 - BIT_MA_CONTROL_UROV_BASE_PART1)) & 0x1) << INDEX_ML_CTRUROV_STARTED_FROM_UMAX2;
          output_value |= ((data >> (BIT_MA_CONTROL_UROV_STARTED_FROM_UMIN1 - BIT_MA_CONTROL_UROV_BASE_PART1)) & 0x1) << INDEX_ML_CTRUROV_STARTED_FROM_UMIN1;
          output_value |= ((data >> (BIT_MA_CONTROL_UROV_STARTED_FROM_UMIN2 - BIT_MA_CONTROL_UROV_BASE_PART1)) & 0x1) << INDEX_ML_CTRUROV_STARTED_FROM_UMIN2;
          output_value |= ((data >> (BIT_MA_CONTROL_UROV_STARTED_FROM_ZOP1  - BIT_MA_CONTROL_UROV_BASE_PART1)) & 0x1) << INDEX_ML_CTRUROV_STARTED_FROM_ZOP1;
          output_value |= ((data >> (BIT_MA_CONTROL_UROV_STARTED_FROM_NZZ   - BIT_MA_CONTROL_UROV_BASE_PART1)) & 0x1) << INDEX_ML_CTRUROV_STARTED_FROM_NZZ;
          output_value |= ((data >> (BIT_MA_CONTROL_UROV_STARTED_FROM_3I0   - BIT_MA_CONTROL_UROV_BASE_PART1)) & 0x1) << INDEX_ML_CTRUROV_STARTED_FROM_3I0;
          output_value |= ((data >> (BIT_MA_CONTROL_UROV_STARTED_FROM_3U0   - BIT_MA_CONTROL_UROV_BASE_PART1)) & 0x1) << INDEX_ML_CTRUROV_STARTED_FROM_3U0;
        
          target_label->control_urov = output_value;
        }
        else
        {
          if ((target_label->configuration & (1 << UROV_BIT_CONFIGURATION)) == 0) error = ERROR_ILLEGAL_DATA_ADDRESS;
          else  error = ERROR_ILLEGAL_DATA_VALUE;
        }

        break;
      }
    case MA_CONTROL_UROV_PART2:
      {
        if (
            ((target_label->configuration & (1 << UROV_BIT_CONFIGURATION)) != 0)
            &&  
            (
             ((target_label->configuration & (1 << ZDZ_BIT_CONFIGURATION)) != 0)
             ||
             (
              (((data >> (BIT_MA_CONTROL_UROV_STARTED_FROM_ZDZ - BIT_MA_CONTROL_UROV_BASE_PART2)) & 0x1) == 0)
             ) 
            )
            &&  
            (
             ((target_label->configuration & (1 << ACHR_CHAPV_BIT_CONFIGURATION)) != 0)
             ||
             (
              (((data >> (BIT_MA_CONTROL_UROV_STARTED_FROM_ACHR - BIT_MA_CONTROL_UROV_BASE_PART2)) & 0x1) == 0)
             ) 
            )
           )   
        {
          int output_value = target_label->control_urov & 
                            (unsigned int)(~(
                                             CTR_UROV_STARTED_FROM_ZDZ  |
                                             CTR_UROV_STARTED_FROM_ACHR
                                          ));

          output_value |= ((data >> (BIT_MA_CONTROL_UROV_STARTED_FROM_ZDZ   - BIT_MA_CONTROL_UROV_BASE_PART2)) & 0x1) << INDEX_ML_CTRUROV_STARTED_FROM_ZDZ;
          output_value |= ((data >> (BIT_MA_CONTROL_UROV_STARTED_FROM_ACHR  - BIT_MA_CONTROL_UROV_BASE_PART2)) & 0x1) << INDEX_ML_CTRUROV_STARTED_FROM_ACHR;
        
          target_label->control_urov = output_value;
        }
        else
        {
          if ((target_label->configuration & (1 << UROV_BIT_CONFIGURATION)) == 0) error = ERROR_ILLEGAL_DATA_ADDRESS;
          else  error = ERROR_ILLEGAL_DATA_VALUE;
        }

        break;
      }
    case MA_CONTROL_AVR:
      {
        if ((target_label->configuration & (1 << AVR_BIT_CONFIGURATION)) !=0 )
        {
          int output_value = 0;

          output_value |= ((data >> (BIT_MA_CONTROL_AVR                       - BIT_MA_CONTROL_AVR_BASE)) & 0x1) << INDEX_CTR_AVR;
          output_value |= ((data >> (BIT_MA_CONTROL_AVR_OTKL_BLK_VID_ZAHYSTIV - BIT_MA_CONTROL_AVR_BASE)) & 0x1) << INDEX_CTR_AVR_OTKL_BLK_VID_ZAHYSTIV;
        
          target_label->control_avr = output_value;
        }
        else
          error = ERROR_ILLEGAL_DATA_ADDRESS;

        break;
      }
    case MA_CONTROL_APV:
      {
        if (
            ((target_label->configuration & (1 << APV_BIT_CONFIGURATION)) != 0)
            &&
            (
             ((target_label->configuration & (1 << MTZ_BIT_CONFIGURATION)) != 0)
             ||
             (
              ((target_label->configuration & (1 << MTZ_BIT_CONFIGURATION)) == 0)  
              &&
              (
               (((data >> (BIT_MA_CONTROL_APV_STARTED_FROM_MTZ1 - BIT_MA_CONTROL_APV_BASE)) & 0x1) == 0) &&
               (((data >> (BIT_MA_CONTROL_APV_STARTED_FROM_MTZ2 - BIT_MA_CONTROL_APV_BASE)) & 0x1) == 0) &&
               (((data >> (BIT_MA_CONTROL_APV_STARTED_FROM_MTZ3 - BIT_MA_CONTROL_APV_BASE)) & 0x1) == 0) &&
               (((data >> (BIT_MA_CONTROL_APV_STARTED_FROM_MTZ4 - BIT_MA_CONTROL_APV_BASE)) & 0x1) == 0)
              ) 
             ) 
            )
           )   
        {
          int output_value = 0;

          output_value |= ((data >> (BIT_MA_CONTROL_APV_CYCLE1            - BIT_MA_CONTROL_APV_BASE)) & 0x1) << INDEX_ML_CTRAPV_STAGE_1;
          output_value |= ((data >> (BIT_MA_CONTROL_APV_CYCLE2            - BIT_MA_CONTROL_APV_BASE)) & 0x1) << INDEX_ML_CTRAPV_STAGE_2;
          output_value |= ((data >> (BIT_MA_CONTROL_APV_CYCLE3            - BIT_MA_CONTROL_APV_BASE)) & 0x1) << INDEX_ML_CTRAPV_STAGE_3;
          output_value |= ((data >> (BIT_MA_CONTROL_APV_CYCLE4            - BIT_MA_CONTROL_APV_BASE)) & 0x1) << INDEX_ML_CTRAPV_STAGE_4;
          output_value |= ((data >> (BIT_MA_CONTROL_APV_STARTED_FROM_MTZ1 - BIT_MA_CONTROL_APV_BASE)) & 0x1) << INDEX_ML_CTRAPV_STARTED_FROM_MTZ1;
          output_value |= ((data >> (BIT_MA_CONTROL_APV_STARTED_FROM_MTZ2 - BIT_MA_CONTROL_APV_BASE)) & 0x1) << INDEX_ML_CTRAPV_STARTED_FROM_MTZ2;
          output_value |= ((data >> (BIT_MA_CONTROL_APV_STARTED_FROM_MTZ3 - BIT_MA_CONTROL_APV_BASE)) & 0x1) << INDEX_ML_CTRAPV_STARTED_FROM_MTZ3;
          output_value |= ((data >> (BIT_MA_CONTROL_APV_STARTED_FROM_MTZ4 - BIT_MA_CONTROL_APV_BASE)) & 0x1) << INDEX_ML_CTRAPV_STARTED_FROM_MTZ4;
        
          target_label->control_apv = output_value;
        }
        else
        {
          if ((target_label->configuration & (1 << APV_BIT_CONFIGURATION)) == 0) error = ERROR_ILLEGAL_DATA_ADDRESS;
          else  error = ERROR_ILLEGAL_DATA_VALUE;
        }

        break;
      }
    case MA_CONTROL_ACHR_CHAPV:
      {
        if ((target_label->configuration & (1 << ACHR_CHAPV_BIT_CONFIGURATION)) !=0 )
        {
          int output_value = 0;

          output_value |= ((data >> (BIT_MA_CONTROL_ACHR_STATE         - BIT_MA_CONTROL_ACHR_CHAPV_BASE)) & 0x1) << INDEX_CTR_ACHR;
          output_value |= ((data >> (BIT_MA_CONTROL_CHAPV_STATE        - BIT_MA_CONTROL_ACHR_CHAPV_BASE)) & 0x1) << INDEX_CTR_CHAPV;
          output_value |= ((data >> (BIT_MA_CONTROL_CHAPV_VID_DV_STATE - BIT_MA_CONTROL_ACHR_CHAPV_BASE)) & 0x1) << INDEX_CTR_CHAPV_VID_DV;
        
          target_label->control_achr_chapv = output_value;
        }
        else
          error = ERROR_ILLEGAL_DATA_ADDRESS;

        break;
      }
    case MA_CONTROL_CTRL_VV:
      {
        int output_value = 0;
        output_value |= ((data >> (BIT_MA_CONTROL_CTRL_VV_STATE  - BIT_MA_CONTROL_CTRL_VV_BASE)) & 0x1) << INDEX_ML_CTRPRYVOD_VV;
        output_value |= ((data >> (BIT_MA_CONTROL_CTRL_RESURS_VV - BIT_MA_CONTROL_CTRL_VV_BASE)) & 0x1) << INDEX_ML_CTRRESURS_VV;
        target_label->control_switch = output_value;

        output_value = target_label->control_extra_settings_1 & ((unsigned int)(~(
                                                                                  CTR_EXTRA_SETTINGS_1_BLK_ON_CB_MISCEVE  |
                                                                                  CTR_EXTRA_SETTINGS_1_BLK_OFF_CB_MISCEVE | 
                                                                                  CTR_EXTRA_SETTINGS_1_CTRL_FB_ACTIVATION | 
                                                                                  CTR_EXTRA_SETTINGS_1_CTRL_READY_TU      | 
                                                                                  CTR_EXTRA_SETTINGS_1_CTRL_WINDOW_OFF_CB
                                                                                 )));
        output_value |= ((data >> (BIT_MA_CONTROL_CTRL_BLK_ON_CB_MISCEVE  - BIT_MA_CONTROL_CTRL_VV_BASE)) & 0x1) << INDEX_ML_CTREXTRA_SETTINGS_1_BLK_ON_CB_MISCEVE;
        output_value |= ((data >> (BIT_MA_CONTROL_CTRL_BLK_OFF_CB_MISCEVE - BIT_MA_CONTROL_CTRL_VV_BASE)) & 0x1) << INDEX_ML_CTREXTRA_SETTINGS_1_BLK_OFF_CB_MISCEVE;
        output_value |= ((data >> (BIT_MA_CONTROL_CTRL_FB_ACTIVATION      - BIT_MA_CONTROL_CTRL_VV_BASE)) & 0x1) << INDEX_ML_CTREXTRA_SETTINGS_1_CTRL_FB_ACTIVATION;
        output_value |= ((data >> (BIT_MA_CONTROL_CTRL_READY_TU           - BIT_MA_CONTROL_CTRL_VV_BASE)) & 0x1) << INDEX_ML_CTREXTRA_SETTINGS_1_CTRL_READY_TU;
        output_value |= ((data >> (BIT_MA_CONTROL_CTRL_WINDOW_OFF_CB      - BIT_MA_CONTROL_CTRL_VV_BASE)) & 0x1) << INDEX_ML_CTREXTRA_SETTINGS_1_CTRL_WINDOW_OFF_CB;
        target_label->control_extra_settings_1 = output_value;

        break;
      }
    case MA_CONTROL_VMP:
      {
        if ((target_label->configuration & (1 << VMP_BIT_CONFIGURATION)) !=0 )
        {
          int output_value = 0;

          output_value |= ((data >> (BIT_MA_CONTROL_VMP_STATE - BIT_MA_CONTROL_VMP_BASE)) & 0x1) << INDEX_CTR_VMP_STATE;
        
          target_label->control_vmp = output_value;
        }
        else
          error = ERROR_ILLEGAL_DATA_ADDRESS;

        break;
      }
    case MA_CONFIGURATION_PART1:
      {
        int output_value = target_label->configuration & 
                            (unsigned int)(~(
                                             (1 << MTZ_BIT_CONFIGURATION       ) | 
                                             (1 << ZDZ_BIT_CONFIGURATION       ) | 
                                             (1 << ZZ_BIT_CONFIGURATION        ) |
                                             (1 << ZOP_BIT_CONFIGURATION       ) | 
                                             (1 << ACHR_CHAPV_BIT_CONFIGURATION) |
                                             (1 << UMIN_BIT_CONFIGURATION      ) | 
                                             (1 << UMAX_BIT_CONFIGURATION      ) | 
                                             (1 << APV_ZMN_BIT_CONFIGURATION   ) | 
                                             (1 << CONTROL_U_BIT_CONFIGURATION ) |
                                             (1 << APV_BIT_CONFIGURATION       ) | 
                                             (1 << UROV_BIT_CONFIGURATION      ) | 
                                             (1 << AVR_BIT_CONFIGURATION       )
                                            ));

        output_value |= ((data >> (BIT_MA_CONFIGURATION_MTZ        - BIT_MA_CONFIGURATION_BASE_PART1)) & 0x1) << MTZ_BIT_CONFIGURATION;
        output_value |= ((data >> (BIT_MA_CONFIGURATION_ZDZ        - BIT_MA_CONFIGURATION_BASE_PART1)) & 0x1) << ZDZ_BIT_CONFIGURATION;
        output_value |= ((data >> (BIT_MA_CONFIGURATION_ZZ         - BIT_MA_CONFIGURATION_BASE_PART1)) & 0x1) << ZZ_BIT_CONFIGURATION;
        output_value |= ((data >> (BIT_MA_CONFIGURATION_ZOP        - BIT_MA_CONFIGURATION_BASE_PART1)) & 0x1) << ZOP_BIT_CONFIGURATION;
        output_value |= ((data >> (BIT_MA_CONFIGURATION_ACHR_CHAPV - BIT_MA_CONFIGURATION_BASE_PART1)) & 0x1) << ACHR_CHAPV_BIT_CONFIGURATION;
        output_value |= ((data >> (BIT_MA_CONFIGURATION_UMIN       - BIT_MA_CONFIGURATION_BASE_PART1)) & 0x1) << UMIN_BIT_CONFIGURATION;
        output_value |= ((data >> (BIT_MA_CONFIGURATION_UMAX       - BIT_MA_CONFIGURATION_BASE_PART1)) & 0x1) << UMAX_BIT_CONFIGURATION;
        output_value |= ((data >> (BIT_MA_CONFIGURATION_APV_ZMN    - BIT_MA_CONFIGURATION_BASE_PART1)) & 0x1) << APV_ZMN_BIT_CONFIGURATION;
        output_value |= ((data >> (BIT_MA_CONFIGURATION_KROL       - BIT_MA_CONFIGURATION_BASE_PART1)) & 0x1) << CONTROL_U_BIT_CONFIGURATION;
        output_value |= ((data >> (BIT_MA_CONFIGURATION_APV        - BIT_MA_CONFIGURATION_BASE_PART1)) & 0x1) << APV_BIT_CONFIGURATION;
        output_value |= ((data >> (BIT_MA_CONFIGURATION_UROV       - BIT_MA_CONFIGURATION_BASE_PART1)) & 0x1) << UROV_BIT_CONFIGURATION;
        output_value |= ((data >> (BIT_MA_CONFIGURATION_AVR        - BIT_MA_CONFIGURATION_BASE_PART1)) & 0x1) << AVR_BIT_CONFIGURATION;
        
        //���������� �� ���� ��������� ���������. �� ��'���� �� ������������� �������, ���� �� �������� �������� (�� �� ����������� � ���, ��� �� �������� ������������)
        if(action_after_changing_of_configuration(output_value, target_label) != 0)
          error = ERROR_SLAVE_DEVICE_BUSY;

        break;
      }
    case MA_CONFIGURATION_PART2:
      {
        int output_value = target_label->configuration & 
                            (unsigned int)(~(
                                             (1 << VMP_BIT_CONFIGURATION)
                                            ));

        output_value |= ((data >> (BIT_MA_CONFIGURATION_VMP - BIT_MA_CONFIGURATION_BASE_PART2)) & 0x1) << VMP_BIT_CONFIGURATION;
        
        //���������� �� ���� ��������� ���������. �� ��'���� �� ������������� �������, ���� �� �������� �������� (�� �� ����������� � ���, ��� �� �������� ������������)
        if(action_after_changing_of_configuration(output_value, target_label) != 0)
          error = ERROR_SLAVE_DEVICE_BUSY;

        break;
      }
    case MA_TO_DEACTIVATION_PASSWORD_INTERFACE:
      {
        //������������ ���� �������� �����, ���� ���� ��������� �� ����������, �� �������������� ������
        temp_value = data;
        
        if(
#if (TIMEOUT_DEACTIVATION_PASSWORD_MIN != 0)          
           ((temp_value >= TIMEOUT_DEACTIVATION_PASSWORD_MIN) && (temp_value <= TIMEOUT_DEACTIVATION_PASSWORD_MAX)) ||
#else
           (temp_value <= TIMEOUT_DEACTIVATION_PASSWORD_MAX) ||
#endif   
           (temp_value == TIMEOUT_DEACTIVATION_PASSWORD_OFF)
          )   
        {
          unsigned int *point_to_timeout_deactivation_password_interface;
          if (type_interface == USB_RECUEST)
          {
            point_to_timeout_deactivation_password_interface = &target_label->timeout_deactivation_password_interface_USB;
          }
          else if (type_interface == RS485_RECUEST)
          {
            point_to_timeout_deactivation_password_interface = &target_label->timeout_deactivation_password_interface_RS485;
          }
          else error = ERROR_SLAVE_DEVICE_FAILURE;
      
          if (error == 0) *point_to_timeout_deactivation_password_interface = temp_value;
        }
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_LANGUAGE_MENU:
      {
        temp_value = data;
        
#if (VALUE_SETTING_LANGUAGE_MIN != 0)          
        if ((temp_value >= VALUE_SETTING_LANGUAGE_MIN) && (temp_value <= VALUE_SETTING_LANGUAGE_MAX))
#else
        if (temp_value <= VALUE_SETTING_LANGUAGE_MAX)
#endif            
          target_label->language = temp_value;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_SPEED_RS485:
      {
        temp_value = data;
        
#if (VALUE_SPEED_INTERFACE_MIN != 0)          
        if ((temp_value >= VALUE_SPEED_INTERFACE_MIN) && (temp_value <= VALUE_SPEED_INTERFACE_MAX))
#else
        if (temp_value <= VALUE_SPEED_INTERFACE_MAX)
#endif            
          target_label->speed_RS485 = temp_value;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_STOP_BITS_RS485:
      {
        temp_value = data - 1;
        
#if (VALUE_STOP_BITS_INTERFACE_MIN != 0)          
        if ((temp_value >= VALUE_STOP_BITS_INTERFACE_MIN) && (temp_value <= VALUE_STOP_BITS_INTERFACE_MAX))
#else
        if (temp_value <= VALUE_STOP_BITS_INTERFACE_MAX)
#endif            
          target_label->number_stop_bit_RS485 = temp_value;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_PARE_RS485:
      {
        temp_value = data;
        
#if (VALUE_PARE_INTERFACE_MIN != 0)          
        if ((temp_value >= VALUE_PARE_INTERFACE_MIN) && (temp_value <= VALUE_PARE_INTERFACE_MAX))
#else
        if (temp_value <= VALUE_PARE_INTERFACE_MAX)
#endif            
          target_label->pare_bit_RS485 = temp_value;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_TIMEOUT_RS485:
      {
        temp_value = data;
        
#if (VALUE_TIME_OUT_1_INTERFACE_MIN != 0)          
        if ((temp_value >= VALUE_TIME_OUT_1_INTERFACE_MIN) && (temp_value <= VALUE_TIME_OUT_1_INTERFACE_MAX))
#else
        if (temp_value <= VALUE_TIME_OUT_1_INTERFACE_MAX)
#endif            
          target_label->time_out_1_RS485 = temp_value;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_LOGICAL_ADDRESS:
      {
        temp_value = data;
    
        if ((temp_value >= KOEF_ADDRESS_MIN) && (temp_value <= KOEF_ADDRESS_MAX))
          target_label->address = temp_value;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_NAME_OF_CELL_CHARS_01_02:
    case MA_NAME_OF_CELL_CHARS_03_04:
    case MA_NAME_OF_CELL_CHARS_05_06:
    case MA_NAME_OF_CELL_CHARS_07_08:
    case MA_NAME_OF_CELL_CHARS_09_10:
    case MA_NAME_OF_CELL_CHARS_11_12:
    case MA_NAME_OF_CELL_CHARS_13_14:
    case MA_NAME_OF_CELL_CHARS_15_16:
      {
        
        unsigned int two_char_index = (address_data - MA_NAME_OF_CELL_CHARS_01_02) << 1;
        unsigned int byte_1 = (data & 0xff), byte_2 = (data >> 8) & 0xff;
        
        if (
            (
             (byte_1 >= 0x20) && (byte_1 <= 0x7e) || /*�������� ������� � �����*/
             (byte_1 >= 0xc0) && (byte_1 <= 0xff) || /*�������� ������� �������*/
             (byte_1 == 0xa8)                     || /*��������� ������ '�'*/  
             (byte_1 == 0xb8)                     || /*��������� ������ '�'*/  
             (
              (target_label->language == LANGUAGE_UA) &&
              (
               (byte_1 == 0xaf)                     || /*���������� ������ '�'*/  
               (byte_1 == 0xbf)                     || /*���������� ������ '�'*/  
               (byte_1 == 0xa5)                     || /*���������� ������ '�'*/  
               (byte_1 == 0xb4)                     || /*���������� ������ '�'*/  
               (byte_1 == 0xaa)                     || /*���������� ������ '�'*/  
               (byte_1 == 0xba)                        /*���������� ������ '�'*/  
              ) 
             ) 
            )
            &&  
            (
             (byte_2 >= 0x20) && (byte_2 <= 0x7e) || /*�������� ������� � �����*/
             (byte_2 >= 0xc0) && (byte_2 <= 0xff) || /*�������� ������� �������*/
             (byte_2 == 0xa8)                     || /*��������� ������ '�'*/  
             (byte_2 == 0xb8)                     ||   /*��������� ������ '�'*/  
             (
              (target_label->language == LANGUAGE_UA) &&
              (
               (byte_2 == 0xaf)                     || /*���������� ������ '�'*/  
               (byte_2 == 0xbf)                     || /*���������� ������ '�'*/  
               (byte_2 == 0xa5)                     || /*���������� ������ '�'*/  
               (byte_2 == 0xb4)                     || /*���������� ������ '�'*/  
               (byte_2 == 0xaa)                     || /*���������� ������ '�'*/  
               (byte_2 == 0xba)                        /*���������� ������ '�'*/  
              ) 
             )   
            )
           )
        {
          target_label->name_of_cell[two_char_index    ] = byte_1;
          target_label->name_of_cell[two_char_index + 1] = byte_2;
        }
        else
          error = ERROR_ILLEGAL_DATA_VALUE;
        
        break;
      }
    default: break;
    }
  }
  else if ((address_data >= M_ADDRESS_FIRST_TIME_AND_DATA) && (address_data <= M_ADDRESS_LAST_TIME_AND_DATA))
  {
    temp_value = data & 0xff;
    unsigned int tetrad_low = (temp_value & 0xf), tetrad_high = (temp_value >> 4);
    
    //����������� �����, ���������, ���� ����. ���� ��������� �� 0x10, � 10 = 0xA � �� ���� 0xA ���� ��������� � ������ ������ RTC
    if((tetrad_low <= 0x9) && (tetrad_high <= 0x9))
    {
      switch (address_data)
      {
      case MA_YEAR:
        {
          time_edit[6] = temp_value;
          break;
        }
      case MA_MONTH:
        {
          time_edit[5] = temp_value;
          break;
        }
      case MA_DAY:
        {
          time_edit[4] = temp_value;
          break;
        }
      case MA_HOUR:
        {
          time_edit[3] = temp_value;
          break;
        }
      case MA_MINUTE:
        {
          time_edit[2] = temp_value;
          break;
        }
      case MA_SECOND:
        {
          time_edit[1] = temp_value;
          break;
        }
      case MA_MILISECOND:
        {
          time_edit[0] = temp_value;
          break;
        }
      default: break;
      }
    }
    else
      error = ERROR_ILLEGAL_DATA_VALUE;
  }
  else if ((address_data >= M_ADDRESS_FIRST_DI_RANG) && (address_data <= M_ADDRESS_LAST_DI_RANG))
  {
    //����� ���������� ���������� �����
    
    //��������, ���� ���� ����� ������ ����� ���������� ��������
    unsigned int number_input = (address_data - M_ADDRESS_FIRST_DI_RANG)>>VAGA_MAX_FUNCTIONS_IN_INPUT;
    
    if(number_input < NUMBER_INPUTS)
    {
      error = save_new_rang_inputs_from_gmm(number_input, (((address_data -  M_ADDRESS_FIRST_DI_RANG) & (MAX_FUNCTIONS_IN_INPUT - 1)) + 1), data, method_setting);
    }
  }
  else if ((address_data >= M_ADDRESS_FIRST_DO_RANG) && (address_data <= M_ADDRESS_LAST_DO_RANG))
  {
    //����� ���������� ���������� ������
    
    //��������, ���� ����� ����� ������ ����� ���������� ��������
    unsigned int number_output = (address_data - M_ADDRESS_FIRST_DO_RANG)>>VAGA_MAX_FUNCTIONS_IN_OUTPUT;
    
    if(number_output < NUMBER_OUTPUTS)
    {
      error = save_new_rang_oldr_from_gmm(number_output, (((address_data -  M_ADDRESS_FIRST_DO_RANG) & (MAX_FUNCTIONS_IN_OUTPUT - 1)) + 1), SOURCE_OUTPUTS_RANG, data, method_setting);
    }
  }
  else if ((address_data >= M_ADDRESS_FIRST_LED_RANG) && (address_data <= M_ADDRESS_LAST_LED_RANG))
  {
    //����� ���������� ��������������
    
    //��������, ���� ������������� ����� ������ ����� ���������� ��������
    unsigned int number_led = (address_data - M_ADDRESS_FIRST_LED_RANG)>>VAGA_MAX_FUNCTIONS_IN_LED;
    
    if(number_led < NUMBER_LEDS)
    {
      error = save_new_rang_oldr_from_gmm(number_led, (((address_data -  M_ADDRESS_FIRST_LED_RANG) & (MAX_FUNCTIONS_IN_LED - 1)) + 1), SOURCE_LEDS_RANG, data, method_setting);
    }
  }
  else if ((address_data >=  M_ADDRESS_FIRST_DF_RANG) && (address_data <= M_ADDRESS_LAST_DF_RANG))
  {
    //����� ���������� 0-�������
    
    //��������, ��� 0-������� ����� ������ ����� ���������� ��������
    unsigned int number_df_mul_3 = (address_data -  M_ADDRESS_FIRST_DF_RANG)>>VAGA_MAX_FUNCTIONS_IN_DF;
    
    if(number_df_mul_3 <  (NUMBER_DEFINED_FUNCTIONS*3))
    {
      error = save_new_rang_oldr_from_gmm((number_df_mul_3 / 3), (((address_data -  M_ADDRESS_FIRST_DF_RANG) & (MAX_FUNCTIONS_IN_DF - 1)) + 1), (SOURCE_DF_PLUS_RANG + (number_df_mul_3 % 3)), data, method_setting);
    }
  }
  else if ((address_data >= M_ADDRESS_FIRST_DB_RANG) && (address_data <= M_ADDRESS_LAST_DB_RANG))
  {
    //����� ���������� �������������� ������
    
    //��������, ��� �-������ ����� ������ ����� ���������� ��������
    unsigned int number_button = (address_data - M_ADDRESS_FIRST_DB_RANG)>>VAGA_MAX_FUNCTIONS_IN_DB;
    
    if(number_button < NUMBER_DEFINED_BUTTONS)
    {
      error = save_new_rang_buttons_from_gmm(number_button, (((address_data -  M_ADDRESS_FIRST_DB_RANG) & (MAX_FUNCTIONS_IN_DB - 1)) + 1), data, method_setting);
    }
  }
  else if ((address_data >= M_ADDRESS_FIRST_DT_RANG) && (address_data <= M_ADDRESS_LAST_DT_RANG))
  {
    //����� ���������� ��������
    
    //���������, ���� ������� ����� ������ ����� ���������� ��������
    unsigned int number_defined_triggers = (address_data - M_ADDRESS_FIRST_DT_RANG) / MAX_FUNCTIONS_IN_DT;
    
    if(number_defined_triggers < (NUMBER_DEFINED_TRIGGERS << 2))
    {
      
      error = save_new_rang_oldr_from_gmm((number_defined_triggers >> 2),
                     (((address_data -  M_ADDRESS_FIRST_DT_RANG) % MAX_FUNCTIONS_IN_DT) + 1),
                     SOURCE_SET_DT_PLUS_RANG + (number_defined_triggers % 4), data, method_setting);
    }
  }
  else if ((address_data >= M_ADDRESS_FIRST_SETPOINTS_RANG_AR) && (address_data <= M_ADDRESS_LAST_SETPOINTS_RANG_AR))
  {
    //����� ���������� ����������� ����������
    
    error = save_new_rang_oldr_from_gmm(0, (((address_data - M_ADDRESS_FIRST_SETPOINTS_RANG_AR) & (MAX_FUNCTIONS_IN_AREG - 1)) + 1), SOURCE_AR_RANG, data, method_setting);
  }
  else if ((address_data == MA_PREFAULT_INTERVAL_AR) || (address_data == MA_POSTFAULT_INTERVAL_AR))
  {
    //����� ������ ����������� �/��� ������������� ������ ����������� ����������
    unsigned int modified_value = 0;
    unsigned int semaphore_read_state_ar_record_copy = semaphore_read_state_ar_record;
    int state_ar_record_copy = state_ar_record;

    /*������������ ������� - ���� ����� ������ � ����, �� ���� ������ ������ ���� 
    ���� �� ��� - �� �� ��� ���� ������������ ����� ����� �������� �� �����, ���� � ��� ��� ���� �����,
    �� �� �� �������������� �, �������, ��������� ������ ����������� ���������� �� �����*/
    semaphore_read_state_ar_record = 1;
      
    if (
        (state_ar_record == STATE_AR_NO_RECORD      ) ||
        (state_ar_record == STATE_AR_TEMPORARY_BLOCK)
       )   
    {
      /*�� ����� ������ �� ��� ����� �������� ����������� ��������� �������,
      ���� ��� ���� ������� ��������� ��������� ������������ ���� ������
      ����������� ���������� � ������������ �����*/
      state_ar_record = STATE_AR_TEMPORARY_BLOCK; 
      
      temp_value = data*20; //���������� ������� ������ ���������� ������� � ���������

      //������������ ��� ��������
      if (address_data == MA_PREFAULT_INTERVAL_AR)
      {
        //������ ����������� ������
        if ((temp_value >= TIMEOUT_PREFAULT_MIN) && (temp_value <= TIMEOUT_PREFAULT_MAX))
        {
          if (target_label->prefault_number_periods != data)
          {
            target_label->prefault_number_periods = data; //� ������� ��������� �������� �� ���������, � ������� ������
            modified_value = 0xff;
          }
        }
        else
          error = ERROR_ILLEGAL_DATA_VALUE;
      }
      else if (address_data == MA_POSTFAULT_INTERVAL_AR)
      {
        //������ ������������� ������
        if ((temp_value >= TIMEOUT_POSTFAULT_MIN) && (temp_value <= TIMEOUT_POSTFAULT_MAX))
        {
          if (target_label->postfault_number_periods != data)
          {
            target_label->postfault_number_periods = data; //� ������� ��������� �������� �� ���������, � ������� ������
            modified_value = 0xff;
          }
        }
        else
          error = ERROR_ILLEGAL_DATA_VALUE;
      }
        
      if (method_setting == SET_DATA_IMMEDITATE)
      {
        //�������� 䳿 �� ��� ������� �������� ����������� ����������, ���� ��� �� ��� �� ���� ����������� �������
        if (error == 0)
        {
          if (modified_value != 0) actions_after_changing_tiomouts_ar();
        }

        //������������ ������ ����������� ����������
        state_ar_record = STATE_AR_NO_RECORD;
      }
      else
      {
        /*
        ����� �� �������� �������� ���� ����, �� ���� ������ ������������ � current_settings ���������
        
        � �������, ���� ���� �������� ������� �� ���������, �� ���������� �� ���� �����, ��� �� ����
        ���� - ������� �������� �������� ����� ������ ����������� ����������, ��
        ���� �� � ����� ���� ��������� �� ������ ��� ������� 
        STATE_AR_NO_RECORD       - ���� �� ����� ���� ������� 16 �� ����� ������ �������� ��� ������ ��������� �������� ����������� ����������
        STATE_AR_TEMPORARY_BLOCK - ���� �� ����� ���� ������� 16    ����� ����   �������� ��� ������ ��������� �������� ����������� ����������
        */
        
        if (modified_value == 0) state_ar_record = state_ar_record_copy;
      }
    }
    else
    {
      //�������� ��������� ����������, �� ��� ������ ����������� ����������
      error = ERROR_SLAVE_DEVICE_BUSY;
    }

    if (method_setting == SET_DATA_IMMEDITATE)
    {
      //������ �������
      semaphore_read_state_ar_record = 0;
    }
    else
    {
      /*
      ����� �� �������� �������� ���� ����, �� ���� ������ ������������ � current_settings ���������
        
      � �������, ���� ���� �������� ������� �� ���������, �� ���������� �� ���� �����, ��� �� ����
      ���� - ������� �������� �������� semaphore_read_state_ar_record, ��
      ���� �� � ����� ���� ��������� �� ������ ��� ������� 
      0    - ���� �� ����� ���� ������� 16 �� ����� ������ �������� ��� ������ ��������� �������� ����������� ����������
      �� 0 - ���� �� ����� ���� ������� 16    ����� ����   �������� ��� ������ ��������� �������� ����������� ����������
      */
      
       if (modified_value == 0) semaphore_read_state_ar_record = semaphore_read_state_ar_record_copy;
    }
  }
  else if (address_data == MA_CURRENT_NUMBER_RECORD_AR)
  {
    if ((type_interface != USB_RECUEST) && (type_interface != RS485_RECUEST))
    {
      //���������� ������ ���� �� ���� � �����
      error = ERROR_SLAVE_DEVICE_FAILURE;
    }
    else if (
             ((clean_rejestrators & CLEAN_AR) != 0) ||
             (
              ((type_interface == USB_RECUEST  ) && ((control_tasks_dataflash & TASK_MAMORY_READ_DATAFLASH_FOR_AR_USB  ) != 0)) ||
              ((type_interface == RS485_RECUEST) && ((control_tasks_dataflash & TASK_MAMORY_READ_DATAFLASH_FOR_AR_RS485) != 0))
             ) 
            )
    {
      /*
      ����� ��� ���������� ��� ���������� ������ ����������� ����������, 
      ��� ������� ����, ���� �� �������� � ��������� �����������
      */
      error = ERROR_SLAVE_DEVICE_BUSY;
    }
    else if (
             (data < info_rejestrator_ar.number_records) &&
             (data < max_number_records_ar             ) /*��� ���������� �� ����� �� ������������� ������ ������ ������*/
            )
    {
      if (
          (type_interface == USB_RECUEST  ) ||
          (type_interface == RS485_RECUEST)
         )   
      {
        unsigned int *point_to_number_record_of_ar;
        int *point_to_first_number_time_sample, *point_to_last_number_time_sample;
        
        if (type_interface == USB_RECUEST)
        {
          point_to_number_record_of_ar = &number_record_of_ar_for_USB;
          point_to_first_number_time_sample = &first_number_time_sample_for_USB;
          point_to_last_number_time_sample = &last_number_time_sample_for_USB;
        }
        else
        {
          point_to_number_record_of_ar = &number_record_of_ar_for_RS485;
          point_to_first_number_time_sample = &first_number_time_sample_for_RS485;
          point_to_last_number_time_sample = &last_number_time_sample_for_RS485;
        }
        
        //������������ ����� ������ ����������� ���������� ��� �������
        *point_to_number_record_of_ar = data;
        //������ ������� ������� ����������� ���������� ���  ����������

        //����������� ������� ��������� ������ ������ ������ � ������, ������ �������, ������� ���� 
        *point_to_first_number_time_sample = -1;
        int last_number_time_sample_tmp = (SIZE_PAGE_DATAFLASH_2 - sizeof(__HEADER_AR))/((NUMBER_ANALOG_CANALES + number_word_digital_part_ar)*sizeof(short int));
        int max_number_time_sample = (current_settings.prefault_number_periods + current_settings.postfault_number_periods) << VAGA_NUMBER_POINT_AR;
        if (last_number_time_sample_tmp <= max_number_time_sample)
        {
          *point_to_last_number_time_sample = last_number_time_sample_tmp - 1;//����� ���������� �������� ���� �������
        }
        else
        {
          *point_to_last_number_time_sample = max_number_time_sample - 1;
        }

        //������ ������� ������� ��� � ����� ���'��
        if (type_interface == USB_RECUEST)
          control_tasks_dataflash |= TASK_MAMORY_READ_DATAFLASH_FOR_AR_USB;
        else
          control_tasks_dataflash |= TASK_MAMORY_READ_DATAFLASH_FOR_AR_RS485;
      }
      else
      {
        //���������� ������ ���� �� ���� � �����
        error = ERROR_SLAVE_DEVICE_FAILURE;
      }
    }
    else
      error = ERROR_ILLEGAL_DATA_VALUE;
  }
  else if ((address_data >= M_ADDRESS_FIRST_SETPOINTS_RANG_DR) && (address_data <= M_ADDRESS_LAST_SETPOINTS_RANG_DR))
  {
    //����� ���������� ����������� ����������
    
    error = save_new_rang_oldr_from_gmm(0, (((address_data - M_ADDRESS_FIRST_SETPOINTS_RANG_DR) & (MAX_FUNCTIONS_IN_DREG - 1)) + 1), SOURCE_DR_RANG, data, method_setting);
  }
  else if (address_data == MA_CURRENT_NUMBER_RECORD_DR)
  {
    if ((type_interface != USB_RECUEST) && (type_interface != RS485_RECUEST))
    {
      //���������� ������ ���� �� ���� � �����
      error = ERROR_SLAVE_DEVICE_FAILURE;
    }
    else if (
             ((clean_rejestrators & CLEAN_DR) != 0) ||
             (
              ((type_interface == USB_RECUEST  ) && ((control_tasks_dataflash & TASK_MAMORY_READ_DATAFLASH_FOR_DR_USB  ) != 0)) ||
              ((type_interface == RS485_RECUEST) && ((control_tasks_dataflash & TASK_MAMORY_READ_DATAFLASH_FOR_DR_RS485) != 0))
             ) 
            )
    {
      /*
      ����� ��� ���������� ��� ���������� ������ ����������� ����������, 
      ��� ������� ����, ���� �� �������� � ��������� �����������
      */
      error = ERROR_SLAVE_DEVICE_BUSY;
    }
    else if (
             (data < info_rejestrator_dr.number_records) &&
             (data < MAX_NUMBER_RECORDS_INTO_DR        ) /*��� ���������� �� ����� �� ������������� ������ ������ ������*/
            )
    {
      if (type_interface == USB_RECUEST)
      {
        //������������ ����� ������ ����������� ���������� ��� ������� ����� ��������� USB
        number_record_of_dr_for_USB = data;
        //������ ������� ������� ����������� ���������� ��� ���������� USB

        //����������� ����� ������� ������
        part_reading_dr_from_dataflash_for_USB = 0;
        //������ ������� ������� ��� � ����� ���'��
        control_tasks_dataflash |= TASK_MAMORY_READ_DATAFLASH_FOR_DR_USB;
      }
      else if (type_interface == RS485_RECUEST)
      {
        //������������ ����� ������ ����������� ���������� ��� ������� ����� ��������� RS-485
        number_record_of_dr_for_RS485 = data;
        //������ ������� ������� ����������� ���������� ��� ���������� RS-485

        //����������� ����� ������� ������
        part_reading_dr_from_dataflash_for_RS485 = 0;
        //������ ������� ������� ��� � ����� ���'��
        control_tasks_dataflash |= TASK_MAMORY_READ_DATAFLASH_FOR_DR_RS485;
      }
      else
      {
        //���������� ������ ���� �� ���� � �����
        error = ERROR_SLAVE_DEVICE_FAILURE;
      }
    }
    else
      error = ERROR_ILLEGAL_DATA_VALUE;
  }
  else if (address_data == MA_CLEAR_NUMBER_RECORD_AR)
  {
    if (data != CMD_WORD_CLEAR_AR)
    {
      //��� �������� ����������� ���������� �� ���� ���������� �� ����� ����� ��������� �����
      error = ERROR_ILLEGAL_DATA_VALUE;
    }
    else if (
             (current_ekran.current_level == EKRAN_DATA_LADEL_AR)
             ||  
             (state_ar_record             != STATE_AR_NO_RECORD )
             ||  
             (
              (control_tasks_dataflash & (
                                          TASK_MAMORY_PART_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_AR |
                                          TASK_MAMORY_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_AR      |
                                          TASK_MAMORY_READ_DATAFLASH_FOR_AR_USB                         |
                                          TASK_MAMORY_READ_DATAFLASH_FOR_AR_RS485                       |
                                          TASK_MAMORY_READ_DATAFLASH_FOR_AR_MENU
                                         )
              ) != 0
             )
             ||
             ((clean_rejestrators & CLEAN_AR) != 0)  
            ) 
    {
      //����� ��� �����/���������� ����������� ����������, ��� ������� ���� ����������� ������, ���� �� �������� � ��������� �����������
      error = ERROR_SLAVE_DEVICE_BUSY;
    }
    else
    {
      //�������, �� ����� �������� ���������� ���������
      clean_rejestrators |= CLEAN_AR;
    }
  }
  else if (address_data == MA_CLEAR_NUMBER_RECORD_DR)
  {
    if (data != CMD_WORD_CLEAR_DR)
    {
      //��� �������� ����������� ���������� �� ���� ���������� �� ����� ����� ��������� �����
      error = ERROR_ILLEGAL_DATA_VALUE;
    }
    else if (
             (current_ekran.current_level == EKRAN_TITLES_DIGITAL_REGISTRATOR)
             ||  
             (current_ekran.current_level == EKRAN_DATA_LADEL_DR             )
             ||  
             (current_ekran.current_level == EKRAN_CHANGES_SIGNALS_DR        )
             ||  
             (current_ekran.current_level == EKRAN_TITLE_MAX_VALUES          )
             ||  
             (current_ekran.current_level == EKRAN_MAX_VALUES                )
             ||  
             (
              (control_tasks_dataflash & (
                                          TASK_MAMORY_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_DR | 
                                          TASK_MAMORY_READ_DATAFLASH_FOR_DR_USB                    |
                                          TASK_MAMORY_READ_DATAFLASH_FOR_DR_RS485                  |
                                          TASK_MAMORY_READ_DATAFLASH_FOR_DR_MENU
                                         )
              ) != 0
             )
             ||
             ((clean_rejestrators & CLEAN_DR) != 0)  
            ) 
    {
      //����� ��� �����/���������� ����������� ����������, ��� ������� ���� ����������� ������, ���� �� �������� � ��������� �����������
      error = ERROR_SLAVE_DEVICE_BUSY;
    }
    else
    {
      //�������, �� ����� �������� ����������� ����������
      clean_rejestrators |= CLEAN_DR;
    }
  }
  else if (address_data == MA_CLEAR_NUMBER_RECORD_PR_ERR)
  {
    if (
        (current_ekran.current_level == EKRAN_TITLES_PR_ERR_REGISTRATOR )
        ||  
        (current_ekran.current_level == EKRAN_DATA_LADEL_PR_ERR         )
        ||  
        (current_ekran.current_level == EKRAN_CHANGES_DIAGNOSTICS_PR_ERR)
        ||  
        (
         (control_tasks_dataflash & (
                                     TASK_WRITE_PR_ERR_RECORDS_INTO_DATAFLASH    |
                                     TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_USB   |
                                     TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_RS485 |
                                     TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_MENU
                                    )
         ) != 0
        )
        ||
        ((clean_rejestrators & CLEAN_PR_ERR) != 0)  
       ) 
    {
      //����� ��� ���������� ��� ���������� ������ ���������� ���������� ����, ��� ������� ���� ����������� ������, ���� �� �������� � ��������� �����������
      error = ERROR_SLAVE_DEVICE_BUSY;
    }
    else
    {
      //�������, �� ����� �������� ��������� ���������� ����
      clean_rejestrators |= CLEAN_PR_ERR;
    }
  }
  else if (address_data == MA_CURRENT_NUMBER_RECORD_PR_ERR)
  {
    if ((type_interface != USB_RECUEST) && (type_interface != RS485_RECUEST))
    {
      //���������� ������ ���� �� ���� � �����
      error = ERROR_SLAVE_DEVICE_FAILURE;
    }
    else if (
             ((clean_rejestrators & CLEAN_PR_ERR) != 0) ||
             (
              ((type_interface == USB_RECUEST  ) && ((control_tasks_dataflash & TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_USB  ) != 0)) ||
              ((type_interface == RS485_RECUEST) && ((control_tasks_dataflash & TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_RS485) != 0))
             ) 
            )
    {
      /*
      ����� ��� ���������� ��� ���������� ������ ���������� ���������� ����, 
      ��� ������� ����, ���� �� �������� � ��������� �����������
      */
      error = ERROR_SLAVE_DEVICE_BUSY;
    }
    else if (
             (data < info_rejestrator_pr_err.number_records) &&
             (data < MAX_NUMBER_RECORDS_INTO_PR_ERR        ) /*��� ���������� �� ����� �� ������������� ������ ������ ������*/
            )
    {
      if (type_interface == USB_RECUEST)
      {
        //������������ ����� ������ ���������� ���������� ���� ��� ������� ����� ��������� USB
        number_record_of_pr_err_into_USB = data;
        //������ ������� ������� ���������� ���������� ���� ���  ���������� USB

        //������ ������� ������� ��� � ����� ���'�� ��� USB
        control_tasks_dataflash |= TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_USB;
      }
      else if (type_interface == RS485_RECUEST)
      {
        //������������ ����� ������ ���������� ���������� ���� ��� ������� ����� ��������� RS-485
        number_record_of_pr_err_into_RS485 = data;
        //������ ������� ������� ���������� ���������� ���� ���  ���������� RS-485

        //������ ������� ������� ��� � ����� ���'�� ��� RS-485
        control_tasks_dataflash |= TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_RS485;
      }
      else
      {
        //���������� ������ ���� �� ���� � �����
        error = ERROR_SLAVE_DEVICE_FAILURE;
      }
    }
    else
      error = ERROR_ILLEGAL_DATA_VALUE;
  }
  else if (address_data == MA_SET_SERIAL_NUMBER)
  {
    if (password_ustuvannja == 0x1978)
    {
      //��� �������� ������
      if (method_setting == SET_DATA_IMMEDITATE)
        serial_number_dev = data;
      else
        edit_serial_number_dev = data;
    }
    else 
    {
      /*� ��� ����������� ��� ������� ��� ������� ��������� ����� ��� ���� ������ ������ � �����������, ��� �������� ��������� ����������������� ������ ���������*/
      error = ERROR_ILLEGAL_DATA_ADDRESS;
    }    
  }
  else if (address_data == MA_POSSIBILITY_USTUVANNJA)
  {
    if (password_ustuvannja != 0x1978)
    {
      //������������ ������-������� ��������� ������� ����� ���� ���������� ����� 0x1978
      if (data == 0x1978) password_ustuvannja = 0x1978;
      else
      {
        /*� ��� ����������� ��� ������� ��� ������� ��������� ����� ��� ���� ������ ������ � �����������, ��� �������� ��������� ����������������� ������ ���������*/
        error = ERROR_ILLEGAL_DATA_ADDRESS;
      }
    }
    else
    {
      //����������� ����-����� ����� (��� �����, ��� ���������� ���������) ��������� �� �������� ���������� ���������
      if (data != 0x1978) password_ustuvannja = 0;
    }
  }
  else if ((address_data >= MA_ADDRESS_FIRST_USTUVANNJA ) && (address_data <= MA_ADDRESS_LAST_USTUVANNJA))
  {
    //���������
    if (password_ustuvannja == 0x1978)
    {
      if (method_setting == SET_DATA_IMMEDITATE)
        ustuvannja[address_data - MA_ADDRESS_FIRST_USTUVANNJA  ]  = data;
      else
        edit_ustuvannja[address_data - MA_ADDRESS_FIRST_USTUVANNJA  ]  = data;
    }
    else 
    {
      /*� ��� ����������� ��� ������� ��� ������� ��������� ����� ��� ���� ������ ������ � �����������, ��� �������� ��������� ����������������� ������ ���������*/
      error = ERROR_ILLEGAL_DATA_ADDRESS;
    }
  }
  else if ((address_data >= MA_ADDRESS_FIRST_PHI_USTUVANNJA ) && (address_data <= MA_ADDRESS_LAST_PHI_USTUVANNJA))
  {
    //������ ���������
    if (password_ustuvannja == 0x1978)
    {
      unsigned int index = address_data - MA_ADDRESS_FIRST_PHI_USTUVANNJA; 
      int phi_tmp = (short int)data;
      float phi_radian_tmp = PI*((float)phi_tmp)/1800.0f; /*������� ��� �������������� � ������ �� ������� ����� ������, �� ��� ����, ��� �������� ��������� ������ - ����� ������� �� �� 180 � �� 1800= 180�10 */
      if (method_setting == SET_DATA_IMMEDITATE)
      {
        phi_ustuvannja[index] = phi_tmp;
        phi_ustuvannja_sin_cos[2*index    ] = arm_sin_f32(phi_radian_tmp);
        phi_ustuvannja_sin_cos[2*index + 1] = arm_cos_f32(phi_radian_tmp);
      }
      else
      {
        phi_edit_ustuvannja[index] = phi_tmp;
        phi_edit_ustuvannja_sin_cos[2*index    ] = arm_sin_f32(phi_radian_tmp);
        phi_edit_ustuvannja_sin_cos[2*index + 1] = arm_cos_f32(phi_radian_tmp);
      }
    }
    else 
    {
      /*� ��� ����������� ��� ������� ��� ������� ��������� ����� ��� ���� ������ ������ � �����������, ��� �������� ��������� ����������������� ������ ���������*/
      error = ERROR_ILLEGAL_DATA_ADDRESS;
    }
  }
  else if (address_data == MA_LSW_ADR_MEMORY_TO_WRITE)
  {
    registers_address_write = (registers_address_write & 0xffff0000) + (data);
  }
  else if (address_data == MA_MSW_ADR_MEMORY_TO_WRITE)
  {
   registers_address_write = (registers_address_write & 0xffff) + (data << 16);
  }
  else if (address_data == MA_LSW_DATA_MEMORY_TO_WRITE)
  {
    unsigned int *label;

    data_write_to_memory = (data_write_to_memory & 0xffff0000) + (data);
    label = (unsigned int *)(registers_address_write);
    *label = data_write_to_memory;
  }
  else if (address_data == MA_MSW_DATA_MEMORY_TO_WRITE)
  {
    data_write_to_memory = data << 16;
  }
  else if (address_data == MA_NB_REG_FROM_MEM_READ)
  {
    number_registers_read = data;
  }
  else if (address_data == MA_LSW_ADR_MEMORY_TO_READ)
  {
    unsigned int index;
    unsigned short int *label;

    registers_address_read = (registers_address_read & 0xffff0000) + (data);
    label = (unsigned short int *)(registers_address_read);
	  
    for (index = 0; index<number_registers_read; index++)
    {	
      registers_values[index] = *(label++);
    }
  }
  else if (address_data == MA_MSW_ADR_MEMORY_TO_READ)
  {
    registers_address_read = (registers_address_read & 0xffff) + (data << 16);
  }
  else if (address_data == MA_PART_RECEIVE_DIG_OSCILOGRAPH)
  {
    part_transmit_carrent_data = data;
    if(part_transmit_carrent_data == 0)
    {
      action_is_continued = true;
      command_to_receive_current_data = true;
    }
  }
  else if (address_data == MA_DEFAULT_SETTINGS)
  {
    if (data != CMD_WORD_SET_DEFAULT_SETTINGS)
    {
      //��� ������������ �������� ������������ �� ���� ��������� �� ����� ����� ��������� ����� - ������ �����������, �� ���� ������ ������ �� ���� (���������� ����� ���������� �� ����������������� ���������� ����� ���'��)
      error = ERROR_ILLEGAL_DATA_ADDRESS;
    }
    else if (current_ekran.current_level != EKRAN_MAIN)
    {
      //̳������� ������������ ����� ������������� ����� � ��������� ����
      error = ERROR_SLAVE_DEVICE_BUSY;
    }
    else
    {
      /*
      ϳ� ��� ������������ ��������� ��������� ���� ������ ������ ������ 
      ����������� � ������������� ������ ����������� ���������� - ���� ����� �� ��������
      �� �� ������ �� �������� ��������
      */
      
      /*������������ ������� - ���� ����� ������ � ����, �� ���� ������ ������ ���� 
      ���� �� ��� - �� �� ��� ���� ������������ ����� ����� �������� �� �����, ���� � ��� ��� ���� �����,
      �� �� �� �������������� �, �������, ��������� ������ ����������� ���������� �� �����*/
      semaphore_read_state_ar_record = 1;
      
      if (state_ar_record == STATE_AR_NO_RECORD)
      {
        /*�� ����� ������ �� ��� ����� �������� ����������� ��������� �������,
        ���� ��� ���� ������� ��������� ��������� ������������ ���� ������
        ����������� ���������� � ������������ �����*/
        state_ar_record = STATE_AR_TEMPORARY_BLOCK; 
      
        //������� ��������� � "������� �������� ��������"
        min_settings(target_label);
        
        if (method_setting == SET_DATA_IMMEDITATE)
        {
          //�������� 䳿 �� ��� ������� �������� ����������� ����������
          actions_after_changing_tiomouts_ar();

          //������������ ������ ����������� ����������
          state_ar_record = STATE_AR_NO_RECORD;
        }
        /*
        ����� �� �������� �������� ���� ����, �� ���� ������ ������������ � current_settings ���������
        */
      }
      else
      {
        //�������� ��������� ����������, �� ��� ������ ����������� ����������
        error = ERROR_SLAVE_DEVICE_BUSY;
      }

      if (method_setting == SET_DATA_IMMEDITATE)
      {
        //������ �������
        semaphore_read_state_ar_record = 0;
      }
      /*
      ����� �� �������� �������� ���� ����, �� ���� ������ ������������ � current_settings ���������
      */
    }
  }
  else if (address_data == MA_TEST_WATCHDOGS)
  {
    if (data != CMD_TEST_EXTERNAL_WATCHDOG)
    {
      //��� ���������� watchdog ����� ������� ��������� ����� ���� ���������� - ������ �����������, �� ���� ������ ������ �� ���� (���������� ����� ���������� �� ����������������� ���������� ����� ���'��)
      error = ERROR_ILLEGAL_DATA_ADDRESS;
    }
    else
    {
      //�������� ������� �� ���������
      test_watchdogs = data;
    }
  }
  else if (address_data == MA_CMD_RESET_RESURS_MIN_MAX)
  {
    //������� ��������� ��� �������
    restart_resurs_count = 0xff;/*��������� �������� ����������� ���������*/
  }
  else if (address_data == MA_CLEAR_ENERGY)
  {
    if (data != CMD_WORD_CLEAR_ENERGY)
    {
      //��� �������� ������ ��������� ����� ������� ��������� ����� - ������ �����������, �� ���� ������ ������ �� ���� (���������� ����� ���������� �� ����������������� ���������� ����� ���'��)
      error = ERROR_ILLEGAL_DATA_ADDRESS;
    }
    else
    {
      //�������� ������� �� ���������
      clean_energy = 0xff;
    }
  }
  else error = ERROR_ILLEGAL_DATA_ADDRESS;

  return error;
}
/***********************************************************************************/

/***********************************************************************************/
//������� �����
/***********************************************************************************/
inline unsigned int Get_data_file(unsigned char* input_data, unsigned char* output_data, unsigned int* total_number_answer, unsigned int type_interface)
{
  unsigned int error = 0;
  if( *(input_data + 0) == 0x6)
  {
    unsigned int number_file, number_record, length;
    number_file   = ((*(input_data + 1)) << 8) + (*(input_data + 2));
    number_record = ((*(input_data + 3)) << 8) + (*(input_data + 4));
    length        = ((*(input_data + 5)) << 8) + (*(input_data + 6));
    
    unsigned int number_answer_local = (length << 1) + 1;
    
    *total_number_answer += (number_answer_local + 1); 

    if ((type_interface != USB_RECUEST) && (type_interface != RS485_RECUEST))
    {
      //���������� ������ ���� �� ���� � �����
      error = ERROR_SLAVE_DEVICE_FAILURE;
    }
    else if (
             (number_file == 0)
             ||
             (
              (number_file >= 1) && 
              (number_file <= 4) && 
              (
               ((type_interface == USB_RECUEST  ) && (number_record_of_ar_for_USB   == 0xffff)) ||
               ((type_interface == RS485_RECUEST) && (number_record_of_ar_for_RS485 == 0xffff))
              )   
             )
             ||  
             (
              (number_file >= 5) && 
              (number_file <= 6) && 
              (
               ((type_interface == USB_RECUEST  ) && (number_record_of_dr_for_USB   == 0xffff)) ||
               ((type_interface == RS485_RECUEST) && (number_record_of_dr_for_RS485 == 0xffff))
              )   
             )
             ||  
             (number_file > 6)
            )
    {
      //������� ����� �����, ��� �� ������ ������� ����������� ���������� ������
      error = ERROR_ILLEGAL_DATA_ADDRESS;
    }
    else if (
             (number_file >= 1) &&
             (number_file <= 4) &&
             (
              (
               (state_ar_record != STATE_AR_NO_RECORD      ) &&
               (state_ar_record != STATE_AR_TEMPORARY_BLOCK)
              )
              ||
              ((clean_rejestrators & CLEAN_AR) != 0)  
              ||  
              (
               (control_tasks_dataflash & (
                                           TASK_ERASE_DATAFLASH_2                                        |
                                           TASK_MAMORY_PART_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_AR |
                                           TASK_MAMORY_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_AR
                                          )
               ) != 0
              )
             )
            )    
    {
      //����� ��� �������� ������/�������� ��� ���������� ����������, ��� ���� ������� ����� (������������ ����� ��������� 20 �), ���� ������� ����������� ���������� � ��������� ����������
      error = ERROR_SLAVE_DEVICE_BUSY;
      /*
      ��� �� �� ���������� ����� �� ����������� �� TASK_MAMORY_READ_DATAFLASH_FOR_AR_INTERFACE,
      ��, �������, ������ � ����� � ����� ���� ����� ��������� �� �������, �� 
      ��������� ������������ ���������� �� ������� �������. ����� ��������� ������� � �����, �� �����
      ���������� � ��������� dataFlash
      */
    }
    else if (
             (number_file >= 5) &&
             (number_file <= 6) && 
             (
              (
               ((type_interface == USB_RECUEST  ) && ((control_tasks_dataflash & TASK_MAMORY_READ_DATAFLASH_FOR_DR_USB  ) != 0)) ||
               ((type_interface == RS485_RECUEST) && ((control_tasks_dataflash & TASK_MAMORY_READ_DATAFLASH_FOR_DR_RS485) != 0))
              ) 
              ||  
              ((clean_rejestrators & CLEAN_DR) != 0)
             )  
            )   
    {
      //����� ��� ���������� ��� ���������� ������ ����������� ����������, ���� �� �������� � ��������� �����������
      error = ERROR_SLAVE_DEVICE_BUSY;
    }
    else if ((*total_number_answer + 5) < 255)
    {
      *(output_data + 0 ) = number_answer_local;
      *(output_data + 1 ) = 0x6;
      //������ ����� ��� ����� ������

      int temp_data;
      switch (number_file)
      {
      case 1:
        {
          //*************************************
          //��������� ��� ����������� ����������
          //*************************************
          
          //����������� ������� ������� ���� (�� ����� �� ���� ������� � ���������� ������ �������� ������� ��� �������� ������������ ����������� ����������)
          int max_number_time_sample = (current_settings.prefault_number_periods + current_settings.postfault_number_periods) << VAGA_NUMBER_POINT_AR;
          
          //������� ���� ����������� ����������� ����� ��� ����������� ����������
          while (
                 ((type_interface == USB_RECUEST  ) && ((control_tasks_dataflash & TASK_MAMORY_READ_DATAFLASH_FOR_AR_USB  ) != 0)) ||
                 ((type_interface == RS485_RECUEST) && ((control_tasks_dataflash & TASK_MAMORY_READ_DATAFLASH_FOR_AR_RS485) != 0))
                )
          {
            //��� ����� ���� ������������� Watchdog, �� ��� ����� ���� ��������� ������� ������ � ���
          }
          
          int *point_to_first_number_time_sample, *point_to_last_number_time_sample;
          if (type_interface == USB_RECUEST)
          {
            point_to_first_number_time_sample = &first_number_time_sample_for_USB;
            point_to_last_number_time_sample  = &last_number_time_sample_for_USB;
          }
          else
          {
            point_to_first_number_time_sample = &first_number_time_sample_for_RS485;
            point_to_last_number_time_sample  = &last_number_time_sample_for_RS485;
          }

          //���������� �� ������� ��������� ����������� ����������
          if ((*point_to_first_number_time_sample) != -1)
          {
            //����� �� ������������ ���������� ��������� ����������� ��������
              
            //����������� ������� ��������� ������ ������ ������ � ������, ������ �������, ������� ���� 
            *point_to_first_number_time_sample = -1;
            int last_number_time_sample_tmp = (SIZE_PAGE_DATAFLASH_2 - sizeof(__HEADER_AR))/((NUMBER_ANALOG_CANALES + number_word_digital_part_ar)*sizeof(short int));
            if (last_number_time_sample_tmp <= max_number_time_sample)
            {
              *point_to_last_number_time_sample = last_number_time_sample_tmp - 1;//����� ���������� �������� ���� �������
            }
            else
            {
              *point_to_last_number_time_sample = max_number_time_sample - 1;
            }

            //������ ������� ������� ��� � ����� ���'��
            if (type_interface == USB_RECUEST)
              control_tasks_dataflash |= TASK_MAMORY_READ_DATAFLASH_FOR_AR_USB;
            else
              control_tasks_dataflash |= TASK_MAMORY_READ_DATAFLASH_FOR_AR_RS485;
                
            //������� ���� ����������� ����������� ����� ��� ����������� ����������
            while (
                   ((type_interface == USB_RECUEST  ) && ((control_tasks_dataflash & TASK_MAMORY_READ_DATAFLASH_FOR_AR_USB  ) != 0)) ||
                   ((type_interface == RS485_RECUEST) && ((control_tasks_dataflash & TASK_MAMORY_READ_DATAFLASH_FOR_AR_RS485) != 0))
                  )   
            {
              //���� ����� ���� ������������� Watchdog, �� ��� ����� ���� ��������� ������� ������ � ���
            }
          }
              
          //���� �� ���� �����, �� ������� �� ��������� ����������� ���������� ��� ��������
          __HEADER_AR header_ar_tmp;
          /*
          � ������ ������ ��������� ������ � ��������� ���������� �����������.
          ��� �������� �� �� ������ ������ ��������� ��������� ����������� ����������
          ��� ����� ���� ��������� ������ ����
          */
          if (type_interface == USB_RECUEST)
            header_ar_tmp = *((__HEADER_AR*)buffer_for_USB_read_record_ar);
          else
            header_ar_tmp = *((__HEADER_AR*)buffer_for_RS485_read_record_ar);
              
          switch (number_record)
          {
          case 0:
            {
              if (length <= 10)
              {
                unsigned int i = 0;
                while (i < length)
                {
                  if (i < 8)
                  {
                    unsigned int index_cell;
                    
                    index_cell =  (i - 0)<<1;
                    temp_data  = header_ar_tmp.name_of_cell[ index_cell] | (header_ar_tmp.name_of_cell[ index_cell+1]<<8);
                  }
                  else if (i == 8)
                  {
                    //������� ����� �������� ������ ���� � ��� ����� (�������������� �� �����-�����������), ���� � ���� �� ������� ��� ������ � DataFlash � ����� ��������� ����������� ����������
                    temp_data = serial_number_dev & 0xffff;
                  }
                  else
                  {
                    temp_data = 1999;
                  }
                  *(output_data + 2 + 2*i) = (temp_data >> 8) & 0xff;
                  *(output_data + 3 + 2*i) = temp_data & 0xff;
                  i++;
                }
              }
              else error = ERROR_ILLEGAL_DATA_ADDRESS;
              break;
            }
          case 1:
            {
              if (length <= 3)
              {
                unsigned int i = 0;
                while (i < length)
                {
                  if (i == 0)
                  {
                    temp_data  = NUMBER_ANALOG_CANALES + NUMBER_TOTAL_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG;
                  }
                  else if (i == 1)
                  {
                    temp_data = NUMBER_ANALOG_CANALES;
                  }
                  else
                  {
                    temp_data = NUMBER_TOTAL_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG;
                  }
                  *(output_data + 2 + 2*i) = (temp_data >> 8) & 0xff;
                  *(output_data + 3 + 2*i) = temp_data & 0xff;
                  i++;
                }
              }
              else error = ERROR_ILLEGAL_DATA_ADDRESS;
              break;
            }
          case 2:
          case 3:
          case 4:
          case 5:
          case 6:
          case 7:
          case 8:
          case 9:
            {
              if (length <= 27)
              {
                unsigned int phase_line        = header_ar_tmp.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_PHASE_LINE;
                unsigned int canal_3U0_Ubc_TN2 = header_ar_tmp.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_3U0_Ubc_TN2;
                unsigned int i = 0;
                while (i < length)
                {
                  if (i == 0)
                  {
                    //����� ������
                    temp_data = (number_record - 2) + 1;
                  }
                  else if ( i < 9)
                  {
                    //��������������� ������ - 16 ASCII �������
                    char idetyficator[NUMBER_ANALOG_CANALES][16] = {
                    "3I0             ",
                    "Ia              ",
                    "Ic              ",
                    "                ",
                    "                ",
                    "                ",
                    "                ",
                    "Uab-TN2         "
                    };
                    
                    if (phase_line == 0)
                    {
                      const char idetyficator_phase[3][16] = {
                      "Ua              ",
                      "Ub              ",
                      "Uc              "
                      };
                      char *point_to_changed_name = idetyficator[I_Ua + 0];
                      for (unsigned int j = 0; j < 3; j++)
                      {
                        for (unsigned int k = 0; k < 16; k++) *(point_to_changed_name + j*16 + k) = idetyficator_phase[j][k];
                      }
                    }
                    else
                    {
                      const char idetyficator_line[3][16] = {
                      "Uab             ",
                      "Ubc             ",
                      "Uca             "
                      };
                      char *point_to_changed_name = idetyficator[I_Ua + 0];
                      for (unsigned int j = 0; j < 3; j++)
                      {
                        for (unsigned int k = 0; k < 16; k++) *(point_to_changed_name + j*16 + k) = idetyficator_line[j][k];
                      }
                    }
                    
                    if (canal_3U0_Ubc_TN2 == 0)
                    {
                      const char idetyficator_3U0[16] = "3U0             ";
                      char *point_to_changed_name = idetyficator[NUMBER_ANALOG_CANALES_VAL_1 + 0];
                      for (unsigned int k = 0; k < 16; k++) *(point_to_changed_name + k) = idetyficator_3U0[k];
                    }
                    else
                    {
                      const char idetyficator_Ubc_TN2[16] = "Ubc-TN2         ";
                      char *point_to_changed_name = idetyficator[NUMBER_ANALOG_CANALES_VAL_1 + 0];
                      for (unsigned int k = 0; k < 16; k++) *(point_to_changed_name + k) = idetyficator_Ubc_TN2[k];
                    }
                    
                    unsigned int index_cell;
                    
                    index_cell =  (i - 1)<<1;
                    temp_data  = idetyficator[number_record - 2][index_cell] | (idetyficator[number_record - 2][index_cell+1]<<8);
                  }
                  else if ( i == 9)
                  {
                    //���� ������ - 2 ASCII �������
                    char phase[NUMBER_ANALOG_CANALES][2] = {
                    "I0",
                    "A ",
                    "C ",
                    "  ",
                    "  ",
                    "  ",
                    "  ",
                    "AB"
                    };
                    
                    if (phase_line == 0)
                    {
                      const char phase_p[3][2] = {
                      "A ",
                      "B ",
                      "C "
                      };
                      char *point_to_changed_name = phase[I_Ua + 0];
                      for (unsigned int j = 0; j < 3; j++)
                      {
                        for (unsigned int k = 0; k < 2; k++) *(point_to_changed_name + j*2 + k) = phase_p[j][k];
                      }
                    }
                    else
                    {
                      const char pase_l[3][2] = {
                      "AB",
                      "BC",
                      "CA"
                      };
                      char *point_to_changed_name = phase[I_Ua + 0];
                      for (unsigned int j = 0; j < 3; j++)
                      {
                        for (unsigned int k = 0; k < 2; k++) *(point_to_changed_name + j*2 + k) = pase_l[j][k];
                      }
                    }
                    
                    if (canal_3U0_Ubc_TN2 == 0)
                    {
                      const char phase_3U0[2] = "U0";
                      char *point_to_changed_name = phase[NUMBER_ANALOG_CANALES_VAL_1 + 0];
                      for (unsigned int k = 0; k < 2; k++) *(point_to_changed_name + k) = phase_3U0[k];
                    }
                    else
                    {
                      const char phase_Ubc_TN2[2] = "BC";
                      char *point_to_changed_name = phase[NUMBER_ANALOG_CANALES_VAL_1 + 0];
                      for (unsigned int k = 0; k < 2; k++) *(point_to_changed_name + k) = phase_Ubc_TN2[k];
                    }
                    
                    temp_data  = phase[number_record - 2][0] | (phase[number_record - 2][1]<<8);
                  }
                  else if ( i < 18)
                  {
                    //������������ ������� � ��� - 16 ASCII ������� - ����� ��� �� ��������, ���� � �� ���� ������� ' '
                    temp_data  = ((' ')<<8) | (' ');
                  }
                  else if ( i == 18)
                  {
                    //������� ���������� - 2 ASCII �������
                    const char label_meas[2][2] = {"mA","mV"};
                    unsigned int index;
                    if (number_record <= (2 + I_Ic))index = 0;
                    else index = 1;
                    
                    temp_data  = label_meas[index][0] | (label_meas[index][1]<<8);
                  }
                  else if ( i == 19)
                  {
                    //���������� ������
                    if      (number_record == (2 + I_3I0)) temp_data  = (1000*MNOGNYK_3I0) >> (VAGA_DILENNJA_3I0 + 8);
                    else if (number_record <= (2 + I_Ic )) temp_data  = (1000*MNOGNYK_I)   >> (VAGA_DILENNJA_I   + 4);
                    else                                   temp_data  = (1000*MNOGNYK_U)   >> (VAGA_DILENNJA_U   + 4);
                  }
                  else if ( i == 20)
                  {
                    //��������� �������
                    temp_data  = 0;
                  }
                  else if ( i == 21)
                  {
                    //���� � ���
                    temp_data  = 0; //��� ����� ������� ������� ����������
                  }
                  else if ( i == 22)
                  {
                    //����� �������
                    temp_data  = -32767;
                  }
                  else if ( i == 23)
                  {
                    //������ �������
                    temp_data  = 32767;
                  }
                  else if ( i == 24)
                  {
                    //��������� ���������� �������������
                    if      (number_record == (2 + I_3I0)) temp_data  = header_ar_tmp.T0;
                    else if (number_record <= (2 + I_Ic )) temp_data  = header_ar_tmp.TCurrent;
                    else                                   temp_data  = header_ar_tmp.TVoltage;
                  }
                  else if ( i == 25)
                  {
                    //��������� ���������� �������������
                    temp_data  = 1;
                  }
                  else if ( i == 26)
                  {
                    //��� ������ ������������ � �������� �������
                    temp_data  = 'S';
                  }
                  *(output_data + 2 + 2*i) = (temp_data >> 8) & 0xff;
                  *(output_data + 3 + 2*i) = temp_data & 0xff;
                  i++;
                }
              }
              else error = ERROR_ILLEGAL_DATA_ADDRESS;
              break;
            }
          case (  2 + NUMBER_ANALOG_CANALES):
          case (  3 + NUMBER_ANALOG_CANALES):
          case (  4 + NUMBER_ANALOG_CANALES):
          case (  5 + NUMBER_ANALOG_CANALES):
          case (  6 + NUMBER_ANALOG_CANALES):
          case (  7 + NUMBER_ANALOG_CANALES):
          case (  8 + NUMBER_ANALOG_CANALES):
          case (  9 + NUMBER_ANALOG_CANALES):
          case ( 10 + NUMBER_ANALOG_CANALES):
          case ( 11 + NUMBER_ANALOG_CANALES):
          case ( 12 + NUMBER_ANALOG_CANALES):
          case ( 13 + NUMBER_ANALOG_CANALES):
          case ( 14 + NUMBER_ANALOG_CANALES):
          case ( 15 + NUMBER_ANALOG_CANALES):
          case ( 16 + NUMBER_ANALOG_CANALES):
          case ( 17 + NUMBER_ANALOG_CANALES):
          case ( 18 + NUMBER_ANALOG_CANALES):
          case ( 19 + NUMBER_ANALOG_CANALES):
          case ( 20 + NUMBER_ANALOG_CANALES):
          case ( 21 + NUMBER_ANALOG_CANALES):
          case ( 22 + NUMBER_ANALOG_CANALES):
          case ( 23 + NUMBER_ANALOG_CANALES):
          case ( 24 + NUMBER_ANALOG_CANALES):
          case ( 25 + NUMBER_ANALOG_CANALES):
          case ( 26 + NUMBER_ANALOG_CANALES):
          case ( 27 + NUMBER_ANALOG_CANALES):
          case ( 28 + NUMBER_ANALOG_CANALES):
          case ( 29 + NUMBER_ANALOG_CANALES):
          case ( 30 + NUMBER_ANALOG_CANALES):
          case ( 31 + NUMBER_ANALOG_CANALES):
          case ( 32 + NUMBER_ANALOG_CANALES):
          case ( 33 + NUMBER_ANALOG_CANALES):
          case ( 34 + NUMBER_ANALOG_CANALES):
          case ( 35 + NUMBER_ANALOG_CANALES):
          case ( 36 + NUMBER_ANALOG_CANALES):
          case ( 37 + NUMBER_ANALOG_CANALES):
          case ( 38 + NUMBER_ANALOG_CANALES):
          case ( 39 + NUMBER_ANALOG_CANALES):
          case ( 40 + NUMBER_ANALOG_CANALES):
          case ( 41 + NUMBER_ANALOG_CANALES):
          case ( 42 + NUMBER_ANALOG_CANALES):
          case ( 43 + NUMBER_ANALOG_CANALES):
          case ( 44 + NUMBER_ANALOG_CANALES):
          case ( 45 + NUMBER_ANALOG_CANALES):
          case ( 46 + NUMBER_ANALOG_CANALES):
          case ( 47 + NUMBER_ANALOG_CANALES):
          case ( 48 + NUMBER_ANALOG_CANALES):
          case ( 49 + NUMBER_ANALOG_CANALES):
          case ( 50 + NUMBER_ANALOG_CANALES):
          case ( 51 + NUMBER_ANALOG_CANALES):
          case ( 52 + NUMBER_ANALOG_CANALES):
          case ( 53 + NUMBER_ANALOG_CANALES):
          case ( 54 + NUMBER_ANALOG_CANALES):
          case ( 55 + NUMBER_ANALOG_CANALES):
          case ( 56 + NUMBER_ANALOG_CANALES):
          case ( 57 + NUMBER_ANALOG_CANALES):
          case ( 58 + NUMBER_ANALOG_CANALES):
          case ( 59 + NUMBER_ANALOG_CANALES):
          case ( 60 + NUMBER_ANALOG_CANALES):
          case ( 61 + NUMBER_ANALOG_CANALES):
          case ( 62 + NUMBER_ANALOG_CANALES):
          case ( 63 + NUMBER_ANALOG_CANALES):
          case ( 64 + NUMBER_ANALOG_CANALES):
          case ( 65 + NUMBER_ANALOG_CANALES):
          case ( 66 + NUMBER_ANALOG_CANALES):
          case ( 67 + NUMBER_ANALOG_CANALES):
          case ( 68 + NUMBER_ANALOG_CANALES):
          case ( 69 + NUMBER_ANALOG_CANALES):
          case ( 70 + NUMBER_ANALOG_CANALES):
          case ( 71 + NUMBER_ANALOG_CANALES):
          case ( 72 + NUMBER_ANALOG_CANALES):
          case ( 73 + NUMBER_ANALOG_CANALES):
          case ( 74 + NUMBER_ANALOG_CANALES):
          case ( 75 + NUMBER_ANALOG_CANALES):
          case ( 76 + NUMBER_ANALOG_CANALES):
          case ( 77 + NUMBER_ANALOG_CANALES):
          case ( 78 + NUMBER_ANALOG_CANALES):
          case ( 79 + NUMBER_ANALOG_CANALES):
          case ( 80 + NUMBER_ANALOG_CANALES):
          case ( 81 + NUMBER_ANALOG_CANALES):
          case ( 82 + NUMBER_ANALOG_CANALES):
          case ( 83 + NUMBER_ANALOG_CANALES):
          case ( 84 + NUMBER_ANALOG_CANALES):
          case ( 85 + NUMBER_ANALOG_CANALES):
          case ( 86 + NUMBER_ANALOG_CANALES):
          case ( 87 + NUMBER_ANALOG_CANALES):
          case ( 88 + NUMBER_ANALOG_CANALES):
          case ( 89 + NUMBER_ANALOG_CANALES):
          case ( 90 + NUMBER_ANALOG_CANALES):
          case ( 91 + NUMBER_ANALOG_CANALES):
          case ( 92 + NUMBER_ANALOG_CANALES):
          case ( 93 + NUMBER_ANALOG_CANALES):
          case ( 94 + NUMBER_ANALOG_CANALES):
          case ( 95 + NUMBER_ANALOG_CANALES):
          case ( 96 + NUMBER_ANALOG_CANALES):
          case ( 97 + NUMBER_ANALOG_CANALES):
          case ( 98 + NUMBER_ANALOG_CANALES):
          case ( 99 + NUMBER_ANALOG_CANALES):
          case (100 + NUMBER_ANALOG_CANALES):
          case (101 + NUMBER_ANALOG_CANALES):
          case (102 + NUMBER_ANALOG_CANALES):
          case (103 + NUMBER_ANALOG_CANALES):
          case (104 + NUMBER_ANALOG_CANALES):
          case (105 + NUMBER_ANALOG_CANALES):
          case (106 + NUMBER_ANALOG_CANALES):
          case (107 + NUMBER_ANALOG_CANALES):
          case (108 + NUMBER_ANALOG_CANALES):
          case (109 + NUMBER_ANALOG_CANALES):
          case (110 + NUMBER_ANALOG_CANALES):
          case (111 + NUMBER_ANALOG_CANALES):
          case (112 + NUMBER_ANALOG_CANALES):
          case (113 + NUMBER_ANALOG_CANALES):
          case (114 + NUMBER_ANALOG_CANALES):
          case (115 + NUMBER_ANALOG_CANALES):
          case (116 + NUMBER_ANALOG_CANALES):
          case (117 + NUMBER_ANALOG_CANALES):
          case (118 + NUMBER_ANALOG_CANALES):
          case (119 + NUMBER_ANALOG_CANALES):
          case (120 + NUMBER_ANALOG_CANALES):
          case (121 + NUMBER_ANALOG_CANALES):
          case (122 + NUMBER_ANALOG_CANALES):
          case (123 + NUMBER_ANALOG_CANALES):
          case (124 + NUMBER_ANALOG_CANALES):
          case (125 + NUMBER_ANALOG_CANALES):
          case (126 + NUMBER_ANALOG_CANALES):
          case (127 + NUMBER_ANALOG_CANALES):
          case (128 + NUMBER_ANALOG_CANALES):
          case (129 + NUMBER_ANALOG_CANALES):
          case (130 + NUMBER_ANALOG_CANALES):
          case (131 + NUMBER_ANALOG_CANALES):
          case (132 + NUMBER_ANALOG_CANALES):
          case (133 + NUMBER_ANALOG_CANALES):
          case (134 + NUMBER_ANALOG_CANALES):
          case (135 + NUMBER_ANALOG_CANALES):
          case (136 + NUMBER_ANALOG_CANALES):
          case (137 + NUMBER_ANALOG_CANALES):
          case (138 + NUMBER_ANALOG_CANALES):
          case (139 + NUMBER_ANALOG_CANALES):
          case (140 + NUMBER_ANALOG_CANALES):
          case (141 + NUMBER_ANALOG_CANALES):
          case (142 + NUMBER_ANALOG_CANALES):
          case (143 + NUMBER_ANALOG_CANALES):
          case (144 + NUMBER_ANALOG_CANALES):
          case (145 + NUMBER_ANALOG_CANALES):
          case (146 + NUMBER_ANALOG_CANALES):
          case (147 + NUMBER_ANALOG_CANALES):
          case (148 + NUMBER_ANALOG_CANALES):
          case (149 + NUMBER_ANALOG_CANALES):
          case (150 + NUMBER_ANALOG_CANALES):
          case (151 + NUMBER_ANALOG_CANALES):
          case (152 + NUMBER_ANALOG_CANALES):
          case (153 + NUMBER_ANALOG_CANALES):
          case (154 + NUMBER_ANALOG_CANALES):
          case (155 + NUMBER_ANALOG_CANALES):
          case (156 + NUMBER_ANALOG_CANALES):
          case (157 + NUMBER_ANALOG_CANALES):
          case (158 + NUMBER_ANALOG_CANALES):
          case (159 + NUMBER_ANALOG_CANALES):
          case (160 + NUMBER_ANALOG_CANALES):
          case (161 + NUMBER_ANALOG_CANALES):
          case (162 + NUMBER_ANALOG_CANALES):
          case (163 + NUMBER_ANALOG_CANALES):
          case (164 + NUMBER_ANALOG_CANALES):
          case (165 + NUMBER_ANALOG_CANALES):
          case (166 + NUMBER_ANALOG_CANALES):
          case (167 + NUMBER_ANALOG_CANALES):
          case (168 + NUMBER_ANALOG_CANALES):
          case (169 + NUMBER_ANALOG_CANALES):
          case (170 + NUMBER_ANALOG_CANALES):
          case (171 + NUMBER_ANALOG_CANALES):
          case (172 + NUMBER_ANALOG_CANALES):
          case (173 + NUMBER_ANALOG_CANALES):
          case (174 + NUMBER_ANALOG_CANALES):
          case (175 + NUMBER_ANALOG_CANALES):
          case (176 + NUMBER_ANALOG_CANALES):
            {
              if (length <= 19)
              {
                unsigned int i = 0;
                while (i < length)
                {
                  if (i == 0)
                  {
                    //����� ������
                    temp_data = (number_record - (2 + NUMBER_ANALOG_CANALES)) + 1;
                  }
                  else if ( i < 9)
                  {
                    //��������������� ������ - 16 ASCII �������
                    const char idetyficator[MAX_NAMBER_LANGUAGE][NUMBER_TOTAL_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG][16] =
                    {
                      {
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
                        " �����. ��������",
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
                        " ����.����.���  ",
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
                    int index_language = index_language_in_array(current_settings.language);
                    unsigned int index_cell;
                    
                    index_cell =  (i - 1)<<1;
                    temp_data  = idetyficator[index_language][number_record - (2 + NUMBER_ANALOG_CANALES)][index_cell] | (idetyficator[index_language][number_record - (2 + NUMBER_ANALOG_CANALES)][index_cell+1]<<8);
                  }
                  else if ( i == 9)
                  {
                    //���� ������ - 2 ASCII ������� - ����� �� ��������
                    temp_data  = (' '<<8) | ' ';
                  }
                  else if ( i < 18)
                  {
                    //������������ ������� � ��� - 16 ASCII �������- ����� �� ��������
                    temp_data  = (' '<<8) | ' ';
                  }
                  else if ( i == 18)
                  {
                    //���������� ����
                    temp_data  = 0;
                  }
                  *(output_data + 2 + 2*i) = (temp_data >> 8) & 0xff;
                  *(output_data + 3 + 2*i) = temp_data & 0xff;
                  i++;
                }
              }
              else error = ERROR_ILLEGAL_DATA_ADDRESS;
              break;
            }
          case (2 + NUMBER_ANALOG_CANALES + NUMBER_TOTAL_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG):
          case (3 + NUMBER_ANALOG_CANALES + NUMBER_TOTAL_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG):
            {
              if (length <= 1)
              {
                
                if (number_record == (2 + NUMBER_ANALOG_CANALES + NUMBER_TOTAL_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG)) temp_data  = 5000; //������ �� (x100)
                else temp_data  = 1; //ʳ������ ������ �������������
                *(output_data + 2 ) = (temp_data >> 8) & 0xff;
                *(output_data + 3 ) = temp_data & 0xff;
              }
              else error = ERROR_ILLEGAL_DATA_ADDRESS;
              break;
            }
          case (4 + NUMBER_ANALOG_CANALES + NUMBER_TOTAL_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG):
            {
              if (length <= 2)
              {
                unsigned int i = 0;
                while ((i < length) && (error == 0))
                {
                  if (i == 0) temp_data  = ((50*1000)<<VAGA_NUMBER_POINT_AR)>>4; //������� �������
                  else temp_data = max_number_time_sample; //������� ������� �� ���� ����� ������������� ���� ������� ������� � ����� ����������� ����������

                  *(output_data + 2 + 2*i ) = (temp_data >> 8) & 0xff;
                  *(output_data + 3 + 2*i ) = temp_data & 0xff;
                  i++;
                }
              }
              else error = ERROR_ILLEGAL_DATA_ADDRESS;
              break;
            }
          case (5 + NUMBER_ANALOG_CANALES + NUMBER_TOTAL_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG):
          case (6 + NUMBER_ANALOG_CANALES + NUMBER_TOTAL_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG):
            {
              
              if (length <= 7)
              {
                unsigned char time_avar_analog[7];
                
                //���������� ������ BCD � int
                for (unsigned int i = 0; i < 7; i++)
                {
                  unsigned int val = header_ar_tmp.time[i], val_l, val_m;
                  val_l = val & 0xf;
                  val_m = (val >> 4) & 0xf;
                  time_avar_analog[i] = (unsigned char)(val_m*10 + val_l);
                }
                
                if (number_record == (5 + NUMBER_ANALOG_CANALES + NUMBER_TOTAL_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG))
                {
                  //��������� ��� ����� ������� � ����������� ����� = ��� ������ ���� ��� ����������� ������
                  //������������ ��� ����������� ������ ���� ���� 5000��, �� ����������� ������� ������ 250

                  //��� � ����� ������ ���������� ������
                  unsigned int max_time_milliseconds_before = (current_settings.prefault_number_periods)*2; //2 - �� ����� �� 20 ��, �� �������� ����� �� 50��
                  unsigned int flag_carry = 0;
                  unsigned int s, ds_ms;
                    
                  //ʳ������ ������
                  s = max_time_milliseconds_before / 100;
                  //ʳ������ ������� � ����� ��������
                  ds_ms = max_time_milliseconds_before - s*100;
                    
                  //³������ ������ � ��� ��������
                  if (time_avar_analog[0] >= ds_ms)
                  {
                    time_avar_analog[0] -= ds_ms;
                    flag_carry = 0;
                  }
                  else
                  {
                    time_avar_analog[0] = time_avar_analog[0] + 100 - ds_ms;
                    flag_carry = 1;
                  }
                      
                  //³������ �������
                  if (time_avar_analog[1] >= (s + flag_carry))
                  {
                    time_avar_analog[1] -= (s + flag_carry);
                    flag_carry = 0;
                  }
                  else
                  {
                    time_avar_analog[1] = time_avar_analog[1] + 60 - (s + flag_carry);
                    flag_carry = 1;
                  }
                    
                  //������ �������, ���� � ����������� ��������� ��������
                  if (flag_carry != 0)
                  {
                    //³������ �������
                    if (time_avar_analog[2] >=  flag_carry)
                    {
                      time_avar_analog[2] -= flag_carry;
                      flag_carry = 0;
                    }
                    else
                    {
                      time_avar_analog[2] = time_avar_analog[2] + 60 - flag_carry;
                      flag_carry = 1;
                    }

                    //������ �������, ���� � ����������� ��������� ��������
                    if (flag_carry != 0)
                    {
                      //³������ ������
                      if (time_avar_analog[3] >=  flag_carry)
                      {
                        time_avar_analog[3] -= flag_carry;
                        flag_carry = 0;
                      }
                      else
                      {
                        time_avar_analog[3] = time_avar_analog[3] + 24 - flag_carry;
                        flag_carry = 1;
                      } 

                      //������ �������, ���� � ����������� ��������� ��������
                      if (flag_carry != 0)
                      {
                        //³������ �� �����
                        if (time_avar_analog[4] > flag_carry)
                        {
                          time_avar_analog[4] -= flag_carry;
                          flag_carry = 0;
                        }
                        else
                        {
                          unsigned int max_value, number_previous_mounth;
                            
                          if (((int)(time_avar_analog[5] - 1)) > 0) number_previous_mounth = time_avar_analog[5] - 1;
                          else number_previous_mounth = 12; //��������� ����� - �������
                             
                          //����������� ������� ��� � ������������ ����� (�� �� � ������ "��������" �������� � ���� ��������� �� �������� �������� � ������)
                          if (number_previous_mounth == 2)
                          {
                            //��������� ����� - �����
                            //�������� �� ���������� ��
                            if((time_avar_analog[6] & 0xfc) == 0)
                            {
                              //г� ���������� - ������� ��� � ������ 29
                              max_value = 29;
                            }
                            else
                            {
                              //г� �� ���������� - ������� ��� � ������ 28
                              max_value = 28;
                            }
                          }
                          else if (
                                   ((number_previous_mounth <= 7) && ((number_previous_mounth & 0x01) != 0)) ||
                                   ((number_previous_mounth >= 8) && ((number_previous_mounth & 0x01) == 0)) 
                                  )
                          {
                            //��������� ����� �� 31 ����
                            max_value = 31;
                          }
                          else
                          {
                            //��������� ����� �� 30 ���
                            max_value = 30;
                          }
                            
                          time_avar_analog[4] = time_avar_analog[4] + max_value - flag_carry;
                          flag_carry = 1;
                        } 

                        //������ �������, ���� � ����������� ��������� ��������
                        if (flag_carry != 0)
                        {
                          //³������ �����
                          if ((int)(time_avar_analog[5] - flag_carry) > 0)
                          {
                            time_avar_analog[5] -= flag_carry;
                            flag_carry = 0;
                          }
                          else
                          {
                            time_avar_analog[5] = 12;
                            flag_carry = 1;
                          } 

                          //������ �������, ���� � ����������� ��������� ��������
                          if (flag_carry != 0)
                          {
                            //³������ ����
                            if (time_avar_analog[6] > flag_carry)
                            {
                              time_avar_analog[6] -= flag_carry;
                              flag_carry = 0;
                            }
                            else
                            {
                              time_avar_analog[6] = 99;
                              flag_carry = 1;
                            } 
                          }
                        }
                      }
                    }
                  }
                }
                 
                unsigned int i = 0;
                while (i < length)
                {
                  if (i < 3)
                  {
                    temp_data = time_avar_analog[4 + i];
                    if (i == 2)temp_data += 2000; //�� ������ �� ���� ������������� ������
                  }
                  else if (i < 5 ) temp_data = time_avar_analog[3 - (i - 3)];
                  else if (i == 5) temp_data = time_avar_analog[1]*100 + time_avar_analog[0];
                  else temp_data = 0;
                  
                  *(output_data + 2 + 2*i) = (temp_data >> 8) & 0xff;
                  *(output_data + 3 + 2*i) = temp_data & 0xff;
                  i++;
                }
                
              }
              else error = ERROR_ILLEGAL_DATA_ADDRESS;
              break;
            }
          case (7 + NUMBER_ANALOG_CANALES + NUMBER_TOTAL_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG):
          case (8 + NUMBER_ANALOG_CANALES + NUMBER_TOTAL_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG):
            {
              if (length <= 1)
              {
                
                if (number_record == (7 + NUMBER_ANALOG_CANALES + NUMBER_TOTAL_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG)) temp_data  = 'B'; //��� - �� ����� �����
                else temp_data  = (1000000 >> VAGA_NUMBER_POINT_AR)/50; //����� �������������
                *(output_data + 2 ) = (temp_data >> 8) & 0xff;
                *(output_data + 3 ) = temp_data & 0xff;
              }
              else error = ERROR_ILLEGAL_DATA_ADDRESS;
              break;
            }
          default:
            {
              error = ERROR_ILLEGAL_DATA_ADDRESS;
              break;
            }
          }
          //*************************************
          break;
        }        
      case 2:
      case 3:
      case 4:
        {
          //*************************************
          //��� ����������� ����������
          //*************************************
          //����������� ������� ������� ���� 
          int max_number_time_sample = (current_settings.prefault_number_periods + current_settings.postfault_number_periods) << VAGA_NUMBER_POINT_AR;
          
          //������� ���� ����������� ����������� ����� ��� ����������� ����������
          while (
                 ((type_interface == USB_RECUEST  ) && ((control_tasks_dataflash & TASK_MAMORY_READ_DATAFLASH_FOR_AR_USB  ) != 0)) ||
                 ((type_interface == RS485_RECUEST) && ((control_tasks_dataflash & TASK_MAMORY_READ_DATAFLASH_FOR_AR_RS485) != 0))
                )
          {
            //��� ������ ���� ������������� Watchdog, �� ��� ����� ���� ��������� ������� ������ � ���
          }

          if (
              ((number_file == 2) && ( number_record < 10000) && ( number_record          < ((unsigned int)(max_number_time_sample)))) ||
              ((number_file == 3) && ( number_record < 10000) && ((number_record + 10000) < ((unsigned int)(max_number_time_sample)))) ||
              ((number_file == 4) && ( number_record < 10000) && ((number_record + 20000) < ((unsigned int)(max_number_time_sample))))
             )
          {
            if (number_file == 3) number_record += 10000;
            else if (number_file == 4) number_record += 20000;
              
            int *point_to_first_number_time_sample, *point_to_last_number_time_sample;
            if (type_interface == USB_RECUEST)
            {
              point_to_first_number_time_sample = &first_number_time_sample_for_USB;
              point_to_last_number_time_sample  = &last_number_time_sample_for_USB;
            }
            else
            {
              point_to_first_number_time_sample = &first_number_time_sample_for_RS485;
              point_to_last_number_time_sample  = &last_number_time_sample_for_RS485;
            }
            
            //���������� �� ������� ��������� ����������� ����������
            if (
                (((int)number_record) < (*point_to_first_number_time_sample)) || 
                (((int)number_record) > (*point_to_last_number_time_sample ))
               )
            {
              //����������� ������� ��� �� � ��������
              
              //����������� ������� ��� ��������� ������ ������ ������ � ������������� ������ ���� � ������, ������ �������, ������� ���� 
              *point_to_first_number_time_sample = number_record;
              int last_number_time_sample_tmp = number_record + SIZE_PAGE_DATAFLASH_2/((NUMBER_ANALOG_CANALES + number_word_digital_part_ar)*sizeof(short int));
              if (last_number_time_sample_tmp <= max_number_time_sample)
              {
                *point_to_last_number_time_sample = last_number_time_sample_tmp - 1;//����� ���������� �������� ���� �������
              }
              else
              {
                *point_to_last_number_time_sample = max_number_time_sample - 1;
              }

              //������ ������� ������� ��� � ����� ���'��
              if (type_interface == USB_RECUEST)
                control_tasks_dataflash |= TASK_MAMORY_READ_DATAFLASH_FOR_AR_USB;
              else
                control_tasks_dataflash |= TASK_MAMORY_READ_DATAFLASH_FOR_AR_RS485;
                
              //������� ���� ����������� ����������� ����� ��� ����������� ����������
              while (
                     ((type_interface == USB_RECUEST  ) && ((control_tasks_dataflash & TASK_MAMORY_READ_DATAFLASH_FOR_AR_USB  ) != 0)) ||
                     ((type_interface == RS485_RECUEST) && ((control_tasks_dataflash & TASK_MAMORY_READ_DATAFLASH_FOR_AR_RS485) != 0))
                    )
              {
                //��� ������ ���� ������������� Watchdog, �� ��� ����� ���� ��������� ������� ������ � ���
              }
            }
            
            //���� �� ���� �����, �� ������� �� ���������� ������� ������� � ����������� � ����� ������� ����������� ���������� ��� ����������
            
            //��������� ������ � ����� ������� � ����� ��������� �������� ��� ������� ���
            unsigned int index_time_sample;
            if((*point_to_first_number_time_sample) == -1)
            {
              index_time_sample = sizeof(__HEADER_AR) + number_record*(NUMBER_ANALOG_CANALES + number_word_digital_part_ar)*sizeof(short int);
            }
            else
            {
              index_time_sample = 0 + (number_record - (*point_to_first_number_time_sample))*(NUMBER_ANALOG_CANALES + number_word_digital_part_ar)*sizeof(short int);
            }
              
            if (length <= (3 + NUMBER_ANALOG_CANALES + number_word_digital_part_ar))
            {
              unsigned int i = 0;
              while (i < length)
              {
                if (i == 0) temp_data = number_record + 1;
                else if ((i == 1) || (i == 2))
                {
                  if (i == 1) temp_data = number_record & 0xffff;
                  else temp_data = number_record >> 16;
                }
                else 
                {
                  unsigned char *point_to_buffer;
                  if (type_interface == USB_RECUEST)
                    point_to_buffer = buffer_for_USB_read_record_ar;
                  else
                    point_to_buffer = buffer_for_RS485_read_record_ar;
                  
                  temp_data = (*(point_to_buffer + index_time_sample +2*(i-3))) + ((*(point_to_buffer + index_time_sample + 1 +2*(i-3))) << 8);
                }
                *(output_data + 2 + 2*i) = (temp_data >> 8) & 0xff;
                *(output_data + 3 + 2*i) = temp_data & 0xff;
                i++;
              }
            }
            else error = ERROR_ILLEGAL_DATA_ADDRESS;
          }
          else error = ERROR_ILLEGAL_DATA_ADDRESS;
          //*************************************
          break;
        }        
      case 5:
        {
          //*************************************
          //��������� ��� ����������� ����������
          //*************************************
          unsigned char *point_to_buffer;
          if (type_interface == USB_RECUEST) point_to_buffer = buffer_for_USB_read_record_dr;
          else point_to_buffer = buffer_for_RS485_read_record_dr;

          switch (number_record)
          {
          case 0:
            {
              if (length <= 10)
              {
                unsigned int i = 0;
                while (i < length)
                {
                  if (i < 8)
                  {
                    unsigned int index_cell;
                    
                    index_cell =  (i - 0)<<1;
                    temp_data  = (*(point_to_buffer + FIRST_INDEX_NAME_OF_CELL_DR + index_cell)) | ((*(point_to_buffer + FIRST_INDEX_NAME_OF_CELL_DR + index_cell + 1))<<8);
                  }
                  else if (i == 8)
                  {
                    //������� ����� �������� ������ ���� � ��� ����� (�������������� �� �����-�����������), ���� � ���� �� ������� ��� ������ � DataFlash � ����� ��������� ����������� ����������
                    temp_data = serial_number_dev & 0xffff;
                  }
                  else
                  {
                    temp_data = 1999;
                  }
                  *(output_data + 2 + 2*i) = (temp_data >> 8) & 0xff;
                  *(output_data + 3 + 2*i) = temp_data & 0xff;
                  i++;
                }
              }
              else error = ERROR_ILLEGAL_DATA_ADDRESS;
              break;
            }
          case 1:
            {
              if (length <= 3)
              {
                unsigned int i = 0;
                while (i < length)
                {
                  if (i == 0)
                  {
                    temp_data  = 0 + NUMBER_TOTAL_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG;
                  }
                  else if (i == 1)
                  {
                    temp_data = 0;
                  }
                  else
                  {
                    temp_data = NUMBER_TOTAL_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG;
                  }
                  *(output_data + 2 + 2*i) = (temp_data >> 8) & 0xff;
                  *(output_data + 3 + 2*i) = temp_data & 0xff;
                  i++;
                }
              }
              else error = ERROR_ILLEGAL_DATA_ADDRESS;
              break;
            }
          case 2:
          case 3:
          case 4:
          case 5:
          case 6:
          case 7:
          case 8:
          case 9:
          case 10:
          case 11:
          case 12:
          case 13:
          case 14:
          case 15:
          case 16:
          case 17:
          case 18:
          case 19:
          case 20:
          case 21:
          case 22:
          case 23:
          case 24:
          case 25:
          case 26:
          case 27:
          case 28:
          case 29:
          case 30:
          case 31:
          case 32:
          case 33:
          case 34:
          case 35:
          case 36:
          case 37:
          case 38:
          case 39:
          case 40:
          case 41:
          case 42:
          case 43:
          case 44:
          case 45:
          case 46:
          case 47:
          case 48:
          case 49:
          case 50:
          case 51:
          case 52:
          case 53:
          case 54:
          case 55:
          case 56:
          case 57:
          case 58:
          case 59:
          case 60:
          case 61:
          case 62:
          case 63:
          case 64:
          case 65:
          case 66:
          case 67:
          case 68:
          case 69:
          case 70:
          case 71:
          case 72:
          case 73:
          case 74:
          case 75:
          case 76:
          case 77:
          case 78:
          case 79:
          case 80:
          case 81:
          case 82:
          case 83:
          case 84:
          case 85:
          case 86:
          case 87:
          case 88:
          case 89:
          case 90:
          case 91:
          case 92:
          case 93:
          case 94:
          case 95:
          case 96:
          case 97:
          case 98:
          case 99:
          case 100:
          case 101:
          case 102:
          case 103:
          case 104:
          case 105:
          case 106:
          case 107:
          case 108:
          case 109:
          case 110:
          case 111:
          case 112:
          case 113:
          case 114:
          case 115:
          case 116:
          case 117:
          case 118:
          case 119:
          case 120:
          case 121:
          case 122:
          case 123:
          case 124:
          case 125:
          case 126:
          case 127:
          case 128:
          case 129:
          case 130:
          case 131:
          case 132:
          case 133:
          case 134:
          case 135:
          case 136:
          case 137:
          case 138:
          case 139:
          case 140:
          case 141:
          case 142:
          case 143:
          case 144:
          case 145:
          case 146:
          case 147:
          case 148:
          case 149:
          case 150:
          case 151:
          case 152:
          case 153:
          case 154:
          case 155:
          case 156:
          case 157:
          case 158:
          case 159:
          case 160:
          case 161:
          case 162:
          case 163:
          case 164:
          case 165:
          case 166:
          case 167:
          case 168:
          case 169:
          case 170:
          case 171:
          case 172:
          case 173:
          case 174:
          case 175:
          case 176:
            {
              if (length <= 19)
              {
                unsigned int i = 0;
                while (i < length)
                {
                  if (i == 0)
                  {
                    //����� ������
                    temp_data = (number_record - 2) + 1;
                  }
                  else if ( i < 9)
                  {
                    //��������������� ������ - 16 ASCII �������
                    const char idetyficator[MAX_NAMBER_LANGUAGE][NUMBER_TOTAL_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG][16] =
                    {
                      {
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
                        " �����. ��������",
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
                        " ����.I��.���.  ",
                        " ����.������ �� ",
                        " ���.������ ��  ",
                        "  CB Actuator   ",
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
                        " ����.����.���  ",
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
                    int index_language = index_language_in_array(current_settings.language);
                    unsigned int index_cell;
                    
                    index_cell =  (i - 1)<<1;
                    temp_data  = idetyficator[index_language][number_record - 2][index_cell] | (idetyficator[index_language][number_record - 2][index_cell+1]<<8);
                  }
                  else if ( i == 9)
                  {
                    //���� ������ - 2 ASCII ������� - ����� �� ��������
                    temp_data  = (' '<<8) | ' ';
                  }
                  else if ( i < 18)
                  {
                    //������������ ������� � ��� - 16 ASCII �������- ����� �� ��������
                    temp_data  = (' '<<8) | ' ';
                  }
                  else if ( i == 18)
                  {
                    //���������� ����
                    temp_data  = 0;
                  }
                  *(output_data + 2 + 2*i) = (temp_data >> 8) & 0xff;
                  *(output_data + 3 + 2*i) = temp_data & 0xff;
                  i++;
                }
              }
              else error = ERROR_ILLEGAL_DATA_ADDRESS;
              break;
            }
          case ( 2 + NUMBER_TOTAL_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG):
          case ( 3 + NUMBER_TOTAL_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG):
            {
              if (length <= 1)
              {
                
                if (number_record == ( 2 + NUMBER_TOTAL_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG))
                {
                  temp_data  = MAIN_FREQUENCY*100; //������ ��
                }
                else
                {
                  temp_data  = 0; //ʳ������ ������ �������������
                }
                *(output_data + 2 ) = (temp_data >> 8) & 0xff;
                *(output_data + 3 ) = temp_data & 0xff;
              }
              else error = ERROR_ILLEGAL_DATA_ADDRESS;
              break;
            }
          case ( 4 + NUMBER_TOTAL_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG):
            {
              if (length <= 2)
              {
                unsigned int i = 0;
                while (i < length)
                {
                  if (i == 0) temp_data  = 0; //������� �������
                  else
                  {
                      temp_data = *(point_to_buffer + FIRST_INDEX_NUMBER_ITEMS_DR); //������� ������� � ����������� ��������� ������� � ������� �������� ������� (� ��� ������)
                  }
                  
                  *(output_data + 2 + 2*i) = (temp_data >> 8) & 0xff;
                  *(output_data + 3 + 2*i) = temp_data & 0xff;
                  i++;
                }
              }
              else error = ERROR_ILLEGAL_DATA_ADDRESS;
              break;
            }
          case ( 5 + NUMBER_TOTAL_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG):
          case ( 6 + NUMBER_TOTAL_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG):
            {
              
              if (length <= 7)
              {
                //���������� ������ BCD � int
                unsigned int time_avar_digital[7];

                //���������� ������ BCD � int
                for (unsigned int i = 0; i < 7; i++)
                {
                  unsigned int val = *(point_to_buffer + FIRST_INDEX_DATA_TIME_DR + i), val_l, val_m;
                  val_l = val & 0xf;
                  val_m = (val >> 4) & 0xf;
                  time_avar_digital[i] = val_m*10 + val_l;
                }
                  
                unsigned int i = 0;
                while (i < length)
                {
                  if (i < 3)
                  {
                    temp_data = time_avar_digital[4 + i];
                    if (i == 2)temp_data += 2000; //�� ������ �� ���� ������������� ������
                  }
                  else if (i < 5 ) temp_data = time_avar_digital[3 - (i - 3)];
                  else if (i == 5) temp_data = time_avar_digital[1]*100 + time_avar_digital[0];
                  else temp_data = 0;/*�������� �������� - ����� � ����� ������ �� ���������*/

                  *(output_data + 2 + 2*i) = (temp_data >> 8) & 0xff;
                  *(output_data + 3 + 2*i) = temp_data & 0xff;
                  i++;
                }
              }
              else error = ERROR_ILLEGAL_DATA_ADDRESS;
              break;
            }
          case ( 7 + NUMBER_TOTAL_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG):
          case ( 8 + NUMBER_TOTAL_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG):
            {
              if (length <= 1)
              {
                
                if (number_record == ( 7 + NUMBER_TOTAL_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG))
                {
                  temp_data  = 'B'; //��� - �� ����� �����
                }
                else temp_data  = 1000; //�������, �� ���� ��������� ������ ���� � ����� �����, ��� �������� �����������
                *(output_data + 2 ) = (temp_data >> 8) & 0xff;
                *(output_data + 3 ) = temp_data & 0xff;
              }
              else error = ERROR_ILLEGAL_DATA_ADDRESS;
              break;
            }
          default:
            {
              error = ERROR_ILLEGAL_DATA_ADDRESS;
              break;
            }
          }
          //*************************************
          break;
        }
      case 6:
        {
          //*************************************
          //��� 1 ��� ����������� ����������
          //*************************************
          unsigned char *point_to_buffer;
          if (type_interface == USB_RECUEST) point_to_buffer = buffer_for_USB_read_record_dr;
          else point_to_buffer = buffer_for_RS485_read_record_dr;

          if (number_record < (*(point_to_buffer + FIRST_INDEX_NUMBER_ITEMS_DR)))
          {
            unsigned int max_number_two_bytes = (NUMBER_TOTAL_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG >> 4);
            if ((max_number_two_bytes << 4) != NUMBER_TOTAL_SIGNAL_FOR_RANG_OUTPUT_LED_DF_REG)
              max_number_two_bytes++;
              
            if (length <= (3 + max_number_two_bytes))
            {
              unsigned int i = 0;
              while (i < length)
              {
                if (i == 0) temp_data = number_record + 1;
                else
                {
                  unsigned int offset = FIRST_INDEX_FIRST_DATA_DR + (number_record + 1)*28; //�� ��������� ����� ������ �������� �������� (�� �������� ������� ������ ����������� ����������)
                  if (i == 1)
                  {
                    temp_data =  (*(point_to_buffer + offset + 0)) + ((*(point_to_buffer + offset + 1)) << 8 );
                  }
                  else if (i == 2)
                  {
                    temp_data =  *(point_to_buffer + offset + 2);
                  }
                  else
                  {
                    temp_data = (*(point_to_buffer + offset + 3 + (i - 3)*2)) + ((*(point_to_buffer + offset + 4 + (i - 3)*2)) << 8);
                  }
                }
                *(output_data + 2 + 2*i) = (temp_data >> 8) & 0xff;
                *(output_data + 3 + 2*i) = temp_data & 0xff;
                i++;
              }
            }
            else error = ERROR_ILLEGAL_DATA_ADDRESS;
          }
          else error = ERROR_ILLEGAL_DATA_ADDRESS;
          //*************************************
          break;
        }
      default:
        {
          //����������, ���� �������� ����� �� ���� ��������
          error = ERROR_ILLEGAL_DATA_ADDRESS;
          break;
        }
      }
    }
    else error = ERROR_ILLEGAL_DATA_ADDRESS;
  }
  else error = ERROR_ILLEGAL_DATA_ADDRESS;
  return error;  
}
/***********************************************************************************/

/***********************************************************************************/
//������ ������� ��� �������� ����� ����� ��������� RS-485
/***********************************************************************************/
inline void start_transmint_data_via_RS_485(unsigned int count)
{
  //����������, �� ����� ���������� ���
  unsigned int current_time_tim4 = TIM4->CNT;
  unsigned int delta_time;

  //���������� ���, �������� ����� ��������������� �������
  if (
      (current_time_tim4 > time_last_receive_byte) ||
      (
       (current_time_tim4 == time_last_receive_byte) &&
       (mark_current_tick_RS_485 != 0)  
      ) 
     )   
    delta_time = current_time_tim4 - time_last_receive_byte;
  else 
    delta_time = current_time_tim4 + 0xffff - time_last_receive_byte;

  if (max_reaction_time_rs_485 < delta_time) max_reaction_time_rs_485 = delta_time;
  
  if (delta_time < MAX_TIMEOUT_PACKET)
  {
    //����� ��������� �� �����

    //���������� ��������� �� ��������
    GPIO_485DE->BSRRL = GPIO_PIN_485DE;

    //������� ��, �� ��������, �� �������� ���� ���������
    USART_ClearFlag(USART_RS485, USART_FLAG_TC);

    //���������� ��������� �����������, ����  ���� �������� �� ����� �� DMA1 ����� ����� DMA1_ChannelRS485_TX
    DMA_StreamRS485_Tx->CR |= DMA_IT_TC;

    //��������� ���� DMA ���� �� ���������
    if ((DMA_StreamRS485_Tx->CR & (uint32_t)DMA_SxCR_EN) !=0) DMA_StreamRS485_Tx->CR &= ~(uint32_t)DMA_SxCR_EN;
    DMA_StreamRS485_Tx->NDTR = count;
    //���������� �������� ����� DMA
    if ((USART_RS485->CR3 & USART_DMAReq_Tx) == 0) USART_RS485->CR3 |= USART_DMAReq_Tx;

    //������� ���������, �� �������� ��� ���������� �������� ����� ��� DMA1 �� ������ RS-485_TX
    DMA_ClearFlag(DMA_StreamRS485_Tx, DMA_FLAG_TCRS485_Tx | DMA_FLAG_HTRS485_Tx | DMA_FLAG_TEIRS485_Tx | DMA_FLAG_DMEIRS485_Tx | DMA_FLAG_FEIRS485_Tx);
    //��������� ��������
    DMA_StreamRS485_Tx->CR |= (uint32_t)DMA_SxCR_EN;
  }
  else
  {
    //�� ����� ��������� �� �����, �� ������� ��������� ������ ��� �� ��������� ��� ���������� ������ - ����� ���������� �� ������ ����������� �� RS-485
    restart_monitoring_RS485();
  }
}
/***********************************************************************************/

/***********************************************************************************/
//�������� ������� ������ �� ��������� MODBUS-RTU
/***********************************************************************************/
void modbus_rountines(unsigned int type_interface)
{
 unsigned char *received_buffer, *transmited_buffer;
 int volatile *received_count;
 int *transmited_count;
 unsigned int error = 0;
  
  if(type_interface == USB_RECUEST)
  {
    received_buffer = usb_received;
    transmited_buffer = usb_transmiting;
    received_count = &usb_received_count;
    transmited_count = &usb_transmiting_count;
  }
  else if (type_interface == RS485_RECUEST)
  {
    received_buffer = RxBuffer_RS485;
    transmited_buffer = TxBuffer_RS485;
    received_count = &RxBuffer_RS485_count;
    transmited_count = &TxBuffer_RS485_count;
  }
  else
  {
    //���������� ����� ����� �� ���� � ����
    total_error_sw_fixed(45);
  }
   
  //�������� ������ ������������ �������
  unsigned int global_requect;
  if(
     (*received_count >= 3)  
     &&
     (
      ((global_requect = (*received_buffer == BROADCAST_ADDRESS_MODBUS_RTU)) != 0) ||
      (*received_buffer == current_settings.address)
     )
    )   
  {
    unsigned short int CRC_sum;
    
    //�������� ���������� ����
    CRC_sum = 0xffff;
    for (int index = 0; index < (*received_count-2); index++) CRC_sum = AddCRC(*(received_buffer + index),CRC_sum);

    unsigned int func_modbus = *(received_buffer+1);
    if (
        ((CRC_sum & 0xff) == *(received_buffer+*received_count-2)) &&
        ((CRC_sum >> 8  ) == *(received_buffer+*received_count-1)) &&
        (
         (global_requect == 0) ||
         (func_modbus == 6 ) ||
         (func_modbus == 16)
        )
       )
    {
      //������ ������� �� �������� ��������� ���������� ������ ������ � ��������� ����������
      restart_timeout_interface |= (1 << type_interface);
      
      //������� �����
      switch (func_modbus)
      {
      case 1:
      case 2:
        {
          unsigned int add_data, number;
          unsigned int number_byte_transmit, number_word_transmit, number_word_read;
          unsigned int offset;

          add_data = (*(received_buffer + 2))<<8 | (*(received_buffer + 3));
          number   = (*(received_buffer + 4))<<8 | (*(received_buffer + 5));
          
          number_byte_transmit = number >> 3;
          if((number_byte_transmit<<3) < number) number_byte_transmit++; //������� ��� ����� ������������� �� ������� ����� ��� ����� �� 8 (���� �� ��� ������� ����)

          //��������� ������� ������������� ��� (2 �����) � ������
          if ((number_byte_transmit & 0x1) == 0)
          {
            //����� ������� ����, � ������� ������ �� 2 ����� ����� ������� ���
            number_word_transmit = number_byte_transmit >> 1;
          }
          else
          {
            //������� ������� ����, � ������� ����� ������� �� 2 ����� �� ������ ���� ����, ��� �������� ������� ��� ��� ����������
            number_word_transmit = (number_byte_transmit + 1) >> 1;
          }
                   
          if(
             (number != 0                   ) &&
             (number_byte_transmit < (255-5)) &&
             (
#if (BIT_MA_OUTPUTS_LAST + 1) < BIT_MA_INPUTS_LAST
              ((add_data >= BIT_MA_OUTPUTS_BASE   ) && ((add_data + number - 1) <= BIT_MA_OUTPUTS_LAST   )) ||
              ((add_data >= BIT_MA_INPUTS_BASE    ) && ((add_data + number - 1) <= BIT_MA_INPUTS_LAST    )) ||
#else
              ((add_data >= BIT_MA_OUTPUTS_BASE   ) && ((add_data + number - 1) <= BIT_MA_INPUTS_LAST    )) ||
#endif
              ((add_data >= BIT_MA_LEDS_BASE      ) && ((add_data + number - 1) <= BIT_MA_LEDS_LAST      )) ||
              ((add_data >= BIT_MA_CONTROL_BASE   ) && ((add_data + number - 1) <= BIT_MA_CONTROL_LAST   )) ||
#if (BIT_MA_CURRENT_AF_LAST + 1) < BIT_MA_GENERAL_AF_BASE
              ((add_data >= BIT_MA_CURRENT_AF_BASE) && ((add_data + number - 1) <= BIT_MA_CURRENT_AF_LAST)) ||
              ((add_data >= BIT_MA_GENERAL_AF_BASE) && ((add_data + number - 1) <= BIT_MA_GENERAL_AF_LAST)) 
#else
              ((add_data >= BIT_MA_CURRENT_AF_BASE) && ((add_data + number - 1) <= BIT_MA_GENERAL_AF_LAST)) 
#endif
             )
            )
          {
            unsigned int first_address_of_word_for_function_3_or_4;

            //������� ������� ������
            *transmited_buffer = *(received_buffer);
            *(transmited_buffer + 1) = *(received_buffer + 1);
            *(transmited_buffer + 2) = number_byte_transmit;

#if (BIT_MA_OUTPUTS_LAST + 1) < BIT_MA_INPUTS_LAST            
            if((add_data >= BIT_MA_OUTPUTS_BASE   ) && ((add_data + number - 1) <= BIT_MA_OUTPUTS_LAST   ))
            {
              //���� ������
              offset = add_data - BIT_MA_OUTPUTS_BASE;
              first_address_of_word_for_function_3_or_4 = MA_OUTPUTS;
            }
            else if((add_data >= BIT_MA_INPUTS_BASE    ) && ((add_data + number - 1) <= BIT_MA_INPUTS_LAST    ))
            {
              //���� �����
              offset = add_data - BIT_MA_INPUTS_BASE;
              first_address_of_word_for_function_3_or_4 = MA_INPUTS;
            }
#else
            if((add_data >= BIT_MA_OUTPUTS_BASE   ) && ((add_data + number - 1) <= BIT_MA_INPUTS_LAST   ))
            {
              //���� ������ + �����
              offset = add_data - BIT_MA_OUTPUTS_BASE;
              first_address_of_word_for_function_3_or_4 = MA_OUTPUTS;
            }
#endif
            else if((add_data >= BIT_MA_LEDS_BASE      ) && ((add_data + number - 1) <= BIT_MA_LEDS_LAST      ))
            {
              //���� ��������������
              offset = add_data - BIT_MA_LEDS_BASE;
              first_address_of_word_for_function_3_or_4 = MA_LEDS;
            }
            else if((add_data >= BIT_MA_CONTROL_BASE   ) && ((add_data + number - 1) <= BIT_MA_CONTROL_LAST   ))
            {
              //���� ������� �������
              offset = add_data - BIT_MA_CONTROL_BASE;
              first_address_of_word_for_function_3_or_4 = MA_CONTROL_BASE;
            }
#if (BIT_MA_CURRENT_AF_LAST + 1) < BIT_MA_GENERAL_AF_BASE
            else if((add_data >= BIT_MA_CURRENT_AF_BASE) && ((add_data + number - 1) <= BIT_MA_CURRENT_AF_LAST))
            {
              //���� �������� �������
              offset = add_data - BIT_MA_CURRENT_AF_BASE;
              first_address_of_word_for_function_3_or_4 = M_ADDRESS_FIRST_CURRENT_AF;
            }
            else if((add_data >= BIT_MA_GENERAL_AF_BASE) && ((add_data + number - 1) <= BIT_MA_GENERAL_AF_LAST))
            {
              //���� �������� �������
              offset = add_data - BIT_MA_GENERAL_AF_BASE;
              first_address_of_word_for_function_3_or_4 = M_ADDRESS_FIRST_GENERAL_AF;
            }
#else
            else if((add_data >= BIT_MA_CURRENT_AF_BASE) && ((add_data + number - 1) <= BIT_MA_GENERAL_AF_LAST))
            {
              //���� �������� �������
              offset = add_data - BIT_MA_CURRENT_AF_BASE;
              first_address_of_word_for_function_3_or_4 = M_ADDRESS_FIRST_CURRENT_AF;
            }
#endif
            
            //���������, � ����� ����� ����� ��������� ���������� ������ �������
            first_address_of_word_for_function_3_or_4 += (offset >> 4);
            //��������� �� ������ �� ������
            offset &= 0xf;
            
            number_word_read = number_word_transmit;
            /*
            ��������� ������ ��� ����� ��������� (��������� ������ �� ������� �� 
            � � ������ �� �������� ��������� �� �����, ��� ���� ��������� �������� Get_data
            �  ������ �������, �� ���� ������ �� �� ���� �������� � ������ ������ ��� �������� ��������)
            ��� �� ��������� ������ ��� ����� ���� ��������� �������� Get_data ��� �������� ��� ��� ��������
            */
            if ((offset + number) > (number_word_transmit << 4)) number_word_read++; //�� ���� ��������� �� �������� ����� �� ������� �������
            
            //������� �������� ��� �����
            unsigned int i=0;
            while((i < number_word_read) && ((error = Get_data((transmited_buffer + 3 + 2*i), (first_address_of_word_for_function_3_or_4 + i), type_interface))==0)) i++;
          }
          else
          {
            if ((number == 0) || (number_byte_transmit >= (255-5))) error = ERROR_ILLEGAL_DATA_VALUE;
            else error = ERROR_ILLEGAL_DATA_ADDRESS;
          }
          
          //������� ����� ������ � ���� ������� � �������� MODBUS-RTU
          if (error == 0)
          {
            unsigned short int temp_value_for_offset, current_word, next_word;
            unsigned int maska = 0, max_bit_in_high_byte = (number & 0x7);
            
            for(unsigned int i = 0; i < number_word_transmit; i++)
            {
              //������� Get_data �������� ����� � ������� MSB-LSB � �.�
              current_word = (*(transmited_buffer + 3 + 2*i) << 8) | (*(transmited_buffer + 3 + 2*i + 1));
              if ((i + 1) < number_word_read) next_word = (*(transmited_buffer + 3 + 2*(i + 1)) << 8) | (*(transmited_buffer + 3 + 2*(i + 1) + 1));
              else next_word = 0;
              
              //��������� , �� ��� � ���������� ����� ����� ���������� � ���� ����� � ������ �� � ������ �������
              temp_value_for_offset = next_word << (16 - offset);
              
              //������� ����� �� ����������� �������
              temp_value_for_offset |= (current_word >> offset);
             
              if((2*i    ) < number_byte_transmit)
                *(transmited_buffer + 3 + 2*i    ) = temp_value_for_offset        & 0xff;
              if((2*i + 1) < number_byte_transmit)
                *(transmited_buffer + 3 + 2*i + 1) = (temp_value_for_offset >> 8) & 0xff;
            }
            
            //� ���������� ���� ����� ���� ��� ���������
            if (max_bit_in_high_byte != 0)
            {
              for(unsigned int i = 0; i < max_bit_in_high_byte; i++) maska = (maska << 1) + 0x1;
              *(transmited_buffer + 3 + number_byte_transmit - 1 ) &= maska;
            }
              
            CRC_sum = 0xffff;
            for (int index = 0; index < ((int)(number_byte_transmit + 3)); index++) CRC_sum = AddCRC(*(transmited_buffer + index),CRC_sum);
            *(transmited_buffer + 3 + number_byte_transmit + 0) = CRC_sum & 0xff;
            *(transmited_buffer + 3 + number_byte_transmit + 1) = CRC_sum >> 8;

            *transmited_count = number_byte_transmit + 5;
            if(type_interface == USB_RECUEST) data_usb_transmiting = true;
            else if(type_interface ==  RS485_RECUEST) start_transmint_data_via_RS_485(*transmited_count);
          }
          else
          {
            //³�������� ��� �������
            Error_modbus((unsigned char)current_settings.address, *(received_buffer+1), error, transmited_buffer);
            *transmited_count = 5;
            if(type_interface == USB_RECUEST) data_usb_transmiting = true;
            else if(type_interface ==  RS485_RECUEST) start_transmint_data_via_RS_485(*transmited_count);
          }
          
          break;
        }//ʳ���� ��� ������� ������� 1 � 2
      case 3:
      case 4:
        {
          unsigned int add_data, number;
          number   = (*(received_buffer + 4))<<8 | (*(received_buffer + 5));
          
          if ((number == 0) || (number > ((255-5)>>1)))
          {
            //������� ������ ������� �������
            error = ERROR_ILLEGAL_DATA_VALUE;
          }
          else
          {
            *transmited_buffer = *(received_buffer);
            *(transmited_buffer + 1) = *(received_buffer + 1) ;
            *(transmited_buffer + 2) = number*2;

            add_data = (*(received_buffer + 2))<<8 | (*(received_buffer + 3));

            if (
                ((add_data >= M_ADDRESS_FIRST_MEASUREMENTS_1 ) && (add_data <= M_ADDRESS_LAST_MEASUREMENTS_1)) ||
                ((add_data >= M_ADDRESS_FIRST_MEASUREMENTS_2 ) && (add_data <= M_ADDRESS_LAST_MEASUREMENTS_2)) ||
                ((add_data >= M_ADDRESS_FIRST_TMP_MEASURMENTS) && (add_data <  M_ADDRESS_LAST_TMP_MEASURMENTS))  
               )
            {
              //������� ����������
              semaphore_measure_values_low1 = 1;
              for (unsigned int i = 0; i < (NUMBER_ANALOG_CANALES + 8); i++ ) 
              {
                measurement_low[i] = measurement_middle[i];
              }
              semaphore_measure_values_low1 = 0;
            }

            unsigned int i=0;
            while((i<number) && ((error = Get_data((transmited_buffer+3+2*i),(add_data+i), type_interface))==0))i++;
          }

          if (error == 0)
          {
            CRC_sum = 0xffff;
            for (int index = 0; index < ((int)(3+2*number)); index++) CRC_sum = AddCRC(*(transmited_buffer + index),CRC_sum);
            *(transmited_buffer+3+2*number) = CRC_sum & 0xff;
            *(transmited_buffer+4+2*number) = CRC_sum >> 8;

            *transmited_count = 5+2*number;
            if(type_interface == USB_RECUEST) data_usb_transmiting = true;
            else if(type_interface ==  RS485_RECUEST) start_transmint_data_via_RS_485(*transmited_count);
          }
          else
          {
            Error_modbus((unsigned char)current_settings.address, *(received_buffer+1), error, transmited_buffer);
            *transmited_count = 5;
            if(type_interface == USB_RECUEST) data_usb_transmiting = true;
            else if(type_interface ==  RS485_RECUEST) start_transmint_data_via_RS_485(*transmited_count);
          }

          break;
        }//ʳ���� ��� ������� ������� 3 � 4
      case 5:
        {
          unsigned int add_data;
          unsigned short int value, temp_value = 0;
          unsigned int offset;
          unsigned int reinit_settings = 0;       
          
          add_data = (*(received_buffer + 2))<<8 | (*(received_buffer + 3));
          value    = (*(received_buffer + 4))<<8 | (*(received_buffer + 5));

          if ((type_interface != USB_RECUEST) && (type_interface != RS485_RECUEST))
          {
            //���������� ������ ���� �� ���� � �����
            error = ERROR_SLAVE_DEVICE_FAILURE;
          }
          else if(
                  (((value == 0 ) || (value == 0xff00)) && (add_data >= BIT_MA_CONTROL_BASE) && (add_data <= BIT_MA_CONTROL_LAST)) || /*��������� �������*/
                  (
                   (value == 0xff00) 
                   &&
                   (
                    (add_data == BIT_MA_RESET_GENERAL_AF) /*�������� ��������� �������*/
                    ||
                    (  
                     (_CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_MISCEVE_DYSTANCIJNE) == 0)
                     &&
                     (  
                      (add_data == BIT_MA_RESET_BLOCK_READY_TU_VID_ZAHYSTIV) /*�������� ���������� ��������� �� �� �� ������������ �������*/  
                      ||
                      (  
                       (_CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_READY_TU) != 0)
                       &&
                       (
                        ((add_data >= BIT_MA_INPUT_DF1) && (add_data <= BIT_MA_INPUT_DF8)) || /*����� ������������ �������*/
                        ((add_data >= BIT_MA_DT1_SET  ) && (add_data <= BIT_MA_DT4_RESET)) || /*������������ ��������*/
                        ( add_data == BIT_MA_VKL_VV                                      ) || /*���.  �����������*/
                        ( add_data == BIT_MA_OTKL_VV                                     ) || /*����. �����������*/
                        ( add_data == BIT_MA_RESET_LEDS                                  ) || /*�������� ���������*/
                        ( add_data == BIT_MA_RESET_RELES                                 ) || /*�������� ����*/
                        ( add_data == BIT_MA_RESET_RESURS_VYMYKACHA                      ) || /*�������� ������� ��������*/
                        (
                         (
                          (add_data == BIT_MA_RESET_BLOCK_APV_ZMN)    /*�������� ��������� ���-���*/
                         )
                         &&
                         ((current_settings.configuration & (1 << APV_ZMN_BIT_CONFIGURATION)) !=0 ) /*���-��� �������� � ������������*/  
                        ) ||
                        (
                         (
                          (add_data == BIT_MA_OTKL_AVR             ) || /*³��������� ���*/
                          (add_data == BIT_MA_SBROS_BLOCK_AVR      )    /*�������� ��������� ���*/
                         )
                         &&
                         ((current_settings.configuration & (1 << AVR_BIT_CONFIGURATION)) !=0 ) /*��� �������� � ������������*/  
                        )
                       )   
                      )
                     )    
                    )
                   )   
                  )
                 )
          {
            unsigned int first_address_of_word_for_function_3_or_4;
           
            //��������� ���������� ������� ������ � ������� ������� ���� ������� ���
            if ((add_data >= BIT_MA_CONTROL_BASE) && (add_data <= BIT_MA_CONTROL_LAST))
            {
              //���� ������� �������
              offset = add_data - BIT_MA_CONTROL_BASE;
              first_address_of_word_for_function_3_or_4 = MA_CONTROL_BASE;
            }
            else if ((add_data >= BIT_MA_INPUT_DF1) && (add_data <= BIT_MA_INPUT_DF8))
            {
              offset = add_data - BIT_MA_DF_BASE;
              first_address_of_word_for_function_3_or_4 = M_ADDRESS_DF;
            }
            else if (( add_data >= BIT_MA_DT1_SET) && (add_data <= BIT_MA_DT4_RESET ))
            {
              offset = add_data - BIT_MA_DT_BASE;
              first_address_of_word_for_function_3_or_4 = M_ADDRESS_DT;
            }
            else if(
                    (add_data == BIT_MA_RESET_BLOCK_APV_ZMN)    /*�������� ��������� ���-���*/
                   )
            {
              offset = add_data - BIT_MA_APV_ZMN_BASE;
              first_address_of_word_for_function_3_or_4 = M_ADDRESS_APV_ZMN;
            }
            else if(
                    (add_data == BIT_MA_OTKL_AVR             ) || /*³��������� ���*/
                    (add_data == BIT_MA_SBROS_BLOCK_AVR      )    /*�������� ��������� ���*/
                   )
            {
              offset = add_data - BIT_MA_AVR_BASE;
              first_address_of_word_for_function_3_or_4 = M_ADDRESS_AVR;
            }
            else if(
                    (add_data == BIT_MA_VKL_VV                ) || /*���.  �����������*/
                    (add_data == BIT_MA_OTKL_VV               ) || /*����. �����������*/
                    (add_data == BIT_MA_RESET_LEDS            ) || /*�������� ���������*/
                    (add_data == BIT_MA_RESET_RELES           ) || /*�������� ����*/
                    (add_data == BIT_MA_RESET_GENERAL_AF      ) || /*�������� ��������� �������*/
                    (add_data == BIT_MA_RESET_RESURS_VYMYKACHA) || /*�������� ������� ��������*/
                    (add_data == BIT_MA_RESET_BLOCK_READY_TU_VID_ZAHYSTIV) /*�������� ���������� ��������� �� �� �� �������*/
                   )
            {
              offset = add_data - BIT_MA_COMMAND_BASE;
              first_address_of_word_for_function_3_or_4 = M_ADDRESS_COMMAND_BASE;
            }
            
            //�������� ��
            if (first_address_of_word_for_function_3_or_4 == MA_CONTROL_BASE)
            {
              //��� ��������� ������ ��������� �������
              
              ///����������, �� ������ ������� ������ � �� ������� ���� �� � � ���� �����������
              if (
                  (
                   ((type_interface == USB_RECUEST  ) && (password_set_USB   == 0)) ||
                   ((type_interface == RS485_RECUEST) && (password_set_RS485 == 0))
                  )
                  &&  
                  (current_ekran.edition == 0)
                 )
              {
                //����� ��������� ����� ���, ���� ������ ������ � ������� ���� �� � ����� �����������, ��� ��� ������� ���������
            
                //���������, � ����� ����� ����� ��������� ���������� ������ �������
                first_address_of_word_for_function_3_or_4 += (offset >> 4);

                //��������� �� ������ ������� ���������� � ���������� ����
                offset &= 0xf;
            
                //������� �������� ���� �����
                unsigned char temp_value_in_char[2];
                error = Get_data(temp_value_in_char, first_address_of_word_for_function_3_or_4, type_interface);
                temp_value = temp_value_in_char[1];
                temp_value |= temp_value_in_char[0] << 8;

                if (error == 0)
                {
                  //���� ������ ���������� �����, �� ������� ����, ���� ����� �������� 
                  if (value == 0xff00) temp_value |=   (1 << offset); //����������
                  else if (value == 0x0)temp_value &= ~(1 << offset); //�����
                  else error = ERROR_ILLEGAL_DATA_VALUE;              //����������� ��������, ��� ���������� ����� �� ���� ������� �� ���������� �� �� ����� ��� �������� � �� �������� �������� �� �����������

                  if (error == 0)
                  {
                    /*
                    ������ ���� ����� changed_settings, ��� ��� �������� �����
                    ���� ��������� �������� �������� ��������. ������� � ��������� ����
                    ������� ���� CHANGED_ETAP_ENDED -> CHANGED_ETAP_NONE,
                    �� � ����� ����� "�������������" �� ���������, ���� �� ��������� 
                    ���� ��������� CHANGED_ETAP_ENDED, ���� ���� ���������� ������
                    ������� ������� ������ ������� ��������� � ����� ����� � 
                    CHANGED_ETAP_NONE, � ���� ���������� �������� ������
                    ������ ���� ���� � ���������, �� ������� �� ����, �� �� � ���� �������
                    �������� �������� �������� (�� ���� �������� �������) CHANGED_ETAP_ENDED.
                    �� � �����, �������� ����� ���� ���� ����� �������� ��������� ������� ���������.
                    */
                    unsigned int changed_settings_tmp = changed_settings;
                    
                    //�������, �� �����, �������, ���� ��������� ���� ������
                    changed_settings = CHANGED_ETAP_EXECUTION;
                    error = Set_data(temp_value,first_address_of_word_for_function_3_or_4, SET_DATA_IMMEDITATE, false, type_interface);
                    if (error == 0)
                    {
                      //ĳ���� �������� ���� ���������
                      reinit_settings = 1;
                      
                      /*
                      ���� ����� changed_settings � CHANGED_ETAP_EXECUTION
                      � CHANGED_ETAP_ENDED ���������� � ������� fix_change_settings
                      */
                    }
                    else
                    {
                      /*
                      ���� ��������� �� ��������, ���� ���������� �������� ��������
                      ����� changed_settings, ��� ���� �� �� ������������ � ��������
                      CHANGED_ETAP_EXECUTION
                      */
                      
                      changed_settings = changed_settings_tmp;
                    }
                  }
                }
              }
              else
              {
                if (current_ekran.edition != 0) error = ERROR_SLAVE_DEVICE_BUSY;
                else error = ERROR_ILLEGAL_DATA_ADDRESS;
              }
            }
            else if (
                     (
                      ((first_address_of_word_for_function_3_or_4 == M_ADDRESS_DF) || (first_address_of_word_for_function_3_or_4 == M_ADDRESS_DT))
                      &&
                      (
                       ((type_interface == USB_RECUEST  ) && (password_set_USB   == 0)) ||
                       ((type_interface == RS485_RECUEST) && (password_set_RS485 == 0))
                      ) 
                     )
                     ||  
                     (first_address_of_word_for_function_3_or_4 == M_ADDRESS_APV_ZMN)
                     ||  
                     (first_address_of_word_for_function_3_or_4 == M_ADDRESS_AVR)
                     ||  
                     (first_address_of_word_for_function_3_or_4 == M_ADDRESS_COMMAND_BASE)
                    )
            {
              //��� ������ ��������� �������
              
              /*
              ��� �� ������������� ���������� ��������� ������� � ��������� �-������, �� ������� ������� ��������� �� ���������
              ������� � �-������, �� ��������� ������� � ���������
              */
              if       (add_data == BIT_MA_RESET_BLOCK_APV_ZMN              ) activation_function_from_interface |= 1 << RANG_BUTTON_RESET_BLOCK_APV_ZMN;               /*�������� ��������� ���-���*/
              else if  (add_data == BIT_MA_OTKL_AVR                         ) activation_function_from_interface |= 1 << RANG_BUTTON_OTKL_AVR;                          /*³��������� ���*/
              else if  (add_data == BIT_MA_SBROS_BLOCK_AVR                  ) activation_function_from_interface |= 1 << RANG_BUTTON_SBROS_BLOCK_AVR;                   /*�������� ��������� ���*/
              else if  (add_data == BIT_MA_INPUT_DF1                        ) activation_function_from_interface |= 1 << RANG_BUTTON_DF1_IN;                            /*��1*/
              else if  (add_data == BIT_MA_INPUT_DF2                        ) activation_function_from_interface |= 1 << RANG_BUTTON_DF2_IN;                            /*��2*/
              else if  (add_data == BIT_MA_INPUT_DF3                        ) activation_function_from_interface |= 1 << RANG_BUTTON_DF3_IN;                            /*��3*/
              else if  (add_data == BIT_MA_INPUT_DF4                        ) activation_function_from_interface |= 1 << RANG_BUTTON_DF4_IN;                            /*��4*/
              else if  (add_data == BIT_MA_INPUT_DF5                        ) activation_function_from_interface |= 1 << RANG_BUTTON_DF5_IN;                            /*��5*/
              else if  (add_data == BIT_MA_INPUT_DF6                        ) activation_function_from_interface |= 1 << RANG_BUTTON_DF6_IN;                            /*��6*/
              else if  (add_data == BIT_MA_INPUT_DF7                        ) activation_function_from_interface |= 1 << RANG_BUTTON_DF7_IN;                            /*��7*/
              else if  (add_data == BIT_MA_INPUT_DF8                        ) activation_function_from_interface |= 1 << RANG_BUTTON_DF8_IN;                            /*��8*/
              else if  (add_data == BIT_MA_DT1_SET                          ) activation_function_from_interface |= 1 << RANG_BUTTON_DT1_SET;                           /*���. ��1*/
              else if  (add_data == BIT_MA_DT1_RESET                        ) activation_function_from_interface |= 1 << RANG_BUTTON_DT1_RESET;                         /*����. ��1*/
              else if  (add_data == BIT_MA_DT2_SET                          ) activation_function_from_interface |= 1 << RANG_BUTTON_DT2_SET;                           /*���. ��2*/
              else if  (add_data == BIT_MA_DT2_RESET                        ) activation_function_from_interface |= 1 << RANG_BUTTON_DT2_RESET;                         /*����. ��2*/
              else if  (add_data == BIT_MA_DT3_SET                          ) activation_function_from_interface |= 1 << RANG_BUTTON_DT3_SET;                           /*���. ��3*/
              else if  (add_data == BIT_MA_DT3_RESET                        ) activation_function_from_interface |= 1 << RANG_BUTTON_DT3_RESET;                         /*����. ��3*/
              else if  (add_data == BIT_MA_DT4_SET                          ) activation_function_from_interface |= 1 << RANG_BUTTON_DT4_SET;                           /*���. ��4*/
              else if  (add_data == BIT_MA_DT4_RESET                        ) activation_function_from_interface |= 1 << RANG_BUTTON_DT4_RESET;                         /*����. ��4*/
              else if  (add_data == BIT_MA_VKL_VV                           ) activation_function_from_interface |= 1 << RANG_BUTTON_VKL_VV;                            /*���.  �����������*/
              else if  (add_data == BIT_MA_OTKL_VV                          ) activation_function_from_interface |= 1 << RANG_BUTTON_OTKL_VV;                           /*����. �����������*/
              else if  (add_data == BIT_MA_RESET_LEDS                       ) activation_function_from_interface |= 1 << RANG_BUTTON_RESET_LEDS;                        /*�������� ���������*/
              else if  (add_data == BIT_MA_RESET_RELES                      ) activation_function_from_interface |= 1 << RANG_BUTTON_RESET_RELES;                       /*�������� ����*/
              else if  (add_data == BIT_MA_RESET_BLOCK_READY_TU_VID_ZAHYSTIV) activation_function_from_interface |= 1 << RANG_BUTTON_RESET_BLOCK_READY_TU_VID_ZAHYSTIV;                            /*���.  �����������*/
              else if  (add_data == BIT_MA_RESET_GENERAL_AF) 
              {
                //�������� ��������� ������� 
                reset_trigger_function_from_interface |= (1 << type_interface);
              }
              else if  (add_data == BIT_MA_RESET_RESURS_VYMYKACHA)
              {
                restart_counter = 0xff; /*������ ��� �������� ������� ��������� � ������� �������*/
              }
            }
            else
            {
              //���������� ���� �������� ����� �� ����� �����
              
              error = ERROR_ILLEGAL_DATA_ADDRESS;
            }
          }
          else
          {
            if (
                ((value != 0x0) && (value != 0xff00)) ||
                (
                 (value == 0x0) 
                 &&
                 (  
                  (add_data == BIT_MA_RESET_GENERAL_AF) /*�������� ��������� �������*/
                  ||
                  (  
                   (_CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_MISCEVE_DYSTANCIJNE) == 0)
                   &&
                   (  
                    (add_data == BIT_MA_RESET_BLOCK_READY_TU_VID_ZAHYSTIV) /*�������� ���������� ��������� �� �� �� ������������ �������*/  
                    ||
                    (
                     (_CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_READY_TU) != 0)
                     &&
                     (
                      ((add_data >= BIT_MA_INPUT_DF1) && (add_data <= BIT_MA_INPUT_DF8)) || /*����� ������������ �������*/
                      ((add_data >= BIT_MA_DT1_SET ) && (add_data <= BIT_MA_DT4_RESET )) || /*�����. ������*/
                      ( add_data == BIT_MA_VKL_VV                                      ) || /*���.  �����������*/
                      ( add_data == BIT_MA_OTKL_VV                                     ) || /*����. �����������*/
                      ( add_data == BIT_MA_RESET_LEDS                                  ) || /*�������� ���������*/
                      ( add_data == BIT_MA_RESET_RELES                                 ) || /*�������� ����*/
                      ( add_data == BIT_MA_RESET_RESURS_VYMYKACHA                      ) || /*�������� ������� ��������*/
                      (
                       (
                        (add_data == BIT_MA_RESET_BLOCK_APV_ZMN)    /*�������� ��������� ���-���*/
                       )
                       &&
                       ((current_settings.configuration & (1 << APV_ZMN_BIT_CONFIGURATION)) !=0 ) /*���-��� �������� � ������������*/  
                      ) ||
                      (
                       (
                        (add_data == BIT_MA_OTKL_AVR             ) || /*³��������� ���*/
                        (add_data == BIT_MA_SBROS_BLOCK_AVR      )    /*�������� ��������� ���*/
                       )
                       &&
                       ((current_settings.configuration & (1 << AVR_BIT_CONFIGURATION)) !=0 ) /*��� �������� � ������������*/  
                      )
                     )   
                    )
                   )
                  )
                 )   
                )
               ) error = ERROR_ILLEGAL_DATA_VALUE;
            else error = ERROR_ILLEGAL_DATA_ADDRESS;
          }
          
          if (error == 0)
          {
            for (int index = 0; index < 8; index++) *(transmited_buffer + index ) = *(received_buffer + index );
            *transmited_count = 8;
            if(type_interface == USB_RECUEST) data_usb_transmiting = true;
            else if(type_interface ==  RS485_RECUEST) start_transmint_data_via_RS_485(*transmited_count);

            if (reinit_settings != 0)
            {
              if(type_interface == USB_RECUEST) fix_change_settings(0, 2);
              else if(type_interface ==  RS485_RECUEST) fix_change_settings(0, 3);

              //����������� �������, �� �� ����� ����� �������� ����������
              new_state_keyboard |= (1<<BIT_REWRITE);
            }
          }
          else
          {
            //³�������� ��� �������
            Error_modbus((unsigned char)current_settings.address, *(received_buffer+1), error, transmited_buffer);
            *transmited_count = 5;
            if(type_interface == USB_RECUEST) data_usb_transmiting = true;
            else if(type_interface ==  RS485_RECUEST) start_transmint_data_via_RS_485(*transmited_count);
          }
          break;
        }//ʳ���� ��� ������� ������� 5        
      case 6:
        {
          unsigned int add_data;
          unsigned short int data;
          unsigned int changing_settings = 0, changing_ustuvannja = 0;

          add_data = (*(received_buffer + 2))<<8 | (*(received_buffer + 3));
          data     = (*(received_buffer + 4))<<8 | (*(received_buffer + 5));

          if ((type_interface != USB_RECUEST) && (type_interface != RS485_RECUEST))
          {
            //���������� ������ ���� �� ���� � �����
            error = ERROR_SLAVE_DEVICE_FAILURE;
          }
          else if (
                   (global_requect != 0) && /*����� �� ����� BROADCAST_ADDRESS_MODBUS_RTU ��������� Modbus-RTU*/
                   (
                    !(
                      ((add_data >= M_ADDRESS_FIRST_TIME_AND_DATA) && (add_data <= M_ADDRESS_LAST_TIME_AND_DATA))
                     )
                   )     
                  )
          {
            /*
            �� �������� ����� ����� �������� ����� ��� � ����
            */
            error = ERROR_BROADCAST_ADDRESS;
          }
          else if (
                   (current_ekran.edition == 0                              ) ||
                   (add_data              == MA_CURRENT_NUMBER_RECORD_AR    ) ||
                   (add_data              == MA_CURRENT_NUMBER_RECORD_DR    ) ||
                   (add_data              == MA_CURRENT_NUMBER_RECORD_PR_ERR)  
                  )
          {
            /*****/
            //�������� �� ����������� ������ ������� ��� ������
            /*****/
            if (
                (
                 ((type_interface == USB_RECUEST  ) && (password_set_USB   != 0)) ||
                 ((type_interface == RS485_RECUEST) && (password_set_RS485 != 0))
                )
                &&
                (
                 ((add_data >= M_ADDRESS_FIRST_SETPOINTS_PART1                 ) && (add_data <= M_ADDRESS_LAST_SETPOINTS_PART1                 )                                       ) || /*������� � ��������*/
                 ((add_data >= (M_ADDRESS_FIRST_SETPOINTS_ZACHYSTIV + SHIFT_G1)) && (add_data <= (M_ADDRESS_LAST_SETPOINTS_ZACHYSTIV + SHIFT_G1))                                       ) || /*������� � �������� ����� �����*/
                 ((add_data >= (M_ADDRESS_FIRST_SETPOINTS_ZACHYSTIV + SHIFT_G2)) && (add_data <= (M_ADDRESS_LAST_SETPOINTS_ZACHYSTIV + SHIFT_G2))                                       ) || /*������� � �������� ����� �����*/
                 ((add_data >= (M_ADDRESS_FIRST_SETPOINTS_ZACHYSTIV + SHIFT_G3)) && (add_data <= (M_ADDRESS_LAST_SETPOINTS_ZACHYSTIV + SHIFT_G3))                                       ) || /*������� � �������� ������ �����*/
                 ((add_data >= (M_ADDRESS_FIRST_SETPOINTS_ZACHYSTIV + SHIFT_G4)) && (add_data <= (M_ADDRESS_LAST_SETPOINTS_ZACHYSTIV + SHIFT_G4))                                       ) || /*������� � �������� �������� �����*/
                 ((add_data >= M_ADDRESS_FIRST_SETPOINTS_CONTINUE              ) && (add_data <= M_ADDRESS_LAST_SETPOINTS_CONTINUE              ) && (add_data != MA_PASSWORD_INTERFACE)) || /*������� � �������� (�����������) � ������������ ��� ������ �������*/
                 ((add_data >= M_ADDRESS_FIRST_TIME_AND_DATA                   ) && (add_data <= M_ADDRESS_LAST_TIME_AND_DATA                   )                                       ) || /*���*/
                 ((add_data >= M_ADDRESS_FIRST_SETPOINTS_RANG                  ) && (add_data <= M_ADDRESS_LAST_SETPOINTS_RANG                  )                                       ) || /*����������*/
                 ((add_data >= M_ADDRESS_FIRST_SETPOINTS_RANG_AR               ) && (add_data <= M_ADDRESS_LAST_SETPOINTS_RANG_AR               )                                       ) || /*���������� ����������� ����������*/
                 ((add_data >= MA_PREFAULT_INTERVAL_AR                         ) && (add_data <= MA_POSTFAULT_INTERVAL_AR                       )                                       ) || /*������������ ������ �����������/������������� ������ ����������� ����������*/
                 ((add_data >= M_ADDRESS_FIRST_SETPOINTS_RANG_DR               ) && (add_data <= M_ADDRESS_LAST_SETPOINTS_RANG_DR               )                                       ) || /*���������� ����������� ����������*/
                  (add_data == MA_CLEAR_NUMBER_RECORD_PR_ERR                   )                                                                                                          || /*�������� ���������� ���������� ����*/        
                  (add_data == MA_CLEAR_NUMBER_RECORD_AR                       )                                                                                                          || /*�������� ����������� ����������*/        
                  (add_data == MA_CLEAR_NUMBER_RECORD_DR                       )                                                                                                          || /*�������� ����������� ����������*/        
                  (add_data == MA_DEFAULT_SETTINGS                             )                                                                                                          || /*������������ �������� ������������*/        
                  (add_data == MA_TEST_WATCHDOGS                               )                                                                                                          || /*���������� ����������� � ���������� watchdog*/        
                  (add_data == MA_CLEAR_ENERGY                                 )                                                                                                             /*�������� ������ ��������� ������*/        
                )   
               )
            {
              //�� ����� ����� �������� ��� ������, �� ����� �������� ����� ������ �������
              error = ERROR_ILLEGAL_DATA_ADDRESS;
            }
            else
            {
              unsigned int changed_settings_tmp, changed_ustuvannja_tmp; /*���� �������������� �����*/
              
              if ((add_data >= M_ADDRESS_FIRST_TIME_AND_DATA) && (add_data <= M_ADDRESS_LAST_TIME_AND_DATA))
              {
                if (_CHECK_SET_BIT(control_i2c_taskes, TASK_START_WRITE_RTC_BIT) == 0)
                {  
                  //��� ��������� ���������� ����� ���-����, ���� ������ ���� ����
                  unsigned char *label_to_time_array, *label_calibration;
                  if (copying_time == 0)
                  {
                    label_to_time_array = time;
                    label_calibration = &calibration;
                  }
                  else
                  {
                    label_to_time_array = time_copy;
                    label_calibration = &calibration_copy;
                  }
                  for(unsigned int index = 0; index < 7; index++) time_edit[index] = *(label_to_time_array + index);
                  calibration_edit = *label_calibration;
                }
                else
                {
                  /*
                  �� ���������� ��������� ������� ������ ����, � ���� ���� ������ 
                  ���������� ������ ��� ��� �������� �������� ���� (��� ���� ������� ����� ����)
                  ���� �� �������� � ��������� �����������
                  */
                  error = ERROR_SLAVE_DEVICE_BUSY;
                }
              }
              else if(
                      ((add_data >= M_ADDRESS_FIRST_SETPOINTS_PART1                 ) && (add_data <= M_ADDRESS_LAST_SETPOINTS_PART1                 )                                       ) || /*������� � ��������*/
                      ((add_data >= (M_ADDRESS_FIRST_SETPOINTS_ZACHYSTIV + SHIFT_G1)) && (add_data <= (M_ADDRESS_LAST_SETPOINTS_ZACHYSTIV + SHIFT_G1))                                       ) || /*������� � �������� ����� �����*/
                      ((add_data >= (M_ADDRESS_FIRST_SETPOINTS_ZACHYSTIV + SHIFT_G2)) && (add_data <= (M_ADDRESS_LAST_SETPOINTS_ZACHYSTIV + SHIFT_G2))                                       ) || /*������� � �������� ����� �����*/
                      ((add_data >= (M_ADDRESS_FIRST_SETPOINTS_ZACHYSTIV + SHIFT_G3)) && (add_data <= (M_ADDRESS_LAST_SETPOINTS_ZACHYSTIV + SHIFT_G3))                                       ) || /*������� � �������� ������ �����*/
                      ((add_data >= (M_ADDRESS_FIRST_SETPOINTS_ZACHYSTIV + SHIFT_G4)) && (add_data <= (M_ADDRESS_LAST_SETPOINTS_ZACHYSTIV + SHIFT_G4))                                       ) || /*������� � �������� �������� �����*/
                      ((add_data >= M_ADDRESS_FIRST_SETPOINTS_CONTINUE              ) && (add_data <= M_ADDRESS_LAST_SETPOINTS_CONTINUE              ) && (add_data != MA_PASSWORD_INTERFACE)) || /*������� � �������� (�����������) � ������������ ��� ������ �������*/
                      ((add_data >= M_ADDRESS_FIRST_SETPOINTS_RANG                  ) && (add_data <= M_ADDRESS_LAST_SETPOINTS_RANG                  )                                       ) || /*����������*/
                      ((add_data >= M_ADDRESS_FIRST_SETPOINTS_RANG_AR               ) && (add_data <= M_ADDRESS_LAST_SETPOINTS_RANG_AR               )                                       ) || /*���������� ����������� ����������*/
                      ((add_data >= MA_PREFAULT_INTERVAL_AR                         ) && (add_data <= MA_POSTFAULT_INTERVAL_AR                       )                                       ) || /*������������ ������ �����������/������������� ������ ����������� ����������*/
                      ((add_data >= M_ADDRESS_FIRST_SETPOINTS_RANG_DR               ) && (add_data <= M_ADDRESS_LAST_SETPOINTS_RANG_DR               )                                       ) || /*���������� ����������� ����������*/
                       (add_data == MA_DEFAULT_SETTINGS                             )                                                                                              /*������������ �������� ������������*/        
                     ) 
              {
                //������� ���������� ���������, �� ��� ��������� ������ ���������
                changing_settings = 0xff;
                
                /*
                ������ ���� ����� changed_settings, ��� ��� �������� �����
                ���� ��������� �������� �������� ��������. ������� � ��������� ����
                ������� ���� CHANGED_ETAP_ENDED -> CHANGED_ETAP_NONE,
                �� � ����� ����� "�������������" �� ���������, ���� �� ��������� 
                ���� ��������� CHANGED_ETAP_ENDED, ���� ���� ���������� ������
                ������� ������� ������ ������� ��������� � ����� ����� � 
                CHANGED_ETAP_NONE, � ���� ���������� �������� ������
                ������ ���� ���� � � ���������, �� ������� �� ����, �� �� � ���� �������
                �������� �������� �������� (�� ���� �������� �������) CHANGED_ETAP_ENDED.
                �� � �����, �������� ����� ���� ���� ����� �������� ��������� ������� ���������.
                */
                changed_settings_tmp = changed_settings;
                if(
                   ((add_data >= M_ADDRESS_FIRST_SETPOINTS_RANG   ) && (add_data <= M_ADDRESS_LAST_SETPOINTS_RANG   )) || /*����������*/
                   ((add_data >= M_ADDRESS_FIRST_SETPOINTS_RANG_AR) && (add_data <= M_ADDRESS_LAST_SETPOINTS_RANG_AR)) || /*���������� ����������� ����������*/
                   ((add_data >= M_ADDRESS_FIRST_SETPOINTS_RANG_DR) && (add_data <= M_ADDRESS_LAST_SETPOINTS_RANG_DR))    /*���������� ����������� ����������*/
                  )
                {
                  //���������� ��� ����, �� ����� ���� ���������� ����������, �� ������� �������� �� ��������� ���� � 0
                  point_to_edited_rang = NULL;
                  clear_array_rang[0] = 0;
                  clear_array_rang[1] = 0;
                  clear_array_rang[2] = 0;
                  clear_array_rang[3] = 0;
                  clear_array_rang[4] = 0;
                  clear_array_rang[5] = 0;
                  
                  set_array_rang[0] = 0;
                  set_array_rang[1] = 0;
                  set_array_rang[2] = 0;
                  set_array_rang[3] = 0;
                  set_array_rang[4] = 0;
                  set_array_rang[5] = 0;
                }
                
                //�������, �� �����, �������, ���� ��������� ���� ������
                changed_settings = CHANGED_ETAP_EXECUTION;
                
              }
              else if((add_data >= MA_ADDRESS_FIRST_USTUVANNJA) && (add_data <= MA_ADDRESS_LAST_PHI_USTUVANNJA))/*�������� � ���� ������� �����������*/ 
              {
                //������� ���������� ���������, �� ��� ��������� ������ ������� �����������
                changing_ustuvannja = 0xff;
                
                /*
                ������ ���� ����� changed_ustuvannja, ��� ��� �������� �����
                ���� ����������� ��������� �������� �������� ��������. ������� � ��������� ����
                ������� ���� CHANGED_ETAP_ENDED -> CHANGED_ETAP_NONE,
                �� � ����� ����� "�������������" �� ���������, ���� �� ��������� 
                ���� ��������� CHANGED_ETAP_ENDED, ���� ���� ���������� ������
                ����������� ������� ������ ����������� ��������� � ����� ����� � 
                CHANGED_ETAP_NONE, � ���� ���������� �������� ������
                ������ ���� ���� � � ����� ���������, �� ������� �� ����, �� �� � ���� �������
                �������� �������� �������� (�� ���� ������������ ��������) CHANGED_ETAP_ENDED.
                �� � �����, �������� ����� ���� ���� ����� �������� ��������� ������ ���������.
                */
                changed_ustuvannja_tmp = changed_ustuvannja;

                //�������, �� �����, �������, ������� ��������� ���� �������
                changed_ustuvannja = CHANGED_ETAP_EXECUTION;
              }

              if (error == 0)
              {
                error = Set_data(data,add_data, SET_DATA_IMMEDITATE, false, type_interface);
                if (error != 0)
                {
                  if (changing_settings != 0)
                  {
                    /*
                    ���� ��������� �� ��������, ���� ���������� �������� ��������
                    ����� changed_settings, ��� ���� �� �� ������������ � ��������
                    CHANGED_ETAP_EXECUTION
                    */
                    changed_settings = changed_settings_tmp;
                  }

                  if (changing_ustuvannja != 0)
                  {
                    /*
                    ���� ����������� ��������� �� ��������, ���� ���������� �������� ��������
                    ����� changed_ustuvannja, ��� ���� �� �� ������������ � ��������
                    CHANGED_ETAP_EXECUTION
                    */
                    changed_ustuvannja = changed_ustuvannja_tmp;
                  }
                }
              }
            }
          }
          else error = ERROR_SLAVE_DEVICE_BUSY;
             
          /*****/
          //���� � ������ ���������� ���, �� ������ ���� ��������, �� ��� �� ���� �������� �� �������� ���
          /*****/
          if ((error == 0) && (add_data >= M_ADDRESS_FIRST_TIME_AND_DATA) && (add_data <= M_ADDRESS_LAST_TIME_AND_DATA))
          {
            //������������ ������ ����-����

            //���������� ����������� �����
            if (check_data_for_data_time_menu() == 1)
            {
              //��� ��������
              //����������� ����������� ������ ���� � RTC
              //��� ����� ����������� �� ���������� ��������� ������� ��������, ��� ����������������� � ������� ����������� �������
              _SET_BIT(control_i2c_taskes, TASK_START_WRITE_RTC_BIT);
              _SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT);
            }
            else error = ERROR_ILLEGAL_DATA_VALUE;
          }
          /*****/
           
          if(error == 0)
          {
            if  (global_requect == 0)
            {
              for (int index = 0; index < 8; index++) *(transmited_buffer + index ) = *(received_buffer + index );
              *transmited_count = 8;
              if(type_interface == USB_RECUEST) data_usb_transmiting = true;
              else if(type_interface ==  RS485_RECUEST) start_transmint_data_via_RS_485(*transmited_count);
            }
            else
            {
              if(type_interface == RS485_RECUEST)
              {
                //������������� ��������� �� RS-485
                restart_monitoring_RS485();
              }
            }
            
            /*****/
            //��� ����������� �������� ���������� � EEPROM
            /*****/
            if (
                ((add_data >= M_ADDRESS_FIRST_SETPOINTS_PART1                 ) && (add_data <= M_ADDRESS_LAST_SETPOINTS_PART1                 )) ||
                ((add_data >= (M_ADDRESS_FIRST_SETPOINTS_ZACHYSTIV + SHIFT_G1)) && (add_data <= (M_ADDRESS_LAST_SETPOINTS_ZACHYSTIV + SHIFT_G1))) ||
                ((add_data >= (M_ADDRESS_FIRST_SETPOINTS_ZACHYSTIV + SHIFT_G2)) && (add_data <= (M_ADDRESS_LAST_SETPOINTS_ZACHYSTIV + SHIFT_G2))) ||
                ((add_data >= (M_ADDRESS_FIRST_SETPOINTS_ZACHYSTIV + SHIFT_G3)) && (add_data <= (M_ADDRESS_LAST_SETPOINTS_ZACHYSTIV + SHIFT_G3))) ||
                ((add_data >= (M_ADDRESS_FIRST_SETPOINTS_ZACHYSTIV + SHIFT_G4)) && (add_data <= (M_ADDRESS_LAST_SETPOINTS_ZACHYSTIV + SHIFT_G4))) ||
                ((add_data >= M_ADDRESS_FIRST_SETPOINTS_CONTINUE              ) && (add_data <= M_ADDRESS_LAST_SETPOINTS_CONTINUE              )) ||
                ((add_data >= M_ADDRESS_FIRST_SETPOINTS_RANG                  ) && (add_data <= M_ADDRESS_LAST_SETPOINTS_RANG                  )) ||
                ((add_data >= M_ADDRESS_FIRST_SETPOINTS_RANG_AR               ) && (add_data <= M_ADDRESS_LAST_SETPOINTS_RANG_AR               )) ||
                ((add_data >= MA_PREFAULT_INTERVAL_AR                         ) && (add_data <= MA_POSTFAULT_INTERVAL_AR                       )) ||
                ((add_data >= M_ADDRESS_FIRST_SETPOINTS_RANG_DR               ) && (add_data <= M_ADDRESS_LAST_SETPOINTS_RANG_DR               )) 
               )
            {
              //�������� ���������, ��� ���������� �� ���������
              
              if (
                  (
                   (add_data == MA_PASSWORD_INTERFACE)
                   &&
                   (  
                    (  
                     ((type_interface == USB_RECUEST  ) && (password_set_USB   == 1) && (previous_password_interface != current_settings.password_interface_USB  )) ||  
                     ((type_interface == RS485_RECUEST) && (password_set_RS485 == 1) && (previous_password_interface != current_settings.password_interface_RS485))  
                    )/*�������, ���� �������������� ����� ������ ������� ������� �� 0 (� ������ ������)*/
                    ||
                    (
                     ((type_interface == USB_RECUEST  ) && (current_settings.password_interface_USB   == 0) && (previous_password_interface != current_settings.password_interface_USB  )) || 
                     ((type_interface == RS485_RECUEST) && (current_settings.password_interface_RS485 == 0) && (previous_password_interface != current_settings.password_interface_RS485)) 
                    )/*�������, ���� �������������� ����� ������ ������� �����        0 (���� ������ ������)*/ 
                   )   
                  )
                  ||  
                  ( add_data != MA_PASSWORD_INTERFACE) /*������������ ��� ����� ���������� �� ���������� (�� ����������� ������ �������)*/ 
                 )   
              {
                //��������� ��� �������, ���� �������� ������ ������ �������
                   
                //�������� ���������
                if (
                    ((add_data >= M_ADDRESS_FIRST_SETPOINTS_RANG   ) && (add_data <= M_ADDRESS_LAST_SETPOINTS_RANG   )) ||
                    ((add_data >= M_ADDRESS_FIRST_SETPOINTS_RANG_AR) && (add_data <= M_ADDRESS_LAST_SETPOINTS_RANG_AR)) ||
                    ((add_data >= M_ADDRESS_FIRST_SETPOINTS_RANG_DR) && (add_data <= M_ADDRESS_LAST_SETPOINTS_RANG_DR)) 
                   )
                {
                  if(point_to_edited_rang != NULL)
                  {
                    //������ �������� �� �� ������ � �������� ����� ��� �������� ����������
                    //(�� ������� �������� ������ ��������� ����� �������� ������)
                    set_previous_ranguvannja();
                  }
                    
                  //�������� ��������� �� ����������
                  if(type_interface == USB_RECUEST) fix_change_settings(1, 2);
                  else if(type_interface ==  RS485_RECUEST) fix_change_settings(1, 3);
                }
                else
                {
                  //���� ����������� ������������� ���������� RS-485, �� �������������� ����
                  if ((add_data >= MA_SPEED_RS485) && (add_data <= MA_TIMEOUT_RS485))
                  {
                    //ϳ��������� ���� �������� �������� � ����, ��� ����������� �� ������� � RS-485 ����� � ����������� �����������
                    calculate_namber_bit_waiting_for_rs_485();
                    //����������� ������� ��� ������������������ RS-485
                    if (add_data != MA_TIMEOUT_RS485) make_reconfiguration_RS_485 = 0xff;
                  }
                    
                  //�������� ��������� ���������� (��� ����������)
                  if(type_interface == USB_RECUEST) fix_change_settings(0, 2);
                  else if(type_interface ==  RS485_RECUEST) fix_change_settings(0, 3);
                }

                //����������� �������, �� �� ����� ����� �������� ����������
                new_state_keyboard |= (1<<BIT_REWRITE);
              }
            }
            else if (
                     ((add_data >= MA_ADDRESS_FIRST_USTUVANNJA) && (add_data <= MA_ADDRESS_LAST_PHI_USTUVANNJA)) ||
                     ( add_data == MA_SET_SERIAL_NUMBER)  
                    )
            {
              if (
                  ((add_data >= MA_ADDRESS_FIRST_USTUVANNJA) && (add_data <= MA_ADDRESS_LAST_PHI_USTUVANNJA))
                 )   
              {
                //�������, �� ������������ �������� ����� ������� ��� ����������� ���������
                changed_ustuvannja = CHANGED_ETAP_ENDED;
              }
              //����� �������� �����������
              _SET_BIT(control_i2c_taskes, TASK_START_WRITE_USTUVANNJA_EEPROM_BIT);
            }
            else if (add_data == MA_DEFAULT_SETTINGS)
            {
              //³������� ������ ������� �������� � �������� ������������
              
              //������ ������, ��  �� ��������� ������� � ���������� ������������
              fix_change_settings(0, 0);
              fix_change_settings(1, 0);
      
              //����������������� RS-485
              //ϳ��������� �������� �������� � ����, ��� ����������� �� ������� � RS-485 ����� � ����������� �����������
              calculate_namber_bit_waiting_for_rs_485();
              //����������� ������� ��� ������������������ RS-485
              make_reconfiguration_RS_485 = 0xff;
              
              if (current_settings.password_interface_RS485 == 0) password_set_RS485 = 0;
              else password_set_RS485 = 1;
              if (current_settings.password_interface_USB   == 0) password_set_USB   = 0;
              else password_set_USB   = 1;

              //����������� �������, �� �� ����� ����� �������� ����������
              new_state_keyboard |= (1<<BIT_REWRITE);
            }
            /*****/
          }
          else 
          {
            if (global_requect == 0)
            {
              Error_modbus((unsigned char)current_settings.address, *(received_buffer+1), error, transmited_buffer);
              *transmited_count = 5;
              if(type_interface == USB_RECUEST) data_usb_transmiting = true;
              else if(type_interface ==  RS485_RECUEST) start_transmint_data_via_RS_485(*transmited_count);
            }
            else
            {
              if(type_interface == RS485_RECUEST)
              {
                //������������� ��������� �� RS-485
                restart_monitoring_RS485();
              }
            }
          }
          break;
        }//ʳ���� ��� ������� ������� 6
      case 15:
        {
          unsigned int add_data, number, reinit_settings = 0;       
        
          add_data = (*(received_buffer + 2))<<8 | (*(received_buffer + 3));
          number   = (*(received_buffer + 4))<<8 | (*(received_buffer + 5));

          unsigned int number_bytes = number >> 3;
          if ((number_bytes << 3) != number) number_bytes++;
        
          if ((type_interface != USB_RECUEST) && (type_interface != RS485_RECUEST))
          {
            //���������� ������ ���� �� ���� � �����
            error = ERROR_SLAVE_DEVICE_FAILURE;
          }
          else if ((number < 1) || (number > 0x7B0) || (number_bytes != *(received_buffer + 6)))
              error= ERROR_ILLEGAL_DATA_VALUE;
          else if (
                   ((add_data >= BIT_MA_CONTROL_BASE) && ((add_data + number - 1) <= BIT_MA_CONTROL_LAST))
                   ||
                   (
                    ((add_data >= BIT_MA_RESET_GENERAL_AF) && ((add_data + number - 1) <= BIT_MA_RESET_GENERAL_AF))
                    ||
                    (
                     (_CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_MISCEVE_DYSTANCIJNE) == 0)
                     &&
                     (  
                      ((add_data >= BIT_MA_RESET_BLOCK_READY_TU_VID_ZAHYSTIV) && ((add_data + number - 1) <= BIT_MA_RESET_BLOCK_READY_TU_VID_ZAHYSTIV))
                      ||  
                      (
                       (_CHECK_SET_BIT(active_functions, RANG_OUTPUT_LED_DF_REG_READY_TU) != 0)
                       &&  
                       (
                        ((add_data >= BIT_MA_RESET_BLOCK_APV_ZMN) && ((add_data + number - 1) <= BIT_MA_RESET_BLOCK_APV_ZMN   )) || 
                        ((add_data >= BIT_MA_OTKL_AVR           ) && ((add_data + number - 1) <= BIT_MA_SBROS_BLOCK_AVR       )) || 
                        ((add_data >= BIT_MA_INPUT_DF1          ) && ((add_data + number - 1) <= BIT_MA_INPUT_DF8             )) || 
                        ((add_data >= BIT_MA_DT1_SET            ) && ((add_data + number - 1) <= BIT_MA_DT4_RESET             )) ||
                        ((add_data >= BIT_MA_VKL_VV             ) && ((add_data + number - 1) <= BIT_MA_OTKL_VV               )) ||
                        ((add_data >= BIT_MA_RESET_LEDS         ) && ((add_data + number - 1) <= BIT_MA_RESET_RESURS_VYMYKACHA))
                       )
                      )
                     )   
                    )   
                   ) 
                  )
          {
            unsigned int first_address_of_word_for_function_3_or_4;
            unsigned int offset;

            if((add_data >= BIT_MA_CONTROL_BASE) && (add_data <= BIT_MA_CONTROL_LAST))
            {
              //���� ������� �������
              offset = add_data - BIT_MA_CONTROL_BASE;
              first_address_of_word_for_function_3_or_4 = MA_CONTROL_BASE;
            }
            else if((add_data >= BIT_MA_RESET_BLOCK_APV_ZMN) && (add_data <= BIT_MA_RESET_BLOCK_APV_ZMN))
            {
              //������� ���-���
              offset = add_data - BIT_MA_APV_ZMN_BASE;
              first_address_of_word_for_function_3_or_4 = M_ADDRESS_APV_ZMN;
            }
            else if((add_data >= BIT_MA_OTKL_AVR) && (add_data <= BIT_MA_SBROS_BLOCK_AVR))
            {
              //������� ���
              offset = add_data - BIT_MA_AVR_BASE;
              first_address_of_word_for_function_3_or_4 = M_ADDRESS_AVR;
            }
            else if((add_data >= BIT_MA_INPUT_DF1) && (add_data <= BIT_MA_INPUT_DF8)) /*���������� �������*/
            {
              offset = add_data - BIT_MA_DF_BASE;
              first_address_of_word_for_function_3_or_4 = M_ADDRESS_DF;
            }
            else if((add_data >= BIT_MA_DT1_SET) && (add_data <= BIT_MA_DT4_RESET)) /*�����. ������*/
            {
              offset = add_data - BIT_MA_DT_BASE;
              first_address_of_word_for_function_3_or_4 = M_ADDRESS_DT;
            }
            else if(
                    ((add_data >= BIT_MA_VKL_VV                           ) && (add_data <= BIT_MA_OTKL_VV               )) ||
                    ((add_data >= BIT_MA_RESET_LEDS                       ) && (add_data <= BIT_MA_RESET_RESURS_VYMYKACHA)) ||
                    ( add_data == BIT_MA_RESET_BLOCK_READY_TU_VID_ZAHYSTIV)
                   )
            {
              //������� �������
              offset = add_data - BIT_MA_COMMAND_BASE;
              first_address_of_word_for_function_3_or_4 = M_ADDRESS_COMMAND_BASE;
            }

            if (
                (first_address_of_word_for_function_3_or_4 >= MA_CONTROL_BASE) &&
                (first_address_of_word_for_function_3_or_4 <= MA_CONTROL_LAST)
               )
            {
              //��� ��������� ������ ����������, ��� ���������� �� ���������
              
              //���������� �� ������ �� �� �������� ����� ��������
              if (
                  (
                   ((type_interface == USB_RECUEST  ) && (password_set_USB   == 0)) ||
                   ((type_interface == RS485_RECUEST) && (password_set_RS485 == 0))
                  )   
                  &&
                  (current_ekran.edition == 0)
                 )
              {
                //�������� ������ � ���������

                //������ ���� ������� ���������
                edition_settings  = current_settings;

                //��������� ��������� ������ �������/������ ������ �������
                first_address_of_word_for_function_3_or_4 += (offset >> 4);
                //��������� ������� � ���������� ����
                offset &= 0xf;
                
                //������� �������� ���� �����
                unsigned short int temp_value;
                unsigned char temp_value_in_char[2];
                error = Get_data(temp_value_in_char,first_address_of_word_for_function_3_or_4, type_interface);
                temp_value = temp_value_in_char[1];
                temp_value |= temp_value_in_char[0] << 8;

                unsigned int index_byte = 0, index_bit, index_of_bit_in_target_word;
                unsigned char temp_data;
                unsigned int i = 0;
                index_of_bit_in_target_word = offset;//���������� ����� ���
                while ((i < number) && (error == 0))
                {
                  //������� ���� ���������� �� �������� �������������, � �� ������� ��������� ��������, �� � ��� ����� �������� ��-������
                  index_bit  = i &  0x7; //�������� ����� �������� �� ��������� �������� ������ ��� ����� ����� ����� �� 8 - ����� �� ���������� ������ ��� � �������� "������" �������
            
                  //����� ���� ������� ����� ���� ����� ��� � 0, �� ������ ���� ��� � ��������
                  if (index_bit == 0)
                  {
                    index_byte = i >> 3  ; //������� �� ��� ������� ������ ��������� �������� ���� ������� ��� ����� ����� ����� �� 8 - ����� �� ���������� ������ ����� � �������� "������" �������
                    temp_data = *(received_buffer + 7 + index_byte);
                  }
            
                  //�������� �������� ���, ��� ����� ����������
                  unsigned int value_of_bit;
                  value_of_bit = ((temp_data << (7 - index_bit)) >> 7) & 0x1;
            
                  //� ����, ��� ������� �������� ������� � ���� ��, ���� �� �������
                  //�� ������ ����� ��� ��� �������, �� ����� ������� - ��� ��� ����� �� �������� �� ��������!!!
                  temp_value &= (unsigned short)(~(1 << index_of_bit_in_target_word));

                  //����� ����������� �������� ��
                  temp_value |=  (value_of_bit << index_of_bit_in_target_word);
  
                  //�������� ����� ���
                  i++;
                  //���������� ����� ���������� ���, ���� ����� ������
                  index_of_bit_in_target_word = ((offset + i) & 0xf);//�������� ������ �������� �� ��������� �������� ������ ��� ����� ����� ����� �� 16 - ����� �� ���������� ������ ��� � ��������� ����
            
                  /*
                  � ���, ���� ������ ���������� �������� ��� � ���� ��� ���� �� �������� ������� ��,
                  �� ������� ����� �������� �������� ������������ ����� � ���� � �� ��� ��� ������, �� ������� ���� �����
                  */
                  if ((index_of_bit_in_target_word == 0) || (i == number))
                  {
                    //�������� �������� ���� ��������
                    error = Set_data(temp_value, first_address_of_word_for_function_3_or_4, SET_DATA_INTO_EDIT_TABLE, (i < number), type_interface); /*��� � ��� ��������� �� �������, ���� �������� ����������� (i) � (number)*/
                    if (error == 0)
                    {
                      if (reinit_settings == 0) reinit_settings = 1; //�������, �� ����� ���� �������� ����� ����� ��������� � EEPROM

                      //���� � �� ��� ��� ������, �� ������� ���� �����
                      if (i < number)
                      {
                        //�������� ������ ����� � ����� ����� ����������� ����
                        first_address_of_word_for_function_3_or_4++;
  
                        //������� ���� �����
                        error = Get_data(temp_value_in_char,first_address_of_word_for_function_3_or_4, type_interface);
                        temp_value = temp_value_in_char[1];
                        temp_value |= temp_value_in_char[0] << 8;
                      }
                    }
                  }
                }
              }
              else
              {
                if (current_ekran.edition != 0) error = ERROR_SLAVE_DEVICE_BUSY;
                else error = ERROR_ILLEGAL_DATA_ADDRESS;
              }
            }
            else if (
                     (
                      (
                       (first_address_of_word_for_function_3_or_4 == M_ADDRESS_DF) || 
                       (first_address_of_word_for_function_3_or_4 == M_ADDRESS_DT)
                      )
                      &&
                      (
                       ((type_interface == USB_RECUEST  ) && (password_set_USB   == 0)) ||
                       ((type_interface == RS485_RECUEST) && (password_set_RS485 == 0))
                      ) 
                     )
                     ||  
                     (first_address_of_word_for_function_3_or_4 == M_ADDRESS_APV_ZMN)
                     ||  
                     (first_address_of_word_for_function_3_or_4 == M_ADDRESS_AVR)
                     ||  
                     (first_address_of_word_for_function_3_or_4 == M_ADDRESS_COMMAND_BASE)  
                    )
            {
              //��� ������ ��������� ������ �������������
              
              /*
              ��� �� ������������� ��������� ��������� ������� � ��������� �-������, �� ������� ������� ��������� �� ���������
              ������� � �-������, �� ��������� ������� � ���������
              */
              
              unsigned int index_byte = 0, index_bit, number_activated_function;
              unsigned char temp_data;
              unsigned int i = 0;
              unsigned int activation_function_from_interface_tmp = 0, reset_trigger_functions = 0, restart_counter_tmp = 0;
              while ((i < number) && (error == 0))
              {
                //������� ���� ���������� �� �������� ������������� ��������� ��������, �� � ��� ����� �������� ��-������
                index_bit  = i &  0x7; //�������� ����� �������� �� ��������� �������� ������ ��� ����� ����� ����� �� 8 - ����� �� ���������� ������ ��� � �������� "������" �������
            
                //����� ���� ������� ����� ���� ����� ��� � 0, �� ������ ���� ��� � ��������
                if (index_bit == 0)
                {
                  index_byte = i >> 3  ; //������� �� ��� ������� ������ ��������� �������� ���� ������� ��� ����� ����� ����� �� 8 - ����� �� ���������� ������ ����� � �������� "������" �������
                  temp_data = *(received_buffer + 7 + index_byte);
                }
            
                //�������� �������� ���, ��� ����� ����������
                unsigned int value_of_bit;
                value_of_bit = ((temp_data << (7 - index_bit)) >> 7) & 0x1;
                
                if (value_of_bit != 0)
                {
                  //��� ��������� �-������� �� ������ ������ � ���� ���������� ����� ��������� ("1") �� ������� ����������� ��� ������� ����
                  number_activated_function = add_data + i;
                  if       (number_activated_function == BIT_MA_RESET_BLOCK_APV_ZMN) 
                    activation_function_from_interface_tmp |= 1 << RANG_BUTTON_RESET_BLOCK_APV_ZMN;           /*�������� ��������� ���-���*/
                  else if  (number_activated_function == BIT_MA_OTKL_AVR        ) 
                    activation_function_from_interface_tmp |= 1 << RANG_BUTTON_OTKL_AVR;                      /*³��������� ���*/
                  else if  (number_activated_function == BIT_MA_SBROS_BLOCK_AVR ) 
                    activation_function_from_interface_tmp |= 1 << RANG_BUTTON_SBROS_BLOCK_AVR;               /*�������� ��������� ���*/
                  else if  (number_activated_function == BIT_MA_INPUT_DF1                        ) 
                    activation_function_from_interface_tmp |= 1 << RANG_BUTTON_DF1_IN;                        /*��1*/
                  else if  (number_activated_function == BIT_MA_INPUT_DF2                        ) 
                    activation_function_from_interface_tmp |= 1 << RANG_BUTTON_DF2_IN;                        /*��2*/
                  else if  (number_activated_function == BIT_MA_INPUT_DF3                        ) 
                    activation_function_from_interface_tmp |= 1 << RANG_BUTTON_DF3_IN;                        /*��3*/
                  else if  (number_activated_function == BIT_MA_INPUT_DF4                        ) 
                    activation_function_from_interface_tmp |= 1 << RANG_BUTTON_DF4_IN;                        /*��4*/
                  else if  (number_activated_function == BIT_MA_INPUT_DF5                        ) 
                    activation_function_from_interface_tmp |= 1 << RANG_BUTTON_DF5_IN;                        /*��5*/
                  else if  (number_activated_function == BIT_MA_INPUT_DF6                        ) 
                    activation_function_from_interface_tmp |= 1 << RANG_BUTTON_DF6_IN;                        /*��6*/
                  else if  (number_activated_function == BIT_MA_INPUT_DF7                        ) 
                    activation_function_from_interface_tmp |= 1 << RANG_BUTTON_DF7_IN;                        /*��7*/
                  else if  (number_activated_function == BIT_MA_INPUT_DF8                        ) 
                    activation_function_from_interface_tmp |= 1 << RANG_BUTTON_DF8_IN;                        /*��8*/
                  else if  (number_activated_function == BIT_MA_DT1_SET                          ) 
                    activation_function_from_interface_tmp |= 1 << RANG_BUTTON_DT1_SET;                       /*��������. �����. ��. 1*/
                  else if  (number_activated_function == BIT_MA_DT1_RESET                        ) 
                    activation_function_from_interface_tmp |= 1 << RANG_BUTTON_DT1_RESET;                     /*����. �����. ��. 1*/
                  else if  (number_activated_function == BIT_MA_DT2_SET                          ) 
                    activation_function_from_interface_tmp |= 1 << RANG_BUTTON_DT2_SET;                       /*��������. �����. ��. 2*/
                  else if  (number_activated_function == BIT_MA_DT2_RESET                        ) 
                    activation_function_from_interface_tmp |= 1 << RANG_BUTTON_DT2_RESET;                     /*����. �����. ��. 2*/
                  else if  (number_activated_function == BIT_MA_DT3_SET                          ) 
                    activation_function_from_interface_tmp |= 1 << RANG_BUTTON_DT3_SET;                       /*��������. �����. ��. 3*/
                  else if  (number_activated_function == BIT_MA_DT3_RESET                        ) 
                    activation_function_from_interface_tmp |= 1 << RANG_BUTTON_DT3_RESET;                     /*����. �����. ��. 3*/
                  else if  (number_activated_function == BIT_MA_DT4_SET                          ) 
                    activation_function_from_interface_tmp |= 1 << RANG_BUTTON_DT4_SET;                       /*��������. �����. ��. 4*/
                  else if  (number_activated_function == BIT_MA_DT4_RESET                        ) 
                    activation_function_from_interface_tmp |= 1 << RANG_BUTTON_DT4_RESET;                     /*����. �����. ��. 4*/
                  else if  (number_activated_function == BIT_MA_VKL_VV                           )
                   activation_function_from_interface_tmp |= 1 << RANG_BUTTON_VKL_VV;                        /*���.  �����������*/
                  else if  (number_activated_function == BIT_MA_OTKL_VV                          )
                    activation_function_from_interface_tmp |= 1 << RANG_BUTTON_OTKL_VV;                       /*����. �����������*/
                  else if  (number_activated_function == BIT_MA_RESET_LEDS                       )
                    activation_function_from_interface_tmp |= 1 << RANG_BUTTON_RESET_LEDS;                    /*�������� ���������*/
                  else if  (number_activated_function == BIT_MA_RESET_RELES                      )
                    activation_function_from_interface_tmp |= 1 << RANG_BUTTON_RESET_RELES;                   /*�������� ����*/
                  else if  (number_activated_function == BIT_MA_RESET_BLOCK_READY_TU_VID_ZAHYSTIV)
                    activation_function_from_interface_tmp |= 1 << RANG_BUTTON_RESET_BLOCK_READY_TU_VID_ZAHYSTIV;/*�������� ���������� ��������� �� �� �� �������*/
                  else if  (number_activated_function == BIT_MA_RESET_GENERAL_AF                 ) 
                  {
                    //�������� ��������� ������� 
                    reset_trigger_functions = 0xff; /*��������� �������� ������, �� ����� ������� ������� �������*/
                  }
                  else if  (number_activated_function == BIT_MA_RESET_RESURS_VYMYKACHA)
                  {
                    //�������� ��������� �������
                    restart_counter_tmp = 0xff;
                  }
                  else 
                  {
                    //���������� ���� �������� ����� �� ����� �����
                    error = ERROR_ILLEGAL_DATA_ADDRESS;
                  }
                }

                i++;
              }

              if (error == 0)
              {
                if (activation_function_from_interface_tmp != 0)
                {
                  activation_function_from_interface |= activation_function_from_interface_tmp;
                }
                if (reset_trigger_functions != 0)
                {
                  reset_trigger_function_from_interface |= (1 << type_interface);
                }
                if (restart_counter_tmp != 0)
                {
                  restart_counter = 0xff;
                }
              }
            }
            else
            {
              //���������� ���� �������� ����� �� ����� �����
              error = ERROR_ILLEGAL_DATA_ADDRESS;
            }
          }
          else
            error = ERROR_ILLEGAL_DATA_ADDRESS;

          if (error == 0)
          {
            CRC_sum = 0xffff;
            for (int index = 0; index < 6; index++)
            {
              *(transmited_buffer + index ) = *(received_buffer + index );
              CRC_sum = AddCRC(*(transmited_buffer + index),CRC_sum);
            }
            *(transmited_buffer + 6) = CRC_sum & 0xff;
            *(transmited_buffer + 7) = CRC_sum >> 8;

            *transmited_count = 8;
            if(type_interface == USB_RECUEST) data_usb_transmiting = true;
            else if(type_interface ==  RS485_RECUEST) start_transmint_data_via_RS_485(*transmited_count);
          
            if (reinit_settings != 0)
            {
              //�������, �� ���� ��������� ����� ������ �����
              changed_settings = CHANGED_ETAP_EXECUTION;
              
              //������� ������ ���� � ������ ���������
              current_settings = edition_settings;

              if(type_interface == USB_RECUEST) fix_change_settings(0, 2);
              else if(type_interface ==  RS485_RECUEST) fix_change_settings(0, 3);

              //����������� �������, �� �� ����� ����� �������� ����������
              new_state_keyboard |= (1<<BIT_REWRITE);
            }
          }
          else
          {
            //³�������� ��� �������
            Error_modbus((unsigned char)current_settings.address, *(received_buffer+1), error, transmited_buffer);
            *transmited_count = 5;
            if(type_interface == USB_RECUEST) data_usb_transmiting = true;
            else if(type_interface ==  RS485_RECUEST) start_transmint_data_via_RS_485(*transmited_count);
          }
          break;
        }//ʳ���� ��� ������� ������� 15        
      case 16:
        {
          unsigned int add_data, number;
          unsigned int reinit_ustuvannja = 0, reinit_settings = 0, change_timeout_ar = 0, reinit_ranguvannja = 0, set_min_param = 0, reconfiguration_RS_485 = 0, reconfiguration_RS_485_with_reset_usart = 0;
          unsigned int setting_new_rtc = 0;
            
          add_data = (*(received_buffer + 2))<<8 | (*(received_buffer + 3));
          number   = (*(received_buffer + 4))<<8 | (*(received_buffer + 5));

          //������ ������������/�������������� ������ �������
          unsigned int before_password_set;
          if (type_interface == USB_RECUEST) before_password_set = password_set_USB;
          else if (type_interface == RS485_RECUEST) before_password_set = password_set_RS485;
          else error= ERROR_SLAVE_DEVICE_FAILURE;

          if ((number < 1) || (number > 0x7B) || ((*(received_buffer + 6)) != ( number <<1)))
            error= ERROR_ILLEGAL_DATA_VALUE;
          else if (
                   (global_requect != 0) && /*����� �� ����� BROADCAST_ADDRESS_MODBUS_RTU ��������� Modbus-RTU*/
                   (
                    !(
                      ((add_data >= M_ADDRESS_FIRST_TIME_AND_DATA) && ((add_data + number - 1) <= M_ADDRESS_LAST_TIME_AND_DATA))
                     )
                   )     
                  )
          {
            /*
            �� �������� ����� ����� �������� ����� ��� � ����
            */
            error = ERROR_BROADCAST_ADDRESS;
          }

          //�������� ������� ������� ���
          unsigned int i = 0;
          while((i < number) && (error == 0 ))
          {
            unsigned short int data = (*(received_buffer+7+2*i))<<8 | (*(received_buffer+8+2*i));

            if (
                (current_ekran.edition == 0                                      ) ||
                (add_data              == MA_CURRENT_NUMBER_RECORD_AR    ) ||
                (add_data              == MA_CURRENT_NUMBER_RECORD_DR    ) ||
                (add_data              == MA_CURRENT_NUMBER_RECORD_PR_ERR)  
               )
            {
              /*****/
              //�������� �� ����������� ������ ������� ��� ������
              /*****/
              if (
                  ((add_data >= M_ADDRESS_FIRST_SETPOINTS_PART1                 ) && (add_data <= M_ADDRESS_LAST_SETPOINTS_PART1                 )) || /*������� � ��������*/
                  ((add_data >= (M_ADDRESS_FIRST_SETPOINTS_ZACHYSTIV + SHIFT_G1)) && (add_data <= (M_ADDRESS_LAST_SETPOINTS_ZACHYSTIV + SHIFT_G1))) || /*������� � �������� ����� �����*/
                  ((add_data >= (M_ADDRESS_FIRST_SETPOINTS_ZACHYSTIV + SHIFT_G2)) && (add_data <= (M_ADDRESS_LAST_SETPOINTS_ZACHYSTIV + SHIFT_G2))) || /*������� � �������� ����� �����*/
                  ((add_data >= (M_ADDRESS_FIRST_SETPOINTS_ZACHYSTIV + SHIFT_G3)) && (add_data <= (M_ADDRESS_LAST_SETPOINTS_ZACHYSTIV + SHIFT_G3))) || /*������� � �������� ������ �����*/
                  ((add_data >= (M_ADDRESS_FIRST_SETPOINTS_ZACHYSTIV + SHIFT_G4)) && (add_data <= (M_ADDRESS_LAST_SETPOINTS_ZACHYSTIV + SHIFT_G4))) || /*������� � �������� �������� �����*/
                  ((add_data >= M_ADDRESS_FIRST_SETPOINTS_CONTINUE              ) && (add_data <= M_ADDRESS_LAST_SETPOINTS_CONTINUE              )) || /*������� � �������� (�����������) � ������������ ��� ������ �������*/
                  ((add_data >= M_ADDRESS_FIRST_TIME_AND_DATA                   ) && (add_data <= M_ADDRESS_LAST_TIME_AND_DATA                   )) || /*���*/
                  ((add_data >= M_ADDRESS_FIRST_SETPOINTS_RANG                  ) && (add_data <= M_ADDRESS_LAST_SETPOINTS_RANG                  )) || /*����������*/
                  ((add_data >= M_ADDRESS_FIRST_SETPOINTS_RANG_AR               ) && (add_data <= M_ADDRESS_LAST_SETPOINTS_RANG_AR               )) || /*���������� ����������� ����������*/
                  ((add_data >= MA_PREFAULT_INTERVAL_AR                         ) && (add_data <= MA_POSTFAULT_INTERVAL_AR                       )) || /*������������ ������ �����������/������������� ������ ����������� ����������*/
                  ((add_data >= M_ADDRESS_FIRST_SETPOINTS_RANG_DR               ) && (add_data <= M_ADDRESS_LAST_SETPOINTS_RANG_DR               )) || /*���������� ����������� ����������*/
                   (add_data == MA_CLEAR_NUMBER_RECORD_PR_ERR                   )                                                                   || /*�������� ���������� ���������� ����*/
                   (add_data == MA_CLEAR_NUMBER_RECORD_AR                       )                                                                   || /*�������� ����������� ����������*/        
                   (add_data == MA_CLEAR_NUMBER_RECORD_DR                       )                                                                   || /*�������� ����������� ����������*/        
                   (add_data == MA_DEFAULT_SETTINGS                             )                                                                   || /*������������ �������� ������������*/        
                   (add_data == MA_CLEAR_ENERGY                                 )                                                                   || /*�������� ������ ��������� ������*/        
                   (add_data == MA_TEST_WATCHDOGS                               )                                                       /*���������� ����������� � ���������� watchdog*/        
                 )
              {
                if (
                    (add_data != MA_PASSWORD_INTERFACE) &&
                    (
                     ((type_interface == USB_RECUEST  ) && (password_set_USB != 0  )) ||
                     ((type_interface == RS485_RECUEST) && (password_set_RS485 != 0))
                    )   
                   )
                {
                  //�� ����� ����� �������� ��� ������, �� ����� �������� ����� ������ �������
                  error = ERROR_ILLEGAL_DATA_ADDRESS;
                }
                else if (
                         (number != 1)
                         &&
                         (  
                          (add_data == MA_CLEAR_NUMBER_RECORD_PR_ERR) || /*�������� ���������� ���������� ����*/
                          (add_data == MA_CLEAR_NUMBER_RECORD_AR    ) || /*�������� ����������� ����������*/        
                          (add_data == MA_CLEAR_NUMBER_RECORD_DR    ) || /*�������� ����������� ����������*/        
                          (add_data == MA_DEFAULT_SETTINGS          ) || /*������������ �������� ������������*/        
                          (add_data == MA_CLEAR_ENERGY              ) || /*�������� ������ ��������� ������*/        
                          (add_data == MA_TEST_WATCHDOGS            )    /*���������� ����������� � ���������� watchdog*/        
                         )   
                        )
                {
                  //ֳ ������� ������ ���������� �������� ����� �� ���� ������ - ������ ����������� ��� �������
                  error = ERROR_ILLEGAL_DATA_ADDRESS;
                }
                else
                {
                  //����� ���������� ��� ��� ��� ���������
                
                  //���� � ���� ���������� �� ������ ��� ������ ���� �������� �� ��������� (��� ����) �� ������ ���� ��������� ���������
                  if (
                      (
                       (reinit_settings    == 0) && 
                       (reinit_ranguvannja == 0)
                      )/*�� �� ���������� ����� ����������, ���� �� �� �������� ���� ������� ���������*/ 
                      &&  
                      ( 
                       !(
                         (add_data >= M_ADDRESS_FIRST_TIME_AND_DATA) && 
                         (add_data <= M_ADDRESS_LAST_TIME_AND_DATA ) 
                        )/*���� ������� ��������� �� ����� ������ ���� �� ������������ ���*/
                      )    
                     )
                  {
                    //������ ���� ������� ���������
                    edition_settings  = current_settings;

                    //���������� ��� ����, �� ���� ����� ���������� ����������, �� ������� �������� �� ��������� ���� � 0
                    point_to_edited_rang = NULL;
                    clear_array_rang[0] = 0;
                    clear_array_rang[1] = 0;
                    clear_array_rang[2] = 0;
                    clear_array_rang[3] = 0;
                    clear_array_rang[4] = 0;
                    clear_array_rang[5] = 0;
                    
                    set_array_rang[0] = 0;
                    set_array_rang[1] = 0;
                    set_array_rang[2] = 0;
                    set_array_rang[3] = 0;
                    set_array_rang[4] = 0;
                    set_array_rang[5] = 0;
                  }

                  if (
                      (add_data >= M_ADDRESS_FIRST_TIME_AND_DATA) &&
                      (add_data <= M_ADDRESS_LAST_TIME_AND_DATA ) &&
                      (setting_new_rtc == 0                     )
                     )
                  {
                    if (_CHECK_SET_BIT(control_i2c_taskes, TASK_START_WRITE_RTC_BIT) == 0)
                    {  
                      //�������, �� ����� ������ ����� ��������� ���
                      setting_new_rtc = 1;

                      //������ ���� ����, ���� � ��������� �� ��� �� ��������� ����, ��������� �� �� ����������� � ����, ���� ������� ������ �����, �� �������� �� � ��������� RTC
                      unsigned char *label_to_time_array, *label_calibration;
                      if (copying_time == 0)
                      {
                        label_to_time_array = time;
                        label_calibration = &calibration;
                      }
                      else
                      {
                        label_to_time_array = time_copy;
                        label_calibration = &calibration_copy;
                      }
                      for(unsigned int index = 0; index < 7; index++) time_edit[index] = *(label_to_time_array + index);
                      calibration_edit = *label_calibration;
                    }
                    else
                    {
                      /*
                      �� ���������� ��������� ������� ������ ����, � ���� ���� ������ 
                      ���������� ������ ��� ��� �������� �������� ���� (��� ���� ������� ����� ����)
                      ���� �� �������� � ��������� �����������
                      */
                      error = ERROR_SLAVE_DEVICE_BUSY;
                    }
                  }
                
                  if (error == 0)
                  {
                    //������� ��� �������� ����� ��������� ���������
                    error = Set_data(data, add_data, SET_DATA_INTO_EDIT_TABLE, ((i + 1) < number), type_interface); /*��� � �� �� ��������� �� �������, ���� �������� �����������(i + 1) � (number)*/
                  }
                }
              }
              else
              {
                //ֳ ��� �� ���������� �������� �� ������
              
                if (
                    (add_data >= MA_ADDRESS_FIRST_USTUVANNJA) && (add_data <= MA_ADDRESS_LAST_PHI_USTUVANNJA) || /*������� �������� � ����� �����������*/
                    (add_data == MA_SET_SERIAL_NUMBER                                                       )    /*������� �����*/  
                   )
                {
                  //��������� ��� ��� ��� ��������� ��� ������� �����
              
                  //���� � ���� ���������� �� ������ ��� ������ ���� �������� �� ��������� �� ������ ���� ������ ���������
                  if (reinit_ustuvannja == 0)
                  {
                    for(unsigned int k = 0; k < NUMBER_ANALOG_CANALES; k++) 
                    {
                      edit_ustuvannja[k] = ustuvannja[k];
                      phi_edit_ustuvannja[k] = phi_ustuvannja[k];
                      phi_edit_ustuvannja_sin_cos[2*k] = phi_ustuvannja_sin_cos[2*k];
                      phi_edit_ustuvannja_sin_cos[2*k + 1] = phi_ustuvannja_sin_cos[2*k + 1];
                    }
                    edit_serial_number_dev = serial_number_dev;
                  }
                }
                //������� ��� �������� ����� ���������� ����� (��� �������� �� ��������������� ����� ��� ���������, � ��� ��� ����� ������� ��� ���� ���� ������ ��������� ��������� �������)
                error = Set_data(data, add_data, SET_DATA_INTO_EDIT_TABLE, ((i + 1) < number), type_interface); /*��� � �� �� ��������� �� �������, ���� �������� �����������(i + 1) � (number)*/
              }
            }
            else error = ERROR_SLAVE_DEVICE_BUSY;
              
            if (error == 0)
            {
              if (
                  ((add_data >= M_ADDRESS_FIRST_SETPOINTS_PART1                 ) && (add_data <= M_ADDRESS_LAST_SETPOINTS_PART1                 )) ||
                  ((add_data >= (M_ADDRESS_FIRST_SETPOINTS_ZACHYSTIV + SHIFT_G1)) && (add_data <= (M_ADDRESS_LAST_SETPOINTS_ZACHYSTIV + SHIFT_G1))) ||
                  ((add_data >= (M_ADDRESS_FIRST_SETPOINTS_ZACHYSTIV + SHIFT_G2)) && (add_data <= (M_ADDRESS_LAST_SETPOINTS_ZACHYSTIV + SHIFT_G2))) ||
                  ((add_data >= (M_ADDRESS_FIRST_SETPOINTS_ZACHYSTIV + SHIFT_G3)) && (add_data <= (M_ADDRESS_LAST_SETPOINTS_ZACHYSTIV + SHIFT_G3))) ||
                  ((add_data >= (M_ADDRESS_FIRST_SETPOINTS_ZACHYSTIV + SHIFT_G4)) && (add_data <= (M_ADDRESS_LAST_SETPOINTS_ZACHYSTIV + SHIFT_G4))) ||
                  ((add_data >= M_ADDRESS_FIRST_SETPOINTS_CONTINUE              ) && (add_data <= M_ADDRESS_LAST_SETPOINTS_CONTINUE              )) ||
                  ((add_data >= M_ADDRESS_FIRST_SETPOINTS_RANG                  ) && (add_data <= M_ADDRESS_LAST_SETPOINTS_RANG                  )) ||
                  ((add_data >= M_ADDRESS_FIRST_SETPOINTS_RANG_AR               ) && (add_data <= M_ADDRESS_LAST_SETPOINTS_RANG_AR               )) || 
                  ((add_data >= MA_PREFAULT_INTERVAL_AR                         ) && (add_data <= MA_POSTFAULT_INTERVAL_AR                       )) ||
                  ((add_data >= M_ADDRESS_FIRST_SETPOINTS_RANG_DR               ) && (add_data <= M_ADDRESS_LAST_SETPOINTS_RANG_DR               )) 
                 )
              {
                //�������� ���������, ��� ���������� �� ���������
                
                if (
                    (
                     (add_data == MA_PASSWORD_INTERFACE)
                     &&
                     (  
                      (  
                       ((type_interface == USB_RECUEST  ) && (password_set_USB   == 1) && (previous_password_interface != edition_settings.password_interface_USB  )) ||  
                       ((type_interface == RS485_RECUEST) && (password_set_RS485 == 1) && (previous_password_interface != edition_settings.password_interface_RS485))  
                      )/*�������, ���� �������������� ����� ������ ������� ������� �� 0 (� ������ ������)*/
                      ||
                      (
                       ((type_interface == USB_RECUEST  ) && (edition_settings.password_interface_USB   == 0) && (previous_password_interface != edition_settings.password_interface_USB  )) || 
                       ((type_interface == RS485_RECUEST) && (edition_settings.password_interface_RS485 == 0) && (previous_password_interface != edition_settings.password_interface_RS485)) 
                      )/*�������, ���� �������������� ����� ������ ������� �����        0 (���� ������ ������)*/ 
                     )   
                    )
                    ||  
                    ( add_data != MA_PASSWORD_INTERFACE) /*������������ ��� ����� ���������� �� ���������� (�� ����������� ������ �������)*/ 
                   )   
                {
                  //��������� ��� �������, ���� �������� ������ ������ �������
                  //�������� ���������
                  if (
                      ((add_data >= M_ADDRESS_FIRST_SETPOINTS_RANG   ) && (add_data <= M_ADDRESS_LAST_SETPOINTS_RANG   )) ||
                      ((add_data >= M_ADDRESS_FIRST_SETPOINTS_RANG_AR) && (add_data <= M_ADDRESS_LAST_SETPOINTS_RANG_AR)) ||
                      ((add_data >= M_ADDRESS_FIRST_SETPOINTS_RANG_DR) && (add_data <= M_ADDRESS_LAST_SETPOINTS_RANG_DR)) 
                     )
                  {
                    //�������, �� ����� �������� ��������� �� ����������
                    reinit_ranguvannja = 1;
                  }
                  else
                  {
                    //�������, �� ����� �������� ��������� �� ���������� (��� ����������)
                    reinit_settings = 1;
                    
                    if ((add_data >= MA_PREFAULT_INTERVAL_AR) && (add_data <= MA_POSTFAULT_INTERVAL_AR))
                    {
                      //�������, �� ��������� �� ����� ���� �������� 䳿 �� ��� ������� �������� ����������� ����������
                      change_timeout_ar = 1;
                    }
                    else if ((add_data >= MA_SPEED_RS485) && (add_data <= MA_TIMEOUT_RS485))
                    {
                      //�������, �� ����� ����������������� ��������� RS-485
                      reconfiguration_RS_485 = 1;
                        
                      if(add_data != MA_TIMEOUT_RS485)
                      {
                        //�������, �� ����� ����������������� USART ��� ���������� RS-485
                        reconfiguration_RS_485_with_reset_usart = 1;
                      }
                    }
                  }
                }
              }
              else if (
                       ((add_data >= MA_ADDRESS_FIRST_USTUVANNJA ) && (add_data <= MA_ADDRESS_LAST_PHI_USTUVANNJA)) ||
                       ( add_data == MA_SET_SERIAL_NUMBER)  
                      )
              {
                //�������, �� ����� �������� ������� �����������
                reinit_ustuvannja = 1;
              }
              else if (add_data == MA_DEFAULT_SETTINGS)
              {
                //�������� � �������� ������������
                set_min_param = 1;
              }
            }
            add_data++;
            i++;
          } 

          /*****/
          //���� ���� ������ ���������� ���-����, �� �������� ����� � ��������� RTC, �� ��� �� ���� �������� �� �������� ���
          /*****/
          if ((error == 0) && (setting_new_rtc != 0))
          {
            //������������ ������ ����-����

            //���������� ����������� �����
            if (check_data_for_data_time_menu() == 1)
            {
              //��� ��������
              //����������� ����������� ������ ���� � RTC
              //��� ����� ����������� �� ���������� ��������� ������� ��������, ��� ����������������� � ������� ����������� �������
              _SET_BIT(control_i2c_taskes, TASK_START_WRITE_RTC_BIT);
              _SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT);
            }
            else error = ERROR_ILLEGAL_DATA_VALUE;
          }
          /*****/

          /*****/
          /*
          ���� ���� ������ �������� ���������� �������� 16, �� ����� ������ �� �������� �� ���
          � ��������� �� ������ ���� ��� ������� �� ������� �� ����, �� ������� "������ ��" ���
          "������ ��" ��������� �� ������� ����, �� � ������������
          */
          /*****/
          if ((error == 0) && (reinit_ranguvannja != 0))
          {
            //���������� �� ������ ���� ��� ������ � �������� �����
            if(point_to_edited_rang != NULL)
            {
              //������ �������� �� �� ������ � �������� ����� ��� �������� ����������
              //(�� ������� �������� ������ ��������� ����� �������� ������)
              set_previous_ranguvannja();
            }
            
            //�������� �� ���������� ���������� ������� "������ ��" ��� "������ ��" �� ���������� ������
            unsigned int number_func_WORK_BV_into_outputs = 0, number_func_WORK_BO_into_outputs = 0;
            unsigned int maska_func_WORK_BV[N_BIG] = {0, 0, 0, 0, 0, 0}, maska_func_WORK_BO[N_BIG] = {0, 0, 0, 0, 0, 0};

            _SET_BIT(maska_func_WORK_BV, RANG_OUTPUT_LED_DF_REG_WORK_BV);
            _SET_BIT(maska_func_WORK_BO, RANG_OUTPUT_LED_DF_REG_WORK_BO);
            for (unsigned int k = 0; k < NUMBER_OUTPUTS; k++)
            {
              unsigned int target_sell[N_BIG];
              target_sell[0] = edition_settings.ranguvannja_outputs[N_BIG*k    ];
              target_sell[1] = edition_settings.ranguvannja_outputs[N_BIG*k + 1];
              target_sell[2] = edition_settings.ranguvannja_outputs[N_BIG*k + 2];
              target_sell[3] = edition_settings.ranguvannja_outputs[N_BIG*k + 3];
              target_sell[4] = edition_settings.ranguvannja_outputs[N_BIG*k + 4];
              target_sell[5] = edition_settings.ranguvannja_outputs[N_BIG*k + 5];

              //ϳ��������� ������� ������� "������ ��" �� ��� �������
              if (
                  ((target_sell[0] & maska_func_WORK_BV[0]) != 0)
                  ||
                  ((target_sell[1] & maska_func_WORK_BV[1]) != 0)
                  ||
                  ((target_sell[2] & maska_func_WORK_BV[2]) != 0)
                  ||
                  ((target_sell[3] & maska_func_WORK_BV[3]) != 0)
                  ||
                  ((target_sell[4] & maska_func_WORK_BV[4]) != 0)
                  ||
                  ((target_sell[5] & maska_func_WORK_BV[5]) != 0)
                 ) 
                number_func_WORK_BV_into_outputs++;

              //ϳ��������� ������� ������� "������ ��" �� ��� �������
              if (
                  ((target_sell[0] & maska_func_WORK_BO[0]) != 0)
                  ||
                  ((target_sell[1] & maska_func_WORK_BO[1]) != 0)
                  ||
                  ((target_sell[2] & maska_func_WORK_BO[2]) != 0)
                  ||
                  ((target_sell[3] & maska_func_WORK_BO[3]) != 0)
                  ||
                  ((target_sell[4] & maska_func_WORK_BO[4]) != 0)
                  ||
                  ((target_sell[5] & maska_func_WORK_BO[5]) != 0)
                 ) 
                number_func_WORK_BO_into_outputs++;
              
              if (
                  (number_func_WORK_BV_into_outputs > 1) ||
                  (number_func_WORK_BO_into_outputs > 1)
                 )
              {
                //��������� �������� - ������� ��
                 error = ERROR_ILLEGAL_DATA_VALUE;
              }
            }
          }
          /*****/
          
          if (error == 0)
          {
            if  (global_requect == 0)
            {
              CRC_sum = 0xffff;
              for (int index = 0; index < 6; index++)
              {
                *(transmited_buffer + index ) = *(received_buffer + index );
                CRC_sum = AddCRC(*(transmited_buffer + index),CRC_sum);
              }
              *(transmited_buffer +6 ) = CRC_sum & 0xff;
              *(transmited_buffer +7 ) = CRC_sum >> 8;

              *transmited_count = 8;
              if(type_interface == USB_RECUEST) data_usb_transmiting = true;
              else if(type_interface ==  RS485_RECUEST) start_transmint_data_via_RS_485(*transmited_count);
            }
            else
            {
              if(type_interface == RS485_RECUEST)
              {
                //������������� ��������� �� RS-485
                restart_monitoring_RS485();
              }
            }

            /*****/
            //��� ����������� �������� ���������� � EEPROM
            /*****/
            if (reinit_ustuvannja != 0)
            {
              //���������� ������� ��� �������� � ��
              //�������, �� �������� ������ ��������� ����� ������ �����
              changed_ustuvannja = CHANGED_ETAP_EXECUTION;
              for(unsigned int k = 0; k < NUMBER_ANALOG_CANALES; k++) 
              {
                ustuvannja[k] = edit_ustuvannja[k];
                phi_ustuvannja[k] = phi_edit_ustuvannja[k];
                phi_ustuvannja_sin_cos[2*k] = phi_edit_ustuvannja_sin_cos[2*k];
                phi_ustuvannja_sin_cos[2*k + 1] = phi_edit_ustuvannja_sin_cos[2*k + 1];
              }
              //�������, �� �������� ������ ��������� ����� � ����� ��� ����������� � ����������� �������
              changed_ustuvannja = CHANGED_ETAP_ENDED;
              serial_number_dev = edit_serial_number_dev;

              _SET_BIT(control_i2c_taskes, TASK_START_WRITE_USTUVANNJA_EEPROM_BIT);
            }
            if (
                (reinit_settings    != 0) ||
                (reinit_ranguvannja != 0) ||
                (set_min_param      != 0) ||
                (change_timeout_ar  != 0)
               )
            {
              //�������, �� ���� ��������� ����� ������ �����
              changed_settings = CHANGED_ETAP_EXECUTION;

              //������� ������ ���� � ������ ���������
              current_settings = edition_settings;
              if (
                  (state_ar_record == STATE_AR_TEMPORARY_BLOCK) ||
                  (semaphore_read_state_ar_record != 0)  
                 )
              {
                /*
                �� �������� ���� ����, ���� �������������� ������� ���������,
                ��� ���� ��������� ������ ����������� ��� ������������� �������
                ����������� ����������.
                ��� ����� ������ �� ����, �� ����� state_ar_record ���� �������
                STATE_AR_TEMPORARY_BLOCK � ����� semaphore_read_state_ar_record
                �� ���� ����. ��� �� 
                ����� �� ����������� - �� ����� ������������� ������,
                �� ��������� ������������ ���� ���� ���������������� ������.
                */
                if(
                   ((set_min_param != 0) || (change_timeout_ar != 0)) &&
                   (state_ar_record == STATE_AR_TEMPORARY_BLOCK) &&
                   (semaphore_read_state_ar_record != 0)  
                  )
                {
                  //�������� 䳿 �� ��� ������� �������� ����������� ����������
                  actions_after_changing_tiomouts_ar();

                  //������������ ������ ����������� ����������
                  state_ar_record = STATE_AR_NO_RECORD;

                  //������ �������
                  semaphore_read_state_ar_record = 0;
                }
                else
                {
                  //���� ���� ����� ��������, ������� �������� ����������� �������, ���� ����� ��������� ��������, ��� ���� ���� �� ������������
                  total_error_sw_fixed(41);
                }
              }

              if (reinit_settings != 0)
              {
                if(type_interface == USB_RECUEST) fix_change_settings(0, 2);
                else if(type_interface ==  RS485_RECUEST) fix_change_settings(0, 3);
              }

              if (reinit_ranguvannja != 0)
              {
                if(type_interface == USB_RECUEST) fix_change_settings(1, 2);
                else if(type_interface ==  RS485_RECUEST) fix_change_settings(1, 3);
              }
              
              if (set_min_param != 0)
              {
                //������ ������, ��  �� ��������� ������� � ���������� ������������
                fix_change_settings(0, 0);
                fix_change_settings(1, 0);
                
                //����������� ���� �� ����� ����������������� ������� RS-485
                reconfiguration_RS_485 = 1;
                reconfiguration_RS_485_with_reset_usart = 1;

                if (current_settings.password_interface_RS485 == 0) password_set_RS485 = 0;
                else password_set_RS485 = 1;
                if (current_settings.password_interface_USB   == 0) password_set_USB   = 0;
                else password_set_USB   = 1;
              }
                
              if (reconfiguration_RS_485 != 0)
              {
                //ϳ��������� ���� �������� �������� � ����, ��� ����������� �� ������� � RS-485 ����� � ����������� �����������
                calculate_namber_bit_waiting_for_rs_485();
                //����������� ������� ��� ������������������ RS-485
                if (reconfiguration_RS_485_with_reset_usart != 0) make_reconfiguration_RS_485 = 0xff;
              }

              //����������� �������, �� �� ����� ����� �������� ����������
              new_state_keyboard |= (1<<BIT_REWRITE);
            }
            /*****/
          }
          else 
          {
            if(state_ar_record == STATE_AR_TEMPORARY_BLOCK) state_ar_record = STATE_AR_NO_RECORD;
            if (semaphore_read_state_ar_record != 0) semaphore_read_state_ar_record = 0;
            
            //������������ ��������� ���� ������� �� ������
            if (type_interface == USB_RECUEST) password_set_USB = before_password_set;
            else if (type_interface == RS485_RECUEST) password_set_RS485 = before_password_set;

            if  (global_requect == 0)
            {
              Error_modbus((unsigned char)current_settings.address, *(received_buffer+1), error, transmited_buffer);
              *transmited_count = 5;
              if(type_interface == USB_RECUEST) data_usb_transmiting = true;
              else if(type_interface ==  RS485_RECUEST) start_transmint_data_via_RS_485(*transmited_count);
            }
            else
            {
              if(type_interface == RS485_RECUEST)
              {
                //������������� ��������� �� RS-485
                restart_monitoring_RS485();
              }
            }
          }

          break;
        }//ʳ���� ��� ������� ������� 16
      case 20:
        {
          *transmited_buffer = *(received_buffer);
          *(transmited_buffer + 1) = *(received_buffer + 1) ;

          unsigned int number_requests = *(received_buffer + 2);
          unsigned int total_number_answer = 0;

          if ((number_requests >= 0x7) && (number_requests <= 0xF5))
          {
            unsigned int i = 0; 
            while ((i < number_requests) && ((error = Get_data_file((received_buffer + 3 + i), (transmited_buffer + 3 + total_number_answer), &total_number_answer, type_interface)) == 0))
            {
              i += 7;
            }
         
          }
          else error = ERROR_ILLEGAL_DATA_VALUE;
        
          if (error == 0)
          {
            *(transmited_buffer + 2) = total_number_answer ;

            CRC_sum = 0xffff;
            for (int index = 0; index < ((int)(total_number_answer + 3)); index++) CRC_sum = AddCRC(*(transmited_buffer + index),CRC_sum);
            *(transmited_buffer+3+total_number_answer) = CRC_sum & 0xff;
            *(transmited_buffer+4+total_number_answer) = CRC_sum >> 8;
            
            *transmited_count = 5+total_number_answer;
            if(type_interface == USB_RECUEST) data_usb_transmiting = true;
            else if(type_interface ==  RS485_RECUEST) start_transmint_data_via_RS_485(*transmited_count);
          }
          else
          {
            
            Error_modbus((unsigned char)current_settings.address, *(received_buffer+1), error, transmited_buffer);
            *transmited_count = 5;
            if(type_interface == USB_RECUEST) data_usb_transmiting = true;
            else if(type_interface ==  RS485_RECUEST) start_transmint_data_via_RS_485(*transmited_count);
          }

          break;
        }//ʳ���� ��� ������� ������� 20        
      default:
        {
          Error_modbus((unsigned char)current_settings.address, *(received_buffer+1), ERROR_ILLEGAL_FUNCTION, transmited_buffer);
          *transmited_count = 5;
          if(type_interface == USB_RECUEST) data_usb_transmiting = true;
          else if(type_interface ==  RS485_RECUEST) start_transmint_data_via_RS_485(*transmited_count);
        }
      }
    }
    else
    {
      if(type_interface == RS485_RECUEST)
      {
        //������������� ��������� �� RS-485
        restart_monitoring_RS485();
      }
    }
  }
  else
  {
    if(type_interface == RS485_RECUEST)
    {
      //������������� ��������� �� RS-485
      restart_monitoring_RS485();
    }
  }
  *received_count = 0;
}
/***********************************************************************************/
