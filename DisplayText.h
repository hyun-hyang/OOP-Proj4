#ifndef _DISPLAYTEXT_
#define _DISPLAYTEXT_

#include <vector>
#include <string>

#include "d3dUtility.h"
#include "d3dfont.h"

using std::vector;
using std::string;

class DisplayText
{
private:

	int windowWidth;
	int windowHeight;

	string jumperName;
	string playerBallCount[2];

	string turnStatus;

	CD3DFont* FontObjects[7];

public:
	DisplayText(const int windowWidth, const int windowHeight);
	~DisplayText();

	bool create(const char* fontFamily, const int fontSize, IDirect3DDevice9* pDevice);
	void destory();

	bool update();
};

#endif