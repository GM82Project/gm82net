#include <thread>
#include <sstream>

#include "gm.h"
#include "Buffer.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// This function creates a named pipe which spits out the entire contents of the relevant buffer.
// It returns the filename of the pipe.
// This is useful for compressing models, as d3d_model_load only accepts filenames.
// However, this won't work for any other such functions, as those have additional checks in place
// using GetFileAttributesW to make sure the file exists, and calling that function with a pipe
// is undefined behaviour that breaks everything.
gmexport const char* buffer_make_pipe(double id) {
    ///buffer_make_pipe(id)
    //id: buffer to use
    //returns: pipe name
    //Creates a single-use pipe using the buffer's data. Currently, this is only usable with d3d_model_load, due to some implementation details.
    //This may be expandable in the future.
    
	Buffer *b = gmdata.FindBuffer(gm_cast<unsigned int>(id));
	if(b == NULL) return "";
	volatile bool can_exit = false;
	std::thread([b, &can_exit]() {
		for (int i = 0;;i++) {
			std::stringstream ss;
			ss << "\\\\.\\pipe\\gm82netpipe." << i;
			gmreturnstring = ss.str();
			HANDLE pipe = CreateNamedPipeA(
				gmreturnstring.c_str(),
				PIPE_ACCESS_OUTBOUND | FILE_FLAG_FIRST_PIPE_INSTANCE,
				PIPE_TYPE_BYTE,
				10,
				100,
				100,
				0,
				NULL
			);
			if (pipe == INVALID_HANDLE_VALUE) continue;
			can_exit = true;

			ConnectNamedPipe(pipe, NULL);
			ConnectNamedPipe(pipe, NULL);
			DWORD bytes_written;
			WriteFile(pipe, b->GetData(), b->GetLength(), &bytes_written, NULL);
			CloseHandle(pipe);
			break;
		}
	}).detach();
	while (!can_exit) Sleep(0);
	return gmreturnstring.c_str();
}