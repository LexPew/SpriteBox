#pragma once
class PerformanceMetrics
{
	//Handles calculating and returning all performance related metrics, e.g fps

private:
	//Smoothed Average frame rate
	float timeAveragedFramesPerSecond	{ 1 };	//This holds the final averaged fps count
	int frames							{ 0 };	 //Increased every update call until reset when framesTimer reaches 1
	float framesTimer					{ 100.0f }; //Timer that counts up to frameSmoothInterval via delta time
	float smoothingFactor				{ .5f }; //Controls how smooth the fps value is
	float frameSmoothInterval			{ 0.2f };
	//Sampled points
	#define maxSamples 50

	int sampleCounter{ 0 };
public:
	float framesPerSecondSamples[maxSamples];
	PerformanceMetrics()
	{
		
		for (int i = 0; i < maxSamples; i++)
		{
			framesPerSecondSamples[i] = 0;
		}
	}
	void Update(float deltaTime)
	{
		//Increase the frame counter and the timer
		frames++;
		framesTimer += deltaTime;

		//If we have reached a second or greater calculate the averaged framerate and reset the timer
		if (framesTimer >= frameSmoothInterval)
		{
			//(fpsAlpha * averageFps + (1.0f - fpsAlpha) * (framesThisSecond / fpsTimer));
			timeAveragedFramesPerSecond = (smoothingFactor * timeAveragedFramesPerSecond) + (1.0f - smoothingFactor) * (frames / framesTimer);
			frames = 0;
			framesTimer = 0;
			if (sampleCounter != maxSamples - 1)
			{
				sampleCounter++;

			}
			else
			{
				sampleCounter = 0;

			}
			framesPerSecondSamples[sampleCounter] = timeAveragedFramesPerSecond;
		}
	}
	float GetAveragedFrameRate()
	{
		return timeAveragedFramesPerSecond;
	}
	void SetSmoothingFactor(float newSmoothingFactor)
	{
		smoothingFactor = newSmoothingFactor;
	}
	int GetMaxSamples()
	{
		return maxSamples;
	}
};

