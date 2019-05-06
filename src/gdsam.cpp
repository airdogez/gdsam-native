#include "gdsam.hpp"

#include <sam.h>
#include <reciter.h>
#include <debug.h>

using namespace godot;

void SAM::set_input(String text, bool phonetic){
	memset(input, 0, 256);
	strcat_s((char*)input, 256, text.ascii().get_data());
	strcat_s((char*)input, 256, " ");
	if(!phonetic){
		strcat_s((char*)input, 256, "[");
		if (!textToPhonemes(state, input)){
			Godot::print("Couldn't transform texto to phonemes");
		}
	}
}

void SAM::set_pitch(int pitch){
    state.pitch = (unsigned char) pitch;
}

void SAM::set_speed(int speed){
    state.speed = (unsigned char) speed;
}

void SAM::set_mouth(int mouth){
    state.mouth = (unsigned char) mouth;
}

void SAM::set_throat(int throat){
    state.throat= (unsigned char) throat;
}

void SAM::set_singmode(bool sing){
	state.singmode = sing;
}


void SAM::generate(String text, bool phonetic, int pitch, int speed, int mouth, int throat, bool sing){
    //state = SamState();
	memset(state.buffer, 0, sizeof(state.buffer));
	state.bufferpos = 0;
	state.pitch = pitch;
	state.speed = speed;
	state.mouth = mouth;
	state.throat = throat;
	state.singmode = sing;
    memset(input, 0, 256);
	strcat_s((char*)input, 256, text.ascii().get_data());
	strcat_s((char*)input, 256, " ");
	strcat_s((char*)input, 256, "[");
	if(!phonetic){
		if (!textToPhonemes(state, input))
		{
			Godot::print("Couldn't transform texto to phonemes");
		}
	}
    if (!SAMMain(input, state)){
		Godot::print("Couldn't generate tts");
    }
}


int SAM::generate_tts(int debug){
	state.debug = debug;
	memset(state.buffer, 0, sizeof(state.buffer));
	state.bufferpos = 0;
    if (!SAMMain(input, state)){
		return -1;
    }
	return 0;
}

void SAM::write_wav(char* filename, char* buffer, int bufferlength)
{
	unsigned int filesize;
	unsigned int fmtlength = 16;
	unsigned short int format=1; //PCM
	unsigned short int channels=1;
	unsigned int samplerate = 22050;
	unsigned short int blockalign = 1;
	unsigned short int bitspersample=8;

	FILE *file;
	fopen_s(&file, filename, "wb");
	if (file == NULL) return;
	//RIFF header
	fwrite("RIFF", 4, 1,file);
	filesize=bufferlength + 12 + 16 + 8 - 8;
	fwrite(&filesize, 4, 1, file);
	fwrite("WAVE", 4, 1, file);

	//format chunk
	fwrite("fmt ", 4, 1, file);
	fwrite(&fmtlength, 4, 1, file);
	fwrite(&format, 2, 1, file);
	fwrite(&channels, 2, 1, file);
	fwrite(&samplerate, 4, 1, file);
	fwrite(&samplerate, 4, 1, file); // bytes/second
	fwrite(&blockalign, 2, 1, file);
	fwrite(&bitspersample, 2, 1, file);

	//data chunk
	fwrite("data", 4, 1, file);
	fwrite(&bufferlength, 4, 1, file);
	fwrite(buffer, bufferlength, 1, file);

	fclose(file);
}

Vector2 SAM::get_buffer_at_pos(int idx){
    return Vector2(state.buffer[idx], state.buffer[idx]);
}

int SAM::get_buffer_size(){
    return state.bufferpos/50;
}

Array SAM::get_buffer(){
	Array ar = Array();
	for(int i = 0; i<state.bufferpos/50; i++){
		ar.append(state.buffer[i]);
	}
	return ar;
}

SAM::SAM() {
    state = SamState();
    //memset(input, 0, 256);
}

void SAM::_register_methods() {
	register_method("set_pitch", &SAM::set_pitch);
	register_method("set_mouth", &SAM::set_mouth);
	register_method("set_speed", &SAM::set_speed);
	register_method("set_throat", &SAM::set_throat);
	register_method("set_singmode", &SAM::set_singmode);
	register_method("set_input", &SAM::set_input);

	register_method("get_buffer_at_pos", &SAM::get_buffer_at_pos);
	register_method("get_buffer_size", &SAM::get_buffer_size);
	register_method("get_buffer", &SAM::get_buffer);

	register_method("generate", &SAM::generate);
	register_method("generate_tts", &SAM::generate_tts);
}
