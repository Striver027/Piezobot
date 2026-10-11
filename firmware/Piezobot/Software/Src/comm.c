/**
  ******************************************************************************
  * @file    comm.c
  * @brief   USART3 reception: forward to USART1 and store in Comm_RxBuffer
  ******************************************************************************
  * Data flow:
  *   USART3 (PB11 / RX) --IRQ--> int.c: HAL_UART_RxCpltCallback()
  *                                --> Comm_Usart3RxHandler()  [here]
  *                                --> USART1 (PA9 / TX) --> PC   (forwarding)
  *                                --> Comm_RxBuffer              (AT answers)
  ******************************************************************************
  */

#include "comm.h"
#include "usart.h"

uint8_t Comm_RxBuffer[COMM_RX_BUFFER_SIZE];
uint8_t Comm_RxCount;

/* 1 = a protocol is being parsed, the interrupt stops handling the bytes */
uint8_t Comm_ProtocolRun;

/* One byte of the interrupt reception */
static uint8_t usart3_rx_byte;
static uint8_t usart1_tx_byte;

void Comm_Init(void)
{
    Comm_RxCount = 0U;
    HAL_UART_Receive_IT(&huart3, &usart3_rx_byte, 1U);
}

/**
  * @brief  Forward one received USART3 byte to USART1 and store it.
  * @note   Called from the USART3 interrupt (int.c), so it runs in interrupt
  *         context.
  */
void Comm_Usart3RxHandler(void)
{
    /* While a protocol is being parsed the byte must not be touched here:
       the parsing routine reads USART3 itself. Reception is still re-armed so
       the interrupt chain stays alive. */
    
        /* Store for the AT answer check */
        if (Comm_RxCount < COMM_RX_BUFFER_SIZE)
        {
            Comm_RxBuffer[Comm_RxCount] = usart3_rx_byte;
            Comm_RxCount++;
        }

        /* Forward to USART1 */
        usart1_tx_byte = usart3_rx_byte;
        HAL_UART_Transmit(&huart1, &usart1_tx_byte, 1U, 100U);

    HAL_UART_Receive_IT(&huart3, &usart3_rx_byte, 1U);
}

/**
  * @brief  Arm interrupt reception on USART3 again.
  * @note   Call after a polled AT exchange is finished.
  */
void Comm_ResumeReceive(void)
{
    HAL_UART_Receive_IT(&huart3, &usart3_rx_byte, 1U);
}

/**
  * @brief  Recover the USART3 reception after a framing/noise/overrun error.
  */
void Comm_Usart3ErrorHandler(void)
{
    HAL_UART_AbortReceive(&huart3);
    __HAL_UART_CLEAR_FLAG(&huart3, UART_CLEAR_PEF | UART_CLEAR_FEF |
                                  UART_CLEAR_NEF | UART_CLEAR_OREF);
    HAL_UART_Receive_IT(&huart3, &usart3_rx_byte, 1U);
}
