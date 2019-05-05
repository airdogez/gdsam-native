#ifndef GDSAM_H
#define GDSAM_H

#include <Godot.hpp>
#include <Reference.hpp>

namespace godot {
	class SAM : public Reference {
		GODOT_CLASS(SAM, Reference)

	private:

	public:
		static void _register_methods();

		// constructor
		SAM();
		void _init() {}
	};
}
#endif
