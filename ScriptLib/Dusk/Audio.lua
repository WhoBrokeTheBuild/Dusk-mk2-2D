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

Dusk.NewMusic = function(filename)
	return Dusk.Music( dusk_music_new(filename) );
end

Dusk.DeleteMusic = function(music)
	return Dusk.Music( dusk_music_delete(music.dusk_ptr) );
end

local Music = Dusk.Class(Dusk.Object, function(self, ptr)
  Dusk.Object.init(self, ptr)
end)

function Music:Play()
	dusk_music_play( self.dusk_ptr );
end

function Music:Stop()
	dusk_music_stop( self.dusk_ptr );
end

function Music:Pause()
	dusk_music_pause( self.dusk_ptr );
end

function Music:SetLooping(isLooping)
	dusk_music_set_looping( self.dusk_ptr, isLooping );
end

function Music:IsPlaying()
	return dusk_music_is_playing( self.dusk_ptr );
end

function Music:IsPaused()
	return dusk_music_is_paused( self.dusk_ptr );
end

function Music:IsStopped()
	return dusk_music_is_stopped( self.dusk_ptr );
end

function Music:IsLooping()
	return dusk_music_is_looping( self.dusk_ptr );
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
