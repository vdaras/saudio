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

#include "AudioStreamingServer.h"

//stndard library includes
#include <algorithm>
#include <cstring>
#include <iostream>

#include "exception/GenericAudioStreamerException.h"
#include "http/HttpRequest.h"
#include "http/HttpResponse.h"
#include "http/HttpException.h"
#include "http/ParsingHttpRequestExtractor.h"
#include "system/filesystem/FileSystemUtils.h"
#include "util/url/PercentUrlCodec.h"

constexpr int DEFAULT_BUFFER_SIZE = 4096;


std::map<std::string, HttpContentType> AudioStreamingServer::EXTENSION_TO_CONTENT_TYPE = {
    { ".mp3" , MP3 },
    { ".mp4" , MP4 },
    { ".ogg" , OGG },
    { ".wav" , WAV }
};

AudioStreamingServer::AudioStreamingServer(unsigned short port, unsigned maxConnections, unsigned servingThreads, const std::string& libraryDirectory)
: Server(port, maxConnections, servingThreads),
  audioLibrary(new AudioLibrary(libraryDirectory)),
  httpExtractor(new ParsingHttpRequestExtractor),
  urlCodec(new PercentURLCodec) {
}

AudioStreamingServer::~AudioStreamingServer() {
}

void AudioStreamingServer::Serve(Socket& clientSocket)
{
    try {
        
        std::array<char, DEFAULT_BUFFER_SIZE> recvBuffer;
        int read = clientSocket.Receive(recvBuffer);
        HttpRequest request(recvBuffer.data(), read);

        std::string requestUrl = httpExtractor->ExtractGET(request);
        requestUrl = urlCodec->DecodeURL(requestUrl);

        const char* songsearch = "/songsearch/";
        if(requestUrl.find(songsearch) == 0) {
            
            std::string keyword = requestUrl.substr(strlen(songsearch));
            SendMediaList(clientSocket, keyword, httpExtractor->ExtractHOST(request));

        } else if(audioLibrary->FileExists(requestUrl.substr(1))) {

            std::ifstream audioFile(audioLibrary->GetFullPath(requestUrl), std::ifstream::binary);
            if(audioFile.is_open()) {
                std::string extension = FindExtension(requestUrl);
                std::transform(extension.begin(), extension.end(), extension.begin(), tolower);
                StreamFile(clientSocket, audioFile, EXTENSION_TO_CONTENT_TYPE[extension]);
            } else {
                SendNotFound(clientSocket);
            }

        } else {
            SendNotFound(clientSocket);
        }

    } catch(const GenericAudioStreamerException& e) {
        std::lock_guard<std::mutex> guard(stderrMutex);
        std::cerr << e.what();
    } catch(const IHttpRequestExtractor::HttpExtractionException& e) {
        HttpResponse response(HTTP_1_1, BAD_REQUEST, NONE, 0);
        SendResponseHeader(clientSocket, response);
    }
}


void AudioStreamingServer::SendResponseHeader(Socket& clientSocket, const HttpResponse& response) const {
    std::string header = response.GenerateHeader();
    std::array<char, DEFAULT_BUFFER_SIZE> buffer;
    std::copy(std::begin(header), std::end(header), buffer.data());
    clientSocket.Send(buffer);
}


void AudioStreamingServer::StreamFile(Socket& clientSocket, std::ifstream& file, HttpContentType contentType) const {
    file.seekg(0, file.end);
    int fileLength = file.tellg();
    HttpResponse response(HTTP_1_1, OK, contentType, fileLength);
    SendResponseHeader(clientSocket, response);
    
    file.seekg(0, file.beg);
    std::array<char, DEFAULT_BUFFER_SIZE> sendbuf;
    file.read(sendbuf.data(), DEFAULT_BUFFER_SIZE);
    while(file.gcount() > 0) {
        clientSocket.Send(sendbuf, file.gcount());
        file.read(sendbuf.data(), DEFAULT_BUFFER_SIZE);
    }
}


void AudioStreamingServer::SendMediaList(Socket& clientSocket, const std::string& keyword, const std::string& hostName) const {
    
    const auto files = audioLibrary->Search(keyword);
    std::vector<std::string> urls;
    urls.reserve(std::distance(files.begin(), files.end()));
    
    int responseSize = 0;
    for(const auto& file : files) {
        std::string encodedFile = urlCodec->EncodeURL(file);
        std::string url;
        url.reserve(hostName.length() + encodedFile.length() + 9); //account 2 for '/', '\n' and 7 for 'http://'
        url += "http://";
        url += hostName;
        url += '/';
        url += encodedFile;
        url += '\n';
        responseSize += url.length();
        urls.push_back(std::move(url));
    }

    HttpResponse response(HTTP_1_1, OK, M3U, responseSize, keyword + ".m3u");
    SendResponseHeader(clientSocket, response);
    std::array<char, DEFAULT_BUFFER_SIZE> buffer;
    for(const std::string& url : urls) {
        std::copy(std::begin(url), std::end(url), buffer.data());
        clientSocket.Send(buffer, url.size());
    }
}


void AudioStreamingServer::SendNotFound(Socket& clientSocket) const {

    static const char* notFoundContent = "<h1>File Not Found</h1>";
    static const unsigned notFoundContentLength = strlen(notFoundContent);

    std::array<char, DEFAULT_BUFFER_SIZE> buffer;
    std::copy(notFoundContent, notFoundContent + notFoundContentLength, buffer.data());

    HttpResponse response(HTTP_1_1, NOT_FOUND, NONE, notFoundContentLength);
    SendResponseHeader(clientSocket, response);
    clientSocket.Send(buffer, notFoundContentLength);
}
