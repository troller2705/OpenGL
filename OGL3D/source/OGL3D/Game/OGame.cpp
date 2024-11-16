#include <OGL3D/Game/OGame.h>
#include <OGL3D/Window/OWindow.h>
#include <OGL3D/Graphics/OGraphicsEngine.h>

// Constructor
OGame::OGame()
{
	m_graphicsEngine = std::make_unique<OGraphicsEngine>();
	m_display = std::make_unique<OWindow>();

	m_display->makeCurrentContext();

	m_graphicsEngine->setViewport(m_display->getInnerSize());
}

// Destructor
OGame::~OGame()
{
	
}

void OGame::onCreate()
{
	const f32 triangleVertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};

	m_triangleVAO = m_graphicsEngine->createVertexArrayObject({(void*)triangleVertices, sizeof(f32)*3,3});
}

void OGame::onUpdate()
{
	m_graphicsEngine->clear(OVec4(1, 0, 0, 1));

	m_graphicsEngine->setVertexArrayObject(m_triangleVAO);

	m_graphicsEngine->drawTriangles(3, 0);

	m_display->present(false);
}

void OGame::onQuit()
{
}



void OGame::quit()
{
	m_isRunning = false;
}
