// https://github.com/zyfu0000/lameHelper/blob/master/Windows/lameHelper.cpp
// http://www.cplusplus.com/forum/windows/210933/
// https://rodic.fr/blog/libavcodec-tutorial-decode-audio-file/
// https://asawicki.info/news_1385_music_analysis_-_spectrogram.html

#include <Windows.h>
#include <string>

#include "mp3ToPCM.h"
#include "spectralAnalysis.h"
#include "window.h"
#include "kissfft/kiss_fft.h"

#define USE_MPG123
#ifndef USE_MPG123
#include "ffmpeg_decode.h"
#endif

int main(void)
{
#ifdef USE_MPG123
	mp3ToPCM rawPCM{ "..\\test.mp3" };
	if (rawPCM.loadFile()) {
		std::cout << "[!] Failed to decode into PCM" << std::endl;
		return -1;
	}

	double* pcmBuf = NULL;
	rawPCM.getFpuBuf(&pcmBuf);
#else
#endif

	return 0;
}

void panic(std::string s)
{
	std::cout << "[!] " << s << std::endl;
	ExitProcess(0);
}