#pragma once

#define _USE_MATH_DEFINES
#include <cmath>

#include <mpg123.h>
#include <vector>
#include <string>

#include <iostream>
#include <fstream>

#ifndef BYTE
typedef unsigned char BYTE;
#endif

class mp3ToPCM {
private:
	std::vector<BYTE> rawPcm;

public:
	std::string filename;

	mp3ToPCM(std::string filename) :
		filename(filename)
	{

	}

	// //http://www.cplusplus.com/forum/windows/210933/
	int loadFile()
	{

		mpg123_init();

		int err;
		mpg123_handle* mh = mpg123_new(NULL, &err);
		size_t buffer_size = mpg123_outblock(mh);
		BYTE* buf = (BYTE*)malloc(buffer_size * sizeof(BYTE));

		if (mpg123_open(mh, filename.c_str())) {
			return -1;
		}

		int channels, encoding;
		long rate;
		mpg123_getformat(mh, &rate, &channels, &encoding);

		int m_bits = mpg123_encsize(encoding);
		int m_rate = rate;
		int m_channels = channels;

		size_t done = 0;
		for (size_t totalBtyes = 0; mpg123_read(mh, buf, buffer_size, &done) == MPG123_OK; )
		{
			rawPcm.resize(rawPcm.size() + buffer_size);

			char* data = new char[done + 1];
			for (int i = 0; i != done; i++)
			{
				rawPcm[totalBtyes + i] = static_cast<BYTE>(buf[i]);
			}

			totalBtyes += done;
		}

		mpg123_close(mh);
		mpg123_delete(mh);
		mpg123_exit();

		return 0;
	}

	const std::vector<BYTE>& getBuf(void)
	{
		return this->rawPcm;
	}

	size_t getSize(void)
	{
		return (size_t)rawPcm.size();
	}

private:

	std::ifstream::pos_type filesize(const char* filename)
	{
		std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
		return in.tellg();
	}
};
