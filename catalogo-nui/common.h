#ifndef COMMON_HPP
#define COMMON_HPP

#define BLOCK_SIDE 200
#define SCROLL_AREA_HEIGHT BLOCK_SIDE + 10

#ifdef NO_PORTABLE

#define APPLICATION_PATH "../CVBot/"
#define CLASSIFIERS_PATH "../classifiers/"
#define SOUNDS_PATH "../sounds/"

#define DATA_PATH "../data/"
#define ICONS_PATH "icons/"
#define XML_PATH "xml/"

#else

#define APPLICATION_PATH "../SeguimientoNariz/"
#define CLASSIFIERS_PATH "classifiers/"
#define SOUNDS_PATH "sounds/"

#define DATA_PATH "data/"
#define ICONS_PATH "icons/"
#define XML_PATH "xml/"

#endif

#endif // COMMON_HPP
