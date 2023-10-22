#pragma once
#include <vector>

using namespace std;

class Animation
{
public:
	float speed;
	vector<SDL_Rect> frames;
	bool loop = true;

private:
	float current_frame;
	int loops = 0;

public:
	Animation() : frames(), speed(1.0f), current_frame(0.0f)
	{}

	SDL_Rect& GetCurrentFrame()
	{
		current_frame += speed;
		if (current_frame >= frames.size())
			current_frame = 0.0f;
		

		return frames[(int)current_frame];
	}

	bool Finished() const
	{
		return current_frame >= (frames.size() - 1); 
	}

	void Reset()
	{
		current_frame = 0.0f;
	}
};