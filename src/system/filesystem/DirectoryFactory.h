/**
 * Copyright (c) 2011-2017, Vasileios Daras. All rights reserved.
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

#ifndef DIRECTORY_FACTORY_H
#define DIRECTORY_FACTORY_H

//standard library includes
#include <memory>

#include "Directory.h"

class DirectoryFactory {

    public:

    /**
     * @param rootDirectory
     *        Path of the root directory.
     *
     * @return
     *         A directory object representing the root of the directory tree.        
     */
    static std::unique_ptr<Directory> CreateDirectoryTree(const std::string& rootDirectory);


    private:

    /**
     * Populates a directory by calling itself recursively.
     *
     * @param directory
     *        Directory object to populate.
     *
     * @param directoryPath
     *        Full path of the current directory. 
     */
    static void PopulateDirectoryUnix(Directory* directory, const std::string& directoryPath);

};

#endif
