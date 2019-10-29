#include "ETCTextureLoader.hpp"
#include "Etc.h"
#include <Exception.hpp>

namespace rwc
{

unsigned int ETCTextureLoader::load(const char* /*path*/)
{
   throw LoaderException("ETC compression not suppoerted", LOCATION);
}

} // namespace rwc
