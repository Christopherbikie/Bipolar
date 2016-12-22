#pragma once

#include <scene.h>
#include "../graphics/Model.h"

namespace bplr
{
	namespace assets
	{
		extern const std::vector<std::string> assimpFiles;

		graphics::Model* loadModel(std::string path);
	}
}
