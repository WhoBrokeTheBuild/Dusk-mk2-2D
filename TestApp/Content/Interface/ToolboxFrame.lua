require "Dusk/UI"

function ToolboxFrame_UpdateSizeButton_OnClick()
	local ui = Dusk.GetUIManager()

	print(ui:GetInput("ToolboxFrame_NameInput"):GetValue())
	print(ui:GetInput("ToolboxFrame_WidthInput"):GetValue())
	print(ui:GetInput("ToolboxFrame_HeightInput"):GetValue())
	print(ui:GetInput("ToolboxFrame_ScaleInput"):GetValue())
	print(ui:GetInput("ToolboxFrame_TileWidthInput"):GetValue())
	print(ui:GetInput("ToolboxFrame_TileHeightInput"):GetValue())
end
