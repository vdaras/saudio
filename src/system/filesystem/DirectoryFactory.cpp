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

#include "DirectoryFactory.h"


//system includes
#if defined __unix__ || (defined (__APPLE__) && defined (__MACH__))
#include <dirent.h>
#endif

#include "system/SystemException.h"

std::unique_ptr<Directory> DirectoryFactory::CreateDirectoryTree(const std::string& rootDirectory) {
    Directory* root = new Directory("");
#if defined __unix__ || (defined (__APPLE__) && defined (__MACH__))
    PopulateDirectoryUnix(root, rootDirectory);
#else
    throw new UnsupportedOSException();
#endif
    return std::unique_ptr<Directory>(root);
}


#if defined __unix__ || (defined (__APPLE__) && defined (__MACH__))
void DirectoryFactory::PopulateDirectoryUnix(Directory* directory, const std::string& directoryPath) {
    DIR* current = opendir(directoryPath.c_str());
    dirent* directoryEntry = readdir(current);
    while(directoryEntry != NULL) {
        std::string name(directoryEntry->d_name);
        if(directoryEntry->d_type == DT_DIR) {
            if(name != "." && name != "..") {
                Directory* subDirectory = new Directory(name, directory);
                PopulateDirectoryUnix(subDirectory, directoryPath + '/' + name);
                directory->subDirectories.push_front(subDirectory);
            }
        } else {
            directory->files.push_front(name);
        }
        directoryEntry = readdir(current);
    }
    closedir(current);
}
#endif
