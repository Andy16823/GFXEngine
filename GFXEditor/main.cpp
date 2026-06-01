#include <iostream>
#include "Editor.h"

using namespace GFXEditor;

int main() {
	Editor editor;
	editor.setResizable(true);
	editor.start(1280, 720, "./shaders", "GFXEditor", false, true);
	return 0;
}