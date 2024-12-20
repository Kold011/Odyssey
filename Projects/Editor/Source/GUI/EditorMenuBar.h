#pragma once
#include "GUIElement.h"

namespace Odyssey
{
	class EditorMenuBar : public GUIElement
	{
	public:
		EditorMenuBar() = default;

	public:
		virtual void Update() override;
		virtual bool Draw() override;

	private:
		void OpenFileDialog();

	private:
		bool m_ShowDemoWindow = false;
	};
}