#pragma once

class CustomRenderSystem
{
public:
	CustomRenderSystem();
	virtual void render() = 0;
	virtual ~CustomRenderSystem() = 0;
private:
};
