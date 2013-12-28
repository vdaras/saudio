/**
 * Copyright (c) 2011-2014, Vasileios Daras. All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301  USA
 */

#include "Directory.h"

//standard library includes
#include <algorithm>

Directory::Directory(const std::string& name, Directory* parent)
    : name(name),
      parentDirectory(parent)
{

}

Directory::~Directory()
{
    std::for_each(subDirectories.begin(), subDirectories.end(), [](Directory* dir)
    {
        delete dir;
    });
    subDirectories.clear();
}


const std::string& Directory::GetName() const
{
    return name;
}

const std::forward_list<std::string>& Directory::GetFiles() const
{
    return files;
};


const std::forward_list<Directory*>& Directory::GetSubDirectories() const
{
    return subDirectories;
}

Directory* Directory::GetParent() const
{
    return parentDirectory;
}
