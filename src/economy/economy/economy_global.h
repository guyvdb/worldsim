#ifndef ECONOMY_GLOBAL_H
#define ECONOMY_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(ECONOMY_LIBRARY)
#  define ECONOMY_EXPORT Q_DECL_EXPORT
#else
#  define ECONOMY_EXPORT Q_DECL_IMPORT
#endif

#endif // ECONOMY_GLOBAL_H
