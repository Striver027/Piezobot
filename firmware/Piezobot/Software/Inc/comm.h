/**
  ******************************************************************************
  * @file    comm.h
  * @brief   Reception buffer for USART3 (AT answers of the HC-12 module)
  ******************************************************************************
  * The USART3 interrupt stores every received byte in Comm_RxBuffer and counts
  * them in Comm_RxCount, and forwards the byte to USART1.
  *
  * Set Comm_ProtocolRun = 1 to suspend that handling while a communication
  * protocol is being parsed, and back to 0 when the parsing is done. The
  * interrupt itself keeps running (reception is still re-armed), the byte is
  * simply dropped.
  ******************************************************************************
  */

#ifndef __COMM_H
#define __COMM_H

#include "stm32g4xx_hal.h"

#define COMM_RX_BUFFER_SIZE    64U

extern uint8_t Comm_RxBuffer[COMM_RX_BUFFER_SIZE];
extern uint8_t Comm_RxCount;

/* 1 = a protocol is being parsed, the interrupt stops handling the bytes */
extern uint8_t Comm_ProtocolRun;

void Comm_Init(void);

/* Data handling for the USART3 interrupt; called from int.c. */
void Comm_Usart3RxHandler(void);
void Comm_Usart3ErrorHandler(void);

/* Arm interrupt reception on USART3 again. */
void Comm_ResumeReceive(void);

#endif /* __COMM_H */
