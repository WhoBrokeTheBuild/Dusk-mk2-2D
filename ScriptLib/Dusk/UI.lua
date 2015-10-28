require "Dusk/Events"

-- Dusk.UIManager

local UIManager = Dusk.Class(Dusk.Object, function(self, ptr)
	Dusk.Object.init(self, ptr)
end)

function UIManager:GetElement(name)
    return Dusk.UIElement( dusk_ui_manager_get_element(self.dusk_ptr, name) )
end

function UIManager:GetInput(name)
    return Dusk.UIInput( dusk_ui_manager_get_element(self.dusk_ptr, name) )
end

Dusk.UIManager = UIManager

Dusk.HasUIManager = function()
	return (dusk_ptr_ui_manager ~= nil)
end

dusk_ui_manager = Dusk.UIManager( dusk_ptr_ui_manager )
Dusk.GetUIManager = function()
	return dusk_ui_manager
end

-- Dusk.UIState

Dusk.UIState = {
    StateDefault  = 1,
    StateActive   = 2,
    StateHover    = 3,
    StateDisabled = 4
}

-- Dusk.UIRelPoint

Dusk.UIRelPoint = {
    TopLeft		= 1,
    TopRight	= 2,
    BottomLeft  = 3,
    BottomRight = 4
}

-- UI Size Constants

Dusk.UISizeMin = "min"
Dusk.UISizeMax = "max"

-- Dusk.UIElement

local UIElement = Dusk.Class(Dusk.EventDispatcher, function(self, ptr)
	Dusk.EventDispatcher.init(self, ptr)
end)

function UIElement:IsMouseOver()
	return dusk_ui_element_is_mouse_over(self.dusk_ptr)
end

function UIElement:IsMouseDown()
	return dusk_ui_element_is_mouse_down(self.dusk_ptr)
end

function UIElement:HasFocus()
	return dusk_ui_element_has_focus(self.dusk_ptr)
end

function UIElement:IsFocusable()
	return dusk_ui_element_is_focusable(self.dusk_ptr)
end

function UIElement:IsActive()
	return dusk_ui_element_is_active(self.dusk_ptr)
end

function UIElement:IsVisible()
	return dusk_ui_element_is_visible(self.dusk_ptr)
end

function UIElement:GetName()
	return dusk_ui_element_get_name(self.dusk_ptr)
end

function UIElement:GetState()
	return dusk_ui_element_get_state(self.dusk_ptr)
end

function UIElement:GetPos()
	return dusk_ui_element_get_pos(self.dusk_ptr)
end

function UIElement:GetSize()
	return dusk_ui_element_get_size(self.dusk_ptr)
end

function UIElement:SetSize(width, height)
	return dusk_ui_element_get_size(self.dusk_ptr, width, height)
end

UIElement.EvtShow         = 1
UIElement.EvtHide         = 2
UIElement.EvtActivate     = 3
UIElement.EvtDeactivate   = 4
UIElement.EvtMouseEnter   = 5
UIElement.EvtMouseLeave   = 6
UIElement.EvtMouseDown    = 7
UIElement.EvtMouseUp      = 8
UIElement.EvtFocus        = 9
UIElement.EvtBlur         = 10
UIElement.EvtUpdate       = 11
UIElement.EvtRender       = 12
UIElement.EvtLayoutChange = 13
UIElement.EvtStateChange  = 14

Dusk.UIElement = UIElement

-- Dusk.UIInput

local UIInput = Dusk.Class(Dusk.UIElement, function(self, ptr)
	Dusk.UIElement.init(self, ptr)
end)

function UIInput:GetValue()
	return dusk_ui_input_get_value(self.dusk_ptr)
end

UIInput.EvtChange = 100

Dusk.UIInput = UIInput
