#pragma once
#include <JuceHeader.h>


#define NAME_WF		   "sigType"
#define NAME_F1        "Freq 1"
#define NAME_F2        "Freq 2"
#define NAME_F3        "Freq 3"
#define NAME_BAL       "Balance"
#define NAME_DUR       "Duration"
#define NAME_Q         "Quality"
#define NAME_TYP       "Type"
#define NAME_LOG       "dbScale"
#define NAME_DR        "DynRange"
#define NAME_LVL       "outLevel"
#define NAME_ACTV      "active"

#define DEFAULT_WF     0
#define DEFAULT_F1     100.0
#define DEFAULT_F2     100.0
#define DEFAULT_F3     10000.0
#define DEFAULT_BAL    0.0
#define DEFAULT_DUR    0.0
#define DEFAULT_Q      0.707
#define DEFAULT_TYP    0
#define DEFAULT_LOG    0
#define DEFAULT_DR     -20.0
#define DEFAULT_LVL    0.0
#define DEFAULT_ACTV   false

#define RATE_SMTH      0.05
#define AMP_SMTH       0.05

#define NOISE_ID       1

const auto oscChoices = StringArray{ "Sine", "Noise", "2 Sines", "Sine + Noise", "Impulse train", "Log sweep", "Ramp", "Ramp * Sine", "Ramp * Noise", "Sine Burst", "Noise Burst" };
const auto filtChoices = StringArray{ "LP", "BP", "HP" };
const auto rampChoices = StringArray{ "Linear +", "dB +", "Linear -", "dB -" };

static AudioProcessorValueTreeState::ParameterLayout createParameterLayout()
{
    std::vector<std::unique_ptr<RangedAudioParameter>> params;

    params.push_back(std::make_unique<AudioParameterChoice>(NAME_WF, "Signal type", oscChoices, DEFAULT_WF));
    
    params.push_back(std::make_unique<AudioParameterFloat>(NAME_F1, "Frequency 1", NormalisableRange<float>(0.05f, 20000, 0.001f, 0.15f), DEFAULT_F1));
    params.push_back(std::make_unique<AudioParameterFloat>(NAME_F2, "Frequency 2", NormalisableRange<float>(0.05f, 20000, 0.001f, 0.15f), DEFAULT_F2));
    params.push_back(std::make_unique<AudioParameterFloat>(NAME_F3, "Frequency 3", NormalisableRange<float>(0.05f, 20000, 0.001f, 0.15f), DEFAULT_F3));
    params.push_back(std::make_unique<AudioParameterFloat>(NAME_BAL, "Balance", NormalisableRange<float>(-1.0f, 1.0, 0.001f, 4.0f, true), DEFAULT_BAL));
    params.push_back(std::make_unique<AudioParameterFloat>(NAME_DUR, "Duration (%)", NormalisableRange<float>(0.0f, 1.0, 0.001f), DEFAULT_DUR));
    params.push_back(std::make_unique<AudioParameterFloat>(NAME_Q, "Quality", NormalisableRange<float>(0.1f, 20.0, 0.01f, 0.6), DEFAULT_Q));
    params.push_back(std::make_unique<AudioParameterChoice>(NAME_TYP, "Filter type", filtChoices, DEFAULT_TYP));
    params.push_back(std::make_unique<AudioParameterChoice>(NAME_LOG, "Ramp type", rampChoices, DEFAULT_LOG));
    params.push_back(std::make_unique<AudioParameterFloat>(NAME_DR, "Dynamic range", NormalisableRange<float>(-96.0f, 0.0, 0.1f, 3.0f), DEFAULT_DR));

    params.push_back(std::make_unique<AudioParameterFloat>(NAME_LVL, "Out level", NormalisableRange<float>(-96.0f, 6.0f, 0.01f, 2.0f), DEFAULT_LVL));
    params.push_back(std::make_unique<AudioParameterBool>(NAME_ACTV, "Active", DEFAULT_ACTV));

    return { params.begin(), params.end() };
}