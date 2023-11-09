#include "AudioData.h"

#include <luna/core/Log.h>

namespace luna
{
	namespace audio
	{

		std::size_t read_ogg_callback(void* destination, std::size_t size1, std::size_t size2, void* fileHandle)
		{
			OggStreamData* audioData = reinterpret_cast<OggStreamData*>(fileHandle);
			ALsizei length = size1 * size2;

			if (audioData->SizeConsumed + length > audioData->Size)
				length = audioData->Size - audioData->SizeConsumed;

			if (!audioData->File.is_open())
			{
				audioData->File.open(audioData->Filename, std::ios::binary);
				if (!audioData->File.is_open())
				{
					LNA_CORE_ERROR("Could not re-open streaming file: {}", audioData->Filename);
					return 0;
				}
			}

			char* moreData = new char[length];
			audioData->File.clear();

			audioData->File.seekg(audioData->SizeConsumed);
			if (!audioData->File.read(&moreData[0], length))
			{
				if (audioData->File.eof())
				{
					audioData->File.clear();
				}
				else if (audioData->File.fail())
				{
					LNA_CORE_ERROR("OGG stream has fail bit set: {}", audioData->Filename);
					audioData->File.clear();
					return 0;
				}
				else if (audioData->File.bad())
				{
					LNA_CORE_ERROR("OGG stream has bad bit set: {}", audioData->Filename);
					audioData->File.clear();
					return 0;
				}
			}

			audioData->SizeConsumed += length;
			std::memcpy(destination, &moreData[0], length);

			delete[] moreData;
			audioData->File.clear();

			return length;
		}

		std::int32_t seek_ogg_callback(void* fileHandle, ogg_int64_t to, std::int32_t type)
		{
			OggStreamData* audioData = reinterpret_cast<OggStreamData*>(fileHandle);

			switch (type)
			{
			case SEEK_CUR:
				audioData->SizeConsumed += to;
				break;
			case SEEK_END:
				audioData->SizeConsumed = audioData->Size - to;
				break;
			case SEEK_SET:
				audioData->SizeConsumed = to;
				break;
			default:
				return -1;
			}

			if (audioData->SizeConsumed < 0)
			{
				audioData->SizeConsumed = 0;
				return -1;
			}

			if (audioData->SizeConsumed > audioData->Size)
			{
				audioData->SizeConsumed = audioData->Size;
				return -1;
			}

			return 0;
		}

		long int tell_ogg_callback(void* fileHandle)
		{
			OggStreamData* audioData = reinterpret_cast<OggStreamData*>(fileHandle);
			return audioData->SizeConsumed;
		}

	}
}