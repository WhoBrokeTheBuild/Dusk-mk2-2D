if not Dusk then Dusk = { } end

-- Dusk.Window

Dusk.GetWindow = function()
	return Dusk.Window( dusk_graphics_system_get_window() )
end

local Window = Dusk.Class(Dusk.IEventDispatcher, function(self, ptr)
    Dusk.IEventDispatcher.init(self, ptr)
end)

function Window:GetWidth()
    return dusk_window_get_width(self.dusk_ptr)
end

function Window:GetHeight()
    return dusk_window_get_height(self.dusk_ptr)
end

function Window:GetTitle()
    return dusk_window_get_title(self.dusk_ptr)
end

function Window:SetTitle(title)
    return dusk_window_set_title(self.dusk_ptr, title)
end

Dusk.Window = Window

-- Dusk.GraphicsContext

Dusk.GetGraphicsContext = function()
	return Dusk.GraphicsContext( dusk_graphics_system_get_graphics_context() )
end

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
