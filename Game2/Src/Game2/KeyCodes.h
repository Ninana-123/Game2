/******************************************************************************/
/*!
\file		KeyCodes.h
\author 	Liu Xujie
\par    	email: l.xujie@digipen.edu
\date   	29/09/2923
\brief		Defines key codes and a mapping of key codes to key names 
            (characters).

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#pragma once
#include <map>


/* The unknown key */
#define KEY_UNKNOWN            -1

/* Printable keys */
#define KEY_SPACE              32
#define KEY_APOSTROPHE         39  /* ' */
#define KEY_COMMA              44  /* , */
#define KEY_MINUS              45  /* - */
#define KEY_PERIOD             46  /* . */
#define KEY_SLASH              47  /* / */
#define KEY_0                  48
#define KEY_1                  49
#define KEY_2                  50
#define KEY_3                  51
#define KEY_4                  52
#define KEY_5                  53
#define KEY_6                  54
#define KEY_7                  55
#define KEY_8                  56
#define KEY_9                  57
#define KEY_SEMICOLON          59  /* ; */
#define KEY_EQUAL              61  /* = */
#define KEY_A                  65
#define KEY_B                  66
#define KEY_C                  67
#define KEY_D                  68
#define KEY_E                  69
#define KEY_F                  70
#define KEY_G                  71
#define KEY_H                  72
#define KEY_I                  73
#define KEY_J                  74
#define KEY_K                  75
#define KEY_L                  76
#define KEY_M                  77
#define KEY_N                  78
#define KEY_O                  79
#define KEY_P                  80
#define KEY_Q                  81
#define KEY_R                  82
#define KEY_S                  83
#define KEY_T                  84
#define KEY_U                  85
#define KEY_V                  86
#define KEY_W                  87
#define KEY_X                  88
#define KEY_Y                  89
#define KEY_Z                  90
#define KEY_LEFT_BRACKET       91  /* [ */
#define KEY_BACKSLASH          92  /* \ */
#define KEY_RIGHT_BRACKET      93  /* ] */
#define KEY_GRAVE_ACCENT       96  /* ` */
#define KEY_WORLD_1            161 /* non-US #1 */
#define KEY_WORLD_2            162 /* non-US #2 */

/* Function keys */
#define KEY_ESCAPE             256
#define KEY_ENTER              257
#define KEY_TAB                258
#define KEY_BACKSPACE          259
#define KEY_INSERT             260
#define KEY_DELETE             261
#define KEY_RIGHT              262
#define KEY_LEFT               263
#define KEY_DOWN               264
#define KEY_UP                 265
#define KEY_PAGE_UP            266
#define KEY_PAGE_DOWN          267
#define KEY_HOME               268
#define KEY_END                269
#define KEY_CAPS_LOCK          280
#define KEY_SCROLL_LOCK        281
#define KEY_NUM_LOCK           282
#define KEY_PRINT_SCREEN       283
#define KEY_PAUSE              284
#define KEY_F1                 290
#define KEY_F2                 291
#define KEY_F3                 292
#define KEY_F4                 293
#define KEY_F5                 294
#define KEY_F6                 295
#define KEY_F7                 296
#define KEY_F8                 297
#define KEY_F9                 298
#define KEY_F10                299
#define KEY_F11                300
#define KEY_F12                301
#define KEY_F13                302
#define KEY_F14                303
#define KEY_F15                304
#define KEY_F16                305
#define KEY_F17                306
#define KEY_F18                307
#define KEY_F19                308
#define KEY_F20                309
#define KEY_F21                310
#define KEY_F22                311
#define KEY_F23                312
#define KEY_F24                313
#define KEY_F25                314
#define KEY_KP_0               320
#define KEY_KP_1               321
#define KEY_KP_2               322
#define KEY_KP_3               323
#define KEY_KP_4               324
#define KEY_KP_5               325
#define KEY_KP_6               326
#define KEY_KP_7               327
#define KEY_KP_8               328
#define KEY_KP_9               329
#define KEY_KP_DECIMAL         330
#define KEY_KP_DIVIDE          331
#define KEY_KP_MULTIPLY        332
#define KEY_KP_SUBTRACT        333
#define KEY_KP_ADD             334
#define KEY_KP_ENTER           335
#define KEY_KP_EQUAL           336
#define KEY_LEFT_SHIFT         340
#define KEY_LEFT_CONTROL       341
#define KEY_LEFT_ALT           342
#define KEY_LEFT_SUPER         343
#define KEY_RIGHT_SHIFT        344
#define KEY_RIGHT_CONTROL      345
#define KEY_RIGHT_ALT          346
#define KEY_RIGHT_SUPER        347
#define KEY_MENU               348

namespace Engine {
    using KeyCode = unsigned int;
    namespace Key {
        // Define a mapping of key codes to key names (characters)
        const std::map<KeyCode, std::string> keyMap = {
            {32, "Space"},
            {39, "Apostrophe"},
            {44, "Comma"},
            {45, "Minus"},
            {46, "Period"},
            {47, "Slash"},
            {48, "D0"},
            {49, "D1"},
            {50, "D2"},
            {51, "D3"},
            {52, "D4"},
            {53, "D5"},
            {54, "D6"},
            {55, "D7"},
            {56, "D8"},
            {57, "D9"},
            {59, "Semicolon"},
            {61, "Equal"},
            {65, "A"},
            {66, "B"},
            {67, "C"},
            {68, "D"},
            {69, "E"},
            {70, "F"},
            {71, "G"},
            {72, "H"},
            {73, "I"},
            {74, "J"},
            {75, "K"},
            {76, "L"},
            {77, "M"},
            {78, "N"},
            {79, "O"},
            {80, "P"},
            {81, "Q"},
            {82, "R"},
            {83, "S"},
            {84, "T"},
            {85, "U"},
            {86, "V"},
            {87, "W"},
            {88, "X"},
            {89, "Y"},
            {90, "Z"},
            {91, "LeftBracket"},
            {92, "Backslash"},
            {93, "RightBracket"},
            {96, "GraveAccent"},
            {161, "World1"},
            {162, "World2"},
            {256, "Escape"},
            {257, "Enter"},
            {258, "Tab"},
            {259, "Backspace"},
            {260, "Insert"},
            {261, "Delete"},
            {262, "Right"},
            {263, "Left"},
            {264, "Down"},
            {265, "Up"},
            {266, "PageUp"},
            {267, "PageDown"},
            {268, "Home"},
            {269, "End"},
            {280, "CapsLock"},
            {281, "ScrollLock"},
            {282, "NumLock"},
            {283, "PrintScreen"},
            {284, "Pause"},
            {290, "F1"},
            {291, "F2"},
            {292, "F3"},
            {293, "F4"},
            {294, "F5"},
            {295, "F6"},
            {296, "F7"},
            {297, "F8"},
            {298, "F9"},
            {299, "F10"},
            {300, "F11"},
            {301, "F12"},
            {302, "F13"},
            {303, "F14"},
            {304, "F15"},
            {305, "F16"},
            {306, "F17"},
            {307, "F18"},
            {308, "F19"},
            {309, "F20"},
            {310, "F21"},
            {311, "F22"},
            {312, "F23"},
            {313, "F24"},
            {314, "F25"},
            {320, "KP0"},
            {321, "KP1"},
            {322, "KP2"},
            {323, "KP3"},
            {324, "KP4"},
            {325, "KP5"},
            {326, "KP6"},
            {327, "KP7"},
            {328, "KP8"},
            {329, "KP9"},
            {330, "KPDecimal"},
            {331, "KPDivide"},
            {332, "KPMultiply"},
            {333, "KPSubtract"},
            {334, "KPAdd"},
            {335, "KPEnter"},
            {336, "KPEqual"},
            {340, "LeftShift"},
            {341, "LeftControl"},
            {342, "LeftAlt"},
            {343, "LeftWindows"},
            {344, "RightShift"},
            {345, "RightControl"},
            {346, "RightAlt"},
            {347, "RightWindows"},
            {348, "Menu"}
        };
    }
}
