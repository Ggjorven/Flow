#include <Flow/Flow.hpp>

#include <iostream>

int main(int argc, char* argv[])
{
	// Yaml
	{
		Flow::Yaml::File file = Flow::Yaml::File("test.yml", Flow::FileMode::Write);

		file << Flow::Yaml::FileManip::BeginMap;
		file << Flow::Yaml::FileManip::Key << "Test";
		file << Flow::Yaml::FileManip::Value << "Test";

		file << Flow::Yaml::FileManip::EndMap;
	}
	{
		Flow::Yaml::File file = Flow::Yaml::File("test.yml", Flow::FileMode::Read);

		std::string val = file["Test"].as<std::string>();
		std::cout << "YAML str: " << val << std::endl;
	}

	// Binary
	{
		Flow::Binary::File file = Flow::Binary::File("test.bin", Flow::FileMode::Write);
		file << std::string("Test");
		file << (uint32_t)69420;
	}
	{
		Flow::Binary::File file = Flow::Binary::File("test.bin", Flow::FileMode::Read);

		std::string val = file.Read<std::string>(0);
		std::cout << "Binary str: " << val << std::endl;

		uint32_t uVal = file.Read<uint32_t>(Flow::Binary::SizeOf(val));
		std::cout << "Binary u32: " << uVal << std::endl;
	}

	return 0;
}