#include "stdafx.h"

//Get the sign of the number
int Utils::sign(double value)
{
	if (value < 0)
		return -1;

	if (value > 0)
		return 1;

	return 0;
}

std::vector<std::string> Utils::split(const std::string& s, char delim)
{
    std::vector<std::string> result;
    std::stringstream ss(s);
    std::string item;

    while (getline(ss, item, delim))
        result.push_back(item);

    return result;
}

std::string Utils::getNthLineContent(const std::string& file_path, const int &line)
{
	std::ifstream in;
	in.open(file_path);

	std::string content;

	for (int i = 0; i < line; ++i)
		std::getline(in, content);

	return content.substr(content.find(':') + 1, -1);
}
