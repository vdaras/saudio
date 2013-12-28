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

#ifndef DIRECTORY_H
#define DIRECTORY_H

//standard libary includes
#include <string>
#include <forward_list>

/**
 * Objects of this class represent a directory of the filesystem.
 */
class Directory {

    friend class DirectoryFactory;
    
    std::string name;

	Directory* parentDirectory;

	std::forward_list<std::string> files;

	std::forward_list<Directory*> subDirectories;

    /**
     * Constructor.
     *
     * @param name
     *        Name of the directory. (relative to cwd)
     *
     * @param parent
     *        Parent direcctory of this directory.
     */
    Directory(const std::string& name, Directory* parent = nullptr);

    public:

    /**
     * Destructor.
     */
    ~Directory();
    
    /**
     * @return
     *         Name of the directory.
     */
    const std::string& GetName() const;

    /**
     * @return
     *         A list of files in the directory.
     */
    const std::forward_list<std::string>& GetFiles() const;

    /**
     * @return 
     *         A list of all directories in the directory.
     */
    const std::forward_list<Directory*>& GetSubDirectories() const;


    /**
     * @return 
     *         Parent of this directory.
     */
    Directory* GetParent() const;


    private:

    //disable copy construction and move operations
    Directory(const Directory& copy) = delete;

    Directory(Directory&& rvalue) = delete;

    Directory& operator=(const Directory& assign) = delete;

    Directory& operator=(Directory&& rvalue) = delete;

};

#endif
