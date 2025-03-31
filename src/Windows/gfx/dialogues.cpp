#include "os/iden.hpp"
#ifdef OS_WINDOWS
#include "gfx/surface.hpp"

#include "Windows/gfx/window.hpp"

#include <Windows.h>

namespace osw32 {
	// https://stackoverflow.com/questions/34092427/winapi-getopenfilename-extension-filter-not-working
	std::vector<char> fileMenuFilter(gfx::fileMenu* mn) {
		std::string filter = "";
		for (size_t f = 0; f < mn->fileFormats.size(); ++f) {
			filter += "(*." + mn->fileFormats[f].extension + ") " + mn->fileFormats[f].name + "$";
			filter += "*." + mn->fileFormats[f].extension + "$";
		}
		std::vector<char> filterc(filter.begin(), filter.end());
		for (size_t b = 0; b < filterc.size(); ++b) {
			if (filterc[b] == '$') {
				filterc[b] = '\0';
			}
		}
		return filterc;
	}
}

std::string gfx::surface::dialogueOpenFile(gfx::fileMenu* mn) {
	osw32::window* win = (osw32::window*)this->data;

	// Copied from AI, forgive my sins
	OPENFILENAME ofn {};
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = win->hwnd;
	ofn.lpstrTitle = "Select a file";
	ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
	std::vector<char> filter = osw32::fileMenuFilter(mn);
	ofn.lpstrFilter = filter.data();

	char filename[512] = "";
	ofn.lpstrFile = filename;
	ofn.nMaxFile = sizeof(filename);
	if (GetOpenFileName(&ofn)) {
		return std::string(filename);
	} else {
		return "";
	}
}

std::string gfx::surface::dialogueSaveFile(fileMenu* mn) {
	osw32::window* win = (osw32::window*)this->data;

	OPENFILENAME ofn {};
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = win->hwnd;
	ofn.lpstrTitle = "Create/Choose a file to save as";
	ofn.Flags = OFN_CREATEPROMPT;
	std::vector<char> filter = osw32::fileMenuFilter(mn);
	ofn.lpstrFilter = filter.data();

	char filename[512] = "";
	ofn.lpstrFile = filename;
	ofn.nMaxFile = sizeof(filename);
	if (GetSaveFileName(&ofn)) {
		return std::string(filename);
	} else {
		return "";
	}
}

#endif