extends AudioStreamPlayer

onready var playback = get_stream_playback()
const SAM = preload("res://lib/gdsam.gdns")
var sam

func _fill_buffer():
	var to_fill = playback.get_frames_available()
	var buf = sam.get_buffer()
	
	for i in buf:
		playback.push_frame(Vector2(i,i)/255.0)

func _ready():
	sam = SAM.new()
	sam.set_input("HELLO MY NAME IS SAM")
	sam.generate_tts()
	_fill_buffer()
	play()
