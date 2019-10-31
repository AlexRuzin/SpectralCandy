#include <Windows.h>
#include <string>
#include <iostream>
#include <fstream>

#include <lame/lame.h>

class mp3RawFile {
private:
	char *buf;

	lame_t lame;

public:
	std::string filename;
	
	mp3RawFile(std::string filename) :
		filename(filename)
	{

	}

	int loadFile()
	{
		buf = new char(filesize(filename.c_str()));

		lame = lame_init();
		lame_set_in_samplerate(lame, 44100);
		lame_set_VBR(lame, vbr_default);
		lame_init_params(lame);

		FILE* mp3 = fopen(filename.c_str(), "rb");
		if (mp3 == NULL) {
			panic("Failed to read file: " + filename);
		}

		do {
			read = fread(pcm_buffer, 2 * sizeof(short int), PCM_SIZE, pcm);
			if (read == 0)
				write = lame_encode_flush(lame, mp3_buffer, MP3_SIZE);
			else
				write = lame_encode_buffer_interleaved(lame, pcm_buffer, read, mp3_buffer, MP3_SIZE);
			fwrite(mp3_buffer, write, 1, mp3);
		} while (read != 0);

		lame_close(lame);


	}

private:
	std::ifstream::pos_type filesize(const char* filename)
	{
		std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
		return in.tellg();
	}
};

int main(void)
{


	return 0;
}

void panic(std::string s)
{
	std::cout << "[!] " << s << std::endl;
	ExitProcess(0);
}