#pragma once

// Temp Keycodes, look familiar? :)

/* The mod keys */
#define LNA_MOD_SHIFT           0x0001
#define LNA_MOD_CONTROL         0x0002
#define LNA_MOD_ALT             0x0004
#define LNA_MOD_SUPER           0x0008
#define LNA_MOD_CAPS_LOCK       0x0010
#define LNA_MOD_NUM_LOCK        0x0020

/* The unknown key */
#define LNA_KEY_UNKNOWN            -1

/* Printable keys */
#define LNA_KEY_SPACE              32
#define LNA_KEY_APOSTROPHE         39  /* ' */
#define LNA_KEY_COMMA              44  /* , */
#define LNA_KEY_MINUS              45  /* - */
#define LNA_KEY_PERIOD             46  /* . */
#define LNA_KEY_SLASH              47  /* / */

#define LNA_KEY_0                  48
#define LNA_KEY_1                  49
#define LNA_KEY_2                  50
#define LNA_KEY_3                  51
#define LNA_KEY_4                  52
#define LNA_KEY_5                  53
#define LNA_KEY_6                  54
#define LNA_KEY_7                  55
#define LNA_KEY_8                  56
#define LNA_KEY_9                  57

#define LNA_KEY_SEMICOLON          59  /* ; */
#define LNA_KEY_EQUAL              61  /* = */

#define LNA_KEY_A                  65
#define LNA_KEY_B                  66
#define LNA_KEY_C                  67
#define LNA_KEY_D                  68
#define LNA_KEY_E                  69
#define LNA_KEY_F                  70
#define LNA_KEY_G                  71
#define LNA_KEY_H                  72
#define LNA_KEY_I                  73
#define LNA_KEY_J                  74
#define LNA_KEY_K                  75
#define LNA_KEY_L                  76
#define LNA_KEY_M                  77
#define LNA_KEY_N                  78
#define LNA_KEY_O                  79
#define LNA_KEY_P                  80
#define LNA_KEY_Q                  81
#define LNA_KEY_R                  82
#define LNA_KEY_S                  83
#define LNA_KEY_T                  84
#define LNA_KEY_U                  85
#define LNA_KEY_V                  86
#define LNA_KEY_W                  87
#define LNA_KEY_X                  88
#define LNA_KEY_Y                  89
#define LNA_KEY_Z                  90

#define LNA_KEY_LEFT_BRACKET       91  /* [ */
#define LNA_KEY_BACKSLASH          92  /* \ */
#define LNA_KEY_RIGHT_BRACKET      93  /* ] */
#define LNA_KEY_GRAVE_ACCENT       96  /* ` */

#define LNA_KEY_WORLD_1            161 /* non-US #1 */
#define LNA_KEY_WORLD_2            162 /* non-US #2 */

/* Function keys */
#define LNA_KEY_ESCAPE             256
#define LNA_KEY_ENTER              257
#define LNA_KEY_TAB                258
#define LNA_KEY_BACKSPACE          259
#define LNA_KEY_INSERT             260
#define LNA_KEY_DELETE             261

#define LNA_KEY_RIGHT              262
#define LNA_KEY_LEFT               263
#define LNA_KEY_DOWN               264
#define LNA_KEY_UP                 265

#define LNA_KEY_PAGE_UP            266
#define LNA_KEY_PAGE_DOWN          267
#define LNA_KEY_HOME               268
#define LNA_KEY_END                269

#define LNA_KEY_CAPS_LOCK          280
#define LNA_KEY_SCROLL_LOCK        281
#define LNA_KEY_NUM_LOCK           282
#define LNA_KEY_PRINT_SCREEN       283
#define LNA_KEY_PAUSE              284

#define LNA_KEY_F1                 290
#define LNA_KEY_F2                 291
#define LNA_KEY_F3                 292
#define LNA_KEY_F4                 293
#define LNA_KEY_F5                 294
#define LNA_KEY_F6                 295
#define LNA_KEY_F7                 296
#define LNA_KEY_F8                 297
#define LNA_KEY_F9                 298
#define LNA_KEY_F10                299
#define LNA_KEY_F11                300
#define LNA_KEY_F12                301
#define LNA_KEY_F13                302
#define LNA_KEY_F14                303
#define LNA_KEY_F15                304
#define LNA_KEY_F16                305
#define LNA_KEY_F17                306
#define LNA_KEY_F18                307
#define LNA_KEY_F19                308
#define LNA_KEY_F20                309
#define LNA_KEY_F21                310
#define LNA_KEY_F22                311
#define LNA_KEY_F23                312
#define LNA_KEY_F24                313
#define LNA_KEY_F25                314

#define LNA_KEY_KP_0               320
#define LNA_KEY_KP_1               321
#define LNA_KEY_KP_2               322
#define LNA_KEY_KP_3               323
#define LNA_KEY_KP_4               324
#define LNA_KEY_KP_5               325
#define LNA_KEY_KP_6               326
#define LNA_KEY_KP_7               327
#define LNA_KEY_KP_8               328
#define LNA_KEY_KP_9               329

#define LNA_KEY_KP_DECIMAL         330
#define LNA_KEY_KP_DIVIDE          331
#define LNA_KEY_KP_MULTIPLY        332
#define LNA_KEY_KP_SUBTRACT        333
#define LNA_KEY_KP_ADD             334
#define LNA_KEY_KP_ENTER           335
#define LNA_KEY_KP_EQUAL           336

#define LNA_KEY_LEFT_SHIFT         340
#define LNA_KEY_LEFT_CONTROL       341
#define LNA_KEY_LEFT_ALT           342
#define LNA_KEY_LEFT_SUPER         343

#define LNA_KEY_RIGHT_SHIFT        344
#define LNA_KEY_RIGHT_CONTROL      345
#define LNA_KEY_RIGHT_ALT          346
#define LNA_KEY_RIGHT_SUPER        347

#define LNA_KEY_MENU               348
#define LNA_KEY_LAST               LNA_KEY_MENU