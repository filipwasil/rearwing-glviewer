#pragma once

#include <string>
#include <iostream>
#include <filesystem>

static const char* GENERATED_ASSETS_PATH = "../../../app/assets/generated";

static std::string createGeneratedDirectory(const char* path)
{
    const std::string assetsPath = std::string(GENERATED_ASSETS_PATH) + "/" + path + "/";
    try
    {
        if (!std::filesystem::exists(GENERATED_ASSETS_PATH))
        {
            std::filesystem::create_directory(GENERATED_ASSETS_PATH);
        }

        if (!std::filesystem::exists(assetsPath))
        {
            std::filesystem::create_directory(assetsPath);
        }
    }
    catch (const std::filesystem::filesystem_error& fs_error)
    {
        std::cout << fs_error.what() << std::endl;
        return "";
    }
    return assetsPath + "/";
}
