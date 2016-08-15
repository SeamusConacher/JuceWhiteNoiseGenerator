/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

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
		setSize(800, 600);

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
		for (int channel = 0; channel < bufferToFill.buffer->getNumChannels(); ++channel)
		{
			// Get a pointer to the start sample in the buffer for this audio output channel
			float* const buffer = bufferToFill.buffer->getWritePointer(channel, bufferToFill.startSample);

			// Fill the required number of samples with noise between -0.125 and 0.125
			for (int sample = 0; sample < bufferToFill.numSamples; ++sample)
			{
				buffer[sample] = random.nextFloat() * 0.25f - 0.125f;
			}
		}
	}

	void releaseResources() override
	{
		Logger::getCurrentLogger()->writeToLog("Releasing audio resources");
	}

	//==============================================================================
	void paint(Graphics& g) override
	{
		// (Our component is opaque, so we must completely fill the background with a solid colour)
		g.fillAll(Colours::black);
	}

	void resized() override
	{
		// This is called when the MainContentComponent is resized.
		// If you add any child components, this is where you should
		// update their positions.
	}


private:
	Random random;
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainContentComponent)
};


// (This function is called by the app startup code to create our main component)
Component* createMainContentComponent()     { return new MainContentComponent(); }


#endif  // MAINCOMPONENT_H_INCLUDED
