if not Dusk then Dusk = { } end

-- Dusk.GraphicsSystem

Dusk.GetGraphicsSystem = function()
	return Dusk.GraphicsSystem( dusk_get_graphics_system() )
end

local GraphicsSystem = Dusk.Class(Dusk.Object, function(self, ptr)
	Dusk.Object.init(self, ptr)
end)

function GraphicsSystem:GetWinSize()
    return dusk_graphics_system_get_window_size()
end

function GraphicsSystem:GetWinTitle()
    return dusk_graphics_system_get_window_title()
end

function GraphicsSystem:SetWinTitle(title)
    return dusk_graphics_system_set_window_title(title)
end

function GraphicsSystem:GetContext()
	return Dusk.GraphicsContext( dusk_graphics_system_get_context() )
end

Dusk.GraphicsSystem = GraphicsSystem

-- Dusk.GraphicsContext

local GraphicsContext = Dusk.Class(Dusk.Object, function(self, ptr)
	Dusk.Object.init(self, ptr)
end)

function GraphicsContext:Draw(sprite)
	dusk_graphics_context_draw(self.dusk_ptr, sprite.dusk_ptr)
end

Dusk.GraphicsContext = GraphicsContext

-- Dusk.Texture

Dusk.NewTexture = function(filename)
	return Dusk.Texture( dusk_texture_new(filename) )
end

Dusk.DeleteTexture = function(texture)
	dusk_texture_delete(texture.dusk_ptr)
end

local Texture = Dusk.Class(Dusk.Object, function(self, ptr)
    Dusk.Object.init(self, ptr)
end)

Dusk.Texture = Texture

-- Dusk.Sprite

Dusk.NewSprite = function(texture)
	return Dusk.Sprite( dusk_sprite_new(texture.dusk_ptr) )
end

Dusk.DeleteSprite = function(sprite)
	dusk_sprite_delete(sprite.dusk_ptr)
end

local Sprite = Dusk.Class(Dusk.Object, function(self, ptr)
    Dusk.Object.init(self, ptr)
end)

function Sprite:GetPos()
	return dusk_sprite_get_pos(self.dusk_ptr)
end

function Sprite:SetPos(x, y)
	dusk_sprite_set_pos(self.dusk_ptr, x, y)
end

Dusk.Sprite = Sprite
