/**
 * @file generator.h
 * @author Kacper Janowski
 * @brief 
 * @version 0.1
 * @date 2021-05-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef GENERATOR_H_
#define GENERATOR_H_

// include
#include "stdint.h"
#include "math.h"
#include "time.h"
#include "stdlib.h"

#include "pdsp.h"
#include "pdsp_config.h"

// define
#define pdsp_sinf(fi)       sinf(fi)  
#define pdsp_asinf(fii)		asinf(fii)
#define FS					8000.0f
#define PDSP_2PI_DIV_FS     ((M_PI *2.0f)/FS)

typedef enum {OSC_Sinusoid, OSC_Square, OSC_Triangle} OSC_WaveType_t;

/**
 * @brief Structure with oscillator parameters
 * 
 */
typedef struct {
	OSC_WaveType_t type;	
	float amplitude;
	float frequency;
	int n;
	float phaseOffset;
    float duty;
}GEN_Cfg_t;

/**
 * @brief Structure with oscillator parameters 
 * 
 */
typedef struct {
	OSC_WaveType_t type;	
	float amplitude; //nie wiem czy potrzebne
	float frequency;
	int n; //nie wiem czy potrzebne
	float phase;
    float phaseStep;    // krok fazy
}OSC_Cfg_t;

/**
 * @brief Oscillator initialization method
 * 
 * @param cfg Oscillator structire
 * @param A Aamplitude
 * @param f Frequency
 * @param sfill Fill signal
 * @param tp type of oscillator
 */
void GEN_Init(GEN_Cfg_t *cfg, OSC_WaveType_t type, float A, float f, float phaseOffset, float duty);

/**
 * @brief Generator executing function
 * 
 * @param cfg Generator structure
 * @return int8_t The function returns the determined signal samples
 */
uint8_t GEN_GetValue(GEN_Cfg_t *cfg);

/**
 * @brief Oscilator executing function (mniejsza liczba mnozen dzieki obliczeniu kroku fazy)
 * 
 * @param cfg Generator structure
 * @return float 
 */
float OSC_GetValueF(OSC_Cfg_t *cfg);

/**
 * @brief 
 * 
 * @param cfg 
 * @return float 
 */
float OSC_GetValuePeriodF(OSC_Cfg_t *cfg);

/**
 * @brief 
 * 
 * @param cfg 
 * @return float 
 */
float OSC_GetSinPeriodF(OSC_Cfg_t *cfg);

/**
 * @brief 
 * 
 * @param cfg 
 * @param freq 
 */
void OSC_SetFreq(OSC_Cfg_t *cfg, float freq);

#endif  // GENERATOR_H_