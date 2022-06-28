#pragma once
#ifndef   MAINGRAPH_HPP
#define   MAINGRAPH_HPP


// qt
#include <QGraphicsView>


// main graph for main window, that
// used in ui file
class MainGraph: public QGraphicsView
{
	Q_OBJECT

public: // creation and destruction of objects
	explicit MainGraph(QWidget* parent = nullptr);
	~MainGraph() noexcept = default; // no virtual

public: // methods for control the scale
	// it works for the view has no rotation applied
	auto getScaleFactor() const -> qreal;

	auto stepScale() const -> qreal
	{ return m_stepScale; }

	void setStepScale(qreal val)
	{ m_stepScale = val; }

	auto minScale() const -> qreal
	{ return m_minScale; }

	void setMinScale(qreal val)
	{ m_minScale = val; }

	auto maxScale() const -> qreal
	{ return m_maxScale; }

	void setMaxScale(qreal val)
	{ m_maxScale = val; }

protected: // scaling when scrolling the mouse wheel while holding ctrl
	void wheelEvent(QWheelEvent* event) override;

private: // members
	qreal m_stepScale;
	qreal m_minScale, m_maxScale;
};


#endif // MAINGRAPH_HPP
