/**
 * @file generator.c
 * @author Kacper Janowski
 * @brief 
 * @version 0.1
 * @date 2021-05-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "generator.h"

float randval;

void GEN_Init(GEN_Cfg_t *cfg, OSC_WaveType_t type, float A, float f, float phaseOffset, float duty){
	cfg->amplitude = (float) fmod(A, (PDSP_CODEC_Vpp * 500.0f));
	cfg->frequency = (float) fmod(f, (PDSP_CODEC_Fs / 2.0f));
    cfg->type = type;
    cfg->phaseOffset = (float) fmod(phaseOffset, PDSP_2PI);
    cfg->duty = (float) fmod(duty, 100.0f) / 100.0f;
	cfg->n = 0;
}

uint8_t GEN_GetValue(GEN_Cfg_t *cfg){
	float y;    //phase
	float sample_fill;
	float left;
	float right;

    float yDuty;    //phaseDusty
    float wave;
    float alpha;

    y = PDSP_2PI_DIV_FS * cfg->frequency * cfg->n * cfg->phaseOffset;

	switch (cfg->type)
	{
	case OSC_Sinusoid:		
		wave = pdsp_sinf(y);
		break;
	case OSC_Triangle:		
        y = (float) fmod(y, PDSP_2PI);
        yDuty = PDSP_2PI * cfg->duty;

        alpha = (y < yDuty) ? ((PDSP_2PI - yDuty)/PDSP_2PI) : - (yDuty / PDSP_2PI);
        wave = 2.0f * alpha * y * -1.0f;
		break;
	case OSC_Square:	
        y = (float)fmod(y, PDSP_2PI);
        wave = (y < (PDSP_2PI * cfg->duty)) ? 1.0f : -1.0f;
		break;
	default:
        wave = 0.0f;
        break;
	}
    cfg->n++;
	return (uint8_t) (cfg->amplitude * wave) / (PDSP_CODEC_Vres * 1000.0f);
}


void OSC_Init (OSC_Cfg_t *cfg, OSC_WaveType_t type, float f, float phaseOffset) {
    cfg->type = type;
    cfg->frequency = f;
    cfg->phase = (float) fmod(phaseOffset, PDSP_2PI);
    cfg->phaseStep = (f * PDSP_2PI_DIV_FS);
}

void OSC_SetFreq(OSC_Cfg_t *cfg, float freq) {
    cfg->frequency = freq;
    cfg->phaseStep = (freq * PDSP_2PI_DIV_FS);
}

float OSC_GetValueF(OSC_Cfg_t *cfg) {
    float wave;
    float phase;

    switch (cfg->type)
    {
    case OSC_Sinusoid:
        wave = pdsp_sinf(cfg->phase);
        break;
    case OSC_Triangle:
        phase = (cfg->phase + PDSP_PI_DIV_2);
        if (phase > PDSP_2PI)
            phase -= PDSP_2PI;
        wave = (2 * (phase / PDSP_2PI)) - 1.0f;
        wave = (wave > 0) ? -wave : wave;
        wave = (2 * (wave + 0.5f));
        break;
    case OSC_Square:
        wave = (cfg->phase < PDSP_PI) ? 1.0f : -1.0f;
        break;
    default:
        wave = 0.0f;
        break;
    }

    cfg->phase += cfg->phaseStep;

    return wave;
}

float OSC_GetValuePeriodF(OSC_Cfg_t *cfg) {
    float wave;

    wave = OSC_GetValueF(cfg);

    if (cfg->phase > PDSP_2PI)
        cfg->phase -= PDSP_2PI;
    
    return wave;
}

float OSC_GetSinPeriodF(OSC_Cfg_t *cfg) {
    float wave;

    wave = pdsp_sinf(cfg->phase);

    cfg->phase += cfg->phaseStep;
    if(cfg->phase > PDSP_2PI)
        cfg->phase -= PDSP_2PI;

    return wave;
}

