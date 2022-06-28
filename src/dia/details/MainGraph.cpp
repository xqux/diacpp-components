// related header
#include "MainGraph.hpp"

// qt
#include <QWheelEvent>


// qt enums
using Qt::KeyboardModifier::ControlModifier;


MainGraph::MainGraph(QWidget* parent)
	: QGraphicsView(parent)
	, m_stepScale(1.0)
	, m_minScale(1.0), m_maxScale(1.0)
{
	// enable antialiasing and high quality rendering
	setRenderHints(QPainter::RenderHint::Antialiasing |
	               QPainter::RenderHint::TextAntialiasing |
	               QPainter::RenderHint::SmoothPixmapTransform |
	               QPainter::RenderHint::LosslessImageRendering);

	setViewportUpdateMode(FullViewportUpdate);

	// enable mouse scrolling
	setDragMode(QGraphicsView::DragMode::ScrollHandDrag);

	// center scene when resizing and follow mouse cursor on zoom
	setResizeAnchor(QGraphicsView::ViewportAnchor::AnchorViewCenter);
	setTransformationAnchor(QGraphicsView::ViewportAnchor::AnchorUnderMouse);
}

auto MainGraph::getScaleFactor() const -> qreal
{
	auto trf = QGraphicsView::transform();
	return trf.m11();
}

void MainGraph::wheelEvent(QWheelEvent* event)
{
	assert(event != nullptr && "event mustn't be null.");

	auto mods = event->modifiers();
	auto delta = event->angleDelta().y();

	if (mods != ControlModifier || delta == 0)
	{ QGraphicsView::wheelEvent(event); }
	else
	{
		if (delta > 0)
		{
			if (getScaleFactor() > m_maxScale)
			{ return; }

			scale(m_stepScale, m_stepScale);
		}
		else // delta < 0
		{
			if (getScaleFactor() < m_minScale)
			{ return; }

			auto step = 1 / m_stepScale;
			scale(step, step);
		}
	}
}
