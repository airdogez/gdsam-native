#ifndef GDSAM_H
#define GDSAM_H

#include <Godot.hpp>
#include <Reference.hpp>

#include <state.h>

namespace godot
{
class SAM : public Reference
{
	GODOT_CLASS(SAM, Reference)

  private:
	SamState state;
	unsigned char input[256];
	void write_wav(char *filename, char *buffer, int bufferlength);

  public:
	static void _register_methods();

	void set_input(String text,  bool phonetic = false);
	void set_pitch(int pitch);
	void set_speed(int speed);
	void set_mouth(int mouth);
	void set_throat(int throat);
	void set_singmode(bool sing);

	int generate_tts(int debug = 0);
	void generate(String text, int pitch, int speed, int mouth, int throat);

	Vector2 get_buffer_at_pos(int idx);
	int get_buffer_size();
	Array get_buffer();

	// constructor
	SAM();
	void _init() {}

};
} // namespace godot
#endif
