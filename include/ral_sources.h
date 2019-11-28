#pragma once

#include "ral_al_names.h"
#include<vector>

namespace ral
{
	template<SizeT number_of_names>
	class Sources : public ALNames<number_of_names>
	{
		///Create openal sources with error checking.
		static Sources::NamesArrayT CreateSources() noexcept;

		///Delete array of openal sources with error checking.
		static void DeleteSources(const Sources::NamesArrayT& names) noexcept;

	public:

		///3xALfloat type alias
		using ALfloat3T = std::tuple<ALfloat, ALfloat, ALfloat>;

		///Creates new openal sources.
		Sources() noexcept;

		///Deletes stored openal sources.
		~Sources() override;

		///Transfer openal names into this object.
		Sources(Sources&& other) noexcept;

		///Delete stored buffers and transfer into this object.
		Sources& operator=(Sources&& other) noexcept;


		//Properties

		///Gets 1xALfloat property of specified source object. Properties: 
		ALfloat GetPropertyFloat(const SizeT name_index, ALenum prop_name) noexcept;

		///Sets 1xALfloat property of specified source object. Properties: 
		void SetProperty(const SizeT name_index, ALenum prop_name, ALfloat f_val) noexcept;

		///Gets 1xALint property of specified source object. Properties: 
		ALint GetPropertyInt(const SizeT name_index, ALenum nprop_nameame) noexcept;

		///Sets 1xALint property of specified source object. Properties: 
		void SetProperty(const SizeT name_index, ALenum prop_name, ALint i_val) noexcept;

		///Gets 3x ALfloat property of the listener. Properties: 
		ALfloat3T GetProperty3Float(const SizeT name_index, const ALenum prop_name) noexcept;

		///Sets 3x ALfloat property of the listener. Properties:
		void SetProperty(const SizeT name_index, const ALenum prop_name, const ALfloat val_1, const ALfloat val_2, const ALfloat val_3) noexcept;

		///Gets ALfloat vector property of the listener. Properties:
		std::vector<ALfloat> GetPropertyFloatVector(const SizeT name_index, const ALenum prop_name);

		///Sets ALfloat vector property of the listener. Properties: 
		void SetProperty(const SizeT name_index, const ALenum prop_name, const std::vector<ALfloat>& values);

		///Sets ALfloat vector property of the listener. Properties: 
		void SetProperty(const SizeT name_index, const ALenum prop_name, const ALfloat* data_ptr) noexcept;


		//Source playback

		///Starts source playback
		void Play(const SizeT name_index = SizeT{}) noexcept;

		///Stops source playback
		void Stop(const SizeT name_index = SizeT{}) noexcept;

		///Rewinds source
		void Rewind(const SizeT name_index = SizeT{}) noexcept;

		///Pauses source playback
		void Pause(const SizeT name_index = SizeT{}) noexcept;

		///Plays all stored sources
		void PlayAll() noexcept;

		///Stops all stored sources
		void StopAll() noexcept;

		///Rewinds all stored sources
		void RewindAll() noexcept;

		///Pauses all stored sources
		void PauseAll() noexcept;


		//Source queuing

		///Queues stored source
		void QueueBuffers(const SizeT name_index, ALsizei numEntries, const ALuint* bids) noexcept;

		///Queues stored source
		void UnqueueBuffers(const SizeT name_index, ALsizei numEntries, const ALuint* bids) noexcept;
	};

	template<SizeT number_of_names>
	inline typename Sources<number_of_names>::NamesArrayT Sources<number_of_names>::CreateSources() noexcept
	{
		Sources::NamesArrayT new_sources{};
		alGenSources(static_cast<ALsizei>(number_of_names), new_sources.data());
		AL_CHECK_CALL();
		return new_sources;
	}

	template<SizeT number_of_names>
	inline void Sources<number_of_names>::DeleteSources(const Sources::NamesArrayT& names) noexcept
	{
		alDeleteSources(static_cast<ALsizei>(number_of_names), names.data());
		AL_CHECK_CALL();
	}

	template<SizeT number_of_names>
	inline Sources<number_of_names>::Sources() noexcept
		: ALNames<number_of_names>{ CreateSources() }
	{
	}

	template<SizeT number_of_names>
	inline Sources<number_of_names>::~Sources()
	{
		DeleteSources(Sources::Names());
		ResetNames();
	}

	template<SizeT number_of_names>
	inline Sources<number_of_names>::Sources(Sources&& other) noexcept
		: ALNames<number_of_names>(other)
	{
	}

	template<SizeT number_of_names>
	inline Sources<number_of_names>& Sources<number_of_names>::operator=(Sources&& other) noexcept
	{
		if (&other != this)
		{
			DeleteSources(Sources::Names());
			ALNames<number_of_names>::operator=(other);
		}
		return *this;
	}

	template<SizeT number_of_names>
	inline ALfloat ral::Sources<number_of_names>::GetPropertyFloat(const SizeT name_index, ALenum prop_name) noexcept
	{
		ALfloat f_value{};
		alGetSourcef(Sources::Name(name_index), prop_name, &f_value);
		AL_CHECK_CALL();
		return f_value;
	}

	template<SizeT number_of_names>
	inline void ral::Sources<number_of_names>::SetProperty(const SizeT name_index, ALenum prop_name, ALfloat f_val) noexcept
	{
		alSourcef(Sources::Name(name_index), prop_name, f_val);
		AL_CHECK_CALL();
	}

	template<SizeT number_of_names>
	inline ALint ral::Sources<number_of_names>::GetPropertyInt(const SizeT name_index, ALenum prop_name) noexcept
	{
		ALfloat i_value{};
		alGetSourcei(Sources::Name(name_index), prop_name, &i_value);
		AL_CHECK_CALL();
		return i_value;
	}

	template<SizeT number_of_names>
	inline void ral::Sources<number_of_names>::SetProperty(const SizeT name_index, ALenum prop_name, ALint i_val) noexcept
	{
		alSourcei(Sources::Name(name_index), prop_name, i_val);
		AL_CHECK_CALL();
	}

	template<SizeT number_of_names>
	inline typename ral::Sources<number_of_names>::ALfloat3T ral::Sources<number_of_names>::GetProperty3Float(const SizeT name_index, const ALenum prop_name) noexcept
	{
		ALfloat v_1{}, v_2{}, v_3{};
		alSource3f(Sources::Name(name_index), prop_enum, &v_1, &v_2, &v_3);
		return std::make_tuple(v_1, v_2, v_3);
	}

	template<SizeT number_of_names>
	inline void ral::Sources<number_of_names>::SetProperty(const SizeT name_index, const ALenum prop_name, const ALfloat val_1, const ALfloat val_2, const ALfloat val_3) noexcept
	{
		alSource3f(Sources::Name(name_index), prop_name, i_val);
		AL_CHECK_CALL();
	}

	template<SizeT number_of_names>
	inline std::vector<ALfloat> Sources<number_of_names>::GetPropertyFloatVector(const SizeT name_index, const ALenum prop_name)
	{
		std::vector<ALfloat> vec_values(3, ALfloat{});
		alGetSourcefv(Sources::Name(name_index), prop_name, vec_values.data());
		AL_CHECK_CALL();
		return vec_values;
	}

	template<SizeT number_of_names>
	inline void Sources<number_of_names>::SetProperty(const SizeT name_index, const ALenum prop_name, const std::vector<ALfloat>& values)
	{
		alSourcefv(Sources::Name(name_index), prop_name, values.data());
		AL_CHECK_CALL();
	}

	template<SizeT number_of_names>
	inline void Sources<number_of_names>::SetProperty(const SizeT name_index, const ALenum prop_name, const ALfloat* data_ptr) noexcept
	{
		alSourcefv(Sources::Name(name_index), prop_name, data_ptr);
		AL_CHECK_CALL();
	}
	template<SizeT number_of_names>
	inline void Sources<number_of_names>::Play(const SizeT name_index) noexcept
	{
		alSourcePlay(Sources::Name(name_index));
		AL_CHECK_CALL();
	}

	template<SizeT number_of_names>
	inline void Sources<number_of_names>::Stop(const SizeT name_index) noexcept
	{
		alSourceStop(Sources::Name(name_index));
		AL_CHECK_CALL();
	}

	template<SizeT number_of_names>
	inline void Sources<number_of_names>::Rewind(const SizeT name_index) noexcept
	{
		alSourceRewind(Sources::Name(name_index));
		AL_CHECK_CALL();
	}

	template<SizeT number_of_names>
	inline void Sources<number_of_names>::Pause(const SizeT name_index) noexcept
	{
		alSourcePause(Sources::Name(name_index));
		AL_CHECK_CALL();
	}

	template<SizeT number_of_names>
	inline void Sources<number_of_names>::PlayAll() noexcept
	{
		alSourcePlayv(static_cast<ALsizei>(number_of_names), Sources::Names().data());
		AL_CHECK_CALL();
	}

	template<SizeT number_of_names>
	inline void Sources<number_of_names>::StopAll() noexcept
	{
		alSourceStopv(static_cast<ALsizei>(number_of_names), Sources::Names().data());
		AL_CHECK_CALL();
	}

	template<SizeT number_of_names>
	inline void Sources<number_of_names>::RewindAll() noexcept
	{
		alSourceRewindv(static_cast<ALsizei>(number_of_names), Sources::Names().data());
		AL_CHECK_CALL();
	}

	template<SizeT number_of_names>
	inline void Sources<number_of_names>::PauseAll() noexcept
	{
		alSourcePausev(static_cast<ALsizei>(number_of_names), Sources::Names().data());
		AL_CHECK_CALL();
	}

	template<SizeT number_of_names>
	inline void Sources<number_of_names>::QueueBuffers(const SizeT name_index, ALsizei numEntries, const ALuint* bids) noexcept
	{
		alSourceQueueBuffers(Sources::Name(name_index), numEntries, bids);
		AL_CHECK_CALL();
	}

	template<SizeT number_of_names>
	inline void Sources<number_of_names>::UnqueueBuffers(const SizeT name_index, ALsizei numEntries, const ALuint* bids) noexcept
	{
		alSourceUnqueueBuffers(Sources::Name(name_index), numEntries, bids);
		AL_CHECK_CALL();
	}
}

