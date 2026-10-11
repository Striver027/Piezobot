/**
  ******************************************************************************
  * @file    HC_12.c
  * @brief   HC-12 AT command driver (USART3 @ 9600 8N1)
  ******************************************************************************
  * HC12_Set() decides what to send from its two arguments, fills the command
  * string character by character while counting the length, sends it with the
  * AT_MODE_SEND() macro, and checks the answer against the expected string.
  *
  * No line terminator is appended: the command is sent exactly as built.
  * No sprintf(): the digits are written directly, so the printf library stays
  * out of the image.
  ******************************************************************************
  */

#include "HC_12.h"
#include "main.h"
#include "usart.h"
#include "comm.h"
#include <string.h>

/* Decimal digits of the largest possible parameter (115200 = 6) */
#define HC12_DEC_MAX_DIGITS     10U


/**
  * @brief  Write v as decimal digits into dst, padded to at least pad digits.
  * @retval number of characters written
  */
static uint8_t hc12_fill_dec(char *dst, uint32_t v, uint8_t pad)
{
    char    rev[HC12_DEC_MAX_DIGITS];
    uint8_t n;
    uint8_t p;

    n = 0U;

    if (v == 0U)
    {
        rev[n] = '0';
        n++;
    }
    else
    {
        while ((v > 0U) && (n < (uint8_t)HC12_DEC_MAX_DIGITS))
        {
            rev[n] = (char)('0' + (char)(v % 10U));
            n++;
            v /= 10U;
        }
    }

    for (p = n; p < pad; p++)
    {
        *dst = '0';
        dst++;
    }

    while (n > 0U)
    {
        n--;
        *dst = rev[n];
        dst++;
    }

    return (uint8_t)((pad > n) ? pad : n);
}

/**
  * @brief  Send one AT command to the HC-12 module and validate the response.
  * @param  cmd   command selector, one of HC12_CmdTypeDef
  * @param  param parameter value, ignored for HC12_CMD_OK / HC12_CMD_DEFAULT
  * @retval HAL_OK      the module answered with the expected "OK..." string
  * @retval HAL_ERROR   parameter rejected (invalid cmd or out-of-range param)
  * @retval HAL_TIMEOUT no complete response received within the timeout
  */
HAL_StatusTypeDef HC12_Set(HC12_CmdTypeDef cmd, uint32_t param)
{
    char cmd_buf[HC12_CMD_BUF_SIZE];
    uint16_t idx;
    uint16_t len;
    uint8_t  done;

    len = 0U;

    /* ---- 1. Decide what to send, character by character ---------------- */
    switch (cmd)
    {
    case HC12_CMD_OK:
        cmd_buf[len] = 'A';                                     len++;
        cmd_buf[len] = 'T';                                     len++;
        break;

    case HC12_CMD_B:
        if ((param != 1200U)  && (param != 2400U)  && (param != 4800U) &&
            (param != 9600U)  && (param != 19200U) && (param != 38400U) &&
            (param != 57600U) && (param != 115200U))
        {
            return HAL_ERROR;
        }
        cmd_buf[len] = 'A';                                     len++;
        cmd_buf[len] = 'T';                                     len++;
        cmd_buf[len] = '+';                                     len++;
        cmd_buf[len] = 'B';                                     len++;
        len += hc12_fill_dec(&cmd_buf[len], param, 0U);
        break;

    case HC12_CMD_C:
        if ((param < 1U) || (param > 127U))
        {
            return HAL_ERROR;
        }
        cmd_buf[len] = 'A';                                     len++;
        cmd_buf[len] = 'T';                                     len++;
        cmd_buf[len] = '+';                                     len++;
        cmd_buf[len] = 'C';                                     len++;
        len += hc12_fill_dec(&cmd_buf[len], param, 3U);
        break;

    case HC12_CMD_FU:
        if ((param < 1U) || (param > 4U))
        {
            return HAL_ERROR;
        }
        cmd_buf[len] = 'A';                                     len++;
        cmd_buf[len] = 'T';                                     len++;
        cmd_buf[len] = '+';                                     len++;
        cmd_buf[len] = 'F';                                     len++;
        cmd_buf[len] = 'U';                                     len++;
        len += hc12_fill_dec(&cmd_buf[len], param, 0U);
        break;

    case HC12_CMD_P:
        if ((param < 1U) || (param > 8U))
        {
            return HAL_ERROR;
        }
        cmd_buf[len] = 'A';                                     len++;
        cmd_buf[len] = 'T';                                     len++;
        cmd_buf[len] = '+';                                     len++;
        cmd_buf[len] = 'P';                                     len++;
        len += hc12_fill_dec(&cmd_buf[len], param, 0U);
        break;

    case HC12_CMD_DEFAULT:
        cmd_buf[len] = 'A';                                     len++;
        cmd_buf[len] = 'T';                                     len++;
        cmd_buf[len] = '+';                                     len++;
        cmd_buf[len] = 'D';                                     len++;
        cmd_buf[len] = 'E';                                     len++;
        cmd_buf[len] = 'F';                                     len++;
        cmd_buf[len] = 'A';                                     len++;
        cmd_buf[len] = 'U';                                     len++;
        cmd_buf[len] = 'L';                                     len++;
        cmd_buf[len] = 'T';                                     len++;
        break;

    default:
        return HAL_ERROR;
    }

    /* ---- 3. Send ------------------------------------------------------- */
    HC12_AT_ON;
    HAL_Delay(200);                     /* TEST: let SET settle before sending */

    HAL_UART_Transmit(&huart3, (uint8_t *)cmd_buf, len, 100U);  /* to module */
    HAL_UART_Transmit(&huart1, (uint8_t *)cmd_buf, len, 100U);  /* echo to PC */

    /* ---- 4. Wait, then look for "OK" in what was received --------------- */
    HAL_Delay(HC12_RESP_TIMEOUT_MS);

    done = 0U;
    for (idx = 0U; (uint16_t)(idx + 1U) < (uint16_t)Comm_RxCount; idx++)
    {
        if ((Comm_RxBuffer[idx] == 'O') && (Comm_RxBuffer[idx + 1U] == 'K'))
        {
            done = 1U;
            break;
        }
    }

    HC12_AT_OFF;
    Comm_ResumeReceive();

    if (done != 0U)
    {
        return HAL_OK;
    }
    return HAL_TIMEOUT;
}
