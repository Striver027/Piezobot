/**
  ******************************************************************************
  * @file    HC_12.h
  * @brief   HC-12 wireless module AT command driver (USART3 @ 9600 8N1)
  ******************************************************************************
  * Command / response pairs taken from the module datasheet (section 6.3):
  *
  *   AT            -> OK                     test communication
  *   AT+Bxxxx      -> OK+Bxxxx               baud rate   (1200..115200)
  *   AT+Cxxx       -> OK+Cxxx                channel     (001..127, 400kHz step)
  *   AT+FUx        -> OK+FUx                 transparent mode (FU1..FU4)
  *   AT+Px         -> OK+Px                  TX power    (1..8)
  *   AT+DEFAULT    -> OK+DEFAULT             restore factory settings
  *
  * The SET pin (PB1 / LoRa_SET) must be driven LOW to enter AT command mode and
  * released HIGH afterwards; this is handled inside HC12_Set().
  ******************************************************************************
  */

#ifndef __HC12_H
#define __HC12_H

#include "stm32g4xx_hal.h"

/* Command selector: first argument of HC12_Set() */
typedef enum
{
    HC12_CMD_OK      = 0x00U,   /*!< AT            (no parameter)                  */
    HC12_CMD_B       = 0x01U,   /*!< AT+Bxxxx      baud rate                       */
    HC12_CMD_C       = 0x02U,   /*!< AT+Cxxx       wireless channel                */
    HC12_CMD_FU      = 0x03U,   /*!< AT+FUx        transparent mode                */
    HC12_CMD_P       = 0x04U,   /*!< AT+Px         TX power                        */
    HC12_CMD_DEFAULT = 0x05U    /*!< AT+DEFAULT    (no parameter)                  */
} HC12_CmdTypeDef;

/* Parameter values for HC12_CMD_B (AT+Bxxxx) */
typedef enum
{
    HC12_BAUD_1200   = 1200U,
    HC12_BAUD_2400   = 2400U,
    HC12_BAUD_4800   = 4800U,
    HC12_BAUD_9600   = 9600U,    /*!< factory default */
    HC12_BAUD_19200  = 19200U,
    HC12_BAUD_38400  = 38400U,
    HC12_BAUD_57600  = 57600U,
    HC12_BAUD_115200 = 115200U
} HC12_BaudTypeDef;

/* Parameter values for HC12_CMD_C (AT+Cxxx): 001..127 */
typedef enum
{
    HC12_CH_001 = 1U,   HC12_CH_021 = 21U,  HC12_CH_041 = 41U,
    HC12_CH_061 = 61U,  HC12_CH_081 = 81U,  HC12_CH_100 = 100U,
    HC12_CH_101 = 101U, HC12_CH_121 = 121U, HC12_CH_127 = 127U
} HC12_ChannelTypeDef;

/* Parameter values for HC12_CMD_FU (AT+FUx) */
typedef enum
{
    HC12_FU1 = 1U,      /*!< mode FU1 */
    HC12_FU2 = 2U,      /*!< mode FU2 */
    HC12_FU3 = 3U,      /*!< mode FU3 (factory default) */
    HC12_FU4 = 4U       /*!< mode FU4 */
} HC12_FuTypeDef;

/* Parameter values for HC12_CMD_P (AT+Px) */
typedef enum
{
    HC12_P1 = 1U,   /*!<  -1 dBm */
    HC12_P2 = 2U,   /*!<   2 dBm */
    HC12_P3 = 3U,   /*!<   5 dBm */
    HC12_P4 = 4U,   /*!<   8 dBm */
    HC12_P5 = 5U,   /*!<  11 dBm */
    HC12_P6 = 6U,   /*!<  14 dBm */
    HC12_P7 = 7U,   /*!<  17 dBm */
    HC12_P8 = 8U    /*!<  20 dBm (factory default) */
} HC12_PowerTypeDef;

/* String buffer sizes. */
#define HC12_CMD_BUF_SIZE      16U
#define HC12_RESP_BUF_SIZE     32U

/* Wait for the answer of the module, in ms (measured: < 50 ms) */
#define HC12_RESP_TIMEOUT_MS   50U

#define HC12_AT_ON     HAL_GPIO_WritePin(LoRa_SET_GPIO_Port, LoRa_SET_Pin, GPIO_PIN_RESET);
#define HC12_AT_OFF    HAL_GPIO_WritePin(LoRa_SET_GPIO_Port, LoRa_SET_Pin, GPIO_PIN_SET);

/**
  * @brief  Send one AT command to the HC-12 module and validate its response.
  * @param  cmd   command selector, one of HC12_CmdTypeDef
  * @param  param parameter value; ignored for HC12_CMD_OK / HC12_CMD_DEFAULT.
  *               uint32_t on purpose: the baud-rate values (19200, 115200) do
  *               not fit in a uint8_t and would silently be truncated.
  * @retval HAL_OK      the module answered with the expected "OK..." string
  * @retval HAL_ERROR   parameter rejected (invalid cmd or out-of-range param)
  * @retval HAL_TIMEOUT no complete response received within the timeout
  */
HAL_StatusTypeDef HC12_Set(HC12_CmdTypeDef cmd, uint32_t param);

#endif /* __HC12_H */
