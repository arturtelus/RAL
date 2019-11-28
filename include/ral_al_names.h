#pragma once

#include<al.h>
#include<array>
#include<cstdint>
#include<type_traits>

#include "ral_error.h"

namespace ral
{
	///Size type alias for ALNames class
	using SizeT = std::uint32_t;

	///Stores specific number of openal names.
	template<SizeT number_of_names>
	class ALNames
	{
	public:

		static_assert((number_of_names > SizeT{ 0 }), "Number of AL names must not be 0.");

		///Stored array alias.
		using NamesArrayT = std::array<ALuint, number_of_names>;

		///Construct empty ALNames.
		ALNames() noexcept;

		///Constructs object and copies provided array.
		ALNames(NamesArrayT al_names) noexcept;

		///Destructor, pure virtual.
		virtual ~ALNames() = 0;

		///Transfer stored al names.
		ALNames(ALNames&& other) noexcept;

		///Transfer stored al names. 
		ALNames& operator=(ALNames&& other) noexcept;

		///Copy construction is deleted.
		ALNames(const ALNames& other) = delete;

		///Copy assign is deleted.
		ALNames& operator=(ALNames& other) = delete;

		///Get stored array
		const NamesArrayT& Names() const { return al_names_; };

		///Get al object name using index
		ALuint Name(const SizeT name_index = SizeT{ 0 }) const { return al_names_.at(index); };

	private:

		///Array of openal names.
		NamesArrayT al_names_;

	protected:

		///Resets values of stored al names
		void ResetNames() noexcept { al_names_.fill(ALuint{}); };
	};

	template<SizeT number_of_names>
	inline ALNames<number_of_names>::ALNames() noexcept
		: al_names_{}
	{
	}

	template<SizeT number_of_names>
	inline ALNames<number_of_names>::ALNames(NamesArrayT al_names) noexcept
		: al_names_{ al_names }
	{
		al_names.fill(ALuint{});
	}

	template<SizeT number_of_names>
	inline ALNames<number_of_names>::~ALNames() noexcept
	{
	}

	template<SizeT number_of_names>
	inline ALNames<number_of_names>::ALNames(ALNames&& other) noexcept
		: al_names_{}
	{
		al_names_.swap(other.al_names_);
		other.ResetNames();
	}

	template<SizeT number_of_names>
	inline ALNames<number_of_names>& ALNames<number_of_names>::operator=(ALNames&& other) noexcept
	{
		if (&other != this)
		{
			al_names_.swap(other.al_names_);
			other.ResetNames();
		}
		return *this;
	}
}