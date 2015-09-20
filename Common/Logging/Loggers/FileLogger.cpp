#include "FileLogger.hpp"

namespace dusk
{

Map<string, ofstream*> FileLogger::s_Streams;
Map<string, int> FileLogger::s_StreamOwners;

FileLogger::FileLogger(const string& filename) :
	m_Filename(filename),
	m_Stream(nullptr)
{
	if (s_Streams.contains_key(m_Filename))
	{
		m_Stream = s_Streams[m_Filename];
		++s_StreamOwners[m_Filename];
	}
	else
	{
		m_Stream = new ofstream();
		m_Stream->open(m_Filename);

		s_Streams.add(m_Filename, m_Stream);
		s_StreamOwners.add(m_Filename, 1);
	}
}

FileLogger::~FileLogger()
{
	if (--s_StreamOwners[m_Filename] <= 0)
	{
		ofstream* pFile = s_Streams[m_Filename];
		pFile->close();
		s_Streams.erase(m_Filename);
	}
}

void FileLogger::Log(const string& line, const LogForegroundColor& fgColor, const LogBackgroundColor& bgColor)
{
	size_t len = line.length();
	char* fullLine = new char[len + 1];

	memcpy(fullLine, line.c_str(), len);
	fullLine[len] = '\n';

	m_Stream->write(fullLine, len + 1);
	m_Stream->flush();
}

} // namespace dusk
