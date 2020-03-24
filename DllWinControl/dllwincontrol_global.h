#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(DLLWINCONTROL_LIB)
#  define DLLWINCONTROL_EXPORT Q_DECL_EXPORT
# else
#  define DLLWINCONTROL_EXPORT Q_DECL_IMPORT
# endif
#else
# define DLLWINCONTROL_EXPORT
#endif
