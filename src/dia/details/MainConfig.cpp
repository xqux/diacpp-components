// related header
#include "MainConfig.hpp"

// qt
#include <QPoint>
#include <QSize>
#include <QSettings>
#include <QFile>


MainConfig::MainConfig(QObject* parent)
	: QObject(parent)
	, m_file(new QFile(this)) {}

auto MainConfig::setConfigPath(QString const& filePath) -> bool
{
	if (filePath.isEmpty())
	{
		m_file->close();
		m_file->setFileName(filePath);
		return false;
	}

	try
	{
		auto new_file = new QFile(filePath, this);
		if (!new_file->open(QIODevice::OpenModeFlag::ReadWrite |
		                    QIODevice::OpenModeFlag::Text |
		                    QIODevice::OpenModeFlag::Append))
		{
			delete new_file;
			return false;
		}

		delete m_file;
		m_file = new_file;
		return true;
	}
	catch (...)
	{ return false; }
}

auto MainConfig::configPath() const -> QString
{ return m_file->fileName(); }

#if defined(SAVING_WINDOW_POSITION_ENABLED) && SAVING_WINDOW_POSITION_ENABLED || \
    defined(SAVING_WINDOW_SIZE_ENABLED) && SAVING_WINDOW_SIZE_ENABLED

void MainConfig::saveGeometry(QPoint const& pos, QSize const& size)
{
	auto settings = QSettings(m_file->fileName(), QSettings::Format::IniFormat);

	(void)pos;
	(void)size;

#if defined(SAVING_WINDOW_POSITION_ENABLED) && SAVING_WINDOW_POSITION_ENABLED

	settings.setValue("MainWindow/state/pos", pos);

#endif // SAVING_WINDOW_POSITION_ENABLED

#if defined(SAVING_WINDOW_SIZE_ENABLED) && SAVING_WINDOW_SIZE_ENABLED

	settings.setValue("MainWindow/state/size", size);

#endif // SAVING_WINDOW_SIZE_ENABLED
}

auto MainConfig::restoreGeometry(QPoint& pos, QSize& size) -> bool
{
	auto settings = QSettings(m_file->fileName(), QSettings::Format::IniFormat);

	(void)pos;
	(void)size;

#if defined(SAVING_WINDOW_POSITION_ENABLED) && SAVING_WINDOW_POSITION_ENABLED

	auto savedPos = settings.value("MainWindow/state/pos");
	if (!savedPos.isValid())
	{ return false; }

#endif // SAVING_WINDOW_POSITION_ENABLED

#if defined(SAVING_WINDOW_SIZE_ENABLED) && SAVING_WINDOW_SIZE_ENABLED

	auto savedSize = settings.value("MainWindow/state/size");
	if (!savedSize.isValid())
	{ return false; }

#endif // SAVING_WINDOW_SIZE_ENABLED

#if defined(SAVING_WINDOW_POSITION_ENABLED) && SAVING_WINDOW_POSITION_ENABLED

	pos = savedPos.toPoint();

#endif // SAVING_WINDOW_POSITION_ENABLED

#if defined(SAVING_WINDOW_SIZE_ENABLED) && SAVING_WINDOW_SIZE_ENABLED

	size = savedSize.toSize();

#endif // SAVING_WINDOW_SIZE_ENABLED

	return true;
}

#else  // SAVING_WINDOW_POSITION_ENABLED || SAVING_WINDOW_SIZE_ENABLED

void MainConfig::saveGeometry(QPoint const& pos, QSize const& size)
{
	(void)pos;
	(void)size;
}

auto MainConfig::restoreGeometry(QPoint& pos, QSize& size) -> bool
{
	(void)pos;
	(void)size;

	return true;
}

#endif // SAVING_WINDOW_POSITION_ENABLED || SAVING_WINDOW_SIZE_ENABLED
