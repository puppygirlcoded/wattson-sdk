#include <vendor/std.hpp>

void Render::OnSwapBuffers()
{
	std::unique_lock< std::shared_mutex > lock(this->m_smMutex);

	if (this->m_dThreadedDrawData.empty())
	{
		return;
	}

	const auto DrawList = ImGui::GetBackgroundDrawList();
	for (const DrawObject& Object : this->m_dThreadedDrawData)
	{
		if (!Object.m_Object.has_value())
		{ 
			continue;
		}

		switch (Object.m_Type)
		{
		case EDrawTypeLine:
		{
			auto LineObject = std::any_cast<LineDrawObject>(Object.m_Object);
			DrawList->AddLine({ LineObject.m_vecStart.x, LineObject.m_vecStart.y }, { LineObject.m_vecEnd.x, LineObject.m_vecEnd.y }, ImColor(255, 255, 255), LineObject.m_flThickness);
		}
		break;
		case EDrawTypeText:
		{
			auto TextObject = std::any_cast<TextDrawObject>(Object.m_Object);
			if (TextObject.m_bCenter)
			{
				ImVec2 m_vecTextSize = ImGui::CalcTextSize(TextObject.m_sLabel.data());
				DrawList->AddText({ TextObject.m_vecPosition.x - m_vecTextSize.x / 2.f, TextObject.m_vecPosition.y }, ImColor(255, 255, 255), TextObject.m_sLabel.data());
			}
			else
			{
				DrawList->AddText({ TextObject.m_vecPosition.x, TextObject.m_vecPosition.y }, ImColor(255, 255, 255), TextObject.m_sLabel.data());
			}
		}
		break;
		}
	}
}