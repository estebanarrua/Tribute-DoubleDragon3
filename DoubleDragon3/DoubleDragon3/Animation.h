#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include <vector>

using namespace std;

struct Frame
{
	SDL_Rect rect;
	bool flip;
};

class Animation
{
public:
	float speed;
	vector<Frame> frames;

private:
	float current_frame;

public:
	Animation() : frames(), speed(1.0f), current_frame(0.0f)
	{}

	Frame& GetCurrentFrame()
	{
		current_frame += speed;
		if(current_frame >= frames.size())
			current_frame = 0.0f;
		return frames[(int)current_frame];
	}
};

#endif //ANIMATION