/******************************************************************************/
/*!
\file		Scene.h
\author		Kwok Jun Lin Wayne, k.junlinwayne, 2200751
\par		k.junlinwayne@digipen.edu
\date		25/01/2024
\brief		Contains the declarations of Scene.

Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
 */
 /******************************************************************************/

#ifndef ENGINE_SCENE_H
#define ENGINE_SCENE_H

namespace Engine {
	class Scene {
	public: 
		/*!
		\brief Virtual destructor for the Scene class.
		*/
		virtual ~Scene() {} //virtual destructor

		/*!
		\brief Pure virtual function to be overridden by derived classes.
		\details This function is called when the scene is loaded.
		*/
		virtual void OnLoad() = 0;

		/*!
		\brief Pure virtual function to be overridden by derived classes.
		\details This function is called when the scene is shut down.
		*/
		virtual void OnShutDown() = 0;
	};
}
#endif	ENGINE_SCENE_H