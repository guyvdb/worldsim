#ifndef CULTURE_GLOBAL_H
#define CULTURE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(CULTURE_LIBRARY)
#  define EXPORT Q_DECL_EXPORT
#else
#  define EXPORT Q_DECL_IMPORT
#endif

#endif // CULTURE_GLOBAL_H
