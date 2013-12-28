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

#ifndef AUDIO_LIBRARY_H
#define AUDIO_LIBRARY_H

//standard libary includes
#include <forward_list>
#include <set>
#include <string>
#include <vector>


class Directory;

/**
 * Class encapsulating functionality for the server's audio
 * library.
 */
class AudioLibrary {

	static std::set<std::string> SupportedFileTypes;

    std::forward_list<std::string> audioFiles; 

    std::string rootDirectoryPath;

    public:

    /**
     * Constructor.
     *
     * @param rootDirectoryPath
     *        Root directory of the audio library.
     */
    AudioLibrary(const std::string& rootDirectoryPath);

 
    /**
     * Checks if a file, given its path, is supported by the audio application by
     * comparing its extension to the supported file type extensions.
     *
     * @param filePath
     *        Path of the file.
     *
     * @return
     *         Whether the file type of a file is supported by the audio application.
     */
    bool SupportsFileType(const std::string& filePath) const;


    /**
     * Checks if a file, given its path, exists in the library.
     *
     * @param filePath
     *        Path of the file.
     *
     * @return
     *         Whether a file exists in the library or not.
     */
    bool FileExists(const std::string& filePath) const;


    /**
     * @return
     *         The full path of a file by appending the libraries root path.
     */
    std::string GetFullPath(const std::string& filePath) const;


    /**
     * Compiles a list of all files that contain a certain keyword.
     *
     * @param keyword
     *        Keyword to use when searching
     *
     * @return
     *         A list of all files that matched the search.
     * 
     */
    std::forward_list<const std::string*> Search(const std::string& keyword) const;

    private:

    /**
     * Compiles a list of all supported files in a directory.
     *
     * @param Directory
     *        Directory to process.
     *
     * @param path
     *        Current relative path.
     */
    void CompileFileList(Directory* directory, std::string path);
}; 	

#endif