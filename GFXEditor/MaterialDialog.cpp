#include "MaterialDialog.h"
#include "SolidMaterial.h"

void GFXEditor::Plugins::MaterialDialog::show(GFXEngine::Graphics::Material* material, MaterialDialogCallback callback)
{
	m_material = material;
	m_visible = true;
	m_callback = callback;
}

bool GFXEditor::Plugins::MaterialDialog::isEnabled() const
{
	return true;
}

void GFXEditor::Plugins::MaterialDialog::onRegister(WorldEditor& editor)
{
	
}

void GFXEditor::Plugins::MaterialDialog::init(GFXEditor::WorldEditor& editor, GFXEngine::Core::UIContext& context, GFXEngine::Graphics::Renderer& renderer)
{
	
}

void GFXEditor::Plugins::MaterialDialog::update(GFXEditor::WorldEditor& editor, GFXEngine::Core::UIContext& context, GFXEngine::InputManager& input, float deltaTime)
{
	
}

void GFXEditor::Plugins::MaterialDialog::beforeRender(GFXEditor::WorldEditor& editor, GFXEngine::Core::UIContext& context, GFXEngine::Graphics::Renderer& renderer, uint32_t imageIndex)
{
	
}

void GFXEditor::Plugins::MaterialDialog::render(GFXEditor::WorldEditor& editor, GFXEngine::Core::UIContext& context, GFXEngine::Graphics::Renderer& renderer, uint32_t imageIndex)
{
	if (!m_visible || m_material == nullptr)
		return;

	ImGui::Begin("Material Dialog");

	if(auto solidMaterial = dynamic_cast<GFXEngine::Graphics::SolidMaterial*>(m_material))
	{
		ImGui::Text("Solid Material");
		if(ImGui::ColorEdit4("Color", &solidMaterial->getColorRef()[0]))
		{
			solidMaterial->updateMaterial(renderer);
		}
	}

	ImGui::PushID("ApplyButton");
	if(ImGui::Button("Apply"))
	{
		if (m_callback)
			m_callback.value()(*this, m_material);

		this->hide();
	}
	ImGui::PopID();
	ImGui::End();
}

void GFXEditor::Plugins::MaterialDialog::afterRender(GFXEditor::WorldEditor& editor, GFXEngine::Core::UIContext& context, GFXEngine::Graphics::Renderer& renderer, uint32_t imageIndex)
{
	
}

void GFXEditor::Plugins::MaterialDialog::handleInput(GFXEditor::WorldEditor& editor, GLFWwindow* window, int key, int scancode, int action, int mods)
{
	
}

void GFXEditor::Plugins::MaterialDialog::handleMouseInput(GFXEditor::WorldEditor& editor, GLFWwindow* window, int button, int action, int mods)
{
	
}

void GFXEditor::Plugins::MaterialDialog::handleMouseMove(GFXEditor::WorldEditor& editor, GLFWwindow* window, double xpos, double ypos)
{
	
}

void GFXEditor::Plugins::MaterialDialog::dispose(GFXEditor::WorldEditor& editor, GFXEngine::Core::UIContext& context, GFXEngine::Graphics::Renderer& renderer)
{
	
}
