#include "Audio.hpp"

#include <Mmsystem.h>
#include <mciapi.h>
#pragma comment(lib, "Winmm.lib")

namespace Moon
{
	void Audio::Play(const String& file)
	{
		String play = "play \"./src/sound/" + file + "\"";
		mciSendStringW(WString(play.begin(), play.end()).c_str(), NULL, 0, NULL);
	}
}