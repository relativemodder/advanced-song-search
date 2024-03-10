#include <utils.hpp>


bool Utils::string_contains_substring(std::string haystack, std::string needle) {
	return haystack.find(needle) != std::string::npos;
}


std::string Utils::str_to_lowercase(std::string sourceString) {
	std::string destinationString;

	destinationString.resize(sourceString.size());

	std::transform(sourceString.begin(),
					sourceString.end(),
					destinationString.begin(),
					::tolower);
	return destinationString;
}


bool Utils::compare_to_filter(std::string original, std::string filter) {
	return Utils::string_contains_substring(
		str_to_lowercase(original), 
		str_to_lowercase(filter)
	);
}