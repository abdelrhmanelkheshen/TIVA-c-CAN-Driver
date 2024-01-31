 /****************************************************************************
 *
 * Module: CAN
 *
 * File Name: CAN_config.h
 *
 * Description: Header file for the CAN driver configration
 *
 * Author: Ahmed Hesham
 *
 * Created on: Sep 25, 2023
 *
 *****************************************************************************/
#ifndef _CAN_CONFIG_H
#define _CAN_CONFIG_H
#include "CAN_interface.h"

#define CAN_CONFIGURED_CHANNELS              (1U)
#define CAN_MSG_USED                         (9U)
#define CAN_ID0_BR                           (1000000U)

#define CAN0_MSG1_ID                          (0x0101)
#define CAN0_MSG2_ID                          (0x1001)
#define CAN0_MSG3_ID                          (0x3001)
#define CAN0_MSG4_ID                          (0x3001)
#define CAN0_MSG5_ID                          (0x2001)
#define CAN0_MSG6_ID                          (0x4001)
#define CAN0_MSG7_ID                          (0x5001)
#define CAN0_MSG8_ID                          (0x5001)
#define CAN0_MSG9_ID                          (0x0001)

#define CAN0_MSG_MASK                        (0xFFFFF)
#define CAN0_MSG_MASK_ZERO                   (0U)

#define CAN0_MSG_RX_FLAG           (MSG_OBJ_RX_INT_ENABLE| MSG_OBJ_USE_ID_FILTER | MSG_OBJ_EXTENDED_ID)
#define CAN0_MSG_TX_FLAG           (MSG_OBJ_TX_INT_ENABLE| MSG_OBJ_USE_ID_FILTER | MSG_OBJ_EXTENDED_ID)
#define CAN0_MSG_TX_REMOTE_FLAG    (MSG_OBJ_TX_INT_ENABLE| MSG_OBJ_REMOTE_FRAME)
#define CAN0_MSG_RX_REMOTE_FLAG    (MSG_OBJ_RX_INT_ENABLE| MSG_OBJ_REMOTE_FRAME)


extern uint8 Data1;
extern uint8 Data2;
extern uint8 Data3;
extern uint8 Data4;
extern uint8 Data5;
extern uint8 Data6;
extern uint8 Data7;
#endif 
