/*
 * Copyright 2014 (C) Yannick Pflanzer <neo-engine.de>
 *
 * This file is part of NeoGui.
 *
 * NeoGui is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * NeoGui is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with NeoGui.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Diese Datei ist Teil von NeoGui.
 *
 * NeoGui ist Freie Software: Sie k�nnen es unter den Bedingungen
 * der GNU Lesser General Public License, wie von der Free Software Foundation,
 * Version 3 der Lizenz oder (nach Ihrer Wahl) jeder sp�teren
 * ver�ffentlichten Version, weiterverbreiten und/oder modifizieren.
 *
 * NeoGui wird in der Hoffnung, dass es n�tzlich sein wird, aber
 * OHNE JEDE GEW�HRLEISTUNG, bereitgestellt; sogar ohne die implizite
 * Gew�hrleistung der MARKTF�HIGKEIT oder EIGNUNG F�R EINEN BESTIMMTEN ZWECK.
 * Siehe die GNU Lesser General Public License f�r weitere Details.
 *
 * Sie sollten eine Kopie der GNU Lesser General Public License zusammen mit
 *diesem
 * Programm erhalten haben. Wenn nicht, siehe <http://www.gnu.org/licenses/>.
 */

#ifndef __NEO2D_H__
#define __NEO2D_H__

#ifdef SWIG
#define DISOWN(a) %apply SWIGTYPE* DISOWN {a};
#else
#define DISOWN(a)
#endif

#ifdef WIN32
	#ifdef _MSC_VER
		#pragma warning(disable: 4251)
	#endif

	#if defined(NEO2D_DLL)
		#define NEO2D_EXPORT __declspec( dllexport )
	#elif defined(NEO_CORE_STATIC)
		#define NEO2D_EXPORT
	#else
		#define NEO2D_EXPORT __declspec( dllimport )
	#endif

#else
	#define NEO2D_EXPORT
#endif

#endif