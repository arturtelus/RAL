#pragma once

#include "ral_al_names.h"
#include "ral_wave.h"

namespace ral
{
	template<SizeT number_of_names>
	class Buffers : public ALNames<number_of_names>
	{
		///Create openal buffers with error chcecking.
		static Buffers::NamesArrayT CreateBuffers() noexcept;

		///Delete array of openal buffers with error checking
		static void DeleteBuffers(const Buffers::NamesArrayT& names) noexcept;

	public:

		///Creates empty openal buffers
		Buffers() noexcept;

		///Deletes stored openal buffers
		~Buffers() override;

		///Transfer openal names into this object.
		Buffers(Buffers&& other) noexcept;

		///Delete stored buffers and transfer into this object.
		Buffers& operator=(Buffers&& other) noexcept;

		///Copies data into buffer and sets its properties.
		void CopyData(const SizeT name_index, ALenum format, const ALvoid* data, ALsizei size, ALsizei freq) const noexcept;

		///Copies decoded wav data into buffer and sets its properties.
		void CopyData(const SizeT name_index, const WaveFileDataPtrT wav_data_ptr) const noexcept;

		///Get buffer property. This function calls alGetBufferi. Buffer properties: AL_FREQUENCY, AL_SIZE, AL_BITS, AL_CHANNELS.
		ALint GetProperty(const SizeT name_index, ALenum prop);
	};

	template<SizeT number_of_names>
	inline typename Buffers<number_of_names>::NamesArrayT Buffers<number_of_names>::CreateBuffers() noexcept
	{
		Buffers::NamesArrayT new_buffers{};
		alGenBuffers(static_cast<ALsizei>(number_of_names), new_buffers.data());
		AL_CHECK_CALL();
		return new_buffers;
	}

	template<SizeT number_of_names>
	inline void Buffers<number_of_names>::DeleteBuffers(const Buffers::NamesArrayT& names) noexcept
	{
		alDeleteBuffers(static_cast<ALsizei>(number_of_names), names.data());
		AL_CHECK_CALL();
	}

	template<SizeT number_of_names>
	inline Buffers<number_of_names>::Buffers() noexcept
		: ALNames<number_of_names>{ CreateBuffers() }
	{
	}

	template<SizeT number_of_names>
	inline Buffers<number_of_names>::~Buffers()
	{
		DeleteBuffers(Buffers::Names());
		ResetNames();
	}

	template<SizeT number_of_names>
	inline Buffers<number_of_names>::Buffers(Buffers&& other) noexcept
		: ALNames<number_of_names>(std::move(other))
	{
	}

	template<SizeT number_of_names>
	inline Buffers<number_of_names>& Buffers<number_of_names>::operator=(Buffers&& other) noexcept
	{
		if (&other != this)
		{
			DeleteBuffers(Buffers::Names());
			ALNames<number_of_names>::operator=(std::move(other));
		}
		return *this;
	}

	template<SizeT number_of_names>
	inline void ral::Buffers<number_of_names>::CopyData(const SizeT name_index, ALenum format, const ALvoid* data, ALsizei size, ALsizei freq) const noexcept
	{
		alBufferData(Names(name_index), format, data, size, freq);
		ALCheckError();
	}

	template<SizeT number_of_names>
	inline void ral::Buffers<number_of_names>::CopyData(const SizeT name_index, const WaveFileDataPtrT wav_data_ptr) const noexcept
	{
		const auto& wav_header{ decoded_riff_wave_ptr->header };
		const auto& wav_data_buffer{ decoded_riff_wave_ptr->data_buffer };

		ALenum format_to_load{ (wav_header.number_of_channels > 1) ?
			((wav_header.bits_per_sample > std::uint16_t{8}) ? AL_FORMAT_STEREO16 : AL_FORMAT_STEREO8) :
			((wav_header.bits_per_sample > std::uint16_t{8}) ? AL_FORMAT_MONO16 : AL_FORMAT_MONO8)
		};

		alBufferData(Names(name_index), format_to_load, wav_data_buffer.data(), wav_header.data_chunk_size, wav_header.sample_rate);
		ALCheckError();
	}

	template<SizeT number_of_names>
	inline ALint ral::Buffers<number_of_names>::GetProperty(const SizeT name_index, ALenum prop)
	{
		ALint prop_val{};
		alGetBufferi(Names(name_index), prop, &prop_val);
		ALCheckError();
		return ALint();
	}
}