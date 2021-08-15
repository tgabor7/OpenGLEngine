#include "Animation.h"



Animation::Animation()
{
}
Animation::Animation(vector<int> jIndices, vector<float> weights, vector<KeyFrame> frames)
{
	this->weights = weights;
	this->jointIndices = jIndices;
	this->frames = frames;

}
void Animation::setFrames(int i) {
	this->i = i;
}
KeyFrame Animation::getFrame() {
	return this->frames[i];
}
void Animation::stepAnimation(float speed) {
	if ((int)pointer < frames.size() - 1) {
		pointer += speed;
	}
	else {
		pointer = 0;
	}
	this->i = (int)pointer;
}
void Animation::stepAnimation() {
	if (i < frames.size() - 1) {
		i++;
	}
	else {
		i = 0;
	}

}
Animation::~Animation()
{
}
