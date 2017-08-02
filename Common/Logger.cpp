/*
    Copyright(c) Microsoft Open Technologies, Inc. All rights reserved.

    The MIT License(MIT)

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files(the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions :

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.
*/

#include "pch.h"
#if 0
#include "Logger.h"
#include "Util.h"
#include <windows.storage.h>
#include <ppltasks.h>

using namespace Windows::Storage;
using namespace Windows::Foundation;
using namespace Platform;
using namespace concurrency;
using namespace std;
using namespace nodeuwputil;

unique_ptr<Logger> Logger::m_instance;
mutex Logger::m_mutex;
once_flag Logger::m_onceflag;

Logger& Logger::GetInstance(String^ logFileName)
{
	call_once(m_onceflag, [=] {
		m_instance.reset(new (nothrow) Logger(logFileName));
	});
	return *m_instance.get();
}

Logger::Logger(String^ logFileName)
{
	StorageFolder^ localFolder = ApplicationData::Current->LocalFolder;	
	m_file = create_task(localFolder->CreateFileAsync(logFileName, 
		Windows::Storage::CreationCollisionOption::OpenIfExists)).get();
}

void Logger::Log(ILogger::LogLevel logLevel, const char* str) const
{
	lock_guard<mutex> lock(m_mutex);
	shared_ptr<wchar_t> wc = CharToWChar(str, strlen(str) + 1);
	String^ pstr = ref new String(wc.get());

	// Append console logs to file
	create_task(FileIO::AppendTextAsync(m_file, pstr + "\r\n")).wait();
}
#endif