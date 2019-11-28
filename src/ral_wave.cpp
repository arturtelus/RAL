#include "ral_wave.h"

#include<array>
#include<fstream>

#ifdef DEBUG
#include<iostream>
#endif // DEBUG

namespace ral
{
	WaveFileDataPtrT ReadAndDecodeRiffWave(WaveReadingFunctionT&& read_function)
	{
		constexpr std::uint64_t four_B{ 4 };
		constexpr std::uint64_t two_B{ 2 };
		constexpr std::array<std::uint8_t, four_B> valid_riff_chunk_id{ 'R', 'I', 'F','F' };
		constexpr std::array<std::uint8_t, four_B> valid_fmt_chunk_id{ 'f', 'm', 't',' ' };
		constexpr std::array<std::uint8_t, four_B> valid_data_chunk_id{ 'd', 'a', 't','a' };

		WaveFileDataPtrT wave_file_data_ptr{ std::make_shared<WaveFileData>() };

		auto& wave_file_header{ wave_file_data_ptr->header };
		auto& wave_file_buffer{ wave_file_data_ptr->data_buffer };
		bool load_failed{ false };

		//RIFF header chunk
		if (read_function(wave_file_header.riff_chunk_id.data(), four_B) &&
			read_function(&wave_file_header.riff_chunk_size, four_B) &&
			read_function(&wave_file_header.riff_chunk_format, four_B) &&
			//Header FMT chunk
			read_function(&wave_file_header.fmt_chunk_id, four_B) &&
			read_function(&wave_file_header.fmt_chunk_size, four_B) &&
			read_function(&wave_file_header.audio_format, two_B) &&
			read_function(&wave_file_header.number_of_channels, two_B) &&
			read_function(&wave_file_header.sample_rate, four_B) &&
			read_function(&wave_file_header.byte_rate, four_B) &&
			read_function(&wave_file_header.block_align, two_B) &&
			read_function(&wave_file_header.bits_per_sample, two_B) &&
			//Header Data chunk
			read_function(&wave_file_header.data_chunk_id, four_B) &&
			read_function(&wave_file_header.data_chunk_size, four_B))
		{
			//Verify file header
			if ((wave_file_header.riff_chunk_id == valid_riff_chunk_id) &&
				(wave_file_header.fmt_chunk_id == valid_fmt_chunk_id) &&
				(wave_file_header.data_chunk_id == valid_data_chunk_id) &&

				(wave_file_header.data_chunk_size > std::uint32_t{ 0 }) &&
				(wave_file_header.sample_rate > std::uint32_t{ 0 }) &&
				(wave_file_header.bits_per_sample > std::uint16_t{ 0 }) &&
				(wave_file_header.number_of_channels > std::uint16_t{ 0 }))
			{
				//OK read data buffer
				wave_file_buffer.resize(wave_file_header.data_chunk_size);
				if (!read_function(wave_file_buffer.data(), wave_file_header.data_chunk_size))
				{
#ifdef DEBUG
					std::cerr << "ral::DecodeWavFromBuffer(), Failed to read wav data segment!\n";
#endif // DEBUG
					load_failed = true;
				}
			}
			else
			{
#ifdef DEBUG
				std::cerr << "ral::DecodeWavFromBuffer(), wav header is malformated!\n";
#endif // DEBUG
				load_failed = true;
			}
		}
		else
		{
#ifdef DEBUG
			std::cerr << "DecodeWavFromBuffer(), Unable to read wav header!\n";
#endif // DEBUG
			load_failed = true;
		}

		//Dealloc pointer if file loading failed
		if (load_failed)
		{
			wave_file_data_ptr.reset();
		}

		return wave_file_data_ptr;
	}

	WaveFileDataPtrT ral::LoadAndDecodeRiffWaveFromFile(const std::string_view file_path)
	{
		if (std::ifstream wav_file{ file_path.data(), std::ios::binary }; wav_file)
		{
			return ReadAndDecodeRiffWave([&wav_file](void* out_data_ptr, const std::uint64_t bytes_to_read) {
				wav_file.read(reinterpret_cast<char*>(out_data_ptr), bytes_to_read);
				return wav_file.good();
				});
		}
#ifdef DEBUG
		std::cerr << "LoadAndDecodeRiffWaveFromFile(), Unable to open " << file_path.data() << " file!\n";
#endif // DEBUG
		return {};
	}
}