/**************************************************************************//**
 * \file Scene.h
 * \author Kwok Jun Lin Wayne, k.junlinwayne, 2200751
 * \par k.junlinwayne@digipen.edu
 * \date 25/01/2024
 * \brief Contains the declarations of Scene.
 *
 * Copyright (C) 2024 DigiPen Institute of Technology.
 * Reproduction or disclosure of this file or its contents
 * without the prior written consent of DigiPen Institute of
 * Technology is prohibited.
 *****************************************************************************/

#ifndef ENGINE_SCENE_H
#define ENGINE_SCENE_H

namespace Engine {
    /**
     * \class Scene
     * \brief Represents a scene in the game.
     *
     * This class serves as a base class for different scenes in the game.
     * Derived classes should implement specific scene functionalities by
     * overriding virtual functions.
     */
    class Scene {
    public:
        /**
         * \brief Virtual destructor for the Scene class.
         */
        virtual ~Scene() {} // Virtual destructor

        /**
         * \brief Pure virtual function to be overridden by derived classes.
         * \details This function is called when the scene is loaded.
         */
        virtual void OnLoad() = 0;

        /**
         * \brief Pure virtual function to be overridden by derived classes.
         * \details This function is called when the scene is initialized.
         */
        virtual void OnInit() = 0;

        /**
         * \brief Pure virtual function to be overridden by derived classes.
         * \details This function is called when the scene is updated.
         * \param deltaTime The time since the last update.
         */
        virtual void OnUpdate(double deltaTime) = 0;

        /**
         * \brief Pure virtual function to be overridden by derived classes.
         * \details This function is called when resources used by the scene
         * need to be freed.
         */
        virtual void FreeLevel() = 0;

        /**
         * \brief Pure virtual function to be overridden by derived classes.
         * \details This function is called when the scene is shut down.
         */
        virtual void OnShutDown() = 0;
    };
}
#endif // ENGINE_SCENE_H