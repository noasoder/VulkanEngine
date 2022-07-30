#ifndef H_ENUM_NAMES
#define H_ENUM_NAMES

#include <stdio.h>
#include <vector>
#include "vulkan/vulkan.h"

#define STRF(x) #x

const std::vector<VkPolygonMode> VkPolygonMode_All = { VK_POLYGON_MODE_FILL, VK_POLYGON_MODE_LINE, VK_POLYGON_MODE_POINT };
const char* VkPolygonMode_Str[] =
{
	STRF(VK_POLYGON_MODE_FILL),
	STRF(VK_POLYGON_MODE_LINE),
	STRF(VK_POLYGON_MODE_POINT),
};


const std::vector<VkCullModeFlagBits> VkCullModeFlagBits_All = { VK_CULL_MODE_NONE, VK_CULL_MODE_FRONT_BIT, VK_CULL_MODE_BACK_BIT, VK_CULL_MODE_FRONT_AND_BACK };
const char* VkCullModeFlagBits_Str[] =
{
	STRF(VK_CULL_MODE_NONE),
	STRF(VK_CULL_MODE_FRONT_BIT),
	STRF(VK_CULL_MODE_BACK_BIT),
	STRF(VK_CULL_MODE_FRONT_AND_BACK),
};


#endif // !H_ENUM_NAMES