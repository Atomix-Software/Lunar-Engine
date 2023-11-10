#include "OpenAL.hpp"
#include "AudioData.h"

#include <luna/core/Log.h>

namespace luna
{
	namespace audio
	{

		void start_ogg(const OggStreamData& audioData)
		{
			alCall(alSourceStop, audioData.Source);
			alCall(alSourcePlay, audioData.Source);
		}

		void stop_ogg(const OggStreamData& audioData)
		{
			alCall(alSourceStop, audioData.Source);
		}

		void pause_ogg(const OggStreamData& audioData)
		{
			alCall(alSourcePause, audioData.Source);
		}

		void resume_ogg(const OggStreamData& audioData)
		{
			start_ogg(audioData);
		}

		void update_ogg(OggStreamData& audioData)
		{
			ALint buffersProcessed = 0;
			alCall(alGetSourcei, audioData.Source, AL_BUFFERS_PROCESSED, &buffersProcessed);
			if (buffersProcessed <= 0)
				return;

			while (buffersProcessed--)
			{
				ALuint buffer;
				alCall(alSourceUnqueueBuffers, audioData.Source, 1, &buffer);

				char* data = new char[BUFFER_SIZE];
				std::memset(data, 0, BUFFER_SIZE);

				ALsizei dataSizeToBuffer = 0;
				std::int32_t sizeRead = 0;

				while (sizeRead < BUFFER_SIZE)
				{
					std::int32_t result = ov_read(&audioData.OggVorbisFile, &data[sizeRead], BUFFER_SIZE - sizeRead, 0, 2, 1, &audioData.OggCurrentSection);
					switch (result)
					{
					case OV_HOLE:
						LNA_CORE_ERROR("OV_HOLE found in when updating buffer!");
						break;
					case OV_EBADLINK:
						LNA_CORE_ERROR("OV_EBADLINK found in when updating buffer!");
						break;
					case OV_EINVAL:
						LNA_CORE_ERROR("OV_EINVAL found in when updating buffer!");
						break;
					case 0:
						std::int32_t seekResult = ov_raw_seek(&audioData.OggVorbisFile, 0);
						if (seekResult == OV_ENOSEEK)
							LNA_CORE_ERROR("OV_ENOSEEK found in when trying to loop!");
						else if (seekResult == OV_EINVAL)
							LNA_CORE_ERROR("OV_EINVAL found in when trying to loop!");
						else if (seekResult == OV_EREAD)
							LNA_CORE_ERROR("OV_EREAD found in when trying to loop!");
						else if (seekResult == OV_EFAULT)
							LNA_CORE_ERROR("OV_EFAULT found in when trying to loop!");
						else if (seekResult == OV_EOF)
							LNA_CORE_ERROR("OV_EOF found in when trying to loop!");
						else if (seekResult == OV_EBADLINK)
							LNA_CORE_ERROR("OV_EBADLINK found in when trying to loop!");

						if (seekResult != 0)
						{
							LNA_CORE_ERROR("Unknown error in ov_raw_seek!");
							return;
						}
					}

					sizeRead += result;
				}
				dataSizeToBuffer = sizeRead;

				if (dataSizeToBuffer > 0)
				{
					alCall(alBufferData, buffer, audioData.Format, data, dataSizeToBuffer, audioData.SampleRate);
					alCall(alSourceQueueBuffers, audioData.Source, 1, &buffer);
				}

				ALint state, looping;
				alCall(alGetSourcei, audioData.Source, AL_SOURCE_STATE, &state);
				alCall(alGetSourcei, audioData.Source, AL_LOOPING, &looping);

				if ((state != AL_PLAYING && AL_LOOPING == AL_TRUE) && state != AL_PAUSED)
				{
					alCall(alSourceStop, audioData.Source);
					alCall(alSourcePlay, audioData.Source);
				}
				else if ((state != AL_PLAYING && AL_LOOPING == AL_FALSE))
				{
					alCall(alSourceStop, audioData.Source);
					alCall(alSourceRewind, audioData.Source);
				}

				delete[] data;
			}
		}

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

		bool create_stream_from_file(const std::string& filename, OggStreamData& audioData)
		{
			audioData.Filename = filename;
			audioData.File.open(filename, std::ios::binary);
			if (!audioData.File.is_open())
			{
				LNA_CORE_ERROR("Couldn't open OGG file!");
				return false;
			}

			audioData.File.seekg(0, std::ios_base::beg);
			audioData.File.ignore(std::numeric_limits<std::streamsize>::max());
			audioData.Size = audioData.File.gcount();
			audioData.File.clear();
			audioData.File.seekg(0, std::ios_base::beg);
			audioData.SizeConsumed = 0;

			ov_callbacks oggCallbacks;
			oggCallbacks.read_func = read_ogg_callback;
			oggCallbacks.close_func = nullptr;
			oggCallbacks.seek_func = seek_ogg_callback;
			oggCallbacks.tell_func = tell_ogg_callback;

			if (ov_open_callbacks(reinterpret_cast<void*>(&audioData), &audioData.OggVorbisFile, nullptr, -1, oggCallbacks) < 0)
			{
				LNA_CORE_ERROR("Could not setup ogg callbacks!");
				return false;
			}

			vorbis_info* vorbisInfo = ov_info(&audioData.OggVorbisFile, -1);

			audioData.Channels = vorbisInfo->channels;
			audioData.BitsPerSample = 16;
			audioData.SampleRate = vorbisInfo->rate;
			audioData.Duration = ov_time_total(&audioData.OggVorbisFile, -1);

			alCall(alGenSources, 1, &audioData.Source);
			alCall(alSourcef, audioData.Source, AL_PITCH, 1);
			alCall(alSourcef, audioData.Source, AL_GAIN, DEFAULT_GAIN);
			alCall(alSource3f, audioData.Source, AL_POSITION, 0, 0, 0);
			alCall(alSource3f, audioData.Source, AL_VELOCITY, 0, 0, 0);
			alCall(alSourcei, audioData.Source, AL_LOOPING, AL_FALSE);

			alCall(alGenBuffers, NUM_BUFFERS, &audioData.Buffers[0]);

			if (audioData.File.eof())
			{
				LNA_CORE_ERROR("Already reached end without loading data!");
				return false;
			}
			else if (audioData.File.fail())
			{
				LNA_CORE_ERROR("Fail bit set!");
				return false;
			}
			else if (!audioData.File)
			{
				LNA_CORE_ERROR("Failed to load the file");
				return false;
			}

			char* data = new char[BUFFER_SIZE];
			for (std::uint8_t i = 0; i < NUM_BUFFERS; i++)
			{
				std::int32_t dataSoFar = 0;
				while (dataSoFar < BUFFER_SIZE)
				{
					std::int32_t result = ov_read(&audioData.OggVorbisFile, &data[dataSoFar], BUFFER_SIZE - dataSoFar, 0, 2, 1, &audioData.OggCurrentSection);
					switch (result)
					{
					case OV_HOLE:
						LNA_CORE_ERROR("OV_HOLE found in the buffer!");
						break;
					case OV_EBADLINK:
						LNA_CORE_ERROR("OV_EBADLINK found in the buffer!");
						break;
					case OV_EINVAL:
						LNA_CORE_ERROR("OV_EINVAL found in the buffer!");
						break;
					case 0:
						LNA_CORE_WARN("Reached EOF in buffer!");
						break;
					default:
						dataSoFar += result;
						break;
					}
				}

				if (audioData.Channels == 1 && audioData.BitsPerSample == 8)
					audioData.Format = AL_FORMAT_MONO8;
				else if (audioData.Channels == 1 && audioData.BitsPerSample == 16)
					audioData.Format = AL_FORMAT_MONO16;
				else if (audioData.Channels == 2 && audioData.BitsPerSample == 8)
					audioData.Format = AL_FORMAT_STEREO8;
				else if (audioData.Channels == 2 && audioData.BitsPerSample == 16)
					audioData.Format = AL_FORMAT_STEREO16;
				else
				{
					LNA_CORE_ERROR("Unrecognized ogg format: {} channels, {} bps!", audioData.Channels, audioData.BitsPerSample);
					delete[] data;
					return false;
				}

				alCall(alBufferData, audioData.Buffers[i], audioData.Format, data, dataSoFar, audioData.SampleRate);
			}

			alCall(alSourceQueueBuffers, audioData.Source, NUM_BUFFERS, &audioData.Buffers[0]);

			delete[] data;
			return true;
		}

	}
}