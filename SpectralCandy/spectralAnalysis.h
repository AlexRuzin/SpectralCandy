#pragma once

#include <assert.h>
#include <iterator>
#include <complex>
#include <vector>

#include "kissfft/kiss_fft.h"

class spectralAnalysis {
private:
	std::vector<float> rawfpu;
	const float pi;

public:
	const std::vector<BYTE>& rawBuf;
	const size_t sampleSize;

	spectralAnalysis(const std::vector<BYTE> in, size_t sampleSize) :
		rawBuf(in),
		sampleSize(sampleSize),
		pi(atan(1) * 4)
	{
		assert(in.size() != 0 && sampleSize != 0); 

		BYTE* buf = const_cast<BYTE*>(&rawBuf[0]);
		for (unsigned int i = 0; i < in.size() / 4; i++, buf += 4) {
			short lSample = *(const short*)buf;
			short rSample = *(const short*)(buf + 2);

			rawfpu.push_back(((float)lSample + (float)rSample) / 65536.f);
		}

		size_t pad = (sampleSize - rawfpu.size() % sampleSize) % sampleSize;
		if (pad > 0)
			rawfpu.resize(rawfpu.size() + pad, 0);
	}

	// Returns number of processed samples
	size_t processSamples(void)
	{
		for (std::vector<float>::const_iterator iSample = rawfpu.begin(); iSample != rawfpu.end(); iSample += sampleSize) {
			std::vector<float>* windowed = this->getWindow(std::vector<float>{iSample, iSample + sampleSize});

			const size_t nfft = sampleSize;
			kiss_fft_cfg cfg = kiss_fft_alloc(nfft, 0, 0, 0);

			std::vector<std::complex<float>> outFft(nfft, 0.0);

			kiss_fft(cfg, (kiss_fft_cpx*)&windowed[0], (kiss_fft_cpx*)&outFft[0]);
		}

		return 0;
	}

private:


	std::vector<float> *getWindow(const std::vector<float> in)
	{
		std::vector<float> *out = new std::vector<float>(in.size());
		for (std::vector<float>::const_iterator i = in.begin(); i != in.end(); i++) {
			float multiplier = 0.5 * (1 - (float)cosf(2 * pi * std::distance(in.begin(), i) / (in.size() - 1)));
			out->at(std::distance(in.begin(), i)) = multiplier * (*i);
		}

		return out;
	}
};