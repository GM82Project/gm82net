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


#define buffer_write_variable
    ///buffer_write_variable(id,value)
    //id: buffer id
    //value: value to write
    //Writes the contents of a variable to a buffer. This is useful if the variable may contain either a real or a string.
    //This method of storage uses 9 bytes for a number, and string length+2 for strings.
    
    if (is_string(argument1)) {
        buffer_write_u8(argument0,1) //string
        buffer_write_u32(argument0,string_byte_length(argument1))
        buffer_write_data(argument0,argument1)
    } else {
        buffer_write_u8(argument0,2) //double
        buffer_write_double(argument0,argument1)
    }


#define buffer_read_variable
    ///buffer_read_variable(id)
    //id: buffer id
    //returns: value
    //Reads a variable written using buffer_write_variable.
    
    var __t;__t=buffer_read_u8(argument0)
    if (__t==1) return buffer_read_data(argument0,buffer_read_u32(argument0))
    if (__t==2) return buffer_read_double(argument0)
    show_error("Error in function buffer_read_variable: invalid type id "+string(__t),0)
    return ansi_char(0)
//
//