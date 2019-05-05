#ifndef GDSAM_H
#define GDSAM_H

#include <Godot.hpp>
#include <Reference.hpp>

#include <state.h>

namespace godot {
	class SAM : public Reference {
		GODOT_CLASS(SAM, Reference)

	private:

	public:
	  static void _register_methods();

	  void set_input(String text);
	  void set_pitch(int pitch);
	  void set_speed(int speed);
	  void set_mouth(int mouth);
	  void set_throat(int throat);

	  int get_pitch();

	  int generate_tts();

	  void write_wav(char *filename, char *buffer, int bufferlength);
	  Vector2 get_buffer_at_pos(int idx);
	  int get_buffer_size();

	  String get_output();

	  // constructor
	  SAM();
	  void _init() {}

	  SamState state;
	  unsigned char input[256];
	};
}
#endif
