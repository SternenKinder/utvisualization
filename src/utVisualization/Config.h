#ifndef __UBITRACK_VISUALIZATION_CONFIG_H_INCLUDED__
#define __UBITRACK_VISUALIZATION_CONFIG_H_INCLUDED__
#define UBITRACK_COMPONENTS_PATH "lib/ubitrack"
#define UBITRACK_COMPONENTS_RELAVIVEPATH "ubitrack"

#ifdef _WIN32
// fix for simplified build scripts (ulrich eck)
#   ifdef UTVISUALIZATION_DLL
#       define UBITRACK_DLL
#   endif
#	ifdef UBITRACK_DLL
#		define UBITRACK_EXPORT __declspec( dllexport )
#	else
#		define UBITRACK_EXPORT __declspec( dllimport )
#	endif
#else // _WIN32
#	define UBITRACK_EXPORT
#endif

#ifndef HAVE_GLEW
#define HAVE_GLEW
#endif
#ifndef HAVE_LAPACK 
#define HAVE_LAPACK
#endif
#ifndef HAVE_OPENCV 
#define HAVE_OPENCV
#endif
#endif
