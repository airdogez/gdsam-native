extends Node2D

const SAM = preload("res://lib/gdsam.gdns")


func _ready():
	var sam = SAM.new()
	sam.set_input("HELLO MY NAME IS SAM")
	
