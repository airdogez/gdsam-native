extends AudioStreamPlayer

onready var playback = get_stream_playback()
const SAM = preload("res://lib/gdsam.gdns")
var sam
var phonetic = false

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
	#sam.set_speed(100)
	#sam.set_pitch(64)
	#sam.set_throat(150)
	#sam.set_mouth(200)
	sam.generate_tts(true)
	#sam.generate(text, 128,128,128,128)
	_fill_buffer()
	play()
	


func _on_speed_value_changed(value):
	print(value)
	sam.set_speed(value)

func _on_pitch_value_changed(value):
	sam.set_pitch(value)
	
func _on_mouth_value_changed(value):
	sam.set_mouth(value)
	
func _on_throat_value_changed(value):
	sam.set_throat(value)

func _on_PhoneticCheck_toggled(button_pressed):
	sam.set_singmode(button_pressed)

func _on_SingCheck_toggled(button_pressed):
	phonetic = button_pressed
