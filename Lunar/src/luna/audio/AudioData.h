#pragma once

#include <string>
#include <iostream>
#include <fstream>

#include <ogg/ogg.h>
#include <vorbis/vorbisfile.h>

#include <AL/al.h>

const size_t NUM_BUFFERS = 4;
const ALsizei BUFFER_SIZE = 65536;

namespace luna
{
	namespace audio
	{

		struct OggStreamData
		{
			ALuint Buffers[NUM_BUFFERS];
			std::string Filename;
			std::ifstream File;

			std::uint8_t Channels;
			std::int32_t SampleRate;
			std::uint8_t BitsPerSample;

			ALsizei Size;
			ALuint Source;
			ALsizei SizeConsumed = 0;
			ALenum Format;

			OggVorbis_File OggVorbisFile;
			std::int_fast32_t OggCurrentSection = 0;
			std::size_t Duration;
		};

	}
}