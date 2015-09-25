DuskLog("verbose", "Setting up the Window");

local prog = Dusk.GetProgram()
local gs = Dusk.GetGraphicsSystem()
local is = Dusk.GetInputSystem()
local ctx = gs:GetContext()

is:MapKey("pause", Dusk.Keys.Space)

local tex = Dusk.NewTexture("Textures/test.png")
local spr = Dusk.NewSprite(tex)

local xSpeed = 2
local ySpeed = 2
local moving = true

function OnUpdate(timeInfo)
    if not moving then
        return
    end

    local x, y = spr:GetPos()
    local width, height = gs:GetWinSize()

    if x >= width - 100 or x <= 0 then
        xSpeed = xSpeed * -1
    end

    if y >= height - 100 or y <= 0 then
        ySpeed = ySpeed * -1
    end

    x = x + (xSpeed * timeInfo.Delta)
    y = y + (ySpeed * timeInfo.Delta)

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

    prog:RemoveEventListener(prog.EvtUpdate, "OnUpdate")
    prog:RemoveEventListener(prog.EvtRender, "OnRender")
    prog:RemoveEventListener(prog.EvtExit, "OnExit")
end
prog:AddEventListener(prog.EvtExit, "OnExit")

function OnMappedInputPressed(inputId)
	if inputId == "pause" then
		moving = not moving
	end
end
is:AddEventListener(is.EvtMappedInputPress, "OnMappedInputPressed")
