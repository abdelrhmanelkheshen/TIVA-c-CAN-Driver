#include "CAN_interface.h"
/* PB structure used with CAN_Init API */

uint8 Data1;
uint8 Data2;
uint8 Data3;
uint8 Data4;
uint8 Data5;
uint8 Data6;
uint8 Data7;

CAN_ConfigType can_config[CAN_CONFIGURED_CHANNELS] = 
{
  {CAN0,CAN_ID0_BR}
};

CAN_MessageConfig msg_config[CAN_MSG_USED] = 
{
  {CAN0_MSG1_ID,CAN0_MSG_MASK, CAN0_MSG_TX_FLAG,sizeof(Data2),(uint8*)&Data2,TX,2},                        /*DTC_Check Send8*/
  
  {CAN0_MSG2_ID,CAN0_MSG_MASK, CAN0_MSG_RX_FLAG,sizeof(Data1),(uint8*)&Data1,RX,1},                       /*DTC_Check Receive*/      
  
  {CAN0_MSG3_ID,CAN0_MSG_MASK_ZERO, CAN0_MSG_RX_REMOTE_FLAG,sizeof(Data3),(uint8*)&Data3,RX_REMOTE,3},    //Keep ALive Receive/
  
  {CAN0_MSG4_ID,CAN0_MSG_MASK_ZERO, CAN0_MSG_TX_REMOTE_FLAG  ,sizeof(Data3),(uint8*)&Data3,TX_REMOTE,4},   //Keep Alive Send/
  
  {CAN0_MSG5_ID,CAN0_MSG_MASK, CAN0_MSG_TX_FLAG,sizeof(Data4),(uint8*)&Data4,TX,5},                        //ECU2 State Send/
  
  {CAN0_MSG6_ID,CAN0_MSG_MASK, CAN0_MSG_TX_FLAG,sizeof(Data5),(uint8*)&Data5,TX,6},                        //ADC Temp Send/
  
  {CAN0_MSG7_ID, CAN0_MSG_MASK_ZERO, CAN0_MSG_RX_REMOTE_FLAG, sizeof(Data6), (uint8*)&Data6,RX_REMOTE,7},  //ADC Voltage Remote Receive/
  
  {CAN0_MSG8_ID,CAN0_MSG_MASK, CAN0_MSG_TX_FLAG,sizeof(Data6),(uint8*)&Data6,TX,8},                        //ADC Voltage Send/
  
  {CAN0_MSG9_ID,CAN0_MSG_MASK, CAN0_MSG_RX_FLAG,sizeof(Data7),(uint8*)&Data7,RX,9}                        //ECU1 State Receive/  
};