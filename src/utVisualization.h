/*
 * Ubitrack - Library for Ubiquitous Tracking
 * Copyright 2006, Technische Universitaet Muenchen, and individual
 * contributors as indicated by the @authors tag. See the 
 * copyright.txt in the distribution for a full listing of individual
 * contributors.
 *
 * This is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; either version 2.1 of
 * the License, or (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this software; if not, write to the Free
 * Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA, or see the FSF site: http://www.fsf.org.
 */

/**
 * @file
 * Common definitions of the ubitrack vision library
 *
 * @author Daniel Pustka <daniel.pustka@in.tum.de>
 */

#ifndef __UTVISUALIZATION_H_INCLUDED__
#define __UTVISUALIZATION_H_INCLUDED__

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

#include <utVisualization/Config.h>

#endif // __UTVISUALIZATION_H_INCLUDED__