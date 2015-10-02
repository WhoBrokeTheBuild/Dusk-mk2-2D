#ifndef DUSK_UTILITY_STRINGS_HPP
#define DUSK_UTILITY_STRINGS_HPP

#include <iostream>
#include <string>

using std::string;

namespace dusk
{

string Basename(const string& filename);
string Dirname(const string& filename);

} // namespace dusk

#endif // DUSK_UTILITY_STRINGS_HPP
