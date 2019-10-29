#pragma once

/* Copyright (C) Filip Wasil, All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Filip Wasil <fillwave@gmail.com>
 */

#include <array>
#include <tuple>
#include <vector>
#include <core/BufferData.hpp>

namespace rwc {
class Platform;

struct VertexBuffer final {
  static constexpr std::size_t MAX_ATTRIBUTES = 5;

  template <long unsigned int TSize, typename... TArg>
  VertexBuffer(const std::array<std::tuple<TArg...> , TSize>& data)
   : mData{}
   , mStride{sizeof(std::tuple<TArg...>)}
   , mTupleSize{sizeof...(TArg)}{
    static_assert(sizeof...(TArg) < MAX_ATTRIBUTES, "Exceeded maximum arguments in buffer");
    if constexpr (sizeof...(TArg) - 1 > 0) {
      getAttributeData<sizeof...(TArg) - 1, std::tuple<TArg...>>(data[0]);
    } else {
      getAttributeData<std::tuple<TArg...>>(data[0]);
    }

    const auto dataSize = sizeof(std::tuple<TArg...>) * TSize;
    mData.resize(dataSize);
    memcpy(mData.data(), data.data(), dataSize);

    mVertexInputBinding.binding = 0; //todo
    mVertexInputBinding.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
    mVertexInputBinding.stride = sizeof(std::tuple<TArg...>);
  }

  template <class TArgumentType>
  unsigned int getAttributeVulkanType() { // implement in Cpp
    return VK_FORMAT_R32G32B32A32_SFLOAT;
  }

  template <int TArgumentIdx, class TTuple>
  size_t getAttributeOffset(TTuple& t) {
    if (TArgumentIdx > 0) {
      return std::get<TArgumentIdx>(t) + getAttributeOffset<TArgumentIdx - 1>(t);
    } else {
      return std::get<TArgumentIdx>(t);
    }
  }

  template <int TArgumentIdx, class TTuple>
  uint32_t getAttributeData(const TTuple& t) {
    mVertexInputAttributeDescription[TArgumentIdx].binding = 0;
    mVertexInputAttributeDescription[TArgumentIdx].location = TArgumentIdx;
    mVertexInputAttributeDescription[TArgumentIdx].format =
      static_cast<VkFormat>(getAttributeVulkanType<decltype(std::get<TArgumentIdx>(t))>());
    if constexpr (TArgumentIdx - 1 > 0) {
      mVertexInputAttributeDescription[TArgumentIdx].offset = getAttributeData<TArgumentIdx - 1, TTuple>(t);
    } else {
      mVertexInputAttributeDescription[TArgumentIdx].offset = getAttributeData<TTuple>(t);
    }
    return sizeof(std::get<TArgumentIdx>(t)) + mVertexInputAttributeDescription[TArgumentIdx].offset;
  }

  template <class TTuple>
  uint32_t getAttributeData(const TTuple& t) {
    mVertexInputAttributeDescription[0].binding = 0;
    mVertexInputAttributeDescription[0].location = 0;
    mVertexInputAttributeDescription[0].format =
      static_cast<VkFormat>(getAttributeVulkanType<decltype(std::get<0>(t))>());
    mVertexInputAttributeDescription[0].offset = 0;
    return sizeof(std::get<0>(t));
  }

  BufferData mBufferData;

  std::vector<float> mData;
  size_t mStride;
  size_t mTupleSize;

  VkVertexInputBindingDescription mVertexInputBinding;
  std::array<VkVertexInputAttributeDescription, MAX_ATTRIBUTES> mVertexInputAttributeDescription;
};

} // namespace rwc
