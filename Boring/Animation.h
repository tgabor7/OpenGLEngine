#pragma once
#include <vector>
#include "KeyFrame.h"
#include "EntityHandler.h"

using namespace std;

class Animation : public Component<Animation>
{
public:
	Animation();
	Animation(vector<int> jIndices, vector<float> weights, vector<KeyFrame> frames);
	vector<float> weights;
	vector<int> jointIndices;
	vector<KeyFrame> frames;
	void setFrames(int i);
	int i = 0;
	KeyFrame getFrame();
	void stepAnimation();
	void stepAnimation(float speed);

	~Animation();
private:
	float pointer;
};

