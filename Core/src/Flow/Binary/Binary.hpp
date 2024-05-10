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
		template<typename T>
		void Write(T data);
		template<>
		void Write<std::string>(std::string str);

		template<typename T>
		File& operator << (T data);

		// Reading
		template<typename T>
		T Read(size_t offset = 0);
		template<>
		std::string Read<std::string>(size_t offset);

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
	inline void File::Write(T data)
	{
		m_Write.write(reinterpret_cast<const char*>(&data), sizeof(T));
	}

	template<>
	inline void File::Write(std::string str)
	{
		int32_t size = (int32_t)str.size();
		m_Write.write(reinterpret_cast<const char*>(&size), sizeof(int32_t));

		m_Write.write(str.c_str(), size);
	}

	template<typename T>
	inline File& File::operator << (T data)
	{
		Write<T>(data);
		return *this;
	}

	// Reading
	template<typename T>
	inline T File::Read(size_t offset)
	{
		// TODO: Logging
		T def = {};
		memcpy(&def, &m_Read[offset], sizeof(T));
		offset += sizeof(T);

		return def;
	}

	template<>
	inline std::string File::Read<std::string>(size_t offset)
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