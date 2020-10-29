#ifndef GEOGRAPHY_GLOBAL_H
#define GEOGRAPHY_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(GEOGRAPHY_LIBRARY)
#  define GEOGRAPHY_EXPORT Q_DECL_EXPORT
#else
#  define GEOGRAPHY_EXPORT Q_DECL_IMPORT
#endif

#endif // GEOGRAPHY_GLOBAL_H
