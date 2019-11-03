#pragma once

#include <vector>
#include <assert.h>

class hanningWindow {
private:
	std::vector<BYTE>* output;

public:
	const std::vector<BYTE> inBuffer;

	hanningWindow(const std::vector<BYTE> b) :
		inBuffer(b),
		output(NULL)
	{

	}

	int doWindow(__out std::vector<BYTE>** o)
	{
		this->output = new std::vector<BYTE>(2048);
		for (std::vector<BYTE>::const_iterator i = inBuffer.begin(); i != inBuffer.end(); i++) {

		}
	}

	std::vector<BYTE>* getOutput()
	{
		assert(this->output != NULL);
		return this->output;
	}
};