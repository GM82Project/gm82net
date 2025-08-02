#define __gm82buf_init
    globalvar __gm82buf_version;
    __gm82buf_version=100


#define buffer_create
    ///buffer_create([filename])
    //filename: optional filename to preload
    //returns: buffer id
    //Creates and returns a buffer index. If a filename is passed, the file is also preloaded to the buffer.
    //Note that unlike 39dll, there isn't a default buffer. You always need to explicitly create and destroy buffers.
    
    var __b; __b=__gm82buf_buffer_create()
    if (argument_count) {
        if (!file_exists(argument0)) show_error("Error creating buffer with file: file '"+string(argument0)+"' does not exist.",0)
        else buffer_load(__b,argument0)
    }
    return __b
//
//