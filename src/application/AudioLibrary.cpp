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

#include "AudioLibrary.h"

//standard library includes
#include <algorithm>
#include <iostream>

#include "exception/GenericAudioStreamerException.h"
#include "system/filesystem/Directory.h"
#include "system/filesystem/DirectoryFactory.h"
#include "system/filesystem/FileSystemUtils.h"

std::set<std::string> AudioLibrary::SupportedFileTypes =
{
    ".mp3",
    ".ogg",
    ".wav"
};

AudioLibrary::AudioLibrary(const std::string& rootDirectoryPath)
    : rootDirectoryPath(rootDirectoryPath)
{

    std::unique_ptr<Directory> dir = DirectoryFactory::CreateDirectoryTree(rootDirectoryPath);

    CompileFileList(dir.get(), "");
}

bool AudioLibrary::SupportsFileType(const std::string& filePath) const
{

    std::string extension = FindExtension(filePath);

    std::transform(extension.begin(), extension.end(), extension.begin(), tolower);

    return SupportedFileTypes.find(extension) != SupportedFileTypes.end();
}

bool AudioLibrary::FileExists(const std::string& filePath) const
{
    return std::find(audioFiles.begin(), audioFiles.end(), filePath) != audioFiles.end();
}


std::string AudioLibrary::GetFullPath(const std::string& filePath) const
{
    return rootDirectoryPath + filePath;
}


std::forward_list<const std::string*> AudioLibrary::Search(const std::string& keyword) const
{

    std::forward_list<const std::string*> results;

for(const std::string& file : audioFiles)
    {

        if(file.find(keyword) != std::string::npos)
        {
            results.push_front(&file);
        }
    }

    return results;
}

void AudioLibrary::CompileFileList(Directory* dir, std::string path)
{

for(Directory* subDir : dir->GetSubDirectories())
    {

        std::string name = subDir->GetName();

        CompileFileList(subDir, path + name + "/");
    }

for(const std::string& file : dir->GetFiles())
    {

        if(SupportsFileType(file))
        {

            std::string filePath = path + file;

            audioFiles.push_front(filePath);

        }
    }
}
