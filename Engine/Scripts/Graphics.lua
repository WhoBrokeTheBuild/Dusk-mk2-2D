if not Dusk then Dusk = { } end
if not Dusk.Graphics then Dusk.Graphics = { } end

Dusk.Graphics.GetWindow = function()
	return Dusk.Graphics.Window( dusk_graphics_system_get_window() )
end

Dusk.Graphics.GetShaderManager = function()
	return Dusk.Graphics.ShaderManager( dusk_graphics_system_get_shader_manager() );
end

Dusk.Graphics.GetContext = function()
	return Dusk.Graphics.GraphicsContext( dusk_graphics_system_get_graphics_context() );
end

-- Dusk.Graphics.Window

local Window = DuskClass(DuskObject, function(self, ptr)
    DuskObject.init(self, ptr)
end)

function Window:SetSize(width, height)
    return dusk_window_set_size(self.dusk_ptr, width, height)
end

function Window:GetWidth()
    return dusk_window_get_width(self.dusk_ptr)
end

function Window:SetWidth(width)
    return dusk_window_set_width(self.dusk_ptr, width)
end

function Window:GetHeight()
    return dusk_window_get_height(self.dusk_ptr)
end

function Window:SetHeight(height)
    return dusk_window_set_height(self.dusk_ptr, height)
end

function Window:GetTitle()
    return dusk_window_get_title(self.dusk_ptr)
end

function Window:SetTitle(title)
    return dusk_window_set_title(self.dusk_ptr, title)
end

Dusk.Graphics.Window = Window

-- Dusk.Graphics.ShaderManager

local ShaderManager = DuskClass(DuskObject, function(self, ptr)
	DuskObject.init(self, ptr)
end)

function ShaderManager:LoadProgram(name, fragShader, vertShader)
	return dusk_shader_manager_load_program(self.dusk_ptr, name, fragShader, vertShader)
end

Dusk.Graphics.ShaderManager = ShaderManager

-- Dusk.Graphics.GraphicsContext

local GraphicsContext = DuskClass(DuskObject)

Dusk.Graphics.GraphicsContext = GraphicsContext
