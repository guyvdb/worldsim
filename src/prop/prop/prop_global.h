#ifndef PROP_GLOBAL_H
#define PROP_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(PROP_LIBRARY)
#  define PROP_EXPORT Q_DECL_EXPORT
#else
#  define PROP_EXPORT Q_DECL_IMPORT
#endif

#endif // PROP_GLOBAL_H
