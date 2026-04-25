/*
             Stargazer
    Created by Ross Fish 2018
        Moffenzeef Modular
  http://moffenzeefmodular.com/stargazer

        Waveforms by Adventure Kid
    AKWF waveforms are Public Domain
  https://www.adventurekid.se/akrt/waveforms/adventure-kid-waveforms/

    Waveforms formatted for Teensy by Datanoise
  https://github.com/DatanoiseTV/AKWF_WaveForms

  MOF-STARGAZER-CODE-v1.0-4.24.26-PEDALMAPLFOFREQALL
  Expression pedal mapped to all 3 LFO frequencies.
  Wavetable interpolation: blends between adjacent wavetables.
*/

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveform       waveform2;      //xy=1628,1374
AudioSynthWaveform       waveform1;      //xy=1631,1335
AudioSynthWaveform       waveform3;      //xy=1746,1425
AudioMixer4              mixer1;         //xy=1777,1355
AudioEffectWaveshaper    waveshape1;     //xy=1874,1470
AudioFilterBiquad        filter1;         //xy=1902,1362
AudioSynthWaveformDc     dc1;            //xy=2009,1298
AudioSynthWaveform       waveform5;      //xy=2013,1244
AudioAnalyzeRMS          rms2;           //xy=2020,1476
AudioSynthWaveform       waveform4;      //xy=2024,1412
AudioMixer4              allpassMix1;    //xy=2035,1310
AudioEffectBitcrusher    bitcrusher1;    //xy=2035,1356
AudioEffectWaveshaper    waveshape2;     //xy=2162,1188
AudioMixer4              mixer3;         //xy=2169,1262
AudioEffectWaveshaper    waveshape3;     //xy=2172,1446
AudioFilterStateVariable filter2;        //xy=2174,1361
AudioAnalyzeRMS          rms4;           //xy=2306,1191
AudioAnalyzeRMS          rms3;           //xy=2313,1447
AudioEffectMultiply      multiply1;      //xy=2332,1313
AudioMixer4              mixer2;         //xy=2467,1328
AudioOutputAnalog        dac1;           //xy=2617,1315
AudioConnection          patchCord1(waveform2, 0, mixer1, 1);
AudioConnection          patchCord2(waveform1, 0, mixer1, 0);
AudioConnection          patchCord3(mixer1, 0, allpassMix1, 0);
AudioConnection          patchCord4(waveform3, waveshape1);
AudioConnection          patchCord5(mixer1, 0, filter1, 0);
AudioConnection          patchCord6(waveshape1, rms2);
AudioConnection          patchCord7(filter1, 0, allpassMix1, 1);
AudioConnection          patchCord7f(allpassMix1, 0, mixer1, 2);
AudioConnection          patchCord7d(allpassMix1, 0, bitcrusher1, 0);
AudioConnection          patchCord8(dc1, 0, mixer3, 1);
AudioConnection          patchCord9(waveform5, 0, mixer3, 0);
AudioConnection          patchCord10(waveform5, waveshape2);
AudioConnection          patchCord11(waveform4, 0, filter2, 1);
AudioConnection          patchCord12(waveform4, waveshape3);
AudioConnection          patchCord13(bitcrusher1, 0, filter2, 0);
AudioConnection          patchCord14(waveshape2, rms4);
AudioConnection          patchCord15(mixer3, 0, multiply1, 0);
AudioConnection          patchCord16(waveshape3, rms3);
AudioConnection          patchCord17(filter2, 0, multiply1, 1);
AudioConnection          patchCord18(multiply1, 0, mixer2, 0);
AudioConnection          patchCord19(mixer2, dac1);
// GUItool: end automatically generated code

float osc1 = 0;
float osc2 = 0;
float oscMix = 0;

float cutoff1 = 0;
float res1 = 0;
float cutoff2 = 0;
float res2 = 0;

float LFO1AMP = 0;
float LFO1FREQ = 0;
float LFO1MATH = 0;

float LFO2AMP = 0;
float LFO2FREQ = 0;
float LFO2MATH = 0;

float LFO3AMP = 0;
float LFO3FREQ = 0;
float LFO3MATH = 0;

int waveSelect1 = 0;
int waveSelect2 = 0;
int waveSelect3 = 0;
int waveSelect4 = 0;

int bitRate = 0;
int sampleRedux = 0;

int expPedal = 0;

int LFO1led = 0;
int LFO2led = 0;
int LFO3led = 0;

float rectify[2] = {0.0, 1.0};

float sub = 0;

float diffWAVE = 0;
int currentWAVE = 0;
float smoothWAVE = 0;

float diffOSC = 0;
int currentADCOSC = 0;
float smoothADCOSC = 0;

float diffPEDAL = 0;
float smoothPEDAL = 0;
int currentPEDAL = 0;


int waveSelect = 0;

// Buffer for interpolated wavetable (AKWF tables are 256 samples)
static int16_t blendedWave[256];
static float lastWavePos = -1.0f;

// Software LFOs (drive LEDs and phaser)
static float lfo1Phase = 0.0f;
static uint32_t lfo1LastMicros = 0;
static float lfo1SHvalue = 0.0f;
static float lfo1PrevPhase = 1.0f;

static float lfo2Phase = 0.0f;
static uint32_t lfo2LastMicros = 0;
static float lfo2SHvalue = 0.0f;
static float lfo2PrevPhase = 1.0f;

static float lfo3Phase = 0.0f;
static uint32_t lfo3LastMicros = 0;
static float lfo3SHvalue = 0.0f;
static float lfo3PrevPhase = 1.0f;

static float lfo1Out = 0.0f;
static float lfo2Out = 0.0f;
static float lfo3Out = 0.0f;


#include "AKWF_R.H"
#include "AKWF_aguitar.H"
#include "AKWF_altosax.H"
#include "AKWF_birds.H"
#include "AKWF_bitreduced.H"
#include "AKWF_blended.H"
#include "AKWF_bsaw.H"
#include "AKWF_c604.H"
#include "AKWF_clavinet.H"
#include "AKWF_distorted.H"
#include "AKWF_eguitar.H"
#include "AKWF_eorgan.H"
#include "AKWF_epiano.H"
#include "AKWF_fmsynth.H"
#include "AKWF_granular.H"
#include "AKWF_hvoice.H"
#include "AKWF_overtone.H"

struct WaveTable {
  int16_t const* table;
};

#define TABLE_NUM 89

WaveTable waveTables[TABLE_NUM] {
  AKWF_R_sym_saw_15,
  AKWF_R_sym_saw_25,
  AKWF_aguitar_0008,
  AKWF_altosax_0005,
  AKWF_birds_0002,
  AKWF_birds_0004,
  AKWF_birds_0005,
  AKWF_bitreduced_0002,
  AKWF_bitreduced_0006,
  AKWF_bitreduced_0007,
  AKWF_bitreduced_0011,
  AKWF_bitreduced_0013,
  AKWF_bitreduced_0016,
  AKWF_bitreduced_0019,
  AKWF_bitreduced_0022,
  AKWF_bitreduced_0026,
  AKWF_bitreduced_0028,
  AKWF_bitreduced_0031,
  AKWF_bitreduced_0032,
  AKWF_bitreduced_0038,
  AKWF_blended_0002,
  AKWF_blended_0003,
  AKWF_blended_0007,
  AKWF_blended_0012,
  AKWF_blended_0013,
  AKWF_blended_0030,
  AKWF_bsaw_0001,
  AKWF_c604_0004,
  AKWF_clavinet_0001,
  AKWF_distorted_0004,
  AKWF_distorted_0005,
  AKWF_distorted_0009,
  AKWF_distorted_0010,
  AKWF_distorted_0014,
  AKWF_distorted_0015,
  AKWF_distorted_0017,
  AKWF_distorted_0018,
  AKWF_distorted_0022,
  AKWF_distorted_0023,
  AKWF_distorted_0026,
  AKWF_distorted_0027,
  AKWF_eguitar_0003,
  AKWF_eorgan_0042,
  AKWF_eorgan_0043,
  AKWF_eorgan_0046,
  AKWF_eorgan_0055,
  AKWF_eorgan_0058,
  AKWF_eorgan_0059,
  AKWF_eorgan_0060,
  AKWF_eorgan_0061,
  AKWF_eorgan_0062,
  AKWF_epiano_0005,
  AKWF_epiano_0008,
  AKWF_fmsynth_0002,
  AKWF_fmsynth_0004,
  AKWF_fmsynth_0005,
  AKWF_fmsynth_0006,
  AKWF_fmsynth_0007,
  AKWF_fmsynth_0024,
  AKWF_fmsynth_0034,
  AKWF_fmsynth_0035,
  AKWF_fmsynth_0036,
  AKWF_fmsynth_0040,
  AKWF_fmsynth_0051,
  AKWF_fmsynth_0055,
  AKWF_fmsynth_0056,
  AKWF_fmsynth_0057,
  AKWF_fmsynth_0058,
  AKWF_fmsynth_0059,
  AKWF_fmsynth_0060,
  AKWF_granular_0009,
  AKWF_granular_0020,
  AKWF_granular_0033,
  AKWF_hvoice_0030,
  AKWF_hvoice_0033,
  AKWF_hvoice_0035,
  AKWF_hvoice_0036,
  AKWF_hvoice_0039,
  AKWF_hvoice_0048,
  AKWF_hvoice_0052,
  AKWF_hvoice_0054,
  AKWF_hvoice_0056,
  AKWF_hvoice_0071,
  AKWF_overtone_0001,
  AKWF_overtone_0005,
  AKWF_overtone_0017,
  AKWF_overtone_0026,
  AKWF_overtone_0028,
};

short waveShapesLFO1[6] = {
  WAVEFORM_SINE,
  WAVEFORM_TRIANGLE,
  WAVEFORM_SAWTOOTH,
  WAVEFORM_SAWTOOTH_REVERSE,
  WAVEFORM_SQUARE,
  WAVEFORM_SAMPLE_HOLD,
};

short waveShapesLFO2[6] = {
  WAVEFORM_SINE,
  WAVEFORM_TRIANGLE,
  WAVEFORM_SAWTOOTH,
  WAVEFORM_SAWTOOTH_REVERSE,
  WAVEFORM_SQUARE,
  WAVEFORM_SAMPLE_HOLD,
};

short waveShapesLFO3[6] = {
  WAVEFORM_SINE,
  WAVEFORM_TRIANGLE,
  WAVEFORM_SAWTOOTH,
  WAVEFORM_SAWTOOTH_REVERSE,
  WAVEFORM_SQUARE,
  WAVEFORM_SAMPLE_HOLD,
};

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void setPhaserStage(int stage, float freq, float q) {
  double w0    = (double)freq * (2.0 * PI / 44100.0);
  double cosW0 = cos(w0);
  double alpha = sin(w0) / (2.0 * (double)q);
  double norm  = 1.0 + alpha;
  double c[5]  = {
    (1.0 - alpha) / norm,  // b0
    -2.0 * cosW0  / norm,  // b1
    1.0,                   // b2
    -2.0 * cosW0  / norm,  // a1
    (1.0 - alpha) / norm   // a2
  };
  filter1.setCoefficients(stage, c);
}

void setup() {
  waveform1.begin(WAVEFORM_ARBITRARY);
  waveform2.begin(WAVEFORM_ARBITRARY);
  AudioMemory(100);
  // Phaser: 4-stage allpass (wet) summed with dry
  allpassMix1.gain(0, 0.5f);   // dry
  allpassMix1.gain(1, 0.5f);   // wet (4-stage allpass)
  allpassMix1.gain(2, 0.0f);
  allpassMix1.gain(3, 0.0f);
  dac1.analogReference(EXTERNAL);
  analogReference(EXTERNAL);
  pinMode(2, INPUT); // Sub OCT switch
  pinMode(13, OUTPUT); // Teensy LED
  pinMode(3, OUTPUT); // Main LED
  digitalWrite(13, HIGH);
  digitalWrite(3, HIGH);
}

void loop() {

  // EXPRESSION PEDAL -> all 3 LFO frequencies
  currentPEDAL = analogRead(A0);
  diffPEDAL = currentPEDAL - smoothPEDAL;
  smoothPEDAL = smoothPEDAL + (diffPEDAL * 0.9f); // Lower decimal value = more smoothing
  expPedal = map(smoothPEDAL, 1, 1023, -512, 512);

  // MAIN OSCILLATOR FREQUENCY & AMPLITUDE
  waveform1.amplitude(0.8f);
  currentADCOSC = analogRead(A1);
  diffOSC = currentADCOSC - smoothADCOSC;
  smoothADCOSC = smoothADCOSC + (diffOSC * 0.005); // Decimal value is digital lowpass, lower value = more slew
  osc1 = mapfloat(smoothADCOSC, 0, 1023, 1.0f, 500.0f);
  waveform1.frequency(osc1);

  // MAIN OSCILLATOR WAVETABLE SELECTION WITH INTERPOLATION
  currentWAVE = analogRead(A3);
  diffWAVE = currentWAVE - smoothWAVE;
  smoothWAVE = smoothWAVE + (diffWAVE * 0.004f); // Decimal value is digital lowpass, lower value = more slew

  // Compute fractional position across the wavetable array
  float wavePos = mapfloat(smoothWAVE, 0, 1023, 0.0f, (float)(TABLE_NUM - 1));
  // Only recompute blend when position changes enough to avoid ADC noise artifacts
  if (fabsf(wavePos - lastWavePos) > 0.2f) {
    lastWavePos = wavePos;

    int waveIndexA = constrain((int)wavePos, 0, TABLE_NUM - 2);
    int waveIndexB = waveIndexA + 1;
    float blendAmt = constrain(wavePos - (float)waveIndexA, 0.0f, 1.0f);

    int16_t* waveA = const_cast<int16_t*>(waveTables[waveIndexA].table);
    int16_t* waveB = const_cast<int16_t*>(waveTables[waveIndexB].table);

    AudioNoInterrupts();
    for (int i = 0; i < 256; i++) {
      blendedWave[i] = (int16_t)((float)waveA[i] * (1.0f - blendAmt) + (float)waveB[i] * blendAmt);
    }
    waveform1.arbitraryWaveform(blendedWave, 500.0f);
    waveform2.arbitraryWaveform(blendedWave, 500.0f);
    AudioInterrupts();
  }

  // DETUNED OSCILLATOR SECTION
  if (digitalRead(2) == HIGH) {
    sub = 1;
  }
  else {
    sub = 2;
  }

  osc2 = osc1 + mapfloat(analogRead(A2), 0, 1023, -5.0f, 5.0f);
  waveform2.amplitude(0.8f);
  waveform2.frequency(osc2 / sub);

  oscMix = mapfloat(analogRead(A4), 0, 1023, 0.0f, 0.5f);
  mixer1.gain(0, 0.5f);
  mixer1.gain(1, oscMix);
  mixer1.gain(3, 0.0);

  // PHASER (FILTER 1) - 4-stage AudioFilterBiquad allpass + dry/wet mix
  cutoff1 = mapfloat(analogRead(A5), 0, 1023, 80.0f, 5000.0f);
  { float resRaw = analogRead(A6) / 1023.0f;
    res1 = resRaw * resRaw * 0.65f; }  // quadratic curve: gentle low end, aggressive top (max 0.65)
  mixer1.gain(2, res1);

  // LFO 1
  waveSelect2 = map(analogRead(A9), 0, 1023, 0, 5);
  waveform3.begin(waveShapesLFO1[waveSelect2]);
  waveform3.arbitraryWaveform(waveShapesLFO1, 100.0f);

  LFO1MATH = expPedal + analogRead(A10);
  LFO1MATH = max(LFO1MATH, 0);
  LFO1MATH = min(LFO1MATH, 1023);
  LFO1FREQ = 0.05f * powf(10000.0f, LFO1MATH / 1023.0f);
  waveform3.frequency(LFO1FREQ);

  LFO1AMP = mapfloat(analogRead(A11), 0, 1023, 0.0f, 2.0f);
  waveform3.amplitude(LFO1AMP);

  // Software LFO sweeps all 4 allpass stages
  uint32_t lfo1Now = micros();
  float lfo1dt = (lfo1LastMicros == 0) ? 0.0f : constrain((lfo1Now - lfo1LastMicros) / 1000000.0f, 0.0f, 0.05f);
  lfo1LastMicros = lfo1Now;
  lfo1Phase += LFO1FREQ * lfo1dt;
  if (lfo1Phase >= 1.0f) lfo1Phase -= 1.0f;

  lfo1Out = 0.0f;
  switch (waveSelect2) {
    case 0: lfo1Out = sinf(lfo1Phase * TWO_PI); break;
    case 1: lfo1Out = 1.0f - 4.0f * fabsf(lfo1Phase - 0.5f); break;
    case 2: lfo1Out = 2.0f * lfo1Phase - 1.0f; break;
    case 3: lfo1Out = 1.0f - 2.0f * lfo1Phase; break;
    case 4: lfo1Out = (lfo1Phase < 0.5f) ? 1.0f : -1.0f; break;
    case 5:
      if (lfo1Phase < lfo1PrevPhase)
        lfo1SHvalue = (random(32767) / 16383.5f) - 1.0f;
      lfo1PrevPhase = lfo1Phase;
      lfo1Out = lfo1SHvalue;
      break;
  }

  float phaserFreq = constrain(cutoff1 + lfo1Out * LFO1AMP * cutoff1, 100.0f, 8000.0f);
  setPhaserStage(0, phaserFreq, 0.707f);
  setPhaserStage(1, phaserFreq, 0.707f);
  setPhaserStage(2, phaserFreq, 0.707f);
  setPhaserStage(3, phaserFreq, 0.707f);

  // SAMPLE RATE AND BIT DEPTH
  sampleRedux = map(analogRead(A19), 0, 1023, 18000, 400);
  bitRate = map(analogRead(A20), 0, 1023, 11, 1);
  bitcrusher1.sampleRate(sampleRedux);
  bitcrusher1.bits(bitRate);

  // FILTER 2
  cutoff2 = mapfloat(analogRead(A7), 0, 1023, 80.0f, 15000.0f);
  res2 = mapfloat(analogRead(A8), 0, 1023, 1.5f, 5.0f);
  filter2.frequency(cutoff2);
  filter2.resonance(res2);

  // LFO 2
  waveSelect3 = map(analogRead(A12), 0, 1023, 0, 5);
  waveform4.begin(waveShapesLFO2[waveSelect3]);
  waveform4.arbitraryWaveform(waveShapesLFO3, 100.0f);

  LFO2MATH = expPedal + analogRead(A13);
  LFO2MATH = max(LFO2MATH, 0);
  LFO2MATH = min(LFO2MATH, 1023);
  LFO2FREQ = 0.05f * powf(10000.0f, LFO2MATH / 1023.0f);
  waveform4.frequency(LFO2FREQ);

  LFO2AMP = mapfloat(analogRead(A15), 0, 1023, 0.0f, 1.0f);
  waveform4.amplitude(LFO2AMP);

  { uint32_t lfo2Now = micros();
    float lfo2dt = (lfo2LastMicros == 0) ? 0.0f : constrain((lfo2Now - lfo2LastMicros) / 1000000.0f, 0.0f, 0.05f);
    lfo2LastMicros = lfo2Now;
    lfo2Phase += LFO2FREQ * lfo2dt;
    if (lfo2Phase >= 1.0f) lfo2Phase -= 1.0f;
    switch (waveSelect3) {
      case 0: lfo2Out = sinf(lfo2Phase * TWO_PI); break;
      case 1: lfo2Out = 1.0f - 4.0f * fabsf(lfo2Phase - 0.5f); break;
      case 2: lfo2Out = 2.0f * lfo2Phase - 1.0f; break;
      case 3: lfo2Out = 1.0f - 2.0f * lfo2Phase; break;
      case 4: lfo2Out = (lfo2Phase < 0.5f) ? 1.0f : -1.0f; break;
      case 5:
        if (lfo2Phase < lfo2PrevPhase) lfo2SHvalue = (random(32767) / 16383.5f) - 1.0f;
        lfo2PrevPhase = lfo2Phase;
        lfo2Out = lfo2SHvalue;
        break;
    }
  }

  // VCA
  dc1.amplitude(1.0f);
  mixer3.gain(0, 1.0f);
  mixer3.gain(1, 1.0f);
  mixer3.gain(2, 0.0f);
  mixer3.gain(3, 0.0f);

  // LFO 3
  waveSelect4 = map(analogRead(A16), 0, 1023, 0, 5);
  waveform5.begin(waveShapesLFO3[waveSelect4]);
  waveform5.arbitraryWaveform(waveShapesLFO3, 100.0f);

  LFO3MATH = expPedal + analogRead(A17);
  LFO3MATH = max(LFO3MATH, 0);
  LFO3MATH = min(LFO3MATH, 1023);
  LFO3FREQ = 0.05f * powf(10000.0f, LFO3MATH / 1023.0f);
  waveform5.frequency(LFO3FREQ);

  LFO3AMP = mapfloat(analogRead(A18), 0, 1023, 0.0f, 1.0f);
  waveform5.amplitude(LFO3AMP);

  { uint32_t lfo3Now = micros();
    float lfo3dt = (lfo3LastMicros == 0) ? 0.0f : constrain((lfo3Now - lfo3LastMicros) / 1000000.0f, 0.0f, 0.05f);
    lfo3LastMicros = lfo3Now;
    lfo3Phase += LFO3FREQ * lfo3dt;
    if (lfo3Phase >= 1.0f) lfo3Phase -= 1.0f;
    switch (waveSelect4) {
      case 0: lfo3Out = sinf(lfo3Phase * TWO_PI); break;
      case 1: lfo3Out = 1.0f - 4.0f * fabsf(lfo3Phase - 0.5f); break;
      case 2: lfo3Out = 2.0f * lfo3Phase - 1.0f; break;
      case 3: lfo3Out = 1.0f - 2.0f * lfo3Phase; break;
      case 4: lfo3Out = (lfo3Phase < 0.5f) ? 1.0f : -1.0f; break;
      case 5:
        if (lfo3Phase < lfo3PrevPhase) lfo3SHvalue = (random(32767) / 16383.5f) - 1.0f;
        lfo3PrevPhase = lfo3Phase;
        lfo3Out = lfo3SHvalue;
        break;
    }
  }

  // Final Output Attenuator
  mixer2.gain(0, 0.2f);
  mixer2.gain(1, 0.0f);
  mixer2.gain(2, 0.0f);
  mixer2.gain(3, 0.0f);

  // LEDs: map instantaneous LFO value (-1..+1) to full brightness range (0..255)
  analogWrite(4, (int)((lfo1Out * 0.5f + 0.5f) * 255.0f));
  analogWrite(5, (int)((lfo2Out * 0.5f + 0.5f) * 255.0f));
  analogWrite(6, (int)((lfo3Out * 0.5f + 0.5f) * 255.0f));
}
