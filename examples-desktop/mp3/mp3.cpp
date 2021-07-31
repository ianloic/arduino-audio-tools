// Simple wrapper for Arduino sketch to compilable with cpp in cmake
#include "Arduino.h"
#include "AudioTools.h"
#include "BabyElephantWalk60_mp3.h"

using namespace audio_tools;  


// MemoryStream -> AudioOutputStream -> MP3Decoder -> CsvStream
MemoryStream mp3(BabyElephantWalk60_mp3, BabyElephantWalk60_mp3_len);
PortAudioStream portaudio_stream;   // Output of sound on desktop 
MP3DecoderMini decoder(portaudio_stream);  // decode wav to pcm and send it to printer
AudioOutputStream out(decoder);     // output to decoder
StreamCopy copier(out, mp3);        // copy in to out


/// open portaudio with audio inform provided by mp3
void mp3InfoCallback(MP3MiniAudioInfo &info){
    PortAudioConfig pc;
    pc = info;
    portaudio_stream.begin(pc);
}

void setup(){
  Serial.begin(115200);
  AudioLogger::instance().begin(Serial, AudioLogger::Debug);  
  // this is not really necessary
  decoder.begin();
}

void loop(){
  if (mp3) {
    copier.copy();
  } else {
    auto info = decoder.audioInfo();
    LOGI("The audio rate from the mp3 file is %d", info.sample_rate);
    LOGI("The channels from the mp3 file is %d", info.channels);
    exit(0);
  }
}