extends AudioStreamPlayer

onready var playback = get_stream_playback()
const SAM = preload("res://lib/gdsam.gdns")
var sam

func _fill_buffer():
	var to_fill = playback.get_frames_available()
	var size = sam.get_buffer_size()
	
	for i in range(size):
		playback.push_frame(sam.get_buffer_at_pos(i))

func _ready():
	sam = SAM.new()
	sam.set_input("HELLO MY NAME IS SAM")
	sam.generate_tts()
	_fill_buffer()
	play()
