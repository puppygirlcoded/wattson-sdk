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
			DrawList->AddLine({ LineObject.m_vecStart.x, LineObject.m_vecStart.y }, { LineObject.m_vecEnd.x, LineObject.m_vecEnd.y }, ImColor(LineObject.m_colColor.r, LineObject.m_colColor.g, LineObject.m_colColor.b, LineObject.m_colColor.a), LineObject.m_flThickness);
		}
		break;
		case EDrawTypeText:
		{
			auto TextObject = std::any_cast<TextDrawObject>(Object.m_Object);
			if (TextObject.m_bCenter)
			{
				ImVec2 m_vecTextSize = ImGui::CalcTextSize(TextObject.m_sLabel.data());
				DrawList->AddText({ TextObject.m_vecPosition.x - m_vecTextSize.x / 2.f, TextObject.m_vecPosition.y }, ImColor(TextObject.m_colColor.r, TextObject.m_colColor.g, TextObject.m_colColor.b, TextObject.m_colColor.a), TextObject.m_sLabel.data());
			}
			else
			{
				DrawList->AddText({ TextObject.m_vecPosition.x, TextObject.m_vecPosition.y }, ImColor(TextObject.m_colColor.r, TextObject.m_colColor.g, TextObject.m_colColor.b, TextObject.m_colColor.a), TextObject.m_sLabel.data());
			}
		}
		break;
		case EDrawTypeRect:
		{
			auto RectObject = std::any_cast<RectDrawObject>(Object.m_Object);

			DrawList->AddRect({ RectObject.m_vecPosition.x, RectObject.m_vecPosition.y }, 
				{ RectObject.m_vecPosition.x + RectObject.m_vecSize.x, RectObject.m_vecPosition.y + RectObject.m_vecSize.y }, 
				ImColor(RectObject.m_colColor.r, RectObject.m_colColor.g, RectObject.m_colColor.b, RectObject.m_colColor.a), 0.f, 0, RectObject.m_flThickness);
		}
		break;
		case EDrawTypeRectFill:
		{
			auto RectObject = std::any_cast<RectDrawObject>(Object.m_Object);

			DrawList->AddRectFilled({ RectObject.m_vecPosition.x, RectObject.m_vecPosition.y },
				{ RectObject.m_vecPosition.x + RectObject.m_vecSize.x, RectObject.m_vecPosition.y + RectObject.m_vecSize.y },
				ImColor(RectObject.m_colColor.r, RectObject.m_colColor.g, RectObject.m_colColor.b, RectObject.m_colColor.a));
		}
		break;
		}
	}
}