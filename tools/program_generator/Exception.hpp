#pragma once

#include <stdexcept>
#include <string>
 
namespace rwc
{

class Exception : public std::runtime_error
{
public:
	Exception(const std::string& desc) : std::runtime_error(desc)
	{
		// empty
	}
};

class OffscreenContextException : public Exception
{
public:
    using Exception::Exception;
};

class ProgramGeneratorException : public Exception
{
public:
    using Exception::Exception;

};
} /* namespace rwc */

