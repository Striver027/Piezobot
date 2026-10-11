/**
  ******************************************************************************
  * @file    wave.c
  * @brief   
  ******************************************************************************
  * @attention

  *
  ******************************************************************************
  */
 
/* Includes ------------------------------------------------------------------*/
#include "wave.h"
//#include "stm32g4xx_hal.h"

uint32_t toothsheet_fullwave[] = 
	{	0,41,83,124,165,207,248,290,331,372,
		414,455,496,538,579,620,662,703,745,786,
		827,869,910,951,993,1034,1075,1117,1158,1200,
		1241,1282,1324,1365,1406,1448,1489,1530,1572,1613,
		1655,1696,1737,1779,1820,1861,1903,1944,1985,2027,
		2068,2110,2151,2192,2234,2275,2316,2358,2399,2440,
		2482,2523,2565,2606,2647,2689,2730,2771,2813,2854,
		2895,2937,2978,3020,3061,3102,3144,3185,3226,3268,
		3309,3350,3392,3433,3475,3516,3557,3599,3640,3681,
		3723,3764,3805,3847,3888,3930,3971,4012,4054,4095,};
uint32_t toothsheet_runwave_left[WAVE_LENTH] = 
	{	0};
uint32_t toothsheet_runwave_right[WAVE_LENTH] = 
	{	0};




/**
 * @brief  Scale one full sawtooth period into a DAC drive buffer.
 * @param  fullwave  source period, 12-bit values 0..4095 (toothsheet_fullwave)
 * @param  rate      speed factor 0..1 (1 = full amplitude)
 * @param  genwave   destination buffer of WAVE_LENTH entries (DAC DMA source)
 */
void RunWave_Gen(uint32_t *fullwave, float rate, uint32_t *genwave)
{
    for(uint32_t i = 0; i < WAVE_LENTH; i++)
    {
        genwave[i] = (uint32_t)fullwave[i] * rate ;
    }
}

