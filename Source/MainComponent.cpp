#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainContentComponent : public AudioAppComponent
{
public:
	//==============================================================================
	MainContentComponent()
	{
		levelSliderL.setRange(0.0, 0.25);
		levelSliderL.setTextBoxStyle(Slider::TextBoxRight, false, 100, 20);
		levelSliderR.setRange(0.0, 0.25);
		levelSliderR.setTextBoxStyle(Slider::TextBoxRight, false, 100, 20);
		levelLabelL.setText("Noise Level L", dontSendNotification);
		levelLabelR.setText("Noise Level R", dontSendNotification);

		addAndMakeVisible(levelSliderL);
		addAndMakeVisible(levelSliderR);
		addAndMakeVisible(levelLabelL);
		addAndMakeVisible(levelLabelR);

		setSize(600, 75);

		// No inputs, two outputs
		setAudioChannels(0, 2);
	}

	~MainContentComponent()
	{
		shutdownAudio();
	}

	//==============================================================================
	void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override
	{
		// Log the block size and sample rate
		String message;
		message << "Preparing to play audio..." << newLine;
		message << " samplesPerBlockExpected = " << samplesPerBlockExpected << newLine;
		message << " sampleRate = " << sampleRate;
		Logger::getCurrentLogger()->writeToLog(message);
	}

	void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override
	{
		const float levelL = (float)levelSliderL.getValue();
		const float levelR = (float)levelSliderR.getValue();
		float level;

		for (int channel = 0; channel < bufferToFill.buffer->getNumChannels(); ++channel)
		{
			if (channel == 0)
			{
				level = levelL;
			}
			else
			{
				level = levelR;
			}

			// Get a pointer to the start sample in the buffer for this audio output channel
			float* const buffer = bufferToFill.buffer->getWritePointer(channel, bufferToFill.startSample);

			// Fill the required number of samples with noise between -0.125 and 0.125
			for (int sample = 0; sample < bufferToFill.numSamples; ++sample)
			{
				const float noise = random.nextFloat() * 2.0f - 1.0f;
				// While this method of volume control will add distortion as the slider is moved,
				// the output is noise anyway, so in this situation it is fine
				buffer[sample] = noise * level;
			}
		}
	}

	void releaseResources() override
	{
		Logger::getCurrentLogger()->writeToLog("Releasing audio resources");
	}

	void resized() override
	{
		levelLabelL.setBounds(10, 10, 90, 20);
		levelLabelR.setBounds(10, 40, 92, 20);
		levelSliderL.setBounds(100, 10, getWidth() - 110, 20);
		levelSliderR.setBounds(100, 40, getWidth() - 110, 20);
	}


private:
	Slider levelSliderL;
	Slider levelSliderR;
	Label levelLabelL;
	Label levelLabelR;
	Random random;
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainContentComponent)
};


// (This function is called by the app startup code to create our main component)
Component* createMainContentComponent()     { return new MainContentComponent(); }


#endif  // MAINCOMPONENT_H_INCLUDED
