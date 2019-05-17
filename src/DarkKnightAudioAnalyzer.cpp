/*
 Copyright (C) 2019 Luis Fernando García [http://luiscript.com]
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */

#include "DarkKnightAudioAnalyzer.hpp"

void DarkKnightAudioAnalyzer::setup()
{
    
    smooth = power = 0.0;
    
    int sampleRate = 44100;
    int bufferSize = 512;
    int outChannels = 0;
    int inChannels = 2;
    
    // setup the sound stream
    
    
    ofSoundStreamSettings streamSettings;
    streamSettings.sampleRate = 44100;
    streamSettings.bufferSize = 512;
    streamSettings.numOutputChannels = 0;
    streamSettings.numInputChannels = 2;
    streamSettings.setInListener(this);
    
    soundStream.setup(streamSettings);
    
    audioAnalyzer.setup(sampleRate, bufferSize, inChannels);
    soundStream.start();
    audioAnalyzer.reset(sampleRate, bufferSize, inChannels);
}

void DarkKnightAudioAnalyzer::update()
{
    power = audioAnalyzer.getValue(POWER, 0, smooth);
    p->setValue(power);
}

void DarkKnightAudioAnalyzer::draw()
{
    
}

void DarkKnightAudioAnalyzer::addModuleParameters()
{
    gui->addSlider("Smooth", 0, 1)->bind(smooth);
    p = gui->addValuePlotter("", 0, 1);
    gui->addSlider("Power value ", 0, 1)->setPrecision(4)->bind(power);
}


void DarkKnightAudioAnalyzer::audioIn(ofSoundBuffer &inBuffer){
    audioAnalyzer.analyze(inBuffer);
}

void DarkKnightAudioAnalyzer::unMount()
{
    
    soundStream.stop();
    soundStream.close();
//    audioAnalyzer.exit();
}

