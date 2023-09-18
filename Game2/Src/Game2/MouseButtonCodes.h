#pragma once
#include <map>

namespace Engine
{
	using MouseCode = unsigned int;

	namespace Mouse
	{
		const std::map<MouseCode, std::string> mouseMap = {
			{0, "Left Mouse Button"},
			{1, "Right Mouse Button"},
			{2, "Button2"},
			{3, "Button3"},
			{4, "Button4"},
			{5, "Button5"},
			{6, "Button6"},
			{7, "Button7"}
		};
	}
}