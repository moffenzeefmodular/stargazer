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
AudioFilterStateVariable filter1;        //xy=1902,1362
AudioSynthWaveformDc     dc1;            //xy=2009,1298
AudioSynthWaveform       waveform5;      //xy=2013,1244
AudioAnalyzeRMS          rms2;           //xy=2020,1476
AudioSynthWaveform       waveform4;      //xy=2024,1412
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
AudioConnection          patchCord3(waveform3, 0, filter1, 1);
AudioConnection          patchCord4(waveform3, waveshape1);
AudioConnection          patchCord5(mixer1, 0, filter1, 0);
AudioConnection          patchCord6(waveshape1, rms2);
AudioConnection          patchCord7(filter1, 0, bitcrusher1, 0);
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
float LFO2AMP = 0;
float LFO3AMP = 0;

float LFO1FREQ = 0;
float LFO1MATH = 0;
float LFO2FREQ = 0;
float LFO2MATH = 0;
float LFO3FREQ = 0;
float LFO3MATH = 0;

int waveSelect1CurrentState = 0;
int waveSelect1LastState = 0;

int waveSelect2CurrentState = 0;
int waveSelect2LastState = 0;

int waveSelect3CurrentState = 0;
int waveSelect3LastState = 0;

int waveSelect4CurrentState = 0;
int waveSelect4LastState = 0;

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
float smoothADCPEDAL = 0;
int currentADCPEDAL = 0;

int waveSelect = 0;

#define MAX_FREQ 600    // max frequency < - > arbitraryWaveform(array, maxFreq); 

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

#define TABLE_NUM 91 // 

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
  AKWF_distorted_0023,
  AKWF_distorted_0026,
  AKWF_distorted_0027,
  AKWF_distorted_0022,
  AKWF_distorted_0023,
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
  AKWF_hvoice_0039,
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

float mapfloat1(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void setup() {
  waveform1.begin(WAVEFORM_ARBITRARY);
  waveform2.begin(WAVEFORM_ARBITRARY);
  AudioMemory(100);  // put your setup code here, to run once:
  dac1.analogReference(EXTERNAL);
  analogReference(EXTERNAL);
  pinMode(2, INPUT); // Sub OCT switch
  pinMode(13, OUTPUT); // Teensy LED
  pinMode(3, OUTPUT); // Main LED
  digitalWrite(13, HIGH);
  digitalWrite(3, HIGH);
}

void loop() {

  // SCROLL DOWN TO VERY END OF LOOP TO SEE MAIN OSCILLATOR CODE. I HAD TO DECLARE ALL OF THAT LAST DUE TO
  // SOME STRANGE BUG IN TEENSY AUDIO LIBRARY IN REGARDS TO ARBITRARYWAVEFORM. I ALREADY SPOKE TO PAUL
  // ABOUT IT AND APPARENTLY IN THE NEWEST VERSION OF THE AUDIO LIBRARY IT IS REPAIRED. BEFORE I INTEGRATE
  // THE UPDATED OBJECT I WANT TO MAKE SURE IT HAS GONE THROUGH IT'S BETA PACES AND HAS BEEN ADEQUATELY TESTED.

  // Filter 2
  filter2.resonance(res2);
  res2 = mapfloat(analogRead(A8), 0, 1023, 1.5, 5.0);
  cutoff2 = mapfloat(analogRead(A7), 0, 1023, 80.0, 15000.0);
  filter2.frequency(cutoff2);

  // OSCILLATOR 2
  if (digitalRead(2) == HIGH) {
    sub = 1;
  }
  else {
    sub = 2;
  }

  waveform2.amplitude(0.8);
  osc2 = osc1 + mapfloat(analogRead(A2), 0, 1023, -5.0, 5.0);
  waveform2.frequency(osc2 / sub);

  oscMix = mapfloat(analogRead(A4), 0, 1023, 0.0, 0.5);

  // LFO 1
  currentADCPEDAL = analogRead(A0);
  diffPEDAL = currentADCPEDAL - smoothADCPEDAL;
  smoothADCPEDAL = smoothADCPEDAL + (diffPEDAL * 0.005);
  expPedal = map(smoothADCPEDAL, 1, 1023, -512, 512); // Change this line to cal pedal

  LFO1MATH = expPedal + analogRead(A10);
  LFO1MATH = max(LFO1MATH, 0);
  LFO1MATH = min(LFO1MATH, 1023);

  LFO1FREQ = mapfloat(LFO1MATH, 0, 1023, 0.05, 100.0);

  waveform3.frequency(LFO1FREQ);
  waveSelect2CurrentState = map(analogRead(A9), 0, 1010, 0, 5);

  if (waveSelect2CurrentState != waveSelect2LastState) {
    waveform3.begin(waveShapesLFO1[waveSelect2CurrentState]);
  }

  waveSelect2LastState = waveSelect2CurrentState;

  LFO1AMP = mapfloat(analogRead(A11), 0, 1023, 0.0, 1.0);
  waveform3.amplitude(LFO1AMP);

  // LFO 2
  LFO2AMP = mapfloat(analogRead(A15), 0, 1023, 0.0, 1.0);
  waveform4.amplitude(LFO2AMP);

  LFO2MATH = expPedal + analogRead(A13);
  LFO2MATH = max(LFO2MATH, 0);
  LFO2MATH = min(LFO2MATH, 1023);

  LFO2FREQ = mapfloat(LFO2MATH, 0, 1023, 0.05, 100.0);

  waveform4.frequency(LFO2FREQ);
  waveSelect3CurrentState = map(analogRead(A12), 0, 1010, 0, 5);

  if (waveSelect3CurrentState != waveSelect3LastState) {
    waveform4.begin(waveShapesLFO2[waveSelect3CurrentState]);
  }

  waveSelect3LastState = waveSelect3CurrentState;

  //LFO 3
  LFO3AMP = mapfloat(analogRead(A18), 0, 1023, 0.0, 1.0);
  waveform5.amplitude(LFO3AMP);

  LFO3MATH = expPedal + analogRead(A17);
  LFO3MATH = max(LFO3MATH, 0);
  LFO3MATH = min(LFO3MATH, 1023);

  LFO3FREQ = mapfloat(LFO3MATH, 0, 1023, 0.05, 100.0);
  waveform5.frequency(LFO3FREQ);

  waveSelect4CurrentState = map(analogRead(A16), 0, 1023, 0, 5);

  if (waveSelect4CurrentState != waveSelect4LastState) {
    waveform5.begin(waveShapesLFO3[waveSelect4CurrentState]);
  }

  waveSelect4LastState = waveSelect4CurrentState;

  // Bitcrusher
  bitRate = map(analogRead(A20), 0, 1023, 11, 1);
  sampleRedux = map(analogRead(A19), 0, 1023, 18000, 1);
  bitcrusher1.bits(bitRate);
  bitcrusher1.sampleRate(sampleRedux);

  // Oscillator Mixer
  mixer1.gain(0, 0.5);
  mixer1.gain(1, oscMix);
  mixer1.gain(2, 0.0);
  mixer1.gain(3, 0.0);

  // VCA
  dc1.amplitude(1.0);
  mixer3.gain(0, 1.0);
  mixer3.gain(1, 1.0);
  mixer3.gain(2, 0.0);
  mixer3.gain(3, 0.0);

  // Final Output Attenuator
  mixer2.gain(0, 0.2);
  mixer2.gain(1, 0.0);
  mixer2.gain(2, 0.0);
  mixer2.gain(3, 0.0);

  // Rectifiers for LEDS
  waveshape1.shape(rectify, 2);
  waveshape2.shape(rectify, 2);
  waveshape3.shape(rectify, 2);

  // Write LEDs
  LFO1led = mapfloat(rms2.read(), 0.5, 1.0, 0, 255);
  analogWrite(4, LFO1led);

  LFO2led = mapfloat(rms3.read(), 0.5, 1.0, 0, 255);
  analogWrite(5, LFO2led);

  LFO3led = mapfloat(rms4.read(), 0.5, 1.0, 0, 255);
  analogWrite(6, LFO3led);

  // MAIN OSCILLATOR FREQUENCY & AMPLITUDE
  waveform1.amplitude(0.8);

  currentADCOSC = analogRead(A1);
  diffOSC = currentADCOSC - smoothADCOSC;
  smoothADCOSC = smoothADCOSC + (diffOSC * 0.01f); // Decimal value is digital lowpass, lower value = more slew
  osc1 = mapfloat(smoothADCOSC, 0.0, 1023.0, 1.0, 500.0);
  waveform1.frequency(osc1);

  // MAIN OSCILLATOR WAVETABLE SELECTION
  currentWAVE = analogRead(A3);
  diffWAVE = currentWAVE - smoothWAVE;
  smoothWAVE = smoothWAVE + (diffWAVE * 0.008f); // Decimal value is digital lowpass, lower value = more slew

  waveSelect = map(smoothWAVE, 0, 1023, 1, 91);

  struct WaveTable* waveTable  = &waveTables[waveSelect];
  int16_t* wave = const_cast<short int*>(waveTable->table);

  waveform1.arbitraryWaveform(wave, MAX_FREQ);
  waveform2.arbitraryWaveform(wave, MAX_FREQ);

  // Filter 1
  cutoff1 = mapfloat(analogRead(A5), 0, 1023, 80.0, 5000.0);
  res1 = mapfloat(analogRead(A6), 0, 1023, 1.5, 5.0);
  filter1.frequency(cutoff1);
  filter1.resonance(res1);

}
