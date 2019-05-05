extends AudioStreamPlayer

onready var playback = get_stream_playback()
const SAM = preload("res://lib/gdsam.gdns")
var sam

func _fill_buffer():
	var buf = sam.get_buffer()
	playback.clear_buffer()
	for i in buf:
		playback.push_frame(Vector2(i,i))

func _ready():
	sam = SAM.new()


func _on_Button_pressed():
	var textfield := $"../Control/TextEdit"
	var text = textfield.text
	sam.set_input(text, false)
	sam.generate_tts(true)
	#sam.generate(text, 128,128,128,128)
	_fill_buffer()
	play()
	
