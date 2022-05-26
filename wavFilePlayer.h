#include <Audio.h>
// #include <Wire.h> // already in mpr121.h
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

const char *mySounds[] = {"ONE.WAV", "TWO.WAV", "THREE.WAV",
                     "FOUR.WAV", "FIVE.WAV", "SIX.WAV", "SEVEN.WAV",
                     "EIGHT.WAV", "NINE.WAV", "TEN.WAV", "ELEVEN.WAV",
                     "TWELVE.WAV"}; // filenames are always uppercase 8.3 format

// GUItool: begin automatically generated code
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioPlaySdWav           playSdWav1;     //xy=250,98
AudioEffectEnvelope      envelope1;      //xy=634,146
AudioEffectEnvelope      envelope2;      //xy=664,288
AudioAmplifier           amp1;           //xy=966,318
AudioAmplifier           amp2;           //xy=973,412
AudioOutputI2S           i2s1;           //xy=1094,556
AudioConnection          patchCord1(playSdWav1, 0, envelope1, 0);
AudioConnection          patchCord2(playSdWav1, 1, envelope2, 0);
AudioConnection          patchCord3(envelope1, amp1);
AudioConnection          patchCord4(envelope2, amp2);
AudioConnection          patchCord5(amp1, 0, i2s1, 0);
AudioConnection          patchCord6(amp2, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=841,659
// GUItool: end automatically generated code


// Use these with the Teensy Audio Shield
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14

void init_player() {

  // Audio connections require memory to work.  For more
  // detailed information, see the MemoryAndCpuUsage example
  AudioMemory(8);

  // Comment these out if not using the audio adaptor board.
  // This may wait forever if the SDA & SCL pins lack
  // pullup resistors
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);

  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  if (!(SD.begin(SDCARD_CS_PIN))) {
    // stop here, but print a message repetitively
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }
}

// Map of which voice has which key playing
int active[MAX_POLY];
// Map of when each voice started playing, for note stealing
long when[MAX_POLY];
// Map of when we started the fade out so we know when to kill the note after the fade
long faded_ms[MAX_POLY];

void playSound(int track) {
//    int player = get_free_voice();/
//    Serial.print("notezzzz");
//    Serial.println(player);

playSdWav1.play(mySounds[track]);
envelope1.noteOn();
envelope2.noteOn();
}
