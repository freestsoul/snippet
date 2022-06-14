/**************************************************************************

Copyright: freestsoul

Author: freesoul

Date: 2022-06-14

Description: Provide RSA Encode and Decode function.

**************************************************************************/

#ifndef COM_FREESOUL_SNIPPET_RSA_ENDECODE_H
#define COM_FREESOUL_SNIPPET_RSA_ENDECODE_H

#include <string>

namespace com {
namespace freesoul {
namespace snippet {

std::string base64_encode(unsigned char const* bytes_to_encode,
                          unsigned int in_len);
std::string base64_decode(std::string const& encoded_string);

}  // namespace snippet
}  // namespace freesoul
}  // namespace com

#endif