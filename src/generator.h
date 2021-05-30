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
 * @brief Generator initialization method
 * 
 * @param cfg Oscillator structure
 * @param A Aamplitude
 * @param f Frequency
 * @param sfill Fill signal
 * @param tp type of oscillator
 */
void GEN_Init(GEN_Cfg_t *cfg, OSC_WaveType_t type, float A, float f, float phaseOffset, float duty);

/**
 * @brief Oscillator initialization method
 *
 * @param cfg Oscillator structure
 * @param type Type of oscillator
 * @param A Amplitude
 * @param f Frequency
 * @param phaseOffset
 */
void OSC_Init (OSC_Cfg_t *cfg, OSC_WaveType_t type, float A, float f, float phaseOffset);

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
 * @return float Returns the value of the specified type of oscillator
 */
float OSC_GetValueF(OSC_Cfg_t *cfg);
//uint16_t OSC_GetValueF(OSC_Cfg_t *cfg);

/**
 * @brief Oscilator executing function (float)
 * 
 * @param cfg Oscillator structure
 * @return float Returns the frequency period value
 */
float OSC_GetValuePeriodF(OSC_Cfg_t *cfg);

/**
 * @brief Getting the value of the sine period
 * 
 * @param cfg Oscillator structure
 * @return float Returns the frequency period value for a sine wave
 */
float OSC_GetSinPeriodF(OSC_Cfg_t *cfg);

/**
 * @brief Frequency setting
 * 
 * @param cfg Oscillator structure
 * @param freq Frequency
 */
void OSC_SetFreq(OSC_Cfg_t *cfg, float freq);

#endif  // GENERATOR_H_