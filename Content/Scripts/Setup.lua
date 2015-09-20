DuskLog("verbose", "Setting up the Window");

local prog = Dusk.GetProgram()
local win = Dusk.GetWindow()
local ctx = Dusk.GetGraphicsContext()

win:SetTitle("Dusk Test")

local tex = Dusk.NewTexture("Textures/test.png")
local spr = Dusk.NewSprite(tex)

prog:AddEventListener(prog.EVT_UPDATE, "OnUpdate")
prog:AddEventListener(prog.EVT_RENDER, "OnRender")
prog:AddEventListener(prog.EVT_EXIT,   "OnExit")

local xSpeed = 2
local ySpeed = 2

function OnUpdate(timeInfo)
    local x, y = spr:GetPos()

    if x >= win:GetWidth() - 100 or x <= 0 then
        xSpeed = xSpeed * -1
    end

    if y >= win:GetHeight() - 100 or y <= 0 then
        ySpeed = ySpeed * -1
    end

    x = x + (xSpeed * timeInfo.Delta)
    y = y + (ySpeed * timeInfo.Delta)

    spr:SetPos(x, y)
end

function OnRender()
    ctx:Draw(spr)
end

function OnExit()
    Dusk.DeleteSprite(spr)
    Dusk.DeleteTexture(tex)

    prog:RemoveEventListener(prog.EVT_UPDATE, "OnUpdate")
    prog:RemoveEventListener(prog.EVT_RENDER, "OnRender")
    prog:RemoveEventListener(prog.EVT_EXIT, "OnExit")
end
