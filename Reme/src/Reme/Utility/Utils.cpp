#include "reme_pch.h"
#include "Reme/Utility/Utils.h"

#include <fstream>

namespace Reme
{
	std::string ReadFile(const std::string& filepath)
	{
		PROFILE_FUNCTION();
		
		std::string result;
		std::ifstream in(filepath, std::ios::in | std::ios::binary);
		if (in)
		{
			in.seekg(0, std::ios::end);
			size_t size = in.tellg();
			if (size != -1)
			{
				result.resize(size);
				in.seekg(0, std::ios::beg);
				in.read(&result[0], size);
				in.close();
			}
			else
			{
				LOG_ERROR("Could not read from file '{0}'", filepath);
			}
		}
		else
		{
			LOG_ERROR("Could not open file '{0}'", filepath);
		}

		return result;
	}
}
