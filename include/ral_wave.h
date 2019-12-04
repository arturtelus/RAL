#pragma once

#include<cstdint>
#include<array>
#include<vector>
#include<memory>
#include<functional>

namespace ral
{
	///Wav file header descriptor 44B
	struct WaveHeader
	{
		//RIFF chunk

		///Riff chunk id, four characters.
		std::array<std::uint8_t, 4> riff_chunk_id; //'RIFF' Big endian

		///File size - 8B
		std::uint32_t riff_chunk_size;

		///File type
		std::array<std::uint8_t, 4> riff_chunk_format; //'WAVE' Big endian

		//FMT subchunk

		///FMT chunk id
		std::array<std::uint8_t, 4> fmt_chunk_id; //'fmt ' Big endian

		///Length of format data (16B)
		std::uint32_t fmt_chunk_size;

		///Audio format, (1 - PCM)
		std::uint16_t audio_format;

		///Number of audio channels (1-mono, 2-stereo)
		std::uint16_t number_of_channels;

		///Audio sampling rate
		std::uint32_t sample_rate;

		///sample_rate * number_of_channels * bits_per_sample / 8
		std::uint32_t byte_rate;

		///number_of_channels * bits_per_sample / 8
		std::uint16_t block_align;

		///Number of bits per sound sample
		std::uint16_t bits_per_sample;

		//Data subchunk

		///Data chunk id
		std::array<std::uint8_t, 4> data_chunk_id; //'data' Big endian

		///Size of data segment in B
		std::uint32_t data_chunk_size;

		//Data segment goes after this
	};

	///Represents decoded wav file
	struct WaveFileData
	{
		///Decoded wav file header
		WaveHeader header{};

		///Sound data buffer
		std::vector<uint8_t> data_buffer;
	};

	///Pointer to WaveFileData struct
	using WaveFileDataPtrT = std::shared_ptr<WaveFileData>;

	///Reading function alias, params: data_ptr - out data, bytes_to_read, return operation success
	using WaveReadingFunctionT = std::function<bool(void* data_ptr, const std::uint64_t bytes_to_read)>;

	///Decode wav file using specified reading function
	WaveFileDataPtrT ReadAndDecodeRiffWave(WaveReadingFunctionT&& read_function);

	///Load from file and decode
	WaveFileDataPtrT LoadAndDecodeRiffWaveFromFile(const std::string_view file_path);
}