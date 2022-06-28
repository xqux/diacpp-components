#pragma once
#ifndef   MAINLOGGER_HPP
#define   MAINLOGGER_HPP


// qt
#include <QFile>
#include <QObject>
#include <QTextStream>


// the main logger
class MainLogger: public QObject
{
	Q_OBJECT

public: // creation and destruction of objects
	explicit MainLogger(QObject* parent = nullptr);
	~MainLogger() noexcept = default; // no virtual

public:
	auto setLogPath(QString const& filePath) -> bool;
	auto logPath() const -> QString;

public: // whitespace characters when logging
	auto rsep() -> QString&
	{ return m_sep; }

	auto rendln() -> QString&
	{ return m_endln; }

public:
	template <typename Arg, typename... Rest>
	auto print(Arg&& arg, Rest&&... rest) -> bool
	{
		auto stm = QTextStream(m_file);

		stm << arg;
		((stm << m_sep << rest), ...);

		return stm.status() == QTextStream::Status::Ok;
	}

	template <typename Arg, typename... Rest>
	auto println(Arg&& arg, Rest&&... rest) -> bool
	{
		auto stm = QTextStream(m_file);

		stm << arg;
		((stm << m_sep << rest), ...);
		stm << m_endln;

		return stm.status() == QTextStream::Status::Ok;
	}

public: // if there is no new line at the end of the file, writes
	void ensureTrailingNewLine();

public:
	auto openFileExternally() const -> bool;

private: // members
	QFile* m_file;
	QString m_sep, m_endln;
};


#endif // MAINLOGGER_HPP
