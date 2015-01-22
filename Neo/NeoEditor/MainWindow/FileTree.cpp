//========================================================================
//	Copyright (c) 2014-2015 Yannick Pflanzer <www.neo-engine.de>
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 2
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software Foundation,
//  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
//
//========================================================================

#include "FileTree.h"

#include <NeoEngine.h>
#include "../Maratis/Maratis.h"
#include <FL/fl_message.H>

using namespace Neo;

int FileTree::handle(int e)
{
    switch(e)
    {
    case FL_DND_ENTER:
    case FL_DND_DRAG:
    case FL_DND_RELEASE:
        return 1;
        break;

    case FL_DRAG:
        {
        	std::string fullPath = "file://" + m_currentPath;

#ifndef WIN32
        	fullPath += "/";
#else
        	fullPath += "\\";
#endif

    		const char* s = text(value());

    		if(!s)
    			return 0;

    		fullPath += s;

            Fl::copy(fullPath.c_str(), fullPath.length(), 0);
            Fl::dnd();
            return 1;
        }
        break;

    case FL_PASTE:
        {
            Scene* scene = NeoEngine::getInstance()->getLevel()->getCurrentScene();
            Fl_File_Browser::handle(FL_PUSH);

            this->do_callback(this, (long) 1);
            return 1;
        }
    }

    return Fl_File_Browser::handle(e);
}

int FileTree::load(const char* directory, Fl_File_Sort_F* sort)
{
	m_currentPath = directory;
	return Fl_File_Browser::load(directory, sort);
}
