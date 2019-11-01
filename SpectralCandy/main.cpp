// https://github.com/zyfu0000/lameHelper/blob/master/Windows/lameHelper.cpp
// http://www.cplusplus.com/forum/windows/210933/

#include <Windows.h>
#include <string>
#include <iostream>
#include <fstream>

#include <mpg123.h>

class mp3ToPCM {
private:
	char *buf;

	

public:
	std::string filename;
	
	mp3ToPCM(std::string filename) :
		filename(filename)
	{

	}

	// //http://www.cplusplus.com/forum/windows/210933/
	int loadFile()
	{

		buf = new char(filesize(filename.c_str()));

		mpg123_init();

		int err;
		mpg123_handle *mh = mpg123_new(NULL, &err);
		size_t buffer_size = mpg123_outblock(mh);
		unsigned char* buffer = new unsigned char(buffer_size * sizeof(char));

		mpg123_open(mh, filename.c_str());

		int channels, encoding;
		long rate;
		mpg123_getformat(mh, &rate, &channels, &encoding);

		int m_bits = mpg123_encsize(encoding);
		int m_rate = rate;
		int m_channels = channels;

		size_t done;
		for (int totalBtyes = 0; mpg123_read(mh, buffer, buffer_size, &done) == MPG123_OK; )
		{
			char* data = new char[done + 1];
			for (int i = 0; i != done; i++)
			{
				char tst = static_cast<char>(buffer[i]);
			}

			totalBtyes += done;
		}

		mpg123_close(mh);
		mpg123_delete(mh);
		mpg123_exit();

		return 0;
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
	mp3ToPCM rawPCM{ "test.mp3" };
	if (rawPCM.loadFile()) {
		std::cout << "[!] Failed to decode into PCM" << std::endl;
		return -1;
	}


	return 0;
}

void panic(std::string s)
{
	std::cout << "[!] " << s << std::endl;
	ExitProcess(0);
}