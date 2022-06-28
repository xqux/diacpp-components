#pragma once
#ifndef   MAINCONFIG_HPP
#define   MAINCONFIG_HPP


// qt
#include <QObject>


// qt types
class QFile;


// the config
class MainConfig: public QObject
{
	Q_OBJECT

public: // creation and destruction of objects
	explicit MainConfig(QObject* parent = nullptr);
	~MainConfig() noexcept = default;

public:
	auto setConfigPath(QString const& filePath) -> bool;
	auto configPath() const -> QString;

public: // save and restore window geometry
	void saveGeometry(QPoint const& pos, QSize const& size);
	auto restoreGeometry(QPoint& pos, QSize& size) -> bool;

private: // members
	QFile* m_file;
};


#endif // MAINCONFIG_HPP
