#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <filesystem>

#include "Flow/Core/Core.hpp"

namespace Flow::Binary
{

	class File
	{
	public:
		File(const std::filesystem::path& file, FileMode mode);
		virtual ~File();

		// Writing
		void Write(const std::string& str);

		template<typename T>
		File& operator << (T data);

		// Reading
		template<typename T>
		T Read(uint32_t offset = 0);
		template<>
		std::string Read<std::string>(uint32_t offset);

	private:
		void StartRead();
		void StartWrite();

		void EndRead();
		void EndWrite();

	private:
		std::filesystem::path m_Path = {};
		FileMode m_Mode = FileMode::None;

		std::vector<char> m_Read = { };
		std::ofstream m_Write = {};
	};

	// Writing
	template<typename T>
	inline File& File::operator << (T data)
	{
		Write(data);
		return *this;
	}

	// Reading
	template<typename T>
	inline T File::Read(uint32_t offset)
	{
		// TODO: Logging
		return T();
	}

	template<>
	inline std::string File::Read<std::string>(uint32_t offset)
	{
		if (offset + sizeof(int32_t) > m_Read.size())
		{
			// TODO: Logging
			return {};
		}

		int32_t size = 0;
		memcpy(&size, &m_Read[offset], sizeof(int32_t));
		offset += sizeof(int32_t);

		if (offset + size > m_Read.size())
		{
			// TODO: Logging
			return {};
		}

		std::string data(m_Read.begin() + offset, m_Read.begin() + offset + size);
		offset += size; // Unnecessary

		return data;
	}

}