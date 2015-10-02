require "Dusk/Program"
require "Dusk/Graphics"
require "Dusk/Input"

DuskLog("verbose", "Setting up the Window");

local prog = Dusk.GetProgram()
local gs = Dusk.GetGraphicsSystem()
local is = Dusk.GetInputSystem()
local ctx = gs:GetContext()
local dir = "stop"

is:MapKey("left", Dusk.Keys.A)
is:MapKey("right", Dusk.Keys.D)
is:MapKey("up", Dusk.Keys.W)
is:MapKey("down", Dusk.Keys.S)

local tex = Dusk.NewTexture("Content/Textures/test.png")
local spr = Dusk.NewSprite(tex)

function OnMappedInputPressed(inputId)
	if inputId == "left" then
        dir = "left"
    elseif inputId == "right" then
        dir = "right"
    elseif inputId == "up" then
        dir = "up"
    elseif inputId == "down" then
        dir = "down"
	end
end
is:AddEventListener(is.EvtMappedInputPress, "OnMappedInputPressed")

function OnMappedInputReleased(inputId)
	if inputId == "left" and dir == "left" then
        dir = "stop"
    elseif inputId == "right" and dir == "right" then
        dir = "stop"
    elseif inputId == "up" and dir == "up" then
        dir = "stop"
    elseif inputId == "down" and dir == "down" then
        dir = "stop"
	end
end
is:AddEventListener(is.EvtMappedInputRelease, "OnMappedInputReleased")

function OnUpdate(timeInfo)
    local x, y = spr:GetPos()
    local speed = 2 * timeInfo.Delta

    if dir == "left" then
        x = x - speed
    elseif dir == "right" then
        x = x + speed
    elseif dir == "up" then
        y = y - speed
    elseif dir == "down" then
        y = y + speed
    end

    spr:SetPos(x, y)
end
prog:AddEventListener(prog.EvtUpdate, "OnUpdate")

function OnRender()
    ctx:Draw(spr)
end
prog:AddEventListener(prog.EvtRender, "OnRender")

function OnExit()
    Dusk.DeleteSprite(spr)
    Dusk.DeleteTexture(tex)

    is:RemoveEventListener(is.EvtMappedInputPress, "OnMappedInputPressed")
    is:RemoveEventListener(is.EvtMappedInputRelease, "OnMappedInputReleased")

    prog:RemoveEventListener(prog.EvtUpdate, "OnUpdate")
    prog:RemoveEventListener(prog.EvtRender, "OnRender")
    prog:RemoveEventListener(prog.EvtExit, "OnExit")
end
prog:AddEventListener(prog.EvtExit, "OnExit")
