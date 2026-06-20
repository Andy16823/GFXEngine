#pragma once
#include "Renderer.h"
#include "UIContext.h"
#include "InputManager.h"
#include <string>
#include "Utils.h"

namespace GFXEngine {
	namespace Core {

		class UIWidget {
		private:
			bool m_isVisible = false;
			std::string m_name;
			std::string m_uuid;

		public:
			//************************************
			// Method:    UIWidget
			// FullName:  GFXEngine::Core::UIWidget::UIWidget
			// Access:    public 
			// Returns:   
			// Qualifier: : m_uuid(Utils::generateUUID())
			//************************************
			UIWidget() : m_uuid(Utils::generateUUID()) {}
			
			//************************************
			// Method:    ~UIWidget
			// FullName:  GFXEngine::Core::UIWidget::~UIWidget
			// Access:    virtual public 
			// Returns:   
			// Qualifier:
			//************************************
			virtual ~UIWidget() = default;

		public:
			//************************************
			// Method:    init
			// FullName:  GFXEngine::Core::UIWidget::init
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: UIContext & context
			// Parameter: GFXEngine::Graphics::Renderer & renderer
			//************************************
			virtual void init(UIContext& context, GFXEngine::Graphics::Renderer& renderer) = 0;
			
			//************************************
			// Method:    handleInput
			// FullName:  GFXEngine::Core::UIWidget::handleInput
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: GLFWwindow * window
			// Parameter: int key
			// Parameter: int mods
			// Parameter: int action
			//************************************
			virtual void handleInput(GLFWwindow* window, int key, int mods, int action) = 0;
			
			//************************************
			// Method:    handleMouseInput
			// FullName:  GFXEngine::Core::UIWidget::handleMouseInput
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: GLFWwindow * window
			// Parameter: int button
			// Parameter: int mods
			// Parameter: int action
			//************************************
			virtual void handleMouseInput(GLFWwindow* window, int button, int mods, int action) = 0;
			
			//************************************
			// Method:    handleMouseMove
			// FullName:  GFXEngine::Core::UIWidget::handleMouseMove
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: GLFWwindow * window
			// Parameter: double xpos
			// Parameter: double ypos
			//************************************
			virtual void handleMouseMove(GLFWwindow* window, double xpos, double ypos) = 0;
			
			//************************************
			// Method:    update
			// FullName:  GFXEngine::Core::UIWidget::update
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: UIContext & context
			// Parameter: InputManager & input
			// Parameter: float deltaTime
			//************************************
			virtual void update(UIContext& context, InputManager& input, float deltaTime) = 0;
			
			//************************************
			// Method:    beforeRender
			// FullName:  GFXEngine::Core::UIWidget::beforeRender
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: UIContext & context
			// Parameter: GFXEngine::Graphics::Renderer & renderer
			// Parameter: uint32_t imageIndex
			//************************************
			virtual void beforeRender(UIContext& context, GFXEngine::Graphics::Renderer& renderer, uint32_t imageIndex) = 0;
			
			//************************************
			// Method:    render
			// FullName:  GFXEngine::Core::UIWidget::render
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: UIContext & context
			// Parameter: GFXEngine::Graphics::Renderer & renderer
			// Parameter: uint32_t imageIndex
			//************************************
			virtual void render(UIContext& context, GFXEngine::Graphics::Renderer& renderer, uint32_t imageIndex) = 0;
			
			//************************************
			// Method:    afterRender
			// FullName:  GFXEngine::Core::UIWidget::afterRender
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: UIContext & context
			// Parameter: GFXEngine::Graphics::Renderer & renderer
			// Parameter: uint32_t imageIndex
			//************************************
			virtual void afterRender(UIContext& context, GFXEngine::Graphics::Renderer& renderer, uint32_t imageIndex) = 0;
			
			//************************************
			// Method:    dispose
			// FullName:  GFXEngine::Core::UIWidget::dispose
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: UIContext & context
			// Parameter: GFXEngine::Graphics::Renderer & renderer
			//************************************
			virtual void dispose(UIContext& context, GFXEngine::Graphics::Renderer& renderer) = 0;

		public:
			//************************************
			// Method:    getName
			// FullName:  GFXEngine::Core::UIWidget::getName
			// Access:    public 
			// Returns:   const std::string&
			// Qualifier: const
			//************************************
			const std::string& getName() const { return m_name; };
			
			//************************************
			// Method:    getUUID
			// FullName:  GFXEngine::Core::UIWidget::getUUID
			// Access:    public 
			// Returns:   const std::string&
			// Qualifier: const
			//************************************
			const std::string& getUUID() const { return m_uuid; };
			
			//************************************
			// Method:    isVisible
			// FullName:  GFXEngine::Core::UIWidget::isVisible
			// Access:    public 
			// Returns:   bool
			// Qualifier: const
			//************************************
			bool isVisible() const { return m_isVisible; }

			//************************************
			// Method:    setName
			// FullName:  GFXEngine::Core::UIWidget::setName
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: const std::string & name
			//************************************
			void setName(const std::string& name) { m_name = name; }

			//************************************
			// Method:    setVisible
			// FullName:  GFXEngine::Core::UIWidget::setVisible
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: bool visible
			//************************************
			void setVisible(bool visible) {	m_isVisible = visible; }

		public:
			//************************************
			// Method:    show
			// FullName:  GFXEngine::Core::UIWidget::show
			// Access:    public 
			// Returns:   void
			// Qualifier:
			//************************************
			void show() { m_isVisible = true; }
			
			//************************************
			// Method:    hide
			// FullName:  GFXEngine::Core::UIWidget::hide
			// Access:    public 
			// Returns:   void
			// Qualifier:
			//************************************
			void hide() { m_isVisible = false; }
			
			//************************************
			// Method:    toggle
			// FullName:  GFXEngine::Core::UIWidget::toggle
			// Access:    public 
			// Returns:   void
			// Qualifier:
			//************************************
			void toggle() {	m_isVisible = !m_isVisible; }
		};
	}
}