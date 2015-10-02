require "Dusk/Object"

-- Dusk.AudioSystem

Dusk.GetAudioSystem = function()
	return Dusk.AudioSystem( dusk_get_audio_system() )
end

local AudioSystem = Dusk.Class(Dusk.Object, function(self, ptr)
	Dusk.Object.init(self, ptr)
end)

function AudioSystem:GetMusicVolume()

end

function AudioSystem:SetMusicVolume(volume)

end

function AudioSystem:GetSoundVolume()

end

function AudioSystem:SetSoundVolume(volume)

end

Dusk.AudioSystem = AudioSystem

-- Dusk.Music

local Music = Dusk.Class(Dusk.Object, function(self, ptr)
  Dusk.Object.init(self, ptr)
end)

function Music:Play()

end

function Music:Stop()

end

Dusk.Music = Music

-- Dusk.Sound

local Sound = Dusk.Class(Dusk.Object, function(self, ptr)
  Dusk.Object.init(self, ptr)
end)

function Sound:Play()

end

function Sound:Stop()

end

Dusk.Sound = Sound
