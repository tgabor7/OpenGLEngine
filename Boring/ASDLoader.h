#pragma once
#include "DataTypes.h"
#include "Animation.h"

typedef unsigned char byte;
class ASDLoader
{

public:
	ASDLoader();
	static ModelData loadSkin(const char* path);
	static Animation loadAnimation(const char* path);
	~ASDLoader();

};

